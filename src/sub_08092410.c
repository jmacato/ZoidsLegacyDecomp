#include "m2c_prelude.h"

extern void func_080EB084(void);
extern void func_080922A4(void);
extern void func_08093D9C(u8);
extern void func_08096080(u8);
extern void func_080D2050(u8);
extern void func_080A7860(u8);
extern void func_0809EB68(u8);
extern void func_080A8ED4(u8);
extern void func_08092348(void);
extern void func_0809290C(void);
extern void func_080952AC(void);
extern s32 func_080ECD5C(s32);
extern void func_08096DB0(u8);
extern void func_08092834(void);
extern void func_08092FA0(void);
extern void func_080923E0(void);
extern void func_080923E4(void);

void sub_08092410(void)
{
    u8 active;
    u8 *flags;

    active = *(u8 *)0x0300067C & 1;
    func_080EB084();
    func_080922A4();

    flags = (u8 *)0x03000074;
    if (*flags != 0) {
        if (*flags & 1)
            func_08093D9C(active);
        if (*(u8 *)0x03000074 & 2)
            func_08096080(active);
        if (*(u8 *)0x03000074 & 4)
            func_080D2050(active);
        if (*(u8 *)0x03000074 & 8)
            func_080A7860(active);
        if (*(u8 *)0x03000074 & 0x10)
            func_0809EB68(active);
        if (*(u8 *)0x03000074 & 0x20)
            func_080A8ED4(active);
    }

    func_08092348();
    if (*(u8 *)0x0300067C != 0)
        func_0809290C();

    if (active != 0) {
        register volatile u16 *display asm("r2") = (volatile u16 *)0x04000010;
        register s32 *state asm("r1") = (s32 *)0x03000054;
        *display++ = state[0] >> 8;
        *display++ = state[1] >> 8;
        *display++ = state[2] >> 8;
        *display++ = state[3] >> 8;
        *display++ = state[4] >> 8;
        *display++ = state[5] >> 8;
        *display++ = state[6] >> 8;
        *display++ = state[7] >> 8;

        {
            register volatile u16 *display asm("r1") = (volatile u16 *)0x04000000;
            *display = *(u16 *)0x0300004C;
            display += 0x28;
            *display++ = *(u16 *)0x0300004E;
            *display++ = *(u16 *)0x03000050;
            *display = *(u16 *)0x03000052;
        }
        func_080952AC();
        func_080ECD5C(*(s32 *)0x03000010);
    }

    func_08096DB0(active);
    if (active == 0) {
        func_08092834();
        func_08092FA0();
    }
    func_080923E0();
    func_080923E4();
}
