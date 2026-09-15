#include "m2c_prelude.h"

s32 func_08097C24(u8, s32, s32);

s32 sub_08097D80(u8 *arg0, s32 arg1, s32 arg2) {
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
    ret = func_08097C24(*ptr, value_r6, offset);
    offset += 0x20;
    ptr++;
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
