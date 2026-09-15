#include "m2c_prelude.h"

typedef struct {
    u8 pad00[0x8C];
    s32 field8C;
    s32 field90;
} EffectState;

extern volatile u16 D_03000050;

void sub_080DF82C(EffectState *state)
{
    s32 *field8C = &state->field8C;
    s32 *field90 = &state->field90;

    *field90 = 0;
    *field8C = 0;
    D_03000050 = 0x1010;
}
