#include "m2c_prelude.h"
extern void func_08092E84(s32);
extern s32 func_080C9024(void *, s32, s32, s32, s32, s32, s32, s32);
extern void func_080C9164(void *);

void sub_080C9E94(void *arg0) {
    s32 *p8c = (s32 *)((u8 *)arg0 + 0x8c);
    s32 t = *p8c;
    if (t == 0) {
        *(s32 *)((u8 *)arg0 + 0x88) = func_080C9024(arg0, 6, 0, 0, t, 7, 0x100, t);
        func_08092E84(0x58);
        *p8c = *p8c + 1;
        return;
    }
    func_080C9164(arg0);
}
