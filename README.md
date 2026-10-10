# Zoids Legacy (USA) decompilation

This repository contains 1,155 byte-exact code regions from the game.
They cover all 1,238 inventoried callable owners and their 373,728 code bytes.
The source includes C, inline assembly, assembler macros, and assembly files.
It does not contain a ROM, game data, generated ROMs, saves, or binary probes.

> HEAD'S UP: The decomped functions looks jank right now due to the use of both permutators, function/argument/register macros, and typical AI slop. I'll try to clean it up when i get more free time :P 

## Requirements

Install Python 3, a C preprocessor, ARM binutils, and agbcc.
Build agbcc from commit `da598c1d918402c42c0c0d7128ba14567f3175e9` of [pret/agbcc](https://github.com/pret/agbcc).
Build its normal compiler with GCC 14. Apple's Clang build fails on one source file.
From the agbcc checkout, run these commands:

    make -C gcc clean
    make -C gcc old
    cp gcc/old_agbcc old_agbcc
    make -C gcc clean
    make -C gcc CC=gcc-14
    cp gcc/agbcc agbcc

Run these builds serially; the makefile has dependencies that fail with parallel builds.

Set `AGBCC` and `OLD_AGBCC` when the compiler executables are outside `../agbcc/`.

## Verify

Provide your own clean Zoids Legacy (USA) ROM.
The verifier checks its SHA-1 before it compiles any code.

    make verify ROM=/path/to/Zoids\ Legacy\ \(USA\).gba

The verifier compiles each listed region at its original address.
It compares each generated region with the local ROM.
Full verification also requires complete coverage of every inventoried callable span.
It creates temporary files only and never writes a ROM.

Use `python3 tools/verify.py --rom /path/to/rom --region region0` to verify one region.

## Non-matching C

Eleven routines from the hand-written half of the MP2K sound driver use instructions and register conventions that agbcc cannot produce, so the verified build keeps them as assembly. `src/audio/nonmatching/` has equivalent C for 10 of them. SoundMain has no C form because it hands a custom stack frame to the mixer code in IWRAM. `nonmatching.txt` lists each C file with its ROM span.

    python3 tools/nonmatching.py --rom /path/to/rom [--entry m4a_ply_note] [--diff]

The tool compiles each entry at its original address and reports how many instructions match the ROM. `--diff` prints the instruction diff.

## Copied native code and sound mixer

The remaining-code audit added eight matching Thumb C routines, fourteen ARM assembly routines, eleven register branch stubs, and the startup restart branch.
The ARM sources keep the original CPU mode and register conventions; agbcc remains unchanged.

[`src/audio/m4a_sound_mixer.s`](src/audio/m4a_sound_mixer.s) contains the mixer continuation at `080EAB28`–`080EAE52` and its shared `bx r3` return at `080EAE52`.
`InitializeSoundEngine` copies 896 bytes from `080EAB28` to `03007758`; this includes the mixer and following routines.
`SoundMain` enters at `03007759`, with the Thumb bit set.
The mixer switches to ARM for reverb and PCM mixing, then returns to Thumb for channel control and register restoration.
It clears or applies reverb to the output buffer, updates channel envelopes, and mixes direct or interpolated PCM samples.
Looping channels restart at their sample loop point; finished channels stop.

This entry uses SoundMain's stack frame rather than an ordinary C call.
On entry, `r5` holds the output buffer, `r8` holds the sample count, and `r6` holds `0x630`.
Stack offsets `0` and `4` hold sample and channel counts; `8` holds the output buffer.
Offsets `12` and `16` hold the loop pointer and remaining loop samples; `20` holds the scanline deadline.
Offset `24` holds the engine pointer, followed by saved `r8`–`r11`, `r4`–`r7`, and the return address.
The signature load uses the existing literal at `080EAE54`, beyond the shared return instruction.
The extracted assembly preserves these offsets and mode switches; the mixer has no C replacement.

## Build the translated ROM

Put a clean `Zoids Legacy (USA).gba` in the repository root. Install Python 3, a host C compiler (`cc`), and the ARM GNU toolchain (`arm-none-eabi-gcc`, `-as`, `-objcopy`, `-nm`).

    python3 tools/insert_vwf.py --output "Zoids Legacy (USA) - Retranslated.gba"

The translation lives in `dialogue-en.json` and `scene-translation.json`, and `kerning-choices.json` holds the font spacing. The two text files hold only the translated English and build metadata. The tools read the original game text and bytes from your ROM when they load these files, so the repository ships no game text. The build rejects edits that use glyphs the font lacks, speaker names, battle menu choices, and battle quotes that overflow their windows, and Deck Command names wider than their menu line.

To release a patch, set the version in `VERSION` and run `python3 tools/build_site_patch.py`. It writes `site/patch.bps` and `site/version.mjs`, and the credits read the same `VERSION` through their `{VERSION}` placeholder.
