//! RunEventScripts (0x080A67E4), SeekEventCommand (0x080A016C) and the command handlers' control flow.
//! Every executed command's successors come from its handler: one SeekEventCommand step for most handlers,
//! and the branch, choice, jump and end handlers listed in `class`. Conditions depend on runtime state, so every outcome is followed.

use std::cell::RefCell;
use std::collections::{BTreeMap, BTreeSet, HashMap, HashSet};

use serde_json::{json, Value};

use super::text::{parse_list, parse_window};
use super::Port;
use crate::basis::Basis;
use crate::rom::{le32, R};
use crate::run::Ctx;
use crate::{repo_root, verify_c};

pub const EVENTS: Basis = Basis::C(&[
    ("src/events/run_event_scripts.c", "b5d81310df6acae653f77c2a995f2abcb888539a"),
    ("src/events/seek_event_command.c", "de0f16e227c7cac6726dcb152aa5e3de5ed1fc67"),
    ("src/events/event_script.h", "23f6268830cf2d663af58bc5552d8fd4105e85b2"),
    ("src/events/start_map_event_script.c", "f8e624a2e5325ae38560b2094ff21857194cabec"),
    ("src/events/show_event_choices.c", "8c5ec8c66d03ae03d1b3c6bbc9a8b4cd82278f09"),
    ("src/events/commands/event_animate_world_map_structure.c", "b8bcf727ff81ae5c144b0752ea2e0366ca50e164"),
    ("src/events/commands/event_backup_player_and_field_state.c", "445583b8c14acabef35666cef6089e000692d2ba"),
    ("src/events/commands/event_call_scene_function.c", "02723b69d214eb63ae7d3f4bce88bb64e624370c"),
    ("src/events/commands/event_center_battle_camera.c", "402beb91e3d5911ba0a4c2a4a92ccdc7f11fbe7a"),
    ("src/events/commands/event_change_bit_liger_zero_form.c", "04806c7f4cb0fd1eb84ddb7d850dead4243a2e55"),
    ("src/events/commands/event_change_map.c", "613681f0e5835f389adc8c4a668a0dbb6ef8e10f"),
    ("src/events/commands/event_chevron_screen_transitions.c", "a05f2689e5d623b9148e8ab62bd118e0e4217351"),
    ("src/events/commands/event_choice.c", "89631399b8418df11a1c38726b9750d0e4dc1004"),
    ("src/events/commands/event_clear_additional_field_travel_restriction.c", "3d1c4595f378c4313dc47a2f1a457874ff10d404"),
    ("src/events/commands/event_clear_flag.c", "0de17a116b4fc17ba7735671895285bb88a72851"),
    ("src/events/commands/event_close_portrait.c", "a4c46b579d1ed8d06c68b77ed23c81af0ec4ace4"),
    ("src/events/commands/event_combine_battle_zoids.c", "7b1dc0601dfc0aaa219c29f306a1bea6bba7847d"),
    ("src/events/commands/event_conceal_field_with_checkerboard.c", "c5ce47199a17fcb2dbc49d9c5afd604c064b1efa"),
    ("src/events/commands/event_conceal_field_with_dither.c", "1aa290f94ee7cf1d555d13b8e2569f6d53038fcf"),
    ("src/events/commands/event_conceal_field_with_rotating_split.c", "ea5f883cad11cb89bd92d9632bf88d201200874f"),
    ("src/events/commands/event_conceal_field_with_rotating_square.c", "69029b09459f92a12482145c8c0c7a0b0d9c6a86"),
    ("src/events/commands/event_conceal_field_with_scaled_z.c", "d268d72063ce3c7aa1a47799a21ab9a6b9897f07"),
    ("src/events/commands/event_create_battle_equipment_sprite.c", "2c7e4f4eca90d132349bbe665dd1b927aa33db4b"),
    ("src/events/commands/event_create_battle_unit_sprite_at_position.c", "5fa19e67eb1ce938059e9d80413f7cb13385c6b7"),
    ("src/events/commands/event_create_sprite.c", "4b1effad2d11d666e0344c1651c91317b2a3d265"),
    ("src/events/commands/event_destroy_sprite.c", "adbfd474dee10422dddbad1a48a0de0faf512b82"),
    ("src/events/commands/event_disable_world_map_decorations.c", "ab330f535131c8f8d84e3837cb7721293b96ba18"),
    ("src/events/commands/event_enable_battle_rule.c", "7d65cc27fd54b62f3a6e5e39b746752a92107419"),
    ("src/events/commands/event_end.c", "b27dd24c12732497269e5b4ec55322d48a3f8df5"),
    ("src/events/commands/event_enter_battle_scene.c", "3c980bea39d2bd71f59a24757b7a4fe7ce174fda"),
    ("src/events/commands/event_enter_battle.c", "70b9096502da6e09eaaa83521a65f2d65793b5a4"),
    ("src/events/commands/event_enter_field.c", "165b6b836b2dfa146c45f58bdb17701c37b1bf40"),
    ("src/events/commands/event_fade_screen_from_black.c", "9a7f88f781cda3d405823e888d40d809570813b4"),
    ("src/events/commands/event_fade_screen_from_white.c", "2502a68b33d3bf1dbed2f08cabcdd4500eeaf7e3"),
    ("src/events/commands/event_fade_screen_to_black.c", "82e55dec8b06a1a78d8582e922e48e2d08b91e93"),
    ("src/events/commands/event_fade_screen_to_white.c", "cdd1b60133ade6da8fd98f1d2c1a07362f20273f"),
    ("src/events/commands/event_flash_screen_white.c", "0ddf403b40d4b92a5f1147ddbfb86382b5cee6bc"),
    ("src/events/commands/event_focus_battle_camera_on_unit.c", "1c1dccc338211af7174c8a00cfeff0ddebfd46c4"),
    ("src/events/commands/event_focus_field_camera_on_actor.c", "f9a4918dbb5958c81a69ad3a7dd159d79b67dbdd"),
    ("src/events/commands/event_grant_pulse_effect.c", "076ffc9ae8f74d9955a706cdffd2c3cb0645030a"),
    ("src/events/commands/event_if_flag_clear.c", "649d04bf293dca4fea9bd250020b72024d41253e"),
    ("src/events/commands/event_if_flag_set.c", "d62a89e52ee521874db978233b71bc82dedbd511"),
    ("src/events/commands/event_if_interacted_actor.c", "becd93ac76519f3eae33514d0b55120c7588c36f"),
    ("src/events/commands/event_if_party_restriction.c", "5f6eff11323328a4d6c9851fe6f33d45d97146f8"),
    ("src/events/commands/event_if_player_deck_command_unlocked.c", "37fe41356bf3ce1c302c8af92fcacd541f82141f"),
    ("src/events/commands/event_if_player_in_rect.c", "f1dc2e8393b56464e1171ad5d9ff4c0ae77e126d"),
    ("src/events/commands/event_if_player_interaction.c", "a6be942f845b7f8fd21099a453964edea70b8224"),
    ("src/events/commands/event_if_player_team_has_pilot.c", "ba40fc2f7a6fdc35af0890a01d2af19c3396a740"),
    ("src/events/commands/event_jump.c", "a4119da4a3a05b973e4072eb5732a1bd231f45c5"),
    ("src/events/commands/event_level_up_pulse.c", "625c80d41e52daa45a4c20b3a3fad88d92b336f7"),
    ("src/events/commands/event_load_battle_scene_model_from_player_pilot.c", "b51949dfd2b9fbbff0af1ea291f59ea94a9e8471"),
    ("src/events/commands/event_load_battle_scene_model.c", "766d78d0354e9d8569a3bdc9bb8b682972af6697"),
    ("src/events/commands/event_load_field_map_at_position.c", "3f4d72078671103da98b332431590b84ee2dddd1"),
    ("src/events/commands/event_load_sprite_graphics.c", "a08839d14d81be0786c3a3f8ae0c46ac99c09bea"),
    ("src/events/commands/event_move_field_camera_in_direction.c", "6f7294e45b2ebbdfd62357f4a0a5ef6fe35a256f"),
    ("src/events/commands/event_move_sprite.c", "9a88457d43584bd9249b973c1c5257b5e88bb35b"),
    ("src/events/commands/event_offer_pulse_emotion_growth.c", "64f7f8f426d05dba7060991896ae51c3052d7d33"),
    ("src/events/commands/event_open_equipment_shop.c", "e81bff760f554dcaa7295b79292db815702394ae"),
    ("src/events/commands/event_open_item_shop.c", "3ee47c0904c03e97f08de4ac6661978349a95ab0"),
    ("src/events/commands/event_open_pause_menu.c", "77cb674597c52767468519a686c8114950a13a41"),
    ("src/events/commands/event_open_team_setup_if_empty.c", "6a0625a751a2850254576c61eaabd8b991d77062"),
    ("src/events/commands/event_open_zoids_lab.c", "7ba3ff4a54256cd6db6ce2da20be00e9679727b6"),
    ("src/events/commands/event_play_battle_equipment_animation.c", "8c4c63141df86506b0cd5f2970ddf17e023280b5"),
    ("src/events/commands/event_play_battle_impact_animation.c", "4bf3242637dcc76a704fe24f4c2981f9cde51a58"),
    ("src/events/commands/event_play_battle_model_equipment_impact_animation.c", "f8309e89c5f1d58cfe68e6308aa7edb861c8403c"),
    ("src/events/commands/event_play_battle_mounted_equipment_animation.c", "619ef3487a6112d3cad1e094fc3915447e5eebb8"),
    ("src/events/commands/event_play_field_music.c", "5e644fecaa80d96cdbadcbf2cfb7d814f9c5e877"),
    ("src/events/commands/event_play_map_music.c", "ad13eec87f8ed327f3ee94a0dbee9559c42f1632"),
    ("src/events/commands/event_play_song.c", "40bb29ae9a49ce91df32b04eb1f611ce77156d83"),
    ("src/events/commands/event_queue_field_actor_command.c", "e326447192d2a84139ab5e9ac680accd9f110f1d"),
    ("src/events/commands/event_remove_actor.c", "8034b551e0c5cc6ab74e2609aba4e6ea9188a84d"),
    ("src/events/commands/event_remove_battle_unit.c", "1540337f23ec7061c979fe3b142a2064df45be2d"),
    ("src/events/commands/event_remove_world_map_structure.c", "ec957b0510b81e39f2281af60d543ab0754217c4"),
    ("src/events/commands/event_request_battle_phalanx_volley.c", "135a36a150e3e96e702dbc44db2708e05ca22e01"),
    ("src/events/commands/event_request_battle_speed_lines.c", "776e0d5c7722fdb258dbb503f39b857311fb7eb9"),
    ("src/events/commands/event_reset_sprite_pool.c", "04774fdaffded27324c9c9f2806a82c92340a19e"),
    ("src/events/commands/event_reset_world_map_background_effects.c", "c4701de26a460eae1ab3c5782ab865d7d0385c17"),
    ("src/events/commands/event_restart.c", "cef40d225260904cc5707d19cd9a5a6ce60777c8"),
    ("src/events/commands/event_return_to_title.c", "903f895e201520712a7feda102351292335845e5"),
    ("src/events/commands/event_reveal_field_with_checkerboard.c", "a87366544f96b955dd4099cc4ba25b01ef073c7d"),
    ("src/events/commands/event_reveal_field_with_dither.c", "36298d3ebd36eb6c79f840ae1f3148e3db967013"),
    ("src/events/commands/event_reveal_field_with_leftward_chevron.c", "e7ddc5ad93affc6a773d12e11b0a280ccf1674e2"),
    ("src/events/commands/event_reveal_field_with_rotating_split.c", "0a314561bfe7548251425ebdc144bb6f9bd6d070"),
    ("src/events/commands/event_reveal_field_with_rotating_square.c", "de6e586cd659ef8e6d685cf31a10618b3e9fe2fe"),
    ("src/events/commands/event_reveal_field_with_scaled_z.c", "9d24e74ad67334882c17bb8c39d4981236f0e3d0"),
    ("src/events/commands/event_save_clear_data.c", "0623f1c23c5f2bdf2df1255682448a31afce700f"),
    ("src/events/commands/event_set_additional_field_travel_restriction.c", "906509bfb870c23f184725de975ecf3dd4827eac"),
    ("src/events/commands/event_set_battle_camera_side.c", "e9af2fbf8f78a902ba164ae2fe79f3cc47fd090f"),
    ("src/events/commands/event_set_battle_fuzor_component_models.c", "ad767816619829fd0eadff3eb9589a9ac20739b6"),
    ("src/events/commands/event_set_battle_intro_camera.c", "be0df8f638ce63f90d8789c5a94c73fa28926e44"),
    ("src/events/commands/event_set_battle_scene_terrain.c", "d7d5dd6a7908f3e02876d414f68a31a9ccf26338"),
    ("src/events/commands/event_set_battle_side_models_from_encounter.c", "6ab5b72ffa6954dad9780493b4ea003058de0fbf"),
    ("src/events/commands/event_set_battle_side_models_from_player_team.c", "83b4fab5cfd86cb30a48e9740b115548464f85e8"),
    ("src/events/commands/event_set_battle_unit_model_from_player_pilot.c", "f6c787553b027c8878c740d9dfd960743358cecb"),
    ("src/events/commands/event_set_battle_unit_model.c", "ec9c7172078842695dc57a385bc3f659eaf8355c"),
    ("src/events/commands/event_set_field_actor_behavior.c", "c0906cdb4b01bdacb6956874005ded91c0c4eb25"),
    ("src/events/commands/event_set_field_travel_restriction.c", "85e3d5a9a9ebe5e26f75b23e4449ef284822b827"),
    ("src/events/commands/event_set_field_view_center_position.c", "a6889c9721f04f7c216aa36bc7eb7c676c9a0ac1"),
    ("src/events/commands/event_set_flag.c", "98823a316d940688cd12f8c7f2369a4546ab15fb"),
    ("src/events/commands/event_set_transport_model.c", "3de1d107e31efc692f2b3e17f28e4d303d891496"),
    ("src/events/commands/event_set_world_map_structure.c", "fcab0278f74a0e0d3efd154d0a7b9bf9048c0c3e"),
    ("src/events/commands/event_shake_field_camera.c", "0db62ea1648f4ee4327a1fe8ba748fbcae9520f4"),
    ("src/events/commands/event_show_credits.c", "7d00482a818cd1b80d27819321c67f0e5b004643"),
    ("src/events/commands/event_show_pilot_portrait.c", "7af7d445048c160bc8c62d567cf7bf9b20fba3c0"),
    ("src/events/commands/event_show_text.c", "09186da2f0c5ee44fd9bf62d1d329d8f6c89e366"),
    ("src/events/commands/event_show_world_map_bg1_overlay.c", "ccc10a7235475aafd790ebdc7fa8ec4d67ecd505"),
    ("src/events/commands/event_show_world_map_structure_appearance.c", "c95a611325ad356555ea91b8430e5ac7ec9bf054"),
    ("src/events/commands/event_skip_marker.c", "cd6057b31770fd7425532473bb4883d44d627b84"),
    ("src/events/commands/event_spawn_actor_relative.c", "4138d9b2000b3b613af14145ac11c28aae36ab28"),
    ("src/events/commands/event_spawn_actor.c", "7d5a04de0be40670bce814c005ae9445c25178c9"),
    ("src/events/commands/event_spawn_transport_actor.c", "0a7d271182992a7136c66908c1a246b8ef34d57f"),
    ("src/events/commands/event_start_battle.c", "cdf93064c86327b6482d4048d0cf9c862244ee49"),
    ("src/events/commands/event_start_scripts.c", "bcfe118b72c8cde6ab335ffc30cb02e6cb5b70e2"),
    ("src/events/commands/event_stop_camera_shake.c", "10f2d2b71b23c21c7369f3d51108244fa3577a7a"),
    ("src/events/commands/event_stop_field_music.c", "fcc98f0d07c734426d3c5ec37c9ef88a474b4cb2"),
    ("src/events/commands/event_stop_song.c", "cd2a56e31860186b193fd650ec1c380f22075d4b"),
    ("src/events/commands/event_unlock_bit_liger_zero_form.c", "d3c30f158379b4161f3994903dee936f86902479"),
    ("src/events/commands/event_update_player_assets_and_roster.c", "2513c231e791399171d93ba5a7ec53b684c9bad1"),
    ("src/events/commands/event_wait_for_scene_actions.c", "5e29b2f5f4ce420763f9e1502a9a3a96597c2db7"),
    ("src/events/commands/event_wait_frames.c", "c647e3f3193029d1af5be72461251106dc12078e"),
    ("src/events/commands/event_yes_no.c", "042c275add207598ef1964400ab674b859e396f5"),
]);

pub const PORT: Port = Port { name: "event_script", bases: &[EVENTS], run };

const LENGTHS: u32 = 0x087A_17FC;
const HANDLERS: u32 = 0x087A_190C;
const MAP_SCRIPTS: u32 = 0x087A_0BF8;
const FIELD_MAP_DEFINITIONS: u32 = 0x087C_4434;
const MAP_GROUP_POSITIONS: u32 = 0x087A_FBB4;
const START_MAP_EVENT_SCRIPT: u32 = 0x0809_FD3C;
/// Last opcode in enum EventOpcode (event_script.h).
const LAST_OPCODE: u8 = 0x97;
const FORMAT: &str = "event_script";

const END: u8 = 0x00;
const START_SCRIPTS: u8 = 0x09;
const JUMP: u8 = 0x0A;
const RESTART: u8 = 0x0B;
const YES_NO: u8 = 0x0E;
const BRANCH_TRUE: i32 = 0x0F;
const BRANCH_FALSE: i32 = 0x10;
const CHOICE: u8 = 0x11;
const CHOICE_CASE: u8 = 0x12;
const ALTERNATIVE: u8 = 0x18;
const TEXT: u8 = 0x20;
const CHANGE_MAP: u8 = 0x42;
const OFFER_PULSE_GROWTH: u8 = 0x7E;
const PULSE_GROWTH_ACCEPTED: i32 = 0x7F;
const PULSE_GROWTH_DECLINED: i32 = 0x80;
const RETURN_TO_TITLE: u8 = 0x83;
const SCAN_NEXT: i32 = -1;

#[derive(Clone, Copy, PartialEq, Debug)]
enum Class {
    /// The handler sets the cursor to 0 or to the script start, or the script stops.
    Stop,
    Jump,
    /// event_if_*: on success skip (ALTERNATIVE, command) pairs; on failure continue only at an ALTERNATIVE.
    If,
    /// Seek BRANCH_TRUE or BRANCH_FALSE.
    Branch,
    Choice,
    PulseGrowth,
    Next,
}

fn class(op: u8) -> Class {
    match op {
        END | RESTART | CHANGE_MAP | RETURN_TO_TITLE => Class::Stop,
        JUMP => Class::Jump,
        0x13..=0x17 => Class::If,
        YES_NO | 0x19..=0x1C => Class::Branch,
        CHOICE => Class::Choice,
        OFFER_PULSE_GROWTH => Class::PulseGrowth,
        _ => Class::Next,
    }
}

/// Opcode names from enum EventOpcode in event_script.h.
fn opcode_names() -> R<HashMap<u8, String>> {
    let text = std::fs::read_to_string(repo_root().join("src/events/event_script.h")).map_err(|error| error.to_string())?;
    let mut names = HashMap::new();
    for line in text.lines().take_while(|line| !line.contains("EVENT_SCAN_NEXT")) {
        let line = line.trim().trim_end_matches(',');
        if let Some((name, value)) = line.split_once('=') {
            let name = name.trim();
            if let Some(hex) = value.trim().strip_prefix("0x") {
                if let (true, Ok(value)) = (name.starts_with("EVENT_"), u8::from_str_radix(hex, 16)) {
                    names.entry(value).or_insert_with(|| name.trim_start_matches("EVENT_").to_string());
                }
            }
        }
    }
    Ok(names)
}

enum State {
    DecrementTerminators,
    CheckSelectedOpcode,
    CheckSelectorClass,
    ScanTerminators,
    CheckNesting,
}

struct Walk<'a, 'b> {
    ctx: &'a Ctx<'b>,
    lengths_id: usize,
    length_opcodes: &'a RefCell<BTreeSet<u8>>,
    item: usize,
}

impl Walk<'_, '_> {
    fn byte(&self, address: u32) -> R<u8> {
        Ok(self.ctx.rom.claim(address, 1, FORMAT, self.item)?[0])
    }

    fn length(&self, op: u8) -> R<u32> {
        if op > LAST_OPCODE {
            return Err(format!("opcode 0x{op:02X} is past the last EventOpcode"));
        }
        self.length_opcodes.borrow_mut().insert(op);
        Ok(u32::from(self.ctx.rom.claim(LENGTHS + u32::from(op), 1, "table.event_command_lengths", self.lengths_id)?[0]))
    }

    /// One command of SeekEventCommand's switch.
    fn step(&self, at: u32, depth: u8, nesting: &mut [u8; 4]) -> R<u32> {
        match self.byte(at)? {
            START_SCRIPTS => Ok(at + 2 + 4 * u32::from(self.byte(at + 1)?)),
            TEXT => {
                let mut cursor = at + 1;
                if self.text_byte(cursor)? != 0 {
                    loop {
                        match self.text_byte(cursor)? {
                            1 => cursor += 1,
                            2 => cursor += 2,
                            0x0D if depth != 0 => nesting[depth as usize - 1] = nesting[depth as usize - 1].wrapping_add(1),
                            _ => {}
                        }
                        cursor += 1;
                        if self.text_byte(cursor)? == 0 {
                            break;
                        }
                    }
                }
                Ok(cursor + 1)
            }
            op => match self.length(op)? {
                0 => Err(format!("opcode 0x{op:02X} at 0x{at:08X} has length 0; SeekEventCommand would not advance")),
                length => Ok(at + length),
            },
        }
    }

    fn text_byte(&self, address: u32) -> R<u8> {
        Ok(self.ctx.rom.claim(address, 1, super::text::FORMAT, self.item)?[0])
    }

    /// SeekEventCommand(slot, target, choice) starting at `start`.
    fn seek(&self, start: u32, target: i32, choice: u8) -> R<u32> {
        let shifted = u32::from(target as u16) << 16;
        let value = (shifted as i32) >> 16;
        let selector_class = (shifted.wrapping_add(0xFFF1_0000) >> 16) as u16;
        let mut cursor = start;
        let mut terminators: u8 = 0;
        let mut depth: u8 = 0;
        let mut nesting = [0u8; 4];
        let mut state = State::CheckSelectorClass;
        for _ in 0..2_000_000 {
            state = match state {
                State::DecrementTerminators => {
                    terminators = terminators.wrapping_sub(1);
                    State::CheckSelectedOpcode
                }
                State::CheckSelectedOpcode => {
                    let op = self.byte(cursor)?;
                    if value == i32::from(CHOICE_CASE) && op == CHOICE_CASE {
                        if depth == 1 {
                            if self.byte(cursor + 1)? == choice {
                                return Ok(cursor);
                            }
                        } else {
                            if depth == 0 {
                                return Err(format!("seek from 0x{start:08X}: CHOICE_CASE at 0x{cursor:08X} outside any CHOICE"));
                            }
                            let slot = depth as usize - 1;
                            nesting[slot] = nesting[slot].wrapping_sub(1);
                            if nesting[slot] == 0 {
                                depth -= 1;
                            }
                        }
                    }
                    if value == SCAN_NEXT || i32::from(op) == value {
                        if (value - BRANCH_TRUE) as u16 <= 1 {
                            State::ScanTerminators
                        } else if value != i32::from(CHOICE_CASE) {
                            return Ok(cursor);
                        } else {
                            State::CheckSelectorClass
                        }
                    } else {
                        State::CheckSelectorClass
                    }
                }
                State::CheckSelectorClass => {
                    if selector_class > 1 {
                        State::CheckNesting
                    } else {
                        State::ScanTerminators
                    }
                }
                State::ScanTerminators => {
                    if matches!(self.byte(cursor)?, YES_NO | 0x19 | 0x1A | 0x1B | 0x1C) {
                        terminators = terminators.wrapping_add(1);
                    }
                    State::CheckNesting
                }
                State::CheckNesting => {
                    if value == i32::from(CHOICE_CASE) && self.byte(cursor)? == CHOICE {
                        if depth as usize >= nesting.len() {
                            return Err(format!("seek from 0x{start:08X}: CHOICE nesting deeper than 4 at 0x{cursor:08X}"));
                        }
                        nesting[depth as usize] = 0;
                        depth += 1;
                    }
                    cursor = self.step(cursor, depth, &mut nesting)?;
                    if selector_class > 1 || i32::from(self.byte(cursor)?) != value {
                        State::CheckSelectedOpcode
                    } else if terminators == 1 {
                        return Ok(cursor);
                    } else {
                        State::DecrementTerminators
                    }
                }
            };
        }
        Err(format!("seek from 0x{start:08X} for {target} did not stop"))
    }

    /// ShowEventChoices(script): option count. 1 takes an operand, 0x0A ends a line, other units are 2 bytes.
    fn choices(&self, script: u32) -> R<(u8, String)> {
        let mut cursor = script;
        let mut count: u8 = 0;
        let mut bytes = Vec::new();
        loop {
            let token = self.text_byte(cursor)?;
            match token {
                0 => break,
                0x0A => {
                    count += 1;
                    bytes.push(0x0A);
                    cursor += 1;
                }
                _ => {
                    let pair = self.ctx.rom.claim(cursor, 2, super::text::FORMAT, self.item)?;
                    bytes.extend_from_slice(pair);
                    cursor += 2;
                }
            }
        }
        let count = count + 1;
        if count > 4 {
            return Err(format!("choice text at 0x{script:08X} has {count} lines; ShowEventChoices keeps 4"));
        }
        let mut dry = self.ctx.rom.dry_cursor(script);
        let rendered = parse_window(&mut dry).unwrap_or_default();
        Ok((count, rendered))
    }
}

/// EventShowText prints the payload with RunMenuScript(0x080177D0/D5) -> PRINT_BUFFER -> DrawWindowText on window 1 or 2,
/// which 0x080177DA/0x080177ED open with flags 0x71 (no text-list flag). The display must stop where SeekEventCommand does.
fn script_text(ctx: &Ctx, item: usize, address: u32, end: u32) -> R<String> {
    let mut window = ctx.rom.dry_cursor(address);
    if parse_window(&mut window).is_ok() && window.address == end {
        return parse_window(&mut ctx.rom.cursor(address, super::text::FORMAT, item));
    }
    let mut list = ctx.rom.dry_cursor(address);
    if parse_list(&mut list).is_ok() && list.address == end {
        return parse_list(&mut ctx.rom.cursor(address, super::text::FORMAT, item));
    }
    Err(format!("event TEXT at 0x{address:08X}: neither DrawWindowText nor the list parser stops at 0x{end:08X}"))
}

fn run(ctx: &Ctx) -> R<()> {
    let names = opcode_names()?;
    let regions = verify_c::regions(&repo_root().join("regions.txt"))?;
    let pinned: HashSet<&str> = match EVENTS {
        Basis::C(files) => files.iter().map(|(path, _)| *path).collect(),
        _ => HashSet::new(),
    };
    let (lengths_id, _) = ctx.item("table.event_command_lengths", LENGTHS, EVENTS, ctx.roots.require(LENGTHS)?);
    let (handlers_id, _) = ctx.item("table.event_command_handlers", HANDLERS, EVENTS, ctx.roots.require(HANDLERS)?);
    ctx.count(lengths_id, "c_enum:EventOpcode (entries read as used)");
    ctx.count(handlers_id, "c_enum:EventOpcode (entries read as used)");

    let (table_id, _) = ctx.item("table.map_event_scripts", MAP_SCRIPTS, EVENTS, ctx.roots.require(MAP_SCRIPTS)?);
    let next_root = ctx.roots.by_address().range(MAP_SCRIPTS + 1..).next().map(|(address, _)| *address).ok_or("no root after the map script table")?;
    let maps = (next_root - MAP_SCRIPTS) / 4;
    ctx.count(table_id, "next_root");
    let mut roots: Vec<(u32, String)> = Vec::new();
    let mut table = Vec::new();
    for map in 0..maps {
        let pointer = le32(ctx.rom.claim(MAP_SCRIPTS + map * 4, 4, "table.map_event_scripts", table_id)?, 0);
        table.push(format!("0x{pointer:08X}"));
        roots.push((pointer, format!("table.map_event_scripts@0x{MAP_SCRIPTS:08X}[{map}]")));
    }
    ctx.set(table_id, json!({ "maps": maps, "scripts": table }));
    for reference in ctx.roots.calls(START_MAP_EVENT_SCRIPT, 1) {
        roots.push((reference.address, reference.location()));
    }

    let mut handler_ok: HashMap<u8, ()> = HashMap::new();
    let length_opcodes = RefCell::new(BTreeSet::new());
    let mut jumps: BTreeMap<usize, Vec<(u32, u32, u32)>> = BTreeMap::new();
    let mut script_items = Vec::new();
    let mut executed: HashSet<u32> = HashSet::new();
    let mut map_definition_reads: BTreeMap<u8, ()> = BTreeMap::new();
    let mut index = 0;
    while index < roots.len() {
        let (root, from) = roots[index].clone();
        index += 1;
        if !ctx.rom.is_data(root) {
            return Err(format!("event script root 0x{root:08X} ({from}) is not ROM data"));
        }
        let (item, new) = ctx.item("event_script", root, EVENTS, vec![from.clone()]);
        if !new {
            continue;
        }
        script_items.push(item);
        let walk = Walk { ctx, lengths_id, length_opcodes: &length_opcodes, item };
        let mut commands: BTreeMap<u32, Value> = BTreeMap::new();
        let mut work = vec![root];
        while let Some(at) = work.pop() {
            if !executed.insert(at) {
                continue;
            }
            let op = walk.byte(at)?;
            if op > LAST_OPCODE {
                return Err(format!("event script 0x{root:08X}: opcode 0x{op:02X} at 0x{at:08X} is past the last EventOpcode"));
            }
            if !handler_ok.contains_key(&op) {
                let handler = le32(ctx.rom.claim(HANDLERS + u32::from(op) * 4, 4, "table.event_command_handlers", handlers_id)?, 0);
                let offset = (handler & !1).wrapping_sub(crate::BASE);
                let source = regions.iter().find(|region| region.start <= offset && offset < region.end).and_then(|region| region.sources.first().cloned());
                match source {
                    Some(source) if pinned.contains(format!("src/{source}").as_str()) => {}
                    other => return Err(format!("opcode 0x{op:02X}: handler 0x{handler:08X} ({other:?}) is not a pinned handler source")),
                }
                handler_ok.insert(op, ());
            }
            let name = names.get(&op).cloned().unwrap_or_else(|| format!("OP_{op:02X}"));
            let mut entry = json!({ "op": name });
            let mut nesting = [0u8; 4];
            let next = match op {
                START_SCRIPTS => {
                    let count = walk.byte(at + 1)?;
                    let mut targets = Vec::new();
                    for slot in 0..u32::from(count) {
                        let pointer = le32(ctx.rom.claim(at + 2 + 4 * slot, 4, FORMAT, item)?, 0);
                        targets.push(format!("0x{pointer:08X}"));
                        roots.push((pointer, format!("event_script@0x{root:08X}:0x{at:08X}")));
                    }
                    entry["scripts"] = json!(targets);
                    at + 2 + 4 * u32::from(count)
                }
                TEXT => {
                    let end = walk.step(at, 0, &mut nesting)?;
                    entry["text"] = json!(script_text(ctx, item, at + 1, end)?);
                    end
                }
                _ => {
                    let length = walk.length(op)?;
                    if length == 0 {
                        return Err(format!("opcode 0x{op:02X} at 0x{at:08X} has length 0"));
                    }
                    let operands = ctx.rom.claim(at, length, FORMAT, item)?;
                    entry["args"] = json!(operands[1..].to_vec());
                    at + length
                }
            };
            let mut successors = Vec::new();
            match class(op) {
                Class::Stop => {
                    if op == CHANGE_MAP {
                        let map = ctx.rom.peek(at + 1, 1)?[0];
                        map_definition_reads.insert(map, ());
                    }
                }
                Class::Jump => {
                    let target = le32(ctx.rom.claim(at + 1, 4, FORMAT, item)?, 0);
                    jumps.entry(item).or_default().push((at, next, target));
                    entry["target"] = json!(format!("0x{target:08X}"));
                    successors.push(target);
                }
                Class::If => {
                    let first = walk.seek(at, SCAN_NEXT, 0)?;
                    let mut taken = first;
                    if walk.byte(first)? == ALTERNATIVE {
                        loop {
                            taken = walk.seek(walk.seek(taken, SCAN_NEXT, 0)?, SCAN_NEXT, 0)?;
                            if walk.byte(taken)? != ALTERNATIVE {
                                break;
                            }
                        }
                        successors.push(first);
                    }
                    successors.push(taken);
                }
                Class::Branch => {
                    successors.push(walk.seek(at, BRANCH_TRUE, 0)?);
                    successors.push(walk.seek(at, BRANCH_FALSE, 0)?);
                }
                Class::Choice => {
                    let (count, text) = walk.choices(at + 2)?;
                    entry["choices"] = json!(count);
                    entry["choice_text"] = json!(text);
                    for choice in 0..count {
                        successors.push(walk.seek(at, i32::from(CHOICE_CASE), choice)?);
                    }
                }
                Class::PulseGrowth => {
                    successors.push(walk.seek(at, PULSE_GROWTH_ACCEPTED, 0)?);
                    successors.push(walk.seek(at, PULSE_GROWTH_DECLINED, 0)?);
                    successors.push(walk.seek(at, SCAN_NEXT, 0)?);
                }
                Class::Next => successors.push(walk.seek(at, SCAN_NEXT, 0)?),
            }
            if class(op) == Class::Next && successors[0] != next {
                return Err(format!("opcode 0x{op:02X} at 0x{at:08X}: seek gives 0x{:08X}, length gives 0x{next:08X}", successors[0]));
            }
            for &target in &successors {
                if !ctx.rom.is_data(target) {
                    return Err(format!("event script 0x{root:08X}: 0x{at:08X} continues at 0x{target:08X}, which is not ROM data"));
                }
                work.push(target);
            }
            entry["next"] = json!(successors.iter().map(|target| format!("0x{target:08X}")).collect::<Vec<_>>());
            commands.insert(at, entry);
        }
        ctx.count(item, "control_flow");
        ctx.set(item, json!({ "commands": commands.into_iter().map(|(at, mut entry)| { entry["at"] = json!(format!("0x{at:08X}")); entry }).collect::<Vec<_>>() }));
    }

    if !map_definition_reads.is_empty() {
        let (id, _) = ctx.item("table.field_map_definitions", FIELD_MAP_DEFINITIONS, EVENTS, ctx.roots.require(FIELD_MAP_DEFINITIONS)?);
        let (positions, _) = ctx.item("table.map_group_positions", MAP_GROUP_POSITIONS, EVENTS, ctx.roots.require(MAP_GROUP_POSITIONS)?);
        for &map in map_definition_reads.keys() {
            let group = ctx.rom.claim(FIELD_MAP_DEFINITIONS + u32::from(map) * 0x20 + 0x1D, 1, "table.field_map_definitions", id)?[0];
            if group != 0 {
                let entry = MAP_GROUP_POSITIONS + u32::from(group - 1) * 6;
                ctx.rom.claim(entry + 2, 2, "table.map_group_positions", positions)?;
                ctx.rom.claim(entry + 4, 2, "table.map_group_positions", positions)?;
            }
        }
    }

    let length_opcodes = length_opcodes.into_inner();
    for op in 0..=LAST_OPCODE {
        let name = names.get(&op).cloned().unwrap_or_else(|| format!("OP_{op:02X}"));
        if !length_opcodes.contains(&op) {
            let reason = if op == START_SCRIPTS || op == TEXT {
                format!("opcode 0x{op:02X} ({name}): SeekEventCommand steps over EVENT_START_SCRIPTS and EVENT_TEXT by their own operands and never reads their gEventCommandLengths entry (src/events/seek_event_command.c)")
            } else {
                format!("opcode 0x{op:02X} ({name}): SeekEventCommand reads gEventCommandLengths[opcode] only for a command it steps over (src/events/seek_event_command.c); no command the walked event scripts execute or step over has this opcode")
            };
            ctx.unread(lengths_id, LENGTHS + u32::from(op), 1, &reason)?;
        }
        if !handler_ok.contains_key(&op) {
            ctx.unread(
                handlers_id,
                HANDLERS + u32::from(op) * 4,
                4,
                &format!("opcode 0x{op:02X} ({name}): RunEventScripts reads gEventCommandHandlers[opcode] only for the command at a script cursor (src/events/run_event_scripts.c); no command the walked event scripts execute has this opcode"),
            )?;
        }
    }

    let scripts: HashSet<usize> = script_items.iter().copied().collect();
    let mut spans: BTreeMap<usize, Vec<(u32, u32)>> = BTreeMap::new();
    for claim in ctx.rom.claims().iter().filter(|claim| scripts.contains(&claim.item)) {
        spans.entry(claim.item).or_default().push((claim.start, claim.end));
    }
    for (item, list) in &mut spans {
        list.sort();
        let mut merged: Vec<(u32, u32)> = Vec::new();
        for &(start, end) in list.iter() {
            match merged.last_mut() {
                Some(last) if start <= last.1 => last.1 = last.1.max(end),
                _ => merged.push((start, end)),
            }
        }
        for pair in merged.windows(2) {
            let (start, end) = (pair[0].1, pair[1].0);
            let unowned = {
                let owners = ctx.rom.owners();
                (start..end).all(|address| ctx.rom.is_data(address) && owners[(address - crate::BASE) as usize] == 0)
            };
            if !unowned {
                continue;
            }
            let Some(&(at, _, target)) = jumps.get(item).and_then(|list| list.iter().find(|(_, after, target)| *after == start && *target == end)) else {
                return Err(format!("{}: bytes 0x{start:08X}..0x{end:08X} between its reads are unread and no JUMP of the script skips exactly them", ctx.name(*item)));
            };
            ctx.unread(
                *item,
                start,
                end - start,
                &format!("bytes between the JUMP at 0x{at:08X} and its target 0x{target:08X}: EventJump sets the cursor to the target (src/events/commands/event_jump.c), and no executed command or SeekEventCommand step of the walked scripts reaches them"),
            )?;
        }
    }
    Ok(())
}
