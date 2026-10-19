//! Sound-engine roots outside the MP2K walk: the mixer InitializeSoundEngine copies to IWRAM, the PSG wave-channel
//! volume table, and two referenced addresses no matched code reads as data.

use serde_json::json;

use super::{bios, claim_outside_code, Port};
use crate::basis::Basis;
use crate::rom::{R, NEUTRAL};
use crate::run::Ctx;

const SOUND_ENGINE_H: (&str, &str) = ("src/audio/sound_engine.h", "a2a857c55553e643e3253a09e82288e998425f72");

const MIXER_COPY: Basis = Basis::C(&[("src/audio/initialize_sound_engine.c", "083b9e694a1b538f5fb32b1ce02b652b8f5d7c93"), SOUND_ENGINE_H]);
const NOOP_CALLBACK: Basis = Basis::C(&[
    ("src/audio/initialize_sound_mixer_state.c", "893da6d35e0b0cfd61a193c4ea4fe3738a1cd9b1"),
    ("src/audio/configure_sound_mode.c", "c005f38512ae5b9401591d6bcbf597749ae5353c"),
    ("src/audio/initialize_psg_channels.c", "149752e2042a450fc7473c45da3704c01e88f444"),
    SOUND_ENGINE_H,
]);
const WAVE_VOLUMES: Basis = Basis::C(&[
    ("src/audio/update_psg_sound_channels.c", "605de5917e8eb8a3ded4c7350038d37d53c039bc"),
    ("src/audio/update_psg_channel_volume_and_pan.c", "6760cb21d51f5a75ff460c6631ea516d470aedd5"),
    SOUND_ENGINE_H,
]);
const EXTENDED: Basis = Basis::C(&[("src/audio/run_extended_music_command.c", "c4e6c70eeb868d6f823b0537647d44821f928463"), SOUND_ENGINE_H]);

pub const PORT: Port = Port { name: "audio_roots", bases: &[MIXER_COPY, NOOP_CALLBACK, WAVE_VOLUMES, EXTENDED, bios::CPU_SET], run };

/// InitializeSoundEngine: BiosCpuSet((s32)D_080EAB29 & ~1, SOUND_ENGINE_MIXER_RAM, SOUND_ENGINE_MIXER_COPY_CONTROL).
const MIXER_ENTRY: u32 = 0x080E_AB29;
const MIXER_RAM: u32 = 0x0300_7758;
const MIXER_COPY_CONTROL: u32 = 0x0400_00E0;
/// SOUND_NOOP_CALLBACK_THUMB_ENTRY.
const NOOP_ENTRY: u32 = 0x080E_CB79;
/// gPsgWaveChannelVolumes, indexed by PsgChannelState.envelope_volume for channel 3.
const PSG_WAVE_VOLUMES: u32 = 0x086A_33D4;
/// PSG_MAX_AMPLITUDE (sound_engine.h).
const PSG_MAX_AMPLITUDE: u32 = 0x0F;
/// gExtendedMusicCommandHandlers; the music port claims the entries its walked tracks select.
const EXTENDED_HANDLERS: u32 = 0x086A_3418;

fn mixer(ctx: &Ctx) -> R<()> {
    let source = MIXER_ENTRY & !1;
    let (length, fill) = bios::cpu_set_length(MIXER_COPY_CONTROL);
    if fill {
        return Err("SOUND_ENGINE_MIXER_COPY_CONTROL is a fill".into());
    }
    let (id, _) = ctx.item("copy", source, MIXER_COPY, ctx.roots.require(MIXER_ENTRY)?);
    let overlaps = claim_outside_code(ctx.rom, source, length, NEUTRAL, id)?;
    ctx.count(id, "c_constant:SOUND_ENGINE_MIXER_COPY_CONTROL (0xE0 words)");
    ctx.set(id, json!({
        "via": "cpu_set",
        "destination": "SOUND_ENGINE_MIXER_RAM",
        "destination_area": "iwram",
        "destination_address": format!("0x{MIXER_RAM:08X}"),
        "length": length,
        "code_overlaps": overlaps.iter().map(|(start, end)| format!("0x{start:08X}..0x{end:08X}")).collect::<Vec<_>>(),
        "note": "code run from IWRAM; no matched source decodes it",
    }));
    Ok(())
}

/// UpdatePsgSoundChannels reads it for channel 3, which plays the wave (type 3) voices the music port reaches.
/// UpdatePsgChannelVolumeAndPan clamps amplitude to PSG_MAX_AMPLITUDE when the channel plays on one side only;
/// envelope_volume runs between 0 and the amplitude (or the sustain level derived from it).
fn wave_volumes(ctx: &Ctx) -> R<()> {
    const KIND: &str = "table.psg_wave_channel_volumes";
    let waves = ctx.rom.owners().iter().any(|&owner| owner != 0 && ctx.rom.format_name(owner) == "mp2k.psg_wave");
    if !waves {
        return Err("the music port reached no wave-channel (type 3) voice, so nothing shows UpdatePsgSoundChannels reading channel 3's volume table".into());
    }
    let (id, _) = ctx.item(KIND, PSG_WAVE_VOLUMES, WAVE_VOLUMES, ctx.roots.require(PSG_WAVE_VOLUMES)?);
    let values = ctx.rom.claim(PSG_WAVE_VOLUMES, PSG_MAX_AMPLITUDE + 1, KIND, id)?.to_vec();
    ctx.count(
        id,
        "c_constant:PSG_MAX_AMPLITUDE + 1 (the one-sided branch of UpdatePsgChannelVolumeAndPan clamps the amplitude); the both-sides branch stores (volume_left + volume_right) >> 4 unclamped, so a higher envelope_volume is possible when the summed volumes reach 256; whether they do depends on runtime track volumes, which no port models; the 16 entries end at the next referenced address 0x086A33E4",
    );
    ctx.set(id, json!({ "entry_bytes": 1, "nr32_by_envelope_volume": values }));
    Ok(())
}

fn run(ctx: &Ctx) -> R<()> {
    mixer(ctx)?;
    wave_volumes(ctx)?;
    ctx.explain(
        NOOP_ENTRY,
        NOOP_CALLBACK,
        "SOUND_NOOP_CALLBACK_THUMB_ENTRY: a Thumb function entry (0x080ECB78 is outside every regions.txt region); InitializeSoundMixerState stores it in the update_psg_channels, stop_psg_channel, calculate_psg_frequency and reserved_callback fields and ConfigureSoundMode calls stop_psg_channel through CallFunctionR1; matched code only calls it, never reads it as data",
    )?;
    let read = {
        let owners = ctx.rom.owners();
        let start = (EXTENDED_HANDLERS - crate::BASE) as usize;
        owners[start..start + 0x100 * 4].iter().any(|&owner| owner != 0 && ctx.rom.format_name(owner) == "table.mp2k_extended_command_handlers")
    };
    if !read {
        ctx.explain(
            EXTENDED_HANDLERS,
            EXTENDED,
            "gExtendedMusicCommandHandlers: only RunExtendedMusicCommand reads it, indexed by a u8 track byte with no bound; no track the music port walks from gSongTable issues the extended command (MUSIC_HANDLER_EXTENDED_COMMAND), so matched code reads no entry",
        )?;
    }
    Ok(())
}
