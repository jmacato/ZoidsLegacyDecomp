#include "m2c_prelude.h"
void sub_080ABE3C(void *arg0) {
    s32 temp_r1;
    s32 temp_r3;

    temp_r3 = M2C_FIELD(arg0, s32 *, 8) + M2C_FIELD(arg0, s32 *, 0x10);
    M2C_FIELD(arg0, s32 *, 8) = temp_r3;
    temp_r1 = M2C_FIELD(arg0, s32 *, 0xC) + M2C_FIELD(arg0, s32 *, 0x14);
    M2C_FIELD(arg0, s32 *, 0xC) = temp_r1;
    if (*(u16 *)0x0202ECF4 == 0) {
        M2C_FIELD(arg0, s32 *, 8) = (s32) (temp_r3 & 0xFFFFF);
        M2C_FIELD(arg0, s32 *, 0xC) = (s32) (temp_r1 & 0xFFFFF);
    }
}
