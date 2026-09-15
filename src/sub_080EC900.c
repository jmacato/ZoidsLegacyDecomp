#include "m2c_prelude.h"

M2C_UNK func_080ECD64(void *, void *, s32);

void sub_080EC900(void *arg0, void *arg1) {
    register void *state asm("r6");
    register u8 *temp_r3 asm("r3");
    register s32 temp_r2_2 asm("r2");
    u8 temp_r5;
    register u8 *temp_r0 asm("r0");
    register s32 temp_r1 asm("r1");
    register u8 *temp_r2 asm("r2");

    state = arg1;
    temp_r1 = (s32)M2C_FIELD(state, u8 **, 0x40);
    temp_r5 = *(u8 *)temp_r1;
    temp_r2 = (u8 *)temp_r1 + 1;
    M2C_FIELD(state, u8 **, 0x40) = temp_r2;
    temp_r0 = M2C_FIELD(arg0, u8 **, 0x18);
    temp_r1 = *(u8 *)(temp_r1 + 1);
    temp_r3 = (u8 *)(temp_r1 + (s32)temp_r0);
    temp_r0 = temp_r2 + 1;
    M2C_FIELD(state, u8 **, 0x40) = temp_r0;
    temp_r2_2 = temp_r2[1];
    M2C_FIELD(state, u8 **, 0x40) = temp_r0 + 1;
    switch ((u32)temp_r5) {
    case 0:
        *temp_r3 = temp_r2_2;
        return;
    case 1: {
        register s32 current asm("r1");
        register s32 result asm("r0");
        current = *temp_r3;
        result = current + temp_r2_2;
        *temp_r3 = result;
        return;
    }
    case 2: {
        register s32 current asm("r1");
        register s32 result asm("r0");
        current = *temp_r3;
        result = current - temp_r2_2;
        *temp_r3 = result;
        return;
    }
    case 3:
        *temp_r3 = M2C_FIELD(arg0, u8 **, 0x18)[temp_r2_2];
        return;
    case 4: {
        register s32 current asm("r1");
        register s32 other asm("r0");
        other = (s32)(M2C_FIELD(arg0, u8 **, 0x18) + temp_r2_2);
        current = *temp_r3;
        other = *(u8 *)other;
        other = current + other;
        *temp_r3 = other;
        return;
    }
    case 5: {
        register s32 current asm("r1");
        register s32 other asm("r0");
        other = (s32)(M2C_FIELD(arg0, u8 **, 0x18) + temp_r2_2);
        current = *temp_r3;
        other = *(u8 *)other;
        other = current - other;
        *temp_r3 = other;
        return;
    }
    case 6:
        temp_r3 = (u8 *)(u32)*temp_r3;
        if ((u32)temp_r3 == (u32)temp_r2_2) {
            goto invoke;
        }
        goto skip;
    case 7:
        temp_r3 = (u8 *)(u32)*temp_r3;
        if ((u32)temp_r3 != (u32)temp_r2_2) {
            goto invoke;
        }
        goto skip;
    case 8:
        temp_r3 = (u8 *)(u32)*temp_r3;
        if ((u32)temp_r3 > (u32)temp_r2_2) {
            goto invoke;
        }
        goto skip;
    case 9:
        temp_r3 = (u8 *)(u32)*temp_r3;
        if ((u32)temp_r3 >= (u32)temp_r2_2) {
            goto invoke;
        }
        goto skip;
    case 10:
        temp_r3 = (u8 *)(u32)*temp_r3;
        if ((u32)temp_r3 <= (u32)temp_r2_2) {
            goto invoke;
        }
        goto skip;
    case 11:
        temp_r3 = (u8 *)(u32)*temp_r3;
        if ((u32)temp_r3 < (u32)temp_r2_2) {
            goto invoke;
        }
        goto skip;
    case 12: {
        register u8 *other asm("r0");
        other = M2C_FIELD(arg0, u8 **, 0x18) + temp_r2_2;
        temp_r3 = (u8 *)(u32)*temp_r3;
        if ((u32)temp_r3 == (u32)*other) {
            goto invoke;
        }
        goto skip;
    }
    case 13: {
        register u8 *other asm("r0");
        other = M2C_FIELD(arg0, u8 **, 0x18) + temp_r2_2;
        temp_r3 = (u8 *)(u32)*temp_r3;
        if ((u32)temp_r3 != (u32)*other) {
            goto invoke;
        }
        goto skip;
    }
    case 14: {
        register u8 *other asm("r0");
        other = M2C_FIELD(arg0, u8 **, 0x18) + temp_r2_2;
        temp_r3 = (u8 *)(u32)*temp_r3;
        if ((u32)temp_r3 > (u32)*other) {
            goto invoke;
        }
        goto skip;
    }
    case 15: {
        register u8 *other asm("r0");
        other = M2C_FIELD(arg0, u8 **, 0x18) + temp_r2_2;
        temp_r3 = (u8 *)(u32)*temp_r3;
        if ((u32)temp_r3 >= (u32)*other) {
            goto invoke;
        }
        goto skip;
    }
    case 16: {
        register u8 *other asm("r0");
        other = M2C_FIELD(arg0, u8 **, 0x18) + temp_r2_2;
        temp_r3 = (u8 *)(u32)*temp_r3;
        if ((u32)temp_r3 <= (u32)*other) {
            goto invoke;
        }
        goto skip;
    }
    case 17: {
        register u8 *other asm("r0");
        other = M2C_FIELD(arg0, u8 **, 0x18) + temp_r2_2;
        temp_r3 = (u8 *)(u32)*temp_r3;
        if ((u32)temp_r3 < (u32)*other) {
            goto invoke;
        }
        goto skip;
    }
    }
    return;
invoke:
    func_080ECD64(arg0, state, *(s32 *)0x030074B4);
    return;
skip:
    M2C_FIELD(state, u8 **, 0x40) += 4;
}
