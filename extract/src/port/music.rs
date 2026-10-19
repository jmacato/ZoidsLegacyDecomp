//! MP2K sound data: gMusicPlayerTable, gSongTable, song headers, track bytecode, voicegroups, samples and the driver tables.
//! Tracks run as m4a_mplay_main.s does, through the RAM command table that InitializeSoundMixerState copies and InitializePsgChannels patches.
//! AccessPlayerMemory conditions read player memory at runtime, so both outcomes are followed.

use std::cell::RefCell;
use std::collections::{BTreeMap, BTreeSet, HashMap, HashSet};

use serde_json::{json, Value};

use super::Port;
use crate::basis::Basis;
use crate::rom::{le16, le32, NEUTRAL, R};
use crate::run::Ctx;
use crate::verify_c::Region;
use crate::{repo_root, verify_c, BASE};

const SOUND_ENGINE_H: (&str, &str) = ("src/audio/sound_engine.h", "a2a857c55553e643e3253a09e82288e998425f72");
const COMMAND_TYPES_H: (&str, &str) = ("src/audio/mp2k_command_types.h", "052c4398f024788e50db2c8355337c50e9ce0489");
const PLY_NOTE: (&str, &str) = ("src/audio/m4a_ply_note.s", "7b2ee77e9506267de84e5636e30b81f2258e22d1");
const MPLAY_MAIN: (&str, &str) = ("src/audio/m4a_mplay_main.s", "bff4f0dda05feac393e7703bb8fa66c95c660b07");
const DISPATCH: (&str, &str) = ("src/audio/dispatch_music_callback_in_r3.c", "932ca67235d6227b1ef91cdfcb6a5bf2dfb3bd9b");
const TRACK_COMMANDS: (&str, &str) = ("src/audio/music_track_commands.c", "490ea4bdec8fcf5b3a5e038274e9c349f16a7649");
const MIXER_STATE: (&str, &str) = ("src/audio/initialize_sound_mixer_state.c", "893da6d35e0b0cfd61a193c4ea4fe3738a1cd9b1");
const SOUND_ENGINE: (&str, &str) = ("src/audio/initialize_sound_engine.c", "083b9e694a1b538f5fb32b1ce02b652b8f5d7c93");
const PCM_FREQUENCY: (&str, &str) = ("src/audio/calculate_pcm_playback_frequency.c", "a0ecfb4c058f4328b91b8f4807ee11c39344c318");
const BYTE_GUARD: (&str, &str) = ("src/audio/read_music_byte_into_r3_with_address_guard.c", "e36462849ca80a4f09363c0597e6d464f0487579");
const EXTENDED_COMMAND: (&str, &str) = ("src/audio/run_extended_music_command.c", "c4e6c70eeb868d6f823b0537647d44821f928463");

const PLAYERS: Basis = Basis::C(&[
    SOUND_ENGINE,
    ("src/audio/initialize_music_player.c", "011392fbc54be705a3ec3cfc9e98e07a7a5764a7"),
    ("src/audio/continue_all_music_players.c", "be29c9cdef7fa02adbcf0a08942918f5ea571e04"),
    ("src/audio/stop_all_music_players.c", "787a491592fa1c5fc7a14daea4bbae71383cbc21"),
    SOUND_ENGINE_H,
]);
const SONGS: Basis = Basis::C(&[
    ("src/audio/start_song.c", "681b4766d76a8890fbca101f74eb5ffd8bc56e49"),
    ("src/audio/start_or_continue_song_by_id.c", "2e5e29a168c43edb38e801cc5701df7043dad317"),
    ("src/audio/stop_and_continue_song.c", "91d9b7ac44367a1239bb8c23f98b7eecd7210fb2"),
    ("src/audio/song_player_controls.c", "65f031ff90bb96ecdb374a47b9171f96a0b0c9ef"),
    ("src/audio/initialize_song_tracks.c", "09f85687a6f44a8dcc08507103609e965d7da96b"),
]);
const SONG_HEADER: Basis = Basis::C(&[
    ("src/audio/start_music_player.c", "7756256a231b5f9740930a68ee4f27bca8ded618"),
    ("src/audio/configure_sound_mode.c", "c005f38512ae5b9401591d6bcbf597749ae5353c"),
    COMMAND_TYPES_H,
]);
const HANDLER_TABLE: Basis = Basis::C(&[
    ("src/audio/initialize_music_command_handlers.c", "2203a930ada377114590f43446a5958c584037d8"),
    BYTE_GUARD,
    MIXER_STATE,
    SOUND_ENGINE,
    ("src/audio/initialize_psg_channels.c", "149752e2042a450fc7473c45da3704c01e88f444"),
    SOUND_ENGINE_H,
]);
const EXTENDED_HANDLER_TABLE: Basis = Basis::C(&[EXTENDED_COMMAND]);
const SEQUENCER: Basis = Basis::MatchedAsm(&[
    MPLAY_MAIN,
    DISPATCH,
    ("src/audio/m4a_ply_fine.s", "dc51008aad35543c3f65a78aadf1d9bc8b50b4ae"),
    ("src/audio/m4a_read_u32.s", "0d09636d98b71056454c899e023400d5a0600288"),
    ("src/audio/m4a_repeat.s", "fbcb4de7142421b8d288ecca903cc4cdcf2fbd0e"),
    ("src/audio/m4a_ply_endtie.s", "fd752a8a4758045a4688f1b9c37d4dd7db5fdf0e"),
    PLY_NOTE,
    TRACK_COMMANDS,
    ("src/audio/music_command_return_from_pattern.c", "e4497c07ec2558a076d6c99c9963a494eaa65166"),
    ("src/audio/set_music_track_lfo_speed.c", "2fa327ff1ffef9231197f159d917b6664d7e95f8"),
    ("src/audio/set_music_track_modulation_depth.c", "f9bc90b074ec464e3a563be21be1d7dd921f277b"),
    ("src/audio/read_next_music_command_byte_into_r3_with_address_guard.c", "71f0f05b8e14315afd86921e1d70ddca15141bd0"),
    ("src/audio/read_next_music_command_byte_into_r3.c", "30715bf61e7390890258d7a8a8a75657a6b7bc6c"),
    BYTE_GUARD,
    ("src/audio/music_command_access_player_memory.c", "ff937bac2d94cee11bdab44e08b05683b44700d6"),
    EXTENDED_COMMAND,
    ("src/audio/set_music_track_tone_wave.c", "f5479f6ea7926f8b243370a3f97c4fd58824c0d0"),
    ("src/audio/music_command_set_track_tone_type.c", "e14433211bb95bfae724295bb7c5b604fde8bd26"),
    ("src/audio/music_command_set_track_tone_attack.c", "3a5dfb85c002d96084fb333f20e382817fce54e3"),
    ("src/audio/music_command_set_track_tone_decay.c", "21f6c266274ab329cd85748d3c2d610088a609d7"),
    ("src/audio/music_command_set_track_tone_sustain.c", "d1957d24222543e62e660ee7eaf2420f97aaa0e3"),
    ("src/audio/music_command_set_track_tone_release.c", "32363c5406453da84fdab11349f08d245abb5442"),
    ("src/audio/music_command_set_track_pseudo_echo_volume.c", "f31705222cabfbd2720c6933df9d0c57c315363a"),
    ("src/audio/music_command_set_track_pseudo_echo_length.c", "d29d0d234b7095280bffae47c8a84115540a35c3"),
    ("src/audio/music_command_set_track_tone_length.c", "19ed7b7215632bde7f53c6ad70d645151866f66f"),
    ("src/audio/music_command_set_track_tone_pan_sweep.c", "b3c965c22ee0a573642beed9701ed7a98ed5c6f0"),
    ("src/audio/music_command_end_track_via_callback.c", "964a303e80690c5e2f1c3e967f6f7312755a0baf"),
    ("src/runtime/call_function_r2.c", "146fdbe146d83770a54e4c41e1ab5bf818db6254"),
    ("src/audio/clear_music_state_prefix_via_callback.c", "2ebe62732e2e19ab945481db3e612807b01bd99e"),
    ("src/audio/clear_music_state_prefix64_bytes.c", "3f41cea4f5b0295ff9bf29eeca16173b6419e08f"),
    COMMAND_TYPES_H,
]);
const VOICES: Basis = Basis::MatchedAsm(&[PLY_NOTE, TRACK_COMMANDS, COMMAND_TYPES_H, SOUND_ENGINE_H]);
const CLOCK: Basis = Basis::MatchedAsm(&[MPLAY_MAIN, PLY_NOTE, DISPATCH]);
const PCM: Basis = Basis::C(&[PCM_FREQUENCY, SOUND_ENGINE_H]);
const PSG_WAVE: Basis = Basis::C(&[("src/audio/update_psg_sound_channels.c", "605de5917e8eb8a3ded4c7350038d37d53c039bc"), SOUND_ENGINE_H]);
const PSG_TABLES: Basis = Basis::C(&[("src/audio/calculate_psg_frequency_register.c", "782cdeec21bc3e4adec7623b0123d5a4bce0cb80"), SOUND_ENGINE_H]);
const SAMPLE_RATE: Basis = Basis::C(&[
    ("src/audio/configure_sound_sample_rate.c", "422f5973fbfdca510fd67728362a5790b10dbf85"),
    ("src/audio/configure_sound_mode.c", "c005f38512ae5b9401591d6bcbf597749ae5353c"),
    MIXER_STATE,
    SOUND_ENGINE,
    ("src/audio/initialize_audio.c", "8e8a1e14b3aff7fe401c008a54d056a8d7b0d4ee"),
    SOUND_ENGINE_H,
]);

pub const PORT: Port = Port {
    name: "music",
    bases: &[PLAYERS, SONGS, SONG_HEADER, HANDLER_TABLE, EXTENDED_HANDLER_TABLE, SEQUENCER, VOICES, CLOCK, PCM, PSG_WAVE, PSG_TABLES, SAMPLE_RATE],
    run,
};

const MUSIC_PLAYER_TABLE: u32 = 0x086A_4694;
const SONG_TABLE: u32 = 0x086A_46C4;
const COMMAND_TABLE: u32 = 0x086A_3170;
const EXTENDED_TABLE: u32 = 0x086A_3418;
const CLOCK_TABLE: u32 = 0x086A_33E4;
const PCM_KEY_CODES: u32 = 0x086A_3200;
const PCM_RATIOS: u32 = 0x086A_32B4;
const SAMPLE_RATES: u32 = 0x086A_32E4;
const PSG_KEY_CODES: u32 = 0x086A_32FC;
const PSG_CURVE: u32 = 0x086A_3380;
const PSG_NOISE: u32 = 0x086A_3398;

/// MUSIC_COMMAND_HANDLER_COUNT (InitializeMusicCommandHandlers: movs r1, #0x24).
const HANDLER_COUNT: u32 = 36;
/// Wait bytes 0x80..=0xB0 and note bytes 0xCF..=0xFF both index the clock table from 0.
const CLOCK_ENTRIES: u32 = 0xB0 - 0x80 + 1;
const PCM_MAX_KEY: u32 = 0xB2;
const PSG_TONE_MAX_INDEX: u32 = 0x82;
const PSG_NOISE_MAX_INDEX: u32 = 0x3B;
const MUSIC_PLAYER_MAX_TRACKS: u8 = 16;
/// InitializePsgChannels writes these slots after InitializeSoundMixerState copies the ROM table to 0x030074B0.
const PSG_PATCHES: [(usize, u32); 9] = [
    (8, 0x080E_C901),
    (17, 0x080E_B605),
    (19, 0x080E_B619),
    (28, 0x080E_CA59),
    (29, 0x080E_B59D),
    (30, 0x080E_BB9D),
    (31, 0x080E_B329),
    (32, 0x080E_BF65),
    (33, 0x080E_C02D),
];
/// Mode words that reach ConfigureSoundSampleRate from literal call sites (sound_engine.h names).
const SAMPLE_RATE_MODES: [(&str, u32); 3] = [("SOUND_INITIAL_SAMPLE_RATE_MODE", 0x0004_0000), ("SOUND_MODE_DEFAULT", 0x0099_E800), ("SOUND_MODE_GAME", 0x0095_F880)];
const STATE_LIMIT: usize = 4_000_000;

const TRACK: &str = "mp2k.track";
const TONE: &str = "mp2k.tone_data";

#[derive(Clone, Copy, Debug, PartialEq)]
enum Op {
    Fine,
    Goto,
    Pattern,
    PatternEnd,
    Repeat,
    Byte(&'static str),
    LoadTone,
    WriteIo,
    EndTie,
    AccessMemory,
    Extended,
}

const HANDLERS: &[(u32, Op, &str)] = &[
    (0x080E_AE91, Op::Fine, "audio/m4a_ply_fine.s"),
    (0x080E_AF01, Op::Goto, "audio/m4a_read_u32.s"),
    (0x080E_AF21, Op::Pattern, "audio/m4a_read_u32.s"),
    (0x080E_AF3D, Op::PatternEnd, "audio/music_command_return_from_pattern.c"),
    (0x080E_AF51, Op::Repeat, "audio/m4a_repeat.s"),
    (0x080E_AF81, Op::Byte("SetTrackPriority"), "audio/music_track_commands.c"),
    (0x080E_AF8D, Op::Byte("SetPlayerTempo"), "audio/music_track_commands.c"),
    (0x080E_AFA1, Op::Byte("SetTrackKeyShift"), "audio/music_track_commands.c"),
    (0x080E_AFB5, Op::LoadTone, "audio/music_track_commands.c"),
    (0x080E_AFE5, Op::Byte("SetTrackVolume"), "audio/music_track_commands.c"),
    (0x080E_AFF9, Op::Byte("SetTrackPan"), "audio/music_track_commands.c"),
    (0x080E_B00D, Op::Byte("SetTrackPitchBend"), "audio/music_track_commands.c"),
    (0x080E_B021, Op::Byte("SetTrackPitchBendRange"), "audio/music_track_commands.c"),
    (0x080E_B035, Op::Byte("SetTrackLfoDelay"), "audio/music_track_commands.c"),
    (0x080E_B041, Op::Byte("SetTrackModulationType"), "audio/music_track_commands.c"),
    (0x080E_B059, Op::Byte("SetTrackTuning"), "audio/music_track_commands.c"),
    (0x080E_B06D, Op::WriteIo, "audio/music_track_commands.c"),
    (0x080E_B605, Op::Byte("SetMusicTrackLfoSpeed"), "audio/set_music_track_lfo_speed.c"),
    (0x080E_B619, Op::Byte("SetMusicTrackModulationDepth"), "audio/set_music_track_modulation_depth.c"),
    (0x080E_B59D, Op::EndTie, "audio/m4a_ply_endtie.s"),
    (0x080E_C901, Op::AccessMemory, "audio/music_command_access_player_memory.c"),
    (0x080E_CA59, Op::Extended, "audio/run_extended_music_command.c"),
];

#[derive(Clone, Copy, Debug, PartialEq)]
enum Ext {
    /// Calls the RAM command table slot (gMusicTrackEndCallback is slot 0).
    Callback(usize),
    Wave,
    Tone(usize, &'static str),
    Byte(&'static str),
}

const EXTENDED: &[(u32, Ext, &str)] = &[
    (0x080E_CA79, Ext::Callback(0), "audio/music_command_end_track_via_callback.c"),
    (0x080E_CA8D, Ext::Wave, "audio/set_music_track_tone_wave.c"),
    (0x080E_CAD5, Ext::Tone(0, "SetTrackToneType"), "audio/music_command_set_track_tone_type.c"),
    (0x080E_CAE9, Ext::Tone(8, "SetTrackToneAttack"), "audio/music_command_set_track_tone_attack.c"),
    (0x080E_CAFD, Ext::Tone(9, "SetTrackToneDecay"), "audio/music_command_set_track_tone_decay.c"),
    (0x080E_CB11, Ext::Tone(10, "SetTrackToneSustain"), "audio/music_command_set_track_tone_sustain.c"),
    (0x080E_CB25, Ext::Tone(11, "SetTrackToneRelease"), "audio/music_command_set_track_tone_release.c"),
    (0x080E_CB39, Ext::Byte("SetTrackPseudoEchoVolume"), "audio/music_command_set_track_pseudo_echo_volume.c"),
    (0x080E_CB45, Ext::Byte("SetTrackPseudoEchoLength"), "audio/music_command_set_track_pseudo_echo_length.c"),
    (0x080E_CB51, Ext::Tone(2, "SetTrackToneLength"), "audio/music_command_set_track_tone_length.c"),
    (0x080E_CB65, Ext::Tone(3, "SetTrackTonePanSweep"), "audio/music_command_set_track_tone_pan_sweep.c"),
];

fn in_source(regions: &[Region], handler: u32, source: &str) -> bool {
    let offset = (handler & !1).wrapping_sub(BASE);
    handler & 1 == 1 && regions.iter().any(|region| region.start <= offset && offset < region.end && region.sources.iter().any(|name| name == source))
}

struct Driver {
    /// The RAM command table at 0x030074B0 after InitializePsgChannels.
    table: [u32; HANDLER_COUNT as usize],
    clock: [u8; CLOCK_ENTRIES as usize],
    regions: Vec<Region>,
    extended: RefCell<BTreeMap<u8, (u32, Ext)>>,
}

impl Driver {
    fn op(&self, slot: usize) -> R<Op> {
        let handler = self.table[slot];
        let (_, op, source) = HANDLERS.iter().find(|(address, _, _)| *address == handler).ok_or_else(|| format!("command table slot {slot}: handler 0x{handler:08X} is not a ported handler"))?;
        if !in_source(&self.regions, handler, source) {
            return Err(format!("command table slot {slot}: handler 0x{handler:08X} is not in a region of {source}"));
        }
        Ok(*op)
    }

    fn extended(&self, ctx: &Ctx, index: u8) -> R<Ext> {
        if let Some((_, ext)) = self.extended.borrow().get(&index) {
            return Ok(*ext);
        }
        let (item, _) = ctx.item("table.mp2k_extended_command_handlers", EXTENDED_TABLE, EXTENDED_HANDLER_TABLE, ctx.roots.require(EXTENDED_TABLE)?);
        let handler = le32(ctx.rom.claim(EXTENDED_TABLE + 4 * u32::from(index), 4, "table.mp2k_extended_command_handlers", item)?, 0);
        let (_, ext, source) = EXTENDED.iter().find(|(address, _, _)| *address == handler).ok_or_else(|| format!("extended command {index}: handler 0x{handler:08X} is not a ported handler"))?;
        if !in_source(&self.regions, handler, source) {
            return Err(format!("extended command {index}: handler 0x{handler:08X} is not in a region of {source}"));
        }
        self.extended.borrow_mut().insert(index, (handler, *ext));
        Ok(*ext)
    }
}

#[derive(Clone, PartialEq, Eq, Hash)]
struct State {
    pc: u32,
    running: u8,
    level: u8,
    stack: [u32; 3],
    repeat: u8,
    key: u8,
    tone: [u8; 12],
}

impl State {
    /// A track after StartMusicPlayer and the first m4a_mplay_main pass: the 64-byte clear, then tone.type = 1.
    fn start(pc: u32) -> State {
        let mut tone = [0; 12];
        tone[0] = 1;
        State { pc, running: 0, level: 0, stack: [0; 3], repeat: 0, key: 0, tone }
    }
}

#[derive(Default)]
struct Entry {
    bytes: [Option<u8>; 12],
    uses: BTreeSet<String>,
}

struct Group {
    item: usize,
    entries: BTreeMap<u32, Entry>,
    /// Program bytes LoadTrackTone used with this group as player->tone.
    programs: BTreeSet<u32>,
    /// Indexes m4a_ply_note selected here from a split tone (key or keysplit[key]).
    split: BTreeSet<u32>,
}

struct Keysplit {
    item: usize,
    keys: BTreeMap<u8, u8>,
    also_tone_data: BTreeSet<u8>,
}

#[derive(Default)]
struct TrackInfo {
    listing: BTreeMap<(u32, u8), String>,
    ends: BTreeSet<(&'static str, u32)>,
    /// Address after a command with no fallthrough -> the command.
    terminals: BTreeMap<u32, String>,
    /// Goto, Pattern, Repeat and memory-branch targets.
    targets: BTreeSet<u32>,
    songs: BTreeSet<u32>,
    voicegroups: BTreeSet<u32>,
    states: usize,
    memory_branches: usize,
}

#[derive(Default)]
struct Reach {
    pcm: bool,
    psg_tone: bool,
    psg_noise: bool,
}

struct Music<'a, 'b> {
    ctx: &'a Ctx<'b>,
    driver: Driver,
    claimed: RefCell<HashSet<(u32, u32, &'static str, usize)>>,
    groups: RefCell<BTreeMap<u32, Group>>,
    keysplits: RefCell<BTreeMap<u32, Keysplit>>,
    origins: RefCell<HashMap<[u8; 12], BTreeSet<String>>>,
    notes: RefCell<BTreeMap<([u8; 12], u8), String>>,
    tracks: RefCell<HashMap<usize, TrackInfo>>,
    reach: RefCell<Reach>,
    /// AccessPlayerMemory operations 0..5 write player->memory[index]: index -> first walked location.
    memory_writes: RefCell<BTreeMap<u8, String>>,
}

impl<'a, 'b> Music<'a, 'b> {
    fn new(ctx: &'a Ctx<'b>, driver: Driver) -> Self {
        Music {
            ctx,
            driver,
            claimed: RefCell::new(HashSet::new()),
            groups: RefCell::new(BTreeMap::new()),
            keysplits: RefCell::new(BTreeMap::new()),
            origins: RefCell::new(HashMap::new()),
            notes: RefCell::new(BTreeMap::new()),
            tracks: RefCell::new(HashMap::new()),
            reach: RefCell::new(Reach::default()),
            memory_writes: RefCell::new(BTreeMap::new()),
        }
    }

    /// Claim once per (range, format, item); later reads of the same range peek.
    fn read(&self, address: u32, length: u32, format: &'static str, item: usize) -> R<&'b [u8]> {
        if self.claimed.borrow_mut().insert((address, length, format, item)) {
            self.ctx.rom.claim(address, length, format, item)
        } else {
            self.ctx.rom.peek(address, length)
        }
    }

    fn group(&self, base: u32, reached: &str) -> R<usize> {
        if base % 4 != 0 || !self.ctx.rom.is_data(base) {
            return Err(format!("voicegroup 0x{base:08X} ({reached}) is not word-aligned ROM data; the ToneData words are read with ldr"));
        }
        let (item, _) = self.ctx.item("mp2k.voicegroup", base, VOICES, vec![reached.to_string()]);
        self.groups.borrow_mut().entry(base).or_insert_with(|| Group { item, entries: BTreeMap::new(), programs: BTreeSet::new(), split: BTreeSet::new() });
        Ok(item)
    }

    fn tone_bytes(&self, base: u32, index: u32, offset: u32, length: u32, used_as: String) -> R<&'b [u8]> {
        let item = self.groups.borrow()[&base].item;
        let address = base + 12 * index;
        let bytes = self.read(address + offset, length, TONE, item)?;
        let mut groups = self.groups.borrow_mut();
        let entry = groups.get_mut(&base).unwrap().entries.entry(index).or_default();
        for (at, byte) in bytes.iter().enumerate() {
            entry.bytes[offset as usize + at] = Some(*byte);
        }
        entry.uses.insert(used_as);
        Ok(bytes)
    }

    /// m4a_ply_note from the track tone to the channel: keysplit/rhythm lookup, then the wave the channel type reads.
    fn resolve(&self, tone: [u8; 12], key: u8) -> R<()> {
        let origins: Vec<String> = self.origins.borrow().get(&tone).map(|set| set.iter().cloned().collect()).unwrap_or_default();
        let from = origins.join(" ");
        let kind = tone[0];
        let (voice_type, wave, reached) = if kind & 0xC0 != 0 {
            let base = le32(&tone, 4);
            let index = if kind & 0x40 != 0 {
                let table = le32(&tone, 8);
                let (item, _) = self.ctx.item("mp2k.keysplit_table", table, VOICES, origins.clone());
                let value = self.ctx.rom.peek(table.wrapping_add(u32::from(key)), 1)?[0];
                self.keysplits.borrow_mut().entry(table).or_insert_with(|| Keysplit { item, keys: BTreeMap::new(), also_tone_data: BTreeSet::new() }).keys.insert(key, value);
                u32::from(value)
            } else {
                u32::from(key)
            };
            let used_as = if kind & 0x80 != 0 { format!("rhythm key {key}") } else { format!("keysplit key {key}") };
            self.group(base, &from)?;
            self.groups.borrow_mut().get_mut(&base).unwrap().split.insert(index);
            let sub_type = self.tone_bytes(base, index, 0, 1, used_as.clone())?[0];
            if sub_type & 0xC0 != 0 {
                self.tone_bytes(base, index, 0, 1, format!("{used_as}: nested split type, m4a_ply_note returns"))?;
                return Ok(());
            }
            if kind & 0x80 != 0 {
                self.tone_bytes(base, index, 3, 1, used_as.clone())?;
                self.tone_bytes(base, index, 1, 1, used_as.clone())?;
            }
            let wave = le32(self.tone_bytes(base, index, 4, 4, used_as.clone())?, 0);
            self.tone_bytes(base, index, 8, 4, used_as.clone())?;
            if sub_type & 7 != 0 {
                self.tone_bytes(base, index, 2, 2, used_as)?;
            }
            (sub_type, wave, vec![format!("mp2k.voicegroup@0x{base:08X}[{index}]")])
        } else {
            (kind, le32(&tone, 4), origins)
        };
        match voice_type & 7 {
            0 => {
                self.reach.borrow_mut().pcm = true;
                self.pcm_wave(wave, reached)
            }
            3 => {
                self.reach.borrow_mut().psg_tone = true;
                self.psg_wave(wave, reached)
            }
            1 | 2 => {
                self.reach.borrow_mut().psg_tone = true;
                Ok(())
            }
            4 => {
                self.reach.borrow_mut().psg_noise = true;
                Ok(())
            }
            other => Err(format!("tone type 0x{voice_type:02X} ({reached:?}): PSG channel {other} does not exist; m4a_ply_note would use psg_channels + {}", (other - 1) * 64)),
        }
    }

    /// Keysplit bytes are claimed after every ToneData read: m4a_ply_note reads table + key for any key,
    /// and below the table's first key that byte can be another voice's ToneData, read both ways.
    fn claim_keysplits(&self) -> R<()> {
        let mut keysplits = self.keysplits.borrow_mut();
        for (table, split) in keysplits.iter_mut() {
            for &key in split.keys.keys() {
                let at = table.wrapping_add(u32::from(key));
                let owner = self.ctx.rom.owners()[(at - BASE) as usize];
                if owner != 0 && self.ctx.rom.format_name(owner) == TONE {
                    split.also_tone_data.insert(key);
                    continue;
                }
                self.read(at, 1, "mp2k.keysplit_table", split.item)?;
            }
        }
        Ok(())
    }

    fn pcm_wave(&self, address: u32, reached: Vec<String>) -> R<()> {
        let ctx = self.ctx;
        if address % 4 != 0 || !ctx.rom.is_data(address) {
            return Err(format!("PCM wave 0x{address:08X} ({reached:?}) is not word-aligned ROM data; CalculatePcmPlaybackFrequency reads frequency_fixed10 with ldr"));
        }
        let (id, new) = ctx.item("mp2k.pcm_wave", address, PCM, reached);
        if !new {
            return Ok(());
        }
        let header = ctx.rom.claim(address, 16, "mp2k.pcm_wave_header", id)?;
        let frequency = le32(header, 4);
        let loop_start = le32(header, 8);
        let sample_count = le32(header, 12);
        let samples = if sample_count == 0 { &[][..] } else { ctx.rom.claim(address + 16, sample_count, "mp2k.pcm_samples", id)? };
        ctx.count(id, "header_field:PcmWaveHeader.sample_count");
        ctx.file(id, ".bin", samples)?;
        let rate = ((frequency + 512) >> 10).max(1);
        ctx.file(id, ".wav", &wav(samples, rate))?;
        if sample_count > 0 {
            ctx.view(id, json!({ "t": "wav", "samples": ["rom", address + 16, address + 16 + sample_count], "rate": rate }));
        }
        ctx.set(id, json!({
            "reserved00": le16(header, 0),
            "loop_flags": format!("0x{:04X}", le16(header, 2)),
            "frequency_fixed10": frequency,
            "loop_start": loop_start,
            "sample_count": sample_count,
            "matched_reader": "CalculatePcmPlaybackFrequency reads frequency_fixed10 only",
            "samples_reader": "PCM mixer at 0x080EAB28 (no decomp source); extent from PcmWaveHeader.sample_count",
            "wav_sample_rate": rate,
            "wav_sample_rate_basis": "frequency_fixed10 / 1024 from the field name in sound_engine.h; not checked against the mixer",
        }));
        Ok(())
    }

    fn psg_wave(&self, address: u32, reached: Vec<String>) -> R<()> {
        let ctx = self.ctx;
        if address % 4 != 0 || !ctx.rom.is_data(address) {
            return Err(format!("PSG wave 0x{address:08X} ({reached:?}) is not word-aligned ROM data; UpdatePsgSoundChannels reads it as u32"));
        }
        let (id, new) = ctx.item("mp2k.psg_wave", address, PSG_WAVE, reached);
        if !new {
            return Ok(());
        }
        let bytes = ctx.rom.claim(address, 16, "mp2k.psg_wave", id)?;
        ctx.count(id, "c_constant:4 words (UpdatePsgSoundChannels copies wave[0..3] to REG_WAVE_RAM0..3)");
        ctx.set(id, json!({ "bytes": bytes.iter().map(|byte| format!("{byte:02X}")).collect::<String>() }));
        Ok(())
    }
}

struct Walk<'m, 'a, 'b> {
    music: &'m Music<'a, 'b>,
    item: usize,
    start: u32,
    voicegroup: u32,
    song: u32,
    info: TrackInfo,
    forks: Vec<State>,
    loaded_tone: bool,
    /// Inside an AccessPlayerMemory condition, whose Goto has a fallthrough fork.
    conditional: bool,
}

impl Walk<'_, '_, '_> {
    fn byte(&self, address: u32) -> R<u8> {
        Ok(self.music.read(address, 1, TRACK, self.item)?[0])
    }

    fn word(&self, address: u32) -> R<u32> {
        Ok(le32(self.music.read(address, 4, TRACK, self.item)?, 0))
    }

    fn run(&mut self) -> R<()> {
        let mut seen: HashSet<State> = HashSet::new();
        let mut work = vec![State::start(self.start)];
        while let Some(mut state) = work.pop() {
            loop {
                if !seen.insert(state.clone()) {
                    self.info.ends.insert(("repeats_state", state.pc));
                    break;
                }
                if seen.len() > STATE_LIMIT {
                    return Err(format!("track 0x{:08X}: more than {STATE_LIMIT} sequencer states", self.start));
                }
                let stop = self.step(&mut state)?;
                work.append(&mut self.forks);
                if let Some(end) = stop {
                    self.info.ends.insert(end);
                    break;
                }
            }
        }
        self.info.states += seen.len();
        Ok(())
    }

    /// One pass of the m4a_mplay_main command loop at .L80EB17C.
    fn step(&mut self, state: &mut State) -> R<Option<(&'static str, u32)>> {
        let at = state.pc;
        let running = state.running;
        let byte = self.byte(at)?;
        let command = if byte < 0x80 {
            running
        } else {
            state.pc += 1;
            if byte >= 0xBD {
                state.running = byte;
            }
            byte
        };
        let mut text = if byte < 0x80 { format!("({command:02X})") } else { format!("{command:02X}") };
        let stop = if command >= 0xCF {
            self.note(state, command, at, &mut text)?;
            None
        } else if command > 0xB0 {
            self.dispatch(state, usize::from(command - 0xB1), at, &mut text)?
        } else if command >= 0x80 {
            text.push_str(&format!(" Wait {}", self.music.driver.clock[usize::from(command - 0x80)]));
            None
        } else {
            return Err(format!("track 0x{:08X}: data byte 0x{byte:02X} at 0x{at:08X} with no running status; the wait path would index the clock table at -0x80", self.start));
        };
        let slot = self.info.listing.entry((at, if byte < 0x80 { running } else { 0 })).or_default();
        if text.len() > slot.len() {
            *slot = text;
        }
        Ok(stop)
    }

    fn note(&mut self, state: &mut State, command: u8, at: u32, text: &mut String) -> R<()> {
        text.push_str(&format!(" Note {}", self.music.driver.clock[usize::from(command - 0xCF)]));
        let key = self.byte(state.pc)?;
        if key < 0x80 {
            state.key = key;
            state.pc += 1;
            text.push_str(&format!(" key {key}"));
            let velocity = self.byte(state.pc)?;
            if velocity < 0x80 {
                state.pc += 1;
                text.push_str(&format!(" velocity {velocity}"));
                let extra = self.byte(state.pc)?;
                if extra < 0x80 {
                    state.pc += 1;
                    text.push_str(&format!(" gate +{extra}"));
                }
            }
        }
        let key = if state.tone[0] & 0xC0 != 0 { state.key } else { 0 };
        let first = format!("mp2k.track@0x{:08X}:0x{at:08X}", self.start);
        self.music.notes.borrow_mut().entry((state.tone, key)).or_insert(first);
        Ok(())
    }

    fn dispatch(&mut self, state: &mut State, slot: usize, at: u32, text: &mut String) -> R<Option<(&'static str, u32)>> {
        let op = self.music.driver.op(slot)?;
        match op {
            Op::Fine => {
                text.push_str(" Fine");
                self.info.terminals.insert(state.pc, format!("Fine at 0x{at:08X}"));
                return Ok(Some(("fine", at)));
            }
            Op::Goto => {
                let target = self.word(state.pc)?;
                text.push_str(&format!(" Goto 0x{target:08X}"));
                if !self.conditional {
                    self.info.terminals.insert(state.pc + 4, format!("Goto 0x{target:08X} at 0x{at:08X}"));
                }
                self.info.targets.insert(target);
                state.pc = target;
            }
            Op::Pattern => {
                if state.level >= 3 {
                    text.push_str(" Pattern (stack full: m4a_ply_fine)");
                    self.info.terminals.insert(state.pc, format!("Pattern with a full stack (m4a_ply_fine) at 0x{at:08X}"));
                    return Ok(Some(("pattern_stack_full", at)));
                }
                let target = self.word(state.pc)?;
                text.push_str(&format!(" Pattern 0x{target:08X}"));
                self.info.targets.insert(target);
                state.stack[usize::from(state.level)] = state.pc + 4;
                state.level += 1;
                state.pc = target;
            }
            Op::PatternEnd => {
                text.push_str(" PatternEnd");
                if state.level != 0 {
                    state.level -= 1;
                    let level = usize::from(state.level);
                    state.pc = state.stack[level];
                    // Slots at or above the level are written before they are read again.
                    state.stack[level] = 0;
                }
            }
            Op::Repeat => {
                let count = self.byte(state.pc)?;
                text.push_str(&format!(" Repeat {count}"));
                if count == 0 {
                    state.pc = self.word(state.pc + 1)?;
                    self.info.targets.insert(state.pc);
                    text.push_str(&format!(" 0x{:08X}", state.pc));
                } else {
                    let next = u32::from(state.repeat) + 1;
                    state.repeat = next as u8;
                    if next < u32::from(count) {
                        state.pc = self.word(state.pc + 1)?;
                        self.info.targets.insert(state.pc);
                        text.push_str(&format!(" 0x{:08X}", state.pc));
                    } else {
                        state.repeat = 0;
                        state.pc += 5;
                    }
                }
            }
            Op::Byte(name) => {
                let value = self.byte(state.pc)?;
                state.pc += 1;
                text.push_str(&format!(" {name} {value}"));
            }
            Op::WriteIo => {
                let register = self.byte(state.pc)?;
                let value = self.byte(state.pc + 1)?;
                state.pc += 2;
                text.push_str(&format!(" WriteIoRegister 0x{:08X} {value}", 0x0400_0060 + u32::from(register)));
            }
            Op::LoadTone => {
                let program = self.byte(state.pc)?;
                state.pc += 1;
                text.push_str(&format!(" LoadTrackTone {program}"));
                let reached = format!("mp2k.song@0x{:08X}", self.song);
                self.music.group(self.voicegroup, &reached)?;
                let bytes = self.music.tone_bytes(self.voicegroup, u32::from(program), 0, 12, format!("LoadTrackTone from {reached}"))?;
                self.music.groups.borrow_mut().get_mut(&self.voicegroup).unwrap().programs.insert(u32::from(program));
                state.tone.copy_from_slice(bytes);
                self.music.origins.borrow_mut().entry(state.tone).or_default().insert(format!("mp2k.voicegroup@0x{:08X}[{program}]", self.voicegroup));
                self.info.voicegroups.insert(self.voicegroup);
                self.loaded_tone = true;
            }
            Op::EndTie => {
                text.push_str(" EndTie");
                let key = self.byte(state.pc)?;
                if key < 0x80 {
                    state.key = key;
                    state.pc += 1;
                    text.push_str(&format!(" key {key}"));
                }
            }
            Op::AccessMemory => {
                let operation = self.byte(state.pc)?;
                let index = self.byte(state.pc + 1)?;
                let operand = self.byte(state.pc + 2)?;
                state.pc += 3;
                text.push_str(&format!(" AccessPlayerMemory {operation} [{index}] {operand}"));
                if operation <= 5 {
                    self.music.memory_writes.borrow_mut().entry(index).or_insert_with(|| format!("mp2k.track@0x{:08X}:0x{at:08X}", self.start));
                }
                if (6..=17).contains(&operation) {
                    self.info.memory_branches += 1;
                    let mut skip = state.clone();
                    skip.pc += 4;
                    self.info.targets.insert(skip.pc);
                    self.forks.push(skip);
                    text.push_str(" ->");
                    self.conditional = true;
                    let stop = self.dispatch(state, 1, at, text);
                    self.conditional = false;
                    return stop;
                }
            }
            Op::Extended => {
                let index = self.byte(state.pc)?;
                state.pc += 1;
                text.push_str(&format!(" RunExtendedMusicCommand {index}"));
                match self.music.driver.extended(self.music.ctx, index)? {
                    Ext::Callback(slot) => {
                        text.push_str(" ->");
                        return self.dispatch(state, slot, at, text);
                    }
                    Ext::Wave => {
                        let bytes = self.music.read(state.pc, 4, TRACK, self.item)?;
                        state.tone[4..8].copy_from_slice(bytes);
                        state.pc += 4;
                        text.push_str(&format!(" SetMusicTrackToneWave 0x{:08X}", le32(bytes, 0)));
                        self.tone_changed(state.tone, at);
                    }
                    Ext::Tone(offset, name) => {
                        let value = self.byte(state.pc)?;
                        state.tone[offset] = value;
                        state.pc += 1;
                        text.push_str(&format!(" {name} {value}"));
                        self.tone_changed(state.tone, at);
                    }
                    Ext::Byte(name) => {
                        let value = self.byte(state.pc)?;
                        state.pc += 1;
                        text.push_str(&format!(" {name} {value}"));
                    }
                }
            }
        }
        Ok(None)
    }

    fn tone_changed(&self, tone: [u8; 12], at: u32) {
        self.music.origins.borrow_mut().entry(tone).or_default().insert(format!("mp2k.track@0x{:08X}:0x{at:08X}", self.start));
    }
}

fn wav(samples: &[u8], rate: u32) -> Vec<u8> {
    let length = samples.len() as u32;
    let mut out = Vec::with_capacity(46 + samples.len());
    out.extend_from_slice(b"RIFF");
    out.extend_from_slice(&(36 + length + (length & 1)).to_le_bytes());
    out.extend_from_slice(b"WAVEfmt ");
    out.extend_from_slice(&16u32.to_le_bytes());
    out.extend_from_slice(&1u16.to_le_bytes());
    out.extend_from_slice(&1u16.to_le_bytes());
    out.extend_from_slice(&rate.to_le_bytes());
    out.extend_from_slice(&rate.to_le_bytes());
    out.extend_from_slice(&1u16.to_le_bytes());
    out.extend_from_slice(&8u16.to_le_bytes());
    out.extend_from_slice(b"data");
    out.extend_from_slice(&length.to_le_bytes());
    out.extend(samples.iter().map(|sample| sample ^ 0x80));
    if length & 1 == 1 {
        out.push(0);
    }
    out
}

fn hex(value: u32) -> String {
    format!("0x{value:08X}")
}

fn load_driver(ctx: &Ctx) -> R<Driver> {
    let regions = verify_c::regions(&repo_root().join("regions.txt"))?;
    let (id, _) = ctx.item("table.mp2k_command_handlers", COMMAND_TABLE, HANDLER_TABLE, ctx.roots.require(COMMAND_TABLE)?);
    let mut table = [0u32; HANDLER_COUNT as usize];
    for (slot, handler) in table.iter_mut().enumerate() {
        *handler = le32(ctx.rom.claim(COMMAND_TABLE + 4 * slot as u32, 4, "table.mp2k_command_handlers", id)?, 0);
    }
    let rom_table: Vec<String> = table.iter().map(|handler| hex(*handler)).collect();
    for (slot, handler) in PSG_PATCHES {
        table[slot] = handler;
    }
    ctx.count(id, "c_constant:MUSIC_COMMAND_HANDLER_COUNT");
    ctx.set(id, json!({
        "rom": rom_table,
        "ram_0x030074B0_after_initialize_psg_channels": table.iter().map(|handler| hex(*handler)).collect::<Vec<_>>(),
        "track_bytes": "0xB1..0xCE use slots 0..29",
    }));

    let (clock_id, _) = ctx.item("table.mp2k_clock", CLOCK_TABLE, CLOCK, ctx.roots.require(CLOCK_TABLE)?);
    let mut clock = [0u8; CLOCK_ENTRIES as usize];
    clock.copy_from_slice(ctx.rom.claim(CLOCK_TABLE, CLOCK_ENTRIES, "table.mp2k_clock", clock_id)?);
    ctx.count(clock_id, "c_constant:wait bytes 0x80..0xB0 and note bytes 0xCF..0xFF (m4a_mplay_main.s, m4a_ply_note.s)");
    ctx.set(clock_id, json!({ "clocks": clock.to_vec() }));

    Ok(Driver { table, clock, regions, extended: RefCell::new(BTreeMap::new()) })
}

/// MusicPlayerDefinition entries; returns each player's trackCount after InitializeMusicPlayer's clamp, and the player addresses.
fn players(ctx: &Ctx, pending: &mut Vec<Pending>) -> R<(Vec<u8>, Vec<u32>)> {
    let count = *ctx.roots.symbols.get("gMusicPlayerCount").ok_or("gMusicPlayerCount is not in symbols.ld")?;
    let (id, _) = ctx.item("table.music_players", MUSIC_PLAYER_TABLE, PLAYERS, ctx.roots.require(MUSIC_PLAYER_TABLE)?);
    let format = "table.music_players";
    let mut out = Vec::new();
    let mut states = Vec::new();
    let mut entries = Vec::new();
    for index in 0..count {
        let entry = MUSIC_PLAYER_TABLE + 12 * index;
        let player = le32(ctx.rom.claim(entry, 4, format, id)?, 0);
        let tracks = le32(ctx.rom.claim(entry + 4, 4, format, id)?, 0);
        let track_count = ctx.rom.claim(entry + 8, 1, format, id)?[0];
        let priority_check = le16(ctx.rom.claim(entry + 10, 2, format, id)?, 0);
        states.push(player);
        pending.push(Pending {
            item: id,
            start: entry + 9,
            end: entry + 10,
            reason: format!("gMusicPlayerTable[{index}] +9 (MusicPlayerDefinition.reserved09, sound_engine.h): InitializeSoundEngine reads player (+0 word), tracks (+4 word), track_count (+8, u8 *) and priority_check_enabled (+10, u16 *); ContinueAllMusicPlayers, StopAllMusicPlayers, InitializeSongTracks, StartSongById, StartSongIfChanged, StartOrContinueSongById, StopSongById, ContinueSongById, IsSongPlayerStopped, IsMusicPlayerStopped, SetSongVolume and FadeOutSong read only the player word at +0"),
        });
        if track_count == 0 {
            return Err(format!("music player {index}: track_count 0; InitializeMusicPlayer leaves it uninitialized"));
        }
        let used = track_count.min(MUSIC_PLAYER_MAX_TRACKS);
        out.push(used);
        entries.push(json!({ "player": hex(player), "tracks": hex(tracks), "track_count": track_count, "track_count_used": used, "priority_check_enabled": priority_check }));
    }
    ctx.count(id, "c_constant:gMusicPlayerCount");
    ctx.set(id, json!({ "players": entries }));
    Ok((out, states))
}

/// gSongTable entries (song_header, player_index). Returns header -> (song ids, players).
fn songs(ctx: &Ctx, players: &[u8], pending: &mut Vec<Pending>) -> R<BTreeMap<u32, (Vec<u32>, BTreeSet<u16>)>> {
    let (id, _) = ctx.item("table.songs", SONG_TABLE, SONGS, ctx.roots.require(SONG_TABLE)?);
    let next_root = ctx.roots.by_address().range(SONG_TABLE + 1..).next().map(|(address, _)| *address).ok_or("no root after gSongTable")?;
    let mut bound = next_root;
    let mut headers: BTreeMap<u32, (Vec<u32>, BTreeSet<u16>)> = BTreeMap::new();
    let mut entries = Vec::new();
    let mut index = 0u32;
    while SONG_TABLE + 8 * (index + 1) <= bound {
        let entry = SONG_TABLE + 8 * index;
        let header = le32(ctx.rom.claim(entry, 4, "table.songs", id)?, 0);
        let player = le16(ctx.rom.claim(entry + 4, 2, "table.songs", id)?, 0);
        pending.push(Pending {
            item: id,
            start: entry + 6,
            end: entry + 8,
            reason: format!("gSongTable[{index}] +6..7 (SongEntry.unused, start_or_continue_song_by_id.c): StartSongById, StartSongIfChanged, StartOrContinueSongById, StopSongById, ContinueSongById, IsSongPlayerStopped, SetSongVolume and FadeOutSong read song_header (+0, s32) and player_index (+4, u16); InitializeSongTracks reads the u16 at song_id * 8 + MUSIC_SONG_OFFSET(player_index)"),
        });
        if usize::from(player) >= players.len() {
            return Err(format!("song {index}: player_index {player} is past gMusicPlayerTable"));
        }
        if !ctx.rom.is_data(header) {
            return Err(format!("song {index}: header 0x{header:08X} is not ROM data"));
        }
        if header > entry {
            bound = bound.min(header);
        }
        let slot = headers.entry(header).or_default();
        slot.0.push(index);
        slot.1.insert(player);
        entries.push(json!({ "song_header": hex(header), "player_index": player }));
        index += 1;
    }
    ctx.count(id, &format!("next_root:lowest song header address read from the table (0x{bound:08X}); the code does not bound song_id and the next decomp-referenced address is 0x{next_root:08X}"));
    ctx.set(id, json!({ "songs": entries, "unread_bytes_per_entry": "6..8 (SongEntry.unused in start_or_continue_song_by_id.c; no code reads it)" }));
    Ok(headers)
}

fn claim_tables(ctx: &Ctx, reach: &Reach, pending: &mut Vec<Pending>) -> R<()> {
    let (rates, _) = ctx.item("table.sound_sample_rates", SAMPLE_RATES, SAMPLE_RATE, ctx.roots.require(SAMPLE_RATES)?);
    let mut read = Vec::new();
    for (name, mode) in SAMPLE_RATE_MODES {
        let index = (mode & 0xF_0000) >> 16;
        if index == 0 {
            return Err(format!("{name} has no sample frequency bits"));
        }
        let samples = le16(ctx.rom.claim(SAMPLE_RATES + 2 * (index - 1), 2, "table.sound_sample_rates", rates)?, 0);
        read.push(json!({ "mode": name, "frequency_index": index, "entry": index - 1, "samples_per_vblank": samples }));
    }
    ctx.count(rates, "c_literal:SOUND_INITIAL_SAMPLE_RATE_MODE,SOUND_MODE_DEFAULT,SOUND_MODE_GAME (the 0xF0000 mask allows 15 entries, which would overlap PSG_KEY_FREQUENCY_CODES_ROM)");
    ctx.set(rates, json!({ "entries_read": read }));
    let read_entries: BTreeSet<u32> = SAMPLE_RATE_MODES.iter().map(|(_, mode)| ((mode & 0xF_0000) >> 16) - 1).collect();
    let next_root = ctx.roots.by_address().range(SAMPLE_RATES + 1..).next().map(|(address, _)| *address).ok_or("no root after SOUND_SAMPLE_RATE_TABLE")?;
    let modes: Vec<String> = SAMPLE_RATE_MODES.iter().map(|(name, mode)| format!("{name} 0x{mode:X} -> entry {}", ((mode & 0xF_0000) >> 16) - 1)).collect();
    for entry in 0..(next_root - SAMPLE_RATES) / 2 {
        if read_entries.contains(&entry) {
            continue;
        }
        pending.push(Pending {
            item: rates,
            start: SAMPLE_RATES + 2 * entry,
            end: SAMPLE_RATES + 2 * entry + 2,
            reason: format!(
                "SOUND_SAMPLE_RATE_TABLE entry {entry} (frequency index {}), before the next referenced address 0x{next_root:08X}: ConfigureSoundSampleRate reads entry ((mode & 0xF0000) >> 16) - 1; its matched callers pass {} (InitializeSoundMixerState passes the first; ConfigureSoundMode calls it only when mode & SOUND_MODE_SAMPLE_FREQUENCY_MASK != 0, from InitializeSoundEngine and InitializeAudio with the other two, and StartMusicPlayer passes the u8 song[3], which has no bits in 0xF0000); InitializePsgChannels stores it in RAM command slot MUSIC_HANDLER_SAMPLE_RATE (30), which no matched dispatcher selects (m4a_mplay_main.s maps track bytes 0xB1..0xCE to slots 0..29, MusicCommandEndTrackViaCallback calls slot 0, MusicCommandAccessPlayerMemory calls slot 1)",
                entry + 1,
                modes.join(", ")
            ),
        });
    }

    if reach.pcm {
        let (codes_id, _) = ctx.item("table.pcm_key_frequency_codes", PCM_KEY_CODES, PCM, ctx.roots.require(PCM_KEY_CODES)?);
        let codes = ctx.rom.claim(PCM_KEY_CODES, PCM_MAX_KEY + 2, "table.pcm_key_frequency_codes", codes_id)?;
        ctx.count(codes_id, "c_constant:PCM_MAX_KEY (+1 for the next key)");
        ctx.set(codes_id, json!({ "codes": codes.to_vec() }));
        let (ratios_id, _) = ctx.item("table.pcm_frequency_ratios", PCM_RATIOS, PCM, ctx.roots.require(PCM_RATIOS)?);
        let mut ratios = BTreeMap::new();
        for index in codes.iter().map(|code| u32::from(code & 0xF)).collect::<BTreeSet<_>>() {
            ratios.insert(index.to_string(), le32(ctx.rom.claim(PCM_RATIOS + 4 * index, 4, "table.pcm_frequency_ratios", ratios_id)?, 0));
        }
        ctx.count(ratios_id, "c_index:gPcmKeyFrequencyCodes values & 0xF");
        ctx.set(ratios_id, json!({ "ratios": ratios }));
    }
    if reach.psg_tone {
        let (codes_id, _) = ctx.item("table.psg_key_frequency_codes", PSG_KEY_CODES, PSG_TABLES, ctx.roots.require(PSG_KEY_CODES)?);
        let codes = ctx.rom.claim(PSG_KEY_CODES, PSG_TONE_MAX_INDEX + 2, "table.psg_key_frequency_codes", codes_id)?;
        ctx.count(codes_id, "c_constant:PSG_TONE_MAX_INDEX (+1 for the next key)");
        ctx.set(codes_id, json!({ "codes": codes.to_vec() }));
        let (curve_id, _) = ctx.item("table.psg_frequency_curve", PSG_CURVE, PSG_TABLES, ctx.roots.require(PSG_CURVE)?);
        let mut curve = BTreeMap::new();
        for index in codes.iter().map(|code| u32::from(code & 0xF)).collect::<BTreeSet<_>>() {
            curve.insert(index.to_string(), le16(ctx.rom.claim(PSG_CURVE + 2 * index, 2, "table.psg_frequency_curve", curve_id)?, 0) as i16);
        }
        ctx.count(curve_id, "c_index:PSG key frequency code values & 0xF");
        ctx.set(curve_id, json!({ "curve": curve }));
    }
    if reach.psg_noise {
        let (noise_id, _) = ctx.item("table.psg_noise_frequencies", PSG_NOISE, PSG_TABLES, ctx.roots.require(PSG_NOISE)?);
        let values = ctx.rom.claim(PSG_NOISE, PSG_NOISE_MAX_INDEX + 1, "table.psg_noise_frequencies", noise_id)?;
        ctx.count(noise_id, "c_constant:PSG_NOISE_MAX_INDEX");
        ctx.set(noise_id, json!({ "values": values.to_vec() }));
    }
    Ok(())
}

fn tone_fields(bytes: &[Option<u8>; 12]) -> Value {
    let word = |offset: usize| -> Option<u32> {
        let parts: Option<Vec<u8>> = bytes[offset..offset + 4].iter().copied().collect();
        parts.map(|parts| le32(&parts, 0))
    };
    let mut fields = json!({
        "type": bytes[0].map(|value| format!("0x{value:02X}")),
        "key": bytes[1],
        "length": bytes[2],
        "pan_sweep": bytes[3],
        "wave": word(4).map(hex),
    });
    let split = bytes[0].map_or(false, |kind| kind & 0x40 != 0);
    if split {
        fields["keysplit_table"] = json!(word(8).map(hex));
    } else {
        fields["attack"] = json!(bytes[8]);
        fields["decay"] = json!(bytes[9]);
        fields["sustain"] = json!(bytes[10]);
        fields["release"] = json!(bytes[11]);
    }
    fields
}

fn run(ctx: &Ctx) -> R<()> {
    let driver = load_driver(ctx)?;
    let mut pending = Vec::new();
    let (players, player_states) = players(ctx, &mut pending)?;
    let headers = songs(ctx, &players, &mut pending)?;
    let music = Music::new(ctx, driver);
    let mut walked: HashMap<(u32, u32), bool> = HashMap::new();

    for (&header, (ids, song_players)) in &headers {
        let reached: Vec<String> = ids.iter().map(|index| format!("table.songs@0x{SONG_TABLE:08X}[{index}]")).collect();
        let (song, _) = ctx.item("mp2k.song", header, SONG_HEADER, reached);
        let format = "mp2k.song_header";
        let track_count = ctx.rom.claim(header, 1, format, song)?[0];
        let priority = ctx.rom.claim(header + 2, 1, format, song)?[0];
        let reverb = ctx.rom.claim(header + 3, 1, format, song)?[0];
        let voicegroup = le32(ctx.rom.claim(header + 4, 4, NEUTRAL, song)?, 0);
        let limit = song_players.iter().map(|player| players[usize::from(*player)]).max().unwrap_or(0);
        let read = track_count.min(limit);
        let mut tracks = Vec::new();
        let mut dereferenced = false;
        for slot in 0..u32::from(read) {
            let pointer = le32(ctx.rom.claim(header + 8 + 4 * slot, 4, format, song)?, 0);
            tracks.push(hex(pointer));
            if !ctx.rom.is_data(pointer) {
                return Err(format!("song 0x{header:08X} track {slot}: 0x{pointer:08X} is not ROM data"));
            }
            let (item, _) = ctx.item(TRACK, pointer, SEQUENCER, vec![format!("mp2k.song@0x{header:08X}[{slot}]")]);
            music.tracks.borrow_mut().entry(item).or_default().songs.insert(header);
            if let Some(&loaded) = walked.get(&(pointer, voicegroup)) {
                if loaded {
                    music.group(voicegroup, &format!("mp2k.song@0x{header:08X}"))?;
                }
                dereferenced |= loaded;
                continue;
            }
            let mut walk = Walk { music: &music, item, start: pointer, voicegroup, song: header, info: TrackInfo::default(), forks: Vec::new(), loaded_tone: false, conditional: false };
            walk.run()?;
            walked.insert((pointer, voicegroup), walk.loaded_tone);
            dereferenced |= walk.loaded_tone;
            let mut all = music.tracks.borrow_mut();
            let info = all.get_mut(&item).unwrap();
            info.listing.append(&mut walk.info.listing);
            info.ends.append(&mut walk.info.ends);
            info.terminals.append(&mut walk.info.terminals);
            info.targets.append(&mut walk.info.targets);
            info.voicegroups.append(&mut walk.info.voicegroups);
            info.states += walk.info.states;
            info.memory_branches += walk.info.memory_branches;
        }
        if dereferenced {
            ctx.rom.claim(header + 4, 4, format, song)?;
        }
        pending.push(Pending { item: song, start: header + 1, end: header + 2, reason: "song header byte 1: StartMusicPlayer (start_music_player.c) reads song[0], song[2], song[3], the word at song+4 and the track words at song+8+4i; it stores the header in player->songHeader, which StartSongIfChanged, StartOrContinueSongById, StopSongById and ContinueSongById only compare with gSongTable entries".into() });
        if read < track_count {
            let counts: Vec<String> = song_players.iter().map(|player| format!("player {player}: {}", players[usize::from(*player)])).collect();
            pending.push(Pending {
                item: song,
                start: header + 8 + 4 * u32::from(read),
                end: header + 8 + 4 * u32::from(track_count),
                reason: format!("song header track word(s) {read}..{} of {track_count}: StartMusicPlayer copies the word at song+8+4i only while i < song[0] ({track_count}) and i < player[8], the MusicPlayerDefinition.track_count that InitializeMusicPlayer (its only writer) stores clamped to MUSIC_PLAYER_MAX_TRACKS; gSongTable assigns this header to {}", track_count - 1, counts.join(", ")),
            });
        }
        ctx.count(song, "header_field:track_count, limited by MusicPlayerDefinition.track_count (StartMusicPlayer loop bound)");
        ctx.set(song, json!({
            "track_count": track_count,
            "priority": priority,
            "reverb": format!("0x{reverb:02X}"),
            "reverb_calls_configure_sound_mode": reverb & 0x80 != 0,
            "voicegroup": hex(voicegroup),
            "voicegroup_dereferenced": dereferenced,
            "players": song_players.iter().collect::<Vec<_>>(),
            "tracks_read": read,
            "tracks": tracks,
            "unread": if read < track_count { format!("byte 1 and track words {read}..{} (declared.txt)", track_count - 1) } else { "byte 1 (declared.txt)".to_string() },
        }));
    }

    let notes: Vec<(([u8; 12], u8), String)> = music.notes.borrow().iter().map(|(note, first)| (*note, first.clone())).collect();
    for ((tone, key), first) in notes {
        music.resolve(tone, key).map_err(|error| {
            let origins = music.origins.borrow().get(&tone).map(|set| set.iter().cloned().collect::<Vec<_>>().join(" ")).unwrap_or_default();
            format!("{error} (note key {key} first at {first}, tone {tone:02X?} from {origins})")
        })?;
    }
    music.claim_keysplits()?;

    for (item, info) in music.tracks.borrow().iter() {
        let mut text = String::new();
        let mut addresses: HashMap<u32, usize> = HashMap::new();
        for ((at, _), line) in &info.listing {
            *addresses.entry(*at).or_default() += 1;
            text.push_str(&format!("0x{at:08X} {line}\n"));
        }
        let file = ctx.file(*item, ".txt", text.as_bytes())?;
        ctx.count(*item, "control_flow");
        ctx.set(*item, json!({
            "songs": info.songs.iter().map(|song| hex(*song)).collect::<Vec<_>>(),
            "voicegroups": info.voicegroups.iter().map(|group| hex(*group)).collect::<Vec<_>>(),
            "commands": info.listing.len(),
            "addresses_with_several_running_statuses": addresses.values().filter(|count| **count > 1).count(),
            "states": info.states,
            "memory_branches": info.memory_branches,
            "ends": info.ends.iter().map(|(reason, at)| json!([reason, hex(*at)])).collect::<Vec<_>>(),
            "listing": file,
        }));
    }

    for (base, group) in music.groups.borrow().iter() {
        let entries: Vec<Value> = group.entries.iter().map(|(index, entry)| json!({
            "index": index,
            "address": hex(base + 12 * index),
            "bytes": entry.bytes.iter().map(|byte| byte.map(|value| format!("{value:02X}")).unwrap_or_else(|| "..".into())).collect::<Vec<_>>().join(" "),
            "fields": tone_fields(&entry.bytes),
            "uses": entry.uses.iter().collect::<Vec<_>>(),
        })).collect();
        ctx.count(group.item, "reached_index:programs loaded by LoadTrackTone and keys played on split or rhythm tones");
        ctx.set(group.item, json!({ "entries": entries }));
    }
    for (table, split) in music.keysplits.borrow().iter() {
        ctx.count(split.item, "reached_index:keys played");
        ctx.set(split.item, json!({
            "table": hex(*table),
            "keys": split.keys.iter().map(|(key, index)| (key.to_string(), *index)).collect::<BTreeMap<_, _>>(),
            "keys_reading_tone_data": split.also_tone_data.iter().map(|key| json!({ "key": key, "address": hex(table + u32::from(*key)), "index": split.keys[key] })).collect::<Vec<_>>(),
        }));
    }

    if !music.driver.extended.borrow().is_empty() {
        let (item, _) = ctx.item("table.mp2k_extended_command_handlers", EXTENDED_TABLE, EXTENDED_HANDLER_TABLE, ctx.roots.require(EXTENDED_TABLE)?);
        let extended: Vec<Value> = music.driver.extended.borrow().iter().map(|(index, (handler, ext))| json!({ "index": index, "handler": hex(*handler), "op": format!("{ext:?}") })).collect();
        ctx.count(item, "reached_index:extended command bytes in walked tracks (RunExtendedMusicCommand does not bound the index)");
        ctx.set(item, json!({ "entries_read": extended }));
    }

    let reach = music.reach.borrow();
    claim_tables(ctx, &reach, &mut pending)?;
    declare(ctx, &music, pending, &player_states)
}

/// "0,5,7-16" for a set of indexes.
fn ranges(values: &BTreeSet<u32>) -> String {
    let mut parts: Vec<String> = Vec::new();
    let mut iter = values.iter().copied().peekable();
    while let Some(start) = iter.next() {
        let mut end = start;
        while iter.peek() == Some(&(end + 1)) {
            end = iter.next().unwrap();
        }
        parts.push(if start == end { start.to_string() } else { format!("{start}-{end}") });
    }
    if parts.is_empty() {
        "none".into()
    } else {
        parts.join(",")
    }
}

/// Bytes the music port declares, and the data words that hold addresses in the music area.
struct Declarer<'a, 'b> {
    ctx: &'a Ctx<'b>,
    done: HashSet<u32>,
    /// Aligned data and matched-code words with a value in the music area: value -> word addresses.
    words: BTreeMap<u32, Vec<u32>>,
}

const MUSIC_AREA: (u32, u32) = (0x086A_0000, 0x087B_0000);

impl<'a, 'b> Declarer<'a, 'b> {
    fn new(ctx: &'a Ctx<'b>) -> R<Self> {
        let mut words: BTreeMap<u32, Vec<u32>> = BTreeMap::new();
        let mut spans: Vec<(u32, u32, bool)> = Vec::new();
        let mut at = 0;
        let mut code: Vec<(u32, u32)> = ctx.rom.code_spans().to_vec();
        code.sort();
        for (start, end) in code {
            if at < start {
                spans.push((at, start, false));
            }
            spans.push((start, end, true));
            at = at.max(end);
        }
        if at < crate::ROM_SIZE {
            spans.push((at, crate::ROM_SIZE, false));
        }
        for (start, end, is_code) in spans {
            let first = (start + 3) & !3;
            if first + 4 > end {
                continue;
            }
            let bytes = if is_code { ctx.rom.code_bytes(BASE + first, end - first)? } else { ctx.rom.peek(BASE + first, end - first)? };
            for offset in (0..bytes.len() - 3).step_by(4) {
                let value = le32(bytes, offset);
                if (MUSIC_AREA.0..MUSIC_AREA.1).contains(&value) {
                    words.entry(value).or_default().push(BASE + first + offset as u32);
                }
            }
        }
        Ok(Declarer { ctx, done: HashSet::new(), words })
    }

    fn free(&self, address: u32) -> bool {
        self.ctx.rom.is_data(address) && self.ctx.rom.owners()[(address - BASE) as usize] == 0 && !self.done.contains(&address)
    }

    /// Runs of bytes in [start, end) that no port has read and the music port has not declared.
    fn runs(&self, start: u32, end: u32) -> Vec<(u32, u32)> {
        let mut out = Vec::new();
        let mut at = start;
        while at < end {
            if !self.free(at) {
                at += 1;
                continue;
            }
            let first = at;
            while at < end && self.free(at) {
                at += 1;
            }
            out.push((first, at));
        }
        out
    }

    /// The first byte at or after `start` that is read by a port or is code.
    fn next_read(&self, start: u32) -> u32 {
        let mut at = start;
        while at < BASE + crate::ROM_SIZE && self.ctx.rom.is_data(at) && self.ctx.rom.owners()[(at - BASE) as usize] == 0 {
            at += 1;
        }
        at
    }

    /// The words holding an address in [start, end); an error when matched code or a word a port read as a pointer holds one.
    fn holders(&self, start: u32, end: u32) -> R<String> {
        let owners = self.ctx.rom.owners();
        let mut unread = Vec::new();
        for (target, list) in self.words.range(start..end) {
            for &word in list {
                if !self.ctx.rom.is_data(word) {
                    return Err(format!("0x{target:08X} is declared unreachable but matched code at 0x{word:08X} holds it"));
                }
                let formats: Vec<String> = (0..4).map(|index| owners[(word + index - BASE) as usize]).filter(|owner| *owner != 0).map(|owner| self.ctx.rom.format_name(owner)).collect();
                if formats.iter().any(|name| name.starts_with("table.") || matches!(name.as_str(), "mp2k.song_header" | "mp2k.tone_data" | "literal_pool")) {
                    return Err(format!("0x{target:08X} is declared unreachable but the word at 0x{word:08X} is read as {}", formats.join("+")));
                }
                if formats.is_empty() {
                    unread.push(format!("0x{word:08X}->0x{target:08X}"));
                }
            }
        }
        Ok(if unread.is_empty() { "no aligned ROM word holds an address in it".into() } else { format!("aligned ROM words holding an address in it, all unread: {}", unread.join(" ")) })
    }

    fn unread(&mut self, item: usize, start: u32, end: u32, reason: &str) -> R<()> {
        self.done.extend(start..end);
        self.ctx.unread(item, start, end - start, reason)
    }

    fn unreachable(&mut self, start: u32, end: u32, basis: Basis, reason: &str) -> R<()> {
        if let Some((address, _)) = self.ctx.roots.by_address().range(start..end).next() {
            return Err(format!("0x{start:08X}..0x{end:08X} would be declared unreachable but the decomp source references 0x{address:08X}"));
        }
        self.done.extend(start..end);
        self.ctx.unreachable(start, end - start, basis, reason)
    }
}

const SPLIT_READS: &str = "m4a_ply_note.s reads a split tone's sub-voice at tone+4 + 12 * index: byte 0, the wave word at +4 and the word at +8, plus +3 and +1 for a rhythm tone (type & 0x80) and +2 and +3 for a PSG type (type & 7 != 0); it reads only byte 0 when that byte is itself a split type";

/// LoadTrackTone indexes player->tone by a u8 program; m4a_ply_note.s indexes a split base by a key below 0x80 or a u8 keysplit byte.
const VOICE_WINDOW: u32 = 256 * 12;
/// m4a_ply_note.s reads keysplit_table + key; the track key is stored only when the note or EndTie byte is below 0x80.
const KEY_WINDOW: u32 = 0x80;
/// SOUND_ENGINE_PLAYER_MEMORY: InitializeSoundEngine stores it in every player's memory field.
const PLAYER_MEMORY: u32 = 0x0300_7700;
/// sizeof(struct MusicPlayerControlState): MusicPlayerInfo (0x34 bytes), signature, next_update_callback, next_player.
const PLAYER_STATE_BYTES: u32 = 0x40;

const VOICE_SELECTION: &str = "voices are selected only by index: MusicCommandLoadTrackTone (music_track_commands.c) copies the 3 words at player->tone + 12 * program for the u8 program byte, and m4a_ply_note.s reads a split tone's sub-voice at base + 12 * index, base = track tone word +4 ([r5,#40]), index = the track key ([r5,#5], stored only when the note or EndTie byte is below 0x80) for a rhythm tone or keysplit_table[key] (table = track tone word +8, [r5,#44]); player->tone (MusicPlayerInfo +0x30) is written by StartMusicPlayer (song+4), the 64-byte ClearMusicStatePrefixViaCallback in InitializeMusicPlayer, and AccessPlayerMemory when its index reaches a player state; the track tone is written by LoadTrackTone, the extended tone commands (set_music_track_tone_wave.c, music_command_set_track_tone_*.c) and the track start (initialize_pending_music_tracks.c); the walk applies all of them over every song in gSongTable and both outcomes of each AccessPlayerMemory condition";

/// A declaration made next to the reads; emitted after the walk so it can name the voice indexes that hold it.
struct Pending {
    item: usize,
    start: u32,
    end: u32,
    reason: String,
}

#[derive(Clone, PartialEq)]
enum Cover {
    /// A voicegroup whose entry here no walked data selects.
    Unselected(u32),
    /// A voicegroup entry walked data selects only as a split sub-voice, which m4a_ply_note reads in part.
    Partial(u32, u32),
    /// A keysplit table at a key no walked note plays on it.
    Key(u32),
}

/// The index ranges of the walked voicegroups and keysplit tables.
struct Windows<'m> {
    groups: &'m BTreeMap<u32, Group>,
    keysplits: &'m BTreeMap<u32, Keysplit>,
}

impl Windows<'_> {
    /// The voice indexes whose range holds the unread byte at `address`; an error when walked data selects it.
    fn cover(&self, address: u32) -> R<Vec<Cover>> {
        let mut out = Vec::new();
        for (&base, group) in self.groups.range(address.saturating_sub(VOICE_WINDOW - 1)..=address) {
            let index = (address - base) / 12;
            let offset = ((address - base) % 12) as usize;
            if group.programs.contains(&index) {
                return Err(format!("0x{address:08X} is unread but it is in entry {index} of voicegroup 0x{base:08X}, which a walked LoadTrackTone reads in full"));
            }
            match group.entries.get(&index) {
                Some(entry) if entry.bytes[offset].is_some() => return Err(format!("0x{address:08X} is unread but m4a_ply_note read it in entry {index} of voicegroup 0x{base:08X}")),
                Some(_) => out.push(Cover::Partial(base, index)),
                None => out.push(Cover::Unselected(base)),
            }
        }
        for (&table, split) in self.keysplits.range(address.saturating_sub(KEY_WINDOW - 1)..=address) {
            let key = address - table;
            if split.keys.contains_key(&(key as u8)) {
                return Err(format!("0x{address:08X} is unread but a walked note plays key {key} of keysplit 0x{table:08X}"));
            }
            out.push(Cover::Key(table));
        }
        Ok(out)
    }

    /// [start, end) split into runs whose bytes have the same cover.
    fn runs(&self, start: u32, end: u32) -> R<Vec<(u32, u32, Vec<Cover>)>> {
        let mut out: Vec<(u32, u32, Vec<Cover>)> = Vec::new();
        for address in start..end {
            let cover = self.cover(address)?;
            match out.last_mut() {
                Some(last) if last.1 == address && last.2 == cover => last.1 = address + 1,
                _ => out.push((address, address + 1, cover)),
            }
        }
        Ok(out)
    }

    fn describe(&self, start: u32, end: u32, covers: &[Cover]) -> String {
        let parts: Vec<String> = covers
            .iter()
            .map(|cover| match cover {
                Cover::Unselected(base) => {
                    let group = &self.groups[base];
                    let (first, last) = ((start - base) / 12, (end - 1 - base) / 12);
                    let entries = if first == last { format!("entry {first}") } else { format!("entries {first}..{last}") };
                    format!("voicegroup 0x{base:08X} {entries}, which no walked data selects (walked LoadTrackTone programs with it as player->tone: {}; walked split indexes into it: {})", ranges(&group.programs), ranges(&group.split))
                }
                Cover::Partial(base, index) => {
                    let entry = &self.groups[base].entries[index];
                    let read: Vec<u32> = (0..12u32).filter(|offset| entry.bytes[*offset as usize].is_some()).collect();
                    let at = base + 12 * index;
                    format!(
                        "voicegroup 0x{base:08X} entry {index} bytes +{}..+{}, which walked data selects only as a split sub-voice ({}; no walked LoadTrackTone loads program {index} with it as player->tone), so m4a_ply_note.s reads bytes {read:?} of it ({SPLIT_READS})",
                        start - at,
                        end - 1 - at,
                        entry.uses.iter().cloned().collect::<Vec<_>>().join("; ")
                    )
                }
                Cover::Key(table) => {
                    let played: BTreeSet<u32> = self.keysplits[table].keys.keys().map(|key| u32::from(*key)).collect();
                    let keys: BTreeSet<u32> = (start - table..end - table).collect();
                    format!("keysplit 0x{table:08X} {} {} (keys walked notes play on it: {})", if keys.len() == 1 { "key" } else { "keys" }, ranges(&keys), ranges(&played))
                }
            })
            .collect();
        parts.join("; ")
    }

    /// The item of the nearest window start at or below `address` among `covers`.
    fn item(&self, covers: &[Cover]) -> Option<usize> {
        covers
            .iter()
            .map(|cover| match cover {
                Cover::Unselected(base) | Cover::Partial(base, _) => (*base, self.groups[base].item),
                Cover::Key(table) => (*table, self.keysplits[table].item),
            })
            .max_by_key(|(start, _)| *start)
            .map(|(_, item)| item)
    }

    /// "; within the index ranges of walked voices: ..." for the parts of [start, end) a voice index could reach; empty when none can.
    fn note(&self, start: u32, end: u32, selection: &str) -> R<String> {
        let parts: Vec<String> = self
            .runs(start, end)?
            .into_iter()
            .filter(|(_, _, cover)| !cover.is_empty())
            .map(|(first, stop, cover)| format!("0x{first:08X}..0x{stop:08X} is {}", self.describe(first, stop, &cover)))
            .collect();
        Ok(if parts.is_empty() { String::new() } else { format!("; within the index ranges of walked voices: {}; {selection}", parts.join("; ")) })
    }
}

/// Declares the bytes in and around the music items that no ported code reads, from the walk's own results.
fn declare(ctx: &Ctx, music: &Music, pending: Vec<Pending>, player_states: &[u32]) -> R<()> {
    let mut out = Declarer::new(ctx)?;
    let groups = music.groups.borrow();
    let keysplits = music.keysplits.borrow();
    let windows = Windows { groups: &groups, keysplits: &keysplits };

    let writes = music.memory_writes.borrow();
    for (&index, at) in writes.iter() {
        let address = PLAYER_MEMORY + u32::from(index);
        if let Some(player) = player_states.iter().find(|player| **player <= address && address < **player + PLAYER_STATE_BYTES) {
            return Err(format!("AccessPlayerMemory at {at} writes 0x{address:08X} (index {index}), inside the player state at 0x{player:08X}; the port does not model a changed player->tone or player->memory"));
        }
    }
    let reachable: Vec<String> = player_states.iter().filter(|player| **player < PLAYER_MEMORY + 0x100 && **player + PLAYER_STATE_BYTES > PLAYER_MEMORY).map(|player| hex(*player)).collect();
    let written: BTreeSet<u32> = writes.keys().map(|index| u32::from(*index)).collect();
    let selection = format!(
        "{VOICE_SELECTION}; AccessPlayerMemory operations 0..5 write player->memory[u8 index], and InitializeSoundEngine sets player->memory to SOUND_ENGINE_PLAYER_MEMORY (0x03007700) for every player, so the index reaches the player state(s) at {} (gMusicPlayerTable player words, 0x40 bytes each); {}",
        if reachable.is_empty() { "none".to_string() } else { reachable.join(" ") },
        if written.is_empty() { "no walked track issues such a write".to_string() } else { format!("walked tracks write indexes {}, none inside a player state", ranges(&written)) }
    );

    for entry in pending {
        let note = windows.note(entry.start, entry.end, &selection)?;
        out.unread(entry.item, entry.start, entry.end, &format!("{}{note}", entry.reason))?;
    }

    let psg: BTreeSet<u32> = ctx.data_of("mp2k.psg_wave").iter().map(|(address, _)| *address).collect();
    let pcm: BTreeMap<u32, u32> = ctx
        .data_of("mp2k.pcm_wave")
        .iter()
        .map(|(address, data)| data["sample_count"].as_u64().map(|count| (*address, count as u32)).ok_or_else(|| format!("PCM wave 0x{address:08X} has no sample_count")))
        .collect::<R<_>>()?;
    let voice_origin = "the port resolves every voice a walked note plays (m4a_ply_note.s copies the wave word at ToneData+4 into the channel; SetMusicTrackToneWave stores 4 track bytes as the wave) and makes a wave item, which reads the wave's first bytes, for each wave address";
    for (&wave, &next) in psg.iter().zip(psg.iter().skip(1)) {
        let runs = out.runs(wave + 16, next);
        if runs != [(wave + 16, next)] || (next - wave - 16) % 16 != 0 {
            continue;
        }
        for start in (wave + 16..next).step_by(16) {
            let holders = out.holders(start, start + 16)?;
            let note = windows.note(start, start + 16, &selection)?;
            out.unreachable(
                start,
                start + 16,
                VOICES,
                &format!("16 bytes between reached PSG waves 0x{wave:08X} and 0x{next:08X} (UpdatePsgSoundChannels copies 4 words from a channel's wave): {voice_origin}; no reached PSG wave lies in 0x{start:08X}..0x{:08X} (reached: {}); {holders}{note}", start + 16, psg.iter().map(|address| hex(*address)).collect::<Vec<_>>().join(" ")),
            )?;
        }
    }
    for (&wave, &count) in &pcm {
        let start = wave + 16 + count;
        if !out.free(start) {
            continue;
        }
        let next = out.next_read(start);
        if let Some(taken) = (start..next).find(|address| !out.free(*address)) {
            return Err(format!("0x{taken:08X}, after PCM wave 0x{wave:08X}, is unread but already declared"));
        }
        let holders = out.holders(start, next)?;
        let note = windows.note(start, next, &selection)?;
        out.unreachable(
            start,
            next,
            PCM,
            &format!("bytes from 0x{start:08X} (samples[sample_count] of reached PCM wave 0x{wave:08X}, sample_count {count}) to the next byte a port reads (0x{next:08X}): no matched code reads PCM sample bytes (CalculatePcmPlaybackFrequency reads frequency_fixed10 at +4; m4a_ply_note.s stores the wave address in the channel); the sample reader is the mixer InitializeSoundEngine copies from 0x080EAB28 to IWRAM, which has no decomp source, so the port bounds the samples by PcmWaveHeader.sample_count and the decomp does not show whether the mixer reads samples[sample_count] or later; {voice_origin}, and no reached PCM wave starts in this range; {holders}{note}"),
        )?;
    }

    let mut spans: Vec<(u32, u32)> = Vec::new();
    for (&base, group) in groups.iter() {
        let Some(&last) = group.entries.keys().next_back() else { continue };
        let selected_end = base + 12 * (last + 1);
        spans.push((base, out.next_read(selected_end).max(selected_end).min(base + VOICE_WINDOW)));
    }
    for &table in keysplits.keys() {
        spans.push((table, table + KEY_WINDOW));
    }
    spans.sort();
    for (start, end) in spans {
        for (first, stop) in out.runs(start, end) {
            for (from, to, cover) in windows.runs(first, stop)? {
                let Some(item) = windows.item(&cover) else { continue };
                out.unread(item, from, to, &format!("0x{from:08X}..0x{to:08X}: {}; {selection}", windows.describe(from, to, &cover)))?;
            }
        }
    }

    let tracks = music.tracks.borrow();
    let mut targets: BTreeSet<u32> = BTreeSet::new();
    for info in tracks.values() {
        targets.extend(info.targets.iter().copied());
    }
    let starts: BTreeSet<u32> = ctx.data_of(TRACK).iter().map(|(address, _)| *address).collect();
    for (item, info) in tracks.iter() {
        let start_of = ctx.name(*item);
        for (&end_of_command, command) in &info.terminals {
            if !out.free(end_of_command) {
                continue;
            }
            let next = out.next_read(end_of_command);
            if next >= BASE + crate::ROM_SIZE || !ctx.rom.is_data(next) {
                continue;
            }
            let owner = ctx.rom.format_name(ctx.rom.owners()[(next - BASE) as usize]);
            if owner != TRACK && owner != "mp2k.song_header" {
                continue;
            }
            if let Some(target) = targets.range(end_of_command..next).next() {
                return Err(format!("track bytes 0x{end_of_command:08X}..0x{next:08X} follow {command} but a walked jump targets 0x{target:08X}"));
            }
            if let Some(track) = starts.range(end_of_command..next).next() {
                return Err(format!("track bytes 0x{end_of_command:08X}..0x{next:08X} follow {command} but track 0x{track:08X} starts there"));
            }
            let holders = out.holders(end_of_command, next)?;
            let note = windows.note(end_of_command, next, &selection)?;
            out.unreachable(
                end_of_command,
                next,
                SEQUENCER,
                &format!("track bytes after {command} in walked {start_of}, up to the next byte a port reads ({owner} at 0x{next:08X}): m4a_ply_fine.s clears track->flags and m4a_mplay_main.s stops reading a track whose flags are 0 when the handler returns, and the Goto handler (m4a_read_u32.s) replaces track->command with the 4-byte target, so neither falls through; no walked Goto, Pattern, Repeat or memory-branch target and no song track pointer read by StartMusicPlayer lies in this range; {holders}{note}"),
            )?;
        }
    }
    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::roots::Roots;
    use crate::rom::Rom;

    const AT: u32 = 0x0870_0000;

    fn table() -> [u32; HANDLER_COUNT as usize] {
        let mut table = [0x080E_AE91; HANDLER_COUNT as usize];
        let rom: [(usize, u32); 20] = [
            (1, 0x080E_AF01), (2, 0x080E_AF21), (3, 0x080E_AF3D), (4, 0x080E_AF51), (9, 0x080E_AF81), (10, 0x080E_AF8D),
            (11, 0x080E_AFA1), (12, 0x080E_AFB5), (13, 0x080E_AFE5), (14, 0x080E_AFF9), (15, 0x080E_B00D), (16, 0x080E_B021),
            (17, 0x080E_B605), (18, 0x080E_B035), (19, 0x080E_B619), (20, 0x080E_B041), (23, 0x080E_B059), (27, 0x080E_B06D),
            (29, 0x080E_B59D), (8, 0x080E_C901),
        ];
        for (slot, handler) in rom {
            table[slot] = handler;
        }
        table
    }

    fn walk(track: &[u8]) -> R<(TrackInfo, Vec<([u8; 12], u8)>)> {
        let mut bytes = vec![0u8; crate::ROM_SIZE as usize];
        let offset = (AT - BASE) as usize;
        bytes[offset..offset + track.len()].copy_from_slice(track);
        let rom = Rom::new(bytes, Vec::new());
        let roots = Roots { refs: Vec::new(), symbols: HashMap::new() };
        let ctx = Ctx::new(&rom, &roots, std::path::Path::new("/nonexistent"));
        let mut clock = [0u8; CLOCK_ENTRIES as usize];
        for (index, value) in clock.iter_mut().enumerate() {
            *value = index as u8;
        }
        let regions = verify_c::regions(&repo_root().join("regions.txt"))?;
        let music = Music::new(&ctx, Driver { table: table(), clock, regions, extended: RefCell::new(BTreeMap::new()) });
        let (item, _) = ctx.item(TRACK, AT, SEQUENCER, Vec::new());
        let mut walk = Walk { music: &music, item, start: AT, voicegroup: 0, song: 0, info: TrackInfo::default(), forks: Vec::new(), loaded_tone: false, conditional: false };
        walk.run()?;
        let notes = music.notes.borrow().keys().copied().collect();
        Ok((walk.info, notes))
    }

    fn lines(info: &TrackInfo) -> Vec<String> {
        info.listing.iter().map(|((at, _), line)| format!("{:X} {line}", at - AT)).collect()
    }

    #[test]
    fn running_status_reuses_the_last_command() {
        let (info, _) = walk(&[0xBE, 0x40, 0x50, 0xD0, 0x3C, 0x7F, 0x3E, 0x81, 0xB1]).unwrap();
        assert_eq!(lines(&info), ["0 BE SetTrackVolume 64", "2 (BE) SetTrackVolume 80", "3 D0 Note 1 key 60 velocity 127 gate +62", "7 81 Wait 1", "8 B1 Fine"]);
        assert_eq!(info.ends.iter().collect::<Vec<_>>(), [&("fine", AT + 8)]);
    }

    #[test]
    fn data_byte_without_running_status_is_an_error() {
        assert!(walk(&[0x3C, 0xB1]).is_err());
    }

    #[test]
    fn repeat_counts_then_falls_through() {
        let target = (AT + 0).to_le_bytes();
        let (info, _) = walk(&[0x81, 0xB5, 0x03, target[0], target[1], target[2], target[3], 0xB1]).unwrap();
        assert_eq!(info.states, 3 * 2 + 1);
        assert!(info.ends.contains(&("fine", AT + 7)));
    }

    #[test]
    fn pattern_stack_holds_three_levels() {
        let next = |at: u32| (AT + at).to_le_bytes();
        let mut track = Vec::new();
        for level in 0..4u32 {
            let target = next(5 * (level + 1));
            track.extend_from_slice(&[0xB3, target[0], target[1], target[2], target[3]]);
        }
        track.push(0xB1);
        let (info, _) = walk(&track).unwrap();
        assert_eq!(info.ends.iter().collect::<Vec<_>>(), [&("pattern_stack_full", AT + 15)]);
    }

    #[test]
    fn pattern_end_returns_after_the_pointer() {
        let target = (AT + 7).to_le_bytes();
        let (info, _) = walk(&[0xB3, target[0], target[1], target[2], target[3], 0xB1, 0x00, 0x81, 0xB4]).unwrap();
        assert!(info.ends.contains(&("fine", AT + 5)));
        assert_eq!(info.states, 4);
    }

    #[test]
    fn memory_branch_follows_both_outcomes() {
        let target = (AT + 12).to_le_bytes();
        let (info, _) = walk(&[0xB9, 0x06, 0x00, 0x01, target[0], target[1], target[2], target[3], 0x81, 0xB1, 0x00, 0x00, 0x82, 0xB1]).unwrap();
        assert!(info.ends.contains(&("fine", AT + 9)));
        assert!(info.ends.contains(&("fine", AT + 13)));
    }

    #[test]
    fn goto_and_fine_end_the_track() {
        let target = (AT + 7).to_le_bytes();
        let (info, _) = walk(&[0xB2, target[0], target[1], target[2], target[3], 0x00, 0x00, 0xB1]).unwrap();
        assert_eq!(info.terminals.keys().copied().collect::<Vec<_>>(), [AT + 5, AT + 8]);
        assert_eq!(info.targets.iter().copied().collect::<Vec<_>>(), [AT + 7]);
    }

    #[test]
    fn conditional_goto_falls_through() {
        let target = (AT + 12).to_le_bytes();
        let (info, _) = walk(&[0xB9, 0x06, 0x00, 0x01, target[0], target[1], target[2], target[3], 0x81, 0xB1, 0x00, 0x00, 0x82, 0xB1]).unwrap();
        assert_eq!(info.terminals.keys().copied().collect::<Vec<_>>(), [AT + 10, AT + 14]);
        assert_eq!(info.targets.iter().copied().collect::<Vec<_>>(), [AT + 8, AT + 12]);
    }

    #[test]
    fn ranges_join_runs() {
        assert_eq!(ranges(&[0, 5, 7, 8, 9, 11].into_iter().collect()), "0,5,7-9,11");
        assert_eq!(ranges(&BTreeSet::new()), "none");
    }

    #[test]
    fn cover_names_unselected_indexes_and_rejects_selected_ones() {
        const GROUP: u32 = 0x086A_0000;
        const TABLE: u32 = 0x086A_0100;
        let mut entries = BTreeMap::new();
        entries.insert(1, Entry { bytes: [Some(0); 12], uses: BTreeSet::new() });
        let mut partial = [Some(0); 12];
        partial[2] = None;
        entries.insert(2, Entry { bytes: partial, uses: BTreeSet::new() });
        let groups: BTreeMap<u32, Group> = [(GROUP, Group { item: 0, entries, programs: [1].into_iter().collect(), split: [2].into_iter().collect() })].into_iter().collect();
        let keysplits: BTreeMap<u32, Keysplit> = [(TABLE, Keysplit { item: 1, keys: [(5, 2)].into_iter().collect(), also_tone_data: BTreeSet::new() })].into_iter().collect();
        let windows = Windows { groups: &groups, keysplits: &keysplits };
        assert!(windows.cover(GROUP) == Ok(vec![Cover::Unselected(GROUP)]));
        assert!(windows.cover(GROUP + 12).is_err());
        assert!(windows.cover(GROUP + 24 + 2) == Ok(vec![Cover::Partial(GROUP, 2)]));
        assert!(windows.cover(GROUP + 24 + 3).is_err());
        assert!(windows.cover(TABLE + 5).is_err());
        assert!(windows.cover(TABLE + 6) == Ok(vec![Cover::Unselected(GROUP), Cover::Key(TABLE)]));
        assert!(windows.cover(TABLE + KEY_WINDOW) == Ok(vec![Cover::Unselected(GROUP)]));
        assert!(windows.cover(GROUP + VOICE_WINDOW).unwrap().is_empty());
        assert_eq!(windows.item(&windows.cover(TABLE + 6).unwrap()), Some(1));
    }

    #[test]
    fn notes_keep_the_key_only_for_split_tones() {
        let (_, notes) = walk(&[0xD0, 0x3C, 0xB1]).unwrap();
        let mut tone = [0u8; 12];
        tone[0] = 1;
        assert_eq!(notes, [(tone, 0)]);
    }
}
