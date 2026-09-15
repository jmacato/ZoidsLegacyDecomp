#include "m2c_prelude.h"
M2C_UNK func_080EBABC(void *);

void sub_080EB944(void *arg0) {
    u8 temp_r1;
    u8 mask;
    register s32 mask2 asm("r0");
    s32 var_r5;
    void *var_r4;
    u8 var_r7;
    register u8 var_r6 asm("r6");
    var_r5 = M2C_FIELD(arg0, u8 *, 8);
    var_r4 = M2C_FIELD(arg0, void **, 0x2C);
    if ((s32)var_r5 > 0) {
        var_r7 = 0x80;
        do {
            temp_r1 = M2C_FIELD(var_r4, u8 *, 0);
            mask = var_r7;
            mask &= temp_r1;
            if (mask != 0) {
                var_r6 = 0x40;
                mask2 = var_r6;
                asm volatile("" : "+r"(mask2));
                mask2 &= temp_r1;
                asm volatile("" : "+r"(mask2));
                if (mask2 != 0) {
                func_080EBABC(var_r4);
                M2C_FIELD(var_r4, u8 *, 0) = var_r7;
                M2C_FIELD(var_r4, s8 *, 0xF) = 2;
                M2C_FIELD(var_r4, s8 *, 0x13) = var_r6;
                M2C_FIELD(var_r4, s8 *, 0x19) = 0x16;
                M2C_FIELD(var_r4, s8 *, 0x24) = 1;
                }
            }
            var_r5 -= 1;
            var_r4 += 0x50;
        } while ((s32)var_r5 > 0);
    }
}
