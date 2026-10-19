mod basis;
mod image;
mod page;
mod port;
mod rom;
mod roots;
mod run;
mod thumb;
mod verify_c;

use std::fs;
use std::path::{Path, PathBuf};
use std::process::ExitCode;

use sha1::{Digest, Sha1};

pub const BASE: u32 = 0x0800_0000;
pub const ROM_SIZE: u32 = 0x0080_0000;
pub const EXPECTED_SHA1: &str = "460fa2158606097f6e6f63ce966d2d6ecdd58d70";

pub fn repo_root() -> PathBuf {
    match std::env::var_os("ZOIDS_ROOT") {
        Some(root) => PathBuf::from(root),
        None => Path::new(env!("CARGO_MANIFEST_DIR")).parent().unwrap().to_path_buf(),
    }
}

pub fn sha1_hex(data: &[u8]) -> String {
    Sha1::digest(data).iter().map(|byte| format!("{byte:02x}")).collect()
}

pub fn rom_sha1(rom: &[u8]) -> String {
    sha1_hex(rom)
}

fn usage() -> ExitCode {
    eprintln!("usage: zoids-extract verify-c --rom PATH [--region NAME] [--agbcc PATH] [--old-agbcc PATH]");
    eprintln!("       zoids-extract run --rom PATH --out DIR");
    eprintln!("       zoids-extract roots");
    eprintln!("       zoids-extract page --plan PLAN.json --out PAGE.html");
    ExitCode::from(2)
}

fn option(args: &[String], name: &str) -> Option<String> {
    args.iter().position(|arg| arg == name).and_then(|index| args.get(index + 1).cloned())
}

pub fn check_bases() -> Result<(), String> {
    let matched = basis::matched_sources()?;
    let mut errors = Vec::new();
    for port in port::ALL {
        for basis in port.bases {
            if let Err(error) = basis.check(&matched) {
                errors.push(format!("port {}: {error}", port.name));
            }
        }
    }
    if errors.is_empty() {
        Ok(())
    } else {
        Err(errors.join("\n"))
    }
}

fn extract(rom_path: &Path, out: &Path) -> Result<String, String> {
    let bytes = fs::read(rom_path).map_err(|error| format!("{}: {error}", rom_path.display()))?;
    if bytes.len() != ROM_SIZE as usize || rom_sha1(&bytes) != EXPECTED_SHA1 {
        return Err("ROM is not Zoids Legacy (USA).".into());
    }
    check_bases()?;
    let regions = verify_c::regions(&repo_root().join("regions.txt"))?;
    let code = verify_c::merged_spans(&regions)?;
    let rom = rom::Rom::new(bytes, code);
    let roots = roots::Roots::scan()?;
    if out.exists() {
        fs::remove_dir_all(out).map_err(|error| format!("{}: {error}", out.display()))?;
    }
    let ctx = run::Ctx::new(&rom, &roots, out);
    for port in port::ALL {
        (port.run)(&ctx).map_err(|error| format!("port {}: {error}", port.name))?;
    }
    ctx.finish()
}

fn print_roots() -> Result<(), String> {
    let roots = roots::Roots::scan()?;
    for reference in &roots.refs {
        println!(
            "0x{:08X}\t{}\t{}\t{}\t{}\t{}\t{}",
            reference.address,
            reference.location(),
            reference.callee.clone().unwrap_or_default(),
            reference.arg,
            if reference.direct { "direct" } else { "expr" },
            reference.via,
            reference.args.join(" | ")
        );
    }
    Ok(())
}

fn main() -> ExitCode {
    let args: Vec<String> = std::env::args().skip(1).collect();
    let Some(command) = args.first() else { return usage() };
    let result = match command.as_str() {
        "roots" => print_roots(),
        "page" => {
            let (Some(plan), Some(out)) = (option(&args, "--plan"), option(&args, "--out")) else { return usage() };
            page::build(Path::new(&plan), Path::new(&out)).map(|summary| print!("{summary}"))
        }
        "verify-c" | "run" => {
            let Some(rom) = option(&args, "--rom").map(PathBuf::from) else { return usage() };
            if command == "verify-c" {
                return verify_c::main(&rom, option(&args, "--region"), option(&args, "--agbcc"), option(&args, "--old-agbcc"));
            }
            let Some(out) = option(&args, "--out").map(PathBuf::from) else { return usage() };
            extract(&rom, &out).map(|summary| print!("{summary}"))
        }
        _ => return usage(),
    };
    match result {
        Ok(()) => ExitCode::SUCCESS,
        Err(error) => {
            eprintln!("error: {error}");
            ExitCode::from(1)
        }
    }
}

#[cfg(test)]
mod tests {
    #[test]
    fn bases_are_matched_and_pinned() {
        super::check_bases().unwrap();
    }
}
