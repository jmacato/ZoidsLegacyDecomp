#include "m2c_prelude.h"

u8 func_080CA570(u32, u32);

void sub_080CA8D8(void)
{
    register u32 mid asm("r8");
    register u32 outer asm("r9");
    register s32 grid_offset asm("sl");
    register s32 second_index asm("ip");
    register u32 found asm("r6");
    register u32 sub asm("r5");
    register u32 inner asm("r4");
    u32 sub_next;
    volatile s32 maximum;
    volatile u32 outer_count;
    volatile s32 record_product;
    volatile s32 row_eight;
    volatile s32 outer_six;
    u8 *volatile outer_record;
    volatile s32 signed_maximum;
    volatile u32 outer_next;
    volatile u32 mid_next;
    volatile u32 sub_eight;
    u8 *cell;

    maximum = 0;
    outer = 0;
    {
        register u32 initial_count_r1 asm("r1");
        register u32 outer_bound_r6 asm("r6");
        register u32 outer_load_r2 asm("r2");
        initial_count_r1 = *(u8 *)0x0203EFA8;
        if (outer < initial_count_r1) {
            outer_count = initial_count_r1;
            do {
                register u32 zero_r1 asm("r1");
                register u32 next_outer_r2 asm("r2");
                register u8 *count_addr_r0 asm("r0");
                zero_r1 = 0;
                asm volatile("" : "+r"(zero_r1));
                mid = zero_r1;
                count_addr_r0 = (u8 *)(0x0203EFA9 + outer);
                next_outer_r2 = outer + 1;
                outer_next = next_outer_r2;
                if (mid < *count_addr_r0) {
                    {
                        register s32 work_r0 asm("r0");
                        register s32 calc_r1 asm("r1");
                        register u32 record_id_r2 asm("r2");
                        register u32 outer_copy_r6 asm("r6");
                        outer_copy_r6 = outer;
                        asm volatile("" : "+r"(outer_copy_r6));
                        calc_r1 = outer_copy_r6 << 1;
                        work_r0 = 0x0203EF70 + outer;
                        record_id_r2 = *(u8 *)work_r0;
                        work_r0 = 0xA8C;
                        calc_r1 += outer;
                        calc_r1 <<= 1;
                        outer_six = calc_r1;
                        calc_r1 = record_id_r2;
                        calc_r1 *= work_r0;
                        record_product = calc_r1;
                    }
                    {
                        register u32 row_r2 asm("r2");
                        register u32 row asm("ip");
                        row_r2 = 0x0203ECFB;
                        asm volatile("" : "+r"(row_r2));
                        row_r2 = *(u8 *)row_r2;
                        row = row_r2;
                        row_r2 <<= 3;
                        row_eight = row_r2;
                    }
                    do {
                        sub = 0;
                        {
                            register u32 mid_next_r6 asm("r6");
                            mid_next_r6 = mid + 1;
                            asm volatile("" : "+r"(mid_next_r6));
                            mid_next = mid_next_r6;
                        }
                        {
                            register s32 acc_r0 asm("r0");
                            register s32 row8_r1 asm("r1");
                            register u32 row_r2 asm("r2");
                            register u32 row asm("ip");
                            row8_r1 = row_eight;
                            row_r2 = row;
                            acc_r0 = row8_r1 - row_r2;
                            acc_r0 <<= 5;
                            acc_r0 += row;
                            acc_r0 <<= 2;
                            grid_offset = acc_r0;
                        }
                        do {
                            inner = 0;
                            {
                                register u32 sub_eight_r6 asm("r6");
                                sub_eight_r6 = sub * 8;
                                asm volatile("" : "+r"(sub_eight_r6));
                                sub_eight = sub_eight_r6;
                            }
                            sub_next = sub + 1;
                            {
                                register u32 addr_r3 asm("r3");
                                register u32 base_r0 asm("r0");
                                register u32 record_r1 asm("r1");
                                base_r0 = 0x02037314;
                                base_r0 += grid_offset;
                                record_r1 = record_product;
                                addr_r3 = record_r1 + base_r0;
                            do {
                                register u32 base_r0 asm("r0");
                                register u32 record_r1 asm("r1");
                                register u32 cell_r2 asm("r2");
                                base_r0 = outer_six + mid;
                                cell_r2 = 0x0203EF78;
                                asm volatile("" : "+r"(cell_r2));
                                base_r0 += cell_r2;
                                record_r1 = *(u8 *)base_r0;
                                base_r0 = 0x94;
                                record_r1 *= base_r0;
                                record_r1 += 12;
                                record_r1 = addr_r3 + record_r1;
                                {
                                    register u32 sub8_r6 asm("r6");
                                    sub8_r6 = sub_eight;
                                    asm volatile("" : "+r"(sub8_r6));
                                    base_r0 = sub8_r6 + sub;
                                }
                                base_r0 <<= 3;
                                base_r0 += 4;
                                record_r1 += base_r0;
                                base_r0 = inner << 1;
                                base_r0 += inner;
                                base_r0 <<= 2;
                                cell_r2 = record_r1 + base_r0;
                                cell = (u8 *)cell_r2;
                                if ((*(u16 *)cell & 1) != 0) {
                                    register s32 max_load_r0 asm("r0");
                                    register s32 max_r1 asm("r1");
                                    register s32 offset_r6 asm("r6");
                                    max_load_r0 = maximum;
                                    max_r1 = max_load_r0 << 16;
                                    max_r1 >>= 16;
                                    offset_r6 = 4;
                                    max_load_r0 = *(s16 *)(cell + offset_r6);
                                    if (max_r1 < max_load_r0) {
                                        register u32 update_r2 asm("r2");
                                        update_r2 = *(u16 *)(cell + 4);
                                        maximum = update_r2;
                                    }
                                }
                                {
                                    register u32 next_inner_r0 asm("r0");
                                    next_inner_r0 = inner + 1;
                                    next_inner_r0 <<= 24;
                                    inner = next_inner_r0 >> 24;
                                }
                            } while (inner <= 5);
                            }
                            {
                                register u32 next_sub_r0 asm("r0");
                                next_sub_r0 = sub_next << 24;
                                sub = next_sub_r0 >> 24;
                            }
                        } while (sub <= 1);
                        {
                            register u32 next_mid_r0 asm("r0");
                            register u32 mid_load_r1 asm("r1");
                            mid_load_r1 = mid_next;
                            next_mid_r0 = mid_load_r1 << 24;
                            mid = next_mid_r0 >> 24;
                        }
                    } while (mid < *(u8 *)(0x0203EFA9 + outer));
                }
                {
                    register u32 next_outer_r0 asm("r0");
                    outer_load_r2 = outer_next;
                    next_outer_r0 = outer_load_r2 << 24;
                    outer = next_outer_r0 >> 24;
                }
                outer_bound_r6 = outer_count;
                asm volatile("" : "+r"(outer_bound_r6));
            } while (outer < outer_bound_r6);
        }
    }

    {
        register u8 *initial_count_addr_r1 asm("r1");
        register u32 initial_count_r1 asm("r1");
        outer = 0;
        initial_count_addr_r1 = (u8 *)0x0203EFA8;
        asm volatile("" : "+r"(initial_count_addr_r1));
        initial_count_r1 = *initial_count_addr_r1;
        if (outer < initial_count_r1) {
            do {
                register u32 zero_r2 asm("r2");
                register u8 *mid_count_base_r0 asm("r0");
                register u32 outer_copy_r6 asm("r6");
                register u8 *mid_count_ptr_r1 asm("r1");
                register u32 mid_count_r1 asm("r1");
                zero_r2 = 0;
                asm volatile("" : "+r"(zero_r2));
                mid = zero_r2;
                mid_count_base_r0 = (u8 *)0x0203EFA9;
                asm volatile("" : "+r"(mid_count_base_r0));
                outer_copy_r6 = outer;
                asm volatile("" : "+r"(outer_copy_r6));
                mid_count_ptr_r1 = (u8 *)(outer_copy_r6 + (u32)mid_count_base_r0);
                asm volatile("" : "+r"(mid_count_ptr_r1));
                mid_count_r1 = *mid_count_ptr_r1;
                if (mid < mid_count_r1) {
                    {
                        register s32 max_r1 asm("r1");
                        register s32 signed_r0 asm("r0");
                        max_r1 = maximum;
                        signed_r0 = max_r1 << 16;
                        signed_r0 >>= 16;
                        signed_maximum = signed_r0;
                    }
second_mid:
                    found = 0;
                    sub = 0;
                    {
                        register u32 outer_r2 asm("r2");
                        register u32 index_r0 asm("r0");
                        register u8 *record_r0 asm("r0");
                        outer_r2 = outer;
                        asm volatile("" : "+r"(outer_r2));
                        index_r0 = outer_r2 << 1;
                        index_r0 += outer;
                        index_r0 <<= 1;
                        index_r0 += mid;
                        second_index = index_r0;
                        record_r0 = (u8 *)0x0203EF70;
                        record_r0 += outer;
                        outer_record = record_r0;
                    }
second_sub:
                    inner = 0;
                    sub_next = sub + 1;
                    if (found != 0) {
                        goto second_sub_next;
                    }
                    {
                        register s32 product_r3 asm("r3");
                        {
                            register u8 *record_r2 asm("r2");
                            register u32 record_id_r1 asm("r1");
                            register u32 stride_r0 asm("r0");
                            record_r2 = outer_record;
                            record_id_r1 = *record_r2;
                            asm volatile("" : "+r"(record_id_r1));
                            stride_r0 = 0xA8C;
                            product_r3 = record_id_r1;
                            product_r3 *= stride_r0;
                        }
                        {
                            register s32 base_r2 asm("r2");
                            register u8 *grid_r0 asm("r0");
                            register u8 *row_addr_r0 asm("r0");
                            register u32 row_r1 asm("r1");
                            register s32 row_calc_r0 asm("r0");
                            base_r2 = 0x02037314;
                            grid_r0 = (u8 *)0x0203EF78;
                            asm volatile("" : "+r"(grid_r0));
                            grid_offset = (s32)grid_r0;
                            row_addr_r0 = (u8 *)0x0203ECFB;
                            row_r1 = *row_addr_r0;
                            row_calc_r0 = row_r1 << 3;
                            row_calc_r0 -= row_r1;
                            row_calc_r0 <<= 5;
                            row_calc_r0 += row_r1;
                            row_calc_r0 <<= 2;
                            row_calc_r0 += base_r2;
                            product_r3 += row_calc_r0;
                        }
second_inner:
                        asm volatile("" : "+r"(sub));
                        {
                            register u32 index_r0 asm("r0");
                            register u32 type_r1 asm("r1");
                            register u32 factor_r0 asm("r0");
                            register u32 address_r1 asm("r1");
                            register u32 cell_r2 asm("r2");
                            index_r0 = second_index;
                            index_r0 += grid_offset;
                            type_r1 = *(u8 *)index_r0;
                            factor_r0 = 0x94;
                            type_r1 *= factor_r0;
                            type_r1 += 12;
                            address_r1 = product_r3 + type_r1;
                            index_r0 = sub << 3;
                            index_r0 += sub;
                            index_r0 <<= 3;
                            index_r0 += 4;
                            address_r1 += index_r0;
                            index_r0 = inner << 1;
                            index_r0 += inner;
                            index_r0 <<= 2;
                            cell_r2 = address_r1 + index_r0;
                            cell = (u8 *)cell_r2;
                            if ((*(u16 *)cell & 1) != 0) {
                                register s32 offset_r1 asm("r1");
                                register s32 value_r0 asm("r0");
                                register s32 maximum_r2 asm("r2");
                                offset_r1 = 4;
                                value_r0 = *(s16 *)(cell + offset_r1);
                                maximum_r2 = signed_maximum;
                                if (maximum_r2 == value_r0) {
                                    found = 1;
                                }
                            }
                        }
                        {
                            register u32 next_inner_r0 asm("r0");
                            next_inner_r0 = inner + 1;
                            asm volatile("" : "+r"(next_inner_r0));
                            next_inner_r0 <<= 24;
                            inner = next_inner_r0 >> 24;
                        }
                        if (inner <= 5 && found == 0) {
                            goto second_inner;
                        }
                    }
second_sub_next:
                    {
                        register u32 next_sub_r0 asm("r0");
                        next_sub_r0 = sub_next << 24;
                        sub = next_sub_r0 >> 24;
                    }
                    if (sub <= 1 && found == 0) {
                        goto second_sub;
                    }
                    if (found == 0) {
                        if (func_080CA570(outer, mid) == 0) {
                            outer = (u8)(outer - 1);
                            goto second_outer_next;
                        } else {
                            mid = (u8)(mid - 1);
                        }
                    }
                    mid = (u8)(mid + 1);
                    if (mid < *(u8 *)(0x0203EFA9 + outer)) {
                        goto second_mid;
                    }
                }
second_outer_next:
                outer = (u8)(outer + 1);
            } while (outer < *(u8 *)0x0203EFA8);
        }
    }
}
