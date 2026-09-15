#include "m2c_prelude.h"

void func_80ECD2C(void *, void *, u32);

void sub_08092B8C(s32 arg0, s32 arg1, s32 arg2, s32 arg3,
                  s32 arg4, s32 arg5, s32 arg6)
{
    u16 *destination = (u16 *)arg0;
    register u16 *source asm("r10") = (u16 *)arg1;
    register s32 raw_width asm("r0") = arg4;
    register s32 raw_rows asm("r1") = arg5;
    register s32 raw_base asm("r4") = arg6;
    register u32 x asm("r8");
    register u32 y asm("r5");
    register u32 source_width asm("r3");
    volatile u32 rows;
    volatile u32 base;
    volatile u32 source_stride;
    register u32 copy_width asm("r2");
    register u32 width asm("r6");

    x = (u16)arg2;
    y = (u16)arg3;
    source_width = (u16)raw_width;
    rows = (u16)raw_rows;
    base = (u16)raw_base;
    copy_width = source_width;
    if (source_width > 32) {
        copy_width = 32;
    }
    width = copy_width;
    {
        register u32 x_view asm("r1") = x;
        register s32 signed_x asm("r0");
        register s32 signed_y asm("r1");

        asm volatile("" : "+r"(x_view));
        signed_x = (s16)x_view;
        signed_y = (s16)y;
        signed_y <<= 5;
        signed_x += signed_y;
        destination += signed_x;
    }

    y = 0;
    {
        register u32 initial_rows asm("r2") = rows;
        asm volatile("" : "+r"(initial_rows));
        if (y >= initial_rows) {
            goto done;
        }
    }
    {
        source_stride = source_width << 1;
        do {
            u16 column;
            register u16 *next_destination asm("r12");

            func_80ECD2C(source, destination, width);
            column = 0;
            next_destination = destination + 32;
            y++;
            if (column < width) {
                register u32 upper_mask asm("r9");
                register u32 lower_mask asm("r8");
                register u32 upper_load asm("r1") = 0x0C00;
                register u32 lower_load asm("r2");

                asm volatile("" : "+r"(upper_load));
                upper_mask = upper_load;
                lower_load = 0xF3FF;
                asm volatile("" : "+r"(lower_load));
                lower_mask = lower_load;

                do {
                    register u16 *cell asm("r3") =
                        (u16 *)((u32)column << 1);
                    register u32 value asm("r2");
                    register u32 upper asm("r1");
                    register u32 lower asm("r0");
                    register u32 base_value asm("r2");

                    asm volatile("add %0, %0, %1"
                                 : "+r"(cell)
                                 : "r"(destination));
                    value = *cell;
                    upper = upper_mask;
                    upper &= value;
                    lower = lower_mask;
                    lower &= value;
                    base_value = base;
                    lower = base_value + lower;
                    upper |= lower;
                    *cell = upper;
                    column++;
                } while (column < width);
            }
            source = (u16 *)((u8 *)source + source_stride);
            destination = next_destination;
            {
                register u32 wrapped asm("r0") = y << 16;
                register u32 tail_rows asm("r1");
                asm volatile("" : "+r"(wrapped));
                y = wrapped >> 16;
                tail_rows = rows;
                asm volatile("" : "+r"(tail_rows));
                if (y < tail_rows) {
                    goto next_row;
                }
            }
            goto done;
next_row:
            ;
        } while (1);
    }
done:
    ;
}
