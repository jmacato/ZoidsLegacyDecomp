#include "m2c_prelude.h"
M2C_UNK func_80E542C(void *);                          /* extern */
M2C_UNK func_80E5538();                                /* extern */
M2C_UNK func_80E5674(void *);                          /* extern */
M2C_UNK func_80E570C(void *, s32, s32);                /* extern */
M2C_UNK func_80E57D0(void *);                          /* extern */
M2C_UNK func_80E6830(void *, s32, s32);                /* extern */

void sub_080E5880(void *arg0, s32 arg1) {
    func_80E5538();
    func_80E542C(arg0);
    func_80E5674(arg0);
    func_80E6830(arg0, arg1, 0);
    func_80E57D0(arg0);
    func_80E570C(arg0, arg1, 0);
    func_80E57D0(arg0);
    if ((s32) M2C_FIELD(arg0, s16 *, 6) > (s32) (s16) M2C_FIELD(arg0, u16 *, 0x3A)) {
        M2C_FIELD(arg0, s16 *, 6) = (s16) M2C_FIELD(arg0, u16 *, 0x3A);
    }
    if ((s32) M2C_FIELD(arg0, s16 *, 8) > (s32) (s16) M2C_FIELD(arg0, u16 *, 0x3E)) {
        M2C_FIELD(arg0, s16 *, 8) = (s16) M2C_FIELD(arg0, u16 *, 0x3E);
    }
}
