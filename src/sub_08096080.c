#include "m2c_prelude.h"

extern void func_08094290(s32, void *);
extern void func_080942E0(s32);
extern void func_080ECD2C(const void *, void *, void *);
extern u8 D_02000000[];

void sub_08096080(u8 arg0)
{
    u32 enabled = arg0;
    register u32 seven asm("r2");
    register u32 old_mode asm("r3");
    register u32 eight asm("r6");
    register u32 old_bit asm("r1");
    register u32 state asm("r4");
    register u32 mode asm("r5");
    register volatile u8 *state_ptr asm("ip");
    register u32 old_state asm("r1");

    old_state = *(volatile u8 *)0x03005EF7;
    asm volatile("" : "+r"(old_state));
    seven = 7;
    old_mode = seven;
    old_mode &= old_state;
    eight = 8;
    {
        register u32 value asm("r0") = eight;

        value &= old_state;
        value <<= 24;
        old_bit = value >> 24;
    }
    {
        register volatile u8 *current asm("r0") =
            (volatile u8 *)0x03005EE8;

        state = *current;
        mode = seven;
        mode &= state;
        state_ptr = current;
    }
    asm volatile("" : "+r"(old_mode), "+r"(old_bit), "+r"(state),
                 "+r"(mode), "+r"(state_ptr));

    if (mode == 0) {
        goto mode_zero;
    }
    if (mode == 1) {
        goto mode_one;
    }
    {
        register u32 value asm("r0") = eight;

        asm volatile("" : "+r"(value));
        value &= state;
        if (value == 0) {
        register volatile u16 *dma asm("r1") =
            (volatile u16 *)0x040000B0;
        register u32 current asm("r2") = dma[5];
        register u32 mask asm("r0") = 0xC5FF;

        mask &= current;
        dma[5] = mask;
        current = dma[5];
        mask = 0x7FFF;
        mask &= current;
        dma[5] = mask;
        {
            register u32 observed asm("r0") = dma[5];

            asm volatile("" : "+r"(observed));
        }
        }
    }
    goto other_mode;

mode_zero:
    if (enabled == 0) {
        goto finish;
    }
    if (old_mode == 0) {
        goto update_state;
    }
    if (old_mode != 1 && old_bit == 8) {
        register volatile u16 *ime asm("r4") =
            (volatile u16 *)0x04000208;

        *ime = mode;
        func_080942E0(0);
        *ime = 1;
    }
    *(volatile u8 *)0x03000074 &= 0xFD;
    {
        register volatile u8 *current asm("r0") =
            (volatile u8 *)0x03005EE8;

        asm volatile("" : "+r"(current));
        state_ptr = current;
    }
    goto update_state;

mode_one:
    if (enabled == 0) {
        goto finish;
    }
    if (old_mode != 1 && old_bit == 8) {
        register volatile u16 *ime asm("r4") =
            (volatile u16 *)0x04000208;

        *ime = 0;
        func_080942E0(0);
        *ime = mode;
    }
    {
        register volatile u16 *display asm("r1") =
            (volatile u16 *)0x04000040;

        *display = *(volatile u16 *)0x03005EFC;
        display += 2;
        *display = *(volatile u16 *)0x03005EFE;
        display -= 1;
        *display = *(volatile u16 *)0x03005F00;
        display += 2;
        *display = *(volatile u16 *)0x03005F02;
    }
    {
        register volatile u8 *current asm("r1") =
            (volatile u8 *)0x03005EE8;

        asm volatile("" : "+r"(current));
        state_ptr = current;
    }
    goto update_state;

other_mode:
    if (enabled != 0) {
        if (old_mode <= 1 &&
            (8 & *(volatile u8 *)0x03005EE8) != 0) {
            register volatile u16 *ime asm("r5") =
                (volatile u16 *)0x04000208;
            register void *buffer asm("r4");

            *ime = 0;
            buffer = (void *)0x03005F14;
            func_08094290(0, buffer);
            func_080ECD2C((const void *)0x080006A8, buffer,
                          (void *)0x04000017);
            *ime = 1;
        }
        *(volatile u8 *)0x03005F12 ^= 1;
        {
            register volatile u8 *current asm("r2") =
                (volatile u8 *)0x03005EE8;

            asm volatile("" : "+r"(current));
            state_ptr = current;
        }
    }
    {
        register volatile u8 *page_ptr asm("r3");
        register u32 active asm("r0");
        register u32 current asm("r1");

        current = *state_ptr;
        asm volatile("" : "+r"(current));
        active = 8;
        active &= current;
        page_ptr = (volatile u8 *)0x03005F12;
        asm volatile("" : "+r"(page_ptr));
        if (active == 0) {
            register volatile u32 *dma asm("r2") =
                (volatile u32 *)0x040000B0;
            u32 page = *page_ptr;

            dma[0] = page * 0x500 + 0x02000008;
            dma[1] = 0x04000040;
            dma[2] = 0xA6600002;
            (void)dma[2];
        }
        {
            register u32 page asm("r1");
            register u32 offset asm("r0");

            asm volatile("ldrb %0, [%1]"
                         : "=r"(page)
                         : "r"(page_ptr));
            offset = page << 2;
            offset += page;
            offset <<= 8;
            {
                register const u32 *base asm("r1") =
                    (const u32 *)D_02000000;

                asm volatile("" : "+r"(base));
                offset += (u32)base;
            }
            {
                register const u32 *source asm("r0") =
                    (const u32 *)offset;
                register volatile u32 *first asm("r2") =
                    (volatile u32 *)0x04000040;
                register u32 word asm("r1") = source[0];

                *first = word;
                {
                    register volatile u32 *second asm("r1") =
                        (volatile u32 *)0x04000044;

                    *second = source[1];
                }
            }
        }
    }

update_state:
    if (enabled != 0) {
        register volatile u8 *previous asm("r1") =
            (volatile u8 *)0x03005EF7;
        register volatile u8 *current asm("r2") = state_ptr;
        register u32 value asm("r0") = *current;

        *previous = value;
    }

finish:
    {
        register volatile u8 *current asm("r1") = state_ptr;
        register u32 current_value asm("r0") = *current;

        if (current_value != 0 && enabled != 0) {
            register volatile u16 *blend asm("r2");
            register u32 value asm("r1");
            register u32 mask asm("r0");

            *(volatile u16 *)0x04000048 =
                *(volatile u16 *)0x03005EF8;
            blend = (volatile u16 *)0x0400004A;
            value = *blend;
            mask = 0xFF00;
            mask &= value;
            mask |= *(volatile u16 *)0x03005EFA;
            *blend = mask;
        }
    }
}
