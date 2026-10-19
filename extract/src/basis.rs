//! What each port is a port of. C and matched asm files are pinned by SHA-1.

use std::collections::HashSet;
use std::fs;

use crate::{repo_root, sha1_hex, verify_c};

#[derive(Clone, Copy, Debug)]
pub enum Basis {
    /// Ported from these byte-matched C files (and headers), pinned by SHA-1.
    C(&'static [(&'static str, &'static str)]),
    /// Ported from these byte-matched assembly files, pinned by SHA-1.
    MatchedAsm(&'static [(&'static str, &'static str)]),
    /// Behavior of a GBA BIOS call; the decomp has no source for it.
    Bios(&'static str),
}

impl Basis {
    pub fn label(&self) -> String {
        match self {
            Basis::C(files) | Basis::MatchedAsm(files) => files.iter().map(|(path, _)| *path).collect::<Vec<_>>().join(","),
            Basis::Bios(call) => format!("bios:{call}"),
        }
    }

    pub fn kind(&self) -> &'static str {
        match self {
            Basis::C(_) => "c",
            Basis::MatchedAsm(_) => "asm",
            Basis::Bios(_) => "bios",
        }
    }

    /// Each pinned .c/.s file must be a matched region source and must still have the pinned SHA-1.
    pub fn check(&self, matched: &HashSet<String>) -> Result<(), String> {
        let files = match self {
            Basis::C(files) | Basis::MatchedAsm(files) => *files,
            Basis::Bios(_) => return Ok(()),
        };
        for (path, pin) in files {
            let relative = path.strip_prefix("src/").ok_or_else(|| format!("{path}: pins must be under src/"))?;
            if !relative.ends_with(".h") && !matched.contains(relative) {
                return Err(format!("{path} is not a matched region source"));
            }
            let text = fs::read(repo_root().join(path)).map_err(|error| format!("{path}: {error}"))?;
            let actual = sha1_hex(&text);
            if actual != *pin {
                return Err(format!("{path} changed (pinned {pin}, now {actual}); re-check the port"));
            }
        }
        Ok(())
    }
}

pub fn matched_sources() -> Result<HashSet<String>, String> {
    Ok(verify_c::regions(&repo_root().join("regions.txt"))?.into_iter().flat_map(|region| region.sources).collect())
}
