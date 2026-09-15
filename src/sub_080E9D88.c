#include "m2c_prelude.h"
extern u8 D_02034B4C[];
s32 sub_080E9D88(u8 arg0, u8 arg1) {
    u8 *p = D_02034B4C + (arg0 * 0x1380) + (arg1 * 0x270);
    if ((*(u8 *)(p + 0) != 0) && !(8 & *(u16 *)(p + 4))) {
        return 1;
    }
    return 0;
}
