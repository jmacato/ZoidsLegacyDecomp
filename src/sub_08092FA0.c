#include "m2c_prelude.h"
void func_80EB748(void);
void func_80EBD2C(void);
void func_80EBD90(void);

void sub_08092FA0(void) {
    u8 *p;
    u8 t;
    func_80EB748();
    p = (u8 *)0x03003170;
    t = *p;
    if (t == 1) {
        func_80EBD2C();
        *p = 2;
    } else if (t == 3) {
        func_80EBD90();
        *p = 0;
    }
}

u8 *sub_08092FD0(u8 arg) {
    register u8 a asm("r1") = arg;
    if (a == 0) {
        register u8 *q asm("r2") = (u8 *)0x03003170;
        if (*q == 0) {
            *q = 1;
            return (u8 *)0x03003170;
        }
    }
    if (a == 1) {
        if (*(u8 *)0x03003170 == 2) {
            *(u8 *)0x03003170 = 3;
        }
    }
    return (u8 *)0x03003170;
}
