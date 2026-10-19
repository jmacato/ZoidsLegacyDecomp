//! Database viewers: per-ID menu script and scrolling text pointer tables.

use serde_json::json;

use super::menu_script::menu_script;
use super::names::{scrolling_text, SCROLLING};
use super::Port;
use crate::basis::Basis;
use crate::rom::{le32, R};
use crate::run::Ctx;

const ZOID_DATABASE: Basis = Basis::C(&[
    ("src/ui/run_zoid_database_viewer.c", "8bd4d7d998f05ecc32b977fb9156793e9fbcbaa8"),
    ("src/ui/build_unlocked_zoid_model_selection.c", "48e34a0479b522ddb8ead5e11f04fff689ae90e1"),
]);
const CHARACTER_DATABASE: Basis = Basis::C(&[
    ("src/ui/run_character_database_viewer.c", "8f7ec7df2dd4e8bfd257884968975fc898fb8c95"),
    ("src/battle/battle_display.h", "ed9ae1d1b7b71e189ca7f207078675f82ea365b5"),
]);
const EQUIPMENT_DATABASE: Basis = Basis::C(&[
    ("src/ui/run_equipment_database_viewer.c", "32a38808904a12ea224aaf40df87f21918342209"),
    ("src/game/player_state.h", "dadeb1433712e28f47ef2910bb1c20a0d96da19b"),
]);

const STAT_HELP: Basis = Basis::C(&[
    ("src/ui/run_equipment_stat_help_menu.c", "02e8a5cba69be6afa34d2c70ada8410963ee65f7"),
    ("src/ui/player_selection.h", "d3234c00360dfed9bd342175885b1a1ac08cf028"),
]);

const EQUIPMENT_MENU: Basis = Basis::C(&[
    ("src/ui/run_player_equipment_menu.c", "623d2c19dcb2e97417406203512ecfef3e128fe5"),
    ("src/battle/battle.h", "a1dc0242af18cee1d3efcb0fee52c780fc7dcc98"),
]);

pub const PORT: Port = Port { name: "databases", bases: &[ZOID_DATABASE, CHARACTER_DATABASE, EQUIPMENT_DATABASE, SCROLLING, STAT_HELP, EQUIPMENT_MENU], run };

const COMPATIBILITY_MESSAGES: u32 = 0x087F_2DEC;

const WEAPON_STAT_HELP_SCRIPTS: u32 = 0x087A_26B0;
const COMMAND_COMMON_STAT_HELP_SCRIPTS: u32 = 0x087A_26C8;
const COMMAND_EFFECT_STAT_HELP_SCRIPTS: u32 = 0x087A_26D8;
const EQUIPMENT_STAT_HELP_CURSOR_Y: u32 = 0x087A_2788;
const EQUIPMENT_RECORDS: u32 = 0x087B_2524;
/// WEAPON_HELP_POWER..WEAPON_HELP_ATTRIBUTES (selection moves down while <= WEAPON_HELP_CLASSIFICATION).
const WEAPON_HELP_ROWS: u32 = 6;
const WEAPON_HELP_RANGE_AND_AREA: u32 = 2;
const WEAPON_HELP_ACCURACY: u32 = 1;

/// Zoid ids: build_unlocked_zoid_model_selection.c loops 1..151 over a table based at id 0.
const ZOID_IDS: u32 = 152;
const BATTLE_PILOT_QUOTE_PILOT_COUNT: u32 = 105;
const PLAYER_EQUIPMENT_COUNT: u32 = 200;

#[derive(Clone, Copy)]
enum Consumer {
    MenuScript,
    Scrolling,
}

fn pointer_table(ctx: &Ctx, base: u32, count: u32, count_source: &str, basis: Basis, consumer: Consumer) -> R<()> {
    pointer_table_at(ctx, base, 0, count, count_source, basis, consumer).map(|_| ())
}

fn pointer_table_at(ctx: &Ctx, base: u32, first: u32, count: u32, count_source: &str, basis: Basis, consumer: Consumer) -> R<usize> {
    let (id, _) = ctx.item("table.database_text_pointers", base, basis, ctx.roots.require(base)?);
    ctx.count(id, count_source);
    let mut entries = Vec::new();
    for index in first..first + count {
        let pointer = le32(ctx.rom.claim(base + index * 4, 4, "table.database_text_pointers", id)?, 0);
        entries.push(format!("0x{pointer:08X}"));
        if pointer == 0 {
            continue;
        }
        if !ctx.rom.is_data(pointer) {
            return Err(format!("database table 0x{base:08X}[{index}] = 0x{pointer:08X} is not ROM data"));
        }
        let from = vec![format!("table.database_text_pointers@0x{base:08X}[{index}]")];
        match consumer {
            Consumer::MenuScript => menu_script(ctx, pointer, from)?,
            Consumer::Scrolling => scrolling_text(ctx, pointer, from)?,
        };
    }
    ctx.set(id, json!({ "consumer": match consumer { Consumer::MenuScript => "RunMenuScript", Consumer::Scrolling => "InitializeScrollingTextWindow" }, "entries": entries }));
    Ok(id)
}

/// RunEquipmentStatHelpMenu: weapons (flags +2 bit 0 clear) index rows 0..5; command equipment indexes (kind - 1) * 2 + row for rows 0..1
/// when its kind byte (+4) is non-zero, and rows 2..5 from the common table. Kinds come from the equipment records the tables port read.
fn stat_help(ctx: &Ctx) -> R<()> {
    pointer_table(ctx, WEAPON_STAT_HELP_SCRIPTS, WEAPON_HELP_ROWS, "c_enum:WEAPON_HELP_*", STAT_HELP, Consumer::MenuScript)?;
    pointer_table(ctx, COMMAND_COMMON_STAT_HELP_SCRIPTS, WEAPON_HELP_ROWS - WEAPON_HELP_RANGE_AND_AREA, "c_enum:WEAPON_HELP_*", STAT_HELP, Consumer::MenuScript)?;
    let mut kinds = std::collections::BTreeSet::new();
    let mut record = EQUIPMENT_RECORDS;
    while ctx.rom.format_name(ctx.rom.owners()[(record + 4 - crate::BASE) as usize]) == "table.equipment" {
        let flags = crate::rom::le16(ctx.rom.peek(record + 2, 2)?, 0);
        let kind = ctx.rom.peek(record + 4, 1)?[0];
        if flags & 1 != 0 && kind != 0 {
            kinds.insert(u32::from(kind));
        }
        record += 0x18;
    }
    let mut effect_id = None;
    for kind in &kinds {
        effect_id = Some(pointer_table_at(ctx, COMMAND_EFFECT_STAT_HELP_SCRIPTS, (kind - 1) * 2, WEAPON_HELP_ACCURACY + 1, "c_index:equipment command effect kinds", STAT_HELP, Consumer::MenuScript)?);
    }
    let (Some(effect_id), Some(&last)) = (effect_id, kinds.iter().next_back()) else { return Err("no command equipment has a command effect kind".into()) };
    for kind in (1..=last).filter(|kind| !kinds.contains(kind)) {
        ctx.unread(
            effect_id,
            COMMAND_EFFECT_STAT_HELP_SCRIPTS + (kind - 1) * (WEAPON_HELP_ACCURACY + 1) * 4,
            (WEAPON_HELP_ACCURACY + 1) * 4,
            &format!("command effect kind {kind} rows 0..1: RunEquipmentStatHelpMenu reads (kind - 1) * 8 + selection * 4 for selection 0..1, kind = byte +4 of an equipment record with flags bit 0 set (src/ui/run_equipment_stat_help_menu.c); no command record (flags bit 0 set) in table.equipment has kind {kind}"),
        )?;
    }
    let (id, _) = ctx.item("table.equipment_stat_help_cursor_y", EQUIPMENT_STAT_HELP_CURSOR_Y, STAT_HELP, ctx.roots.require(EQUIPMENT_STAT_HELP_CURSOR_Y)?);
    ctx.count(id, "c_enum:WEAPON_HELP_*");
    let rows = ctx.rom.claim(EQUIPMENT_STAT_HELP_CURSOR_Y, WEAPON_HELP_ROWS, "table.equipment_stat_help_cursor_y", id)?.to_vec();
    ctx.set(id, json!({ "y": rows }));
    Ok(())
}

/// RunPlayerEquipmentMenu result 4: PrintWindowTextAt(messages[record.zoid_compatibility_group]) for the selected equipment.
fn compatibility_messages(ctx: &Ctx) -> R<()> {
    let (id, _) = ctx.item("table.equipment_compatibility_messages", COMPATIBILITY_MESSAGES, EQUIPMENT_MENU, ctx.roots.require(COMPATIBILITY_MESSAGES)?);
    ctx.count(id, "c_index:zoid_compatibility_group values in equipment records");
    let mut groups = std::collections::BTreeSet::new();
    let mut record = EQUIPMENT_RECORDS;
    while ctx.rom.format_name(ctx.rom.owners()[(record + 0x15 - crate::BASE) as usize]) == "table.equipment" {
        groups.insert(u32::from(ctx.rom.peek(record + 0x15, 1)?[0]));
        record += 0x18;
    }
    let mut entries = Vec::new();
    for group in &groups {
        let pointer = le32(ctx.rom.claim(COMPATIBILITY_MESSAGES + group * 4, 4, "table.equipment_compatibility_messages", id)?, 0);
        if !ctx.rom.is_data(pointer) {
            return Err(format!("compatibility message {group} = 0x{pointer:08X} is not ROM data"));
        }
        super::text::window_text(ctx, pointer, vec![format!("table.equipment_compatibility_messages@0x{COMPATIBILITY_MESSAGES:08X}[{group}]")])?;
        entries.push(json!({ "group": group, "text": format!("0x{pointer:08X}") }));
    }
    ctx.set(id, json!({ "entries": entries }));
    Ok(())
}

fn run(ctx: &Ctx) -> R<()> {
    stat_help(ctx)?;
    compatibility_messages(ctx)?;
    pointer_table(ctx, 0x087F_26C8, ZOID_IDS, "c_loop_bound:zoid ids", ZOID_DATABASE, Consumer::MenuScript)?;
    pointer_table(ctx, 0x087A_3660, ZOID_IDS, "c_loop_bound:zoid ids", ZOID_DATABASE, Consumer::Scrolling)?;
    pointer_table(ctx, 0x087F_2928, BATTLE_PILOT_QUOTE_PILOT_COUNT, "c_constant:BATTLE_PILOT_QUOTE_PILOT_COUNT", CHARACTER_DATABASE, Consumer::MenuScript)?;
    pointer_table(ctx, 0x087A_38C0, BATTLE_PILOT_QUOTE_PILOT_COUNT, "c_constant:BATTLE_PILOT_QUOTE_PILOT_COUNT", CHARACTER_DATABASE, Consumer::Scrolling)?;
    pointer_table(ctx, 0x087F_2ACC, PLAYER_EQUIPMENT_COUNT, "c_constant:PLAYER_EQUIPMENT_COUNT", EQUIPMENT_DATABASE, Consumer::MenuScript)
}
