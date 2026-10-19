//! GBA BIOS calls used by the decomp to read ROM data. The decomp has no source for these.

use crate::basis::Basis;
use crate::rom::{Rom, R};

pub const LZ77_WRAM: Basis = Basis::Bios("LZ77UnCompWram (SWI 0x11)");
pub const LZ77_VRAM: Basis = Basis::Bios("LZ77UnCompVram (SWI 0x12)");
pub const CPU_SET: Basis = Basis::Bios("CpuSet (SWI 0x0B)");

/// Decode LZ77 type 0x10 data at `address`, claiming the bytes the BIOS reads.
/// `vram`: SWI 0x12 writes halfwords, so a back-reference to the byte just written reads stale data; that is a hard error here.
pub fn lz77(rom: &Rom, address: u32, item: usize, vram: bool) -> R<Vec<u8>> {
    lz77_from(&mut rom.cursor(address, "lz77", item), vram)
}

/// The same decode without claiming, to check another caller's mode.
pub fn lz77_dry(rom: &Rom, address: u32, vram: bool) -> R<Vec<u8>> {
    lz77_from(&mut rom.dry_cursor(address), vram)
}

/// The same decode without claiming; also returns the address after the last byte the BIOS reads.
pub fn lz77_dry_end(rom: &Rom, address: u32, vram: bool) -> R<(Vec<u8>, u32)> {
    let mut cursor = rom.dry_cursor(address);
    let decoded = lz77_from(&mut cursor, vram)?;
    Ok((decoded, cursor.address))
}

fn lz77_from(cursor: &mut crate::rom::Cursor, vram: bool) -> R<Vec<u8>> {
    let address = cursor.address;
    let header = cursor.u32()?;
    if header & 0xFF != 0x10 {
        return Err(format!("LZ77 at 0x{address:08X}: header type 0x{:02X} is not 0x10", header & 0xFF));
    }
    let size = (header >> 8) as usize;
    if size == 0 {
        return Err(format!("LZ77 at 0x{address:08X}: decoded size is 0"));
    }
    let mut out = Vec::with_capacity(size);
    while out.len() < size {
        let flags = cursor.u8()?;
        for bit in (0..8).rev() {
            if out.len() >= size {
                break;
            }
            if flags & (1 << bit) == 0 {
                out.push(cursor.u8()?);
                continue;
            }
            let first = cursor.u8()? as usize;
            let second = cursor.u8()? as usize;
            let length = (first >> 4) + 3;
            let distance = (((first & 0xF) << 8) | second) + 1;
            if distance > out.len() {
                return Err(format!("LZ77 at 0x{address:08X}: back-reference {distance} before the start of the output"));
            }
            if vram && distance == 1 {
                return Err(format!("LZ77 at 0x{address:08X}: VRAM decode with distance 1"));
            }
            if out.len() + length > size {
                return Err(format!("LZ77 at 0x{address:08X}: back-reference runs past the decoded size"));
            }
            for _ in 0..length {
                out.push(out[out.len() - distance]);
            }
        }
    }
    Ok(out)
}

/// CpuSet control word: (bytes read from the source, fill mode).
pub fn cpu_set_length(control: u32) -> (u32, bool) {
    let count = control & 0x1F_FFFF;
    let unit = if control & (1 << 26) != 0 { 4 } else { 2 };
    let fill = control & (1 << 24) != 0;
    (if fill { unit } else { count * unit }, fill)
}

#[cfg(test)]
mod tests {
    use super::*;

    fn rom_with(data: &[u8]) -> Rom {
        let mut bytes = vec![0u8; crate::ROM_SIZE as usize];
        bytes[0x100..0x100 + data.len()].copy_from_slice(data);
        Rom::new(bytes, Vec::new())
    }

    #[test]
    fn literals_and_back_reference() {
        let rom = rom_with(&[0x10, 0x08, 0x00, 0x00, 0b0100_0000, b'a', 0x20, 0x00, b'b', b'c', b'd', b'e']);
        let out = lz77(&rom, crate::BASE + 0x100, 0, false).unwrap();
        assert_eq!(out, b"aaaaaabc");
    }

    #[test]
    fn rejects_other_types() {
        let rom = rom_with(&[0x20, 0x08, 0x00, 0x00]);
        assert!(lz77(&rom, crate::BASE + 0x100, 0, false).is_err());
    }

    #[test]
    fn vram_distance_one_is_an_error() {
        let rom = rom_with(&[0x10, 0x08, 0x00, 0x00, 0b0100_0000, b'a', 0x20, 0x00]);
        assert!(lz77(&rom, crate::BASE + 0x100, 0, true).is_err());
    }

    #[test]
    fn cpu_set_units() {
        assert_eq!(cpu_set_length(0x0400_0028), (0xA0, false));
        assert_eq!(cpu_set_length(0x0000_0010), (0x20, false));
        assert_eq!(cpu_set_length(0x0500_0010), (4, true));
    }
}
