#!/usr/bin/env python3
"""This program compiles each decomp region and compares it with a user ROM."""

from __future__ import annotations

import argparse
import hashlib
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile

import linklib


ROOT = Path(__file__).resolve().parents[1]
EXPECTED_SHA1 = "460fa2158606097f6e6f63ce966d2d6ecdd58d70"
ROM_SIZE = 0x800000


def sha1(path: Path) -> str:
    digest = hashlib.sha1()
    with path.open("rb") as source:
        for block in iter(lambda: source.read(1024 * 1024), b""):
            digest.update(block)
    return digest.hexdigest()


def regions(path: Path):
    for raw in path.read_text().splitlines():
        fields = raw.split("#", 1)[0].split()
        if not fields:
            continue
        if len(fields) < 4:
            raise ValueError(f"invalid region line: {raw}")
        mode = fields[4] if len(fields) > 4 else None
        if mode not in {None, "old", "pb", "noint"}:
            raise ValueError(f"invalid compiler mode: {mode}")
        yield fields[0], int(fields[1], 16), int(fields[2], 16), fields[3].split(","), mode


def run(command: list[str], label: str) -> None:
    result = subprocess.run(command, cwd=ROOT, text=True, capture_output=True)
    if result.returncode == 0:
        return
    detail = (result.stdout + result.stderr).strip().splitlines()
    preview = "\n".join(detail[-8:])
    raise RuntimeError(f"{label} failed\n{preview}")


def coverage(selected) -> tuple[int, int]:
    spans = []
    for _, start, end, _, _ in sorted(selected, key=lambda region: region[1]):
        if not 0 <= start < end <= ROM_SIZE:
            raise ValueError("Region bounds are outside the ROM.")
        start += 0x08000000
        end += 0x08000000
        if spans and start <= spans[-1][1]:
            spans[-1] = (spans[-1][0], max(spans[-1][1], end))
        else:
            spans.append((start, end))
    owners = [owner for owner in json.loads((ROOT / "cfg/functions.json").read_text())
              if owner["kind"] != "block"]
    if not owners:
        raise ValueError("The callable inventory is empty.")
    total_bytes = 0
    missing = []
    for owner in owners:
        start, end = int(owner["lo"], 16), int(owner["hi"], 16)
        if end <= start:
            raise ValueError(f"Invalid owner span: {owner['entry']}")
        total_bytes += end - start
        if not any(low <= start and end <= high for low, high in spans):
            missing.append(owner["entry"])
    if missing:
        raise ValueError(f"Regions omit {len(missing)} complete callable spans; first: {missing[0]}")
    return len(owners), total_bytes


def compile_region(region, work: Path, agbcc: Path, old_agbcc: Path) -> bytes:
    name, start, end, sources, mode = region
    compiler = old_agbcc if mode == "old" else agbcc
    if not compiler.is_file():
        raise RuntimeError(f"{name}: compiler is unavailable: {compiler}")
    flags = ["-O2", "-mno-thumb-interwork" if mode == "noint" else "-mthumb-interwork"]
    if mode == "pb":
        flags.append("-fprologue-bugfix")
    objects = []
    for index, source_name in enumerate(sources):
        source = ROOT / "src" / source_name
        if not source.is_file():
            raise RuntimeError(f"{name}: missing source: {source_name}")
        object_file = work / f"{index}.o"
        if source.suffix == ".s":
            run(["arm-none-eabi-as", "-mcpu=arm7tdmi", "-mthumb-interwork", "-o", str(object_file), str(source)], name)
        else:
            preprocessed = work / f"{index}.i"
            assembly = work / f"{index}.s"
            run(["cc", "-E", "-P", "-I", "tools", str(source), "-o", str(preprocessed)], name)
            run([str(compiler), *flags, "-o", str(assembly), str(preprocessed)], name)
            with assembly.open("a") as output:
                output.write("\t.align\t2, 0\n")
            run(["arm-none-eabi-as", "-mcpu=arm7tdmi", "-mthumb-interwork", "-o", str(object_file), str(assembly)], name)
        objects.append(str(object_file))
    output = work / "region.bin"
    data = linklib.link_text(objects, 0x08000000 + start, str(output), work=str(work))
    length = end - start
    if len(data) > length and all(byte == 0 for byte in data[length:]):
        data = data[:length]
    if len(data) != length:
        raise RuntimeError(f"{name}: generated {len(data)} bytes for a {length}-byte region")
    return data


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--rom", type=Path, required=True)
    parser.add_argument("--agbcc", type=Path, default=Path(os.environ.get("AGBCC", ROOT.parent / "agbcc" / "agbcc")))
    parser.add_argument("--old-agbcc", type=Path, default=Path(os.environ.get("OLD_AGBCC", ROOT.parent / "agbcc" / "old_agbcc")))
    parser.add_argument("--region")
    args = parser.parse_args()

    if not args.rom.is_file():
        print(f"ROM is unavailable: {args.rom}", file=sys.stderr)
        return 2
    if args.rom.stat().st_size != ROM_SIZE:
        print("ROM has an unexpected size.", file=sys.stderr)
        return 2
    if sha1(args.rom) != EXPECTED_SHA1:
        print("ROM hash does not match Zoids Legacy (USA).", file=sys.stderr)
        return 2
    for command in ("cc", "arm-none-eabi-as", "arm-none-eabi-ld", "arm-none-eabi-objcopy", "arm-none-eabi-objdump"):
        if shutil.which(command) is None:
            print(f"Required command is unavailable: {command}", file=sys.stderr)
            return 2

    selected = [region for region in regions(ROOT / "regions.txt") if args.region in {None, region[0]}]
    if not selected:
        print("No region matches the selection.", file=sys.stderr)
        return 2
    complete_coverage = None
    if args.region is None:
        try:
            complete_coverage = coverage(selected)
        except ValueError as error:
            print(f"Coverage failed: {error}", file=sys.stderr)
            return 1
    rom = args.rom.read_bytes()
    failures = []
    with tempfile.TemporaryDirectory(prefix="zoidsq-verify-") as temporary:
        root = Path(temporary)
        for index, region in enumerate(selected, 1):
            name, start, end, _, _ = region
            work = root / name
            work.mkdir()
            try:
                data = compile_region(region, work, args.agbcc, args.old_agbcc)
            except (RuntimeError, subprocess.CalledProcessError) as error:
                failures.append(name)
                print(f"FAIL {name}: {error}", file=sys.stderr)
                continue
            if data != rom[start:end]:
                failures.append(name)
                print(f"FAIL {name}: bytes differ", file=sys.stderr)
                continue
            print(f"PASS {index}/{len(selected)} {name}")
    if failures:
        print(f"Verification failed for {len(failures)} of {len(selected)} regions.", file=sys.stderr)
        return 1
    print(f"Verification passed for {len(selected)} regions.")
    if complete_coverage is not None:
        owners, code_bytes = complete_coverage
        print(f"Known callable coverage: {owners}/{owners} owners, {code_bytes}/{code_bytes} bytes (100%).")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
