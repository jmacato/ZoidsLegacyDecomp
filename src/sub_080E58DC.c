#include "m2c_prelude.h"
struct S24 { s32 a, b, c, d, e, f; };
extern struct S24 D_087B2524[];
s32 func_80E523C(u8);

s32 sub_080E58DC(u8 *arg0, u8 arg1, void *arg2) {
    u16 *p = (u16 *)(arg0 + arg1 * 4 + 0x52);
    if (*p == 0) {
        return 0;
    }
    *(struct S24 *)arg2 = D_087B2524[*p];
    if (!(*(u16 *)((u8 *)arg2 + 2) & 1)) {
        if (arg1 > 3) {
            s32 t = ((u32)(func_80E523C(*arg0) << 0x18) >> 0x16) - 4;
            s32 off = arg1 + t;
            u8 *base = arg0 + 0x1E;
            *(u16 *)((u8 *)arg2 + 0xA) = (u16)(base[off] * 0x14 + *(u16 *)((u8 *)arg2 + 0xA));
        }
        if ((s16)*(u16 *)((u8 *)arg2 + 0xA) > 0x270F) {
            *(u16 *)((u8 *)arg2 + 0xA) = 0x270F;
        }
        if ((s16)*(u16 *)((u8 *)arg2 + 0xC) > (s16)*(u16 *)((u8 *)arg2 + 0xE)) {
            *(u16 *)((u8 *)arg2 + 0xC) = *(u16 *)((u8 *)arg2 + 0xE);
        }
    }
    return 1;
}
