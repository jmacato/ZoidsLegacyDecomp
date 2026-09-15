#include "m2c_prelude.h"

struct Transfer952AC {
    u32 flags;
    u8 *source;
    u8 *destination;
    u16 width;
    u16 count;
};

void func_080ECD2C(void *, void *, u32);

void sub_080952AC(void) {
    register u32 outer asm("r5");
    register s32 outer_offset asm("r6");
    u32 next_outer;
    register struct Transfer952AC *base asm("r3");

    outer = 0;
    base = (struct Transfer952AC *)0x03005DE8;
    asm volatile("" : "+r"(base));
    do {
        register s32 offset asm("r1");
        register struct Transfer952AC *transfer asm("r2");
        register u32 flags asm("r4");
        register s32 active asm("r0");

        offset = outer << 4;
        transfer = (struct Transfer952AC *)(offset + (s32)base);
        flags = transfer->flags;
        active = 1;
        active &= flags;
        outer_offset = offset;
        next_outer = outer + 1;
        if (active != 0) {
            switch (flags & 2) {
            case 0: {
                register void *source asm("r0");
                register void *destination asm("r1");
                register u32 packed asm("r2");

                source = transfer->source;
                asm volatile("" : "+r"(source));
                destination = transfer->destination;
                asm volatile("" : "+r"(destination));
                packed = *(u32 *)&transfer->width;
                packed <<= 10;
                packed >>= 11;
                func_080ECD2C(source, destination, packed);
                break;
            }
            case 2: {
                register struct Transfer952AC *loop_transfer asm("r4");
                register u32 inner asm("r5");

                loop_transfer = transfer;
                inner = 0;
                goto inner_test;
inner_loop:
                    {
                        register u32 width asm("r2");
                        register u32 source_offset asm("r1");
                        register u8 *source asm("r0");
                        register u32 destination_offset asm("r3");
                        register u8 *destination asm("r1");

                        width = loop_transfer->width;
                        source_offset = inner;
                        source_offset *= width;
                        source_offset <<= 1;
                        source = loop_transfer->source;
                        source = (u8 *)((s32)source + source_offset);
                        asm volatile("" : "+r"(source));
                        destination_offset = inner << 6;
                        destination = loop_transfer->destination;
                        destination = (u8 *)((s32)destination + destination_offset);
                        func_080ECD2C(source, destination, width);
                    }
                    {
                        register u32 next_inner asm("r0");

                        next_inner = inner + 1;
                        next_inner <<= 24;
                        inner = next_inner >> 24;
                    }
inner_test:
                if (inner < loop_transfer->count) {
                    goto inner_loop;
                }
                break;
            }
            }
            {
                register struct Transfer952AC *clear_transfer asm("r2");
                register s32 clear_flags asm("r0");
                register s32 clear_mask asm("r1");

                base = (struct Transfer952AC *)0x03005DE8;
                asm volatile("" : "+r"(base));
                clear_transfer = (struct Transfer952AC *)(outer_offset + (s32)base);
                clear_flags = clear_transfer->flags;
                clear_mask = -2;
                clear_flags &= clear_mask;
                clear_transfer->flags = clear_flags;
            }
        }
        {
            register u32 normalized_outer asm("r0");

            normalized_outer = next_outer << 24;
            normalized_outer >>= 24;
            outer = normalized_outer;
        }
    } while (outer <= 15);
}
