#include "m2c_prelude.h"
extern void func_08094554(void *);

void sub_080CD258(void *arg0) {
    s32 temp_r1 = *(s32 *)arg0;
    s32 var_r0_2;
    if ((0xC0 & temp_r1) == 0xC0) {
        if (!(temp_r1 & 0x8000)) {
            *(u16 *)((u8 *)arg0 + 4) = *(u16 *)((u8 *)arg0 + 4) + 0x10;
        } else {
            *(u16 *)((u8 *)arg0 + 4) = *(u16 *)((u8 *)arg0 + 4) - 0x10;
        }
        var_r0_2 = *(u16 *)((u8 *)arg0 + 6) - 8;
    } else {
        if (!(temp_r1 & 0x8000)) {
            *(u16 *)((u8 *)arg0 + 4) = *(u16 *)((u8 *)arg0 + 4) + 0x18;
        } else {
            *(u16 *)((u8 *)arg0 + 4) = *(u16 *)((u8 *)arg0 + 4) - 0x18;
        }
        var_r0_2 = *(u16 *)((u8 *)arg0 + 6) - 0xC;
    }
    *(u16 *)((u8 *)arg0 + 6) = var_r0_2;
    if (*(s32 *)arg0 & 0x8000) {
        if ((s32) *(s16 *)((u8 *)arg0 + 4) < -0x40) {
            goto block_14;
        }
        goto block_13;
    }
    if ((s32) *(s16 *)((u8 *)arg0 + 4) <= 0x130) {
block_13:
        if ((s32) *(s16 *)((u8 *)arg0 + 6) < -0x40) {
            goto block_14;
        }
    } else {
block_14:
        func_08094554(arg0);
    }
}
