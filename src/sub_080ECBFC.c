#include "m2c_prelude.h"

s32 sub_080ECBFC(u8 *arg0, u8 *arg1, s32 arg2) {
    register s32 count asm("r3");
    register s32 sentinel asm("r0");

    count = arg2;
    {
        register u16 *reg asm("r2");
        register u16 value asm("r0");
        u16 mask;

        reg = (u16 *)0x04000204;
        asm volatile("" : "+r"(reg));
        value = *reg;
        asm volatile("" : "+r"(value));
        mask = 0xFFFC;
        value &= mask;
        value |= 3;
        *reg = value;
    }
    count -= 1;
    sentinel = 1;
    sentinel = -sentinel;
    if (count != sentinel) {
        register s32 loop_sentinel asm("r2");

        loop_sentinel = sentinel;
        asm volatile("" : "+r"(loop_sentinel));
        do {
            u8 right;
            u8 left;

            right = *arg1;
            left = *arg0;
            arg0 += 1;
            arg1 += 1;
            if (right != left) {
                return (s32)(arg1 - 1);
            }
            count -= 1;
        } while (count != loop_sentinel);
    }
    return 0;
}
