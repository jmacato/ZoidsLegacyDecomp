"""Replace title menu labels while keeping the original sprite layout."""

import struct

AREA = 0xB80000
GRAPHICS = 0x102EE0
GRAPHICS_POINTER = 0x9B814
# Each digit holds one row of a three-pixel glyph, from top to bottom.
GLYPHS = {
    ' ': '0000000',
    'A': '2557555',
    'C': '3444443',
    'E': '7447447',
    'G': '3447553',
    'I': '7222227',
    'J': '1111152',
    'N': '5577555',
    'O': '2555552',
    'P': '6556444',
    'R': '6556555',
    'S': '3442116',
    'T': '7222222',
    'U': '5555557',
    'V': '5555552',
}
PRESS_START_AREA = 0xB81000
PRESS_START_GRAPHICS = 0x102B3C
PRESS_START_GLYPHS = {
    ' ': (0, 0, 0, 0, 0, 0, 0),
    'A': (14, 17, 17, 31, 17, 17, 17),
    'L': (16, 16, 16, 16, 16, 16, 31),
    'P': (30, 17, 17, 30, 16, 16, 16),
    'R': (30, 17, 17, 30, 20, 18, 17),
    'S': (15, 16, 16, 14, 1, 1, 30),
    'T': (31, 4, 4, 4, 4, 4, 4),
    'U': (17, 17, 17, 17, 17, 17, 14),
}
PRESS_START_POINTER = 0x9B7F4


def patch(rom, labels):
    if labels is None:
        return
    if set(labels) - {'press_start'} != {'continue', 'new_game', 'options'}:
        raise ValueError('Title menu requires continue, new_game, and options labels.')
    if struct.unpack_from('<I', rom, GRAPHICS_POINTER)[0] != 0x08000000 + GRAPHICS:
        raise ValueError('Unexpected title menu graphics pointer.')
    tiles = decompress(rom, GRAPHICS)
    if len(tiles) != 0x8C0:
        raise ValueError('Unexpected title menu graphics size.')
    # Continue has separate tiles for the available and disabled states.
    for key, first, width, color in (
            ('options', 0, 32, 6), ('continue', 6, 48, 6),
            ('new_game', 12, 48, 6), ('continue', 40, 48, 5)):
        pixels = render_label(labels[key], width, color)
        # The rightmost 16 pixels precede the leftmost 32 pixels in the ROM.
        order = list(range(4, 6)) + list(range(4)) if width == 48 else list(range(4))
        first = first - 2 if width == 48 else first
        for index, column in enumerate(order):
            for y in range(8):
                for x in range(0, 8, 2):
                    tiles[(first + index) * 32 + y * 4 + x // 2] = (
                        pixels[y][column * 8 + x] | pixels[y][column * 8 + x + 1] << 4)
    write_graphics(rom, tiles, AREA, GRAPHICS_POINTER)
    if 'press_start' in labels:
        patch_press_start(rom, labels['press_start'])


def write_graphics(rom, tiles, area, pointer):
    # Literal LZ77 groups avoid a compressor dependency. The BIOS accepts them.
    packed = bytearray(struct.pack('<I', len(tiles) << 8 | 0x10))
    for offset in range(0, len(tiles), 8):
        packed.append(0)
        packed.extend(tiles[offset:offset + 8])
    packed.extend(bytes(-len(packed) % 4))
    if area + len(packed) > len(rom) or any(b != 255 for b in rom[area:area + len(packed)]):
        raise ValueError('Title menu graphics overlap existing data.')
    rom[area:area + len(packed)] = packed
    struct.pack_into('<I', rom, pointer, 0x08000000 + area)


def patch_press_start(rom, label):
    if struct.unpack_from('<I', rom, PRESS_START_POINTER)[0] != 0x08000000 + PRESS_START_GRAPHICS:
        raise ValueError('Unexpected Press Start graphics pointer.')
    text = label.upper()
    if not text or len(text) * 6 > 72 or set(text) - PRESS_START_GLYPHS.keys():
        raise ValueError(f'Press Start label does not fit or uses unsupported glyphs: {label}')
    pixels = [[0] * 72 for _ in range(8)]
    left = (72 - len(text) * 6) // 2
    # Keep the original white-to-gray gradient and dark shadow.
    for index, char in enumerate(text):
        for y, row in enumerate(PRESS_START_GLYPHS[char]):
            for x in range(5):
                if row & (16 >> x):
                    column = left + index * 6 + x
                    pixels[y + 1][column + 1] = 4
                    pixels[y][column] = 1 if y < 3 else 2 if y < 5 else 3
    tiles = bytearray(9 * 32)
    for y in range(8):
        for x in range(0, 72, 2):
            tiles[x // 8 * 32 + y * 4 + x % 8 // 2] = pixels[y][x] | pixels[y][x + 1] << 4
    write_graphics(rom, tiles, PRESS_START_AREA, PRESS_START_POINTER)


def decompress(rom, offset):
    if rom[offset] != 0x10:
        raise ValueError('Expected BIOS LZ77 title menu graphics.')
    size = int.from_bytes(rom[offset + 1:offset + 4], 'little')
    offset += 4
    output = bytearray()
    while len(output) < size:
        flags = rom[offset]
        offset += 1
        for bit in range(7, -1, -1):
            if len(output) == size:
                break
            if flags & (1 << bit):
                first, second = rom[offset:offset + 2]
                offset += 2
                distance = ((first & 15) << 8) + second + 1
                for _ in range((first >> 4) + 3):
                    output.append(output[-distance])
            else:
                output.append(rom[offset])
                offset += 1
    return output


def render_label(label, width, color):
    text = label.upper()
    if not text or len(text) * 4 - 1 > width or set(text) - GLYPHS.keys():
        raise ValueError(f'Title menu label does not fit or uses unsupported glyphs: {label}')
    pixels = [[4] * width for _ in range(8)]
    left = (width - (len(text) * 4 - 1)) // 2
    for index, char in enumerate(text):
        for y, row in enumerate(GLYPHS[char], 1):
            for x in range(3):
                if int(row) & (4 >> x):
                    pixels[y][left + index * 4 + x] = color
    return pixels
