#include "m2c_prelude.h"
M2C_UNK func_080ECD60(s32);
extern s32 D_030009F0[];
void sub_0809290C(void) {
    s32 *p = D_030009F0;
    if (*p != 0) {
        do {
            register s32 temp_r1 asm("r1") = p[1];
            if (temp_r1 != -1) {
                u8 v = M2C_FIELD(p, u8 *, 12);
                if (v == 0) {
                    func_080ECD60(p[2]);
                    p[1] = -1;
                } else M2C_FIELD(p, u8 *, 12) = v - 1;
            }
            p += 4;
        } while (*p != 0);
    }
}
