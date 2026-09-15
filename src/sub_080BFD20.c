#include "m2c_prelude.h"
extern u8 D_02034B4C[];

void sub_080BFD20(u8 arg0, u8 arg1) {
    u32 outer_offset;
    u32 row_offset;
    u32 entry_offset;
    register u32 type asm("r1");
    register u32 mask asm("r0");
    u8 *entry;
    register u16 *field asm("r1");
    register void *object asm("r12");
    u8 index;
    register u32 base asm("r2");

    outer_offset = arg0 << 2;
    outer_offset += arg0;
    outer_offset <<= 3;
    outer_offset -= arg0;
    outer_offset <<= 7;
    row_offset = arg1 * 0x270;
    base = (u32)D_02034B4C;
    row_offset += base;
    outer_offset += row_offset;
    object = (void *)outer_offset;
    index = 0;
    do {
        outer_offset = arg0 << 2;
        outer_offset += arg0;
        outer_offset <<= 3;
        outer_offset -= arg0;
        outer_offset <<= 7;
        row_offset = arg1 * 0x270;
        row_offset += base;
        outer_offset += row_offset;
        entry_offset = index * 0xC;
        entry_offset += 0xE4;
        entry = (u8 *)(outer_offset + entry_offset);
        if (!(*(u32 *)entry & 0x1FFF0000)) {
            type = *(u16 *)(entry + 4);
            asm volatile("" : "+r"(type));
            mask = 0x7F;
            mask &= type;
            mask -= 2;
            switch (mask) {
            case 0: {
                register u16 value asm("r0");
                register u16 other asm("r1");
                register u16 sum asm("r0");
                register void *read_object asm("r1");
                register void *write_object asm("r3");

                value = M2C_FIELD(entry, u16 *, 6);
                read_object = object;
                other = M2C_FIELD(read_object, u16 *, 0x3A);
                sum = value;
                asm volatile("" : "+r"(sum));
                sum += other;
                write_object = object;
                M2C_FIELD(write_object, u16 *, 0x3A) = sum;
                break;
            }
            case 1: {
                register u16 value asm("r0");
                register u16 other asm("r1");
                register u16 sum asm("r0");
                register void *read_object asm("r1");
                register void *write_object asm("r3");

                value = M2C_FIELD(entry, u16 *, 6);
                read_object = object;
                other = M2C_FIELD(read_object, u16 *, 0x3C);
                sum = value;
                asm volatile("" : "+r"(sum));
                sum += other;
                write_object = object;
                M2C_FIELD(write_object, u16 *, 0x3C) = sum;
                break;
            }
            case 3: {
                register u16 value asm("r0");
                register u16 other asm("r1");
                register u16 sum asm("r0");
                register void *read_object asm("r1");
                register void *write_object asm("r3");

                value = M2C_FIELD(entry, u16 *, 6);
                read_object = object;
                other = M2C_FIELD(read_object, u16 *, 0x3E);
                sum = value;
                asm volatile("" : "+r"(sum));
                sum += other;
                write_object = object;
                M2C_FIELD(write_object, u16 *, 0x3E) = sum;
                break;
            }
            case 4:
                field = (u16 *)(object + 0x40);
                goto add_field;
            case 5:
                field = (u16 *)(object + 0x42);
                goto add_field;
            case 6:
                field = (u16 *)(object + 0x44);
                goto add_field;
            case 7:
                field = (u16 *)(object + 0x46);
                goto add_field;
            case 8:
                field = (u16 *)(object + 0x48);
                goto add_field;
            case 9:
                field = (u16 *)(object + 0x4A);
                goto add_field;
            case 10:
                field = (u16 *)(object + 0x4C);
add_field:
                {
                    register u16 value asm("r0");
                    register u16 other asm("r3");
                    register u16 sum asm("r0");

                    value = *(u16 *)(entry + 6);
                    other = *field;
                    sum = value;
                    asm volatile("" : "+r"(sum));
                    sum += other;
                    *field = sum;
                }
                break;
            }
        }
        index++;
    } while (index <= 0x1F);
}
