#include "m2c_prelude.h"
M2C_UNK func_08095114(void *);                      /* extern */
s32 func_080D2450(void *, s32, s32, s16, s32, s32, s32, s32); /* extern */
M2C_UNK func_080D2790(s32);                         /* extern */

struct Sub080DA368 {
    u8 pad_0[8];
    s16 field_8;
    u16 pad_a;
    void *slots[32];
    u32 count;
};

void sub_080DA368(struct Sub080DA368 *arg0) {
    u32 index;
    u8 i;

    index = arg0->count;
    if (index <= 7U) {
        arg0->slots[arg0->count] = func_080D2450(arg0, 0, 0, (s16)(index << 5), arg0->field_8, 0x400, 0, 1);
        if (arg0->count == 0) {
            func_080D2790(0);
        }
        arg0->count += 1;
        return;
    }
    i = 0;
    if (arg0->slots[0] == 0) {
        do {
            i += 1;
            if ((u32)i > 7U) {
                break;
            }
        } while (arg0->slots[i] == 0);
    }
    if (i == 8) {
        func_08095114(arg0);
    }
}
