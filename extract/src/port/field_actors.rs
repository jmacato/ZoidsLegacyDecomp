//! Field actor tables: direction vectors, the held-key direction map, GetFieldActorAnimationIndex's index tables,
//! Pulse's emotion palettes, and the special animation sets UpdateFieldActorCommands plays from 0x087ADAF8.

use std::collections::{BTreeMap, BTreeSet};

use serde_json::{json, Value};

use super::{sprites, Port};
use crate::basis::Basis;
use crate::image::palette_swatch;
use crate::rom::{le32, R};
use crate::run::Ctx;

const ACTOR_H: (&str, &str) = ("src/field/field_actor.h", "a72a104ee20ea5fa6e428e29febcc0f71f58990d");
const COMMANDS_C: (&str, &str) = ("src/field/update_field_actor_commands.c", "3df812f3f4b4d94388c22f1c11369468ff7bd85e");
const SPRITES_C: (&str, &str) = ("src/field/initialize_field_actor_sprites.c", "4761ee93f1722e7e9dae073bb73271c1acbdf40a");
const FROM_TABLE_C: (&str, &str) = ("src/graphics/create_sprite_from_table.c", "10890981a20d144607c171ecaf63ea3a74f3e369");

const VECTORS: Basis = Basis::C(&[
    ("src/field/create_field_actor.c", "1be55f32be3cd126a512de430bf91198751cbbe7"),
    COMMANDS_C,
    ("src/field/update_field_actor_facing_and_velocity.c", "6960eced29a6f61b7734ffc5846e2c454ea62bc0"),
    SPRITES_C,
    ("src/game/modes/run_pause_menu.c", "6f7c8bd429aea0f010a68a77103b2d75a1a61252"),
    ACTOR_H,
]);
const INPUT: Basis = Basis::C(&[("src/field/update_player_field_actor_control.c", "b31a91dffae901880998bcf3ac5c936b6c509d46"), ACTOR_H]);
const ANIMATION: Basis = Basis::C(&[("src/field/get_field_actor_animation_index.c", "88ecb7366766953d8cd4d67098f978ab0b81d648"), ACTOR_H]);
const PULSE: Basis = Basis::C(&[
    SPRITES_C,
    ("src/events/commands/event_offer_pulse_emotion_growth.c", "64f7f8f426d05dba7060991896ae51c3052d7d33"),
    ("src/game/player_state.h", "dadeb1433712e28f47ef2910bb1c20a0d96da19b"),
    FROM_TABLE_C,
    ("src/graphics/queue_copy.c", "9f3482ebd43e0bafd38ec6fb0cc9bd5edfafa8b9"),
]);
const SPECIAL: Basis = Basis::C(&[COMMANDS_C, ACTOR_H, FROM_TABLE_C]);

pub const PORT: Port = Port { name: "field_actors", bases: &[VECTORS, INPUT, ANIMATION, PULSE, SPECIAL, sprites::SPRITES], run };

const DIRECTION_VECTORS: u32 = 0x087A_1B98;
const INPUT_DIRECTIONS: u32 = 0x087A_1BD8;
/// gFieldActorTwoWay/FourWay/EightWay/SingleDirectionAnimationIndices, each indexed by current_direction.
const ANIMATION_INDICES: [(u32, &str); 4] = [(0x087A_1BE8, "two_way"), (0x087A_1BF0, "four_way"), (0x087A_1BF8, "eight_way"), (0x087A_1C00, "single_direction")];
/// PULSE_FIELD_PALETTE_POINTERS_ROM, indexed by Pulse's palette_or_portrait_variant.
const PULSE_PALETTES: u32 = 0x087A_1C08;
/// FIELD_ACTOR_SPECIAL_ANIMATION_SETS_ROM and FIELD_ACTOR_SPECIAL_SPRITE_DEFINITIONS_ROM.
const SPECIAL_SETS: u32 = 0x087A_1C18;
const SPECIAL_SPRITES: u32 = 0x087A_DAF8;
/// FIELD_ACTOR_DIRECTION_COUNT (field_actor.h).
const DIRECTIONS: u32 = 8;
/// PULSE_EMOTION_COUNT (player_state.h).
const PULSE_EMOTIONS: u32 = 4;
/// sizeof(struct FieldActorSpecialAnimationSet) and its animations[8].
const SET_BYTES: u32 = 0x24;
const SET_SLOTS: u32 = 8;
const SET_END: u8 = 0xFF;
const EMPTY_SLOT: u8 = 0xFF;
/// CreateSpriteFromTable flags UpdateFieldActorCommands passes; 0x400000 selects 16-byte resource entries.
const SPECIAL_SPRITE_FLAGS: u32 = 0x0044_10D0;
const STREAM_GRAPHICS: u32 = 0x40_0000;
const SPRITE_PALETTE_BYTES: u32 = 0x20;

fn direction_vectors(ctx: &Ctx) -> R<()> {
    const KIND: &str = "table.field_actor_direction_vectors";
    let (id, _) = ctx.item(KIND, DIRECTION_VECTORS, VECTORS, ctx.roots.require(DIRECTION_VECTORS)?);
    let data = ctx.rom.claim(DIRECTION_VECTORS, DIRECTIONS * 8, KIND, id)?;
    let vectors: Vec<Value> = (0..DIRECTIONS as usize).map(|direction| json!({ "direction": direction, "x_fixed8": le32(data, direction * 8) as i32, "y_fixed8": le32(data, direction * 8 + 4) as i32 })).collect();
    ctx.count(id, "c_enum:FIELD_ACTOR_DIRECTION_COUNT (indexed by an actor's u8 direction)");
    ctx.set(id, json!({ "entry_bytes": 8, "vectors": vectors }));
    Ok(())
}

fn input_directions(ctx: &Ctx) -> R<()> {
    const KIND: &str = "table.field_actor_input_directions";
    let (id, _) = ctx.item(KIND, INPUT_DIRECTIONS, INPUT, ctx.roots.require(INPUT_DIRECTIONS)?);
    let data = ctx.rom.claim(INPUT_DIRECTIONS, 16, KIND, id)?.to_vec();
    for (keys, &direction) in data.iter().enumerate() {
        if direction != 0xFF && u32::from(direction) >= DIRECTIONS {
            return Err(format!("held-key direction map 0x{INPUT_DIRECTIONS:08X}[{keys}] = {direction}, past FIELD_ACTOR_DIRECTION_COUNT"));
        }
    }
    ctx.count(id, "c_mask:(gHeldKeys & 0xF0) >> 4");
    ctx.set(id, json!({ "entry_bytes": 1, "no_direction": 0xFF, "directions_by_dpad_bits": data }));
    Ok(())
}

fn animation_indices(ctx: &Ctx) -> R<()> {
    const KIND: &str = "table.field_actor_animation_indices";
    for (address, name) in ANIMATION_INDICES {
        let (id, _) = ctx.item(KIND, address, ANIMATION, ctx.roots.require(address)?);
        let data = ctx.rom.claim(address, DIRECTIONS, KIND, id)?.to_vec();
        ctx.count(id, "c_enum:FIELD_ACTOR_DIRECTION_COUNT (indexed by current_direction)");
        ctx.set(id, json!({ "table": name, "entry_bytes": 1, "animation_by_direction": data }));
    }
    Ok(())
}

/// InitializeFieldActorSprites (model 0x4B) and EventOfferPulseEmotionGrowth read entry palette_or_portrait_variant,
/// which EventOfferPulseEmotionGrowth sets to the chosen emotion (< PULSE_EMOTION_COUNT). Each entry is a 32-byte
/// palette: CreateSpriteFromTable's CpuFastSet of 8 words, or QueueCopy(..., 0x20).
fn pulse_palettes(ctx: &Ctx) -> R<()> {
    const KIND: &str = "table.pulse_field_palettes";
    let (id, _) = ctx.item(KIND, PULSE_PALETTES, PULSE, ctx.roots.require(PULSE_PALETTES)?);
    let mut palettes = Vec::new();
    for emotion in 0..PULSE_EMOTIONS {
        let pointer = le32(ctx.rom.claim(PULSE_PALETTES + emotion * 4, 4, KIND, id)?, 0);
        if !ctx.rom.is_data(pointer) {
            return Err(format!("Pulse palette pointer {emotion} = 0x{pointer:08X} is not ROM data"));
        }
        let (palette_id, new) = ctx.item("sprite.palette", pointer, PULSE, vec![format!("{KIND}@0x{PULSE_PALETTES:08X}[{emotion}]")]);
        let colors = ctx.rom.claim(pointer, SPRITE_PALETTE_BYTES, "palette", palette_id)?.to_vec();
        if new {
            ctx.count(palette_id, "c_literal_length:CpuFastSet 8 words / QueueCopy 0x20");
            ctx.file(palette_id, ".png", &palette_swatch(&colors))?;
            ctx.view(palette_id, json!({ "t": "palette", "colors": ["rom", pointer, pointer + SPRITE_PALETTE_BYTES] }));
        }
        palettes.push(json!({ "emotion": emotion, "palette": format!("0x{pointer:08X}") }));
    }
    ctx.count(id, "c_constant:PULSE_EMOTION_COUNT (EventOfferPulseEmotionGrowth stores the chosen emotion as palette_or_portrait_variant)");
    ctx.set(id, json!({ "entry_bytes": 4, "palettes": palettes }));
    Ok(())
}

/// UpdateFieldActorCommands, FIELD_ACTOR_CMD_PLAY_SPECIAL_ANIMATION: scan 36-byte sets for the actor's model until
/// a set whose model byte is 0xFF (set 0 is compared without that check); argument0 <= 7 picks animations[argument0],
/// skipped when its sprite_resource_id is 0xFF. A later set's slot is reached only when no earlier set for the same
/// model has that slot filled. The chosen slot is drawn with CreateSpriteFromTable(0x087ADAF8, resource, animation).
fn special_animations(ctx: &Ctx) -> R<()> {
    const KIND: &str = "table.field_actor_special_animations";
    let (sets_id, _) = ctx.item(KIND, SPECIAL_SETS, SPECIAL, ctx.roots.require(SPECIAL_SETS)?);
    let mut filled: BTreeSet<(u8, u32)> = BTreeSet::new();
    let mut used: BTreeMap<u8, BTreeSet<u32>> = BTreeMap::new();
    let mut sets = Vec::new();
    let mut end = None;
    for index in 0..=0xFFu32 {
        let at = SPECIAL_SETS + index * SET_BYTES;
        let model = ctx.rom.claim(at, 1, KIND, sets_id)?[0];
        if model == SET_END {
            if index == 0 {
                return Err(format!("special animation set 0 at 0x{at:08X} has model 0xFF, which the scan compares without the end check"));
            }
            ctx.unread(
                sets_id,
                at + 1,
                SET_BYTES - 1,
                &format!("set {index} (model 0xFF) after its model byte: UpdateFieldActorCommands ends the FIELD_ACTOR_CMD_PLAY_SPECIAL_ANIMATION scan at a set whose actor_model_id is 0xFF (src/field/update_field_actor_commands.c)"),
            )?;
            end = Some(index);
            break;
        }
        ctx.unread(
            sets_id,
            at + 1,
            3,
            &format!("set {index} reserved01[3] (struct FieldActorSpecialAnimationSet, src/field/field_actor.h): UpdateFieldActorCommands reads actor_model_id and animations[] only (src/field/update_field_actor_commands.c)"),
        )?;
        let mut slots = Vec::new();
        for slot in 0..SET_SLOTS {
            let entry = at + 4 + slot * 4;
            if filled.contains(&(model, slot)) {
                ctx.unread(
                    sets_id,
                    entry,
                    4,
                    &format!("set {index} animations[{slot}]: the scan for model {model} stops at an earlier set whose animations[{slot}].sprite_resource_id is not 0xFF (src/field/update_field_actor_commands.c)"),
                )?;
                slots.push(json!("unreachable: an earlier set for this model fills this slot"));
                continue;
            }
            let resource = ctx.rom.claim(entry, 1, KIND, sets_id)?[0];
            if resource == EMPTY_SLOT {
                ctx.unread(
                    sets_id,
                    entry + 1,
                    3,
                    &format!("set {index} animations[{slot}] after sprite_resource_id 0xFF: UpdateFieldActorCommands moves to the next set without reading animation_id, keep_secondary_sprite or use_zero_y_offset (src/field/update_field_actor_commands.c)"),
                )?;
                slots.push(Value::Null);
                continue;
            }
            let rest = ctx.rom.claim(entry + 1, 3, KIND, sets_id)?;
            filled.insert((model, slot));
            used.entry(resource).or_default().insert(u32::from(rest[0]));
            slots.push(json!({ "sprite_resource_id": resource, "animation_id": rest[0], "keep_secondary_sprite": rest[1], "use_zero_y_offset": rest[2] }));
        }
        sets.push(json!({ "model_id": model, "animations": slots }));
    }
    let Some(end) = end else { return Err(format!("special animation sets at 0x{SPECIAL_SETS:08X}: no model 0xFF within the u8 set index")) };
    ctx.count(sets_id, &format!("terminator:model 0xFF at set {end} (only its model byte is read)"));
    ctx.set(sets_id, json!({ "set_bytes": SET_BYTES, "sets": sets, "unread": "reserved01[3] of every set" }));

    if SPECIAL_SPRITE_FLAGS & STREAM_GRAPHICS == 0 {
        return Err("special sprites are not created with 16-byte resource entries".into());
    }
    const RESOURCES: &str = "table.sprite_resources_streamed";
    let (defs_id, _) = ctx.item("sprite.resources", SPECIAL_SPRITES, SPECIAL, ctx.roots.require(SPECIAL_SPRITES)?);
    let mut resources = Vec::new();
    for (&resource, animations) in &used {
        let entry = SPECIAL_SPRITES + u32::from(resource) * 16;
        let record = ctx.rom.claim(entry, 16, RESOURCES, defs_id)?.to_vec();
        let (frames, animation_table, graphics, palette) = (le32(&record, 0), le32(&record, 4), le32(&record, 8), le32(&record, 12));
        let from = format!("sprite.resources@0x{SPECIAL_SPRITES:08X}[{resource}]");
        let ids: Vec<u32> = animations.iter().copied().collect();
        let tiles = sprites::sprite_set(ctx, frames, animation_table, from.clone(), &ids)?;
        sprites::streamed_graphics(ctx, graphics, palette, &tiles, from)?;
        resources.push(json!({
            "resource": resource, "frames": format!("0x{frames:08X}"), "animations": format!("0x{animation_table:08X}"),
            "graphics": format!("0x{graphics:08X}"), "palette": format!("0x{palette:08X}"), "animation_ids": ids,
        }));
    }
    ctx.count(defs_id, &format!("c_index:sprite_resource_id of the reachable special animation slots (0x{SPECIAL_SETS:08X})"));
    ctx.set(defs_id, json!({ "stride": 16, "flags": format!("0x{SPECIAL_SPRITE_FLAGS:X}"), "resources": resources }));
    Ok(())
}

fn run(ctx: &Ctx) -> R<()> {
    direction_vectors(ctx)?;
    input_directions(ctx)?;
    animation_indices(ctx)?;
    pulse_palettes(ctx)?;
    special_animations(ctx)
}
