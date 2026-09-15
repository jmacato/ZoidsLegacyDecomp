#include "m2c_prelude.h"
void func_08092E84(s32);
s32 func_080C9024(void *, s32, s32, s32, s32, s32, s32, s32);
void func_080C9164(void *);

void sub_080C9CD4(void *arg0) {
    s32 temp_r1;

    temp_r1 = *(s32 *)((s8 *)arg0 + 0x8C);
    if (temp_r1 == 0) {
        if (*(s32 *)((s8 *)arg0 + 0xA0) >= 0) {
            *(s32 *)((s8 *)arg0 + 0x88) = func_080C9024(arg0, 4, 0, 0, temp_r1, 3, 0x100, temp_r1);
            func_08092E84(0x57);
        } else {
            *(s32 *)((s8 *)arg0 + 0x88) = func_080C9024(arg0, 5, 0, 0, temp_r1, 6, 0x100, temp_r1);
            func_08092E84(0x58);
        }
        *(s32 *)((s8 *)arg0 + 0x8C) = *(s32 *)((s8 *)arg0 + 0x8C) + 1;
        return;
    }
    func_080C9164(arg0);
}
