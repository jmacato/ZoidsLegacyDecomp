"""Read the ROM command streams that own editable text."""

from collections import deque
from functools import lru_cache
from pathlib import Path
import re
import struct

import dialogue

ROOT = Path(__file__).resolve().parent.parent
DATABASE_MENU_SETUPS = (
    (0x7F26C8, 152, 0x0066B1),
    (0x7F2928, 105, 0x006845),
    (0x7F2ACC, 200, 0x006962),
)


def address(value):
    return f'0x{value:06X}'


@lru_cache(maxsize=1)
def clean_rom():
    return dialogue.read_rom(ROOT / 'Zoids Legacy (USA).gba')


def menu_call_sites():
    pattern = re.compile(r'(?:RunMenuScript|func_0?8098BB4)\(\s*\(?(?:const \w+ \*|void \*)?\)?\s*(0x08[0-9A-Fa-f]{6})\s*\)')
    result = {}
    for path in sorted((ROOT / 'src').rglob('*.c')):
        for number, line in enumerate(path.read_text().splitlines(), 1):
            for match in pattern.finditer(line):
                root = int(match[1], 16) - dialogue.BASE
                result.setdefault(address(root), []).append(f'{path.relative_to(ROOT)}:{number}')
    return result


@lru_cache(maxsize=1)
def menu_scripts():
    rom = clean_rom()
    blocks = {}
    index = {}
    definitions = {}
    call_sites = menu_call_sites()
    for root in dialogue.menu_roots(rom):
        key = f'menu:{address(root)}'
        commands = []
        local_windows = {}
        pos = root
        while True:
            at = pos
            opcode = rom[pos]
            command = {'at': address(at), 'opcode': f'{opcode:02X}'}
            if opcode == 0:
                command.update(name='End script', raw='00')
                commands.append(command)
                break
            if opcode == 1:
                number, x, y, width, height, flags = dialogue.menu_window_command(rom, pos)[1:]
                window = {'id': number, 'x': x * 8, 'y': y * 8,
                          'width': width * 8, 'height': height * 8,
                          'flags': flags, 'sourceRoot': address(root),
                          'sourceAt': address(at)}
                local_windows[number] = window
                definitions.setdefault(number, []).append(window)
                command.update(name=f'Define window #{number}', window=window)
                pos += 7
            elif opcode in (5, 9):
                number = rom[pos + 1]
                text_offset = pos + 2
                _, pos = dialogue.decode_text(rom, text_offset)
                command.update(name=(f'Draw title in window #{number}'
                                     if opcode == 9 else f'Draw text in window #{number}'),
                               windowId=number, textOffset=address(text_offset))
                index.setdefault(address(text_offset), []).append({
                    'block': key, 'commandIndex': len(commands), 'at': address(at),
                    'windowId': number, 'localWindows': list(local_windows.values())})
            elif opcode == 6:
                command['name'] = f'Draw buffered text in window #{rom[pos + 1]}'
                pos += 2
            elif opcode == 11:
                command['name'] = f'Set window #{rom[pos + 1]} style to {rom[pos + 2]}'
                pos += 3
            elif opcode == 12:
                command['name'] = 'Wait for A or B'
                pos += 1
            else:
                width = dialogue.MENU_LENGTHS.get(opcode)
                if not width:
                    raise ValueError(f'Unsupported menu command at {address(at)}.')
                pos += width
                command['name'] = f'Command {opcode:02X}'
            command['raw'] = rom[at:min(pos, at + 7 if opcode == 1 else at + 2
                                     if opcode in (5, 9) else pos)].hex(' ').upper()
            commands.append(command)
        blocks[key] = {'kind': 'menu', 'root': address(root), 'commands': commands,
                       'callSites': call_sites.get(address(root), []),
                       'windowDefinitions': list(local_windows.values())}

    database_setups = {}
    for table, count, setup in DATABASE_MENU_SETUPS:
        for slot in range(count):
            root = struct.unpack_from('<I', rom, table + slot * 4)[0] - dialogue.BASE
            database_setups[f'menu:{address(root)}'] = blocks[f'menu:{address(setup)}']['windowDefinitions']

    for locations in index.values():
        for location in locations:
            number = location['windowId']
            local = {item['id']: item for item in location.pop('localWindows')}
            setup = database_setups.get(location['block'])
            if setup:
                local = {**{item['id']: item for item in setup}, **local}
            target = local.get(number)
            source = 'script' if target else 'unknown'
            if target is None:
                earlier = [item for item in definitions.get(number, [])
                           if int(item['sourceAt'], 16) < int(location['at'], 16)]
                if earlier:
                    target = earlier[-1]
                    setup = blocks[f"menu:{target['sourceRoot']}"]['windowDefinitions']
                    local = {**{item['id']: item for item in setup}, **local}
                    source = 'nearest earlier script'
            location['window'] = target
            location['windowSource'] = source
            location['windows'] = [local[key] for key in sorted(local)]
    return blocks, index


def battle_quote_context():
    windows = menu_scripts()[0]['menu:0x004037']['windowDefinitions']
    return {'windowId': 1, 'window': next(item for item in windows if item['id'] == 1),
            'windows': windows, 'windowSource': 'script'}


def event_branch_target(rom, start, selector, value, profile):
    pos = start
    depth = 0
    choices = []
    for _ in range(20000):
        opcode = rom[pos]
        if selector in (0x0F, 0x10) and opcode in (0x0E, 0x19, 0x1A, 0x1B, 0x1C):
            depth += 1
        if selector == 0x12 and opcode == 0x11:
            choices.append(0)
        if opcode == 9:
            pos += 2 + rom[pos + 1] * 4
        elif opcode == 0x20:
            pos += 1
            while rom[pos]:
                if rom[pos] == 1:
                    pos += 1
                elif rom[pos] == 2:
                    pos += 2
                elif rom[pos] == 0x0D and choices:
                    choices[-1] += 1
                pos += 1
            pos += 1
        else:
            if opcode > 0x97 or not rom[profile['lengths'] + opcode]:
                raise ValueError(f'Invalid branch command at {address(pos)}.')
            pos += rom[profile['lengths'] + opcode]
        if rom[pos] != selector:
            continue
        if selector in (0x0F, 0x10):
            if depth == 1:
                return pos
            depth -= 1
        elif selector == 0x12:
            if len(choices) == 1:
                if rom[pos + 1] == value:
                    return pos
            else:
                choices[-1] = (choices[-1] - 1) & 255
                if not choices[-1]:
                    choices.pop()
        else:
            return pos
    raise ValueError(f'Branch at {address(start)} did not reach its marker.')


def event_block(rom, root, profile):
    commands = []
    pos = root
    while True:
        at = pos
        opcode = rom[pos]
        if opcode > 0x97:
            raise ValueError(f'Unsupported event command at {address(pos)}.')
        command = {'at': address(at), 'opcode': f'{opcode:02X}',
                   'name': f'Command {opcode:02X}'}
        if opcode == 0:
            command.update(name='End script', raw='00')
            commands.append(command)
            return commands
        if opcode == 0x20:
            command.update(name='Show dialogue', textOffset=address(pos + 1))
            _, pos = dialogue.decode_text(rom, pos + 1)
            command['raw'] = '20'
        elif opcode == 9:
            count = rom[pos + 1]
            end = pos + 2 + count * 4
            children = [struct.unpack_from('<I', rom, at)[0] - dialogue.BASE
                        for at in range(pos + 2, end, 4)]
            command.update(name='Child script table',
                           children=[address(child) for child in children],
                           raw=rom[pos:pos + 2].hex(' ').upper())
            pos = end
        else:
            width = rom[profile['lengths'] + opcode]
            if not width or pos + width > len(rom):
                raise ValueError(f'Invalid event command at {address(pos)}.')
            if opcode == dialogue.EVENT_JUMP:
                target = struct.unpack_from('<I', rom, at + 1)[0] - dialogue.BASE
                command.update(name='Jump', children=[address(target)])
            pos += width
            command['raw'] = rom[at:pos].hex(' ').upper()
        selectors = []
        if opcode in (0x0E, 0x19, 0x1A, 0x1B, 0x1C):
            selectors = [(0x0F, 0), (0x10, 0)]
        elif opcode == 0x11:
            text, _ = dialogue.decode_text(rom, at + 2)
            selectors = [(0x12, choice) for choice in range(text.count('\n') + 1)]
        elif opcode == 0x7E:
            selectors = [(0x7F, 0), (0x80, 0)]
        if selectors:
            command['children'] = [address(event_branch_target(rom, at, selector, value, profile))
                                   for selector, value in selectors]
        commands.append(command)
        if opcode == 0x83:
            command['name'] = 'Return to title'
            return commands


@lru_cache(maxsize=1)
def event_scripts():
    rom = clean_rom()
    profile = dialogue.PROFILE
    blocks = {}
    index = {}
    for event, root in enumerate(dialogue.rom_roots(rom)):
        pending = deque([(root, [])])
        visited = set()
        while pending:
            block_root, path = pending.popleft()
            if block_root in visited:
                continue
            visited.add(block_root)
            key = f'event:{address(block_root)}'
            if key not in blocks:
                blocks[key] = {'kind': 'event', 'root': address(block_root),
                               'commands': event_block(rom, block_root, profile)}
            for command_number, command in enumerate(blocks[key]['commands']):
                if 'textOffset' in command:
                    index.setdefault(command['textOffset'], []).append({
                        'block': key, 'commandIndex': command_number,
                        'at': command['at'], 'event': event,
                        'eventRoot': address(root), 'path': path})
                for child_number, child in enumerate(command.get('children', [])):
                    pending.append((int(child, 16), path + [{
                        'at': command['at'], 'child': child_number,
                        'to': child}] ))
    return blocks, index


def catalog():
    menu_blocks, menu_index = menu_scripts()
    event_blocks, event_index = event_scripts()
    index = dict(menu_index)
    for offset, locations in event_index.items():
        index.setdefault(offset, []).extend(locations)
    return {'blocks': {**menu_blocks, **event_blocks}, 'index': index}


def menu_contexts():
    _, index = menu_scripts()
    return {int(offset, 16): locations[0] for offset, locations in index.items()}
