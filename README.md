# Zoids Legacy (USA) decompilation

This project rebuilds 1,130 code regions from Zoids Legacy to match the original game byte for byte. It also includes tools for English and Spanish translations. See [the source guide](src/README.md) for the code layout.

You need your own clean USA ROM. The repository does not include the ROM or its original game text.

Some functions are still hard to read because they use generated code and macros. Further cleanup is planned.

## Build a translated ROM

Install Python 3, a C compiler (`cc`), and the ARM GNU toolchain (`arm-none-eabi-gcc`, `-as`, `-objcopy`, `-nm`). Put `Zoids Legacy (USA).gba` in the repository root. Run:

    python3 tools/insert_vwf.py --output "Zoids Legacy (USA) - Retranslated.gba"

The English text is in `dialogue-en.json` and `scene-translation.json`. Font spacing is in `kerning-choices.json`. The builder rejects unsupported characters and text that exceeds the limits for names, battle choices, battle quotes, and Deck Commands.

## Edit translations

Run `python3 tools/script_editor.py`. Open http://127.0.0.1:5097/. Select ENG or ESP. Use Translate interface to change the language of the editor controls.

The editor shows each text record, its script context, and a preview drawn with the game's text core. Dialogue previews stop where the game waits for A. The editor checks text before saving it. Build ROM writes `build/zoids-legacy-<code>.gba`.

To check for clipped text, run:

    python3 tools/text_fit_check.py --language esp

Use `eng` for English. The command writes `build/text-fit-<code>.json`, which the editor uses to mark clipped text.

Exact results use resolved draw arguments and window sizes. Other results use estimates. The command fails if an exact result shows clipped text.

## Build release patches

Set the version in `VERSION`. Run `python3 tools/build_site_patch.py`.

This creates `site/patch.bps`, `site/patch-es.bps`, and `site/version.mjs`. All languages share this version on the title screen, in the credits through `{VERSION}`, and on the website.

## Add a language

Use the English JSON files as examples. Create `scene-translation-<code>.json` and `dialogue-<code>.json`, where `<code>` is a short language code.

Translate `english_draft` in scene entries and `build_text` or `text` in dialogue entries. Keep offsets, control codes, placeholders, and build settings unchanged.

You can omit untranslated entries. They use the original USA text, except required message templates and credits, which use English translations.

### Title menu

Use the Spanish file's `title_menu` section as an example. Set `new_game`, `continue`, and `options`. Add `press_start` to translate the startup prompt.

The builder draws uppercase labels and keeps the original layout, both Continue states, and the prompt's gradient and shadow. Labels allow 12 characters each, except Options, which allows 8. Without `title_menu`, the original labels remain.

For unsupported title letters, add glyphs to `tools/title_menu.py`. For other text, add them to `tools/dialogue.py` and `tools/text_core.py`.

### Build and website

Build with your language files:

    python3 tools/insert_vwf.py --rom "Zoids Legacy (USA).gba" \
      --draft scene-translation-xx.json --dialogue dialogue-xx.json \
      --output translated-xx.gba

Replace `xx` with your language code. Every build reads the shared `VERSION` file.

To add the language to the website:

1. Add a file in `site/locales/` with the existing text keys.
2. Import `PATCH_VERSION` from `../version.mjs` in that file.
3. Add the language button and patch mapping in `site/index.html`, `site/i18n.js`, `site/app.js`, and `site/worker.js`.
4. Add the patch build to `tools/build_site_patch.py`.
5. Generate a BPS patch from the clean USA ROM and your translated ROM.
6. Put the patch in `site/`.

## Build and check the decompiled code

Install Python 3, a C preprocessor, ARM binutils, and [agbcc](https://github.com/pret/agbcc). Use agbcc commit `da598c1d918402c42c0c0d7128ba14567f3175e9`.

From the agbcc checkout, run:

    make -C gcc clean
    make -C gcc old
    cp gcc/old_agbcc old_agbcc
    make -C gcc clean
    make -C gcc CC=gcc-14
    cp gcc/agbcc agbcc

Use GCC 14 because the Apple Clang build fails on one source file. Run the builds one at a time because parallel builds fail. If agbcc is outside `../agbcc/`, set `AGBCC` and `OLD_AGBCC` to the compiler paths.

From this repository, run:

    make verify ROM=/path/to/Zoids\ Legacy\ \(USA\).gba

The tool checks the ROM's SHA-1, compiles each region, and compares its bytes with the ROM. It also checks that all callable spans have code. It uses temporary files and does not write a ROM.

To check one region, run `python3 tools/verify.py --rom /path/to/rom --region region0`.

### C code that does not match

Some hand-written sound routines need assembly to match the ROM. Their C versions are in `src/audio/nonmatching/`, with ROM spans listed in `nonmatching.txt`. SoundMain has no C version because its mixer uses a custom stack frame.

To compare these routines with the ROM, run:

    python3 tools/nonmatching.py --rom /path/to/rom [--entry m4a_ply_note] [--diff]

The tool reports how many instructions match. The `--diff` flag shows the differences.
