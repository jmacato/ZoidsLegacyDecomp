//! Data read by matched code outside the C data tables: literal pools that sit just past their region's end,
//! and the BG1 distortion scene's palette frames.

use std::collections::{BTreeMap, BTreeSet};

use serde_json::json;

use super::Port;
use crate::basis::Basis;
use crate::image::palette_swatch;
use crate::rom::{le16, le32, R};
use crate::run::Ctx;
use crate::{repo_root, verify_c, BASE};

/// Regions whose pc-relative loads read words after the region's end. Any other region doing so is a hard error until reviewed.
const POOLS: Basis = Basis::C(&[
    ("src/runtime/rom_entry_stack.s", "d37a4caa9dc1f3dac01886f02477fad5b13430f4"),
    ("src/runtime/rom_irq_dispatch.s", "9ce6cae1e5c2b61d67334e61513d6dbe007a894f"),
    ("src/battle/deck_commands/execute_battle_deck_command.c", "37a53add94f1ecad5cfc247aa94cba36128bf8e2"),
    ("src/battle/update_battle_rotating_triangle_charge_palette_cycling_beam_effect.c", "afcb3e061b240f4a91e137a16267d48d263d5393"),
]);
const BG1_DISTORTION: Basis = Basis::C(&[
    ("src/events/scenes/run_scene_bg1_distortion_task.c", "8df02702675ec4bb3c74550fe8687d1b3e4fccdb"),
    ("src/graphics/screen_effects.h", "20e02e2b2fa0bfefbd6fd76c1cd45ac8c3e7e8d9"),
]);

const LIBC_REENT: Basis = Basis::C(&[("src/engine/seed_libc_random.c", "c92de01178039e478028fde84af10e4ff2a75cd2")]);

pub const PORT: Port = Port { name: "code_data", bases: &[POOLS, BG1_DISTORTION, LIBC_REENT], run };

const LIBC_REENT_POINTER: u32 = 0x087F_3128;

const SCENE_BG1_SCROLL_PALETTE_FRAMES: u32 = 0x0810_3E18;
/// palette frame = ModuloSigned32(frame + 1, 0x1E); each frame is QueueCopy(frames + frame << 5, 0x05000180, 0x20).
const BG1_PALETTE_FRAMES: u32 = 0x1E;

/// LDR (literal) targets of each callable span in cfg/functions.json, decoded in the span's mode.
fn literal_loads(rom: &crate::rom::Rom) -> R<Vec<(u32, u32)>> {
    let text = std::fs::read_to_string(repo_root().join("cfg/functions.json")).map_err(|error| error.to_string())?;
    let owners: Vec<serde_json::Value> = serde_json::from_str(&text).map_err(|error| error.to_string())?;
    let mut loads = Vec::new();
    for owner in &owners {
        let lo = verify_c::parse_hex(owner["lo"].as_str().unwrap_or(""))?;
        let hi = verify_c::parse_hex(owner["hi"].as_str().unwrap_or(""))?;
        if owner["mode"] == "thumb" {
            for at in (lo..hi).step_by(2) {
                let half = le16(rom.code_bytes(at, 2)?, 0);
                if half & 0xF800 == 0x4800 {
                    loads.push((at, ((at + 4) & !3) + u32::from(half & 0xFF) * 4));
                }
            }
        } else {
            for at in (lo..hi).step_by(4) {
                let word = le32(rom.code_bytes(at, 4)?, 0);
                if word & 0x0F7F_0000 == 0x051F_0000 {
                    let offset = word & 0xFFF;
                    loads.push((at, if word & 0x0080_0000 != 0 { at + 8 + offset } else { at + 8 - offset }));
                }
            }
        }
    }
    Ok(loads)
}

/// A pool counts when its first word starts within 4 bytes after the end of the region holding the load (rom_entry_stack.s
/// is followed by an unsourced `b 0x080000C0`), and each later word directly follows the previous one.
fn pools(ctx: &Ctx) -> R<()> {
    let regions = verify_c::regions(&repo_root().join("regions.txt"))?;
    let pinned: BTreeSet<&str> = match POOLS {
        Basis::C(files) => files.iter().map(|(path, _)| path.trim_start_matches("src/")).collect(),
        _ => BTreeSet::new(),
    };
    let mut by_region: BTreeMap<usize, BTreeMap<u32, Vec<u32>>> = BTreeMap::new();
    for (at, target) in literal_loads(ctx.rom)? {
        if !ctx.rom.is_data(target) {
            continue;
        }
        let Some(index) = regions.iter().position(|region| BASE + region.start <= at && at < BASE + region.end) else { continue };
        by_region.entry(index).or_default().entry(target).or_default().push(at);
    }
    for (index, targets) in by_region {
        let region = &regions[index];
        let end = BASE + region.end;
        let mut expected = end;
        let mut pool = Vec::new();
        for (&target, loads) in &targets {
            let slack = if pool.is_empty() { 4 } else { 0 };
            if target < expected || target > ((expected + 3) & !3) + slack {
                break;
            }
            pool.push((target, loads.clone()));
            expected = target + 4;
        }
        if pool.is_empty() {
            continue;
        }
        let source = region.sources.join(",");
        if !region.sources.iter().all(|file| pinned.contains(file.as_str())) {
            return Err(format!("region {} ({source}) loads a literal pool past its end at 0x{:08X}; review and pin it", region.name, pool[0].0));
        }
        let (id, _) = ctx.item("code.literal_pool", pool[0].0, POOLS, vec![format!("{}:{source}", region.name)]);
        let mut words = Vec::new();
        for (target, loads) in &pool {
            let value = le32(ctx.rom.claim(*target, 4, "literal_pool", id)?, 0);
            words.push(json!({ "at": format!("0x{target:08X}"), "value": format!("0x{value:08X}"), "loaded_by": loads.iter().map(|at| format!("0x{at:08X}")).collect::<Vec<_>>() }));
        }
        ctx.count(id, "pc-relative loads of the region");
        ctx.set(id, json!({ "region": region.name, "words": words }));
    }
    Ok(())
}

fn bg1_palette_frames(ctx: &Ctx) -> R<()> {
    let (id, _) = ctx.item("palette.bg1_distortion_frames", SCENE_BG1_SCROLL_PALETTE_FRAMES, BG1_DISTORTION, ctx.roots.require(SCENE_BG1_SCROLL_PALETTE_FRAMES)?);
    let colors = ctx.rom.claim(SCENE_BG1_SCROLL_PALETTE_FRAMES, BG1_PALETTE_FRAMES * 0x20, "palette", id)?.to_vec();
    ctx.count(id, "c_constant:ModuloSigned32(frame + 1, 0x1E)");
    ctx.file(id, ".png", &palette_swatch(&colors))?;
    ctx.view(id, json!({ "t": "palette", "colors": ["rom", SCENE_BG1_SCROLL_PALETTE_FRAMES, SCENE_BG1_SCROLL_PALETTE_FRAMES + BG1_PALETTE_FRAMES * 0x20] }));
    ctx.set(id, json!({ "frames": BG1_PALETTE_FRAMES, "destination": "0x05000180" }));
    Ok(())
}

/// SeedLibcRandom only stores through *LIBC_REENT_POINTER_ROM (to +0x58); no matched code reads the struct it points to.
fn libc_reent(ctx: &Ctx) -> R<()> {
    let target = le32(ctx.rom.peek(LIBC_REENT_POINTER, 4)?, 0);
    ctx.explain_target(target, LIBC_REENT_POINTER, LIBC_REENT, "SeedLibcRandom (seed_libc_random.c) only stores random_seed through LIBC_REENT_POINTER_ROM into this ROM struct (+0x58); no matched code reads it")
}

fn run(ctx: &Ctx) -> R<()> {
    pools(ctx)?;
    bg1_palette_frames(ctx)?;
    libc_reent(ctx)
}
