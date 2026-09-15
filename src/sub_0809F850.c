#include "m2c_prelude.h"
extern u8 D_020317DA;
extern u8 D_0203183C;
extern u8 D_0203183E;
extern u8 D_02031840;
extern u8 D_02031940;
void sub_0809F850(void) {
    u8 var_r1;

    *(s8 *)((u32)&D_020317DA) = 0;
    *(s16 *)((u32)&D_0203183C) = 0x398;
    *(s16 *)((u32)&D_0203183E) = 9;
    var_r1 = 0;
    do {
        M2C_FIELD((var_r1 * 4), s32 *, ((u32)&D_02031940)) = 0;
        M2C_FIELD((var_r1 * 0x10), s8 *, ((u32)&D_02031840)) = 0;
        var_r1 += 1;
    } while ((u32) var_r1 <= 0xFU);
}
