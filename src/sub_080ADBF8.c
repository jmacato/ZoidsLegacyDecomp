#include "m2c_prelude.h"

void func_080ECD2C(void *, u32, u32);
void func_0809A1BC(u32, u32, u32);

void sub_080ADBF8(u32 arg0, u32 arg1)
{
    u16 work[2];
    u32 palette_home;
    register u32 tile_base asm("r6") = arg0;
    register u32 palette_base asm("r4") = arg1;
    register u32 zero asm("r8");
    register u32 vram_base asm("r5");

    asm volatile("" : "+r"(tile_base), "+r"(palette_base));
    tile_base <<= 24;
    palette_base <<= 24;
    palette_base >>= 24;
    {
        register u16 *work_ptr asm("r0") = work;
        register u32 zero_copy asm("r1") = 0;

        asm volatile("" : "+r"(work_ptr), "+r"(zero_copy));
        zero = zero_copy;
        *work_ptr = zero_copy;
        tile_base >>= 10;
        vram_base = 0x06000000;
        {
            register u32 dma_destination asm("r1");

            asm volatile("add %0, %1, %2"
                         : "=r"(dma_destination)
                         : "r"(tile_base), "r"(vram_base));
            func_080ECD2C(work_ptr, dma_destination, 0x01001010);
        }
    }
    {
        register u16 *work_ptr asm("r0") = work + 1;
        register u32 zero_copy asm("r2") = zero;

        asm volatile("" : "+r"(work_ptr), "+r"(zero_copy));
        *work_ptr = zero_copy;
        palette_base <<= 11;
        asm volatile("add %0, %1, %0"
                     : "+r"(vram_base)
                     : "r"(palette_base));
        func_080ECD2C(work_ptr, vram_base, 0x01000400);
    }
    func_0809A1BC(0x0849A264, 0x05000000, 0x02002880);

    {
        register u8 *source asm("r8");
        register u8 *source_birth asm("r3");
        u32 row;
        register u32 tile_offset asm("r12");
        register u32 mask asm("r9");
        register u32 output_base asm("r10");
        register u32 output_birth asm("r1");

        source_birth = (u8 *)0x08468FA0;
        asm volatile("" : "+r"(source_birth));
        source = source_birth;
        asm volatile("" : "+r"(source));
        row = 0;
        asm volatile("" : "+r"(row));
        tile_offset = tile_base;
        asm volatile("" : "+r"(tile_offset));
        palette_home = palette_base;
        asm volatile("" : "+m"(palette_home));
        mask = 7;
        asm volatile("" : "+r"(mask));
        output_birth = 0x06000020;
        asm volatile("" : "+r"(output_birth));
        output_base = output_birth;
        asm volatile("" : "+r"(output_base));
        do {
            register u32 column asm("r5") = 0;
            register u32 row_word asm("r6");
            register u32 row_chunk asm("r4");
            register u32 row_word_seed asm("r0");
            register u32 row_chunk_seed asm("r1");
            register u32 mask_copy asm("r2");

            row_chunk_seed = row >> 3;
            asm volatile("" : "+r"(row_chunk_seed));
            row_word_seed = row;
            asm volatile("" : "+r"(row_word_seed));
            mask_copy = mask;
            asm volatile("" : "+r"(mask_copy));
            row_word_seed &= mask_copy;
            row_word = row_word_seed << 2;
            row_chunk = row_chunk_seed << 4;
            do {
                register u32 value asm("r3") = *source;
                u32 test;

                asm volatile("" : "+r"(value));
                test = value & 0x40;
                if (test != 0) {
                    register u32 address asm("r1");
                    register u32 shift asm("r0");
                    register u32 output asm("r2");

                    address = column >> 3;
                    asm volatile("add %0, %1, %0"
                                 : "+r"(address)
                                 : "r"(row_chunk));
                    address <<= 5;
                    address += tile_offset;
                    asm volatile("add %0, %1, %0"
                                 : "+r"(address)
                                 : "r"(row_word));
                    address += output_base;
                    shift = column;
                    output = mask;
                    asm volatile("" : "+r"(shift), "+r"(output));
                    shift &= output;
                    shift <<= 2;
                    output = 0xF;
                    output <<= shift;
                    *(u32 *)address |= output;
                } else {
                    register u32 address asm("r1");
                    register u32 shift asm("r0");
                    register u32 output asm("r2");
                    register u32 mask_copy asm("r3");

                    address = column >> 3;
                    asm volatile("add %0, %1, %0"
                                 : "+r"(address)
                                 : "r"(row_chunk));
                    address <<= 5;
                    address += tile_offset;
                    asm volatile("add %0, %1, %0"
                                 : "+r"(address)
                                 : "r"(row_word));
                    address += output_base;
                    output = (value & 0x1F) + 1;
                    shift = column;
                    mask_copy = mask;
                    asm volatile("" : "+r"(shift), "+r"(mask_copy));
                    shift &= mask_copy;
                    shift <<= 2;
                    output <<= shift;
                    *(u32 *)address |= output;
                }
                source += 2;
                {
                    register u32 column_next asm("r0") = column + 1;

                    asm volatile("" : "+r"(column_next));
                    column = (u16)column_next;
                }
            } while (column <= 0x7F);
            {
                register u32 source_skip asm("r1") = 0x80;

                asm volatile("" : "+r"(source_skip));
                source_skip <<= 1;
                source += source_skip;
            }
            asm volatile("" : "+r"(row));
            row = (u16)(row + 1);
        } while (row <= 0x7F);
    }

    {
        u32 row;
        register u32 palette_offset asm("r4");
        register u32 vram asm("r8");
        register u32 vram_birth asm("r2");

        row = 0;
        asm volatile("" : "+r"(row));
        palette_offset = palette_home;
        asm volatile("" : "+r"(palette_offset));
        vram_birth = 0x06000000;
        asm volatile("" : "+r"(vram_birth));
        vram = vram_birth;
        asm volatile("" : "+r"(vram));
        do {
            register u32 column asm("r5") = 0;
            register u32 row_next asm("r6") = row + 1;
            register u32 row32 asm("r2") = row << 5;
            register u32 row16 asm("r3") = row << 4;

            do {
                if (column <= 0xF && row <= 0xF) {
                    register u32 address asm("r1");
                    register u32 value asm("r0");

                    address = (row32 + column) << 1;
                    asm volatile("add %0, %1, %0"
                                 : "+r"(address)
                                 : "r"(palette_offset));
                    address += vram;
                    asm volatile("add %0, %1, %2"
                                 : "=r"(value)
                                 : "r"(column), "r"(row16));
                    value += 1;
                    *(u16 *)address = value;
                } else {
                    register u32 address asm("r0");
                    register u32 value asm("r1");

                    address = (row32 + column) << 1;
                    asm volatile("add %0, %1, %0"
                                 : "+r"(address)
                                 : "r"(palette_offset));
                    address += vram;
                    value = 0;
                    asm volatile("" : "+r"(value));
                    *(u16 *)address = value;
                }
                {
                    register u32 column_next asm("r0") = column + 1;

                    asm volatile("" : "+r"(column_next));
                    column = (u16)column_next;
                }
            } while (column <= 0x1F);
            {
                register u32 row_narrow asm("r0");

                row_narrow = row_next << 16;
                row = row_narrow >> 16;
            }
        } while (row <= 0x1F);
    }
}
