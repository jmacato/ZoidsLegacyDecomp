#include "m2c_prelude.h"
M2C_UNK func_08094330();
M2C_UNK func_08096308(s32, s32);
s32 func_0809669C();
M2C_UNK func_08096FBC(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
M2C_UNK func_08098BB4(M2C_UNK);
M2C_UNK func_0809AB44(s32, s32, s32, s32, s32);
M2C_UNK func_080ED17C(s32);

s32 sub_0809B8C4(void) {
    *(s16 *)0x0300004C = 0x1840;
    func_08096FBC(3, 1, 0, 0x35C, 0x3C0, 0, 0xE, 0, 0x3E6, 0xF);
    func_0809AB44(2, 3, 0, 0, 1);
    func_08094330();
    func_08098BB4(0x08000934);
    func_08096308(0xF, 0);
    func_08098BB4(0x08000AE0);
    func_08096308(0x10, 0);
    goto check_input;

delay:
    func_080ED17C(1);
check_input:
    if ((func_0809669C() << 0x18) == 0) {
        goto delay;
    }
    if ((*(u8 *)0x0200A882 == 1) && (*(u8 *)0x0200A880 == 0)) {
        return 1;
    }
    return 0;
}
