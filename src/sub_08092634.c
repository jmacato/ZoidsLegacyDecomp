#include "m2c_prelude.h"

extern volatile s32 D_040000D4[];
extern s32 D_0300007C;
extern s32 D_03007FFC;
extern s32 D_03000014;
extern s32 D_03000010;
extern s32 D_03000680;
extern s32 D_0300088C;
extern s32 D_03000930;
extern s32 D_0300027C;
extern s32 D_03000054[];
extern u16 D_0300004E;
extern u16 D_03000050;
extern u16 D_03000052;
extern u8 D_0300067C;
extern u8 D_0300067D;
extern u16 D_030009EC;
extern s32 D_030009E8;
extern void func_08092D20();
extern void func_0809289C(void);
extern void func_08092558(void);
extern void func_0809256C(void);
extern void func_08092E2C(void);
extern void func_080ED098(s32);

void sub_08092634(void)
{
    volatile s32 *dma;
    u16 first;
    u32 second;
    register s32 zero5;
    register u16 *first_addr;
    s32 zero4;

    dma = D_040000D4;
    dma[0] = 0x08000104;
    dma[1] = (s32)&D_0300007C;
    dma[2] = 0x84000080;
    dma[2];
    D_03007FFC = (s32)&D_0300007C;
    dma[0] = 0x087A09D8;
    {
        register s32 target14;
        target14 = (s32)&D_03000014;
        dma[1] = target14;
    }
    dma[2] = 0x8400000E;
    dma[2];
    dma[0] = 0x080004C8;
    dma[1] = (s32)&D_03000680;
    dma[2] = 0x84000080;
    dma[2];
    dma[0] = 0x08000520;
    dma[1] = (s32)&D_0300088C;
    dma[2] = 0x84000029;
    dma[2];
    dma[0] = 0x080005AC;
    dma[1] = (s32)&D_03000930;
    dma[2] = 0x84000018;
    dma[2];
    D_03000010 = (s32)&D_03000930;

    first_addr = &first;
    asm volatile("" : "+r"(first_addr));
    zero5 = 0;
    asm volatile("" : "+r"(zero5));
    *first_addr = zero5;
    dma[0] = (s32)first_addr;
    dma[1] = 0x06000000;
    dma[2] = 0x8100C000;
    dma[2];
    first = 0x7FFF;
    dma[0] = (s32)&first;
    dma[1] = 0x05000000;
    dma[2] = 0x81000002;
    dma[2];

    zero4 = 0;
    second = zero4;
    dma[0] = (s32)&second;
    dma[1] = (s32)&D_0300027C;
    dma[2] = 0x85000100;
    dma[2];
    dma[0] = (s32)&D_0300027C;
    dma[1] = 0x07000000;
    dma[2] = 0x84000100;
    func_08092D20(dma[2]);
    func_0809289C();
    func_08092558();
    func_0809256C();
    D_03000054[7] = zero4;
    D_03000054[6] = zero4;
    D_03000054[5] = zero4;
    D_03000054[4] = zero4;
    D_03000054[3] = zero4;
    D_03000054[2] = zero4;
    D_03000054[1] = zero4;
    D_03000054[0] = zero4;
    {
        volatile u16 *p4e = &D_0300004E;
        volatile u16 *p50 = &D_03000050;
        volatile u16 *p52 = &D_03000052;
        *p52 = zero4;
        *p50 = zero4;
        *p4e = zero4;
    }
    func_08092E2C();
    func_080ED098(1);
    D_0300067C = zero5;
    D_0300067D = zero5;
    {
        volatile u16 *pec = &D_030009EC;
        volatile s32 *pe8 = &D_030009E8;
        *pe8 = zero4;
        *pec = zero4;
    }
}
