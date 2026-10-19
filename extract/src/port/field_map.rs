//! InitializeFieldMapGraphics (0x0809D938) map definitions and the field readers of their data:
//! GetFieldBackgroundTile metatile resolution, collision cells, the world-map encounter grid, encounter definitions,
//! field palette animation, warps, return maps and world-map decorations.

use std::collections::{BTreeMap, BTreeSet};

use serde_json::{json, Value};

use super::graphics::lz77_item;
use super::{bios, Port};
use crate::basis::Basis;
use crate::image::{bgr555, palette_swatch};
use crate::rom::{le16, le32, R, NEUTRAL};
use crate::run::Ctx;

const INIT: (&str, &str) = ("src/field/initialize_field_map_graphics.c", "a8a1520a4e455eeec02af498da83b04a3c7ba574");
const DISPLAY_H: (&str, &str) = ("src/field/field_display.h", "d0a733782b71499ab362fb6a884412891a62e012");
const ACTOR_H: (&str, &str) = ("src/field/field_actor.h", "a72a104ee20ea5fa6e428e29febcc0f71f58990d");
const RUN_FIELD_C: (&str, &str) = ("src/game/modes/run_field.c", "7e4acabc58f52925318d5bdb5196e2c2066d5446");
const MAP_CELL_C: (&str, &str) = ("src/field/update_field_actor_map_cell.c", "e31fc41088ae8611e8999fc41a03867a9a024a7c");
const DISPLAY_C: (&str, &str) = ("src/field/update_field_display.c", "ee1fc2a1c12a3ba96f2fec016b106c1a1b64b328");
const QUEUE_COPY_C: (&str, &str) = ("src/graphics/queue_copy.c", "9f3482ebd43e0bafd38ec6fb0cc9bd5edfafa8b9");
const TRANSFER_QUEUE_C: (&str, &str) = ("src/graphics/process_transfer_queue.c", "bd3df7baf01ad4e5d00e43a241686352967859c7");

const MAPS: Basis = Basis::C(&[
    INIT,
    ("src/field/get_field_background_tile.c", "3b4e91f3df8e7a901d314b51a9599ce0ed4866d8"),
    ("src/field/stream_field_background_tilemaps.c", "dc6aec1984afa3811a1ebeca47501c06e9ed5cb9"),
    ("src/graphics/load_compressed_palette.c", "062d97738ff22254c43d529131b02319a2b4c0d5"),
    DISPLAY_H,
]);
const DEFINITIONS: Basis = Basis::C(&[
    INIT,
    RUN_FIELD_C,
    ("src/field/show_field_map_name.c", "e1bfedd7b08c5545951940ad3b8154a744287612"),
    ("src/events/commands/event_play_map_music.c", "ad13eec87f8ed327f3ee94a0dbee9559c42f1632"),
    DISPLAY_H,
]);
const COLLISION: Basis = Basis::C(&[
    INIT,
    ("src/field/get_field_map_cell_collision_mask.c", "8db8293232e48dbd27d1f0b7c000eceee8dd48ad"),
    ("src/field/get_packed_field_map_cell_collision.c", "971405a6589339c237195474127560f1449c5f70"),
    ("src/field/is_field_terrain_blocked_for_actor_model.c", "d65fddf8aaa691963a226df43bfb6117b35c9f5d"),
    MAP_CELL_C,
    ACTOR_H,
]);
const ENCOUNTERS: Basis = Basis::C(&[
    ("src/field/try_select_field_random_encounter.c", "0f314b9346001882aaa8a4790ad9588825153066"),
    ("src/field/select_field_random_encounter_table.c", "f4e75d18a1843b01da87f2728d1e4f5f2367531f"),
    DISPLAY_H,
]);
const ANIMATION: Basis = Basis::C(&[
    DISPLAY_C,
    ("src/field/run_field_display_task.c", "7d801e40be5937e921cfd7599829ed16944dcdfd"),
    QUEUE_COPY_C,
    TRANSFER_QUEUE_C,
]);
const RUN_FIELD: Basis = Basis::C(&[
    RUN_FIELD_C,
    MAP_CELL_C,
    ("src/field/update_field_actors.c", "281558f18c94564bca2f1f8aebcfba726ec842e1"),
    ("src/field/create_field_actor.c", "1be55f32be3cd126a512de430bf91198751cbbe7"),
    ACTOR_H,
    ("src/events/event_script.h", "23f6268830cf2d663af58bc5552d8fd4105e85b2"),
]);
const DECORATIONS: Basis = Basis::C(&[
    ("src/field/update_field_map_decoration_sprites.c", "959e94fe929fba4a08dd73cd964020c107ee25f1"),
    DISPLAY_C,
    DISPLAY_H,
    QUEUE_COPY_C,
    TRANSFER_QUEUE_C,
]);
const SLIDE: Basis = Basis::C(&[("src/events/commands/event_show_world_map_bg1_overlay.c", "ccc10a7235475aafd790ebdc7fa8ec4d67ecd505"), DISPLAY_H]);

pub const PORT: Port = Port {
    name: "field_map",
    bases: &[MAPS, DEFINITIONS, COLLISION, ENCOUNTERS, ANIMATION, RUN_FIELD, DECORATIONS, SLIDE, bios::LZ77_VRAM, bios::LZ77_WRAM, bios::CPU_SET],
    run,
};

const TABLE: u32 = 0x087C_4434;
const RECORD: u32 = 0x20;
const TABLE_FORMAT: &str = "table.field_map_definitions";
const WORLD: u32 = 0;
/// InitializeFieldMapGraphics and UpdateFieldDisplay give map 0x40 the world-map overlays as well.
const OVERLAY_MAP: u32 = 0x40;

const OVERLAY_TILES: u32 = 0x0849_8FA0;
const OVERLAY_BG1_SCREEN: u32 = 0x0849_9A44;
const WORLD_BG2_SCREEN: u32 = 0x0849_9C1C;
const WORLD_BG3_METATILE_MAP: u32 = 0x0849_9D38;
const WORLD_BG3_METATILE_TILES: u32 = 0x0849_A044;
const SLIDE_TILES: u32 = 0x0842_0F28;
const SLIDE_SCREEN: u32 = 0x0842_115C;

const ENCOUNTER_GRID: u32 = 0x0847_8FA0;
const ENCOUNTER_THRESHOLDS: u32 = 0x087C_3864;
/// SelectFieldRandomEncounterTable reads gFieldMapDefinitions - 0xBB0.
const ENCOUNTER_DEFINITIONS: u32 = TABLE - 0xBB0;
const PALETTE_FRAMES: u32 = 0x085C_E1FC;
const PALETTE_FRAMES_B: u32 = 0x085C_E39C;
const WARPS: u32 = 0x087C_5CB4;
/// RunField: (map * 129 + (cell & 0x3F) * 3) halfwords.
const WARP_STRIDE: u32 = 129 * 2;
const RETURN_MAPS: u32 = 0x087D_223C;
const RETURN_MAPS_24: u32 = 0x087D_2322;
const GROUP_POSITIONS: u32 = 0x087A_FBB4;
const ALTERNATE_DECORATIONS: u32 = 0x087A_FCB0;
const DECORATION_GRAPHICS: u32 = 0x087A_FB54;
const DECORATION_PALETTES: u32 = 0x087A_FB58;
/// FIELD_DECORATION_SLOT_COUNT and FIELD_ALTERNATE_DECORATION_COUNT (field_display.h).
const DECORATION_COUNT: u32 = 42;
const ALTERNATE_DECORATION_COUNT: u32 = 3;

const BG0_BUFFER: u32 = 0x0203_2E98;
const BG1_BUFFER: u32 = 0x0203_4E98;
const METATILE_BUFFER: u32 = 0x0203_6E98;
const COLLISION_BUFFER: u32 = 0x0203_AE98;
const MAP_TILES_VRAM: u32 = 0x0600_4000;
const OVERLAY_TILES_VRAM: u32 = 0x0600_C000;

struct Record {
    address: u32,
    width: u16,
    height: u16,
    tiles: u32,
    palette: u32,
    bg0: u32,
    bg1: Option<u32>,
    metatiles: u32,
    collision: u32,
    has_data: u8,
    group: u8,
    song: u8,
}

fn read_record(ctx: &Ctx, table: usize, map: u32) -> R<Record> {
    let address = TABLE + map * RECORD;
    let u16_at = |offset: u32| -> R<u16> { Ok(le16(ctx.rom.claim(address + offset, 2, TABLE_FORMAT, table)?, 0)) };
    let u32_at = |offset: u32| -> R<u32> { Ok(le32(ctx.rom.claim(address + offset, 4, TABLE_FORMAT, table)?, 0)) };
    let u8_at = |offset: u32| -> R<u8> { Ok(ctx.rom.claim(address + offset, 1, TABLE_FORMAT, table)?[0]) };
    ctx.unread(
        table,
        address + 0x1F,
        1,
        &format!("map {map} definition +0x1F: CategoryInfo.pad1F (src/game/modes/run_field.c), MapMusicDefinition.reserved1F (src/events/commands/event_play_map_music.c), the end of reserved1E[2] in FieldMapNameGroupView (src/field/field_display.h), EventFieldMapGroupView (src/events/event_script.h) and EventMapInfo.pad1E (src/events/commands/event_change_map.c); initialize_field_map_graphics.c, run_field.c, run_battle.c and run_recovery_item_menu.c read only +0x00..+0x1E"),
    )?;
    if map == WORLD {
        ctx.unread(
            table,
            address + 0x10,
            4,
            "map 0 definition +0x10 (BG1 metatile map): InitializeFieldMapGraphics reads +0x10 only when map_id != 0 and stores 0 as map 0's second tilemap (src/field/initialize_field_map_graphics.c)",
        )?;
    }
    Ok(Record {
        address,
        width: u16_at(0)?,
        height: u16_at(2)?,
        tiles: u32_at(4)?,
        palette: u32_at(8)?,
        bg0: u32_at(0xC)?,
        bg1: if map == WORLD { None } else { Some(u32_at(0x10)?) },
        metatiles: u32_at(0x14)?,
        collision: u32_at(0x18)?,
        has_data: u8_at(0x1C)?,
        group: u8_at(0x1D)?,
        song: u8_at(0x1E)?,
    })
}

fn next_root(ctx: &Ctx, address: u32) -> R<u32> {
    ctx.roots.by_address().range(address + 1..).next().map(|(next, _)| *next).ok_or_else(|| format!("no root after 0x{address:08X}"))
}

const RAM_BASE: u32 = 0x0200_0000;
const RAM_SIZE: usize = 0x4_0000;
const OWNERS: [&str; 5] = ["nothing", "BG0 metatile map", "BG1 metatile map", "metatile tiles", "collision cells"];
const OWN_BG0: u8 = 1;
const OWN_BG1: u8 = 2;
const OWN_METATILES: u8 = 3;
const OWN_COLLISION: u8 = 4;

/// EWRAM as InitializeFieldMapGraphics leaves it: which decode last wrote each byte.
struct Ram {
    bytes: Vec<u8>,
    owner: Vec<u8>,
    read: Vec<bool>,
}

impl Ram {
    fn new() -> Ram {
        Ram { bytes: vec![0; RAM_SIZE], owner: vec![0; RAM_SIZE], read: vec![false; RAM_SIZE] }
    }

    fn offset(address: u32, length: usize) -> R<usize> {
        let offset = address.checked_sub(RAM_BASE).map(|offset| offset as usize).filter(|offset| offset + length <= RAM_SIZE);
        offset.ok_or_else(|| format!("EWRAM access 0x{address:08X}+{length} is outside the modelled range"))
    }

    fn write(&mut self, address: u32, data: &[u8], owner: u8) -> R<()> {
        let offset = Ram::offset(address, data.len())?;
        self.bytes[offset..offset + data.len()].copy_from_slice(data);
        self.owner[offset..offset + data.len()].fill(owner);
        Ok(())
    }

    fn u8(&mut self, address: u32, owner: u8) -> R<u8> {
        let offset = Ram::offset(address, 1)?;
        if self.owner[offset] != owner {
            return Err(format!("read of the {} at 0x{address:08X} finds the {}", OWNERS[owner as usize], OWNERS[self.owner[offset] as usize]));
        }
        self.read[offset] = true;
        Ok(self.bytes[offset])
    }

    fn u16(&mut self, address: u32, owner: u8) -> R<u16> {
        Ok(u16::from(self.u8(address, owner)?) | u16::from(self.u8(address + 1, owner)?) << 8)
    }

    /// (bytes read, end of the last byte read) in `address..address + length`.
    fn extent(&self, address: u32, length: usize) -> (usize, usize) {
        let offset = (address - RAM_BASE) as usize;
        let read = &self.read[offset..offset + length];
        (read.iter().filter(|flag| **flag).count(), read.iter().rposition(|flag| *flag).map_or(0, |last| last + 1))
    }
}

/// Bytes of `base..` that a reader used, claimed as runs.
struct Used {
    base: u32,
    flags: Vec<bool>,
}

impl Used {
    fn new(base: u32) -> Used {
        Used { base, flags: Vec::new() }
    }

    fn mark(&mut self, offset: u32, length: u32) {
        let end = (offset + length) as usize;
        if self.flags.len() < end {
            self.flags.resize(end, false);
        }
        self.flags[offset as usize..end].fill(true);
    }

    fn claim(&self, ctx: &Ctx, format: &str, item: usize) -> R<u32> {
        let mut index = 0;
        let mut total = 0;
        while index < self.flags.len() {
            if !self.flags[index] {
                index += 1;
                continue;
            }
            let start = index;
            while index < self.flags.len() && self.flags[index] {
                index += 1;
            }
            ctx.rom.claim(self.base + start as u32, (index - start) as u32, format, item)?;
            total += (index - start) as u32;
        }
        Ok(total)
    }

    fn end(&self) -> u32 {
        self.flags.len() as u32
    }
}

/// GetPackedFieldMapCellCollision, UpdateFieldActorMapCell (map 0) and TrySelectFieldRandomEncounter cell index.
fn packed_cell(width: u16, cell_x: u32, cell_y: u32) -> u32 {
    (cell_x & 0xFF) + (((cell_y & 0xFF) * u32::from(width)) >> 1)
}

/// UpdateFieldActorMapCell for maps other than 0: the value an actor with collision cell (`x`, `row`) takes, or None when it keeps its previous value.
fn sampled_cell(cells: &[u8], width: usize, height: usize, x: usize, row: usize) -> Option<u8> {
    let at = |index: usize| cells[index];
    let first = at(x + width * row);
    let (second, third, fourth) = if x + 1 < width {
        let second = at(width * row + x + 1);
        if row + 1 < height {
            (second, at(x + width * (row + 1)), at(width * (row + 1) + x + 1))
        } else {
            (second, at(x), at(x + 1))
        }
    } else {
        let second = at(width * row);
        if row + 1 < height {
            (second, at(x + width * (row + 1)), at(width * (row + 1)))
        } else {
            (second, at(x), at(0))
        }
    };
    if first == second && first == third && first == fourth {
        return Some(first);
    }
    [first, second, third, fourth].into_iter().find(|cell| cell & 0x40 == 0)
}

/// Draw BG screen entries (`columns` x `rows`) from 4bpp characters and a BGR555 palette, as the GBA text BG does.
/// Returns the PNG and the number of entries whose tile lies outside `characters`.
fn render(entries: &[u16], columns: u32, rows: u32, characters: &[u8], palette: &[u8]) -> (Vec<u8>, u32) {
    let width = columns as usize * 8;
    let mut pixels = vec![0u8; width * rows as usize * 8];
    let mut missing = 0;
    for (index, &entry) in entries.iter().enumerate() {
        let tile = usize::from(entry & 0x3FF) * 32;
        if tile + 32 > characters.len() {
            missing += 1;
            continue;
        }
        let bank = (entry >> 12) as u8;
        let (x0, y0) = ((index % columns as usize) * 8, (index / columns as usize) * 8);
        for y in 0..8 {
            let source_y = if entry & 0x800 != 0 { 7 - y } else { y };
            for x in 0..8 {
                let source_x = if entry & 0x400 != 0 { 7 - x } else { x };
                let byte = characters[tile + source_y * 4 + source_x / 2];
                let pixel = if source_x & 1 == 0 { byte & 0xF } else { byte >> 4 };
                pixels[(y0 + y) * width + x0 + x] = bank * 16 + pixel;
            }
        }
    }
    let colors: Vec<u8> = (0..256).flat_map(|index| palette.get(index * 2..index * 2 + 2).map_or([0; 3], |pair| bgr555(le16(pair, 0)))).collect();
    let alpha: Vec<u8> = (0..256).map(|index| if index % 16 == 0 { 0 } else { 255 }).collect();
    let mut out = Vec::new();
    {
        let mut encoder = png::Encoder::new(&mut out, width as u32, rows * 8);
        encoder.set_color(png::ColorType::Indexed);
        encoder.set_depth(png::BitDepth::Eight);
        encoder.set_palette(colors);
        encoder.set_trns(alpha);
        let mut writer = encoder.write_header().expect("png header");
        writer.write_image_data(&pixels).expect("png data");
    }
    (out, missing)
}

fn halfwords(entries: &[u16]) -> Vec<u8> {
    entries.iter().flat_map(|entry| entry.to_le_bytes()).collect()
}

fn hex(address: u32) -> String {
    format!("0x{address:08X}")
}

/// Palette banks the entries use that lie past the decoded palette (those colours are left over in palette RAM).
fn banks_past(entries: &[u16], palette: &[u8]) -> Vec<u16> {
    let banks: BTreeSet<u16> = entries.iter().map(|entry| entry >> 12).filter(|bank| usize::from(*bank) * 32 + 32 > palette.len()).collect();
    banks.into_iter().collect()
}

struct Layer {
    entries: Vec<u16>,
    columns: u32,
    rows: u32,
}

/// `sources`: {"entries", "tiles", "palette"} recipes the browser page decodes; the entries' SHA-1 lets it check its result.
fn write_layer(ctx: &Ctx, item: usize, name: &str, layer: &Layer, characters: &[u8], characters_at: u32, palette: &[u8], sources: Value) -> R<Value> {
    let mut view = sources;
    view["t"] = json!("layer");
    view["name"] = json!(name);
    view["columns"] = json!(layer.columns);
    view["rows"] = json!(layer.rows);
    view["sha1"] = json!(crate::sha1_hex(&halfwords(&layer.entries)));
    ctx.view(item, view);
    let (png, missing) = render(&layer.entries, layer.columns, layer.rows, characters, palette);
    let screen = ctx.file(item, &format!("_{name}_entries.bin"), &halfwords(&layer.entries))?;
    let image = ctx.file(item, &format!("_{name}.png"), &png)?;
    let max_tile = layer.entries.iter().map(|entry| entry & 0x3FF).max().unwrap_or(0);
    Ok(json!({
        "columns": layer.columns,
        "rows": layer.rows,
        "characters": hex(characters_at),
        "max_tile": max_tile,
        "entries_with_tile_outside_characters": missing,
        "palette_banks_outside_palette": banks_past(&layer.entries, palette),
        "screen": screen,
        "image": image,
    }))
}

/// GetFieldBackgroundTile for a map other than 0: every tile inside gFieldMapDimensions.
fn resolve_layer(ram: &mut Ram, map_buffer: u32, owner: u8, width: u16, height: u16) -> R<(Layer, u16)> {
    let (columns, rows) = (u32::from(width.min(0x200)), u32::from(height.min(0x200)));
    let stride = u32::from(width >> 1);
    let mut entries = Vec::with_capacity((columns * rows) as usize);
    let mut max_metatile = 0;
    for y in 0..rows {
        for x in 0..columns {
            let metatile = ram.u16(map_buffer + 2 * (stride * (y >> 1) + (x >> 1)), owner)?;
            max_metatile = max_metatile.max(metatile);
            let cell = (y & 1) * 2 + (x & 1);
            entries.push(ram.u16(METATILE_BUFFER + u32::from(metatile) * 8 + cell * 2, OWN_METATILES)?);
        }
    }
    Ok((Layer { entries, columns, rows }, max_metatile))
}

fn extent_json(ram: &Ram, buffer: u32, decoded: usize) -> Value {
    let (read, end) = ram.extent(buffer, decoded);
    json!({ "buffer": hex(buffer), "decoded_bytes": decoded, "bytes_read": read, "read_end": end })
}

fn collision_summary(cells: &[u8]) -> Value {
    let mut values: BTreeMap<String, u32> = BTreeMap::new();
    for &cell in cells {
        *values.entry(format!("0x{cell:02X}")).or_default() += 1;
    }
    let count = |mask: u8| cells.iter().filter(|cell| *cell & mask != 0).count();
    json!({
        "cells": cells.len(),
        "values": values,
        "with_0x20_conditional_collision": count(0x20),
        "with_0x40": count(0x40),
        "with_0x80_collision": count(0x80),
    })
}

struct Warps {
    id: usize,
    rows: Vec<Value>,
    read: BTreeSet<u32>,
}

/// RunField: a player map_cell_change (UpdateFieldActors: the new map_cell_value) with 0x40 requests the map change in slot (value & 0x3F) of the map's warp row.
fn read_warps(ctx: &Ctx, warps: &mut Warps, map: u32, maps: u32, values: &BTreeSet<u8>) -> R<Vec<Value>> {
    let mut out = Vec::new();
    for &value in values {
        let slot = u32::from(value & 0x3F);
        let address = WARPS + map * WARP_STRIDE + slot * 6;
        let entry = ctx.rom.claim(address, 6, "table.field_map_warps", warps.id)?;
        warps.read.insert(address);
        let (target, x, y) = (le16(entry, 0), le16(entry, 2), le16(entry, 4));
        if u32::from(target) >= maps {
            return Err(format!("map {map}: warp cell 0x{value:02X} at 0x{address:08X} targets map {target}, past the {maps} map definitions"));
        }
        let mut row = json!({ "map": map, "cell": format!("0x{value:02X}"), "slot": slot, "address": hex(address), "target_map": target, "x": x, "y": y });
        if slot >= WARP_STRIDE / 6 {
            row["past_row"] = json!(format!("slot {slot} lies in the row of map {}", map + (slot * 6) / WARP_STRIDE));
        }
        if map != WORLD && value & 0x80 != 0 {
            row["player_blocked"] = json!("GetFieldMapCellCollisionMask blocks the player on 0x80 cells; reached only if the player stands wholly inside them");
        }
        out.push(row.clone());
        warps.rows.push(row);
    }
    Ok(out)
}

/// Warp entries no map's 0x40 cell values select, per row as runs of slots. Slot s >= 43 of map m is slot s - 43 of map m + 1.
fn unread_warps(ctx: &Ctx, warps: &Warps, maps: u32) -> R<()> {
    let slots = WARP_STRIDE / 6;
    if slots * 6 != WARP_STRIDE {
        return Err(format!("warp rows of {WARP_STRIDE} bytes are not whole 6-byte entries"));
    }
    for map in 0..maps {
        let row = WARPS + map * WARP_STRIDE;
        let mut slot = 0;
        while slot < slots {
            if warps.read.contains(&(row + slot * 6)) {
                slot += 1;
                continue;
            }
            let first = slot;
            while slot < slots && !warps.read.contains(&(row + slot * 6)) {
                slot += 1;
            }
            let previous = if map > 0 && first + slots <= 0x3F {
                format!(", and none of map {} selects slots {}..{}", map - 1, first + slots, (slot - 1 + slots).min(0x3F))
            } else {
                String::new()
            };
            ctx.unread(
                warps.id,
                row + first * 6,
                (slot - first) * 6,
                &format!(
                    "map {map} warp slots {first}..{}: RunField reads the 6-byte entry at (map * 129 + (map_cell_value & 0x3F) * 3) halfwords only for a map_cell_value with 0x40 (src/game/modes/run_field.c); no 0x40 cell value the map-cell readers return for map {map} selects these slots{previous}",
                    slot - 1
                ),
            )?;
        }
    }
    Ok(())
}

struct World {
    tiles: Vec<u8>,
    bg1_screen: Vec<u8>,
}

fn reached(map: u32, offset: u32) -> Vec<String> {
    vec![format!("table.field_map_definitions@0x{TABLE:08X}[{map}]+0x{offset:02X}")]
}

fn screen_layer(data: &[u8]) -> Layer {
    let entries: Vec<u16> = data.chunks_exact(2).take(0x400).map(|pair| le16(pair, 0)).collect();
    let rows = (entries.len() as u32).div_ceil(32);
    Layer { entries, columns: 32, rows }
}

fn world_map(ctx: &Ctx, record: &Record, item: usize, map_tiles: &[u8], palette: &[u8], overlays: &World, warps: &mut Warps, maps: u32, cells_out: &mut Vec<u8>) -> R<Value> {
    let width = record.width;
    let stride = u32::from(width >> 1);
    let (map_id, _) = ctx.item("field_map.world_metatile_map", record.bg0, MAPS, reached(WORLD, 0xC));
    let (tiles_id, _) = ctx.item("field_map.world_metatile_tiles", record.metatiles, MAPS, reached(WORLD, 0x14));
    let mut map_used = Used::new(record.bg0);
    let mut tiles_used = Used::new(record.metatiles);
    let map_data = ctx.rom.peek(record.bg0, 2 * (stride * 0xFF + 0xFF) + 2)?;
    let mut tile_offsets = Vec::with_capacity(0x40000);
    let mut max_metatile = 0u16;
    for y in 0..0x200u32 {
        for x in 0..0x200u32 {
            let offset = 2 * (stride * (y >> 1) + (x >> 1));
            let metatile = le16(map_data, offset as usize);
            map_used.mark(offset, 2);
            max_metatile = max_metatile.max(metatile);
            let tile_offset = u32::from(metatile) * 8 + ((y & 1) * 2 + (x & 1)) * 2;
            tiles_used.mark(tile_offset, 2);
            tile_offsets.push(tile_offset);
        }
    }
    let tile_data = ctx.rom.peek(record.metatiles, tiles_used.end())?;
    let entries: Vec<u16> = tile_offsets.iter().map(|&offset| le16(tile_data, offset as usize)).collect();
    let map_bytes = map_used.claim(ctx, "field_metatile_map", map_id)?;
    let tile_bytes = tiles_used.claim(ctx, "field_metatile_tiles", tiles_id)?;
    ctx.count(map_id, "c_mask:0x1FF tile coordinates (GetFieldBackgroundTile, map 0 has no dimension check)");
    ctx.count(tiles_id, "c_index:largest metatile id in the BG0 metatile map");
    let map_slice = ctx.rom.peek(record.bg0, map_used.end())?.to_vec();
    ctx.file(map_id, ".bin", &map_slice)?;
    ctx.file(tiles_id, ".bin", ctx.rom.peek(record.metatiles, tiles_used.end())?)?;
    ctx.set(map_id, json!({ "entries": map_used.end() / 2, "row_stride_metatiles": stride, "bytes_read": map_bytes }));
    ctx.set(tiles_id, json!({ "metatiles": u32::from(max_metatile) + 1, "bytes_read": tile_bytes }));
    let bg0_sources = json!({
        "entries": ["metatiles", ["rom", record.bg0, record.bg0 + map_used.end()], ["rom", record.metatiles, record.metatiles + tiles_used.end()], 0x200, 0x200, stride],
        "tiles": ["lz77", record.tiles], "palette": ["lz77", record.palette],
    });
    let bg0 = write_layer(ctx, item, "bg0", &Layer { entries, columns: 0x200, rows: 0x200 }, map_tiles, MAP_TILES_VRAM, palette, bg0_sources)?;

    let (collision_id, _) = ctx.item("field_map.world_collision", record.collision, COLLISION, reached(WORLD, 0x18));
    let mut collision_used = Used::new(record.collision);
    let mut warp_values = BTreeSet::new();
    let collision_data = ctx.rom.peek(record.collision, packed_cell(width, 0xFF, 0xFF) + 1)?;
    for cell_y in 0..0x100 {
        for cell_x in 0..0x100 {
            let index = packed_cell(width, cell_x, cell_y);
            let cell = collision_data[index as usize];
            collision_used.mark(index, 1);
            if cell & 0x40 != 0 {
                warp_values.insert(cell);
            }
        }
    }
    collision_used.claim(ctx, "field_map_collision", collision_id)?;
    ctx.count(collision_id, "c_mask:0xFF cell coordinates (GetPackedFieldMapCellCollision, UpdateFieldActorMapCell map 0)");
    let cells = ctx.rom.peek(record.collision, collision_used.end())?.to_vec();
    ctx.file(collision_id, ".bin", &cells)?;
    ctx.set(collision_id, collision_summary(&cells));
    *cells_out = cells;
    let warp_rows = read_warps(ctx, warps, WORLD, maps, &warp_values)?;

    let (bg3_map, bg3_map_data) = lz77_item(ctx, WORLD_BG3_METATILE_MAP, false, MAPS, "metatile_map", Some(BG0_BUFFER), ctx.roots.require(WORLD_BG3_METATILE_MAP)?)?;
    let (bg3_tiles, bg3_tiles_data) = lz77_item(ctx, WORLD_BG3_METATILE_TILES, false, MAPS, "metatile_tiles", Some(METATILE_BUFFER), ctx.roots.require(WORLD_BG3_METATILE_TILES)?)?;
    let mut ram = Ram::new();
    ram.write(BG0_BUFFER, &bg3_map_data, OWN_BG1)?;
    ram.write(METATILE_BUFFER, &bg3_tiles_data, OWN_METATILES)?;
    let mut overlay = Vec::with_capacity(80 * 80);
    let mut overlay_max = 0u16;
    for tile_y in 0x104..=0x153u32 {
        for tile_x in 0x16C..0x16C + 80u32 {
            let (x, y) = (tile_x - 0x16C, tile_y - 0x104);
            let metatile = ram.u16(BG0_BUFFER + (y >> 1) * 80 + (x >> 1) * 2, OWN_BG1)?;
            overlay_max = overlay_max.max(metatile);
            overlay.push(ram.u16(METATILE_BUFFER + ((x & 1) + (y & 1) * 2) * 2 + u32::from(metatile) * 8, OWN_METATILES)?);
        }
    }
    let bg3_sources = json!({
        "entries": ["metatiles", ["lz77", WORLD_BG3_METATILE_MAP], ["lz77", WORLD_BG3_METATILE_TILES], 80, 80, 40],
        "tiles": ["lz77", OVERLAY_TILES], "palette": ["lz77", record.palette],
    });
    let mut bg3 = write_layer(ctx, item, "bg3", &Layer { entries: overlay, columns: 80, rows: 80 }, &overlays.tiles, OVERLAY_TILES_VRAM, palette, bg3_sources)?;
    bg3["world_tile_origin"] = json!([0x16C, 0x104]);
    bg3["condition"] = json!("gFieldMapModeFlags & 1, TestEventFlag(0) set and gGameCompletionFlag == 0");
    bg3["metatile_map"] = json!({ "lz77": ctx.name(bg3_map), "extent": extent_json(&ram, BG0_BUFFER, bg3_map_data.len()), "metatiles_read": u32::from(overlay_max) + 1 });
    bg3["metatile_tiles"] = json!({ "lz77": ctx.name(bg3_tiles), "extent": extent_json(&ram, METATILE_BUFFER, bg3_tiles_data.len()) });

    let (bg2_id, bg2_data) = lz77_item(ctx, WORLD_BG2_SCREEN, true, MAPS, "tilemap", Some(0x0600_1000), ctx.roots.require(WORLD_BG2_SCREEN)?)?;
    let bg2_sources = json!({ "entries": ["screen", ["lz77", WORLD_BG2_SCREEN]], "tiles": ["lz77", record.tiles], "palette": ["lz77", record.palette] });
    let mut bg2 = write_layer(ctx, item, "bg2", &screen_layer(&bg2_data), map_tiles, MAP_TILES_VRAM, palette, bg2_sources)?;
    bg2["lz77"] = json!(ctx.name(bg2_id));
    bg2["decoded_bytes"] = json!(bg2_data.len());
    let overlay_sources = json!({ "entries": ["screen", ["lz77", OVERLAY_BG1_SCREEN]], "tiles": ["lz77", OVERLAY_TILES], "palette": ["lz77", record.palette] });
    let mut bg1 = write_layer(ctx, item, "bg1", &screen_layer(&overlays.bg1_screen), &overlays.tiles, OVERLAY_TILES_VRAM, palette, overlay_sources)?;
    bg1["lz77"] = json!(format!("lz77@0x{OVERLAY_BG1_SCREEN:08X}"));
    bg1["condition"] = json!("gFieldMapModeFlags & 1");

    Ok(json!({
        "bg0": bg0,
        "bg0_metatile_map": { "item": ctx.name(map_id), "entries_read": map_bytes / 2 },
        "metatile_tiles": { "item": ctx.name(tiles_id), "metatiles_read": u32::from(max_metatile) + 1, "bytes_read": tile_bytes },
        "bg1": bg1,
        "bg2": bg2,
        "bg3": bg3,
        "collision": { "item": ctx.name(collision_id), "cells_read": collision_used.end() },
        "warps": warp_rows,
    }))
}

fn field_map(ctx: &Ctx, map: u32, record: &Record, item: usize, map_tiles: &[u8], palette: &[u8], overlays: &World, warps: &mut Warps, maps: u32) -> R<Value> {
    let mut ram = Ram::new();
    let mut summary = json!({});
    let mut layers = Vec::new();
    for (layer, pointer, buffer, owner, offset) in [(0u32, Some(record.bg0), BG0_BUFFER, OWN_BG0, 0xCu32), (1, record.bg1, BG1_BUFFER, OWN_BG1, 0x10)] {
        let pointer = pointer.unwrap_or(0);
        if pointer == 0 {
            summary[format!("bg{layer}")] = Value::Null;
            continue;
        }
        let (id, data) = lz77_item(ctx, pointer, false, MAPS, "metatile_map", Some(buffer), reached(map, offset))?;
        ram.write(buffer, &data, owner)?;
        layers.push((layer, id, buffer, owner, data.len(), pointer));
    }
    let (metatiles_id, metatiles) = lz77_item(ctx, record.metatiles, false, MAPS, "metatile_tiles", Some(METATILE_BUFFER), reached(map, 0x14))?;
    ram.write(METATILE_BUFFER, &metatiles, OWN_METATILES)?;
    let (collision_id, collision) = lz77_item(ctx, record.collision, false, COLLISION, "collision", Some(COLLISION_BUFFER), reached(map, 0x18))?;
    ram.write(COLLISION_BUFFER, &collision, OWN_COLLISION)?;

    let mut max_metatile = 0u16;
    for &(layer, id, buffer, owner, decoded, pointer) in &layers {
        let (resolved, layer_max) = resolve_layer(&mut ram, buffer, owner, record.width, record.height)?;
        max_metatile = max_metatile.max(layer_max);
        let (characters, characters_at) = if layer == 1 && map == OVERLAY_MAP { (overlays.tiles.as_slice(), OVERLAY_TILES_VRAM) } else { (map_tiles, MAP_TILES_VRAM) };
        let tiles_source = if characters_at == OVERLAY_TILES_VRAM { OVERLAY_TILES } else { record.tiles };
        let sources = json!({
            "entries": ["metatiles", ["lz77", pointer], ["lz77", record.metatiles], resolved.columns, resolved.rows, u32::from(record.width >> 1)],
            "tiles": ["lz77", tiles_source], "palette": ["lz77", record.palette],
        });
        let mut value = write_layer(ctx, item, &format!("bg{layer}"), &resolved, characters, characters_at, palette, sources)?;
        value["metatile_map"] = json!({ "lz77": ctx.name(id), "extent": extent_json(&ram, buffer, decoded), "metatiles_read": u32::from(layer_max) + 1 });
        summary[format!("bg{layer}")] = value;
    }
    summary["metatile_tiles"] = json!({ "lz77": ctx.name(metatiles_id), "extent": extent_json(&ram, METATILE_BUFFER, metatiles.len()), "metatiles_read": if layers.is_empty() { 0 } else { u32::from(max_metatile) + 1 } });

    let (width, height) = (usize::from(record.width), usize::from(record.height));
    let mut cells = Vec::with_capacity(width * height);
    for y in 0..height {
        for x in 0..width {
            cells.push(ram.u8(COLLISION_BUFFER + (x + width * y) as u32, OWN_COLLISION)?);
        }
    }
    let mut warp_values = BTreeSet::new();
    let mut unsampled = BTreeSet::new();
    for row in 0..height {
        for x in 0..width {
            if let Some(value) = sampled_cell(&cells, width, height, x, row).filter(|value| value & 0x40 != 0) {
                warp_values.insert(value);
            }
        }
    }
    for &cell in &cells {
        if cell & 0x40 != 0 && !warp_values.contains(&cell) {
            unsampled.insert(format!("0x{cell:02X}"));
        }
    }
    let mut collision_value = collision_summary(&cells);
    collision_value["lz77"] = json!(ctx.name(collision_id));
    collision_value["extent"] = extent_json(&ram, COLLISION_BUFFER, collision.len());
    collision_value["0x40_values_no_2x2_sample_returns"] = json!(unsampled);
    summary["collision"] = collision_value;
    summary["warps"] = json!(read_warps(ctx, warps, map, maps, &warp_values)?);
    if map == OVERLAY_MAP && record.bg1 == Some(0) {
        let overlay_sources = json!({ "entries": ["screen", ["lz77", OVERLAY_BG1_SCREEN]], "tiles": ["lz77", OVERLAY_TILES], "palette": ["lz77", record.palette] });
        let mut bg1 = write_layer(ctx, item, "bg1", &screen_layer(&overlays.bg1_screen), &overlays.tiles, OVERLAY_TILES_VRAM, palette, overlay_sources)?;
        bg1["lz77"] = json!(format!("lz77@0x{OVERLAY_BG1_SCREEN:08X}"));
        bg1["condition"] = json!("gFieldMapModeFlags & 1");
        summary["bg1"] = bg1;
    }
    Ok(summary)
}

fn encounters(ctx: &Ctx, world: &Record, maps: u32) -> R<()> {
    let (grid, _) = ctx.item("field_map.world_encounter_grid", ENCOUNTER_GRID, ENCOUNTERS, ctx.roots.require(ENCOUNTER_GRID)?);
    let (thresholds, _) = ctx.item("table.world_map_encounter_thresholds", ENCOUNTER_THRESHOLDS, ENCOUNTERS, ctx.roots.require(ENCOUNTER_THRESHOLDS)?);
    let mut used = Used::new(ENCOUNTER_GRID);
    let mut pairs: BTreeMap<String, u32> = BTreeMap::new();
    let mut indexes = BTreeSet::new();
    let grid_data = ctx.rom.peek(ENCOUNTER_GRID, (packed_cell(world.width, 0xFF, 0xFF) << 1) + 2)?;
    for cell_y in 0..0x100 {
        for cell_x in 0..0x100 {
            let offset = packed_cell(world.width, cell_x, cell_y) << 1;
            let tile = le16(grid_data, offset as usize);
            used.mark(offset, 2);
            indexes.insert(tile >> 8);
            *pairs.entry(format!("threshold_index {} group {}", tile >> 8, tile & 0xFF)).or_default() += 1;
        }
    }
    used.claim(ctx, "world_map_encounter_grid", grid)?;
    ctx.count(grid, "c_mask:0xFF cell coordinates with map 0 width (TrySelectFieldRandomEncounter)");
    ctx.file(grid, ".bin", ctx.rom.peek(ENCOUNTER_GRID, used.end())?)?;
    ctx.set(grid, json!({ "entries": used.end() / 2, "row_stride_cells": world.width >> 1, "threshold_index_and_group": pairs }));
    let mut values = BTreeMap::new();
    for &index in &indexes {
        let value = le16(ctx.rom.claim(ENCOUNTER_THRESHOLDS + 2 * u32::from(index), 2, "table.world_map_encounter_thresholds", thresholds)?, 0);
        values.insert(index.to_string(), value);
    }
    ctx.count(thresholds, "c_index:high bytes of the world-map encounter grid");
    ctx.set(thresholds, json!({ "thresholds": values }));

    let (definitions, _) = ctx.item("table.field_encounter_definitions", ENCOUNTER_DEFINITIONS, ENCOUNTERS, ctx.roots.require(ENCOUNTER_DEFINITIONS)?);
    let mut rows = Vec::new();
    for index in 0..0x100u32 {
        let address = ENCOUNTER_DEFINITIONS + index * 6;
        let map = le16(ctx.rom.claim(address, 2, "table.field_encounter_definitions", definitions)?, 0);
        let threshold = le16(ctx.rom.claim(address + 2, 2, "table.field_encounter_definitions", definitions)?, 0);
        let group = le16(ctx.rom.claim(address + 4, 2, "table.field_encounter_definitions", definitions)?, 0);
        rows.push(json!({ "map": map, "threshold": threshold, "group": group }));
        if map == 0 {
            ctx.count(definitions, "terminator");
            ctx.set(definitions, json!({ "entries": rows, "note": "the map 0 row ends the scan; its threshold and group apply to maps without a row" }));
            return Ok(());
        }
        if u32::from(map) >= maps {
            return Err(format!("encounter definition at 0x{address:08X} names map {map}, past the {maps} map definitions"));
        }
    }
    Err(format!("encounter definitions at 0x{ENCOUNTER_DEFINITIONS:08X}: no map 0 row within the u8 index range"))
}

fn palette_animation(ctx: &Ctx) -> R<()> {
    for (address, frames, banks) in [(PALETTE_FRAMES, 13u32, json!({ "0x7D": "palette bank 1, frames 0..12", "0x7E": "palette bank 3, frames 0..5" })), (PALETTE_FRAMES_B, 13, json!({ "0x7D": "palette bank 2, frames 0..12" }))] {
        let (id, _) = ctx.item("field_map.palette_animation", address, ANIMATION, ctx.roots.require(address)?);
        let data = ctx.rom.claim(address, frames * 0x20, "palette", id)?.to_vec();
        ctx.count(id, "c_constant:frame wrap 0xD for map 0x7D (UpdateFieldDisplay); map 0x7E wraps at 6");
        ctx.file(id, ".png", &palette_swatch(&data))?;
        ctx.view(id, json!({ "t": "palette", "colors": ["rom", address, address + frames * 0x20] }));
        ctx.set(id, json!({ "frames": frames, "bytes_per_frame": 0x20, "frame_interval_updates": 15, "maps": banks }));
    }
    Ok(())
}

fn return_maps(ctx: &Ctx, records: &[Record], positions: usize, maps: u32) -> R<()> {
    for address in [RETURN_MAPS, RETURN_MAPS_24] {
        let (id, _) = ctx.item("table.field_return_maps", address, RUN_FIELD, ctx.roots.require(address)?);
        let mut rows = Vec::new();
        for index in 0..0x100u32 {
            let entry = address + index * 10;
            let map = le16(ctx.rom.claim(entry, 2, "table.field_return_maps", id)?, 0);
            if map == 0 {
                break;
            }
            if u32::from(map) >= maps {
                return Err(format!("return map entry at 0x{entry:08X} names map {map}, past the {maps} map definitions"));
            }
            let fields = ctx.rom.claim(entry + 2, 8, "table.field_return_maps", id)?;
            let group = records[map as usize].group;
            if group == 0 {
                return Err(format!("return map entry at 0x{entry:08X}: map {map} has map group 0, so RunField would read before 0x{GROUP_POSITIONS:08X}"));
            }
            let position = GROUP_POSITIONS + 6 * u32::from(group - 1);
            let x = le16(ctx.rom.claim(position + 2, 2, "table.map_group_positions", positions)?, 0) as i16;
            let y = le16(ctx.rom.claim(position + 4, 2, "table.map_group_positions", positions)?, 0) as i16;
            rows.push(json!({
                "map": map, "x": le16(fields, 0), "y": le16(fields, 2), "state_x": le16(fields, 4), "state_y": le16(fields, 6),
                "map_group": group, "world_position": [x, y],
            }));
        }
        ctx.count(id, "terminator");
        ctx.set(id, json!({ "entries": rows }));
    }
    Ok(())
}

fn decorations(ctx: &Ctx, positions: usize) -> R<()> {
    let (alternate, _) = ctx.item("table.field_decoration_positions", ALTERNATE_DECORATIONS, DECORATIONS, ctx.roots.require(ALTERNATE_DECORATIONS)?);
    let (resources, _) = ctx.item("table.field_decoration_resources", DECORATION_GRAPHICS, DECORATIONS, ctx.roots.require(DECORATION_GRAPHICS)?);
    ctx.roots.require(DECORATION_PALETTES)?;
    let mut kinds = BTreeSet::new();
    let mut tables = json!({});
    for (name, base, count, id, format) in [
        ("map 0", GROUP_POSITIONS, DECORATION_COUNT, positions, "table.map_group_positions"),
        ("map 0x40", ALTERNATE_DECORATIONS, ALTERNATE_DECORATION_COUNT, alternate, "table.map_group_positions"),
    ] {
        let mut rows = Vec::new();
        for index in 0..count {
            let entry = ctx.rom.claim(base + index * 6, 6, format, id)?;
            let (kind, x, y) = (le16(entry, 0) as i16, le16(entry, 2) as i16, le16(entry, 4) as i16);
            if kind < 0 {
                return Err(format!("decoration at 0x{:08X} has kind {kind}", base + index * 6));
            }
            kinds.insert(kind as u32);
            rows.push(json!({ "kind": kind, "x": x, "y": y }));
        }
        tables[name] = json!(rows);
    }
    ctx.count(positions, "c_constant:FIELD_DECORATION_SLOT_COUNT");
    ctx.count(alternate, "c_constant:FIELD_ALTERNATE_DECORATION_COUNT");
    ctx.set(alternate, json!({ "entries": tables["map 0x40"], "note": "the same 6-byte rows as 0x087AFBB4: map group g reads row g - 1, so these are rows 42..44" }));
    let mut resource_rows = Vec::new();
    for &kind in &kinds {
        let graphics = le32(ctx.rom.claim(DECORATION_GRAPHICS + kind * 8, 4, "table.field_decoration_resources", resources)?, 0);
        let palette = le32(ctx.rom.claim(DECORATION_PALETTES + kind * 8, 4, "table.field_decoration_resources", resources)?, 0);
        let from = format!("table.field_decoration_resources@0x{DECORATION_GRAPHICS:08X}[{kind}]");
        let (graphics_id, new) = ctx.item("field_map.decoration_graphics", graphics, DECORATIONS, vec![from.clone()]);
        if new {
            ctx.rom.claim(graphics, 0x200, NEUTRAL, graphics_id)?;
            ctx.count(graphics_id, "c_literal_length");
            ctx.set(graphics_id, json!({ "via": "queue_copy", "length": 0x200, "destination_area": "vram (OBJ)" }));
        }
        let (palette_id, new) = ctx.item("field_map.decoration_palette", palette, DECORATIONS, vec![from]);
        if new {
            let data = ctx.rom.claim(palette, 0x20, "palette", palette_id)?.to_vec();
            ctx.count(palette_id, "c_literal_length");
            ctx.file(palette_id, ".png", &palette_swatch(&data))?;
            ctx.view(palette_id, json!({ "t": "palette", "colors": ["rom", palette, palette + 0x20] }));
            ctx.set(palette_id, json!({ "via": "queue_copy", "length": 0x20, "destination_area": "palette (OBJ)" }));
        }
        resource_rows.push(json!({ "kind": kind, "graphics": hex(graphics), "palette": hex(palette) }));
    }
    let last = *kinds.iter().next_back().ok_or("no decoration kind is read")?;
    let listed: Vec<String> = kinds.iter().map(|kind| kind.to_string()).collect();
    for kind in (0..=last).filter(|kind| !kinds.contains(kind)) {
        ctx.unread(
            resources,
            DECORATION_GRAPHICS + kind * 8,
            8,
            &format!(
                "decoration kind {kind} graphics and palette pointers: UpdateFieldMapDecorationSprites indexes them by decoration_position[0] of the FIELD_DECORATION_SLOT_COUNT rows at 0x087AFBB4 or the FIELD_ALTERNATE_DECORATION_COUNT rows at 0x087AFCB0 (src/field/update_field_map_decoration_sprites.c); those rows hold kinds {{{}}}",
                listed.join(", ")
            ),
        )?;
    }
    ctx.count(resources, "c_index:decoration kinds in the position tables");
    ctx.set(resources, json!({ "entries": resource_rows }));
    let mut data = json!({ "entries": tables["map 0"] });
    data["note"] = json!("also read as map group positions: map group g uses entry g - 1 (+2, +4)");
    ctx.set(positions, data);
    Ok(())
}

/// IsFieldTerrainBlockedForActorModel (is_field_terrain_blocked_for_actor_model.c).
fn terrain_blocked(model: u8, cell: u8, conditional: bool) -> bool {
    if conditional && cell & 0x20 != 0 {
        return true;
    }
    match cell & 0x1F {
        4 | 6 | 7 | 9 => model.wrapping_sub(0x69) <= 2,
        8 | 10 => model == 0x69,
        11 => model.wrapping_sub(0x69) <= 1,
        _ => false,
    }
}

/// The map viewer's collision grid: map 0 reads packed cells through GetPackedFieldMapCellCollision (16-pixel cells,
/// bit 0x40 bypasses the terrain rule); other maps read width x height 8-pixel cells through GetFieldMapCellCollisionMask.
/// `sha1` covers the mask for the default settings: map 0 with model 0x69 and no conditional collision, other maps for the player.
fn collision_view(ctx: &Ctx, map: u32, record: &Record) -> R<Value> {
    if map == WORLD {
        let end = packed_cell(record.width, 0xFF, 0xFF) + 1;
        let cells = ctx.rom.peek(record.collision, end)?;
        let mut mask = Vec::with_capacity(256 * 256);
        for y in 0..256 {
            for x in 0..256 {
                let cell = cells[packed_cell(record.width, x, y) as usize];
                mask.push(u8::from(cell & 0x40 == 0 && terrain_blocked(0x69, cell, false)));
            }
        }
        return Ok(json!({ "t": "map", "map": map, "packed": true, "columns": 256, "rows": 256, "cell": 16, "stride": record.width, "collision": ["rom", record.collision, record.collision + end], "sha1": crate::sha1_hex(&mask) }));
    }
    let cells = super::bios::lz77_dry(ctx.rom, record.collision, false)?;
    let (width, height) = (u32::from(record.width), u32::from(record.height));
    let mask: Vec<u8> = (0..width * height).map(|index| cells.get(index as usize).map_or(0xFF, |cell| cell & 0x80)).collect();
    Ok(json!({ "t": "map", "map": map, "packed": false, "columns": width, "rows": height, "cell": 8, "collision": ["lz77", record.collision], "sha1": crate::sha1_hex(&mask) }))
}

fn run(ctx: &Ctx) -> R<()> {
    let (table, _) = ctx.item("table.field_map_definitions", TABLE, DEFINITIONS, ctx.roots.require(TABLE)?);
    let next = next_root(ctx, TABLE)?;
    if (next - TABLE) % RECORD != 0 {
        return Err(format!("0x{next:08X} - 0x{TABLE:08X} is not a whole number of 32-byte map definitions"));
    }
    let maps = (next - TABLE) / RECORD;
    ctx.count(table, "next_root");
    let warp_next = next_root(ctx, WARPS)?;
    if warp_next - WARPS != maps * WARP_STRIDE {
        return Err(format!("warp table 0x{WARPS:08X}..0x{warp_next:08X} does not hold {maps} rows of {WARP_STRIDE} bytes"));
    }
    let records: Vec<Record> = (0..maps).map(|map| read_record(ctx, table, map)).collect::<R<_>>()?;
    ctx.set(table, json!({
        "maps": maps,
        "count_check": format!("the warp table 0x{WARPS:08X}..0x{warp_next:08X} (next root) holds {maps} rows of {WARP_STRIDE} bytes"),
        "records": records.iter().enumerate().map(|(map, record)| json!({
            "map": map, "address": hex(record.address), "width": record.width, "height": record.height,
            "tiles": hex(record.tiles), "palette": hex(record.palette), "bg0_metatile_map": hex(record.bg0),
            "bg1_metatile_map": record.bg1.map(hex), "metatile_tiles": hex(record.metatiles), "collision": hex(record.collision),
            "has_data_1c": record.has_data, "map_group_1d": record.group, "song_1e": record.song,
        })).collect::<Vec<_>>(),
    }));

    let (_, tiles) = lz77_item(ctx, OVERLAY_TILES, true, MAPS, "tiles", Some(OVERLAY_TILES_VRAM), ctx.roots.require(OVERLAY_TILES)?)?;
    let (_, bg1_screen) = lz77_item(ctx, OVERLAY_BG1_SCREEN, true, MAPS, "tilemap", Some(0x0600_0800), ctx.roots.require(OVERLAY_BG1_SCREEN)?)?;
    let overlays = World { tiles, bg1_screen };
    lz77_item(ctx, SLIDE_TILES, true, SLIDE, "tiles", Some(OVERLAY_TILES_VRAM), ctx.roots.require(SLIDE_TILES)?)?;
    lz77_item(ctx, SLIDE_SCREEN, true, SLIDE, "tilemap", Some(0x0600_0800), ctx.roots.require(SLIDE_SCREEN)?)?;

    let (warps_id, _) = ctx.item("table.field_map_warps", WARPS, RUN_FIELD, ctx.roots.require(WARPS)?);
    let mut warps = Warps { id: warps_id, rows: Vec::new(), read: BTreeSet::new() };
    let mut world_cells = Vec::new();
    for (map, record) in records.iter().enumerate() {
        let map = map as u32;
        let (item, _) = ctx.item("field_map", record.address, MAPS, vec![format!("table.field_map_definitions@0x{TABLE:08X}[{map}]")]);
        let (tiles_id, map_tiles) = lz77_item(ctx, record.tiles, true, MAPS, "tiles", Some(MAP_TILES_VRAM), reached(map, 4))?;
        let (palette_id, palette) = lz77_item(ctx, record.palette, false, MAPS, "palette", Some(0x0500_0000), reached(map, 8))?;
        let mut summary = if map == WORLD {
            world_map(ctx, record, item, &map_tiles, &palette, &overlays, &mut warps, maps, &mut world_cells)?
        } else {
            field_map(ctx, map, record, item, &map_tiles, &palette, &overlays, &mut warps, maps)?
        };
        summary["map"] = json!(map);
        summary["width"] = json!(record.width);
        summary["height"] = json!(record.height);
        summary["tiles"] = json!({ "lz77": ctx.name(tiles_id), "decoded_bytes": map_tiles.len(), "characters": map_tiles.len() / 32 });
        summary["palette"] = json!({ "lz77": ctx.name(palette_id), "decoded_bytes": palette.len(), "colors": palette.len() / 2 });
        summary["map_group"] = json!(record.group);
        summary["song"] = json!(record.song);
        ctx.view(item, collision_view(ctx, map, record)?);
        ctx.count(item, "next_root");
        ctx.set(item, summary);
    }
    ctx.count(warps_id, "c_index:collision cell values with 0x40 that the map-cell readers return");
    unread_warps(ctx, &warps, maps)?;
    ctx.set(warps_id, json!({ "row_bytes": WARP_STRIDE, "entries": warps.rows }));

    encounters(ctx, &records[WORLD as usize], maps)?;
    palette_animation(ctx)?;
    let (positions, _) = ctx.item("table.map_group_positions", GROUP_POSITIONS, DECORATIONS, ctx.roots.require(GROUP_POSITIONS)?);
    return_maps(ctx, &records, positions, maps)?;
    decorations(ctx, positions)?;
    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn packed_cells_cover_the_world_map() {
        assert_eq!(packed_cell(0x200, 0xFF, 0xFF), 0xFFFF);
        assert_eq!(packed_cell(0x200, 0x100, 0x101), 0x100);
    }

    #[test]
    fn map_cell_sampling() {
        let cells = [0x41, 0x41, 0x05, 0x41, 0x41, 0x05];
        assert_eq!(sampled_cell(&cells, 3, 2, 0, 0), Some(0x41));
        assert_eq!(sampled_cell(&cells, 3, 2, 1, 0), Some(0x05));
        let mixed = [0x41, 0x42, 0x41, 0x42];
        assert_eq!(sampled_cell(&mixed, 2, 2, 0, 0), None);
    }

    #[test]
    fn flipped_tile_render() {
        let mut characters = vec![0u8; 32];
        characters[0] = 0x01;
        let palette: Vec<u8> = (0..32).collect();
        let (png, missing) = render(&[0x0C00, 0x0001], 2, 1, &characters, &palette);
        assert_eq!(missing, 1);
        assert!(!png.is_empty());
    }
}
