//! Where each song plays: the map music byte (+0x1E) of every field map definition, the battle music byte (+0) of every
//! encounter formation (run_battle.c plays it), EVENT_PLAY_SONG operands in the walked event scripts (with the maps whose
//! script tables reach them), and constant song ids reaching PlaySong and PlayOrContinueSong in the matched code, directly
//! or through a callee given constant arguments (PlaySongAndWait and similar wrappers).

use std::collections::{BTreeMap, BTreeSet};

use serde_json::json;

use super::Port;
use crate::basis::Basis;
use crate::rom::R;
use crate::run::Ctx;
use crate::thumb::Code;

const USES: Basis = Basis::C(&[
    ("src/events/commands/event_play_song.c", "40bb29ae9a49ce91df32b04eb1f611ce77156d83"),
    ("src/events/event_script.h", "23f6268830cf2d663af58bc5552d8fd4105e85b2"),
    ("src/events/commands/event_play_map_music.c", "ad13eec87f8ed327f3ee94a0dbee9559c42f1632"),
    ("src/audio/play_song.c", "d87090a7431c51a5f54105eccda736c5536445c3"),
    ("src/audio/play_or_continue_song.c", "ae79a32d6eb46c745d7c07586737973a16d3434c"),
    ("src/game/modes/run_battle.c", "133d0dd6c3a4eb5492f36d7d6b72b6d66d951ddb"),
]);

pub const PORT: Port = Port { name: "song_uses", bases: &[USES], run };

const SONG_TABLE: u32 = 0x086A_46C4;
const MAP_DEFINITIONS: u32 = 0x087C_4434;
const MAP_RECORD: u32 = 32;
const MAP_SONG: u32 = 0x1E;
const PLAY_SONG: u32 = 0x0809_2E84;
const PLAY_OR_CONTINUE_SONG: u32 = 0x0809_2E74;
const ENCOUNTER_TABLE: u32 = 0x087B_9454;
const WRAPPER_DEPTH: usize = 2;

#[derive(Default)]
struct Uses {
    maps: BTreeSet<u32>,
    battles: Vec<(u32, u32, Vec<u32>)>,
    scripts: BTreeMap<u32, BTreeSet<u32>>,
    code: BTreeSet<String>,
}

/// Constant song ids a call with these arguments passes to PlaySong or PlayOrContinueSong, with the site of that final
/// call, following callees that are given constant arguments up to WRAPPER_DEPTH calls deep.
fn songs_reached(code: &Code, call: &crate::thumb::Call, depth: usize, out: &mut BTreeSet<(u32, u32)>) {
    if call.target == PLAY_SONG || call.target == PLAY_OR_CONTINUE_SONG {
        if let Some(song) = call.args[0].c() {
            out.insert((song & 0xFFFF, call.site));
        }
        return;
    }
    if depth == 0 || call.args.iter().all(|value| value.c().is_none()) {
        return;
    }
    let Some(function) = code.function_at(call.target) else { return };
    let Ok(analysis) = code.analyze(function, &call.args) else { return };
    for inner in &analysis.calls {
        songs_reached(code, inner, depth - 1, out);
    }
}

/// The maps whose map_event_scripts entries reach an event script, following event_script@parent:command links upward.
pub(crate) fn script_maps(ctx: &Ctx, script: u32, seen: &mut BTreeSet<u32>) -> BTreeSet<u32> {
    let mut maps = BTreeSet::new();
    if !seen.insert(script) {
        return maps;
    }
    for reached in ctx.reached_of("event_script", script) {
        if let Some(rest) = reached.strip_prefix("table.map_event_scripts@") {
            if let Some(index) = rest.split('[').nth(1).and_then(|part| part.trim_end_matches(']').parse::<u32>().ok()) {
                maps.insert(index);
            }
        } else if let Some(rest) = reached.strip_prefix("event_script@0x") {
            if let Ok(parent) = u32::from_str_radix(rest.split(':').next().unwrap_or(""), 16) {
                maps.extend(script_maps(ctx, parent, seen));
            }
        }
    }
    maps
}

fn run(ctx: &Ctx) -> R<()> {
    let (songs_id, _) = ctx.item("table.songs", SONG_TABLE, USES, Vec::new());
    let mut uses: BTreeMap<u32, Uses> = BTreeMap::new();
    let maps = ctx.data("table.field_map_definitions", MAP_DEFINITIONS).and_then(|data| data["maps"].as_u64()).ok_or("table.field_map_definitions has no map count")? as u32;
    for map in 0..maps {
        let song = u32::from(ctx.rom.peek(MAP_DEFINITIONS + map * MAP_RECORD + MAP_SONG, 1)?[0]);
        uses.entry(song).or_default().maps.insert(map);
    }
    let formations = ctx.data("table.encounter_formations", ENCOUNTER_TABLE).ok_or("table.encounter_formations has no records")?;
    for record in formations["records"].as_array().into_iter().flatten() {
        let (Some(song), Some(group), Some(encounter)) = (record["song_id"].as_u64(), record["group"].as_u64(), record["encounter"].as_u64()) else { continue };
        let zoids: Vec<u32> = record["units"].as_array().into_iter().flatten().filter_map(|unit| unit["zoid_id"].as_u64()).filter(|zoid| *zoid != 0).map(|zoid| zoid as u32).collect();
        if !zoids.is_empty() {
            uses.entry(song as u32).or_default().battles.push((group as u32, encounter as u32, zoids));
        }
    }
    for (script, data) in ctx.data_of("event_script") {
        for command in data["commands"].as_array().into_iter().flatten() {
            if command["op"] != "PLAY_SONG" {
                continue;
            }
            let Some(song) = command["args"].get(0).and_then(|value| value.as_u64()) else { continue };
            let found = script_maps(ctx, script, &mut BTreeSet::new());
            uses.entry(song as u32).or_default().scripts.entry(script).or_default().extend(found);
        }
    }
    let regions = crate::verify_c::regions(&crate::repo_root().join("regions.txt"))?;
    let code = Code::new(ctx.rom)?;
    for function in &code.functions {
        let Ok(analysis) = code.analyze(*function, &Default::default()) else { continue };
        for call in &analysis.calls {
            let mut songs = BTreeSet::new();
            songs_reached(&code, call, WRAPPER_DEPTH, &mut songs);
            let file_of = |site: u32| regions.iter().find(|region| region.start <= site - crate::BASE && site - crate::BASE < region.end).and_then(|region| region.sources.first()).cloned();
            for (song, site) in songs {
                let Some(leaf) = file_of(site) else { continue };
                let file = if leaf.starts_with("audio/") { file_of(call.site).unwrap_or(leaf) } else { leaf };
                uses.entry(song).or_default().code.insert(file);
            }
        }
    }
    let listed: Vec<_> = uses.iter().map(|(song, found)| json!([song, {
        "maps": found.maps,
        "battles": found.battles.iter().map(|(group, encounter, zoids)| json!([group, encounter, zoids])).collect::<Vec<_>>(),
        "scripts": found.scripts.iter().map(|(script, maps)| json!([script, maps])).collect::<Vec<_>>(),
        "code": found.code,
    }])).collect();
    ctx.view(songs_id, json!({ "t": "songs", "uses": listed }));
    Ok(())
}
