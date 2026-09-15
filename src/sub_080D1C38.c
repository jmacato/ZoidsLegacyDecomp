#include "m2c_prelude.h"
extern u8 D_02034862;
extern u8 D_02034863;
extern u8 D_02034868;
M2C_UNK func_80ECD2C(M2C_UNK, M2C_UNK, M2C_UNK);       /* extern */

void sub_080D1C38(void) {
    *(s8 *)((u32)&D_02034862) = 0;
    *(s8 *)((u32)&D_02034863) = 0;
    *(s8 *)((u32)&D_02034868) = 0;
    func_80ECD2C(0x080007A4, 0x0300605C, 0x04000028);
}
