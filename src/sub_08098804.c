#include "m2c_prelude.h"
extern u8 D_0200E6C4[]; extern u8 D_0200DE90[];
void sub_08098804(void) {
    u8 i;
    for (i = 0; i <= 9; i++) {
        D_0200E6C4[i] = 0;
        D_0200DE90[i * 0xD2] = 0;
    }
}
