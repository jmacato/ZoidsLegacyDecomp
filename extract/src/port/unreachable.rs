//! Data ranges no decomp code reaches. Each range is declared only after two checks pass:
//! the structural check of its category, and the reference check: no decomp reference falls inside it, and every 4-byte
//! value anywhere in the ROM (any alignment) that equals an address inside it sits where no reader takes it as a pointer.
//! Runs after every other port, so "unread" means no other port claimed the bytes.

use std::collections::{BTreeMap, BTreeSet};
use std::path::{Path, PathBuf};

use serde_json::Value;

use super::battle_popups::enum_values;
use super::text::{parse_list, parse_window};
use super::{bios, event_script, literal, menu_script, sprites, Port};
use crate::basis::Basis;
use crate::rom::{le16, le32, R};
use crate::run::Ctx;
use crate::{repo_root, verify_c, BASE, ROM_SIZE};

const HEADER: Basis = Basis::C(&[("src/game/rom_reset_vector.c", "34ddd46d1492ad746bfbf5d5f5ad6c58373713da")]);
const ARM_RETURN: Basis = Basis::MatchedAsm(&[("src/runtime/rom_entry_stack.s", "d37a4caa9dc1f3dac01886f02477fad5b13430f4")]);
const ARM_CODE: Basis = Basis::MatchedAsm(&[
    ("src/runtime/rom_entry_stack.s", "d37a4caa9dc1f3dac01886f02477fad5b13430f4"),
    ("src/runtime/rom_irq_dispatch.s", "9ce6cae1e5c2b61d67334e61513d6dbe007a894f"),
]);
const THUMB_DEFERRED: Basis = Basis::C(&[
    ("src/engine/fill_deferred_memory.c", "8e3b779dd4c53ddd06231c8e75eb7df2aaff766b"),
    ("src/engine/run_deferred_function_call.c", "16d81fa7180dea7bc725c6c74987237aa9294fa1"),
]);
const THUMB_FIXED: Basis = Basis::C(&[
    ("src/engine/cos256.c", "ca201116c77db35b229944681fec523986ab4909"),
    ("src/engine/divide_fixed8.c", "ec86bd7aeeaa1229dcf939fe405d1d6f7dfb553f"),
]);
const THUMB_TRANSFER: Basis = Basis::C(&[
    ("src/graphics/process_transfer_queue.c", "bd3df7baf01ad4e5d00e43a241686352967859c7"),
    ("src/graphics/disable_display_windows.c", "6602ac49e1fa15d31a86adedfa1f4e91a3a242a1"),
]);
const THUMB_LAB: Basis = Basis::C(&[
    ("src/game/modes/run_zoids_lab.c", "8241fea6a031bf17eeddaa48368b8a90606362ea"),
    ("src/graphics/initialize_scene_scanline_mosaic.c", "8d04257c9ab86ab2df32decad947f3291bae92d2"),
]);
const THUMB_MUSIC: Basis = Basis::C(&[
    ("src/audio/fade_out_music_player.c", "06d957fda91aeae0945b77fac425f64e0801f438"),
    ("src/audio/initialize_pending_music_tracks.c", "44b6a7887db17bb9296248bfaca01430583b36db"),
]);
const THUMB_VENEERS: Basis = Basis::C(&[("src/runtime/call_function_r3.c", "1ee7a293f003534e2e29b4885e3ecb1fd0c0c5d3")]);
const THUMB_RANDOM: Basis = Basis::C(&[
    ("src/engine/seed_libc_random.c", "c92de01178039e478028fde84af10e4ff2a75cd2"),
    ("src/runtime/compare_strings.c", "b5e0721ee646516a9e3c4da90d85197106da4739"),
]);
const MENU: Basis = menu_script::MENU_SCRIPT;
const EVENTS: Basis = event_script::EVENTS;
const TEXT: Basis = Basis::C(&[("src/ui/draw_window_text.c", "e61d2cdddb1782410db0393ca1ea434d4defdb93")]);
const TEXT_GROWTH: Basis = Basis::C(&[
    ("src/ui/draw_window_text.c", "e61d2cdddb1782410db0393ca1ea434d4defdb93"),
    ("src/ui/run_player_status_menu.c", "0c4f77dcafbd6975504b921df5838d0e50421e05"),
    ("src/game/player_state.h", "dadeb1433712e28f47ef2910bb1c20a0d96da19b"),
]);
const TEXT_COMPATIBILITY: Basis = Basis::C(&[
    ("src/ui/draw_window_text.c", "e61d2cdddb1782410db0393ca1ea434d4defdb93"),
    ("src/ui/draw_equipment_stats.c", "66399faab17ed3f7c7e355fbd03804b745e1987b"),
]);
const TEXT_QUOTES: Basis = Basis::C(&[
    ("src/ui/draw_window_text.c", "e61d2cdddb1782410db0393ca1ea434d4defdb93"),
    ("src/battle/show_battle_pilot_action_quote.c", "00383c522e8ad680cd7cf97e7b018a5a23f09588"),
    ("src/battle/battle_display.h", "ed9ae1d1b7b71e189ca7f207078675f82ea365b5"),
]);
const CREDITS: Basis = Basis::C(&[("src/game/modes/run_credits.c", "4c3d1b42812f438e577af40f52e6e0419e3d659e")]);
const SINE: Basis = Basis::C(&[("src/engine/sin256.c", "ec7a3b68a7ac57514c28dff9939df455e70b8e26")]);
const FONT: Basis = Basis::C(&[
    ("src/ui/expand_shift_jis_glyph_tiles.c", "59727430777575c051dcdf0287dbe4db71e17d91"),
    ("src/ui/expand_single_byte_glyph_tile.c", "4fb5fdf87cc4d18aff304753f37fb9271c0531b7"),
    ("src/ui/window.h", "c299d1e84300353c8f991978a0c2761133a5e42c"),
]);
const SPRITES: Basis = sprites::SPRITES;
const LINK: Basis = Basis::C(&[
    ("src/engine/poll_link_send.c", "97e8fe91da9ac7615a4ad5f4ce925a9ad6bf75ca"),
    ("src/engine/poll_link_receive.c", "8f98578615109a70e3d4cb93a58a60b8a0d0e34d"),
    ("src/engine/link_transfer.h", "80ce1576fc1066b437c14e4b308a9ef8dbec3862"),
]);
const LZ77: Basis = bios::LZ77_WRAM;
const PORTRAITS: Basis = Basis::C(&[
    ("src/graphics/load_pilot_portrait_graphics.c", "6df5691c4745a5c883bbd766b8bcc6da558e29f0"),
    ("src/graphics/queue_pilot_portrait_graphics.c", "6ac798ad97216d351a2b3684ae1c107d1ddb1626"),
    ("src/graphics/graphics_resources.h", "f223cb8653d7262d3cfbfb30cb9b1b9ae262bc4d"),
]);
const EVENT_SPRITE_GRAPHICS: Basis = Basis::C(&[
    ("src/graphics/load_sprite_graphics_from_table.c", "ea9d494504eeb3b592c2ef609590e7083cc46b7b"),
    ("src/events/load_event_sprite_graphics.c", "bd7a50719d36790fcf3393b2304464ba9b11669b"),
    ("src/events/commands/event_load_sprite_graphics.c", "a08839d14d81be0786c3a3f8ae0c46ac99c09bea"),
    ("src/events/commands/event_show_world_map_structure_appearance.c", "c95a611325ad356555ea91b8430e5ac7ec9bf054"),
    ("src/events/commands/event_set_world_map_structure.c", "fcab0278f74a0e0d3efd154d0a7b9bf9048c0c3e"),
    ("src/events/commands/event_remove_world_map_structure.c", "ec957b0510b81e39f2281af60d543ab0754217c4"),
    ("src/field/create_world_map_structure_sprite.c", "b4da01ff8ebf9023ec08b0297981d3a698836f03"),
    ("src/events/event_script.h", "23f6268830cf2d663af58bc5552d8fd4105e85b2"),
]);
const FIELD_PALETTES: Basis = Basis::C(&[("src/field/update_field_display.c", "ee1fc2a1c12a3ba96f2fec016b106c1a1b64b328")]);
const SONG: Basis = Basis::C(&[("src/audio/start_music_player.c", "7756256a231b5f9740930a68ee4f27bca8ded618")]);
const SRAM: Basis = Basis::C(&[
    ("src/save/init_sram_access.c", "ff216a8a0d2d95c06c2869023c3448ef90d23a4e"),
    ("src/engine/initialize_engine.c", "ad213d3d2d1b307abb8bc779e5c350589b8e92a3"),
]);
const ENCOUNTERS: Basis = Basis::C(&[
    ("src/field/try_select_field_random_encounter.c", "0f314b9346001882aaa8a4790ad9588825153066"),
    ("src/field/select_field_random_encounter_table.c", "f4e75d18a1843b01da87f2728d1e4f5f2367531f"),
]);
const BATTLE_SCRIPTS: Basis = Basis::C(&[
    ("src/battle/battle_animation.h", "bb6342eaf90720323098ac43177cffe1af98aac3"),
    ("src/battle/start_battle_animation.c", "f0ace9715b59cdfd3ac14018b7269ae91c3cb972"),
    ("src/battle/update_battle_animation_script.c", "85558ec838a614eee796c46367f4776c545a075c"),
]);

pub const PORT: Port = Port {
    name: "unreachable",
    bases: &[
        HEADER, ARM_RETURN, ARM_CODE, THUMB_DEFERRED, THUMB_FIXED, THUMB_TRANSFER, THUMB_LAB, THUMB_MUSIC, THUMB_VENEERS, THUMB_RANDOM, TEXT, TEXT_GROWTH, TEXT_COMPATIBILITY,
        TEXT_QUOTES, CREDITS, SINE, FONT, LINK, PORTRAITS, EVENT_SPRITE_GRAPHICS, FIELD_PALETTES, SONG, SRAM, ENCOUNTERS, BATTLE_SCRIPTS,
    ],
    run,
};

/// Music data another port owns; this module declares nothing inside it.
const MUSIC_WINDOW: (u32, u32) = (0x086A_0000, 0x087A_0000);
const EVENT_SPRITE_TABLE: u32 = 0x087A_F9D4;
const LOAD_SPRITE_GRAPHICS_FROM_TABLE: &str = "func_0809AA64";
const ROM_ENTRY_STACK: u32 = 0x0800_00C0;
const FONT_RANGE_COUNT: usize = 22;
const LINK_PACKET_PAYLOAD_BYTES: u32 = 14;
const FIELD_PALETTE_FRAMES: u32 = 0x100;

#[derive(Clone, Copy, PartialEq, Debug)]
enum Kind {
    /// 0x08000004..0x080000C0: the cartridge header the BIOS checks.
    Header,
    /// The ARM `b` the C runtime returns to.
    ArmReturn,
    /// An ARM routine no matched code branches to.
    ArmRoutine,
    /// Thumb functions between matched regions that no matched code calls.
    Thumb,
    /// Whole menu scripts after a menu script's END.
    Menu,
    /// DrawWindowText strings after a text's terminating 0.
    Text,
    /// Bytes after the credits stream's terminating 0.
    CreditsTail,
    /// Event script bytes after a terminal command.
    EventTail,
    /// Zero padding and an ASCII string after table.sine.
    SineTail,
    /// 2bpp glyphs no font range covers.
    Font,
    /// A complete sprite set {frames, frame table, animations, animation table} whose pointers stay inside it.
    SpriteSet,
    /// The rest of a link tag string past the bytes the link code copies and compares.
    LinkTagTail,
    /// Zero padding and LZ77 streams.
    Lz,
    /// Zero padding and one sprite frame.
    SpriteFrame,
    /// A frame table word past the largest frame id of its animations.
    FrameTableTail,
    /// Zero padding and 32-byte BGR555 palettes.
    Palettes,
    /// A track only an unread song header slot points to.
    SongTrack,
    /// Song header track slots past the ones StartMusicPlayer reads.
    SongSlots,
    /// An ASCII library ID string and words after it.
    SramLibrary,
    /// Bytes after the field encounter definitions' map_id 0 record.
    EncounterTail,
    /// Whole battle animation scripts after a script's -1.
    BattleScripts,
}

struct Entry {
    start: u32,
    end: u32,
    kind: Kind,
    basis: Basis,
}

const fn entry(start: u32, end: u32, kind: Kind, basis: Basis) -> Entry {
    Entry { start, end, kind, basis }
}

const RANGES: &[Entry] = &[
    entry(0x0800_0004, 0x0800_00C0, Kind::Header, HEADER),
    entry(0x0800_00F0, 0x0800_00F4, Kind::ArmReturn, ARM_RETURN),
    entry(0x0800_03E0, 0x0800_04C8, Kind::ArmRoutine, ARM_CODE),
    entry(0x0800_0B83, 0x0800_0B86, Kind::Menu, MENU),
    entry(0x0800_16E0, 0x0800_1730, Kind::Menu, MENU),
    entry(0x0800_2D60, 0x0800_2DD0, Kind::Menu, MENU),
    entry(0x0800_4027, 0x0800_4037, Kind::Menu, MENU),
    entry(0x0800_437F, 0x0800_43D7, Kind::Menu, MENU),
    entry(0x0800_58D4, 0x0800_591E, Kind::Menu, MENU),
    entry(0x0800_5BF1, 0x0800_5C69, Kind::Menu, MENU),
    entry(0x0800_5FD6, 0x0800_6054, Kind::Menu, MENU),
    entry(0x0800_66CE, 0x0800_66D6, Kind::Menu, MENU),
    entry(0x0800_68D2, 0x0800_6962, Kind::Menu, MENU),
    entry(0x0800_69F3, 0x0800_69FA, Kind::Menu, MENU),
    entry(0x0802_4828, 0x0802_482F, Kind::Text, TEXT_COMPATIBILITY),
    entry(0x0802_48B5, 0x0802_48CD, Kind::Text, TEXT_QUOTES),
    entry(0x0802_4B82, 0x0802_4B9B, Kind::Text, TEXT),
    entry(0x0802_C56B, 0x0802_C5E0, Kind::CreditsTail, CREDITS),
    entry(0x0802_C9B8, 0x0802_CE80, Kind::EventTail, EVENTS),
    entry(0x0802_CE86, 0x0802_CEB2, Kind::EventTail, EVENTS),
    entry(0x0804_3ADA, 0x0804_3C87, Kind::EventTail, EVENTS),
    entry(0x0804_5EEE, 0x0804_607B, Kind::EventTail, EVENTS),
    entry(0x0804_9A1D, 0x0804_9A8D, Kind::EventTail, EVENTS),
    entry(0x0805_9997, 0x0805_9AA8, Kind::EventTail, EVENTS),
    entry(0x0805_9CA4, 0x0805_9CA5, Kind::EventTail, EVENTS),
    entry(0x0805_E8E5, 0x0805_EA5D, Kind::EventTail, EVENTS),
    entry(0x0805_ED2A, 0x0805_ED89, Kind::EventTail, EVENTS),
    entry(0x0806_D781, 0x0806_D96F, Kind::EventTail, EVENTS),
    entry(0x0807_474A, 0x0807_474F, Kind::EventTail, EVENTS),
    entry(0x0807_5C01, 0x0807_5C0D, Kind::EventTail, EVENTS),
    entry(0x0808_9CAB, 0x0808_A38C, Kind::EventTail, EVENTS),
    entry(0x0808_CD25, 0x0808_CD2A, Kind::EventTail, EVENTS),
    entry(0x0809_298C, 0x0809_29B0, Kind::Thumb, THUMB_DEFERRED),
    entry(0x0809_2AF4, 0x0809_2B04, Kind::Thumb, THUMB_FIXED),
    entry(0x0809_5330, 0x0809_534C, Kind::Thumb, THUMB_TRANSFER),
    entry(0x080B_A86C, 0x080B_A878, Kind::Thumb, THUMB_LAB),
    entry(0x080E_B8FA, 0x080E_B944, Kind::Thumb, THUMB_MUSIC),
    entry(0x080E_CD6C, 0x080E_CD98, Kind::Thumb, THUMB_VENEERS),
    entry(0x080E_D0A4, 0x080E_D0CC, Kind::Thumb, THUMB_RANDOM),
    entry(0x080E_D206, 0x080E_D21C, Kind::SineTail, SINE),
    entry(0x080F_0D48, 0x080F_1548, Kind::Font, FONT),
    entry(0x0810_53FC, 0x0810_544C, Kind::SpriteSet, SPRITES),
    entry(0x0810_549C, 0x0810_54EC, Kind::SpriteSet, SPRITES),
    entry(0x0810_592C, 0x0810_5954, Kind::SpriteSet, SPRITES),
    entry(0x0810_5C38, 0x0810_5C9C, Kind::SpriteSet, SPRITES),
    entry(0x0810_920A, 0x0810_920C, Kind::LinkTagTail, LINK),
    entry(0x081A_34FA, 0x081A_36DC, Kind::Lz, LZ77),
    entry(0x0824_B49A, 0x0824_B4DC, Kind::SpriteFrame, SPRITES),
    entry(0x0824_B4EC, 0x0824_B4F0, Kind::FrameTableTail, SPRITES),
    entry(0x0827_6A1E, 0x0827_6A74, Kind::SpriteFrame, SPRITES),
    entry(0x0827_6A98, 0x0827_6A9C, Kind::FrameTableTail, SPRITES),
    entry(0x0827_93CA, 0x0827_93E4, Kind::SpriteFrame, SPRITES),
    entry(0x0827_940C, 0x0827_9410, Kind::FrameTableTail, SPRITES),
    entry(0x0839_817A, 0x0839_81A4, Kind::Lz, PORTRAITS),
    entry(0x0839_855F, 0x0839_8588, Kind::Lz, PORTRAITS),
    entry(0x0839_893C, 0x0839_8D38, Kind::Lz, LZ77),
    entry(0x0841_F194, 0x0841_F7BC, Kind::Lz, EVENT_SPRITE_GRAPHICS),
    entry(0x0842_02D0, 0x0842_045C, Kind::Lz, EVENT_SPRITE_GRAPHICS),
    entry(0x0842_113A, 0x0842_115C, Kind::Lz, LZ77),
    entry(0x085D_2D76, 0x085D_2E38, Kind::Palettes, FIELD_PALETTES),
    entry(0x087A_016D, 0x087A_0184, Kind::SongTrack, SONG),
    entry(0x087A_019C, 0x087A_01A0, Kind::SongSlots, SONG),
    entry(0x087A_099C, 0x087A_09D8, Kind::SramLibrary, SRAM),
    entry(0x087C_397A, 0x087C_4434, Kind::EncounterTail, ENCOUNTERS),
    entry(0x087D_573C, 0x087D_57C8, Kind::BattleScripts, BATTLE_SCRIPTS),
    entry(0x087D_5A38, 0x087D_5AC4, Kind::BattleScripts, BATTLE_SCRIPTS),
    entry(0x087D_5BA4, 0x087D_5BB4, Kind::BattleScripts, BATTLE_SCRIPTS),
];

fn hex(address: u32) -> String {
    format!("0x{address:08X}")
}

fn format_at(ctx: &Ctx, address: u32) -> Option<String> {
    let id = ctx.rom.owners()[(address - BASE) as usize];
    (id != 0).then(|| ctx.rom.format_name(id))
}

fn unread(ctx: &Ctx, address: u32) -> bool {
    ctx.rom.is_data(address) && ctx.rom.owners()[(address - BASE) as usize] == 0
}

/// The item of the last claim covering `address`, as finish() attributes bytes.
fn item_at(ctx: &Ctx, address: u32) -> Option<usize> {
    ctx.rom.claims().iter().filter(|claim| claim.start <= address && address < claim.end).last().map(|claim| claim.item)
}

fn mine(address: u32) -> Option<&'static Entry> {
    RANGES.iter().find(|entry| entry.start <= address && address < entry.end)
}

fn s16(ctx: &Ctx, address: u32) -> R<i16> {
    Ok(le16(ctx.rom.peek(address, 2)?, 0) as i16)
}

fn u32_at(ctx: &Ctx, address: u32) -> R<u32> {
    Ok(le32(ctx.rom.peek(address, 4)?, 0))
}

fn parse_hex(value: &Value) -> Option<u32> {
    u32::from_str_radix(value.as_str()?.trim_start_matches("0x"), 16).ok()
}

/// Walked event commands: (at, op, end, item).
struct Command {
    at: u32,
    op: String,
    end: u32,
    item: u32,
    targets: Vec<u32>,
    first_arg: Option<u32>,
}

struct Env {
    commands: Vec<Command>,
    explained: Vec<u32>,
}

impl Env {
    fn new(ctx: &Ctx) -> R<Env> {
        let mut commands = Vec::new();
        for (item, data) in ctx.data_of("event_script") {
            for command in data["commands"].as_array().into_iter().flatten() {
                let at = parse_hex(&command["at"]).ok_or("event command without an address")?;
                let op = command["op"].as_str().unwrap_or("").to_string();
                let mut targets: Vec<u32> = command["next"].as_array().into_iter().flatten().filter_map(parse_hex).collect();
                targets.extend(command["scripts"].as_array().into_iter().flatten().filter_map(parse_hex));
                targets.extend(parse_hex(&command["target"]));
                let end = if op == "START_SCRIPTS" {
                    at + 2 + 4 * command["scripts"].as_array().map_or(0, |list| list.len() as u32)
                } else if op == "TEXT" {
                    command["next"].as_array().and_then(|list| list.first()).and_then(parse_hex).ok_or("TEXT without a successor")?
                } else {
                    at + 1 + command["args"].as_array().map_or(0, |list| list.len() as u32)
                };
                let first_arg = command["args"].get(0).and_then(Value::as_u64).map(|value| value as u32);
                commands.push(Command { at, op, end, item, targets, first_arg });
            }
        }
        commands.sort_by_key(|command| command.at);
        let explained = ctx.data_of("root.explained").into_iter().map(|(address, _)| address).collect();
        Ok(Env { commands, explained })
    }

    fn command_at(&self, address: u32) -> Option<&Command> {
        let index = self.commands.partition_point(|command| command.at <= address);
        self.commands[..index].last().filter(|command| address < command.end)
    }
}

/// Ids the C can pass to LoadSpriteGraphicsFromTable(EVENT_SPRITE_TABLE, id): literal call sites, LoadEventSpriteGraphics
/// (EVENT_LOAD_SPRITE_GRAPHICS operands; 4 and variant + 12 from EventShowWorldMapStructureAppearance), and
/// CreateWorldMapStructureSprite (world_structure_kind + 11, where the kind is 0, SET_WORLD_MAP_STRUCTURE operand + 1,
/// or SHOW_WORLD_MAP_STRUCTURE_APPEARANCE variant + 1).
fn event_sprite_ids(ctx: &Ctx, env: &Env) -> R<BTreeSet<u32>> {
    let names = enum_values("src/events/event_script.h")?;
    for name in ["EVENT_SPRITE_GRAPHICS_TABLE_ROM", "WORLD_MAP_STRUCTURE_GRAPHICS_TABLE_ROM"] {
        if names.get(name) != Some(&EVENT_SPRITE_TABLE) {
            return Err(format!("event_script.h: {name} is not 0x{EVENT_SPRITE_TABLE:08X}"));
        }
    }
    let mut ids = BTreeSet::new();
    const VIA_ID_SOURCES: [&str; 2] = ["src/events/load_event_sprite_graphics.c", "src/field/create_world_map_structure_sprite.c"];
    const CONSTANT_USES: [&str; 1] = ["src/events/event_script.h"];
    const SCENE_REGISTER: &str = "src/events/scenes/play_arcadia_time_space_unit_destruction_scene.c";
    let by_address = ctx.roots.by_address();
    for reference in by_address.get(&EVENT_SPRITE_TABLE).into_iter().flatten() {
        let file = reference.file.as_str();
        if reference.callee.as_deref() == Some(LOAD_SPRITE_GRAPHICS_FROM_TABLE) && reference.arg == 0 {
            if let Some(id) = reference.args.get(1).and_then(|text| literal(text)) {
                ids.insert(id & 0xFF);
                continue;
            }
            if VIA_ID_SOURCES.contains(&file) {
                continue;
            }
            return Err(format!("{}: LoadSpriteGraphicsFromTable(0x{EVENT_SPRITE_TABLE:08X}, {:?}) has an id this check does not model", reference.location(), reference.args.get(1)));
        }
        if CONSTANT_USES.contains(&file) || VIA_ID_SOURCES.contains(&file) {
            continue;
        }
        if file == SCENE_REGISTER {
            let text = std::fs::read_to_string(repo_root().join(file)).map_err(|error| error.to_string())?;
            let calls: Vec<&str> = text.match_indices("LoadSpriteGraphicsFromTable(menu, ").map(|(at, _)| &text[at..]).collect();
            if calls.is_empty() {
                return Err(format!("{file}: no LoadSpriteGraphicsFromTable(menu, ...) call for the register holding 0x{EVENT_SPRITE_TABLE:08X}"));
            }
            for call in calls {
                let argument = call["LoadSpriteGraphicsFromTable(menu, ".len()..].split(',').next().unwrap_or("");
                ids.insert(literal(argument.trim()).ok_or_else(|| format!("{file}: id {argument} is not a literal"))? & 0xFF);
            }
            continue;
        }
        return Err(format!("{}: a reference to 0x{EVENT_SPRITE_TABLE:08X} this check does not model", reference.location()));
    }
    for (function, allowed) in [
        ("func_0809F8A0", &["src/events/load_event_sprite_graphics.c", "src/events/commands/event_load_sprite_graphics.c", "src/events/commands/event_show_world_map_structure_appearance.c"][..]),
        ("func_080A6148", &["src/field/create_world_map_structure_sprite.c", "src/field/initialize_field_map_graphics.c", "src/events/commands/event_show_world_map_structure_appearance.c", "src/events/commands/event_set_world_map_structure.c"][..]),
    ] {
        for file in source_files_mentioning(function)? {
            if !allowed.contains(&file.as_str()) {
                return Err(format!("{file} names {function}; the event sprite id check does not model that caller"));
            }
        }
    }
    for file in source_files_mentioning("world_structure_kind)] =")? {
        if !["src/events/commands/event_set_world_map_structure.c", "src/events/commands/event_remove_world_map_structure.c", "src/events/commands/event_show_world_map_structure_appearance.c"].contains(&file.as_str()) {
            return Err(format!("{file} stores world_structure_kind; the event sprite id check does not model it"));
        }
    }
    ids.insert(11);
    for command in &env.commands {
        let Some(arg) = command.first_arg else { continue };
        match command.op.as_str() {
            "LOAD_SPRITE_GRAPHICS" => {
                ids.insert(arg & 0xFF);
            }
            "SHOW_WORLD_MAP_STRUCTURE_APPEARANCE" => {
                ids.insert(4);
                ids.insert((arg + 12) & 0xFF);
                ids.insert(((arg + 1) & 0xFF) + 11);
            }
            "SET_WORLD_MAP_STRUCTURE" => {
                ids.insert(((arg + 1) & 0xFF) + 11);
            }
            _ => {}
        }
    }
    Ok(ids)
}

fn source_files_mentioning(needle: &str) -> R<Vec<String>> {
    fn walk(dir: &Path, out: &mut Vec<PathBuf>) -> R<()> {
        for entry in std::fs::read_dir(dir).map_err(|error| format!("{}: {error}", dir.display()))? {
            let path = entry.map_err(|error| error.to_string())?.path();
            if path.is_dir() {
                walk(&path, out)?;
            } else if path.extension().is_some_and(|extension| extension == "c" || extension == "h") {
                out.push(path);
            }
        }
        Ok(())
    }
    let root = repo_root();
    let mut files = Vec::new();
    walk(&root.join("src"), &mut files)?;
    let mut out = Vec::new();
    for path in files {
        let text = std::fs::read_to_string(&path).map_err(|error| format!("{}: {error}", path.display()))?;
        if text.contains(needle) {
            out.push(path.strip_prefix(&root).unwrap().to_string_lossy().replace('\\', "/"));
        }
    }
    out.sort();
    Ok(out)
}

/// Table words the C never selects, with the evidence. `at` is a word no port read.
struct Unselected {
    growth: Vec<(u32, BTreeSet<u32>)>,
    quotes: Vec<(u32, Value)>,
    portraits: Vec<u32>,
    portrait_pilot: u32,
    event_sprite_ids: BTreeSet<u32>,
    songs: Vec<(u32, u32, u32, Value)>,
}

impl Unselected {
    fn new(ctx: &Ctx, env: &Env) -> R<Unselected> {
        let growth = ctx
            .data_of("table.pilot_growth_class_names")
            .into_iter()
            .map(|(address, data)| (address, data["entries"].as_array().into_iter().flatten().filter_map(|entry| entry["index"].as_u64()).map(|index| index as u32).collect()))
            .collect();
        let quotes = ctx.data_of("table.pilot_quotes");
        let portraits = ctx.data_of("table.pilot_portraits").into_iter().map(|(address, _)| address).collect();
        let portrait_pilot = *enum_values("src/graphics/graphics_resources.h")?.get("GRAPHICS_PILOT_WITH_ALTERNATE_PORTRAIT_PALETTES").ok_or("graphics_resources.h has no GRAPHICS_PILOT_WITH_ALTERNATE_PORTRAIT_PALETTES")?;
        let songs = ctx
            .data_of("mp2k.song")
            .into_iter()
            .filter_map(|(address, data)| Some((address, data["track_count"].as_u64()? as u32, data["tracks_read"].as_u64()? as u32, data["players"].clone())))
            .collect();
        Ok(Unselected { growth, quotes, portraits, portrait_pilot, event_sprite_ids: event_sprite_ids(ctx, env)?, songs })
    }

    fn reason(&self, at: u32) -> Option<String> {
        for (table, read) in &self.growth {
            let max = read.iter().next_back().copied().unwrap_or(0);
            if at >= *table && (at - table) % 4 == 0 && (at - table) / 4 <= max && !read.contains(&((at - table) / 4)) {
                return Some(format!(
                    "table.pilot_growth_class_names@{}[{}], an index no pilot growth class takes (run_player_status_menu.c indexes by the pilot's growth class; the classes the C stores are {:?})",
                    hex(*table),
                    (at - table) / 4,
                    read
                ));
            }
        }
        for (table, data) in &self.quotes {
            if at < *table || (at - table) % 8 != 0 {
                continue;
            }
            let relative = at - table;
            let (pilot, kind, index) = ((relative / 120) as usize, ((relative % 120) / 24) as usize, ((relative % 24) / 8) as usize);
            if data["pilots"].get(pilot).and_then(|entry| entry["quotes"].get(kind)).and_then(|list| list.get(index)).and_then(|quote| quote["text_source"].as_str()) == Some("player battle quote in RAM") {
                return Some(format!(
                    "text pointer of table.pilot_quotes@{}[{pilot}][{kind}][{index}]: ShowBattlePilotActionQuote prints the RAM custom quote for pilot 1 attack quotes and never loads this pointer (show_battle_pilot_action_quote.c)",
                    hex(*table)
                ));
            }
        }
        for table in &self.portraits {
            if at >= *table && (at - table) % 8 == 4 && (at - table) / 64 == self.portrait_pilot {
                return Some(format!(
                    "palette pointer of table.pilot_portraits@{}[{}][{}]: Load/QueuePilotPortraitGraphics load gPilotPortraitAlternatePalettes instead for pilot GRAPHICS_PILOT_WITH_ALTERNATE_PORTRAIT_PALETTES ({})",
                    hex(*table),
                    self.portrait_pilot,
                    ((at - table) % 64) / 8,
                    self.portrait_pilot
                ));
            }
        }
        if at >= EVENT_SPRITE_TABLE && (at - EVENT_SPRITE_TABLE) % 4 == 0 && (at - EVENT_SPRITE_TABLE) / 8 < 0x100 {
            let id = (at - EVENT_SPRITE_TABLE) / 8;
            if !self.event_sprite_ids.contains(&id) {
                return Some(format!("table.compressed_sprite_graphics@{}[{id}], an id no C path passes (ids the C can pass: {:?})", hex(EVENT_SPRITE_TABLE), self.event_sprite_ids));
            }
        }
        for (header, count, read, players) in &self.songs {
            let first = header + 8 + 4 * read;
            if at >= first && at < header + 8 + 4 * count && (at - first) % 4 == 0 {
                return Some(format!(
                    "track slot {} of mp2k.song@{} (track_count {count}): StartMusicPlayer reads min(track_count, player track_count) = {read} slots for players {players}",
                    (at - header - 8) / 4,
                    hex(*header)
                ));
            }
        }
        None
    }
}

/// Why the word at `at` (value inside a range) is not a pointer any reader takes, or an error.
fn disposition(ctx: &Ctx, env: &Env, unselected: &Unselected, at: u32) -> Result<String, String> {
    if (0..4).all(|index| mine(at + index).is_some()) {
        let entry = mine(at).unwrap();
        return Ok(format!("inside {}..{} (declared here)", hex(entry.start), hex(entry.end)));
    }
    let code = (0..4).filter(|index| !ctx.rom.is_data(at + index)).count();
    if code > 0 {
        if at % 4 == 0 {
            return Err(format!("aligned word at {} is matched code (a literal pool can load it)", hex(at)));
        }
        return Ok("unaligned word in matched code (pc-relative loads read aligned words)".into());
    }
    let formats: Vec<Option<String>> = (0..4).map(|index| format_at(ctx, at + index)).collect();
    if formats.iter().all(Option::is_some) {
        let names: BTreeSet<String> = formats.into_iter().flatten().collect();
        if names.contains(crate::rom::NEUTRAL) {
            let items: Vec<String> = ctx.rom.claims().iter().filter(|claim| claim.start < at + 4 && at < claim.end).map(|claim| ctx.name(claim.item)).collect();
            let areas: Vec<String> = items
                .iter()
                .filter_map(|name| {
                    let (kind, address) = name.split_once('@')?;
                    ctx.data(kind, u32::from_str_radix(address.trim_start_matches("0x"), 16).ok()?)?["destination_area"].as_str().map(str::to_string)
                })
                .collect();
            let graphics = |area: &String| area.starts_with("vram") || area.starts_with("palette") || area.starts_with("oam");
            if names.len() != 1 || areas.len() != items.len() || !areas.iter().all(graphics) {
                return Err(format!("{} is in bytes a port copies raw ({}, destinations {areas:?}); the copy can be read as anything", hex(at), items.join(",")));
            }
            return Ok(format!("in bytes copied raw to {} (tile or color memory) by {}", areas.join("+"), items.join(",")));
        }
        let pointer_bearing = |name: &String| name.starts_with("table.") || matches!(name.as_str(), "mp2k.song_header" | "mp2k.tone_data" | "literal_pool");
        if at % 4 == 0 && names.iter().any(pointer_bearing) {
            return Err(format!("aligned word at {} in {names:?}", hex(at)));
        }
        if names.contains("mp2k.track") {
            return Err(format!("{} is inside music track bytes (GOTO/PATT take 4-byte operands)", hex(at)));
        }
        if names.contains("event_script") {
            let command = env.command_at(at).ok_or_else(|| format!("{} is claimed as event_script but no walked command covers it", hex(at)))?;
            let slot = (command.op == "START_SCRIPTS" && at >= command.at + 2 && (at - command.at - 2) % 4 == 0) || (command.op == "JUMP" && at == command.at + 1);
            if slot {
                return Err(format!("{} is a {} pointer operand of the command at {}", hex(at), command.op, hex(command.at)));
            }
            return Ok(format!("inside the operands of a walked {} command, not at a START_SCRIPTS or JUMP pointer slot (the pointer operands the event walk follows)", command.op));
        }
        let list: Vec<&str> = names.iter().map(String::as_str).collect();
        if at % 4 == 0 {
            return Ok(format!("aligned word decoded by its port as {}", list.join("+")));
        }
        return Ok(format!("unaligned word decoded by its port as {}", list.join("+")));
    }
    if (0..4).all(|index| matches!(ctx.declared_at(at + index), Some((true, _)))) {
        let (_, reason) = ctx.declared_at(at).unwrap();
        return Ok(format!("declared unread by its port ({reason})"));
    }
    if let Some(root) = env.explained.iter().find(|&&root| root <= at && (root..at + 4).all(|address| unread(ctx, address))) {
        return Ok(format!("in the unread bytes from the explained root {} (explained_roots.txt)", hex(*root)));
    }
    if at % 4 != 0 {
        let mut parts = BTreeSet::new();
        let mut readable = true;
        for address in at..at + 4 {
            if mine(address).is_some() {
                parts.insert("bytes declared here".to_string());
            } else if let Some(name) = format_at(ctx, address) {
                if ["event_script", "mp2k.track", crate::rom::NEUTRAL].contains(&name.as_str()) {
                    readable = false;
                } else {
                    parts.insert(format!("bytes read as {name}"));
                }
            } else {
                let (mut before, mut after) = (address, address);
                while unread(ctx, before - 1) {
                    before -= 1;
                }
                while unread(ctx, after) {
                    after += 1;
                }
                let (first, last) = (item_at(ctx, before - 1), item_at(ctx, after));
                let zero = ctx.rom.peek(before, after - before).map_or(false, |bytes| bytes.iter().all(|&byte| byte == 0));
                match (first, last) {
                    (Some(first), Some(last)) if first == last && !["event_script@", "mp2k.track@"].iter().any(|kind| ctx.name(first).starts_with(kind)) => {
                        parts.insert(format!("unread bytes inside {}", ctx.name(first)));
                    }
                    _ if zero => {
                        parts.insert(format!("unread zero padding {}..{}", hex(before), hex(after)));
                    }
                    _ => readable = false,
                }
            }
        }
        if readable {
            return Ok(format!(
                "unaligned word over {}: a 4-byte pointer at an unaligned address is only assembled by the byte-stream readers with pointer operands (event scripts, music tracks), and none covers it",
                parts.into_iter().collect::<Vec<_>>().join(" + ")
            ));
        }
    }
    if (0..4).all(|index| unread(ctx, at + index)) {
        if let Some(reason) = unselected.reason(at) {
            return Ok(reason);
        }
        if (MUSIC_WINDOW.0..MUSIC_WINDOW.1).contains(&at) {
            if let Some(reason) = pcm_samples(ctx, at)? {
                return Ok(reason);
            }
        }
    }
    Err(format!("{} holds an address inside the range in bytes no port reads", hex(at)))
}

/// An unread run in the music data that holds a PcmWaveHeader {u32 0, u32 frequency, u32 loop start, u32 sample count}
/// whose sample bytes cover `at`: 8-bit samples, never a pointer.
fn pcm_samples(ctx: &Ctx, at: u32) -> R<Option<String>> {
    let mut start = at;
    while start > BASE && unread(ctx, start - 1) {
        start -= 1;
    }
    let mut end = at;
    while unread(ctx, end) {
        end += 1;
    }
    let mut header = (start + 3) & !3;
    while header + 16 <= end {
        let fields = ctx.rom.peek(header, 16)?;
        let (kind, frequency, count) = (le32(fields, 0), le32(fields, 4), le32(fields, 12));
        if kind == 0 && frequency != 0 && header + 16 + count <= end && header + 16 <= at && at + 4 <= header + 16 + count {
            return Ok(Some(format!("PCM sample bytes of the PcmWaveHeader at {} (frequency 0x{frequency:08X}, {count} samples) in unread music data", hex(header))));
        }
        header += 4;
    }
    Ok(None)
}

/// Branch, call and pc-relative ADD targets in matched code that land in [start, end).
fn code_targets(ctx: &Ctx, start: u32, end: u32) -> R<Vec<String>> {
    let regions = verify_c::regions(&repo_root().join("regions.txt"))?;
    let text = std::fs::read_to_string(repo_root().join("cfg/functions.json")).map_err(|error| error.to_string())?;
    let owners: Vec<Value> = serde_json::from_str(&text).map_err(|error| error.to_string())?;
    let mut arm = Vec::new();
    for owner in owners.iter().filter(|owner| owner["mode"] == "arm") {
        arm.push((verify_c::parse_hex(owner["lo"].as_str().unwrap_or(""))?, verify_c::parse_hex(owner["hi"].as_str().unwrap_or(""))?));
    }
    let is_arm = |at: u32| arm.iter().any(|&(low, high)| low <= at && at < high);
    let mut found = Vec::new();
    for region in &regions {
        let (low, high) = (BASE + region.start, BASE + region.end);
        let mut at = low;
        while at + 4 <= high {
            if is_arm(at) {
                if at % 4 == 0 {
                    let word = le32(ctx.rom.code_bytes(at, 4)?, 0);
                    if word >> 28 != 0xF && word & 0x0E00_0000 == 0x0A00_0000 {
                        let offset = ((word & 0x00FF_FFFF) << 8) as i32 >> 6;
                        let target = (at as i32 + 8 + offset) as u32;
                        if (start..end).contains(&target) {
                            found.push(format!("ARM B/BL at {} ({})", hex(at), region.sources.join(",")));
                        }
                    }
                    if word >> 28 != 0xF && word & 0x0FFF_0000 == 0x028F_0000 {
                        let rotate = (word >> 8) & 0xF;
                        let target = at + 8 + (word & 0xFF).rotate_right(rotate * 2);
                        if (start..end).contains(&target) {
                            found.push(format!("ARM ADD from pc at {} ({})", hex(at), region.sources.join(",")));
                        }
                    }
                }
                at += 2;
                continue;
            }
            let first = le16(ctx.rom.code_bytes(at, 2)?, 0);
            let second = le16(ctx.rom.code_bytes(at + 2, 2)?, 0);
            if first & 0xF800 == 0xF000 && second & 0xF800 == 0xF800 {
                let offset = ((((first as u32 & 0x7FF) << 12) | ((second as u32 & 0x7FF) << 1)) << 9) as i32 >> 9;
                let target = (at as i32 + 4 + offset) as u32;
                if (start..end).contains(&target) {
                    found.push(format!("Thumb BL at {} ({})", hex(at), region.sources.join(",")));
                }
            }
            at += 2;
        }
        let mut at = low;
        while at + 2 <= high {
            let first = le16(ctx.rom.code_bytes(at, 2)?, 0);
            if !is_arm(at) && first & 0xF800 == 0xA000 {
                let target = ((at + 4) & !3) + u32::from(first & 0xFF) * 4;
                if (start..end).contains(&target) {
                    found.push(format!("Thumb ADR at {} ({})", hex(at), region.sources.join(",")));
                }
            }
            at += 2;
        }
    }
    Ok(found)
}

fn header(ctx: &Ctx, entry: &Entry) -> R<String> {
    if (entry.start, entry.end) != (BASE + 4, ROM_ENTRY_STACK) {
        return Err("the header range is not 0x08000004..0x080000C0".into());
    }
    let vector = le32(ctx.rom.code_bytes(BASE, 4)?, 0);
    let target = (BASE as i32 + 8 + (((vector & 0x00FF_FFFF) << 8) as i32 >> 6)) as u32;
    if vector >> 24 != 0xEA || target != ROM_ENTRY_STACK {
        return Err(format!("reset vector 0x{vector:08X} is not `b 0x080000C0`"));
    }
    let bytes = ctx.rom.peek(entry.start, entry.end - entry.start)?;
    let byte = |address: u32| bytes[(address - entry.start) as usize];
    if byte(BASE + 0xB2) != 0x96 {
        return Err("header byte 0x080000B2 is not the fixed 0x96".into());
    }
    let sum = (0xA0..=0xBC).fold(0u8, |sum, offset| sum.wrapping_add(byte(BASE + offset)));
    let complement = 0u8.wrapping_sub(sum).wrapping_sub(0x19);
    if byte(BASE + 0xBD) != complement {
        return Err(format!("header complement 0x{:02X} does not match 0x{complement:02X}", byte(BASE + 0xBD)));
    }
    let title: String = (0xA0..0xAC).map(|offset| byte(BASE + offset)).take_while(|&value| value != 0).map(char::from).collect();
    if !title.bytes().all(|value| value.is_ascii_graphic() || value == b' ') {
        return Err("header title is not ASCII".into());
    }
    Ok(format!(
        "cartridge header (logo, title \"{title}\", fixed byte 0x96 at 0x080000B2, complement 0x{complement:02X} at 0x080000BD matching 0x080000A0..0x080000BC): the BIOS reads it before the game; the reset vector at 0x08000000 (rom_reset_vector.c) branches over it to 0x080000C0"
    ))
}

fn arm_return(ctx: &Ctx, entry: &Entry) -> R<String> {
    let (mov, bx) = (le32(ctx.rom.code_bytes(entry.start - 8, 4)?, 0), le32(ctx.rom.code_bytes(entry.start - 4, 4)?, 0));
    if mov != 0xE1A0_E00F || bx != 0xE12F_FF11 {
        return Err(format!("the two words before {} are 0x{mov:08X} 0x{bx:08X}, not `mov lr, pc; bx r1`", hex(entry.start)));
    }
    let word = u32_at(ctx, entry.start)?;
    let target = (entry.start as i32 + 8 + (((word & 0x00FF_FFFF) << 8) as i32 >> 6)) as u32;
    if entry.end != entry.start + 4 || word >> 24 != 0xEA || target != ROM_ENTRY_STACK || ctx.rom.is_data(ROM_ENTRY_STACK) {
        return Err(format!("{} holds 0x{word:08X}, not `b 0x080000C0` to the matched rom_entry_stack", hex(entry.start)));
    }
    Ok("unsourced ARM instruction `b 0x080000C0`: rom_entry_stack.s ends with `mov lr, pc; bx r1`, so the C runtime returns here; executed as code, never read as data".into())
}

fn arm_routine(ctx: &Ctx, entry: &Entry) -> R<String> {
    let words: Vec<u32> = ctx.rom.peek(entry.start, entry.end - entry.start)?.chunks(4).map(|word| le32(word, 0)).collect();
    if entry.start % 4 != 0 || words.len() < 3 || words[0] & 0xFFFF_4000 != 0xE92D_4000 {
        return Err(format!("{} does not start with `stmdb sp!, {{..., lr}}`", hex(entry.start)));
    }
    let pool = entry.end - 4;
    if words[words.len() - 2] != 0xE12F_FF1E {
        return Err(format!("the word before {} is not `bx lr`", hex(pool)));
    }
    let mut loads = Vec::new();
    for (index, &word) in words[..words.len() - 1].iter().enumerate() {
        let at = entry.start + index as u32 * 4;
        if word >> 28 == 0xF {
            return Err(format!("{}: 0x{word:08X} has condition 0xF", hex(at)));
        }
        if word & 0x0F7F_0000 == 0x051F_0000 {
            let target = if word & 0x0080_0000 != 0 { at + 8 + (word & 0xFFF) } else { at + 8 - (word & 0xFFF) };
            if target != pool {
                return Err(format!("{}: pc-relative load of {} outside the routine's pool", hex(at), hex(target)));
            }
            loads.push(at);
        }
        if word & 0x0E00_0000 == 0x0A00_0000 {
            let target = (at as i32 + 8 + (((word & 0x00FF_FFFF) << 8) as i32 >> 6)) as u32;
            if !(entry.start..pool).contains(&target) {
                return Err(format!("{}: branch to {} leaves the routine", hex(at), hex(target)));
            }
        }
    }
    if loads.is_empty() {
        return Err(format!("no load reads the last word {}", hex(pool)));
    }
    let callers = code_targets(ctx, entry.start, entry.end)?;
    if !callers.is_empty() {
        return Err(format!("matched code reaches {}: {}", hex(entry.start), callers.join("; ")));
    }
    Ok(format!(
        "unsourced ARM routine: `stmdb sp!, {{..., lr}}` at {}, `bx lr` at {}, its literal word at {} loaded by {}; no ARM B/BL, Thumb BL or pc-relative ADD in matched code targets it",
        hex(entry.start),
        hex(pool - 4),
        hex(pool),
        loads.iter().map(|at| hex(*at)).collect::<Vec<_>>().join(",")
    ))
}

fn thumb(ctx: &Ctx, entry: &Entry) -> R<String> {
    if ctx.rom.is_data(entry.start - 1) || ctx.rom.is_data(entry.end) {
        return Err(format!("{}..{} is not between two matched regions", hex(entry.start), hex(entry.end)));
    }
    let half = |at: u32| -> R<u16> { Ok(le16(ctx.rom.peek(at, 2)?, 0)) };
    let mut at = entry.start;
    if at % 4 == 2 && half(at)? == 0 {
        at += 2;
    }
    let mut functions = Vec::new();
    while at < entry.end {
        let start = at;
        let mut loads = BTreeSet::new();
        let mut branches = Vec::new();
        loop {
            if at >= entry.end {
                return Err(format!("Thumb code from {} runs to {} without a bx", hex(start), hex(entry.end)));
            }
            let instruction = half(at)?;
            if instruction & 0xF800 == 0x4800 {
                loads.insert(((at + 4) & !3) + u32::from(instruction & 0xFF) * 4);
            }
            if instruction & 0xF000 == 0xD000 && instruction & 0x0F00 < 0x0E00 {
                branches.push((at, (at as i32 + 4 + i32::from(instruction as u8 as i8) * 2) as u32));
            }
            if instruction & 0xF800 == 0xE000 {
                branches.push((at, (at as i32 + 4 + ((i32::from(instruction & 0x7FF) << 21) >> 20)) as u32));
            }
            if instruction & 0xF000 == 0xF000 || instruction & 0xFF00 == 0xDE00 || instruction & 0xFF00 == 0xDF00 {
                return Err(format!("{}: 0x{instruction:04X} (BL, undefined or SWI) in unsourced code", hex(at)));
            }
            at += 2;
            if instruction & 0xFF87 == 0x4700 {
                break;
            }
        }
        let body_end = at;
        for (from, target) in &branches {
            if !(start..body_end).contains(target) {
                return Err(format!("{}: branch to {} leaves the function at {}", hex(*from), hex(*target), hex(start)));
            }
        }
        if at < entry.end && half(at)? == 0x46C0 {
            at += 2;
        } else if at % 4 == 2 && !loads.is_empty() && half(at)? == 0 {
            at += 2;
        }
        for &target in &loads {
            if target != at {
                return Err(format!("function {}: literal at {} is not the next pool word {}", hex(start), hex(target), hex(at)));
            }
            let value = u32_at(ctx, at)?;
            if ctx.rom.is_data(value) && unread(ctx, value) {
                return Err(format!("function {}: pool word {} points at unread ROM data {}", hex(start), hex(at), hex(value)));
            }
            at += 4;
        }
        functions.push(start);
    }
    if at != entry.end {
        return Err(format!("Thumb functions end at {}, not {}", hex(at), hex(entry.end)));
    }
    let callers = code_targets(ctx, entry.start, entry.end)?;
    if !callers.is_empty() {
        return Err(format!("matched code reaches {}: {}", hex(entry.start), callers.join("; ")));
    }
    Ok(format!(
        "unsourced Thumb code between matched regions: {} function(s) at {}, each ending in bx with its literal pool loaded only by its own pc-relative loads; no Thumb BL, ADR, ARM B/BL or pc-relative ADD in matched code targets the range",
        functions.len(),
        functions.iter().map(|at| hex(*at)).collect::<Vec<_>>().join(",")
    ))
}

/// One menu script from `address` as RunMenuScript reads it, without claiming. Returns the address after END.
fn dry_menu_script(ctx: &Ctx, address: u32) -> R<u32> {
    let mut list_window: [Option<bool>; 256] = [None; 256];
    let mut cursor = ctx.rom.dry_cursor(address);
    loop {
        let at = cursor.address;
        let op = cursor.u8()?;
        if op > 13 {
            return Err(format!("menu script {}: opcode 0x{op:02X} at {} does not advance the cursor", hex(address), hex(at)));
        }
        let args = cursor.bytes(menu_script::OPERANDS[op as usize])?.to_vec();
        match op {
            0 => return Ok(cursor.address),
            1 => list_window[args[0] as usize] = Some((u32::from(args[5]) * 0x10) & menu_script::WINDOW_FLAG_TEXT_LIST != 0),
            3 => list_window[args[0] as usize] = None,
            5 | 9 => {
                let list = if op == 9 {
                    false
                } else {
                    match list_window[args[0] as usize] {
                        Some(list) => list,
                        None => menu_script::either_grammar(ctx, cursor.address)?.0 == "list",
                    }
                };
                if list {
                    parse_list(&mut cursor)?;
                } else {
                    parse_window(&mut cursor)?;
                }
            }
            _ => {}
        }
    }
}

fn menu(ctx: &Ctx, entry: &Entry) -> R<String> {
    if format_at(ctx, entry.start - 1).as_deref() != Some("menu_script") || ctx.rom.peek(entry.start - 1, 1)?[0] != 0 {
        return Err(format!("the byte before {} is not a menu script END", hex(entry.start)));
    }
    let mut at = entry.start;
    let mut scripts = Vec::new();
    while at < entry.end {
        scripts.push(at);
        at = dry_menu_script(ctx, at)?;
    }
    if at != entry.end {
        return Err(format!("menu scripts from {} end at {}, not {}", hex(entry.start), hex(at), hex(entry.end)));
    }
    Ok(format!(
        "{} whole menu script(s) at {} after the END of a walked menu script, each ending at its own END (RunMenuScript grammar); RunMenuScript stops at END",
        scripts.len(),
        scripts.iter().map(|at| hex(*at)).collect::<Vec<_>>().join(",")
    ))
}

fn text(ctx: &Ctx, entry: &Entry) -> R<String> {
    if format_at(ctx, entry.start - 1).as_deref() != Some(super::text::FORMAT) || ctx.rom.peek(entry.start - 1, 1)?[0] != 0 {
        return Err(format!("the byte before {} is not the 0 ending a read text", hex(entry.start)));
    }
    let mut at = entry.start;
    let mut strings = Vec::new();
    while at < entry.end {
        let mut cursor = ctx.rom.dry_cursor(at);
        strings.push(parse_window(&mut cursor)?);
        at = cursor.address;
    }
    if at != entry.end {
        return Err(format!("strings from {} end at {}, not {}", hex(entry.start), hex(at), hex(entry.end)));
    }
    Ok(format!("{} DrawWindowText string(s) {strings:?} after the 0 ending a read text; DrawWindowText stops at 0", strings.len()))
}

fn next_item(ctx: &Ctx, entry: &Entry) -> R<String> {
    let kinds = ctx.kinds_at(entry.end);
    if kinds.is_empty() {
        return Err(format!("no item starts at {}", hex(entry.end)));
    }
    Ok(format!("{}@{}", kinds.join("+"), hex(entry.end)))
}

fn credits_tail(ctx: &Ctx, entry: &Entry) -> R<String> {
    if format_at(ctx, entry.start - 1).as_deref() != Some("credits") || ctx.rom.peek(entry.start - 1, 1)?[0] != 0 {
        return Err(format!("the byte before {} is not the credits stream's terminating 0", hex(entry.start)));
    }
    Ok(format!("bytes after the credits stream's terminating 0 at {} (RunCredits stops there) up to {}", hex(entry.start - 1), next_item(ctx, entry)?))
}

fn event_tail(ctx: &Ctx, env: &Env, entry: &Entry) -> R<String> {
    let command = env
        .commands
        .iter()
        .find(|command| command.end == entry.start && matches!(command.op.as_str(), "END" | "RESTART" | "CHANGE_MAP" | "RETURN_TO_TITLE" | "JUMP"))
        .ok_or_else(|| format!("no walked terminal command (END, RESTART, CHANGE_MAP, RETURN_TO_TITLE, JUMP) ends at {}", hex(entry.start)))?;
    if let Some(inside) = env.commands.iter().flat_map(|command| command.targets.iter()).find(|target| (entry.start..entry.end).contains(*target)) {
        return Err(format!("a walked successor, START_SCRIPTS or JUMP target {} is inside {}", hex(*inside), hex(entry.start)));
    }
    Ok(format!(
        "event script bytes after the terminal {} at {} of event_script@{} (its handler ends the script or moves the cursor elsewhere); no walked successor, START_SCRIPTS or JUMP target is inside; next item {}",
        command.op,
        hex(command.at),
        hex(command.item),
        next_item(ctx, entry)?
    ))
}

fn sine_tail(ctx: &Ctx, entry: &Entry) -> R<String> {
    if format_at(ctx, entry.start - 1).as_deref() != Some("table.sine") {
        return Err(format!("{} does not follow table.sine", hex(entry.start)));
    }
    let bytes = ctx.rom.peek(entry.start, entry.end - entry.start)?;
    let first = bytes.iter().position(|&byte| byte != 0).ok_or("the range is all zero")?;
    let length = bytes[first..].iter().position(|&byte| byte == 0).ok_or("the string has no NUL")?;
    let string = &bytes[first..first + length];
    if !string.iter().all(|byte| byte.is_ascii_graphic()) || !bytes[first + length..].iter().all(|&byte| byte == 0) {
        return Err("the bytes are not zero padding around one ASCII string".into());
    }
    Ok(format!("zero padding and the ASCII string \"{}\" after table.sine, whose index sin256.c masks to 0..0x40", String::from_utf8_lossy(string)))
}

fn font(ctx: &Ctx, entry: &Entry) -> R<String> {
    if format_at(ctx, entry.start - 1).as_deref() != Some("font_2bpp") || (entry.end - entry.start) % 32 != 0 {
        return Err(format!("{} does not follow read glyphs or is not whole 32-byte glyphs", hex(entry.start)));
    }
    let mut ranges = 0;
    for (kind, size) in [("table.font_sjis_ranges", 32), ("table.font_single_ranges", 16)] {
        let tables = ctx.data_of(kind);
        if tables.len() != 1 {
            return Err(format!("expected one {kind} item"));
        }
        let list = tables[0].1.as_array().ok_or_else(|| format!("{kind} has no range list"))?;
        if list.len() != FONT_RANGE_COUNT {
            return Err(format!("{kind} lists {} ranges, not FONT_RANGE_COUNT {FONT_RANGE_COUNT}", list.len()));
        }
        for range in list {
            let glyphs = parse_hex(&range["glyphs"]).ok_or("range without glyphs")?;
            let count = range["count"].as_u64().ok_or("range without count")? as u32;
            if count > 0 && glyphs < entry.end && entry.start < glyphs + count * size {
                return Err(format!("{kind} range at {} covers part of {}", hex(glyphs), hex(entry.start)));
            }
            ranges += 1;
        }
    }
    for (fallback, _) in ctx.data_of("font.sjis_fallback") {
        if fallback < entry.end && entry.start < fallback + 32 {
            return Err(format!("the 0x81A0 fallback glyph {} is inside", hex(fallback)));
        }
    }
    Ok(format!(
        "{} 2bpp glyphs after the last read Shift-JIS glyph; none of the {ranges} font ranges ExpandShiftJisGlyphTiles and ExpandSingleByteGlyphTile search covers them, and codes outside every range draw the 0x81A0 fallback glyph",
        (entry.end - entry.start) / 32
    ))
}

/// Pieces of 20 bytes until an s16 -1, then its 2 pad bytes. Returns the address after the pad.
fn sprite_frame_end(ctx: &Ctx, mut at: u32) -> R<u32> {
    while s16(ctx, at)? != -1 {
        at += 20;
    }
    if s16(ctx, at + 2)? != 0 {
        return Err(format!("frame terminator at {} is not followed by 2 zero bytes", hex(at)));
    }
    Ok(at + 4)
}

fn sprite_set(ctx: &Ctx, entry: &Entry) -> R<String> {
    let mut at = entry.start;
    let mut frames = Vec::new();
    while !(entry.start..at).contains(&u32_at(ctx, at)?) {
        frames.push(at);
        at = sprite_frame_end(ctx, at)?;
    }
    let mut frame_table = Vec::new();
    while frames.contains(&u32_at(ctx, at)?) {
        frame_table.push(u32_at(ctx, at)?);
        at += 4;
    }
    let mut animations = Vec::new();
    let mut frame_ids = BTreeSet::new();
    while !(entry.start..at).contains(&u32_at(ctx, at)?) {
        animations.push(at);
        while s16(ctx, at)? != -1 {
            frame_ids.insert(s16(ctx, at)?);
            at += 4;
        }
        if s16(ctx, at + 2)? != 0 {
            return Err(format!("animation terminator at {} is not followed by 2 zero bytes", hex(at)));
        }
        at += 4;
    }
    let mut animation_table = 0;
    while at < entry.end {
        if !animations.contains(&u32_at(ctx, at)?) {
            return Err(format!("{}: 0x{:08X} is not an animation of the set", hex(at), u32_at(ctx, at)?));
        }
        animation_table += 1;
        at += 4;
    }
    if at != entry.end || frames.is_empty() || frame_table.is_empty() || animations.is_empty() || animation_table == 0 {
        return Err(format!("{} is not one whole sprite set ending at {}", hex(entry.start), hex(entry.end)));
    }
    if frame_ids.iter().any(|&id| id < 0 || id as usize >= frame_table.len()) {
        return Err(format!("an animation at {} uses a frame id past its frame table", hex(entry.start)));
    }
    Ok(format!(
        "a whole sprite set: {} frame(s), a {}-entry frame table, {} animation(s) and a {animation_table}-entry animation table, every pointer of which stays inside the range",
        frames.len(),
        frame_table.len(),
        animations.len()
    ))
}

fn link_tag_tail(ctx: &Ctx, entry: &Entry) -> R<String> {
    let tag = entry.start - LINK_PACKET_PAYLOAD_BYTES;
    let data = ctx.data("link.tag", tag).ok_or_else(|| format!("no link.tag item at {}", hex(tag)))?;
    let (send, receive) = (data["send_copy_bytes"].as_u64().unwrap_or(0) as u32, data["receive_compare_bytes"].as_u64().unwrap_or(0) as u32);
    if send.max(receive) != LINK_PACKET_PAYLOAD_BYTES {
        return Err(format!("link.tag@{} reads {send}/{receive} bytes, not {LINK_PACKET_PAYLOAD_BYTES}", hex(tag)));
    }
    let bytes = ctx.rom.peek(tag, entry.end - tag)?;
    if bytes[..bytes.len() - 1].contains(&0) || bytes[bytes.len() - 1] != 0 {
        return Err(format!("{}..{} is not the rest of the tag string up to its NUL", hex(entry.start), hex(entry.end)));
    }
    Ok(format!(
        "the rest of the link tag string at {} past its first {LINK_PACKET_PAYLOAD_BYTES} bytes: PollLinkSend copies and PollLinkReceive compares at most LINK_PACKET_PAYLOAD_BYTES ({LINK_PACKET_PAYLOAD_BYTES}) bytes",
        hex(tag)
    ))
}

fn lz(ctx: &Ctx, entry: &Entry) -> R<String> {
    let mut at = entry.start;
    let mut blobs = Vec::new();
    while at < entry.end {
        if ctx.rom.peek(at, 1)?[0] == 0 {
            at += 1;
            continue;
        }
        if at % 4 != 0 {
            return Err(format!("{}: nonzero byte before a 4-aligned LZ77 header", hex(at)));
        }
        let (decoded, after) = bios::lz77_dry_end(ctx.rom, at, false)?;
        blobs.push(format!("{} ({} bytes decoded)", hex(at), decoded.len()));
        at = after;
    }
    if at != entry.end || blobs.is_empty() {
        return Err(format!("LZ77 streams from {} end at {}, not {}", hex(entry.start), hex(at), hex(entry.end)));
    }
    Ok(format!("zero padding and {} whole LZ77 stream(s): {}", blobs.len(), blobs.join(", ")))
}

fn sprite_frame(ctx: &Ctx, entry: &Entry) -> R<String> {
    let mut at = entry.start;
    while at % 4 != 0 && ctx.rom.peek(at, 1)?[0] == 0 {
        at += 1;
    }
    let frame = at;
    at = sprite_frame_end(ctx, at)?;
    if at != entry.end {
        return Err(format!("the frame at {} ends at {}, not {}", hex(frame), hex(at), hex(entry.end)));
    }
    Ok(format!("zero padding and one whole sprite frame at {} ({} pieces)", hex(frame), (at - 4 - frame) / 20))
}

fn frame_table_tail(ctx: &Ctx, entry: &Entry) -> R<String> {
    let (table, frames) = ctx
        .data_of("sprite.frame_table")
        .into_iter()
        .filter_map(|(address, data)| Some((address, data["frames"].as_u64()? as u32)))
        .find(|(address, frames)| address + frames * 4 == entry.start)
        .ok_or_else(|| format!("{} does not follow the read entries of a sprite.frame_table", hex(entry.start)))?;
    if entry.end != entry.start + 4 {
        return Err("a frame table tail must be one word".into());
    }
    let target = u32_at(ctx, entry.start)?;
    let points = mine(target).filter(|range| range.kind == Kind::SpriteFrame).ok_or_else(|| format!("the word points at {}, not a frame declared here", hex(target)))?;
    Ok(format!(
        "entry {frames} of sprite.frame_table@{}, past the largest frame id ({}) of the animations ported with it; UpdateSpritesAndBuildOam reads frame_table[frame id of the current animation command] (update_sprites_and_build_oam.c); it points at {} (declared here)",
        hex(table),
        frames - 1,
        hex(points.start)
    ))
}

fn palettes(ctx: &Ctx, entry: &Entry) -> R<String> {
    let mut at = entry.start;
    while at % 4 != 0 && ctx.rom.peek(at, 1)?[0] == 0 {
        at += 1;
    }
    if (entry.end - at) % 32 != 0 {
        return Err(format!("{}..{} is not whole 32-byte palettes", hex(at), hex(entry.end)));
    }
    if ctx.rom.peek(at, entry.end - at)?.chunks(2).any(|color| le16(color, 0) & 0x8000 != 0) {
        return Err("a color has bit 15 set".into());
    }
    for (animation, _) in ctx.data_of("field_map.palette_animation") {
        if animation < entry.end && entry.start < animation + FIELD_PALETTE_FRAMES * 32 {
            return Err(format!("field palette animation {} with a u8 frame reaches {}", hex(animation), hex(entry.start)));
        }
    }
    Ok(format!(
        "zero padding and {} 32-byte BGR555 palettes; the field palette animations UpdateFieldDisplay copies read base + (u8 frame << 5), which ends before this range",
        (entry.end - at) / 32
    ))
}

fn song_track(ctx: &Ctx, unselected: &Unselected, entry: &Entry) -> R<String> {
    for (header, count, read, _) in &unselected.songs {
        for slot in *read..*count {
            if u32_at(ctx, header + 8 + 4 * slot)? == entry.start && mine(header + 8 + 4 * slot).is_some_and(|range| range.kind == Kind::SongSlots) {
                return Ok(format!("the music track only slot {slot} of mp2k.song@{} points to; that slot is past the {read} slots StartMusicPlayer reads (declared here)", hex(*header)));
            }
        }
    }
    Err(format!("no unread song header slot points at {}", hex(entry.start)))
}

fn song_slots(entry: &Entry, unselected: &Unselected) -> R<String> {
    for (header, count, read, players) in &unselected.songs {
        if entry.start == header + 8 + 4 * read && entry.end == header + 8 + 4 * count {
            return Ok(format!(
                "track pointer slots {read}..{} of mp2k.song@{} (track_count {count}): StartMusicPlayer reads min(track_count, the player's track_count) = {read} slots; players {players}",
                count - 1,
                hex(*header)
            ));
        }
    }
    Err(format!("{} is not the unread track slots of a song header", hex(entry.start)))
}

fn sram_library(ctx: &Ctx, entry: &Entry) -> R<String> {
    let bytes = ctx.rom.peek(entry.start, entry.end - entry.start)?;
    let length = bytes.iter().position(|&byte| byte == 0).ok_or("no NUL")?;
    let id = &bytes[..length];
    if length == 0 || !id.iter().all(|byte| byte.is_ascii_graphic()) || (entry.start + length as u32 + 1) % 4 != 0 {
        return Err("the range does not start with an ASCII ID string ending on a word boundary".into());
    }
    let words = (entry.end - entry.start - length as u32 - 1) / 4;
    if !ctx.kinds_at(entry.end).iter().any(|kind| kind == crate::rom::NEUTRAL) {
        return Err(format!("no copy starts at {}", hex(entry.end)));
    }
    Ok(format!(
        "the library ID string \"{}\" and {words} words after it; InitSramAccess takes its copy sources and destinations from literals (init_sram_access.c) and InitializeEngine's DMA copy starts at {} (initialize_engine.c)",
        String::from_utf8_lossy(id),
        hex(entry.end)
    ))
}

fn encounter_tail(ctx: &Ctx, entry: &Entry) -> R<String> {
    let record = entry.start - 6;
    if (record..entry.start).any(|address| format_at(ctx, address).as_deref() != Some("table.field_encounter_definitions")) || le16(ctx.rom.peek(record, 2)?, 0) != 0 {
        return Err(format!("the 6 bytes before {} are not the map_id 0 record of table.field_encounter_definitions", hex(entry.start)));
    }
    Ok(format!("bytes after the map_id 0 record at {} that ends the field encounter definitions (the encounter lookup stops there) up to {}", hex(record), next_item(ctx, entry)?))
}

fn battle_scripts(ctx: &Ctx, entry: &Entry) -> R<String> {
    if format_at(ctx, entry.start - 2).as_deref() != Some("battle_animation_script") || s16(ctx, entry.start - 2)? != -1 {
        return Err(format!("{} does not follow a battle animation script's -1", hex(entry.start)));
    }
    if !ctx.kinds_at(entry.end).iter().any(|kind| kind == "battle_animation.script") {
        return Err(format!("no battle animation script starts at {}", hex(entry.end)));
    }
    let mut at = entry.start;
    let mut scripts = Vec::new();
    while at < entry.end {
        scripts.push(at);
        at += 2;
        loop {
            match s16(ctx, at)? {
                -1 => {
                    at += 2;
                    break;
                }
                -2 => at += 4,
                _ => at += 8,
            }
            if at >= entry.end {
                return Err(format!("the script at {} runs past {}", hex(*scripts.last().unwrap()), hex(entry.end)));
            }
        }
    }
    if at != entry.end {
        return Err(format!("battle animation scripts from {} end at {}, not {}", hex(entry.start), hex(at), hex(entry.end)));
    }
    Ok(format!(
        "{} whole battle animation script(s) at {} (s16 header, spawn/loop commands, -1), between walked scripts",
        scripts.len(),
        scripts.iter().map(|at| hex(*at)).collect::<Vec<_>>().join(",")
    ))
}

fn run(ctx: &Ctx) -> R<()> {
    for pair in RANGES.windows(2) {
        if pair[0].end > pair[1].start {
            return Err(format!("ranges {} and {} overlap or are out of order", hex(pair[0].start), hex(pair[1].start)));
        }
    }
    for entry in RANGES {
        if entry.start < entry.end && entry.start < MUSIC_WINDOW.1 && MUSIC_WINDOW.0 < entry.end {
            return Err(format!("{} is inside the music window", hex(entry.start)));
        }
        if let Some(address) = (entry.start..entry.end).find(|&address| !unread(ctx, address)) {
            return Err(format!("{}..{}: {} is code or read by a port", hex(entry.start), hex(entry.end), hex(address)));
        }
    }
    let by_address = ctx.roots.by_address();
    for entry in RANGES {
        if let Some((address, references)) = by_address.range(entry.start..entry.end).next() {
            return Err(format!("{} is referenced by the decomp source ({})", hex(*address), references[0].location()));
        }
    }

    let env = Env::new(ctx)?;
    let unselected = Unselected::new(ctx, &env)?;
    let mut hits: BTreeMap<usize, Vec<u32>> = BTreeMap::new();
    for offset in 0..ROM_SIZE - 3 {
        let value = ctx.rom.scan_word(BASE + offset).unwrap();
        let index = RANGES.partition_point(|entry| entry.start <= value);
        if index > 0 && value < RANGES[index - 1].end {
            hits.entry(index - 1).or_default().push(BASE + offset);
        }
    }

    let mut failures = Vec::new();
    for (index, entry) in RANGES.iter().enumerate() {
        let structure = match entry.kind {
            Kind::Header => header(ctx, entry),
            Kind::ArmReturn => arm_return(ctx, entry),
            Kind::ArmRoutine => arm_routine(ctx, entry),
            Kind::Thumb => thumb(ctx, entry),
            Kind::Menu => menu(ctx, entry),
            Kind::Text => text(ctx, entry),
            Kind::CreditsTail => credits_tail(ctx, entry),
            Kind::EventTail => event_tail(ctx, &env, entry),
            Kind::SineTail => sine_tail(ctx, entry),
            Kind::Font => font(ctx, entry),
            Kind::SpriteSet => sprite_set(ctx, entry),
            Kind::LinkTagTail => link_tag_tail(ctx, entry),
            Kind::Lz => lz(ctx, entry),
            Kind::SpriteFrame => sprite_frame(ctx, entry),
            Kind::FrameTableTail => frame_table_tail(ctx, entry),
            Kind::Palettes => palettes(ctx, entry),
            Kind::SongTrack => song_track(ctx, &unselected, entry),
            Kind::SongSlots => song_slots(entry, &unselected),
            Kind::SramLibrary => sram_library(ctx, entry),
            Kind::EncounterTail => encounter_tail(ctx, entry),
            Kind::BattleScripts => battle_scripts(ctx, entry),
        }
        .map_err(|error| format!("{}..{} ({:?}): {error}", hex(entry.start), hex(entry.end), entry.kind));
        let structure = match structure {
            Ok(text) => text,
            Err(error) => {
                failures.push(error);
                continue;
            }
        };
        let mut failed = false;
        let mut kinds: BTreeMap<String, Vec<u32>> = BTreeMap::new();
        for &at in hits.get(&index).into_iter().flatten() {
            let why = match disposition(ctx, &env, &unselected, at) {
                Ok(why) => why,
                Err(error) => {
                    failures.push(format!("{}..{} ({:?}) is referenced: {error}", hex(entry.start), hex(entry.end), entry.kind));
                    failed = true;
                    continue;
                }
            };
            kinds.entry(why).or_default().push(at);
        }
        if failed {
            continue;
        }
        let references = if kinds.is_empty() {
            "no 4-byte value anywhere in the ROM equals an address inside".to_string()
        } else {
            let list: Vec<String> = kinds.iter().map(|(why, list)| format!("{} word(s) [{}]: {why}", list.len(), list.iter().take(3).map(|at| hex(*at)).collect::<Vec<_>>().join(","))).collect();
            format!("4-byte values anywhere in the ROM equal to an address inside: {}", list.join("; "))
        };
        ctx.unreachable(
            entry.start,
            entry.end - entry.start,
            entry.basis,
            &format!("check {:?}: {structure}. No decomp reference falls inside; {references}", entry.kind),
        )?;
    }
    if !failures.is_empty() {
        return Err(failures.join("\n"));
    }
    Ok(())
}
