#include "m2c_prelude.h"
extern u16 func_080AB18C(u8, u8);
extern u16 D_0202ECF4;
extern u16 D_020324A4[];
extern u8 *D_02032E94;

u16 sub_080AB268(u8 arg0, u16 arg1, s32 arg2, s32 arg3) {
    if (D_0202ECF4 != 0x40) {
        u16 width;
        if (arg2 < 0 || arg3 < 0) {
            return 1;
        }
        width = D_020324A4[0];
        if (arg2 >= width || arg3 >= D_020324A4[1]) {
            return 1;
        }
        {
            int m = 0xC0;
            if (arg1 == 0) {
                m = 0x80;
            }
            m &= D_02032E94[arg2 + width * arg3];
            return m;
        }
    }
    return func_080AB18C(arg0, D_02032E94[arg2 + arg3 * D_020324A4[0]]);
}
