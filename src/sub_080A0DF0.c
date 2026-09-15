#include "m2c_prelude.h"
struct S { u8 unk0; u8 unk1; u8 unk2; u8 unk3; u8 unk4; u8 pad[24]; u8 unk1D; };
extern struct S *D_02032990;
extern u32 D_020315DC[];
extern int func_080A016C(int, int, int);
s32 sub_080A0DF0(u8 arg0, struct S **arg1) {
    struct S *p = D_02032990;
    if (p != 0 && p->unk4 != 0x6C) {
        register u8 t asm("r2") = p->unk1D;
        if ((0x40 & t) && ((0x3F & t) == (*arg1)->unk1)) {
            register int neg asm("r5") = -1;
            func_080A016C(arg0, neg, 0);
            if ((*arg1)->unk0 != 0x18) goto end;
        loop:
            func_080A016C(arg0, neg, 0);
            func_080A016C(arg0, neg, 0);
            if ((*arg1)->unk0 == 0x18) goto loop;
            goto end;
        }
    }
    func_080A016C(arg0, -1, 0);
    if ((*arg1)->unk0 != 0x18) {
        *arg1 = (struct S *)D_020315DC[arg0];
        return 1;
    }
end:
    return 0;
}
