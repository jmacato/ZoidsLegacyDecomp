#include "m2c_prelude.h"
void sub_080EB694(void *arg0) {
    register s32 v asm("r3") = M2C_FIELD(arg0, s32 *, 0x34);
    if (v == 0x68736D53) {
        M2C_FIELD(arg0, s32 *, 4) = (s32)(M2C_FIELD(arg0, s32 *, 4) & 0x7FFFFFFF);
    }
}
