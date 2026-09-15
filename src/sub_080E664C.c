#include "m2c_prelude.h"

extern volatile u32 D_0202F090;

void sub_080E664C(u8 index)
{
    D_0202F090 &= ~(1U << index);
}
