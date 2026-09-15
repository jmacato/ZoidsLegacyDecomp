#include "m2c_prelude.h"

typedef struct {
    u8 pad00[0x24];
    u16 field24;
    u16 field26;
    u16 field28;
    u8 pad2A[10];
    u32 signature;
} SoundState;

void sub_080EB6B0(SoundState *state, u16 value)
{
    register u32 signature asm("r3") = state->signature;

    if (signature == 0x68736D53) {
        state->field26 = value;
        state->field24 = value;
        state->field28 = 0x100;
    }
}
