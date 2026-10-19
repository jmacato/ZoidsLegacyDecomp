//! Battles started by event scripts: every EVENT_START_BATTLE command (EventStartBattle sets the encounter group, formation,
//! terrain and options of the battle it starts) in the walked event scripts, with the maps whose script tables reach it and
//! the field scene it starts from. The scene replays one control-flow path from the script's start (and the commands of the
//! scripts that started it) to the battle: EventSpawnActor and EventRemoveActor for actors, the queued actor moves for
//! their positions (UpdateFieldActorCommands: count x 8 pixels along the direction vector; move-to targets in map cells),
//! EventLoadFieldMapAtPosition and EventChangeMap for the map, EventSetFieldViewCenterPosition and
//! EventFocusFieldCameraOnActor for the camera, EventIfPlayerInRect and EventIfInteractedActor for where the player stood,
//! and the last screen conceal before the battle.

use std::collections::{BTreeMap, BTreeSet, HashMap};

use serde_json::{json, Value};

use super::Port;
use crate::basis::Basis;
use crate::rom::R;
use crate::run::Ctx;

const START_BATTLE: Basis = Basis::C(&[
    ("src/events/commands/event_start_battle.c", "cdf93064c86327b6482d4048d0cf9c862244ee49"),
    ("src/events/event_script.h", "23f6268830cf2d663af58bc5552d8fd4105e85b2"),
    ("src/events/commands/event_spawn_actor.c", "7d5a04de0be40670bce814c005ae9445c25178c9"),
    ("src/events/commands/event_remove_actor.c", "8034b551e0c5cc6ab74e2609aba4e6ea9188a84d"),
    ("src/events/commands/event_queue_field_actor_command.c", "e326447192d2a84139ab5e9ac680accd9f110f1d"),
    ("src/field/update_field_actor_commands.c", "3df812f3f4b4d94388c22f1c11369468ff7bd85e"),
    ("src/field/create_field_actor.c", "1be55f32be3cd126a512de430bf91198751cbbe7"),
    ("src/events/commands/event_load_field_map_at_position.c", "3f4d72078671103da98b332431590b84ee2dddd1"),
    ("src/events/commands/event_set_field_view_center_position.c", "a6889c9721f04f7c216aa36bc7eb7c676c9a0ac1"),
    ("src/events/commands/event_if_player_in_rect.c", "f1dc2e8393b56464e1171ad5d9ff4c0ae77e126d"),
    ("src/events/commands/event_focus_field_camera_on_actor.c", "f9a4918dbb5958c81a69ad3a7dd159d79b67dbdd"),
]);

pub const PORT: Port = Port { name: "script_battles", bases: &[START_BATTLE], run };

const ENCOUNTER_TABLE: u32 = 0x087B_9454;
const DIRECTION_VECTORS: u32 = 0x087A_1B98;
const DIRECTION_OFFSET_BEHAVIOR: i64 = 4;
const PARENT_DEPTH: usize = 4;

struct Command {
    at: u32,
    op: String,
    args: Vec<i64>,
    next: Vec<u32>,
}

fn hex(value: &Value) -> Option<u32> { value.as_str().and_then(|text| u32::from_str_radix(text.trim_start_matches("0x"), 16).ok()) }

fn commands_of(data: &Value) -> Vec<Command> {
    data["commands"].as_array().into_iter().flatten().filter_map(|command| Some(Command {
        at: hex(&command["at"])?,
        op: command["op"].as_str()?.to_string(),
        args: command["args"].as_array().into_iter().flatten().filter_map(Value::as_i64).collect(),
        next: command["next"].as_array().into_iter().flatten().filter_map(hex).collect(),
    })).collect()
}

/// One path from the script's first command to `target`, walking predecessors and preferring the nearest earlier command.
fn path_to(commands: &[Command], target: u32) -> Vec<usize> {
    let index: HashMap<u32, usize> = commands.iter().enumerate().map(|(i, command)| (command.at, i)).collect();
    let mut predecessors: HashMap<u32, Vec<u32>> = HashMap::new();
    for command in commands {
        for next in &command.next {
            predecessors.entry(*next).or_default().push(command.at);
        }
    }
    let mut path = Vec::new();
    let mut seen = BTreeSet::new();
    let mut at = target;
    while let Some(&i) = index.get(&at) {
        if !seen.insert(at) {
            break;
        }
        path.push(i);
        let choices = predecessors.get(&at).cloned().unwrap_or_default();
        let Some(previous) = choices.iter().copied().filter(|p| *p < at && !seen.contains(p)).max().or_else(|| choices.iter().copied().find(|p| !seen.contains(p))) else { break };
        at = previous;
    }
    path.reverse();
    path
}

/// The commands that ran before `target` in `script`: first those of the script that started it (up to that start), then this
/// script's own path.
fn lead(ctx: &Ctx, scripts: &BTreeMap<u32, Vec<Command>>, script: u32, target: u32, depth: usize, out: &mut Vec<(u32, usize)>) {
    let Some(commands) = scripts.get(&script) else { return };
    if depth > 0 {
        if let Some((parent, command)) = ctx.reached_of("event_script", script).iter().find_map(|reached| {
            let rest = reached.strip_prefix("event_script@0x")?;
            let (parent, command) = rest.split_once(":0x")?;
            Some((u32::from_str_radix(parent, 16).ok()?, u32::from_str_radix(command, 16).ok()?))
        }) {
            lead(ctx, scripts, parent, command, depth - 1, out);
        }
    }
    out.extend(path_to(commands, target).into_iter().map(|i| (script, i)));
}

#[derive(Clone)]
struct Actor {
    model: i64,
    x: i64,
    y: i64,
    direction: i64,
}

fn scene(ctx: &Ctx, scripts: &BTreeMap<u32, Vec<Command>>, steps: &[(u32, usize)], start_map: Option<u32>) -> R<Value> {
    let vector = |direction: i64| -> R<(i64, i64)> {
        let at = DIRECTION_VECTORS + (direction as u32 & 7) * 8;
        let bytes = ctx.rom.peek(at, 8)?;
        Ok((i32::from_le_bytes(bytes[0..4].try_into().unwrap()) as i64, i32::from_le_bytes(bytes[4..8].try_into().unwrap()) as i64))
    };
    let mut map = start_map.map(i64::from);
    let mut actors: BTreeMap<i64, Actor> = BTreeMap::new();
    let (mut center, mut focus, mut conceal): (Option<(i64, i64)>, Option<i64>, Option<(String, String, Option<i64>)>) = (None, None, None);
    let (mut trigger, mut talked_to, mut song): (Option<[i64; 4]>, Option<i64>, Option<i64>) = (None, None, None);
    let steps: Vec<&Command> = steps.iter().map(|(script, i)| &scripts[script][*i]).collect();
    let Some((_, before)) = steps.split_last() else { return Ok(Value::Null) };
    for command in before {
        let cell = if map == Some(0) { 16 } else { 8 };
        let args = &command.args;
        let arg = |i: usize| args.get(i).copied().unwrap_or(0);
        match command.op.as_str() {
            "SPAWN_ACTOR" if args.len() >= 6 && arg(0) <= 0xC => {
                let (mut x, mut y) = (arg(2) * cell, arg(3) * cell);
                if arg(5) == DIRECTION_OFFSET_BEHAVIOR {
                    let (dx, dy) = vector(arg(4))?;
                    x += (dx << 4) >> 8;
                    y += (dy << 4) >> 8;
                }
                actors.insert(arg(0), Actor { model: arg(1), x, y, direction: arg(4) });
            }
            "REMOVE_ACTOR" => { actors.remove(&arg(0)); }
            op if op.starts_with("QUEUE_ACTOR_MOVE_TO_") => {
                if let Some(actor) = actors.get_mut(&arg(0)) {
                    actor.x = arg(1) * cell;
                    actor.y = arg(2) * cell;
                }
            }
            op if op.starts_with("QUEUE_ACTOR_MOVE_") => {
                let (dx, dy) = vector(arg(1))?;
                if let Some(actor) = actors.get_mut(&arg(0)) {
                    actor.x += (dx * arg(2) * 8) >> 8;
                    actor.y += (dy * arg(2) * 8) >> 8;
                    actor.direction = arg(1);
                }
            }
            "LOAD_FIELD_MAP_AT_POSITION" | "CHANGE_MAP" => {
                map = Some(arg(0));
                let cell = if arg(0) == 0 { 16 } else { 8 };
                let player = actors.get(&0).cloned();
                actors.clear();
                if let Some(player) = player {
                    actors.insert(0, Actor { x: arg(1) * cell, y: arg(2) * cell, ..player });
                }
                center = None;
                focus = None;
                trigger = None;
                talked_to = None;
            }
            "IF_PLAYER_IN_RECT" => trigger = Some([arg(0) * cell, arg(1) * cell, arg(2) * cell + cell, arg(3) * cell + cell]),
            "IF_INTERACTED_ACTOR" => talked_to = Some(arg(0)),
            "PLAY_SONG" => song = Some(arg(0)),
            "SET_FIELD_VIEW_CENTER_POSITION" => { center = Some((arg(0) * cell, arg(1) * cell)); focus = None; }
            "FOCUS_FIELD_CAMERA_ON_ACTOR" => { focus = Some(arg(0)); center = None; }
            "START_BATTLE" => conceal = None,
            op if op.starts_with("REVEAL_FIELD_WITH_") || op.starts_with("FADE_SCREEN_FROM_") => conceal = None,
            op if op.starts_with("CONCEAL_FIELD_WITH_") || op.starts_with("FADE_SCREEN_TO_") => conceal = Some((op.to_string(), format!("0x{:08X}", command.at), args.first().copied())),
            _ => {}
        }
    }
    Ok(json!({
        "map": map,
        "actors": actors.iter().map(|(id, actor)| json!([id, actor.model, actor.x, actor.y, actor.direction])).collect::<Vec<_>>(),
        "center": center.map(|(x, y)| json!([x, y])),
        "focus": focus,
        "conceal": conceal.map(|(op, at, duration)| json!([op, at, duration])),
        "trigger": trigger,
        "talked_to": talked_to,
        "song": song,
    }))
}

fn run(ctx: &Ctx) -> R<()> {
    let (formations_id, _) = ctx.item("table.encounter_formations", ENCOUNTER_TABLE, START_BATTLE, Vec::new());
    let scripts: BTreeMap<u32, Vec<Command>> = ctx.data_of("event_script").into_iter().map(|(script, data)| (script, commands_of(&data))).collect();
    let mut battles = Vec::new();
    for (script, commands) in &scripts {
        for command in commands.iter().filter(|command| command.op == "START_BATTLE") {
            let [group, formation, terrain, options] = command.args[..] else { return Err(format!("START_BATTLE at 0x{:08X} has {} operands", command.at, command.args.len()).into()) };
            let maps: BTreeSet<u32> = super::song_uses::script_maps(ctx, *script, &mut BTreeSet::new());
            let mut steps = Vec::new();
            lead(ctx, &scripts, *script, command.at, PARENT_DEPTH, &mut steps);
            let field = scene(ctx, &scripts, &steps, maps.iter().next().copied())?;
            battles.push(json!({ "script": script, "at": format!("0x{:08X}", command.at), "group": group, "formation": formation, "terrain": terrain, "options": options, "maps": maps, "field": field }));
        }
    }
    ctx.view(formations_id, json!({ "t": "script_battles", "battles": battles }));
    Ok(())
}
