#include "m2c_prelude.h"
u32 sub_080CA560(void) {
    u8 temp_r1;

    temp_r1 = *(u8 *)0x0203EFA8;
    return (u32) ((0 - temp_r1) | temp_r1) >> 0x1F;
}
