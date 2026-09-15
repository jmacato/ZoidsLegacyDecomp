#include "m2c_prelude.h"
struct Foo {
    s32 unk0;
    u16 unk4;
    u16 unk6;
    u8 filler8[0x24 - 0x08];
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    s32 unk30;
};
s32 func_080D2660(s32, s32, s32, s16, s32, s32, s32, s32, s32);
int func_080D2754(void *, s32, s16);
void sub_080D8D20(struct Foo *arg0) {
    s32 temp_r5 = arg0->unk28;
    s32 temp_r1;
    int var_r0;
    int temp_r2;
    s32 result;
    int idx;
    int byteoff;
    char *base;
    if (!(arg0->unk0 & 0x8000)) var_r0 = arg0->unk4 - 8;
    else var_r0 = arg0->unk4 + 8;
    arg0->unk4 = var_r0;
    arg0->unk6 = arg0->unk6 + 4;
    if (!(arg0->unk2C & 1)) {
        temp_r2 = *(s16 *)((char *)arg0 + 4);
        result = func_080D2660(temp_r5, 1, 0,
            !(arg0->unk0 & 0x8000) ? (temp_r2 + 0x10) : (temp_r2 - 0x10),
            (s32)(s16)(arg0->unk6 - 8), 0x500, 0x6D, 0x80, 3);
        idx = ((u32)arg0->unk2C >> 1) + 0x10;
        byteoff = idx << 2;
        base = (char *)(temp_r5 + 0xC);
        *(s32 *)(base + byteoff) = result;
    }
    temp_r1 = arg0->unk30;
    if (temp_r1 == 0) {
        if (*(s16 *)((char *)arg0 + 6) <= 0x6F) goto block_12;
        goto block_13;
    }
    if ((func_080D2754(arg0, temp_r1 - 0x10, *(s16 *)((char *)arg0 + 6)) << 0x18) == 0) {
block_12:
        arg0->unk2C = arg0->unk2C + 1;
        return;
    }
block_13:
    arg0->unk0 = arg0->unk0 | 0x20000;
    arg0->unk24 = 0;
}
