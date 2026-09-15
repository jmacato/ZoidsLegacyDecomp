#include "m2c_prelude.h"
void func_809256C(void);

void sub_08092348(void) {
    u8 *temp_r1;
    temp_r1 = *(u8 **)0x03000880;
    if (temp_r1 != (u8 *)-1) {
        *(u8 **)0x03000884 = temp_r1;
        if (*(u8 *)0x03000888 != 0) {
            *(volatile u16 *)0x04000200 |= 4;
            *(volatile u16 *)0x04000004 |= 0x20;
            *(u8 *)0x03000888 = 0;
        }
        *(volatile u16 *)0x04000004 = (**(u8 **)0x03000884 << 8) | (0xFF & *(volatile u16 *)0x04000004);
        return;
    }
    if (*(u8 *)0x03000888 != 0) {
        *(volatile u16 *)0x04000200 = 0xFFFB & *(volatile u16 *)0x04000200;
        *(volatile u16 *)0x04000004 = 0xFFDF & *(volatile u16 *)0x04000004;
        func_809256C();
    }
}
