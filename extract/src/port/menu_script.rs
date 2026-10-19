//! RunMenuScript (0x08098BB4).

use serde_json::{json, Value};

use super::text::{parse_list, parse_window, FORMAT as TEXT};
use super::Port;
use crate::basis::Basis;
use crate::rom::R;
use crate::run::Ctx;

pub const MENU_SCRIPT: Basis = Basis::C(&[
    ("src/ui/run_menu_script.c", "2cfb02f8be3d3b225ceb631e8fd18bbfe81cbca2"),
    ("src/ui/menu_script.h", "65aa843d8d8bbeedb7243cac0cf6ca75fc589463"),
    ("src/ui/open_window.c", "346e09eb518584f83a404a3a655a013297892e3b"),
    ("src/ui/window.h", "c299d1e84300353c8f991978a0c2761133a5e42c"),
    ("src/ui/draw_window_text.c", "e61d2cdddb1782410db0393ca1ea434d4defdb93"),
]);

pub const PORT: Port = Port { name: "menu_script", bases: &[MENU_SCRIPT], run };

const RUN_MENU_SCRIPT: u32 = 0x0809_8BB4;
const FORMAT: &str = "menu_script";
const NAMES: [&str; 14] = [
    "END", "OPEN_WINDOW", "CLEAR_WINDOW", "CLOSE_WINDOW", "REFRESH", "PRINT_TEXT", "PRINT_BUFFER", "SELECT", "YES_NO", "PRINT_TITLE",
    "CLEAR_TITLE", "SET_FRAME_STYLE", "WAIT_CONFIRM", "CLEAR_RECT",
];
/// Operand bytes after the opcode; PRINT_TEXT and PRINT_TITLE also take NUL-terminated text after their window byte.
pub const OPERANDS: [u32; 14] = [0, 6, 1, 1, 0, 1, 1, 2, 1, 1, 1, 2, 0, 3];
pub const WINDOW_FLAG_TEXT_LIST: u32 = 0x80;

/// PRINT_TEXT on a window the script did not open: the window's flags come from code outside the script,
/// so both parsers run without claiming and must stop at the same byte.
pub fn either_grammar(ctx: &Ctx, address: u32) -> R<(&'static str, u32)> {
    let mut window = ctx.rom.dry_cursor(address);
    let mut list = ctx.rom.dry_cursor(address);
    let as_list = parse_list(&mut list);
    match parse_window(&mut window) {
        Ok(_) if as_list.is_ok() && window.address == list.address => Ok(("either", window.address)),
        Ok(_) => Err(format!("menu text at 0x{address:08X}: DrawWindowText and the list parser stop at different bytes")),
        Err(_) if as_list.is_ok() => Ok(("list", list.address)),
        Err(error) => Err(error),
    }
}

pub fn menu_script(ctx: &Ctx, address: u32, reached: Vec<String>) -> R<usize> {
    let (id, new) = ctx.item("menu_script", address, MENU_SCRIPT, reached);
    if !new {
        return Ok(id);
    }
    let mut list_window: [Option<bool>; 256] = [None; 256];
    let mut ops: Vec<Value> = Vec::new();
    let mut cursor = ctx.rom.cursor(address, FORMAT, id);
    loop {
        let at = cursor.address;
        let op = cursor.u8()?;
        if op > 13 {
            return Err(format!("menu script 0x{address:08X}: opcode 0x{op:02X} at 0x{at:08X} does not advance the cursor"));
        }
        let args: Vec<u8> = cursor.bytes(OPERANDS[op as usize])?.to_vec();
        let mut entry = json!({ "at": format!("0x{at:08X}"), "op": NAMES[op as usize], "args": args });
        match op {
            0 => {
                ops.push(entry);
                break;
            }
            1 => list_window[args[0] as usize] = Some((u32::from(args[5]) * 0x10) & WINDOW_FLAG_TEXT_LIST != 0),
            3 => list_window[args[0] as usize] = None,
            5 | 9 => {
                let mut text = cursor.with_format(TEXT);
                let grammar = if op == 9 {
                    "window"
                } else {
                    match list_window[args[0] as usize] {
                        Some(true) => "list",
                        Some(false) => "window",
                        None => either_grammar(ctx, text.address)?.0,
                    }
                };
                let rendered = if grammar == "list" { parse_list(&mut text)? } else { parse_window(&mut text)? };
                cursor.address = text.address;
                entry["text"] = json!(rendered);
                entry["grammar"] = json!(grammar);
            }
            _ => {}
        }
        ops.push(entry);
    }
    ctx.count(id, "terminator");
    ctx.set(id, json!({ "ops": ops }));
    Ok(id)
}

fn run(ctx: &Ctx) -> R<()> {
    for reference in ctx.roots.calls(RUN_MENU_SCRIPT, 0) {
        if ctx.rom.is_data(reference.address) {
            menu_script(ctx, reference.address, vec![reference.location()])?;
        }
    }
    Ok(())
}
