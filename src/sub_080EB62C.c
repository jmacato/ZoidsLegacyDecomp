#include "m2c_prelude.h"
s32 func_80EAA94(s32, s32);

extern u8 D_086A3200[];
extern u32 D_086A32B4[];

s32 sub_080EB62C(void *arg0, u8 arg1, s32 arg2) {
    s32 temp_r4;
    s32 var_r7;
    u32 acc;
    u32 v2;
    u8 temp_r1;
    u8 var_r6;

    var_r6 = arg1;
    var_r7 = arg2 << 0x18;
    if ((u32) var_r6 > 0xB2U) {
        var_r6 = 0xB2;
        var_r7 = 0xFF000000;
    }
    acc = D_086A3200[var_r6];
    acc = D_086A32B4[acc & 0xF] >> (acc >> 4);
    temp_r1 = D_086A3200[var_r6 + 1];
    v2 = D_086A32B4[temp_r1 & 0xF] >> (temp_r1 >> 4);
    temp_r4 = ((s32 *) arg0)[1];
    {
        register s32 q asm("r1");
        q = func_80EAA94(v2 - acc, var_r7);
        asm volatile("" : "+r"(q));
        return func_80EAA94(temp_r4, acc + q);
    }
}

void sub_080EB690(void) {
}
