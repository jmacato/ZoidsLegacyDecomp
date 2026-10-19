//! Battle unit popups: StartBattleUnitPopup's callback table, the text CreateBattlePopupTextSprites turns into glyph sprites,
//! the glyph and effect sprite resources, and LoadBattlePopupGraphics' compressed graphics tables.

use std::collections::{BTreeMap, BTreeSet};

use serde_json::json;

use super::battle_animation::code_source;
use super::{graphics, sprites, Port};
use crate::basis::Basis;
use crate::rom::{le32, R};
use crate::run::Ctx;
use crate::{repo_root, verify_c};

const POPUP_TABLE: Basis = Basis::C(&[
    ("src/battle/popups/battle_popup.h", "6ddd8260acaacbfa730b427d68eaf8cb18517167"),
    ("src/battle/popups/start_battle_unit_popup.c", "9570930c768ea4318afb72aa00081d387fad927d"),
    ("src/graphics/create_sprite_group.c", "52a5f063631c9d8645a184d52278b9b716fb8c0b"),
    ("src/graphics/update_sprite_groups.c", "511c254adfd8cb331d214b6fb2883a7453cfefb8"),
]);
const POPUP_TEXT: Basis = Basis::C(&[
    ("src/battle/popups/battle_popup.h", "6ddd8260acaacbfa730b427d68eaf8cb18517167"),
    ("src/battle/popups/create_battle_popup_text_sprites.c", "48ac3be56319e34fca781fa616c2f5c98e833ac0"),
    ("src/battle/popups/initialize_battle_damage_popup.c", "db020df32c912e97df359013b58428b5b9bb6558"),
    ("src/battle/popups/initialize_battle_ep_modifier_popup.c", "b72c5e858b8f43994f00deeaca53e7c5072867a0"),
    ("src/battle/popups/initialize_battle_freeze_popup.c", "1d3a50e33cc4b502c091c984475b8673f5e6820a"),
    ("src/battle/popups/initialize_battle_hit_rate_modifier_popup.c", "0e457ba73fb7aad8fd5e004bfc47182c9a7d43f4"),
    ("src/battle/popups/initialize_battle_hp_modifier_popup.c", "abd660713cf1018aa01513b012e3a67be2332b62"),
    ("src/battle/popups/initialize_battle_max_ep_modifier_popup.c", "f22542fbd7c7829ab238fcf9a49aad02b1fd2391"),
    ("src/battle/popups/initialize_battle_max_hp_modifier_popup.c", "baea9df140a7d77241fe1bbd3dd992580488867b"),
    ("src/battle/popups/initialize_battle_miss_popup.c", "29d2a8515eb4208d00e870dab7576cee7ed637a8"),
    ("src/battle/popups/initialize_battle_organoid_popup.c", "625139d8a6c217307be394d159b5b1de2ee7839a"),
    ("src/battle/popups/initialize_battle_pilot_down_arrow_popup.c", "e8835c3b650e5c6185058145ef8c6f730725041f"),
    ("src/battle/popups/initialize_battle_pilot_up_arrow_popup.c", "fef84e928f4500f86bd7b6ba6c15eff181cd18d2"),
    ("src/battle/popups/initialize_battle_sensor_accuracy_modifier_popup.c", "c65a7c7ffb262baae76e9081b754d040c943e71b"),
    ("src/battle/popups/initialize_battle_speed_modifier_popup.c", "38039ddcc5a2f202e57ec7629c80a7daa6f5456d"),
    ("src/battle/popups/initialize_battle_waiting_popup.c", "2a8dd37c056d83ac36fc004adb690811a3558a01"),
    ("src/battle/popups/initialize_battle_wakeup_popup.c", "b34e6c2bf84bac4a330182b9e418a94c694498f1"),
    ("src/battle/popups/initialize_battle_zos_level_popup.c", "960d4dbd1f9eede3da1a5b7d3de4166309a55825"),
    ("src/battle/popups/show_battle_anti_air.c", "482455e562a5bfaf8a76133d0eb82d516ba32771"),
    ("src/battle/popups/show_battle_modifier_labels.c", "a1d6092d1d4ac547c5976ce7b1e4126e0548dc9f"),
    ("src/runtime/copy_bytes.c", "e10e7e371495f3cc4a7382fdf8a91ee500a88795"),
    ("src/engine/append_string.c", "6e8c5d1156f6a69c8c74b04a81c02e85b7fa82e9"),
    ("src/runtime/copy_string.c", "c4d0513f9c0b8bb1147f511ecf77c72f84936c40"),
    ("src/ui/format_number_text.c", "740213c7a26914f219f5fc39f9e84abdfb57ea53"),
    ("src/ui/window.h", "c299d1e84300353c8f991978a0c2761133a5e42c"),
    ("src/graphics/create_sprite_from_table.c", "10890981a20d144607c171ecaf63ea3a74f3e369"),
]);
const POPUP_EFFECTS: Basis = Basis::C(&[
    ("src/battle/popups/battle_popup.h", "6ddd8260acaacbfa730b427d68eaf8cb18517167"),
    ("src/battle/battle_display.h", "ed9ae1d1b7b71e189ca7f207078675f82ea365b5"),
    ("src/battle/popups/create_battle_unit_popup_effect_sprite.c", "2daba79e50d98c8b1ca5cfa33b63e7fb1dd224e1"),
    ("src/battle/popups/initialize_battle_damage_popup.c", "db020df32c912e97df359013b58428b5b9bb6558"),
    ("src/battle/popups/initialize_battle_destroyed_unit_popup.c", "b68f9ece8d8fc7e9bb748ae23fd36383c65a3962"),
    ("src/battle/popups/update_battle_destroyed_unit_popup.c", "e7f04d3a153d8d358b48d1e69d70be3b06ec7bcb"),
    ("src/battle/popups/update_battle_gold_spark_modifier_popup.c", "1b7936fd3fa12bbb296196c7dd5b96037e9c8152"),
    ("src/battle/popups/update_battle_green_streak_modifier_popup.c", "77215e4fef25605df83dea04dee420806779ed25"),
    ("src/battle/popups/update_battle_orange_streak_modifier_popup.c", "99f21c22d5d84c59f512df557ef6526a7e628ea2"),
    ("src/battle/popups/update_battle_purple_ring_popup.c", "b0a2301aeff89e73804332f3c638223fc813069f"),
    ("src/battle/popups/update_battle_purple_spark_modifier_popup.c", "c195582666ed396f773c34fa75f2f2e226dd2706"),
    ("src/battle/popups/update_battle_purple_streak_modifier_popup.c", "61ff92b393a932adf028030faac0b6b6f60b1263"),
    ("src/battle/popups/update_battle_turquoise_spark_modifier_popup.c", "134da470edbd09698ddb486e3fc0d82f3efde2cf"),
    ("src/battle/combinations/animate_battle_combination_arrival.c", "6f67afe4abf012a3897c6e226697015c265e53c4"),
    ("src/graphics/create_sprite_from_table.c", "10890981a20d144607c171ecaf63ea3a74f3e369"),
]);
const POPUP_GRAPHICS_LOADER: Basis = Basis::C(&[("src/battle/popups/load_battle_popup_graphics.c", "c616ec384a33616617754cafa52fee08de30b3a4")]);
const DAMAGE_SHAKE_READER: Basis = Basis::C(&[
    ("src/battle/popups/battle_popup.h", "6ddd8260acaacbfa730b427d68eaf8cb18517167"),
    ("src/battle/popups/update_battle_damage_popup.c", "57ee7dd5e24b76ad56a1d61fdfd19b8a7da132ea"),
]);

pub const PORT: Port = Port { name: "battle_popups", bases: &[POPUP_TABLE, POPUP_TEXT, POPUP_EFFECTS, POPUP_GRAPHICS_LOADER, DAMAGE_SHAKE_READER], run };

const CALLBACKS: u32 = 0x087A_28B0;
/// BATTLE_POPUP_KIND_COUNT
const POPUP_KINDS: u32 = 44;
/// BATTLE_POPUP_GLYPH_RESOURCE_TABLE_ROM; CreateBattlePopupTextSprites always uses resource 0 with flags 0x20048.
const GLYPH_RESOURCES: u32 = 0x087A_C9F0;
/// BATTLE_POPUP_SPRITE_RESOURCE_TABLE_ROM
const EFFECT_RESOURCES: u32 = 0x087A_D1D0;
/// LoadBattlePopupGraphics: LoadSpriteGraphicsFromTable(table, 0, ...) through a local variable for these three banks.
const POPUP_GRAPHICS: [u32; 3] = [0x087A_D1B8, 0x087A_D1C0, 0x087A_D1C8];
const TEXT_FORMAT: &str = "battle_popup_text";
/// gBattleDamageShakeOffsets, read by UpdateBattleDamagePopup for elapsed_updates 0..=BATTLE_POPUP_DAMAGE_SHAKE_LAST_UPDATE.
const DAMAGE_SHAKE: u32 = 0x087A_288C;
const UPDATE_DAMAGE_POPUP: u32 = 0x080C_9204;

/// The characters FormatNumberText(value, 4, flags, ...) can write for a 4-digit value: digits, and with
/// NUMBER_TEXT_SIGN_PREFIX a '+', '-' or ' ' first. Spaces make no glyph.
#[derive(Clone, Copy)]
enum Number {
    None,
    Digits,
    SignedDigits,
}

#[derive(Clone, Copy)]
enum Text {
    /// CreateBattlePopupTextSprites(rom_text, ...)
    Rom(u32),
    /// CopyBytes(BATTLE_POPUP_TEXT_BUFFER_RAM, rom_text, length), then AppendString of the FormatNumberText output.
    Copied(u32, u32, Number),
    /// FormatNumberText straight into the text buffer.
    Formatted(Number),
}

/// Every CreateBattlePopupTextSprites call in battle/popups, by the function that makes it and the text it passes.
const TEXT_CALLS: [(u32, &str, Text); 39] = [
    (0x080C_91A0, "initialize_battle_damage_popup.c", Text::Formatted(Number::Digits)),
    (0x080C_9254, "initialize_battle_miss_popup.c", Text::Rom(0x0810_811C)),
    (0x080C_9274, "initialize_battle_waiting_popup.c", Text::Rom(0x0810_8124)),
    (0x080C_9394, "initialize_battle_freeze_popup.c", Text::Rom(0x0810_812C)),
    (0x080C_93B4, "initialize_battle_hp_modifier_popup.c", Text::Copied(0x0810_8134, 3, Number::SignedDigits)),
    (0x080C_9400, "initialize_battle_max_hp_modifier_popup.c", Text::Copied(0x0810_8138, 6, Number::SignedDigits)),
    (0x080C_944C, "initialize_battle_max_hp_modifier_popup.c", Text::Copied(0x0810_8140, 4, Number::SignedDigits)),
    (0x080C_9498, "initialize_battle_ep_modifier_popup.c", Text::Copied(0x0810_8144, 3, Number::SignedDigits)),
    (0x080C_94E4, "initialize_battle_max_ep_modifier_popup.c", Text::Copied(0x0810_8148, 6, Number::SignedDigits)),
    (0x080C_9530, "initialize_battle_max_ep_modifier_popup.c", Text::Copied(0x0810_8150, 4, Number::SignedDigits)),
    (0x080C_957C, "initialize_battle_speed_modifier_popup.c", Text::Copied(0x0810_8154, 3, Number::SignedDigits)),
    (0x080C_95C8, "initialize_battle_speed_modifier_popup.c", Text::Copied(0x0810_8158, 3, Number::SignedDigits)),
    (0x080C_9614, "initialize_battle_speed_modifier_popup.c", Text::Copied(0x0810_815C, 3, Number::SignedDigits)),
    (0x080C_9660, "initialize_battle_speed_modifier_popup.c", Text::Copied(0x0810_8160, 3, Number::SignedDigits)),
    (0x080C_96AC, "initialize_battle_sensor_accuracy_modifier_popup.c", Text::Copied(0x0810_8164, 3, Number::SignedDigits)),
    (0x080C_96F8, "initialize_battle_sensor_accuracy_modifier_popup.c", Text::Copied(0x0810_8168, 3, Number::SignedDigits)),
    (0x080C_9744, "initialize_battle_sensor_accuracy_modifier_popup.c", Text::Copied(0x0810_816C, 3, Number::SignedDigits)),
    (0x080C_9790, "initialize_battle_sensor_accuracy_modifier_popup.c", Text::Copied(0x0810_8170, 3, Number::SignedDigits)),
    (0x080C_97DC, "initialize_battle_sensor_accuracy_modifier_popup.c", Text::Copied(0x0810_8174, 3, Number::SignedDigits)),
    (0x080C_9828, "initialize_battle_hit_rate_modifier_popup.c", Text::Copied(0x0810_8178, 3, Number::SignedDigits)),
    (0x080C_9874, "show_battle_modifier_labels.c", Text::Copied(0x0810_817C, 8, Number::SignedDigits)),
    (0x080C_98C0, "show_battle_modifier_labels.c", Text::Rom(0x0810_8184)),
    (0x080C_98E0, "show_battle_modifier_labels.c", Text::Rom(0x0810_818C)),
    (0x080C_9900, "show_battle_modifier_labels.c", Text::Rom(0x0810_8198)),
    (0x080C_9920, "show_battle_modifier_labels.c", Text::Rom(0x0810_81A0)),
    (0x080C_9940, "show_battle_modifier_labels.c", Text::Copied(0x0810_81AC, 4, Number::Digits)),
    (0x080C_998C, "show_battle_modifier_labels.c", Text::Rom(0x0810_81B0)),
    (0x080C_99AC, "show_battle_modifier_labels.c", Text::Rom(0x0810_81BC)),
    (0x080C_99CC, "show_battle_anti_air.c", Text::Rom(0x0810_81C8)),
    (0x080C_99EC, "initialize_battle_organoid_popup.c", Text::Rom(0x0810_81D4)),
    (0x080C_9A0C, "initialize_battle_pilot_down_arrow_popup.c", Text::Rom(0x0810_81E0)),
    (0x080C_9A2C, "initialize_battle_pilot_up_arrow_popup.c", Text::Rom(0x0810_81E8)),
    (0x080C_9A4C, "initialize_battle_pilot_up_arrow_popup.c", Text::Rom(0x0810_81F0)),
    (0x080C_9A6C, "initialize_battle_pilot_up_arrow_popup.c", Text::Rom(0x0810_81F8)),
    (0x080C_9A8C, "initialize_battle_zos_level_popup.c", Text::Copied(0x0810_8204, 4, Number::SignedDigits)),
    (0x080C_9AD8, "initialize_battle_zos_level_popup.c", Text::Rom(0x0810_8208)),
    (0x080C_9B00, "initialize_battle_zos_level_popup.c", Text::Rom(0x0810_8210)),
    (0x080C_9B20, "initialize_battle_zos_level_popup.c", Text::Rom(0x0810_8218)),
    (0x080C_9B40, "initialize_battle_wakeup_popup.c", Text::Rom(0x0810_8220)),
];

/// CreateSpriteFromTable(BATTLE_POPUP_SPRITE_RESOURCE_TABLE_ROM, resource, animation 0, ...): the resources passed by
/// CreateBattleUnitPopupEffectSprite's callers in battle/popups, and BLUE_PARTICLES by AnimateBattleCombinationArrival.
const COMBINATION_ARRIVAL_RESOURCE: &str = "BATTLE_POPUP_RESOURCE_BLUE_PARTICLES";

/// CreateBattlePopupTextSprites' glyph animation for one text byte; `None` makes no sprite.
fn glyph(byte: u8) -> Option<u32> {
    if byte.wrapping_sub(b'0') <= 9 {
        return Some(u32::from(byte.wrapping_add(0xF0)));
    }
    let letter = byte.wrapping_sub(b'A');
    if letter <= 0x19 {
        return Some(u32::from(letter));
    }
    match byte {
        b'+' => Some(26),
        b'-' => Some(27),
        b'/' => Some(28),
        b'<' => Some(29),
        b'>' => Some(30),
        0xA0 => Some(31),
        b'%' => Some(42),
        b'?' => Some(43),
        _ => None,
    }
}

fn number_glyphs(number: Number) -> Vec<u32> {
    let mut out: Vec<u32> = match number {
        Number::None => Vec::new(),
        _ => (b'0'..=b'9').filter_map(glyph).collect(),
    };
    if let Number::SignedDigits = number {
        out.extend([b'+', b'-'].into_iter().filter_map(glyph));
    }
    out
}

fn strip_comments(text: &str) -> String {
    let mut out = String::with_capacity(text.len());
    let mut rest = text;
    while !rest.is_empty() {
        if let Some(after) = rest.strip_prefix("/*") {
            rest = after.find("*/").map_or("", |end| &after[end + 2..]);
        } else if let Some(after) = rest.strip_prefix("//") {
            rest = after.find('\n').map_or("", |end| &after[end..]);
        } else {
            let next = rest.chars().next().unwrap();
            out.push(next);
            rest = &rest[next.len_utf8()..];
        }
    }
    out
}

/// Top-level argument texts of each call to `name` in a C file. Declarations (`type name(...)`) are skipped.
pub fn calls(path: &str, name: &str) -> R<Vec<Vec<String>>> {
    let text = std::fs::read_to_string(repo_root().join(path)).map_err(|error| format!("{path}: {error}"))?;
    let text = strip_comments(&text);
    let bytes = text.as_bytes();
    let mut out = Vec::new();
    let mut search = 0;
    while let Some(found) = text[search..].find(name) {
        let at = search + found;
        search = at + name.len();
        let ident = |byte: u8| byte.is_ascii_alphanumeric() || byte == b'_';
        if at > 0 && ident(bytes[at - 1]) || bytes.get(at + name.len()).map_or(false, |&byte| ident(byte)) {
            continue;
        }
        let mut open = at + name.len();
        while bytes.get(open).map_or(false, |byte| byte.is_ascii_whitespace()) {
            open += 1;
        }
        if bytes.get(open) != Some(&b'(') {
            continue;
        }
        let before = text[..at].trim_end();
        let declaration = before.ends_with('*') || before.ends_with(|c: char| c.is_ascii_alphanumeric() || c == '_') && !before.ends_with("return");
        if declaration {
            continue;
        }
        let mut depth = 0;
        let mut args = Vec::new();
        let mut start = open + 1;
        let mut index = open;
        loop {
            match bytes.get(index) {
                Some(b'(') => depth += 1,
                Some(b')') => {
                    depth -= 1;
                    if depth == 0 {
                        args.push(text[start..index].split_whitespace().collect::<Vec<_>>().join(" "));
                        break;
                    }
                }
                Some(b',') if depth == 1 => {
                    args.push(text[start..index].split_whitespace().collect::<Vec<_>>().join(" "));
                    start = index + 1;
                }
                None => return Err(format!("{path}: unterminated call to {name}")),
                _ => {}
            }
            index += 1;
        }
        out.push(args);
    }
    Ok(out)
}

/// `NAME = value,` lines of the enums in a header.
pub fn enum_values(path: &str) -> R<BTreeMap<String, u32>> {
    let text = std::fs::read_to_string(repo_root().join(path)).map_err(|error| format!("{path}: {error}"))?;
    let mut out = BTreeMap::new();
    for line in text.lines() {
        let Some((name, value)) = line.trim().trim_end_matches(',').split_once('=') else { continue };
        let (name, value) = (name.trim(), value.trim());
        if !name.bytes().all(|byte| byte.is_ascii_uppercase() || byte.is_ascii_digit() || byte == b'_') || name.is_empty() {
            continue;
        }
        if let Some(value) = super::literal(value) {
            out.insert(name.to_string(), value);
        }
    }
    Ok(out)
}

/// A constant expression of literals and enum names joined by `|`.
fn flags_value(text: &str, names: &BTreeMap<String, u32>) -> Option<u32> {
    let mut value = 0;
    for term in text.trim_matches(|c| c == '(' || c == ')' || c == ' ').split('|') {
        let term = term.trim().trim_matches(|c| c == '(' || c == ')').trim();
        value |= super::literal(term).or_else(|| names.get(term).copied())?;
    }
    Some(value)
}

fn text_item(ctx: &Ctx, text: Text, reached: String) -> R<Vec<u32>> {
    let (address, copy, number) = match text {
        Text::Rom(address) => (Some(address), None, Number::None),
        Text::Copied(address, length, number) => (Some(address), Some(length), number),
        Text::Formatted(number) => (None, None, number),
    };
    let mut glyphs = number_glyphs(number);
    let Some(address) = address else { return Ok(glyphs) };
    ctx.roots.require(address)?;
    let (id, new) = ctx.item("battle_popup.text", address, POPUP_TEXT, vec![reached]);
    let mut bytes = Vec::new();
    loop {
        let at = address + bytes.len() as u32;
        if copy.map_or(false, |length| bytes.len() as u32 >= length) {
            return Err(format!("popup text 0x{address:08X}: no 0 in the {} bytes CopyBytes copies; AppendString would scan the old buffer", copy.unwrap()));
        }
        let byte = if new { ctx.rom.claim(at, 1, TEXT_FORMAT, id)?[0] } else { ctx.rom.peek(at, 1)?[0] };
        if byte == 0 {
            break;
        }
        bytes.push(byte);
    }
    if let (true, Some(length)) = (new, copy) {
        let rest = address + bytes.len() as u32 + 1;
        if rest < address + length {
            ctx.rom.claim(rest, address + length - rest, crate::rom::NEUTRAL, id)?;
        }
    }
    glyphs.extend(bytes.iter().filter_map(|&byte| glyph(byte)));
    if new {
        ctx.count(id, if copy.is_some() { "terminator (inside the CopyBytes length)" } else { "terminator" });
        ctx.set(id, json!({
            "text": bytes.iter().map(|&byte| if byte.is_ascii_graphic() || byte == b' ' { char::from(byte).to_string() } else { format!("{{0x{byte:02X}}}") }).collect::<String>(),
            "glyph_animations": bytes.iter().map(|&byte| glyph(byte)).collect::<Vec<_>>(),
            "copy_bytes": copy,
            "number": match number { Number::None => "none", Number::Digits => "digits", Number::SignedDigits => "sign and digits" },
        }));
    }
    Ok(glyphs)
}

fn resource_entry(ctx: &Ctx, table: usize, base: u32, resource: u32, reached: String, animations: &[u32]) -> R<()> {
    let entry = ctx.rom.claim(base + resource * 8, 8, "table.sprite_resources", table)?;
    let (frames, animation_table) = (le32(entry, 0), le32(entry, 4));
    for pointer in [frames, animation_table] {
        if !ctx.rom.is_data(pointer) {
            return Err(format!("sprite resource 0x{base:08X}[{resource}]: 0x{pointer:08X} is not ROM data"));
        }
    }
    sprites::sprite_set(ctx, frames, animation_table, reached, animations).map(|_| ())
}

/// A text argument as an address: a literal, an enum name, or a name declared with asm("D_XXXXXXXX") in the file.
fn text_address(arg: &str, source: &str, names: &BTreeMap<String, u32>) -> Option<u32> {
    let name = super::strip_casts(arg).trim_start_matches('&').trim();
    if let Some(value) = super::literal(name).or_else(|| names.get(name).copied()) {
        return Some(value);
    }
    let line = source.lines().find(|line| line.contains(name) && line.contains("asm(\"D_"))?;
    let hex = line.split("asm(\"D_").nth(1)?.get(..8)?;
    u32::from_str_radix(hex, 16).ok()
}

/// Each TEXT_CALLS entry against its file: the function is defined there, the file passes that text (and CopyBytes length,
/// and FormatNumberText flags) somewhere, and the file has as many CreateBattlePopupTextSprites calls as the table lists.
fn check_text_calls() -> R<()> {
    let mut names = enum_values("src/battle/popups/battle_popup.h")?;
    names.extend(enum_values("src/ui/window.h")?);
    let ascii = names["NUMBER_TEXT_ASCII"];
    let mut per_file: BTreeMap<&str, usize> = BTreeMap::new();
    for (function, file, text) in TEXT_CALLS {
        let path = format!("src/battle/popups/{file}");
        let source = strip_comments(&std::fs::read_to_string(repo_root().join(&path)).map_err(|error| format!("{path}: {error}"))?);
        if !source.contains(&format!("asm(\"func_{function:08X}\")")) {
            return Err(format!("{path} does not define func_{function:08X}"));
        }
        *per_file.entry(file).or_default() += 1;
        let resolve = |arg: Option<&String>| arg.and_then(|arg| text_address(arg, &source, &names));
        let shown = calls(&path, "CreateBattlePopupTextSprites")?;
        let number = match text {
            Text::Rom(address) => {
                if !shown.iter().any(|args| resolve(args.first()) == Some(address)) {
                    return Err(format!("{path}: no CreateBattlePopupTextSprites call passes 0x{address:08X}"));
                }
                Number::None
            }
            Text::Copied(address, length, number) => {
                let copied = calls(&path, "CopyBytes")?;
                if !copied.iter().any(|args| resolve(args.get(1)) == Some(address) && args.get(2).and_then(|arg| super::literal(arg)) == Some(length)) {
                    return Err(format!("{path}: no CopyBytes call copies {length} bytes from 0x{address:08X}"));
                }
                number
            }
            Text::Formatted(number) => number,
        };
        let expected = match number {
            Number::None => continue,
            Number::Digits => [ascii, ascii | names["NUMBER_TEXT_LEADING_SPACES"]],
            Number::SignedDigits => [ascii | names["NUMBER_TEXT_SIGN_PREFIX"]; 2],
        };
        let formatted = calls(&path, "FormatNumberText")?;
        if !formatted.iter().any(|args| {
            let width = args.get(1).and_then(|arg| super::literal(arg).or_else(|| names.get(arg.as_str()).copied()));
            let flags = args.get(2).and_then(|arg| flags_value(arg, &names));
            width == Some(4) && flags.map_or(false, |flags| expected.contains(&flags))
        }) {
            return Err(format!("{path}: no 4-digit FormatNumberText call with the flags listed for func_{function:08X}"));
        }
    }
    for (file, expected) in &per_file {
        let found = calls(&format!("src/battle/popups/{file}"), "CreateBattlePopupTextSprites")?.len();
        if found != *expected {
            return Err(format!("src/battle/popups/{file} has {found} CreateBattlePopupTextSprites calls, the port lists {expected}"));
        }
    }
    Ok(())
}

fn run(ctx: &Ctx) -> R<()> {
    let regions = verify_c::regions(&repo_root().join("regions.txt"))?;
    check_text_calls()?;

    let (table_id, _) = ctx.item("table.battle_unit_popup_callbacks", CALLBACKS, POPUP_TABLE, ctx.roots.require(CALLBACKS)?);
    ctx.count(table_id, "c_constant:BATTLE_POPUP_KIND_COUNT");
    let mut kinds = Vec::new();
    let mut texts: BTreeMap<u32, Vec<u32>> = BTreeMap::new();
    for kind in 0..POPUP_KINDS {
        let pair = ctx.rom.claim(CALLBACKS + kind * 8, 8, "table.battle_unit_popup_callbacks", table_id)?;
        let mut sources = Vec::new();
        for pointer in [le32(pair, 0), le32(pair, 4)] {
            if pointer == 0 {
                sources.push(json!(null));
                continue;
            }
            sources.push(json!(code_source(&regions, pointer)?));
            texts.entry(pointer & !1).or_default().push(kind);
        }
        kinds.push(json!({ "kind": kind, "init": format!("0x{:08X}", le32(pair, 0)), "update": format!("0x{:08X}", le32(pair, 4)), "init_source": sources[0], "update_source": sources[1] }));
    }

    let mut glyphs = BTreeSet::new();
    let mut unreached = Vec::new();
    for (function, file, text) in TEXT_CALLS {
        let Some(popup_kinds) = texts.get(&function) else {
            unreached.push(format!("func_{function:08X} ({file})"));
            continue;
        };
        let reached = format!("table.battle_unit_popup_callbacks@0x{CALLBACKS:08X}{popup_kinds:?}:func_{function:08X}");
        glyphs.extend(text_item(ctx, text, reached)?);
    }
    if !unreached.is_empty() {
        return Err(format!("popup text functions not in the popup callback table: {}", unreached.join(", ")));
    }
    ctx.set(table_id, json!({ "kinds": kinds }));

    let (glyph_table, glyph_new) = ctx.item("sprite.resources", GLYPH_RESOURCES, POPUP_TEXT, ctx.roots.require(GLYPH_RESOURCES)?);
    let glyph_ids: Vec<u32> = glyphs.iter().copied().collect();
    resource_entry(ctx, glyph_table, GLYPH_RESOURCES, 0, format!("sprite.resources@0x{GLYPH_RESOURCES:08X}"), &glyph_ids)?;
    if glyph_new {
        ctx.count(glyph_table, "c_literal:resource 0 (CreateBattlePopupTextSprites)");
        ctx.set(glyph_table, json!({ "stride": 8, "resources_read": [0], "glyph_animations_used": glyph_ids }));
    }

    let popup_names = enum_values("src/battle/popups/battle_popup.h")?;
    let mut display_names = enum_values("src/battle/battle_display.h")?;
    display_names.extend(popup_names.clone());
    let mut resources: BTreeMap<u32, Vec<String>> = BTreeMap::new();
    let mut effect_sites = Vec::new();
    for file in std::fs::read_dir(repo_root().join("src/battle/popups")).map_err(|error| error.to_string())? {
        let name = file.map_err(|error| error.to_string())?.file_name().to_string_lossy().into_owned();
        if name.ends_with(".c") && name != "create_battle_unit_popup_effect_sprite.c" {
            for args in calls(&format!("src/battle/popups/{name}"), "CreateBattleUnitPopupEffectSprite")? {
                effect_sites.push((name.clone(), args));
            }
        }
    }
    effect_sites.sort();
    for (file, args) in &effect_sites {
        let pinned = match POPUP_EFFECTS {
            Basis::C(files) => files.iter().any(|(path, _)| *path == format!("src/battle/popups/{file}")),
            _ => false,
        };
        if !pinned {
            return Err(format!("src/battle/popups/{file} calls CreateBattleUnitPopupEffectSprite but is not pinned"));
        }
        let resource = args.get(1).and_then(|text| popup_names.get(text.as_str()).copied().or_else(|| super::literal(text)));
        let animation = args.get(2).and_then(|text| super::literal(text));
        let flags = args.get(6).and_then(|text| flags_value(text, &display_names));
        match (resource, animation, flags) {
            (Some(resource), Some(0), Some(flags)) if flags & 0x40_0000 == 0 => resources.entry(resource).or_default().push(format!("src/battle/popups/{file}")),
            _ => return Err(format!("src/battle/popups/{file}: CreateBattleUnitPopupEffectSprite({}) is not a literal resource, animation 0 and 8-byte-entry flags", args.join(", "))),
        }
    }
    let arrival = popup_names.get(COMBINATION_ARRIVAL_RESOURCE).copied().ok_or("BATTLE_POPUP_RESOURCE_BLUE_PARTICLES is not in battle_popup.h")?;
    let arrival_file = "src/battle/combinations/animate_battle_combination_arrival.c";
    let arrival_source = std::fs::read_to_string(repo_root().join(arrival_file)).map_err(|error| format!("{arrival_file}: {error}"))?;
    let arrival_calls = calls(arrival_file, "CreateSpriteFromTable")?;
    let arrival_ok = arrival_source.contains("particle_resources = (void *)BATTLE_POPUP_SPRITE_RESOURCE_TABLE_ROM;")
        && arrival_calls.len() == 1
        && arrival_calls[0].get(0).map(String::as_str) == Some("particle_resources")
        && arrival_calls[0].get(1).map(String::as_str) == Some(COMBINATION_ARRIVAL_RESOURCE)
        && arrival_calls[0].get(2).map(String::as_str) == Some("0");
    if !arrival_ok {
        return Err(format!("{arrival_file}: expected one CreateSpriteFromTable(particle_resources, {COMBINATION_ARRIVAL_RESOURCE}, 0, ...) on the popup sprite table"));
    }
    resources.entry(arrival).or_default().push(arrival_file.into());
    let (effect_table, effect_new) = ctx.item("sprite.resources", EFFECT_RESOURCES, POPUP_EFFECTS, ctx.roots.require(EFFECT_RESOURCES)?);
    for &resource in resources.keys() {
        resource_entry(ctx, effect_table, EFFECT_RESOURCES, resource, format!("sprite.resources@0x{EFFECT_RESOURCES:08X}"), &[0])?;
    }
    if effect_new {
        ctx.count(effect_table, "resource ids passed by the C callers");
        ctx.set(effect_table, json!({ "stride": 8, "resources_read": resources }));
    }

    for table in POPUP_GRAPHICS {
        let reached = ctx.roots.require(table)?;
        graphics::sprite_graphics(ctx, table, 0, false, reached[0].clone())?;
    }

    if !texts.contains_key(&UPDATE_DAMAGE_POPUP) {
        return Err(format!("func_{UPDATE_DAMAGE_POPUP:08X} is not in the popup callback table"));
    }
    let (shake_id, _) = ctx.item("table.battle_damage_shake_offsets", DAMAGE_SHAKE, DAMAGE_SHAKE_READER, ctx.roots.require(DAMAGE_SHAKE)?);
    ctx.count(shake_id, "c_constant:BATTLE_POPUP_DAMAGE_SHAKE_LAST_UPDATE + 1");
    let last = *popup_names.get("BATTLE_POPUP_DAMAGE_SHAKE_LAST_UPDATE").ok_or("BATTLE_POPUP_DAMAGE_SHAKE_LAST_UPDATE is not in battle_popup.h")?;
    let offsets = ctx.rom.claim(DAMAGE_SHAKE, (last + 1) * 4, "table.battle_damage_shake_offsets", shake_id)?;
    ctx.set(shake_id, json!({ "x_offsets": offsets.chunks(4).map(|word| le32(word, 0) as i32).collect::<Vec<_>>() }));
    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn glyph_animations() {
        assert_eq!(glyph(b'A'), Some(0));
        assert_eq!(glyph(b'Z'), Some(25));
        assert_eq!(glyph(b'0'), Some(32));
        assert_eq!(glyph(b'9'), Some(41));
        assert_eq!(glyph(b'?'), Some(43));
        assert_eq!(glyph(b' '), None);
        assert_eq!(glyph(b'a'), None);
    }

    #[test]
    fn flag_expressions() {
        let names: BTreeMap<String, u32> = [("A".to_string(), 0x20), ("B".to_string(), 0x400)].into_iter().collect();
        assert_eq!(flags_value("(A | B)", &names), Some(0x420));
        assert_eq!(flags_value("0x100", &names), Some(0x100));
        assert_eq!(flags_value("phase", &names), None);
    }
}
