#include "m2c_prelude.h"
extern volatile u8 D_0203EFA8;
extern u8 *D_020372F4;
extern u8 D_0203EF70[];

void func_080CA570(u8, u8);

void sub_080CB2EC(u16 arg0) {
    u8 i;

    i = 0;
    if (i < D_0203EFA8) {
        register u8 **base_slot asm("r6");
        u8 *base;

        base_slot = &D_020372F4;
        do {
            base = *base_slot;
            base += D_0203EF70[i] * 4;
            base += 0x52;
            if (*(u16 *)base != arg0) {
                func_080CA570(i, 0xFF);
                i = (u8)(i - 1);
            }
            i = (u8)(i + 1);
        } while (i < D_0203EFA8);
    }
}
