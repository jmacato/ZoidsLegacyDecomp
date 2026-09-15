#include "m2c_prelude.h"
extern s8 D_030032D4[];
void sub_080930E8(void) {
    *(volatile s16 *)0x04000208 = 0;
    *(u16 *)0x04000200 &= 0xFF3F;
    *(volatile s16 *)0x04000208 = 1;
    *(s16 *)0x04000128 = 0x2003;
    M2C_FIELD((void *)0x0400010C, s32 *, 0) = 0xABFB;
    M2C_FIELD((void *)0x0400010C, s16 *, 0xF6) = 0xC0;
    D_030032D4[6] = 0;
}
