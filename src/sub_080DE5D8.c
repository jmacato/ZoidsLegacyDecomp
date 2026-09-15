#include "m2c_prelude.h"

void func_08095114(void *);
void func_08095208(s32, s32, s32);
void *func_080D2450(void *, s32, s32, s32, s32, s32, void *, void *);
void *func_080D2660(void *, s32, s32, s32, s32, s32, s32, s32, s32);
void func_080D2790(s32);
void func_080ECD28(void *, void *, u32);
void func_080ECD2C(void *, void *, u32);

#define BLEND_COMPONENT(component, fade) \
    ((component) + (((31 - (component)) * (fade)) >> 5))

typedef struct {
    u8 pad0[4];
    s16 x;
    u8 pad6[2];
    s16 y;
} OwnerCoordinates;

void sub_080DE5D8(void *arg0)
{
    u8 *owner = arg0;
    u16 local_colors[2];
    u32 state = *(u32 *)(owner + 0x8C);

    switch (state) {
    case 0:
        {
            s32 x = *(s16 *)(owner + 4);
            s32 y = *(s16 *)(owner + 8);
            *(void **)(owner + 0xC) = func_080D2660(
                owner, 3, 0, x, y, 0x400, 0xC0, 0x49, 0);
        }
        func_080D2790(0);
        goto increment_state;

    case 1:
        {
            register void *zero asm("r5") = *(void **)(owner + 0xC);
            register u32 x_offset asm("r2");
            register s32 x asm("r3");
            register s32 y asm("r0");
            if (zero != 0) {
                return;
            }
            x_offset = 4;
            x = *(s16 *)(owner + x_offset);
            y = (s16)(*(s32 *)(owner + 8) - 0x18);
            *(void **)(owner + 0xC) = func_080D2450(
                owner, 2, 0, x, y, 0x400, zero, zero);
            *(void **)(owner + 0x10) = func_080D2450(
                owner, 1, 0, (s16)(*(s32 *)(owner + 4) + 0x80),
                (s16)(*(s32 *)(owner + 8) - 0x18), 0x400, zero, zero);
            func_080D2790(1);
            __asm__("" : "+r"(owner));
            goto increment_state;
        }

    case 2:
        {
            register void *zero asm("r4") = *(void **)(owner + 0x10);
            register u32 *timer asm("r5");
            if (zero != 0) {
                return;
            }
            timer = (u32 *)(owner + 0x90);
            ++*timer;
            if (*timer != 30) {
                return;
            }
            *(void **)(owner + 0x10) = func_080D2450(
                owner, 0, 0, 0x70, -0x20, 0x400, zero, zero);
            *timer = (u32)zero;
            func_080D2790(1);
            __asm__("" : "+r"(owner));
            goto increment_state;
        }

    case 3:
        {
            register void *zero asm("r2") = *(void **)(owner + 0x10);
            register u32 *timer asm("r1");
            register s32 x asm("r3");
            register s32 y asm("r0");
            if (zero != 0) {
                return;
            }
            timer = (u32 *)(owner + 0x90);
            ++*timer;
            if (*timer != 30) {
                return;
            }
            x = *(s16 *)(owner + 4);
            y = *(s16 *)(owner + 8);
            *(volatile u32 *)(owner + 0x10) = (u32)func_080D2450(
                owner, 4, 0, x, y, 0x400, zero, zero);
            func_080D2790(1);
            goto increment_state;
        }

    case 4:
        if (*(u16 *)(*(u8 **)(owner + 0x10) + 0x14) != 4) {
            return;
        }
        {
            register void *palette0 asm("sl");
            register void *palette1 asm("r9");
            register void *copy0 asm("r5");
            register void *copy1 asm("r4");
            register u32 white asm("r6");
            register u32 fill asm("r8");
            register u16 *color asm("r0");
            register u32 palette0_load asm("r2");
            register void *palette1_load asm("r6");
            register u32 white_load asm("r1");
            register u32 fill_load asm("r2");

            palette0_load = 0x05000000;
            palette0 = (void *)palette0_load;
            copy0 = (void *)0x02034934;
            func_080ECD28(palette0, copy0, 0x20);
            palette1_load = (void *)0x05000200;
            __asm__("" : "+r"(palette1_load));
            palette1 = palette1_load;
            copy1 = (void *)0x02034A34;
            func_080ECD28(palette1, copy1, 0x18);
            color = &local_colors[0];
            white_load = 0x7FFF;
            __asm__("" : "+r"(white_load));
            white = white_load;
            *color = white;
            copy0 += 0x80;
            fill_load = 0x01000040;
            fill = fill_load;
            func_080ECD2C(color, copy0, fill_load);
            color = (u16 *)((u8 *)local_colors + 2);
            *color = white;
            copy1 += 0x60;
            func_080ECD2C(color, copy1, fill);
            func_08095208(copy0, palette0, 0x80);
            func_08095208(copy1, palette1, 0x60);
        }
        {
            register u32 x_offset asm("r6") = 4;
            register s32 x asm("r3") = *(s16 *)(owner + x_offset);
            register u32 y_offset asm("r1") = 8;
            register s32 y asm("r0") = *(s16 *)(owner + y_offset);
            *(void **)(owner + 0x14) = func_080D2450(
                owner, 5, 0, x, y, 0x400, 0, 0);
            *(u32 *)(owner + 0x90) = 0;
        }
        func_080D2790(2);
        goto increment_state;

    case 5:
        {
            register u32 index asm("r9");
            register u32 *timer asm("sl");
            u32 mask;
            register u16 *loop_base asm("ip");

            {
                register u32 zero asm("r2") = 0;
                __asm__("" : "+r"(zero));
                index = zero;
            }
            {
                register u32 timer_init asm("r6") = 0x90;
                __asm__("" : "+r"(timer_init));
                timer_init += (u32)owner;
                timer = (u32 *)timer_init;
            }
            {
                register u32 mask_init asm("r0") = 0x1F;
                __asm__("" : "+r"(mask_init));
                mask = mask_init;
            }
            {
                register u16 *loop_base_init asm("r1") = (u16 *)0x020349B4;
                __asm__("" : "+r"(loop_base_init));
                loop_base = loop_base_init;
            }
first_loop:
            {
                register u32 offset asm("r3");
                register u32 color asm("r0");
                register u32 red asm("r4");
                register u32 green asm("r6");
                register u32 blue asm("r5");
                register u32 transition asm("r2");
                register u32 work0 asm("r0");
                register u32 work1 asm("r1");
                register u32 index_view asm("r2");

                index_view = index;
                offset = index_view << 1;
                color = *(u16 *)(0x02034934 + offset);
                red = mask;
                red &= color;
                color <<= 16;
                green = color >> 21;
                green &= mask;
                blue = color >> 26;
                blue &= mask;
                work0 = mask;
                work0 -= red;
                transition = *timer;
                transition = mask - transition;
                work0 *= transition;
                work0 >>= 5;
                work0 = red + work0;
                work0 <<= 24;
                red = work0 >> 24;
                work0 = mask;
                work0 -= green;
                __asm__ volatile("" : "+r"(work0));
                work1 = work0;
                work1 *= transition;
                work1 >>= 5;
                work1 = green + work1;
                work1 <<= 24;
                work0 = mask;
                work0 -= blue;
                work0 *= transition;
                work0 >>= 5;
                work0 = blue + work0;
                work0 <<= 24;
                offset += (u32)loop_base;
                work1 >>= 19;
                red |= work1;
                work0 >>= 14;
                red |= work0;
                *(u16 *)offset = red;
            }
            index = (u8)(index + 1);
            if (index <= 0x3F) {
                goto first_loop;
            }

            {
                register u32 zero asm("r0") = 0;
                register u16 *loop_base_init asm("r1") = (u16 *)0x02034A34;
                register u32 second_mask asm("r2") = 0x1F;
                index = zero;
                loop_base = loop_base_init;
                mask = second_mask;
            }
second_loop:
            {
                register u32 offset asm("r3");
                register u32 color asm("r0");
                register u32 red asm("r4");
                register u32 green asm("r6");
                register u32 blue asm("r5");
                register u32 transition asm("r2");
                register u32 work0 asm("r0");
                register u32 work1 asm("r1");
                register u32 index_view asm("r6");
                register u16 *base_view asm("r1");

                index_view = index;
                offset = index_view << 1;
                base_view = loop_base;
                color = *(u16 *)(offset + (u32)base_view);
                red = mask;
                red &= color;
                color <<= 16;
                green = color >> 21;
                green &= mask;
                blue = color >> 26;
                blue &= mask;
                work0 = mask;
                work0 -= red;
                transition = *timer;
                transition = mask - transition;
                work0 *= transition;
                work0 >>= 5;
                work0 = red + work0;
                work0 <<= 24;
                red = work0 >> 24;
                work0 = mask;
                work0 -= green;
                __asm__ volatile("" : "+r"(work0));
                work1 = work0;
                work1 *= transition;
                work1 >>= 5;
                work1 = green + work1;
                work1 <<= 24;
                work0 = mask;
                work0 -= blue;
                work0 *= transition;
                work0 >>= 5;
                work0 = blue + work0;
                work0 <<= 24;
                {
                    register u32 output_base asm("r2") = 0x02034A94;
                    offset += output_base;
                }
                work1 >>= 19;
                red |= work1;
                work0 >>= 14;
                red |= work0;
                *(u16 *)offset = red;
            }
            index = (u8)(index + 1);
            if (index <= 0x2F) {
                goto second_loop;
            }

            {
                register s32 dma_destination asm("r1") = 0x05000000;
                func_08095208(0x020349B4, dma_destination, 0x80);
            }
            func_08095208((void *)0x02034A94, (void *)0x05000200, 0x60);
            {
                register u32 *timer_copy asm("r6") = timer;
                register u32 next asm("r0") = *timer_copy + 1;
                *timer_copy = next;
                if (next != 32) {
                    return;
                }
            }
        }

increment_state:
        ++*(u32 *)(owner + 0x8C);
        return;

    case 6:
        if (*(void **)(owner + 0xC) == 0
            && *(void **)(owner + 0x10) == 0
            && *(void **)(owner + 0x14) == 0) {
            func_08095114(owner);
        }
        return;
    }
    return;
}
#undef BLEND_COMPONENT
