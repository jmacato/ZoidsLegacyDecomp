#include "m2c_prelude.h"
s32 func_80E58DC(s32, u8, void *);                     /* extern */
M2C_UNK func_80E59A0(s32, void *);                     /* extern */
M2C_UNK func_80E6994(s32, s32, M2C_UNK, u16, void *);  /* extern */

s32 sub_080E59BC(s32 arg0, s32 arg1, M2C_UNK arg2, u8 arg3, void *arg4) {
    u8 temp_r6;
    s32 off;

    temp_r6 = arg3;
    if ((func_80E58DC(arg0, temp_r6, arg4) << 0x18) != 0) {
        if (!(1 & M2C_FIELD(arg4, u16 *, 2))) {
            func_80E59A0(arg0, arg4);
            off = temp_r6 * 4;
            func_80E6994(arg0, arg1, arg2, M2C_FIELD((arg0 + off), u16 *, 0x52), arg4);
        }
        return 1;
    }
    return 0;
}
