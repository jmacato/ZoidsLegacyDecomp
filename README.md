# Zoids Legacy (USA) decompilation

This repository contains 1,130 code regions that match the original game byte for byte. These regions cover all 1,205 callable owners in the inventory, with 371,784 bytes of code.

The source includes C, inline assembly, assembler macros, and assembly files. The repository does not include a ROM, game data, generated ROMs, saves, or binary probes.

> Some functions are hard to read. They use code from permutators, macros for functions, arguments, and registers, and rough AI-generated code. I plan to clean them up when I have more free time.

## Requirements

Install Python 3, a C preprocessor, ARM binutils, and agbcc. Use commit `da598c1d918402c42c0c0d7128ba14567f3175e9` from [pret/agbcc](https://github.com/pret/agbcc). Build the normal agbcc compiler with GCC 14.

The Apple Clang build fails on one source file.

From the agbcc checkout, run these commands in order:

    make -C gcc clean
    make -C gcc old
    cp gcc/old_agbcc old_agbcc
    make -C gcc clean
    make -C gcc CC=gcc-14
    cp gcc/agbcc agbcc

Run one build at a time. The makefile has dependencies that fail with parallel builds.

If the compiler executables are outside `../agbcc/`, set `AGBCC` and `OLD_AGBCC` to their paths.

## Check the source against the ROM

Provide your own clean Zoids Legacy (USA) ROM. Run:

    make verify ROM=/path/to/Zoids\ Legacy\ \(USA\).gba

The tool checks the ROM's SHA-1 before it compiles any code. It compiles each listed region at its original address, then compares the result with the ROM. A full check also requires code for every callable span in the inventory. The tool creates temporary files and never writes a ROM.

To check one region, run `python3 tools/verify.py --rom /path/to/rom --region region0`.

## C code that does not match

Eleven hand-written routines in the MP2K sound driver use instructions and register conventions that agbcc cannot produce. The build keeps these routines as assembly to preserve the original bytes. The `src/audio/nonmatching/` directory contains equivalent C code for 10 routines. SoundMain has no C version because it passes a custom stack frame to the mixer code in IWRAM. The `nonmatching.txt` file lists each C file and its ROM span.

To compare the C code with the ROM, run:

    python3 tools/nonmatching.py --rom /path/to/rom [--entry m4a_ply_note] [--diff]

The tool compiles each entry at its original address and reports how many instructions match the ROM. The `--diff` flag shows the differences between instructions.

## Build the translated ROM

Put a clean `Zoids Legacy (USA).gba` in the repository root. Install Python 3, a host C compiler (`cc`), and the ARM GNU toolchain (`arm-none-eabi-gcc`, `-as`, `-objcopy`, `-nm`). Run:

    python3 tools/insert_vwf.py --output "Zoids Legacy (USA) - Retranslated.gba"

The English translation uses `dialogue-en.json` and `scene-translation.json`. These files contain translated text and build metadata. The `kerning-choices.json` file sets the font spacing. The tools read the original text and bytes from your ROM, so the repository does not include the original game text.

The builder rejects characters that the font does not support. It also rejects speaker names, battle menu choices, and battle quotes that exceed their window size. Deck Command names must fit their menu line.

### Build the release patches

Set the patch version in `VERSION`. Run `python3 tools/build_site_patch.py`.

The command writes `site/patch.bps`, `site/patch-es.bps`, and `site/version.mjs`. All languages use the same version from `VERSION`, including future languages. Each ROM shows this version on the title screen and uses it for the `{VERSION}` placeholder in the credits. The website uses the same version through `PATCH_VERSION` in `site/version.mjs`.

## Edit and check the text

Run `python3 tools/script_editor.py`. Open http://127.0.0.1:5097/. Select ENG or ESP to choose the language. Turn on Translate interface to use that language for the editor controls.

The editor lists every text record from the ROM and shows the event or menu script that uses it. It draws previews with the game's text core. Dialogue previews stop at each point where the game waits for A. Long passages show one dialogue box at a time.

The editor checks edits with the same rules as the builder before it saves them to the language's JSON files. Build ROM writes `build/zoids-legacy-<code>.gba`.

To find text that exceeds its window size, run `python3 tools/text_fit_check.py --language esp`. Use `eng` for English.

The check reads draw calls in `src/`. It gets each window size from the menu script or the `OpenWindow` call that opens it. The text core then lays out each string at that width. The check writes `build/text-fit-<code>.json`. The editor uses this file to mark clipped text and show previews.

An exact result means that the check resolved every draw argument. Other results depend on an inferred window or position. The command exits with an error if an exact result shows clipped text.

## Add another language

### Translate the game text

Create `scene-translation-<code>.json` and `dialogue-<code>.json`, with the English files as format examples. Replace `<code>` with a short language code. Translate `english_draft` in scene entries. Translate `build_text` or `text` in dialogue entries. Keep each offset, control code, placeholder, and build setting.

You can include only the entries that you translate. Missing entries keep the text from the original USA ROM. Required message templates and credits use the English translation if your files omit them.

### Translate the title menu

The Spanish dialogue file uses `title_menu` to set labels for `new_game`, `continue`, and `options`. The builder draws these labels in uppercase with a small sprite font. It keeps both Continue states and the original menu layout. The optional `press_start` label replaces the startup prompt and keeps its gradient and shadow.

Files without `title_menu`, including the English file, keep the original menu graphics. The shared version indicator still appears on the title screen. New Game, Continue, and Press Start labels allow 12 characters each. Options allows 8 characters.

Before you use unsupported title letters, add them to `tools/title_menu.py`. For other text, add missing characters to `tools/dialogue.py` and `tools/text_core.py`.

### Build the language ROM

Build the ROM with your translation files:

    python3 tools/insert_vwf.py --rom "Zoids Legacy (USA).gba" \
      --draft scene-translation-xx.json --dialogue dialogue-xx.json \
      --output translated-xx.gba

Replace `xx` with the same language code in each file name.

The builder reads the shared patch version from `VERSION`. No separate version file or command option is needed for another language.

### Add the language to the website

The website text uses stable keys in `site/index.html`. Each language has a file in `site/locales/`.

Add a locale file for the language. Add its language button and patch mapping in `site/i18n.js`, `site/app.js`, `site/index.html`, and `site/worker.js`. Add its patch build to `tools/build_site_patch.py`. In the locale file, import `PATCH_VERSION` from `../version.mjs`.

Generate the BPS patch locally from the clean USA ROM and the translated ROM. Put the patch in `site/`.
