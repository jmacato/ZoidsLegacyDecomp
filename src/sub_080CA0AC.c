#include "m2c_prelude.h"
extern void *func_8095098(s32, s32, s32);
extern void func_08095114(void *);
extern s32 D_087A28B0[][2];
extern void *D_02032F64[];
extern void *D_02032E8C[][6];

void sub_080CA0AC(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 temp_r4;
    u8 temp_r5;
    void *temp_r0;
    void *temp_r2;
    u32 idx;

    arg0 = arg0 << 0x10;
    temp_r4 = arg1;
    temp_r5 = arg2;
    idx = (u32)arg0 >> 0x10;
    temp_r0 = func_8095098(0, D_087A28B0[idx][0], D_087A28B0[idx][1]);
    D_02032F64[temp_r5] = temp_r0;
    temp_r2 = D_02032E8C[temp_r4][temp_r5];
    *(s32 *)((u8 *)temp_r0 + 4) = *(s16 *)((u8 *)temp_r2 + 4);
    *(s32 *)((u8 *)temp_r0 + 8) = *(s16 *)((u8 *)temp_r2 + 6);
    *(s32 *)((u8 *)temp_r0 + 0xA0) = arg3;
    *(s32 *)((u8 *)temp_r0 + 0xA4) = temp_r4;
    *(s32 *)((u8 *)temp_r0 + 0xA8) = temp_r5;
}

void sub_080CA114(void) {
    u8 i;
    void **base;
    void **p;

    i = 0;
    base = D_02032F64;
    do {
        p = (void **)((i * 4) + (s32)base);
        if (*p != 0) {
            func_08095114(*p);
            *p = 0;
        }
        i += 1;
    } while ((u32)i <= 5U);
}
