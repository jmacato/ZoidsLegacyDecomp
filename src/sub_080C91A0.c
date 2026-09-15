#include "m2c_prelude.h"
void func_08092E84(s32);
void func_08098284(u32, s32, s32, s32);
void func_080C8F48(s32, void *, s32);
s32 func_080C9024(void *, s32, s32, s32, s32, s32, s32, s32);

struct S {
    u8 pad0[12];
    s32 unkC;
    u8 pad10[124];
    s32 unk8C;
    u8 pad90[16];
    u32 unkA0;
};

void sub_080C91A0(struct S *arg0) {
    u32 var_r0;

    arg0->unkC = func_080C9024(arg0, 0, 0, 0, -0x20, 0, 0, 0);
    var_r0 = arg0->unkA0;
    if (var_r0 > 0x270FU) {
        var_r0 = 0x270F;
    }
    func_08098284(var_r0, 4, 0xA, 0x02030564);
    func_080C8F48(0x02030564, arg0, 1);
    func_08092E84(0x59);
    arg0->unk8C = 0;
}
