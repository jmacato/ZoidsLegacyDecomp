#include "m2c_prelude.h"

struct ConfigA8800 {
    s32 x;
    s32 y;
    s32 scale;
    s16 width;
    s16 unk0E;
    s16 unk10;
    u8 pad12[2];
    s32 center_x;
    s32 center_y;
    s32 size;
    u8 pad20[0x40];
    s32 flags;
};

extern struct ConfigA8800 D_030033C4;
extern volatile u16 D_0300004E;
extern volatile u16 D_03000050;
extern s32 *D_02032E8C[];
extern u8 D_02032EEC[];

M2C_UNK func_08092D8C(s32, M2C_UNK);                /* extern */
M2C_UNK func_08092E0C(s32);                         /* extern */
M2C_UNK func_08092E84(s32);                         /* extern */
s32 *func_08094374(M2C_UNK, s32, u16, s16, s32, s32, s32, s32, s32); /* extern */
asm(".set func_08094374_4, func_08094374");
extern s32 *func_08094374_4(s32, s32, s32, s32);
s32 *func_08094484(M2C_UNK, M2C_UNK, s32, s32, s32, s32, s32, s32, s32); /* extern */
asm(".set func_08094484_4, func_08094484");
extern s32 *func_08094484_4(s32, s32, s32, s32);
M2C_UNK func_08094554(s32 *);                       /* extern */
M2C_UNK func_08094564(s32 *);                       /* extern */
M2C_UNK func_08095208(M2C_UNK, M2C_UNK, s32);       /* extern */
M2C_UNK func_08096308(s32, s32);                    /* extern */
s32 func_0809669C();                                /* extern */
M2C_UNK func_08098BB4(M2C_UNK);                     /* extern */
M2C_UNK func_0809A4CC(s32, s32, s32, s32);          /* extern */
M2C_UNK func_0809A9C8(s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_0809AA64(s32, s32, s32, s32);          /* extern */
M2C_UNK func_080ECD28(M2C_UNK, s32, s32);           /* extern */
s32 func_080ECD5C(s32);                             /* extern */
M2C_UNK func_080ED17C(s32);                         /* extern */

void sub_080A8800(void) {
    s32 *frame[32];
    s32 *sp94;
    s32 sp98;
    s32 sp9C;
    u32 spA0;
    s32 spA4;
    s16 temp_r1;
    s16 temp_r3_3;
    s16 temp_r4;
    s32 temp_r4_2;
    s32 var_r0;
    s32 **var_r0_4;
    s32 **var_r1;
    s32 **var_r4_3;
    register s32 **var_r5 asm("r5");
    s32 *temp_r0;
    s32 *temp_r0_10;
    s32 *temp_r0_4;
    s32 *temp_r0_5;
    s32 *temp_r0_7;
    s32 *rng;
    s32 *temp_r1_2;
    s32 *temp_r1_6;
    s32 *temp_r2_2;
    s32 temp_r0_11;
    register s32 temp_r0_6 asm("r0");
    s32 temp_r1_3;
    s32 temp_r1_4;
    s32 temp_r1_5;
    s32 temp_r2;
    s32 temp_r2_3;
    register s32 temp_r3 asm("r3");
    s32 temp_r3_2;
    register s32 temp_r5 asm("r5");
    register s32 temp_r5_2 asm("r5");
    s32 temp_r7;
    s32 var_r0_2;
    s32 var_r0_3;
    s32 var_r4_2;
    register s32 var_sl asm("sl");
    u16 temp_r0_2;
    register u16 temp_r0_8 asm("r0");
    u32 temp_r0_3;
    u32 temp_r0_9;
    register u32 var_r6 asm("r6");
    register u32 var_r6_10 asm("r6");
    register u32 var_r6_2 asm("r6");
    register u32 var_r6_3 asm("r6");
    register u32 var_r6_4 asm("r6");
    register u32 var_r6_5 asm("r6");
    register u32 var_r6_6 asm("r6");
    register u32 var_r6_7 asm("r6");
    u32 var_r6_8;
    register u32 var_r6_9 asm("r6");
    register u32 var_r8 asm("r8");
    register u32 var_r8_2 asm("r8");
    register u32 var_r8_3 asm("r8");
    register void *var_ip asm("ip");
    register u32 palette_next_outer_2 asm("r9");
    register u32 tail_next asm("r9");
    register u32 palette_max_2 asm("r4");
    register void *var_r4 asm("r4");
    register void *palette_base asm("sl");
    register u32 palette_next_outer asm("r9");
    register s32 zero_r4 asm("r4");
    register u32 zero_r5 asm("r5");

    {
        register s32 *mode asm("r1") = (s32 *)0x02021690;
        asm volatile("" : "+r"(mode));
        *mode = 9;
    }
    {
        register s32 *color asm("r1") = (s32 *)0x02030558;
        register s32 value asm("r0") = 0xFF10;
        asm volatile("" : "+r"(color), "+r"(value));
        *color = value;
    }
    {
        register s8 *color_mode asm("r0") = (s8 *)0x0203055C;
        register struct ConfigA8800 *config asm("r1");

        zero_r4 = 0;
        asm volatile("" : "+r"(color_mode), "+r"(zero_r4));
        color_mode[1] = zero_r4;
        config = &D_030033C4;
        asm volatile("" : "+r"(config));
        config->x = zero_r4;
        config->y = zero_r4;
        config->scale = 0x10000;
        zero_r5 = 0;
        config->width = 0x20;
        asm volatile(
            "strh r4, [r1, #16]\n\t"
            "strh r4, [r1, #14]"
            : : "r"(zero_r4), "r"(config) : "memory");
        config->center_x = 0x78;
        config->center_y = 0x58;
        config->size = 0x80;
        config->flags = 0x20000;
    }
    func_080ED17C(1);
    func_0809A4CC(0x91, 0, 0, 0);
    temp_r0 = func_08094484(0x0821024C, 0x08210258, 0, 0,
        zero_r4, zero_r4, zero_r4, 0x82C8, 0x080BAE19);
    D_02032E8C[0] = temp_r0;
    M2C_FIELD(temp_r0, s32 *, 0x28) = zero_r4;
    M2C_FIELD(temp_r0, s32 *, 0x2C) = zero_r4;
    M2C_FIELD(temp_r0, s32 *, 0x30) = zero_r4;
    D_02032EEC[0] = zero_r5;
    func_0809AA64(0x087AF9D4, 7, 0x80, 2);
    func_0809AA64(0x087AF9D4, 4, 0x100, 4);
    func_08096308(1, 0x10);
    goto test_ready_1;
wait_ready_1:
    func_080ED17C(1);
test_ready_1:
    if ((func_0809669C() << 0x18) == 0) {
        goto wait_ready_1;
    }
    D_0300004E = 0x740;
    D_03000050 = 0x810;
    {
        register s32 palette_target asm("r0") = 0x05000200;
        var_r4 = (void *)0x02002880;
        asm volatile("" : "+r"(palette_target), "+r"(var_r4));
        func_080ECD28(palette_target, var_r4, 8);
    }
    zero_r5 = 0;
    var_r8 = zero_r5;
    palette_base = var_r4;
    do {
        var_r6 = 0;
        palette_next_outer = var_r8 + 1;
        var_r4 = palette_base;
loop_6:
        {
        u32 green_blend_1;
        u32 packed_1;
        register u32 red_blend_1 asm("r0");
        register u32 red_source_1 asm("r2");

        red_blend_1 = M2C_FIELD(var_r4, u16 *, 0);
        asm volatile("add %0, r7, #0" : "=r"(red_source_1));
        red_source_1 &= red_blend_1;
        temp_r2 = red_source_1;
        red_blend_1 <<= 0x10;
        temp_r5 = (red_blend_1 >> 0x15) & 0x1F;
        temp_r3 = (red_blend_1 >> 0x1A) & 0x1F;
        red_blend_1 = (0x1F - temp_r2) * var_r8;
        red_blend_1 >>= 5;
        red_blend_1 = temp_r2 + red_blend_1;
        red_blend_1 <<= 0x18;
        temp_r2 = red_blend_1 >> 0x18;
        red_blend_1 = 0x1F - temp_r5;
        asm volatile("" : "+r"(red_blend_1));
        green_blend_1 = red_blend_1;
        green_blend_1 *= var_r8;
        green_blend_1 >>= 5;
        asm volatile("add %0, %1, %0"
                     : "+r"(green_blend_1)
                     : "r"(temp_r5));
        green_blend_1 <<= 0x18;
        red_blend_1 = 0x1F - temp_r3;
        red_blend_1 *= var_r8;
        red_blend_1 >>= 5;
        red_blend_1 = temp_r3 + red_blend_1;
        red_blend_1 <<= 0x18;
        packed_1 = temp_r2;
        packed_1 |= green_blend_1 >> 0x13;
        packed_1 |= red_blend_1 >> 0xE;
        M2C_FIELD(var_r4, u16 *, 0x20) = packed_1;
        }
        var_r4 += 2;
        var_r6 += 1;
        if (var_r6 <= 0xFU) {
            goto loop_6;
        }
        func_08095208(0x020028A0, 0x05000200, 0x20);
        var_r8 = palette_next_outer;
        func_080ED17C(1);
    } while (var_r8 <= 0x20U);
    temp_r0_4 = func_08094374(0x087AFA94, 7, 3U, 0, 0, 0x80, 2, 0x87E0, 0x080BADD5);
    frame[0] = temp_r0_4;
    M2C_FIELD(temp_r0_4, s32 *, 0x28) = 0xFFFF8000;
    M2C_FIELD(temp_r0_4, s32 *, 0x2C) = 0;
    M2C_FIELD(temp_r0_4, s32 *, 0x30) = 0;
    sp98 = 0x2000;
    sp9C = 0xE000;
    spA0 = 0x2000;
    spA4 = 0;
    var_r8_2 = 0;
    func_08092E84(0x6B);
loop_9:
    switch (spA4) {                                 /* irregular */
    case 0:
        if (M2C_FIELD(frame[0], s32 *, 0) & 4) {
            func_08094564(frame[0]);
        }
        M2C_FIELD(frame[0], s32 *, 0x28) = (s32) (M2C_FIELD(frame[0], s32 *, 0x28) + (s16) sp98);
        temp_r1 = (s16) sp9C;
        if ((s32) temp_r1 < (s32)0xFFFFF000) {
            sp9C = (s32) (u16) (temp_r1 + 0x40);
        } else {
            func_0809A4CC(0x87, 6, 0x40, 1);
            {
                register s32 constructor_sp0 asm("r2");
                register s32 constructor_arg9 asm("r0");

                asm volatile("ldr %0, [sp, #164]"
                             : "=r"(constructor_sp0)
                             : "g"(spA4)
                             : "memory");
                asm volatile(
                    "str %0, [sp, #0]\n\t"
                    "mov r0, #64\n\t"
                    "str r0, [sp, #4]\n\t"
                    "mov r0, #1\n\t"
                    "str r0, [sp, #8]\n\t"
                    "mov r0, #178\n\t"
                    "lsl r0, r0, #2\n\t"
                    "str r0, [sp, #12]"
                    : "+r"(constructor_sp0)
                    :
                    : "r0", "memory");
                constructor_arg9 = 0x080BADD5;
                asm volatile("str %0, [sp, #16]"
                             : "+r"(constructor_arg9)
                             :
                             : "memory");
                temp_r0_5 = func_08094484_4(
                    ({ register s32 arg asm("r0") = 0x0821024C;
                       asm volatile("" : "+r"(arg)); arg; }),
                    ({ register s32 arg asm("r1") = 0x08210258;
                       asm volatile("" : "+r"(arg)); arg; }),
                    0, 0);
            }
            D_02032E8C[1] = temp_r0_5;
            M2C_FIELD(temp_r0_5, s32 *, 0x28) = (s32) (M2C_FIELD(frame[0], s32 *, 0x28) + 0x6000);
            M2C_FIELD(temp_r0_5, s32 *, 0x2C) = (s32) M2C_FIELD(frame[0], s32 *, 0x2C);
            M2C_FIELD(temp_r0_5, s32 *, 0x30) = (s32) M2C_FIELD(frame[0], s32 *, 0x30);
            D_02032EEC[1] = (u8) spA4;
            func_08094554(frame[0]);
            spA4 = 1;
        }
        {
        register s32 *field_child asm("r1") = frame[0];

        asm volatile("" : "+r"(field_child));
        var_r0 = (s16) sp9C;
        if ((s32) var_r0 < 0) {
            var_r0 += 0xFF;
        }
        M2C_FIELD(field_child, s16 *, 0xA) = (s16) (var_r0 >> 8);
        }
        break;
    case 1:
        temp_r1_2 = D_02032E8C[1];
        temp_r4 = (s16) sp98;
        M2C_FIELD(temp_r1_2, s32 *, 0x28) = (s32) (M2C_FIELD(temp_r1_2, s32 *, 0x28) + temp_r4);
        temp_r0_6 = 0xFF & temp_r4;
        if (temp_r0_6 == 0) {
            {
                register s32 constructor_stack asm("r0") = temp_r0_6;

                asm volatile(
                    "str %0, [sp, #0]\n\t"
                    "mov %0, #128\n\t"
                    "lsl %0, %0, #1\n\t"
                    "str %0, [sp, #4]\n\t"
                    "mov %0, #4\n\t"
                    "str %0, [sp, #8]"
                    : "+r"(constructor_stack)
                    :
                    : "memory");
                constructor_stack = 0x85C0;
                asm volatile("str %0, [sp, #12]"
                             : "+r"(constructor_stack)
                             :
                             : "memory");
                constructor_stack = 0x080BADD5;
                asm volatile("str %0, [sp, #16]"
                             : "+r"(constructor_stack)
                             :
                             : "memory");
                temp_r0_7 = func_08094374_4(
                    ({ register s32 arg asm("r0") = 0x087AFA94;
                       asm volatile("" : "+r"(arg)); arg; }),
                    ({ register s32 arg asm("r1") = 4;
                       asm volatile("" : "+r"(arg)); arg; }),
                    0, 0);
            }
            frame[1] = temp_r0_7;
            temp_r2_2 = D_02032E8C[1];
            M2C_FIELD(temp_r0_7, s32 *, 0x28) = (s32) (M2C_FIELD(temp_r2_2, s32 *, 0x28) + 0x1000);
            M2C_FIELD(temp_r0_7, s32 *, 0x2C) = (s32) M2C_FIELD(temp_r2_2, s32 *, 0x2C);
            M2C_FIELD(temp_r0_7, s32 *, 0x30) = (s32) M2C_FIELD(temp_r2_2, s32 *, 0x30);
            func_08092E84(0x64);
        }
        sp98 = (s32) (u16) (temp_r4 - 0x80);
        spA0 = (u32) ((spA0 << 0x10) + 0xFF800000) >> 0x10;
        break;
    }
    D_030033C4.x = (s32) (D_030033C4.x + (s16) spA0);
    temp_r1_3 = D_030033C4.scale;
    if (temp_r1_3 > 0x8000) {
        D_030033C4.scale = (s32) (temp_r1_3 + 0xFFFFFE00);
    }
    if (var_r8_2 <= 0x10U) {
        var_r6_2 = 0;
        palette_next_outer_2 = var_r8_2 + 1;
        palette_max_2 = 0x1F;
        temp_r7 = 0x10 - var_r8_2;
        {
            register u8 *palette_input_2 asm("r0");
            palette_input_2 = (u8 *)0x020028A0;
            asm volatile("" : "+r"(palette_input_2));
            palette_input_2 -= 0x20;
            var_ip = palette_input_2;
        }
        do {
            asm volatile(
                ".syntax unified\n\t"
                "mov r1, %0\n\t"
                "ldrh r0, [r1]\n\t"
                "adds r2, %1, #0\n\t"
                "ands r2, r0\n\t"
                "lsls r0, r0, #16\n\t"
                "lsrs r5, r0, #21\n\t"
                "ands r5, %1\n\t"
                "lsrs r3, r0, #26\n\t"
                "ands r3, %1\n\t"
                "subs r0, %1, r2\n\t"
                "muls r0, %2\n\t"
                "lsrs r0, r0, #4\n\t"
                "adds r0, r2, r0\n\t"
                "lsls r0, r0, #24\n\t"
                "lsrs r2, r0, #24\n\t"
                "subs r0, %1, r5\n\t"
                "adds r1, r0, #0\n\t"
                "muls r1, %2\n\t"
                "lsrs r1, r1, #4\n\t"
                "adds r1, r5, r1\n\t"
                "lsls r1, r1, #24\n\t"
                "subs r0, %1, r3\n\t"
                "muls r0, %2\n\t"
                "lsrs r0, r0, #4\n\t"
                "adds r0, r3, r0\n\t"
                "lsls r0, r0, #24\n\t"
                "lsrs r1, r1, #19\n\t"
                "orrs r2, r1\n\t"
                "lsrs r0, r0, #14\n\t"
                "orrs r2, r0\n\t"
                "mov r3, %0\n\t"
                "strh r2, [r3, #32]\n\t"
                "movs r5, #2\n\t"
                "add %0, r5\n\t"
                ".syntax divided"
                : "+r"(var_ip)
                : "r"(palette_max_2), "r"(temp_r7)
                : "r0", "r1", "r2", "r3", "r5", "cc", "memory");
            var_r6_2 += 1;
        } while (var_r6_2 <= 0xFU);
        func_08095208(0x020028A0, 0x05000200, 0x20);
        var_r8_2 = palette_next_outer_2;
    }
    func_080ED17C(1);
    temp_r3_3 = (s16) spA0;
    if (temp_r3_3 != 0) {
        goto loop_9;
    }
    sp94 = func_08094484(0x08359850, 0x0835985C, 0, 8, 0x68, 0x3C2, 0xD, 8, (s32) temp_r3_3);
    func_08098BB4(0x08017BD3);
    func_0809A9C8(0x36, 1, 0, 0x3C2, 0xD, 0x02002880);
    func_08098BB4(0x08018A3A);
    {
        register s32 *flag_store asm("r2");
        s32 flag_value = *sp94 | 0x20000;

        asm volatile("ldr %0, [sp, #148]"
                     : "=r"(flag_store)
                     : "g"(sp94)
                     : "memory");
        *flag_store = flag_value;
    }
    func_08098BB4(0x08017BE6);
    if (D_030033C4.x > 0xFF) {
        do {
            temp_r1_4 = D_030033C4.x;
            var_r0_2 = 0 - temp_r1_4;
            if (var_r0_2 < 0) {
                var_r0_2 += 7;
            }
            D_030033C4.x = (s32) (temp_r1_4 + (var_r0_2 >> 3));
            temp_r1_5 = D_030033C4.scale;
            var_r0_3 = 0x10000 - temp_r1_5;
            if (var_r0_3 < 0) {
                var_r0_3 += 7;
            }
            D_030033C4.scale = (s32) (temp_r1_5 + (var_r0_3 >> 3));
            func_080ED17C(1);
        } while (D_030033C4.x > 0xFF);
    }
    D_030033C4.x = 0;
    D_030033C4.scale = 0x10000;
    var_r6_3 = 0;
    do {
        func_080ED17C(1);
        var_r6_3 += 1;
    } while (var_r6_3 <= 0x1DU);
    func_08092D8C(4, 0x080A876D);
    var_r6_4 = 0;
    do {
        func_080ED17C(1);
        var_r6_4 += 1;
    } while (var_r6_4 <= 0x3BU);
    func_0809AA64(0x087AC9F8, 6, 0x40, 1);
    {
    register s32 *clear_zero asm("r1");

    var_r6_5 = 0;
    clear_zero = 0;
    asm volatile("" : "+r"(clear_zero));
    var_r0_4 = frame;
    do {
        *var_r0_4 = clear_zero;
        var_r0_4 += 1;
        var_r6_5 += 1;
    } while (var_r6_5 <= 0x1FU);
    }
    {
        register u32 outer_zero asm("r3") = 0;
        asm volatile("" : "+r"(outer_zero));
        var_r8_3 = outer_zero;
    }
    var_r4_2 = 0;
    {
        register s32 countdown_seed asm("r5") = 0x12;
        asm volatile("" : "+r"(countdown_seed));
        var_sl = countdown_seed;
    }
loop_46:
    {
    register u32 outer_check asm("r0") = var_r8_3;
    asm volatile("" : "+r"(outer_check));
    if (outer_check == 0xF0) {
        func_08092E0C(4);
        func_08094554(*(s32 **)0x02031C94);
        func_08096308(4, 0x3C);
    }
    }
    var_r6_6 = 0;
    {
        register u32 tail_seed asm("r1") = 1;
        asm volatile("" : "+r"(tail_seed));
        tail_seed += var_r8_3;
        tail_next = tail_seed;
    }
    {
    register s32 cleanup_mask asm("r2") = 1;

    asm volatile("" : "+r"(cleanup_mask));
    var_r1 = frame;
    do {
        temp_r0_10 = *var_r1;
        if (temp_r0_10 != 0) {
            temp_r0_11 = *temp_r0_10 & cleanup_mask;
            if (temp_r0_11 == 0) {
                *var_r1 = (s32 *) temp_r0_11;
            }
        }
        var_r1 += 1;
        var_r6_6 += 1;
    } while (var_r6_6 <= 0x1FU);
    }
    if ((var_r4_2 == var_sl) || (var_sl == 0)) {
        var_r6_7 = 0;
        rng = (s32 *)0x03000010;
        var_r5 = frame;
loop_56:
        if (*var_r5 == 0) {
            if (var_r8_3 <= 0x3BU) {
                var_r6_8 = 2;
            } else {
                var_r6_8 = (u32) (func_080ECD5C(*rng) * 3) >> 0xF;
            }
            temp_r4_2 = (s16) (((u32) (func_080ECD5C(*rng) * 0x41) >> 0xF) + 0x58);
            {
                register s32 spawn_y asm("r0") =
                    (s32) (s16) (0x58 - ((u32) (func_080ECD5C(*rng) * 0x41) >> 0xF));
                register u32 spawn_subtype asm("r2") = (u16) var_r6_8;

                asm volatile("" : "+r"(spawn_subtype));
                asm volatile(
                    "str %0, [sp, #0]\n\t"
                    "mov %0, #64\n\t"
                    "str %0, [sp, #4]\n\t"
                    "mov %0, #1\n\t"
                    "str %0, [sp, #8]\n\t"
                    "mov %0, #208\n\t"
                    "lsl %0, %0, #2\n\t"
                    "str %0, [sp, #12]\n\t"
                    "mov %0, #0\n\t"
                    "str %0, [sp, #16]"
                    : "+r"(spawn_y)
                    :
                    : "memory");
                *var_r5 = func_08094374_4(0x087ACDD8, 6,
                    spawn_subtype, temp_r4_2);
            }
            func_08092E84(0x5B);
        } else {
            var_r5 += 1;
            var_r6_7 += 1;
            if (var_r6_7 <= 0x1FU) {
                goto loop_56;
            }
        }
        var_r4_2 = 0;
        if (var_sl != 0) {
            var_sl -= 1;
        }
    } else {
        var_r4_2 += 1;
    }
    var_r8_3 = tail_next;
    func_080ED17C(1);
    if (var_r8_3 <= 0x12BU) {
        goto loop_46;
    }
    {
    register s32 active_mask asm("r5");

    var_r6_9 = 0;
    var_r4_3 = frame;
    active_mask = 1;
    asm volatile("" : "+r"(active_mask));
    do {
        temp_r1_6 = *var_r4_3;
        if (*temp_r1_6 & active_mask) {
            func_08094554(temp_r1_6);
        }
        var_r4_3 += 1;
        var_r6_9 += 1;
    } while (var_r6_9 <= 0x1FU);
    }
    func_08092E84(0x81);
    var_r6_10 = 0;
    do {
        func_080ED17C(1);
        var_r6_10 += 1;
    } while (var_r6_10 <= 0x1DU);
    func_08094554(D_02032E8C[0]);
    func_08096308(3, 0x1E);
    goto test_ready_2;
wait_ready_2:
    func_080ED17C(1);
test_ready_2:
    if ((func_0809669C() << 0x18) == 0) {
        goto wait_ready_2;
    }
    {
        register s32 *flag_store_2 asm("r2");
        s32 flag_value_2 = *sp94 & 0xFFFDFFFF;

        asm volatile("ldr %0, [sp, #148]"
                     : "=r"(flag_store_2)
                     : "g"(sp94)
                     : "memory");
        *flag_store_2 = flag_value_2;
    }
    func_08098BB4(0x08017BD3);
    func_0809A9C8(1, 5, 0, 0x3C2, 0xD, 0x02002880);
    func_08098BB4(0x08018A79);
    func_0809A9C8(3, 5, 0, 0x3C2, 0xD, 0x02002880);
    func_08098BB4(0x08018AD7);
    func_08096308(2, 0x10);
    goto test_ready_3;
wait_ready_3:
    func_080ED17C(1);
test_ready_3:
    if ((func_0809669C() << 0x18) == 0) {
        goto wait_ready_3;
    }
    *(s32 *)0x02021690 = -1;
    func_080ED17C(1);
}
