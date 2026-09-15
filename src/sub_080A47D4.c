#include "m2c_prelude.h"
extern void func_080A016C(u8, s32, s32);
extern s32 D_020217B4[];
extern u8 D_0202ECF4[];

s32 sub_080A47D4(u8 arg0, void **arg1) {
    s32 *p;
    register s32 v asm("r1");
    register s32 var_r2 asm("r2");
    u8 temp_r0;
    D_0202ECF4[2] = *((u8 *)*arg1 + 1);
    if (*((u8 *)*arg1 + 1) == 0x6C) {
        D_0202ECF4[3] = 1;
    }
    temp_r0 = *((u8 *)*arg1 + 1);
    switch (temp_r0) {
    case 0x69:
        p = D_020217B4;
        v = p[4];
        var_r2 = 0x80000;
        goto block_15;
    case 0x6A:
        p = D_020217B4;
        v = p[4];
        var_r2 = 0x100000;
        goto block_15;
    case 0x6B:
        p = D_020217B4;
        v = p[4];
        var_r2 = 0x400000;
        goto block_15;
    case 0x6C:
        p = D_020217B4;
        v = p[4];
        var_r2 = 0x200000;
block_15:
        p[4] = v | var_r2;
        break;
    }
    func_080A016C(arg0, -1, 0);
    return 0;
}
