"""Wrap event dialogue to the USA ROM's fixed-width text boxes."""

import re

TOKEN = re.compile(r"\{[0-9A-Fa-f]{2}(?: [0-9A-Fa-f]{2})*\}")
SPEAKER = re.compile(r"^(\{01 02\}[^\n]+\n)(.*)$", re.S)
PLAYER_COLUMNS = 8
FULL_WIDTH_SPEAKERS = {
    'Townsperson', 'Child', 'Old man', 'Store Clerk', 'Store clerk',
    'Barkeeper', 'Waitress', 'Lab researcher', 'Warrior', 'Employee',
    'Emploee', 'Villager', 'Villagers', 'Memo',
}


def visible_width(text):
    return len(TOKEN.sub(lambda match: 'X' * PLAYER_COLUMNS if match[0] == '{03}' else '', text))


def original_columns(entry):
    if entry['english_offset'] == '0x050F28':
        return max(map(visible_width, entry['english_original'].splitlines()))
    match = SPEAKER.match(entry['english_original'])
    if not match:
        return 28
    name = match[1][len('{01 02}'):].rstrip('\n')
    # The portrait window is 22 tiles wide; the full window is 30. Borders use two.
    return 28 if name in FULL_WIDTH_SPEAKERS else 20


def wrap_paragraph(text, columns, indent):
    if re.search(r"[{}]", TOKEN.sub("", text)):
        raise ValueError("Invalid control token in dialogue.")
    words, word = [], ''
    for match in re.finditer(r'\{[0-9A-Fa-f ]+\}|\s+|[^\s{}]+', text):
        value = match[0]
        if value.isspace():
            if word:
                words.append(word)
                word = ''
        else:
            word += value
    if word:
        words.append(word)
    lines, line = [], ''
    for word in words:
        if visible_width(word) > columns - len(indent):
            raise ValueError(f'Word exceeds {columns} columns: {word}')
        candidate = line + (' ' if line.strip() else '') + word
        if visible_width(candidate) > columns:
            lines.append(line)
            line = indent + word
        else:
            line = candidate
    if line:
        lines.append(line)
    return '\n'.join(lines)


def wrap_entry(entry):
    text = entry['english_draft']
    columns = original_columns(entry)
    if entry['english_offset'] == '0x050F28':
        if len(text.splitlines()) != 2 or any(visible_width(line) > columns for line in text.splitlines()):
            raise ValueError('Keep the two menu choices within their original width.')
        return text
    match = SPEAKER.match(text)
    header, body = (match[1], match[2]) if match else ('', text)
    return header + wrap_paragraph(body, columns, ' ' if header else '')


def check_entry(entry):
    columns = original_columns(entry)
    if entry.get('text_columns') != columns or entry.get('player_name_columns') != PLAYER_COLUMNS:
        raise ValueError(f'Incorrect line limits at {entry["english_offset"]}.')
    for line in entry['english_draft'].splitlines():
        if visible_width(line) > columns:
            raise ValueError(f'Line exceeds {columns} columns at {entry["english_offset"]}.')
