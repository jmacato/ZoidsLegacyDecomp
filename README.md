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

## Non-matching C

Eleven routines from the hand-written half of the MP2K sound driver use instructions and register conventions that agbcc cannot produce, so the verified build keeps them as assembly. `src/audio/nonmatching/` has equivalent C for 10 of them. SoundMain has no C form because it hands a custom stack frame to the mixer code in IWRAM. `nonmatching.txt` lists each C file with its ROM span.

    python3 tools/nonmatching.py --rom /path/to/rom [--entry m4a_ply_note] [--diff]

The tool compiles each entry at its original address and reports how many instructions match the ROM. `--diff` prints the instruction diff.

## Build the translated ROM

Put a clean `Zoids Legacy (USA).gba` in the repository root. Install Python 3, a host C compiler (`cc`), and the ARM GNU toolchain (`arm-none-eabi-gcc`, `-as`, `-objcopy`, `-nm`).

    python3 tools/insert_vwf.py --output "Zoids Legacy (USA) - Retranslated.gba"

The translation lives in `dialogue-en.json` and `scene-translation.json`, and `kerning-choices.json` holds the font spacing. The two text files hold only the translated English and build metadata. The tools read the original game text and bytes from your ROM when they load these files, so the repository ships no game text. The build rejects edits that use glyphs the font lacks, speaker names, battle menu choices, and battle quotes that overflow their windows, and Deck Command names wider than their menu line.

To release the patches, set the English version in `VERSION` and the Spanish version in `VERSION_ES`. Run `python3 tools/build_site_patch.py`. It writes `site/patch.bps`, `site/patch-es.bps`, and `site/version.mjs`. Each ROM uses its own version for the `{VERSION}` placeholder in the credits.

## Edit and check the text

Run `python3 tools/script_editor.py` and open http://127.0.0.1:5097/. Use ENG or ESP to pick the language. Turn on Translate interface to show the editor itself in that language. The editor lists every text record from the ROM, shows the event or menu script that uses it, and renders the text with the game's own text core. Dialogue previews stop wherever the game waits for A, so long lines show each box in order. Saves go to the language's JSON files after the same checks the builder runs. Build ROM writes `build/zoids-legacy-<code>.gba`.

Run `python3 tools/text_fit_check.py --language esp` (or `eng`) to find text that does not fit its window. The check reads the draw calls in `src/`, takes each window's size from the menu script or `OpenWindow` call that opens it, and lays out every string with the text core at that width. It writes `build/text-fit-<code>.json`, which the editor uses to mark and preview clipped text. Results where every draw argument resolved are listed as exact; the rest depend on an inferred window or position. The command exits with an error when an exact result clips.

## Localize another language

Create `scene-translation-<code>.json` and `dialogue-<code>.json` using the English files as format examples. Replace `<code>` with a short language code. Translate `english_draft` in scene entries and `build_text` or `text` in dialogue entries. Keep each offset, control code, placeholder, and build setting. You can include only the entries you translate. Missing entries keep the text from the original USA ROM, except required message templates and credits, which use the English translation.

The Spanish dialogue file also sets `title_menu` labels for `new_game`, `continue`, and `options`. The builder draws these labels in uppercase with a small sprite font. It keeps both Continue states and the original menu layout. The optional `press_start` label replaces the startup prompt and keeps its gradient and shadow. Files without `title_menu` keep the original menu graphics, including the English build. Add unsupported title letters to `tools/title_menu.py` before using them. The title labels allow 12 characters for New Game, Continue, and Press Start, and 8 for Options.

Add any missing glyphs to `tools/dialogue.py` and `tools/text_core.py`. Then build the ROM with your files:

    python3 tools/insert_vwf.py --rom "Zoids Legacy (USA).gba" \
      --draft scene-translation-xx.json --dialogue dialogue-xx.json \
      --version-file VERSION_XX --output translated-xx.gba

Replace `xx` with the same language code in each file name. The Spanish build selects `VERSION_ES` automatically when you use `dialogue-es.json`; the English build uses `VERSION` by default. Use `--version-file` for other languages or to override either default.

The website text uses stable keys in `site/index.html`. Each language has its own file in `site/locales/`. To add a website language, add its locale file, language button, and patch mapping in `site/i18n.js`, `site/app.js`, `site/index.html`, and `site/worker.js`. Add its version to `tools/build_site_patch.py` and import that version in its locale file. Generate the BPS patch locally from the clean USA ROM and the translated ROM. Put the patch in `site/`.
