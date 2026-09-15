#include "m2c_prelude.h"

extern void *func_08094484(s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern u8 func_080ECF78(u8, s32);

extern u8 *D_02032EBC[2][6];
extern u8 *D_02032E8C[2][6];
extern u8 D_02032EEC[2][6];

void sub_080BAC54(void) {
    u8 row;
    u8 col;
    u8 zero;

    row = 0;
    zero = 0;
    do {
        u32 next_row;
        col = 0;
        do {
            u8 index = row * 6 + col;
            if (row == 0) {
                D_02032EBC[0][col] = func_08094484(0x08106F50, 0x08106F5C, 0, 0, row, index << 3, 14, 0x20048, row);
                ({ u8 **pA = D_02032E8C[0]; asm volatile("" : "+r"(pA)); pA; })[col] =
                    func_08094484(0x0821024C, 0x08210258, 0, 0, row, index << 6, index,
                        ({ s32 v = 3; v -= func_080ECF78(col, 3); v <<= 6; v |= 0x20308; v; }), row);
            } else {
                D_02032EBC[row][col] = func_08094484(0x08106F50, 0x08106F5C, 0, 0, zero, index << 3, 14, 0x20048, zero);
                D_02032E8C[row][col] = func_08094484(0x0821024C, 0x08210258, 0, 0, zero, index << 6, index,
                    ({ s32 w = ((func_080ECF78(col, 3) << 6) + 0x40) | 0x28308; w; }), zero);
            }
            *(u8 **)(D_02032EBC[row][col] + 40) = D_02032E8C[row][col];
            D_02032EEC[row][col] = zero;
            next_row = row + 1;
            col++;
        } while (col <= 5);
        row = next_row;
    } while (row <= 1);
}
