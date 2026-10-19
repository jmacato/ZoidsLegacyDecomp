//! LoadBattleStreakParticleGraphics (0x080CCF3C): the init callback 0x080CCF3D that RunBattleScene, PlayBattlePhalanxVolleyAnimation,
//! EventLoadBattleSceneModel and EventLoadBattleSceneModelFromPlayerPilot pass to CreateSpriteGroup. CreateSpriteGroup stores it at +0xAC
//! and UpdateSpriteGroups calls it once on a later frame, after each creator stored palette_variant (+0x8C) = the side's deck command
//! (gBattleState[0x27BE + side]) - BATTLE_PHALANX_FIRST_DECK_COMMAND. It loads LoadSpriteGraphicsFromTable(BATTLE_STREAK_GRAPHICS_TABLE_ROM,
//! (u8)(palette_variant + BATTLE_STREAK_RESOURCE_SLOT), ...).

use std::collections::BTreeSet;

use super::battle_popups::enum_values;
use super::graphics::sprite_graphics;
use super::Port;
use crate::basis::Basis;
use crate::rom::R;
use crate::run::Ctx;

const STREAK: Basis = Basis::C(&[
    ("src/battle/load_battle_streak_particle_graphics.c", "b7e22ba81abec96bc14bb5c5430a015cdf2910fc"),
    ("src/battle/battle_display.h", "ed9ae1d1b7b71e189ca7f207078675f82ea365b5"),
    ("src/graphics/create_sprite_group.c", "52a5f063631c9d8645a184d52278b9b716fb8c0b"),
    ("src/graphics/update_sprite_groups.c", "511c254adfd8cb331d214b6fb2883a7453cfefb8"),
    ("src/battle/is_battle_combined_attack_leader.c", "da06be27b64c80fa3dc5eb4a10062364692a6942"),
    ("src/game/modes/run_battle_scene.c", "1d8942aaaced975a60c680c0ca681e138bf98c69"),
    ("src/battle/play_battle_phalanx_volley_animation.c", "6797b03ee990a30b5273fda9c5051ca69344b1af"),
    ("src/events/commands/event_load_battle_scene_model.c", "766d78d0354e9d8569a3bdc9bb8b682972af6697"),
    ("src/events/commands/event_load_battle_scene_model_from_player_pilot.c", "b51949dfd2b9fbbff0af1ea291f59ea94a9e8471"),
    ("src/events/commands/event_request_battle_phalanx_volley.c", "135a36a150e3e96e702dbc44db2708e05ca22e01"),
    ("src/events/event_script.h", "23f6268830cf2d663af58bc5552d8fd4105e85b2"),
]);

pub const PORT: Port = Port { name: "battle_streak_particles", bases: &[STREAK], run };

/// table.battle_phalanx_palettes, whose port records the deck commands IsBattleCombinedAttackLeader accepts.
const PHALANX_PALETTES: u32 = 0x087A_2A10;

fn constant(names: &std::collections::BTreeMap<String, u32>, name: &str, file: &str) -> R<u32> {
    names.get(name).copied().ok_or_else(|| format!("{name} is not in {file}"))
}

fn run(ctx: &Ctx) -> R<()> {
    let display = enum_values("src/battle/battle_display.h")?;
    let slot = constant(&display, "BATTLE_STREAK_RESOURCE_SLOT", "battle_display.h")?;
    let table = constant(&display, "BATTLE_STREAK_GRAPHICS_TABLE_ROM", "battle_display.h")?;
    let first = constant(&display, "BATTLE_PHALANX_FIRST_DECK_COMMAND", "battle_display.h")?;
    let events = enum_values("src/events/event_script.h")?;
    let deck_add = constant(&events, "EVENT_PHALANX_OPCODE_TO_DECK_ADD", "event_script.h")?;

    let phalanx = ctx.data("table.battle_phalanx_palettes", PHALANX_PALETTES).ok_or("the phalanx tables were not ported first")?;
    let leader_commands: Vec<u32> = phalanx["deck_commands"].as_array().ok_or("table.battle_phalanx_palettes has no deck_commands")?.iter().filter_map(|value| value.as_u64()).map(|value| value as u32).collect();
    if leader_commands.is_empty() {
        return Err("table.battle_phalanx_palettes lists no deck commands".into());
    }
    let mut commands: BTreeSet<(u32, String)> = leader_commands.iter().map(|&command| (command, "IsBattleCombinedAttackLeader case (run_battle_scene.c, PlayBattlePhalanxVolleyAnimation)".to_string())).collect();
    for (address, data) in ctx.data_of("event_script") {
        for command in data["commands"].as_array().into_iter().flatten() {
            let Some(op) = command["op"].as_str() else { continue };
            if !(op.starts_with("REQUEST_") && op.ends_with("_PHALANX_VOLLEY")) {
                continue;
            }
            let opcode = constant(&events, &format!("EVENT_{op}"), "event_script.h")?;
            let stored = (opcode + deck_add) & 0xFF;
            commands.insert((stored, format!("event_script@0x{address:08X}:{} (gEventBattlePhalanxOpcode + EVENT_PHALANX_OPCODE_TO_DECK_ADD)", command["at"].as_str().unwrap_or(""))));
        }
    }
    let mut loaded = BTreeSet::new();
    for (command, from) in commands {
        let variant = command.wrapping_sub(first);
        let id = variant.wrapping_add(slot) & 0xFF;
        if loaded.insert(id) {
            sprite_graphics(ctx, table, id, false, format!("LoadBattleStreakParticleGraphics palette_variant {} ({from})", variant as i32))?;
        }
    }
    Ok(())
}
