#include "m2c_prelude.h"

s32 func_08097A2C(s32, s32, s32, s32);

s32 sub_08097BF4(u8 *arg0, s32 arg1, s32 arg2) {
    u8 *ptr;
    s32 offset;
    s32 ret;
    register s32 value_r6 asm("r6");

    ret = (s32)arg0;
    ptr = arg0;
    offset = arg2;
    value_r6 = (u8)arg1;
    asm volatile("" : "+r"(value_r6));
    goto test;
loop:
    {
        register s32 key_r0 asm("r0");
        register s32 high_r1 asm("r1");
        high_r1 = ptr[0] << 8;
        key_r0 = ptr[1] | high_r1;
        ret = func_08097A2C(key_r0, value_r6, offset, offset + 0x20);
    }
    offset += 0x40;
    ptr += 2;
test:
    {
        register s32 loop_value_r1 asm("r1");
        asm volatile("ldrb %0, [%1]"
                     : "=r"(loop_value_r1)
                     : "r"(ptr));
        if (loop_value_r1 != 0) {
            goto loop;
        }
    }
    return ret;
}
