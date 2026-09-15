#include "m2c_prelude.h"
extern u8 D_020325A0;
extern u8 D_02032998;
void sub_080A0114(void) {
    s32 temp_r0;
    s32 temp_r1;
    u8 var_r3;
    void *temp_r2;

    if (*(u8 *)((u32)&D_02032998) != 0xFF) {
        var_r3 = 0;
        do {
            temp_r0 = var_r3 * 0x48;
            temp_r2 = temp_r0 + ((u32)&D_020325A0);
            temp_r1 = M2C_FIELD(temp_r0, s32 *, ((u32)&D_020325A0));
            if ((1 & temp_r1) && ((M2C_FIELD(temp_r2, u16 *, 6) == 0) || (M2C_FIELD(temp_r2, u8 *, 5) == *(u8 *)((u32)&D_02032998)))) {
                M2C_FIELD(temp_r0, s32 *, ((u32)&D_020325A0)) = (s32) (temp_r1 & ~2);
            }
            var_r3 += 1;
        } while ((u32) var_r3 <= 0xDU);
        *(u8 *)((u32)&D_02032998) = 0xFF;
    }
}
