//! LoadEventSpriteGraphics(resource_id): LoadSpriteGraphicsFromTable(0x087AF9D4, resource_id, ...) for the ids the walked event scripts pass.

use std::collections::{BTreeMap, BTreeSet};

use super::graphics::sprite_graphics;
use super::{literal, Port};
use crate::basis::Basis;
use crate::repo_root;
use crate::rom::R;
use crate::run::Ctx;

const EVENT_SPRITES: Basis = Basis::C(&[
    ("src/events/load_event_sprite_graphics.c", "bd7a50719d36790fcf3393b2304464ba9b11669b"),
    ("src/events/commands/event_load_sprite_graphics.c", "a08839d14d81be0786c3a3f8ae0c46ac99c09bea"),
    ("src/events/commands/event_show_world_map_structure_appearance.c", "c95a611325ad356555ea91b8430e5ac7ec9bf054"),
    ("src/events/event_script.h", "23f6268830cf2d663af58bc5552d8fd4105e85b2"),
    ("src/events/commands/event_set_world_map_structure.c", "fcab0278f74a0e0d3efd154d0a7b9bf9048c0c3e"),
    ("src/field/create_world_map_structure_sprite.c", "b4da01ff8ebf9023ec08b0297981d3a698836f03"),
    ("src/field/initialize_field_map_graphics.c", "a8a1520a4e455eeec02af498da83b04a3c7ba574"),
    ("src/events/scenes/play_arcadia_time_space_unit_destruction_scene.c", "087388ac61561ec98f9e7142623934ef5a15fc00"),
]);

pub const PORT: Port = Port { name: "event_sprites", bases: &[EVENT_SPRITES], run };

const EVENT_SPRITE_GRAPHICS_TABLE: u32 = 0x087A_F9D4;
const LOAD_SPRITE_GRAPHICS_FROM_TABLE: u32 = 0x0809_AA64;
const QUEUE_SPRITE_GRAPHICS_FROM_TABLE: u32 = 0x0809_AAA8;
/// EventShowWorldMapStructureAppearance loads resource 4 and structure_variant + 12.
const STRUCTURE_BASE_RESOURCE: u32 = 4;
const STRUCTURE_RESOURCE_OFFSET: u32 = 12;
/// CreateWorldMapStructureSprite loads world_structure_kind + 11; EventSetWorldMapStructure stores operand + 1 as the kind.
const SET_STRUCTURE_RESOURCE_OFFSET: u32 = 12;
/// Callers whose id is computed; their ids come from the event script operands above.
const COMPUTED_ID_CALLERS: [&str; 2] = ["src/events/load_event_sprite_graphics.c", "src/field/create_world_map_structure_sprite.c"];
/// Calls whose table argument is a register variable set to 0x087AF9D4, which the root scan does not resolve.
const REGISTER_TABLE_CALLS: [(&str, &str, u32); 2] = [
    ("src/events/scenes/play_arcadia_time_space_unit_destruction_scene.c", "LoadSpriteGraphicsFromTable(menu, 0x13, 0, 0);", 0x13),
    ("src/events/scenes/play_arcadia_time_space_unit_destruction_scene.c", "LoadSpriteGraphicsFromTable(menu, 7, 0x80, 2);", 7),
];

fn run(ctx: &Ctx) -> R<()> {
    let mut ids: BTreeMap<u32, String> = BTreeMap::new();
    for (address, data) in ctx.data_of("event_script") {
        for command in data["commands"].as_array().into_iter().flatten() {
            let first = command["args"].get(0).and_then(|value| value.as_u64()).map(|value| value as u32);
            let at = command["at"].as_str().unwrap_or("");
            match (command["op"].as_str(), first) {
                (Some("LOAD_SPRITE_GRAPHICS"), Some(id)) => {
                    ids.entry(id).or_insert_with(|| format!("event_script@0x{address:08X}:{at}"));
                }
                (Some("SHOW_WORLD_MAP_STRUCTURE_APPEARANCE"), Some(variant)) => {
                    ids.entry(STRUCTURE_BASE_RESOURCE).or_insert_with(|| format!("event_script@0x{address:08X}:{at}"));
                    ids.entry((variant + STRUCTURE_RESOURCE_OFFSET) & 0xFF).or_insert_with(|| format!("event_script@0x{address:08X}:{at}"));
                }
                (Some("SET_WORLD_MAP_STRUCTURE"), Some(operand)) => {
                    ids.entry((operand + SET_STRUCTURE_RESOURCE_OFFSET) & 0xFF).or_insert_with(|| format!("event_script@0x{address:08X}:{at}"));
                }
                _ => {}
            }
        }
    }
    let mut literal_ids = BTreeSet::new();
    for callee in [LOAD_SPRITE_GRAPHICS_FROM_TABLE, QUEUE_SPRITE_GRAPHICS_FROM_TABLE] {
        for reference in ctx.roots.calls(callee, 0).into_iter().filter(|reference| reference.address == EVENT_SPRITE_GRAPHICS_TABLE && !COMPUTED_ID_CALLERS.contains(&reference.file.as_str())) {
            literal_ids.insert(reference.args.get(1).and_then(|text| literal(text)).ok_or_else(|| format!("{}: table 0x{EVENT_SPRITE_GRAPHICS_TABLE:08X} with a non-literal id", reference.location()))?);
        }
    }
    for (path, call, id) in REGISTER_TABLE_CALLS {
        let source = std::fs::read_to_string(repo_root().join(path)).map_err(|error| format!("{path}: {error}"))?;
        if !source.contains(call) {
            return Err(format!("{path} no longer contains {call}"));
        }
        literal_ids.insert(id);
    }
    for (id, from) in &ids {
        sprite_graphics(ctx, EVENT_SPRITE_GRAPHICS_TABLE, *id, false, from.clone())?;
    }
    let (table, _) = ctx.item("table.compressed_sprite_graphics", EVENT_SPRITE_GRAPHICS_TABLE, super::graphics::SPRITE_GRAPHICS, vec![]);
    let end = ctx.roots.by_address().range(EVENT_SPRITE_GRAPHICS_TABLE + 1..).next().map(|(address, _)| *address).ok_or("no root after the event sprite graphics table")?;
    let produced: BTreeSet<u32> = ids.keys().copied().chain(literal_ids.iter().copied()).collect();
    let listed: Vec<String> = produced.iter().map(|id| id.to_string()).collect();
    for entry in (0..(end - EVENT_SPRITE_GRAPHICS_TABLE) / 8).filter(|entry| !produced.contains(entry)) {
        ctx.unread(table, EVENT_SPRITE_GRAPHICS_TABLE + entry * 8, 8, &format!(
            "entry {entry} is never indexed: the C indexes 0x087AF9D4 only with literal ids (play_*_scene.c, load_scene_background_graphics.c), LoadEventSpriteGraphics ids (LOAD_SPRITE_GRAPHICS operands of the walked event scripts; 4 and structure_variant + 12 in event_show_world_map_structure_appearance.c) and CreateWorldMapStructureSprite's world_structure_kind + 11 (kind = script operand + 1 from event_set_world_map_structure.c or event_show_world_map_structure_appearance.c, nonzero in initialize_field_map_graphics.c); these ids are {}",
            listed.join(", ")
        ))?;
    }
    Ok(())
}
