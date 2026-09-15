#include "m2c_prelude.h"
extern u8 D_02034B4C[];
extern u8 D_000027BE[];

s32 sub_080E8C48(u8 arg0, u8 arg1) {
    register u8 temp_r2 asm("r2");
    u8 *ptr;

    temp_r2 = arg1;
    ptr = D_02034B4C + (s32)D_000027BE;
    switch (*(u8 *)(arg0 + (s32)ptr)) {
    case 47:
        if (temp_r2 == 4) {
            return 1;
        }
        break;
    case 48:
    case 46:
        if (temp_r2 == 1) {
            return 1;
        }
        break;
    }
    return 0;
}
