#include "m2c_prelude.h"
extern void func_08092E84(s32);
extern s32 func_080C9024(void *, s32, s32, s32, s32, s32, s32, s32);
extern void func_080C9164(void *);

void sub_080C9B60(void *arg0) {
    s32 t = *(s32 *)((u8 *)arg0 + 0x8c);
    if (t == 0) {
        if (*(s32 *)((u8 *)arg0 + 0xA0) >= 0) {
            *(s32 *)((u8 *)arg0 + 0x88) = func_080C9024(arg0, 3, 0, 0, t, t, 0x100, t);
            func_08092E84(0x57);
        } else {
            *(s32 *)((u8 *)arg0 + 0x88) = func_080C9024(arg0, 5, 0, 0, t, 6, 0x100, t);
            func_08092E84(0x58);
        }
        *(s32 *)((u8 *)arg0 + 0x8c) += 1;
        return;
    }
    func_080C9164(arg0);
}
