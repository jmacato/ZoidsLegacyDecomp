#include "m2c_prelude.h"
s16 func_08092A90(s32); /* extern */

extern u8 D_02032B9C;
extern u8 D_02032B9D;
extern u8 D_02032B9E;
extern s16 D_02032BA0[];

void sub_080BA8C0(void) {
    s32 var_r0;
    s32 temp_r0_2;
    s32 temp_r2;
    u8 temp_r0;
    u8 var_r2;
    u8 var_r4;
    s16 *base;
    register s16 *dest asm("r3");
    s32 packed;

    if (D_02032B9C != 0) {
        var_r4 = 0;
        base = D_02032BA0;
        do {
            var_r0 = func_08092A90(D_02032B9D + var_r4);
            if (var_r0 < 0) {
                var_r0 += 0x1F;
            }
            temp_r0 = (var_r0 >> 5) + 7;
            var_r2 = temp_r0;
            if ((s8)temp_r0 < 0) {
                var_r2 = 0;
            }
            if ((s8)var_r2 > 0xE) {
                var_r2 = 0xE;
            }
            dest = (s16 *)(var_r4 << 1);
            {
                register s32 flag_value asm("r0");
                register s32 flag_index asm("r1");

                flag_value = D_02032B9E;
                flag_index = 1;
                flag_index ^= flag_value;
                flag_value = flag_index << 2;
                flag_value += flag_index;
                flag_value <<= 6;
                dest = (s16 *)((u8 *)dest + flag_value);
            }
            dest = (s16 *)((u8 *)dest + (s32)base);
            temp_r2 = var_r2;
            temp_r2 <<= 24;
            temp_r2 >>= 24;
            packed = temp_r2 << 4;
            packed |= temp_r2;
            temp_r0_2 = 0xE;
            temp_r0_2 -= temp_r2;
            temp_r2 = temp_r0_2;
            temp_r2 <<= 8;
            packed |= temp_r2;
            temp_r0_2 <<= 12;
            packed |= temp_r0_2;
            *dest = (s16)packed;
            var_r4 += 1;
        } while (var_r4 <= 0x9F);
        D_02032B9D += 4;
    }
}
