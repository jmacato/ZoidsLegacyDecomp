//! Battle effect and battle scene tables: palette cycles, effect vectors and offsets, the phalanx volley tables,
//! unit world positions, combination formations, anchor points, zoid body sprites, equipment sprite graphics,
//! the scene skip palette cycle and the run_battle.c window text and link tag.

use std::collections::{BTreeMap, BTreeSet};

use serde_json::{json, Value};

use super::battle_animation::code_source;
use super::battle_popups::{calls, enum_values};
use super::{bios, graphics, sprites, text, Port};
use crate::basis::Basis;
use crate::image::palette_swatch;
use crate::rom::{le16, le32, R};
use crate::run::Ctx;
use crate::{repo_root, verify_c};

const BATTLE_ANIMATION_H: (&str, &str) = ("src/battle/battle_animation.h", "bb6342eaf90720323098ac43177cffe1af98aac3");
const BATTLE_DISPLAY_H: (&str, &str) = ("src/battle/battle_display.h", "ed9ae1d1b7b71e189ca7f207078675f82ea365b5");
const BATTLE_H: (&str, &str) = ("src/battle/battle.h", "a1dc0242af18cee1d3efcb0fee52c780fc7dcc98");
const QUEUE_COPY: (&str, &str) = ("src/graphics/queue_copy.c", "9f3482ebd43e0bafd38ec6fb0cc9bd5edfafa8b9");
const PROCESS_TRANSFER_QUEUE: (&str, &str) = ("src/graphics/process_transfer_queue.c", "bd3df7baf01ad4e5d00e43a241686352967859c7");
const CREATE_SPRITE_FROM_TABLE: (&str, &str) = ("src/graphics/create_sprite_from_table.c", "10890981a20d144607c171ecaf63ea3a74f3e369");
const CREATE_MIRRORED_SPRITE: (&str, &str) = ("src/graphics/create_mirrored_sprite_from_table.c", "7e29c39fccf33d12f177563a45bab42837a6bb8d");
const CREATE_BATTLE_ANIMATION_SPRITE: (&str, &str) = ("src/battle/create_battle_animation_sprite.c", "db2535631b290e8a435595614663b3d8dde2d75f");
const LOAD_BATTLE_ANIMATION_RESOURCES: (&str, &str) = ("src/battle/load_battle_animation_resources.c", "9184fcf8e856f39f3a1bec7d0fd546984f09ef13");
const UPDATE_SPRITES: (&str, &str) = ("src/graphics/update_sprites_and_build_oam.c", "88c4542b353249eb6d2ce2b1f47149a73220c791");
const RUN_BATTLE_SCENE: (&str, &str) = ("src/game/modes/run_battle_scene.c", "1d8942aaaced975a60c680c0ca681e138bf98c69");
const ZOID_BODY_SPRITES_H: (&str, &str) = ("src/graphics/zoid_body_sprites.h", "e82a2bc0f89fd31f0043d6543b84944668b2b5d4");

const PALETTE_CYCLES: Basis = Basis::C(&[
    BATTLE_ANIMATION_H,
    ("src/battle/update_battle_charged_cyan_beam_effect.c", "335f330148cb1f2adf273beae349ba5a41f82279"),
    ("src/battle/update_battle_fixed_x_palette_cycling_beam_effect.c", "dc84baf745428d4284534f5f283a18a4ca68bb78"),
    ("src/battle/update_battle_palette_cycling_beam_sine_impact_trail_effect.c", "91b2b1f642beb02271eec936f6b3e5d019af5a4b"),
    ("src/battle/update_battle_rotating_triangle_charge_palette_cycling_beam_effect.c", "afcb3e061b240f4a91e137a16267d48d263d5393"),
    CREATE_BATTLE_ANIMATION_SPRITE,
    CREATE_MIRRORED_SPRITE,
    CREATE_SPRITE_FROM_TABLE,
    LOAD_BATTLE_ANIMATION_RESOURCES,
    UPDATE_SPRITES,
    QUEUE_COPY,
    PROCESS_TRANSFER_QUEUE,
]);
const VECTORS: Basis = Basis::C(&[
    ("src/engine/math3d.h", "282baa448777ee923285ad67029bc5ebeaf801e3"),
    ("src/engine/transform_vector3s_fixed8.c", "d0aeece7c2a71b7d29566ccfa0db0dc1a6e07dfe"),
    ("src/battle/update_battle_rotating_triangle_effect.c", "c3c5243e97d3d7eb9f83c2ccc56fbe196bda4330"),
    ("src/battle/update_battle_rotating_triangle_charge_thin_beam_effect.c", "533fa2b033d6adee4ea0594ecf4b7b138aaaca11"),
    ("src/battle/update_battle_rotating_triangle_charge_palette_cycling_beam_effect.c", "afcb3e061b240f4a91e137a16267d48d263d5393"),
]);
const EFFECT_OFFSETS: Basis = Basis::C(&[
    BATTLE_ANIMATION_H,
    ("src/battle/update_battle_lightning_explosion_white_flash_effect.c", "1a16a625b990cb2f0af4d8bc1bc175dcf5d66ce0"),
    ("src/battle/update_battle_flame_arc_particle_and_ring_projectile_effect.c", "fd38bb6c1b06da716ba8ac2e935e72df91812f80"),
]);
const CAMERA: Basis = Basis::C(&[("src/battle/update_battle_animation_camera.c", "2f73f65cbe50aa5e87ab603c7c9025990489fc10")]);
const PHALANX: Basis = Basis::C(&[
    BATTLE_DISPLAY_H,
    ("src/battle/play_battle_phalanx_volley_animation.c", "6797b03ee990a30b5273fda9c5051ca69344b1af"),
    ("src/battle/is_battle_combined_attack_leader.c", "da06be27b64c80fa3dc5eb4a10062364692a6942"),
    RUN_BATTLE_SCENE,
    ("src/events/commands/event_play_battle_equipment_animation.c", "8c4c63141df86506b0cd5f2970ddf17e023280b5"),
    ("src/events/commands/event_play_battle_mounted_equipment_animation.c", "619ef3487a6112d3cad1e094fc3915447e5eebb8"),
    ("src/battle/deck_commands/execute_battle_deck_command.c", "37a53add94f1ecad5cfc247aa94cba36128bf8e2"),
    ("src/battle/present_queued_battle_effect_results.c", "99eba47e04cbfeaaf79cb86f01fb27ad98bbca1e"),
    ("src/battle/load_battle_streak_particle_graphics.c", "b7e22ba81abec96bc14bb5c5430a015cdf2910fc"),
    ("src/events/commands/event_request_battle_phalanx_volley.c", "135a36a150e3e96e702dbc44db2708e05ca22e01"),
    ("src/events/commands/event_load_battle_scene_model.c", "766d78d0354e9d8569a3bdc9bb8b682972af6697"),
    ("src/events/commands/event_load_battle_scene_model_from_player_pilot.c", "b51949dfd2b9fbbff0af1ea291f59ea94a9e8471"),
]);
const POSITIONS: Basis = Basis::C(&[
    BATTLE_H,
    ("src/battle/configure_battle_unit_sprites.c", "48e5fdafafbfff09dddb053254241c74df278d64"),
    ("src/battle/combinations/animate_battle_combination_arrival.c", "6f67afe4abf012a3897c6e226697015c265e53c4"),
    ("src/battle/combinations/animate_battle_combination_departure.c", "0fa371430f7543fb365c84121a99fce5e5bef5de"),
    ("src/battle/present_queued_battle_effect_results.c", "99eba47e04cbfeaaf79cb86f01fb27ad98bbca1e"),
    ("src/battle/start_battle_camera_transition.c", "e8e2269c9c9db0e66ffb551fc6e492c598c24bfd"),
    ("src/battle/update_battle_unit_sprite_motion.c", "22d24bce9f36faef76ea2b77f7d70ae7ac484d2f"),
]);
const FORMATIONS: Basis = Basis::C(&[
    ("src/battle/combinations/battle_combination.h", "bf0361dc52ef308a3077e865ff718ca3f30f38ac"),
    ("src/battle/combinations/is_battle_combination_formation_valid.c", "d197a3d725fe57456b784adf6967de10a283c586"),
    ("src/battle/combinations/is_player_combination_formation_valid.c", "b42aa2df946a10b0cdf77e784ff158ced0bf67a6"),
    ("src/battle/deck_commands/select_player_battle_deck_command.c", "821656e3eebc0c0aeb131ffb6048c8666901f8ae"),
]);
const ANCHORS: Basis = Basis::C(&[
    BATTLE_ANIMATION_H,
    BATTLE_DISPLAY_H,
    ("src/battle/create_battle_animation_group.c", "07c2436146ed8e6e15ddb2574067c3eac7b44e38"),
    RUN_BATTLE_SCENE,
    ("src/events/commands/event_load_battle_scene_model.c", "766d78d0354e9d8569a3bdc9bb8b682972af6697"),
    ("src/events/commands/event_load_battle_scene_model_from_player_pilot.c", "b51949dfd2b9fbbff0af1ea291f59ea94a9e8471"),
]);
const CURSOR_POSITIONS: Basis = Basis::C(&[
    ("src/battle/create_battle_animation_group.c", "07c2436146ed8e6e15ddb2574067c3eac7b44e38"),
    ("src/battle/create_battle_selection_cursor_sprites.c", "504a7b33b4af6b0a1f8589a15e27c592cc545955"),
    ("src/battle/position_battle_equipment_selection_cursor.c", "57aab01a211a1c11f64757fd02f42bd97405a0d2"),
    ("src/battle/select_battle_equipment_slot.c", "fdf11434a74f9e156e7d24687a9608fa299fb19f"),
    ("src/battle/load_battle_scene_zoid_graphics.c", "84565f0e04d66d1ed5e5b31ac2c4c9fecf83c74f"),
    ("src/battle/update_zoid_equipment_animation.c", "8e5be177d31ff7afc281673e69fb3f40b9fe34fc"),
    ("src/events/commands/event_create_battle_equipment_sprite.c", "2c7e4f4eca90d132349bbe665dd1b927aa33db4b"),
    ("src/ui/run_player_equipment_menu.c", "623d2c19dcb2e97417406203512ecfef3e128fe5"),
    ("src/ui/run_zoid_database_viewer.c", "8bd4d7d998f05ecc32b977fb9156793e9fbcbaa8"),
]);
const BODY_SPRITES: Basis = Basis::C(&[
    BATTLE_H,
    ZOID_BODY_SPRITES_H,
    ("src/graphics/initialize_berserk_fury_body_sprites.c", "17afa639cdc33a5486106fcad125437aec8097fe"),
    ("src/graphics/initialize_blitz_tiger_body_sprites.c", "1b66a06f3fe214d4ed1d07c8e81d9defd5d940da"),
    ("src/graphics/initialize_cannonry_molga_body_sprites.c", "2578fef9c71d5cd974327d27477ed8c7ccae11ef"),
    ("src/graphics/initialize_rr_pile_bunker_body_sprites.c", "f9635f61bdc85683f7dac797730a989db03081bc"),
    ("src/graphics/initialize_strum_fury_body_sprites.c", "ecc7aaabd960a475a2c5b1fe40908ba3bb94be39"),
    ("src/graphics/initialize_zero_schneider_body_sprites.c", "d8aacd2edcbc071cf473534a9014a6b261ee384e"),
    ("src/graphics/update_berserk_fury_body_sprites.c", "13739cb21baf524a6ad0c59551975d83db73ce3e"),
    ("src/graphics/update_blitz_tiger_body_sprites.c", "90a74070897fa9fd5d9fa944894041e5dcc1039b"),
    ("src/battle/start_zoid_equipment_animation.c", "12d37d5af768705762198e28bace916eed6c3ce0"),
    CREATE_MIRRORED_SPRITE,
    CREATE_SPRITE_FROM_TABLE,
]);
const EQUIPMENT_GRAPHICS: Basis = Basis::C(&[
    ("src/battle/load_battle_scene_zoid_graphics.c", "84565f0e04d66d1ed5e5b31ac2c4c9fecf83c74f"),
    ("src/events/commands/event_create_battle_equipment_sprite.c", "2c7e4f4eca90d132349bbe665dd1b927aa33db4b"),
    ("src/ui/run_equipment_database_viewer.c", "32a38808904a12ea224aaf40df87f21918342209"),
    ("src/ui/run_player_equipment_menu.c", "623d2c19dcb2e97417406203512ecfef3e128fe5"),
    ("src/ui/run_zoid_database_viewer.c", "8bd4d7d998f05ecc32b977fb9156793e9fbcbaa8"),
    ("src/graphics/load_sprite_graphics_from_table.c", "ea9d494504eeb3b592c2ef609590e7083cc46b7b"),
]);
const SKIP_PALETTES: Basis = Basis::C(&[("src/battle/run_battle_scene_skip_and_palette_task.c", "23307c9388b3f82542319ddc44b78fd9b861d1ec"), QUEUE_COPY, PROCESS_TRANSFER_QUEUE]);
const RUN_BATTLE: Basis = Basis::C(&[
    ("src/game/modes/run_battle.c", "133d0dd6c3a4eb5492f36d7d6b72b6d66d951ddb"),
    ("src/engine/link_transfer.h", "80ce1576fc1066b437c14e4b308a9ef8dbec3862"),
    ("src/engine/begin_link_send.c", "7951c6e62f68f1c2610097b8fd097068380b9155"),
    ("src/engine/begin_link_receive.c", "a02bd747b086614096e668022529c603499dc1c9"),
    ("src/engine/poll_link_send.c", "97e8fe91da9ac7615a4ad5f4ce925a9ad6bf75ca"),
    ("src/engine/poll_link_receive.c", "8f98578615109a70e3d4cb93a58a60b8a0d0e34d"),
]);

pub const PORT: Port = Port {
    name: "battle_effects",
    bases: &[
        PALETTE_CYCLES, VECTORS, EFFECT_OFFSETS, CAMERA, PHALANX, POSITIONS, FORMATIONS, ANCHORS, CURSOR_POSITIONS, BODY_SPRITES, EQUIPMENT_GRAPHICS,
        SKIP_PALETTES, RUN_BATTLE, text::WINDOW_TEXT, graphics::SPRITE_GRAPHICS, bios::LZ77_VRAM,
    ],
    run,
};

const CALLBACKS: u32 = 0x087A_2D1C;
const HEADERS: u32 = 0x087D_2338;
/// CreateBattleAnimationSprite: CreateMirroredSpriteFromTable(0x087ACDD8, gBattleAnimationResourceIds[resource_slot], animation_id, ...).
const BATTLE_SPRITE_RESOURCES: u32 = 0x087A_CDD8;

struct CycleUser {
    update: u32,
    source: &'static str,
    resource_slot: usize,
    animation: u32,
}

/// QueueCopy(&blocks[sequence[sprite->animation_step] * block_bytes], sprite palette bank, block_bytes) whenever the
/// sprite's frame_timer is 0. The sprite is CreateBattleAnimationSprite(group, resource_slot, animation, ...).
struct Cycle {
    sequence: u32,
    blocks: u32,
    block_bytes: u32,
    users: &'static [CycleUser],
}

const CYCLES: [Cycle; 2] = [
    Cycle {
        sequence: 0x087A_2AF0,
        blocks: 0x087A_2A50,
        block_bytes: 0x10,
        users: &[CycleUser { update: 0x080D_CEC0, source: "battle/update_battle_charged_cyan_beam_effect.c", resource_slot: 0, animation: 0 }],
    },
    Cycle {
        sequence: 0x087A_2CCC,
        blocks: 0x087A_2B0C,
        block_bytes: 0x20,
        users: &[
            CycleUser { update: 0x080D_F288, source: "battle/update_battle_fixed_x_palette_cycling_beam_effect.c", resource_slot: 0, animation: 1 },
            CycleUser { update: 0x080D_F090, source: "battle/update_battle_palette_cycling_beam_sine_impact_trail_effect.c", resource_slot: 0, animation: 1 },
            CycleUser { update: 0x080D_EB84, source: "battle/update_battle_rotating_triangle_charge_palette_cycling_beam_effect.c", resource_slot: 0, animation: 0 },
        ],
    },
];

/// TransformVector3sFixed8(matrix, &vector, out) inputs: struct Vector3s {s16 x, y, z}.
const VECTOR_ROOTS: [u32; 3] = [0x087A_2A48, 0x087A_2B04, 0x087A_2CEC];
const LIGHTNING_OFFSETS: u32 = 0x087A_2CF4;
const FLAME_LAUNCH_X: u32 = 0x087A_2D08;
const CAMERA_OFFSETS: u32 = 0x087A_2A24;
/// UpdateBattleAnimationCamera cases 5, 7, 8: table[counter >> 1] while counter <= 0x10.
const CAMERA_COUNTER_LAST: u32 = 0x10;
const PHALANX_PALETTES: u32 = 0x087A_2A10;
const PHALANX_SCROLL: u32 = 0x087A_2A1C;
const PHALANX_PALETTE_DESTINATION: u32 = 0x0500_0100;
/// EventRequestBattlePhalanxVolley stores its own opcode; the scene model commands store opcode + 0xCC as the deck command.
const EVENT_COMMAND_HANDLERS: u32 = 0x087A_190C;
const EVENT_REQUEST_PHALANX_VOLLEY: u32 = 0x080A_39FC;
const PHALANX_EVENT_OPCODE_BIAS: u32 = 0xCC;
const WORLD_POSITIONS: u32 = 0x087A_2790;
const WORLD_POSITIONS_Z: u32 = 0x087A_2798;
const BODY_ATTACHMENTS: u32 = 0x087E_B08C;
const BODY_ATTACHMENT_ALIASES: [u32; 2] = [0x087E_B09C, 0x087E_B09E];
/// CreateBattleAnimationGroup reads zoid points 0..5 ({s16 x, s16 y} at +0..+23); nothing reads +24..+31 of the 32-byte row.
const BODY_ATTACHMENT_POINTS: u32 = 6;
const CURSOR_POSITIONS_TABLE: u32 = 0x087E_C38C;
const CURSOR_POSITIONS_Y: u32 = 0x087E_C38E;
/// SelectBattleEquipmentSlot keeps the slot in 0..7; each zoid row is 8 {s16 x, s16 y} entries (zoid_id << 5).
const EQUIPMENT_SLOTS: u32 = 8;
const ROW_BYTES: u32 = 32;
const BODY_SPRITE_RESOURCES: u32 = 0x087A_A244;
const EQUIPMENT_SPRITE_GRAPHICS: u32 = 0x087A_BC6C;
/// The 0x087ABC6C readers accept item ids up to 0x64 (run_equipment_database_viewer.c, run_player_equipment_menu.c `<= 0x64`;
/// the others `item - 1 <= 0x63`) and load entry item * 2 (slot 0) or item * 2 + 1.
const EQUIPMENT_LAST_ITEM: u32 = 0x64;
/// Every 0x087ABC6C reader then calls CreateSpriteFromTable or CreateMirroredSpriteFromTable on this table with the same index,
/// which reads the frame and animation words with no null check.
const EQUIPMENT_SPRITE_RESOURCES: u32 = 0x087A_C2BC;
const SKIP_PALETTE_CYCLE: u32 = 0x083C_773C;
/// RunBattleSceneSkipAndPaletteTask: palette_frame runs 0..5 and back, QueueCopy((palette_frame << 5) + table, 0x05000080, 0x20).
const SKIP_PALETTE_LAST_FRAME: u32 = 5;
const RUN_BATTLE_WINDOW_TEXT: u32 = 0x0810_7058;

fn require(ctx: &Ctx, kind: &str, address: u32, basis: Basis) -> R<usize> {
    let reached = ctx.roots.require(address)?;
    Ok(ctx.item(kind, address, basis, reached).0)
}

fn next_root(ctx: &Ctx, after: u32) -> R<u32> {
    ctx.roots.by_address().range(after + 1..).next().map(|(address, _)| *address).ok_or_else(|| format!("no referenced address after 0x{after:08X}"))
}

fn owned_by(ctx: &Ctx, address: u32, length: u32, format: &str) -> R<()> {
    let owners = ctx.rom.owners();
    for offset in address - crate::BASE..address - crate::BASE + length {
        let name = ctx.rom.format_name(owners[offset as usize]);
        if name != format {
            return Err(format!("0x{:08X} is {name:?}, expected {format}", crate::BASE + offset));
        }
    }
    Ok(())
}

fn hex(value: u32) -> String {
    format!("0x{value:08X}")
}

fn s16(data: &[u8], offset: usize) -> i16 {
    le16(data, offset) as i16
}

fn header_constant(names: &BTreeMap<String, u32>, name: &str, file: &str) -> R<u32> {
    names.get(name).copied().ok_or_else(|| format!("{name} is not in {file}"))
}

/// Commands of a sprite animation already read by the sprites port: {s16 frame, s16 duration} until frame -1.
fn animation_length(ctx: &Ctx, animations_table: u32, animation: u32) -> R<u32> {
    owned_by(ctx, animations_table + animation * 4, 4, "table.sprite_animations")?;
    let pointer = le32(ctx.rom.peek(animations_table + animation * 4, 4)?, 0);
    let mut count = 0;
    loop {
        let at = pointer + count * 4;
        owned_by(ctx, at, 2, "sprite_animation")?;
        if s16(ctx.rom.peek(at, 2)?, 0) == -1 {
            break;
        }
        count += 1;
    }
    if count == 0 {
        return Err(format!("sprite animation 0x{pointer:08X} has no commands"));
    }
    Ok(count)
}

/// The battle animation sprite resource entry for `resource`, as the sprites port read it: (frames, animations).
fn battle_sprite_resource(ctx: &Ctx, resource: u32, reached: String, animations: &[u32]) -> R<(u32, u32)> {
    let entry = BATTLE_SPRITE_RESOURCES + resource * 8;
    owned_by(ctx, entry, 8, "table.sprite_resources")?;
    let record = ctx.rom.peek(entry, 8)?;
    let (frames, animation_table) = (le32(record, 0), le32(record, 4));
    sprites::sprite_set(ctx, frames, animation_table, reached, animations)?;
    Ok((frames, animation_table))
}

/// Callback kinds whose init or update function is `function`, with their headers' resource ids, from the battle_animation port.
fn kinds_for(ctx: &Ctx, function: u32) -> R<Vec<(u64, Vec<(u64, Vec<i64>)>)>> {
    let callbacks = ctx.data("table.battle_animation_callbacks", CALLBACKS).ok_or("the battle_animation port did not read the callback table")?;
    let headers = ctx.data("table.battle_animation_resource_headers", HEADERS).ok_or("the battle_animation port did not read the resource headers")?;
    let by_index: BTreeMap<u64, &Value> = headers["headers"].as_array().ok_or("no headers")?.iter().map(|header| (header["index"].as_u64().unwrap(), header)).collect();
    let mut out = Vec::new();
    for kind in callbacks["kinds"].as_array().ok_or("no callback kinds")? {
        let pointer = hex(function | 1);
        if kind["init"].as_str() != Some(pointer.as_str()) && kind["update"].as_str() != Some(pointer.as_str()) {
            continue;
        }
        let mut listed = Vec::new();
        for index in kind["headers"].as_array().ok_or("no headers for a kind")? {
            let index = index.as_u64().ok_or("bad header index")?;
            let header = by_index.get(&index).ok_or_else(|| format!("header {index} was not read"))?;
            let resources = header["resource_ids"].as_array().ok_or("no resource ids")?.iter().map(|value| value.as_i64().unwrap()).collect();
            listed.push((index, resources));
        }
        out.push((kind["kind"].as_u64().ok_or("bad kind")?, listed));
    }
    Ok(out)
}

fn palette_cycles(ctx: &Ctx) -> R<()> {
    let regions = verify_c::regions(&repo_root().join("regions.txt"))?;
    for cycle in &CYCLES {
        let sequence_id = require(ctx, "table.battle_palette_cycle_sequence", cycle.sequence, PALETTE_CYCLES)?;
        let blocks_id = require(ctx, "battle_effect.palette_cycle_blocks", cycle.blocks, PALETTE_CYCLES)?;
        let mut steps = 0;
        let mut users = Vec::new();
        for user in cycle.users {
            let source = code_source(&regions, user.update | 1)?;
            if source != user.source {
                return Err(format!("func_{:08X} is in {source}, the port expects {}", user.update, user.source));
            }
            let kinds = kinds_for(ctx, user.update)?;
            if kinds.is_empty() {
                users.push(json!({ "update": hex(user.update), "source": user.source, "callback_kinds": [] }));
                continue;
            }
            let mut uses = Vec::new();
            for (kind, headers) in &kinds {
                for (index, resources) in headers {
                    let resource = *resources.get(user.resource_slot).ok_or_else(|| format!("header {index} (kind {kind}) has no resource slot {}", user.resource_slot))?;
                    let resource = u32::try_from(resource).map_err(|_| format!("header {index}: resource {resource}"))?;
                    let reached = format!("{}@{}", "table.battle_palette_cycle_sequence", hex(cycle.sequence));
                    let (_, animation_table) = battle_sprite_resource(ctx, resource, reached, &[user.animation])?;
                    let length = animation_length(ctx, animation_table, user.animation)?;
                    if user.animation != 0 && animation_length(ctx, animation_table, 0)? != length {
                        return Err(format!("resource {resource}: animations {} and 0 differ in length; the end mode 0x30 switch to animation 0 would change the step bound", user.animation));
                    }
                    steps = steps.max(length);
                    uses.push(json!({ "callback_kind": kind, "header": index, "resource": resource, "animation": user.animation, "commands": length }));
                }
            }
            users.push(json!({ "update": hex(user.update), "source": user.source, "uses": uses }));
        }
        if steps == 0 {
            return Err(format!("palette cycle 0x{:08X}: no reached callback uses it", cycle.sequence));
        }
        let sequence = ctx.rom.claim(cycle.sequence, steps, "table.battle_palette_cycle_sequence", sequence_id)?.to_vec();
        ctx.count(sequence_id, "c_index:sprite animation_step, below the command count of the animation each user's sprite plays");
        let blocks = u32::from(*sequence.iter().max().unwrap()) + 1;
        let colors = ctx.rom.claim(cycle.blocks, blocks * cycle.block_bytes, "palette", blocks_id)?.to_vec();
        ctx.count(blocks_id, "c_index:largest sequence value + 1");
        ctx.file(blocks_id, ".png", &palette_swatch(&colors))?;
        ctx.view(blocks_id, json!({ "t": "palette", "colors": ["rom", cycle.blocks, cycle.blocks + blocks * cycle.block_bytes] }));
        ctx.set(sequence_id, json!({ "steps": steps, "blocks": hex(cycle.blocks), "block_bytes": cycle.block_bytes, "sequence": sequence, "users": users }));
        ctx.set(blocks_id, json!({ "blocks": blocks, "block_bytes": cycle.block_bytes, "sequence": hex(cycle.sequence) }));
    }
    Ok(())
}

fn vectors(ctx: &Ctx) -> R<()> {
    for address in VECTOR_ROOTS {
        let id = require(ctx, "battle_effect.vector3s", address, VECTORS)?;
        let data = ctx.rom.claim(address, 6, "vector3s", id)?;
        ctx.count(id, "c_struct:struct Vector3s (math3d.h), input of TransformVector3sFixed8");
        ctx.set(id, json!({ "x": s16(data, 0), "y": s16(data, 2), "z": s16(data, 4) }));
    }
    Ok(())
}

fn effect_offsets(ctx: &Ctx) -> R<()> {
    let names = enum_values("src/battle/battle_animation.h")?;
    let launch_positions = header_constant(&names, "BATTLE_FLAME_ARC_PARTICLE_RING_LAUNCH_POSITION_COUNT", "battle_animation.h")?;
    let flame_id = require(ctx, "table.battle_flame_arc_launch_x_offsets", FLAME_LAUNCH_X, EFFECT_OFFSETS)?;
    let flame = ctx.rom.claim(FLAME_LAUNCH_X, launch_positions, "table.battle_flame_arc_launch_x_offsets", flame_id)?.to_vec();
    ctx.count(flame_id, "c_enum:BATTLE_FLAME_ARC_PARTICLE_RING_LAUNCH_POSITION_COUNT (the C index is (random * 17) >> 15; the random routine is not decompiled)");
    ctx.set(flame_id, json!({ "x_offsets": flame }));

    let last_update = header_constant(&names, "BATTLE_LIGHTNING_EXPLOSION_LAST_EMISSION_UPDATE", "battle_animation.h")?;
    let pairs = last_update / 4 + 1;
    if pairs != header_constant(&names, "BATTLE_LIGHTNING_EXPLOSION_COUNT", "battle_animation.h")? {
        return Err("BATTLE_LIGHTNING_EXPLOSION_COUNT is not LAST_EMISSION_UPDATE / 4 + 1".into());
    }
    let lightning_id = require(ctx, "table.battle_lightning_explosion_offsets", LIGHTNING_OFFSETS, EFFECT_OFFSETS)?;
    let own_pairs = (FLAME_LAUNCH_X - LIGHTNING_OFFSETS) / 4;
    let mut offsets = Vec::new();
    let mut overlapping = Vec::new();
    for index in 0..pairs {
        let at = LIGHTNING_OFFSETS + index * 4;
        let data = if index < own_pairs {
            ctx.rom.claim(at, 4, "table.battle_lightning_explosion_offsets", lightning_id)?
        } else {
            owned_by(ctx, at, 4, "table.battle_flame_arc_launch_x_offsets")?;
            overlapping.push(index);
            ctx.rom.peek(at, 4)?
        };
        offsets.push(json!({ "x": le16(data, 0), "y": le16(data, 2), "at": hex(at) }));
    }
    ctx.count(lightning_id, "c_enum:BATTLE_LIGHTNING_EXPLOSION_LAST_EMISSION_UPDATE / 4 + 1 (index = explosion_updates >> 2)");
    ctx.set(lightning_id, json!({
        "offsets": offsets,
        "pairs_read_from_flame_arc_table": overlapping,
        "note": "the C reads pair 5 from the first 4 bytes of gBattleFlameArcParticleLaunchXOffsets (comment in the C); those bytes are claimed by the flame table",
    }));
    Ok(())
}

fn camera(ctx: &Ctx) -> R<()> {
    let id = require(ctx, "table.battle_animation_camera_offsets", CAMERA_OFFSETS, CAMERA)?;
    let count = CAMERA_COUNTER_LAST / 2 + 1;
    let data = ctx.rom.claim(CAMERA_OFFSETS, count * 4, "table.battle_animation_camera_offsets", id)?;
    ctx.count(id, "c_guard:counter <= 0x10, index counter >> 1 (update_battle_animation_camera.c cases 5, 7, 8)");
    ctx.set(id, json!({ "values": data.chunks(4).map(|word| le32(word, 0) as i32).collect::<Vec<_>>() }));
    Ok(())
}

/// PlayBattlePhalanxVolleyAnimation indexes both tables with persistent_command_ids[side] - BATTLE_PHALANX_FIRST_DECK_COMMAND.
/// run_battle_scene.c calls it only after IsBattleCombinedAttackLeader matched command 46, 47 or 48.
fn phalanx(ctx: &Ctx) -> R<()> {
    let first = header_constant(&enum_values("src/battle/battle_display.h")?, "BATTLE_PHALANX_FIRST_DECK_COMMAND", "battle_display.h")?;
    let leader = std::fs::read_to_string(repo_root().join("src/battle/is_battle_combined_attack_leader.c")).map_err(|error| error.to_string())?;
    let cases: Vec<u32> = leader.lines().filter_map(|line| line.trim().strip_prefix("case ")?.strip_suffix(':')?.parse().ok()).collect();
    let commands: BTreeSet<u32> = cases.iter().copied().collect();
    if commands != [46, 47, 48].into_iter().collect() {
        return Err(format!("is_battle_combined_attack_leader.c cases are {cases:?}, the port expects 46, 47, 48"));
    }
    let indices: Vec<u32> = commands.iter().map(|command| command - first).collect();
    let count = indices.iter().max().unwrap() + 1;
    let palettes_id = require(ctx, "table.battle_phalanx_palettes", PHALANX_PALETTES, PHALANX)?;
    let scroll_id = require(ctx, "table.battle_phalanx_vertical_scroll", PHALANX_SCROLL, PHALANX)?;
    let mut palettes = Vec::new();
    for index in 0..count {
        let pointer = le32(ctx.rom.claim(PHALANX_PALETTES + index * 4, 4, "table.battle_phalanx_palettes", palettes_id)?, 0);
        if !ctx.rom.is_data(pointer) {
            return Err(format!("phalanx palette {index}: 0x{pointer:08X} is not ROM data"));
        }
        let from = format!("table.battle_phalanx_palettes@{}[{index}]", hex(PHALANX_PALETTES));
        graphics::lz77_item(ctx, pointer, true, bios::LZ77_VRAM, "palette", Some(PHALANX_PALETTE_DESTINATION), vec![from])?;
        palettes.push(hex(pointer));
    }
    let handlers_end = next_root(ctx, EVENT_COMMAND_HANDLERS)?;
    let mut event_ops = Vec::new();
    for op in 0..(handlers_end - EVENT_COMMAND_HANDLERS) / 4 {
        let handler = le32(ctx.rom.peek(EVENT_COMMAND_HANDLERS + op * 4, 4)?, 0);
        if handler & !1 == EVENT_REQUEST_PHALANX_VOLLEY {
            let command = (op + PHALANX_EVENT_OPCODE_BIAS) & 0xFF;
            if !commands.contains(&command) {
                return Err(format!("event opcode {op} requests a phalanx volley as deck command {command}, outside {commands:?}"));
            }
            event_ops.push(op);
        }
    }
    if event_ops.is_empty() {
        return Err("no event opcode runs EventRequestBattlePhalanxVolley".into());
    }
    let display = enum_values("src/battle/battle_display.h")?;
    let streak_graphics = header_constant(&display, "BATTLE_STREAK_GRAPHICS_TABLE_ROM", "battle_display.h")?;
    let streak_slot = header_constant(&display, "BATTLE_STREAK_RESOURCE_SLOT", "battle_display.h")?;
    for &index in &indices {
        graphics::sprite_graphics(ctx, streak_graphics, streak_slot + index, false, "load_battle_streak_particle_graphics.c: BATTLE_STREAK_RESOURCE_SLOT + palette_variant (phalanx deck command - BATTLE_PHALANX_FIRST_DECK_COMMAND)".to_string())?;
    }
    let scroll = ctx.rom.claim(PHALANX_SCROLL, count * 2, "table.battle_phalanx_vertical_scroll", scroll_id)?;
    let source = "c_switch:IsBattleCombinedAttackLeader cases 46, 47, 48 minus BATTLE_PHALANX_FIRST_DECK_COMMAND (run_battle_scene.c path); the event command paths only check the id is nonzero";
    ctx.count(palettes_id, source);
    ctx.count(scroll_id, source);
    ctx.set(palettes_id, json!({ "deck_commands": commands, "lz77_palettes": palettes, "destination": hex(PHALANX_PALETTE_DESTINATION) }));
    ctx.set(scroll_id, json!({ "deck_commands": commands, "background_y_scroll": scroll.chunks(2).map(|half| le16(half, 0)).collect::<Vec<_>>() }));
    Ok(())
}

fn world_positions(ctx: &Ctx) -> R<()> {
    let names = enum_values("src/battle/battle.h")?;
    let sides = header_constant(&names, "BATTLE_SIDE_COUNT", "battle.h")?;
    let units = header_constant(&names, "BATTLE_ACTIVE_UNIT_COUNT", "battle.h")?;
    ctx.roots.require(WORLD_POSITIONS_Z)?;
    if WORLD_POSITIONS_Z != WORLD_POSITIONS + 8 {
        return Err("the z column root is not +8 of the position table".into());
    }
    let id = require(ctx, "table.battle_unit_world_positions", WORLD_POSITIONS, POSITIONS)?;
    let mut rows = Vec::new();
    for index in 0..sides * units {
        let data = ctx.rom.claim(WORLD_POSITIONS + index * 12, 12, "table.battle_unit_world_positions", id)?;
        rows.push(json!({ "side": index / units, "unit": index % units, "x": le32(data, 0) as i32, "y": le32(data, 4) as i32, "z": le32(data, 8) as i32 }));
    }
    ctx.count(id, "c_enum:BATTLE_SIDE_COUNT * BATTLE_ACTIVE_UNIT_COUNT (index side * 6 + unit)");
    ctx.set(id, json!({ "record_bytes": 12, "positions": rows }));
    Ok(())
}

fn formations(ctx: &Ctx) -> R<()> {
    let names = enum_values("src/battle/combinations/battle_combination.h")?;
    let table = header_constant(&names, "BATTLE_COMBINATION_FORMATION_TABLE_ROM", "battle_combination.h")?;
    let recipes = header_constant(&names, "BATTLE_COMBINATION_RECIPE_COUNT", "battle_combination.h")?;
    let models = header_constant(&names, "BATTLE_COMBINATION_MODEL_COUNT", "battle_combination.h")?;
    let id = require(ctx, "table.battle_combination_formations", table, FORMATIONS)?;
    let record = 1 + models;
    let mut rows = Vec::new();
    for recipe in 0..recipes {
        let data = ctx.rom.claim(table + recipe * record, record, "table.battle_combination_formations", id)?;
        let listed: Vec<u8> = data[1..].iter().copied().take_while(|model| *model != 0).collect();
        rows.push(json!({ "recipe": recipe, "mode": data[0], "model_ids": listed, "record": data.to_vec() }));
    }
    ctx.count(id, "c_enum:BATTLE_COMBINATION_RECIPE_COUNT; whole struct BattleCombinationFormationRule records (the model scans stop at the first 0)");
    ctx.set(id, json!({ "record_bytes": record, "recipes": rows }));
    Ok(())
}

fn zoid_rows(ctx: &Ctx, table: u32, aliases: &[u32], expected_end: u32) -> R<u32> {
    for &alias in aliases {
        ctx.roots.require(alias)?;
    }
    let end = next_root(ctx, aliases.iter().copied().max().unwrap_or(table))?;
    if end != expected_end || (end - table) % ROW_BYTES != 0 {
        return Err(format!("zoid row table 0x{table:08X}: next referenced address 0x{end:08X} is not 0x{expected_end:08X} or not whole 32-byte rows"));
    }
    Ok((end - table) / ROW_BYTES)
}

fn anchors(ctx: &Ctx) -> R<()> {
    let rows = zoid_rows(ctx, BODY_ATTACHMENTS, &BODY_ATTACHMENT_ALIASES, CURSOR_POSITIONS_TABLE)?;
    let id = require(ctx, "table.battle_body_attachment_points", BODY_ATTACHMENTS, ANCHORS)?;
    let mut listed = Vec::new();
    for zoid in 0..rows {
        let data = ctx.rom.claim(BODY_ATTACHMENTS + zoid * ROW_BYTES, BODY_ATTACHMENT_POINTS * 4, "table.battle_body_attachment_points", id)?;
        ctx.unread(id, BODY_ATTACHMENTS + zoid * ROW_BYTES + BODY_ATTACHMENT_POINTS * 4, ROW_BYTES - BODY_ATTACHMENT_POINTS * 4, "row bytes after point 5: every C read of D_087EB08C is an s16 at row +0x0..+0x16 (CreateBattleAnimationGroup anchor points 0..5 in create_battle_animation_group.c; +4, +6 and +0x10/+0x12 through 0x087EB09C/0x087EB09E in run_battle_scene.c; +4, +6, +0x10, +0x12 in event_load_battle_scene_model.c and event_load_battle_scene_model_from_player_pilot.c)")?;
        listed.push(data.chunks(4).map(|point| json!([s16(point, 0), s16(point, 2)])).collect::<Vec<_>>());
    }
    ctx.count(id, "next_root (zoid_id is a runtime u8 with no C bound; 152 rows = model ids 0..151 of build_unlocked_zoid_model_selection.c); points 0..5 per row from CreateBattleAnimationGroup");
    ctx.set(id, json!({ "row_bytes": ROW_BYTES, "points_read": BODY_ATTACHMENT_POINTS, "rows": listed }));

    let cursor_rows = zoid_rows(ctx, CURSOR_POSITIONS_TABLE, &[CURSOR_POSITIONS_Y], 0x087E_D68C)?;
    if cursor_rows != rows {
        return Err(format!("anchor tables have {rows} and {cursor_rows} zoid rows"));
    }
    let id = require(ctx, "table.battle_equipment_cursor_positions", CURSOR_POSITIONS_TABLE, CURSOR_POSITIONS)?;
    let mut listed = Vec::new();
    for zoid in 0..cursor_rows {
        let data = ctx.rom.claim(CURSOR_POSITIONS_TABLE + zoid * ROW_BYTES, EQUIPMENT_SLOTS * 4, "table.battle_equipment_cursor_positions", id)?;
        listed.push(data.chunks(4).map(|point| json!([s16(point, 0), s16(point, 2)])).collect::<Vec<_>>());
    }
    ctx.count(id, "next_root (zoid_id is a runtime u8 with no C bound; 152 rows = model ids 0..151 of build_unlocked_zoid_model_selection.c); 8 slots per row from SelectBattleEquipmentSlot's 0..7");
    ctx.set(id, json!({ "row_bytes": ROW_BYTES, "slots": EQUIPMENT_SLOTS, "rows": listed }));
    Ok(())
}

/// A call argument as a value: a literal or an enum name.
fn argument(text: &str, names: &BTreeMap<String, u32>) -> Option<u32> {
    let text = super::strip_casts(text);
    super::literal(text).or_else(|| names.get(text).copied())
}

fn body_sprites(ctx: &Ctx) -> R<()> {
    let mut names = enum_values("src/battle/battle.h")?;
    names.extend(enum_values("src/graphics/zoid_body_sprites.h")?);
    let mut used: BTreeMap<u32, BTreeSet<u32>> = BTreeMap::new();
    let mut sources: BTreeMap<u32, BTreeSet<String>> = BTreeMap::new();
    for zoid in ["berserk_fury", "blitz_tiger", "cannonry_molga", "rr_pile_bunker", "strum_fury", "zero_schneider"] {
        let path = format!("src/graphics/initialize_{zoid}_body_sprites.c");
        let source = std::fs::read_to_string(repo_root().join(&path)).map_err(|error| format!("{path}: {error}"))?;
        if !source.contains("asm(\"D_087AA244\")") {
            return Err(format!("{path} does not declare D_087AA244"));
        }
        let created = calls(&path, "CreateMirroredSpriteFromTable")?;
        if created.is_empty() {
            return Err(format!("{path} creates no sprite"));
        }
        let mut resources = BTreeSet::new();
        for args in &created {
            let resource = args.get(1).and_then(|text| argument(text, &names));
            let animation = args.get(2).and_then(|text| argument(text, &names));
            let flags: Vec<u32> = args.get(7).map_or(Vec::new(), |text| text.split(|c: char| !c.is_ascii_alphanumeric()).filter(|token| token.starts_with("0x")).filter_map(super::literal).collect());
            match (resource, animation) {
                (Some(resource), Some(animation)) if !flags.is_empty() && flags.iter().all(|value| value & 0x40_0000 == 0) => {
                    used.entry(resource).or_default().insert(animation);
                    sources.entry(resource).or_default().insert(path.clone());
                    resources.insert(resource);
                }
                _ => return Err(format!("{path}: CreateMirroredSpriteFromTable({}) is not a literal resource and animation with 8-byte entries", args.join(", "))),
            }
        }
        if resources.len() != 1 {
            return Err(format!("{path} creates sprites from {} resources", resources.len()));
        }
        let resource = *resources.iter().next().unwrap();
        let update = format!("src/graphics/update_{zoid}_body_sprites.c");
        if !repo_root().join(&update).exists() {
            continue;
        }
        for args in calls(&update, "SetSpriteAnimation")? {
            let Some(text) = args.get(1) else { continue };
            if let Some(animation) = argument(text, &names) {
                used.entry(resource).or_default().insert(animation);
                sources.entry(resource).or_default().insert(update.clone());
            } else if text.ends_with("animation.berserk_fury_animation_id") {
                let start = "src/battle/start_zoid_equipment_animation.c";
                let assigned = std::fs::read_to_string(repo_root().join(start)).map_err(|error| error.to_string())?;
                let mut found = 0;
                for line in assigned.lines().filter(|line| line.contains("berserk_fury_animation_id) =")) {
                    let value = line.split('=').nth(1).map(|rest| rest.trim().trim_end_matches(';').trim());
                    let animation = value.and_then(|value| argument(value, &names)).ok_or_else(|| format!("{start}: cannot read {line:?}"))?;
                    used.entry(resource).or_default().insert(animation);
                    found += 1;
                }
                if found == 0 {
                    return Err(format!("{start} assigns no berserk_fury_animation_id"));
                }
                sources.entry(resource).or_default().insert(start.into());
            } else {
                return Err(format!("{update}: SetSpriteAnimation({}) has an animation the port cannot resolve", args.join(", ")));
            }
        }
    }
    let id = require(ctx, "sprite.resources", BODY_SPRITE_RESOURCES, BODY_SPRITES)?;
    let mut listed = BTreeMap::new();
    for (&resource, animations) in &used {
        let entry = ctx.rom.claim(BODY_SPRITE_RESOURCES + resource * 8, 8, "table.sprite_resources", id)?;
        let (frames, animation_table) = (le32(entry, 0), le32(entry, 4));
        for pointer in [frames, animation_table] {
            if !ctx.rom.is_data(pointer) {
                return Err(format!("body sprite resource {resource}: 0x{pointer:08X} is not ROM data"));
            }
        }
        let ids: Vec<u32> = animations.iter().copied().collect();
        sprites::sprite_set(ctx, frames, animation_table, format!("sprite.resources@{}", hex(BODY_SPRITE_RESOURCES)), &ids)?;
        listed.insert(resource.to_string(), json!({ "frames": hex(frames), "animations": hex(animation_table), "animation_ids": ids, "sources": sources[&resource] }));
    }
    let end = next_root(ctx, BODY_SPRITE_RESOURCES)?;
    if (end - BODY_SPRITE_RESOURCES) % 8 != 0 {
        return Err(format!("body sprite resources: 0x{end:08X} is not a whole number of 8-byte entries"));
    }
    let ids: Vec<String> = used.keys().map(|resource| resource.to_string()).collect();
    let reason = format!("gZoidBodyAnimationResources entry no C indexes: the only C uses of D_087AA244 are the CreateMirroredSpriteFromTable calls in initialize_{{berserk_fury,blitz_tiger,cannonry_molga,rr_pile_bunker,strum_fury,zero_schneider}}_body_sprites.c, whose resource arguments are the constants {}", ids.join(", "));
    for resource in (0..(end - BODY_SPRITE_RESOURCES) / 8).filter(|resource| !used.contains_key(resource)) {
        ctx.unread(id, BODY_SPRITE_RESOURCES + resource * 8, 8, &reason)?;
    }
    ctx.count(id, "resource ids passed by the C callers");
    ctx.set(id, json!({ "stride": 8, "resources_read": listed }));
    Ok(())
}

fn equipment_graphics(ctx: &Ctx) -> R<()> {
    let reached = ctx.roots.require(EQUIPMENT_SPRITE_GRAPHICS)?;
    let (id, _) = ctx.item("table.compressed_sprite_graphics", EQUIPMENT_SPRITE_GRAPHICS, graphics::SPRITE_GRAPHICS, reached.clone());
    let entries = (EQUIPMENT_LAST_ITEM + 1) * 2;
    if EQUIPMENT_SPRITE_GRAPHICS + entries * 8 > next_root(ctx, EQUIPMENT_SPRITE_GRAPHICS)? {
        return Err("equipment sprite graphics entries run past the next referenced address".into());
    }
    let mut nulls = Vec::new();
    for entry in 0..entries {
        let at = EQUIPMENT_SPRITE_GRAPHICS + entry * 8;
        let record = ctx.rom.peek(at, 8)?;
        let (tiles, palette) = (le32(record, 0), le32(record, 4));
        match (tiles, palette) {
            (0, 0) => {
                ctx.rom.claim(at, 8, "table.compressed_sprite_graphics", id)?;
                nulls.push(entry);
            }
            _ if ctx.rom.is_data(tiles) && ctx.rom.is_data(palette) => graphics::sprite_graphics(ctx, EQUIPMENT_SPRITE_GRAPHICS, entry, false, reached[0].clone())?,
            _ => return Err(format!("equipment sprite graphics entry {entry}: 0x{tiles:08X} / 0x{palette:08X} is not ROM data")),
        }
    }
    let (resources_id, new) = ctx.item("sprite.resources", EQUIPMENT_SPRITE_RESOURCES, sprites::SPRITES, ctx.roots.require(EQUIPMENT_SPRITE_RESOURCES)?);
    if new {
        return Err(format!("sprite.resources 0x{EQUIPMENT_SPRITE_RESOURCES:08X} was not read by the sprites port"));
    }
    if EQUIPMENT_SPRITE_RESOURCES + entries * 8 > next_root(ctx, EQUIPMENT_SPRITE_RESOURCES)? {
        return Err("equipment sprite resource entries run past the next referenced address".into());
    }
    for entry in 0..entries {
        let at = EQUIPMENT_SPRITE_RESOURCES + entry * 8;
        let record = ctx.rom.peek(at, 8)?;
        let (frames, animations) = (le32(record, 0), le32(record, 4));
        if frames != 0 && !(ctx.rom.is_data(frames) && ctx.rom.is_data(animations)) {
            return Err(format!("equipment sprite resource entry {entry}: 0x{frames:08X} / 0x{animations:08X} is not ROM data"));
        }
        ctx.rom.claim(at, 8, "table.sprite_resources", resources_id)?;
    }
    ctx.count(id, "c_guard:item <= 0x64 (run_equipment_database_viewer.c, run_player_equipment_menu.c); entries item * 2 and item * 2 + 1");
    ctx.set(id, json!({
        "entries": entries,
        "null_entries": nulls,
        "null_entry_items": nulls.iter().map(|entry| entry / 2).collect::<BTreeSet<_>>(),
        "note": "LoadSpriteGraphicsFromTable has no null check; the guards admit these items, the port does not decode their 0 pointers",
        "unbounded_reader": "event_create_battle_equipment_sprite.c passes a script byte with no guard",
    }));
    Ok(())
}

fn skip_palettes(ctx: &Ctx) -> R<()> {
    let id = require(ctx, "battle_scene.skip_palette_cycle", SKIP_PALETTE_CYCLE, SKIP_PALETTES)?;
    let colors = ctx.rom.claim(SKIP_PALETTE_CYCLE, (SKIP_PALETTE_LAST_FRAME + 1) * 0x20, "palette", id)?.to_vec();
    ctx.count(id, "c_loop_bound:palette_frame 0..5 (run_battle_scene_skip_and_palette_task.c turns at 5 and 0)");
    ctx.file(id, ".png", &palette_swatch(&colors))?;
    ctx.view(id, json!({ "t": "palette", "colors": ["rom", SKIP_PALETTE_CYCLE, SKIP_PALETTE_CYCLE + (SKIP_PALETTE_LAST_FRAME + 1) * 0x20] }));
    ctx.set(id, json!({ "palettes": SKIP_PALETTE_LAST_FRAME + 1, "destination": "0x05000080" }));
    Ok(())
}

/// run_battle.c passes 0x08107058 to PrintWindowText through a register variable. Its link tag 0x08107148 is ported by port::link.
fn run_battle(ctx: &Ctx) -> R<()> {
    text::window_text(ctx, RUN_BATTLE_WINDOW_TEXT, ctx.roots.require(RUN_BATTLE_WINDOW_TEXT)?)?;
    Ok(())
}

fn run(ctx: &Ctx) -> R<()> {
    palette_cycles(ctx)?;
    vectors(ctx)?;
    effect_offsets(ctx)?;
    camera(ctx)?;
    phalanx(ctx)?;
    world_positions(ctx)?;
    formations(ctx)?;
    anchors(ctx)?;
    body_sprites(ctx)?;
    equipment_graphics(ctx)?;
    skip_palettes(ctx)?;
    run_battle(ctx)
}
