#include "m2c_prelude.h"

struct LibcRandomStateView {
    u8 reserved00[0x58];
    u32 random_seed;
};

u32 NextLibcRandom(void) asm("func_080ED0A4");

u32 NextLibcRandom(void) {
    struct LibcRandomStateView *state = *(struct LibcRandomStateView **)0x087F3128;
    u32 next = state->random_seed * 0x41C64E6D + 0x3039;
    state->random_seed = next;
    return next & 0x7FFFFFFF;
}
