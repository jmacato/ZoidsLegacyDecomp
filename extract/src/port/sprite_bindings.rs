//! The tiles and palette a CreateSprite / CreateSpriteFromTable sprite draws with: what OBJ VRAM holds at its tile offset
//! and palette RAM at its palette bank when it is created. Constant propagation over the matched code (thumb.rs) gives the
//! call arguments; loads are replayed in call-site order from each entry point no code calls or references directly.

use std::collections::{BTreeMap, BTreeSet, HashMap};
use std::rc::Rc;

use serde_json::{json, Value};

use super::graphics::lz77_item;
use super::{bios, Port};
use crate::basis::Basis;
use crate::rom::{le16, le32, R};
use crate::run::Ctx;
use crate::thumb::{Call, Code, Store, ARGS, V};

pub const BINDINGS: Basis = Basis::C(&[
    ("src/graphics/create_sprite.c", "3e6d071d427dd01d0493109c99bfdbe77c897841"),
    ("src/graphics/create_sprite_from_table.c", "10890981a20d144607c171ecaf63ea3a74f3e369"),
    ("src/graphics/update_sprites_and_build_oam.c", "88c4542b353249eb6d2ce2b1f47149a73220c791"),
    ("src/graphics/load_compressed_palette.c", "062d97738ff22254c43d529131b02319a2b4c0d5"),
    ("src/graphics/load_sprite_graphics_from_table.c", "ea9d494504eeb3b592c2ef609590e7083cc46b7b"),
    ("src/graphics/queue_copy.c", "9f3482ebd43e0bafd38ec6fb0cc9bd5edfafa8b9"),
    ("src/graphics/process_transfer_queue.c", "bd3df7baf01ad4e5d00e43a241686352967859c7"),
    ("src/runtime/bios_cpu_fast_set.c", "6cd6d462cc140c38f3a41b6439e2f3a1f1f8af7d"),
    ("src/runtime/bios_cpu_set.c", "8e28b09f3c4534c72786f043994f7d9f90ce8382"),
    ("src/runtime/bios_lz77_to_vram.c", "677a5e6ea025e95d37197486ddb4d820024df4e3"),
    ("src/runtime/bios_lz77_to_wram.c", "749b617a2692633d25e32cc119e645cf942a4722"),
]);

pub const PORT: Port = Port { name: "sprite_bindings", bases: &[BINDINGS, bios::LZ77_VRAM, bios::LZ77_WRAM, bios::CPU_SET], run };

const CREATE_SPRITE: u32 = 0x0809_4484;
const CREATE_SPRITE_FROM_TABLE: u32 = 0x0809_4374;
const CPU_FAST_SET: u32 = 0x080E_CD28;
const CPU_SET: u32 = 0x080E_CD2C;
const LZ77_VRAM: u32 = 0x080E_CD34;
const LZ77_WRAM: u32 = 0x080E_CD38;
const QUEUE_COPY: u32 = 0x0809_5208;
const OBJ_VRAM: u32 = 0x0601_0000;
const OBJ_VRAM_BYTES: u32 = 0x8000;
const OBJ_PALETTE: u32 = 0x0500_0200;
const STREAMED: u32 = 0x40_0000;
const LOAD_PILOT_PORTRAIT: u32 = 0x0809_A94C;
const QUEUE_PILOT_PORTRAIT: u32 = 0x0809_A9C8;
const LOAD_ZOID_ICON: u32 = 0x0809_A4CC;
const QUEUE_ZOID_ICON: u32 = 0x0809_A52C;
/// GRAPHICS_ZOID_ICON_BYTES, GRAPHICS_PILOT_PORTRAIT_BYTES (graphics_resources.h).
const ZOID_ICON_BYTES: u32 = 0x800;
const PILOT_PORTRAIT_BYTES: u32 = 0x480;
const DEPTH: usize = 24;

#[derive(Clone, Copy, PartialEq, Eq, Hash, Debug, PartialOrd, Ord)]
enum Source {
    Lz77 { address: u32, vram: bool },
    Rom(u32),
    Memory(u32),
    /// Source `slot` of whichever entry an indexed loader was given (see Family).
    Family { family: usize, slot: usize },
    Unknown,
}

/// What an indexed loader writes when its index is not a constant: one source list per table entry it can be given.
struct Family {
    label: &'static str,
    choices: Vec<(String, Vec<Source>)>,
}

#[derive(Clone, Debug)]
enum Event {
    /// LZ77 (`length` from the header) or a copy (`length` is the CpuSet / CpuFastSet control or QueueCopy byte count).
    Write { destination: V, length: V, source: V, kind: u32 },
    Store { address: u32, size: u8, value: V },
    Sprite { args: [V; ARGS], table: bool },
    Loader { target: u32, args: [V; ARGS] },
    Unresolved { what: &'static str, args: [V; ARGS] },
}

#[derive(Clone, Debug)]
struct Step {
    chain: Vec<u32>,
    event: Event,
}

#[derive(Clone, Copy, Debug)]
struct Span {
    start: u32,
    end: u32,
    source: Source,
    offset: u32,
}

#[derive(Default)]
struct Memory {
    spans: Vec<Span>,
}

impl Memory {
    fn write(&mut self, start: u32, end: u32, source: Source, offset: u32) {
        let mut kept = Vec::with_capacity(self.spans.len() + 2);
        for span in self.spans.drain(..) {
            if span.end <= start || span.start >= end {
                kept.push(span);
                continue;
            }
            if span.start < start {
                kept.push(Span { end: start, ..span });
            }
            if span.end > end {
                kept.push(Span { start: end, offset: span.offset + (end - span.start), ..span });
            }
        }
        kept.push(Span { start, end, source, offset });
        kept.sort_by_key(|span| span.start);
        self.spans = kept;
    }

    /// The known spans inside [start, end), clipped.
    fn read_partial(&self, start: u32, end: u32) -> Vec<Span> {
        self.spans
            .iter()
            .filter(|span| span.end > start && span.start < end && span.source != Source::Unknown)
            .map(|span| {
                let (from, to) = (span.start.max(start), span.end.min(end));
                Span { start: from, end: to, source: span.source, offset: span.offset + (from - span.start) }
            })
            .collect()
    }

    /// The spans covering [start, end), clipped; `None` when any byte is unwritten or unknown.
    fn read(&self, start: u32, end: u32) -> Option<Vec<Span>> {
        let mut out = Vec::new();
        let mut at = start;
        for span in &self.spans {
            if span.end <= at || span.start >= end {
                continue;
            }
            if span.start > at || span.source == Source::Unknown {
                return None;
            }
            let stop = span.end.min(end);
            out.push(Span { start: at, end: stop, source: span.source, offset: span.offset + (at - span.start) });
            at = stop;
            if at >= end {
                break;
            }
        }
        (at >= end).then_some(out)
    }
}

struct Walker<'a> {
    code: &'a Code<'a>,
    ctx: &'a Ctx<'a>,
    memo: HashMap<(u32, [V; ARGS]), Rc<Vec<Step>>>,
    active: BTreeSet<u32>,
    failures: BTreeMap<u32, String>,
}

fn rom_word(ctx: &Ctx, address: u32) -> Option<u32> {
    (address >= crate::BASE && address % 4 == 0).then(|| ctx.rom.scan_word(address)).flatten()
}

impl<'a> Walker<'a> {
    fn walk(&mut self, entry: u32, args: [V; ARGS], depth: usize) -> Rc<Vec<Step>> {
        if let Some(steps) = self.memo.get(&(entry, args.clone())) {
            return steps.clone();
        }
        let Some(function) = self.code.function_at(entry) else { return Rc::new(Vec::new()) };
        let analysis = match self.code.analyze(function, &args) {
            Ok(analysis) => analysis,
            Err(error) => {
                self.failures.insert(entry, error);
                return Rc::new(Vec::new());
            }
        };
        self.active.insert(entry);
        enum Site {
            Call(Call),
            Reference(u32),
            Store(Store),
        }
        let mut sites: Vec<(u32, Site)> = analysis.calls.iter().map(|call| (call.site, Site::Call(call.clone()))).collect();
        for (&site, &value) in &analysis.literals {
            if value & 1 == 1 && self.code.function_at(value & !1).is_some() {
                sites.push((site, Site::Reference(value & !1)));
            }
        }
        sites.extend(analysis.stores.iter().map(|store| (store.site, Site::Store(store.clone()))));
        sites.sort_by_key(|(site, _)| *site);
        let mut steps = Vec::new();
        for (site, item) in sites {
            let local = |event: Event| Step { chain: vec![site], event };
            let call = match item {
                Site::Reference(target) => {
                    if depth < DEPTH && !self.active.contains(&target) {
                        let inner = self.walk(target, Default::default(), depth + 1);
                        steps.extend(inner.iter().map(|step| Step { chain: [vec![site], step.chain.clone()].concat(), event: step.event.clone() }));
                    }
                    continue;
                }
                Site::Store(store) => {
                    steps.push(local(Event::Store { address: store.address, size: store.size, value: store.value }));
                    continue;
                }
                Site::Call(call) => call,
            };
            let a = call.args;
            match call.target {
                LZ77_VRAM | LZ77_WRAM => match a[0].c() {
                    Some(source) if self.ctx.rom.is_data(source) && rom_word(self.ctx, source).map_or(false, |header| header & 0xFF == 0x10) => {
                        let length = rom_word(self.ctx, source).unwrap() >> 8;
                        steps.push(local(Event::Write { destination: a[1].clone(), length: V::C(length), source: V::C(source), kind: call.target }));
                    }
                    _ => steps.push(local(Event::Unresolved { what: "lz77", args: a })),
                },
                CPU_FAST_SET | CPU_SET | QUEUE_COPY => {
                    steps.push(local(Event::Write { destination: a[1].clone(), length: a[2].clone(), source: a[0].clone(), kind: call.target }));
                }
                CREATE_SPRITE | CREATE_SPRITE_FROM_TABLE => steps.push(local(Event::Sprite { args: a, table: call.target == CREATE_SPRITE_FROM_TABLE })),
                LOAD_PILOT_PORTRAIT | QUEUE_PILOT_PORTRAIT | LOAD_ZOID_ICON | QUEUE_ZOID_ICON => steps.push(local(Event::Loader { target: call.target, args: a })),
                target => {
                    if depth < DEPTH && !self.active.contains(&target) && self.code.function_at(target).is_some() {
                        let inner = self.walk(target, a, depth + 1);
                        steps.extend(inner.iter().map(|step| Step { chain: [vec![site], step.chain.clone()].concat(), event: step.event.clone() }));
                    }
                }
            }
        }
        self.active.remove(&entry);
        let steps = Rc::new(steps);
        self.memo.insert((entry, args), steps.clone());
        steps
    }
}

/// Bytes stored at fixed RAM addresses so far, in call-site order.
#[derive(Default)]
struct Globals {
    bytes: BTreeMap<u32, u8>,
}

impl Globals {
    fn read(&self, address: u32, size: u8) -> Option<u32> {
        let mut value = 0u32;
        for index in 0..u32::from(size) {
            value |= u32::from(*self.bytes.get(&(address + index))?) << (index * 8);
        }
        Some(value)
    }

    fn store(&mut self, address: u32, size: u8, value: Option<u32>) {
        for index in 0..u32::from(size) {
            match value {
                Some(value) => self.bytes.insert(address + index, (value >> (index * 8)) as u8),
                None => self.bytes.remove(&(address + index)),
            };
        }
    }

    fn eval(&self, value: &V) -> Option<u32> {
        value.eval(&|address, size| self.read(address, size))
    }
}

/// Entry points: functions no matched code calls with BL or loads as a pointer literal.
fn entry_points(code: &Code) -> R<Vec<u32>> {
    let mut targets = BTreeSet::new();
    for function in &code.functions {
        let Ok(analysis) = code.analyze(*function, &Default::default()) else { continue };
        targets.extend(analysis.calls.iter().map(|call| call.target));
        targets.extend(analysis.literals.values().filter(|value| *value & 1 == 1).map(|value| value & !1));
    }
    Ok(code.functions.iter().map(|function| function.entry).filter(|entry| !targets.contains(entry)).collect())
}

struct Piece {
    tile: u32,
    x: i32,
    y: i32,
    width: u32,
    height: u32,
    flips: u32,
    color256: bool,
}

fn pieces(ctx: &Ctx, frame: u32) -> R<Vec<Piece>> {
    let mut out = Vec::new();
    let mut at = frame;
    loop {
        let piece = ctx.rom.peek(at, 20)?;
        if le16(piece, 0) as i16 == -1 {
            return Ok(out);
        }
        out.push(Piece {
            tile: u32::from(le16(piece, 0)),
            x: i32::from(le16(piece, 4) as i16),
            y: i32::from(le16(piece, 6) as i16),
            width: u32::from(le16(piece, 8)),
            height: u32::from(le16(piece, 0xA)),
            flips: u32::from(piece[2]) & 3,
            color256: piece[0x11] & 0x20 != 0,
        });
        at += 20;
    }
}

/// Frames as indexed pixels into the 256-colour OBJ palette (0 = transparent), each piece at its x/y with its flips,
/// earlier pieces in front, as UpdateSpritesAndBuildOam orders them. Returns (left, top, width, height, pixels) per frame.
fn render(frames: &[Vec<Piece>], tile_offset: u32, palette_bank: u32, vram: &[u8]) -> Vec<(i32, i32, u32, u32, Vec<u8>)> {
    frames
        .iter()
        .map(|pieces| {
            if pieces.is_empty() {
                return (0, 0, 0, 0, Vec::new());
            }
            let left = pieces.iter().map(|piece| piece.x).min().unwrap();
            let top = pieces.iter().map(|piece| piece.y).min().unwrap();
            let right = pieces.iter().map(|piece| piece.x + piece.width as i32).max().unwrap();
            let bottom = pieces.iter().map(|piece| piece.y + piece.height as i32).max().unwrap();
            let (width, height) = ((right - left) as u32, (bottom - top) as u32);
            let mut pixels = vec![0u8; (width * height) as usize];
            let mut filled = vec![false; pixels.len()];
            for piece in pieces {
                let base = (tile_offset + piece.tile) * 32;
                for row in 0..piece.height {
                    for column in 0..piece.width {
                        let sx = if piece.flips & 1 != 0 { piece.width - 1 - column } else { column };
                        let sy = if piece.flips & 2 != 0 { piece.height - 1 - row } else { row };
                        let tile = sy / 8 * (piece.width / 8) + sx / 8;
                        let wrap = |at: u32| (if vram.len() == OBJ_VRAM_BYTES as usize { at & (OBJ_VRAM_BYTES - 1) } else { at }) as usize;
                        let color = if piece.color256 {
                            vram[wrap(base + tile * 64 + sy % 8 * 8 + sx % 8)]
                        } else {
                            let byte = vram[wrap(base + tile * 32 + sy % 8 * 4 + sx % 8 / 2)];
                            let nibble = (byte >> (sx % 2 * 4)) & 15;
                            if nibble == 0 { 0 } else { (palette_bank as u8 & 15) * 16 + nibble }
                        };
                        if color == 0 {
                            continue;
                        }
                        let x = (piece.x - left) as u32 + column;
                        let y = (piece.y - top) as u32 + row;
                        let index = (y * width + x) as usize;
                        if !filled[index] {
                            filled[index] = true;
                            pixels[index] = color;
                        }
                    }
                }
            }
            (left, top, width, height, pixels)
        })
        .collect()
}

fn merge(mut ranges: Vec<(u32, u32)>) -> Vec<(u32, u32)> {
    ranges.sort();
    let mut merged: Vec<(u32, u32)> = Vec::new();
    for (start, end) in ranges {
        match merged.last_mut() {
            Some(last) if start <= last.1 => last.1 = last.1.max(end),
            _ => merged.push((start, end)),
        }
    }
    merged
}

fn resolve(memory: &Memory, ranges: Vec<(u32, u32)>) -> Result<Vec<Span>, String> {
    let mut spans = Vec::new();
    for (start, end) in ranges {
        spans.extend(memory.read(start, end).ok_or_else(|| format!("{}..{} not written by a constant load before this call in call-site order", hex(start), hex(end)))?);
    }
    Ok(spans)
}

fn source_json(span: &Span) -> Value {
    match span.source {
        Source::Family { slot, .. } => json!({ "slot": slot }),
        Source::Lz77 { address, .. } => json!(["lz77", address]),
        Source::Rom(address) => json!(["rom", address, address + span.offset + (span.end - span.start)]),
        _ => Value::Null,
    }
}

/// Copy each span's source bytes into `target` (OBJ VRAM or OBJ palette RAM starting at `base`).
fn fill(ctx: &Ctx, spans: &[Span], target: &mut [u8], base: u32, site: &[String], new_sources: &mut Vec<String>) -> Result<(), String> {
    for span in spans {
        let bytes = match span.source {
            Source::Lz77 { address, vram } => {
                if ctx.kinds_at(address).iter().any(|kind| kind == "lz77") {
                    bios::lz77_dry(ctx.rom, address, vram)?
                } else {
                    new_sources.push(format!("  new lz77 {} at {}", hex(address), site.join(">")));
                    lz77_item(ctx, address, vram, BINDINGS, "raw", Some(span.start), vec![format!("sprite binding {}", site.join(">"))])?.1
                }
            }
            Source::Rom(address) => ctx.rom.peek(address, span.offset + (span.end - span.start))?.to_vec(),
            _ => return Err(format!("{}..{} has no ROM source", hex(span.start), hex(span.end))),
        };
        let slice = bytes.get(span.offset as usize..(span.offset + span.end - span.start) as usize).ok_or_else(|| format!("{}..{}: source shorter than its span", hex(span.start), hex(span.end)))?;
        target[(span.start - base) as usize..(span.end - base) as usize].copy_from_slice(slice);
    }
    Ok(())
}

/// Replay a store, write or loader call. Returns the spans written (`Some(empty)` for a store), or `None` for a loader
/// call whose tile offset or palette bank is unknown.
fn replay(ctx: &Ctx, event: &Event, globals: &mut Globals, memory: &mut Memory, families: &mut Vec<Family>) -> R<Option<Vec<Span>>> {
    let mut written = Vec::new();
    match event {
        Event::Store { address, size, value } => {
            let value = globals.eval(value);
            globals.store(*address, *size, value);
            memory.write(*address, *address + u32::from(*size), Source::Unknown, 0);
        }
        Event::Write { destination, length, source, kind } => {
            let (Some(destination), Some(length), Some(source)) = (globals.eval(destination), globals.eval(length), globals.eval(source)) else { return Ok(Some(written)) };
            let (length, source) = match *kind {
                LZ77_VRAM | LZ77_WRAM => (length, Source::Lz77 { address: source, vram: *kind == LZ77_VRAM }),
                _ => {
                    let (length, fill) = match *kind {
                        CPU_FAST_SET => (((length & 0x1F_FFFF) + 7) / 8 * 32, length & (1 << 24) != 0),
                        CPU_SET => ((length & 0x1F_FFFF) * if length & (1 << 26) != 0 { 4 } else { 2 }, length & (1 << 24) != 0),
                        _ => (length & 0xFFFF, false),
                    };
                    (length, if fill { Source::Unknown } else if ctx.rom.is_data(source) { Source::Rom(source) } else { Source::Memory(source) })
                }
            };
            if length == 0 {
                return Ok(Some(written));
            }
            match source {
                Source::Memory(from) => {
                    let pieces = memory.read_partial(from, from + length);
                    memory.write(destination, destination + length, Source::Unknown, 0);
                    let mut at = from;
                    for span in pieces.iter().chain(std::iter::once(&Span { start: from + length, end: from + length, source: Source::Unknown, offset: 0 })) {
                        if span.start > at {
                            written.push(Span { start: destination + (at - from), end: destination + (span.start - from), source: Source::Unknown, offset: 0 });
                        }
                        at = at.max(span.end);
                    }
                    for span in pieces {
                        let piece = Span { start: destination + (span.start - from), end: destination + (span.end - from), ..span };
                        memory.write(piece.start, piece.end, piece.source, piece.offset);
                        written.push(piece);
                    }
                }
                other => {
                    memory.write(destination, destination + length, other, 0);
                    written.push(Span { start: destination, end: destination + length, source: other, offset: 0 });
                }
            }
        }
        Event::Loader { target, args } => {
            let values: Vec<Option<u32>> = args.iter().map(|value| globals.eval(value)).collect();
            let Some(writes) = loader(ctx, *target, &values, families)? else { return Ok(None) };
            for (destination, length, source) in writes {
                memory.write(destination, destination + length, source, 0);
                written.push(Span { start: destination, end: destination + length, source, offset: 0 });
            }
        }
        _ => {}
    }
    Ok(Some(written))
}

/// Call-site order is not execution order, so for each span a binding uses, take the innermost function on the sprite's
/// call chain whose calls write that span at all; every write there must put the binding's bytes there.
fn conflict(spans: &[Span], chain: &[u32], writes: &[(&[u32], Span)]) -> Option<String> {
    for span in spans {
        let overlapping: Vec<&(&[u32], Span)> = writes.iter().filter(|(_, write)| write.end > span.start && write.start < span.end && !(write.source == Source::Unknown && matches!(write.start >> 24, 0x02 | 0x03))).collect();
        let Some(depth) = (0..chain.len()).rev().find(|&depth| overlapping.iter().any(|(at, _)| at.starts_with(&chain[..depth]))) else { continue };
        for (at, write) in overlapping.iter().filter(|(at, _)| at.starts_with(&chain[..depth])) {
            let agrees = write.source == span.source && i64::from(write.offset) - i64::from(write.start) == i64::from(span.offset) - i64::from(span.start);
            if !agrees {
                let caller = if depth == 0 { "the entry point".to_string() } else { format!("the call at {}", hex(chain[depth - 1])) };
                return Some(format!("{}..{}: {caller} also writes {}..{} from {:?} (call {}); call-site order cannot choose", hex(span.start.max(write.start)), hex(span.end.min(write.end)), hex(write.start), hex(write.end), write.source, at.iter().map(|site| hex(*site)).collect::<Vec<_>>().join(">")));
            }
        }
    }
    None
}

type Rendered = Vec<(i32, i32, u32, u32, Vec<u8>)>;

/// The frames side by side, 2 pixels apart, as an indexed PNG.
fn sheet_png(frames: &Rendered, pram: &[u8]) -> Vec<u8> {
    let width: u32 = frames.iter().map(|frame| frame.2 + 2).sum::<u32>().max(1);
    let height = frames.iter().map(|frame| frame.3).max().unwrap_or(1).max(1);
    let mut sheet = vec![0u8; (width * height) as usize];
    let mut left = 0;
    for (_, _, frame_width, frame_height, pixels) in frames {
        for y in 0..*frame_height {
            for x in 0..*frame_width {
                sheet[(y * width + left + x) as usize] = pixels[(y * frame_width + x) as usize];
            }
        }
        left += frame_width + 2;
    }
    let colors: Vec<[u8; 3]> = (0..256).map(|index| crate::image::bgr555(le16(pram, index * 2))).collect();
    crate::image::indexed_png(width, height, &sheet, &colors, true)
}

struct Bound {
    spans: Vec<Span>,
    family: Option<usize>,
    /// Per choice: each frame's u16 width, u16 height and pixels, then the 512 OBJ palette bytes with unused entries 0.
    hashed: Vec<u8>,
    /// The first choice's frames side by side, as an indexed PNG.
    png: Vec<u8>,
}

fn families_in(spans: &[Span]) -> BTreeSet<usize> {
    spans.iter().filter_map(|span| match span.source {
        Source::Family { family, .. } => Some(family),
        _ => None,
    }).collect()
}

/// Spans with family sources replaced by choice `choice`'s sources.
fn choose(spans: &[Span], families: &[Family], choice: usize) -> Vec<Span> {
    spans.iter().map(|span| match span.source {
        Source::Family { family, slot } => Span { source: families[family].choices[choice].1[slot], ..*span },
        _ => *span,
    }).collect()
}

#[allow(clippy::too_many_arguments)]
fn bind(ctx: &Ctx, memory: &Memory, families: &[Family], frames: &[Vec<Piece>], tile: u32, palette: u32, tiles_needed: Vec<(u32, u32)>, site: &[String], new_sources: &mut Vec<String>) -> Result<Bound, String> {
    let tile_spans = resolve(memory, tiles_needed)?;
    let tile_families = families_in(&tile_spans);
    if tile_families.len() > 1 {
        return Err("tiles come from two indexed loaders".into());
    }
    let choices = tile_families.iter().next().map_or(1, |family| families[*family].choices.len());
    let mut renders = Vec::new();
    let mut used = BTreeSet::new();
    for choice in 0..choices {
        let mut vram = vec![0u8; OBJ_VRAM_BYTES as usize];
        fill(ctx, &choose(&tile_spans, families, choice), &mut vram, OBJ_VRAM, site, new_sources)?;
        let rendered = render(frames, tile, palette, &vram);
        used.extend(rendered.iter().flat_map(|frame| frame.4.iter().copied()).filter(|index| *index != 0).map(u32::from));
        renders.push(rendered);
    }
    let palette_spans = resolve(memory, merge(used.iter().map(|index| (OBJ_PALETTE + index * 2, OBJ_PALETTE + index * 2 + 2)).collect()))?;
    let all: Vec<Span> = tile_spans.iter().chain(&palette_spans).copied().collect();
    let all_families = families_in(&all);
    if all_families.len() > 1 {
        return Err("tiles and palette come from two indexed loaders".into());
    }
    let family = all_families.iter().next().copied();
    let choices = family.map_or(1, |family| families[family].choices.len());
    let mut hashed = Vec::new();
    let mut png = Vec::new();
    for choice in 0..choices {
        for (_, _, width, height, pixels) in &renders[choice.min(renders.len() - 1)] {
            hashed.extend((*width as u16).to_le_bytes());
            hashed.extend((*height as u16).to_le_bytes());
            hashed.extend(pixels);
        }
        let mut pram = vec![0u8; 0x200];
        fill(ctx, &choose(&palette_spans, families, choice), &mut pram, OBJ_PALETTE, site, new_sources)?;
        if choice == 0 {
            png = sheet_png(&renders[0], &pram);
        }
        hashed.extend(pram);
    }
    Ok(Bound { spans: all, family, hashed, png })
}

/// Ports of the indexed graphics loaders. Their writes for constant indices; for an unknown index, writes from a new
/// family with one choice per table entry the C can be given. `None` when the tile offset or palette bank is unknown.
fn loader(ctx: &Ctx, target: u32, args: &[Option<u32>], families: &mut Vec<Family>) -> R<Option<Vec<(u32, u32, Source)>>> {
    let portrait = matches!(target, LOAD_PILOT_PORTRAIT | QUEUE_PILOT_PORTRAIT);
    let queued = matches!(target, QUEUE_PILOT_PORTRAIT | QUEUE_ZOID_ICON);
    let (tile, bank) = if portrait { (args[3].map(|tile| tile & 0xFFFF), args[4].map(|bank| bank & 0xFFFF)) } else { (args[2].map(|tile| tile & 0xFFFF), args[3].map(|bank| bank & 0xFF)) };
    let (Some(tile), Some(bank)) = (tile, bank) else { return Ok(None) };
    let word = |address: u32| -> R<u32> { Ok(le32(ctx.rom.peek(address, 4)?, 0)) };
    let mut choices: Vec<(String, Vec<Source>)> = Vec::new();
    if portrait {
        let pilots: Vec<u32> = match args[0] {
            Some(pilot) => vec![pilot & 0xFFFF],
            None => (0..super::graphics_tables::next_root_count(ctx, super::graphics_tables::PILOT_PORTRAITS, 64)?).collect(),
        };
        let expressions: Vec<u32> = match args[1] {
            Some(expression) => vec![expression & 0xFF],
            None => (0..8).collect(),
        };
        let alternates: Vec<u32> = match args[2] {
            Some(index) => vec![index & 0xFF],
            None => (0..super::graphics_tables::next_root_count(ctx, super::graphics_tables::PILOT_ALTERNATE_PALETTES, 4)?).collect(),
        };
        for &pilot in &pilots {
            for &expression in &expressions {
                let record = super::graphics_tables::PILOT_PORTRAITS + pilot * 64 + expression * 8;
                let tiles = word(record)?;
                if tiles == 0 {
                    continue;
                }
                if pilot == super::graphics_tables::PILOT_WITH_ALTERNATE_PALETTES {
                    for &index in &alternates {
                        let palette = word(super::graphics_tables::PILOT_ALTERNATE_PALETTES + index * 4)?;
                        choices.push((format!("pilot {pilot}, expression {expression}, alternate palette {index}"), vec![Source::Lz77 { address: tiles, vram: !queued }, Source::Lz77 { address: palette, vram: false }]));
                    }
                } else {
                    choices.push((format!("pilot {pilot}, expression {expression}"), vec![Source::Lz77 { address: tiles, vram: !queued }, Source::Lz77 { address: word(record + 4)?, vram: false }]));
                }
            }
        }
    } else {
        let zoids: Vec<u32> = match args[0] {
            Some(zoid) => vec![zoid & 0xFF],
            None => (0..super::graphics_tables::next_root_count(ctx, super::graphics_tables::ZOID_ICON_TILES, 4)?).collect(),
        };
        let variants: Vec<u32> = match args[1] {
            Some(variant) => vec![variant & 0xFF],
            None => (0..8).collect(),
        };
        for &zoid in &zoids {
            let tiles = word(super::graphics_tables::ZOID_ICON_TILES + zoid * 4)?;
            for &variant in &variants {
                let palette = word(super::graphics_tables::ZOID_ICON_PALETTES + zoid * 32 + variant * 4)?;
                if tiles != 0 && palette != 0 {
                    choices.push((format!("zoid {zoid}, palette {variant}"), vec![Source::Lz77 { address: tiles, vram: !queued }, Source::Lz77 { address: palette, vram: false }]));
                }
            }
        }
    }
    let tiles_length = |source: &Source| -> R<u32> {
        let Source::Lz77 { address, .. } = source else { unreachable!() };
        Ok(match (queued, portrait) {
            (true, true) => PILOT_PORTRAIT_BYTES,
            (true, false) => ZOID_ICON_BYTES,
            _ => word(*address)? >> 8,
        })
    };
    let palette_length = |source: &Source| -> R<u32> {
        let Source::Lz77 { address, .. } = source else { unreachable!() };
        Ok(if queued { 0x20 } else { ((word(*address)? >> 8) + 31) / 32 * 32 })
    };
    let Some(first) = choices.first() else { return Err(format!("indexed loader 0x{target:08X}: no table entry for {args:?}")) };
    let (tiles_bytes, palette_bytes) = (tiles_length(&first.1[0])?, palette_length(&first.1[1])?);
    for (name, sources) in &choices {
        if tiles_length(&sources[0])? != tiles_bytes || palette_length(&sources[1])? != palette_bytes {
            return Err(format!("indexed loader 0x{target:08X}: {name} writes a different length than {}", first.0));
        }
    }
    let (tiles_at, palette_at) = (OBJ_VRAM + tile * 32, OBJ_PALETTE + bank * 32);
    if choices.len() == 1 {
        let sources = &choices[0].1;
        return Ok(Some(vec![(tiles_at, tiles_bytes, sources[0]), (palette_at, palette_bytes, sources[1])]));
    }
    let label = if portrait { "pilot portrait" } else { "zoid icon" };
    let family = match families.iter().position(|known| known.label == label && known.choices == choices) {
        Some(index) => index,
        None => {
            families.push(Family { label, choices });
            families.len() - 1
        }
    };
    Ok(Some(vec![(tiles_at, tiles_bytes, Source::Family { family, slot: 0 }), (palette_at, palette_bytes, Source::Family { family, slot: 1 })]))
}

fn hex(value: u32) -> String {
    format!("0x{value:08X}")
}

fn run(ctx: &Ctx) -> R<()> {
    let code = Code::new(ctx.rom)?;
    let entries = entry_points(&code)?;
    let mut walker = Walker { code: &code, ctx, memo: HashMap::new(), active: BTreeSet::new(), failures: BTreeMap::new() };
    let mut bound: BTreeMap<u32, Vec<Value>> = BTreeMap::new();
    let mut signatures: BTreeSet<(u32, String)> = BTreeSet::new();
    let mut unbound: BTreeMap<u32, Vec<Value>> = BTreeMap::new();
    let mut unresolved: BTreeMap<Vec<u32>, (&'static str, String)> = BTreeMap::new();
    let mut frame_cache: HashMap<u32, Vec<Vec<Piece>>> = HashMap::new();
    let mut new_sources: Vec<String> = Vec::new();
    let mut families: Vec<Family> = Vec::new();
    let mut sheets: BTreeMap<u32, Vec<Vec<u8>>> = BTreeMap::new();
    let mut templates: BTreeMap<&'static str, (Vec<Span>, usize, u32, u32, u32, u32, Vec<String>)> = BTreeMap::new();
    let mut leaves: BTreeMap<u32, (BTreeSet<u32>, BTreeSet<String>, BTreeSet<String>)> = BTreeMap::new();
    for &entry in &entries {
        let steps = walker.walk(entry, Default::default(), 0);
        let mut root_writes: Vec<(&[u32], Span)> = Vec::new();
        {
            let (mut memory, mut globals) = (Memory::default(), Globals::default());
            for step in steps.iter() {
                if let Some(written) = replay(ctx, &step.event, &mut globals, &mut memory, &mut families)? {
                    root_writes.extend(written.into_iter().map(|span| (step.chain.as_slice(), span)));
                }
            }
        }
        let mut memory = Memory::default();
        let mut globals = Globals::default();
        for step in steps.iter() {
            match &step.event {
                Event::Store { .. } | Event::Write { .. } | Event::Loader { .. } => {
                    if replay(ctx, &step.event, &mut globals, &mut memory, &mut families)?.is_none() {
                        unresolved.insert([vec![entry], step.chain.clone()].concat(), ("loader", String::new()));
                    }
                }
                Event::Unresolved { what, args } => {
                    let shown: Vec<String> = args.iter().map(|value| globals.eval(value).map_or("?".into(), hex)).collect();
                    unresolved.insert([vec![entry], step.chain.clone()].concat(), (what, shown.join(",")));
                }
                Event::Sprite { args, table } => {
                    let value = |index: usize| globals.eval(&args[index]);
                    let shown: Vec<String> = (0..ARGS).map(|index| value(index).map_or("?".into(), hex)).collect();
                    let leaf_site = *step.chain.last().unwrap();
                    if *table && value(7).map_or(false, |flags| flags & STREAMED != 0) {
                        continue;
                    }
                    let resolved = match (value(0), value(1), value(5), value(6), value(7)) {
                        (Some(frames), Some(animations), Some(tile), Some(palette), Some(flags)) if !table => Some((frames, animations, tile, palette, flags)),
                        (Some(source_table), Some(id), Some(tile), Some(palette), flags) if *table => {
                            let stride = ctx.data("sprite.resources", source_table).and_then(|data| data["stride"].as_u64());
                            let streamed = match (flags, stride) {
                                (Some(flags), _) => flags & STREAMED != 0,
                                (None, Some(stride)) => stride == 16,
                                _ => {
                                    leaves.entry(leaf_site).or_default().2.insert(shown.join(","));
                                    continue;
                                }
                            };
                            if streamed {
                                continue;
                            }
                            let entry = source_table + (id & 0xFFFF) * 8;
                            rom_word(ctx, entry).zip(rom_word(ctx, entry + 4)).map(|(frames, animations)| (frames, animations, tile, palette, 0))
                        }
                        _ => None,
                    };
                    let Some((frames, animations, tile, palette, flags)) = resolved else {
                        leaves.entry(leaf_site).or_default().2.insert(shown.join(","));
                        continue;
                    };
                    let (tile, palette) = (tile & 0xFFFF, palette & 0xFFFF);
                    let site = [vec![entry], step.chain.clone()].concat();
                    let site_text: Vec<String> = site.iter().map(|at| hex(*at)).collect();
                    if flags & STREAMED != 0 {
                        continue;
                    }
                    let leaf = leaves.entry(*step.chain.last().unwrap()).or_default();
                    let Some(table) = ctx.data("sprite.frame_table", frames) else {
                        leaf.1.insert(format!("{} not extracted", hex(frames)));
                        unbound.entry(frames).or_default().push(json!({ "site": site_text, "reason": "frame table not extracted" }));
                        continue;
                    };
                    let count = table["frames"].as_u64().unwrap_or(0) as u32;
                    if !frame_cache.contains_key(&frames) {
                        let mut list = Vec::new();
                        for index in 0..count {
                            list.push(pieces(ctx, le32(ctx.rom.peek(frames + index * 4, 4)?, 0))?);
                        }
                        frame_cache.insert(frames, list);
                    }
                    let frame_pieces = &frame_cache[&frames];
                    let mut tiles_needed: Vec<(u32, u32)> = Vec::new();
                    for piece in frame_pieces.iter().flatten() {
                        let units = piece.width * piece.height / 64 * if piece.color256 { 2 } else { 1 };
                        let start = OBJ_VRAM + ((tile + piece.tile) * 32 & (OBJ_VRAM_BYTES - 1));
                        tiles_needed.push((start, start + units * 32));
                    }
                    let resolved = bind(ctx, &memory, &families, frame_pieces, tile, palette & 15, merge(tiles_needed), &site_text, &mut new_sources);
                    let bound_sprite = match resolved {
                        Ok(found) => found,
                        Err(missing) => {
                            leaves.get_mut(step.chain.last().unwrap()).unwrap().1.insert(format!("{} tile {tile:#X} palette {palette}: {missing}", hex(frames)));
                            unbound.entry(frames).or_default().push(json!({ "site": site_text, "tile": tile, "palette": palette, "reason": missing }));
                            continue;
                        }
                    };
                    if let Some(conflict) = conflict(&bound_sprite.spans, &step.chain, &root_writes) {
                        leaves.get_mut(step.chain.last().unwrap()).unwrap().1.insert(format!("{} tile {tile:#X} palette {palette}: {conflict}", hex(frames)));
                        unbound.entry(frames).or_default().push(json!({ "site": site_text, "tile": tile, "palette": palette, "reason": conflict }));
                        continue;
                    }
                    let recipe: Vec<Value> = bound_sprite.spans.iter().map(|span| json!([span.start, span.end, source_json(span), span.offset])).collect();
                    leaves.get_mut(step.chain.last().unwrap()).unwrap().0.insert(frames);
                    let sha1 = crate::sha1_hex(&bound_sprite.hashed);
                    if signatures.insert((frames, format!("{tile}:{palette}:{sha1}"))) {
                        let mut view = json!({
                            "t": "sprite", "frames": frames, "count": frame_pieces.len(), "animations": animations,
                            "animation_count": ctx.data("sprite.animation_table", animations).and_then(|data| data["animations"].as_u64()).unwrap_or(0),
                            "tile": tile, "palette": palette & 15,
                            "memory": recipe, "sha1": sha1, "site": site_text,
                        });
                        if let Some(family_index) = bound_sprite.family {
                            let label = families[family_index].label;
                            templates.entry(label).or_insert_with(|| (bound_sprite.spans.clone(), family_index, frames, animations, tile, palette & 15, site_text.clone()));
                            let family = &families[family_index];
                            view["family"] = json!({
                                "label": family.label,
                                "choices": family.choices.iter().map(|(name, sources)| json!([name, sources.iter().map(|source| source_json(&Span { start: 0, end: 0, source: *source, offset: 0 })).collect::<Vec<_>>()])).collect::<Vec<_>>(),
                            });
                        }
                        bound.entry(frames).or_default().push(view);
                        sheets.entry(frames).or_default().push(bound_sprite.png.clone());
                    }
                }
            }
        }
    }
    for (table, data) in ctx.data_of("sprite.resources") {
        if data["stride"] != 16 {
            continue;
        }
        for index in 0..data["resources"].as_array().map_or(0, Vec::len) as u32 {
            let entry = ctx.rom.peek(table + index * 16, 16)?;
            let (frames, animations, graphics, palette) = (le32(entry, 0), le32(entry, 4), le32(entry, 8), le32(entry, 12));
            if frames == 0 {
                continue;
            }
            let Some(table_data) = ctx.data("sprite.frame_table", frames) else { continue };
            if !frame_cache.contains_key(&frames) {
                let mut list = Vec::new();
                for frame in 0..table_data["frames"].as_u64().unwrap_or(0) as u32 {
                    list.push(pieces(ctx, le32(ctx.rom.peek(frames + frame * 4, 4)?, 0))?);
                }
                frame_cache.insert(frames, list);
            }
            let frame_pieces = &frame_cache[&frames];
            let end = frame_pieces.iter().flatten().map(|piece| (piece.tile + piece.width * piece.height / 64 * if piece.color256 { 2 } else { 1 }) * 32).max().unwrap_or(0);
            if end == 0 {
                continue;
            }
            let tiles = ctx.rom.peek(graphics, end)?;
            let rendered = render(frame_pieces, 0, 0, tiles);
            let mut pram = vec![0u8; 0x200];
            pram[..32].copy_from_slice(ctx.rom.peek(palette, 32)?);
            let mut hashed = Vec::new();
            for (_, _, width, height, pixels) in &rendered {
                hashed.extend((*width as u16).to_le_bytes());
                hashed.extend((*height as u16).to_le_bytes());
                hashed.extend(pixels);
            }
            hashed.extend(&pram);
            let sha1 = crate::sha1_hex(&hashed);
            if !signatures.insert((frames, format!("streamed:{sha1}"))) {
                continue;
            }
            bound.entry(frames).or_default().push(json!({
                "t": "sprite", "frames": frames, "count": frame_pieces.len(), "animations": animations,
                "animation_count": ctx.data("sprite.animation_table", animations).and_then(|data| data["animations"].as_u64()).unwrap_or(0),
                "tile": 0, "palette": 0, "streamed": [graphics, graphics + end, palette], "memory": [], "sha1": sha1,
                "site": [format!("{}[{index}]", hex(table))],
            }));
            sheets.entry(frames).or_default().push(sheet_png(&rendered, &pram));
        }
    }
    let mut report = new_sources.clone();
    for (frames, views) in &bound {
        let (id, _) = ctx.item("sprite.frame_table", *frames, super::sprites::SPRITES, Vec::new());
        for (index, view) in views.iter().enumerate() {
            ctx.view(id, view.clone());
            ctx.file(id, &format!(".sprite{index}.png"), &sheets[frames][index])?;
        }
    }
    let mut choice_views: Vec<(u32, Value, Vec<u8>)> = Vec::new();
    for (label, (spans, family_index, frames, animations, tile, palette, site_text)) in &templates {
        let target = if *label == "pilot portrait" { LOAD_PILOT_PORTRAIT } else { LOAD_ZOID_ICON };
        let mut args = vec![None; ARGS];
        let (tile_arg, bank_arg) = if target == LOAD_PILOT_PORTRAIT { (3, 4) } else { (2, 3) };
        args[tile_arg] = Some(*tile);
        args[bank_arg] = Some(*palette);
        let Some(writes) = loader(ctx, target, &args, &mut families)? else { continue };
        let Some(Source::Family { family: all, .. }) = writes.first().map(|write| write.2) else { continue };
        let template: Vec<Span> = spans.iter().map(|span| match span.source {
            Source::Family { slot, family } if family == *family_index => Span { source: Source::Family { family: all, slot }, ..*span },
            _ => *span,
        }).collect();
        let frame_pieces = &frame_cache[frames];
        let mut seen = BTreeSet::new();
        for (choice, (name, sources)) in families[all].choices.iter().enumerate() {
            let Source::Lz77 { address: tiles_address, .. } = sources[0] else { continue };
            if !seen.insert((tiles_address, sources[1])) {
                continue;
            }
            let chosen = choose(&template, &families, choice);
            let (mut vram, mut pram) = (vec![0u8; OBJ_VRAM_BYTES as usize], vec![0u8; 0x200]);
            let (tile_spans, palette_spans): (Vec<Span>, Vec<Span>) = chosen.iter().partition(|span| span.start >= OBJ_VRAM);
            fill(ctx, &tile_spans, &mut vram, OBJ_VRAM, site_text, &mut new_sources)?;
            fill(ctx, &palette_spans, &mut pram, OBJ_PALETTE, site_text, &mut new_sources)?;
            let rendered = render(frame_pieces, *tile, *palette, &vram);
            let mut hashed = Vec::new();
            for (_, _, width, height, pixels) in &rendered {
                hashed.extend((*width as u16).to_le_bytes());
                hashed.extend((*height as u16).to_le_bytes());
                hashed.extend(pixels);
            }
            hashed.extend(&pram);
            choice_views.push((tiles_address, json!({
                "t": "sprite", "frames": frames, "count": frame_pieces.len(), "animations": animations,
                "animation_count": ctx.data("sprite.animation_table", *animations).and_then(|data| data["animations"].as_u64()).unwrap_or(0),
                "tile": tile, "palette": palette, "label": name,
                "memory": chosen.iter().map(|span| json!([span.start, span.end, source_json(span), span.offset])).collect::<Vec<_>>(),
                "sha1": crate::sha1_hex(&hashed), "site": site_text,
            }), sheet_png(&rendered, &pram)));
        }
    }
    for (tiles, view, png) in &choice_views {
        let (id, _) = ctx.item("lz77", *tiles, BINDINGS, Vec::new());
        let index = ctx.view_count(id);
        ctx.view(id, view.clone());
        ctx.file(id, &format!(".sprite{index}.png"), png)?;
    }
    let unbound_tables: BTreeSet<u32> = unbound.keys().filter(|frames| !bound.contains_key(frames)).copied().collect();
    for frames in &unbound_tables {
        let (id, _) = ctx.item("sprite.frame_table", *frames, super::sprites::SPRITES, Vec::new());
        let mut reasons: Vec<(String, String)> = unbound[frames].iter().map(|entry| (entry["site"].as_array().map(|site| site.iter().filter_map(|at| at.as_str()).collect::<Vec<_>>().join(" > ")).unwrap_or_default(), entry["reason"].as_str().unwrap_or("").to_string())).collect();
        reasons.sort();
        reasons.dedup_by(|a, b| a.1 == b.1);
        reasons.truncate(8);
        ctx.view(id, json!({ "t": "unbound", "reasons": reasons }));
    }
    report.push(format!("sprite bindings: {} frame tables bound ({} bindings), {} frame tables only unbound, {} unresolved call sites, {} entry points, {} functions not analyzed",
        bound.len(), bound.values().map(Vec::len).sum::<usize>(), unbound_tables.len(), unresolved.len(), entries.len(), walker.failures.len()));
    for frames in &unbound_tables {
        report.push(format!("  unbound {} {}", hex(*frames), unbound[frames][0]));
    }
    let all_tables: BTreeSet<u32> = ctx.data_of("sprite.frame_table").into_iter().map(|(address, _)| address).collect();
    let never: Vec<String> = all_tables.iter().filter(|frames| !bound.contains_key(frames) && !unbound.contains_key(frames)).map(|frames| hex(*frames)).collect();
    report.push(format!("  frame tables with no CreateSprite site found: {} {}", never.len(), never.join(" ")));
    let (mut ok, mut partial, mut never) = (0, 0, 0);
    for (site, (bound_tables, missing, unknown)) in &leaves {
        match (bound_tables.is_empty(), missing.is_empty() && unknown.is_empty()) {
            (false, true) => ok += 1,
            (false, false) => partial += 1,
            _ => never += 1,
        }
        report.push(format!("  site {} bound {} | missing {} | unknown args {}", hex(*site), bound_tables.len(), missing.iter().take(3).cloned().collect::<Vec<_>>().join("; "), unknown.iter().take(2).cloned().collect::<Vec<_>>().join(" ; ")));
    }
    report.insert(0, format!("sites: {} bound in every context, {} bound in some, {} never bound", ok, partial, never));
    std::fs::write(ctx.out_dir().join("sprite_bindings.txt"), report.join("\n") + "\n").map_err(|error| error.to_string())?;
    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn memory_overwrites_split_older_spans() {
        let mut memory = Memory::default();
        memory.write(0x100, 0x200, Source::Rom(0x0800_1000), 0);
        memory.write(0x140, 0x150, Source::Unknown, 0);
        assert!(memory.read(0x100, 0x200).is_none());
        let tail = memory.read(0x150, 0x160).unwrap();
        assert_eq!((tail[0].start, tail[0].offset), (0x150, 0x50));
        assert_eq!(memory.read_partial(0x130, 0x160).len(), 2);
    }

    #[test]
    fn a_disagreeing_write_inside_the_caller_is_a_conflict() {
        let span = Span { start: 0x0601_0000, end: 0x0601_0020, source: Source::Lz77 { address: 0x0810_0000, vram: true }, offset: 0 };
        let other = Span { source: Source::Lz77 { address: 0x0811_0000, vram: true }, ..span };
        let chain = [0x10, 0x20];
        assert!(conflict(&[span], &chain, &[(&[0x10, 0x18], other)]).is_some());
        assert!(conflict(&[span], &chain, &[(&[0x10, 0x18], span)]).is_none());
        assert!(conflict(&[span], &chain, &[(&[0x10, 0x18], span), (&[0x30], other)]).is_none());
    }
}
