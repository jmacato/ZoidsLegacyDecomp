#include "m2c_prelude.h"

extern void func_08094330(void);
extern void func_08096308(s32, s32);
extern void func_08096FBC(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern void *func_0809716C(s32);
extern void func_0809844C(s32, s32, s32, s32, s32, s32, s32);
extern void func_08098BB4(s32);
extern void func_0809AB44(s32, s32, s32, s32, s32);

void sub_080E3CE0(void) {
    volatile u32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 sp24;
    s32 sp28;
    s32 sp2C;
    u8 temp_r0;
    register s32 item asm("ip");
    register s32 inner asm("r8");
    register s32 outer asm("r9");
    register u8 *table asm("sl");
    register s32 *first_bits asm("r5");
    register u32 first_mask asm("r3");
    register u32 first_one asm("r4");
    register s32 inner2 asm("r4");
    register s32 inner12 asm("r6");
    s32 outer8;
    register s32 outer_offset asm("r5");
    register s32 outer_load asm("r1");
    register u32 outer_norm asm("r0");

    *(s16 *)0x0300004C = 0x1140;
    func_08096FBC(0, 1, 0, 0x3C0, 0x3C0, 0, 0xE, 0, 0x3E6, 0xF);
    func_0809AB44(1, 3, 0x40, 0xD, 0x18);
    func_08098BB4(0x08006176);
    {
        register s32 count_zero asm("r0");
        register s32 outer_seed asm("r1");

        count_zero = 0;
        sp1C = count_zero;
        outer_seed = 1;
        asm volatile("" : "+r"(outer_seed));
        outer = outer_seed;
    }
    first_bits = (s32 *)0x020217B4;
    first_mask = 0x1F;
    first_one = 1;
    do {
        register u32 current asm("r0");
        register s32 *word asm("r2");
        register u32 bit asm("r1");

        current = outer;
        word = (s32 *)((current >> 5) * 4 + (u32)first_bits);
        current &= first_mask;
        bit = first_one;
        bit <<= current;
        current = *word;
        current &= bit;
        if (current != 0) {
            sp1C = (u8)(sp1C + 1);
        }
        temp_r0 = outer + 1;
        outer = temp_r0;
    } while (temp_r0 <= 0x97);
    func_0809844C(sp1C, 3, 0, 2, 1, 0xE, 0);
    {
        register s32 count_zero asm("r1");

        count_zero = 0;
        sp1C = count_zero;
        outer = count_zero;
    }
    do {
        register u32 outer_minus asm("r0");
        register u32 width_one asm("r2");
        register u32 inner_zero asm("r1");
        register u32 outer_next asm("r2");
        register s32 outer8_seed asm("r1");
        register s32 outer_total asm("r0");

        outer_minus = outer;
        outer_minus -= 1;
        outer_minus <<= 24;
        outer_minus >>= 24;
        width_one = 1;
        sp18 = width_one;
        if (outer_minus <= 1) {
            sp18 = 3;
        }
        inner_zero = 0;
        asm volatile("" : "+r"(inner_zero));
        inner = inner_zero;
        outer_next = outer;
        asm volatile("" : "+r"(outer_next));
        outer_next += 1;
        sp28 = outer_next;
        if (inner < sp18) {
            outer8_seed = outer;
            asm volatile("" : "+r"(outer8_seed));
            outer8_seed <<= 3;
            sp20 = outer8_seed;
            outer_total = outer8_seed;
            asm volatile("" : "+r"(outer_total));
            outer_total += outer;
            outer_total <<= 2;
            sp24 = outer_total;
            do {
                register u32 address asm("r0");
                register s32 row_offset asm("r1");
                register u8 *table_seed asm("r2");
                register u32 count asm("r0");
                register u32 item_seed asm("r2");

                item_seed = 1;
                asm volatile("" : "+r"(item_seed));
                item = item_seed;
                address = inner;
                inner2 = address << 1;
                address = inner2 + address;
                address <<= 2;
                asm volatile("" : "+g"(sp20) : "r"(inner));
                outer8 = sp20;
                asm volatile("" : : "r"(outer8));
                row_offset = sp24;
                address += row_offset;
                table_seed = (u8 *)0x087A3D24;
                address += (u32)table_seed;
                sp2C = inner + 1;
                count = *(u8 *)address;
                if ((u32)item <= count) {
                    table = table_seed;
item_loop:
                    {
                        register u32 item_address asm("r1");
                        register u32 value asm("r3");
                        register u32 word_address asm("r2");
                        register u32 work0 asm("r0");
                        register u32 bit asm("r1");
                        register s32 inner_copy asm("r1");
                        register s32 outer_copy asm("r2");
                        register s32 item_copy asm("r2");

                        asm volatile("" : "=r"(inner_copy) : "0"(inner), "r"(item));
                        address = inner2 + inner_copy;
                        inner12 = address << 2;
                        item_copy = item;
                        asm volatile("" : "+r"(item_copy));
                        item_address = item_copy;
                        item_address += inner12;
                        asm volatile("" : "=r"(outer_copy) : "0"(outer), "r"(item));
                        address = outer8 + outer_copy;
                        outer_offset = address << 2;
                        item_address += outer_offset;
                        item_address += (u32)table;
                        value = *(u8 *)item_address;
                        word_address = value >> 5;
                        word_address <<= 2;
                        work0 = 0x020217C8;
                        word_address += work0;
                        work0 = 0x1F;
                        value &= work0;
                        bit = 1;
                        bit <<= value;
                        work0 = *(u32 *)word_address;
                        work0 &= bit;
                        if (work0 != 0) {
                            sp1C = (u8)(sp1C + 1);
                        }
                        item = (u8)(item + 1);
                        address = inner12 + outer_offset;
                        address += (u32)table;
                        count = *(u8 *)address;
                        if ((u32)item <= count) {
                            goto item_loop;
                        }
                    }
                }
                {
                    register s32 next_load asm("r1");
                    register u32 normalized asm("r0");
                    register s32 width asm("r2");

                    next_load = sp2C;
                    normalized = next_load;
                    normalized <<= 24;
                    normalized >>= 24;
                    inner = normalized;
                    width = sp18;
                    if ((u32)inner < (u32)width) {
                        goto inner_loop;
                    }
                }
                goto inner_done;
inner_loop:
                ;
            } while (1);
inner_done:
            ;
        }
        outer_load = sp28;
        asm volatile("" : "+r"(outer_load));
        outer_norm = outer_load;
        outer_norm <<= 24;
        outer_norm >>= 24;
        outer = outer_norm;
    } while (outer_norm <= 6);
    func_0809844C(sp1C, 3, 0, 2, 1, 0xE, 2);
    *(u8 *)(func_0809716C(1) + 0x16) = *(u8 *)0x02032E70;
    func_08094330();
    func_08096308(0xF, 0);
    asm volatile("" : : "g"(sp20));
}
