//! ROM tables read by event command handlers: EventSetFlag's unlock bits, EventCallSceneFunction's scene functions
//! (indexed by the operands of the walked event scripts), the Fuzor component models, the structure shake steps,
//! the Pulse confirmation text printed through the menu buffer, and the world-map distortion scene's tilemap.

use std::collections::BTreeMap;

use serde_json::{json, Value};

use super::graphics::lz77_item;
use super::{bios, text, Port};
use crate::basis::Basis;
use crate::rom::{le32, R};
use crate::run::Ctx;
use crate::{repo_root, verify_c, BASE};

const EVENT_H: (&str, &str) = ("src/events/event_script.h", "23f6268830cf2d663af58bc5552d8fd4105e85b2");
const MENU_C: (&str, &str) = ("src/ui/run_menu_script.c", "2cfb02f8be3d3b225ceb631e8fd18bbfe81cbca2");
const MENU_H: (&str, &str) = ("src/ui/menu_script.h", "65aa843d8d8bbeedb7243cac0cf6ca75fc589463");

const SET_FLAG: Basis = Basis::C(&[("src/events/commands/event_set_flag.c", "98823a316d940688cd12f8c7f2369a4546ab15fb"), EVENT_H]);
const SCENE_FUNCTIONS: Basis = Basis::C(&[("src/events/commands/event_call_scene_function.c", "02723b69d214eb63ae7d3f4bce88bb64e624370c"), EVENT_H]);
const FUZOR: Basis = Basis::C(&[("src/events/commands/event_set_battle_fuzor_component_models.c", "ad767816619829fd0eadff3eb9589a9ac20739b6"), EVENT_H]);
const SHAKE: Basis = Basis::C(&[("src/events/commands/event_show_world_map_structure_appearance.c", "c95a611325ad356555ea91b8430e5ac7ec9bf054")]);
const CONFIRM: Basis = Basis::C(&[
    ("src/events/commands/event_offer_pulse_emotion_growth.c", "64f7f8f426d05dba7060991896ae51c3052d7d33"),
    EVENT_H,
    MENU_C,
    MENU_H,
    ("src/ui/draw_window_text.c", "e61d2cdddb1782410db0393ca1ea434d4defdb93"),
]);
const DISTORTION: Basis = Basis::C(&[("src/events/scenes/play_world_map_distortion_scene.c", "22849365a718b2235b4df8fcbf8e2624aa485cbb")]);

pub const PORT: Port = Port { name: "event_tables", bases: &[SET_FLAG, SCENE_FUNCTIONS, FUZOR, SHAKE, CONFIRM, DISTORTION, bios::LZ77_VRAM], run };

const HANDLERS: u32 = 0x087A_190C;
const OP_SET_FLAG: u8 = 0x1E;
const OP_CALL_SCENE_FUNCTION: u8 = 0x84;
const FLAG_UNLOCKS: u32 = 0x087A_1894;
const SCENE_FUNCTION_TABLE: u32 = 0x087A_1B6C;
/// EVENT_FUZOR_COMPONENT_MODELS_ROM, read for unit_slot 0..5.
const FUZOR_MODELS: u32 = 0x087A_18E0;
const FUZOR_UNIT_SLOTS: u32 = 6;
/// EventShowWorldMapStructureAppearance reads s32 steps while carrier_r6 <= 8.
const SHAKE_STEPS: u32 = 0x087A_18E8;
const SHAKE_STEP_COUNT: u32 = 9;
/// EVENT_PULSE_CONFIRM_EMOTION_TEXT, stored to EVENT_PLAYER_ASSET_MESSAGE_POINTER_RAM before RunMenuScript(0x080177D5).
const CONFIRM_TEXT: u32 = 0x0810_3D60;
const CONFIRM_MENU: u32 = 0x0801_77D5;
const MENU_CLEAR_WINDOW: u8 = 2;
const MENU_PRINT_BUFFER: u8 = 6;
const MENU_END: u8 = 0;
/// PlayWorldMapDistortionScene: BiosLz77ToVram(0x0842295C, 0x0600F000), a BG tilemap (it then ORs 0xC000 into 0x200 entries).
const DISTORTION_TILEMAP: u32 = 0x0842_295C;
const DISTORTION_TILEMAP_VRAM: u32 = 0x0600_F000;

/// Every EVENT_ name enum EventOpcode gives `value`.
fn opcode_names(value: u8) -> R<Vec<String>> {
    let text = std::fs::read_to_string(repo_root().join(EVENT_H.0)).map_err(|error| error.to_string())?;
    let mut names = Vec::new();
    for line in text.lines().take_while(|line| !line.contains("EVENT_SCAN_NEXT")) {
        let Some((name, number)) = line.trim().trim_end_matches(',').split_once('=') else { continue };
        let name = name.trim();
        if let (true, Some(Ok(number))) = (name.starts_with("EVENT_"), number.trim().strip_prefix("0x").map(|hex| u8::from_str_radix(hex, 16))) {
            if number == value {
                names.push(name.trim_start_matches("EVENT_").to_string());
            }
        }
    }
    Ok(names)
}

/// The first operand byte of every walked command with this opcode, with where it was executed.
fn operands(ctx: &Ctx, op: u8, source: &str) -> R<BTreeMap<u8, Vec<String>>> {
    let names = opcode_names(op)?;
    if names.len() != 1 {
        return Err(format!("opcode 0x{op:02X} has names {names:?} in enum EventOpcode"));
    }
    let regions = verify_c::regions(&repo_root().join("regions.txt"))?;
    let handler = le32(ctx.rom.peek(HANDLERS + u32::from(op) * 4, 4)?, 0);
    let offset = (handler & !1).wrapping_sub(BASE);
    if !regions.iter().any(|region| region.start == offset && region.sources.iter().any(|file| file == source)) {
        return Err(format!("opcode 0x{op:02X}: handler 0x{handler:08X} is not the start of {source}"));
    }
    let mut out: BTreeMap<u8, Vec<String>> = BTreeMap::new();
    for (script, data) in ctx.data_of("event_script") {
        for command in data["commands"].as_array().into_iter().flatten() {
            if command["op"].as_str() != Some(names[0].as_str()) {
                continue;
            }
            let value = command["args"].get(0).and_then(Value::as_u64).ok_or_else(|| format!("event_script@0x{script:08X}: {} without an operand", names[0]))?;
            out.entry(value as u8).or_default().push(format!("event_script@0x{script:08X}:{}", command["at"].as_str().unwrap_or("")));
        }
    }
    Ok(out)
}

/// EventSetFlag: reads flag_id of every {flag_id, unlock_bit} entry up to the 0 flag_id, and unlock_bit of entries
/// whose flag_id is the command's.
fn flag_unlocks(ctx: &Ctx) -> R<()> {
    const KIND: &str = "table.event_flag_unlock_bits";
    let flags = operands(ctx, OP_SET_FLAG, "events/commands/event_set_flag.c")?;
    let (id, _) = ctx.item(KIND, FLAG_UNLOCKS, SET_FLAG, ctx.roots.require(FLAG_UNLOCKS)?);
    let mut entries = Vec::new();
    for index in 0..=0xFFu32 {
        let at = FLAG_UNLOCKS + index * 2;
        let flag = ctx.rom.claim(at, 1, KIND, id)?[0];
        if flag == 0 {
            ctx.count(id, &format!("terminator:flag_id 0 at entry {index}; unlock_bit read for flag ids set by walked SET_FLAG commands"));
            ctx.set(id, json!({ "entry_bytes": 2, "entries": entries, "set_flag_operands": flags.keys().collect::<Vec<_>>() }));
            return Ok(());
        }
        let mut entry = json!({ "flag_id": flag });
        if flags.contains_key(&flag) {
            entry["unlock_bit"] = json!(ctx.rom.claim(at + 1, 1, KIND, id)?[0]);
        }
        entries.push(entry);
    }
    Err(format!("flag unlock table 0x{FLAG_UNLOCKS:08X}: the u8 index wraps before a flag_id 0"))
}

/// EventCallSceneFunction: CallFunctionR0(gEventSceneFunctions[function_index]).
fn scene_functions(ctx: &Ctx) -> R<()> {
    const KIND: &str = "table.event_scene_functions";
    let indexes = operands(ctx, OP_CALL_SCENE_FUNCTION, "events/commands/event_call_scene_function.c")?;
    let (id, _) = ctx.item(KIND, SCENE_FUNCTION_TABLE, SCENE_FUNCTIONS, ctx.roots.require(SCENE_FUNCTION_TABLE)?);
    let regions = verify_c::regions(&repo_root().join("regions.txt"))?;
    let mut entries = Vec::new();
    for (&index, from) in &indexes {
        let function = le32(ctx.rom.claim(SCENE_FUNCTION_TABLE + u32::from(index) * 4, 4, KIND, id)?, 0);
        let offset = (function & !1).wrapping_sub(BASE);
        let region = regions.iter().find(|region| region.start == offset).filter(|_| function & 1 == 1);
        let Some(region) = region else {
            return Err(format!("scene function {index} = 0x{function:08X} is not a Thumb entry at the start of a matched region"));
        };
        entries.push(json!({ "index": index, "function": format!("0x{function:08X}"), "source": region.sources, "called_from": from }));
    }
    ctx.count(id, "c_index:function_index operands of walked CALL_SCENE_FUNCTION commands");
    ctx.set(id, json!({ "entry_bytes": 4, "entries": entries }));
    Ok(())
}

fn fuzor_models(ctx: &Ctx) -> R<()> {
    const KIND: &str = "table.fuzor_component_models";
    let (id, _) = ctx.item(KIND, FUZOR_MODELS, FUZOR, ctx.roots.require(FUZOR_MODELS)?);
    let models = ctx.rom.claim(FUZOR_MODELS, FUZOR_UNIT_SLOTS, KIND, id)?.to_vec();
    ctx.count(id, "c_loop_bound:unit_slot <= 5 (EventSetBattleFuzorComponentModels)");
    ctx.set(id, json!({ "entry_bytes": 1, "model_by_unit_slot": models, "note": "0 skips the slot" }));
    Ok(())
}

fn shake_steps(ctx: &Ctx) -> R<()> {
    const KIND: &str = "table.world_map_structure_shake_steps";
    let (id, _) = ctx.item(KIND, SHAKE_STEPS, SHAKE, ctx.roots.require(SHAKE_STEPS)?);
    let data = ctx.rom.claim(SHAKE_STEPS, SHAKE_STEP_COUNT * 4, KIND, id)?;
    let steps: Vec<i32> = (0..SHAKE_STEP_COUNT as usize).map(|index| le32(data, index * 4) as i32).collect();
    ctx.count(id, "c_loop_bound:carrier_r6 <= 8 (one step per frame while the dust sprite is active)");
    ctx.set(id, json!({ "entry_bytes": 4, "bg_y_fixed8_steps": steps }));
    Ok(())
}

/// PRINT_BUFFER prints the text at EVENT_PLAYER_ASSET_MESSAGE_POINTER_RAM with the list parser when the window has
/// flag 0x80, else DrawWindowText. Window 2's flags come from earlier scripts, so both parsers must stop at one byte.
fn confirm_text(ctx: &Ctx) -> R<()> {
    let menu = ctx.rom.peek(CONFIRM_MENU, 5)?;
    if menu[0] != MENU_CLEAR_WINDOW || menu[2] != MENU_PRINT_BUFFER || menu[3] != menu[1] || menu[4] != MENU_END {
        return Err(format!("menu script 0x{CONFIRM_MENU:08X} is not CLEAR_WINDOW, PRINT_BUFFER, END on one window"));
    }
    let mut window = ctx.rom.dry_cursor(CONFIRM_TEXT);
    let mut list = ctx.rom.dry_cursor(CONFIRM_TEXT);
    let as_window = text::parse_window(&mut window);
    let as_list = text::parse_list(&mut list);
    if as_window.is_err() || as_list.is_err() || window.address != list.address {
        return Err(format!("menu buffer text 0x{CONFIRM_TEXT:08X}: DrawWindowText and the list parser do not stop at the same byte"));
    }
    let mut reached = ctx.roots.require(CONFIRM_TEXT)?;
    reached.push(format!("menu_script@0x{CONFIRM_MENU:08X}"));
    let (id, new) = ctx.item("text.menu_buffer", CONFIRM_TEXT, CONFIRM, reached);
    if new {
        let rendered = text::parse_window(&mut ctx.rom.cursor(CONFIRM_TEXT, text::FORMAT, id))?;
        ctx.count(id, "terminator");
        ctx.set(id, json!({ "text": rendered, "grammar": "either", "menu_script": format!("0x{CONFIRM_MENU:08X}"), "window": menu[1] }));
    }
    Ok(())
}

fn run(ctx: &Ctx) -> R<()> {
    flag_unlocks(ctx)?;
    scene_functions(ctx)?;
    fuzor_models(ctx)?;
    shake_steps(ctx)?;
    confirm_text(ctx)?;
    lz77_item(ctx, DISTORTION_TILEMAP, true, DISTORTION, "tilemap", Some(DISTORTION_TILEMAP_VRAM), ctx.roots.require(DISTORTION_TILEMAP)?)?;
    Ok(())
}
