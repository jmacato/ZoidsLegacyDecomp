#include "m2c_prelude.h"
M2C_UNK func_809223C(u8);                              /* extern */
M2C_UNK func_8092604();                                /* extern */
M2C_UNK func_809279C();                                /* extern */
M2C_UNK func_80946A0();                                /* extern */
M2C_UNK func_8095154();                                /* extern */
M2C_UNK func_8096278();                                /* extern */
M2C_UNK func_8096774();                                /* extern */
M2C_UNK func_80972D4();                                /* extern */
M2C_UNK func_80ECD40(s32);                             /* extern */
M2C_UNK func_80ED174();                                /* extern */

void sub_080921D4(void) {
    s32 temp_r1;

loop_1:
    func_8092604();
    func_80ED174();
    func_80972D4();
    func_8095154();
    func_80946A0();
    func_8096774();
    func_8096278();
    func_809279C();
    func_809223C(*(u8 *)0x03000075);
    temp_r1 = 0x3FF & *(u16 *)0x0300000C;
    if (temp_r1 == 0x30C) {
        temp_r1 &= *(u16 *)0x0300000E;
        if (temp_r1) {
            func_80ECD40(0xFF);
        }
    }
    *(s32 *)0x03000078 += 1;
    goto loop_1;
}
