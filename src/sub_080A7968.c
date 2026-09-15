#include "m2c_prelude.h"
M2C_UNK func_08092D8C(s32, M2C_UNK);                /* extern */
M2C_UNK func_08092E0C(s32);                         /* extern */
M2C_UNK func_0809534C();                            /* extern */
M2C_UNK func_0809538C(s32, s32, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_08096308(s32, s32);                    /* extern */
s32 func_0809669C();                                /* extern */
M2C_UNK func_0809A5B4(s32, s32, s32, s32, s32);     /* extern */
M2C_UNK func_080D0AF0(s32);                         /* extern */
M2C_UNK func_080D12A0(s32, s32);                    /* extern */
M2C_UNK func_080ECD2C(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */
M2C_UNK func_080ED17C(s32);                         /* extern */

void sub_080A7968(void) {
    u32 var_r4;

    *(s32 *)0x02021690 = 0xA;
    func_080ED17C(1);
    func_080D0AF0(0);
    func_080D12A0(0, 0);
    *(s16 *)0x0300004C = 0x1140;
    *(s16 *)0x04000008 = 0x87;
    *(s32 *)0x03000054 = 0;
    func_0809A5B4(0, 0, 1, 0, 1);
    *(s16 *)0x05000000 = 0;
    *(s8 *)0x0203198D = 0;
    *(u8 *)0x03000074 |= 8;
    *(s8 *)0x0203198C = 1;
    func_080ECD2C(0x08000844, 0x030060FC, 0x04000014);
    func_08092D8C(4, 0x080A7915);
    func_0809538C(1, 0xF0, 0x148C, 0, 0, 0, 0x3F, 0);
    func_08096308(1, 0x10);
    goto loop_2;
loop_1:
    func_080ED17C(1);
loop_2:
    if ((func_0809669C() << 0x18) == 0) {
        goto loop_1;
    }
    var_r4 = 0;
    do {
        func_080ED17C(1);
        var_r4 += 1;
    } while (var_r4 <= 0x12BU);
    func_08096308(2, 0x10);
    goto loop_4;
loop_3:
    func_080ED17C(1);
loop_4:
loop_8:
    if ((func_0809669C() << 0x18) == 0) {
        goto loop_3;
    }
    func_08092E0C(4);
    *(s8 *)0x0203198C = 3;
    func_0809534C();
    *(s32 *)0x02021690 = -1;
    func_080ED17C(1);
}
