//! Port of tools/verify.py and tools/linklib.py: compile each region and compare it with the ROM.

use std::collections::{BTreeSet, HashSet};
use std::fs;
use std::path::{Path, PathBuf};
use std::process::{Command, ExitCode};
use std::sync::atomic::{AtomicUsize, Ordering};
use std::sync::Mutex;

use crate::{repo_root, rom_sha1, BASE, EXPECTED_SHA1, ROM_SIZE};

const CALL_VIA_BASE: u32 = 0x080E_CD5C;
const AS: [&str; 3] = ["arm-none-eabi-as", "-mcpu=arm7tdmi", "-mthumb-interwork"];

#[derive(Clone, Debug)]
pub struct Region {
    pub name: String,
    pub start: u32,
    pub end: u32,
    pub sources: Vec<String>,
    pub mode: Option<String>,
}

pub fn regions(path: &Path) -> Result<Vec<Region>, String> {
    let text = fs::read_to_string(path).map_err(|error| format!("{}: {error}", path.display()))?;
    let mut out = Vec::new();
    for raw in text.lines() {
        let fields: Vec<&str> = raw.split('#').next().unwrap().split_whitespace().collect();
        if fields.is_empty() {
            continue;
        }
        if fields.len() < 4 {
            return Err(format!("invalid region line: {raw}"));
        }
        let mode = fields.get(4).map(|mode| mode.to_string());
        if let Some(mode) = &mode {
            if !["old", "pb", "noint", "o1"].contains(&mode.as_str()) {
                return Err(format!("invalid compiler mode: {mode}"));
            }
        }
        out.push(Region {
            name: fields[0].to_string(),
            start: parse_hex(fields[1])?,
            end: parse_hex(fields[2])?,
            sources: fields[3].split(',').map(str::to_string).collect(),
            mode,
        });
    }
    Ok(out)
}

pub fn parse_hex(text: &str) -> Result<u32, String> {
    u32::from_str_radix(text.trim_start_matches("0x").trim_start_matches("0X"), 16).map_err(|_| format!("bad hex: {text}"))
}

fn functions() -> Result<Vec<serde_json::Value>, String> {
    let path = repo_root().join("cfg/functions.json");
    let text = fs::read_to_string(&path).map_err(|error| format!("{}: {error}", path.display()))?;
    match serde_json::from_str(&text).map_err(|error| error.to_string())? {
        serde_json::Value::Array(items) => Ok(items),
        _ => Err("cfg/functions.json is not a list".into()),
    }
}

fn field_hex(item: &serde_json::Value, key: &str) -> Result<u32, String> {
    parse_hex(item[key].as_str().ok_or_else(|| format!("functions.json entry lacks {key}"))?)
}

pub fn merged_spans(regions: &[Region]) -> Result<Vec<(u32, u32)>, String> {
    let mut sorted: Vec<&Region> = regions.iter().collect();
    sorted.sort_by_key(|region| region.start);
    let mut spans: Vec<(u32, u32)> = Vec::new();
    for region in sorted {
        if !(region.start < region.end && region.end <= ROM_SIZE) {
            return Err("Region bounds are outside the ROM.".into());
        }
        match spans.last_mut() {
            Some(last) if region.start <= last.1 => last.1 = last.1.max(region.end),
            _ => spans.push((region.start, region.end)),
        }
    }
    Ok(spans)
}

fn coverage(regions: &[Region]) -> Result<(usize, u64), String> {
    let spans = merged_spans(regions)?;
    let owners: Vec<serde_json::Value> = functions()?.into_iter().filter(|owner| owner["kind"] != "block").collect();
    if owners.is_empty() {
        return Err("The callable inventory is empty.".into());
    }
    let mut total = 0u64;
    let mut missing = Vec::new();
    for owner in &owners {
        let (start, end) = (field_hex(owner, "lo")?, field_hex(owner, "hi")?);
        if end <= start {
            return Err(format!("Invalid owner span: {}", owner["entry"]));
        }
        total += u64::from(end - start);
        if !spans.iter().any(|&(low, high)| BASE + low <= start && end <= BASE + high) {
            missing.push(owner["entry"].as_str().unwrap_or("?").to_string());
        }
    }
    if !missing.is_empty() {
        return Err(format!("Regions omit {} complete callable spans; first: {}", missing.len(), missing[0]));
    }
    Ok((owners.len(), total))
}

fn compiler_flags(mode: Option<&str>) -> Vec<&'static str> {
    let mut flags = vec![
        if mode == Some("o1") { "-O" } else { "-O2" },
        if mode == Some("noint") { "-mno-thumb-interwork" } else { "-mthumb-interwork" },
    ];
    if mode == Some("pb") {
        flags.push("-fprologue-bugfix");
    }
    flags
}

fn run(program: &str, args: &[&str], label: &str) -> Result<String, String> {
    let output = Command::new(program)
        .args(args)
        .current_dir(repo_root())
        .output()
        .map_err(|error| format!("{label} failed\n{program}: {error}"))?;
    let stdout = String::from_utf8_lossy(&output.stdout).into_owned();
    if output.status.success() {
        return Ok(stdout);
    }
    let detail = format!("{stdout}{}", String::from_utf8_lossy(&output.stderr));
    let lines: Vec<&str> = detail.trim().lines().collect();
    Err(format!("{label} failed\n{}", lines[lines.len().saturating_sub(8)..].join("\n")))
}

fn assemble(source: &Path, object: &Path, label: &str) -> Result<(), String> {
    let mut args: Vec<&str> = AS[1..].to_vec();
    args.extend(["-o", object.to_str().unwrap(), source.to_str().unwrap()]);
    run(AS[0], &args, label).map(|_| ())
}

fn function_addresses() -> Result<HashSet<u32>, String> {
    let items = functions()?;
    let key = if items.first().map_or(false, |item| item.get("entry").is_some()) { "entry" } else { "addr" };
    items.iter().map(|item| field_hex(item, key)).collect()
}

fn relocations(object: &Path, label: &str) -> Result<Vec<(String, String)>, String> {
    let text = run("arm-none-eabi-objdump", &["-r", object.to_str().unwrap()], label)?;
    Ok(text
        .lines()
        .filter_map(|line| {
            let parts: Vec<&str> = line.split_whitespace().collect();
            (parts.len() >= 3 && parts[1].starts_with("R_ARM_")).then(|| (parts[2].to_string(), parts[1].to_string()))
        })
        .collect())
}

fn defined(object: &Path, label: &str) -> Result<HashSet<String>, String> {
    let text = run("arm-none-eabi-objdump", &["-t", object.to_str().unwrap()], label)?;
    let mut out = HashSet::new();
    for line in text.lines() {
        if line.contains(" *UND*") || line.contains("*ABS*") {
            continue;
        }
        let Some(split) = line.rfind(char::is_whitespace) else { continue };
        let name = &line[split + 1..];
        if !name.is_empty() && (line.contains("g ") || line.contains("l ")) {
            out.insert(name.to_string());
        }
    }
    Ok(out)
}

fn link_text(objects: &[PathBuf], vma: u32, work: &Path, functions: &HashSet<u32>, label: &str) -> Result<Vec<u8>, String> {
    let mut known = HashSet::new();
    for object in objects {
        known.extend(defined(object, label)?);
    }
    let mut calls: BTreeSet<(String, u32)> = BTreeSet::new();
    let mut absolutes: BTreeSet<(String, u32)> = BTreeSet::new();
    for object in objects {
        for (symbol, kind) in relocations(object, label)? {
            if known.contains(&symbol) {
                continue;
            }
            let address = if let Some(hex) = symbol.strip_prefix("func_") {
                match u32::from_str_radix(hex, 16) {
                    Ok(address) if !hex.is_empty() => address,
                    _ => continue,
                }
            } else if let Some(register) = symbol.strip_prefix("_call_via_r").and_then(|rest| rest.parse::<u32>().ok()).filter(|r| *r < 8) {
                if symbol.len() != "_call_via_r0".len() {
                    continue;
                }
                CALL_VIA_BASE + 4 * register
            } else {
                continue;
            };
            if kind.contains("CALL") || kind.contains("JUMP") {
                calls.insert((symbol, address));
            } else if functions.contains(&address) {
                absolutes.insert((symbol, address));
            }
        }
    }

    let stub_source = work.join("_stubs.s");
    let mut stubs = String::from(".syntax unified\n.thumb\n");
    for (symbol, address) in &calls {
        stubs.push_str(&format!(".section .stub_{address:X},\"ax\",%progbits\n.global {symbol}\n.thumb_func\n{symbol}:\n.byte 0,0\n"));
    }
    fs::write(&stub_source, stubs).map_err(|error| error.to_string())?;
    let stub_object = work.join("_stubs.o");
    assemble(&stub_source, &stub_object, label)?;

    let stubbed: HashSet<u32> = calls.iter().map(|(_, address)| *address).collect();
    let mut script = format!("INCLUDE \"{}\"\n", repo_root().join("symbols.ld").display());
    for (symbol, address) in &absolutes {
        if !stubbed.contains(address) {
            script.push_str(&format!("{symbol} = 0x{:08X};\n", address + 1));
        }
    }
    script.push_str("SECTIONS {\n");
    let inputs: Vec<String> = objects.iter().map(|object| format!("{}(.text .text.* .rodata .rodata.*)", object.display())).collect();
    script.push_str(&format!("  .text 0x{vma:08X} : SUBALIGN(2) {{ {} }}\n", inputs.join(" ")));
    for (_, address) in &calls {
        script.push_str(&format!("  .stub_{address:X} 0x{address:08X} : {{ {}(.stub_{address:X}) }}\n", stub_object.display()));
    }
    script.push_str("  /DISCARD/ : { *(*) }\n}\n");
    let linker_script = work.join("_link.ld");
    fs::write(&linker_script, script).map_err(|error| error.to_string())?;

    let elf = work.join("_link.elf");
    let mut args: Vec<String> = vec!["--entry=0".into(), "-T".into(), linker_script.display().to_string()];
    args.extend(objects.iter().map(|object| object.display().to_string()));
    args.extend([stub_object.display().to_string(), "-o".into(), elf.display().to_string()]);
    run("arm-none-eabi-ld", &args.iter().map(String::as_str).collect::<Vec<_>>(), label)?;
    let binary = work.join("region.bin");
    run("arm-none-eabi-objcopy", &["-O", "binary", "-j", ".text", elf.to_str().unwrap(), binary.to_str().unwrap()], label)?;
    fs::read(&binary).map_err(|error| error.to_string())
}

fn compile_region(region: &Region, work: &Path, agbcc: &Path, old_agbcc: &Path, functions: &HashSet<u32>) -> Result<Vec<u8>, String> {
    let label = region.name.as_str();
    let compiler = if region.mode.as_deref() == Some("old") { old_agbcc } else { agbcc };
    if !compiler.is_file() {
        return Err(format!("compiler is unavailable: {}", compiler.display()));
    }
    let flags = compiler_flags(region.mode.as_deref());
    let mut objects = Vec::new();
    for (index, name) in region.sources.iter().enumerate() {
        let source = repo_root().join("src").join(name);
        if !source.is_file() {
            return Err(format!("missing source: {name}"));
        }
        let object = work.join(format!("{index}.o"));
        if source.extension().map_or(false, |ext| ext == "s") {
            assemble(&source, &object, label)?;
        } else {
            let preprocessed = work.join(format!("{index}.i"));
            let assembly = work.join(format!("{index}.s"));
            run("cc", &["-E", "-P", "-I", "tools", source.to_str().unwrap(), "-o", preprocessed.to_str().unwrap()], label)?;
            let mut args = flags.clone();
            args.extend(["-o", assembly.to_str().unwrap(), preprocessed.to_str().unwrap()]);
            run(compiler.to_str().unwrap(), &args, label)?;
            let mut text = fs::read_to_string(&assembly).map_err(|error| error.to_string())?;
            text.push_str("\t.align\t2, 0\n");
            fs::write(&assembly, text).map_err(|error| error.to_string())?;
            assemble(&assembly, &object, label)?;
        }
        objects.push(object);
    }
    let mut data = link_text(&objects, BASE + region.start, work, functions, label)?;
    let length = (region.end - region.start) as usize;
    if data.len() > length && data[length..].iter().all(|&byte| byte == 0) {
        data.truncate(length);
    }
    if data.len() != length {
        return Err(format!("generated {} bytes for a {length}-byte region", data.len()));
    }
    Ok(data)
}

fn on_path(command: &str) -> bool {
    std::env::var_os("PATH").map_or(false, |path| std::env::split_paths(&path).any(|dir| dir.join(command).is_file()))
}

fn compiler_path(flag: Option<String>, variable: &str, file: &str) -> PathBuf {
    if let Some(path) = flag.or_else(|| std::env::var(variable).ok()) {
        return PathBuf::from(path);
    }
    let root = repo_root();
    let sibling = root.parent().unwrap().join("agbcc").join(file);
    if sibling.is_file() {
        return sibling;
    }
    root.join("build/agbcc").join(file)
}

pub fn main(rom_path: &Path, only: Option<String>, agbcc: Option<String>, old_agbcc: Option<String>) -> ExitCode {
    let agbcc = compiler_path(agbcc, "AGBCC", "agbcc");
    let old_agbcc = compiler_path(old_agbcc, "OLD_AGBCC", "old_agbcc");
    let rom = match fs::read(rom_path) {
        Ok(rom) => rom,
        Err(_) => {
            eprintln!("ROM is unavailable: {}", rom_path.display());
            return ExitCode::from(2);
        }
    };
    if rom.len() != ROM_SIZE as usize {
        eprintln!("ROM has an unexpected size.");
        return ExitCode::from(2);
    }
    if rom_sha1(&rom) != EXPECTED_SHA1 {
        eprintln!("ROM hash does not match Zoids Legacy (USA).");
        return ExitCode::from(2);
    }
    for command in ["cc", "arm-none-eabi-as", "arm-none-eabi-ld", "arm-none-eabi-objcopy", "arm-none-eabi-objdump"] {
        if !on_path(command) {
            eprintln!("Required command is unavailable: {command}");
            return ExitCode::from(2);
        }
    }
    let all = match regions(&repo_root().join("regions.txt")) {
        Ok(all) => all,
        Err(error) => {
            eprintln!("{error}");
            return ExitCode::from(2);
        }
    };
    let selected: Vec<Region> = all.into_iter().filter(|region| only.as_ref().map_or(true, |name| &region.name == name)).collect();
    if selected.is_empty() {
        eprintln!("No region matches the selection.");
        return ExitCode::from(2);
    }
    let complete = if only.is_none() {
        match coverage(&selected) {
            Ok(result) => Some(result),
            Err(error) => {
                eprintln!("Coverage failed: {error}");
                return ExitCode::from(1);
            }
        }
    } else {
        None
    };
    let functions = match function_addresses() {
        Ok(functions) => functions,
        Err(error) => {
            eprintln!("{error}");
            return ExitCode::from(2);
        }
    };

    let temporary = std::env::temp_dir().join(format!("zoids-verify-c-{}", std::process::id()));
    let _ = fs::remove_dir_all(&temporary);
    if let Err(error) = fs::create_dir_all(&temporary) {
        eprintln!("{}: {error}", temporary.display());
        return ExitCode::from(2);
    }
    let next = AtomicUsize::new(0);
    let results: Mutex<Vec<Option<Result<(), String>>>> = Mutex::new(vec![None; selected.len()]);
    let workers = std::thread::available_parallelism().map_or(4, |count| count.get());
    std::thread::scope(|scope| {
        for _ in 0..workers {
            scope.spawn(|| loop {
                let index = next.fetch_add(1, Ordering::Relaxed);
                let Some(region) = selected.get(index) else { break };
                let work = temporary.join(&region.name);
                let outcome = fs::create_dir_all(&work)
                    .map_err(|error| error.to_string())
                    .and_then(|_| compile_region(region, &work, &agbcc, &old_agbcc, &functions))
                    .and_then(|data| {
                        if data == rom[region.start as usize..region.end as usize] {
                            Ok(())
                        } else {
                            Err("bytes differ".into())
                        }
                    });
                let _ = fs::remove_dir_all(&work);
                results.lock().unwrap()[index] = Some(outcome);
            });
        }
    });
    let _ = fs::remove_dir_all(&temporary);

    let results = results.into_inner().unwrap();
    let mut failures = 0;
    for (index, (region, outcome)) in selected.iter().zip(&results).enumerate() {
        match outcome.as_ref().unwrap() {
            Ok(()) => println!("PASS {}/{} {}", index + 1, selected.len(), region.name),
            Err(error) => {
                failures += 1;
                eprintln!("FAIL {}: {error}", region.name);
            }
        }
    }
    if failures > 0 {
        eprintln!("Verification failed for {failures} of {} regions.", selected.len());
        return ExitCode::from(1);
    }
    println!("Verification passed for {} regions.", selected.len());
    if let Some((owners, bytes)) = complete {
        println!("Known callable coverage: {owners}/{owners} owners, {bytes}/{bytes} bytes (100%).");
    }
    ExitCode::SUCCESS
}
