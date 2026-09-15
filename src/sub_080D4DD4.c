#include "m2c_prelude.h"

extern void func_08094554();
extern void func_08095114(void *);
extern void func_080D12A0(s32, s32);
extern void *func_080D2450();
extern void *func_080D2660();
extern void func_080D2790(s32);
extern u32 func_080ECD5C(u32);
extern s32 func_080ECD98(s32, s32);
extern u32 D_03000010;

void sub_080D4DD4(void *arg0)
{
    register char *owner asm("r8") = arg0;
    register s32 *state_slot asm("r6") = (s32 *)(owner + 0x8C);
    register u32 state asm("r0") = *state_slot;
    s32 *saved_state;
    char *children;
    u8 index;

    asm volatile("" : "=m"(saved_state), "=m"(children));

    if (state <= 7) {
        register s32 *x_ptr asm("r1");
        register s16 *y_ptr asm("r2");
        register s32 *x_slot asm("r9");
        register s16 *y_slot asm("sl");

        x_ptr = (s32 *)0x90;
        asm volatile("add %0, %1, %0" : "+r"(x_ptr) : "r"(owner));
        x_slot = x_ptr;
        y_ptr = (s16 *)0x94;
        asm volatile("add %0, %1, %0" : "+r"(y_ptr) : "r"(owner));
        y_slot = y_ptr;

        if (state == 0) {
            register s32 bias asm("r4");
            register s32 x_value asm("r3");
            void *created;

            x_value = *x_ptr;
            bias = -0x100;
            asm volatile("" : "+r"(bias));
            created = func_080D2450(owner, 1, 0,
                (s16)(x_value + bias), (s32)*y_ptr,
                0x10, 0x080D2529, 1);
            {
                register char *owner_view asm("r2") = owner;
                *(void **)(owner_view + 0xC) = created;
            }
            *(s32 *)((char *)created + 0x28) = 0x20;
            func_080D2790(0);
        }
        {
            register s32 *x_view asm("r4") = x_slot;
            register s16 *y_view asm("r1");
            register s32 constant asm("r0");
            register s32 x_value asm("r3");
            register s32 y_offset asm("r2");
            register s32 y_value asm("r0");
            register s32 next asm("r2");
            register s32 offset asm("r3");
            register char *slot asm("r1");
            void *created;

            x_value = *x_view;
            constant = 0xFF00;
            asm volatile("" : "+r"(constant));
            x_value += constant;
            x_value += *state_slot << 5;
            x_value <<= 16;
            x_value >>= 16;
            y_view = y_slot;
            asm volatile("" : "+r"(y_view));
            y_offset = 0;
            y_value = *(s16 *)((char *)y_view + y_offset);
            created = func_080D2450(owner, 0, 0,
                x_value, y_value, 0x400, 0, 1);
            next = *state_slot + 1;
            offset = next << 2;
            slot = owner + 0xC;
            slot += offset;
            *(void **)slot = created;
            *state_slot = next;
        }
        return;
    }

    if (state == 8) {
        register char *x_ptr asm("r5") = owner + 0x90;
        register char *y_ptr asm("r4");
        register s32 x_offset asm("r4");
        register s32 x_value asm("r3");
        register s32 y_offset asm("r1");
        register s32 y_value asm("r0");
        void *created;

        asm volatile(
            "mov %0, #0\n\t"
            "ldrsh %1, [%2, %0]"
            : "=r"(x_offset), "=r"(x_value)
            : "r"(x_ptr));
        y_ptr = owner;
        y_ptr += 0x94;
        y_offset = 0;
        y_value = *(s16 *)(y_ptr + y_offset);
        created = func_080D2450(owner, 2, 0,
            x_value, y_value, 0x400, 0, 0);
        {
            register char *owner_view asm("r2") = owner;

            *(void **)(owner_view + 0x30) = created;
        }
        index = 0;
        saved_state = state_slot;
        {
            register char *saved_x asm("r9") = x_ptr;
            register char *saved_y asm("sl") = y_ptr;
            register char *child_base asm("r2") = owner;

            child_base += 0xC;
            children = child_base;
            {
                register u32 *rng asm("r6") = &D_03000010;

                do {
                    register s32 random asm("r4");
                    register s32 angle asm("r5");
                    register s32 perturb asm("r0");
                    register s32 priority_base asm("r4");
                    register s32 child_offset asm("r1");
                    register char *children_view asm("r4");
                    s32 priority;
                    void *spawned;

                    random = func_080ECD5C(*rng);
                    angle = func_080ECD98(index << 6, 7);
                    perturb = (u32)(random * 9) >> 15;
                    perturb -= 0x24;
                    angle += perturb;
                    priority = (u32)(func_080ECD5C(*rng) * 0x201) >> 15;
                    priority_base = 0x200;
                    asm volatile("" : "+r"(priority_base));
                    priority += priority_base;
                    {
                        register char *x_view asm("r0") = saved_x;
                        register s32 x_offset asm("r2") = 0;
                        register s32 x_value asm("r3");

                        x_value = *(s16 *)(x_view + x_offset);
                        {
                            register char *y_view asm("r4");
                            register s32 y_offset asm("r2");
                            register s32 y_value asm("r0");

                            asm volatile(
                                "mov %0, %3\n\t"
                                "mov %1, #0\n\t"
                                "ldrsh %2, [%0, %1]"
                                : "=r"(y_view), "=r"(y_offset),
                                  "=r"(y_value)
                                : "r"(saved_y));
                            spawned = func_080D2660(owner, 4, 0,
                                x_value, y_value, 0x20, angle, priority, 0);
                        }
                    }
                    child_offset = index;
                    child_offset += 10;
                    child_offset <<= 2;
                    children_view = children;
                    asm volatile("add %0, %1, %0"
                                 : "+r"(child_offset)
                                 : "r"(children_view));
                    *(void **)child_offset = spawned;
                    index = (u8)(index + 1);
                } while (index <= 7);
            }
        }
        func_080D12A0(6, 0);
        func_080D2790(1);
        {
            register s32 *slot asm("r1") = saved_state;
            *slot = *slot + 1;
        }
        return;
    }

    if (state == 9) {
        index = 0;
        {
            register char *owner_view asm("r2") = owner;

            if (*(s32 *)(owner_view + 0xC) == 0) {
                register char *scan_base asm("r1") = owner;

                scan_base += 0xC;
                do {
                    index = (u8)(index + 1);
                } while (index <= 0x11 &&
                    *(s32 *)(scan_base + (index << 2)) == 0);
            }
        }
        if (index != 0x12) {
            return;
        }

        index = 0;
        {
            void *created;
            register char *x_ptr asm("r9");
            register char *y_ptr asm("sl");
            register char *child_base asm("r2");

            {
                register char *state_view asm("r4") = owner;
                state_view += 0x8C;
                saved_state = (s32 *)state_view;
            }
            {
                register char *x_init asm("r0") = (char *)0x90;
                asm volatile("add %0, %1, %0"
                             : "+r"(x_init) : "r"(owner));
                x_ptr = x_init;
            }
            {
                register char *y_init asm("r1") = (char *)0x94;
                asm volatile("add %0, %1, %0"
                             : "+r"(y_init) : "r"(owner));
                y_ptr = y_init;
            }
            child_base = owner;
            child_base += 0xC;
            children = child_base;

            do {
                register s32 random asm("r4");
                register s32 angle asm("r5");
                register s32 child_offset asm("r6");
                register char *children_view asm("r4");
                register s32 *child asm("r6");
                register s32 perturb asm("r0");
                register s32 priority_base asm("r4");
                s32 priority;

                child_offset = index << 2;
                children_view = children;
                asm volatile("add %0, %1, %0"
                             : "+r"(child_offset)
                             : "r"(children_view));
                child = (s32 *)child_offset;
                func_08094554(*child);
                {
                    register u32 *rng_view asm("r1") = &D_03000010;
                    random = func_080ECD5C(*rng_view);
                }
                angle = func_080ECD98(index << 4, 7);
                perturb = (u32)(random * 5) >> 15;
                perturb += 0x76;
                angle += perturb;
                {
                    register u32 *rng_view asm("r2") = &D_03000010;
                    priority = (u32)(func_080ECD5C(*rng_view) * 0x401) >> 15;
                }
                priority_base = 0x200;
                asm volatile("" : "+r"(priority_base));
                priority += priority_base;
                {
                    register volatile s32 *outgoing asm("sp");
                    register s32 x_value asm("r3");

                    {
                        register char *x_view asm("r0") = x_ptr;
                        register s32 x_offset asm("r2") = 0;

                        x_value = *(s16 *)(x_view + x_offset);
                        asm volatile("" : "+r"(x_value));
                    }
                    {
                        register char *y_view asm("r4");
                        register s32 y_offset asm("r2");
                        register s32 y_value asm("r0");

                        asm volatile(
                            "mov %0, %3\n\t"
                            "mov %1, #0\n\t"
                            "ldrsh %2, [%0, %1]"
                            : "=r"(y_view), "=r"(y_offset),
                              "=r"(y_value)
                            : "r"(y_ptr));
                        outgoing[0] = y_value;
                    }
                    {
                        register s32 zero asm("r4") = 0;

                        outgoing[1] = zero;
                        outgoing[2] = angle;
                        outgoing[3] = priority;
                        outgoing[4] = zero;
                        {
                            register char *call0 asm("r0") = owner;
                            register s32 call1 asm("r1") = 3;
                            register s32 call2 asm("r2") = 0;

                            asm volatile("" : "+r"(call0), "+r"(call1),
                                               "+r"(call2), "+r"(x_value));
                            *child = (s32)func_080D2660(
                                call0, call1, call2, x_value);
                        }
                    }
                }
                index = (u8)(index + 1);
            } while (index <= 7);

            {
                register char *x_view asm("r0");
                register s32 x_offset asm("r1");
                register s32 x_value asm("r3");
                register char *y_view asm("r2");
                register s32 y_offset asm("r4");
                register s32 y_value asm("r0");

                asm volatile(
                    "mov %0, %3\n\t"
                    "mov %1, #0\n\t"
                    "ldrsh %2, [%0, %1]"
                    : "=r"(x_view), "=r"(x_offset), "=r"(x_value)
                    : "r"(x_ptr));
                asm volatile(
                    "mov %0, %3\n\t"
                    "mov %1, #0\n\t"
                    "ldrsh %2, [%0, %1]"
                    : "=r"(y_view), "=r"(y_offset), "=r"(y_value)
                    : "r"(y_ptr));
                created = func_080D2450(owner, 2, 1,
                    x_value, y_value, 0x400, 0, 0);
            }
            {
                register char *owner_view asm("r1") = owner;

                asm volatile("" : "+r"(owner_view));
                *(void **)(owner_view + 0x2C) = created;
            }
            index = 0;
            {
                register u32 *rng asm("r6") = &D_03000010;

                do {
                    register s32 random asm("r4");
                    register s32 angle asm("r5");
                    register s32 perturb asm("r0");
                    register s32 priority_base asm("r2");
                    register s32 child_offset asm("r1");
                    register char *children_view asm("r2");
                    s32 priority;
                    void *spawned;

                    random = func_080ECD5C(*rng);
                    angle = func_080ECD98(index << 5, 7);
                    perturb = (u32)(random * 9) >> 15;
                    perturb += 0x6C;
                    angle += perturb;
                    priority = (u32)(func_080ECD5C(*rng) * 0x201) >> 15;
                    priority_base = 0x200;
                    asm volatile("" : "+r"(priority_base));
                    priority += priority_base;
                    {
                        register char *x_view asm("r4");
                        register s32 x_offset asm("r0");
                        register s32 x_value asm("r3");
                        register char *y_view asm("r2");
                        register s32 y_offset asm("r4");
                        register s32 y_value asm("r0");

                        asm volatile(
                            "mov %0, %3\n\t"
                            "mov %1, #0\n\t"
                            "ldrsh %2, [%0, %1]"
                            : "=r"(x_view), "=r"(x_offset),
                              "=r"(x_value)
                            : "r"(x_ptr));
                        asm volatile(
                            "mov %0, %3\n\t"
                            "mov %1, #0\n\t"
                            "ldrsh %2, [%0, %1]"
                            : "=r"(y_view), "=r"(y_offset),
                              "=r"(y_value)
                            : "r"(y_ptr));
                        spawned = func_080D2660(owner, 4, 0,
                            x_value, y_value,
                            0x20, angle, priority, 0);
                    }
                    child_offset = index;
                    child_offset += 9;
                    child_offset <<= 2;
                    children_view = children;
                    asm volatile("add %0, %1, %0"
                                 : "+r"(child_offset)
                                 : "r"(children_view));
                    *(void **)child_offset = spawned;
                    index = (u8)(index + 1);
                } while (index <= 7);
            }
            func_080D12A0(6, 0);
            func_080D2790(2);
            {
                register s32 *slot asm("r4") = saved_state;
                *slot = *slot + 1;
            }
        }
        return;
    }

    {
        register char *scan_base asm("r1");

        index = 0;
        scan_base = owner;
        if (*(s32 *)(scan_base + 0xC) == 0) {
            scan_base += 0xC;
            do {
                index = (u8)(index + 1);
            } while (index <= 0x11 &&
                *(s32 *)(scan_base + (index << 2)) == 0);
        }
        if (index == 0x12) {
            func_08095114(owner);
        }
    }
}
