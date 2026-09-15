#include "m2c_prelude.h"

void func_080ED038(void *, void *, s32);
void func_0809F7F0(s32);

extern u8 D_0202DD80[];
extern u8 D_02027378[];
extern u8 D_020218E4[];
extern u8 D_020282EC[];
extern u8 D_0202ECF4[];

void sub_080BB7EC(void)
{
    register u8 *destination asm("r5");
    register u8 *source asm("r2");
    register u32 index asm("r4");
    u8 *source_base;
    register u8 *scan asm("r0");
    register u8 *current asm("r3");
    u8 first_source;

    index = 1;
    source_base = D_0202DD80;
    scan = source_base;
    scan += 0x40;
    source = scan;
    first_source = *scan;
    destination = D_02027378;
    if (first_source != 0x1E) {
        do {
            register u32 next asm("r0");
            next = index + 1;
            next <<= 24;
            index = next >> 24;
            if (index > 0x34) {
                break;
            }
            scan = (u8 *)(index * 0x40);
            scan += (u32)source_base;
            source = scan;
        } while (*scan != 0x1E);
    }

    index = 1;
    scan = destination;
    scan += 0x40;
    current = scan;
    if (((*(u16 *)(scan + 2) & 0xFF00) >> 8) != 0x1E) {
        do {
            register u32 next asm("r0");
            next = index + 1;
            next <<= 24;
            index = next >> 24;
            if (index > 0x34) {
                break;
            }
            scan = (u8 *)(index * 0x40);
            scan += (u32)destination;
            current = scan;
        } while (((*(u16 *)(scan + 2) & 0xFF00) >> 8) != 0x1E);
    }

    {
        register u8 *selected_source asm("r6");
        u16 destination_flags;
        destination = current;
        selected_source = source;
        func_080ED038(destination, source, 0x40);
        destination_flags = *(u16 *)(destination + 2);
        {
            u32 mask = 0xFFFB;
            register u16 masked_destination asm("r1");
            masked_destination = mask;
            asm volatile("" : "+r"(masked_destination));
            masked_destination &= destination_flags;
            *(u16 *)(destination + 2) = masked_destination;
            if (selected_source[1] != 0) {
                register u8 *table_a asm("r4");
                register u8 *table_b asm("r3");
                register u32 table_a_address asm("r0");
                register u32 table_b_address asm("r1");
                table_a = D_020218E4;
                table_a_address = destination[1] * 0x70;
                table_a_address += (u32)table_a;
                table_b = D_020282EC;
                table_b_address = selected_source[1] * 0x70;
                table_b_address += (u32)table_b;
                table_a_address += 4;
                table_b_address += 4;
                func_080ED038((void *)table_a_address,
                               (void *)table_b_address, 0x70);
                {
                    register u8 *table_entry asm("r1");
                    register u16 table_flags asm("r2");
                    register u16 masked_table_flags asm("r0");
                    table_entry = (u8 *)(destination[1] * 0x70 + (u32)table_a);
                    table_flags = *(u16 *)(table_entry + 8);
                    masked_table_flags = mask;
                    asm volatile("" : "+r"(masked_table_flags));
                    masked_table_flags &= table_flags;
                    *(u16 *)(table_entry + 8) = masked_table_flags;
                }
                table_a[1]++;
            }
        }
    }
    func_0809F7F0(0x89);
    func_0809F7F0(0xCB);
    func_0809F7F0(0xCC);
    func_0809F7F0(0xCD);
    func_0809F7F0(0xCE);
    func_0809F7F0(0xCF);
    D_0202ECF4[0x21] = 0;
}
