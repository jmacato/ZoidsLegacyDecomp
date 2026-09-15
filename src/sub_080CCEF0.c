#include "m2c_prelude.h"
void func_8094554(void *);

void sub_080CCEF0(void *arg0) {
    register u32 v asm("r0");

    if ((*(u32 *)((s8 *)arg0 + 0) & 0x8000) == 0) {
        v = *(u32 *)((s8 *)arg0 + 40);
        v += *(u32 *)((s8 *)arg0 + 44);
        *(u32 *)((s8 *)arg0 + 40) = v;
        v >>= 8;
        *(u16 *)((s8 *)arg0 + 4) = v;
        if ((s32)(v << 16) > 0x01100000) {
            func_8094554(arg0);
        }
    } else {
        v = *(u32 *)((s8 *)arg0 + 40) - *(u32 *)((s8 *)arg0 + 44);
        *(u32 *)((s8 *)arg0 + 40) = v;
        v >>= 8;
        *(u16 *)((s8 *)arg0 + 4) = v;
        if ((s32)(v << 16) < 0) {
            func_8094554(arg0);
        }
    }
}
