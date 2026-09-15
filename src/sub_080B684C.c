#include "m2c_prelude.h"
M2C_UNK func_08092E84(s32);

extern u16 D_03006034_A[];
extern u16 D_03006034_B[];
extern u16 D_03006034_C[];
extern u16 D_03006034_D[];

s32 sub_080B684C(s32 arg0, s32 arg1) {
    register s32 value asm("r4");
    register s32 bound asm("r5");

    value = arg0;
    bound = arg1;
    if (D_03006034_A[0] & 0x20) {
        if (value > 1) {
            value--;
        } else {
            value = bound;
        }
        func_08092E84(0x40);
    }
    if (D_03006034_B[0] & 0x10) {
        if (value < bound) {
            value++;
        } else {
            value = 1;
        }
        func_08092E84(0x40);
    }
    if (D_03006034_C[0] & 0x200) {
        if (value > 10) {
            value -= 10;
        } else if (value > 1) {
            value = 1;
        } else {
            value = bound;
        }
        func_08092E84(0x40);
    }
    if (D_03006034_D[0] & 0x100) {
        if (value < bound - 10) {
            value += 10;
        } else if (value < bound) {
            value = bound;
        } else {
            value = 1;
        }
        func_08092E84(0x40);
    }
    return value;
}
