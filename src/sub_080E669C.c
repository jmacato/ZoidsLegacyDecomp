#include "m2c_prelude.h"
s32 sub_080E669C(void) {
    register u8 *ptr asm("r3");
    register s32 temp_r2 asm("r2");
    register s32 base asm("r1");

    ptr = (u8 *)0x02030554;
    temp_r2 = *ptr;
    base = 0x02030494;
    {
        s32 ret = (temp_r2 * 0x18) + base;
        *ptr = temp_r2 + 1;
        return ret;
    }
}
