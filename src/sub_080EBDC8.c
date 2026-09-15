#include "m2c_prelude.h"
extern void func_80EBABC(void *);

void sub_080EBDC8(void *arg0, s8 *arg1, int arg2) {
    s32 temp_r0;
    s32 temp_r1;
    register s8 *var_r6 asm("r6");
    u8 var_r4;
    register void *temp_r5 asm("r5");

    var_r6 = arg1;
    arg2 = arg2 << 0x18;
    var_r4 = (u32)arg2 >> 0x18;
    if (var_r4 != 0) {
        if ((u32) var_r4 > 0x10U) {
            var_r4 = 0x10;
        }
        temp_r5 = *(void **)0x03007FF0;
        temp_r1 = M2C_FIELD(temp_r5, s32 *, 0);
        if (temp_r1 == 0x68736D53) {
            M2C_FIELD(temp_r5, s32 *, 0) = (s32) (temp_r1 + 1);
            func_80EBABC(arg0);
            M2C_FIELD(arg0, s8 **, 0x2C) = var_r6;
            M2C_FIELD(arg0, u8 *, 8) = var_r4;
            M2C_FIELD(arg0, s32 *, 4) = 0x80000000;
            if (var_r4 != 0) {
                do {
                    *var_r6 = 0;
                    var_r4 -= 1;
                    var_r6 += 0x50;
                } while (var_r4 != 0);
            }
            temp_r0 = M2C_FIELD(temp_r5, s32 *, 0x20);
            if (temp_r0 != 0) {
                M2C_FIELD(arg0, s32 *, 0x38) = temp_r0;
                M2C_FIELD(arg0, void **, 0x3C) = (void *) M2C_FIELD(temp_r5, void **, 0x24);
                M2C_FIELD(temp_r5, s32 *, 0x20) = 0;
            }
            M2C_FIELD(temp_r5, void **, 0x24) = arg0;
            M2C_FIELD(temp_r5, s32 *, 0x20) = 0x080EB0C1;
            M2C_FIELD(temp_r5, s32 *, 0) = 0x68736D53;
            M2C_FIELD(arg0, s32 *, 0x34) = 0x68736D53;
        }
    }
}
