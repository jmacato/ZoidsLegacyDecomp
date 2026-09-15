#include "m2c_prelude.h"

typedef struct {
    u8 pad00[0x8C];
    s32 field8C;
} EffectState;

extern volatile u16 D_03000050;

void sub_080DFB4C(EffectState *state)
{
    state->field8C = 0;
    D_03000050 = 0x1010;
}
