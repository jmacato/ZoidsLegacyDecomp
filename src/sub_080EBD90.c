#include "m2c_prelude.h"
void sub_080EBD90(void) {
    s32 *temp_r2;
    s32 temp_r3;
    temp_r2 = *(s32 **)0x03007FF0;
    temp_r3 = temp_r2[0];
    if (temp_r3 != 0x68736D53) {
        *(u16 *)0x040000C6 = 0xB600;
        *(volatile u8 *)((s32)temp_r2 + 4);
        *(u8 *)((s32)temp_r2 + 4) = 0;
        temp_r2[0] = temp_r3 - 0xA;
    }
}
