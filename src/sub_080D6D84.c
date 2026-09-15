#include "m2c_prelude.h"
extern s32 func_080D2660();
extern s32 func_080D2754();

void sub_080D6D84(void *arg0) {
    void *temp_r5 = *(void **)((char *)arg0 + 0x28);
    s32 var_r0;
    s32 var_r0_2;
    s32 temp_r2_2;

    if (!(*(s32 *)arg0 & 0x8000)) {
        var_r0 = *(u16 *)((char *)arg0 + 4) - 0x10;
    } else {
        var_r0 = *(u16 *)((char *)arg0 + 4) + 0x10;
    }
    *(u16 *)((char *)arg0 + 4) = var_r0;
    *(u16 *)((char *)arg0 + 6) = *(u16 *)((char *)arg0 + 6) - 8;
    if (!(*(s32 *)((char *)arg0 + 0x2C) & 1)) {
        s32 *dst;
        s32 idx;
        s32 r;
        s32 off;
        s32 temp_r2 = *(s16 *)((char *)arg0 + 4);
        if (!(*(s32 *)arg0 & 0x8000)) {
            var_r0_2 = (s16) (temp_r2 + 0x20);
        } else {
            var_r0_2 = (s16) (temp_r2 - 0x20);
        }
        r = func_080D2660(temp_r5, 1, 0, var_r0_2,
                (s16) (*(u16 *)((char *)arg0 + 6) + 0x10), 0x500, 0x13, 0x80, 3);
        idx = (*(u32 *)((char *)arg0 + 0x2C) >> 1) + 0x18;
        off = idx << 2;
        dst = (s32 *)((char *)temp_r5 + 0xC);
        *(s32 *)((char *)dst + off) = r;
    }
    temp_r2_2 = *(s32 *)((char *)arg0 + 0x30);
    if (temp_r2_2 == 0) {
        if (!(*(s32 *)arg0 & 0x8000)) {
            if (*(s16 *)((char *)arg0 + 4) >= 0) {
                goto check_y;
            }
            goto block_13;
        }
        if (*(s16 *)((char *)arg0 + 4) > 0xEF) {
            goto block_13;
        }
    check_y:
        if (*(s16 *)((char *)arg0 + 6) >= 0) {
            goto block_15;
        }
    }
block_13:
    if (temp_r2_2 != 0) {
        goto block_14;
    }
    goto block_16;
block_14:
    if ((func_080D2754(arg0, temp_r2_2 - 0x10, *(s16 *)((char *)arg0 + 6)) << 0x18) == 0) {
    block_15:
        *(s32 *)((char *)arg0 + 0x2C) = *(s32 *)((char *)arg0 + 0x2C) + 1;
        return;
    }
block_16:
    *(s32 *)arg0 = *(s32 *)arg0 | 0x20000;
    *(s32 *)((char *)arg0 + 0x24) = 0;
}
