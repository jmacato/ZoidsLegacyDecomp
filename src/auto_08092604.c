#include "m2c_prelude.h"
M2C_UNK func_8096F50();                                /* extern */

void sub_08092604(void) {
    u16 temp_r1;

    temp_r1 = ~*(u16 *)0x04000130;
    *(s16 *)0x0300000E = temp_r1 & ~*(u16 *)0x0300000C;
    *(u16 *)0x0300000C = temp_r1;
    func_8096F50();
}
