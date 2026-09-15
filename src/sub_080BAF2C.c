#include "m2c_prelude.h"

struct S {
    s32 f0;
    u8 pad4[10];
    u16 fE;
    u8 f10;
    u8 pad11[19];
    s32 f24;
    s32 f28;
    s32 f2C;
    s32 f30;
};

extern void func_0809A4CC(u8, u8, u16, u8);

extern struct S *D_02032E8C[2][6];
extern struct S *D_02032EBC[2][6];
extern u8 D_02032EEC[2][6];
extern s32 D_087A2790[][3];

void sub_080BAF2C(u8 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, s32 arg5, s32 arg6) {
    u8 idx2 = arg3 * 6 + arg4;
    struct S **slot;
    u8 *baseS;
    struct S *p2;
    struct S *q2;
    struct S *p3;

    baseS = (u8 *)0x02032E8C;
    asm volatile("" : "+r"(baseS));
    slot = (struct S **)(arg4 * 4 + arg3 * 24 + (s32)baseS);
    func_0809A4CC(arg0, arg1, (*slot)->fE, (*slot)->f10);
    if (arg2 == 4) {
        struct S *t = *slot;
        t->f24 = 0x080BAE19;
        t->f0 |= 0x80000;
    } else {
        struct S *t = *slot;
        t->f24 = 0x080BADD5;
        t->f0 &= 0xFFF7FFFF;
    }
    {
        register u32 scratch_r3 asm("r3");
        asm volatile("" : "=&r"(scratch_r3) : "r"(&D_02032E8C[0][0]));
    }
    p2 = D_02032E8C[arg3][arg4];
    p2->f0 &= 0xFFFDFFFF;
    if (arg3 == 0) {
        D_02032EBC[0][arg4]->f24 = 0x080BAEED;
    } else {
        D_02032EBC[arg3][arg4]->f24 = 0x080BAEAD;
    }
    q2 = D_02032EBC[arg3][arg4];
    q2->f0 &= 0xFFFDFFFF;
    q2->f2C = 0x20000;
    p3 = D_02032E8C[arg3][arg4];
    p3->f28 = D_087A2790[idx2][0] + arg5;
    p3->f2C = D_087A2790[idx2][1];
    p3->f30 = D_087A2790[idx2][2] + arg6;
    D_02032EEC[arg3][arg4] = 0;
}
