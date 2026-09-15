#include "m2c_prelude.h"

s32 sub_0809716C(s32 arg0) {
    u8 *scratch_base;
    u8 *return_base;
    s32 index;
    s32 first;
    register s32 key_r3 asm("r3");

    key_r3 = (u8)arg0;
    asm volatile("" : "+r"(key_r3));
    index = 0;
    scratch_base = (u8 *)0x0200A8A0;
    first = scratch_base[0x13];
    {
        register u8 *captured_r5 asm("r5");
        captured_r5 = scratch_base;
        asm volatile("" : "+&r"(captured_r5) : "r"(scratch_base));
        return_base = captured_r5;
    }
    if (first != key_r3) {
        register u8 *loop_base asm("r4");
        s32 stride;

        loop_base = return_base;
        asm volatile("" : "+r"(loop_base));
        stride = 0x4D0;
        do {
            index = (u8)(index + 1);
            if ((u32)index > 9U) {
                break;
            }
        } while (loop_base[index * stride + 0x13] != key_r3);
    }
    {
        s32 result;
        result = index * 0x4D0;
        result += (s32)return_base;
        return result;
    }
}
