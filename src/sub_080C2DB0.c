#include "m2c_prelude.h"
extern u8 D_02032F7C[];
void sub_080C2DB0(void) {
    u8 i;
    for (i = 0; i <= 5; i++) {
        D_02032F7C[i] = 0x80;
    }
}
