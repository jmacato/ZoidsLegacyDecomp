#include "m2c_prelude.h"
void func_08095208(s32, s32, s32);
void func_0809544C(s32, u16, s32, u16);
void func_080ED17C(s32);
extern s16 D_0300004E[];

void sub_080CFD98(void)
{
    register s32 var_r9 asm("r9");
    u8 temp_r0;
    u8 temp_r2;
    u8 temp_r3;
    u8 input_state;
    s32 var_r0;
    u8 var_r5;
    u8 var_r7;
    register u8 *timer asm("r4") = (u8 *)0x02033F55;
    register u8 *state asm("r8");

    var_r7 = 0;
    var_r5 = 0;
    var_r9 = 0;
    timer = (u8 *)0x02033F55;
loop_1:
    input_state = *(u8 *)0x02030664;
    state = (u8 *)0x02033F54;
    if ((input_state != 1) && (*(u8 *)0x02033FCC == 0)) {
        temp_r2 = *state;
        if (temp_r2 == 0) {
            register u16 held_input asm("r1") = *(u16 *)0x0300000C;
            register u8 state_value asm("r3") = 2;
            if (2 & held_input) {
                register u8 *state_store asm("r1") = state;
                *state_store = state_value;
                *timer = temp_r2;
            }
            goto block_6;
        }
        goto block_7;
    }
block_6:
    {
        register u8 *state_check asm("r1") = state;
        if (*state_check != 0) {
block_7:
        {
            register u8 *branch_state asm("r6") = state;
            if (*branch_state == 1) {
                *timer += 1;
                temp_r3 = *timer;
                func_0809544C(0xF0, (u16)(0x50 - temp_r3), 0xF0,
                               (u16)(((temp_r3 + 0x50) << 8) | 0xA0));
                if (*timer == 0x20)
                    *branch_state = 0;
            } else {
                *timer += 1;
                temp_r0 = *timer;
                func_0809544C(0xF0, temp_r0 + 0x30, 0xF0,
                               (u16)(((0x70 - temp_r0) << 8) | 0xA0));
                if (*timer == 0x20) {
                    register u8 zero asm("r0") = 0;
                    register u8 *state_store asm("r1") = state;
                    *state_store = zero;
                    *(u8 *)0x02033FCC = 1;
                    *(s16 *)0x03000052 = 0x10;
                    D_0300004E[0] = 0xFF;
                }
            }
        }
    }
    }
    if (var_r9 == 0) {
        if (var_r7 == 0) {
            func_08095208((var_r5 << 5) + 0x083C773C, 0x05000080, 0x20);
            if (var_r5 == 5) {
                register u8 one asm("r1") = 1;
                var_r9 = one;
            } else {
                var_r0 = var_r5 + 1;
                goto block_22;
            }
            goto block_23;
        }
    } else if (var_r7 == 0) {
        func_08095208((var_r5 << 5) + 0x083C773C, 0x05000080, 0x20);
        if (var_r5 == 0) {
            var_r9 = 0;
        } else {
            var_r0 = var_r5 - 1;
block_22:
            var_r5 = var_r0;
        }
block_23:
        var_r7 = 4;
    }
    var_r7 -= 1;
    func_080ED17C(1);
    goto loop_1;
}
