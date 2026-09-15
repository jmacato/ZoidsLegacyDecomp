#include "m2c_prelude.h"
extern u8 D_020218E4[];
s32 func_080A016C(u8, s32, s32);
s32 func_080C1070(s32, s32);

s32 sub_080A103C(u8 arg0, void **arg1) {
    u8 temp_r5;
    u8 target;
    u8 *base;
    u8 *p7;
    u32 var_r2;

    temp_r5 = arg0;
    var_r2 = 0;
    base = D_020218E4;
    p7 = base + 0x690C;
    target = *((u8 *)*arg1 + 1);
    do {
        u8 idx = *(u8 *)(var_r2 + (u32)p7);
        u8 v = *(u8 *)(base + idx * 0x70 + 6);
        u8 w = *(u8 *)(base + v * 0x40 + 0x5A94);
        if (w == target) {
            break;
        }
        var_r2 += 1;
    } while (var_r2 <= 5);
    if (var_r2 <= 5) {
        func_080A016C(temp_r5, 0xF, 0);
    } else {
        func_080A016C(temp_r5, 0x10, 0);
    }
    return 0;
}

s32 sub_080A10A0(u8 arg0, void **arg1) {
    u8 temp_r4;

    temp_r4 = arg0;
    switch (*((u8 *)*arg1 + 1)) {
    case 0x47:
        if ((func_080C1070(4, 0) != 0) || (func_080C1070(4, 1) != 0) || (func_080C1070(4, 2) != 0)) {
            func_080A016C(temp_r4, 0xF, 0);
        } else {
            func_080A016C(temp_r4, 0x10, 0);
        }
        break;
    case 0x76:
        if (func_080C1070(5, 1) != 0) {
            func_080A016C(temp_r4, 0xF, 0);
        } else {
            func_080A016C(temp_r4, 0x10, 0);
        }
        break;
    case 0x80:
        if ((func_080C1070(1, 0) != 0) || (func_080C1070(1, 1) != 0)) {
            func_080A016C(temp_r4, 0xF, 0);
        } else {
            func_080A016C(temp_r4, 0x10, 0);
        }
        break;
    case 0x81:
        if ((func_080C1070(2, 0) != 0) || (func_080C1070(2, 1) != 0)) {
            func_080A016C(temp_r4, 0xF, 0);
        } else {
            func_080A016C(temp_r4, 0x10, 0);
        }
        break;
    case 0x82:
        if (func_080C1070(3, 0) != 0) {
            func_080A016C(temp_r4, 0xF, 0);
        } else {
            func_080A016C(temp_r4, 0x10, 0);
        }
        break;
    case 0x83:
        if ((func_080C1070(0, 0) != 0) || (func_080C1070(0, 1) != 0) || (func_080C1070(0, 3) != 0) || (func_080C1070(0, 4) != 0)) {
            func_080A016C(temp_r4, 0xF, 0);
        } else {
            func_080A016C(temp_r4, 0x10, 0);
        }
        break;
    case 0x84:
        if ((func_080C1070(6, 3) != 0) || (func_080C1070(6, 4) != 0) || (func_080C1070(6, 5) != 0)) {
            func_080A016C(temp_r4, 0xF, 0);
        } else {
            func_080A016C(temp_r4, 0x10, 0);
        }
        break;
    case 0x97:
        if ((func_080C1070(7, 0) != 0) || (func_080C1070(7, 1) != 0) || (func_080C1070(7, 3) != 0) || (func_080C1070(7, 4) != 0)) {
            func_080A016C(temp_r4, 0xF, 0);
        } else {
            func_080A016C(temp_r4, 0x10, 0);
        }
        break;
    default:
        func_080A016C(temp_r4, 0x10, 0);
        break;
    }
    return 0;
}
