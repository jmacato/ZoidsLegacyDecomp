//! ROM access. Every read claims its bytes under one format; a second format on the same byte is a hard error.

use std::cell::RefCell;

use crate::{BASE, ROM_SIZE};

pub type R<T> = Result<T, String>;

/// A raw copy moves bytes without interpreting them, so it yields to any other format.
pub const NEUTRAL: &str = "copy";

pub struct Claim {
    pub item: usize,
    pub start: u32,
    pub end: u32,
}

pub struct Rom {
    bytes: Vec<u8>,
    code: Vec<(u32, u32)>,
    owner: RefCell<Vec<u16>>,
    formats: RefCell<Vec<String>>,
    claims: RefCell<Vec<Claim>>,
}

impl Rom {
    pub fn new(bytes: Vec<u8>, code: Vec<(u32, u32)>) -> Rom {
        Rom {
            owner: RefCell::new(vec![0; bytes.len()]),
            bytes,
            code,
            formats: RefCell::new(vec![String::new()]),
            claims: RefCell::new(Vec::new()),
        }
    }

    pub fn is_data(&self, address: u32) -> bool {
        let Some(offset) = address.checked_sub(BASE).filter(|offset| *offset < ROM_SIZE) else { return false };
        !self.code.iter().any(|&(start, end)| start <= offset && offset < end)
    }

    pub fn code_spans(&self) -> &[(u32, u32)] {
        &self.code
    }

    fn format_id(&self, format: &str) -> u16 {
        let mut formats = self.formats.borrow_mut();
        if let Some(index) = formats.iter().position(|known| known == format) {
            return index as u16;
        }
        formats.push(format.to_string());
        (formats.len() - 1) as u16
    }

    pub fn format_name(&self, id: u16) -> String {
        self.formats.borrow()[id as usize].clone()
    }

    pub fn owners(&self) -> std::cell::Ref<'_, Vec<u16>> {
        self.owner.borrow()
    }

    pub fn claims(&self) -> std::cell::Ref<'_, Vec<Claim>> {
        self.claims.borrow()
    }

    /// Instruction bytes, for decoding matched code. Never claims and never returns data bytes.
    pub fn code_bytes(&self, address: u32, length: u32) -> R<&[u8]> {
        let offset = address.checked_sub(BASE).filter(|offset| offset + length <= ROM_SIZE).ok_or_else(|| format!("code read outside the ROM at 0x{address:08X}"))?;
        if !self.code.iter().any(|&(start, end)| start <= offset && offset + length <= end) {
            return Err(format!("0x{address:08X} is not matched code"));
        }
        Ok(&self.bytes[offset as usize..(offset + length) as usize])
    }

    /// The 4 bytes at `address` whether code or data, for reference scans. Never claims.
    pub fn scan_word(&self, address: u32) -> Option<u32> {
        let offset = address.checked_sub(BASE).filter(|offset| offset + 4 <= ROM_SIZE)? as usize;
        Some(u32::from_le_bytes([self.bytes[offset], self.bytes[offset + 1], self.bytes[offset + 2], self.bytes[offset + 3]]))
    }

    /// Read without claiming. Only for checks that do not consume data (for example "is this a terminator").
    pub fn peek(&self, address: u32, length: u32) -> R<&[u8]> {
        let offset = self.range(address, length)?;
        Ok(&self.bytes[offset..offset + length as usize])
    }

    fn range(&self, address: u32, length: u32) -> R<usize> {
        let offset = address.checked_sub(BASE).filter(|offset| *offset < ROM_SIZE).ok_or_else(|| format!("read outside the ROM at 0x{address:08X}"))?;
        if length == 0 || offset.checked_add(length).map_or(true, |end| end > ROM_SIZE) {
            return Err(format!("read of {length} bytes at 0x{address:08X} leaves the ROM"));
        }
        for &(start, end) in &self.code {
            if offset < end && start < offset + length {
                return Err(format!("read at 0x{address:08X}+{length} enters code 0x{:08X}..0x{:08X}", BASE + start, BASE + end));
            }
        }
        Ok(offset as usize)
    }

    pub fn claim(&self, address: u32, length: u32, format: &str, item: usize) -> R<&[u8]> {
        let offset = self.range(address, length)?;
        let id = self.format_id(format);
        let neutral = self.format_id(NEUTRAL);
        let mut owner = self.owner.borrow_mut();
        for index in offset..offset + length as usize {
            let current = owner[index];
            if id == neutral && current != 0 {
                continue;
            }
            if current != 0 && current != id && current != neutral {
                return Err(format!(
                    "byte 0x{:08X} is {} and also {format}",
                    BASE + index as u32,
                    self.formats.borrow()[current as usize]
                ));
            }
            owner[index] = id;
        }
        self.claims.borrow_mut().push(Claim { item, start: address, end: address + length });
        Ok(&self.bytes[offset..offset + length as usize])
    }

    pub fn cursor<'a>(&'a self, address: u32, format: &'a str, item: usize) -> Cursor<'a> {
        Cursor { rom: self, address, format, item, dry: false }
    }

    /// A cursor that reads without claiming, for trying a grammar.
    pub fn dry_cursor(&self, address: u32) -> Cursor<'_> {
        Cursor { rom: self, address, format: "", item: 0, dry: true }
    }
}

pub struct Cursor<'a> {
    pub rom: &'a Rom,
    pub address: u32,
    pub format: &'a str,
    pub item: usize,
    pub dry: bool,
}

impl<'a> Cursor<'a> {
    pub fn bytes(&mut self, length: u32) -> R<&'a [u8]> {
        if length == 0 {
            return Ok(&[]);
        }
        let data = if self.dry { self.rom.peek(self.address, length)? } else { self.rom.claim(self.address, length, self.format, self.item)? };
        self.address += length;
        Ok(data)
    }

    pub fn u8(&mut self) -> R<u8> {
        Ok(self.bytes(1)?[0])
    }

    pub fn u32(&mut self) -> R<u32> {
        let data = self.bytes(4)?;
        Ok(u32::from_le_bytes([data[0], data[1], data[2], data[3]]))
    }

    pub fn peek_u8(&self) -> R<u8> {
        Ok(self.rom.peek(self.address, 1)?[0])
    }

    pub fn with_format(&self, format: &'a str) -> Cursor<'a> {
        Cursor { rom: self.rom, address: self.address, format, item: self.item, dry: self.dry }
    }
}

pub fn le16(data: &[u8], offset: usize) -> u16 {
    u16::from_le_bytes([data[offset], data[offset + 1]])
}

pub fn le32(data: &[u8], offset: usize) -> u32 {
    u32::from_le_bytes([data[offset], data[offset + 1], data[offset + 2], data[offset + 3]])
}
