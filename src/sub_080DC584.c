#include "m2c_prelude.h"

M2C_UNK func_08094554(void *);                      /* extern */
M2C_UNK func_08095114(void *);                      /* extern */
M2C_UNK func_08095208(M2C_UNK, s32, s32);           /* extern */
M2C_UNK func_080D12A0(s32, s32);                    /* extern */
M2C_UNK func_080D218C();                            /* extern */
void *func_080D2450(void *, s32, s32, s16, s32, s32, u32, u32); /* extern */
M2C_UNK func_080ECD28(s32, M2C_UNK, s32);           /* extern */
u16 func_080ECD98(s32, s32);                        /* extern */

void sub_080DC584(void *arg0) {
    volatile s32 sp10;
    volatile s32 sp14;
    s16 temp_r1_2;
    register s32 *var_r9 asm("r9");
    s32 temp_r2;
    s32 temp_r2_2;
    s32 temp_r2_4;
    s32 temp_r2_5;
    s32 temp_r3;
    s32 temp_r3_2;
    s32 temp_r3_3;
    s32 temp_r3_4;
    s32 temp_r3_5;
    s32 temp_r4;
    s32 temp_r4_2;
    s32 temp_r4_4;
    s32 temp_r4_5;
    s32 temp_r5;
    s32 temp_r5_2;
    s32 temp_r5_3;
    s32 temp_r5_4;
    s32 temp_r6_2;
    s32 temp_r6_3;
    s32 temp_r6_5;
    s32 temp_r6_6;
    s32 var_r0;
    register s32 var_r1 asm("r1");
    register s32 var_r6 asm("r6");
    u16 temp_r0;
    u16 temp_r0_3;
    u16 temp_r0_5;
    u16 temp_r0_7;
    u32 temp_r6_4;
    u32 temp_r0_2;
    u32 temp_r0_4;
    u32 temp_r0_6;
    u32 temp_r0_8;
    register u32 temp_r2_3 asm("r2");
    u32 temp_r4_3;
    register u32 temp_r6 asm("r6");
    u8 var_r7;
    u8 var_r7_2;
    u8 var_r7_3;
    u8 var_r7_4;
    void *temp_r1;
    void *temp_r2_6;
    void *temp_r2_7;
    void *temp_r2_8;

    register void *owner_r8 asm("r8") = arg0;
    register u32 *state_ptr asm("r5") = (u32 *)((u8 *)owner_r8 + 0x8C);

    temp_r6 = *state_ptr;
    if (temp_r6 > 0x13U) {
        goto high_state;
    }
    if (temp_r6 == 0) {
        void *created;
        register void *base_r2 asm("r2");
        register void *base_r3 asm("r3");

        created = func_080D2450(owner_r8, 0, 0, M2C_FIELD(arg0, s16 *, 4), (s32) (s16) (M2C_FIELD(arg0, s32 *, 8) + 0x80), 0x420, temp_r6, temp_r6);
        base_r2 = owner_r8;
        M2C_FIELD(base_r2, void **, 0xC) = created;
        M2C_FIELD(owner_r8, s32 *, 0xA8) = 0xC0;
        created = func_080D2450(owner_r8, 0, 0, (s16) (M2C_FIELD(base_r2, s32 *, 4) - 0x20), (s32) (s16) (M2C_FIELD(base_r2, s32 *, 8) + 0x80), 0x420, temp_r6, temp_r6);
        base_r3 = owner_r8;
        M2C_FIELD(base_r3, void **, 0x10) = created;
        func_080ECD28(0x05000000, 0x02034934, 0x20);
        func_080ECD28(0x05000200, 0x02034A34, 0x18);
        func_080D12A0(0xB, 0);
    }
    temp_r2_3 = *state_ptr;
    if (temp_r2_3 <= 3U) {
        register void *base_r4 asm("r4") = owner_r8;
        u32 flags = M2C_FIELD(base_r4, u32 *, 0) & 2;
        var_r6 = 0xFFF0;
        if (!flags) {
            var_r6 = 0x10;
        }
        sp10 = 0xFFE0;
        asm volatile("mov r9, r5" : "=r"(var_r9));
        sp14 = var_r6 << 0x10;
    } else {
        register void *flags_base asm("r1") = owner_r8;
        if (!(M2C_FIELD(flags_base, s32 *, 0) & 2)) {
            var_r1 = (s32) (temp_r2_3 << 0x17) >> 0x18;
            var_r0 = 0x10;
        } else {
            var_r1 = (s32) (temp_r2_3 << 0x17) >> 0x18;
            var_r0 = -0x10;
        }
        {
            register u32 result_r6 asm("r6");
            func_080ECD98(var_r0, var_r1);
            asm volatile("lsl r0, r0, #16\n\tlsr r6, r0, #16"
                         : "=r"(result_r6) : : "r0");
            temp_r6_4 = result_r6;
        }
        {
            register u32 *late_state_ptr asm("r5") = (u32 *)((u8 *)owner_r8 + 0x8C);
            register u32 late_state asm("r4") = *late_state_ptr;
            temp_r4_3 = late_state;
        }
        var_r1 = (s32)(temp_r4_3 << 0x17) >> 0x18;
        sp10 = (s32)func_080ECD98(-0x20, var_r1);
        *(s16 *)0x03000050 = (0x14 - temp_r4_3) | 0x1000;
        {
        register u32 index asm("r7");
        register u32 mask asm("ip");
        register u16 *loop_base asm("sl");

        index = 0;
        asm volatile("mov r9, r5" : "=r"(var_r9));
        sp14 = temp_r6_4 << 0x10;
        {
            register u32 mask_seed asm("r4") = 0x1F;
            asm volatile("" : "+r"(mask_seed));
            mask = mask_seed;
        }
        {
            register u16 *base_seed asm("r6") = (u16 *)0x020349B4;
            loop_base = base_seed;
        }
low_first_loop:
        {
            register u32 offset asm("r3");
            register u32 color asm("r0");
            register u32 red asm("r4");
            register u32 green asm("r6");
            register u32 blue asm("r5");
            register u32 transition asm("r2");
            register u32 work0 asm("r0");
            register u32 work1 asm("r1");

            offset = index << 1;
            color = *(u16 *)(0x02034934 + offset);
            red = mask;
            red &= color;
            color <<= 16;
            green = color >> 21;
            green &= mask;
            blue = color >> 26;
            blue &= mask;
            work0 = mask;
            work0 -= red;
            transition = *var_r9 - 3;
            work0 *= transition;
            work0 >>= 4;
            work0 = red + work0;
            work0 <<= 24;
            red = work0 >> 24;
            work0 = mask;
            work0 -= green;
            asm volatile("" : "+r"(work0));
            work1 = work0;
            work1 *= transition;
            work1 >>= 4;
            work1 = green + work1;
            work1 <<= 24;
            work0 = mask;
            work0 -= blue;
            work0 *= transition;
            work0 >>= 4;
            work0 = blue + work0;
            work0 <<= 24;
            offset += (u32)loop_base;
            work1 >>= 19;
            red |= work1;
            work0 >>= 14;
            red |= work0;
            *(u16 *)offset = red;
        }
        index = (u8)(index + 1);
        if (index <= 0x3F) {
            goto low_first_loop;
        }

        index = 0;
        {
            register u16 *base_seed asm("r0") = (u16 *)0x02034A34;
            register u32 mask_seed asm("r1") = 0x1F;
            loop_base = base_seed;
            mask = mask_seed;
        }
low_second_loop:
        {
            register u32 offset asm("r3");
            register u32 color asm("r0");
            register u32 red asm("r4");
            register u32 green asm("r6");
            register u32 blue asm("r5");
            register u32 transition asm("r2");
            register u32 work0 asm("r0");
            register u32 work1 asm("r1");

            offset = index << 1;
            color = *(u16 *)(offset + (u32)loop_base);
            red = mask;
            red &= color;
            color <<= 16;
            green = color >> 21;
            green &= mask;
            blue = color >> 26;
            blue &= mask;
            work0 = mask;
            work0 -= red;
            transition = *var_r9 - 3;
            work0 *= transition;
            work0 >>= 4;
            work0 = red + work0;
            work0 <<= 24;
            red = work0 >> 24;
            work0 = mask;
            work0 -= green;
            asm volatile("" : "+r"(work0));
            work1 = work0;
            work1 *= transition;
            work1 >>= 4;
            work1 = green + work1;
            work1 <<= 24;
            work0 = mask;
            work0 -= blue;
            work0 *= transition;
            work0 >>= 4;
            work0 = blue + work0;
            work0 <<= 24;
            {
                register u32 output_base asm("r2") = 0x02034A94;
                offset += output_base;
            }
            work1 >>= 19;
            red |= work1;
            work0 >>= 14;
            red |= work0;
            *(u16 *)offset = red;
        }
        index = (u8)(index + 1);
        if (index <= 0x2F) {
            goto low_second_loop;
        }
        }
        {
            register u32 palette_dest asm("r1") = 0x05000000;
            asm volatile("" : "+r"(palette_dest));
            func_08095208(0x020349B4, palette_dest, 0x80);
        }
        func_08095208(0x02034A94, 0x05000200, 0x60);
    }
    {
        register void *base_first asm("r3") = owner_r8;
        register void *object_first asm("r1") = M2C_FIELD(base_first, void **, 0xC);
        register u32 old_first asm("r0") = M2C_FIELD(object_first, u16 *, 4);
        register s32 saved_y asm("r4") = sp14;
        register s32 delta_y asm("r3") = saved_y >> 0x10;
        M2C_FIELD(object_first, u16 *, 4) = (u16)(delta_y + old_first);
        {
            register void *base asm("r6") = owner_r8;
            register void *object asm("r2") = M2C_FIELD(base, void **, 0xC);
            register u32 old_value asm("r0") = M2C_FIELD(object, u16 *, 6);
            register s32 saved_x asm("r4") = sp10;
            register s32 delta_x asm("r1") = (s16)saved_x;
            M2C_FIELD(object, u16 *, 6) = (u16)(delta_x + old_value);
            object = *(void * volatile *)((u8 *)base + 0x10);
            old_value = M2C_FIELD(object, u16 *, 4);
            delta_y += old_value;
            M2C_FIELD(object, u16 *, 4) = (u16)delta_y;
            object = *(void * volatile *)((u8 *)base + 0x10);
            old_value = M2C_FIELD(object, u16 *, 6);
            delta_x += old_value;
            M2C_FIELD(object, u16 *, 6) = (u16)delta_x;
        }
    }
    {
        register s32 *phase asm("r6") = var_r9;
        *phase += 1;
    }
    goto return_c;

high_state:
    {
    register u32 high_state_value asm("r6");
    asm volatile("" : "=r"(high_state_value));
    if (high_state_value > 0x33U) {
        goto cleanup;
    }
    if (high_state_value == 0x14) {
        register void *base_r1 asm("r1") = owner_r8;
        register void *base_r2 asm("r2");
        func_08094554(M2C_FIELD(base_r1, void **, 0xC));
        base_r2 = owner_r8;
        func_08094554(M2C_FIELD(base_r2, void **, 0x10));
        func_080D218C();
    }
    {
    u32 index;
    register u32 *phase asm("r9");
    register u32 mask asm("ip");
    register u16 *loop_base asm("sl");

    index = 0;
    asm volatile("mov r9, r5" : "=r"(phase));
    {
        register u32 base_seed asm("r3") = 0x020349B4;
        asm volatile("" : "+r"(base_seed));
        base_seed -= 0x80;
        loop_base = (u16 *)base_seed;
    }
    {
        register u32 mask_seed asm("r4") = 0x1F;
        asm volatile("" : "+r"(mask_seed));
        mask = mask_seed;
    }
    {
        register u16 *base_seed asm("r6") = (u16 *)0x020349B4;
        asm volatile("" : "+r"(base_seed));
        owner_r8 = base_seed;
    }
high_first_loop:
    {
        register u32 offset asm("r3");
        register u32 color asm("r0");
        register u32 red asm("r4");
        register u32 green asm("r6");
        register u32 blue asm("r5");
        register u32 transition asm("r2");
        register u32 work0 asm("r0");
        register u32 work1 asm("r1");
        register u32 difference asm("r1");
        register u32 input_base asm("r1");
        register u32 mask_view asm("r2");

        offset = index << 1;
        input_base = (u32)loop_base;
        asm volatile("" : "+r"(input_base));
        color = offset + input_base;
        color = *(u16 *)color;
        red = mask;
        red &= color;
        color <<= 16;
        green = color >> 21;
        mask_view = mask;
        asm volatile("" : "+r"(mask_view));
        green &= mask_view;
        blue = color >> 26;
        blue &= mask_view;
        difference = mask_view;
        difference -= red;
        asm volatile("" : "+r"(difference));
        transition = (u32)phase;
        work0 = *(u32 *)transition;
        transition = 0x33 - work0;
        work0 = difference;
        work0 *= transition;
        work0 >>= 5;
        work0 = red + work0;
        work0 <<= 24;
        red = work0 >> 24;
        work0 = mask;
        work0 -= green;
        asm volatile("" : "+r"(work0));
        work1 = work0;
        work1 *= transition;
        work1 >>= 5;
        work1 = green + work1;
        work1 <<= 24;
        work0 = mask;
        work0 -= blue;
        work0 *= transition;
        work0 >>= 5;
        work0 = blue + work0;
        work0 <<= 24;
        offset += (u32)owner_r8;
        work1 >>= 19;
        red |= work1;
        work0 >>= 14;
        red |= work0;
        *(u16 *)offset = red;
    }
    index = (u8)(index + 1);
    if (index <= 0x3F) {
        goto high_first_loop;
    }

    index = 0;
    {
        register u16 *base_seed asm("r0") = (u16 *)0x02034A34;
        register u32 mask_seed asm("r1") = 0x1F;
        register u32 output_seed asm("r2") = 0x60;
        owner_r8 = base_seed;
        mask = mask_seed;
        output_seed += (u32)owner_r8;
        loop_base = (u16 *)output_seed;
    }
high_second_loop:
    {
        register u32 offset asm("r3");
        register u32 color asm("r0");
        register u32 red asm("r4");
        register u32 green asm("r6");
        register u32 blue asm("r5");
        register u32 transition asm("r2");
        register u32 work0 asm("r0");
        register u32 work1 asm("r1");
        register u32 difference asm("r1");

        offset = index << 1;
        {
            register u32 input_base asm("r4") = (u32)owner_r8;
            register u32 address asm("r0");
            asm volatile("" : "+r"(input_base));
            address = offset + input_base;
            asm volatile("" : "+r"(address));
            color = *(u16 *)address;
        }
        red = mask;
        red &= color;
        color <<= 16;
        green = color >> 21;
        green &= mask;
        blue = color >> 26;
        blue &= mask;
        difference = mask;
        difference -= red;
        asm volatile("" : "+r"(difference));
        transition = (u32)phase;
        work0 = *(u32 *)transition;
        transition = 0x33 - work0;
        work0 = difference;
        work0 *= transition;
        work0 >>= 5;
        work0 = red + work0;
        work0 <<= 24;
        red = work0 >> 24;
        work0 = mask;
        work0 -= green;
        asm volatile("" : "+r"(work0));
        work1 = work0;
        work1 *= transition;
        work1 >>= 5;
        work1 = green + work1;
        work1 <<= 24;
        work0 = mask;
        work0 -= blue;
        work0 *= transition;
        work0 >>= 5;
        work0 = blue + work0;
        work0 <<= 24;
        offset += (u32)loop_base;
        work1 >>= 19;
        red |= work1;
        work0 >>= 14;
        red |= work0;
        *(u16 *)offset = red;
    }
    index = (u8)(index + 1);
    if (index <= 0x2F) {
        goto high_second_loop;
    }
    {
        register u32 palette_dest asm("r1") = 0x05000000;
        asm volatile("" : "+r"(palette_dest));
        func_08095208(0x020349B4, palette_dest, 0x80);
    }
    func_08095208(0x02034A94, 0x05000200, 0x60);
    {
        register u32 *phase_update asm("r1") = phase;
        *phase_update += 1;
    }
    }
    goto return_c;
    }
cleanup:
    func_08095114(owner_r8);
return_c:
    asm volatile(".Lsub_080DC584_return:");
}
