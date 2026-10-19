//! Font range tables read by ExpandShiftJisGlyphTiles and ExpandSingleByteGlyphTile.

use serde_json::json;

use super::Port;
use crate::basis::Basis;
use crate::image::{indexed_png, tile_2bpp, tile_sheet, GRAY4};
use crate::rom::{le16, le32, R};
use crate::run::Ctx;

const SJIS: Basis = Basis::C(&[
    ("src/ui/expand_shift_jis_glyph_tiles.c", "59727430777575c051dcdf0287dbe4db71e17d91"),
    ("src/ui/window.h", "c299d1e84300353c8f991978a0c2761133a5e42c"),
]);
const SINGLE: Basis = Basis::C(&[
    ("src/ui/expand_single_byte_glyph_tile.c", "4fb5fdf87cc4d18aff304753f37fb9271c0531b7"),
    ("src/ui/window.h", "c299d1e84300353c8f991978a0c2761133a5e42c"),
]);

pub const PORT: Port = Port { name: "font", bases: &[SJIS, SINGLE], run };

const SJIS_RANGES: u32 = 0x087A_0A98;
const SINGLE_RANGES: u32 = 0x087A_0B48;
const FONT_RANGE_COUNT: u32 = 22;
/// Both expanders read 2bpp 8x8 tiles; single-byte ranges point into Shift-JIS glyph data.
const FORMAT: &str = "font_2bpp";
const FONT_SHIFT_JIS_FALLBACK: u32 = 0x81A0;

fn glyphs(ctx: &Ctx, kind: &str, basis: Basis, address: u32, first: u32, count: u32, size: u32, from: String) -> R<()> {
    let (id, new) = ctx.item(kind, address, basis, vec![from]);
    if !new {
        return Ok(());
    }
    let data = ctx.rom.claim(address, count * size, FORMAT, id)?;
    ctx.view(id, json!({ "t": "glyphs", "data": ["rom", address, address + count * size], "size": size }));
    let tiles: Vec<[u8; 64]> = data.chunks(16).map(tile_2bpp).collect();
    let columns = if size == 32 { 2 } else { 1 };
    let mut sheet: Vec<[u8; 64]> = Vec::new();
    if size == 32 {
        let per_row = 16usize;
        for row in 0..(count as usize).div_ceil(per_row) {
            for half in 0..2 {
                for glyph in row * per_row..((row + 1) * per_row).min(count as usize) {
                    sheet.push(tiles[glyph * 2 + half]);
                }
                for _ in ((row + 1) * per_row).min(count as usize)..(row + 1) * per_row {
                    sheet.push([0; 64]);
                }
            }
        }
        let (width, height, pixels) = tile_sheet(&sheet, per_row);
        ctx.file(id, ".png", &indexed_png(width, height, &pixels, &GRAY4, false))?;
    } else {
        let (width, height, pixels) = tile_sheet(&tiles, 16.min(count as usize) * columns);
        ctx.file(id, ".png", &indexed_png(width, height, &pixels, &GRAY4, false))?;
    }
    ctx.count(id, "c_range_count");
    ctx.set(id, json!({ "first_code": format!("0x{first:X}"), "count": count, "glyph_bytes": size }));
    Ok(())
}

/// Each 8-byte range entry: the search reads first code and count; the glyph pointer is at +4. SJIS +3 and single-byte +2..+3 are never read.
fn ranges(ctx: &Ctx, table: u32, sjis: bool) -> R<Vec<(u32, u32, u32)>> {
    let reached = ctx.roots.require(table)?;
    let (kind, basis) = if sjis { ("table.font_sjis_ranges", SJIS) } else { ("table.font_single_ranges", SINGLE) };
    let (id, _) = ctx.item(kind, table, basis, reached);
    let mut out = Vec::new();
    for index in 0..FONT_RANGE_COUNT {
        let entry = table + index * 8;
        let (first, count) = if sjis {
            let head = ctx.rom.claim(entry, 3, kind, id)?;
            ctx.unread(id, entry + 3, 1, "struct ShiftJisFontRange.data03 (src/ui/window.h): ExpandShiftJisGlyphTiles reads only first_code (+0), glyph_count (+2) and glyphs (+4) of each range (src/ui/expand_shift_jis_glyph_tiles.c)")?;
            (u32::from(le16(head, 0)), u32::from(head[2]))
        } else {
            let head = ctx.rom.claim(entry, 2, kind, id)?;
            ctx.unread(id, entry + 2, 2, "struct SingleByteFontRange.data02 (src/ui/window.h): ExpandSingleByteGlyphTile reads only first_code (+0), glyph_count (+1) and glyphs (+4) of each range (src/ui/expand_single_byte_glyph_tile.c)")?;
            (u32::from(head[0]), u32::from(head[1]))
        };
        let pointer = le32(ctx.rom.claim(entry + 4, 4, kind, id)?, 0);
        out.push((first, count, pointer));
    }
    ctx.count(id, "c_constant:FONT_RANGE_COUNT");
    ctx.set(id, json!(out.iter().map(|(first, count, pointer)| json!({"first_code": format!("0x{first:X}"), "count": count, "glyphs": format!("0x{pointer:08X}")})).collect::<Vec<_>>()));
    Ok(out)
}

fn run(ctx: &Ctx) -> R<()> {
    let sjis = ranges(ctx, SJIS_RANGES, true)?;
    for (first, count, pointer) in &sjis {
        if *count > 0 {
            glyphs(ctx, "font.sjis", SJIS, *pointer, *first, *count, 32, format!("table.font_sjis_ranges@0x{SJIS_RANGES:08X}"))?;
        }
    }
    let covered = sjis.iter().any(|(first, count, _)| *first <= FONT_SHIFT_JIS_FALLBACK && FONT_SHIFT_JIS_FALLBACK < first + count);
    let (first, _, pointer) = sjis[0];
    let fallback = pointer + (FONT_SHIFT_JIS_FALLBACK - first) * 32;
    let (id, _) = ctx.item("font.sjis_fallback", fallback, SJIS, vec![format!("table.font_sjis_ranges@0x{SJIS_RANGES:08X}")]);
    ctx.rom.claim(fallback, 32, FORMAT, id)?;
    ctx.set(id, json!({ "code": "0x81A0", "inside_a_range": covered, "note": "codes in no range draw range 0's glyph for 0x81A0" }));

    for (first, count, pointer) in ranges(ctx, SINGLE_RANGES, false)? {
        if count > 0 {
            glyphs(ctx, "font.single", SINGLE, pointer, first, count, 16, format!("table.font_single_ranges@0x{SINGLE_RANGES:08X}"))?;
        }
    }
    Ok(())
}
