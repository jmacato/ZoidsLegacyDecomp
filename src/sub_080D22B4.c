#include "m2c_prelude.h"

extern void *func_08094374();

void *sub_080D22B4(void *arg0, u16 arg1, u16 arg2, u16 arg3,
                   u16 arg4, u16 arg5, u16 arg6, s32 arg7,
                   s32 arg8, s32 arg9) {
    s32 angle;

    arg9 <<= 24;
    if (arg9 != 0) {
        s32 signed_angle = (s16)arg3;

        if (arg7 & 0x1000) {
            angle = 0x100 - signed_angle;
            __asm__ volatile ("" : : : "memory");
            angle <<= 16;
        } else {
            angle = 0xF0;
            angle -= signed_angle;
            angle <<= 16;
        }
    } else {
        angle = arg3 << 16;
    }

    return func_08094374(arg0, arg1, arg2, angle >> 16, (s16)arg4,
                        arg5, arg6, arg7, arg8);
}
