#include "m2c_prelude.h"
extern volatile u16 D_04000004;
extern u16 D_0300004C;
extern u16 D_02031988;

void sub_080A00D4(void) {
    while ((D_04000004 & 2) == 0)
        ;
    *(volatile u16 *)0x04000000 = D_0300004C;
    *(volatile u16 *)0x05000000 = D_02031988;
}
