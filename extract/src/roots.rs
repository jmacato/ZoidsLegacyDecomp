//! ROM addresses referenced by the decomp source, tagged by the call they appear in.

use std::collections::{BTreeMap, HashMap};
use std::fs;
use std::path::Path;

use crate::rom::R;
use crate::{repo_root, BASE, ROM_SIZE};

#[derive(Clone, Debug)]
pub struct Reference {
    pub address: u32,
    pub file: String,
    pub line: u32,
    /// Innermost enclosing call: "func_XXXXXXXX" when the name resolves through an asm alias, else the name.
    pub callee: Option<String>,
    pub arg: usize,
    /// The reference is a whole argument of `callee`, not part of a larger expression.
    pub direct: bool,
    /// Argument texts of `callee`, whitespace-collapsed.
    pub args: Vec<String>,
    /// "literal", or the symbol name used.
    pub via: String,
}

impl Reference {
    pub fn location(&self) -> String {
        format!("{}:{}", self.file, self.line)
    }
}

pub struct Roots {
    pub refs: Vec<Reference>,
    pub symbols: HashMap<String, u32>,
}

fn is_ident_start(byte: u8) -> bool {
    byte.is_ascii_alphabetic() || byte == b'_'
}

fn is_ident(byte: u8) -> bool {
    byte.is_ascii_alphanumeric() || byte == b'_'
}

fn rom_address(value: u32) -> bool {
    (BASE..BASE + ROM_SIZE).contains(&value)
}

fn parse_number(token: &str) -> Option<u32> {
    let token = token.trim_end_matches(|c| c == 'u' || c == 'U' || c == 'l' || c == 'L');
    let hex = token.strip_prefix("0x").or_else(|| token.strip_prefix("0X"))?;
    (hex.len() == 8).then(|| u32::from_str_radix(hex, 16).ok()).flatten()
}

fn symbol_address(name: &str, symbols: &HashMap<String, u32>) -> Option<u32> {
    if let Some(address) = symbols.get(name) {
        return Some(*address);
    }
    let hex = name.strip_prefix("D_").or_else(|| name.strip_prefix("func_"))?;
    (hex.len() == 8).then(|| u32::from_str_radix(hex, 16).ok()).flatten()
}

/// `func_8094484`, `func_08094484_4` -> `func_08094484` (agbcc emits `.set func_08094484_4, func_08094484`).
fn canonical_function(name: &str) -> Option<String> {
    let hex = name.strip_prefix("func_")?;
    let hex = hex.split('_').next().unwrap();
    u32::from_str_radix(hex, 16).ok().map(|address| format!("func_{address:08X}"))
}

fn load_symbols() -> R<HashMap<String, u32>> {
    let text = fs::read_to_string(repo_root().join("symbols.ld")).map_err(|error| error.to_string())?;
    let mut out = HashMap::new();
    for line in text.lines() {
        let line = line.split("/*").next().unwrap();
        let Some((name, value)) = line.split_once('=') else { continue };
        let name = name.trim();
        let value = value.trim().trim_end_matches(';').trim();
        if name.bytes().all(is_ident) && !name.is_empty() {
            if let Some(address) = value.strip_prefix("0x").and_then(|hex| u32::from_str_radix(hex, 16).ok()) {
                out.entry(name.to_string()).or_insert(address);
            }
        }
    }
    Ok(out)
}

/// `NAME = 0x08XXXXXX,` enum entries and `#define NAME 0x08XXXXXX` lines.
fn constants(text: &str, out: &mut HashMap<String, u32>) {
    for line in text.lines() {
        let line = line.split("//").next().unwrap().split("/*").next().unwrap().trim();
        let (name, value) = if let Some(rest) = line.strip_prefix("#define") {
            let mut parts = rest.split_whitespace();
            match (parts.next(), parts.next(), parts.next()) {
                (Some(name), Some(value), None) => (name, value),
                _ => continue,
            }
        } else if let Some((name, value)) = line.split_once('=') {
            (name.trim(), value.trim().trim_end_matches(','))
        } else {
            continue;
        };
        if name.is_empty() || !name.bytes().all(|byte| byte.is_ascii_uppercase() || byte.is_ascii_digit() || byte == b'_') {
            continue;
        }
        if let Some(address) = parse_number(value.trim_matches(|c| c == '(' || c == ')')).filter(|value| rom_address(*value)) {
            out.insert(name.to_string(), address);
        }
    }
}

/// `name ... asm("target")` declarations: name -> target.
fn aliases(text: &str) -> HashMap<String, String> {
    let bytes = text.as_bytes();
    let mut out = HashMap::new();
    let mut search = 0;
    while let Some(found) = text[search..].find("asm(\"") {
        let at = search + found;
        search = at + 5;
        if at > 0 && is_ident(bytes[at - 1]) {
            continue;
        }
        let Some(close) = text[at + 5..].find('"') else { break };
        let target = &text[at + 5..at + 5 + close];
        if target.is_empty() || !target.bytes().all(is_ident) || !is_ident_start(target.as_bytes()[0]) {
            continue;
        }
        let mut index = at;
        loop {
            while index > 0 && bytes[index - 1].is_ascii_whitespace() {
                index -= 1;
            }
            if index == 0 {
                break;
            }
            let close = bytes[index - 1];
            let open = match close {
                b')' => b'(',
                b']' => b'[',
                _ => break,
            };
            let mut depth = 0;
            while index > 0 {
                index -= 1;
                if bytes[index] == close {
                    depth += 1;
                } else if bytes[index] == open {
                    depth -= 1;
                    if depth == 0 {
                        break;
                    }
                }
            }
        }
        let end = index;
        while index > 0 && is_ident(bytes[index - 1]) {
            index -= 1;
        }
        if index < end {
            out.insert(text[index..end].to_string(), target.to_string());
        }
    }
    out
}

struct Frame {
    callee: Option<String>,
    paren: bool,
    arg: usize,
    arg_start: usize,
    args: Vec<String>,
    refs: Vec<(usize, Option<String>)>,
    /// (variable, argument index, line, ROM addresses assigned to it earlier in the function)
    uses: Vec<(String, usize, u32, Vec<u32>)>,
}

/// `name = (cast) <token>;`: the plain variable assigned the token at start..end, if any.
fn assigned_name(text: &str, start: usize, end: usize) -> Option<String> {
    let bytes = text.as_bytes();
    let mut after = end;
    while after < bytes.len() && (bytes[after].is_ascii_whitespace() || bytes[after] == b')') {
        after += 1;
    }
    if after >= bytes.len() || bytes[after] != b';' {
        return None;
    }
    let mut index = start;
    loop {
        while index > 0 && bytes[index - 1].is_ascii_whitespace() {
            index -= 1;
        }
        if index > 0 && bytes[index - 1] == b')' {
            let mut depth = 0;
            while index > 0 {
                index -= 1;
                match bytes[index] {
                    b')' => depth += 1,
                    b'(' => {
                        depth -= 1;
                        if depth == 0 {
                            break;
                        }
                    }
                    _ => {}
                }
            }
            continue;
        }
        break;
    }
    if index == 0 || bytes[index - 1] != b'=' || (index >= 2 && b"=!<>+-*/&|^%".contains(&bytes[index - 2])) {
        return None;
    }
    index -= 1;
    while index > 0 && bytes[index - 1].is_ascii_whitespace() {
        index -= 1;
    }
    let end = index;
    while index > 0 && is_ident(bytes[index - 1]) {
        index -= 1;
    }
    (index < end && is_ident_start(bytes[index]) && (index == 0 || !matches!(bytes[index - 1], b'.' | b'>'))).then(|| text[index..end].to_string())
}

/// `(const void *)(0x08...)` -> `0x08...`
pub fn strip_casts(text: &str) -> &str {
    let mut text = text.trim();
    while text.starts_with('(') {
        let mut depth = 0;
        let mut close = None;
        for (index, byte) in text.bytes().enumerate() {
            match byte {
                b'(' => depth += 1,
                b')' => {
                    depth -= 1;
                    if depth == 0 {
                        close = Some(index);
                        break;
                    }
                }
                _ => {}
            }
        }
        let Some(close) = close else { break };
        let rest = text[close + 1..].trim();
        text = if rest.is_empty() { text[1..close].trim() } else { rest };
    }
    text
}

fn collapse(text: &str) -> String {
    text.split_whitespace().collect::<Vec<_>>().join(" ")
}

fn scan(path: &Path, relative: &str, symbols: &HashMap<String, u32>, global: &HashMap<String, String>, named: &HashMap<String, u32>, out: &mut Vec<Reference>) -> R<()> {
    let text = fs::read_to_string(path).map_err(|error| format!("{}: {error}", path.display()))?;
    let local = aliases(&text);
    let resolve = |name: &str| -> Option<u32> {
        match local.get(name).or_else(|| global.get(name)) {
            Some(target) => symbol_address(target, symbols),
            None => symbol_address(name, symbols).or_else(|| named.get(name).copied()),
        }
    };
    let callee_name = |name: &str| -> String {
        match local.get(name).or_else(|| global.get(name)) {
            Some(target) => canonical_function(target).unwrap_or_else(|| name.to_string()),
            None => canonical_function(name).unwrap_or_else(|| name.to_string()),
        }
    };
    let asm_file = relative.ends_with(".s") || relative.ends_with(".inc");
    let bytes = text.as_bytes();
    let mut stack: Vec<Frame> = Vec::new();
    let mut assigned: HashMap<String, Vec<u32>> = HashMap::new();
    let mut line = 1u32;
    let mut index = 0;

    let push_ref = |stack: &mut Vec<Frame>, out: &mut Vec<Reference>, address: u32, line: u32, via: String, token: &str| {
        let call = stack.iter().rposition(|frame| frame.callee.is_some());
        let (callee, arg) = call.map_or((None, 0), |position| (stack[position].callee.clone(), stack[position].arg));
        out.push(Reference { address, file: relative.to_string(), line, callee, arg, direct: false, args: Vec::new(), via });
        if let Some(position) = call {
            let top = position == stack.len() - 1;
            stack[position].refs.push((out.len() - 1, top.then(|| token.to_string())));
        }
    };

    while index < bytes.len() {
        let byte = bytes[index];
        if byte == b'\n' {
            line += 1;
            index += 1;
            continue;
        }
        if text[index..].starts_with("//") || (asm_file && byte == b'@') {
            while index < bytes.len() && bytes[index] != b'\n' {
                index += 1;
            }
            continue;
        }
        if text[index..].starts_with("/*") {
            let end = text[index + 2..].find("*/").map_or(bytes.len(), |end| index + 4 + end);
            line += text[index..end].matches('\n').count() as u32;
            index = end;
            continue;
        }
        if byte == b'"' || (byte == b'\'' && !asm_file) {
            let mut end = index + 1;
            while end < bytes.len() && bytes[end] != byte {
                if bytes[end] == b'\\' {
                    end += 1;
                }
                end += 1;
            }
            let content = &text[index + 1..end.min(bytes.len())];
            let alias = !content.is_empty() && content.bytes().all(is_ident);
            if byte == b'"' && !alias {
                let mut offset = 0;
                let content_bytes = content.as_bytes();
                while offset < content_bytes.len() {
                    if is_ident(content_bytes[offset]) && (offset == 0 || !is_ident(content_bytes[offset - 1])) {
                        let mut stop = offset;
                        while stop < content_bytes.len() && is_ident(content_bytes[stop]) {
                            stop += 1;
                        }
                        let token = &content[offset..stop];
                        let value = if content_bytes[offset].is_ascii_digit() { parse_number(token) } else { None };
                        if let Some(value) = value.filter(|value| rom_address(*value)) {
                            let at_line = line + content[..offset].matches('\n').count() as u32;
                            out.push(Reference { address: value, file: relative.to_string(), line: at_line, callee: None, arg: 0, direct: false, args: Vec::new(), via: "asm".into() });
                        }
                        offset = stop;
                    } else {
                        offset += 1;
                    }
                }
            }
            line += content.matches('\n').count() as u32;
            index = (end + 1).min(bytes.len());
            continue;
        }
        if is_ident_start(byte) || byte.is_ascii_digit() {
            let start = index;
            while index < bytes.len() && (is_ident(bytes[index]) || (bytes[start].is_ascii_digit() && bytes[index] == b'.')) {
                index += 1;
            }
            let token = &text[start..index];
            if byte.is_ascii_digit() {
                if let Some(value) = parse_number(token).filter(|value| rom_address(*value)) {
                    push_ref(&mut stack, out, value, line, "literal".into(), token);
                    if let Some(name) = assigned_name(&text, start, index) {
                        assigned.entry(name).or_default().push(value);
                    }
                }
                continue;
            }
            let mut next = index;
            while next < bytes.len() && (bytes[next] == b' ' || bytes[next] == b'\t') {
                next += 1;
            }
            if next < bytes.len() && bytes[next] == b'(' && !["if", "while", "for", "switch", "return", "sizeof", "asm", "__asm__", "volatile", "__volatile__"].contains(&token) {
                stack.push(Frame { callee: Some(callee_name(token)), paren: true, arg: 0, arg_start: next + 1, args: Vec::new(), refs: Vec::new(), uses: Vec::new() });
                index = next + 1;
                continue;
            }
            if let Some(value) = resolve(token).filter(|value| rom_address(*value)) {
                push_ref(&mut stack, out, value, line, token.to_string(), token);
                if let Some(name) = assigned_name(&text, start, index) {
                    assigned.entry(name).or_default().push(value);
                }
            } else if let Some(candidates) = assigned.get(token) {
                if let Some(frame) = stack.last_mut().filter(|frame| frame.callee.is_some()) {
                    frame.uses.push((token.to_string(), frame.arg, line, candidates.clone()));
                }
            }
            continue;
        }
        match byte {
            b'(' | b'[' | b'{' => {
                if byte == b'{' && stack.is_empty() {
                    assigned.clear();
                }
                stack.push(Frame { callee: None, paren: byte == b'(', arg: 0, arg_start: index + 1, args: Vec::new(), refs: Vec::new(), uses: Vec::new() });
            }
            b')' | b']' | b'}' => {
                if let Some(mut frame) = stack.pop() {
                    if frame.callee.is_some() {
                        frame.args.push(collapse(&text[frame.arg_start..index]));
                        let args: Vec<String> = if frame.args.len() == 1 && frame.args[0].is_empty() { Vec::new() } else { frame.args.clone() };
                        for (name, arg, at_line, candidates) in frame.uses {
                            if frame.args.get(arg).map_or(false, |text| strip_casts(text) == name) {
                                for address in candidates {
                                    out.push(Reference { address, file: relative.to_string(), line: at_line, callee: frame.callee.clone(), arg, direct: true, args: args.clone(), via: format!("assigned:{name}") });
                                }
                            }
                        }
                        for (reference, token) in frame.refs {
                            let arg = out[reference].arg;
                            out[reference].direct = token.map_or(false, |token| frame.args.get(arg).map_or(false, |text| strip_casts(text).trim_start_matches('&').trim() == token));
                            out[reference].args = args.clone();
                        }
                    }
                }
            }
            b',' => {
                if let Some(frame) = stack.last_mut() {
                    if frame.callee.is_some() && frame.paren {
                        frame.args.push(collapse(&text[frame.arg_start..index]));
                        frame.arg += 1;
                        frame.arg_start = index + 1;
                    }
                }
            }
            _ => {}
        }
        index += 1;
    }
    Ok(())
}

fn source_files(dir: &Path, out: &mut Vec<std::path::PathBuf>) -> R<()> {
    let mut entries: Vec<_> = fs::read_dir(dir).map_err(|error| error.to_string())?.filter_map(Result::ok).map(|entry| entry.path()).collect();
    entries.sort();
    for path in entries {
        if path.is_dir() {
            source_files(&path, out)?;
        } else if matches!(path.extension().and_then(|ext| ext.to_str()), Some("c" | "h" | "s" | "inc")) {
            out.push(path);
        }
    }
    Ok(())
}

impl Roots {
    pub fn scan() -> R<Roots> {
        let symbols = load_symbols()?;
        let root = repo_root();
        let mut files = Vec::new();
        source_files(&root.join("src"), &mut files)?;
        let mut global: HashMap<String, String> = HashMap::new();
        let mut ambiguous: Vec<String> = Vec::new();
        let mut named: HashMap<String, u32> = HashMap::new();
        for path in &files {
            let text = fs::read_to_string(path).map_err(|error| error.to_string())?;
            constants(&text, &mut named);
            for (name, target) in aliases(&text) {
                match global.get(&name) {
                    Some(existing) if *existing != target => ambiguous.push(name),
                    _ => {
                        global.insert(name, target);
                    }
                }
            }
        }
        for name in ambiguous {
            global.remove(&name);
        }
        let mut refs = Vec::new();
        for path in &files {
            let relative = path.strip_prefix(&root).unwrap().to_string_lossy().into_owned();
            scan(path, &relative, &symbols, &global, &named, &mut refs)?;
        }
        Ok(Roots { refs, symbols })
    }

    /// Direct arguments `arg` of calls to the function at `callee`.
    pub fn calls(&self, callee: u32, arg: usize) -> Vec<&Reference> {
        let name = format!("func_{callee:08X}");
        self.refs.iter().filter(|reference| reference.callee.as_deref() == Some(name.as_str()) && reference.arg == arg && reference.direct).collect()
    }

    pub fn at(&self, address: u32) -> Vec<&Reference> {
        self.refs.iter().filter(|reference| reference.address == address).collect()
    }

    /// A ROM address that the decomp source references; a port may start only from these.
    pub fn require(&self, address: u32) -> R<Vec<String>> {
        let found: Vec<String> = self.at(address).iter().map(|reference| reference.location()).collect();
        if found.is_empty() {
            return Err(format!("0x{address:08X} is not referenced by the decomp source"));
        }
        Ok(found)
    }

    pub fn by_address(&self) -> BTreeMap<u32, Vec<&Reference>> {
        let mut out: BTreeMap<u32, Vec<&Reference>> = BTreeMap::new();
        for reference in &self.refs {
            out.entry(reference.address).or_default().push(reference);
        }
        out
    }
}
