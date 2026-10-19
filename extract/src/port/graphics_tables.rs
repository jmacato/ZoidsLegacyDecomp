//! ID-indexed graphics tables: Zoid bodies and icons, pilot portraits, battle terrain and sky, scene backgrounds.
//! The C indexes these by IDs it does not bound, so record counts are the distance to the next C-referenced address.

use serde_json::json;

use super::graphics::lz77_item;
use super::Port;
use crate::basis::Basis;
use crate::image::{render_tilemap, tiles_4bpp};
use crate::rom::{le32, R};
use crate::run::Ctx;
use crate::{repo_root, verify_c};

const ZOID_BODY: Basis = Basis::C(&[
    ("src/graphics/load_zoid_body_graphics.c", "dfe8bbedd8e22058665428919808a58fbc9ac8c8"),
    ("src/graphics/load_zoid_body_graphics_with_wram_staging.c", "3ab6170c26046a2134c7e9548e4dd2aed80226e1"),
    ("src/ui/select_zoid_palette_variant.c", "71f9cee08aefe67c82f527b2e7ffa0326234efcc"),
    ("src/ui/run_zoid_database_viewer.c", "8bd4d7d998f05ecc32b977fb9156793e9fbcbaa8"),
    ("src/graphics/graphics_resources.h", "f223cb8653d7262d3cfbfb30cb9b1b9ae262bc4d"),
]);
const ZOID_ICON: Basis = Basis::C(&[
    ("src/graphics/load_zoid_icon_graphics.c", "869cc7ff634e1f4c69aea53c17e2cda306597e6b"),
    ("src/graphics/queue_zoid_icon_graphics.c", "10eb3ae3fb3d98eca4f19afed5d0fcb1d3fa5287"),
]);
const PORTRAIT: Basis = Basis::C(&[
    ("src/graphics/load_pilot_portrait_graphics.c", "6df5691c4745a5c883bbd766b8bcc6da558e29f0"),
    ("src/graphics/queue_pilot_portrait_graphics.c", "6ac798ad97216d351a2b3684ae1c107d1ddb1626"),
    ("src/graphics/graphics_resources.h", "f223cb8653d7262d3cfbfb30cb9b1b9ae262bc4d"),
]);
const TERRAIN: Basis = Basis::C(&[
    ("src/graphics/load_battle_terrain_and_sky_graphics.c", "698b4d83ef5cdc2ccbcb7b6e77dc4466adb7b51d"),
    ("src/graphics/graphics_resources.h", "f223cb8653d7262d3cfbfb30cb9b1b9ae262bc4d"),
    ("src/battle/initialize_battle_field_display.c", "1e2b7c7aeffdc3152068ea112cfa8b659bf6961f"),
]);
const SCENE: Basis = Basis::C(&[("src/graphics/load_scene_background_graphics.c", "fb161086f9004046b62eaba7225de9940f5a2252")]);

pub const PORT: Port = Port { name: "graphics_tables", bases: &[ZOID_BODY, ZOID_ICON, PORTRAIT, TERRAIN, SCENE], run };

const ZOID_BODY_GRAPHICS: u32 = 0x087A_5CF0;
const ZOID_BODY_BG_PALETTES: u32 = 0x087A_641C;
const ZOID_BODY_OBJ_PALETTES: u32 = 0x087A_8F24;
const ZOID_BODY_SPRITE_GROUP_CALLBACKS: u32 = 0x087A_3164;
pub const ZOID_ICON_TILES: u32 = 0x087A_A70C;
pub const ZOID_ICON_PALETTES: u32 = 0x087A_A96C;
pub const PILOT_PORTRAITS: u32 = 0x087A_DBB8;
pub const PILOT_ALTERNATE_PALETTES: u32 = 0x087A_F604;
pub const PILOT_WITH_ALTERNATE_PALETTES: u32 = 75;
const TERRAIN_GRAPHICS: u32 = 0x087A_F614;
const SCENE_BACKGROUNDS: u32 = 0x087A_F794;

pub fn next_root_count(ctx: &Ctx, table: u32, stride: u32) -> R<u32> {
    let next = ctx.roots.by_address().range(table + 1..).next().map(|(address, _)| *address).ok_or("no root after table")?;
    if (next - table) % stride != 0 {
        return Err(format!("table 0x{table:08X}: next referenced address 0x{next:08X} is not a whole number of {stride}-byte records"));
    }
    Ok((next - table) / stride)
}

fn table(ctx: &Ctx, kind: &str, address: u32, basis: Basis, stride: u32) -> R<(usize, u32)> {
    let (id, _) = ctx.item(kind, address, basis, ctx.roots.require(address)?);
    let count = next_root_count(ctx, address, stride)?;
    ctx.count(id, "next_root");
    Ok((id, count))
}

fn pointer(ctx: &Ctx, address: u32, format: &str, id: usize) -> R<u32> {
    let value = le32(ctx.rom.claim(address, 4, format, id)?, 0);
    if value != 0 && !ctx.rom.is_data(value) {
        return Err(format!("{format} at 0x{address:08X}: 0x{value:08X} is not ROM data"));
    }
    Ok(value)
}

/// {LZ77 tiles, LZ77 palette} drawn together.
fn pair(ctx: &Ctx, tiles: u32, palette: u32, basis: Basis, from: String) -> R<()> {
    let (tiles_id, decoded_tiles) = lz77_item(ctx, tiles, true, basis, "tiles", None, vec![from.clone()])?;
    if palette != 0 {
        let (_, decoded_palette) = lz77_item(ctx, palette, false, basis, "palette", None, vec![from])?;
        let colored = format!("files/lz77/{tiles:08X}.color.png");
        if !ctx.has_file(tiles_id, &colored) {
            ctx.file(tiles_id, ".color.png", &tiles_4bpp(&decoded_tiles, &decoded_palette))?;
            ctx.view(tiles_id, json!({ "t": "tiles", "bpp": 4, "tiles": ["lz77", tiles], "palette": ["lz77", palette] }));
        }
    }
    Ok(())
}

/// The eight palette words of a zoid row; the C indexes the row by a runtime u8 zoid id and checks no tiles word first.
fn palette_row(ctx: &Ctx, row: u32, format: &str, id: usize) -> R<Vec<u32>> {
    (0..8).map(|variant| pointer(ctx, row + variant * 4, format, id)).collect()
}

fn lone_palette(ctx: &Ctx, palette: u32, basis: Basis, from: String) -> R<()> {
    lz77_item(ctx, palette, false, basis, "palette", None, vec![from]).map(|_| ())
}

fn zoid_bodies(ctx: &Ctx) -> R<()> {
    let (body, count) = table(ctx, "table.zoid_body_graphics", ZOID_BODY_GRAPHICS, ZOID_BODY, 12)?;
    let (bg_palettes, bg_count) = table(ctx, "table.zoid_body_bg_palettes", ZOID_BODY_BG_PALETTES, ZOID_BODY, 32)?;
    let (obj_palettes, obj_count) = table(ctx, "table.zoid_body_obj_palettes", ZOID_BODY_OBJ_PALETTES, ZOID_BODY, 32)?;
    let (callbacks, _) = ctx.item("table.zoid_body_sprite_group_callbacks", ZOID_BODY_SPRITE_GROUP_CALLBACKS, ZOID_BODY, ctx.roots.require(ZOID_BODY_SPRITE_GROUP_CALLBACKS)?);
    ctx.count(callbacks, "zoids whose obj_tiles is non-null");
    if bg_count != count || obj_count != count {
        return Err(format!("Zoid body tables disagree: {count} graphics records, {bg_count} bg palette records, {obj_count} obj palette records"));
    }
    let callbacks_end = ctx.roots.by_address().range(ZOID_BODY_SPRITE_GROUP_CALLBACKS + 1..).next().map(|(address, _)| *address).ok_or("no root after the sprite group callbacks")?;
    let regions = verify_c::regions(&repo_root().join("regions.txt"))?;
    let mut zoids = Vec::new();
    for zoid in 0..count {
        let record = ZOID_BODY_GRAPHICS + zoid * 12;
        let bg_tiles = pointer(ctx, record, "table.zoid_body_graphics", body)?;
        let bg_tilemap = pointer(ctx, record + 4, "table.zoid_body_graphics", body)?;
        let obj_tiles = pointer(ctx, record + 8, "table.zoid_body_graphics", body)?;
        let from = format!("table.zoid_body_graphics@0x{ZOID_BODY_GRAPHICS:08X}[{zoid}]");
        let variants = palette_row(ctx, ZOID_BODY_BG_PALETTES + zoid * 32, "table.zoid_body_bg_palettes", bg_palettes)?;
        let obj_variants = palette_row(ctx, ZOID_BODY_OBJ_PALETTES + zoid * 32, "table.zoid_body_obj_palettes", obj_palettes)?;
        for &palette in obj_variants.iter().filter(|palette| **palette != 0) {
            if obj_tiles != 0 {
                pair(ctx, obj_tiles, palette, ZOID_BODY, from.clone())?;
            } else {
                lone_palette(ctx, palette, ZOID_BODY, from.clone())?;
            }
        }
        let mut obj = json!(null);
        if obj_tiles != 0 {
            let mut pair_callbacks = Vec::new();
            for slot in 0..2 {
                let callback = le32(ctx.rom.claim(ZOID_BODY_SPRITE_GROUP_CALLBACKS + zoid * 8 + slot * 4, 4, "table.zoid_body_sprite_group_callbacks", callbacks)?, 0);
                let offset = (callback & !1).wrapping_sub(crate::BASE);
                if callback != 0 && !regions.iter().any(|region| region.start <= offset && offset < region.end) {
                    return Err(format!("Zoid {zoid} sprite group callback 0x{callback:08X} is not in a matched region"));
                }
                pair_callbacks.push(format!("0x{callback:08X}"));
            }
            obj = json!({ "tiles": format!("0x{obj_tiles:08X}"), "palettes": obj_variants.iter().map(|p| format!("0x{p:08X}")).collect::<Vec<_>>(), "callbacks": pair_callbacks });
        } else if ZOID_BODY_SPRITE_GROUP_CALLBACKS + (zoid + 1) * 8 <= callbacks_end {
            ctx.unread(callbacks, ZOID_BODY_SPRITE_GROUP_CALLBACKS + zoid * 8, 8, "gZoidBodySpriteGroupCallbacks[zoid]: load_zoid_body_graphics.c and load_zoid_body_graphics_with_wram_staging.c, the only C that reads D_087A3164, read both callback words only inside if (obj_tiles != 0), and this zoid's obj_tiles word (table.zoid_body_graphics +8) is 0")?;
        }
        if bg_tiles == 0 {
            for &palette in variants.iter().filter(|palette| **palette != 0) {
                lone_palette(ctx, palette, ZOID_BODY, from.clone())?;
            }
            zoids.push(json!(null));
            continue;
        }
        for &palette in variants.iter().filter(|palette| **palette != 0) {
            pair(ctx, bg_tiles, palette, ZOID_BODY, from.clone())?;
        }
        let (tilemap_id, tilemap) = lz77_item(ctx, bg_tilemap, true, ZOID_BODY, "tilemap", None, vec![from.clone()])?;
        lz77_item(ctx, bg_tilemap, false, ZOID_BODY, "tilemap", None, vec![from.clone()])?;
        if let Some(&palette) = variants.iter().find(|palette| **palette != 0) {
            let tiles = crate::port::bios::lz77_dry(ctx.rom, bg_tiles, true)?;
            let colors = crate::port::bios::lz77_dry(ctx.rom, palette, false)?;
            if !ctx.has_file(tilemap_id, &format!("files/lz77/{bg_tilemap:08X}.render.png")) {
                ctx.file(tilemap_id, ".render.png", &render_tilemap(&tiles, &tilemap, &colors, 32, true))?;
                ctx.view(tilemap_id, json!({ "t": "tilemap", "tiles": ["lz77", bg_tiles], "map": ["lz77", bg_tilemap], "palette": ["lz77", palette], "width": 32, "bpp": 8 }));
            }
        }
        zoids.push(json!({
            "bg_tiles": format!("0x{bg_tiles:08X}"), "bg_tilemap": format!("0x{bg_tilemap:08X}"),
            "bg_palettes": variants.iter().map(|p| format!("0x{p:08X}")).collect::<Vec<_>>(), "obj": obj,
        }));
    }
    ctx.set(body, json!({ "zoids": zoids }));
    Ok(())
}

fn zoid_icons(ctx: &Ctx) -> R<()> {
    let (tiles_table, count) = table(ctx, "table.zoid_icon_tiles", ZOID_ICON_TILES, ZOID_ICON, 4)?;
    let (palettes_table, palette_count) = table(ctx, "table.zoid_icon_palettes", ZOID_ICON_PALETTES, ZOID_ICON, 32)?;
    if palette_count != count {
        return Err(format!("Zoid icon tables disagree: {count} tile records, {palette_count} palette records"));
    }
    for zoid in 0..count {
        let tiles = pointer(ctx, ZOID_ICON_TILES + zoid * 4, "table.zoid_icon_tiles", tiles_table)?;
        let from = format!("table.zoid_icon_tiles@0x{ZOID_ICON_TILES:08X}[{zoid}]");
        for palette in palette_row(ctx, ZOID_ICON_PALETTES + zoid * 32, "table.zoid_icon_palettes", palettes_table)? {
            if palette == 0 {
                continue;
            }
            if tiles != 0 {
                pair(ctx, tiles, palette, ZOID_ICON, from.clone())?;
            } else {
                lone_palette(ctx, palette, ZOID_ICON, from.clone())?;
            }
        }
    }
    Ok(())
}

fn portraits(ctx: &Ctx) -> R<()> {
    let (portraits, count) = table(ctx, "table.pilot_portraits", PILOT_PORTRAITS, PORTRAIT, 64)?;
    let (alternates, alternate_count) = table(ctx, "table.pilot_portrait_alternate_palettes", PILOT_ALTERNATE_PALETTES, PORTRAIT, 4)?;
    for pilot in 0..count {
        for expression in 0..8 {
            let record = PILOT_PORTRAITS + pilot * 64 + expression * 8;
            let tiles = pointer(ctx, record, "table.pilot_portraits", portraits)?;
            if pilot == PILOT_WITH_ALTERNATE_PALETTES {
                ctx.unread(portraits, record + 4, 4, "palette word of GRAPHICS_PILOT_WITH_ALTERNATE_PORTRAIT_PALETTES (75): LoadPilotPortraitGraphics and QueuePilotPortraitGraphics (load_pilot_portrait_graphics.c, queue_pilot_portrait_graphics.c), the only readers of 0x087ADBB8, load the palette from 0x087AF604 when pilot_id == 75 (cmp/beq at 0x0809A97A and 0x0809A9FE) and never load +4; every caller's expression id is 0..7, so no other row reaches this word")?;
            }
            if tiles == 0 {
                if pilot != PILOT_WITH_ALTERNATE_PALETTES {
                    pointer(ctx, record + 4, "table.pilot_portraits", portraits)?;
                }
                continue;
            }
            let from = format!("table.pilot_portraits@0x{PILOT_PORTRAITS:08X}[{pilot}][{expression}]");
            if pilot == PILOT_WITH_ALTERNATE_PALETTES {
                lz77_item(ctx, tiles, true, PORTRAIT, "tiles", None, vec![from.clone()])?;
                for index in 0..alternate_count {
                    let palette = pointer(ctx, PILOT_ALTERNATE_PALETTES + index * 4, "table.pilot_portrait_alternate_palettes", alternates)?;
                    pair(ctx, tiles, palette, PORTRAIT, from.clone())?;
                }
            } else {
                let palette = pointer(ctx, record + 4, "table.pilot_portraits", portraits)?;
                pair(ctx, tiles, palette, PORTRAIT, from)?;
            }
        }
    }
    Ok(())
}

fn terrain(ctx: &Ctx) -> R<()> {
    let (id, count) = table(ctx, "table.battle_terrain_graphics", TERRAIN_GRAPHICS, TERRAIN, 16)?;
    for terrain in 0..count {
        let record = TERRAIN_GRAPHICS + terrain * 16;
        let from = format!("table.battle_terrain_graphics@0x{TERRAIN_GRAPHICS:08X}[{terrain}]");
        let words: Vec<u32> = (0..4).map(|index| pointer(ctx, record + index * 4, "table.battle_terrain_graphics", id)).collect::<R<_>>()?;
        let [terrain_tiles, terrain_palette, sky_tiles, sky_palette] = [words[0], words[1], words[2], words[3]];
        for (tiles, palette) in [(terrain_tiles, terrain_palette), (sky_tiles, sky_palette)] {
            if tiles != 0 {
                lz77_item(ctx, tiles, true, TERRAIN, "tiles", None, vec![from.clone()])?;
            }
            if palette != 0 {
                lz77_item(ctx, palette, false, TERRAIN, "palette", None, vec![from.clone()])?;
            }
        }
        let palettes = [(0u32, terrain_palette), (0x80, sky_palette)].into_iter().filter(|(_, palette)| *palette != 0).collect::<Vec<_>>();
        if terrain_tiles != 0 {
            bg_view(ctx, terrain_tiles, &palettes, 8, 8)?;
        }
        if sky_tiles != 0 {
            bg_view(ctx, sky_tiles, &palettes, 16, 16)?;
        }
    }
    Ok(())
}

/// Record = 3 {tiles, palette} pairs: size class 0-2 uses pair 0, 3 pair 1, 4 pair 2. Background ids above 0xFC load nothing.
fn scene_backgrounds(ctx: &Ctx) -> R<()> {
    let (id, count) = table(ctx, "table.scene_background_graphics", SCENE_BACKGROUNDS, SCENE, 24)?;
    for background in 0..count.min(0xFD) {
        let from = format!("table.scene_background_graphics@0x{SCENE_BACKGROUNDS:08X}[{background}]");
        for slot in 0..3 {
            let record = SCENE_BACKGROUNDS + background * 24 + slot * 8;
            let tiles = pointer(ctx, record, "table.scene_background_graphics", id)?;
            let palette = pointer(ctx, record + 4, "table.scene_background_graphics", id)?;
            if tiles != 0 {
                lz77_item(ctx, tiles, true, SCENE, "tiles", None, vec![from.clone()])?;
                if palette != 0 {
                    lz77_item(ctx, palette, false, SCENE, "palette", None, vec![from.clone()])?;
                    bg_view(ctx, tiles, &[(0x80, palette)], 16, 16)?;
                }
            }
        }
    }
    Ok(())
}

/// A 256-colour background as the C lays it out: tile n at row n / columns, column n % columns (the scene and sky
/// tilemaps count up 16 per row; the terrain's affine map counts up 8 per row), each pixel byte an index into BG palette
/// RAM holding each LZ77 palette at its byte offset. The duplicated columns and rows the C also writes are wrap-around.
fn bg_view(ctx: &Ctx, tiles: u32, palettes: &[(u32, u32)], columns: u32, rows: u32) -> R<()> {
    let (id, _) = ctx.item("lz77", tiles, TERRAIN, Vec::new());
    let data = crate::port::bios::lz77_dry(ctx.rom, tiles, true)?;
    let mut pram = vec![0u8; 0x200];
    for &(offset, palette) in palettes {
        let colors = crate::port::bios::lz77_dry(ctx.rom, palette, false)?;
        let end = (offset as usize + colors.len()).min(0x200);
        pram[offset as usize..end].copy_from_slice(&colors[..end - offset as usize]);
    }
    let (width, height) = (columns * 8, rows * 8);
    let mut pixels = vec![0u8; (width * height) as usize];
    for tile in 0..columns * rows {
        let Some(bytes) = data.get(tile as usize * 64..tile as usize * 64 + 64) else { continue };
        for (index, &value) in bytes.iter().enumerate() {
            let (x, y) = ((tile % columns) * 8 + index as u32 % 8, (tile / columns) * 8 + index as u32 / 8);
            pixels[(y * width + x) as usize] = value;
        }
    }
    let mut hashed = pixels.clone();
    hashed.extend(&pram);
    let colors: Vec<[u8; 3]> = (0..256).map(|index| crate::image::bgr555(u16::from_le_bytes([pram[index * 2], pram[index * 2 + 1]]))).collect();
    let suffix = format!(".bg{:08X}.png", palettes[0].1);
    if !ctx.has_file(id, &format!("files/lz77/{tiles:08X}{suffix}")) {
        ctx.file(id, &suffix, &crate::image::indexed_png(width, height, &pixels, &colors, true))?;
    }
    ctx.view(id, json!({
        "t": "bg", "bpp": 8, "tiles": ["lz77", tiles], "columns": columns, "rows": rows,
        "palettes": palettes.iter().map(|(offset, palette)| json!([offset, ["lz77", palette]])).collect::<Vec<_>>(),
        "sha1": crate::sha1_hex(&hashed),
    }));
    Ok(())
}

fn run(ctx: &Ctx) -> R<()> {
    zoid_bodies(ctx)?;
    zoid_icons(ctx)?;
    portraits(ctx)?;
    terrain(ctx)?;
    scene_backgrounds(ctx)
}
