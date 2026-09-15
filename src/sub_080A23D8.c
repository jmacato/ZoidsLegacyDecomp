#include "m2c_prelude.h"
M2C_UNK func_08096308(s32, s32);                    /* extern */
M2C_UNK func_080A016C(u8, s32, s32);                /* extern */
M2C_UNK func_080ED17C(s32);                         /* extern */

s32 sub_080A23D8(u8 arg0, void **arg1) {
    *(u8 *)0x02030664 = 1;
    *(u8 *)0x02032B98 = M2C_FIELD(*arg1, u8 *, 1);
    *(s32 *)0x02021690 = 7;
    func_08096308(0x10, 0);
    *(u8 *)0x02030664 = 2;
    do {
        func_080ED17C(1);
    } while (*(u8 *)0x02030664 != 1);
    func_080A016C(arg0, -1, 0);
    return 0;
}
