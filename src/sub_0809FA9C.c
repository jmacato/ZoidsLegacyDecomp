#include "m2c_prelude.h"
struct PtrS {
    u32 unk0;
    u16 unk4;
    u16 unk6;
};

struct S {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    u16 unk4;
    u16 unk6;
    u16 unk8;
    u16 unkA;
    u8 unkC;
    u8 unkD;
    u16 unkE;
};

extern struct PtrS *D_02031940[];
extern struct S D_02031840[];

void func_080ED17C(s32);

void sub_0809FA9C(void) {
    s32 var_r7;
    u8 i;
    struct S *p;
    struct PtrS *q;
    s32 v;
    s32 c;
    s32 temp;

    do {
        var_r7 = 0;
        i = 0;
        do {
            if (D_02031940[i] != 0) {
                p = &D_02031840[i];
                if (p->unk0 != 0) {
                    p->unk8 = p->unk8 + p->unk4;
                    if ((s16)p->unk8 > (c = p->unkC)) {
                        do {
                            if (p->unk1 == 0) {
                                q = D_02031940[i];
                                v = q->unk4 + 1;
                            } else {
                                q = D_02031940[i];
                                v = q->unk4 - 1;
                            }
                            q->unk4 = v;
                            p->unk8 = p->unk8 - p->unkC;
                        } while ((s16)p->unk8 > (c = p->unkC));
                    }
                    p->unkA = p->unkA + p->unk6;
                    if ((s16)p->unkA > c) {
                        do {
                            if (p->unk2 == 0) {
                                q = D_02031940[i];
                                v = q->unk6 + 1;
                            } else {
                                q = D_02031940[i];
                                v = q->unk6 - 1;
                            }
                            q->unk6 = v;
                            p->unkA = p->unkA - p->unkC;
                        } while ((s16)p->unkA > p->unkC);
                    }
                    temp = p->unkD + 1;
                    p->unkD = temp;
                    if ((u32)(u8)temp >= (u32)p->unkC) {
                        p->unk0 = 0;
                    } else {
                        var_r7 = 1;
                    }
                }
            }
            i = i + 1;
        } while (i <= 15);
        func_080ED17C(1);
    } while (var_r7 != 0);
}
