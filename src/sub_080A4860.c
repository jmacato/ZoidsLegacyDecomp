#include "m2c_prelude.h"
extern u8 D_0202ECF4[];
extern int func_080A9D78();
extern int func_080A016C();

s32 sub_080A4860(u8 arg0, u8 **arg1) {
    u8 *e = *arg1;
    if (e[1] <= 0xC) {
        u8 f = *(u8 *)0x020316F4;
        int var_r4 = 8;
        int ret;
        if (f == 0) var_r4 = 16;
        ret = func_080A9D78(D_0202ECF4[2], e[1], (e[2] * var_r4) << 8,
                            (e[3] * var_r4) << 8, e[4], 0, e[5], 0);
        if (ret != 0 && (*arg1)[5] == 0)
            *(s32 *)0x02032990 = ret;
    }
    func_080A016C(arg0, -1, 0);
    return 0;
}
