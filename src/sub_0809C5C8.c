#include "m2c_prelude.h"

extern s32 func_08094484(void *, void *, s32, s32, s32, s32, s32, s32, s32);
extern void func_08094564(void *, s32);
extern void func_08096F3C(void);
extern void func_080972C8(void);
extern void func_0809C45C(void);
extern void func_0809C540(s32, s32);
extern void func_080ECD34(void *, void *);
extern u8 func_080ECF78(u8, u8);

extern s32 D_020216F8;
extern s32 D_020216FC;
extern s32 D_02021700;
extern u8 D_02021704;
extern u8 D_02021706;
extern u8 D_02021708;
extern u16 *D_0202170C;
extern volatile u8 D_02021710;
extern u8 D_02021711;
extern s32 D_02021714[];
extern u8 D_0202176C;

void sub_0809C5C8(u16 *list, u8 count, u8 selection, u8 offset)
{
    u8 i;
    s32 zero;
    s32 list_zero;

    func_080ECD34((void *)0x081046A8, (void *)0x06010000);
    {
        u8 *state_a;
        u8 *state_b;

        state_a = &D_02021704;
        state_b = &D_02021706;
        *state_b = 0;
        *state_a = 0;
    }

    {
        register void *resource_a asm("r0");
        register void *resource_b asm("r1");
        register s32 list_zero_seed asm("r2");

        resource_a = (void *)0x080ED8F8;
        resource_b = (void *)0x080ED92C;
        zero = 0;
        list_zero_seed = 0;
        asm volatile("" : "+r"(list_zero_seed));
        list_zero = list_zero_seed;
        D_020216F8 = func_08094484(resource_a, resource_b,
            0, 8, 0x48, 0x3F4, 0xF, 0x20, zero);
    }
    D_020216FC = func_08094484((void *)0x080ED578,
        (void *)0x080ED5A0, 0, 0xE8, 0x48, 0x3E6, 0xF, 0x20030, zero);
    D_02021700 = func_08094484((void *)0x080ED620,
        (void *)0x080ED648, 0, 0xE8, 0x90, 0x3E8, 0xF, 0x20030, zero);

    D_0202170C = list;
    D_02021710 = count;
    {
        register volatile u8 *selection_addr asm("r0");
        register u32 selection_store asm("r2");

        selection_addr = &D_02021711;
        selection_store = selection;
        *selection_addr = selection_store;
    }
    {
        register u8 *selected asm("r1");

        selected = &D_0202176C;
        *selected = list_zero;
        if (*list != 0) {
            register u8 *selected_store asm("r3");
            register s32 current asm("r2");
            s32 next;

            selected_store = selected;
            current = list_zero;
            do {
                next = current + 1;
                current = next;
                list++;
            } while (*list != 0);
            *selected_store = next;
        }
    }

    {
        u8 *selected;
        register u32 limit asm("r5");

        selected = &D_0202176C;
        limit = (u32)&D_02021710;
        *selected = func_080ECF78(*selected, *(volatile u8 *)limit);
        i = 0;
        limit = *(volatile u8 *)limit;
        asm volatile("" : "+r"(limit));
        if (i < limit) {
            do {
                D_02021714[i] = func_08094484((void *)0x081058DC,
                    (void *)0x08105918, 2, (offset + i) * 8, 0x38,
                    0x36, 0xF, 8, 0);
                i = (u8)(i + 1);
            } while (i < D_02021710);
        }
    }

    {
        s32 *items;
        u8 *selected;

        items = D_02021714;
        selected = &D_0202176C;
        func_08094564((void *)items[*selected], 1);
        *(u32 *)items[*selected] |= 0x200000;
    }

    func_08094484((void *)0x081058DC, (void *)0x08105918,
        3, 0xF0, 0, 0x36, 0xF, 8, 0);
    D_02021708 = 0;
    func_0809C540(0, 0xFF);
    func_0809C45C();
    func_080972C8();
    func_08096F3C();
}
