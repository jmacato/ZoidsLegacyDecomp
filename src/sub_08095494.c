#include "m2c_prelude.h"
extern u8 D_02000000[];
void sub_08095494(void) {
    u8 var_r1;
    u8 var_r2;
    void *temp_r0;
    s32 base;
    s32 base4;
    s32 z;
    s32 v;
    var_r1 = 0;
    base = (s32) D_02000000;
    base4 = base + 4;
    z = 0;
    v = 0xA000A0;
    do {
        var_r2 = 0;
        do {
            temp_r0 = (void *) ((var_r2 * 8) + (var_r1 * 0x500));
            *(s32 *)((s32) temp_r0 + base) = z;
            *(s32 *)((s32) temp_r0 + base4) = v;
            var_r2 += 1;
        } while ((u32) var_r2 <= 0x9FU);
        var_r1 += 1;
    } while ((u32) var_r1 <= 1U);
}
