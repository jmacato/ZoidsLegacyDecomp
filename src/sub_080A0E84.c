#include "m2c_prelude.h"
struct S { u8 unk0; u8 unk1; };
extern u8 D_020316FC[];
extern u32 D_020315DC[];
extern int func_0809F818(u8);
extern int func_080A016C(int, int, int);
s32 sub_080A0E84(u8 arg0, struct S **arg1) {
    if (D_020316FC[arg0] != 0 && (func_0809F818((*arg1)->unk1) << 24) != 0) {
        register int neg asm("r5") = -1;
        func_080A016C(arg0, neg, 0);
        if ((*arg1)->unk0 != 0x18) goto end;
    loop:
        func_080A016C(arg0, neg, 0);
        func_080A016C(arg0, neg, 0);
        if ((*arg1)->unk0 == 0x18) goto loop;
        goto end;
    }
    func_080A016C(arg0, -1, 0);
    if ((*arg1)->unk0 != 0x18) {
        *arg1 = (struct S *)D_020315DC[arg0];
        D_020316FC[arg0] = 0;
        return 1;
    }
end:
    return 0;
}
