#include "m2c_prelude.h"

extern u8 D_030033C4[];

s32 func_809370C(void *, s32 *, s32 *);
s32 func_80ECD30(s32, s32);

s32 sub_08093E30(s32 *position, s16 *output, s8 *visible) {
    s32 input[3];
    s32 transformed[3];
    u8 *base;
    register s32 result asm("r0");
    s32 depth;
    s32 scale;

    base = D_030033C4;
    input[0] = position[0] - *(s32 *)(base + 0);
    input[1] = position[1];
    input[2] = *(s32 *)(base + 4) - position[2];
    result = func_809370C(base + 0x40, input, transformed);
    depth = transformed[2] + *(s32 *)(base + 8);
    if (depth < 0 || depth >= *(s32 *)(base + 0x60) ||
        (scale = *(s32 *)(base + 0x1C)) == 0) {
        *visible = 0;
        goto done;
    }

    output[0] = *(s32 *)(base + 0x14) +
        func_80ECD30(transformed[0] * scale, depth);
    output[1] = *(s32 *)(base + 0x18) +
        func_80ECD30(transformed[1] * *(s32 *)(base + 0x1C), depth);
    *visible = 1;
    result = (s16)func_80ECD30(*(s32 *)(base + 0x1C) << 16, depth);

done:
    return result;
}
