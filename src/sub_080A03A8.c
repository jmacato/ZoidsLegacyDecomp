#include "m2c_prelude.h"
extern u8 D_0203055C[];
extern void func_08092E0C();
extern void func_0809534C();
extern void func_0809F850();
extern void func_080A016C();
extern void func_080ED17C();

s32 sub_080A03A8(u8 arg0, void **arg1) {
    s32 temp_r0;
    s8 *var_r0;
    s32 var_r1;
    s32 var_r2;
    s32 tmp;
    s32 t;

    *(s8 *)0x02030664 = 1;
    temp_r0 = *(s32 *)0x02021690;
    if (temp_r0 != 9) {
        if (temp_r0 == 0xA && D_0203055C[2] == 0xFF) {
            func_0809534C();
            func_08092E0C(7);
        }
        *(s8 *)0x02030666 = 0;
        *(s32 *)0x02031744 = 0;
        func_0809F850();
        D_0203055C[1] = *(u8 *)((s32)*arg1 + 1);
        *(s32 *)0x02021690 = 9;
        *(s32 *)0x02030558 = 0xFF00;
        func_080ED17C(1);
        *(s8 *)0x02030666 = 0;
        *(s32 *)0x02031744 = 0;
        var_r1 = 0;
        do {
            var_r2 = 0;
            t = var_r1 << 2;
            tmp = var_r1 + 1;
            t += var_r1;
            t <<= 3;
            t -= var_r1;
            t <<= 7;
            var_r0 = (s8 *)(t + 0x02034B4C);
            do {
                *var_r0 = 0;
                var_r0 += 0x270;
                var_r2 += 1;
            } while ((u32)var_r2 <= 5U);
            var_r1 = tmp;
        } while ((u32)var_r1 <= 1U);
    }
    func_080A016C(arg0, -1, 0);
    return 0;
}
