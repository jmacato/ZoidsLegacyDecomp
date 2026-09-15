#include "m2c_prelude.h"
M2C_UNK func_080ECD2C(M2C_UNK, M2C_UNK, M2C_UNK);
extern u8 D_02032B9C;
extern u8 D_02032B9E;
extern u8 D_02032B9D;
extern u8 D_03000074;

void sub_080BA878(void) {
    D_02032B9C = 1;
    D_02032B9E = 0;
    D_02032B9D = 0;
    func_080ECD2C((void *)0x080008E4, (void *)0x030060FC, (void *)0x04000014);
    D_03000074 |= 8;
}
