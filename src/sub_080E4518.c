#include "m2c_prelude.h"

M2C_UNK func_080E705C(void *, s32);                 /* extern */
M2C_UNK func_080E77FC(void *);                      /* extern */
M2C_UNK func_080E8B08(s32, u8);                     /* extern */
M2C_UNK func_080E90AC(s32, u8);                     /* extern */
M2C_UNK func_080ECD2C(M2C_UNK *, void *, M2C_UNK);      /* extern */
extern u8 D_087AFCC4[];

void sub_080E4518(void) {
    s32 sp0;
    s32 sp4;
    s32 sp8;
    s32 spC;
    s8 *sp10;
    u8 *sp14;
    void *sp18;
    s32 sp1C;
    s32 sp20;
    s32 sp24;
    s32 sp28;
    s32 sp2C;
    s32 sp30;
    u8 *sp34;
    s16 temp_r0_4;
    s32 temp_r0_8;
    s32 temp_r0_9;
    s32 temp_r1_2;
    s32 temp_r2;
    s32 temp_r2_2;
    u8 secondary_id;
    register s32 work_base asm("r4");
    s32 next_r5;
    u8 *temp_r0;
    u8 temp_r0_2;
    register s32 temp_r0_3 asm("r0");
    u8 var_r1;
    u8 var_r5;
    u8 var_r5_4;
    u8 var_sl;
    void *temp_r0_5;
    void *temp_r1;
    void *temp_r1_3;
    u8 *temp_r3;
    u8 *temp_r4;
    u8 *temp_r6;
    u8 var_r5_5;
    u8 var_r5_6;
    register s32 *word_dst asm("r8");
    register s32 *word_src asm("r12");
    s32 word_base;
    u8 *copy_dest;
    u8 copy_value;
    u8 *copy8_dst;
    u8 *copy8_src;

    {
    register s32 entry_offset asm("r2");
    entry_offset = *(u8 *)0x02032E74 * 0x280;
    temp_r0_8 = *(u8 *)0x02032E78 << 7;
    {
    register u8 *entry_table asm("r1") = (u8 *)0x087A3EF0;
    asm volatile("" : : "r"(entry_table));
    temp_r0_8 += (s32)entry_table;
    }
    entry_offset += temp_r0_8;
    sp4 = entry_offset;
    sp8 = 0;
    entry_offset += 0x60;
    sp1C = entry_offset;
    sp20 = sp4 + 0x6A;
    }
loop_1:
    var_sl = 0;
    {
    register s32 row_seed asm("r3") = sp8;
    register s32 double_row asm("r4");
    temp_r0_8 = row_seed * 4;
    double_row = row_seed * 2;
    sp2C = double_row;
    asm volatile("" : : "r"(double_row));
    row_seed += 1;
    sp24 = row_seed;
    }
    {
    register s32 row_again asm("r5") = sp8;
    temp_r0_8 = (temp_r0_8 + row_again) * 8;
    temp_r0_8 -= row_again;
    }
    spC = temp_r0_8 * 0x80;
loop_2:
    {
    register s32 outer_guard5 asm("r5");
    register s32 outer_guard asm("r6");
    asm volatile("" : "=r"(outer_guard5), "=r"(outer_guard));
    temp_r2 = var_sl * 0x270;
    asm volatile("" : : "r"(outer_guard5), "r"(outer_guard));
    }
    temp_r0_8 = temp_r2 + 0x02034B4C;
    {
    register s32 record_offset asm("r3") = spC;
    asm volatile("" : : "r"(record_offset));
    temp_r4 = record_offset + temp_r0_8;
    }
    temp_r3 = temp_r4 + 0x70;
    temp_r6 = temp_r4 + 0xB0;
    temp_r0 = sp4 + ((sp2C + sp8) * 0x10) + (var_sl * 8);
    sp34 = temp_r0;
    M2C_FIELD(temp_r4, u8 *, 0) = (u8) *temp_r0;
    M2C_FIELD(temp_r4, u8 *, 1) = (u8) M2C_FIELD(sp34, u8 *, 1);
    M2C_FIELD(temp_r4, u8 *, 2) = (u8) M2C_FIELD(sp34, u8 *, 2);
    M2C_FIELD(temp_r4, s8 *, 3) = 0;
    M2C_FIELD(temp_r4, s16 *, 4) = 4;
    {
    register s32 field_zero asm("r1") = 0;
    asm volatile("" : "+r"(field_zero));
    M2C_FIELD(temp_r4, s16 *, 0x10) = field_zero;
    }
    var_r5 = 0;
    sp30 = var_sl * 4;
    {
    register s32 next_sl asm("r2") = var_sl + 1;
    asm volatile("" : "+r"(next_sl));
    sp28 = next_sl;
    }
    {
    register u8 *clear12 asm("r9");
    register u8 *clear18 asm("r8");
    register u8 *matrix asm("r12");
    register u8 *matrix_seed asm("r7");
    asm volatile(
        "mov %0, #30\n"
        "add %0, %1"
        : "=r"(matrix_seed)
        : "r"(temp_r4));
    matrix = matrix_seed;
    sp18 = temp_r4 + 0x50;
    sp10 = temp_r4 + 0xA0;
    sp14 = temp_r4 + 0xA1;
    asm volatile(
        "mov r7, #18\n"
        "add r7, %2\n"
        "mov %0, r7\n"
        "mov r0, #24\n"
        "add r0, %2\n"
        "mov %1, r0"
        : "=r"(clear12), "=r"(clear18)
        : "r"(temp_r4)
        : "r0", "r7");
    do {
        asm volatile(
            "mov r1, %0\n"
            "add r0, r1, %2\n"
            "mov r2, #0\n"
            "strb r2, [r0]\n"
            "mov r7, %1\n"
            "add r0, r7, %2\n"
            "strb r2, [r0]"
            :
            : "r"(clear12), "r"(clear18), "r"(var_r5)
            : "r0", "r1", "r2", "r7", "memory");
        var_r1 = 0;
        do {
            u8 *matrix_cell;
            register s32 matrix_zero asm("r7");
            matrix_cell = &matrix[var_r1 + (var_r5 * 4)];
            matrix_zero = 0;
            *matrix_cell = matrix_zero;
            var_r1 += 1;
        } while ((u32) var_r1 <= 3U);
        next_r5 = var_r5 + 1;
        asm volatile("" : "+r"(next_r5));
        var_r5 = next_r5;
    } while ((u32) var_r5 <= 5U);
    }
    {
    register s32 word_guard5 asm("r5");
    register s32 word_guard7 asm("r7");
    asm volatile("" : "=r"(word_guard5), "=r"(word_guard7));
    word_base = (M2C_FIELD(temp_r4, u8 *, 0) * 0x38) + (s32)D_087AFCC4;
    asm volatile("" : : "r"(word_guard5), "r"(word_guard7));
    }
    var_r5 = 0;
    word_dst = (s32 *)sp18;
    word_base += 0x18;
    word_src = (s32 *)word_base;
    do {
        temp_r2_2 = var_r5 * 4;
        *(s32 *)((s32)word_dst + temp_r2_2) = *(s32 *)((s32)word_src + temp_r2_2);
        if (var_r5 <= 3U) {
            copy_dest = temp_r4 + temp_r2_2;
            copy_value = M2C_FIELD(&sp34[var_r5], u8 *, 3);
            M2C_FIELD(copy_dest, s16 *, 0x52) = copy_value;
        }
        var_r5 = (u8) (var_r5 + 1);
    } while ((u32) var_r5 <= 7U);
    temp_r0_2 = M2C_FIELD(temp_r4, u8 *, 2);
    temp_r1 = (temp_r0_2 * 0x10) + 0x087B70E4;
    M2C_FIELD(temp_r3, u8 *, 0) = temp_r0_2;
    *sp10 = 0x63;
    *sp14 = M2C_FIELD(temp_r1, u8 *, 1);
    M2C_FIELD(temp_r3, u16 *, 0x34) = (u16) M2C_FIELD(temp_r1, u16 *, 4);
    M2C_FIELD(temp_r3, u16 *, 0x36) = (u16) M2C_FIELD(temp_r1, u16 *, 6);
    M2C_FIELD(temp_r3, u16 *, 0x38) = (u16) M2C_FIELD(temp_r1, u16 *, 8);
    M2C_FIELD(temp_r3, u16 *, 0x3A) = (u16) M2C_FIELD(temp_r1, u16 *, 0xA);
    M2C_FIELD(temp_r3, u16 *, 0x3C) = (u16) M2C_FIELD(temp_r1, u16 *, 0xC);
    func_080E705C(temp_r3, 1);
    temp_r0_3 = *sp14;
    if (temp_r0_3 != 0) {
        register s32 secondary_id_local asm("r2");
        register u8 *secondary_row asm("r1");
        u8 secondary_value;
        u8 *secondary_dest;
        secondary_id_local = temp_r0_3;
        asm volatile("" : "+r"(secondary_id_local));
        temp_r1_2 = secondary_id_local * 0xC;
        secondary_row = (u8 *)(temp_r1_2 + 0x087B7774);
        asm volatile("" : "+r"(secondary_row));
        M2C_FIELD(temp_r6, u8 *, 0) = secondary_id_local;
        secondary_value = M2C_FIELD(secondary_row, u8 *, 0);
        secondary_dest = temp_r6 + 0x28;
        *secondary_dest = secondary_value;
        M2C_FIELD(temp_r6, u16 *, 0x2A) = M2C_FIELD(secondary_row, u16 *, 2);
        M2C_FIELD(temp_r6, u16 *, 0x2C) = M2C_FIELD(secondary_row, u16 *, 4);
        M2C_FIELD(temp_r6, u16 *, 0x2E) = M2C_FIELD(secondary_row, u16 *, 6);
        M2C_FIELD(temp_r6, u16 *, 0x30) = M2C_FIELD(secondary_row, u16 *, 8);
        M2C_FIELD(temp_r6, u16 *, 0x32) = M2C_FIELD(secondary_row, u16 *, 0xA);
        func_080E77FC(temp_r6);
    } else {
        register void *dma_src asm("r0");
        register void *dma_dst asm("r1");
        register u32 dma_control asm("r2");
        sp0 = temp_r0_3;
        dma_src = &sp0;
        dma_dst = temp_r6;
        asm volatile("" : "+r"(dma_src), "+r"(dma_dst));
        dma_control = 0x0500000D;
        func_080ECD2C(dma_src, dma_dst, dma_control);
    }
    func_080E90AC(sp8, var_sl);
    func_080E8B08(sp8, var_sl);
    M2C_FIELD(temp_r4, u16 *, 6) = (u16) M2C_FIELD(temp_r4, u16 *, 0x3A);
    temp_r0_4 = M2C_FIELD(temp_r4, s16 *, 0x3E);
    M2C_FIELD(temp_r4, s16 *, 8) = (s16) ((s32) (temp_r0_4 + ((u32) temp_r0_4 >> 0x1F)) >> 1);
    {
    register s32 work_clear asm("r2");
    {
    register s32 bottom_first asm("r0") = sp30;
    asm volatile("add %0, sl" : "+r"(bottom_first));
    bottom_first *= 8;
    bottom_first -= var_sl;
    bottom_first *= 0x10;
    {
    register s32 bottom_row asm("r3") = spC;
    asm volatile("" : : "r"(bottom_row));
    bottom_first += bottom_row;
    }
    work_base = 0x02034B4C;
    {
    register s32 clear_guard asm("r6");
    asm volatile("" : "=r"(clear_guard));
    work_clear = work_base + (0x9A << 2);
    asm volatile("" : : "r"(clear_guard));
    }
    *(s32 *)(bottom_first + work_clear) = 0;
    asm volatile(
        "add r7, #4\n"
        "add r1, %1, r7\n"
        "add r0, %0, r1\n"
        "str %2, [r0]"
        : "+r"(bottom_first)
        : "r"(work_base), "r"(0)
        : "r1", "r7", "memory");
    }
    temp_r2 = (var_r5 * 0x270) + work_base;
    M2C_FIELD(temp_r2, s16 *, 0x15E4) = 0;
    {
    register s32 next_inner asm("r3") = sp28;
    register s32 inner_guard5 asm("r5");
    u8 next_inner_value;
    asm volatile("" : "=r"(inner_guard5));
    asm volatile(
        "lsl %0, %1, #24\n"
        "lsr %0, %0, #24"
        : "=&l"(next_inner_value)
        : "r"(next_inner));
    asm volatile("" : : "r"(inner_guard5));
    var_sl = next_inner_value;
    }
    if ((u32) var_sl <= 5U) {
        goto loop_2;
    }
    {
    register s32 next_outer asm("r4") = sp24;
    register s32 outer_tail_guard5 asm("r5");
    u8 next_outer_value;
    asm volatile("" : "=r"(outer_tail_guard5));
    asm volatile(
        "lsl %0, %1, #24\n"
        "lsr %0, %0, #24"
        : "=&l"(next_outer_value)
        : "r"(next_outer));
    asm volatile("" : : "r"(outer_tail_guard5));
    sp8 = next_outer_value;
    }
    if ((u32) sp8 <= 1U) {
        goto loop_1;
    }
    var_r5 = 0;
    {
    register u16 *first_copy_dst asm("r3");
    register s32 first_copy_guard asm("r6");
    asm volatile("" : "=r"(first_copy_guard));
    first_copy_dst = (u16 *)(work_clear + 0xA034);
    asm volatile("" : : "r"(first_copy_guard));
    do {
        temp_r0_8 = var_r5 * 2;
        M2C_FIELD(temp_r0_8, u16 *, (s32)first_copy_dst) = (u16) M2C_FIELD(temp_r0_8, u16 *, 0x02021774);
        var_r5 += 1;
    } while ((u32) var_r5 <= 8U);
    }
    {
    register u16 *second_copy_dst asm("r3");
    register u16 *second_copy_src asm("r2");
    var_r5 = 0;
    second_copy_dst = (u16 *)0x0203EE0C;
    second_copy_src = (u16 *)0x02021786;
    asm volatile("" : "+r"(second_copy_dst), "+r"(second_copy_src));
    do {
        temp_r0_9 = var_r5_4 * 2;
        second_copy_dst[var_r5] = second_copy_src[var_r5];
        var_r5 += 1;
    } while ((u32) var_r5 <= 0x16U);
    }
    {
    register u8 *third_copy_dst asm("r3");
    register u8 *third_copy_src asm("r2");
    var_r5 = 0;
    third_copy_dst = (u8 *)0x02037300;
    third_copy_src = (u8 *)sp1C;
    asm volatile("" : "+r"(third_copy_dst), "+r"(third_copy_src));
    do {
        M2C_FIELD(var_r5, u8 *, (s32)third_copy_dst) = third_copy_src[var_r5];
        var_r5 += 1;
    } while ((u32) var_r5 <= 9U);
    }
    {
    register u8 *fourth_copy_dst asm("r3");
    register u8 *fourth_copy_src asm("r2");
    var_r5 = 0;
    fourth_copy_dst = (u8 *)0x020217F4;
    fourth_copy_src = (u8 *)sp20;
    asm volatile("" : "+r"(fourth_copy_dst), "+r"(fourth_copy_src));
    do {
        M2C_FIELD(var_r5, u8 *, (s32)fourth_copy_dst) = fourth_copy_src[var_r5];
        var_r5 += 1;
    } while ((u32) var_r5 <= 9U);
    }
    }
}
