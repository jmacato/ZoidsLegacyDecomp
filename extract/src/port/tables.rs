//! Fixed-record tables read by the zoid, equipment, pilot, Pulse, encounter, challenge, shop and save code.

use std::collections::BTreeSet;

use serde_json::{json, Value};

use super::names;
use super::Port;
use crate::basis::Basis;
use crate::rom::{le16, le32, R};
use crate::run::Ctx;

const PLAYER_STATE_H: (&str, &str) = ("src/game/player_state.h", "dadeb1433712e28f47ef2910bb1c20a0d96da19b");
const BATTLE_H: (&str, &str) = ("src/battle/battle.h", "a1dc0242af18cee1d3efcb0fee52c780fc7dcc98");
const BATTLE_DISPLAY_H: (&str, &str) = ("src/battle/battle_display.h", "ed9ae1d1b7b71e189ca7f207078675f82ea365b5");
const FIELD_DISPLAY_H: (&str, &str) = ("src/field/field_display.h", "d0a733782b71499ab362fb6a884412891a62e012");
const MODEL_SELECTION: (&str, &str) = ("src/ui/build_unlocked_zoid_model_selection.c", "48e34a0479b522ddb8ead5e11f04fff689ae90e1");
const ENEMY_UNITS: (&str, &str) = ("src/battle/initialize_enemy_battle_units_from_encounter.c", "f8146e6d6b0cab378c86b4172aee104b04648cd9");
const CHALLENGE_UNITS: (&str, &str) = ("src/battle/initialize_challenge_battle_units.c", "ab0501803381ad3720a48fe08c7b517ec1b0313d");
const ADD_PILOT: (&str, &str) = ("src/zoids/add_or_reactivate_player_pilot.c", "5ded91cc81d35ebd840ff4a27390ab37836fd315");
const STATUS_MENU: (&str, &str) = ("src/ui/run_player_status_menu.c", "0c4f77dcafbd6975504b921df5838d0e50421e05");
const OUTCOME: (&str, &str) = ("src/battle/process_battle_outcome_and_rewards.c", "14d76b6aeb8915fa7805b35630693d2080d428f5");
const EQUIPMENT_EFFECTS: (&str, &str) = ("src/battle/apply_battle_equipment_effects.c", "ec8c3dfe03491a349dc278542918417a5b5f60e2");
const TRY_ENCOUNTER: (&str, &str) = ("src/field/try_select_field_random_encounter.c", "0f314b9346001882aaa8a4790ad9588825153066");
const RUN_EQUIPMENT_SHOP: (&str, &str) = ("src/game/modes/run_equipment_shop.c", "ddf098ab99a62be94f4fe0b302f282e8bca19476");

pub const ZOID_BASE: Basis = Basis::C(&[
    PLAYER_STATE_H,
    BATTLE_H,
    MODEL_SELECTION,
    ("src/zoids/load_zoid_base_stats.c", "0a2b87cbe385ff5eb55af76a690cb0274b7f7380"),
]);
pub const ZOID_SHOP: Basis = Basis::C(&[
    PLAYER_STATE_H,
    MODEL_SELECTION,
    ("src/zoids/get_player_zoid_sell_value.c", "5a620e2334be950f4a4fb2591febd241e73c83ba"),
]);
pub const EQUIPMENT: Basis = Basis::C(&[
    BATTLE_H,
    PLAYER_STATE_H,
    ("src/zoids/load_zoid_equipment_stats.c", "d1e2fff70a21ff393294f04f7ec81a3f360c310a"),
    ENEMY_UNITS,
    CHALLENGE_UNITS,
    RUN_EQUIPMENT_SHOP,
]);
pub const PILOTS: Basis = Basis::C(&[
    PLAYER_STATE_H,
    BATTLE_DISPLAY_H,
    ADD_PILOT,
    ENEMY_UNITS,
    CHALLENGE_UNITS,
    ("src/battle/initialize_player_battle_units.c", "1635294cfe67b9b5f3b6a6b889aec373d07c9980"),
]);
pub const AUXILIARY_PILOTS: Basis = Basis::C(&[
    PLAYER_STATE_H,
    ("src/zoids/initialize_player_auxiliary_pilot.c", "632e8d960ffa01e230e1c5ae54476c4d4787c1b1"),
    ENEMY_UNITS,
    CHALLENGE_UNITS,
    EQUIPMENT_EFFECTS,
]);
const AUXILIARY_PILOT_IDS: Basis = Basis::C(&[
    PLAYER_STATE_H,
    ("src/zoids/initialize_player_auxiliary_pilot.c", "632e8d960ffa01e230e1c5ae54476c4d4787c1b1"),
    ("src/events/commands/event_offer_pulse_emotion_growth.c", "64f7f8f426d05dba7060991896ae51c3052d7d33"),
    ("src/events/commands/event_level_up_pulse.c", "625c80d41e52daa45a4c20b3a3fad88d92b336f7"),
]);
const EXPERIENCE: Basis = Basis::C(&[PLAYER_STATE_H, ADD_PILOT, OUTCOME, STATUS_MENU]);
const GROWTH: Basis = Basis::C(&[PLAYER_STATE_H, ADD_PILOT, STATUS_MENU]);
const PULSE_GROWTH: Basis = Basis::C(&[
    PLAYER_STATE_H,
    ("src/events/commands/event_offer_pulse_emotion_growth.c", "64f7f8f426d05dba7060991896ae51c3052d7d33"),
    ("src/events/commands/event_level_up_pulse.c", "625c80d41e52daa45a4c20b3a3fad88d92b336f7"),
    OUTCOME,
]);
pub const ABILITY_SCHEDULE: Basis = Basis::C(&[
    PLAYER_STATE_H,
    BATTLE_DISPLAY_H,
    ("src/zoids/update_pilot_abilities.c", "bf3b1f67c38fd5a8785a3430b99c99c6076cf150"),
]);
const AUXILIARY_EFFECTS: Basis = Basis::C(&[
    PLAYER_STATE_H,
    ("src/zoids/load_auxiliary_pilot_effects.c", "57c7791fbdc1d3585d91b84ab710d2684e43f801"),
    EQUIPMENT_EFFECTS,
]);
const PULSE_SCHEDULE: Basis = Basis::C(&[
    PLAYER_STATE_H,
    ("src/zoids/update_pulse_effects_from_emotion_growth.c", "0ea138ba37f97fc51c2090695f674262974fc9d0"),
]);
const ENCOUNTERS: Basis = Basis::C(&[
    BATTLE_H,
    FIELD_DISPLAY_H,
    TRY_ENCOUNTER,
    ENEMY_UNITS,
    ("src/game/modes/run_battle.c", "133d0dd6c3a4eb5492f36d7d6b72b6d66d951ddb"),
]);
const FIELD_ENCOUNTERS: Basis = Basis::C(&[
    TRY_ENCOUNTER,
    ("src/field/select_field_random_encounter_table.c", "f4e75d18a1843b01da87f2728d1e4f5f2367531f"),
]);
const WORLD_THRESHOLDS: Basis = Basis::C(&[TRY_ENCOUNTER]);
const CHALLENGES: Basis = Basis::C(&[
    PLAYER_STATE_H,
    ("src/game/modes/run_challenge_menu.c", "11ced92b4c8b6955266529d668cfeac81cdd208a"),
    CHALLENGE_UNITS,
    ("src/ui/initialize_challenge_course_menu.c", "45f7407703469f7be8ea6bbacf1d7b3bde18727a"),
    ("src/ui/build_challenge_round_selection_rows.c", "cac32b3106a20f871243b3729ea2b5cf247f7b65"),
]);
const ITEM_SHOP: Basis = Basis::C(&[PLAYER_STATE_H, ("src/game/modes/run_item_shop.c", "cc40340e48e052a5fdd528554c4ab853e929a9d3")]);
const EQUIPMENT_SHOP: Basis = Basis::C(&[PLAYER_STATE_H, RUN_EQUIPMENT_SHOP]);
const SAVE: Basis = Basis::C(&[
    ("src/save/invalidate_save_blocks.c", "417f2b9b02d287506a7fd27c1b792259424856cf"),
    ("src/save/transfer_save_block.c", "b01aa38f8b707ca9ec35755d0236e50e2207cf70"),
    ("src/runtime/compare_strings.c", "b5e0721ee646516a9e3c4da90d85197106da4739"),
    ("src/save/write_sram_with_retries.c", "d73841714099409031976908675cca68bbe8ad0d"),
    ("src/save/copy_sram_bytes.c", "b76a0142a2fb4d8ff4a4fcca73bd3d8f3af8339d"),
]);

pub const PORT: Port = Port {
    name: "tables",
    bases: &[
        ZOID_BASE, ZOID_SHOP, EQUIPMENT, PILOTS, AUXILIARY_PILOTS, AUXILIARY_PILOT_IDS, EXPERIENCE, GROWTH, PULSE_GROWTH, ABILITY_SCHEDULE, AUXILIARY_EFFECTS,
        PULSE_SCHEDULE, ENCOUNTERS, FIELD_ENCOUNTERS, WORLD_THRESHOLDS, CHALLENGES, ITEM_SHOP, EQUIPMENT_SHOP, SAVE, names::ZOID_NAMES,
        names::PILOT_NAMES, names::AUXILIARY_PILOT_NAMES, names::EQUIPMENT_NAMES, names::RECOVERY_ITEM_NAMES, names::RECOVERY_ITEM_DESCRIPTIONS,
        names::ZOID_CORE_NAMES, names::ZOID_CORE_DESCRIPTIONS, names::DECK_COMMAND_NAMES, names::ABILITY_NAMES, names::ABILITY_DESCRIPTIONS,
        names::EFFECT_NAMES, names::EFFECT_DESCRIPTIONS, names::MAP_GROUP_NAMES, names::GROWTH_CLASS_NAMES, names::QUOTES, names::SCROLLING,
        names::PROFICIENCIES,
    ],
    run,
};

const ZOID_BASE_STATS: u32 = 0x087A_FCC4;
const ZOID_SHOP_RECORDS: u32 = 0x087B_1E04;
const EQUIPMENT_RECORDS: u32 = 0x087B_2524;
const PILOT_RECORDS: u32 = 0x087B_70E4;
const AUXILIARY_PILOT_RECORDS: u32 = 0x087B_7774;
/// apply_battle_equipment_effects.c case 21 reads this record and stores auxiliary pilot id 6.
const BATTLE_AUXILIARY_PILOT_RECORD: u32 = 0x087B_77BC;
const EXPERIENCE_THRESHOLDS: u32 = 0x087B_77C8;
/// PULSE_AUXILIARY_PILOT_IDS_ROM: the pilot id of each auxiliary pilot (catalog flag, portrait).
const AUXILIARY_PILOT_PILOT_IDS: u32 = 0x087A_F5F8;
const GROWTH_TABLE: u32 = 0x087B_7958;
const PULSE_STAT_GROWTH: u32 = 0x087B_7988;
const ABILITY_SCHEDULE_TABLE: u32 = 0x087B_79B0;
const AUXILIARY_EFFECT_TABLE: u32 = 0x087B_924C;
const PULSE_EFFECT_SCHEDULE: u32 = 0x087B_9364;
const ENCOUNTER_TABLE: u32 = 0x087B_9454;
const WORLD_ENCOUNTER_THRESHOLDS: u32 = 0x087C_3864;
const FIELD_ENCOUNTER_DEFINITIONS: u32 = 0x087C_3884;
const CHALLENGE_UNLOCK_FLAGS: u32 = 0x087A_3EE4;
const CHALLENGE_DEFINITIONS: u32 = 0x087A_3EF0;
const ITEM_SHOP_ORDER: u32 = 0x087A_1F98;
const ITEM_PRICES: u32 = 0x087A_2188;
const EQUIPMENT_SHOP_ORDER: u32 = 0x087A_21B0;
const EQUIPMENT_PRICES: u32 = 0x087A_2390;
const SAVE_VERSION: u32 = 0x087A_0A48;
const SAVE_SIGNATURE: u32 = 0x087A_0A4C;
const SAVE_BLOCKS: u32 = 0x087A_0A58;

/// build_unlocked_zoid_model_selection.c: `for (index = 1; index <= 151; ...)` over both zoid tables.
const ZOID_LAST_MODEL: u32 = 151;
/// BATTLE_PILOT_QUOTE_PILOT_COUNT (battle_display.h).
pub const PILOT_COUNT: u32 = 105;
const PLAYER_AUXILIARY_PILOT_COUNT: u32 = 6;
const PLAYER_PILOT_ABILITY_COUNT: u32 = 10;
const PULSE_EMOTION_COUNT: u32 = 4;
const PULSE_EMOTION_GROWTH_LIMIT: i16 = 99;
const PLAYER_PILOT_LEVEL_LIMIT: i16 = 99;
const PLAYER_EQUIPMENT_COUNT: u32 = 200;
const PLAYER_RECOVERY_ITEM_COUNT: u32 = 10;
const BATTLE_ENCOUNTERS_PER_GROUP: u32 = 20;
const BATTLE_ACTIVE_UNIT_COUNT: u32 = 6;
/// initialize_challenge_course_menu.c `course_index <= 9`, build_challenge_round_selection_rows.c `round_index <= 4`.
const CHALLENGE_COURSES: u32 = 10;
const CHALLENGE_ROUNDS: u32 = 5;
/// run_player_status_menu.c reads growth rows only when the chosen class is `<= 3`.
const GROWTH_MENU_LAST_ROW: u8 = 3;
const PILOT_ABILITY_ZOID_PROFICIENCY_1: u16 = 3;
const PILOT_ABILITY_ZOID_PROFICIENCY_3: u16 = 5;

const ZOID_STATS: [&str; 10] =
    ["max_hp", "dcp", "max_ep", "ep_regen", "speed", "mobility", "defense", "armor_rate", "sensor_accuracy", "load_capacity"];
const PILOT_GROWTH: [&str; 5] = ["max_hp", "mobility", "sensor_accuracy", "weapon_accuracy", "dcp"];
const PULSE_BONUSES: [&str; 5] =
    ["hp_recovery_percent", "weapon_power_bonus_percent", "sensor_accuracy_bonus_percent", "speed_bonus_percent", "defense_bonus_percent"];

/// IDs read out of decoded records, which index other tables.
#[derive(Default)]
pub struct Reach {
    pub zoids: BTreeSet<u32>,
    pub pilots: BTreeSet<u32>,
    pub equipment: BTreeSet<u32>,
    pub equipment_count: u32,
    pub growth_classes: BTreeSet<u8>,
    pub proficiencies: BTreeSet<u8>,
    pub ability_kinds: BTreeSet<u8>,
    pub effect_kinds: BTreeSet<u8>,
    pub cores: BTreeSet<u8>,
    pub deck_commands: BTreeSet<u8>,
}

fn table(ctx: &Ctx, kind: &str, address: u32, basis: Basis) -> R<usize> {
    let reached = ctx.roots.require(address)?;
    Ok(ctx.item(kind, address, basis, reached).0)
}

fn next_root(ctx: &Ctx, address: u32) -> R<u32> {
    ctx.roots.by_address().range(address + 1..).next().map(|(next, _)| *next).ok_or_else(|| format!("no root after 0x{address:08X}"))
}

fn s16(data: &[u8], offset: usize) -> i16 {
    le16(data, offset) as i16
}

fn hex(value: u32) -> String {
    format!("0x{value:08X}")
}

fn zoid_base_stats(ctx: &Ctx, reach: &mut Reach) -> R<()> {
    const KIND: &str = "table.zoid_base_stats";
    let id = table(ctx, KIND, ZOID_BASE_STATS, ZOID_BASE)?;
    let mut records = Vec::new();
    for model in 0..=ZOID_LAST_MODEL {
        let data = ctx.rom.claim(ZOID_BASE_STATS + model * 0x38, 0x38, KIND, id)?;
        let stats: serde_json::Map<String, Value> = ZOID_STATS.iter().enumerate().map(|(index, name)| (name.to_string(), json!(le16(data, 4 + index * 2)))).collect();
        let mut equipment = Vec::new();
        for slot in 0..8 {
            let item = le16(data, 0x18 + slot * 4 + 2);
            reach.equipment.insert(u32::from(item));
            equipment.push(json!({ "flags": le16(data, 0x18 + slot * 4), "item_id": item }));
        }
        records.push(json!({
            "id": model,
            "movement_flags": data[0],
            "data01": data[1],
            "size_class": data[2],
            "required_pilot_level": data[3],
            "stats": stats,
            "equipment": equipment,
        }));
    }
    ctx.count(id, "c_loop_bound:build_unlocked_zoid_model_selection.c index 1..151; entry 0 is the table base");
    ctx.set(id, json!({ "record_bytes": 0x38, "records": records, "claimed": "whole records" }));
    Ok(())
}

fn zoid_shop(ctx: &Ctx, reach: &mut Reach) -> R<()> {
    const KIND: &str = "table.zoid_shop";
    let id = table(ctx, KIND, ZOID_SHOP_RECORDS, ZOID_SHOP)?;
    let mut records = Vec::new();
    for model in 0..=ZOID_LAST_MODEL {
        let data = ctx.rom.claim(ZOID_SHOP_RECORDS + model * 12, 12, KIND, id)?;
        reach.cores.extend([data[1], data[2]]);
        records.push(json!({
            "id": model,
            "base_model_or_series_id": data[0],
            "required_core_id0": data[1],
            "required_core_id1": data[2],
            "reserved03": data[3],
            "purchase_price": le32(data, 4),
            "sell_value": le32(data, 8),
        }));
    }
    ctx.count(id, "c_loop_bound:build_unlocked_zoid_model_selection.c index 1..151; entry 0 is the table base");
    ctx.set(id, json!({ "record_bytes": 12, "records": records, "claimed": "whole records" }));
    Ok(())
}

/// Bytes 3 and 14..15 (padding03, padding0E) are read by none of the five readers.
fn pilots(ctx: &Ctx) -> R<(Vec<u8>, BTreeSet<u8>, BTreeSet<u8>)> {
    const KIND: &str = "table.pilots";
    let id = table(ctx, KIND, PILOT_RECORDS, PILOTS)?;
    let mut records = Vec::new();
    let mut levels = Vec::new();
    let mut auxiliary = BTreeSet::new();
    let mut classes = BTreeSet::new();
    for pilot in 0..PILOT_COUNT {
        let at = PILOT_RECORDS + pilot * 16;
        let head = ctx.rom.claim(at, 3, KIND, id)?;
        let (level, auxiliary_id, class) = (head[0], head[1], head[2]);
        let bonuses = ctx.rom.claim(at + 4, 10, KIND, id)?;
        for (offset, length, field) in [(3, 1, "padding03"), (0xE, 2, "padding0E")] {
            ctx.unread(id, at + offset, length, &format!("PilotBaseRecordView.{field} (player_state.h): the readers of 0x087B70E4 read only level +0 (add_or_reactivate_player_pilot.c, initialize_enemy_battle_units_from_encounter.c, initialize_player_battle_units.c), auxiliary_pilot_id +1 (add_or_reactivate_player_pilot.c, initialize_enemy_battle_units_from_encounter.c, initialize_challenge_battle_units.c), growth_class +2 (add_or_reactivate_player_pilot.c) and the s16 bonuses at +4..+0xD"))?;
        }
        levels.push(level);
        auxiliary.insert(auxiliary_id);
        classes.insert(class);
        records.push(json!({
            "id": pilot,
            "level": level,
            "auxiliary_pilot_id": auxiliary_id,
            "growth_class": class,
            "max_hp_bonus_percent": s16(bonuses, 0),
            "mobility_bonus_percent": s16(bonuses, 2),
            "sensor_accuracy_bonus_percent": s16(bonuses, 4),
            "weapon_accuracy_bonus_percent": s16(bonuses, 6),
            "dcp_bonus_percent": s16(bonuses, 8),
        }));
    }
    ctx.count(id, "c_enum:BATTLE_PILOT_QUOTE_PILOT_COUNT (battle_display.h; pilot id space, not used by code; equals next_root)");
    ctx.set(id, json!({ "record_bytes": 16, "records": records, "unread": ["padding03", "padding0E"] }));
    Ok((levels, auxiliary, classes))
}

/// Ids 0..5 index PlayerStateView.auxiliary_pilots[PLAYER_AUXILIARY_PILOT_COUNT]; id 6 is the battle-only record.
fn auxiliary_pilots(ctx: &Ctx, used: &BTreeSet<u8>) -> R<u32> {
    const KIND: &str = "table.auxiliary_pilots";
    let id = table(ctx, KIND, AUXILIARY_PILOT_RECORDS, AUXILIARY_PILOTS)?;
    ctx.roots.require(BATTLE_AUXILIARY_PILOT_RECORD)?;
    let battle_only = (BATTLE_AUXILIARY_PILOT_RECORD - AUXILIARY_PILOT_RECORDS) / 12;
    if (BATTLE_AUXILIARY_PILOT_RECORD - AUXILIARY_PILOT_RECORDS) % 12 != 0 || battle_only < PLAYER_AUXILIARY_PILOT_COUNT {
        return Err(format!("0x{BATTLE_AUXILIARY_PILOT_RECORD:08X} is not an auxiliary pilot record after the player ids"));
    }
    let count = battle_only + 1;
    if let Some(&bad) = used.iter().find(|&&value| u32::from(value) >= PLAYER_AUXILIARY_PILOT_COUNT) {
        return Err(format!("a pilot record names auxiliary pilot {bad}, outside PlayerStateView.auxiliary_pilots"));
    }
    let mut records = Vec::new();
    for auxiliary in 0..count {
        let at = AUXILIARY_PILOT_RECORDS + auxiliary * 12;
        let level_bonus = ctx.rom.claim(at, 1, KIND, id)?[0];
        let data = ctx.rom.claim(at + 2, 10, KIND, id)?;
        ctx.unread(id, at + 1, 1, "AuxiliaryPilotBaseRecordView.padding01 (player_state.h): initialize_player_auxiliary_pilot.c, initialize_enemy_battle_units_from_encounter.c, initialize_challenge_battle_units.c and apply_battle_equipment_effects.c case 21 (record 6, 0x087B77BC) read only level_bonus +0 and the s16 bonuses at +2..+0xB")?;
        let mut record = json!({ "id": auxiliary, "level_bonus": level_bonus });
        for (index, name) in PULSE_BONUSES.iter().enumerate() {
            record[*name] = json!(s16(data, index * 2));
        }
        records.push(record);
    }
    ctx.count(id, "c_constant:PLAYER_AUXILIARY_PILOT_COUNT (ids 0..5) + apply_battle_equipment_effects.c record 6 at 0x087B77BC");
    ctx.set(id, json!({ "record_bytes": 12, "records": records, "unread": ["padding01"] }));
    Ok(count)
}

fn auxiliary_pilot_pilot_ids(ctx: &Ctx) -> R<()> {
    const KIND: &str = "table.auxiliary_pilot_pilot_ids";
    let id = table(ctx, KIND, AUXILIARY_PILOT_PILOT_IDS, AUXILIARY_PILOT_IDS)?;
    let data = ctx.rom.claim(AUXILIARY_PILOT_PILOT_IDS, PLAYER_AUXILIARY_PILOT_COUNT * 2, KIND, id)?;
    let ids: Vec<u16> = (0..PLAYER_AUXILIARY_PILOT_COUNT as usize).map(|index| le16(data, index * 2)).collect();
    ctx.count(id, "c_constant:PLAYER_AUXILIARY_PILOT_COUNT (indexed by a player auxiliary pilot record's auxiliary_pilot_id)");
    ctx.set(id, json!({ "entry_bytes": 2, "pilot_ids": ids }));
    Ok(())
}

/// thresholds[level - 1] when a pilot joins; thresholds[level] in the level-up loop, which stops at a 0 entry, and in the status menu.
fn experience_thresholds(ctx: &Ctx, levels: &[u8]) -> R<()> {
    const KIND: &str = "table.pilot_experience_thresholds";
    let id = table(ctx, KIND, EXPERIENCE_THRESHOLDS, EXPERIENCE)?;
    let mut read: BTreeSet<u32> = BTreeSet::new();
    let joining = &levels[1..];
    if levels[0] != 0 {
        return Err("pilot record 0 is not the empty pilot".into());
    }
    for &level in joining {
        if level == 0 {
            return Err("a pilot record other than 0 has level 0; AddOrReactivatePlayerPilot would read thresholds[-1]".into());
        }
        read.insert(u32::from(level) - 1);
    }
    let lowest = u32::from(*joining.iter().min().ok_or("no pilot records")?);
    let mut level = lowest;
    loop {
        let value = le32(ctx.rom.claim(EXPERIENCE_THRESHOLDS + level * 4, 4, KIND, id)?, 0);
        read.insert(level);
        if value == 0 {
            break;
        }
        level += 1;
        if level > 0xFF {
            return Err("pilot level-up loop passes the u8 level range".into());
        }
    }
    let mut values = Vec::new();
    for &index in &read {
        let value = le32(ctx.rom.claim(EXPERIENCE_THRESHOLDS + index * 4, 4, KIND, id)?, 0);
        values.push(json!({ "index": index, "experience": value as i32 }));
    }
    ctx.count(id, &format!("terminator:level-up loop (process_battle_outcome_and_rewards.c) from level {lowest} stops at the 0 entry at index {level}; index level-1 for joining pilots 1..104 (pilot 0 is the empty all-zero record, not followed)"));
    ctx.set(id, json!({ "entry_bytes": 4, "thresholds": values }));
    Ok(())
}

/// Rows are 12 bytes; both readers take five u16 at +0..+9. Bytes +10..+11 are never read.
fn growth(ctx: &Ctx, classes: &BTreeSet<u8>) -> R<()> {
    const KIND: &str = "table.pilot_growth";
    let id = table(ctx, KIND, GROWTH_TABLE, GROWTH)?;
    let rows: BTreeSet<u8> = (0..=GROWTH_MENU_LAST_ROW).chain(classes.iter().copied()).collect();
    let mut records = Vec::new();
    for &row in &rows {
        let data = ctx.rom.claim(GROWTH_TABLE + u32::from(row) * 12, 10, KIND, id)?;
        ctx.unread(id, GROWTH_TABLE + u32::from(row) * 12 + 10, 2, "growth row bytes +0xA..+0xB: add_or_reactivate_player_pilot.c (row = pilot record growth_class) and run_player_status_menu.c (row = D_0200A880 when <= 3) read only the u16 at +0, +2, +4, +6 and +8")?;
        let mut record = json!({ "growth_class": row });
        for (index, name) in PILOT_GROWTH.iter().enumerate() {
            record[*name] = json!(le16(data, index * 2));
        }
        records.push(record);
    }
    ctx.count(id, "c_comparison:run_player_status_menu.c D_0200A880 <= 3, and the growth_class of every pilot record (0..3)");
    ctx.set(id, json!({ "row_bytes": 12, "rows": records, "unread": "bytes +10..+11 of each row" }));
    Ok(())
}

fn pulse_stat_growth(ctx: &Ctx) -> R<()> {
    const KIND: &str = "table.pulse_stat_growth";
    let id = table(ctx, KIND, PULSE_STAT_GROWTH, PULSE_GROWTH)?;
    let mut records = Vec::new();
    for emotion in 0..PULSE_EMOTION_COUNT {
        let data = ctx.rom.claim(PULSE_STAT_GROWTH + emotion * 10, 10, KIND, id)?;
        let mut record = json!({ "emotion": emotion });
        for (index, name) in PULSE_BONUSES.iter().enumerate() {
            record[*name] = json!(s16(data, index * 2));
        }
        records.push(record);
    }
    ctx.count(id, "c_constant:PULSE_EMOTION_COUNT (the row is the emotion chosen by the PULSE_EMOTION_COUNT loop in event_offer_pulse_emotion_growth.c)");
    ctx.set(id, json!({ "record_bytes": 10, "records": records }));
    Ok(())
}

/// UpdatePilotAbilities reads `level` of every entry, `kind` when level != 0, and `value` when it learns the entry (kind != 0).
fn ability_schedule(ctx: &Ctx, reach: &mut Reach) -> R<()> {
    const KIND: &str = "table.pilot_ability_schedule";
    let id = table(ctx, KIND, ABILITY_SCHEDULE_TABLE, ABILITY_SCHEDULE)?;
    let mut rows = Vec::new();
    for pilot in 0..PILOT_COUNT {
        let mut entries = Vec::new();
        for entry in 0..PLAYER_PILOT_ABILITY_COUNT {
            let at = ABILITY_SCHEDULE_TABLE + pilot * 60 + entry * 6;
            let level = s16(ctx.rom.claim(at, 2, KIND, id)?, 0);
            let mut record = json!({ "level": level });
            if !(0..=PLAYER_PILOT_LEVEL_LIMIT).contains(&level) {
                return Err(format!("ability schedule entry at 0x{at:08X} needs level {level}, outside 0..PLAYER_PILOT_LEVEL_LIMIT; whether its value is read is unclear"));
            }
            if level != 0 {
                let kind = le16(ctx.rom.claim(at + 2, 2, KIND, id)?, 0);
                record["kind"] = json!(kind);
                if kind != 0 {
                    let value = le16(ctx.rom.claim(at + 4, 2, KIND, id)?, 0);
                    record["value"] = json!(value);
                    reach.ability_kinds.insert(kind as u8);
                    if (PILOT_ABILITY_ZOID_PROFICIENCY_1..=PILOT_ABILITY_ZOID_PROFICIENCY_3).contains(&kind) {
                        reach.proficiencies.insert(value as u8);
                    }
                } else {
                    ctx.unread(id, at + 4, 2, "PilotAbilityScheduleEntry.value (player_state.h): UpdatePilotAbilities (update_pilot_abilities.c), the only reader of 0x087B79B0, goes to next_schedule_entry when kind == 0 (ldrsh kind at 0x080E70CC, branch at 0x080E70D2) before any load of +4; this entry's kind is 0")?;
                }
            } else {
                ctx.unread(id, at + 2, 4, "PilotAbilityScheduleEntry.kind and .value (player_state.h): UpdatePilotAbilities (update_pilot_abilities.c), the only reader of 0x087B79B0, goes to next_schedule_entry when level == 0 (ldrsh level at 0x080E70B6, branch at 0x080E70C2) before loading kind +2 or value +4; this entry's level is 0")?;
            }
            entries.push(record);
        }
        rows.push(json!({ "pilot": pilot, "entries": entries }));
    }
    ctx.count(id, "c_enum:BATTLE_PILOT_QUOTE_PILOT_COUNT (pilot id space) x PLAYER_PILOT_ABILITY_COUNT entries");
    ctx.set(id, json!({ "row_bytes": 60, "entry_bytes": 6, "rows": rows }));
    Ok(())
}

/// LoadAuxiliaryPilotEffects reads `kind` of all ten slots and `value` unless kind is 0x1A or 0x1B.
fn auxiliary_effects(ctx: &Ctx, count: u32, reach: &mut Reach) -> R<()> {
    const KIND: &str = "table.auxiliary_pilot_effects";
    let id = table(ctx, KIND, AUXILIARY_EFFECT_TABLE, AUXILIARY_EFFECTS)?;
    let mut rows = Vec::new();
    for auxiliary in 0..count {
        let mut slots = Vec::new();
        for slot in 0..PLAYER_PILOT_ABILITY_COUNT {
            let at = AUXILIARY_EFFECT_TABLE + auxiliary * 40 + slot * 4;
            let kind = s16(ctx.rom.claim(at, 2, KIND, id)?, 0);
            let mut record = json!({ "kind": kind });
            match kind {
                0x1A => record["unlocks_deck_command"] = json!(0x26),
                0x1B => record["unlocks_deck_command"] = json!(0x25),
                _ => {
                    reach.effect_kinds.insert(kind as u8);
                    record["value"] = json!(s16(ctx.rom.claim(at + 2, 2, KIND, id)?, 0));
                }
            }
            slots.push(record);
        }
        rows.push(json!({ "auxiliary_pilot_id": auxiliary, "slots": slots }));
    }
    ctx.count(id, "auxiliary pilot ids of table.auxiliary_pilots (0..6) x PLAYER_PILOT_ABILITY_COUNT slots");
    ctx.set(id, json!({ "row_bytes": 40, "rows": rows }));
    Ok(())
}

/// UpdatePulseEffectsFromEmotionGrowth reads `emotion_growth` of every entry, and `kind` and `value` when it is not 0.
fn pulse_effect_schedule(ctx: &Ctx, reach: &mut Reach) -> R<()> {
    const KIND: &str = "table.pulse_effect_schedule";
    let id = table(ctx, KIND, PULSE_EFFECT_SCHEDULE, PULSE_SCHEDULE)?;
    let mut rows = Vec::new();
    for emotion in 0..PULSE_EMOTION_COUNT {
        let mut entries = Vec::new();
        for entry in 0..PLAYER_PILOT_ABILITY_COUNT {
            let at = PULSE_EFFECT_SCHEDULE + emotion * 60 + entry * 6;
            let threshold = s16(ctx.rom.claim(at, 2, KIND, id)?, 0);
            let mut record = json!({ "emotion_growth": threshold });
            if !(0..=PULSE_EMOTION_GROWTH_LIMIT).contains(&threshold) {
                return Err(format!("Pulse schedule entry at 0x{at:08X} needs growth {threshold}, outside 0..PULSE_EMOTION_GROWTH_LIMIT; whether its kind is read is unclear"));
            }
            if threshold != 0 {
                let data = ctx.rom.claim(at + 2, 4, KIND, id)?;
                reach.effect_kinds.insert(data[0]);
                record["kind"] = json!(le16(data, 0));
                record["value"] = json!(s16(data, 2));
            } else {
                ctx.unread(id, at + 2, 4, "PulseEffectScheduleEntry.kind and .value (player_state.h): UpdatePulseEffectsFromEmotionGrowth (update_pulse_effects_from_emotion_growth.c), the only reader of 0x087B9364, skips the entry when emotion_growth == 0 (ldrsh at 0x080E7A2C, beq at 0x080E7A30) before loading kind +2 or value +4; this entry's emotion_growth is 0")?;
            }
            entries.push(record);
        }
        rows.push(json!({ "emotion": emotion, "entries": entries }));
    }
    ctx.count(id, "c_constant:PULSE_EMOTION_COUNT rows x PLAYER_PILOT_ABILITY_COUNT entries (loop bounds)");
    ctx.set(id, json!({ "row_bytes": 60, "entry_bytes": 6, "rows": rows }));
    Ok(())
}

/// SelectFieldRandomEncounterTable scans 6-byte records until map_id 0; TrySelectFieldRandomEncounter then reads
/// the threshold (+2) and group (+4) of the selected record, which is the terminator when no map matches.
fn field_encounter_definitions(ctx: &Ctx) -> R<BTreeSet<u32>> {
    const KIND: &str = "table.field_encounter_definitions";
    let id = table(ctx, KIND, FIELD_ENCOUNTER_DEFINITIONS, FIELD_ENCOUNTERS)?;
    let mut records = Vec::new();
    let mut groups = BTreeSet::new();
    for index in 0..=0xFFu32 {
        let data = ctx.rom.claim(FIELD_ENCOUNTER_DEFINITIONS + index * 6, 6, KIND, id)?;
        let (map, threshold, group) = (le16(data, 0), le16(data, 2), le16(data, 4));
        groups.insert(u32::from(group));
        records.push(json!({ "index": index, "map_id": map, "encounter_threshold": threshold, "encounter_group": group }));
        if map == 0 {
            ctx.count(id, "terminator:map_id 0 (its threshold and group are read too)");
            ctx.set(id, json!({ "record_bytes": 6, "records": records }));
            return Ok(groups);
        }
    }
    Err("field encounter definitions: the u8 index wraps before a map_id 0 record".into())
}

fn world_encounter_thresholds(ctx: &Ctx) -> R<()> {
    const KIND: &str = "table.world_map_encounter_thresholds";
    let id = table(ctx, KIND, WORLD_ENCOUNTER_THRESHOLDS, WORLD_THRESHOLDS)?;
    let end = next_root(ctx, WORLD_ENCOUNTER_THRESHOLDS)?;
    let count = (end - WORLD_ENCOUNTER_THRESHOLDS) / 2;
    let data = ctx.rom.claim(WORLD_ENCOUNTER_THRESHOLDS, count * 2, KIND, id)?;
    let values: Vec<u16> = (0..count as usize).map(|index| le16(data, index * 2)).collect();
    ctx.count(id, "next_root (index is the high byte of a world map encounter tile; the C gives no bound)");
    ctx.set(id, json!({ "entry_bytes": 2, "thresholds": values }));
    Ok(())
}

/// Groups of BATTLE_ENCOUNTERS_PER_GROUP 100-byte BattleEncounterRecords.
fn encounter_formations(ctx: &Ctx, groups_used: &BTreeSet<u32>, reach: &mut Reach) -> R<()> {
    const KIND: &str = "table.encounter_formations";
    let id = table(ctx, KIND, ENCOUNTER_TABLE, ENCOUNTERS)?;
    let record_bytes = 4 + BATTLE_ACTIVE_UNIT_COUNT * 16;
    let group_bytes = BATTLE_ENCOUNTERS_PER_GROUP * record_bytes;
    let end = next_root(ctx, ENCOUNTER_TABLE)?;
    if (end - ENCOUNTER_TABLE) % group_bytes != 0 {
        return Err(format!("encounter table 0x{ENCOUNTER_TABLE:08X}..0x{end:08X} is not a whole number of {group_bytes}-byte groups"));
    }
    let groups = (end - ENCOUNTER_TABLE) / group_bytes;
    if let Some(&bad) = groups_used.iter().find(|&&group| group >= groups) {
        return Err(format!("a field encounter definition names encounter group {bad}, past the {groups} groups before the next root"));
    }
    let mut records = Vec::new();
    for group in 0..groups {
        for encounter in 0..BATTLE_ENCOUNTERS_PER_GROUP {
            let data = ctx.rom.claim(ENCOUNTER_TABLE + group * group_bytes + encounter * record_bytes, record_bytes, KIND, id)?;
            let mut units = Vec::new();
            for unit in 0..BATTLE_ACTIVE_UNIT_COUNT as usize {
                let at = 4 + unit * 16;
                let equipment = &data[at + 4..at + 8];
                reach.zoids.insert(u32::from(data[at]));
                reach.pilots.insert(u32::from(data[at + 2]));
                reach.equipment.extend(equipment.iter().map(|&item| u32::from(item)));
                units.push(json!({
                    "zoid_id": data[at],
                    "palette_variant": data[at + 1],
                    "pilot_id": data[at + 2],
                    "flag40_enabled": data[at + 3],
                    "equipment_item_ids": equipment,
                    "experience_reward": le32(data, at + 8),
                    "money_reward": le32(data, at + 12),
                }));
            }
            records.push(json!({ "group": group, "encounter": encounter, "song_id": data[0], "data01": &data[1..4], "units": units }));
        }
    }
    ctx.count(id, "next_root groups (u8 gBattleSetup[3]; the C gives no bound) x c_constant:BATTLE_ENCOUNTERS_PER_GROUP");
    ctx.set(id, json!({ "record_bytes": record_bytes, "group_bytes": group_bytes, "groups": groups, "records": records, "claimed": "whole records" }));
    Ok(())
}

fn challenges(ctx: &Ctx, reach: &mut Reach) -> R<()> {
    const FLAGS: &str = "table.challenge_course_unlock_flags";
    let flags_id = table(ctx, FLAGS, CHALLENGE_UNLOCK_FLAGS, CHALLENGES)?;
    let flags = ctx.rom.claim(CHALLENGE_UNLOCK_FLAGS, CHALLENGE_COURSES, FLAGS, flags_id)?;
    ctx.count(flags_id, "c_loop_bound:initialize_challenge_course_menu.c course_index <= 9");
    ctx.set(flags_id, json!({ "unlock_flags": flags }));

    const KIND: &str = "table.challenge_battles";
    let id = table(ctx, KIND, CHALLENGE_DEFINITIONS, CHALLENGES)?;
    let mut records = Vec::new();
    for course in 0..CHALLENGE_COURSES {
        for round in 0..CHALLENGE_ROUNDS {
            let data = ctx.rom.claim(CHALLENGE_DEFINITIONS + course * 0x280 + round * 0x80, 0x80, KIND, id)?;
            let mut sides = Vec::new();
            for side in 0..2usize {
                let mut units = Vec::new();
                for unit in 0..6usize {
                    let at = side * 0x30 + unit * 8;
                    reach.zoids.insert(u32::from(data[at]));
                    reach.pilots.insert(u32::from(data[at + 2]));
                    reach.equipment.extend(data[at + 3..at + 7].iter().map(|&item| u32::from(item)));
                    units.push(json!({
                        "model_id": data[at],
                        "palette_variant": data[at + 1],
                        "pilot_id": data[at + 2],
                        "fixed_equipment_ids": &data[at + 3..at + 7],
                        "reserved07": data[at + 7],
                    }));
                }
                sides.push(json!(units));
            }
            let rewards: Vec<Value> = (0..5usize)
                .map(|index| {
                    let kind = data[0x74 + index * 2];
                    let reward = data[0x75 + index * 2];
                    let what = match kind {
                        1 => "deck_command",
                        2 => "zoid_core",
                        3 => "zoid_data",
                        _ => "none",
                    };
                    match kind {
                        1 => {
                            reach.deck_commands.insert(reward);
                        }
                        2 => {
                            reach.cores.insert(reward);
                        }
                        3 => {
                            reach.zoids.insert(u32::from(reward));
                        }
                        _ => {}
                    }
                    json!({ "kind": kind, "reward": what, "id": reward })
                })
                .collect();
            records.push(json!({
                "course": course,
                "round": round,
                "sides": sides,
                "battle_recovery_item_quantities": &data[0x60..0x6A],
                "inventory_recovery_item_quantities": &data[0x6A..0x74],
                "reserved74": &data[0x74..0x80],
                "reserved74_rewards": rewards,
            }));
        }
    }
    ctx.count(id, "c_loop_bound:initialize_challenge_course_menu.c course_index <= 9 x build_challenge_round_selection_rows.c round_index <= 4");
    ctx.set(id, json!({ "record_bytes": 0x80, "course_bytes": 0x280, "records": records, "claimed": "whole records" }));
    Ok(())
}

/// Shop pages: 16 bytes, up to eight u16 ids; the shop reads ids until a 0 or the eighth.
fn shop_pages(ctx: &Ctx, kind: &str, address: u32, basis: Basis, reader: &str) -> R<Vec<Vec<u16>>> {
    let id = table(ctx, kind, address, basis)?;
    let end = next_root(ctx, address)?;
    if (end - address) % 16 != 0 {
        return Err(format!("{kind} 0x{address:08X}..0x{end:08X} is not a whole number of 16-byte pages"));
    }
    let mut pages = Vec::new();
    for page in 0..(end - address) / 16 {
        let mut ids = Vec::new();
        let mut slots_read = 0;
        for slot in 0..8 {
            let value = le16(ctx.rom.claim(address + page * 16 + slot * 2, 2, kind, id)?, 0);
            slots_read = slot + 1;
            if value == 0 {
                break;
            }
            ids.push(value);
        }
        if slots_read < 8 {
            ctx.unread(
                id,
                address + page * 16 + slots_read * 2,
                16 - slots_read * 2,
                &format!("page {page} slots {slots_read}..7, after its 0 slot: {reader} lists u16 slots up to the first 0 (at most 8) and later reads only the low byte of a listed slot, picked by the menu selection"),
            )?;
        }
        pages.push(ids);
    }
    ctx.count(id, "next_root pages (the page is an event command operand; the C gives no bound); ids up to the first 0, at most 8");
    ctx.set(id, json!({ "page_bytes": 16, "pages": pages }));
    Ok(pages)
}

fn prices(ctx: &Ctx, kind: &str, address: u32, count: u32, basis: Basis, source: &str) -> R<()> {
    let id = table(ctx, kind, address, basis)?;
    let data = ctx.rom.claim(address, count * 4, kind, id)?;
    let values: Vec<u32> = (0..count as usize).map(|index| le32(data, index * 4)).collect();
    ctx.count(id, source);
    ctx.set(id, json!({ "entry_bytes": 4, "prices": values }));
    Ok(())
}

fn shops(ctx: &Ctx, reach: &mut Reach) -> R<()> {
    let items = shop_pages(ctx, "table.item_shop_pages", ITEM_SHOP_ORDER, ITEM_SHOP, "RunItemShop state 0x1000 (src/game/modes/run_item_shop.c)")?;
    if let Some(&bad) = items.iter().flatten().find(|&&item| u32::from(item) >= PLAYER_RECOVERY_ITEM_COUNT) {
        return Err(format!("item shop page lists item {bad}, outside PLAYER_RECOVERY_ITEM_COUNT"));
    }
    prices(ctx, "table.item_prices", ITEM_PRICES, PLAYER_RECOVERY_ITEM_COUNT, ITEM_SHOP, "c_constant:PLAYER_RECOVERY_ITEM_COUNT (item ids index recovery_item_quantities)")?;
    let equipment = shop_pages(ctx, "table.equipment_shop_pages", EQUIPMENT_SHOP_ORDER, EQUIPMENT_SHOP, "RunEquipmentShop block_60 (src/game/modes/run_equipment_shop.c)")?;
    if let Some(&bad) = equipment.iter().flatten().find(|&&item| u32::from(item) >= PLAYER_EQUIPMENT_COUNT) {
        return Err(format!("equipment shop page lists equipment {bad}, outside PLAYER_EQUIPMENT_COUNT"));
    }
    reach.equipment.extend(equipment.iter().flatten().map(|&item| u32::from(item)));
    prices(ctx, "table.equipment_prices", EQUIPMENT_PRICES, PLAYER_EQUIPMENT_COUNT, EQUIPMENT_SHOP, "c_constant:PLAYER_EQUIPMENT_COUNT (equipment ids index equipment_quantities)")
}

fn equipment(ctx: &Ctx, reach: &mut Reach) -> R<()> {
    const KIND: &str = "table.equipment";
    let id = table(ctx, KIND, EQUIPMENT_RECORDS, EQUIPMENT)?;
    let highest = *reach.equipment.iter().max().ok_or("no equipment ids reached")?;
    let count = PLAYER_EQUIPMENT_COUNT.max(highest + 1);
    let mut records = Vec::new();
    for item in 0..count {
        let data = ctx.rom.claim(EQUIPMENT_RECORDS + item * 0x18, 0x18, KIND, id)?;
        records.push(json!({
            "id": item,
            "family_id": data[0],
            "family_variant": data[1],
            "flags": le16(data, 2),
            "attributes": le32(data, 4),
            "range_kind": data[8],
            "area_type": data[9],
            "power_or_value": le16(data, 10),
            "accuracy_or_secondary_value": le16(data, 12),
            "accuracy_limit_or_duration": s16(data, 14),
            "ep_cost": s16(data, 16),
            "weight": le16(data, 18),
            "mount_constraints": data[20],
            "zoid_compatibility_group": data[21],
            "data16": le16(data, 22),
        }));
    }
    let unreferenced = (PLAYER_EQUIPMENT_COUNT..count).filter(|item| !reach.equipment.contains(item)).count();
    ctx.count(
        id,
        &format!("reached_ids:max(PLAYER_EQUIPMENT_COUNT, highest item id read from decoded zoid/encounter/challenge/shop records {highest} + 1); {unreferenced} ids in 200..{count} are referenced by no decoded record"),
    );
    ctx.set(id, json!({ "record_bytes": 0x18, "records": records, "claimed": "whole records" }));
    reach.equipment_count = count;
    Ok(())
}

/// InvalidateSaveBlocks and TransferSaveBlock walk {data, size} entries until both are 0.
fn save(ctx: &Ctx) -> R<()> {
    const KIND: &str = "table.save_blocks";
    let id = table(ctx, KIND, SAVE_BLOCKS, SAVE)?;
    let mut blocks = Vec::new();
    for index in 0..=0xFFu32 {
        let data = ctx.rom.claim(SAVE_BLOCKS + index * 8, 8, KIND, id)?;
        let (address, size) = (le32(data, 0), le32(data, 4));
        if address == 0 && size == 0 {
            ctx.count(id, "terminator:{0,0}");
            ctx.set(id, json!({ "entry_bytes": 8, "blocks": blocks }));
            return save_magic(ctx);
        }
        blocks.push(json!({ "data": hex(address), "area": super::area(address), "size": size }));
    }
    Err("save block table: the u8 index wraps before a {0,0} entry".into())
}

/// TransferSaveBlock writes 4 bytes from 0x087A0A48, and writes 11 bytes from 0x087A0A4C or compares them with
/// CompareStrings, whose word loop (both pointers are word aligned) reads whole words up to the one holding the NUL.
fn save_magic(ctx: &Ctx) -> R<()> {
    const KIND: &str = "table.save_magic";
    let (version_id, _) = ctx.item(KIND, SAVE_VERSION, SAVE, ctx.roots.require(SAVE_VERSION)?);
    let version = ctx.rom.claim(SAVE_VERSION, 4, KIND, version_id)?;
    ctx.count(version_id, "c_literal_length:WriteSramWithRetries(0x087A0A48, ..., 4)");
    ctx.set(version_id, json!({ "bytes": version, "value": le32(version, 0) }));

    let (signature_id, _) = ctx.item(KIND, SAVE_SIGNATURE, SAVE, ctx.roots.require(SAVE_SIGNATURE)?);
    let mut words = 0u32;
    loop {
        let word = le32(ctx.rom.peek(SAVE_SIGNATURE + words * 4, 4)?, 0);
        words += 1;
        if word.wrapping_add(0xFEFE_FEFF) & !word & 0x8080_8080 != 0 {
            break;
        }
    }
    let length = 11u32.max(words * 4);
    let data = ctx.rom.claim(SAVE_SIGNATURE, length, KIND, signature_id)?;
    let text: String = data.iter().take_while(|&&byte| byte != 0).map(|&byte| byte as char).collect();
    ctx.count(signature_id, &format!("c_literal_length:WriteSramWithRetries(..., 11); CompareStrings word loop reads {} bytes", words * 4));
    ctx.set(signature_id, json!({ "bytes": data, "text": text }));
    Ok(())
}

fn run(ctx: &Ctx) -> R<()> {
    let mut reach = Reach::default();
    zoid_base_stats(ctx, &mut reach)?;
    zoid_shop(ctx, &mut reach)?;
    let (levels, auxiliary, classes) = pilots(ctx)?;
    let auxiliary_count = auxiliary_pilots(ctx, &auxiliary)?;
    auxiliary_pilot_pilot_ids(ctx)?;
    experience_thresholds(ctx, &levels)?;
    growth(ctx, &classes)?;
    reach.growth_classes = classes;
    pulse_stat_growth(ctx)?;
    ability_schedule(ctx, &mut reach)?;
    auxiliary_effects(ctx, auxiliary_count, &mut reach)?;
    pulse_effect_schedule(ctx, &mut reach)?;
    let groups = field_encounter_definitions(ctx)?;
    world_encounter_thresholds(ctx)?;
    encounter_formations(ctx, &groups, &mut reach)?;
    challenges(ctx, &mut reach)?;
    shops(ctx, &mut reach)?;
    equipment(ctx, &mut reach)?;
    if let Some(&bad) = reach.zoids.iter().find(|&&zoid| zoid > ZOID_LAST_MODEL) {
        return Err(format!("a decoded record names zoid model {bad}, past the zoid tables"));
    }
    if let Some(&bad) = reach.pilots.iter().find(|&&pilot| pilot >= PILOT_COUNT) {
        return Err(format!("a decoded record names pilot {bad}, past BATTLE_PILOT_QUOTE_PILOT_COUNT"));
    }
    save(ctx)?;
    names::run(ctx, &reach, ZOID_LAST_MODEL + 1)
}
