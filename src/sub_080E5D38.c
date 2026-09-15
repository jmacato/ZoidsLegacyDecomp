#include "m2c_prelude.h"
s32 sub_080E5D38(u16 arg0, u8 arg1) {
    extern u8 D_020218E4;
    extern u8 D_off_6934;
    u16 temp_r0;
    u8 temp_r0_2;
    register u8 temp_r2 asm("r2");
    u32 base;
    u8 *ptr;

    temp_r0 = arg0;
    temp_r2 = arg1;
    base = (u32)&D_020218E4 + (u32)&D_off_6934;
    ptr = (u8 *)(temp_r0 + base);
    temp_r0_2 = *ptr;
    if ((u32)temp_r0_2 > (u32)temp_r2) {
        register s32 value asm("r0");
        value = temp_r0_2;
        asm volatile("" : "+r"(value));
        value -= temp_r2;
        asm volatile("" : "+r"(value));
        *ptr = value;
        return 1;
    }
    {
        register s32 zero asm("r0");
        zero = 0;
        asm volatile("" : "+r"(zero));
        *ptr = zero;
        return zero;
    }
}
