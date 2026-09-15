#include "m2c_prelude.h"
struct Foo {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ u16 unk4;
    /* 0x06 */ u16 unk6;
    /* 0x08 */ u8 filler8[0x24 - 0x08];
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
};

s32 func_080D2660(s32, s32, s32, s16, s32, s32, s32, s32, s32);
int func_080D2754(void *, s32, s16);

void sub_080D980C(struct Foo *arg0) {
    s32 temp_r5 = arg0->unk28;
    int var_r0;
    int temp_r2;
    s16 var_r0_2;
    s32 result;
    int idx;
    int byteoff;
    char *base;

    if (!(arg0->unk0 & 0x8000)) {
        var_r0 = arg0->unk4 - 8;
    } else {
        var_r0 = arg0->unk4 + 8;
    }
    arg0->unk4 = var_r0;
    if (!(arg0->unk2C & 1)) {
        temp_r2 = *(s16 *)((char *)arg0 + 4);
        result = func_080D2660(temp_r5, 1, 0, !(arg0->unk0 & 0x8000) ? (temp_r2 + 0x10) : (temp_r2 - 0x10), (s32)(s16)arg0->unk6, 0x500, 0x80, 0x80, 2);
        idx = ((u32)arg0->unk2C >> 1) + 5;
        byteoff = idx << 2;
        base = (char *)(temp_r5 + 0xC);
        *(s32 *)(base + byteoff) = result;
        if (!(arg0->unk0 & 0x8000)) {
            if (*(s16 *)((char *)arg0 + 4) < 0) {
                goto block_11;
            }
            goto block_13;
        }
        if (*(s16 *)((char *)arg0 + 4) > 0xEF) {
block_11:
            arg0->unk0 = arg0->unk0 | 0x20000;
            arg0->unk24 = 0;
            return;
        }
        goto block_13;
    }
block_13:
    arg0->unk2C = arg0->unk2C + 1;
}
