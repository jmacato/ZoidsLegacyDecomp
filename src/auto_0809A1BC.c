#include "m2c_prelude.h"
M2C_UNK func_80ECD28(u16 *, u16 *, u32);               /* extern */
M2C_UNK func_80ECD38(void *, u16 *);                   /* extern */

void sub_0809A1BC(void *arg0, u16 *arg1, u16 *arg2) {
    func_80ECD38(arg0, arg2);
    if (arg1 == (u16 *)0x05000000) {
        *arg2 = *arg1;
    }
    func_80ECD28(arg2, arg1, (u32) ((M2C_FIELD(arg0, u8 *, 1) | (M2C_FIELD(arg0, u8 *, 2) << 8) | (M2C_FIELD(arg0, u8 *, 3) << 0x10)) << 9) >> 0xB);
}
