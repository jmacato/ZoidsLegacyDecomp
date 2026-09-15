#include "m2c_prelude.h"

struct Record {
    u8 pad0[8];
    s32 x;
    s32 y;
    u8 pad10[14];
    u8 value;
};

extern s32 func_080AC098(struct Record *);
extern u16 D_0202ECF4;
extern u16 D_020324A4[];
extern u8 *D_02032E94;

void sub_080A98C4(struct Record *arg0)
{
    register s32 temp_r1 asm("r1");
    register s32 temp_r2 asm("r2");
    s32 var_r0_3;
    s32 var_r0_4;
    s32 var_r3;
    s32 var_r4;
    s32 var_r5;
    u32 temp_r1_2;
    u32 temp_r2_2;
    u32 temp_r2_4;
    u8 temp_r2_5;
    u32 compare_r0;
    register u32 var_r1 asm("r1");
    u8 values[4];
    u32 next_x;
    u8 *values_r2;
    u16 *dims;

    if (D_0202ECF4 == 0) {
        {
        register s32 x asm("r0");
        x = arg0->x;
        if (x < 0) {
            x += 0xFFF;
        }
        var_r5 = (x >> 12) & 0xFF;
        }
        {
        register s32 y asm("r0");
        y = arg0->y;
        if (y < 0) {
            y += 0xFFF;
        }
        var_r0_3 = (y >> 12) & 0xFF;
        }
        arg0->value = *(u8 *)(D_02032E94 +
            (var_r5 + (((u32)D_020324A4[0] * var_r0_3) >> 1)));
        return;
    }

    temp_r2 = arg0->x;
    var_r0_3 = temp_r2;
    if (temp_r2 < 0) {
        var_r0_3 = temp_r2 + 0x7FF;
    }
    var_r5 = var_r0_3 >> 11;
    {
    register s32 remainder asm("r0");
    remainder = temp_r2 - (var_r5 << 11);
    temp_r2 = 0x3FF;
    if (remainder <= temp_r2) {
        var_r5--;
    }
    }
    temp_r1 = arg0->y;
    var_r0_4 = temp_r1;
    if (temp_r1 < 0) {
        var_r0_4 = temp_r1 + 0x7FF;
    }
    var_r4 = var_r0_4 >> 11;
    {
    register s32 remainder asm("r0");
    remainder = temp_r1 - (var_r4 << 11);
    if (remainder <= temp_r2) {
        var_r4--;
    }
    }
    var_r0_4 = func_080AC098(arg0) << 24;
    var_r3 = var_r4;
    asm volatile("" : "+r"(var_r3));
    if (var_r0_4 == 0) {
        var_r3++;
    }
    values_r2 = values;
    dims = D_020324A4;
    {
    s32 first_offset;
    first_offset = dims[0] * var_r3;
    var_r4 = (s32)D_02032E94;
    values_r2[0] = *(u8 *)((u8 *)var_r4 + (var_r5 + first_offset));
    }
    next_x = var_r5 + 1;
    temp_r1_2 = dims[0];
    if (next_x < (u32)temp_r1_2) {
        u8 *second_value;
        second_value = values;
        temp_r1_2 *= var_r3;
        temp_r1_2 += var_r5;
        second_value[1] = *(u8 *)(temp_r1_2 - (0 - (u32)var_r4) + 1);
        temp_r2_2 = var_r3 + 1;
        if (temp_r2_2 < (u32)dims[1]) {
            u8 *lower_values;
            lower_values = values;
            lower_values[2] = *(u8 *)((u8 *)var_r4 +
                (var_r5 + (dims[0] * temp_r2_2)));
            {
            u32 fourth_offset;
            fourth_offset = dims[0] * temp_r2_2 + var_r5;
            fourth_offset += (u32)var_r4;
            lower_values[3] = *(u8 *)(fourth_offset + 1);
            }
        } else {
            values[2] = *(u8 *)((u8 *)var_r4 + var_r5);
            values[3] = *(u8 *)((u8 *)var_r4 + var_r5 + 1);
        }
    } else {
        values[1] = *(u8 *)((u8 *)var_r4 + (temp_r1_2 * var_r3));
        temp_r2_4 = var_r3 + 1;
        if (temp_r2_4 < (u32)dims[1]) {
            values[2] = *(u8 *)((u8 *)var_r4 +
                (var_r5 + (dims[0] * temp_r2_4)));
            values[3] = *(u8 *)((u8 *)var_r4 + (dims[0] * temp_r2_4));
        } else {
            values[2] = *(u8 *)((u8 *)var_r4 + var_r5);
            values[3] = *(u8 *)var_r4;
        }
    }
    {
    u8 *eq_r0;
    u8 *eq_r1;
    eq_r0 = values;
    eq_r1 = values;
    temp_r2_5 = eq_r0[0];
    compare_r0 = eq_r1[1];
    }
    var_r1 = temp_r2_5;
    if ((var_r1 == compare_r0) && (var_r1 == values[2]) &&
        (var_r1 == values[3])) {
        arg0->value = temp_r2_5;
        return;
    }
    var_r1 = values[0];
    if (!(0x40 & var_r1) || (var_r1 = values[1], ((0x40 & var_r1) == 0)) ||
        (var_r1 = values[2], ((0x40 & var_r1) == 0)) ||
        (var_r1 = values[3], ((0x40 & var_r1) == 0))) {
        arg0->value = var_r1;
    }
}
