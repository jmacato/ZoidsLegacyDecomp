#include "m2c_prelude.h"
extern u32 D_0202F090;

void sub_080E65B4(u8 arg0) {
    if ((u8)(arg0 - 1) <= 3) D_0202F090 &= 0xFFFFFFE1;
    else if ((u8)(arg0 - 5) <= 5) D_0202F090 &= 0xFFFFF81F;
    else if ((u8)(arg0 - 11) <= 5) D_0202F090 &= 0xFFFE07FF;
    else if (arg0 == 18) D_0202F090 &= 0xFFF7FFFF;
    else if (arg0 == 19) D_0202F090 &= 0xFFFBFFFF;
    D_0202F090 |= 1 << arg0;
}
