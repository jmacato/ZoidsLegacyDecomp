#include "m2c_prelude.h"

extern volatile u8 D_02034863;
extern volatile u16 D_02034864;

void sub_080D1D44(void)
{
    D_02034863 = 3;
    D_02034864 = 0x40;
}
