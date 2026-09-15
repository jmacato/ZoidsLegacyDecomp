#include "m2c_prelude.h"

extern void func_08095114(void *);
extern void func_08095208(s32, s32, s32);
extern void func_080D12A0(s32, s32);
extern void *func_080D2450();
extern void *func_080D2660();
extern void func_080D2790(s32);
extern void func_080ECD28(s32, s32, s32);
extern void func_080ECD2C(s16 *, s32, s32);

void sub_080DF320(void *arg0) {
    struct {
        s16 first;
        u16 pad;
        s32 offset;
        s32 inverse;
    } homes;
    register char *owner asm("r8") = arg0;
    register s32 *state_slot asm("r7");
    u32 state;

    {
        register s32 *fade asm("r4") = (s32 *)(owner + 0x90);
        u32 fade_value = *fade;

        if (fade_value != 0) {
            if (fade_value <= 0x1FU) {
                register s32 index asm("r6") = 0;
                register s32 *saved_fade asm("r9") = fade;
                register u16 *call_destination asm("r12") = (u16 *)0x020349B4;
                register u32 maximum = 0x1F;
                register u16 *destination asm("r10") = call_destination;

                do {
                    register s32 offset asm("r1") = index * 2;
                    register u16 *source asm("r2");
                    register u16 *address asm("r0");
                    register u32 color asm("r1");
                    register u32 red asm("r2");
                    register u32 green asm("r3");
                    register s32 inverse asm("r4");
                    register s32 alpha asm("r5");
                    register u32 work asm("r0");
                    register u16 *output asm("r5");

                    homes.offset = offset;
                    source = (u16 *)0x02034934;
                    asm volatile(
                        "add %0, %2, %3\n\t"
                        "ldrh %1, [%0]"
                        : "=r"(address), "=r"(color)
                        : "r"(offset), "r"(source));
                    red = maximum;
                    red &= color;
                    color <<= 16;
                    green = color >> 21;
                    green &= maximum;
                    color >>= 26;
                    color &= maximum;
                    inverse = maximum - red;
                    homes.inverse = inverse;
                    asm volatile(
                        "mov %0, %1\n\t"
                        "ldr %0, [%0]"
                        : "=r"(alpha)
                        : "r"(saved_fade));
                    inverse = maximum - alpha;
                    alpha = homes.inverse;
                    asm volatile("" : "+r"(alpha));
                    work = alpha;
                    work *= inverse;
                    work >>= 5;
                    red += work;
                    red = (u8)red;
                    work = maximum - green;
                    work *= inverse;
                    work >>= 5;
                    green += work;
                    green <<= 24;
                    work = maximum - color;
                    work *= inverse;
                    work >>= 5;
                    color += work;
                    color <<= 24;
                    output = (u16 *)((char *)destination + homes.offset);
                    green >>= 19;
                    red |= green;
                    color >>= 14;
                    red |= color;
                    *output = red;
                    work = index + 1;
                    index = (u8)work;
                } while ((u32)index <= 0x3F);
                func_08095208((s32)call_destination, 0x05000000, 0x80);
                {
                    register s32 *fade_view asm("r1") = saved_fade;
                    register s32 next asm("r0") = *fade_view;
                    next += 1;
                    *fade_view = next;
                }
            } else {
                *fade = 0;
            }
        }
    }
    {
        register s32 *state_seed asm("r0") = (s32 *)(owner + 0x8C);
        state = *state_seed;
        asm volatile("" : "+r"(state_seed));
        state_slot = state_seed;
    }
    switch (state) {                            /* irregular */
    case 0:
        M2C_FIELD(owner, void **, 0x98) = func_080D2450(owner, 0, 0, 0xA8, 0x48, 0x1020, 0, 0);
        func_080D2790(0);
        asm volatile("" : : "r"(state_slot));
        goto advance;
    case 1: {
        register void **child_slot asm("r6") = (void **)(owner + 0x98);
        if (*(u16 *)((char *)*child_slot + 0x14) != 0xF) {
            return;
        }
        *child_slot = func_080D2450(owner, 0, 0, 0xA0, 0x60, 0x1020, 0, 0);
        func_080D2450(owner, 0, 0, 0xC7, 0x57, 0x1020, 0, 0);
        func_080D2790(0);
        asm volatile("" : : "r"(owner));
        goto advance;
    }
    case 2: {
        register void **child_slot asm("r4") = (void **)(owner + 0x98);
        if (*(u16 *)((char *)*child_slot + 0x14) != 0x1E) {
            return;
        }
        *child_slot = func_080D2450(owner, 0, 0, 0x9F, 0x2F, 0x1020, 0, 0);
        func_080D2790(0);
        asm volatile("" : : "r"(state_slot));
        goto advance;
    }
    case 3:
        if (M2C_FIELD(M2C_FIELD(owner, void **, 0x98), u16 *, 0x14) != 0xF) {
            return;
        }
        func_080D2450(owner, 0, 0, 0x88, 0x18, 0x1020, 0, 0);
        func_080D2790(0);
        M2C_FIELD(owner, u32 *, 0x94) = 0U;
        goto advance;
    case 4: {
        register u32 *counter_seed asm("r0") = (u32 *)(owner + 0x94);
        register u32 count asm("r1");
        register u32 remainder asm("r2");
        register u32 *counter asm("r9");

        asm volatile(
            "ldr %1, [%0]\n\t"
            "mov %2, #3\n\t"
            "and %2, %2, %1\n\t"
            "mov %3, %0"
            : "+r"(counter_seed), "=r"(count), "=r"(remainder),
              "=r"(counter));
        if (remainder == 0) {
            register u32 index_work asm("r0") = count >> 2;
            register u32 index asm("r6") = (u8)index_work;
            register s32 x asm("r3");
            register const u16 *table asm("r1");
            register s32 offset asm("r4");
            register s32 y asm("r0");
            void *created;

            {
                register char *owner_view asm("r4") = owner;
                x = *(s32 *)(owner_view + 4);
            }
            table = (const u16 *)0x087A2CF4;
            offset = index * 4;
            {
                register u32 table_value asm("r0");
                asm volatile(
                    "add %0, %2, %3\n\t"
                    "ldrh %0, [%0]\n\t"
                    "add %1, %1, %0\n\t"
                    "lsl %1, %1, #16\n\t"
                    "asr %1, %1, #16"
                    : "=r"(table_value), "+r"(x)
                    : "r"(offset), "r"(table));
            }
            {
                register char *owner_view asm("r5") = owner;
                y = *(s32 *)(owner_view + 8);
            }
            table = (const u16 *)((const char *)table + 2);
            asm volatile(
                "add %0, %1, %0\n\t"
                "ldrh %0, [%0]"
                : "+r"(table)
                : "r"(offset));
            y = (s16)(y + (u32)table);
            created = func_080D2450(owner, 1, 0, x, y,
                remainder, remainder, remainder);
            {
                register char *destination asm("r1") = owner;
                destination += 0xC;
                destination += offset;
                *(void **)destination = created;
            }
            if (index == 0) {
                register s32 palette_destination asm("r5") = 0x05000000;
                register char *palette asm("r4") = (char *)0x02034934;

                func_080ECD28(palette_destination, (s32)palette, 0x20);
                {
                    register s16 *home asm("r1") = &homes.first;
                    register s32 white asm("r2") = 0x7FFF;
                    register s32 white_view asm("r0");
                    asm volatile(
                        "mov %0, %1\n\t"
                        "strh %0, [%2]"
                        : "=r"(white_view)
                        : "r"(white), "r"(home));
                }
                palette += 0x80;
                func_080ECD2C(&homes.first, (s32)palette, 0x01000040);
                func_08095208((s32)palette, palette_destination, 0x80);
                M2C_FIELD(owner, u32 *, 0x90) = 1U;
                func_080D12A0(8, 0);
                func_080D2790(1);
            }
        }
        {
            register u32 *counter_view asm("r4") = counter;
            register u32 value asm("r0") = *counter_view;
            if (value == 0x14) {
                goto advance;
            }
            value += 1;
            {
                register u32 *counter_store asm("r5") = counter;
                *counter_store = value;
            }
            return;
        }
    }
    case 5: {
        register s32 index asm("r6") = 0;
        register char *children asm("r4") = owner + 0xC;
        do {
            register s32 child_offset asm("r0") = index * 4;
            register void *child asm("r0") = *(void **)(children + child_offset);
            register s32 x_offset asm("r1");
            register s32 x asm("r3");
            register s32 y_offset asm("r2");
            register s32 y asm("r0");
            void *created;

            asm volatile(
                "mov %0, #4\n\t"
                "ldrsh %1, [%4, %0]\n\t"
                "mov %2, #6\n\t"
                "ldrsh %3, [%4, %2]"
                : "=r"(x_offset), "=r"(x), "=r"(y_offset), "=r"(y)
                : "r"(child));
            created = func_080D2660(owner, 2, 0, x, y,
                0x400, 0, 0x80, 2);
            {
                register s32 destination asm("r1");
                asm volatile(
                    "add %0, %1, #5\n\t"
                    "lsl %0, %0, #2\n\t"
                    "add %0, %2, %0\n\t"
                    "str %3, [%0]"
                    : "=r"(destination)
                    : "r"(index), "r"(children), "r"(created));
            }
            {
                register s32 next asm("r0") = index + 1;
                index = (u8)next;
            }
        } while ((u32)index <= 4);
        goto advance;
    }
advance:
        *state_slot = *state_slot + 1;
        return;
    case 6: {
        register s32 index asm("r6") = 0;
        register char *owner_view asm("r4") = owner;
        if (*(s32 *)(owner_view + 0xC) == 0) {
            register char *children asm("r1") = owner + 0xC;
            do {
                register s32 next asm("r0") = index + 1;
                index = (u8)next;
            } while ((u32)index <= 9 &&
                ({
                    register s32 child_value asm("r0") = index * 4;
                    asm volatile(
                        "add %0, %1, %0\n\t"
                        "ldr %0, [%0]"
                        : "+r"(child_value)
                        : "r"(children));
                    child_value;
                }) == 0);
        }
        if ((index == 0xA) && (M2C_FIELD(owner, u32 *, 0x90) == 0)) {
            func_08095114(owner);
        }
        return;
    }
    }
}
