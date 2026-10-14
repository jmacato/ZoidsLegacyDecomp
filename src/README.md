# Source layout

The directories group source files by game system. These links show the main functions, data structures, and related code.

## Start here

- [Game state machine](game/run_game_state_machine.c): game modes and the functions that handle them.
- [Event interpreter](events/run_event_scripts.c): event commands and the code that runs scripts.
- [Battle data](battle/battle.h): unit state, stats, and effects.
- [Task scheduler](engine/tasks.h): task state and the rules that select which task runs next.

## Battles and Zoids

- [Unit sprites and gauges](battle/battle_display.h).
- [Animation scripts and resources](battle/battle_animation.h): effect stages, projectile fields, and effect callbacks.
- [Queued battle results](battle/present_queued_battle_effect_results.c): popups, camera positions, and unit destruction.
- [Story result checks](battle/check_battle_result_and_play_story_scenes.c): special endings and dialogue triggers.
- [Pulse effect growth](zoids/update_pulse_effects_from_emotion_growth.c): four emotion tracks and [rules for adding effects](zoids/add_pulse_effect.c).
- [Zoid customization](ui/run_zoid_customization_menu.c): power, EP recovery, defense bonuses, and palette selection.
- [Battle combinations](events/commands/event_combine_battle_zoids.c): formation checks, departure, animation, and arrival.

Animation callbacks control dust, shields, sweeping windows, falling streaks, and repeating background sprites.

## Menus and text

- [Window fields and text formats](ui/window.h).
- [Team lists, equipment details, and repairs](ui/player_selection.h): selection records and menu stages.
- [Name and battle quote entry](ui/name_entry.h): character tables, input, and text editors.

## Maps and graphics

- [Map display](field/field_display.h): map graphics, decoration sprites, encounters, and scanline state.
- [Camera projection](graphics/camera.h).
- [Screen effects](graphics/screen_effects.h): scanline masks and screen transition state.

## Directories

| Directory | Contents |
| --- | --- |
| [game/](game/) | Main state machine, mode IDs, and mode handlers in [modes/](game/modes/) |
| [battle/](battle/) | Unit state, effects, recovery items, and battle stat calculations |
| [events/](events/) | Event interpreter, flags, command handlers in [commands/](events/commands/), and scripted scenes in [scenes/](events/scenes/) |
| [field/](field/) | Map transitions, tile loading, actors, decorations, and random encounters |
| [zoids/](zoids/) | Zoid forms, base stats, equipment bonuses, and abilities |
| [ui/](ui/) | Windows, tile allocation, and menu scripts |
| [graphics/](graphics/) | Sprites, scanline events, HBlank callbacks, and graphics transfers |
| [audio/](audio/) | Songs, music players, sequence commands, and sound driver assembly. [nonmatching/](audio/nonmatching/) contains C versions of hand-written driver routines. |
| [save/](save/) | Save blocks and SRAM access |
| [engine/](engine/) | Startup, frame updates, task scheduling, input, deferred callbacks, and fixed-point math |
| [runtime/](runtime/) | BIOS calls, startup, interrupt handling, and compiler support |
| [unnamed/](unnamed/) | Assembly fragments that preserve matching compiler output |

## Original addresses and matching code

The [source map](../source-map.csv) links original filenames to current paths, ROM addresses, region IDs, and function names.

- Headers have no ROM region.
- Assembly fragments list the region that contains them.
- Each region stays in a separate compilation unit so that its bytes match the ROM.
- The fragments in [unnamed/](unnamed/) preserve compiler output for menus and battle routines.
