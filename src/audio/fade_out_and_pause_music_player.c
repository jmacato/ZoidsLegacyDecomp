#include "sound_engine.h"

void FadeOutAndPauseMusicPlayer(struct MusicPlayerControlState *state, u16 interval) asm("func_080EB8FC");

void FadeOutAndPauseMusicPlayer(struct MusicPlayerControlState *state, u16 interval) {
    register u32 signature asm("r3") = state->signature;

    if (signature == SOUND_ENGINE_SIGNATURE) {
        state->player.fadeCounter = interval;
        state->player.fadeInterval = interval;
        state->player.fadeVolume = 0x101;
    }
}
