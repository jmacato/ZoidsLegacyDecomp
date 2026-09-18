"""Encode and decode Zoids Legacy script text and control tokens."""


import re


ROM_SHA1 = "460fa2158606097f6e6f63ce966d2d6ecdd58d70"
ROM_SIZE = 0x800000
BASE = 0x08000000
FONT_TABLE = 0x7A0A98
TOKEN = re.compile(r"\{([0-9A-Fa-f]{2}(?: [0-9A-Fa-f]{2})*)\}")


def text_units(data: bytes, start: int):
    pos = start
    while pos < len(data):
        value = data[pos]
        if value == 0:
            return
        width = {1: 2, 2: 3}.get(value, 2 if 0x80 <= value <= 0x9F else 1)
        if pos + width > len(data):
            raise ValueError(f"Truncated text at 0x{pos:X}.")
        yield data[pos:pos + width]
        pos += width
    raise ValueError(f"Missing text terminator at 0x{start:X}.")


def readable(unit: bytes) -> str:
    if unit == b"\x0a":
        return "\n"
    if unit[0] < 0x20:
        return "{" + unit.hex(" ").upper() + "}"
    try:
        char = unit.decode("shift_jis")
        # Only narrow full-width ASCII. Other characters retain their exact mapping.
        if len(unit) == 2 and len(char) == 1:
            if char == "\u3000":
                return " "
            if 0xFF01 <= ord(char) <= 0xFF5E and char not in "｛｝":
                return chr(ord(char) - 0xFEE0)
            if char.encode("shift_jis") == unit and char not in "{}":
                return char
    except UnicodeError:
        pass
    return "{" + unit.hex(" ").upper() + "}"


def decode_text(data: bytes, start: int) -> tuple[str, int]:
    if not 0 <= start < len(data):
        raise ValueError("Text offset is outside the ROM.")
    units = list(text_units(data, start))
    return "".join(map(readable, units)), start + sum(map(len, units)) + 1


def encode_text(text: str) -> bytes:
    result = bytearray()
    pos = 0
    while pos < len(text):
        char = text[pos]
        if char == "{":
            match = TOKEN.match(text, pos)
            if match is None:
                raise ValueError(f"Invalid byte token at character {pos}.")
            result.extend(bytes.fromhex(match[1]))
            pos = match.end()
            continue
        if char == "\n":
            result.append(10)
        elif char == " ":
            result.extend(b"\x81\x40")
        elif "!" <= char <= "~" and char not in "{}":
            result.extend(chr(ord(char) + 0xFEE0).encode("shift_jis"))
        elif ord(char) >= 0x80:
            result.extend(char.encode("shift_jis"))
        else:
            raise ValueError(f"Use a byte token for character {char!r}.")
        pos += 1
    result.append(0)
    _, end = decode_text(bytes(result), 0)
    if end != len(result):
        raise ValueError("Text contains an early terminator.")
    return bytes(result)


def control_units(raw: bytes) -> list[bytes]:
    return [unit for unit in text_units(raw, 0) if unit[0] < 0x20 and unit != b"\n"]
