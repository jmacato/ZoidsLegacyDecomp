#include "m2c_prelude.h"

typedef struct {
    u32 word0;
    u32 flags;
    u16 unk8;
    u16 amount;
} BattleState;

u8 func_080BF464(s32, s32, s32);                    /* extern */
BattleState *func_080E669C(u32, u32, u32, u32);     /* extern */
M2C_UNK func_080E66B8();                            /* extern */
s32 func_080E74F0(s32, s32, s32);                   /* extern */
u8 func_080E7BCC();                                 /* extern */
M2C_UNK func_080E8C90(u8, u8, u8, u8, BattleState *); /* extern */
s32 func_080ECD98(s32, s32);                        /* extern */
M2C_UNK jtbl_080E7CCC();                            /* static */
extern u8 D_0203055C[];

s16 sub_080E7C18(u32 arg0, u32 arg1, u32 arg2, u32 arg3, u32 arg4, u32 arg5, u32 arg6) {
    register u32 first asm("r0") = arg0;
    register u32 second asm("r1") = arg1;
    register u32 third asm("r5") = arg2;
    register u32 fourth asm("r6") = arg3;
    register u32 raw_unit asm("r2") = arg4;
    register u32 raw_member asm("r3") = arg5;
    register u32 raw_arg6 asm("r4") = arg6;
    register u32 unit asm("r9");
    register u32 member asm("sl");
    volatile u32 outgoing_reserve;
    volatile s32 sp4;
    volatile s32 sp8;
    volatile s32 spC;
    void *volatile sp10;
    void *volatile sp14;
    BattleState *volatile sp18;
    volatile u32 outgoing;
    volatile s32 sp20;
    volatile s32 sp24;
    volatile s32 sp28;
    u8 *volatile sp2C;
    volatile s32 sp30;
    register s32 first4 asm("r1");
    register s32 second4 asm("r0");
    register s32 first_scan_saved asm("r2");
    register s32 first_scan_base asm("r2");
    s16 temp_r0_11;
    s16 temp_r0_7;
    s16 temp_r0_9;
    s16 temp_r1_5;
    s32 temp_r1_3;
    s32 temp_r1_7;
    register s32 temp_r4 asm("r4");
    register s32 temp_r5_4 asm("r5");
    u16 temp_r0_6;
    u16 temp_r1_10;
    u16 temp_r1_2;
    s32 temp_r1_4;
    u16 temp_r1_6;
    u16 temp_r1_8;
    register u16 temp_r7 asm("r7");
    u16 preloaded_amount;
    u16 var_r4;
    u16 var_r4_2;
    u16 var_r6_2;
    u16 var_r7;
    u32 temp_r0_10;
    u32 temp_r1_9;
    u32 var_r0;
    u32 var_r0_2;
    u32 var_r0_3;
    u32 var_r6;
    u8 temp_r0_3;
    s32 temp_r0_4;
    u8 temp_r0_5;
    u8 var_r3;
    u8 var_r3_2;
    u8 var_r3_3;
    u8 var_r3_4;
    register u32 var_r8 asm("r8");
    void *temp_r0_2;
    register void *temp_r5 asm("r5");
    register void *temp_r5_2 asm("r5");
    register void *temp_r5_3 asm("r5");
    register void *temp_r5_5 asm("r5");
    register void *third_scan_entry asm("r5");

    asm volatile("" : "=m"(outgoing_reserve));
    first = (u8)first;
    sp4 = first;
    second = (u8)second;
    sp8 = second;
    third = (u8)third;
    fourth = (u8)fourth;
    raw_unit = (u8)raw_unit;
    unit = raw_unit;
    raw_member = (u8)raw_member;
    member = raw_member;
    raw_arg6 = (u8)raw_arg6;
    spC = raw_arg6;
    sp18 = func_080E669C(first, second, raw_unit, raw_member);
    sp10 = (void *)(0x02034B4C + sp4 * 0x1380 + sp8 * 0x270);
    {
        register s32 unit_stride asm("r1");

        asm volatile(
            "mov r3, r9\n\t"
            "lsl %0, r3, #2\n\t"
            "add %0, r9\n\t"
            "lsl %0, %0, #3\n\t"
            "sub %0, %0, r3\n\t"
            "lsl %0, %0, #7"
            : "=&r"(unit_stride)
            : "r"(unit)
            : "r3", "cc");
        sp14 = (void *)(0x02034B4C + unit_stride + member * 0x270);
    }
    asm volatile(
        "ldr r0, [sp, #24]\n"
        "str r0, [sp]\n"
        "ldr r0, [sp, #4]\n"
        "ldr r1, [sp, #8]\n"
        "add r2, r5, #0\n"
        "add r3, r6, #0\n"
        "bl func_080E8C90"
        : "=m"(outgoing)
        : "r"(third), "r"(fourth), "m"(sp4), "m"(sp8), "m"(sp18)
        : "r0", "r1", "r2", "r3", "lr", "cc", "memory");
    asm volatile(
        "ldr r1, [sp, #24]\n\t"
        "ldrh %0, [r1, #12]"
        : "=r"(temp_r7)
        : "m"(sp18)
        : "r1", "memory");
    var_r6 = 0;
    temp_r0_3 = M2C_FIELD(sp14, u8 *, 0x38);
    switch (temp_r0_3) {                            /* switch 1 */
    case 1:                                         /* switch 1 */
        break;
    case 0:                                         /* switch 1 */
        asm volatile(
            "lsl %0, %1, #16"
            : "=r"(var_r0)
            : "r"(var_r6)
            : "cc");
        {
            register u32 case_addend asm("r2") = 0xFFEC0000;

            asm volatile(
                "add %0, %0, %1"
                : "+r"(var_r0)
                : "r"(case_addend)
                : "cc");
        }
        asm volatile("" : "+r"(var_r0));
        var_r6 = var_r0 >> 0x10;
        break;
    case 2:                                         /* switch 1 */
        asm volatile(
            "lsl %0, %1, #16\n\t"
            "mov r3, #160\n\t"
            "lsl r3, r3, #12\n\t"
            "add %0, %0, r3"
            : "=r"(var_r0)
            : "r"(var_r6)
            : "r3", "cc");
        var_r6 = var_r0 >> 0x10;
        break;
    case 3:                                         /* switch 1 */
        asm volatile(
            "lsl %0, %1, #16\n\t"
            "mov %1, #200\n\t"
            "lsl %1, %1, #13\n\t"
            "add %0, %0, %1"
            : "=r"(var_r0), "+r"(var_r6)
            :
            : "cc");
        var_r6 = var_r0 >> 0x10;
        break;
    case 4:                                         /* switch 1 */
        var_r0 = (var_r6 << 0x10) + 0x1E0000;
        var_r6 = var_r0 >> 0x10;
        break;
    }
    temp_r0_4 = (u8)func_080E7BCC(sp4, sp8, unit, member);
    if (temp_r0_4 == 2) {
        goto block_13;
    }
    if (temp_r0_4 <= 2) {
        goto block_12;
    }
    if (temp_r0_4 == 3) {
        goto block_15;
    }
    goto block_12;
block_13:
    var_r0_2 = (var_r6 << 0x10) + 0xFFF60000;
    goto block_14;
block_15:
    var_r0_2 = (var_r6 << 0x10) + 0xFFE20000;
block_14:
    var_r6 = var_r0_2 >> 0x10;
block_12:
    var_r8 = 0;
    asm volatile(
        "ldr r2, [sp, #4]\n\t"
        "lsl r1, r2, #2\n\t"
        "ldr r3, [sp, #8]\n\t"
        "lsl r0, r3, #2\n\t"
        "mov r2, r9\n\t"
        "lsl r2, r2, #2\n\t"
        "str r2, [sp, #36]\n\t"
        "mov r3, sl\n\t"
        "lsl r3, r3, #2\n\t"
        "str r3, [sp, #40]"
        : "=r"(first4), "=r"(second4), "=m"(sp24), "=m"(sp28)
        : "m"(sp4), "m"(sp8), "r"(unit), "r"(member)
        : "r2", "r3", "cc", "memory");
    preloaded_amount = M2C_FIELD(sp14, u16 *, 0xC);
    sp30 = M2C_FIELD(sp18, s32 *, 4);
    sp2C = sp10 + 0x36;
    first_scan_saved = sp4;
    first4 += first_scan_saved;
    first4 *= 8;
    first4 -= first_scan_saved;
    first4 <<= 7;
    first_scan_saved = sp8;
    second4 += first_scan_saved;
    second4 *= 8;
    second4 -= first_scan_saved;
    second4 <<= 4;
    second4 += 0x02034B4C;
    asm volatile("" : "+r"(second4));
    first_scan_base = first4 + second4;
loop_16:
    {
        register u32 first_scan_entry_offset asm("r0") = var_r8 << 1;

        first_scan_entry_offset += var_r8;
        first_scan_entry_offset <<= 2;
        first_scan_entry_offset += 0xE4;
        temp_r5 = first_scan_base + first_scan_entry_offset;
    }
    if ((M2C_FIELD(temp_r5, u16 *, 4) == 0) || !(M2C_FIELD(temp_r5, s32 *, 0) & 0x200)) {
        temp_r0_5 = var_r8 + 1;
        var_r8 = temp_r0_5;
        if ((u32) temp_r0_5 <= 0x1FU) {
            goto loop_16;
        }
    }
    {
    register s32 first_member_offset asm("ip");

    var_r4 = preloaded_amount;
    {
        register u32 first_index_seed asm("r3") = 0;

        var_r3 = first_index_seed;
    }
    outgoing = (((sp24 + unit) * 8) - unit) << 7;
    sp20 = sp30;
    first_member_offset = (((sp28 + member) * 8) - member) << 4;
    do {
        register u8 *first_scan_loop_base asm("r1") = (u8 *)0x02034B4C;

        first_scan_loop_base += first_member_offset;
        {
            register s32 first_row_offset asm("r2") = outgoing;

            asm volatile(
                "add %0, %1, %0"
                : "+r"(first_scan_loop_base)
                : "r"(first_row_offset)
                : "cc");
        }
        {
            register u32 first_entry_offset asm("r0") = var_r3 << 1;

            first_entry_offset += var_r3;
            first_entry_offset <<= 2;
            first_entry_offset += 0xE4;
            temp_r5_2 = first_scan_loop_base + first_entry_offset;
        }
        temp_r1_2 = M2C_FIELD(temp_r5_2, u16 *, 4);
        if (temp_r1_2 != 0) {
            register u32 kind_mask asm("r0") = 0x7F;

            kind_mask &= temp_r1_2;
            if (kind_mask == 0xE) {
                {
                    register s32 loaded_flags asm("r1") =
                        M2C_FIELD(temp_r5_2, s32 *, 0);
                    register u32 first_flag_mask asm("r0") = 0x10000;

                first_flag_mask &= loaded_flags;
                {
                register s32 flags_view asm("r2") = loaded_flags;

                if ((first_flag_mask != 0) && ((u32) var_r8 <= 0x1FU)) {
                    register s32 signed_sum asm("r0") = (s16)var_r4;
                    register u32 addend asm("r1") =
                        M2C_FIELD(temp_r5_2, u16 *, 6);

                    signed_sum += addend;
                    var_r4 = (u16)signed_sum;
                }
                if (0x20000 & flags_view) {
                    register u32 saved_mask asm("r0") = 0x80;
                    register u32 saved_flags asm("r2") = sp20;

                    saved_mask &= saved_flags;
                    if (saved_mask != 0) {
                        register s32 signed_sum asm("r0") = (s16)var_r4;
                        register u32 addend asm("r5") =
                            M2C_FIELD(temp_r5_2, u16 *, 6);

                        signed_sum += addend;
                        var_r4 = (u16)signed_sum;
                    }
                }
                }
                }
            }
        }
        var_r3 += 1;
    } while ((u32) var_r3 <= 0x1FU);
    }
    {
        register s32 base_value asm("r0");

        asm volatile(
            "ldr r3, [sp, #16]\n\t"
            "mov r1, #12\n\t"
            "ldrsh %0, [r3, r1]"
            : "=r"(base_value)
            : "m"(sp10)
            : "r1", "r3", "memory");
        temp_r1_4 = func_080ECD98(base_value - (s16)var_r4, 0xA);
    }
    {
        register u32 retained_adjustment asm("r6") = var_r6;

        asm volatile("" : "+r"(retained_adjustment));
        {
            register s32 signed_adjustment asm("r1") =
                (s16)retained_adjustment;

            signed_adjustment += temp_r1_4;
            signed_adjustment <<= 16;
            retained_adjustment = (u32)signed_adjustment >> 16;
            signed_adjustment >>= 16;
            if (signed_adjustment < 0) {
                register s32 clamp_sum asm("r0") =
                    signed_adjustment + M2C_FIELD(sp10, u16 *, 0x4A);

                clamp_sum <<= 16;
                retained_adjustment = (u32)clamp_sum >> 16;
                if (clamp_sum > 0) {
                    retained_adjustment = 0;
                }
            }
        }
        asm volatile(
            "lsl r0, %2, #16\n\t"
            "asr r0, r0, #16\n\t"
            "lsl r1, %1, #16\n\t"
            "asr r1, r1, #16\n\t"
            "add r0, r0, r1\n\t"
            "lsl r0, r0, #16\n\t"
            "lsr %0, r0, #16"
            : "=r"(var_r7)
            : "r"(retained_adjustment), "0"(temp_r7)
            : "r0", "r1", "cc");
    }
    {
    register s32 second_row_offset asm("r6");
    register s32 second_member_offset asm("r4");

    var_r3_2 = 0;
    {
        register s32 row_work asm("r0") = sp24 + unit;

        row_work *= 8;
        asm volatile(
            "mov r2, r9\n\t"
            "sub %0, %0, r2"
            : "+r"(row_work)
            :
            : "r2", "cc");
        second_row_offset = row_work << 7;
    }
    {
        register s32 member_work asm("r0") = sp28 + member;

        member_work *= 8;
        asm volatile(
            "mov r1, sl\n\t"
            "sub %0, %0, r1"
            : "+r"(member_work)
            :
            : "r1", "cc");
        second_member_offset = member_work << 4;
    }
    do {
        register u8 *second_table_base asm("r2") = (u8 *)0x02034B4C;
        register u8 *second_scan_base asm("r1");

        asm volatile("" : "+r"(second_table_base));
        asm volatile(
            "add %0, %1, %2"
            : "=r"(second_scan_base)
            : "r"(second_member_offset), "r"(second_table_base)
            : "cc");
        asm volatile(
            "add %0, %1, %0"
            : "+r"(second_scan_base)
            : "r"(second_row_offset)
            : "cc");
        {
            register u32 second_entry_offset asm("r0") = var_r3_2 << 1;

            second_entry_offset += var_r3_2;
            second_entry_offset <<= 2;
            second_entry_offset += 0xE4;
            temp_r5_3 = second_scan_base + second_entry_offset;
        }
        temp_r1_6 = M2C_FIELD(temp_r5_3, u16 *, 4);
        if (temp_r1_6 != 0) {
            register u32 kind_mask asm("r0") = 0x7F;

            kind_mask &= temp_r1_6;
            if (kind_mask == 0x11) {
                {
                    register s32 loaded_flags asm("r1") =
                        M2C_FIELD(temp_r5_3, s32 *, 0);
                    register u32 first_flag_mask asm("r0") = 0x10000;

                first_flag_mask &= loaded_flags;
                {
                register s32 flags_view asm("r2") = loaded_flags;

                if (first_flag_mask != 0) {
                    register u32 first_index_view asm("r0") = var_r8;

                    asm volatile("" : "+r"(first_index_view));
                    if (first_index_view <= 0x1FU) {
                        register u32 subtrahend asm("r1") =
                            M2C_FIELD(temp_r5_3, u16 *, 6);
                        register s32 signed_value asm("r0") = (s16)var_r7;

                        signed_value -= subtrahend;
                        var_r7 = (u16)signed_value;
                    }
                }
                if (0x20000 & flags_view) {
                    register u32 saved_mask asm("r0") = 0x80;
                    register u32 saved_flags asm("r1") = sp30;

                    saved_mask &= saved_flags;
                    if (saved_mask != 0) {
                        register u32 subtrahend asm("r1") =
                            M2C_FIELD(temp_r5_3, u16 *, 6);
                        register s32 signed_value asm("r0") = (s16)var_r7;

                        signed_value -= subtrahend;
                        var_r7 = (u16)signed_value;
                    }
                }
                if (!(0xFF0000 & flags_view)) {
                    register u32 subtrahend asm("r1") =
                        M2C_FIELD(temp_r5_3, u16 *, 6);
                    register s32 signed_value asm("r0") = (s16)var_r7;

                    signed_value -= subtrahend;
                    var_r7 = (u16)signed_value;
                }
                }
                }
            }
        }
        var_r3_2 += 1;
    } while ((u32) var_r3_2 <= 0x1FU);
    }
    {
        register u8 *side_ptr asm("r2") = sp2C;

        if ((0x40 & *side_ptr) && !(0x40 & M2C_FIELD(sp14, u8 *, 0x36))) {
            register u32 shifted_value asm("r0") = var_r7 << 16;

            asm volatile(
                "mov r3, #160\n\t"
                "lsl r3, r3, #13\n\t"
                "add %0, %0, r3"
                : "+r"(shifted_value)
                :
                : "r3", "cc");
            var_r7 = (u16)(shifted_value >> 16);
        }
    }
    {
        register BattleState *state_ptr asm("r6") = sp18;

        if (!(state_ptr->flags & 0x20) &&
            (func_080BF464(sp4, sp8, 0x16) == 0xFF) &&
            (0x40 & M2C_FIELD(sp14, u8 *, 0x36))) {
            register u32 shifted_value asm("r0");

            asm volatile(
                "lsl %0, %1, #16"
                : "=r"(shifted_value)
                : "r"(var_r7)
                : "cc");
            {
                register u32 addend asm("r1") = 0xFFEC0000;

                asm volatile(
                    "add %0, %0, %1"
                    : "+r"(shifted_value)
                    : "r"(addend)
                    : "cc");
            }
            var_r7 = (u16)(shifted_value >> 16);
        }
    }
    {
        register BattleState *state_ptr asm("r2") = sp18;

        if (!(state_ptr->flags & 0x40)) {
            if (D_0203055C[1] == 0xB) {
                register u32 shifted_value asm("r0");

                asm volatile(
                    "lsl %0, %1, #16"
                    : "=r"(shifted_value)
                    : "r"(var_r7)
                    : "cc");
                {
                    register u32 addend asm("r3") = 0xFFEC0000;

                    asm volatile(
                        "add %0, %0, %1"
                        : "+r"(shifted_value)
                        : "r"(addend)
                        : "cc");
                }
                var_r0_3 = shifted_value;
                goto block_56;
            }
        } else if (D_0203055C[1] != 0xB) {
            register u32 shifted_value asm("r0");

            asm volatile(
                "lsl %0, %1, #16"
                : "=r"(shifted_value)
                : "r"(var_r7)
                : "cc");
            {
                register u32 addend asm("r6") = 0xFFEC0000;

                asm volatile(
                    "add %0, %0, %1"
                    : "+r"(shifted_value)
                    : "r"(addend)
                    : "cc");
            }
            var_r0_3 = shifted_value;
block_56:
            var_r7 = (u16) (var_r0_3 >> 0x10);
        }
    }
    if (func_080BF464(sp4, sp8, 0x1E) != 0xFF) {
        register BattleState *state_ptr asm("r1") = sp18;

        if ((state_ptr->flags & 0x10) &&
            (0x40 & M2C_FIELD(sp14, u8 *, 0x36))) {
            register u32 shifted_value asm("r0") = var_r7 << 16;

            asm volatile(
                "mov r2, #160\n\t"
                "lsl r2, r2, #13\n\t"
                "add %0, %0, r2"
                : "+r"(shifted_value)
                :
                : "r2", "cc");
            var_r7 = (u16)(shifted_value >> 16);
        }
    }
    temp_r4 = sp24 + unit;
    temp_r4 *= 8;
    asm volatile(
        "mov r3, r9\n\t"
        "sub %0, %0, r3"
        : "+r"(temp_r4)
        :
        : "r3", "cc");
    temp_r4 <<= 7;
    {
        register s32 member_offset asm("r0") = sp28 + member;

        member_offset *= 8;
        asm volatile(
            "mov r6, sl\n\t"
            "sub %0, %0, r6"
            : "+r"(member_offset)
            :
            : "r6", "cc");
        member_offset <<= 4;
        {
            register s32 table_base asm("r6") = 0x02034B4C;

            asm volatile("" : "+r"(table_base));
            member_offset += table_base;
        }
        temp_r4 += member_offset;
    }
    temp_r5_4 = temp_r4 + 0x70;
    {
        s32 reduction = func_080E74F0(
            temp_r5_4, 0x1F, M2C_FIELD(sp18, s32 *, 4));
        register s32 signed_value asm("r1") = (s16)var_r7;

        signed_value -= reduction;
        var_r7 = (u16)signed_value;
    }
    {
        register BattleState *state_ptr asm("r1") = sp18;
        s32 reduction = func_080E74F0(
            temp_r5_4, 0x20, state_ptr->flags);
        register s32 signed_value asm("r1") = (s16)var_r7;

        signed_value -= reduction;
        var_r7 = (u16)signed_value;
    }
    var_r3_3 = 0;
    do {
        {
            register u32 third_scan_entry_offset asm("r0") = var_r3_3 << 1;

            third_scan_entry_offset += var_r3_3;
            third_scan_entry_offset <<= 2;
            third_scan_entry_offset += 0xE4;
            third_scan_entry = temp_r4 + third_scan_entry_offset;
        }
        temp_r1_8 = M2C_FIELD(third_scan_entry, u16 *, 4);
        if (temp_r1_8 != 0) {
            register u32 kind_mask asm("r0") = 0x7F;

            kind_mask &= temp_r1_8;
            if (kind_mask == 0x13) {
                temp_r0_7 = (s16) var_r7;
                temp_r1_9 = 0x64 - temp_r0_7;
                var_r7 = temp_r0_7 + ((s32) (temp_r1_9 + (temp_r1_9 >> 0x1F)) >> 1);
            }
        }
        var_r3_3 += 1;
    } while ((u32) var_r3_3 <= 0x1FU);
    {
    register u32 optional_enabled asm("r2") = spC;

    if (optional_enabled != 0) {
        register s32 optional_row_offset asm("r8");
        register s32 optional_member_offset asm("r9");

        {
            register u32 optional_index_seed asm("r3") = 0;

            var_r4_2 = M2C_FIELD(sp14, u16 *, 0x48);
            var_r3_4 = optional_index_seed;
        }
        {
            register s32 row_work asm("r0") = sp24 + unit;

            row_work *= 8;
            asm volatile(
                "mov r6, r9\n\t"
                "sub %0, %0, r6"
                : "+r"(row_work)
                :
                : "r6", "cc");
            optional_row_offset = row_work << 7;
        }
        {
            register s32 member_work asm("r0") = sp28 + member;

            member_work *= 8;
            asm volatile(
                "mov r1, sl\n\t"
                "sub %0, %0, r1"
                : "+r"(member_work)
                :
                : "r1", "cc");
            optional_member_offset = member_work << 4;
        }
        do {
            register u8 *optional_base asm("r1") = (u8 *)0x02034B4C;

            optional_base += optional_member_offset;
            optional_base += optional_row_offset;
            {
                register u32 optional_entry_offset asm("r0") = var_r3_4 << 1;

                optional_entry_offset += var_r3_4;
                optional_entry_offset <<= 2;
                optional_entry_offset += 0xE4;
                temp_r5_5 = optional_base + optional_entry_offset;
            }
            temp_r1_10 = M2C_FIELD(temp_r5_5, u16 *, 4);
            if (temp_r1_10 != 0) {
                register u32 kind_mask asm("r0") = 0x7F;
                register u32 entry_flags asm("r1");
                register u32 high_mask asm("r0");
                register u32 low_mask asm("r2");
                register BattleState *state_ptr asm("r6");
                register u32 state_flags asm("r0");

                kind_mask &= temp_r1_10;
                if (kind_mask == 0xA) {
                    entry_flags = M2C_FIELD(temp_r5_5, u32 *, 0);
                    high_mask = 0x1F000000;
                    entry_flags &= high_mask;
                    low_mask = 31;
                    entry_flags >>= 24;
                    state_ptr = sp18;
                    state_flags = state_ptr->flags;
                    entry_flags &= state_flags;
                    state_flags &= low_mask;
                    if (entry_flags == state_flags) {
                        register s32 signed_sum asm("r0") = (s16)var_r4_2;
                        register u32 addend asm("r5") =
                            M2C_FIELD(temp_r5_5, u16 *, 6);

                        signed_sum += addend;
                        var_r4_2 = (u16)signed_sum;
                    }
                }
            }
            var_r3_4 += 1;
        } while ((u32) var_r3_4 <= 0x1FU);
        temp_r0_9 = (s16) var_r4_2;
        if ((s32) temp_r0_9 < 0) {
            var_r4_2 = 0;
        } else if ((s32) temp_r0_9 > 0x63) {
            var_r4_2 = 0x63;
        }
        temp_r0_10 = (s16) var_r7 - (s16) var_r4_2;
        var_r7 = (u16) ((u32) ((temp_r0_10 + (temp_r0_10 >> 0x1F)) << 0xF) >> 0x10);
    }
    }
    temp_r0_11 = (s16) var_r7;
    if ((s32) temp_r0_11 < 0) {
        var_r7 = 0;
    } else if ((s32) temp_r0_11 > 0x3E7) {
        var_r7 = 0x3E7;
    }
    func_080E66B8();
    return (s16) var_r7;
}
