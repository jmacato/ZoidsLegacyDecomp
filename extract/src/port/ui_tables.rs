//! UI, menu and engine tables: status menu, equipment stats layouts, team formation, name entry, databases,
//! battle rules, screen transitions, intro text, task entry points and the QueueTilemapCopy call sites.

use std::collections::BTreeSet;

use serde_json::{json, Value};

use super::graphics::lz77_item;
use super::menu_script::menu_script;
use super::text::{self, sjis};
use super::{area, bios, literal, Port};
use crate::basis::Basis;
use crate::image::tiles_4bpp;
use crate::rom::{le16, le32, NEUTRAL, R};
use crate::run::Ctx;
use crate::BASE;

const PLAYER_STATE_H: (&str, &str) = ("src/game/player_state.h", "dadeb1433712e28f47ef2910bb1c20a0d96da19b");
const PLAYER_SELECTION_H: (&str, &str) = ("src/ui/player_selection.h", "d3234c00360dfed9bd342175885b1a1ac08cf028");
const NAME_ENTRY_H: (&str, &str) = ("src/ui/name_entry.h", "92b36d57fc30b1b9de64bc76eb0a1293f0f2f029");
const DECK_COMMANDS_H: (&str, &str) = ("src/battle/deck_commands/deck_commands.h", "a9c37e35a2366d649455b0864194df3f43e84b05");
const SCREEN_EFFECTS_H: (&str, &str) = ("src/graphics/screen_effects.h", "20e02e2b2fa0bfefbd6fd76c1cd45ac8c3e7e8d9");
const STATUS_MENU: (&str, &str) = ("src/ui/run_player_status_menu.c", "0c4f77dcafbd6975504b921df5838d0e50421e05");
const MODEL_STATS: (&str, &str) = ("src/ui/show_zoid_model_stats_and_equipment.c", "0e245d65bc312133e4e717b58efefe70adaaca46");
const DRAW_EQUIPMENT_STATS: (&str, &str) = ("src/ui/draw_equipment_stats.c", "66399faab17ed3f7c7e355fbd03804b745e1987b");
const BATTLE_FORMATION: (&str, &str) = ("src/ui/run_battle_team_formation_menu.c", "1c3e5472e5f757ad988dbcbb1621e969b108d4fe");
const PLAYER_FORMATION: (&str, &str) = ("src/ui/run_player_team_formation_menu.c", "8b0ecde27149642174b1dbed0182584d100f15fa");
const RUN_DATABASE: (&str, &str) = ("src/game/modes/run_database.c", "ff5c76b32ebae51fa848f239090f6b58f61d4f9f");
const EQUIPMENT_DATABASE: (&str, &str) = ("src/ui/run_equipment_database_viewer.c", "32a38808904a12ea224aaf40df87f21918342209");
const ZOID_DATABASE: (&str, &str) = ("src/ui/run_zoid_database_viewer.c", "8bd4d7d998f05ecc32b977fb9156793e9fbcbaa8");
const BATTLE_RULE: (&str, &str) = ("src/battle/does_player_team_meet_battle_rule.c", "b2101fd18674f58b519e9d3b771322060cc299af");
const UPDATE_PILOT_ABILITIES: (&str, &str) = ("src/zoids/update_pilot_abilities.c", "bf3b1f67c38fd5a8785a3430b99c99c6076cf150");

const SINE: Basis = Basis::C(&[("src/engine/sin256.c", "ec7a3b68a7ac57514c28dff9939df455e70b8e26")]);
const LIBC_RANDOM: Basis = Basis::C(&[("src/engine/seed_libc_random.c", "c92de01178039e478028fde84af10e4ff2a75cd2")]);
const INITIALIZE_GAME: Basis = Basis::C(&[("src/engine/initialize_game.c", "fd1dd5aa6e788e25e3664df4f9f0d3c5f4d5921a")]);
const TASKS: Basis = Basis::C(&[
    ("src/engine/start_task_with_argument.c", "0890a3b30b605697f1690e774b21004fb07ea3a5"),
    ("src/engine/tasks.h", "e671e2a1912528eab6e8ae3298f592dcff71ef9d"),
    ("src/engine/run_task_entry.c", "0757078a8a5e800aea8cda86c6fb730f0e854edc"),
    ("src/engine/initialize_tasks.c", "1ea61360fd47e52fe123a00311e09d7fa027082c"),
]);
const INTRO: Basis = Basis::C(&[
    ("src/game/modes/run_intro.c", "0790fa906882026c95d87d3e6ff0ae5f27d59d23"),
    ("src/ui/allocate_window_single_byte_glyph_tile.c", "995f3670348bd5795c2e289827b1d7081d878560"),
]);
const SECRET_CODES: Basis = Basis::C(&[("src/ui/run_title_secret_code_monitor.c", "37029e6a070fa07f2703e163ee5d16ba74c7781e")]);
const NAME_ENTRY: Basis = Basis::C(&[
    NAME_ENTRY_H,
    ("src/ui/set_name_entry_character_category.c", "16bbc54a01e2bfc082d5f6519ce63e43fab7b5c1"),
    ("src/ui/populate_name_entry_character_grid.c", "d686be7cb214da3672da95a5f4b4ad9f4f36ed28"),
    ("src/ui/update_name_entry_from_keys.c", "e3e0826477714cf0bd5ac7def1fd9e890d14dae8"),
    ("src/ui/initialize_name_entry_ui.c", "cb059b8bf830ec961c34cb6a9a9a65f25391a007"),
    ("src/ui/draw_window_text.c", "e61d2cdddb1782410db0393ca1ea434d4defdb93"),
]);
const STATUS_MENU_TABLES: Basis = Basis::C(&[STATUS_MENU, MODEL_STATS]);
const COMPATIBLE_MODELS: Basis = Basis::C(&[
    PLAYER_SELECTION_H,
    ("src/ui/append_player_equipment_selection_rows.c", "64fc545bbb333a6fbcf428763864d24812c7f389"),
    ("src/ui/build_player_equipment_selection.c", "cc021e8b6cccae3f1b0e9b944ff6f30042e8edc9"),
]);
const STAT_LAYOUTS: Basis = Basis::C(&[PLAYER_SELECTION_H, DRAW_EQUIPMENT_STATS]);
const STAT_STRINGS: Basis = Basis::C(&[DRAW_EQUIPMENT_STATS, ("src/engine/append_string.c", "6e8c5d1156f6a69c8c74b04a81c02e85b7fa82e9"), ("src/runtime/copy_string.c", "c4d0513f9c0b8bb1147f511ecf77c72f84936c40")]);
const TEAM_SLOTS: Basis = Basis::C(&[BATTLE_FORMATION, PLAYER_FORMATION]);
const QUEUE_TILEMAP_COPY: Basis = Basis::C(&[
    ("src/graphics/queue_tilemap_copy.c", "e3afccb01472b6685eef716babe98fce7dbed105"),
    ("src/graphics/process_transfer_queue.c", "bd3df7baf01ad4e5d00e43a241686352967859c7"),
]);
const MODEL_GROUPS: Basis = Basis::C(&[
    PLAYER_SELECTION_H,
    ("src/ui/does_player_zoid_match_model_group.c", "f8ca648340ae7564399b654be9e23ccb6c407fa1"),
    ("src/ui/build_filtered_player_zoid_selection.c", "b7467c85c3de2093f5e2c0a79d78988f3cb5a33b"),
    ("src/ui/run_zoid_development_menu.c", "157d74f51dd5bde6957b6ca4a7c72d51a81d229a"),
    ("src/ui/run_zoid_cau_development_menu.c", "24353ff8964cd3c5fe0d1917a8bb4c1c122e490a"),
]);
const DECK_CATALOG: Basis = Basis::C(&[
    DECK_COMMANDS_H,
    ("src/battle/deck_commands/append_deck_command_catalog_rows.c", "0f08dbaa79f51770b8c45c7d253c06fd3688213a"),
    ("src/battle/deck_commands/edit_player_deck_commands.c", "424e3f82ed146947fb57720fc95443b38f2bc87a"),
    ("src/battle/deck_commands/select_battle_deck_command_to_add.c", "c8ff1210e18615ce5eb494a04b946af83c83277d"),
]);
const DECK_TARGET_SCRIPTS: Basis = Basis::C(&[DECK_COMMANDS_H, ("src/battle/deck_commands/prepare_battle_deck_command_data.c", "23e56b8205c4049215f35500f5270b8142fb871e")]);
const ZOID_DATABASE_ROWS: Basis = Basis::C(&[RUN_DATABASE, ZOID_DATABASE]);
const CHARACTER_DATABASE_ROWS: Basis = Basis::C(&[
    RUN_DATABASE,
    ("src/ui/initialize_database_menu.c", "da77f9f06075e5e681f441e55defd4e38eb6e384"),
    ("src/ui/run_character_database_viewer.c", "8f7ec7df2dd4e8bfd257884968975fc898fb8c95"),
]);
const EQUIPMENT_DATABASE_LIST: Basis = Basis::C(&[EQUIPMENT_DATABASE, PLAYER_STATE_H]);
const MODEL_FAMILIES: Basis = Basis::C(&[PLAYER_STATE_H, BATTLE_RULE, ("src/zoids/find_ability_value.c", "2933698faf5e36985c98f7abac3ade1a0f5dcca3"), UPDATE_PILOT_ABILITIES]);
const ABILITY_SCHEDULE_FIELDS: Basis = Basis::C(&[UPDATE_PILOT_ABILITIES]);
const SCALED_WINDOWS: Basis = Basis::C(&[
    SCREEN_EFFECTS_H,
    ("src/graphics/start_screen_transition.c", "ca6d1599520f821688f377e5a37fa9d6a77a4c39"),
    ("src/graphics/configure_scaled_scanline_windows.c", "0b8a04fdda7eba5186df705cff79333b6969e4ba"),
    ("src/graphics/build_scaled_scanline_windows.c", "aab52f287acf232c1b11a228a7ec8a3b15d490df"),
    ("src/graphics/build_screen_transition_frame.c", "d7f8767150b74245a001b7cfb60071b85a960e63"),
    ("src/graphics/update_screen_transition_registers.c", "0d321379127b2a4ca26fc9945f851fcc926b67e5"),
]);
const PILOT_ASSIGNMENT_SCRIPTS: Basis = Basis::C(&[("src/ui/run_player_pilot_assignment_menu.c", "ac3abe877cd0970a7685f0140df393ea44234fbd")]);
const MENU_GRADIENT: Basis = Basis::C(&[("src/graphics/load_menu_gradient_background.c", "c19df4e69264e81eccde270e4dde40037dbe5557")]);
const TEAM_MARKER: Basis = Basis::C(&[PLAYER_SELECTION_H, ("src/ui/create_player_selection_status_sprites.c", "4ae3be13905eb706fe4ce53b8c697976c2bdaa3f")]);
const SCANLINE_EVENT: Basis = Basis::C(&[
    PLAYER_SELECTION_H,
    EQUIPMENT_DATABASE,
    ZOID_DATABASE,
    ("src/graphics/insert_scanline_event.c", "9ec51aa351216e7440bcd3c07105a50cbb37da66"),
    ("src/field/field_display.h", "d0a733782b71499ab362fb6a884412891a62e012"),
]);
const PROFICIENCY_PREFIX: Basis = Basis::C(&[
    PLAYER_STATE_H,
    ("src/zoids/format_pilot_ability_description_text.c", "83cadfc545863387ebd0611a78820a74df218f9a"),
    ("src/runtime/copy_bytes.c", "e10e7e371495f3cc4a7382fdf8a91ee500a88795"),
]);
const PILOT_DISPLAY_NAMES: Basis = Basis::C(&[
    ("src/zoids/get_pilot_display_name.c", "b1e539d3d52ba3346e2d9f15832f42509c57af16"),
    ("src/battle/get_battle_pilot_display_name.c", "852cc1aaddb30c27ce83f3ef7a4eb96ba7ee750d"),
    ("src/battle/show_battle_unit_status_viewer.c", "1dc08dc246d6c31a7f6e06072a2cb02b7686a8d4"),
]);

pub const PORT: Port = Port {
    name: "ui_tables",
    bases: &[
        SINE, LIBC_RANDOM, INITIALIZE_GAME, TASKS, INTRO, SECRET_CODES, NAME_ENTRY, STATUS_MENU_TABLES, COMPATIBLE_MODELS, STAT_LAYOUTS, STAT_STRINGS,
        TEAM_SLOTS, QUEUE_TILEMAP_COPY, MODEL_GROUPS, DECK_CATALOG, DECK_TARGET_SCRIPTS, ZOID_DATABASE_ROWS, CHARACTER_DATABASE_ROWS,
        EQUIPMENT_DATABASE_LIST, MODEL_FAMILIES, ABILITY_SCHEDULE_FIELDS, SCALED_WINDOWS, PILOT_ASSIGNMENT_SCRIPTS, MENU_GRADIENT, TEAM_MARKER,
        SCANLINE_EVENT, PROFICIENCY_PREFIX, PILOT_DISPLAY_NAMES,
    ],
    run,
};

const SINE_TABLE: u32 = 0x080E_D184;
const LIBC_REENT_POINTER: u32 = 0x087F_3128;
const WAITCNT_VALUE: u32 = 0x087A_0A10;
const TASK_ENTRY_POINTS: u32 = 0x087A_0A14;
const INTRO_TEXT: u32 = 0x087A_0F28;
const FIRST_SECRET_CODE: u32 = 0x087A_1194;
const SECOND_SECRET_CODE: u32 = 0x087A_11B6;
const NAME_ENTRY_CHARACTER_TABLES: u32 = 0x087A_11D8;
const STATUS_ZOID_SCRIPTS: u32 = 0x087A_1D80;
const STATUS_ZOID_CURSOR_Y: u32 = 0x087A_1DB8;
const STATUS_EQUIPMENT_CURSOR_Y: u32 = 0x087A_1DC6;
const STATUS_PILOT_SCRIPTS: u32 = 0x087A_1DD0;
const STATUS_PILOT_CURSOR_Y: u32 = 0x087A_1DF0;
const STATUS_AUXILIARY_SCRIPTS: u32 = 0x087A_1DF8;
const STATUS_AUXILIARY_CURSOR_Y: u32 = 0x087A_1E24;
const EQUIPMENT_COMPATIBLE_MODELS: u32 = 0x087A_1E2F;
const EQUIPMENT_STAT_TEXT_LAYOUTS: u32 = 0x087A_1E7F;
const WEAPON_OPTION_TEXT: u32 = 0x087A_1EF0;
const COMMAND_OPTION_TEXT: u32 = 0x087A_1F14;
const TEAM_SLOT_POSITIONS: u32 = 0x087A_1F4C;
const PLAYER_ZOID_MODEL_GROUPS: u32 = 0x087A_1F8C;
const DECK_COMMAND_CATALOG_ORDER: u32 = 0x087A_2820;
const ZOID_DATABASE_GROUPS: u32 = 0x087A_3A64;
const CHARACTER_DATABASE_GROUPS: u32 = 0x087A_3D24;
const EQUIPMENT_DATABASE_IDS: u32 = 0x087A_3E40;
const ZOID_MODEL_FAMILIES: u32 = 0x087A_5810;
const TIGER_MODEL_LIST: u32 = 0x087A_58AC;
const WOLF_MODEL_LIST: u32 = 0x087A_58C6;
const ABILITY_SCHEDULE: u32 = 0x087B_79B0;
const ABILITY_SCHEDULE_KIND_FIELD: u32 = 0x087B_79B2;
const ABILITY_SCHEDULE_VALUE_FIELD: u32 = 0x087B_79B4;
const SCALED_WINDOW_BOUNDS: u32 = 0x087E_D854;
const EQUIPMENT_COMPATIBILITY_NAMES: u32 = 0x087F_2E14;
const DECK_FALSE_NEGO_TARGET_SCRIPT: u32 = 0x0801_9B45;
const DECK_SUPPORT_TARGET_SCRIPT: u32 = 0x0801_9B7C;
const PILOT_ASSIGNMENT_STATS_SCRIPT: u32 = 0x0800_23CC;
const PILOT_ASSIGNMENT_STATS_CLOSE_SCRIPT: u32 = 0x0800_24C5;
const MENU_GRADIENT_TILES: u32 = 0x080F_1548;
const MENU_GRADIENT_PALETTE: u32 = 0x080F_1640;
const TEAM_MARKER_FRAMES: u32 = 0x0810_53C4;
const TEAM_MARKER_ANIMATIONS: u32 = 0x0810_53D0;
const DATABASE_SCANLINE_EVENT: u32 = 0x0810_9334;
const PROFICIENCY_DESCRIPTION_PREFIX: u32 = 0x0810_9404;
const MYSTERY_WARRIOR_NAME: u32 = 0x0810_9414;
const MYSTERY_WOMAN_NAME: u32 = 0x0810_9434;
const BATTLE_MYSTERY_WARRIOR_NAME: u32 = 0x0810_948C;
const BATTLE_MYSTERY_WOMAN_NAME: u32 = 0x0810_94AC;

const EQUIPMENT_RECORDS: u32 = 0x087B_2524;
const ZOID_SHOP_RECORDS: u32 = 0x087B_1E04;
const QUEUE_TILEMAP_COPY_ADDRESS: u32 = 0x0809_5254;

/// enums and literal bounds from the pinned C.
const TASK_CONTEXT_COUNT: u32 = 12;
const INTRO_ROWS: u32 = 20;
const INTRO_ROW_BYTES: u32 = 0x1F;
const SECRET_CODE_LENGTH: u32 = 0x11;
const NAME_ENTRY_CATEGORY_BYTES: u32 = 0x106;
const NAME_ENTRY_CATEGORY_HALFWORDS: u32 = 131;
const NAME_ENTRY_SELECT_CATEGORIES: u32 = 3;
const EQUIPMENT_COMPATIBLE_MODEL_COUNT: u32 = 8;
const EQUIPMENT_SELECTION_LAST_ID: u32 = 0xC7;
const EQUIPMENT_STAT_TEXT_LAYOUT_BYTES: u32 = 28;
const EQUIPMENT_STAT_TEXT_LAYOUT_COUNT: u32 = 4;
/// Layout bytes DrawEquipmentStats reads: (x, y) pairs at these offsets of the 28-byte record.
const EQUIPMENT_STAT_TEXT_LAYOUT_PAIRS: [u32; 9] = [0x0, 0x2, 0x4, 0x6, 0xA, 0xE, 0x12, 0x16, 0x1A];
const WEAPON_OPTION_ENTRIES: u32 = 9;
const COMMAND_OPTION_ENTRIES: u32 = 7;
const PLAYER_TEAM_SLOT_COUNT: u32 = 6;
const PLAYER_ZOID_MODEL_GROUP_FIRST_ID: u8 = 200;
const PLAYER_ZOID_MODEL_GROUP_MODELS_PER_ROW: u32 = 6;
const ZOID_LAST_MODEL: u32 = 151;
const DECK_COMMAND_COUNT: u32 = 52;
const ZOID_DATABASE_ROW_BYTES: u32 = 0xB0;
const ZOID_DATABASE_ENTRY_BYTES: u32 = 0xB;
const ZOID_DATABASE_SUBMENU_ROWS: u32 = 3;
const CHARACTER_DATABASE_CATEGORIES: u32 = 7;
const CHARACTER_DATABASE_ROW_BYTES: u32 = 36;
const CHARACTER_DATABASE_ENTRY_BYTES: u32 = 12;
const PILOT_COUNT: u32 = 105;
const PLAYER_EQUIPMENT_COUNT: u32 = 200;
const MODEL_FAMILY_BYTES: u32 = 0x1A;
const PILOT_ABILITY_COUNT: u32 = 10;
const ABILITY_SCHEDULE_ROW_BYTES: u32 = 60;
const SCANLINE_WINDOW_COUNT: u32 = 160;
const SCALED_WINDOW_TRANSITION_DURATION: u32 = 0x24;
const PROFICIENCY_DESCRIPTION_PREFIX_BYTES: u32 = 15;

fn hex(value: u32) -> String {
    format!("0x{value:08X}")
}

fn table(ctx: &Ctx, kind: &str, address: u32, basis: Basis) -> R<usize> {
    let reached = ctx.roots.require(address)?;
    Ok(ctx.item(kind, address, basis, reached).0)
}

fn next_root(ctx: &Ctx, address: u32) -> R<u32> {
    ctx.roots.by_address().range(address + 1..).next().map(|(next, _)| *next).ok_or_else(|| format!("no root after 0x{address:08X}"))
}

/// Bytes another port read under `format`, read again here without a second claim.
fn owned<'a>(ctx: &Ctx<'a>, address: u32, length: u32, format: &str) -> R<&'a [u8]> {
    {
        let owners = ctx.rom.owners();
        for offset in 0..length {
            let owner = owners[(address + offset - BASE) as usize];
            if ctx.rom.format_name(owner) != format {
                return Err(format!("byte 0x{:08X} is not read as {format} by the port that owns that table", address + offset));
            }
        }
    }
    ctx.rom.peek(address, length)
}

/// Equipment records the tables port read, as (id, record bytes).
fn equipment_records<'a>(ctx: &Ctx<'a>) -> R<Vec<(u32, &'a [u8])>> {
    let mut records = Vec::new();
    let mut id = 0;
    loop {
        let at = EQUIPMENT_RECORDS + id * 0x18;
        let owner = ctx.rom.owners()[(at - BASE) as usize];
        if ctx.rom.format_name(owner) != "table.equipment" {
            break;
        }
        records.push((id, owned(ctx, at, 0x18, "table.equipment")?));
        id += 1;
    }
    if records.is_empty() {
        return Err("no table.equipment records were read before this port".into());
    }
    Ok(records)
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

/// Sin256: index `angle & 0x3F`, or `0x40 - (angle & 0x3F)`, so entries 0..0x40.
fn sine(ctx: &Ctx) -> R<()> {
    const KIND: &str = "table.sine";
    let id = table(ctx, KIND, SINE_TABLE, SINE)?;
    let data = ctx.rom.claim(SINE_TABLE, 0x41 * 2, KIND, id)?;
    let values: Vec<u16> = (0..0x41).map(|index| le16(data, index * 2)).collect();
    ctx.count(id, "c_index:sin256.c table_index is angle & 0x3F or 0x40 - (angle & 0x3F) (0..0x40)");
    ctx.set(id, json!({ "entry_bytes": 2, "values": values }));
    Ok(())
}

/// SeedLibcRandom loads the pointer and stores random_seed at +0x58 through it; matched code never reads the target.
fn libc_reent(ctx: &Ctx) -> R<()> {
    const KIND: &str = "table.libc_reent_pointer";
    let id = table(ctx, KIND, LIBC_REENT_POINTER, LIBC_RANDOM)?;
    let pointer = le32(ctx.rom.claim(LIBC_REENT_POINTER, 4, KIND, id)?, 0);
    ctx.count(id, "c_constant:LIBC_REENT_POINTER_ROM (one pointer)");
    ctx.set(id, json!({ "pointer": hex(pointer), "area": area(pointer), "written": hex(pointer.wrapping_add(0x58)), "target_read": false }));
    Ok(())
}

fn waitcnt(ctx: &Ctx) -> R<()> {
    const KIND: &str = "table.waitcnt_value";
    let id = table(ctx, KIND, WAITCNT_VALUE, INITIALIZE_GAME)?;
    let value = le16(ctx.rom.claim(WAITCNT_VALUE, 2, KIND, id)?, 0);
    ctx.count(id, "c_constant:one u16 copied to 0x04000204 by InitializeGame");
    ctx.set(id, json!({ "value": value, "destination": "0x04000204" }));
    Ok(())
}

/// The address of `RunTaskSlot{slot}` from its asm("func_...") declaration in run_task_entry.c.
fn task_slot_function(source: &str, slot: u32) -> R<u32> {
    let declaration = format!("void RunTaskSlot{slot}(void) asm(\"func_");
    let at = source.find(&declaration).ok_or_else(|| format!("run_task_entry.c declares no RunTaskSlot{slot}"))?;
    let hex = &source[at + declaration.len()..at + declaration.len() + 8];
    u32::from_str_radix(hex, 16).map_err(|error| format!("RunTaskSlot{slot}: {error}"))
}

/// StartTaskWithArgument stores entry_points[slot] as the resume pc of gTaskContexts[slot] (TASK_CONTEXT_COUNT contexts).
fn task_entry_points(ctx: &Ctx) -> R<()> {
    const KIND: &str = "table.task_entry_points";
    let id = table(ctx, KIND, TASK_ENTRY_POINTS, TASKS)?;
    let source = std::fs::read_to_string(crate::repo_root().join("src/engine/run_task_entry.c")).map_err(|error| error.to_string())?;
    let data = ctx.rom.claim(TASK_ENTRY_POINTS, TASK_CONTEXT_COUNT * 4, KIND, id)?;
    let mut entries = Vec::new();
    for slot in 0..TASK_CONTEXT_COUNT {
        let pointer = le32(data, slot as usize * 4);
        let mut entry = json!({ "slot": slot, "pointer": hex(pointer) });
        if slot != 0 {
            let function = task_slot_function(&source, slot)?;
            if pointer != function | 1 {
                return Err(format!("task entry {slot} is 0x{pointer:08X}, not RunTaskSlot{slot} (0x{function:08X}) in Thumb mode"));
            }
            entry["function"] = json!(format!("RunTaskSlot{slot}"));
        }
        entries.push(entry);
    }
    ctx.count(id, "c_enum:TASK_CONTEXT_COUNT (entry_points[slot] is stored into gTaskContexts[slot])");
    ctx.set(id, json!({ "entry_bytes": 4, "entries": entries }));
    Ok(())
}

/// RunIntro: 20 rows of 0x1F bytes. Byte 0 of each row is read; when it is not 0, bytes are glyph codes until a 0.
fn intro(ctx: &Ctx) -> R<()> {
    const KIND: &str = "table.intro_text";
    let id = table(ctx, KIND, INTRO_TEXT, INTRO)?;
    let mut rows = Vec::new();
    for row in 0..INTRO_ROWS {
        let start = INTRO_TEXT + row * INTRO_ROW_BYTES;
        let mut cursor = ctx.rom.cursor(start, text::FORMAT, id);
        let mut bytes = Vec::new();
        loop {
            match cursor.u8()? {
                0 => break,
                byte => bytes.push(byte),
            }
        }
        if cursor.address < start + INTRO_ROW_BYTES {
            ctx.unread(
                id,
                cursor.address,
                start + INTRO_ROW_BYTES - cursor.address,
                &format!("intro row {row} after its 0 terminator: RunIntro reads byte 0 of each 0x1F-byte row and, when it is not 0, bytes up to the first 0 (src/game/modes/run_intro.c)"),
            )?;
        }
        rows.push(json!({ "row": row, "text": glyphs(&bytes) }));
    }
    ctx.count(id, "c_loop_bound:run_intro.c rows 0..0x13; terminator:0 in each row");
    ctx.set(id, json!({ "row_bytes": INTRO_ROW_BYTES, "glyphs": "AllocateWindowSingleByteGlyphTile, one byte per glyph", "rows": rows }));
    Ok(())
}

/// RunTitleSecretCodeMonitor compares pressed keys with code[position] and resets after position 0x11.
fn secret_codes(ctx: &Ctx) -> R<()> {
    const KIND: &str = "table.title_secret_code";
    for address in [FIRST_SECRET_CODE, SECOND_SECRET_CODE] {
        let id = table(ctx, KIND, address, SECRET_CODES)?;
        let data = ctx.rom.claim(address, SECRET_CODE_LENGTH * 2, KIND, id)?;
        let keys: Vec<String> = (0..SECRET_CODE_LENGTH as usize).map(|index| format!("0x{:04X}", le16(data, index * 2))).collect();
        ctx.count(id, "c_loop_bound:run_title_secret_code_monitor.c position resets when it reaches 0x11");
        ctx.set(id, json!({ "entry_bytes": 2, "key_masks": keys }));
    }
    Ok(())
}

/// Display of a name entry character: the u16 is printed as two bytes followed by a 0 terminator.
fn name_entry_glyph(bytes: [u8; 2]) -> String {
    if (0x80..=0x9F).contains(&bytes[0]) {
        return sjis(u16::from_be_bytes(bytes));
    }
    let shown: Vec<u8> = bytes.iter().copied().take_while(|&byte| byte != 0).collect();
    glyphs(&shown)
}

/// Category records of NAME_ENTRY_CATEGORY_BYTES: a u16 count, then characters 1..count.
/// Categories are 0 (InitializeNameEntryUi) and SELECT steps through ModuloSigned32(category + 1, 3).
fn name_entry(ctx: &Ctx) -> R<()> {
    const KIND: &str = "table.name_entry_characters";
    let id = table(ctx, KIND, NAME_ENTRY_CHARACTER_TABLES, NAME_ENTRY)?;
    let mut categories = Vec::new();
    for category in 0..NAME_ENTRY_SELECT_CATEGORIES {
        let base = NAME_ENTRY_CHARACTER_TABLES + category * NAME_ENTRY_CATEGORY_BYTES;
        let count = u32::from(le16(ctx.rom.claim(base, 2, KIND, id)?, 0));
        if count > NAME_ENTRY_CATEGORY_HALFWORDS - 1 {
            return Err(format!("name entry category {category} has {count} characters, more than its {} slots", NAME_ENTRY_CATEGORY_HALFWORDS - 1));
        }
        let mut characters = Vec::new();
        for index in 0..count {
            let data = ctx.rom.claim(base + 2 + index * 2, 2, text::FORMAT, id)?;
            characters.push(name_entry_glyph([data[0], data[1]]));
        }
        if count < NAME_ENTRY_CATEGORY_HALFWORDS - 1 {
            ctx.unread(
                id,
                base + 2 + count * 2,
                NAME_ENTRY_CATEGORY_BYTES - 2 - count * 2,
                &format!(
                    "name entry category {category} characters {}..130 (past its count {count}): PopulateNameEntryCharacterGrid reads characters only while remaining_characters != 0 (src/ui/populate_name_entry_character_grid.c) and UpdateNameEntryFromKeys only when grid_character_index < count (src/ui/update_name_entry_from_keys.c)",
                    count + 1
                ),
            )?;
        }
        categories.push(json!({ "category": category, "count": count, "characters": characters }));
    }
    ctx.count(id, "c_constant:ModuloSigned32(category + 1, 3) (categories 0..2) x the count halfword of each category");
    ctx.set(id, json!({ "category_bytes": NAME_ENTRY_CATEGORY_BYTES, "categories": categories }));
    Ok(())
}

fn script_pointers(ctx: &Ctx, address: u32, count: u32, source: &str) -> R<()> {
    const KIND: &str = "table.menu_script_pointers";
    let id = table(ctx, KIND, address, STATUS_MENU_TABLES)?;
    let mut entries = Vec::new();
    for index in 0..count {
        let pointer = le32(ctx.rom.claim(address + index * 4, 4, KIND, id)?, 0);
        if !ctx.rom.is_data(pointer) {
            return Err(format!("menu script pointer 0x{address:08X}[{index}] = 0x{pointer:08X} is not ROM data"));
        }
        menu_script(ctx, pointer, vec![format!("{KIND}@0x{address:08X}[{index}]")])?;
        entries.push(hex(pointer));
    }
    ctx.count(id, source);
    ctx.set(id, json!({ "entry_bytes": 4, "consumer": "RunMenuScript", "entries": entries }));
    Ok(())
}

fn cursor_rows(ctx: &Ctx, address: u32, count: u32, source: &str) -> R<()> {
    const KIND: &str = "table.menu_cursor_y";
    let id = table(ctx, KIND, address, STATUS_MENU_TABLES)?;
    let rows = ctx.rom.claim(address, count, KIND, id)?.to_vec();
    ctx.count(id, source);
    ctx.set(id, json!({ "entry_bytes": 1, "y": rows }));
    Ok(())
}

/// RunPlayerStatusMenu and ShowZoidModelStatsAndEquipment: a cursor index that moves down while below a literal bound
/// selects a menu script and the cursor sprite's y.
fn status_menu(ctx: &Ctx) -> R<()> {
    let stats = "c_loop_bound:cursor moves down while <= 0xC (0..13); run_player_status_menu.c and show_zoid_model_stats_and_equipment.c";
    script_pointers(ctx, STATUS_ZOID_SCRIPTS, 14, stats)?;
    cursor_rows(ctx, STATUS_ZOID_CURSOR_Y, 14, stats)?;
    cursor_rows(ctx, STATUS_EQUIPMENT_CURSOR_Y, 8, "c_loop_bound:cursor moves down while <= 6 (0..7); run_player_status_menu.c and show_zoid_model_stats_and_equipment.c")?;
    let pilot = "c_loop_bound:run_player_status_menu.c state 0x2030 cursor moves down while <= 6 (0..7)";
    script_pointers(ctx, STATUS_PILOT_SCRIPTS, 8, pilot)?;
    cursor_rows(ctx, STATUS_PILOT_CURSOR_Y, 8, pilot)?;
    let auxiliary = "c_loop_bound:run_player_status_menu.c state 0x2070 cursor moves down while <= 9 (or <= 4), so 0..10";
    script_pointers(ctx, STATUS_AUXILIARY_SCRIPTS, 11, auxiliary)?;
    cursor_rows(ctx, STATUS_AUXILIARY_CURSOR_Y, 11, auxiliary)
}

/// AppendPlayerEquipmentSelectionRows, for an equipment record with a non-zero zoid_compatibility_group (+0x15):
/// row = table + group * 8; reads row[0], then row[1..] until a 0 or the selected model, at most index 7, then row[index] again.
/// Over all selected models that is row[0..=first 0], or row[0..=8] when the first eight are all non-zero.
fn compatible_models(ctx: &Ctx) -> R<()> {
    const KIND: &str = "table.equipment_compatible_models";
    let id = table(ctx, KIND, EQUIPMENT_COMPATIBLE_MODELS, COMPATIBLE_MODELS)?;
    let records = equipment_records(ctx)?;
    let mut groups = BTreeSet::new();
    for &(equipment, record) in &records {
        if (1..=EQUIPMENT_SELECTION_LAST_ID).contains(&equipment) && record[0x15] != 0 {
            groups.insert(u32::from(record[0x15]));
        }
    }
    if (records.len() as u32) <= EQUIPMENT_SELECTION_LAST_ID {
        return Err(format!("table.equipment has {} records; BuildPlayerEquipmentSelection reaches id 0xC7", records.len()));
    }
    let mut rows = Vec::new();
    let mut read = BTreeSet::new();
    for &group in &groups {
        let row = EQUIPMENT_COMPATIBLE_MODELS + group * EQUIPMENT_COMPATIBLE_MODEL_COUNT;
        let mut models = Vec::new();
        let mut index = 0;
        loop {
            let model = ctx.rom.claim(row + index, 1, KIND, id)?[0];
            read.insert(row + index);
            if model == 0 {
                break;
            }
            if index == EQUIPMENT_COMPATIBLE_MODEL_COUNT {
                models.push(json!({ "index": index, "model": model, "read_past_row": true }));
                break;
            }
            models.push(json!({ "index": index, "model": model }));
            index += 1;
        }
        rows.push(json!({ "group": group, "models": models }));
    }
    let last_group = *groups.iter().next_back().ok_or("no equipment 1..0xC7 has a zoid_compatibility_group")?;
    for group in 0..=last_group {
        let row = EQUIPMENT_COMPATIBLE_MODELS + group * EQUIPMENT_COMPATIBLE_MODEL_COUNT;
        let reason = if groups.contains(&group) {
            format!("row of zoid_compatibility_group {group} after its first 0 model: AppendPlayerEquipmentSelectionRows stops at a 0 model (src/ui/append_player_equipment_selection_rows.c)")
        } else {
            format!("row {group}: AppendPlayerEquipmentSelectionRows indexes rows only by a non-zero zoid_compatibility_group (+0x15) of the selected equipment (src/ui/append_player_equipment_selection_rows.c), whose ids are 1..0xC7 (src/ui/build_player_equipment_selection.c); no table.equipment record 1..0xC7 has group {group}")
        };
        let mut offset = 0;
        while offset < EQUIPMENT_COMPATIBLE_MODEL_COUNT {
            if read.contains(&(row + offset)) {
                offset += 1;
                continue;
            }
            let start = offset;
            while offset < EQUIPMENT_COMPATIBLE_MODEL_COUNT && !read.contains(&(row + offset)) {
                offset += 1;
            }
            ctx.unread(id, row + start, offset - start, &reason)?;
        }
    }
    ctx.count(id, "c_index:zoid_compatibility_group of equipment 1..0xC7 (build_player_equipment_selection.c); terminator:model 0, at most EQUIPMENT_COMPATIBLE_MODEL_COUNT");
    ctx.set(id, json!({ "row_bytes": EQUIPMENT_COMPATIBLE_MODEL_COUNT, "rows": rows }));
    Ok(())
}

/// DrawEquipmentStats(record, window, layout): layout 0..3 selects a 28-byte record; the (x, y) bytes at the listed
/// offsets are read on its paths. Bytes 8..9, 0xC..0xD, 0x10..0x11, 0x14..0x15 and 0x18..0x19 are never read.
fn stat_layouts(ctx: &Ctx) -> R<()> {
    const KIND: &str = "table.equipment_stat_text_layouts";
    let id = table(ctx, KIND, EQUIPMENT_STAT_TEXT_LAYOUTS, STAT_LAYOUTS)?;
    let mut layouts = Vec::new();
    for layout in 0..EQUIPMENT_STAT_TEXT_LAYOUT_COUNT {
        let base = EQUIPMENT_STAT_TEXT_LAYOUTS + layout * EQUIPMENT_STAT_TEXT_LAYOUT_BYTES;
        let mut positions = serde_json::Map::new();
        for offset in EQUIPMENT_STAT_TEXT_LAYOUT_PAIRS {
            let pair = ctx.rom.claim(base + offset, 2, KIND, id)?;
            positions.insert(format!("+{offset:02X}"), json!([pair[0], pair[1]]));
        }
        let read = |offset: u32| EQUIPMENT_STAT_TEXT_LAYOUT_PAIRS.iter().any(|&pair| pair <= offset && offset < pair + 2);
        let pairs: Vec<String> = EQUIPMENT_STAT_TEXT_LAYOUT_PAIRS.iter().map(|pair| format!("+0x{pair:02X}")).collect();
        let mut offset = 0;
        while offset < EQUIPMENT_STAT_TEXT_LAYOUT_BYTES {
            if read(offset) {
                offset += 1;
                continue;
            }
            let start = offset;
            while offset < EQUIPMENT_STAT_TEXT_LAYOUT_BYTES && !read(offset) {
                offset += 1;
            }
            ctx.unread(
                id,
                base + start,
                offset - start,
                &format!(
                    "struct EquipmentStatTextLayout +0x{start:02X}..+0x{:02X} (src/ui/player_selection.h): DrawEquipmentStats reads only the (x, y) byte pairs at {} of the 28-byte layout (src/ui/draw_equipment_stats.c)",
                    offset - 1,
                    pairs.join(", ")
                ),
            )?;
        }
        layouts.push(json!({ "layout": layout, "positions": positions }));
    }
    ctx.count(id, "c_enum:EQUIPMENT_STAT_TEXT_LAYOUT_COUNT (switch cases 0..3; callers pass 0..3)");
    ctx.set(id, json!({ "record_bytes": EQUIPMENT_STAT_TEXT_LAYOUT_BYTES, "layouts": layouts, "unread": "+08..+09, +0C..+0D, +10..+11, +14..+15, +18..+19" }));
    Ok(())
}

fn string_pointers(ctx: &Ctx, kind: &str, address: u32, indices: &[u32], source: &str) -> R<usize> {
    let id = table(ctx, kind, address, STAT_STRINGS)?;
    let mut entries = Vec::new();
    for &index in indices {
        let pointer = le32(ctx.rom.claim(address + index * 4, 4, kind, id)?, 0);
        if !ctx.rom.is_data(pointer) {
            return Err(format!("{kind} 0x{address:08X}[{index}] = 0x{pointer:08X} is not ROM data"));
        }
        let text_id = text::string(ctx, pointer, vec![format!("{kind}@0x{address:08X}[{index}]")])?;
        entries.push(json!({ "index": index, "pointer": hex(pointer), "text": ctx.name(text_id) }));
    }
    ctx.count(id, source);
    ctx.set(id, json!({ "entry_bytes": 4, "consumer": "AppendString/CopyString", "entries": entries }));
    Ok(id)
}

/// DrawEquipmentStats: weapon option strings at literal offsets 0..0x20 of 0x087A1EF0, command option strings at 0..0x18
/// of 0x087A1F14 (each read when its attribute bit is set), and CopyString(0x087F2E14[group]) for a weapon
/// (flags bit 0 clear) whose zoid_compatibility_group is not 0.
fn stat_strings(ctx: &Ctx) -> R<()> {
    let weapon: Vec<u32> = (0..WEAPON_OPTION_ENTRIES).collect();
    string_pointers(ctx, "table.weapon_option_text", WEAPON_OPTION_TEXT, &weapon, "c_index:draw_equipment_stats.c literal offsets 0x0..0x20")?;
    let command: Vec<u32> = (0..COMMAND_OPTION_ENTRIES).collect();
    string_pointers(ctx, "table.command_option_text", COMMAND_OPTION_TEXT, &command, "c_index:draw_equipment_stats.c literal offsets 0x0..0x18")?;
    let mut groups = BTreeSet::new();
    for (_, record) in equipment_records(ctx)? {
        if le16(record, 2) & 1 == 0 && record[0x15] != 0 {
            groups.insert(u32::from(record[0x15]));
        }
    }
    let listed: Vec<u32> = groups.iter().copied().collect();
    let id = string_pointers(
        ctx,
        "table.equipment_compatibility_names",
        EQUIPMENT_COMPATIBILITY_NAMES,
        &listed,
        "c_index:non-zero zoid_compatibility_group (+0x15) of weapon records (flags bit 0 clear) in table.equipment",
    )?;
    let last = *groups.iter().next_back().ok_or("no weapon record has a zoid_compatibility_group")?;
    for group in (0..=last).filter(|group| !groups.contains(group)) {
        let reason = if group == 0 {
            "entry 0: DrawEquipmentStats reads 0x087F2E14[zoid_compatibility_group] only when the group is not 0 (src/ui/draw_equipment_stats.c: both CopyString calls of this table follow a group != 0 test)".to_string()
        } else {
            format!("entry {group}: DrawEquipmentStats indexes by zoid_compatibility_group (+0x15) of a weapon record, flags bit 0 clear (src/ui/draw_equipment_stats.c); no weapon record in table.equipment has group {group}")
        };
        ctx.unread(id, EQUIPMENT_COMPATIBILITY_NAMES + group * 4, 4, &reason)?;
    }
    Ok(())
}

/// Team formation menus: {s16 x, s16 y} per team slot, read for slots 0..5.
fn team_slots(ctx: &Ctx) -> R<()> {
    const KIND: &str = "table.team_slot_positions";
    let id = table(ctx, KIND, TEAM_SLOT_POSITIONS, TEAM_SLOTS)?;
    let data = ctx.rom.claim(TEAM_SLOT_POSITIONS, PLAYER_TEAM_SLOT_COUNT * 4, KIND, id)?;
    let slots: Vec<Value> = (0..PLAYER_TEAM_SLOT_COUNT as usize).map(|slot| json!({ "slot": slot, "x": le16(data, slot * 4) as i16, "y": le16(data, slot * 4 + 2) as i16 })).collect();
    ctx.count(id, "c_loop_bound:run_battle_team_formation_menu.c slot 0..5 (var_r4 <= 5)");
    ctx.set(id, json!({ "entry_bytes": 4, "slots": slots }));
    Ok(())
}

/// QueueTilemapCopy(source, destination, width, rows): ProcessTransferQueue copies `width` halfwords per row with CpuSet,
/// from source + row * width * 2, for rows 0..rows-1 (u8 row counter).
fn tilemap_copies(ctx: &Ctx) -> R<()> {
    for reference in ctx.roots.calls(QUEUE_TILEMAP_COPY_ADDRESS, 0) {
        if !ctx.rom.is_data(reference.address) {
            continue;
        }
        let (Some(width), Some(rows)) = (reference.args.get(2).and_then(|text| literal(text)), reference.args.get(3).and_then(|text| literal(text))) else { continue };
        let (width, rows) = (width & 0xFFFF, rows & 0xFFFF);
        if rows > 0xFF {
            return Err(format!("QueueTilemapCopy at {}: {rows} rows never ends (u8 row counter)", reference.location()));
        }
        let (row_bytes, fill) = bios::cpu_set_length(width);
        if fill {
            return Err(format!("QueueTilemapCopy at {}: width 0x{width:X} sets the CpuSet fill bit", reference.location()));
        }
        let length = row_bytes * rows;
        if length == 0 {
            continue;
        }
        let (id, new) = ctx.item("copy", reference.address, QUEUE_TILEMAP_COPY, vec![reference.location()]);
        let overlaps = super::claim_outside_code(ctx.rom, reference.address, length, NEUTRAL, id)?;
        if new {
            let destination = reference.args.get(1).cloned().unwrap_or_default();
            ctx.count(id, "c_literal_length:width halfwords x rows");
            ctx.set(
                id,
                json!({
                    "via": "queue_tilemap_copy",
                    "destination": destination,
                    "destination_area": super::address_of(&destination, ctx.roots).map(area).unwrap_or("unknown"),
                    "width_halfwords": width,
                    "rows": rows,
                    "length": length,
                    "code_overlaps": overlaps.iter().map(|(start, end)| format!("0x{start:08X}..0x{end:08X}")).collect::<Vec<_>>(),
                }),
            );
        }
    }
    Ok(())
}

/// DoesPlayerZoidMatchModelGroup(record, id) for id >= PLAYER_ZOID_MODEL_GROUP_FIRST_ID: row (id + 0x38) & 0xFF of 6 models;
/// reads row[0], then row[1..] until a 0, at most index 5. The ids come from base_model_or_series_id of the zoid shop
/// records of models 1..151 (run_zoid_development_menu.c, run_zoid_cau_development_menu.c).
fn model_groups(ctx: &Ctx) -> R<()> {
    const KIND: &str = "table.player_zoid_model_groups";
    let id = table(ctx, KIND, PLAYER_ZOID_MODEL_GROUPS, MODEL_GROUPS)?;
    let mut group_ids = BTreeSet::new();
    for model in 1..=ZOID_LAST_MODEL {
        let series = owned(ctx, ZOID_SHOP_RECORDS + model * 12, 1, "table.zoid_shop")?[0];
        if series >= PLAYER_ZOID_MODEL_GROUP_FIRST_ID {
            group_ids.insert(series);
        }
    }
    let mut rows = Vec::new();
    for &group_id in &group_ids {
        let row = u32::from(group_id.wrapping_add(0x38));
        let base = PLAYER_ZOID_MODEL_GROUPS + row * PLAYER_ZOID_MODEL_GROUP_MODELS_PER_ROW;
        let mut models = Vec::new();
        for index in 0..PLAYER_ZOID_MODEL_GROUP_MODELS_PER_ROW {
            let model = ctx.rom.claim(base + index, 1, KIND, id)?[0];
            if model == 0 {
                break;
            }
            models.push(model);
        }
        rows.push(json!({ "group_id": group_id, "row": row, "models": models }));
    }
    ctx.count(id, "c_index:base_model_or_series_id >= 200 of table.zoid_shop models 1..151; terminator:model 0, at most PLAYER_ZOID_MODEL_GROUP_MODELS_PER_ROW");
    ctx.set(id, json!({ "row_bytes": PLAYER_ZOID_MODEL_GROUP_MODELS_PER_ROW, "rows": rows }));
    Ok(())
}

fn deck_catalog(ctx: &Ctx) -> R<()> {
    const KIND: &str = "table.deck_command_catalog_order";
    let id = table(ctx, KIND, DECK_COMMAND_CATALOG_ORDER, DECK_CATALOG)?;
    let order = ctx.rom.claim(DECK_COMMAND_CATALOG_ORDER, DECK_COMMAND_COUNT, KIND, id)?.to_vec();
    if let Some(&bad) = order.iter().find(|&&command| u32::from(command) >= DECK_COMMAND_COUNT) {
        return Err(format!("deck command catalog lists command {bad}, outside DECK_COMMAND_COUNT"));
    }
    ctx.count(id, "c_enum:DECK_COMMAND_COUNT (append_deck_command_catalog_rows.c catalog_index <= DECK_COMMAND_COUNT - 1)");
    ctx.set(id, json!({ "entry_bytes": 1, "command_ids": order }));
    Ok(())
}

fn scripts(ctx: &Ctx) -> R<()> {
    for address in [DECK_FALSE_NEGO_TARGET_SCRIPT, DECK_SUPPORT_TARGET_SCRIPT, PILOT_ASSIGNMENT_STATS_SCRIPT, PILOT_ASSIGNMENT_STATS_CLOSE_SCRIPT] {
        menu_script(ctx, address, ctx.roots.require(address)?)?;
    }
    Ok(())
}

/// A database group entry: count at +0, ids at +1..+count (RunDatabase scans them, the viewers step through 1..count).
fn id_list(ctx: &Ctx, kind: &str, address: u32, id: usize, limit: u32, what: &str) -> R<Value> {
    let count = ctx.rom.claim(address, 1, kind, id)?[0];
    let ids = if count == 0 { Vec::new() } else { ctx.rom.claim(address + 1, u32::from(count), kind, id)?.to_vec() };
    if let Some(&bad) = ids.iter().find(|&&value| u32::from(value) >= limit) {
        return Err(format!("{kind} entry 0x{address:08X} lists {what} {bad}, outside 0..{limit}"));
    }
    Ok(json!({ "address": hex(address), "count": count, "ids": ids }))
}

/// RunDatabase zoid data: entry = table + category * 0xB0 + subcategory * 0xB. Categories 0..2 open a submenu whose
/// selection is the subcategory; other categories use subcategory 0. The submenu item counts come from RunMenuScript
/// list text, which no port counts, so categories 0..2 take every entry of their 0xB0-byte row.
fn zoid_database(ctx: &Ctx) -> R<()> {
    const KIND: &str = "table.zoid_database_groups";
    let id = table(ctx, KIND, ZOID_DATABASE_GROUPS, ZOID_DATABASE_ROWS)?;
    let end = next_root(ctx, ZOID_DATABASE_GROUPS)?;
    if (end - ZOID_DATABASE_GROUPS) % ZOID_DATABASE_ROW_BYTES != 0 {
        return Err(format!("zoid database table 0x{ZOID_DATABASE_GROUPS:08X}..0x{end:08X} is not whole 0xB0-byte rows"));
    }
    let categories = (end - ZOID_DATABASE_GROUPS) / ZOID_DATABASE_ROW_BYTES;
    let mut rows = Vec::new();
    for category in 0..categories {
        let columns = if category < ZOID_DATABASE_SUBMENU_ROWS { ZOID_DATABASE_ROW_BYTES / ZOID_DATABASE_ENTRY_BYTES } else { 1 };
        let row = ZOID_DATABASE_GROUPS + category * ZOID_DATABASE_ROW_BYTES;
        let mut entries = Vec::new();
        for column in 0..columns {
            let address = row + column * ZOID_DATABASE_ENTRY_BYTES;
            let list = id_list(ctx, KIND, address, id, ZOID_LAST_MODEL + 1, "zoid model")?;
            let end = address + 1 + list["count"].as_u64().ok_or("id list without a count")? as u32;
            if end < address + ZOID_DATABASE_ENTRY_BYTES {
                ctx.unread(
                    id,
                    end,
                    address + ZOID_DATABASE_ENTRY_BYTES - end,
                    &format!("zoid database category {category} entry {column} past its count: RunDatabase scans ids 1..count (src/game/modes/run_database.c) and RunZoidDatabaseViewer steps through 1..count after RunDatabase found a seen id among them (src/ui/run_zoid_database_viewer.c)"),
                )?;
            }
            entries.push(list);
        }
        if columns * ZOID_DATABASE_ENTRY_BYTES < ZOID_DATABASE_ROW_BYTES {
            ctx.unread(
                id,
                row + columns * ZOID_DATABASE_ENTRY_BYTES,
                ZOID_DATABASE_ROW_BYTES - columns * ZOID_DATABASE_ENTRY_BYTES,
                &format!("zoid database category {category} entries {columns}..: RunDatabase sets the subcategory (sp18) to 0 and opens no submenu for categories above 2 (src/game/modes/run_database.c)"),
            )?;
        }
        rows.push(json!({ "category": category, "entries": entries }));
    }
    ctx.count(
        id,
        "next_root categories (4 rows of 0xB0); categories 0..2: every 0xB-byte entry of the row (submenu item counts not ported), others: entry 0 (run_database.c sets the subcategory to 0)",
    );
    ctx.set(id, json!({ "row_bytes": ZOID_DATABASE_ROW_BYTES, "entry_bytes": ZOID_DATABASE_ENTRY_BYTES, "rows": rows }));
    Ok(())
}

/// InitializeDatabaseMenu counts characters over categories 0..6, three entries for categories 1 and 2 and one otherwise;
/// RunDatabase passes the same entry (category * 36 + subcategory * 12) to RunCharacterDatabaseViewer.
fn character_database(ctx: &Ctx) -> R<()> {
    const KIND: &str = "table.character_database_groups";
    let id = table(ctx, KIND, CHARACTER_DATABASE_GROUPS, CHARACTER_DATABASE_ROWS)?;
    let mut rows = Vec::new();
    for category in 0..CHARACTER_DATABASE_CATEGORIES {
        let columns = if (1..=2).contains(&category) { 3 } else { 1 };
        let row = CHARACTER_DATABASE_GROUPS + category * CHARACTER_DATABASE_ROW_BYTES;
        let mut entries = Vec::new();
        for column in 0..columns {
            let address = row + column * CHARACTER_DATABASE_ENTRY_BYTES;
            let list = id_list(ctx, KIND, address, id, PILOT_COUNT, "character")?;
            let count = list["count"].as_u64().ok_or("id list without a count")? as u32;
            if count == 0 {
                return Err(format!("character database entry 0x{address:08X} has count 0; RunCharacterDatabaseViewer reads [1] whatever the count, which this port does not read"));
            }
            let end = address + 1 + count;
            if end < address + CHARACTER_DATABASE_ENTRY_BYTES {
                ctx.unread(
                    id,
                    end,
                    address + CHARACTER_DATABASE_ENTRY_BYTES - end,
                    &format!("character database category {category} entry {column} past its count: InitializeDatabaseMenu reads ids 1..count (src/ui/initialize_database_menu.c) and RunCharacterDatabaseViewer [1] and [1..count] (src/ui/run_character_database_viewer.c)"),
                )?;
            }
            entries.push(list);
        }
        if columns * CHARACTER_DATABASE_ENTRY_BYTES < CHARACTER_DATABASE_ROW_BYTES {
            ctx.unread(
                id,
                row + columns * CHARACTER_DATABASE_ENTRY_BYTES,
                CHARACTER_DATABASE_ROW_BYTES - columns * CHARACTER_DATABASE_ENTRY_BYTES,
                &format!("character database category {category} entries {columns}..2: InitializeDatabaseMenu reads entry 0 only for categories other than 1 and 2 (src/ui/initialize_database_menu.c), and RunDatabase keeps the subcategory (sp18) 0 for them (src/game/modes/run_database.c)"),
            )?;
        }
        rows.push(json!({ "category": category, "entries": entries }));
    }
    ctx.count(id, "c_loop_bound:initialize_database_menu.c categories 0..6, entries 0..2 for categories 1..2 and 0 otherwise; ids 1..count");
    let database_ids: BTreeSet<u32> = rows.iter().flat_map(|row| row["entries"].as_array().into_iter().flatten()).flat_map(|list| list["ids"].as_array().into_iter().flatten()).filter_map(|value| value.as_u64()).map(|value| value as u32).collect();
    super::sprites::field_actor_null_definitions(ctx, &database_ids)?;
    ctx.set(id, json!({ "row_bytes": CHARACTER_DATABASE_ROW_BYTES, "entry_bytes": CHARACTER_DATABASE_ENTRY_BYTES, "rows": rows }));
    Ok(())
}

/// RunEquipmentDatabaseViewer steps an index through 1..table[0] and shows equipment table[index].
fn equipment_database(ctx: &Ctx) -> R<()> {
    const KIND: &str = "table.equipment_database_ids";
    let id = table(ctx, KIND, EQUIPMENT_DATABASE_IDS, EQUIPMENT_DATABASE_LIST)?;
    let list = id_list(ctx, KIND, EQUIPMENT_DATABASE_IDS, id, PLAYER_EQUIPMENT_COUNT, "equipment")?;
    ctx.count(id, "c_index:count byte at +0; run_equipment_database_viewer.c index wraps between 1 and table[0]");
    ctx.set(id, list);
    Ok(())
}

/// 26-model rows. DoesPlayerTeamMeetBattleRule scans rows 1 (+0x1A), 6 (+0x9C) and 7 (+0xB6) for a team zoid's model;
/// FindAbilityValue scans row `value` of a zoid proficiency ability (kinds 3..5). Both scan up to all 26 entries.
fn model_families(ctx: &Ctx) -> R<()> {
    const KIND: &str = "table.zoid_model_families";
    let id = table(ctx, KIND, ZOID_MODEL_FAMILIES, MODEL_FAMILIES)?;
    ctx.roots.require(TIGER_MODEL_LIST)?;
    ctx.roots.require(WOLF_MODEL_LIST)?;
    let mut rows = BTreeSet::new();
    for offset in [0x1A, TIGER_MODEL_LIST - ZOID_MODEL_FAMILIES, WOLF_MODEL_LIST - ZOID_MODEL_FAMILIES] {
        if offset % MODEL_FAMILY_BYTES != 0 {
            return Err(format!("battle rule model list at +0x{offset:X} is not a 26-byte row"));
        }
        rows.insert(offset / MODEL_FAMILY_BYTES);
    }
    let rule_rows = rows.clone();
    let mut proficiency_rows = BTreeSet::new();
    for pilot in 0..PILOT_COUNT {
        for entry in 0..PILOT_ABILITY_COUNT {
            let at = ABILITY_SCHEDULE + pilot * ABILITY_SCHEDULE_ROW_BYTES + entry * 6;
            if le16(owned(ctx, at, 2, "table.pilot_ability_schedule")?, 0) == 0 {
                continue;
            }
            let kind = le16(owned(ctx, at + 2, 2, "table.pilot_ability_schedule")?, 0);
            if (3..=5).contains(&kind) {
                let value = le16(owned(ctx, at + 4, 2, "table.pilot_ability_schedule")?, 0) as i16;
                if value < 0 {
                    return Err(format!("ability schedule entry 0x{at:08X} has a negative proficiency row {value}"));
                }
                proficiency_rows.insert(value as u32);
            }
        }
    }
    rows.extend(proficiency_rows.iter().copied());
    let mut listed = Vec::new();
    for &row in &rows {
        let models = ctx.rom.claim(ZOID_MODEL_FAMILIES + row * MODEL_FAMILY_BYTES, MODEL_FAMILY_BYTES, KIND, id)?.to_vec();
        listed.push(json!({ "row": row, "battle_rule": rule_rows.contains(&row), "proficiency": proficiency_rows.contains(&row), "models": models }));
    }
    let last = *rows.iter().next_back().ok_or("no model family row is read")?;
    let values: Vec<String> = proficiency_rows.iter().map(|row| row.to_string()).collect();
    for row in (0..=last).filter(|row| !rows.contains(row)) {
        ctx.unread(
            id,
            ZOID_MODEL_FAMILIES + row * MODEL_FAMILY_BYTES,
            MODEL_FAMILY_BYTES,
            &format!(
                "model family row {row}: DoesPlayerTeamMeetBattleRule reads rows 1, 6 and 7 (+0x1A, +0x9C, +0xB6; src/battle/does_player_team_meet_battle_rule.c) and FindAbilityValue row ability_values[slot] of a kind 3..5 ability (src/zoids/find_ability_value.c), which UpdatePilotAbilities copies from table.pilot_ability_schedule values {{{}}} (src/zoids/update_pilot_abilities.c)",
                values.join(", ")
            ),
        )?;
    }
    ctx.count(id, "c_index:battle rule rows 1, 6, 7 and the values of ability schedule entries with kind 3..5; 26 entries each (scan index <= 0x19)");
    ctx.set(id, json!({ "row_bytes": MODEL_FAMILY_BYTES, "rows": listed }));
    Ok(())
}

fn ability_schedule_fields(ctx: &Ctx) -> R<()> {
    let level = le16(owned(ctx, ABILITY_SCHEDULE, 2, "table.pilot_ability_schedule")?, 0);
    for (address, field) in [(ABILITY_SCHEDULE_KIND_FIELD, "kind (+2)"), (ABILITY_SCHEDULE_VALUE_FIELD, "value (+4)")] {
        if level != 0 {
            return Err(format!("pilot 0 schedule entry 0 has level {level}; its {field} field at 0x{address:08X} would be read"));
        }
        ctx.explain(
            address,
            ABILITY_SCHEDULE_FIELDS,
            &format!(
                "update_pilot_abilities.c uses 0x{address:08X} as the base of the {field} field, indexed by active_pilot_id * 60 + entry * 6; the table is table.pilot_ability_schedule at 0x087B79B0. The byte at the base itself belongs to pilot 0 entry 0, whose level is 0, and UpdatePilotAbilities skips an entry with level 0 before reading its kind or value"
            ),
        )?;
    }
    Ok(())
}

/// Rows of the scaled windows read by BuildScaledScanlineWindows for both scales = progress * progress
/// (BuildScreenTransitionFrame), progress 0..0x24 (StartScreenTransition, UpdateScreenTransitionRegisters).
fn scaled_window_rows() -> BTreeSet<u32> {
    let mut rows = BTreeSet::new();
    for progress in 0..=SCALED_WINDOW_TRANSITION_DURATION {
        let scale = (progress * progress) & 0xFFFF;
        if scale == 0 {
            continue;
        }
        let step = ((0x10000 / scale) as i16 as u16) as u32;
        let mut source_y = 0x5000u32.wrapping_sub(step.wrapping_mul(80));
        for _ in 0..SCANLINE_WINDOW_COUNT {
            source_y = source_y.wrapping_add(step);
            if source_y <= 0x9FFF {
                rows.insert(source_y >> 8);
            }
        }
    }
    rows
}

/// StartScreenTransition kinds 7 and 8: window 0 bounds at the table, window 1 at table + 0xA0 * 4.
/// Each source row is {s16 left, s16 right}.
fn scaled_windows(ctx: &Ctx) -> R<()> {
    const KIND: &str = "table.scaled_window_bounds";
    let id = table(ctx, KIND, SCALED_WINDOW_BOUNDS, SCALED_WINDOWS)?;
    let rows = scaled_window_rows();
    let mut windows = Vec::new();
    for window in 0..2 {
        let base = SCALED_WINDOW_BOUNDS + window * SCANLINE_WINDOW_COUNT * 4;
        let mut bounds = Vec::new();
        for &row in &rows {
            let data = ctx.rom.claim(base + row * 4, 4, KIND, id)?;
            bounds.push(json!({ "row": row, "left": le16(data, 0) as i16, "right": le16(data, 2) as i16 }));
        }
        windows.push(json!({ "window": window, "address": hex(base), "rows": bounds }));
    }
    ctx.count(id, &format!("c_loop_bound:source rows (source_y_fixed8 >> 8, at most 0x9F) reached for progress 0..0x24; {} of SCANLINE_WINDOW_COUNT rows", rows.len()));
    ctx.set(id, json!({ "row_bytes": 4, "windows": windows }));
    Ok(())
}

/// LoadMenuGradientBackground: BiosLz77ToVram(0x080F1548, char block + tile offset), palette 0x080F1640.
fn menu_gradient(ctx: &Ctx) -> R<()> {
    let (tiles_id, tiles) = lz77_item(ctx, MENU_GRADIENT_TILES, true, bios::LZ77_VRAM, "tiles", None, ctx.roots.require(MENU_GRADIENT_TILES)?)?;
    let palette = bios::lz77_dry(ctx.rom, MENU_GRADIENT_PALETTE, false)?;
    let colored = format!("files/lz77/{MENU_GRADIENT_TILES:08X}.color.png");
    if !ctx.has_file(tiles_id, &colored) {
        ctx.file(tiles_id, ".color.png", &tiles_4bpp(&tiles, &palette))?;
        ctx.view(tiles_id, json!({ "t": "tiles", "bpp": 4, "tiles": ["lz77", MENU_GRADIENT_TILES], "palette": ["lz77", MENU_GRADIENT_PALETTE] }));
    }
    Ok(())
}

/// CreatePlayerSelectionStatusSprites: CreateSprite(TEAM_MARKER_FRAMES, TEAM_MARKER_ANIMATIONS, 0, ...).
fn team_marker(ctx: &Ctx) -> R<()> {
    ctx.roots.require(TEAM_MARKER_ANIMATIONS)?;
    let reached = ctx.roots.require(TEAM_MARKER_FRAMES)?.join(" ");
    super::sprites::sprite_set(ctx, TEAM_MARKER_FRAMES, TEAM_MARKER_ANIMATIONS, reached, &[0]).map(|_| ())
}

/// The database viewers copy this 16-byte ScanlineEvent (struct DatabaseScanlineEventWords) and insert it.
/// InsertScanlineEvent overwrites next (+8) and previous (+12).
fn scanline_event(ctx: &Ctx) -> R<()> {
    const KIND: &str = "table.scanline_event";
    let id = table(ctx, KIND, DATABASE_SCANLINE_EVENT, SCANLINE_EVENT)?;
    let data = ctx.rom.claim(DATABASE_SCANLINE_EVENT, 16, KIND, id)?;
    ctx.count(id, "c_constant:sizeof(struct DatabaseScanlineEventWords) (16 bytes)");
    ctx.set(
        id,
        json!({
            "scanline": data[0],
            "flags": data[1],
            "reserved02": le16(data, 2),
            "callback": hex(le32(data, 4)),
            "next": hex(le32(data, 8)),
            "previous": hex(le32(data, 12)),
        }),
    );
    Ok(())
}

/// FormatPilotAbilityDescriptionText: CopyBytes(destination, prefix, PILOT_PROFICIENCY_DESCRIPTION_PREFIX_BYTES).
fn proficiency_prefix(ctx: &Ctx) -> R<()> {
    let (id, _) = ctx.item("copy", PROFICIENCY_DESCRIPTION_PREFIX, PROFICIENCY_PREFIX, ctx.roots.require(PROFICIENCY_DESCRIPTION_PREFIX)?);
    let bytes = ctx.rom.claim(PROFICIENCY_DESCRIPTION_PREFIX, PROFICIENCY_DESCRIPTION_PREFIX_BYTES, NEUTRAL, id)?.to_vec();
    ctx.count(id, "c_constant:PILOT_PROFICIENCY_DESCRIPTION_PREFIX_BYTES");
    ctx.set(id, json!({ "via": "copy_bytes", "destination": "destination_text", "destination_area": "unknown", "length": PROFICIENCY_DESCRIPTION_PREFIX_BYTES, "bytes": bytes }));
    Ok(())
}

/// GetPilotDisplayName results go to PrintWindowText(At) and AppendString; GetBattlePilotDisplayName's to PrintWindowTextAt.
fn pilot_display_names(ctx: &Ctx) -> R<()> {
    for address in [MYSTERY_WARRIOR_NAME, MYSTERY_WOMAN_NAME] {
        let reached = ctx.roots.require(address)?;
        text::window_text(ctx, address, reached.clone())?;
        text::string(ctx, address, reached)?;
    }
    for address in [BATTLE_MYSTERY_WARRIOR_NAME, BATTLE_MYSTERY_WOMAN_NAME] {
        text::window_text(ctx, address, ctx.roots.require(address)?)?;
    }
    Ok(())
}

fn run(ctx: &Ctx) -> R<()> {
    sine(ctx)?;
    libc_reent(ctx)?;
    waitcnt(ctx)?;
    task_entry_points(ctx)?;
    intro(ctx)?;
    secret_codes(ctx)?;
    name_entry(ctx)?;
    status_menu(ctx)?;
    compatible_models(ctx)?;
    stat_layouts(ctx)?;
    stat_strings(ctx)?;
    team_slots(ctx)?;
    tilemap_copies(ctx)?;
    model_groups(ctx)?;
    deck_catalog(ctx)?;
    scripts(ctx)?;
    zoid_database(ctx)?;
    character_database(ctx)?;
    equipment_database(ctx)?;
    model_families(ctx)?;
    ability_schedule_fields(ctx)?;
    scaled_windows(ctx)?;
    menu_gradient(ctx)?;
    team_marker(ctx)?;
    scanline_event(ctx)?;
    proficiency_prefix(ctx)?;
    pilot_display_names(ctx)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn scaled_rows_cover_every_scanline_row() {
        let rows = scaled_window_rows();
        assert_eq!(rows.len() as u32, SCANLINE_WINDOW_COUNT);
        assert_eq!(rows.iter().next_back(), Some(&0x9F));
    }

    #[test]
    fn name_entry_glyphs() {
        assert_eq!(name_entry_glyph([0x82, 0x60]), "Ａ");
        assert_eq!(name_entry_glyph([b'A', 0]), "A");
    }
}
