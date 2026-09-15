#include "m2c_prelude.h"
void func_8092834(void);
void func_8092FA0(void);

void sub_0809223C(u8 arg0) {
    volatile u8 *p;
    u8 temp_r0;
    int var_r1_2;

    temp_r0 = *(u8 *)0x0300067D;
    if (arg0 > temp_r0) {
        arg0 = arg0 - temp_r0;
    } else {
        arg0 = 1;
    }
    var_r1_2 = (u8)(arg0 - 1);
    if (var_r1_2 != 0xFF) {
        p = (volatile u8 *)0x0300067C;
        do {
            if (var_r1_2 != 0) {
                *p = 2;
            } else {
                *p = 1;
            }
            var_r1_2 -= 1;
            do { } while (*p != 0);
            var_r1_2 = (u8)var_r1_2;
        } while (var_r1_2 != 0xFF);
    }
    func_8092834();
    func_8092FA0();
    *(u8 *)0x0300067D = 0;
}
