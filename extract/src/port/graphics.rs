//! LZ77 graphics loaded by literal call sites: BiosLz77ToVram/Wram, LoadCompressedPalette, LoadMirroredBgTilemap.

use serde_json::json;

use super::{area, bios, literal, resolve_at, Port};
use crate::basis::Basis;
use crate::image::{gray_tiles_4bpp, palette_swatch, tiles_4bpp};
use crate::rom::{le32, R};
use crate::run::Ctx;

const COMPRESSED_PALETTE: Basis = Basis::C(&[("src/graphics/load_compressed_palette.c", "062d97738ff22254c43d529131b02319a2b4c0d5")]);
const MIRRORED_TILEMAP: Basis = Basis::C(&[
    ("src/graphics/load_mirrored_bg_tilemap.c", "9fdbcadc9748f0cb874bec7849f26c9afce1071e"),
    ("src/graphics/graphics_resources.h", "f223cb8653d7262d3cfbfb30cb9b1b9ae262bc4d"),
]);

pub const SPRITE_GRAPHICS: Basis = Basis::C(&[
    ("src/graphics/load_sprite_graphics_from_table.c", "ea9d494504eeb3b592c2ef609590e7083cc46b7b"),
    ("src/graphics/queue_sprite_graphics_from_table.c", "3cdd0dbb05af635720a46daf29a1bc243e73a654"),
    ("src/graphics/graphics_resources.h", "f223cb8653d7262d3cfbfb30cb9b1b9ae262bc4d"),
    ("src/graphics/load_compressed_palette.c", "062d97738ff22254c43d529131b02319a2b4c0d5"),
]);

pub const PORT: Port = Port { name: "graphics", bases: &[bios::LZ77_VRAM, bios::LZ77_WRAM, COMPRESSED_PALETTE, MIRRORED_TILEMAP, SPRITE_GRAPHICS], run };

const LOAD_SPRITE_GRAPHICS_FROM_TABLE: u32 = 0x0809_AA64;
const QUEUE_SPRITE_GRAPHICS_FROM_TABLE: u32 = 0x0809_AAA8;

const BIOS_LZ77_TO_VRAM: u32 = 0x080E_CD34;
const BIOS_LZ77_TO_WRAM: u32 = 0x080E_CD38;
const LOAD_COMPRESSED_PALETTE: u32 = 0x0809_A1BC;
const LOAD_MIRRORED_BG_TILEMAP: u32 = 0x0809_AC30;

/// An LZ77 blob; decoded once, and checked again when another caller uses the VRAM decode.
pub fn lz77_item(ctx: &Ctx, address: u32, vram: bool, basis: Basis, use_as: &str, destination: Option<u32>, reached: Vec<String>) -> R<(usize, Vec<u8>)> {
    let (id, new) = ctx.item("lz77", address, basis, reached);
    if !new {
        let decoded = bios::lz77_dry(ctx.rom, address, vram)?;
        ctx.view(id, json!({ "t": "lz77", "use": use_as, "sha1": crate::sha1_hex(&decoded) }));
        return Ok((id, decoded));
    }
    let decoded = bios::lz77(ctx.rom, address, id, vram)?;
    ctx.view(id, json!({ "t": "lz77", "use": use_as, "sha1": crate::sha1_hex(&decoded) }));
    let target = destination.map(area).unwrap_or("unknown");
    ctx.file(id, ".bin", &decoded)?;
    if use_as == "palette" || target == "palette" {
        ctx.file(id, ".png", &palette_swatch(&decoded))?;
    } else if use_as == "tiles" || target == "vram" {
        ctx.file(id, ".png", &gray_tiles_4bpp(&decoded))?;
    }
    ctx.count(id, "lz77_header_size");
    ctx.set(id, json!({
        "decoded_bytes": decoded.len(),
        "use": use_as,
        "destination": destination.map(|address| format!("0x{address:08X}")),
        "destination_area": target,
    }));
    Ok((id, decoded))
}

/// Load/QueueSpriteGraphicsFromTable(table, id): an 8-byte {LZ77 tiles, LZ77 palette} entry at table + id * 8.
/// The queued form also reads the next entry's palette pointer and byte 3 of that palette's header.
pub fn sprite_graphics(ctx: &Ctx, table: u32, id: u32, queued: bool, reached: String) -> R<()> {
    let (table_id, _) = ctx.item("table.compressed_sprite_graphics", table, SPRITE_GRAPHICS, vec![reached.clone()]);
    ctx.count(table_id, "ids used by ported callers");
    let entry = table + (id & 0xFF) * 8;
    let record = ctx.rom.claim(entry, 8, "table.compressed_sprite_graphics", table_id)?;
    let (tiles, palette) = (le32(record, 0), le32(record, 4));
    let from = format!("table.compressed_sprite_graphics@0x{table:08X}[{id}]");
    let (tiles_id, decoded_tiles) = lz77_item(ctx, tiles, !queued, SPRITE_GRAPHICS, "tiles", Some(0x0601_0000), vec![from.clone()])?;
    let (_, decoded_palette) = lz77_item(ctx, palette, false, SPRITE_GRAPHICS, "palette", Some(0x0500_0200), vec![from])?;
    if queued {
        let next = le32(ctx.rom.claim(entry + 12, 4, "table.compressed_sprite_graphics", table_id)?, 0);
        ctx.rom.claim(next + 3, 1, "lz77", table_id)?;
    }
    let colored = format!("files/lz77/{tiles:08X}.color.png");
    if !ctx.has_file(tiles_id, &colored) {
        ctx.file(tiles_id, ".color.png", &tiles_4bpp(&decoded_tiles, &decoded_palette))?;
        ctx.view(tiles_id, json!({ "t": "tiles", "bpp": 4, "tiles": ["lz77", tiles], "palette": ["lz77", palette] }));
    }
    Ok(())
}

fn run(ctx: &Ctx) -> R<()> {
    for (callee, queued) in [(LOAD_SPRITE_GRAPHICS_FROM_TABLE, false), (QUEUE_SPRITE_GRAPHICS_FROM_TABLE, true)] {
        for reference in ctx.roots.calls(callee, 0) {
            if !ctx.rom.is_data(reference.address) {
                continue;
            }
            if let Some(id) = reference.args.get(1).and_then(|text| literal(text)) {
                sprite_graphics(ctx, reference.address, id, queued, reference.location())?;
            }
        }
    }
    for (callee, vram, basis) in [(BIOS_LZ77_TO_VRAM, true, bios::LZ77_VRAM), (BIOS_LZ77_TO_WRAM, false, bios::LZ77_WRAM)] {
        for reference in ctx.roots.calls(callee, 0) {
            if !ctx.rom.is_data(reference.address) {
                continue;
            }
            let destination = reference.args.get(1).and_then(|text| resolve_at(text, reference, ctx.roots));
            let use_as = if destination.map(area) == Some("palette") { "palette" } else { "raw" };
            lz77_item(ctx, reference.address, vram, basis, use_as, destination, vec![reference.location()])?;
        }
    }
    for reference in ctx.roots.calls(LOAD_COMPRESSED_PALETTE, 0) {
        if ctx.rom.is_data(reference.address) {
            let destination = reference.args.get(1).and_then(|text| resolve_at(text, reference, ctx.roots));
            lz77_item(ctx, reference.address, false, COMPRESSED_PALETTE, "palette", destination, vec![reference.location()])?;
        }
    }
    for reference in ctx.roots.calls(LOAD_MIRRORED_BG_TILEMAP, 0) {
        if !ctx.rom.is_data(reference.address) {
            continue;
        }
        let mirrored = reference.args.get(2).and_then(|text| literal(text));
        let screen = reference.args.get(1).and_then(|text| literal(text)).map(|block| 0x0600_0000 + (block << 11));
        if mirrored != Some(0) {
            lz77_item(ctx, reference.address, false, MIRRORED_TILEMAP, "tilemap", screen, vec![reference.location()])?;
        }
        if mirrored.map_or(true, |value| value & 0xFF == 0) {
            lz77_item(ctx, reference.address, true, MIRRORED_TILEMAP, "tilemap", screen, vec![reference.location()])?;
        }
    }
    Ok(())
}
