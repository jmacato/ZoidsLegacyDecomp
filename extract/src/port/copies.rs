//! Raw copies from ROM: InitializeEngine DMA, BiosCpuSet, BiosCpuFastSet, CopyBytes and QueueCopy with literal sources and lengths.

use serde_json::json;

use super::{area, bios, claim_outside_code, literal, resolve_at, Port};
use crate::basis::Basis;
use crate::rom::R;
use crate::run::Ctx;

const ENGINE: Basis = Basis::C(&[("src/engine/initialize_engine.c", "ad213d3d2d1b307abb8bc779e5c350589b8e92a3")]);
const COPY_BYTES: Basis = Basis::C(&[("src/runtime/copy_bytes.c", "e10e7e371495f3cc4a7382fdf8a91ee500a88795")]);
const QUEUE_COPY: Basis = Basis::C(&[
    ("src/graphics/queue_copy.c", "9f3482ebd43e0bafd38ec6fb0cc9bd5edfafa8b9"),
    ("src/graphics/process_transfer_queue.c", "bd3df7baf01ad4e5d00e43a241686352967859c7"),
]);
const CPU_FAST_SET: Basis = Basis::Bios("CpuFastSet (SWI 0x0C)");

pub const PORT: Port = Port { name: "copies", bases: &[ENGINE, COPY_BYTES, QUEUE_COPY, bios::CPU_SET, CPU_FAST_SET], run };

const BIOS_CPU_SET: u32 = 0x080E_CD2C;
const BIOS_CPU_FAST_SET: u32 = 0x080E_CD28;
const COPY_BYTES_ADDRESS: u32 = 0x080E_D038;
const QUEUE_COPY_ADDRESS: u32 = 0x0809_5208;

/// DMA3 writes in InitializeEngine: (source, destination, control).
const ENGINE_DMA: [(u32, u32, u32); 5] = [
    (0x0800_0104, 0x0300_007C, 0x8400_0080),
    (0x087A_09D8, 0x0300_0014, 0x8400_000E),
    (0x0800_04C8, 0x0300_0680, 0x8400_0080),
    (0x0800_0520, 0x0300_088C, 0x8400_0029),
    (0x0800_05AC, 0x0300_0930, 0x8400_0018),
];

fn dma_length(control: u32) -> R<u32> {
    if control & (3 << 23) != 0 {
        return Err(format!("DMA control 0x{control:08X} does not increment its source"));
    }
    let count = match control & 0xFFFF {
        0 => 0x10000,
        count => count,
    };
    Ok(count * if control & (1 << 26) != 0 { 4 } else { 2 })
}

/// CpuFastSet moves 8 words at a time, so the count rounds up to a multiple of 8.
fn cpu_fast_set_length(control: u32) -> (u32, bool) {
    let count = (control & 0x1F_FFFF).div_ceil(8) * 8;
    let fill = control & (1 << 24) != 0;
    (if fill { 4 } else { count * 4 }, fill)
}

fn copy(ctx: &Ctx, basis: Basis, how: &str, source: u32, destination: &str, target: Option<u32>, length: u32, reached: Vec<String>) -> R<()> {
    let target = target.map(area).unwrap_or("unknown");
    let format = crate::rom::NEUTRAL;
    let (id, new) = ctx.item("copy", source, basis, reached);
    if !new {
        return Ok(());
    }
    let overlaps = claim_outside_code(ctx.rom, source, length, format, id)?;
    ctx.count(id, "c_literal_length");
    ctx.set(
        id,
        json!({
            "via": how,
            "destination": destination,
            "destination_area": target,
            "length": length,
            "code_overlaps": overlaps.iter().map(|(start, end)| format!("0x{start:08X}..0x{end:08X}")).collect::<Vec<_>>(),
        }),
    );
    Ok(())
}

fn run(ctx: &Ctx) -> R<()> {
    for (source, destination, control) in ENGINE_DMA {
        let reached = ctx.roots.require(source)?;
        copy(ctx, ENGINE, "dma3", source, &format!("0x{destination:08X}"), Some(destination), dma_length(control)?, reached)?;
    }
    let sites: [(u32, usize, usize, usize, Basis, &str); 4] = [
        (BIOS_CPU_SET, 0, 1, 2, bios::CPU_SET, "cpu_set"),
        (BIOS_CPU_FAST_SET, 0, 1, 2, CPU_FAST_SET, "cpu_fast_set"),
        (COPY_BYTES_ADDRESS, 1, 0, 2, COPY_BYTES, "copy_bytes"),
        (QUEUE_COPY_ADDRESS, 0, 1, 2, QUEUE_COPY, "queue_copy"),
    ];
    for (callee, source_arg, destination_arg, length_arg, basis, how) in sites {
        for reference in ctx.roots.calls(callee, source_arg) {
            let Some(control) = reference.args.get(length_arg).and_then(|text| literal(text)) else { continue };
            let destination = reference.args.get(destination_arg).cloned().unwrap_or_default();
            let length = match how {
                "cpu_set" => {
                    let (length, fill) = bios::cpu_set_length(control);
                    if fill {
                        continue;
                    }
                    length
                }
                "cpu_fast_set" => {
                    let (length, fill) = cpu_fast_set_length(control);
                    if fill {
                        continue;
                    }
                    length
                }
                "queue_copy" => ((control & 0xFFFF) << 10 >> 11) * 2,
                _ => control,
            };
            if length == 0 {
                continue;
            }
            let target = resolve_at(&destination, reference, ctx.roots);
            copy(ctx, basis, how, reference.address, &destination, target, length, vec![reference.location()])?;
        }
    }
    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn lengths() {
        assert_eq!(dma_length(0x8400_0080).unwrap(), 0x200);
        assert_eq!(dma_length(0x8400_000E).unwrap(), 0x38);
        assert_eq!(cpu_fast_set_length(8), (32, false));
        assert_eq!(cpu_fast_set_length(0x40), (256, false));
        assert_eq!(cpu_fast_set_length(5), (32, false));
    }
}
