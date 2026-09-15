#include "m2c_prelude.h"
extern void func_080921D4(void);
extern void func_0809223C(u8);
extern int func_08092634();
extern void func_08092D8C();
extern void func_080962D8(void);
extern void func_08096308(int, int);
extern int func_0809669C(void);
extern void func_08096774(void);
extern void func_08096F3C(void);
extern void func_080EB748(void);
extern void func_080ECC48(void);

extern s32 D_02021690;
extern s8 D_02021694;

void sub_080920EC(void) {
    register int z4 asm("r4");
    volatile u32 *dma;
    volatile u16 *disp;
    volatile u16 *shadow;
    u32 v;

    *(volatile u16 *)0x04000204 = *(volatile u16 *)0x087A0A10;

    v = 0;
    dma = (volatile u32 *)0x040000D4;
    dma[0] = (u32)&v;
    dma[1] = 0x02000000;
    dma[2] = 0x85010000;
    dma[2];
    v = 0;
    dma[0] = (u32)&v;
    dma[1] = 0x03000000;
    dma[2] = 0x85001EC0;
    func_08092634(dma[2]);

    *(volatile u16 *)0x04000208 = 1;
    *(volatile u16 *)0x04000200 = 0x2001;
    *(volatile u16 *)0x04000004 = 8;
    shadow = (volatile u16 *)0x0300004C;
    disp = (volatile u16 *)0x04000000;
    z4 = 0;
    *disp = 0;
    *shadow = *disp;
    func_080EB748();
    func_080ECC48();
    *(volatile s8 *)0x03000074 = z4;
    func_080962D8();
    func_08096308(4, 8);
    while ((func_0809669C() << 0x18) == 0) {
        func_08096774();
        func_0809223C(*(volatile u8 *)0x03000075);
    }
    func_08096F3C();
    D_02021694 = 0;
    D_02021690 = 0;
    func_08092D8C(1, 0x0809A0B1);
    func_080921D4();
}
