#include "m2c_prelude.h"
extern void func_08094290(s32, s32);
extern void func_080942E0(s32);
extern u8 D_0203198C;
extern u8 D_0203198D;
extern u8 D_0203198E[];
extern s32 D_03000054[];
extern u8 D_03000074;

void sub_080A7860(s32 arg0) {
    u8 v;
    if ((arg0 << 0x18) != 0) {
        v = D_0203198C;
        if (v == 1) {
            s16 *p = (s16 *)0x04000208;
            *p = 0;
            func_08094290(2, 0x030060FC);
            *p = v;
            D_0203198C = 2;
        } else if (v == 3) {
            s16 *p = (s16 *)0x04000208;
            *p = 0;
            func_080942E0(2);
            D_03000074 &= 0xF7;
            *p = 1;
            D_0203198C = 0;
            return;
        }
        D_0203198D ^= 1;
    }
    if (D_0203198C == 2) {
        u16 *dst = (u16 *)0x04000012;
        u8 *base = D_0203198E;
        *dst = *(u16 *)(base + D_0203198D * 0x140);
        D_03000054[1] = *(s16 *)(base + D_0203198D * 0x140) << 8;
    }
}
