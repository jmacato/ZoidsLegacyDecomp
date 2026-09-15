#include "m2c_prelude.h"
void sub_080ACB5C(u8 arg0) {
    u8 i;
    for (i = 0; i < arg0; i++) {
        *(*(s32 **)(0x02032A88 + i * 4)) |= 0x20000;
        *(*(s32 **)(0x02032AA8 + i * 4)) |= 0x20000;
    }
}
