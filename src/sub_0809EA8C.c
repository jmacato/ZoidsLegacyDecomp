#include "m2c_prelude.h"
extern u8 D_020324B9;

void sub_0809EA8C(void) {
    register volatile u16 *p asm("r1");
    if (D_020324B9 != 0) {
        while ((*(volatile u16*)0x04000004 & 2) == 0)
            ;
        p = (volatile u16*)0x0400000E;
        *p = 0x300;
        p += 7;
        *(volatile u32*)p = 0;
        *(volatile u16*)0x04000050 = *(volatile u16*)0x04000050 & 0xf7f7;
    }
}
