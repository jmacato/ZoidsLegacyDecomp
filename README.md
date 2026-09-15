# Zoids Legacy (USA) decompilation

This repository contains 1,130 byte-exact code regions from the game.
They cover all 1,205 inventoried callable owners and their 371,784 code bytes.
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
