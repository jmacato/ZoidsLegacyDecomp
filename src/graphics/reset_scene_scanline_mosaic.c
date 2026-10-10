#include "m2c_prelude.h"
#include "screen_effects.h"

void ResetSceneScanlineMosaic(void) asm("func_080BA86C");

void ResetSceneScanlineMosaic(void) {
    *(u8 *)SCENE_MOSAIC_STATE_RAM = SCENE_SCANLINE_DISABLED;
}
