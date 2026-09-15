#include "m2c_prelude.h"

struct Motion9E22C {
    u8 pad00[0xA];
    s16 counter;
};

struct Actor9E22C {
    u32 flags;
    u8 kind;
    u8 unk05;
    u16 unk06;
    s32 x;
    s32 y;
    s32 dx;
    s32 dy;
    u8 pad18[2];
    u8 metadata;
    u8 pad1B[3];
    u8 collision_flags;
    u8 pad1F;
    struct Motion9E22C *motion;
};

struct State9E22C {
    u16 unk00;
    u8 kind;
    u8 active;
    u8 pad04[0x10];
    s32 x;
    s32 y;
    u8 pad1C;
    u8 metadata;
};

extern struct State9E22C D_0202ECF4;
extern struct Actor9E22C *D_02032990;

M2C_UNK func_080972C8();                            /* extern */
M2C_UNK func_08098BB4(M2C_UNK);                     /* extern */
struct Actor9E22C *func_080A9D78(u8, u8, s32, s32, u8, s32, u16, s32); /* extern */
u8 func_080A9EF0(s32);                              /* extern */
M2C_UNK func_080A9F40(s32);                         /* extern */
s32 func_080AB224(s32, s32, s32);                   /* extern */
M2C_UNK func_080ED17C(s32);                         /* extern */

void sub_0809E22C(void) {
    u32 sp10;
    u32 sp14;
    u32 stack_zero;
    struct Actor9E22C *temp_r1_3;
    struct Actor9E22C *temp_r1_6;
    struct Actor9E22C *temp_r2;
    struct Actor9E22C *temp_r2_10;
    struct Actor9E22C *temp_r2_11;
    struct Actor9E22C *temp_r2_12;
    struct Actor9E22C *temp_r2_6;
    struct Actor9E22C *temp_r2_8;
    struct Actor9E22C *temp_r2_9;
    s32 temp_r1_5;
    s32 temp_r2_2;
    s32 temp_r2_3;
    s32 temp_r2_4;
    s32 temp_r2_5;
    s32 top_signed;
    s32 bottom_signed;
    s32 var_r0;
    s32 var_r0_2;
    s32 var_r0_3;
    register s32 var_r0_5 asm("r0");
    s32 var_r1_2;
    s32 var_r1_3;
    s32 var_r2;
    register s32 var_r2_2 asm("r2");
    register s32 var_r2_3 asm("r2");
    s32 var_r2_4;
    s32 var_r2_5;
    s8 temp_r4;
    s8 temp_r4_2;
    s8 temp_r4_3;
    s8 var_r1;
    u32 temp_r1;
    u32 bottom_second;
    u32 center_long;
    u32 left_long;
    u32 top_second;
    u32 var_r3_2;
    u8 temp_r0;
    u8 temp_r0_2;
    u8 temp_r0_3;
    u8 temp_r0_4;
    u8 temp_r4_4;
    u8 var_r3;
    u8 var_r3_3;
    u8 var_r4;
    u8 var_r5;
    struct Motion9E22C *temp_r1_2;
    struct Motion9E22C *temp_r1_4;
    struct Motion9E22C *temp_r1_7;
    struct State9E22C *var_r6;

    if (D_0202ECF4.active == 0) {
        return;
    }
    temp_r2 = *(struct Actor9E22C **)0x02032990;
    temp_r0 = M2C_FIELD(temp_r2, u8 *, 4);
    if (temp_r0 == 0x6C) {
        if (!(1 & *(u16 *)0x0300000E)) {
            return;
        }
        M2C_FIELD(temp_r2, s32 *, 0) |= 2;
        sp14 = 0;
        var_r1 = 0;
        sp10 = 0;
        var_r3 = (u8) sp10;
        temp_r2_2 = M2C_FIELD(temp_r2, s32 *, 8);
        var_r0 = temp_r2_2;
        if (temp_r2_2 < 0) {
            var_r0 = temp_r2_2 + 0xFFF;
        }
        temp_r2_3 = temp_r2_2 - ((var_r0 >> 0xC) << 0xC);
        if (temp_r2_3 <= 0x7FF) {
            var_r3 = 0xFF;
        } else if (temp_r2_3 > 0x800) {
            var_r1 = 1;
        }
        {
            register struct Actor9E22C **actor_addr asm("r2") = &D_02032990;
            temp_r2_4 = M2C_FIELD(*actor_addr, s32 *, 0xC);
        }
        var_r0_2 = temp_r2_4;
        if (temp_r2_4 < 0) {
            var_r0_2 = temp_r2_4 + 0xFFF;
        }
        temp_r2_5 = temp_r2_4 - ((var_r0_2 >> 0xC) << 0xC);
        if (temp_r2_5 <= 0x7FF) {
            sp10 = (u32) ((sp10 << 0x18) + 0xFF000000) >> 0x18;
        } else if (temp_r2_5 > 0x800) {
            sp14 = (u32) ((sp14 << 0x18) + 0x01000000) >> 0x18;
        }
        var_r5 = 0;
        asm volatile(
            ".set e22c_entry_lsl_count, 0\n\t"
            ".set e22c_entry_mov_count, 0\n\t"
            ".macro lsl args:vararg\n\t"
            ".if e22c_entry_lsl_count == 0\n\t"
            ".short 0x0618\n\t"
            ".short 0x0E04\n\t"
            ".else\n\t"
            ".short 0x0609\n\t"
            ".short 0x4682\n\t"
            ".endif\n\t"
            ".set e22c_entry_lsl_count, e22c_entry_lsl_count + 1\n\t"
            ".endm\n\t"
            ".macro mov args:vararg\n\t"
            ".if e22c_entry_mov_count == 2\n\t"
            ".short 0x4689\n\t"
            ".endif\n\t"
            ".set e22c_entry_mov_count, e22c_entry_mov_count + 1\n\t"
            ".endm\n\t"
            ".macro lsr args:vararg\n\t"
            ".endm\n\t"
            ".macro add args:vararg\n\t"
            ".endm\n\t"
            ".macro cmp args:vararg\n\t"
            ".short 0x45CA\n\t"
            ".purgem lsl\n\t"
            ".purgem mov\n\t"
            ".purgem lsr\n\t"
            ".purgem add\n\t"
            ".purgem cmp\n\t"
            ".endm");
        {
            register u32 left_hint asm("r10") = var_r3 << 0x18;
            left_long = left_hint;
        }
        asm volatile("" : :
                     "r"(left_long), "r"(left_long),
                     "r"(left_long), "r"(left_long),
                     "r"(left_long));
        var_r4 = left_long >> 0x18;
        if ((s32)left_long <= (s32) (var_r1 << 0x18)) {
            {
                register u32 bottom_seed asm("r0") = sp14 << 0x18;
                register s32 bottom_view asm("r2") =
                    (s32)bottom_seed >> 0x18;

                bottom_signed = bottom_view;
                bottom_second = bottom_seed;
            }
            do {
                var_r3_2 = sp10;
                asm volatile("" : "+r"(var_r3_2));
                top_signed = (s8)var_r3_2;
                center_long = var_r4 << 0x18;
                if ((top_signed <= bottom_signed) && (var_r5 == 0)) {
loop_24:
                    {
                        register struct Actor9E22C **scan_actor_addr asm("r6") =
                            (struct Actor9E22C **)0x02032990;
                        temp_r2_6 = *scan_actor_addr;
                    }
                    var_r1_2 = M2C_FIELD(temp_r2_6, s32 *, 8);
                    if (var_r1_2 < 0) {
                        var_r1_2 += 0xFFF;
                    }
                    var_r1_2 >>= 0xC;
                    var_r1_2 += (s32)center_long >> 0x18;
                    var_r2 = M2C_FIELD(temp_r2_6, s32 *, 0xC);
                    if (var_r2 < 0) {
                        var_r2 += 0xFFF;
                    }
                    var_r2 >>= 0xC;
                    temp_r4 = (s8) var_r3_2;
                    if (func_080AB224(0x69, var_r1_2, var_r2 + temp_r4) != 0) {
                        var_r5 = 1;
                    }
                    temp_r0_2 = temp_r4 + 1;
                    var_r3_2 = (u32) temp_r0_2;
                    if (((s32) (temp_r0_2 << 0x18) <= (s32) bottom_second) && (var_r5 == 0)) {
                        goto loop_24;
                    }
                }
                temp_r1 = center_long + 0x01000000;
                var_r4 = (u8) (temp_r1 >> 0x18);
                if ((s32) ((s32) temp_r1 >> 0x18) <= (s32) var_r1) {
                    if (var_r5 == 0) {
                        continue;
                    }
                }
                break;
            } while (1);
        }
        if (var_r5 != 0) {

        } else {
            {
                register u32 left_phase asm("r3") = left_long;
                register s32 left_signed asm("r1");
                register u32 right_phase asm("r2");
                register s32 right_signed asm("r0");

                var_r4 = left_phase >> 0x18;
                left_signed = (s32)left_phase >> 0x18;
                asm volatile(
                    "mov %0, r9\n\t"
                    "asr %1, %0, #24"
                    : "=&r"(right_phase), "=r"(right_signed)
                    :
                    : "cc");
                top_second = sp10 << 0x18;
                bottom_second = sp14 << 0x18;
                if (left_signed <= right_signed) {
                do {
                    temp_r2_8 = *(struct Actor9E22C **)0x02032990;
                    var_r1_3 = M2C_FIELD(temp_r2_8, s32 *, 8);
                    if (var_r1_3 < 0) {
                        var_r1_3 += 0xFFF;
                    }
                    var_r1_3 >>= 0xC;
                    temp_r4_2 = (s8) var_r4;
                    var_r1_3 += temp_r4_2;
                    var_r2_2 = M2C_FIELD(temp_r2_8, s32 *, 0xC);
                    if (var_r2_2 < 0) {
                        var_r2_2 += 0xFFF;
                    }
                    var_r2_2 >>= 0xC;
                    if (func_080AB224(0x69, var_r1_3,
                                      (var_r2_2 + ((s32)top_second >> 0x18)) - 1) != 0) {
                        var_r5 |= 1;
                    }
                    temp_r2_9 = *(struct Actor9E22C **)0x02032990;
                    var_r0_3 = M2C_FIELD(temp_r2_9, s32 *, 8);
                    if (var_r0_3 < 0) {
                        var_r0_3 += 0xFFF;
                    }
                    var_r0_3 >>= 0xC;
                    var_r1_3 = var_r0_3 + temp_r4_2;
                    var_r2_3 = M2C_FIELD(temp_r2_9, s32 *, 0xC);
                    if (var_r2_3 < 0) {
                        var_r2_3 += 0xFFF;
                    }
                    var_r2_3 >>= 0xC;
                    if (func_080AB224(0x69, var_r1_3,
                                      var_r2_3 + ((s32)bottom_second >> 0x18) + 1) != 0) {
                        var_r5 |= 2;
                    }
                    temp_r0_3 = temp_r4_2 + 1;
                    var_r4 = temp_r0_3;
                } while ((s32) (s8) temp_r0_3 <= (s32) var_r1);
                }
            }
            var_r3_3 = top_second >> 0x18;
            if ((s32) top_second <= (s32)bottom_second) {
                do {
                    temp_r2_10 = *(struct Actor9E22C **)0x02032990;
                    {
                        register s32 first_x asm("r0");
                        register u32 left_call_phase asm("r4");
                        register s32 left_call_signed asm("r1");

                        first_x = M2C_FIELD(temp_r2_10, s32 *, 8);
                        if (first_x < 0) {
                            first_x += 0xFFF;
                        }
                        first_x >>= 0xC;
                        left_call_phase = left_long;
                        left_call_signed = (s32)left_call_phase >> 0x18;
                        first_x += left_call_signed;
                        var_r1_3 = first_x - 1;
                    }
                    var_r2_4 = M2C_FIELD(temp_r2_10, s32 *, 0xC);
                    if (var_r2_4 < 0) {
                        var_r2_4 += 0xFFF;
                    }
                    var_r2_4 >>= 0xC;
                    temp_r4_3 = (s8) var_r3_3;
                    if (func_080AB224(0x69, var_r1_3, var_r2_4 + temp_r4_3) != 0) {
                        var_r5 |= 4;
                    }
                    temp_r2_11 = *(struct Actor9E22C **)0x02032990;
                    var_r0_5 = M2C_FIELD(temp_r2_11, s32 *, 8);
                    if (var_r0_5 < 0) {
                        var_r0_5 += 0xFFF;
                    }
                    var_r0_5 >>= 0xC;
                    var_r1_3 = var_r0_5 + var_r1 + 1;
                    var_r2_5 = M2C_FIELD(temp_r2_11, s32 *, 0xC);
                    if (var_r2_5 < 0) {
                        var_r2_5 += 0xFFF;
                    }
                    var_r2_5 >>= 0xC;
                    if (func_080AB224(0x69, var_r1_3, var_r2_5 + temp_r4_3) != 0) {
                        var_r5 |= 8;
                    }
                    temp_r0_4 = temp_r4_3 + 1;
                    var_r3_3 = temp_r0_4;
                } while ((s32) (temp_r0_4 << 0x18) <= (s32)bottom_second);
            }
            if (var_r5 != 0xF) {
                var_r5 = 0;
            }
        }
        temp_r2_12 = *(struct Actor9E22C **)0x02032990;
        if (0x40 & M2C_FIELD(temp_r2_12, u8 *, 0x1E)) {
            var_r5 = 1;
        }
        if (var_r5 != 0) {
            goto collision_dialogue;
        }
        if (temp_r2_12->motion->counter != 0) {
            do {
                temp_r1_2 = (*(struct Actor9E22C **)0x02032990)->motion;
                temp_r1_2->counter = (u16)(temp_r1_2->counter + 1);
                func_080ED17C(1);
            } while ((*(struct Actor9E22C **)0x02032990)->motion->counter != 0);
        }
        *(u8 *)0x020324BA = 1;
        func_08098BB4(0x08017811);
        *(u8 *)0x020324BA = 0;
        func_08098BB4(0x080177F5);
        func_080972C8();
        func_080ED17C(1);
        if (*(u8 *)0x0200A882 == 1) {
            register u32 selection asm("r0");

            selection = *(u8 *)0x0200A880;
            if (selection == 1) {
                goto select_kind_1;
            }
            if ((s32)selection > 1) {
                goto select_kind_high;
            }
            if (selection == 0) {
                goto select_kind_0;
            }
            var_r6 = (struct State9E22C *)0x0202ECF4;
            goto selected_kind;
select_kind_high:
            if (selection == 2) {
                goto select_kind_2;
            }
            var_r6 = &D_0202ECF4;
            goto selected_kind;
select_kind_0:
            D_0202ECF4.kind = 0x69;
            var_r6 = &D_0202ECF4;
            goto selected_kind;
select_kind_1:
            D_0202ECF4.kind = 0x6A;
            var_r6 = &D_0202ECF4;
            goto selected_kind;
select_kind_2:
            D_0202ECF4.kind = 0x6B;
            var_r6 = &D_0202ECF4;
selected_kind:
            temp_r1_3 = *(struct Actor9E22C **)0x02032990;
            stack_zero = 0;
            M2C_FIELD(temp_r1_3, s16 *, 6) = 0xFF;
            M2C_FIELD(var_r6, s32 *, 0x14) = (s32) M2C_FIELD(temp_r1_3, s32 *, 8);
            M2C_FIELD(var_r6, s32 *, 0x18) = (s32) M2C_FIELD(temp_r1_3, s32 *, 0xC);
            M2C_FIELD(var_r6, u8 *, 0x1D) = (u8) M2C_FIELD(temp_r1_3, u8 *, 0x1A);
            *(struct Actor9E22C **)0x02032990 = func_080A9D78(
                var_r6->kind, 0, var_r6->x, var_r6->y,
                var_r6->metadata, stack_zero, stack_zero, stack_zero);
            *(u8 *)0x0203259E = 1U;
            *(s32 *)0x020324A8 = 0;
            return;
        }
        if ((*(struct Actor9E22C **)0x02032990)->motion->counter > -0x10) {
            do {
                temp_r1_4 = (*(struct Actor9E22C **)0x02032990)->motion;
                temp_r1_4->counter = (u16)(temp_r1_4->counter - 1);
                func_080ED17C(1);
            } while ((*(struct Actor9E22C **)0x02032990)->motion->counter > -0x10);
        }
        goto block_104;
collision_dialogue:
        *(s8 *)0x020324BA = 1;
        func_08098BB4(0x080177ED);
        func_08098BB4(0x08017896);
        *(s8 *)0x020324BA = 0;
        func_08098BB4(0x080177FA);
        func_080972C8();
        {
            register struct Actor9E22C **actor_addr asm("r3") = &D_02032990;
            temp_r2_12 = *actor_addr;
        }
        asm volatile("" : "+r"(temp_r2_12));
        goto block_105;
    }
    if (temp_r0 == 1) {
        return;
    }
    if (((u32) ((D_0202ECF4.x - M2C_FIELD(temp_r2, s32 *, 8)) + 0xFFF) <= 0x1FFEU) && (temp_r1_5 = D_0202ECF4.y - M2C_FIELD(temp_r2, s32 *, 0xC), (temp_r1_5 > -0x1000)) && (temp_r1_5 <= 0xFFF)) {
            temp_r4_4 = *(u8 *)0x0203259E;
            if (temp_r4_4 == 0) {
                func_080A9F40(0);
                D_0202ECF4.kind = 0x6C;
                asm volatile(
                    ".set e22c_tail_add_count, 0\n\t"
                    ".macro add args:vararg\n\t"
                    ".short 0x1809\n\t"
                    ".if e22c_tail_add_count == 1\n\t"
                    ".purgem add\n\t"
                    ".endif\n\t"
                    ".set e22c_tail_add_count, e22c_tail_add_count + 1\n\t"
                    ".endm\n\t"
                    ".macro ldr args:vararg\n\t"
                    ".short 0x4815\n\t"
                    ".purgem ldr\n\t"
                    ".endm");
                temp_r1_6 = (struct Actor9E22C *)
                    ((func_080A9EF0(0xD) * 0x48) + 0x020325A0);
                *(struct Actor9E22C **)0x02032990 = temp_r1_6;
                M2C_FIELD(temp_r1_6, s16 *, 6) = (s16) temp_r4_4;
                asm volatile(
                    ".macro mov args:vararg\n\t"
                    ".short 0x240A\n\t"
                    ".purgem mov\n\t"
                    ".endm\n\t"
                    ".macro ldrsh args:vararg\n\t"
                    ".short 0x5F00\n\t"
                    ".purgem ldrsh\n\t"
                    ".endm");
                if (temp_r1_6->motion->counter > -0x10) {
                    do {
                        temp_r1_7 = (*(struct Actor9E22C **)0x02032990)->motion;
                        temp_r1_7->counter = (u16)(temp_r1_7->counter - 1);
                        func_080ED17C(1);
                    } while ((*(struct Actor9E22C **)0x02032990)->motion->counter > -0x10);
                }
                goto block_104;
            }
    } else {
        goto out_of_range;
    }
    return;
block_104:
    temp_r2_12 = *(struct Actor9E22C **)0x02032990;
block_105:
    temp_r2_12->flags &= ~2;
    return;
out_of_range:
    *(u8 *)0x0203259E = 0U;
}
