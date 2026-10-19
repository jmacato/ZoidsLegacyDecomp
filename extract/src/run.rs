//! Items found by the ports, and the output files.

use std::cell::RefCell;
use std::collections::{BTreeMap, HashMap};
use std::fs;
use std::path::{Path, PathBuf};

use serde_json::{json, Value};

use crate::basis::Basis;
use crate::rom::{Rom, R};
use crate::roots::Roots;
use crate::{sha1_hex, BASE, ROM_SIZE};

pub struct Item {
    pub kind: String,
    pub address: u32,
    pub basis: Basis,
    pub reached: Vec<String>,
    pub count: Option<String>,
    pub data: Value,
    pub files: Vec<String>,
    /// Content-free render recipes for the browser page (ROM ranges and decode steps, never decoded values).
    pub views: Vec<Value>,
}

pub struct Declared {
    pub start: u32,
    pub end: u32,
    pub item: Option<usize>,
    pub basis: Basis,
    pub reason: String,
}

pub struct Ctx<'a> {
    pub rom: &'a Rom,
    pub roots: &'a Roots,
    out: PathBuf,
    items: RefCell<Vec<Item>>,
    index: RefCell<HashMap<(String, u32), usize>>,
    declared: RefCell<Vec<Declared>>,
}

impl<'a> Ctx<'a> {
    pub fn new(rom: &'a Rom, roots: &'a Roots, out: &Path) -> Ctx<'a> {
        Ctx { rom, roots, out: out.to_path_buf(), items: RefCell::new(Vec::new()), index: RefCell::new(HashMap::new()), declared: RefCell::new(Vec::new()) }
    }

    pub fn out_dir(&self) -> &Path {
        &self.out
    }

    /// The item for (kind, address); `true` when it is new and the caller must decode it.
    pub fn item(&self, kind: &str, address: u32, basis: Basis, reached: Vec<String>) -> (usize, bool) {
        let key = (kind.to_string(), address);
        if let Some(&id) = self.index.borrow().get(&key) {
            let mut items = self.items.borrow_mut();
            for from in reached {
                if !items[id].reached.contains(&from) {
                    items[id].reached.push(from);
                }
            }
            return (id, false);
        }
        let mut items = self.items.borrow_mut();
        items.push(Item { kind: kind.to_string(), address, basis, reached, count: None, data: Value::Null, files: Vec::new(), views: Vec::new() });
        let id = items.len() - 1;
        self.index.borrow_mut().insert(key, id);
        (id, true)
    }

    pub fn name(&self, id: usize) -> String {
        let items = self.items.borrow();
        format!("{}@0x{:08X}", items[id].kind, items[id].address)
    }

    /// The data an earlier port set on (kind, address).
    pub fn data(&self, kind: &str, address: u32) -> Option<Value> {
        let id = *self.index.borrow().get(&(kind.to_string(), address))?;
        Some(self.items.borrow()[id].data.clone())
    }

    pub fn reached_of(&self, kind: &str, address: u32) -> Vec<String> {
        let Some(&id) = self.index.borrow().get(&(kind.to_string(), address)) else { return Vec::new() };
        self.items.borrow()[id].reached.clone()
    }

    pub fn data_of(&self, kind: &str) -> Vec<(u32, Value)> {
        self.items.borrow().iter().filter(|item| item.kind == kind).map(|item| (item.address, item.data.clone())).collect()
    }

    /// Attach a render recipe. It may hold addresses, lengths, enum-like parameters and SHA-1s of bytes Rust decoded; never ROM content.
    pub fn view_count(&self, id: usize) -> usize {
        self.items.borrow()[id].views.len()
    }

    pub fn view(&self, id: usize, view: Value) {
        let mut items = self.items.borrow_mut();
        if !items[id].views.contains(&view) {
            items[id].views.push(view);
        }
    }

    pub fn set(&self, id: usize, data: Value) {
        self.items.borrow_mut()[id].data = data;
    }

    pub fn count(&self, id: usize, source: &str) {
        self.items.borrow_mut()[id].count = Some(source.to_string());
    }

    pub fn file(&self, id: usize, suffix: &str, bytes: &[u8]) -> R<String> {
        let (kind, address) = {
            let items = self.items.borrow();
            (items[id].kind.clone(), items[id].address)
        };
        let relative = format!("files/{}/{:08X}{suffix}", kind.replace('.', "/"), address);
        let path = self.out.join(&relative);
        fs::create_dir_all(path.parent().unwrap()).map_err(|error| error.to_string())?;
        fs::write(&path, bytes).map_err(|error| format!("{}: {error}", path.display()))?;
        self.items.borrow_mut()[id].files.push(relative.clone());
        Ok(relative)
    }

    /// A referenced address no port reads, with the reason from the C (for example: runtime-only extent). Claims nothing.
    pub fn explain(&self, address: u32, basis: Basis, reason: &str) -> R<()> {
        let (id, _) = self.item("root.explained", address, basis, self.roots.require(address)?);
        self.set(id, serde_json::json!({ "reason": reason }));
        Ok(())
    }

    /// A ROM address held in ported data that no port reads, with the reason from the C. Claims nothing.
    pub fn explain_target(&self, address: u32, referrer: u32, basis: Basis, reason: &str) -> R<()> {
        let (id, _) = self.item("root.explained", address, basis, vec![format!("pointer at 0x{referrer:08X}")]);
        self.set(id, serde_json::json!({ "reason": reason }));
        Ok(())
    }

    /// Bytes inside item `id` that the C it ports never reads, with the C evidence. A port must not also read them.
    pub fn unread(&self, id: usize, address: u32, length: u32, reason: &str) -> R<()> {
        let basis = self.items.borrow()[id].basis;
        self.declared.borrow_mut().push(Declared { start: address, end: address + length, item: Some(id), basis, reason: reason.to_string() });
        Ok(())
    }

    /// A data range no decomp code reaches, with the check that shows it. A port must not also read it.
    pub fn unreachable(&self, address: u32, length: u32, basis: Basis, reason: &str) -> R<()> {
        self.declared.borrow_mut().push(Declared { start: address, end: address + length, item: None, basis, reason: reason.to_string() });
        Ok(())
    }

    /// The declaration covering `address`: (declared inside an item, reason).
    pub fn declared_at(&self, address: u32) -> Option<(bool, String)> {
        self.declared.borrow().iter().find(|entry| entry.start <= address && address < entry.end).map(|entry| (entry.item.is_some(), entry.reason.clone()))
    }

    /// Kinds of the items that start at `address`.
    pub fn kinds_at(&self, address: u32) -> Vec<String> {
        self.items.borrow().iter().filter(|item| item.address == address).map(|item| item.kind.clone()).collect()
    }

    pub fn has_file(&self, id: usize, relative: &str) -> bool {
        self.items.borrow()[id].files.iter().any(|file| file == relative)
    }

    pub fn finish(&self) -> R<String> {
        let items = self.items.borrow();
        let claims = self.rom.claims();
        let mut spans: Vec<Vec<(u32, u32)>> = vec![Vec::new(); items.len()];
        for claim in claims.iter() {
            spans[claim.item].push((claim.start, claim.end));
        }
        for list in &mut spans {
            list.sort();
            let mut merged: Vec<(u32, u32)> = Vec::new();
            for &(start, end) in list.iter() {
                match merged.last_mut() {
                    Some(last) if start <= last.1 => last.1 = last.1.max(end),
                    _ => merged.push((start, end)),
                }
            }
            *list = merged;
        }

        let mut order: Vec<usize> = (0..items.len()).collect();
        order.sort_by_key(|&id| (items[id].address, items[id].kind.clone()));
        let mut families: BTreeMap<String, Vec<Value>> = BTreeMap::new();
        let mut index = Vec::new();
        for &id in &order {
            let item = &items[id];
            let bytes: u32 = spans[id].iter().map(|(start, end)| end - start).sum();
            let span_text: Vec<Value> = spans[id].iter().map(|(start, end)| json!([format!("0x{start:08X}"), format!("0x{end:08X}")])).collect();
            index.push(json!({
                "kind": item.kind,
                "address": format!("0x{:08X}", item.address),
                "bytes": bytes,
                "spans": span_text,
                "basis": item.basis.label(),
                "basis_kind": item.basis.kind(),
            }));
            families.entry(item.kind.clone()).or_default().push(json!({
                "address": format!("0x{:08X}", item.address),
                "reached": item.reached,
                "count": item.count,
                "basis": item.basis.label(),
                "files": item.files,
                "data": item.data,
            }));
        }

        let owners = self.rom.owners();
        let code_bytes: u32 = self.rom.code_spans().iter().map(|(start, end)| end - start).sum();
        let mut per_format: BTreeMap<String, u64> = BTreeMap::new();
        let mut counts: HashMap<u16, u64> = HashMap::new();
        for &owner in owners.iter() {
            if owner != 0 {
                *counts.entry(owner).or_default() += 1;
            }
        }
        for (id, count) in counts {
            per_format.insert(self.rom.format_name(id), count);
        }
        let known: u64 = per_format.values().sum();
        let data_bytes = u64::from(ROM_SIZE - code_bytes);

        let roots = self.roots.by_address();
        let format_names: Vec<String> = (0..=owners.iter().copied().max().unwrap_or(0)).map(|id| self.rom.format_name(id)).collect();
        let pointer_format = |id: u16| {
            let name = &format_names[id as usize];
            id != 0 && (name.starts_with("table.") || matches!(name.as_str(), "mp2k.song_header" | "mp2k.tone_data" | "literal_pool"))
        };
        // Words that can hold a ROM pointer: aligned words read as a table, song header, tone data or literal pool, or aligned words of matched code.
        // Event-script pointers (START_SCRIPTS, JUMP) are followed by the walk itself, which fails on any non-data target.
        let mut pointer_words: BTreeMap<u32, Vec<u32>> = BTreeMap::new();
        for offset in 0..ROM_SIZE - 3 {
            let in_code = !self.rom.is_data(BASE + offset);
            let read_as_pointer = offset % 4 == 0 && (0..4).all(|index| pointer_format(owners[(offset + index) as usize]));
            if !(read_as_pointer || (in_code && offset % 4 == 0 && (0..4).all(|index| !self.rom.is_data(BASE + offset + index)))) {
                continue;
            }
            let bytes = if in_code { self.rom.code_bytes(BASE + offset, 4)? } else { self.rom.peek(BASE + offset, 4)? };
            let value = u32::from_le_bytes([bytes[0], bytes[1], bytes[2], bytes[3]]);
            if self.rom.is_data(value) {
                pointer_words.entry(value).or_default().push(BASE + offset);
            }
        }
        let mut closure = String::from("# ROM data addresses held in aligned pointer-bearing words that no port read: target referrer(s)\n");
        let mut dangling = 0;
        for (target, from) in &pointer_words {
            let offset = target - BASE;
            if owners[offset as usize] != 0 || items.iter().any(|item| item.address == *target) {
                continue;
            }
            let from_data: Vec<&u32> = from.iter().filter(|at| self.rom.is_data(**at)).collect();
            if from_data.is_empty() {
                continue;
            }
            dangling += 1;
            closure.push_str(&format!("0x{target:08X} {}\n", from_data.iter().map(|at| format!("0x{at:08X}")).collect::<Vec<_>>().join(" ")));
        }
        let declared = self.declared.borrow();
        let mut declared_at = vec![u32::MAX; ROM_SIZE as usize];
        for (index, entry) in declared.iter().enumerate() {
            for address in entry.start..entry.end {
                let offset = (address - BASE) as usize;
                if owners[offset] != 0 && self.rom.format_name(owners[offset]) != crate::rom::NEUTRAL {
                    return Err(format!("0x{address:08X} is declared unread ({}) but read as {}", entry.reason, self.rom.format_name(owners[offset])));
                }
                declared_at[offset] = index as u32;
            }
        }
        let mut owner_item = vec![usize::MAX; ROM_SIZE as usize];
        for claim in claims.iter() {
            for offset in claim.start - BASE..claim.end - BASE {
                owner_item[offset as usize] = claim.item;
            }
        }
        let mut classes: BTreeMap<&str, (u64, u64)> = BTreeMap::new();
        let mut unread = String::from("# Data bytes no ported reader read: start end size class [references at start]\n# class: declared_unread = inside an item, declared unread by its port with the C evidence; declared_unreachable = declared unreachable with its check;\n# explained = holds an explained address (explained_roots.txt); unselected_entries = starts a ported table whose entries the C never indexes;\n# fill_ff / zero = fill nothing points into; must be 0: undeclared_gap, undeclared_unreferenced, referenced_unread\n");
        let mut unread_bytes = 0u64;
        let mut fields: BTreeMap<usize, Vec<(u32, u32)>> = BTreeMap::new();
        let mut offset = 0u32;
        while offset < ROM_SIZE {
            if owners[offset as usize] != 0 || !self.rom.is_data(BASE + offset) {
                offset += 1;
                continue;
            }
            let start = offset;
            while offset < ROM_SIZE && owners[offset as usize] == 0 && self.rom.is_data(BASE + offset) {
                offset += 1;
            }
            unread_bytes += u64::from(offset - start);
            let bytes = self.rom.peek(BASE + start, offset - start)?;
            let before = if start > 0 { owner_item[start as usize - 1] } else { usize::MAX };
            let after = if offset < ROM_SIZE { owner_item[offset as usize] } else { usize::MAX };
            let referrers: Vec<String> = pointer_words.range(BASE + start..BASE + offset).flat_map(|(_, from)| from.iter().map(|at| format!("0x{at:08X}"))).collect();
            let starts_here: Vec<&Item> = items.iter().filter(|item| (BASE + start..BASE + offset).contains(&item.address)).collect();
            let all_declared = (start..offset).all(|at| declared_at[at as usize] != u32::MAX);
            let inside = before != usize::MAX && before == after;
            let class = if all_declared && declared[declared_at[start as usize] as usize].item.is_some() {
                "declared_unread"
            } else if all_declared {
                "declared_unreachable"
            } else if starts_here.iter().any(|item| item.kind == "root.explained") {
                "explained"
            } else if inside {
                "undeclared_gap"
            } else if !starts_here.is_empty() {
                "undeclared_gap"
            } else if !referrers.is_empty() {
                "referenced_unread"
            } else if bytes.iter().all(|&byte| byte == 0xFF) {
                "fill_ff"
            } else if bytes.iter().all(|&byte| byte == 0) {
                "zero"
            } else {
                "undeclared_unreferenced"
            };
            if class == "undeclared_gap" {
                fields.entry(before).or_default().push((start + BASE - items[before].address, offset - start));
            }
            let entry = classes.entry(class).or_default();
            entry.0 += 1;
            entry.1 += u64::from(offset - start);
            let refs: Vec<String> = roots.get(&(BASE + start)).map_or(Vec::new(), |list| list.iter().take(3).map(|reference| reference.location()).collect());
            let mut after_kind = if before != usize::MAX { format!("after:{} ", items[before].kind) } else { String::new() };
            if all_declared {
                after_kind.push_str(&format!("reason:{} ", declared[declared_at[start as usize] as usize].reason.replace(' ', "_")));
            }
            if !referrers.is_empty() {
                after_kind.push_str(&format!("referrers:{} ", referrers.join(",")));
            }
            if let Some(item) = starts_here.first() {
                after_kind.push_str(&format!("item:{}@0x{:08X} ", item.kind, item.address));
            }
            unread.push_str(&format!("0x{:08X} 0x{:08X} {} {class} {after_kind}{}\n", BASE + start, BASE + offset, offset - start, refs.join(" ")));
        }

        let mut unported = String::from("# ROM data addresses the source references that no ported reader read and no ported item starts at: address references\n");
        let mut unported_count = 0;
        let starts: std::collections::HashSet<u32> = items.iter().map(|item| item.address).collect();
        for (address, list) in &roots {
            if !self.rom.is_data(*address) || owners[(address - BASE) as usize] != 0 || starts.contains(address) {
                continue;
            }
            unported_count += 1;
            let refs: Vec<String> = list.iter().map(|reference| {
                let callee = reference.callee.clone().unwrap_or_default();
                format!("{}[{}:{}]", reference.location(), callee, reference.arg)
            }).collect();
            unported.push_str(&format!("0x{address:08X} {}\n", refs.join(" ")));
        }

        let mut coverage = String::new();
        coverage.push_str(&format!("rom bytes           {ROM_SIZE}\n"));
        coverage.push_str(&format!("code bytes          {code_bytes} (regions.txt, byte-matched C/asm)\n"));
        coverage.push_str(&format!("data bytes          {data_bytes}\n"));
        coverage.push_str(&format!("known data bytes    {known} ({:.2}% of data)\n", 100.0 * known as f64 / data_bytes as f64));
        coverage.push_str(&format!("unread data bytes   {unread_bytes}\n"));
        coverage.push_str(&format!("items               {}\n", items.len()));
        coverage.push_str(&format!("unported roots      {unported_count}\n"));
        coverage.push_str(&format!("dangling pointers   {dangling} (closure.txt)\n\n# unread bytes per class: ranges bytes\n"));
        for (class, (ranges, bytes)) in &classes {
            coverage.push_str(&format!("{class:32} {ranges} {bytes}\n"));
        }
        coverage.push_str("\n# known bytes per format\n");
        for (format, count) in &per_format {
            coverage.push_str(&format!("{format:32} {count}\n"));
        }
        coverage.push_str("\n# items per kind\n");
        for (kind, list) in &families {
            coverage.push_str(&format!("{kind:32} {}\n", list.len()));
        }

        let write = |name: &str, text: &str| -> R<()> {
            let path = self.out.join(name);
            fs::create_dir_all(path.parent().unwrap()).map_err(|error| error.to_string())?;
            fs::write(&path, text).map_err(|error| format!("{}: {error}", path.display()))
        };
        for (kind, list) in &families {
            write(&format!("data/{kind}.json"), &serde_json::to_string_pretty(list).unwrap())?;
        }
        let manifest = serde_json::to_string_pretty(&json!({
            "rom_sha1": crate::EXPECTED_SHA1,
            "code_bytes": code_bytes,
            "data_bytes": data_bytes,
            "known_data_bytes": known,
            "unread_data_bytes": unread_bytes,
            "items": index,
        }))
        .unwrap();
        write("manifest.json", &manifest)?;
        write("coverage.txt", &coverage)?;
        write("unread.txt", &unread)?;
        write("closure.txt", &closure)?;
        let mut field_text = String::from("# Undeclared gaps: bytes inside an item that its port neither reads nor declares unread: item kind basis | +offset:length ...\n");
        for (id, gaps) in &fields {
            let item = &items[*id];
            let list: Vec<String> = gaps.iter().map(|(at, length)| format!("+0x{at:X}:{length}")).collect();
            field_text.push_str(&format!("0x{:08X} {} {} | {}\n", item.address, item.kind, item.basis.label(), list.join(" ")));
        }
        write("unread_fields.txt", &field_text)?;
        let mut declared_text = String::from("# Declared unread or unreachable ranges: start end item basis | reason\n");
        for entry in declared.iter() {
            let item = entry.item.map_or("-".to_string(), |id| format!("{}@0x{:08X}", items[id].kind, items[id].address));
            declared_text.push_str(&format!("0x{:08X} 0x{:08X} {item} {} | {}\n", entry.start, entry.end, entry.basis.label(), entry.reason));
        }
        write("declared.txt", &declared_text)?;
        write("unported_roots.txt", &unported)?;
        let mut explained = String::from("# Referenced addresses no port reads, with the reason: address reason\n");
        for item in items.iter().filter(|item| item.kind == "root.explained") {
            explained.push_str(&format!("0x{:08X} {}\n", item.address, item.data["reason"].as_str().unwrap_or("")));
        }
        write("explained_roots.txt", &explained)?;

        let mut kinds: Vec<String> = items.iter().map(|item| item.kind.clone()).collect();
        kinds.sort();
        kinds.dedup();
        let mut bases: Vec<String> = items.iter().map(|item| item.basis.label()).chain(declared.iter().map(|entry| entry.basis.label())).collect();
        bases.sort();
        bases.dedup();
        let position: HashMap<usize, usize> = order.iter().enumerate().map(|(at, id)| (*id, at)).collect();
        let mut plan_items = Vec::new();
        for &id in &order {
            let item = &items[id];
            let mut parts = Vec::new();
            for &(start, end) in &spans[id] {
                let mut at = start;
                while at < end {
                    let format = owners[(at - BASE) as usize];
                    let mut stop = at + 1;
                    while stop < end && owners[(stop - BASE) as usize] == format {
                        stop += 1;
                    }
                    parts.push(json!([at, stop, format]));
                    at = stop;
                }
            }
            let reason = if item.kind == "root.explained" { item.data["reason"].clone() } else { Value::Null };
            let via: Vec<usize> = if spans[id].is_empty() {
                let mut owning: Vec<usize> = claims.iter().filter(|claim| claim.start <= item.address && item.address < claim.end && claim.item != id).map(|claim| position[&claim.item]).collect();
                if owning.is_empty() {
                    let name = format!("{}@0x{:08X}", item.kind, item.address);
                    owning = items.iter().enumerate().filter(|(other, entry)| *other != id && !spans[*other].is_empty() && entry.reached.iter().any(|from| from.starts_with(&name))).map(|(other, _)| position[&other]).collect();
                }
                owning.sort();
                owning.dedup();
                owning
            } else {
                Vec::new()
            };
            plan_items.push(json!([
                kinds.binary_search(&item.kind).unwrap(),
                item.address,
                bases.binary_search(&item.basis.label()).unwrap(),
                item.count,
                item.reached,
                parts,
                item.views,
                reason,
                via,
            ]));
        }
        let class_names: Vec<&str> = vec!["declared_unread", "declared_unreachable", "explained", "fill_ff", "zero", "undeclared_gap", "referenced_unread", "undeclared_unreferenced"];
        let mut reasons: Vec<String> = declared.iter().map(|entry| entry.reason.clone()).collect();
        reasons.sort();
        reasons.dedup();
        let mut plan_unread = Vec::new();
        for line in unread.lines().filter(|line| !line.starts_with('#')) {
            let fields: Vec<&str> = line.split_whitespace().collect();
            let start = crate::verify_c::parse_hex(fields[0])?;
            let end = crate::verify_c::parse_hex(fields[1])?;
            let class = class_names.iter().position(|name| *name == fields[3]).ok_or_else(|| format!("unknown class {}", fields[3]))?;
            let offset = (start - BASE) as usize;
            let entry = (declared_at[offset] != u32::MAX).then(|| &declared[declared_at[offset] as usize]);
            let reason = entry.map_or(-1, |entry| reasons.binary_search(&entry.reason).unwrap() as i64);
            let basis = entry.map_or(-1, |entry| bases.binary_search(&entry.basis.label()).unwrap() as i64);
            let inside = entry.and_then(|entry| entry.item).map_or(-1, |id| position[&id] as i64);
            let before = if offset > 0 && owner_item[offset - 1] != usize::MAX { position[&owner_item[offset - 1]] as i64 } else { -1 };
            plan_unread.push(json!([start, end, class, reason, basis, inside, before]));
        }
        let regions: Vec<Value> = crate::verify_c::regions(&crate::repo_root().join("regions.txt"))?
            .iter()
            .map(|region| json!([BASE + region.start, BASE + region.end, region.sources.join(",")]))
            .collect();
        let plan = json!({
            "version": 1,
            "rom_sha1": crate::EXPECTED_SHA1,
            "rom_size": ROM_SIZE,
            "base": BASE,
            "summary": {
                "code_bytes": code_bytes, "data_bytes": data_bytes, "known_data_bytes": known, "unread_data_bytes": unread_bytes,
                "unported_roots": unported_count, "dangling_pointers": dangling,
                "classes": classes.iter().map(|(class, (ranges, bytes))| (class.to_string(), json!([ranges, bytes]))).collect::<serde_json::Map<String, Value>>(),
            },
            "formats": format_names,
            "kinds": kinds,
            "bases": bases,
            "classes": class_names,
            "reasons": reasons,
            "regions": regions,
            "items": plan_items,
            "unread": plan_unread,
        });
        write("plan.json", &serde_json::to_string(&plan).unwrap())?;
        Ok(format!("{coverage}\nmanifest.json sha1 {}\n", sha1_hex(manifest.as_bytes())))
    }
}
