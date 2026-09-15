#include "m2c_prelude.h"
struct Spr {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s16 unkC;
};
struct Obj {
    u8 pad0[0xC];
    struct Spr *unkC;
    struct Spr *unk10;
    struct Spr *unk14;
    u8 pad18[0x8C - 0x18];
    u32 unk8C;
    u8 pad90[0xA4 - 0x90];
    s32 unkA4;
    s32 unkA8;
};
extern void func_08092E84(s32);
extern void func_080BB05C(s32, s32);
extern struct Spr *func_080C9024(struct Obj *, s32, s32, s32, s32, s32, s32, s32);
extern void func_080C9164(struct Obj *);
extern s16 func_080ECD98(s32, s32);

void sub_080C92C4(struct Obj *arg0) {
    u32 v = arg0->unk8C;
    if (v <= 0x15U) {
        if (v == 0x14) {
            struct Spr *s14;
            struct Spr *t14;
            s14 = func_080C9024(arg0, 1, 0, 0, -0x20, 0, 0x200, 0);
            arg0->unk10 = s14;
            s14->unkC = s14->unkC * 2;
            t14 = arg0->unk10;
            if ((s32) t14->unkC > 0x100) {
                t14->unk0 = t14->unk0 | 0x80000;
            }
            func_08092E84(0x5C);
        } else if (v == 0x15) {
            struct Spr *s15;
            struct Spr *t15;
            s15 = func_080C9024(arg0, 1, 0, 0, -0x40, 0, 0x100, 0);
            arg0->unk14 = s15;
            s15->unkC = func_080ECD98(arg0->unkC->unkC * 0xF, 0xA);
            t15 = arg0->unk14;
            if ((s32) t15->unkC > 0x100) {
                t15->unk0 = t15->unk0 | 0x80000;
            }
            func_080BB05C(arg0->unkA4, arg0->unkA8);
        }
        arg0->unk8C = arg0->unk8C + 1;
        return;
    }
    func_080C9164(arg0);
}
