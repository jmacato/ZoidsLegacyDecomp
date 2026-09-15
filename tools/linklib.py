#!/usr/bin/env python3
"""Link compiled code at its original ROM address.

Thumb call stubs prevent the linker from adding interworking veneers.
The output contains only the compiled region; it excludes the stubs.
"""
import json, os, re, subprocess

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
BASE = 0x08000000
AS = ["arm-none-eabi-as", "-mcpu=arm7tdmi", "-mthumb-interwork"]
LD = "arm-none-eabi-ld"
OBJCOPY = "arm-none-eabi-objcopy"
OBJDUMP = "arm-none-eabi-objdump"
RE_FUNC = re.compile(r"^func_([0-9A-Fa-f]+)$")

def _all_func_addrs():
    with open(os.path.join(ROOT, "cfg", "functions.json")) as source:
        fs = json.load(source)
    key = "entry" if "entry" in fs[0] else "addr"
    return {int(f[key], 16) for f in fs}

def _relocs(obj):
    """Return the symbol and type for each relocation."""
    out = subprocess.run([OBJDUMP, "-r", obj], capture_output=True, text=True, check=True).stdout
    rels = []
    for ln in out.splitlines():
        p = ln.split()
        if len(p) >= 3 and p[1].startswith("R_ARM_"):
            rels.append((p[2], p[1]))
    return rels

def _defined(obj):
    """Return symbols defined in an object section."""
    out = subprocess.run([OBJDUMP, "-t", obj], capture_output=True, text=True, check=True).stdout
    d = set()
    for ln in out.splitlines():
        if " *UND*" in ln or "*ABS*" in ln:
            continue
        m = re.search(r"\s(\S+)$", ln)
        if m and ("g " in ln or "l " in ln):
            d.add(m.group(1))
    return d

def link_text(objs, vma, out_bin, work="grind", extra_includes=()):
    """Link objects at `vma` and write their `.text` bytes."""
    funcs = _all_func_addrs()
    defined = set()
    for o in objs:
        defined |= _defined(o)
    call_syms, abs_syms = set(), set()
    for o in objs:
        for sym, typ in _relocs(o):
            if sym in defined:
                continue
            m = RE_FUNC.match(sym)
            if not m:
                continue
            addr = int(m.group(1), 16)
            if "CALL" in typ or "JUMP" in typ:
                # Symbol names can identify internal branch targets outside the inventory.
                call_syms.add((sym, addr))
            elif addr in funcs:
                abs_syms.add((sym, addr))

    stub_s = os.path.join(work, "_stubs.s")
    with open(stub_s, "w") as f:
        f.write(".syntax unified\n.thumb\n")
        for sym, addr in sorted(call_syms):
            f.write('.section .stub_%X,"ax",%%progbits\n.global %s\n.thumb_func\n%s:\n.byte 0,0\n'
                    % (addr, sym, sym))
    stub_o = os.path.join(work, "_stubs.o")
    subprocess.run(AS + ["-o", stub_o, stub_s], check=True, cwd=ROOT)

    ld = os.path.join(work, "_link.ld")
    with open(ld, "w") as f:
        f.write('INCLUDE "%s"\n' % os.path.join(ROOT, "symbols.ld"))
        for inc in extra_includes:
            f.write('INCLUDE "%s"\n' % inc)
        stubbed = {a for _, a in call_syms}
        for sym, addr in sorted(abs_syms):
            if addr not in stubbed:
                f.write("%s = 0x%08X;\n" % (sym, addr + 1))   # Thumb state bit.
        f.write("SECTIONS {\n")
        # SUBALIGN(2) prevents a leading pad at two-byte aligned addresses.
        f.write("  .text 0x%08X : SUBALIGN(2) { %s }\n" % (vma, " ".join("%s(.text .text.* .rodata .rodata.*)" % o for o in objs)))
        for sym, addr in sorted(call_syms):
            f.write("  .stub_%X 0x%08X : { %s(.stub_%X) }\n" % (addr, addr, stub_o, addr))
        f.write("  /DISCARD/ : { *(*) }\n}\n")

    elf = os.path.join(work, "_link.elf")
    subprocess.run([LD, "--entry=0", "-T", ld] + objs + [stub_o, "-o", elf], check=True, cwd=ROOT)
    subprocess.run([OBJCOPY, "-O", "binary", "-j", ".text", elf, out_bin], check=True, cwd=ROOT)
    return open(out_bin, "rb").read()
