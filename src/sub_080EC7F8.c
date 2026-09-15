#include "m2c_prelude.h"

typedef struct {
    u8 flags;
    u8 pad01[0x15];
    u8 field16;
    u8 pad17;
    u8 field18;
    u8 pad19;
    u8 field1A;
} SoundChannel;

void sub_080EC7F8(SoundChannel *channel)
{
    register SoundChannel *state asm("r1") = channel;
    register s32 unused_zero asm("r2") = 0;
    register s32 value asm("r0") = 0;

    asm volatile("" : "+r"(unused_zero));
    state->field1A = value;
    state->field16 = value;
    value = state->field18;
    if (value == 0) {
        value = 0xC;
    } else {
        value = 3;
    }
    {
        register u8 flags asm("r2") = state->flags;

        value |= flags;
        state->flags = value;
    }
}
