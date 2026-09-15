#include "m2c_prelude.h"

void func_080BF514(u8, u8, u8);
void func_080E8B08(u8, u8);
s32 func_080E9D88(u8, u8);
extern u8 D_02034B4C[];
extern u8 D_0203ED28[];

void sub_080BF858(void) {
    s32 next_row;
    s32 next_col;
    u8 row;
    u8 col;
    u8 slot;

    row = 0;
    do {
    col = 0;
    next_row = row + 1;
    do {
        s32 ret = func_080E9D88(row, col) << 24;
        next_col = col + 1;
        if (ret != 0) {
            register u32 row4 asm("r10");
            register u32 col4 asm("r8");
            register u8 *base asm("r9");

            slot = 0;
            row4 = row << 2;
            col4 = col << 2;
            base = D_02034B4C;
            do {
                u8 *grid = (u8 *)(((((row4 + row) << 3) - row) << 7)
                    + (((((col4 + col) << 3) - col) << 4) + (u32)base));
                u8 *entry = grid + ((slot * 0xC) + 0xE4);
                u16 field = *(u16 *)(entry + 4);

                if (field != 0) {
                    switch (field & 0xE000) {
                    case 0x4000:
                        break;
                    case 0x0: {
                        u16 uval0 = *(u16 *)(entry + 8);
                        if (*(s16 *)(entry + 8) != 0) {
                            u32 nv = uval0 - 1;
                            *(u16 *)(entry + 8) = nv;
                            if ((nv << 16) == 0) {
                                func_080BF514(row, col, slot);
                            }
                        }
                        break;
                    }
                    case 0x6000:
                        if ((*(u32 *)(((row * 0x18) + col4) + (u32)D_0203ED28)
                             & (1 << slot)) != 0) {
                            func_080BF514(row, col, slot);
                        }
                        break;
                    case 0xA000: {
                        u16 uval = *(u16 *)(entry + 8);
                        s16 sval = *(s16 *)(entry + 8);
                        if (sval >= 0) {
                            u16 pu = *(u16 *)(grid + 8);
                            if (*(s16 *)(grid + 8) < sval) {
                                func_080BF514(row, col, slot);
                            } else {
                                *(u16 *)(grid + 8) = pu - uval;
                            }
                        } else {
                            *(u16 *)(entry + 8) = -uval;
                        }
                        break;
                    }
                    }
                }
                slot++;
            } while ((u32)slot <= 0x1F);
            func_080E8B08(row, col);
        }
        col = (u8)next_col;
    } while ((u32)col <= 5);
    {
        s32 t = next_row;
        asm volatile("" : "+r"(t));
        row = (u8)t;
    }
    } while ((u32)row <= 1);
}
