#include "m2c_prelude.h"
int func_80A016C(int, int, int);
extern u8 D_020218E4[];
extern u8 D_off_69FC[];

int sub_080A0FEC(u8 arg0, u8 **arg1) {
    s32 base;
    u32 idx;
    u32 *p;

    base = (s32)D_020218E4;
    idx = (*arg1)[1];
    p = (u32 *)((idx >> 5) * 4);
    base += (s32)D_off_69FC;
    p = (u32 *)((s32)p + base);
    idx &= 0x1F;
    if (*p & (1 << idx)) {
        func_80A016C(arg0, 15, 0);
    } else {
        func_80A016C(arg0, 16, 0);
    }
    return 0;
}
