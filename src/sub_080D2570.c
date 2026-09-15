#include "m2c_prelude.h"
struct Obj {
    s32 unk0;
    s16 unk4;
    s16 unk6;
    s32 filler[8];
    s32 unk28;
    s32 unk2C;
    s32 unk30;
    s32 unk34;
};

s16 func_08092A90(u8);
s16 func_08092ADC(u8);
void func_08094554(void *);

void sub_080D2570(struct Obj *arg0) {
    s32 temp_r1;
    s32 temp_r1_2;
    s32 temp_r1_3;
    s32 temp_r2;
    s32 var_r0;
    s32 var_r0_2;
    s32 var_r0_3;
    s32 var_r0_4;
    u8 temp_r5;

    temp_r5 = (u8) arg0->unk30;
    var_r0 = func_08092ADC(temp_r5) * arg0->unk34;
    if (var_r0 < 0) var_r0 += 0xFF;
    temp_r2 = var_r0 >> 8;
    if (!(arg0->unk0 & 0x8000)) {
        temp_r1 = arg0->unk28 + temp_r2;
        arg0->unk28 = temp_r1;
        if (((u32) (u8) (temp_r5 - 0x40) <= 0x80U) || (temp_r1 <= 0x10000)) {
            if ((u32) (u8) (temp_r5 - 0x41) > 0x7EU) goto block_13;
            if (temp_r1 >= (s32) 0xFFFFF000) goto block_13;
        }
        goto block_19;
    }
    temp_r1_2 = arg0->unk28 - temp_r2;
    arg0->unk28 = temp_r1_2;
    if ((u32) (u8) (temp_r5 - 0x40) > 0x80U) {
        if (temp_r1_2 < (s32) 0xFFFFF000) goto block_19;
    }
    if ((u32) (u8) (temp_r5 - 0x41) <= 0x7EU) {
        if (temp_r1_2 > 0x10000) goto block_19;
    }
block_13:
    var_r0_2 = func_08092A90(temp_r5) * arg0->unk34;
    if (var_r0_2 < 0) var_r0_2 += 0xFF;
    temp_r1_3 = arg0->unk2C + (var_r0_2 >> 8);
    arg0->unk2C = temp_r1_3;
    if ((u32) (u8) (temp_r5 - 1) <= 0x7EU) {
        if (temp_r1_3 > 0x9000) goto block_19;
    }
    if ((u32) temp_r5 <= 0x80U) goto block_stores;
    if (temp_r1_3 >= (s32) 0xFFFFF000) goto block_stores;
block_19:
    func_08094554(arg0);
    return;
block_stores:
    var_r0_3 = arg0->unk28;
    if (var_r0_3 < 0) var_r0_3 += 0xFF;
    arg0->unk4 = (s16) (var_r0_3 >> 8);
    var_r0_4 = arg0->unk2C;
    if (var_r0_4 < 0) var_r0_4 += 0xFF;
    arg0->unk6 = (s16) (var_r0_4 >> 8);
}
