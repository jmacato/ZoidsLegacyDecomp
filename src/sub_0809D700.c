#include "m2c_prelude.h"
extern u8 D_020324BB[]; extern u8 D_020324E8[];
void sub_0809D700(void) {
    u8 i;
    for (i = 0; i <= 0x29; i++) {
        D_020324BB[i] |= 0xFF;
        *(s32 *)(D_020324E8 + i * 4) = 0;
    }
}
