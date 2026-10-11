"""Find native calls, constants and windows in the decompiled C sources."""

import ast
from functools import lru_cache
from pathlib import Path
import re

ROOT = Path(__file__).resolve().parent.parent
RUN_SCRIPT = 'func_08098BB4'
OPEN_WINDOW = 'func_08098514'
CAST = re.compile(r'\(\s*(?:const\s+|volatile\s+)*(?:void|u8|u16|u32|s8|s16|s32|int|char|struct\s+\w+)\s*\**\s*\)')
DEFINITION = re.compile(r'^[A-Za-z_][\w \t\*]*?\b(\w+)\s*\(([^;{}]*)\)\s*\{', re.M)
PROTOTYPE = re.compile(r'\b(\w+)\s*\([^;{}]*\)\s*asm\("(\w+)"\)')
ALIAS = re.compile(r'\.set\s+(\w+)\s*,\s*(\w+)')
DEFINE = re.compile(r'^\s*#define\s+(\w+)\s+(.+?)\s*$', re.M)


def strip_comments(source):
    return re.sub(r'/\*.*?\*/|//[^\n]*', lambda match: re.sub(r'[^\n]', ' ', match[0]), source, flags=re.S)


@lru_cache(maxsize=1)
def symbols():
    values = {}
    for name, value in re.findall(r'^\s*(\w+)\s*=\s*(0x[0-9A-Fa-f]+)\s*;', (ROOT / 'symbols.ld').read_text(), re.M):
        values[name] = int(value, 16)
    return values


@lru_cache(maxsize=1)
def macros():
    values = {}
    for path in [*sorted((ROOT / 'src').rglob('*.h')), *sorted((ROOT / 'include').rglob('*.h'))]:
        for name, value in DEFINE.findall(strip_comments(path.read_text(errors='replace'))):
            values.setdefault(name, value)
    return values


def evaluate(expression, names, depth=0):
    if depth > 8:
        return None
    text = CAST.sub(' ', expression).strip()
    if not text:
        return None
    def replace(match):
        word = match[0]
        if re.fullmatch(r'0[xX][0-9A-Fa-f]+|\d+', word):
            return str(int(word, 0))
        value = names.get(word)
        if value is None and word.startswith('D_') and re.fullmatch(r'D_0[0-9A-F]{7}', word):
            value = int(word[2:], 16)
        if isinstance(value, str):
            value = evaluate(value, names, depth + 1)
        if value is None:
            raise KeyError(word)
        return str(value)
    try:
        text = re.sub(r'\b(?:0[xX][0-9A-Fa-f]+|\d+)[uUlL]*\b|\b[A-Za-z_]\w*\b', replace, text)
        tree = ast.parse(text, mode='eval')
    except (KeyError, SyntaxError):
        return None
    allowed = (ast.Expression, ast.BinOp, ast.UnaryOp, ast.Constant, ast.Add, ast.Sub, ast.Mult,
               ast.LShift, ast.RShift, ast.BitOr, ast.BitAnd, ast.USub, ast.Invert, ast.FloorDiv)
    if not all(isinstance(node, allowed) for node in ast.walk(tree)):
        return None
    try:
        return int(eval(compile(tree, '<expression>', 'eval')))
    except (ArithmeticError, ValueError):
        return None


def split_arguments(source, start):
    depth, current, arguments = 0, [], []
    for at in range(start, len(source)):
        char = source[at]
        if char in '([{':
            depth += 1
        elif char in ')]}':
            if depth == 0:
                arguments.append(''.join(current).strip())
                return arguments, at
            depth -= 1
        if char == ',' and depth == 0:
            arguments.append(''.join(current).strip())
            current = []
        else:
            current.append(char)
    return None, len(source)


class SourceFile:
    def __init__(self, path):
        self.path = path
        self.text = strip_comments(path.read_text(errors='replace'))
        self.names = {**symbols()}
        for name, value in DEFINE.findall(self.text):
            self.names[name] = value
        for name, value in macros().items():
            self.names.setdefault(name, value)
        for name, symbol in re.findall(r'\b(\w+)\s*\[\s*\]\s*asm\("(D_[0-9A-Fa-f]{8})"\)', self.text):
            self.names[name] = int(symbol[2:], 16)
        self.aliases = {}
        for name, target in PROTOTYPE.findall(self.text):
            self.aliases[name] = target
        for name, target in ALIAS.findall(self.text):
            self.aliases[name] = self.aliases.get(target, target)
        for name, target in re.findall(r'#define\s+(\w+)\s+(func_[0-9A-Fa-f]{8})\b', self.text):
            self.aliases[name] = target
        self.functions = []
        for match in DEFINITION.finditer(self.text):
            name = match[1]
            if name in ('if', 'while', 'for', 'switch'):
                continue
            depth, at = 0, match.end() - 1
            for at in range(match.end() - 1, len(self.text)):
                if self.text[at] == '{':
                    depth += 1
                elif self.text[at] == '}':
                    depth -= 1
                    if depth == 0:
                        break
            self.functions.append((name, self.aliases.get(name, name), match.start(), at))

    def line(self, at):
        return self.text.count('\n', 0, at) + 1

    def calls(self, start=0, end=None):
        end = len(self.text) if end is None else end
        for match in re.finditer(r'\b([A-Za-z_]\w*)\s*\(', self.text[start:end]):
            target = self.aliases.get(match[1], match[1])
            if not re.fullmatch(r'func_[0-9A-Fa-f]{8}', target):
                continue
            arguments, _ = split_arguments(self.text, start + match.end())
            if arguments is not None:
                yield target, arguments, start + match.start()

    def function_at(self, at):
        return next((item for item in self.functions if item[2] <= at <= item[3]), None)

    def locals(self, function):
        names = dict(self.names)
        body = self.text[function[2]:function[3]]
        assigned = {}
        for name, value in re.findall(r'\b(\w+)(?:\s+asm\("\w+"\))?\s*=\s*([^;=]+);', body):
            assigned.setdefault(name, set()).add(evaluate(value, names))
        for name, values in assigned.items():
            # A local only counts as constant when every assignment agrees.
            if len(values) == 1 and None not in values:
                names[name] = values.pop()
        return names


@lru_cache(maxsize=1)
def sources():
    return [SourceFile(path) for path in sorted((ROOT / 'src').rglob('*.c'))]


@lru_cache(maxsize=1)
def callers():
    result = {}
    for source in sources():
        for function in source.functions:
            for target, _, _ in source.calls(function[2], function[3]):
                result.setdefault(target, set()).add((source, function))
    return result
