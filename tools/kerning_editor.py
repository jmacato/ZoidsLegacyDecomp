"""Serve an original-ROM font editor with JSON autosave."""

import argparse
from collections import Counter
import hashlib
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer
import json
from pathlib import Path
import re
import struct
import threading
from urllib.parse import urlparse

import dialogue

ROOT = Path(__file__).resolve().parent.parent
CHOICES = ROOT / 'kerning-choices.json'


def font_data(rom):
    if hashlib.sha1(rom).hexdigest() != dialogue.ROM_SHA1:
        raise ValueError('Use the clean USA ROM.')
    glyphs = []
    for i in range(22):
        first, count, _, pointer = struct.unpack_from('<HBBI', rom, 0x7A0A98 + i * 8)
        for code in range(first, first + count):
            char = dialogue.readable(code.to_bytes(2, 'big'))
            if len(char) != 1:
                continue
            offset = pointer - dialogue.BASE + (code - first) * 32
            raw = rom[offset:offset + 32]
            pixels = [(raw[y * 2 + x // 4] >> ((x % 4) * 2)) & 3
                      for y in range(16) for x in range(8)]
            columns = [x for x in range(8) if any(pixels[y * 8 + x] for y in range(16))]
            left, right = (min(columns), max(columns) + 1) if columns else (0, 0)
            glyphs.append(dict(code=f'{code:04X}', char=char, pixels=pixels,
                               left=left, width=right-left, advance=min(right-left+1, 8) if columns else 4))
    samples = []
    draft = ROOT / 'scene-translation.json'
    if draft.exists():
        for entry in json.loads(draft.read_text())['entries']:
            text = re.sub(r'\{[^}]*\}', '', entry['english_draft'].replace('{03}', 'Zeru'))
            samples.append(dict(label=entry['scene'], text=text))
    known = {g['char']: g['code'] for g in glyphs}
    counts = Counter((known[a], known[b]) for sample in samples
                     for a, b in zip(sample['text'], sample['text'][1:]) if a in known and b in known)
    return dict(glyphs=glyphs, samples=samples,
                common=[dict(key=f'{a}:{b}', count=n) for (a,b),n in counts.most_common(160)])


def defaults():
    return dict(version=1, font_sha1=dialogue.ROM_SHA1, spacing='proportional', letter_spacing=0, advances={}, pairs={})


def validate(data, codes):
    if not isinstance(data, dict) or data.get('version') != 1 or data.get('font_sha1') != dialogue.ROM_SHA1:
        raise ValueError('This file does not belong to the original USA font.')
    if data.get('spacing') not in ('proportional', 'original'):
        raise ValueError('Invalid base spacing.')
    spacing = data.get('letter_spacing', 0)
    if type(spacing) is not int or not -4 <= spacing <= 8:
        raise ValueError('Default letter spacing must be an integer from -4 to 8.')
    data = {**data, 'letter_spacing': spacing}
    for field, low, high in [('advances', 1, 16), ('pairs', -6, 8)]:
        values = data.get(field)
        if not isinstance(values, dict):
            raise ValueError(f'Invalid {field}.')
        for key, value in values.items():
            parts = key.split(':')
            if len(parts) != (2 if field == 'pairs' else 1) or any(p not in codes for p in parts):
                raise ValueError(f'Unknown glyph in {key}.')
            if type(value) is not int or not low <= value <= high:
                raise ValueError(f'{field} must contain integers from {low} to {high}.')
    return {key: data[key] for key in defaults()}


def serve(port, choices=CHOICES):
    data = font_data((ROOT / 'Zoids Legacy (USA).gba').read_bytes())
    codes = {g['code'] for g in data['glyphs']}
    lock = threading.Lock()
    if choices.exists():
        validate(json.loads(choices.read_text()), codes)
    else:
        choices.write_text(json.dumps(defaults(), indent=2) + '\n')

    class Handler(BaseHTTPRequestHandler):
        def send(self, body, content_type='application/json', status=200):
            if not isinstance(body, bytes):
                body = json.dumps(body, ensure_ascii=False).encode()
            self.send_response(status)
            self.send_header('Content-Type', content_type)
            self.send_header('Content-Length', str(len(body)))
            self.send_header('Cache-Control', 'no-store')
            self.end_headers()
            self.wfile.write(body)

        def do_GET(self):
            path = urlparse(self.path).path
            if path == '/font':
                self.send(data)
            elif path == '/choices':
                with lock:
                    self.send(json.loads(choices.read_text()))
            elif path in ('/', '/editor.js'):
                filename = 'kerning_editor.html' if path == '/' else 'kerning_editor.js'
                self.send(Path(__file__).with_name(filename).read_bytes(),
                          'text/html; charset=utf-8' if path == '/' else 'text/javascript; charset=utf-8')
            else:
                self.send({'error': 'Not found'}, status=404)

        def do_POST(self):
            if self.path != '/choices':
                self.send({'error': 'Not found'}, status=404)
                return
            origin = self.headers.get('Origin')
            if origin and origin != f'http://127.0.0.1:{self.server.server_port}':
                self.send({'error': 'Unexpected origin'}, status=403)
                return
            try:
                size = int(self.headers.get('Content-Length', '0'))
                if not 0 < size <= 1024 * 1024:
                    raise ValueError('Invalid request size.')
                saved = validate(json.loads(self.rfile.read(size)), codes)
                with lock:
                    temp = choices.with_suffix('.json.tmp')
                    temp.write_text(json.dumps(saved, ensure_ascii=False, indent=2) + '\n')
                    temp.replace(choices)
                self.send({'saved': str(choices)})
            except (ValueError, OSError) as error:
                self.send({'error': str(error)}, status=400)

        def log_message(self, *args):
            pass

    server = ThreadingHTTPServer(('127.0.0.1', port), Handler)
    print(f'Editor: http://127.0.0.1:{server.server_port}\nAutosave: {choices}', flush=True)
    server.serve_forever()


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--port', type=int, default=8766)
    parser.add_argument('--choices', type=Path, default=CHOICES)
    args = parser.parse_args()
    serve(args.port, args.choices)
