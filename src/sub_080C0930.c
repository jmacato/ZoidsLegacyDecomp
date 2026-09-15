#include "m2c_prelude.h"
extern void func_80988C8(s32, s32);
extern s32 D_087EF130[];
extern u8 D_020281F6[];
extern u8 D_02037300[];

void sub_080C0930(u8 arg0) {
    s32 i = 0;
    s32 *table = D_087EF130;
    u8 *arr0 = D_020281F6;
    u8 *arr1 = D_02037300;
    do {
        if (arg0 == 0) {
            func_80988C8(3, table[*(u8 *)(i + (s32)arr0)]);
        } else {
            func_80988C8(3, table[*(u8 *)(i + (s32)arr1)]);
        }
        i = (u8)(i + 1);
    } while ((u32)i <= 9);
}
