#include "m2c_prelude.h"

s16 func_080ECD30(s32);

s32 sub_08092B04(u16 arg0, s32 arg1) {
    s32 ret;
    register s32 value_r1 asm("r1");

    value_r1 = (s16)arg1;
    asm volatile("" : "+r"(value_r1));
    if (value_r1 == 0) {
        goto zero;
    }
    ret = (s16)func_080ECD30((s32)(arg0 << 16) >> 8);
    goto done;
zero:
    ret = 0x7FFF;
done:
    return ret;
}
