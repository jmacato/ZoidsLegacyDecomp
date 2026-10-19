//! RunBattleScene loads LoadSpriteGraphicsFromTable(0x087AC9F8 + id * 8, 0, ...) with id = the s16 that StartBattleAnimation stores at
//! record +0x264 for callback kind 0x59: the header's first resource id + 1.

use super::graphics::sprite_graphics;
use super::Port;
use crate::basis::Basis;
use crate::rom::R;
use crate::run::Ctx;

const BATTLE_SCENE_OBJECTS: Basis = Basis::C(&[
    ("src/game/modes/run_battle_scene.c", "1d8942aaaced975a60c680c0ca681e138bf98c69"),
    ("src/battle/start_battle_animation.c", "f0ace9715b59cdfd3ac14018b7269ae91c3cb972"),
]);

pub const PORT: Port = Port { name: "battle_scene_objects", bases: &[BATTLE_SCENE_OBJECTS], run };

const BATTLE_STREAK_GRAPHICS_TABLE: u32 = 0x087A_C9F8;
const RESOURCE_HEADERS: u32 = 0x087D_2338;
const SCENE_OBJECT_CALLBACK_KIND: u64 = 0x59;

fn run(ctx: &Ctx) -> R<()> {
    let Some(data) = ctx.data("table.battle_animation_resource_headers", RESOURCE_HEADERS) else {
        return Err("battle animation resource headers were not ported first".into());
    };
    for header in data["headers"].as_array().into_iter().flatten() {
        if header["callback_kind"].as_u64() != Some(SCENE_OBJECT_CALLBACK_KIND) {
            continue;
        }
        let Some(first) = header["resource_ids"].get(0).and_then(|value| value.as_i64()) else {
            return Err(format!("header {} with callback kind 0x59 has no resource id", header["index"]));
        };
        let id = u32::try_from(first + 1).map_err(|_| format!("header {}: resource id {first} + 1 is negative", header["index"]))?;
        let from = format!("table.battle_animation_resource_headers@0x{RESOURCE_HEADERS:08X}[{}]+0x264", header["index"]);
        sprite_graphics(ctx, BATTLE_STREAK_GRAPHICS_TABLE, id, false, from)?;
    }
    Ok(())
}
