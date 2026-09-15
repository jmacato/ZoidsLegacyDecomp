#include "m2c_prelude.h"
extern void *func_8094374(void *, int, int, int, int, int, int, int, int);

void sub_080C8F48(u8 *arg0, void *arg1, u8 arg2) {
    s32 temp_r1_2;
    u8 temp_r1;
    u8 var_r2;
    void *temp_r0;
    register int var_r4 asm("r4");
    register int sel asm("r0");
    void **dst;
    s32 off;

    var_r4 = 0;
    while ((temp_r1 = *arg0) != 0) {
        if ((u8)(temp_r1 - 0x30) <= 9) {
            var_r2 = temp_r1 + 0xF0;
            goto block_20;
        }
        var_r2 = temp_r1 - 0x41;
        if ((u8)var_r2 > 0x19) {
            sel = temp_r1;
            if (sel == 0x2B) { var_r2 = 0x1A; goto block_20; }
            if (sel == 0x2D) { var_r2 = 0x1B; goto block_20; }
            if (sel == 0x2F) { var_r2 = 0x1C; goto block_20; }
            if (sel == 0x3C) { var_r2 = 0x1D; goto block_20; }
            if (sel == 0x3E) { var_r2 = 0x1E; goto block_20; }
            if (sel == 0xA0) { var_r2 = 0x1F; goto block_20; }
            if (sel == 0x25) { var_r2 = 0x2A; goto block_20; }
            if (sel == 0x3F) { var_r2 = 0x2B; goto block_20; }
        } else {
        block_20:
            temp_r0 = func_8094374((void *)0x087AC9F0, 0, var_r2,
                (s16)(((s32 *)arg1)[1] + var_r4 * 6),
                (s32)(s16)(((s32 *)arg1)[2] - 8),
                0x3B4, 0xD, 0x20048, 0x080C8EF5);
            off = (arg2 + var_r4) * 4;
            dst = (void **)((u8 *)arg1 + 0xC);
            *(void **)((u8 *)dst + off) = temp_r0;
            temp_r1_2 = (0 - var_r4) * 2;
            ((s32 *)temp_r0)[10] = temp_r1_2;
            ((s32 *)temp_r0)[11] = temp_r1_2 + 0x2D;
        }
        arg0 += 1;
        sel = var_r4 + 1;
        var_r4 = (u8)sel;
    }
}
