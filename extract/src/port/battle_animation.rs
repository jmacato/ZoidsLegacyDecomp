//! Battle animations: StartBattleAnimation records and scripts, LoadBattleAnimationResources headers,
//! CreateBattleAnimationGroup callbacks, and the LZ77 zoid equipment animation scripts of StartZoidEquipmentAnimation.

use std::collections::{BTreeMap, BTreeSet};

use serde_json::{json, Value};

use super::{bios, graphics, Port};
use crate::basis::Basis;
use crate::rom::{le16, le32, R};
use crate::run::Ctx;
use crate::{repo_root, verify_c};

/// StartBattleAnimation and every caller: which entry, item id and resource variant each one passes.
const RECORDS_READER: Basis = Basis::C(&[
    ("src/battle/battle_animation.h", "bb6342eaf90720323098ac43177cffe1af98aac3"),
    ("src/battle/start_battle_animation.c", "f0ace9715b59cdfd3ac14018b7269ae91c3cb972"),
    ("src/battle/start_battle_equipment_animation.c", "a6db612572dbc9b3926da19031d850505afa3020"),
    ("src/battle/start_battle_impact_animation.c", "265924d65a6b72cab06c31facd3df1b7ac5d0dbc"),
    ("src/battle/start_battle_sliding_impact_animation.c", "e6547b5ac16befab14a3e013ae2c6432ff2256ea"),
    ("src/battle/start_battle_no_impact_animation.c", "e6cba6c5f23662f195ae76c4bec6ec56ea2dbf10"),
    ("src/battle/start_battle_stationary_no_impact_animation.c", "3fb47fd104ed4fa64742b0f4602a45a7957b59ee"),
    ("src/battle/start_battle_shield_impact_animation.c", "8186083c53487da2bc56f154843e5c1f205999a9"),
    ("src/battle/start_battle_scene_animation.c", "84436a62765ea31d06a4b882f8754a7cd8a5fd42"),
    ("src/game/modes/run_battle_scene.c", "1d8942aaaced975a60c680c0ca681e138bf98c69"),
    ("src/events/commands/event_play_battle_equipment_animation.c", "8c4c63141df86506b0cd5f2970ddf17e023280b5"),
    ("src/events/commands/event_play_battle_mounted_equipment_animation.c", "619ef3487a6112d3cad1e094fc3915447e5eebb8"),
    ("src/events/commands/event_play_battle_impact_animation.c", "4bf3242637dcc76a704fe24f4c2981f9cde51a58"),
    ("src/events/commands/event_play_battle_model_equipment_impact_animation.c", "f8309e89c5f1d58cfe68e6308aa7edb861c8403c"),
    ("src/events/commands/event_combine_battle_zoids.c", "7b1dc0601dfc0aaa219c29f306a1bea6bba7847d"),
]);
const SCRIPT_READER: Basis = Basis::C(&[
    ("src/battle/battle_animation.h", "bb6342eaf90720323098ac43177cffe1af98aac3"),
    ("src/battle/start_battle_animation.c", "f0ace9715b59cdfd3ac14018b7269ae91c3cb972"),
    ("src/battle/update_battle_animation_script.c", "85558ec838a614eee796c46367f4776c545a075c"),
]);
const HEADER_READER: Basis = Basis::C(&[
    ("src/battle/battle_animation.h", "bb6342eaf90720323098ac43177cffe1af98aac3"),
    ("src/battle/start_battle_animation.c", "f0ace9715b59cdfd3ac14018b7269ae91c3cb972"),
    ("src/battle/load_battle_animation_resources.c", "9184fcf8e856f39f3a1bec7d0fd546984f09ef13"),
    ("src/battle/create_battle_animation_sprite.c", "db2535631b290e8a435595614663b3d8dde2d75f"),
    ("src/graphics/create_mirrored_sprite_from_table.c", "7e29c39fccf33d12f177563a45bab42837a6bb8d"),
    ("src/graphics/create_sprite_from_table.c", "10890981a20d144607c171ecaf63ea3a74f3e369"),
]);
const CALLBACK_READER: Basis = Basis::C(&[
    ("src/battle/battle_animation.h", "bb6342eaf90720323098ac43177cffe1af98aac3"),
    ("src/battle/update_battle_animation_script.c", "85558ec838a614eee796c46367f4776c545a075c"),
    ("src/battle/create_battle_animation_group.c", "07c2436146ed8e6e15ddb2574067c3eac7b44e38"),
    ("src/graphics/create_sprite_group.c", "52a5f063631c9d8645a184d52278b9b716fb8c0b"),
    ("src/graphics/update_sprite_groups.c", "511c254adfd8cb331d214b6fb2883a7453cfefb8"),
]);
/// __umodsi3, called as ModuloUnsigned32 by UpdateBattleAnimationScript.
const MODULO: Basis = Basis::MatchedAsm(&[("src/runtime/libgcc_divmod.s", "375fbacf27e825097d843dc3feeafb93ad488311")]);
pub const ZOID_EQUIPMENT: Basis = Basis::C(&[
    ("src/battle/battle_animation.h", "bb6342eaf90720323098ac43177cffe1af98aac3"),
    ("src/battle/start_zoid_equipment_animation.c", "12d37d5af768705762198e28bace916eed6c3ce0"),
    ("src/battle/update_zoid_equipment_animation.c", "8e5be177d31ff7afc281673e69fb3f40b9fe34fc"),
    ("src/battle/start_battle_equipment_animation.c", "a6db612572dbc9b3926da19031d850505afa3020"),
    ("src/battle/start_battle_impact_animation.c", "265924d65a6b72cab06c31facd3df1b7ac5d0dbc"),
    ("src/game/modes/run_battle_scene.c", "1d8942aaaced975a60c680c0ca681e138bf98c69"),
    ("src/graphics/queue_tilemap_copy.c", "e3afccb01472b6685eef716babe98fce7dbed105"),
    ("src/graphics/process_transfer_queue.c", "bd3df7baf01ad4e5d00e43a241686352967859c7"),
]);

pub const PORT: Port = Port { name: "battle_animation", bases: &[RECORDS_READER, SCRIPT_READER, HEADER_READER, CALLBACK_READER, MODULO, ZOID_EQUIPMENT, bios::LZ77_WRAM], run };

const RECORDS: u32 = 0x087D_818C;
const RECORD_BYTES: u32 = 0x60;
const ENTRY_BYTES: u32 = 12;
/// BATTLE_ANIMATION_ENTRY_COUNT
const ENTRIES: u32 = 8;
/// Entry addresses the StartBattle*Animation callers add to item_id * 0x60: entries 2..7 of record 0.
const ENTRY_ROOTS: [u32; 6] = [0x087D_81A4, 0x087D_81B0, 0x087D_81BC, 0x087D_81C8, 0x087D_81D4, 0x087D_81E0];
/// StartBattleSceneAnimation animation ids in run_battle_scene.c and event_combine_battle_zoids.c.
const SCENE_ANIMATIONS: [u32; 2] = [0x320, 0x321];
/// resource_variant arguments: run_battle_scene.c passes 0 or 1, the event commands and StartBattleSceneAnimation pass 0.
const CALLER_VARIANTS: [u32; 2] = [0, 1];
const HEADERS: u32 = 0x087D_2338;
const HEADER_BYTES: u32 = 28;
/// BATTLE_ANIMATION_RESOURCE_COUNT; the loader reads at most 8 resource ids and 8 sound ids.
const LOADER_BOUND: u32 = 8;
const CALLBACKS: u32 = 0x087A_2D1C;
const GRAPHICS: u32 = 0x087A_C9F8;
const SPRITE_RESOURCES: u32 = 0x087A_CDD8;
/// run_battle_scene.c (energy shield) calls LoadSpriteGraphicsFromTable(GRAPHICS + BattleUnit.data264 * 8, 0, ...) with no bound check on the s16 data264.
/// StartBattleAnimation stores resource_ids[0] + 1 of a callback 0x59 header there, but unit records are also filled at setup and copied whole
/// (0x270-byte copies in execute_battle_deck_command.c), so the index is not narrowed: every entry up to SPRITE_RESOURCES is read.
const ENERGY_SHIELD_READER: &str = "run_battle_scene.c energy shield: LoadSpriteGraphicsFromTable(0x087AC9F8 + BattleUnit.data264 * 8, 0, 0x380, 0xE), no bound check on data264";
const X_ADJUST: u32 = 0x087A_C90C;
/// StartBattleAnimation reads D_087AC90C[item_id] only when item_id <= 100.
const X_ADJUST_LAST_ITEM: u32 = 100;
const SPRITE_PRIORITY: u32 = 0x087E_D68C;
/// StartBattleEquipmentAnimation reads D_087ED68C[equipment_slot + zoid_id * 3] for equipment_slot <= 2.
const SPRITE_PRIORITY_SLOTS: u32 = 3;
const ZOID_ANIMATIONS: u32 = 0x087A_773C;
/// StartZoidEquipmentAnimation: D_087A773C + zoid_id * 40 + (animation_slot - 4) * 4.
const ZOID_ROW_BYTES: u32 = 40;
const ZOID_SCRIPT_BUFFER: u32 = 0x0203_4060;

const SCRIPT_END: i16 = -1;
const SCRIPT_LOOP: i16 = -2;
const CALLBACK_PROJECTILE_FLASH: u16 = 1;
const CALLBACK_FALLING_STREAK_IMPACT_SPARK: u16 = 0x5F;
const CALLBACK_RANDOM_X_FALLING_STREAK: u16 = 0x60;
const CALLBACK_FALLING_STREAK_GROUND_ATTACHMENT: u16 = 0x61;

const ZOID_SCRIPT_END: i32 = -1;
const ZOID_COMPLETION_MARKER: i32 = -2;
const ZOID_PLAY_SOUND: i32 = -3;

fn next_root(ctx: &Ctx, after: u32) -> R<u32> {
    ctx.roots.by_address().range(after + 1..).next().map(|(address, _)| *address).ok_or_else(|| format!("no referenced address after 0x{after:08X}"))
}

fn s16(ctx: &Ctx, address: u32, format: &str, id: usize) -> R<i16> {
    Ok(le16(ctx.rom.claim(address, 2, format, id)?, 0) as i16)
}

struct Script {
    header: i16,
    spawns: BTreeSet<u8>,
    ends: bool,
}

/// UpdateBattleAnimationScript from StartBattleAnimation's state: the cursor starts after the s16 header and loop_start is that cursor.
/// -1 ends; -2 increments loop_count and continues past its s16 count when they are equal, else returns to loop_start;
/// any other value spawns a group from {s16 delay, u16 x, u16 y, u16 priority}. (cursor at a -2, loop_count) can take
/// 65536 values per -2 command, so more encounters than that mean the script never ends.
fn script(ctx: &Ctx, address: u32, reached: Vec<String>, entries: usize) -> R<Script> {
    let (id, _) = ctx.item("battle_animation.script", address, SCRIPT_READER, reached);
    let format = "battle_animation_script";
    let header = s16(ctx, address, format, id)?;
    let loop_start = address + 2;
    let mut cursor = loop_start;
    let mut loop_count: u16 = 0;
    let mut spawn: u8 = 0;
    let mut spawns = BTreeSet::new();
    let mut spawn_count = 0u64;
    let mut encounters: u64 = 0;
    let mut commands: BTreeMap<u32, Value> = BTreeMap::new();
    let ends = loop {
        let new = !commands.contains_key(&cursor);
        let read = |at: u32, length: u32| if new { ctx.rom.claim(at, length, format, id) } else { ctx.rom.peek(at, length) };
        let command = le16(read(cursor, 2)?, 0) as i16;
        if command == SCRIPT_END {
            commands.insert(cursor, json!({ "op": "end" }));
            break true;
        }
        if command == SCRIPT_LOOP {
            let count = le16(read(cursor + 2, 2)?, 0) as i16;
            commands.insert(cursor, json!({ "op": "loop", "count": count }));
            let loops = commands.values().filter(|entry| entry["op"] == "loop").count() as u64;
            loop_count = loop_count.wrapping_add(1);
            encounters += 1;
            if encounters > 65536 * loops {
                break false;
            }
            cursor = if i32::from(count) == i32::from(loop_count) { cursor + 4 } else { loop_start };
            continue;
        }
        let fields = read(cursor, 8)?;
        commands.insert(cursor, json!({
            "op": "spawn",
            "delay": le16(fields, 0),
            "x": le16(fields, 2) as i16,
            "y": le16(fields, 4) as i16,
            "priority": le16(fields, 6),
        }));
        spawns.insert(spawn);
        spawn = spawn.wrapping_add(1);
        spawn_count += 1;
        cursor += 8;
    };
    ctx.count(id, if ends { "terminator" } else { "control_flow (no -1 is reached: a loop count never matches)" });
    ctx.set(id, json!({
        "header": header,
        "ends": ends,
        "spawns": if ends { json!(spawn_count) } else { json!("unbounded") },
        "record_entries": entries,
        "commands": commands.into_iter().map(|(at, mut entry)| { entry["at"] = json!(format!("0x{at:08X}")); entry }).collect::<Vec<_>>(),
    }));
    Ok(Script { header, spawns, ends })
}

struct Header {
    callback_kind: u16,
    resources: Vec<i16>,
    sounds: Vec<i16>,
}

/// StartBattleAnimation reads callback_kind; LoadBattleAnimationResources reads resource ids from +2 and sound ids from +0x12,
/// each until -1 or eight values, so the sound list can run into the next header.
fn header(ctx: &Ctx, table: usize, index: u32) -> R<Header> {
    let format = "table.battle_animation_resource_headers";
    let base = HEADERS + index * HEADER_BYTES;
    let callback_kind = le16(ctx.rom.claim(base, 2, format, table)?, 0);
    let mut lists = [Vec::new(), Vec::new()];
    for (list, offset) in lists.iter_mut().zip([2, 0x12]) {
        for slot in 0..LOADER_BOUND {
            let value = s16(ctx, base + offset + slot * 2, format, table)?;
            if value == -1 {
                break;
            }
            list.push(value);
        }
    }
    let [resources, sounds] = lists;
    Ok(Header { callback_kind, resources, sounds })
}

/// Header table bytes up to the last byte the reached headers read that neither StartBattleAnimation nor LoadBattleAnimationResources reads.
fn header_unread(ctx: &Ctx, table: usize, headers: &BTreeMap<u32, Header>) -> R<()> {
    let mut read = BTreeSet::new();
    for (&index, header) in headers {
        let base = index * HEADER_BYTES;
        read.extend(base..base + 2);
        for (list, offset) in [(&header.resources, 2), (&header.sounds, 0x12)] {
            let slots = (list.len() as u32 + 1).min(LOADER_BOUND);
            read.extend(base + offset..base + offset + slots * 2);
        }
    }
    let (Some(&first), Some(&last)) = (headers.keys().next(), headers.keys().next_back()) else { return Ok(()) };
    let after_terminator = "LoadBattleAnimationResources (load_battle_animation_resources.c) reads resource_ids from +2 and sound_ids from +0x12 only up to the first -1 or eight entries, and StartBattleAnimation reads only callback_kind +0 and resource_ids[0] +2; this byte follows a -1 that ends its list".to_string();
    let not_indexed = |index: u32| format!(
        "header {index} is never indexed: StartBattleAnimation and LoadBattleAnimationResources (start_battle_animation.c, load_battle_animation_resources.c) use header = script s16 header + resource_variant, resource_variant = min(caller variant + (entry control & 3), 2), and the callers pass variant 0 or 1 (run_battle_scene.c) or 0 (event commands, StartBattleSceneAnimation); over the scripts of every battle animation record entry this gives the {} header indices {first}..{last} listed in this item's data, which do not include {index}",
        headers.len()
    );
    let reason = |offset: u32| if headers.contains_key(&(offset / HEADER_BYTES)) { after_terminator.clone() } else { not_indexed(offset / HEADER_BYTES) };
    let end = *read.iter().next_back().unwrap() + 1;
    let mut offset = 0;
    while offset < end {
        if read.contains(&offset) {
            offset += 1;
            continue;
        }
        let start = offset;
        let text = reason(start);
        while offset < end && !read.contains(&offset) && reason(offset) == text {
            offset += 1;
        }
        ctx.unread(table, HEADERS + start, offset - start, &text)?;
    }
    Ok(())
}

/// UpdateBattleAnimationScript's kind for a spawn: PROJECTILE_FLASH alternates with the next kind by spawn parity;
/// FALLING_STREAK_IMPACT_SPARK becomes 0x61, or 0x60 in scene 0xD, when spawn_count % 3 != 0.
fn spawn_kinds(kind: u16, spawns: &BTreeSet<u8>) -> BTreeSet<u16> {
    let mut kinds = BTreeSet::new();
    for &spawn in spawns {
        match kind {
            CALLBACK_PROJECTILE_FLASH => {
                kinds.insert(CALLBACK_PROJECTILE_FLASH + u16::from(spawn & 1));
            }
            CALLBACK_FALLING_STREAK_IMPACT_SPARK if spawn % 3 != 0 => {
                kinds.insert(CALLBACK_RANDOM_X_FALLING_STREAK);
                kinds.insert(CALLBACK_FALLING_STREAK_GROUND_ATTACHMENT);
            }
            _ => {
                kinds.insert(kind);
            }
        }
    }
    kinds
}

/// CreateBattleAnimationSprite creates sprites from SPRITE_RESOURCES[gBattleAnimationResourceIds[slot]] through
/// CreateMirroredSpriteFromTable and CreateSpriteFromTable. The sprites port reads that table as 8-byte entries; check it read this one.
fn sprite_resource_read(ctx: &Ctx, resource: i16) -> R<()> {
    let entry = SPRITE_RESOURCES + u32::from(resource as u16) * 8;
    let owners = ctx.rom.owners();
    for offset in entry - crate::BASE..entry - crate::BASE + 8 {
        let name = ctx.rom.format_name(owners[offset as usize]);
        if name != "table.sprite_resources" {
            return Err(format!("battle animation resource {resource}: sprite resource entry 0x{entry:08X} was not read by the sprites port ({name:?})"));
        }
    }
    Ok(())
}

pub fn code_source(regions: &[verify_c::Region], pointer: u32) -> R<String> {
    if pointer & 1 == 0 {
        return Err(format!("callback 0x{pointer:08X} is not a Thumb address"));
    }
    let offset = (pointer & !1).wrapping_sub(crate::BASE);
    let region = regions.iter().find(|region| region.start <= offset && offset < region.end).ok_or_else(|| format!("callback 0x{pointer:08X} is not in a matched region"))?;
    let entry = format!("asm(\"func_{:08X}\")", pointer & !1);
    for source in &region.sources {
        if !source.ends_with(".c") {
            return Err(format!("callback 0x{pointer:08X} is in region {} with source {source}, not matched C", region.name));
        }
        let text = std::fs::read_to_string(repo_root().join("src").join(source)).map_err(|error| format!("{source}: {error}"))?;
        if text.contains(&entry) {
            return Ok(source.clone());
        }
    }
    Err(format!("callback 0x{pointer:08X} is inside region {} but no function in {:?} is named func_{:08X}", region.name, region.sources, pointer & !1))
}

fn animations(ctx: &Ctx) -> R<()> {
    let reached = ctx.roots.require(RECORDS)?;
    for (index, &root) in ENTRY_ROOTS.iter().enumerate() {
        ctx.roots.require(root)?;
        if root != RECORDS + (index as u32 + 2) * ENTRY_BYTES {
            return Err(format!("entry root 0x{root:08X} is not entry {} of record 0", index + 2));
        }
    }
    let end = next_root(ctx, *ENTRY_ROOTS.last().unwrap())?;
    if (end - RECORDS) % RECORD_BYTES != 0 {
        return Err(format!("battle animation records: 0x{end:08X} is not a whole number of 0x60-byte records after 0x{RECORDS:08X}"));
    }
    let records = (end - RECORDS) / RECORD_BYTES;
    for scene in SCENE_ANIMATIONS {
        if scene >= records {
            return Err(format!("scene animation {scene} is past the {records} records before 0x{end:08X}"));
        }
    }
    let (records_id, _) = ctx.item("table.battle_animation_records", RECORDS, RECORDS_READER, reached);
    ctx.count(records_id, "next_root (item_id is a runtime u16; scene animation ids 0x320 and 0x321 fall inside)");
    let format = "table.battle_animation_records";
    let mut scripts: BTreeMap<u32, (BTreeSet<u32>, Vec<String>, usize)> = BTreeMap::new();
    let mut listed = Vec::new();
    let mut null_entries = Vec::new();
    for record in 0..records {
        let mut entries = Vec::new();
        for entry in 0..ENTRIES {
            let at = RECORDS + record * RECORD_BYTES + entry * ENTRY_BYTES;
            let pointer = le32(ctx.rom.claim(at, 4, format, records_id)?, 0);
            let control = ctx.rom.claim(at + 4, 1, format, records_id)?[0];
            let x_offset = s16(ctx, at + 6, format, records_id)?;
            let y_offset = le16(ctx.rom.claim(at + 8, 2, format, records_id)?, 0);
            for (offset, length, field) in [(5, 1, "data05"), (0xA, 2, "data0A")] {
                ctx.unread(records_id, at + offset, length, &format!("BattleAnimationEntry.{field} (battle_animation.h): StartBattleAnimation (start_battle_animation.c), the only C that dereferences an entry, reads script +0, control +4, x_offset +6 and y_offset +8; no C reads BattleAnimationEntry.{field}"))?;
            }
            if pointer == 0 {
                null_entries.push(format!("{record}.{entry}"));
            } else if !ctx.rom.is_data(pointer) {
                return Err(format!("battle animation record {record} entry {entry}: script 0x{pointer:08X} is not ROM data"));
            } else {
                let slot = scripts.entry(pointer).or_default();
                for variant in CALLER_VARIANTS {
                    slot.0.insert((variant + u32::from(control & 3)).min(2));
                }
                if slot.1.is_empty() {
                    slot.1.push(format!("table.battle_animation_records@0x{RECORDS:08X}[{record}][{entry}]"));
                }
                slot.2 += 1;
            }
            entries.push(json!({
                "script": if pointer == 0 { json!(null) } else { json!(format!("0x{pointer:08X}")) },
                "control": control,
                "variant": control & 3,
                "anchor": control & 0x3C,
                "sprite_priority": control >> 6,
                "x_offset": x_offset,
                "y_offset": y_offset,
            }));
        }
        listed.push(json!(entries));
    }
    ctx.set(records_id, json!({
        "records": records,
        "entry_bytes_read": "+0..+4 script, +4 control, +6 x_offset, +8 y_offset",
        "null_script_entries": null_entries,
        "entries": listed,
    }));

    let (adjust_id, _) = ctx.item("table.battle_equipment_x_adjust", X_ADJUST, RECORDS_READER, ctx.roots.require(X_ADJUST)?);
    ctx.count(adjust_id, "c_guard:item_id <= 100 (start_battle_animation.c)");
    let mut adjust = Vec::new();
    for item in 0..=X_ADJUST_LAST_ITEM {
        adjust.push(s16(ctx, X_ADJUST + item * 2, "table.battle_equipment_x_adjust", adjust_id)?);
    }
    ctx.set(adjust_id, json!({ "values": adjust }));

    let (headers_id, _) = ctx.item("table.battle_animation_resource_headers", HEADERS, HEADER_READER, ctx.roots.require(HEADERS)?);
    ctx.count(headers_id, "header ids reached: script header + resource variant");
    let (callbacks_id, _) = ctx.item("table.battle_animation_callbacks", CALLBACKS, CALLBACK_READER, ctx.roots.require(CALLBACKS)?);
    ctx.count(callbacks_id, "callback kinds reached by spawning scripts");
    let mut headers: BTreeMap<u32, Header> = BTreeMap::new();
    let mut header_scripts: BTreeMap<u32, BTreeSet<u32>> = BTreeMap::new();
    let mut kinds: BTreeMap<u16, BTreeSet<u32>> = BTreeMap::new();
    let mut unbounded = Vec::new();
    for (&address, (variants, reached, entries)) in &scripts {
        let run = script(ctx, address, reached.clone(), *entries)?;
        if !run.ends {
            unbounded.push(address);
        }
        for &variant in variants {
            let index = i32::from(run.header) + variant as i32;
            if index < 0 {
                return Err(format!("battle animation script 0x{address:08X}: header {} + variant {variant} is negative", run.header));
            }
            let index = index as u32;
            if !headers.contains_key(&index) {
                headers.insert(index, header(ctx, headers_id, index)?);
            }
            header_scripts.entry(index).or_default().insert(address);
            for kind in spawn_kinds(headers[&index].callback_kind, &run.spawns) {
                kinds.entry(kind).or_default().insert(index);
            }
        }
    }

    header_unread(ctx, headers_id, &headers)?;

    let (graphics_id, _) = ctx.item("table.compressed_sprite_graphics", GRAPHICS, graphics::SPRITE_GRAPHICS, ctx.roots.require(GRAPHICS)?);
    let mut listed_headers = Vec::new();
    for (&index, header) in &headers {
        let reached = format!("table.battle_animation_resource_headers@0x{HEADERS:08X}[{index}]");
        for &resource in &header.resources {
            graphics::sprite_graphics(ctx, GRAPHICS, u32::from(resource as u16), false, reached.clone())?;
            let entry = (GRAPHICS as i32 + i32::from(resource) * 8) as u32;
            let tiles = le32(ctx.rom.claim(entry, 4, "table.compressed_sprite_graphics", graphics_id)?, 0);
            ctx.rom.claim(tiles + 1, 3, "lz77", graphics_id)?;
            sprite_resource_read(ctx, resource)?;
        }
        listed_headers.push(json!({
            "index": index,
            "address": format!("0x{:08X}", HEADERS + index * HEADER_BYTES),
            "callback_kind": header.callback_kind,
            "resource_ids": header.resources,
            "sound_ids": header.sounds,
            "scripts": header_scripts[&index].iter().map(|address| format!("0x{address:08X}")).collect::<Vec<_>>(),
        }));
    }
    ctx.set(headers_id, json!({ "headers": listed_headers }));

    ctx.roots.require(SPRITE_RESOURCES)?;
    for entry in 0..(SPRITE_RESOURCES - GRAPHICS) / 8 {
        graphics::sprite_graphics(ctx, GRAPHICS, entry, false, ENERGY_SHIELD_READER.to_string())?;
    }

    let regions = verify_c::regions(&repo_root().join("regions.txt"))?;
    let mut listed_kinds = Vec::new();
    for (&kind, header_ids) in &kinds {
        let pair = ctx.rom.claim(CALLBACKS + u32::from(kind) * 8, 8, "table.battle_animation_callbacks", callbacks_id)?;
        let mut sources = Vec::new();
        for pointer in [le32(pair, 0), le32(pair, 4)] {
            sources.push(if pointer == 0 { json!(null) } else { json!(code_source(&regions, pointer)?) });
        }
        listed_kinds.push(json!({
            "kind": kind,
            "init": format!("0x{:08X}", le32(pair, 0)),
            "update": format!("0x{:08X}", le32(pair, 4)),
            "init_source": sources[0],
            "update_source": sources[1],
            "headers": header_ids,
        }));
    }
    let end = next_root(ctx, CALLBACKS)?;
    if (end - CALLBACKS) % 8 != 0 {
        return Err(format!("battle animation callbacks: 0x{end:08X} is not a whole number of 8-byte entries"));
    }
    let produced: Vec<String> = kinds.keys().map(|kind| format!("0x{kind:X}")).collect();
    for kind in (0..(end - CALLBACKS) / 8).filter(|kind| !kinds.contains_key(&(*kind as u16))) {
        ctx.unread(callbacks_id, CALLBACKS + kind * 8, 8, &format!(
            "callback kind 0x{kind:X} is never produced: the only reader of 0x087A2D1C is CreateBattleAnimationGroup (create_battle_animation_group.c), called only by UpdateBattleAnimationScript (update_battle_animation_script.c) when a script spawns, with the callback_kind StartBattleAnimation copied from the resource header (kind 1 becomes 1 or 2, 0x5F becomes 0x60 or 0x61); the reached headers of spawning scripts give only kinds {}",
            produced.join(", ")
        ))?;
    }
    ctx.set(callbacks_id, json!({ "kinds": listed_kinds, "scripts_with_unbounded_spawns": unbounded.iter().map(|address| format!("0x{address:08X}")).collect::<Vec<_>>() }));
    Ok(())
}

/// UpdateZoidEquipmentAnimation over the decoded commands {s32 frame_offset_or_command, s32 duration_or_song}.
/// Each advance steps one command, plays -3 commands, stops at -1, and shows the command when the next one is the -2 marker
/// (then restarts at 0 if the frame offset is nonzero) or when its duration is nonzero; zero-duration commands are skipped.
fn zoid_script(decoded: &[u8], address: u32) -> R<Value> {
    let word = |index: u32, half: u32| -> R<i32> {
        let at = (index as usize) * 8 + (half as usize) * 4;
        if at + 4 > decoded.len() {
            return Err(format!("zoid equipment animation 0x{address:08X}: command {index} is past the decoded {} bytes", decoded.len()));
        }
        Ok(le32(decoded, at) as i32)
    };
    let mut steps = Vec::new();
    let mut frames: BTreeMap<i32, Value> = BTreeMap::new();
    let mut seen = BTreeSet::new();
    let mut index: u32 = 0;
    word(0, 1)?;
    let ending = loop {
        if !seen.insert(index) {
            break "cycle";
        }
        let mut marker = false;
        loop {
            index += 1;
            while word(index, 0)? == ZOID_PLAY_SOUND {
                steps.push(json!({ "command": index, "op": "play_song", "song": word(index, 1)? }));
                index += 1;
            }
            if word(index, 0)? == ZOID_SCRIPT_END {
                steps.push(json!({ "command": index, "op": "end" }));
                break;
            }
            if word(index + 1, 0)? == ZOID_COMPLETION_MARKER {
                marker = true;
                break;
            }
            if word(index, 1)? != 0 {
                break;
            }
            steps.push(json!({ "command": index, "op": "skip", "frame_offset": word(index, 0)? }));
        }
        let first = word(index, 0)?;
        if first == ZOID_SCRIPT_END {
            break "end";
        }
        let duration = word(index, 1)?;
        if first != 0 {
            if first < 0 {
                return Err(format!("zoid equipment animation 0x{address:08X}: command {index} frame offset {first} is negative"));
            }
            let at = first as usize;
            if at + 8 > decoded.len() {
                return Err(format!("zoid equipment animation 0x{address:08X}: frame at {first} is past the decoded {} bytes", decoded.len()));
            }
            let (x, y, width, height) = (le16(decoded, at), le16(decoded, at + 2), le16(decoded, at + 4), le16(decoded, at + 6));
            if height > 255 {
                return Err(format!("zoid equipment animation 0x{address:08X}: frame at {first} has {height} rows; ProcessTransferQueue counts rows in a u8"));
            }
            let tilemap = usize::from(width) * usize::from(height) * 2;
            if at + 8 + tilemap > decoded.len() {
                return Err(format!("zoid equipment animation 0x{address:08X}: frame at {first} tilemap runs past the decoded {} bytes", decoded.len()));
            }
            frames.insert(first, json!({ "offset": first, "x": x, "y": y, "width": width, "height": height, "tilemap_bytes": tilemap }));
        }
        steps.push(json!({ "command": index, "op": "show", "frame_offset": first, "duration": duration, "completion_marker": marker }));
        if marker && first != 0 {
            index = 0;
        }
        word(index, 1)?;
    };
    Ok(json!({ "ending": ending, "steps": steps, "frames": frames.into_values().collect::<Vec<_>>() }))
}

fn zoid_equipment(ctx: &Ctx) -> R<()> {
    let (priority_id, _) = ctx.item("table.zoid_equipment_sprite_priority", SPRITE_PRIORITY, ZOID_EQUIPMENT, ctx.roots.require(SPRITE_PRIORITY)?);
    let end = next_root(ctx, SPRITE_PRIORITY)?;
    if (end - SPRITE_PRIORITY) % SPRITE_PRIORITY_SLOTS != 0 {
        return Err(format!("zoid equipment sprite priorities: 0x{end:08X} is not a whole number of 3-byte rows"));
    }
    ctx.count(priority_id, "next_root (zoid_id is a runtime u8; 3 slots per zoid from equipment_slot <= 2)");
    let rows = (end - SPRITE_PRIORITY) / SPRITE_PRIORITY_SLOTS;
    let values = ctx.rom.claim(SPRITE_PRIORITY, rows * SPRITE_PRIORITY_SLOTS, "table.zoid_equipment_sprite_priority", priority_id)?;
    ctx.set(priority_id, json!({ "zoids": rows, "priorities": values.chunks(3).map(|row| row.to_vec()).collect::<Vec<_>>() }));

    let (table_id, _) = ctx.item("table.zoid_equipment_animations", ZOID_ANIMATIONS, ZOID_EQUIPMENT, ctx.roots.require(ZOID_ANIMATIONS)?);
    let end = next_root(ctx, ZOID_ANIMATIONS)?;
    if (end - ZOID_ANIMATIONS) % ZOID_ROW_BYTES != 0 {
        return Err(format!("zoid equipment animations: 0x{end:08X} is not a whole number of 40-byte rows"));
    }
    ctx.count(table_id, "next_root (zoid_id is a runtime u8); 10 slots per row from the zoid_id * 40 stride");
    let rows = (end - ZOID_ANIMATIONS) / ZOID_ROW_BYTES;
    let mut listed = Vec::new();
    for zoid in 0..rows {
        let mut row = Vec::new();
        for slot in 0..ZOID_ROW_BYTES / 4 {
            let at = ZOID_ANIMATIONS + zoid * ZOID_ROW_BYTES + slot * 4;
            let pointer = le32(ctx.rom.claim(at, 4, "table.zoid_equipment_animations", table_id)?, 0);
            if pointer == 0 {
                row.push(json!(null));
                continue;
            }
            let from = format!("table.zoid_equipment_animations@0x{ZOID_ANIMATIONS:08X}[{zoid}][{slot}]");
            let (_, decoded) = graphics::lz77_item(ctx, pointer, false, bios::LZ77_WRAM, "zoid_equipment_animation", Some(ZOID_SCRIPT_BUFFER), vec![from.clone()])?;
            let (script_id, new) = ctx.item("zoid_equipment_animation", pointer, ZOID_EQUIPMENT, vec![from]);
            if new {
                ctx.count(script_id, "control_flow (decoded LZ77 buffer, no ROM bytes)");
                ctx.set(script_id, zoid_script(&decoded, pointer)?);
            }
            row.push(json!(format!("0x{pointer:08X}")));
        }
        listed.push(json!({ "zoid": zoid, "animation_slots_4_to_13": row }));
    }
    ctx.set(table_id, json!({ "zoids": rows, "rows": listed }));
    Ok(())
}

fn run(ctx: &Ctx) -> R<()> {
    animations(ctx)?;
    zoid_equipment(ctx)
}

#[cfg(test)]
mod tests {
    use super::*;

    fn commands(words: &[i32]) -> Vec<u8> {
        words.iter().flat_map(|word| word.to_le_bytes()).collect()
    }

    #[test]
    fn spawn_kind_variants() {
        let spawns: BTreeSet<u8> = [0, 1, 2].into_iter().collect();
        assert_eq!(spawn_kinds(1, &spawns).into_iter().collect::<Vec<_>>(), vec![1, 2]);
        assert_eq!(spawn_kinds(0x5F, &[0].into_iter().collect()).into_iter().collect::<Vec<_>>(), vec![0x5F]);
        assert_eq!(spawn_kinds(0x5F, &spawns).into_iter().collect::<Vec<_>>(), vec![0x5F, 0x60, 0x61]);
        assert_eq!(spawn_kinds(7, &spawns).into_iter().collect::<Vec<_>>(), vec![7]);
    }

    #[test]
    fn zoid_script_plays_skips_and_ends() {
        let mut buffer = commands(&[0, 0, -3, 94, 36, 0, 36, 6, -1]);
        buffer.extend([1, 0, 2, 0, 1, 0, 1, 0, 0xAA, 0xBB]);
        let script = zoid_script(&buffer, 0).unwrap();
        assert_eq!(script["ending"], "end");
        let ops: Vec<&str> = script["steps"].as_array().unwrap().iter().map(|step| step["op"].as_str().unwrap()).collect();
        assert_eq!(ops, vec!["play_song", "skip", "show", "end"]);
        assert_eq!(script["frames"][0]["tilemap_bytes"], 2);
    }

    #[test]
    fn zoid_script_marker_restarts() {
        let mut buffer = commands(&[0, 0, 24, 0, -2, 0]);
        buffer.extend([0, 0, 0, 0, 0, 0, 0, 0]);
        let script = zoid_script(&buffer, 0).unwrap();
        assert_eq!(script["ending"], "cycle");
        assert_eq!(script["steps"][0]["completion_marker"], true);
    }
}
