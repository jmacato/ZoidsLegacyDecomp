#include "m2c_prelude.h"
u8 sub_080E7BCC(u8 a, u8 b, u8 c, u8 d) {
    u8 r;
    if (b <= 5) {
        r = 0;
        if (a != c) {
            r = 1;
            if (d > 2) {
                r = 2;
            }
            if (b <= 2) {
                goto ret_r;
            }
            goto add_one;
        }
        if (b <= 2) {
            if (d > 2) {
                goto add_one;
            }
            goto ret_r;
        }
        if (d > 2) {
            goto ret_r;
        }
add_one:
        r = r + 1;
        return r;
ret_r:
        return r;
    }
    return 1;
}
