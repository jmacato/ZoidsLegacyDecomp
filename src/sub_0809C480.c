#include "m2c_prelude.h"
extern int func_809C434(void);
extern void func_80981F0(void *, s32, s32, s32, s32);
extern u8 D_020216F5;
extern u8 D_02021708;
extern u16 D_087A11DA;

struct S30564 { u16 count; s16 x; };
extern struct S30564 D_02030564;

void sub_0809C480(void) {
    u16 *var_r6;
    u16 var_r4;
    u8 i, j;

    if ((func_809C434() << 24) == 0) {
        register int row asm("r0") = D_020216F5 * 0x106;
        u8 *rb = (u8 *)&D_087A11DA + row;
        var_r6 = (u16 *)(rb + 26 * D_02021708);
        var_r4 = *(u16 *)((u8 *)&D_087A11DA + row - 2) - 13 * D_02021708;
    }
    i = 0;
    do {
        j = 0;
        do {
            if (var_r4 != 0) {
                D_02030564.count = *var_r6;
                var_r4--;
            } else {
                D_02030564.count = 0x4081;
            }
            D_02030564.x = 0;
            func_80981F0(&D_02030564, 0, 2, j * 2 + 1, (s16)(i * 2));
            var_r6++;
            j++;
        } while (j <= 12);
        i++;
    } while (i <= 4);
    func_809C434();
}
