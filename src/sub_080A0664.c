#include "m2c_prelude.h"
extern s32 func_080A016C(u8, s32, s32);
extern void *func_080A9D78(u8, u8, s32, s32, s32, s32, s32, s32);
extern u8 func_080A9EF0(s32);
extern u8 D_020218E4[];
extern s32 D_020325A0[][0x12];

s32 sub_080A0664(s32 arg0, void **arg1) {
    register void **saved_arg1 asm("r9") = arg1;
    u8 *input;
    u8 *pre;
    u8 arg0n;
    s32 scale;
    void *result;
    u32 index;
    u8 flag;
    s32 zero;
    u8 *base;

    arg0n = (u8)arg0;
    pre = (u8 *)*arg1;

    if (pre[1] <= 0xC) {
        flag = *(u8 *)0x020316F4;
        scale = 8;
        if (flag == 0) {
            scale = 0x10;
        }
        index = func_080A9EF0(pre[3]);
        if (index != 0xFF) {
            input = (u8 *)*saved_arg1;
            result = func_080A9D78(input[2], input[1],
                D_020325A0[index][2] + ((input[4] * scale) << 8),
                D_020325A0[index][3] + ((input[5] * scale) << 8),
                (s32)input[6], 0, (s32)input[7], 0);
            if (result != 0) {
                register void **check_arg1 asm("r1") = saved_arg1;
                if (((u8 *)*check_arg1)[7] != 0) {
                    goto done;
                }
                *(void **)0x02032990 = result;
                if (((u8 *)result)[4] == 1) {
                    index = 1;
                    base = D_020218E4;
                    zero = 0;
                loop_7:
                    {
                        u8 *p = (u8 *)((index << 6) + (u32)base);
                        if (p[0x5A94] == 1 && p[0x5AC5] == 1) {
                            index = func_080A9EF0(0xD);
                            if (index == 0xFF) {
                                *(void **)0x02032994 = func_080A9D78(
                                    0x4B, 0xD,
                                    *(s32 *)((u8 *)result + 8),
                                    *(s32 *)((u8 *)result + 12),
                                    (s32)((u8 *)result)[26],
                                    zero, 8, zero);
                            }
                        } else {
                            index += 1;
                            if (index <= 0x34) {
                                goto loop_7;
                            }
                        }
                    }
                }
            }
        }
    }
done:
    func_080A016C(arg0n, -1, 0);
    return 0;
}
