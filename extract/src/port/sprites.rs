//! Sprite frame and animation tables read by UpdateSpritesAndBuildOam, from CreateSprite and CreateSpriteFromTable roots.

use std::collections::BTreeSet;

use serde_json::json;

use super::{literal, Port};
use crate::basis::Basis;
use crate::image::{gray_tiles_4bpp, palette_swatch, tiles_4bpp};
use crate::rom::{le16, le32, R};
use crate::run::Ctx;

pub const SPRITES: Basis = Basis::C(&[
    ("src/field/initialize_field_actor_sprites.c", "4761ee93f1722e7e9dae073bb73271c1acbdf40a"),
    ("src/field/field_actor.h", "a72a104ee20ea5fa6e428e29febcc0f71f58990d"),
    ("src/graphics/update_sprites_and_build_oam.c", "88c4542b353249eb6d2ce2b1f47149a73220c791"),
    ("src/graphics/create_sprite.c", "3e6d071d427dd01d0493109c99bfdbe77c897841"),
    ("src/graphics/create_sprite_from_table.c", "10890981a20d144607c171ecaf63ea3a74f3e369"),
    ("src/graphics/set_sprite_animation.c", "89f8b8fcae379eb0412e2c935f1934f5173d2fac"),
]);

/// The C that indexes gFieldActorSpriteDefinitions: FieldActor.model_id (written only by CreateFieldActor) and the character database ids.
pub const FIELD_ACTOR_MODELS: Basis = Basis::C(&[
    ("src/field/field_actor.h", "a72a104ee20ea5fa6e428e29febcc0f71f58990d"),
    ("src/field/create_field_actor.c", "1be55f32be3cd126a512de430bf91198751cbbe7"),
    ("src/field/get_field_actor_animation_index.c", "88ecb7366766953d8cd4d67098f978ab0b81d648"),
    ("src/events/commands/event_spawn_actor.c", "7d5a04de0be40670bce814c005ae9445c25178c9"),
    ("src/events/commands/event_spawn_actor_relative.c", "4138d9b2000b3b613af14145ac11c28aae36ab28"),
    ("src/events/commands/event_set_transport_model.c", "3de1d107e31efc692f2b3e17f28e4d303d891496"),
    ("src/events/commands/event_spawn_transport_actor.c", "0a7d271182992a7136c66908c1a246b8ef34d57f"),
    ("src/ui/run_character_database_viewer.c", "8f7ec7df2dd4e8bfd257884968975fc898fb8c95"),
]);

pub const PORT: Port = Port { name: "sprites", bases: &[SPRITES, FIELD_ACTOR_MODELS], run };

const CREATE_SPRITE: u32 = 0x0809_4484;
const CREATE_SPRITE_FROM_TABLE: u32 = 0x0809_4374;
const STREAM_GRAPHICS: u32 = 0x40_0000;
const FIELD_ACTOR_SPRITE_DEFINITIONS: u32 = 0x087A_D208;
/// EventSpawnActor and EventSpawnActorRelative call CreateFieldActor only when the actor slot byte is <= 0xC.
const FIELD_ACTOR_SPAWN_LAST_SLOT: u32 = 0xC;
/// Piece bytes UpdateSpritesAndBuildOam reads: +0x0..+0xF and +0x11 of each 20-byte piece.
const PIECE_READS: [(u32, u32); 2] = [(0x0, 0x10), (0x11, 1)];
const PIECE_UNREAD: [(u32, u32); 2] = [(0x10, 1), (0x12, 2)];
const PIECE_BYTES: u32 = 20;

/// Pointer table bound when the C gives none: the next C-referenced address, or the first address an entry points at.
/// Entries whose first word is 0 are empty slots: listed as None, not claimed.
fn pointer_table(ctx: &Ctx, base: u32, kind: &str, id: usize, stride: u32) -> R<(Vec<Option<u32>>, &'static str)> {
    let next_root = ctx.roots.by_address().range(base + 1..).next().map(|(address, _)| *address).unwrap_or(crate::BASE + crate::ROM_SIZE);
    let mut bound = next_root;
    let mut source = "next_root";
    let mut entries = Vec::new();
    let mut at = base;
    while at + stride <= bound {
        let pointer = le32(ctx.rom.peek(at, 4)?, 0);
        if pointer == 0 {
            entries.push(None);
            at += stride;
            continue;
        }
        if !ctx.rom.is_data(pointer) {
            if entries.iter().all(Option::is_none) {
                return Err(format!("{kind} at 0x{base:08X}: first entry 0x{pointer:08X} is not ROM data"));
            }
            source = "layout:first_non_pointer_entry";
            break;
        }
        ctx.rom.claim(at, stride, kind, id)?;
        entries.push(Some(at));
        if pointer > base && pointer < bound {
            bound = pointer;
            source = "layout:first_pointed_address";
        }
        at += stride;
    }
    while entries.last() == Some(&None) {
        entries.pop();
    }
    Ok((entries, source))
}

/// Animation commands {s16 frame, s16 duration} until frame == -1; only the frame field of the terminator is read.
fn animation(ctx: &Ctx, address: u32, reached: String, frames: &mut BTreeSet<u16>) -> R<()> {
    let (id, new) = ctx.item("sprite.animation", address, SPRITES, vec![reached]);
    if !new {
        let mut at = address;
        loop {
            let frame = le16(ctx.rom.peek(at, 2)?, 0) as i16;
            if frame == -1 {
                return Ok(());
            }
            frames.insert(frame as u16);
            at += 4;
        }
    }
    let mut commands = Vec::new();
    let mut at = address;
    loop {
        let frame = le16(ctx.rom.claim(at, 2, "sprite_animation", id)?, 0) as i16;
        if frame == -1 {
            break;
        }
        if frame < 0 {
            return Err(format!("sprite animation 0x{address:08X}: negative frame id {frame} at 0x{at:08X}"));
        }
        let duration = le16(ctx.rom.claim(at + 2, 2, "sprite_animation", id)?, 0);
        frames.insert(frame as u16);
        commands.push(json!({ "frame": frame, "duration": duration }));
        at += 4;
    }
    ctx.count(id, "terminator");
    ctx.set(id, json!({ "commands": commands }));
    Ok(())
}

/// Pieces until s16 -1 at +0; returns (first tile, tile count) of each piece for streamed graphics.
fn frame(ctx: &Ctx, address: u32, reached: String) -> R<Vec<(u32, u32)>> {
    let (id, new) = ctx.item("sprite.frame", address, SPRITES, vec![reached]);
    let mut pieces = Vec::new();
    let mut tiles = Vec::new();
    let mut at = address;
    loop {
        let head = if new { ctx.rom.claim(at, 2, "sprite_frame", id)? } else { ctx.rom.peek(at, 2)? };
        if le16(head, 0) as i16 == -1 {
            break;
        }
        if new {
            for (offset, length) in PIECE_READS {
                ctx.rom.claim(at + offset, length, "sprite_frame", id)?;
            }
            for (offset, length) in PIECE_UNREAD {
                ctx.unread(id, at + offset, length, "sprite frame piece byte: UpdateSpritesAndBuildOam (update_sprites_and_build_oam.c), the only C that dereferences a frame, reads it through var_r7 (r7 after ldr r7, [r0] at 0x0809476A; the only later write to r7 before the epilogue is adds r7, #20 at 0x08094F5A, and r7 is never copied to another register) with loads at +0, +2, +3, +4, +6, +8, +0xA, +0xC (ldrsh and 32-bit ldr), +0xE and +0x11 only")?;
            }
        }
        let piece = ctx.rom.peek(at, PIECE_BYTES)?;
        let (width, height) = (le16(piece, 8) as i16 as i32, le16(piece, 0xA) as i16 as i32);
        tiles.push((u32::from(le16(piece, 0)), ((width * height) / 64).max(0) as u32));
        pieces.push(json!({
            "+0": le16(piece, 0), "+2": piece[2], "+3": piece[3], "+4": le16(piece, 4) as i16, "+6": le16(piece, 6) as i16,
            "+8": width, "+A": height, "+C": le32(piece, 0xC) as i32, "+11": piece[0x11],
        }));
        at += PIECE_BYTES;
    }
    if new {
        ctx.count(id, "terminator");
        ctx.set(id, json!({ "pieces": pieces }));
    }
    Ok(tiles)
}

/// One frame table + animation table pair. Returns the tile ranges its frames use.
pub fn sprite_set(ctx: &Ctx, frames_table: u32, animations_table: u32, reached: String, animation_ids: &[u32]) -> R<Vec<(u32, u32)>> {
    let (anim_id, anim_new) = ctx.item("sprite.animation_table", animations_table, SPRITES, vec![reached.clone()]);
    let (entries, source) = if anim_new {
        let (entries, source) = pointer_table(ctx, animations_table, "table.sprite_animations", anim_id, 4)?;
        ctx.count(anim_id, source);
        ctx.set(anim_id, json!({ "animations": entries.len() }));
        (entries, source)
    } else {
        let count = ctx.rom.claims().iter().filter(|claim| claim.item == anim_id).count();
        ((0..count as u32).map(|index| Some(animations_table + index * 4)).collect(), "")
    };
    for &animation_id in animation_ids {
        if animation_id as usize >= entries.len() {
            return Err(format!("animation table 0x{animations_table:08X}: C uses animation {animation_id}, table has {} by {source}", entries.len()));
        }
    }
    let mut frame_ids = BTreeSet::new();
    for entry in entries.iter().flatten() {
        let pointer = le32(ctx.rom.peek(*entry, 4)?, 0);
        animation(ctx, pointer, format!("sprite.animation_table@0x{animations_table:08X}"), &mut frame_ids)?;
    }
    let (frames_id, _) = ctx.item("sprite.frame_table", frames_table, SPRITES, vec![reached]);
    let count = frame_ids.iter().next_back().map_or(0, |last| u32::from(*last) + 1);
    let next_root = ctx.roots.by_address().range(frames_table + 1..).next().map(|(address, _)| *address).unwrap_or(crate::BASE + crate::ROM_SIZE);
    if frames_table + count * 4 > next_root {
        return Err(format!("frame table 0x{frames_table:08X}: frame {} reaches past the next referenced address 0x{next_root:08X}", count - 1));
    }
    ctx.count(frames_id, "largest frame id in its animations");
    let mut tiles = Vec::new();
    for index in 0..count {
        let pointer = le32(ctx.rom.claim(frames_table + index * 4, 4, "table.sprite_frames", frames_id)?, 0);
        if !ctx.rom.is_data(pointer) {
            return Err(format!("frame table 0x{frames_table:08X}[{index}] = 0x{pointer:08X} is not ROM data"));
        }
        tiles.extend(frame(ctx, pointer, format!("sprite.frame_table@0x{frames_table:08X}"))?);
    }
    ctx.set(frames_id, json!({ "frames": count, "animation_table": format!("0x{animations_table:08X}") }));
    Ok(tiles)
}

pub fn streamed_graphics(ctx: &Ctx, graphics: u32, palette: u32, tiles: &[(u32, u32)], reached: String) -> R<()> {
    let (id, new) = ctx.item("sprite.streamed_tiles", graphics, SPRITES, vec![reached.clone()]);
    let last = tiles.iter().map(|(first, count)| first + count).max().unwrap_or(0);
    for (first, count) in tiles {
        if *count > 0 {
            ctx.rom.claim(graphics + first * 32, count * 32, "sprite_tiles", id)?;
        }
    }
    let (palette_id, _) = ctx.item("sprite.palette", palette, SPRITES, vec![reached]);
    let colors = ctx.rom.claim(palette, 32, "palette", palette_id)?.to_vec();
    if new && last > 0 {
        let data = ctx.rom.peek(graphics, last * 32)?;
        ctx.count(id, "largest tile used by its frames");
        ctx.file(id, ".png", &tiles_4bpp(data, &colors))?;
        ctx.view(id, json!({ "t": "tiles", "bpp": 4, "tiles": ["rom", graphics, graphics + last * 32], "palette": ["rom", palette, palette + 32] }));
        ctx.set(id, json!({ "tiles": last, "palette": format!("0x{palette:08X}") }));
    }
    ctx.view(palette_id, json!({ "t": "palette", "colors": ["rom", palette, palette + 32] }));
    ctx.file(palette_id, ".png", &palette_swatch(&colors)).map(|_| ())
}

/// CreateSpriteFromTable(table, id, ...): 8-byte {frames, animations} entries, or 16-byte {frames, animations, graphics, palette} with flag 0x400000.
pub fn resource_table(ctx: &Ctx, table: u32, streamed: bool, reached: String, used: Option<u32>) -> R<()> {
    let stride = if streamed { 16 } else { 8 };
    let kind = if streamed { "table.sprite_resources_streamed" } else { "table.sprite_resources" };
    let (id, new) = ctx.item("sprite.resources", table, SPRITES, vec![reached]);
    if !new {
        return Ok(());
    }
    let (entries, source) = pointer_table(ctx, table, kind, id, stride)?;
    ctx.count(id, source);
    if let Some(resource) = used {
        if resource as usize >= entries.len() {
            return Err(format!("resource table 0x{table:08X}: C uses resource {resource}, table has {} by {source}", entries.len()));
        }
    }
    let mut listed = Vec::new();
    for entry in entries {
        let Some(entry) = entry else {
            listed.push(json!(null));
            continue;
        };
        let record = ctx.rom.peek(entry, stride)?;
        let (frames, animations) = (le32(record, 0), le32(record, 4));
        let tiles = sprite_set(ctx, frames, animations, format!("sprite.resources@0x{table:08X}"), &[])?;
        if streamed {
            streamed_graphics(ctx, le32(record, 8), le32(record, 12), &tiles, format!("sprite.resources@0x{table:08X}"))?;
        }
        listed.push(json!({ "frames": format!("0x{frames:08X}"), "animations": format!("0x{animations:08X}") }));
    }
    ctx.set(id, json!({ "stride": stride, "resources": listed }));
    Ok(())
}

/// gFieldActorSpriteDefinitions entries whose frame word is 0, which resource_table skips. InitializeFieldActorSprites and
/// GetFieldActorAnimationIndex index the table by FieldActor.model_id; RunCharacterDatabaseViewer reads word 0 of definitions[id]
/// for its ids and calls CreateSpriteFromTable (all 16 bytes) only when that word is nonzero.
pub fn field_actor_null_definitions(ctx: &Ctx, database_ids: &BTreeSet<u32>) -> R<()> {
    let names = super::battle_popups::enum_values("src/field/field_actor.h")?;
    let constant = |name: &str| names.get(name).copied().ok_or_else(|| format!("{name} is not in field_actor.h"));
    let mut models: BTreeSet<u32> = BTreeSet::new();
    models.insert(constant("FIELD_ACTOR_ALTERNATE_PALETTE_MODEL")?);
    for name in ["FIELD_TRANSPORT_GUSTAV_ACTOR", "FIELD_TRANSPORT_HOVER_CARGO_ACTOR", "FIELD_TRANSPORT_DRAGOON_NEST_ACTOR", "FIELD_TRANSPORT_LANDING_ACTOR"] {
        models.insert(constant(name)?);
    }
    for (_, data) in ctx.data_of("event_script") {
        for command in data["commands"].as_array().into_iter().flatten() {
            let arg = |index: usize| command["args"].get(index).and_then(|value| value.as_u64()).map(|value| value as u32);
            match (command["op"].as_str(), arg(0), arg(1)) {
                (Some("SPAWN_ACTOR" | "SPAWN_ACTOR_RELATIVE"), Some(actor), Some(model)) if actor <= FIELD_ACTOR_SPAWN_LAST_SLOT => {
                    models.insert(model);
                }
                (Some("SET_TRANSPORT_MODEL"), Some(model), _) => {
                    models.insert(model);
                }
                _ => {}
            }
        }
    }
    let table = FIELD_ACTOR_SPRITE_DEFINITIONS;
    let (id, new) = ctx.item("sprite.resources", table, SPRITES, ctx.roots.require(table)?);
    if new {
        return Err(format!("sprite.resources 0x{table:08X} was not read by the sprites port"));
    }
    let next_root = ctx.roots.by_address().range(table + 1..).next().map(|(address, _)| *address).ok_or("no root after the field actor sprite definitions")?;
    let count = (next_root - table) / 16;
    if let Some(bad) = models.iter().chain(database_ids).find(|&&model| model >= count) {
        return Err(format!("field actor model or database id {bad} is past the {count} field actor sprite definitions"));
    }
    let model_list: Vec<String> = models.iter().map(|model| model.to_string()).collect();
    let database_list: Vec<String> = database_ids.iter().map(|model| model.to_string()).collect();
    let no_actor = format!(
        "no CreateFieldActor source produces this model id: FieldActor.model_id is written only by CreateFieldActor (create_field_actor.c), whose model comes from SPAWN_ACTOR / SPAWN_ACTOR_RELATIVE byte 2 when byte 1 <= 0xC (event_spawn_actor.c, event_spawn_actor_relative.c), gFieldSaveState[2] (SET_TRANSPORT_MODEL operands, FIELD_TRANSPORT_*_ACTOR) or FIELD_ACTOR_ALTERNATE_PALETTE_MODEL (run_field.c recreates saved actors with their own saved model_id); over the walked event scripts these are {{{}}}",
        model_list.join(", ")
    );
    for entry in 0..count {
        let at = table + entry * 16;
        if le32(ctx.rom.peek(at, 4)?, 0) != 0 {
            continue;
        }
        if models.contains(&entry) {
            return Err(format!("field actor model {entry} has a null sprite definition at 0x{at:08X}; InitializeFieldActorSprites would read it"));
        }
        if database_ids.contains(&entry) {
            ctx.rom.claim(at, 4, "table.sprite_resources_streamed", id)?;
            ctx.unread(id, at + 4, 12, &format!("RunCharacterDatabaseViewer reads only the frame word of definitions[{entry}] and skips CreateSpriteFromTable because it is 0 (run_character_database_viewer.c); {no_actor}"))?;
        } else {
            ctx.unread(id, at, 16, &format!("{no_actor}; and {entry} is not a character database id ({{{}}}, run_character_database_viewer.c)", database_list.join(", ")))?;
        }
    }
    Ok(())
}

fn run(ctx: &Ctx) -> R<()> {
    let mut pairs: Vec<(u32, u32, String, Vec<u32>)> = Vec::new();
    let second = ctx.roots.calls(CREATE_SPRITE, 1);
    for reference in ctx.roots.calls(CREATE_SPRITE, 0) {
        if !ctx.rom.is_data(reference.address) {
            continue;
        }
        let mut animations: Vec<u32> = reference.args.get(1).and_then(|text| super::address_of(text, ctx.roots)).into_iter().collect();
        if animations.is_empty() {
            animations = second.iter().filter(|other| other.file == reference.file && other.line == reference.line && other.args == reference.args).map(|other| other.address).collect();
            animations.sort();
            animations.dedup();
        }
        let ids: Vec<u32> = reference.args.get(2).and_then(|text| literal(text)).into_iter().collect();
        for animation_table in animations {
            if ctx.rom.is_data(animation_table) {
                pairs.push((reference.address, animation_table, reference.location(), ids.clone()));
            }
        }
    }
    for (frames, animations, from, ids) in &pairs {
        sprite_set(ctx, *frames, *animations, from.clone(), ids)?;
    }

    for reference in ctx.roots.calls(CREATE_SPRITE_FROM_TABLE, 0) {
        if !ctx.rom.is_data(reference.address) {
            continue;
        }
        let Some(flags) = reference.args.get(7).and_then(|text| literal(text)) else { continue };
        let resource = reference.args.get(1).and_then(|text| literal(text));
        resource_table(ctx, reference.address, flags & STREAM_GRAPHICS != 0, reference.location(), resource)?;
    }
    let (table, reached) = (FIELD_ACTOR_SPRITE_DEFINITIONS, ctx.roots.require(FIELD_ACTOR_SPRITE_DEFINITIONS)?);
    resource_table(ctx, table, true, reached.join(" "), None)?;
    let _ = gray_tiles_4bpp;
    Ok(())
}
