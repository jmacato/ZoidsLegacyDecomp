#include "m2c_prelude.h"
extern u8 D_020218E8[];
extern u8 D_off_6908[];
extern u8 D_020218E4[];
void func_80E6020(u32);
void func_80E700C(void);
void sub_080E5C34(u8 arg0) {
    register u8 temp_r3 asm("r3");
    register s32 base asm("r1");
    s32 temp_r0;
    u32 var_r2;
    u8 *r4;
    temp_r3 = arg0;
    temp_r0 = temp_r3 * 0x70;
    base = (s32)D_020218E8;
    r4 = (u8 *)(temp_r0 + base);
    var_r2 = 0;
    base += (s32)D_off_6908;
    goto test;
inc:
    var_r2 = (u32) (u8) (var_r2 + 1);
test:
    if (var_r2 > 5) goto after;
    if (*(u8 *)(var_r2 + base) != temp_r3) goto inc;
    func_80E6020(var_r2);
after:
    if (r4[2] != 0) {
        func_80E700C();
    }
    *(s8 *)r4 = 0;
    D_020218E4[1] = D_020218E4[1] - 1;
}
