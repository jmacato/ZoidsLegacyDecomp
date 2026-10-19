//! Ports of the decomp code that reads ROM data. Each port runs the ROM data from roots the C references.

pub mod audio_roots;
pub mod battle_animation;
pub mod battle_effects;
pub mod battle_popups;
pub mod battle_scene_objects;
pub mod battle_streak_particles;
pub mod bios;
pub mod code_data;
pub mod copies;
pub mod credits;
pub mod databases;
pub mod event_tables;
pub mod event_script;
pub mod event_sprites;
pub mod field_actors;
pub mod field_map;
pub mod font;
pub mod graphics;
pub mod graphics_tables;
pub mod link;
pub mod menu_script;
pub mod music;
pub mod names;
pub mod sprite_bindings;
pub mod script_battles;
pub mod song_uses;
pub mod sprites;
pub mod tables;
pub mod text;
pub mod ui_tables;
pub mod unreachable;

use crate::basis::Basis;
use crate::rom::{Rom, R};
use crate::roots::strip_casts;
use crate::run::Ctx;

pub struct Port {
    pub name: &'static str,
    pub bases: &'static [Basis],
    pub run: fn(&Ctx) -> R<()>,
}

pub const ALL: &[Port] = &[copies::PORT, text::PORT, font::PORT, credits::PORT, menu_script::PORT, field_map::PORT, event_script::PORT, graphics::PORT, sprites::PORT, graphics_tables::PORT, music::PORT, tables::PORT, databases::PORT, battle_animation::PORT, battle_popups::PORT, battle_effects::PORT, audio_roots::PORT, event_tables::PORT, field_actors::PORT, link::PORT, ui_tables::PORT, event_sprites::PORT, battle_scene_objects::PORT, battle_streak_particles::PORT, code_data::PORT, unreachable::PORT, sprite_bindings::PORT, song_uses::PORT, script_battles::PORT];

/// An integer literal argument (`0x20`, `14`, `(u16)0x40`); `None` for any expression.
pub fn literal(text: &str) -> Option<u32> {
    let text = strip_casts(text).trim_end_matches(|c| c == 'u' || c == 'U' || c == 'l' || c == 'L');
    if let Some(hex) = text.strip_prefix("0x").or_else(|| text.strip_prefix("0X")) {
        return u32::from_str_radix(hex, 16).ok();
    }
    text.parse::<u32>().ok()
}

/// A literal, `&D_XXXXXXXX`, or a symbols.ld name, as an address.
pub fn address_of(text: &str, roots: &crate::roots::Roots) -> Option<u32> {
    if let Some(value) = literal(text) {
        return Some(value);
    }
    let name = strip_casts(text).trim_start_matches('&').trim();
    if let Some(address) = roots.symbols.get(name) {
        return Some(*address);
    }
    let hex = name.strip_prefix("D_")?;
    (hex.len() == 8).then(|| u32::from_str_radix(hex, 16).ok()).flatten()
}

/// `name` as an address at a call site: `address_of`, or the nearest `name = <address>;` on the lines before it.
pub fn resolve_at(text: &str, reference: &crate::roots::Reference, roots: &crate::roots::Roots) -> Option<u32> {
    if let Some(address) = address_of(text, roots) {
        return Some(address);
    }
    let name = text.trim();
    if name.is_empty() || !name.bytes().all(|byte| byte.is_ascii_alphanumeric() || byte == b'_') {
        return None;
    }
    let source = std::fs::read_to_string(crate::repo_root().join(&reference.file)).ok()?;
    let lines: Vec<&str> = source.lines().take(reference.line as usize).collect();
    for line in lines.iter().rev() {
        let line = line.trim();
        if let Some(rest) = line.strip_prefix(name).map(str::trim_start).and_then(|rest| rest.strip_prefix('=')) {
            if rest.starts_with('=') {
                continue;
            }
            return address_of(rest.trim().trim_end_matches(';'), roots);
        }
    }
    None
}

/// Memory area a GBA address falls in.
pub fn area(address: u32) -> &'static str {
    match address >> 24 {
        0x02 => "ewram",
        0x03 => "iwram",
        0x04 => "io",
        0x05 => "palette",
        0x06 => "vram",
        0x07 => "oam",
        0x08..=0x09 => "rom",
        _ => "unknown",
    }
}

/// Claim `length` bytes at `address` under `format`, skipping parts that are matched code. Returns the code overlaps.
pub fn claim_outside_code(rom: &Rom, address: u32, length: u32, format: &str, item: usize) -> R<Vec<(u32, u32)>> {
    let mut overlaps = Vec::new();
    let mut start = address;
    let end = address + length;
    while start < end {
        if rom.is_data(start) {
            let mut stop = start;
            while stop < end && rom.is_data(stop) {
                stop += 1;
            }
            rom.claim(start, stop - start, format, item)?;
            start = stop;
        } else {
            let mut stop = start;
            while stop < end && !rom.is_data(stop) {
                stop += 1;
            }
            overlaps.push((start, stop));
            start = stop;
        }
    }
    Ok(overlaps)
}
