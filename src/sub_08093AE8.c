#include "m2c_prelude.h"
M2C_UNK func_8093B7C();
M2C_UNK func_8094290(s32, M2C_UNK);
M2C_UNK func_80ECD2C(M2C_UNK, M2C_UNK, M2C_UNK);
extern u8 D_03003430;
extern u16 D_030033C4[];

void sub_08093AE8(s32 arg0, u8 arg1) {
    *(u8 *)0x0300342C = 0;
    *(u8 *)0x0300342D = arg1;
    if (arg1 == 1) {
        func_80ECD2C(0x08000638, &D_03003430, 0x0400001C);
    }
    *(s32 *)0x03003428 = arg0;
    D_030033C4[22] = D_030033C4[6] + 1;
    func_8093B7C();
    if (arg1 == 1) {
        *(s16 *)0x04000208 = 0;
        func_8094290(0, &D_03003430);
        *(s16 *)0x04000208 = (s16)arg1;
    }
}
