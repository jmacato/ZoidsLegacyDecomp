#include "m2c_prelude.h"

extern s32 func_080E9D88(u8, u8);
extern void func_080ECD28(u8 *, u8 *, s32);
extern s32 func_080ECD98(s32, s32);
extern void func_080BAA40(u8, u8 *);

extern u8 *D_02032EBC[2][6];

void sub_080BAB3C(void) {
    u8 outer;
    u8 inner;
    u8 first;
    u8 second;
    u8 *work;

    outer = 0;
    work = (u8 *)0x020028A9;
    do {
        u32 next;
        inner = 0;
        next = outer + 1;
        do {
            if ((func_080E9D88(outer, inner) << 24) != 0) {
                u8 *cell;
                u8 *cell2;
                func_080ECD28((u8 *)0x08277BE4, (u8 *)0x02002880, 0x40);
                cell = (u8 *)(inner * 0x270 + outer * 0x1380 + 0x02034B4C);
                if ((0x40 & *(u16 *)(cell + 4)) == 0) {
                    first = func_080ECD98(*(s16 *)(cell + 6) * 20, *(s16 *)(cell + 0x3A));
                } else {
                    first = 0xFF;
                }
                cell2 = (u8 *)(inner * 0x270 + outer * 0x1380 + 0x02034B4C);
                second = func_080ECD98(*(s16 *)(cell2 + 8) * 20, *(s16 *)(cell2 + 0x3E));
                func_080BAA40(first, work);
                func_080BAA40(second, work + 0x80);
                func_080ECD28(work - 41, (u8 *)((*(u16 *)(D_02032EBC[outer][inner] + 14) << 5) + 0x06016000), 0x40);
            }
            asm volatile("" :: "r"(inner));
            inner++;
        } while (inner <= 5);
        outer = next;
    } while (outer <= 1);
}
