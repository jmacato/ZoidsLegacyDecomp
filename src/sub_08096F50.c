#include "m2c_prelude.h"
extern u16 D_0300000C;
extern u16 D_0300000E;
extern u16 D_03006034;
extern u16 D_03006036;
extern u8 D_03006038;
extern u8 D_03000075;

void sub_08096F50(void) {
    u16 *pC = &D_0300000C;
    u16 *p36 = &D_03006036;
    register u16 temp_r1 asm("r1") = *pC;
    if (temp_r1 == *p36) {
        register u8 *p38 asm("r2") = &D_03006038;
        s32 sum = D_03000075 + *p38;
        *p38 = sum;
        if ((u8)sum > 7) {
            D_03006034 = temp_r1;
            *p38 = 0;
        } else {
            D_03006034 = 0;
        }
    } else {
        *p36 = temp_r1;
        D_03006034 = D_0300000E;
        D_03006038 = 0;
    }
}
