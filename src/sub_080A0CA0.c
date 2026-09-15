#include "m2c_prelude.h"
struct S { u8 unk0; u8 unk1; };
extern u8 D_02032998;
extern u32 D_020315DC[];
extern int func_080A016C(int, int, int);

s32 sub_080A0CA0(u8 arg0, struct S **arg1) {
    register u8 temp_r2 asm("r2");
    register s32 saved asm("r5");

    temp_r2 = arg0;
    saved = temp_r2;

    if (D_02032998 == (*arg1)->unk1) {
        register int neg asm("r4") = -1;
        func_080A016C(temp_r2, neg, 0);
        if ((*arg1)->unk0 != 0x18) goto end;
loop:
        func_080A016C(saved, neg, 0);
        func_080A016C(saved, neg, 0);
        if ((*arg1)->unk0 == 0x18) goto loop;
        goto end;
    }
    func_080A016C(saved, -1, 0);
    if ((*arg1)->unk0 != 0x18) {
        register u32 *base asm("r0");
        register s32 offset asm("r1");

        base = D_020315DC;
        asm volatile("" : "+r"(base));
        offset = saved << 2;
        asm volatile("" : "+r"(offset));
        offset += (s32)base;
        asm volatile("" : "+r"(offset));
        *arg1 = *(struct S **)offset;
        return 1;
    }
end:
    return 0;
}
