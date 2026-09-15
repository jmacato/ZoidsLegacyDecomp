#include "m2c_prelude.h"

extern void func_08095114(void *);
extern void func_08095208(s32, s32, s32);
extern s32 func_0809669C(void);
extern void func_080D2660(void *, s32, s32, s32, s32, s32, s32, s32, s32);
extern s32 func_080ECD5C(s32);

void sub_080DE9AC(void *arg0) {
    u8 *owner;
    register s32 *rng asm("r6");
    register s32 x asm("r5");
    register s32 y asm("r4");
    register u32 *state asm("r8");
    register u32 index asm("ip");
    u32 mask;
    register u16 *dma_source asm("sl");
    register u16 *loop_base asm("r9");

    owner = arg0;
    rng = (s32 *)0x03000010;
    {
        register s32 random asm("r0");
        register u32 delta asm("r1");

        random = func_080ECD5C(*rng);
        x = *(s32 *)(owner + 4);
        delta = random << 6;
        delta += random;
        delta >>= 15;
        x += delta;
        x -= 0x20;
        x <<= 16;
        x >>= 16;

        random = func_080ECD5C(*rng);
        y = *(s32 *)(owner + 8);
        delta = random << 6;
        delta += random;
        delta >>= 15;
        y += delta;
        y -= 0x20;
        y <<= 16;
        y >>= 16;

        random = func_080ECD5C(*rng);
        delta = random << 8;
        delta += random;
        delta >>= 15;
        delta += 0x200;
        func_080D2660(owner, 0, 0, x, y, 0, 0, delta, 0);
    }
    {
        register u32 *initial_state asm("r4");

        initial_state = (u32 *)(owner + 0x8C);
        if (*initial_state == 0) {
            if ((func_0809669C() << 24) != 0) {
                *initial_state = 1;
            }
            if (*initial_state == 0) {
                goto done;
            }
        }
    }
    {
        register u32 *state_seed asm("r0");
        register u32 state_value asm("r1");

        state_seed = (u32 *)(owner + 0x8C);
        state_value = *state_seed;
        state = state_seed;
        if (state_value > 0x1F) {
            goto destroy;
        }
    }

    index = 0;
    {
        register u16 *dma_source_init asm("r2") = (u16 *)0x020349B4;
        dma_source = dma_source_init;
    }
    mask = 0x1F;
    loop_base = dma_source;
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
        register u32 index_view asm("r0");

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
        transition = *state;
        transition = mask - transition;
        work0 *= transition;
        work0 >>= 5;
        work0 = red + work0;
        work0 <<= 24;
        red = work0 >> 24;

        work0 = mask;
        work0 -= green;
        asm volatile("" : "+r"(work0));
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
        register u32 zero asm("r2") = 0;
        register u16 *loop_base_init asm("r0") = (u16 *)0x02034A34;

        index = zero;
        loop_base = loop_base_init;
    }
    mask = 0x1F;
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
        register u32 index_view asm("r1");
        register u16 *base_view asm("r2");

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
        transition = *state;
        transition = mask - transition;
        work0 *= transition;
        work0 >>= 5;
        work0 = red + work0;
        work0 <<= 24;
        red = work0 >> 24;

        work0 = mask;
        work0 -= green;
        asm volatile("" : "+r"(work0));
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

    func_08095208((s32)dma_source, 0x05000000, 0x80);
    func_08095208(0x02034A94, 0x05000200, 0x60);
    {
        register u32 *state_view asm("r1") = state;
        *state_view = *state_view + 1;
    }
    goto done;

destroy:
    func_08095114(owner);
done:
    return;
}
