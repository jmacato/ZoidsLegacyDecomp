#include "m2c_prelude.h"
void sub_080EB5DC(void *arg0, void *arg1)
{
    register s32 v asm("r2") = 0;
    *(s8 *)((s32)arg1 + 0x16) = v;
    *(s8 *)((s32)arg1 + 0x1A) = v;
    v = *(u8 *)((s32)arg1 + 0x18);
    if (v == 0) {
        v = 0xC;
    } else {
        v = 3;
    }
    {
        register u8 t asm("r3");
        t = *(u8 *)arg1;
        t |= v;
        *(u8 *)arg1 = t;
    }
}
