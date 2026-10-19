//! RunCredits: the stream at 0x08029043.

use serde_json::json;

use super::text::sjis;
use super::Port;
use crate::basis::Basis;
use crate::rom::R;
use crate::run::Ctx;

const CREDITS: Basis = Basis::C(&[("src/game/modes/run_credits.c", "4c3d1b42812f438e577af40f52e6e0419e3d659e")]);

pub const PORT: Port = Port { name: "credits", bases: &[CREDITS], run };

const STREAM: u32 = 0x0802_9043;

/// At each line boundary: 0 ends the stream, 0x0A is an empty line. Otherwise glyphs until 0 or 0x0A;
/// a glyph is two bytes, and a leading 1 first sets the palette from the next byte.
fn run(ctx: &Ctx) -> R<()> {
    let reached = ctx.roots.require(STREAM)?;
    let (id, _) = ctx.item("credits", STREAM, CREDITS, reached);
    let mut cursor = ctx.rom.cursor(STREAM, "credits", id);
    let mut lines = Vec::new();
    loop {
        let command = cursor.u8()?;
        if command == 0 {
            break;
        }
        if command == 0x0A {
            lines.push(json!({ "text": "" }));
            continue;
        }
        cursor.address -= 1;
        let mut text = String::new();
        let mut palettes = Vec::new();
        loop {
            if cursor.u8()? == 1 {
                let palette = cursor.u8()?;
                palettes.push(palette);
                text.push_str(&format!("{{palette:{palette}}}"));
            } else {
                cursor.address -= 1;
            }
            let glyph = cursor.bytes(2)?;
            text.push_str(&sjis(u16::from_be_bytes([glyph[0], glyph[1]])));
            match cursor.peek_u8()? {
                0 => {
                    lines.push(json!({ "text": text }));
                    cursor.u8()?;
                    ctx.count(id, "terminator");
                    ctx.view(id, json!({ "t": "text", "g": "credits", "end": cursor.address }));
                    ctx.set(id, json!({ "lines": lines }));
                    return Ok(());
                }
                0x0A => {
                    cursor.u8()?;
                    break;
                }
                _ => {}
            }
        }
        lines.push(json!({ "text": text }));
    }
    ctx.count(id, "terminator");
    ctx.view(id, json!({ "t": "text", "g": "credits", "end": cursor.address }));
    ctx.set(id, json!({ "lines": lines }));
    Ok(())
}
