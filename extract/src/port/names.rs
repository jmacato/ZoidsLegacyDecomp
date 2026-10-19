//! Name and description pointer tables, the pilot quote table and the zoid proficiency text slots.

use std::collections::BTreeSet;

use serde_json::{json, Value};

use super::area;
use super::tables::{Reach, PILOT_COUNT};
use super::text::{self, parse_item, parse_plain, parse_window, sjis};
use crate::basis::Basis;
use crate::rom::{le32, Cursor, R};
use crate::run::Ctx;

const PLAYER_STATE_H: (&str, &str) = ("src/game/player_state.h", "dadeb1433712e28f47ef2910bb1c20a0d96da19b");
const BATTLE_H: (&str, &str) = ("src/battle/battle.h", "a1dc0242af18cee1d3efcb0fee52c780fc7dcc98");
const BATTLE_DISPLAY_H: (&str, &str) = ("src/battle/battle_display.h", "ed9ae1d1b7b71e189ca7f207078675f82ea365b5");
const DECK_COMMANDS_H: (&str, &str) = ("src/battle/deck_commands/deck_commands.h", "a9c37e35a2366d649455b0864194df3f43e84b05");
const MODEL_SELECTION: (&str, &str) = ("src/ui/build_unlocked_zoid_model_selection.c", "48e34a0479b522ddb8ead5e11f04fff689ae90e1");
const ASSETS_EVENT: (&str, &str) = ("src/events/commands/event_update_player_assets_and_roster.c", "2513c231e791399171d93ba5a7ec53b684c9bad1");
const CHALLENGE_MENU: (&str, &str) = ("src/game/modes/run_challenge_menu.c", "11ced92b4c8b6955266529d668cfeac81cdd208a");
const STATUS_MENU: (&str, &str) = ("src/ui/run_player_status_menu.c", "0c4f77dcafbd6975504b921df5838d0e50421e05");
const ITEM_SHOP: (&str, &str) = ("src/game/modes/run_item_shop.c", "cc40340e48e052a5fdd528554c4ab853e929a9d3");
const EQUIPMENT_SHOP: (&str, &str) = ("src/game/modes/run_equipment_shop.c", "ddf098ab99a62be94f4fe0b302f282e8bca19476");
const LINK_TRADE: (&str, &str) = ("src/game/modes/run_link_trade.c", "9a45cd96da0cd53a73026a09b34e40757363a6c5");
const ABILITY_TEXT: (&str, &str) = ("src/zoids/format_pilot_ability_text.c", "45f1812f298e385b9b64f19e9e3b3b93a6a156f0");
const ABILITY_DESCRIPTION_TEXT: (&str, &str) = ("src/zoids/format_pilot_ability_description_text.c", "83cadfc545863387ebd0611a78820a74df218f9a");

pub const ZOID_NAMES: Basis = Basis::C(&[
    MODEL_SELECTION,
    ("src/ui/append_zoid_model_selection_rows.c", "b464da319f5d7dd4e0b4a5f2f18dc18ea1883379"),
    CHALLENGE_MENU,
    ASSETS_EVENT,
]);
pub const PILOT_NAMES: Basis = Basis::C(&[
    BATTLE_DISPLAY_H,
    ("src/zoids/get_pilot_display_name.c", "b1e539d3d52ba3346e2d9f15832f42509c57af16"),
    ("src/battle/get_battle_pilot_display_name.c", "852cc1aaddb30c27ce83f3ef7a4eb96ba7ee750d"),
    ("src/game/reset_player_name_and_battle_quote.c", "6888e84610acd598646a709791721934a7808583"),
    ("src/ui/draw_player_zoid_team_details.c", "1cfe38bf9bd4f9128fc1ec624b9467dde054e500"),
]);
pub const AUXILIARY_PILOT_NAMES: Basis = Basis::C(&[PLAYER_STATE_H, STATUS_MENU]);
pub const EQUIPMENT_NAMES: Basis = Basis::C(&[
    BATTLE_H,
    ("src/battle/show_queued_battle_equipment_name.c", "6eee81f50626cad2190990e6fad46460129f6afb"),
    EQUIPMENT_SHOP,
    ("src/ui/append_player_equipment_selection_rows.c", "64fc545bbb333a6fbcf428763864d24812c7f389"),
]);
pub const RECOVERY_ITEM_NAMES: Basis = Basis::C(&[
    PLAYER_STATE_H,
    ITEM_SHOP,
    ("src/ui/append_recovery_item_inventory_rows.c", "cb55ee354b7af39405cabe09745159cce15eaaab"),
]);
pub const RECOVERY_ITEM_DESCRIPTIONS: Basis = Basis::C(&[PLAYER_STATE_H, ITEM_SHOP]);
pub const ZOID_CORE_NAMES: Basis = Basis::C(&[
    PLAYER_STATE_H,
    CHALLENGE_MENU,
    ("src/ui/append_zoid_core_inventory_rows.c", "2b22ca63063575f4a214706c9d3f507553d7b7a3"),
]);
pub const ZOID_CORE_DESCRIPTIONS: Basis = Basis::C(&[PLAYER_STATE_H, LINK_TRADE]);
pub const DECK_COMMAND_NAMES: Basis = Basis::C(&[
    DECK_COMMANDS_H,
    ("src/battle/deck_commands/append_selected_deck_command_rows.c", "b2255419abbb298ea0ff0ba1e8d81c748fb3bd37"),
    CHALLENGE_MENU,
    ASSETS_EVENT,
]);
pub const ABILITY_NAMES: Basis = Basis::C(&[BATTLE_H, ABILITY_TEXT]);
pub const ABILITY_DESCRIPTIONS: Basis = Basis::C(&[BATTLE_H, ABILITY_DESCRIPTION_TEXT]);
pub const EFFECT_NAMES: Basis = Basis::C(&[
    PLAYER_STATE_H,
    ("src/events/commands/event_grant_pulse_effect.c", "076ffc9ae8f74d9955a706cdffd2c3cb0645030a"),
    STATUS_MENU,
]);
pub const EFFECT_DESCRIPTIONS: Basis = Basis::C(&[PLAYER_STATE_H, STATUS_MENU]);
pub const MAP_GROUP_NAMES: Basis = Basis::C(&[
    ("src/field/show_field_map_name.c", "e1bfedd7b08c5545951940ad3b8154a744287612"),
    ("src/game/modes/run_town_map.c", "6aee928007401f00ac0b3fa9169c9b9b3eb888e4"),
    ("src/ui/run_recovery_item_menu.c", "8bd3358eb75982acdf8c7f9de10194f39820e9d6"),
]);
pub const GROWTH_CLASS_NAMES: Basis = Basis::C(&[PLAYER_STATE_H, STATUS_MENU]);
pub const QUOTES: Basis = Basis::C(&[
    BATTLE_DISPLAY_H,
    ("src/battle/show_battle_pilot_action_quote.c", "00383c522e8ad680cd7cf97e7b018a5a23f09588"),
    ("src/game/modes/run_battle_scene.c", "1d8942aaaced975a60c680c0ca681e138bf98c69"),
]);
pub const SCROLLING: Basis = Basis::C(&[
    DECK_COMMANDS_H,
    ("src/battle/deck_commands/show_deck_command_description.c", "e791f25fdb4adfe33d801af17d7445f3f2a6d1d9"),
    ("src/ui/initialize_scrolling_text_window.c", "433bbd795ae0da1ad5e79608ecb8b6902775ca9d"),
    ("src/ui/refresh_scrolling_text_window.c", "b3c18755a0d83663481f762b71f58808625ba8af"),
    ("src/ui/window.h", "c299d1e84300353c8f991978a0c2761133a5e42c"),
]);
pub const PROFICIENCIES: Basis = Basis::C(&[PLAYER_STATE_H, BATTLE_H, ABILITY_TEXT, ABILITY_DESCRIPTION_TEXT]);
const PLAYER_AUXILIARY_PILOT_COUNT: u32 = 6;
const PLAYER_RECOVERY_ITEM_COUNT: u32 = 10;
const PLAYER_ZOID_CORE_COUNT: u32 = 90;
/// Last value of enum DeckCommandId (DECK_COMMAND_LORD_GALE_GATTAI).
const DECK_COMMAND_LAST: u32 = 51;
/// Last value of enum PilotAbilityKind (PILOT_ABILITY_BALLISTIC_ACCURACY_BONUS).
const PILOT_ABILITY_LAST: u32 = 39;
/// Last value of enum AuxiliaryPilotEffectKind (AUXILIARY_EFFECT_ZOS_2).
const AUXILIARY_EFFECT_LAST: u32 = 25;
/// Growth classes run_player_status_menu.c stores: menu rows 0..3, 4 (custom distribution, sp20 + 0x32 = 4), PILOT_GROWTH_CLASS_MANUAL and PILOT_GROWTH_CLASS_RANDOM.
const GROWTH_CLASSES: [u8; 7] = [0, 1, 2, 3, 4, 5, 6];
const BATTLE_PILOT_QUOTE_KIND_COUNT: u32 = 5;
const BATTLE_PILOT_QUOTES_PER_KIND: u32 = 3;
const BATTLE_PILOT_QUOTE_ATTACK: u32 = 0;
const PLAYER_PROTAGONIST_PILOT_ID: u32 = 1;
const PROFICIENCY_STRIDE: u32 = 35;

const ZOID_NAME_TABLE: u32 = 0x087E_DD54;
const PILOT_NAME_TABLE: u32 = 0x087E_DFB4;
const AUXILIARY_PILOT_NAME_TABLE: u32 = 0x087E_E158;
const EQUIPMENT_NAME_TABLE: u32 = 0x087E_E170;
const RECOVERY_ITEM_NAME_TABLE: u32 = 0x087E_EE10;
const RECOVERY_ITEM_DESCRIPTION_TABLE: u32 = 0x087E_EE38;
const ZOID_CORE_NAME_TABLE: u32 = 0x087E_EE60;
const ZOID_CORE_DESCRIPTION_TABLE: u32 = 0x087E_EFC8;
const DECK_COMMAND_NAME_TABLE: u32 = 0x087E_F130;
const DECK_COMMAND_DESCRIPTION_TABLE: u32 = 0x087E_F200;
const ABILITY_NAME_TABLE: u32 = 0x087E_F2D0;
const ABILITY_DESCRIPTION_TABLE: u32 = 0x087E_F370;
const EFFECT_NAME_TABLE: u32 = 0x087E_F410;
const EFFECT_DESCRIPTION_TABLE: u32 = 0x087E_F478;
const MAP_GROUP_NAME_TABLE: u32 = 0x087E_F4E0;
const QUOTE_TABLE: u32 = 0x087E_F590;
const GROWTH_CLASS_NAME_TABLE: u32 = 0x087A_1F30;
const PROFICIENCY_NAMES: u32 = 0x087A_5962;
const PROFICIENCY_DESCRIPTIONS: u32 = 0x087A_5B29;

/// The text grammar of a C consumer: DrawWindowText, AppendWindowTextItem, CopyString / AppendString,
/// or RefreshScrollingTextWindow.
#[derive(Clone, Copy, PartialEq)]
enum Grammar {
    Window,
    Item,
    Plain,
    Scrolling,
}

fn glyphs(bytes: &[u8]) -> String {
    let mut out = String::new();
    for &byte in bytes {
        match byte {
            0x20..=0x7E if !matches!(byte, b'{' | b'}' | b'\\') => out.push(byte as char),
            _ => out.push_str(&format!("{{{byte:02X}}}")),
        }
    }
    out
}

/// RefreshScrollingTextWindow: 0 ends; 1 and 2 skip one and two operand bytes without reading them; 3 and 0x0A advance one;
/// any other byte below 0x20 does not advance, so the C never returns; every other unit is two bytes copied to the line.
fn parse_scrolling(cursor: &mut Cursor) -> R<String> {
    let start = cursor.address;
    let mut text = String::new();
    loop {
        let at = cursor.address;
        match cursor.u8()? {
            0 => return Ok(text),
            1 => {
                cursor.address += 1;
                text.push_str("{color}");
            }
            2 => {
                cursor.address += 2;
                text.push_str("{pos}");
            }
            3 => text.push_str("{name}"),
            0x0A => text.push('\n'),
            byte @ 0x04..=0x1F => {
                return Err(format!("scrolling text at 0x{start:08X}: byte 0x{byte:02X} at 0x{at:08X} never advances the cursor"));
            }
            byte => {
                let second = cursor.u8()?;
                if (0x80..=0x9F).contains(&byte) {
                    text.push_str(&sjis(u16::from_be_bytes([byte, second])));
                } else {
                    text.push_str(&glyphs(&[byte, second]));
                }
            }
        }
    }
}

fn decode(ctx: &Ctx, grammar: Grammar, address: u32, reached: Vec<String>) -> R<String> {
    match grammar {
        Grammar::Window => text::window_text(ctx, address, reached)?,
        Grammar::Item => text::text_item(ctx, address, reached)?,
        Grammar::Plain => text::string(ctx, address, reached)?,
        Grammar::Scrolling => {
            let (id, new) = ctx.item("text.scrolling", address, SCROLLING, reached);
            if new {
                let mut cursor = ctx.rom.cursor(address, text::FORMAT, id);
                let rendered = parse_scrolling(&mut cursor)?;
                ctx.view(id, json!({ "t": "text", "g": "scrolling", "end": cursor.address }));
                ctx.set(id, json!({ "text": rendered }));
            }
            id
        }
    };
    let mut dry = ctx.rom.dry_cursor(address);
    match grammar {
        Grammar::Window => parse_window(&mut dry),
        Grammar::Item => parse_item(&mut dry),
        Grammar::Plain => parse_plain(&mut dry),
        Grammar::Scrolling => parse_scrolling(&mut dry),
    }
}

fn grammar_names(grammars: &[Grammar]) -> Vec<&'static str> {
    grammars
        .iter()
        .map(|grammar| match grammar {
            Grammar::Window => "DrawWindowText",
            Grammar::Item => "AppendWindowTextItem",
            Grammar::Plain => "CopyString/AppendString",
            Grammar::Scrolling => "RefreshScrollingTextWindow",
        })
        .collect()
}

/// A text pointer read by the C: decoded with each consumer's grammar when it points at ROM data.
fn text_pointer(ctx: &Ctx, pointer: u32, grammars: &[Grammar], from: String) -> R<Value> {
    if area(pointer) != "rom" {
        return Ok(json!({ "pointer": format!("0x{pointer:08X}"), "area": area(pointer) }));
    }
    let mut rendered = String::new();
    for (index, &grammar) in grammars.iter().enumerate() {
        let text = decode(ctx, grammar, pointer, vec![from.clone()])?;
        if index == 0 {
            rendered = text;
        }
    }
    Ok(json!({ "pointer": format!("0x{pointer:08X}"), "text": rendered }))
}

fn pointer_table(ctx: &Ctx, kind: &str, address: u32, indices: &[u32], source: &str, grammars: &[Grammar], basis: Basis) -> R<()> {
    let reached = ctx.roots.require(address)?;
    let (id, _) = ctx.item(kind, address, basis, reached);
    let mut entries = Vec::new();
    for &index in indices {
        let pointer = le32(ctx.rom.claim(address + index * 4, 4, kind, id)?, 0);
        let mut entry = text_pointer(ctx, pointer, grammars, format!("{kind}@0x{address:08X}[{index}]"))?;
        entry["index"] = json!(index);
        entries.push(entry);
    }
    ctx.count(id, source);
    ctx.set(id, json!({ "entry_bytes": 4, "grammars": grammar_names(grammars), "entries": entries }));
    Ok(())
}

fn next_root(ctx: &Ctx, address: u32) -> R<u32> {
    ctx.roots.by_address().range(address + 1..).next().map(|(next, _)| *next).ok_or_else(|| format!("no root after 0x{address:08X}"))
}

/// ShowBattlePilotActionQuote: entry pilot * 120 + kind * 24 + index * 8 holds the text pointer (+0) and portrait variant (+4);
/// bytes +5..+7 are never read. For the protagonist's attack quotes the text comes from RAM, so only the portrait byte is read.
fn quotes(ctx: &Ctx) -> R<()> {
    const KIND: &str = "table.pilot_quotes";
    let (id, _) = ctx.item(KIND, QUOTE_TABLE, QUOTES, ctx.roots.require(QUOTE_TABLE)?);
    let mut pilots = Vec::new();
    for pilot in 0..PILOT_COUNT {
        let mut kinds = Vec::new();
        for kind in 0..BATTLE_PILOT_QUOTE_KIND_COUNT {
            let mut quotes = Vec::new();
            for index in 0..BATTLE_PILOT_QUOTES_PER_KIND {
                let at = QUOTE_TABLE + pilot * 120 + kind * 24 + index * 8;
                let portrait = ctx.rom.claim(at + 4, 1, KIND, id)?[0];
                ctx.unread(id, at + 5, 3, "BattlePilotQuoteEntry.data05[3] (battle_display.h): ShowBattlePilotActionQuote (show_battle_pilot_action_quote.c), the only reader of 0x087EF590 (literal pools 0x080CCC60, 0x080CCDF8), loads only portrait_variant +4 (ldrb [r6, #4] at 0x080CCC34) and text +0 (ldr at 0x080CCC58 and 0x080CCDEC) at table + pilot * 120 + kind * 24 + index * 8, always a multiple of 8")?;
                let mut entry = if pilot == PLAYER_PROTAGONIST_PILOT_ID && kind == BATTLE_PILOT_QUOTE_ATTACK {
                    ctx.unread(id, at, 4, "text pointer of the protagonist's attack quotes: ShowBattlePilotActionQuote prints the player battle quote from RAM for this pilot and kind (show_battle_pilot_action_quote.c); another pilot reaches this entry only through an out-of-range quote index, which local code does not produce and a link partner running this same ROM does not send (run_battle.c:2014, 3239 copy the partner's index; assumption chosen by the user)")?;
                    json!({ "text": Value::Null, "text_source": "player battle quote in RAM" })
                } else {
                    let pointer = le32(ctx.rom.claim(at, 4, KIND, id)?, 0);
                    text_pointer(ctx, pointer, &[Grammar::Window], format!("{KIND}@0x{QUOTE_TABLE:08X}[{pilot}][{kind}][{index}]"))?
                };
                entry["portrait_variant"] = json!(portrait);
                quotes.push(entry);
            }
            kinds.push(json!(quotes));
        }
        pilots.push(json!({ "pilot": pilot, "quotes": kinds }));
    }
    ctx.count(id, "c_enum:BATTLE_PILOT_QUOTE_PILOT_COUNT x BATTLE_PILOT_QUOTE_KIND_COUNT x BATTLE_PILOT_QUOTES_PER_KIND (struct BattlePilotQuoteSet)");
    ctx.set(id, json!({ "entry_bytes": 8, "pilots": pilots, "unread": "data05[3] of every entry" }));
    Ok(())
}

/// FormatPilotAbilityText and FormatPilotAbilityDescriptionText append the 35-byte slot `value` of each table for
/// abilities PILOT_ABILITY_ZOID_PROFICIENCY_1..3; the value is the low byte the schedule teaches (stored as u8).
fn proficiencies(ctx: &Ctx, values: &BTreeSet<u8>) -> R<()> {
    for (kind, table) in [("table.zoid_proficiency_names", PROFICIENCY_NAMES), ("table.zoid_proficiency_descriptions", PROFICIENCY_DESCRIPTIONS)] {
        let (id, _) = ctx.item(kind, table, PROFICIENCIES, ctx.roots.require(table)?);
        let mut entries = Vec::new();
        let mut read = BTreeSet::new();
        for &value in values {
            let address = table + u32::from(value) * PROFICIENCY_STRIDE;
            let text = decode(ctx, Grammar::Plain, address, vec![format!("{kind}@0x{table:08X}[{value}]")])?;
            let mut dry = ctx.rom.dry_cursor(address);
            parse_plain(&mut dry)?;
            read.extend(address..dry.address);
            entries.push(json!({ "index": value, "address": format!("0x{address:08X}"), "text": text }));
        }
        let last = u32::from(*values.iter().next_back().ok_or("no zoid proficiency value is reached")?);
        let listed: Vec<String> = values.iter().map(|value| value.to_string()).collect();
        for slot in 0..=last {
            let base = table + slot * PROFICIENCY_STRIDE;
            let reason = if values.contains(&(slot as u8)) {
                format!("slot {slot} after its 0 terminator: AppendString stops at the first 0 (src/engine/append_string.c); FormatPilotAbilityText and FormatPilotAbilityDescriptionText append the slot text (src/zoids/format_pilot_ability_text.c, src/zoids/format_pilot_ability_description_text.c)")
            } else {
                format!(
                    "slot {slot}: FormatPilotAbilityText and FormatPilotAbilityDescriptionText index by the value of a PILOT_ABILITY_ZOID_PROFICIENCY_1..3 ability (src/zoids/format_pilot_ability_text.c, src/zoids/format_pilot_ability_description_text.c), which UpdatePilotAbilities stores as the low byte of a table.pilot_ability_schedule value (src/zoids/update_pilot_abilities.c); the values are {{{}}}",
                    listed.join(", ")
                )
            };
            let mut at = base;
            while at < base + PROFICIENCY_STRIDE {
                if read.contains(&at) {
                    at += 1;
                    continue;
                }
                let start = at;
                while at < base + PROFICIENCY_STRIDE && !read.contains(&at) {
                    at += 1;
                }
                ctx.unread(id, start, at - start, &reason)?;
            }
        }
        ctx.count(id, "values of table.pilot_ability_schedule entries with kind 3..5 (PILOT_ABILITY_ZOID_PROFICIENCY_1..3)");
        ctx.set(id, json!({ "slot_bytes": PROFICIENCY_STRIDE, "grammars": grammar_names(&[Grammar::Plain]), "entries": entries }));
    }
    Ok(())
}

fn within(what: &str, ids: &BTreeSet<u8>, count: u32) -> R<()> {
    match ids.iter().find(|&&id| u32::from(id) >= count) {
        Some(bad) => Err(format!("a decoded record names {what} {bad}, past the {count} entries of its name table")),
        None => Ok(()),
    }
}

pub fn run(ctx: &Ctx, reach: &Reach, zoid_count: u32) -> R<()> {
    use Grammar::{Item, Plain, Scrolling, Window};
    within("pilot ability kind", &reach.ability_kinds, PILOT_ABILITY_LAST + 1)?;
    within("auxiliary effect kind", &reach.effect_kinds, AUXILIARY_EFFECT_LAST + 1)?;
    within("zoid core", &reach.cores, PLAYER_ZOID_CORE_COUNT)?;
    within("deck command", &reach.deck_commands, DECK_COMMAND_LAST + 1)?;
    let range = |count: u32| (0..count).collect::<Vec<u32>>();
    pointer_table(
        ctx,
        "table.zoid_names",
        ZOID_NAME_TABLE,
        &range(zoid_count),
        "c_loop_bound:build_unlocked_zoid_model_selection.c zoid ids 1..151; entry 0 is the table base",
        &[Window, Item, Plain],
        ZOID_NAMES,
    )?;
    pointer_table(
        ctx,
        "table.pilot_names",
        PILOT_NAME_TABLE,
        &range(PILOT_COUNT),
        "c_enum:BATTLE_PILOT_QUOTE_PILOT_COUNT (pilot id space; equals next_root)",
        &[Window, Plain],
        PILOT_NAMES,
    )?;
    pointer_table(
        ctx,
        "table.auxiliary_pilot_names",
        AUXILIARY_PILOT_NAME_TABLE,
        &range(PLAYER_AUXILIARY_PILOT_COUNT),
        "c_constant:PLAYER_AUXILIARY_PILOT_COUNT (indexed by a player pilot's auxiliary_pilot_id)",
        &[Window],
        AUXILIARY_PILOT_NAMES,
    )?;
    pointer_table(
        ctx,
        "table.equipment_names",
        EQUIPMENT_NAME_TABLE,
        &range(reach.equipment_count),
        "same ids as table.equipment",
        &[Window, Item, Plain],
        EQUIPMENT_NAMES,
    )?;
    pointer_table(
        ctx,
        "table.recovery_item_names",
        RECOVERY_ITEM_NAME_TABLE,
        &range(PLAYER_RECOVERY_ITEM_COUNT),
        "c_constant:PLAYER_RECOVERY_ITEM_COUNT",
        &[Window, Item, Plain],
        RECOVERY_ITEM_NAMES,
    )?;
    pointer_table(
        ctx,
        "table.recovery_item_descriptions",
        RECOVERY_ITEM_DESCRIPTION_TABLE,
        &range(PLAYER_RECOVERY_ITEM_COUNT),
        "c_constant:PLAYER_RECOVERY_ITEM_COUNT",
        &[Window],
        RECOVERY_ITEM_DESCRIPTIONS,
    )?;
    pointer_table(
        ctx,
        "table.zoid_core_names",
        ZOID_CORE_NAME_TABLE,
        &range(PLAYER_ZOID_CORE_COUNT),
        "c_constant:PLAYER_ZOID_CORE_COUNT",
        &[Window, Plain],
        ZOID_CORE_NAMES,
    )?;
    pointer_table(
        ctx,
        "table.zoid_core_descriptions",
        ZOID_CORE_DESCRIPTION_TABLE,
        &range(PLAYER_ZOID_CORE_COUNT),
        "c_constant:PLAYER_ZOID_CORE_COUNT",
        &[Window],
        ZOID_CORE_DESCRIPTIONS,
    )?;
    pointer_table(
        ctx,
        "table.deck_command_names",
        DECK_COMMAND_NAME_TABLE,
        &range(DECK_COMMAND_LAST + 1),
        "c_enum:DeckCommandId (0..51)",
        &[Window, Item, Plain],
        DECK_COMMAND_NAMES,
    )?;
    pointer_table(
        ctx,
        "table.deck_command_descriptions",
        DECK_COMMAND_DESCRIPTION_TABLE,
        &range(DECK_COMMAND_LAST + 1),
        "c_enum:DeckCommandId (0..51)",
        &[Scrolling],
        SCROLLING,
    )?;
    pointer_table(
        ctx,
        "table.pilot_ability_names",
        ABILITY_NAME_TABLE,
        &range(PILOT_ABILITY_LAST + 1),
        "c_enum:PilotAbilityKind (largest value 39)",
        &[Plain],
        ABILITY_NAMES,
    )?;
    pointer_table(
        ctx,
        "table.pilot_ability_descriptions",
        ABILITY_DESCRIPTION_TABLE,
        &range(PILOT_ABILITY_LAST + 1),
        "c_enum:PilotAbilityKind (largest value 39)",
        &[Plain],
        ABILITY_DESCRIPTIONS,
    )?;
    pointer_table(
        ctx,
        "table.auxiliary_effect_names",
        EFFECT_NAME_TABLE,
        &range(AUXILIARY_EFFECT_LAST + 1),
        "c_enum:AuxiliaryPilotEffectKind (0..25)",
        &[Item, Plain],
        EFFECT_NAMES,
    )?;
    pointer_table(
        ctx,
        "table.auxiliary_effect_descriptions",
        EFFECT_DESCRIPTION_TABLE,
        &range(AUXILIARY_EFFECT_LAST + 1),
        "c_enum:AuxiliaryPilotEffectKind (0..25)",
        &[Window],
        EFFECT_DESCRIPTIONS,
    )?;
    let map_groups = (next_root(ctx, MAP_GROUP_NAME_TABLE)? - MAP_GROUP_NAME_TABLE) / 4;
    pointer_table(
        ctx,
        "table.field_map_group_names",
        MAP_GROUP_NAME_TABLE,
        &range(map_groups),
        "next_root (ShowFieldMapName indexes by a field map definition's map_group_id; run_town_map.c reads ids 1..42)",
        &[Window, Item, Plain],
        MAP_GROUP_NAMES,
    )?;
    let classes: BTreeSet<u32> = GROWTH_CLASSES.iter().chain(reach.growth_classes.iter()).map(|&class| u32::from(class)).collect();
    pointer_table(
        ctx,
        "table.pilot_growth_class_names",
        GROWTH_CLASS_NAME_TABLE,
        &classes.into_iter().collect::<Vec<_>>(),
        "growth classes the C stores: run_player_status_menu.c rows 0..3, 4 for a custom distribution (*(sp20 + 0x32) = 4), PILOT_GROWTH_CLASS_MANUAL, PILOT_GROWTH_CLASS_RANDOM",
        &[Window],
        GROWTH_CLASS_NAMES,
    )?;
    quotes(ctx)?;
    proficiencies(ctx, &reach.proficiencies)
}

/// Text read by RefreshScrollingTextWindow (InitializeScrollingTextWindow roots).
pub fn scrolling_text(ctx: &Ctx, address: u32, reached: Vec<String>) -> R<usize> {
    let (id, new) = ctx.item("text.scrolling", address, SCROLLING, reached);
    if new {
        let mut cursor = ctx.rom.cursor(address, text::FORMAT, id);
        let rendered = parse_scrolling(&mut cursor)?;
        ctx.view(id, json!({ "t": "text", "g": "scrolling", "end": cursor.address }));
        ctx.set(id, json!({ "text": rendered }));
    }
    Ok(id)
}
