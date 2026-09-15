#include "m2c_prelude.h"
extern s32 func_080A016C(u8, s32, s32);
extern void *func_080A9D78(u8, u8, s32, s32, s32, s32, s32, s32);
extern u8 func_080A9EF0(s32);
extern u8 D_020218E4[];

s32 sub_080A0590(u8 arg0, void **arg1) {
    u8 *r5 = (u8 *)*arg1;
    s32 r4v;
    void *r0res;
    u32 var_r2;
    u8 flag;
    s32 zero;
    u8 *base;

    if (r5[1] <= 0xC) {
        flag = *(u8 *)0x020316F4;
        r4v = 8;
        if (flag == 0) {
            r4v = 0x10;
        }
        r0res = func_080A9D78(r5[2], r5[1], (r5[3] * r4v) << 8, (r5[4] * r4v) << 8,
                              (s32)r5[5], 0, (s32)r5[6], (s32)r5[7]);
        if (r0res != 0 && ((u8 *)*arg1)[6] == 0) {
            *(void **)0x02032990 = r0res;
            if (((u8 *)r0res)[4] == 1) {
                var_r2 = 1;
                base = D_020218E4;
                zero = 0;
            loop_7:
                {
                    u8 *p = (u8 *)((var_r2 << 6) + (u32)base);
                    if (p[0x5A94] == 1 && p[0x5AC5] == 1) {
                        var_r2 = func_080A9EF0(0xD);
                        if (var_r2 == 0xFF) {
                            *(void **)0x02032994 = func_080A9D78(
                                0x4B, 0xD,
                                *(s32 *)((u8 *)r0res + 8),
                                *(s32 *)((u8 *)r0res + 12),
                                (s32)((u8 *)r0res)[26],
                                zero, 8, zero);
                        }
                    } else {
                        var_r2 += 1;
                        if (var_r2 <= 0x34) {
                            goto loop_7;
                        }
                    }
                }
            }
        }
    }
    func_080A016C(arg0, -1, 0);
    return 0;
}
