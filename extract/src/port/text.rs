//! Text read by DrawWindowText, AppendWindowTextItem, CopyString and AppendString.

use serde_json::json;

use super::Port;
use crate::basis::Basis;
use crate::rom::{Cursor, R};
use crate::run::Ctx;

pub const WINDOW_TEXT: Basis = Basis::C(&[
    ("src/ui/draw_window_text.c", "e61d2cdddb1782410db0393ca1ea434d4defdb93"),
    ("src/ui/window.h", "c299d1e84300353c8f991978a0c2761133a5e42c"),
    ("src/ui/print_window_text.c", "aeb349a9698dd31771fe2da00219265731c8857e"),
    ("src/ui/print_window_text_at.c", "77308e9d892ca00b714cfef215809eadcf970783"),
]);
pub const TEXT_ITEM: Basis = Basis::C(&[("src/ui/append_window_text_item.c", "88c2fa8904aae291a19ca693f9bd5f6e49f86e4e")]);
pub const STRING: Basis = Basis::C(&[
    ("src/runtime/copy_string.c", "c4d0513f9c0b8bb1147f511ecf77c72f84936c40"),
    ("src/engine/append_string.c", "6e8c5d1156f6a69c8c74b04a81c02e85b7fa82e9"),
]);

pub const PORT: Port = Port { name: "text", bases: &[WINDOW_TEXT, TEXT_ITEM, STRING], run };

const DRAW_WINDOW_TEXT: u32 = 0x0809_7DA8;
const PRINT_WINDOW_TEXT_AT: u32 = 0x0809_81F0;
const PRINT_WINDOW_TEXT: u32 = 0x0809_8248;
const APPEND_WINDOW_TEXT_ITEM: u32 = 0x0809_88C8;
const COPY_STRING: u32 = 0x080E_D128;
const APPEND_STRING: u32 = 0x0809_9F5C;

pub const FORMAT: &str = "text";

/// Display form of a two-byte Shift-JIS code. Only the full-width space, digits, letters and common marks are mapped.
pub fn sjis(code: u16) -> String {
    let mapped = match code {
        0x8140 => Some('\u{3000}'),
        0x824F..=0x8258 => char::from_u32(0xFF10 + u32::from(code - 0x824F)),
        0x8260..=0x8279 => char::from_u32(0xFF21 + u32::from(code - 0x8260)),
        0x8281..=0x829A => char::from_u32(0xFF41 + u32::from(code - 0x8281)),
        0x8141 => Some('、'),
        0x8142 => Some('。'),
        0x8143 => Some('，'),
        0x8144 => Some('．'),
        0x8146 => Some('：'),
        0x8147 => Some('；'),
        0x8148 => Some('？'),
        0x8149 => Some('！'),
        0x815B => Some('ー'),
        0x815E => Some('／'),
        0x8165 => Some('‘'),
        0x8166 => Some('’'),
        0x8167 => Some('“'),
        0x8168 => Some('”'),
        0x8169 => Some('（'),
        0x816A => Some('）'),
        0x817B => Some('＋'),
        0x817C => Some('－'),
        0x8181 => Some('＝'),
        0x8193 => Some('％'),
        0x8195 => Some('＆'),
        0x8196 => Some('＊'),
        _ => None,
    };
    mapped.map_or_else(|| format!("{{sjis:{code:04X}}}"), |c| c.to_string())
}

/// Display of bytes a grammar treats one at a time: a lead byte 0x80-0x9F is shown paired with the next byte.
fn display(bytes: &[u8]) -> String {
    let mut out = String::new();
    let mut index = 0;
    while index < bytes.len() {
        let byte = bytes[index];
        if (0x80..=0x9F).contains(&byte) && index + 1 < bytes.len() {
            out.push_str(&sjis(u16::from_be_bytes([byte, bytes[index + 1]])));
            index += 2;
            continue;
        }
        match byte {
            0x0A => out.push('\n'),
            _ => glyph(&mut out, byte),
        }
        index += 1;
    }
    out
}

fn glyph(out: &mut String, byte: u8) {
    match byte {
        b'{' | b'}' | b'\\' => out.push_str(&format!("{{{byte:02X}}}")),
        0x20..=0x7E => out.push(byte as char),
        _ => out.push_str(&format!("{{{byte:02X}}}")),
    }
}

/// DrawWindowText: 0 ends; 1 color; 2 column, row; 3 player name; 0x0A newline; 0x80-0x9F two-byte glyph.
/// Any other byte below 0x20 does not advance the cursor, so the C never returns.
pub fn parse_window(cursor: &mut Cursor) -> R<String> {
    let start = cursor.address;
    let mut text = String::new();
    loop {
        let at = cursor.address;
        match cursor.u8()? {
            0 => return Ok(text),
            1 => text.push_str(&format!("{{color:{}}}", cursor.u8()?)),
            2 => {
                let column = cursor.u8()?;
                let row = cursor.u8()?;
                text.push_str(&format!("{{pos:{column},{row}}}"));
            }
            3 => text.push_str("{name}"),
            0x0A => text.push('\n'),
            byte @ 0x04..=0x1F => {
                return Err(format!("DrawWindowText at 0x{start:08X}: byte 0x{byte:02X} at 0x{at:08X} never advances the cursor"));
            }
            byte @ 0x80..=0x9F => text.push_str(&sjis(u16::from_be_bytes([byte, cursor.u8()?]))),
            byte => glyph(&mut text, byte),
        }
    }
}

/// The text-list parser in RunMenuScript (window flag 0x80): bytes one at a time until 0; 1 takes one operand, 2 takes two.
pub fn parse_list(cursor: &mut Cursor) -> R<String> {
    let mut text = String::new();
    let mut run = Vec::new();
    loop {
        match cursor.u8()? {
            0 => break,
            1 => {
                text.push_str(&display(&run));
                run.clear();
                text.push_str(&format!("{{color:{}}}", cursor.u8()?));
            }
            2 => {
                text.push_str(&display(&run));
                run.clear();
                let column = cursor.u8()?;
                let row = cursor.u8()?;
                text.push_str(&format!("{{pos:{column},{row}}}"));
            }
            3 => {
                text.push_str(&display(&run));
                run.clear();
                text.push_str("{name}");
            }
            byte => run.push(byte),
        }
    }
    text.push_str(&display(&run));
    Ok(text)
}

/// AppendWindowTextItem: bytes until 0; only 1 takes an operand byte.
pub fn parse_item(cursor: &mut Cursor) -> R<String> {
    let mut text = String::new();
    let mut run = Vec::new();
    loop {
        match cursor.u8()? {
            0 => break,
            1 => {
                text.push_str(&display(&run));
                run.clear();
                text.push_str(&format!("{{color:{}}}", cursor.u8()?));
            }
            byte => run.push(byte),
        }
    }
    text.push_str(&display(&run));
    Ok(text)
}

/// CopyString / AppendString: bytes up to and including the first 0.
pub fn parse_plain(cursor: &mut Cursor) -> R<String> {
    let mut run = Vec::new();
    loop {
        match cursor.u8()? {
            0 => break,
            byte => run.push(byte),
        }
    }
    Ok(display(&run))
}

fn text_item_of(ctx: &Ctx, kind: &str, basis: Basis, parse: fn(&mut Cursor) -> R<String>, address: u32, reached: Vec<String>) -> R<usize> {
    let (id, new) = ctx.item(kind, address, basis, reached);
    if new {
        let mut cursor = ctx.rom.cursor(address, FORMAT, id);
        let text = parse(&mut cursor)?;
        let grammar = match kind {
            "text.window" => "window",
            "text.item" => "item",
            _ => "plain",
        };
        ctx.view(id, json!({ "t": "text", "g": grammar, "end": cursor.address }));
        ctx.set(id, json!({ "text": text }));
    }
    Ok(id)
}

pub fn window_text(ctx: &Ctx, address: u32, reached: Vec<String>) -> R<usize> {
    text_item_of(ctx, "text.window", WINDOW_TEXT, parse_window, address, reached)
}

pub fn text_item(ctx: &Ctx, address: u32, reached: Vec<String>) -> R<usize> {
    text_item_of(ctx, "text.item", TEXT_ITEM, parse_item, address, reached)
}

pub fn string(ctx: &Ctx, address: u32, reached: Vec<String>) -> R<usize> {
    text_item_of(ctx, "text.string", STRING, parse_plain, address, reached)
}

fn run(ctx: &Ctx) -> R<()> {
    let sites: [(u32, usize, fn(&Ctx, u32, Vec<String>) -> R<usize>); 6] = [
        (PRINT_WINDOW_TEXT, 0, window_text),
        (PRINT_WINDOW_TEXT_AT, 0, window_text),
        (DRAW_WINDOW_TEXT, 1, window_text),
        (APPEND_WINDOW_TEXT_ITEM, 1, text_item),
        (COPY_STRING, 1, string),
        (APPEND_STRING, 1, string),
    ];
    for (callee, arg, decode) in sites {
        for reference in ctx.roots.calls(callee, arg) {
            if ctx.rom.is_data(reference.address) {
                decode(ctx, reference.address, vec![reference.location()])?;
            }
        }
    }
    Ok(())
}
