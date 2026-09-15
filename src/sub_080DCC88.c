#include "m2c_prelude.h"

typedef struct {
    u8 pad00[0x8C];
    s32 field8C;
    s32 field90;
    s32 field94;
} EffectState;

extern volatile u16 D_03000050;

void sub_080DCC88(EffectState *state)
{
    s32 *field8C = &state->field8C;
    s32 *field90 = &state->field90;
    s32 *field94 = &state->field94;

    *field94 = 0;
    *field90 = 0;
    *field8C = 0;
    D_03000050 = 0x1010;
}
