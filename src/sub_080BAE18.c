#include "m2c_prelude.h"
int func_8093E30(void *, void *, void *);

void sub_080BAE18(void *arg0) {
    u8 local;
    int val;
    register u32 t asm("r0");

    val = (s16) func_8093E30((u8 *)arg0 + 0x28, (u8 *)arg0 + 4, &local);
    *(u16 *)((u8 *)arg0 + 0xC) = val << 1;
    if (local == 0 || (val << 17) > 0x03000000) {
        t = *(u32 *)arg0 | 0x20000;
    } else {
        t = *(u32 *)arg0 & 0xFFFDFFFF;
    }
    *(u32 *)arg0 = t;
}
