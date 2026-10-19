//! Link transfer tags given to BeginLinkSend / BeginLinkReceive, and RunLinkBattle's battle-field tables.
//! PollLinkSend copies LINK_PACKET_PAYLOAD_BYTES of the send tag into the tag packet; PollLinkReceive compares
//! the receive tag with the incoming packet up to the tag's NUL, at most LINK_PACKET_PAYLOAD_BYTES bytes.

use std::collections::{BTreeMap, BTreeSet};

use serde_json::json;

use super::{claim_outside_code, text, Port};
use crate::basis::Basis;
use crate::rom::{le32, R, NEUTRAL};
use crate::roots::Reference;
use crate::run::Ctx;

const TAGS: Basis = Basis::C(&[
    ("src/engine/begin_link_send.c", "7951c6e62f68f1c2610097b8fd097068380b9155"),
    ("src/engine/begin_link_receive.c", "a02bd747b086614096e668022529c603499dc1c9"),
    ("src/engine/poll_link_send.c", "97e8fe91da9ac7615a4ad5f4ce925a9ad6bf75ca"),
    ("src/engine/poll_link_receive.c", "8f98578615109a70e3d4cb93a58a60b8a0d0e34d"),
    ("src/engine/link_transfer.h", "80ce1576fc1066b437c14e4b308a9ef8dbec3862"),
]);
const FIELDS: Basis = Basis::C(&[
    ("src/game/modes/run_link_battle.c", "abc434014ed1ffbba222f329c291b09932d76133"),
    ("src/ui/run_menu_script.c", "2cfb02f8be3d3b225ceb631e8fd18bbfe81cbca2"),
    ("src/ui/open_window.c", "346e09eb518584f83a404a3a655a013297892e3b"),
    ("src/ui/menu_script.h", "65aa843d8d8bbeedb7243cac0cf6ca75fc589463"),
    ("src/ui/print_window_text.c", "aeb349a9698dd31771fe2da00219265731c8857e"),
]);

pub const PORT: Port = Port { name: "link", bases: &[TAGS, FIELDS, text::WINDOW_TEXT], run };

const BEGIN_LINK_SEND: u32 = 0x0809_AEC0;
const BEGIN_LINK_RECEIVE: u32 = 0x0809_B00C;
/// LINK_PACKET_PAYLOAD_BYTES (link_transfer.h).
const PAYLOAD: u32 = 14;
const TAG_FORMAT: &str = "link_tag";

/// RunLinkBattle: RunMenuScript(0x0802875C) prints the field list, RunMenuScript(0x08028871) selects from it.
const FIELD_LIST_MENU: u32 = 0x0802_875C;
const FIELD_SELECT_MENU: u32 = 0x0802_8871;
const FIELD_TERRAINS: u32 = 0x087A_3614;
const FIELD_NAMES: u32 = 0x087A_3624;
const MENU_OPEN_WINDOW: u8 = 1;
const MENU_PRINT_TEXT: u8 = 5;
const MENU_SELECT: u8 = 7;
const WINDOW_FLAG_TEXT_LIST: u8 = 0x80;

/// `name = ...` or `name asm("rN") = ...` on this line (not `==`, `+=`, or a member).
fn assigns(line: &str, name: &str) -> bool {
    let bytes = line.as_bytes();
    let ident = |byte: u8| byte.is_ascii_alphanumeric() || byte == b'_';
    let mut search = 0;
    while let Some(found) = line[search..].find(name) {
        let start = search + found;
        let end = start + name.len();
        search = end;
        if (start > 0 && (ident(bytes[start - 1]) || bytes[start - 1] == b'.' || bytes[start - 1] == b'>')) || (end < bytes.len() && ident(bytes[end])) {
            continue;
        }
        let mut rest = line[end..].trim_start();
        if let Some(after) = rest.strip_prefix("asm(") {
            let Some(close) = after.find(')') else { continue };
            rest = after[close + 1..].trim_start();
        }
        if rest.starts_with('=') && !rest.starts_with("==") {
            return true;
        }
    }
    false
}

/// The tag a call site passes: the reference when it is the argument itself, else the ROM address the named
/// variable was last given in the same function (the scanner's `assigned:` references list every earlier value).
fn tag_of(ctx: &Ctx, reference: &Reference) -> R<u32> {
    let Some(name) = reference.via.strip_prefix("assigned:") else { return Ok(reference.address) };
    let source = std::fs::read_to_string(crate::repo_root().join(&reference.file)).map_err(|error| format!("{}: {error}", reference.file))?;
    let lines: Vec<&str> = source.lines().collect();
    for line in (1..reference.line).rev() {
        let text = lines[line as usize - 1];
        if text.starts_with('}') {
            break;
        }
        if !assigns(text, name) {
            continue;
        }
        let found: BTreeSet<u32> = ctx.roots.refs.iter().filter(|other| other.file == reference.file && other.line == line && !other.via.starts_with("assigned:")).map(|other| other.address).collect();
        if found.len() != 1 {
            return Err(format!("{}: {name} is assigned at line {line}, which references {} ROM addresses", reference.location(), found.len()));
        }
        return Ok(*found.iter().next().unwrap());
    }
    Err(format!("{}: no assignment of {name} earlier in its function", reference.location()))
}

#[derive(Default)]
struct Uses {
    sends: Vec<String>,
    receives: Vec<String>,
    not_this_tag: BTreeSet<String>,
}

fn tags(ctx: &Ctx) -> R<()> {
    let mut sites: BTreeMap<(String, u32, bool), u32> = BTreeMap::new();
    for (callee, send) in [(BEGIN_LINK_SEND, true), (BEGIN_LINK_RECEIVE, false)] {
        for reference in ctx.roots.calls(callee, 2) {
            let tag = tag_of(ctx, reference)?;
            let key = (reference.file.clone(), reference.line, send);
            if let Some(&known) = sites.get(&key) {
                if known != tag {
                    return Err(format!("{}: tag resolves to 0x{known:08X} and 0x{tag:08X}", reference.location()));
                }
                continue;
            }
            if !ctx.rom.is_data(tag) {
                return Err(format!("{}: link tag 0x{tag:08X} is not ROM data", reference.location()));
            }
            sites.insert(key, tag);
        }
    }
    let mut by_tag: BTreeMap<u32, Uses> = BTreeMap::new();
    for ((file, line, send), tag) in &sites {
        let uses = by_tag.entry(*tag).or_default();
        let at = format!("{file}:{line}");
        if *send {
            uses.sends.push(at);
        } else {
            uses.receives.push(at);
        }
    }
    for reference in ctx.roots.refs.iter().filter(|reference| reference.via.starts_with("assigned:") && reference.arg == 2) {
        let send = match reference.callee.as_deref() {
            Some("func_0809AEC0") => true,
            Some("func_0809B00C") => false,
            _ => continue,
        };
        if let Some(uses) = by_tag.get_mut(&reference.address) {
            if sites.get(&(reference.file.clone(), reference.line, send)) != Some(&reference.address) {
                uses.not_this_tag.insert(reference.location());
            }
        }
    }
    for (tag, uses) in &by_tag {
        let reached: Vec<String> = uses.sends.iter().chain(uses.receives.iter()).cloned().collect();
        let (id, _) = ctx.item("link.tag", *tag, TAGS, reached);
        let mut overlaps = Vec::new();
        if !uses.sends.is_empty() {
            overlaps = claim_outside_code(ctx.rom, *tag, PAYLOAD, NEUTRAL, id)?;
        }
        let mut compared = 0;
        if !uses.receives.is_empty() {
            while compared < PAYLOAD {
                let byte = ctx.rom.claim(tag + compared, 1, TAG_FORMAT, id)?[0];
                compared += 1;
                if byte == 0 {
                    break;
                }
            }
        }
        let text: String = ctx.rom.peek(*tag, PAYLOAD)?.iter().take_while(|&&byte| byte != 0).map(|&byte| if byte.is_ascii_graphic() || byte == b' ' { byte as char } else { '?' }).collect();
        let count = match (uses.sends.is_empty(), uses.receives.is_empty()) {
            (false, false) => "c_constant:LINK_PACKET_PAYLOAD_BYTES (PollLinkSend copies 14 tag bytes); terminator:NUL within LINK_PACKET_PAYLOAD_BYTES (PollLinkReceive compares)",
            (false, true) => "c_constant:LINK_PACKET_PAYLOAD_BYTES (PollLinkSend copies 14 tag bytes)",
            _ => "terminator:NUL within LINK_PACKET_PAYLOAD_BYTES (PollLinkReceive compares)",
        };
        ctx.count(id, count);
        ctx.set(id, json!({
            "text": text,
            "sent_by": uses.sends,
            "received_by": uses.receives,
            "send_copy_bytes": if uses.sends.is_empty() { 0 } else { PAYLOAD },
            "receive_compare_bytes": compared,
            "code_overlaps": overlaps.iter().map(|(start, end)| format!("0x{start:08X}..0x{end:08X}")).collect::<Vec<_>>(),
            "calls_the_scanner_pairs_with_this_tag_that_pass_another": uses.not_this_tag,
        }));
    }
    Ok(())
}

/// Items RunMenuScript's list printer makes: one per 0x0A and one at the closing NUL (operands of 1 and 2 skipped).
fn list_items(ctx: &Ctx, address: u32) -> R<u32> {
    let mut cursor = ctx.rom.dry_cursor(address);
    let mut items = 0;
    loop {
        match cursor.u8()? {
            0 => return Ok(items + 1),
            1 => {
                cursor.u8()?;
            }
            2 => {
                cursor.u8()?;
                cursor.u8()?;
            }
            0x0A => items += 1,
            _ => {}
        }
    }
}

/// sp18[0] indexes the field names (0 in state 0x1000, else the field-list selection); sp18[1] = selection - 1
/// indexes the terrain bytes. SELECT clamps the selection below the window's item count, which the list sets.
fn fields(ctx: &Ctx) -> R<()> {
    let menu = ctx.rom.peek(FIELD_LIST_MENU, 9)?;
    if menu[0] != MENU_OPEN_WINDOW || menu[7] != MENU_PRINT_TEXT || menu[8] != menu[1] || menu[6].wrapping_mul(0x10) & WINDOW_FLAG_TEXT_LIST == 0 {
        return Err(format!("menu script 0x{FIELD_LIST_MENU:08X} is not OPEN_WINDOW (text list) then PRINT_TEXT on that window"));
    }
    let window = menu[1];
    let select = ctx.rom.peek(FIELD_SELECT_MENU, 2)?;
    if select[0] != MENU_SELECT || select[1] != window {
        return Err(format!("menu script 0x{FIELD_SELECT_MENU:08X} is not SELECT on window {window}"));
    }
    let items = list_items(ctx, FIELD_LIST_MENU + 9)?;
    let mut list = ctx.rom.dry_cursor(FIELD_LIST_MENU + 9);
    let rendered = text::parse_list(&mut list)?;
    if ctx.rom.peek(list.address, 1)?[0] != 0 {
        return Err(format!("menu script 0x{FIELD_LIST_MENU:08X} does not END after its field list"));
    }
    let next = ctx.roots.by_address().range(FIELD_NAMES + 1..).next().map(|(address, _)| *address).ok_or("no root after the field names")?;
    if FIELD_NAMES + items * 4 > next || FIELD_TERRAINS + items - 1 > FIELD_NAMES {
        return Err(format!("{items} field list items run past the tables at 0x{FIELD_TERRAINS:08X} and 0x{FIELD_NAMES:08X}"));
    }

    let (names_id, _) = ctx.item("table.link_battle_field_names", FIELD_NAMES, FIELDS, ctx.roots.require(FIELD_NAMES)?);
    let mut names = Vec::new();
    for index in 0..items {
        let pointer = le32(ctx.rom.claim(FIELD_NAMES + index * 4, 4, "table.link_battle_field_names", names_id)?, 0);
        let text_id = text::window_text(ctx, pointer, vec![format!("table.link_battle_field_names@0x{FIELD_NAMES:08X}[{index}]")])?;
        names.push(json!({ "index": index, "text": format!("0x{pointer:08X}"), "item": ctx.name(text_id) }));
    }
    ctx.count(names_id, &format!("c_index:selection of the {items}-item field list (menu script 0x{FIELD_LIST_MENU:08X}, SELECT 0x{FIELD_SELECT_MENU:08X} clamps below the item count); 0 in state 0x1000; the peer's value comes from the same menu"));
    ctx.set(names_id, json!({ "entry_bytes": 4, "printed_by": "PrintWindowText(entry, 0, 7)", "names": names, "field_list": rendered }));

    let (terrains_id, _) = ctx.item("table.link_battle_field_terrains", FIELD_TERRAINS, FIELDS, ctx.roots.require(FIELD_TERRAINS)?);
    let values = ctx.rom.claim(FIELD_TERRAINS, items - 1, "table.link_battle_field_terrains", terrains_id)?.to_vec();
    ctx.count(terrains_id, &format!(
        "c_index:selection - 1 for selections 1..{} of the field list; the random branch (CallFunctionR0(*(s32 *)0x03000010) * 0xE) >> 0xF calls IWRAM code copied from 0x080005AC, which has no matched source, so its range is not determined here",
        items - 1
    ));
    ctx.set(terrains_id, json!({ "entry_bytes": 1, "stored_to": "0x0203055C[1]", "values": values }));
    Ok(())
}

fn run(ctx: &Ctx) -> R<()> {
    tags(ctx)?;
    fields(ctx)
}

#[cfg(test)]
mod tests {
    use super::assigns;

    #[test]
    fn assignment_forms() {
        assert!(assigns("    asset = (u8 *)0x08107060;", "asset"));
        assert!(assigns("        register void *asset asm(\"r5\") = (void *)0x08107148;", "asset"));
        assert!(assigns("        const void *link_message = (void *)BATTLE_LINK_PARTY_NAME_MESSAGE;", "link_message"));
        assert!(!assigns("        asset_r2 = 0x08108C20;", "asset"));
        assert!(!assigns("    transfer += 4;", "transfer"));
        assert!(!assigns("    if (asset == 0) {", "asset"));
        assert!(!assigns("    BeginLinkSend(transfer, 4, asset);", "asset"));
    }
}
