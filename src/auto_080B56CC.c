#include "m2c_prelude.h"
s32 func_8094484(M2C_UNK, M2C_UNK, s32, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8094554(s32);                             /* extern */
M2C_UNK func_8098BB4(M2C_UNK);                         /* extern */
M2C_UNK func_809A94C(s32, s32, s32, s32, s32);         /* extern */

void sub_080B56CC(void) {
    s32 temp_r4;

    func_809A94C(5, 0, 0, 0, 0);
    temp_r4 = func_8094484(0x08359850, 0x0835985C, 0, 8, 0x68, 0, 0, 8, 0);
    func_8098BB4(0x080035DE);
    func_8094554(temp_r4);
}
