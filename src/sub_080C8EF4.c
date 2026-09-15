#include "m2c_prelude.h"
extern int func_8092A90(s32);
extern void func_8094554(void *);

struct S {
    u32 w0;
    u8 pad4[6];
    s16 hA;
    u8 pad[0x1c];
    s32 w28;
    s32 w2c;
};

void sub_080C8EF4(struct S *arg0) {
    s32 v = arg0->w28;
    if (v <= 8) {
        if (v >= 0) {
            if (v == 0) {
                arg0->w0 &= 0xFFFDFFFF;
            }
            arg0->hA = -(s16)func_8092A90((arg0->w28 << 20) >> 16) / 32;
        }
    } else {
        if (v == arg0->w2c) {
            func_8094554(arg0);
        }
    }
    arg0->w28 += 1;
}
