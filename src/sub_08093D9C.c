#include "m2c_prelude.h"
void func_80ECD2C(s32, s32, s32);

void sub_08093D9C(u8 arg0) {
    u8 *p342D;
    register u8 *p342C asm("r3");
    s32 *p3428;
    u8 c;
    volatile u16 *dmaH;
    volatile s32 *dmaW;

    p342D = (u8 *)0x0300342D;
    if (*p342D == 0) {
        dmaH = (volatile u16 *)0x040000B0;
        dmaH[5] = 0xC5FF & dmaH[5];
        dmaH[5] = 0x7FFF & dmaH[5];
        dmaH[5];
    }
    p342C = (u8 *)0x0300342C;
    if (arg0 != 0) {
        *p342C ^= 1;
    }
    c = *p342D;
    p3428 = (s32 *)0x03003428;
    if (c == 0) {
        dmaW = (volatile s32 *)0x040000B0;
        dmaW[0] = *p3428 + *p342C * 0xA00 + 0x10;
        dmaW[1] = 0x04000020;
        dmaW[2] = 0xA6600004;
        dmaW[2];
    }
    func_80ECD2C(*p3428 + *p342C * 0xA00, 0x04000020, 0x04000004);
}
