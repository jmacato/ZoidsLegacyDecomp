#include "m2c_prelude.h"

extern s32 func_080E6664(s32);
extern void func_080E705C(void *, s32);
extern void func_080E77FC(void *);
extern void func_080E8B08(s32, s32);
extern void func_080E90AC(s32, s32);
extern void func_080ECD2C(void *, void *, u32);

void sub_080E94A0(s32 arg0, s32 arg1)
{
    volatile u32 dma_zero;
    u8 * volatile config_base;
    volatile u32 outer;
    u8 * volatile metadata_dst;
    u8 * volatile copy_dst;
    volatile u32 next_outer;
    volatile u32 outer4;
    volatile u32 outer16;
    u8 * volatile equipment_saved;

    arg0 <<= 24;
    arg0 = (u32)arg0 >> 24;
    arg1 <<= 24;
    arg1 = (u32)arg1 >> 24;
    {
        register u32 left asm("r2") = arg0 * 0x7D0;
        register u32 right asm("r0") = 0x64;
        register u32 base asm("r1");

        right *= arg1;
        base = 0x087B9454;
        right += base;
        left += right;
        left += 4;
        config_base = (u8 *)left;
    }
    outer = 0;
outer_loop:
    {
        register u32 outer_view asm("r1") = outer;
        register u32 outer4_view asm("r3") = outer_view << 2;
        register u32 row_offset asm("r0");
        u8 *record;
        u8 *secondary;
        u8 *tertiary;
        register u32 input_offset asm("r2");
        register u8 *input asm("r1");
        register u32 clear_index asm("r5");
        register u8 *grid asm("r4");
        register u8 *clear_first asm("ip");
        register u8 *clear_second asm("r9");
        register u8 *detail_kind asm("sl");

        row_offset = outer4_view + outer_view;
        row_offset <<= 3;
        row_offset -= outer_view;
        row_offset <<= 4;
        {
            register u8 *record_base asm("r2") = (u8 *)0x02035ECC;
            register u8 *secondary_base asm("r1") = record_base;

            record = (u8 *)(row_offset + (u32)record_base);
            secondary_base += 0x70;
            secondary = (u8 *)(row_offset + (u32)secondary_base);
            record_base += 0xB0;
            tertiary = (u8 *)(row_offset + (u32)record_base);
        }

        {
            register u32 outer_input asm("r4") = outer;
            input_offset = outer_input << 4;
            {
                register u8 *config_view asm("r0") = config_base;
                input = (u8 *)(input_offset + (u32)config_view);
            }
        }
        record[0] = input[0];
        record[1] = input[1];
        record[2] = input[2];
        {
            register u32 zero8 asm("r1") = 0;
            record[3] = zero8;
        }
        {
            register u32 zero16 asm("r4") = 0;
            *(u16 *)(record + 4) = zero16;
            *(u16 *)(record + 0x10) = zero16;
        }

        clear_index = 0;
        outer4 = outer4_view;
        outer16 = input_offset;
        {
            register u32 next_view asm("r0") = outer + 1;
            next_outer = next_view;
        }
        grid = record + 0x1E;
        {
            register u8 *copy_view asm("r1") = record + 0x50;
            copy_dst = copy_view;
        }
        {
            register u8 *metadata_view asm("r2") = secondary + 0x30;
            metadata_dst = metadata_view;
        }
        {
            register u8 *detail_view asm("r3");
            detail_view = (u8 *)0x31;
            asm volatile("" : "+r"(detail_view));
            detail_view += (u32)secondary;
            detail_kind = detail_view;
        }
        {
            register u32 first_view asm("r0") = 0x12;
            asm volatile("" : "+r"(first_view));
            first_view += (u32)record;
            clear_first = (u8 *)first_view;
        }
        {
            register u32 second_view asm("r1") = 0x18;
            asm volatile("" : "+r"(second_view));
            second_view += (u32)record;
            clear_second = (u8 *)second_view;
        }

clear_outer:
        {
            register u32 zero asm("r3");
            {
                register u8 *first_view asm("r2") = clear_first;
                register u8 *first_at asm("r0");
                asm volatile("" : "+r"(first_view));
                first_at = first_view + clear_index;
                zero = 0;
                *first_at = zero;
            }
            {
                register u8 *second_view asm("r1") = clear_second;
                register u8 *second_at asm("r0");
                asm volatile("" : "+r"(second_view));
                second_at = second_view + clear_index;
                *second_at = zero;
            }
            {
                register u32 inner asm("r1") = 0;
clear_inner:
                {
                    register u32 row asm("r2") = clear_index << 2;
                    register u32 at asm("r0") = inner + row;
                    register u32 inner_zero asm("r3");
                    register u32 next asm("r0");

                    at = (u32)grid + at;
                    inner_zero = 0;
                    *(u8 *)at = inner_zero;
                    next = inner + 1;
                    next <<= 24;
                    inner = next >> 24;
                }
                if (inner <= 3) {
                    goto clear_inner;
                }
            }
        }
        {
            register u32 next asm("r0") = clear_index + 1;
            next <<= 24;
            clear_index = next >> 24;
        }
        if (clear_index <= 5) {
            goto clear_outer;
        }

        {
            register u8 *table asm("r9");
            register u8 *equipment_src asm("r2");

            {
                register u32 id asm("r0") = record[0];
                register u32 table_offset asm("r1") = id << 3;

                table_offset -= id;
                table_offset <<= 3;
                {
                    register u8 *table_base asm("r4") = (u8 *)0x087AFCC4;
                    asm volatile("" : "+r"(table_base));
                    table_offset += (u32)table_base;
                }
                table = (u8 *)table_offset;
            }
            clear_index = 0;
            {
                register u32 input_offset_view asm("r1") = outer16;
                register u8 *config_view2 asm("r2") = config_base;
                register u8 *sum asm("r0") = (u8 *)(input_offset_view + (u32)config_view2);
                equipment_src = sum + 4;
            }
copy_loop:
            {
                register u32 word_offset asm("r4") = clear_index << 2;
                register u8 *dst_base asm("r3") = copy_dst;
                register u8 *dst asm("r0") = dst_base + word_offset;
                register u8 *src asm("r1") = table;

                src += 0x18;
                src += word_offset;
                *(u32 *)dst = *(u32 *)src;
                if (clear_index <= 3) {
                    s32 available;
                    register s32 lookup_id asm("r0") = 0x11;

                    asm volatile("" : "+r"(lookup_id));
                    equipment_saved = equipment_src;
                    available = func_080E6664(lookup_id);
                    available <<= 24;
                    equipment_src = equipment_saved;
                    if (available == 0) {
                        register u8 *slot asm("r0") = record + word_offset;
                        register u8 *equipment_view asm("r1") = equipment_src + clear_index;
                        register u32 value asm("r1") = *equipment_view;
                        slot += 0x52;
                        *(u16 *)slot = value;
                    } else {
                        register u8 *slot asm("r0") = record + word_offset;
                        register u32 zero asm("r4");
                        slot += 0x52;
                        zero = 0;
                        *(u16 *)slot = zero;
                    }
                }
            }
            {
                register u32 next asm("r0") = clear_index + 1;
                next <<= 24;
                clear_index = next >> 24;
            }
            if (clear_index <= 7) {
                goto copy_loop;
            }
        }

        {
            register u32 kind asm("r2") = record[2];
            register u32 table_offset asm("r1") = kind << 4;
            register u8 *table_base asm("r0") = (u8 *)0x087B70E4;
            register u8 *table asm("r1");

            asm volatile("" : "+r"(table_base));
            table_offset += (u32)table_base;
            table = (u8 *)table_offset;
            secondary[0] = kind;
            {
                register u32 value asm("r0") = table[0];
                register u8 *dst asm("r2") = metadata_dst;
                *dst = value;
            }
            {
                register u32 value asm("r0") = table[1];
                register u8 *dst asm("r3") = detail_kind;
                *dst = value;
            }
            *(u16 *)(secondary + 0x34) = *(u16 *)(table + 4);
            *(u16 *)(secondary + 0x36) = *(u16 *)(table + 6);
            *(u16 *)(secondary + 0x38) = *(u16 *)(table + 8);
            *(u16 *)(secondary + 0x3A) = *(u16 *)(table + 0xA);
            *(u16 *)(secondary + 0x3C) = *(u16 *)(table + 0xC);
        }
        func_080E705C(secondary, 1);
        {
            register u8 *kind_view asm("r4") = detail_kind;
            register u32 r2_birth_guard asm("r2");
            u32 kind;

            asm volatile("" : "=r"(r2_birth_guard));
            kind = *kind_view;
            asm volatile("" : : "r"(r2_birth_guard));

            if (kind != 0) {
                register u32 kind_copy asm("r2");
                register u32 table_offset asm("r1");
                register u8 *table asm("r1");

                kind_copy = kind;
                table_offset = kind_copy << 1;
                table_offset += kind_copy;
                table_offset <<= 2;
                {
                    register u8 *table_base asm("r0") = (u8 *)0x087B7774;
                    asm volatile("" : "+r"(table_base));
                    table_offset += (u32)table_base;
                    table = (u8 *)table_offset;
                }
                {
                    register u8 *tertiary_view asm("r0") = tertiary;
                    register u32 table_value asm("r2");
                    tertiary_view[0] = kind_copy;
                    table_value = table[0];
                    tertiary_view += 0x28;
                    *tertiary_view = table_value;
                }
                {
                    register u8 *tertiary_store asm("r2");
                    register u32 first_value asm("r0") = *(u16 *)(table + 2);
                    tertiary_store = tertiary;
                    *(u16 *)(tertiary_store + 0x2A) = first_value;
                    *(u16 *)(tertiary_store + 0x2C) = *(u16 *)(table + 4);
                    *(u16 *)(tertiary_store + 0x2E) = *(u16 *)(table + 6);
                    *(u16 *)(tertiary_store + 0x30) = *(u16 *)(table + 8);
                    *(u16 *)(tertiary_store + 0x32) = *(u16 *)(table + 0xA);
                }
                func_080E77FC(tertiary);
            } else {
                dma_zero = 0;
                {
                    register void *zero_ptr asm("r0");
                    register void *tertiary_view asm("r1");
                    register u32 control asm("r2");

                    zero_ptr = (void *)&dma_zero;
                    asm volatile("" : "+r"(zero_ptr));
                    tertiary_view = tertiary;
                    asm volatile("" : "+r"(tertiary_view));
                    control = 0x0500000D;
                    asm volatile("" : "+r"(control));
                    func_080ECD2C(zero_ptr, tertiary_view, control);
                }
            }
        }

        {
            register s32 one asm("r0") = 1;
            asm volatile("" : "+r"(one));
            func_080E90AC(one, outer);
        }
        {
            register s32 one asm("r0") = 1;
            asm volatile("" : "+r"(one));
            func_080E8B08(one, outer);
        }
        *(u16 *)(record + 6) = *(u16 *)(record + 0x3A);
        {
            register s32 value asm("r0");
            register u32 sign asm("r1");
            register u32 r1_birth_guard asm("r1");
            register u32 r2_birth_guard asm("r2");

            asm volatile("" : "=r"(r1_birth_guard), "=r"(r2_birth_guard));
            value = *(s16 *)(record + 0x3E);
            asm volatile("" : : "r"(r1_birth_guard), "r"(r2_birth_guard));
            sign = (u32)value >> 31;
            value += sign;
            value >>= 1;
            *(u16 *)(record + 8) = value;
        }

        {
            register u32 outer4_view2 asm("r4") = outer4;
            register u32 outer_view2 asm("r0") = outer;
            register u32 row_offset2 asm("r2") = outer4_view2 + outer_view2;
            register u8 *input2 asm("r3");

            row_offset2 <<= 3;
            row_offset2 -= outer_view2;
            row_offset2 <<= 4;
            {
                register u32 dst asm("r1");
                {
                    register u32 global_base asm("r3") = 0x02034B4C;
                    register u32 global_offset asm("r4") = 0x15E8;
                    asm volatile("" : "+r"(global_base));
                    asm volatile("" : "+r"(global_offset));
                    dst = global_base + global_offset;
                    dst = row_offset2 + dst;
                }
                {
                    register u32 input_offset_view2 asm("r0") = outer16;
                    register u8 *config_view3 asm("r4") = config_base;
                    input2 = (u8 *)(input_offset_view2 + (u32)config_view3);
                }
                *(u32 *)dst = *(u32 *)(input2 + 8);
            }
            {
                register u32 dst asm("r0");
                register u32 global_base asm("r1") = 0x02034B4C;
                register u32 global_offset asm("r4") = 0x15EC;
                asm volatile("" : "+r"(global_base));
                asm volatile("" : "+r"(global_offset));
                dst = global_base + global_offset;
                dst = row_offset2 + dst;
                *(u32 *)dst = *(u32 *)(input2 + 0xC);
            }
            {
                register u32 global_base asm("r0") = 0x02034B4C;
                asm volatile("" : "+r"(global_base));
                row_offset2 += global_base;
                {
                    register u32 global_offset asm("r1") = 0x15E4;
                    asm volatile("" : "+r"(global_offset));
                    row_offset2 += global_offset;
                    {
                        register u32 zero asm("r4") = 0;
                        *(u16 *)row_offset2 = zero;
                    }
                }
            }

            {
                register u32 flags asm("r1") = *(u16 *)(record + 4);
                u32 enabled = input2[3];
                if (enabled != 0) {
                    flags |= 0x40;
                }
                *(u16 *)(record + 4) = flags;
            }
        }
    }

    {
        register u32 next_view asm("r1") = next_outer;
        register u32 normalized asm("r0") = next_view << 24;
        normalized >>= 24;
        outer = normalized;
        if (normalized <= 5) {
            goto outer_loop;
        }
    }
}
