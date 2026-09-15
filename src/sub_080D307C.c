#include "m2c_prelude.h"
struct S {
    u8 pad00[4];
    s32 unk4;
    s16 unk8;
    u8 pad0A[2];
    s32 arr[10];
    u8 pad34[0x8C - 0x34];
    u32 unk8C;
    u32 unk90;
    u32 unk94;
};

extern s32 func_080D2450(struct S *, s32, s32, s16, s32, s32, u32, u32);
extern void func_080D2790(s32);
extern void func_08095114(struct S *);

void sub_080D307C(struct S *arg0) {
    u32 temp_r0;
    u32 temp_r5;
    u8 var_r1;
    s32 result;

    temp_r0 = arg0->unk8C;
    if (temp_r0 <= 7) {
        result = func_080D2450(arg0, 0, 0, (s16)(arg0->unk4 - (temp_r0 << 5) - 8), arg0->unk8, 0x500, 0, 0);
        temp_r5 = arg0->unk8C;
        arg0->arr[temp_r5] = result;
        if (temp_r5 == 0) {
            arg0->arr[8] = func_080D2450(arg0, 0, 1, (s16)arg0->unk4, arg0->unk8, 0x500, temp_r5, temp_r5);
            arg0->arr[9] = func_080D2450(arg0, 1, 0, (s16)arg0->unk4, arg0->unk8, 0x400, temp_r5, temp_r5);
            func_080D2790(0);
        }
        arg0->unk8C++;
        return;
    }
    var_r1 = 0;
    if (arg0->arr[0] == 0) {
        do {
            var_r1++;
            if (var_r1 > 9) {
                break;
            }
        } while (arg0->arr[var_r1] == 0);
    }
    if (var_r1 == 10) {
        func_08095114(arg0);
    }
}

void sub_080D3140(struct S *arg0) {
    arg0->unk8C = arg0->unk90 = arg0->unk94 = 0;
}
