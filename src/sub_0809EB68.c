#include "m2c_prelude.h"
extern s32 D_03000054[];

void sub_0809EB68(u8 arg0) {
    u8 *var_r4;
    register u8 var_r0 asm("r0");
    u8 t;

    var_r4 = (u8 *)0x020324B8;
    switch (*var_r4) {
    case 1:
        if (arg0 != 0) {
            *(u8 *)0x020324B8 = 2;
        case 2:
            t = *(u8 *)0x020324B9;
            var_r4 = (u8 *)0x020324B9;
            if (t != 0) {
                register volatile u16 *reg asm("r1") = (volatile u16 *)0x0400000E;
                *reg = 0x1F0E;
                if (arg0 == 0) {
                    reg += 7;
                    *reg = D_03000054[6] >> 8;
                    reg += 1;
                    *reg = D_03000054[7] >> 8;
                    reg += 25;
                    *reg = *(volatile u16 *)0x0300004E;
                    goto block_12;
                }
                goto block_13;
            }
        block_12:
            if (arg0 != 0) {
            block_13:
                var_r0 = *(u8 *)0x02030666 | *(u8 *)0x020324BA;
                goto block_17;
            }
        }
        return;
    case 3:
        if (arg0 != 0) {
            *(volatile u16 *)0x0400000E = 0x300;
            *(volatile u8 *)0x03000074 &= 0xEF;
            var_r0 = 0;
        block_17:
            *var_r4 = var_r0;
        }
        break;
    }
}
