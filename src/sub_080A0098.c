#include "m2c_prelude.h"
void sub_080A0098(void) {
    register volatile u16 *disp asm("r2") = (volatile u16 *)0x04000004;
    register volatile u16 *p asm("r4");
    u16 t;
    t = *disp & 2;
    p = (volatile u16 *)0x02031988;
    while (t == 0)
        t = *disp & 2;
    *(volatile u16 *)0x04000000 = 0;
    *p = *(volatile u16 *)0x05000000;
    *(volatile u16 *)0x05000000 = 0;
}
