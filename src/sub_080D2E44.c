#include "m2c_prelude.h"

extern void func_08095114(void *);
extern void func_080D12A0(s32, s32);
extern void *func_080D2450();
extern void *func_080D2660();
extern void func_080D2790(s32);
extern u32 func_080ECD5C(u32);
extern u32 D_03000010;

void sub_080D2E44(void *arg0) {
    register char *owner asm("r6") = arg0;
    register s32 *state_slot asm("sl") = (s32 *)(owner + 0x8C);
    u8 index;
    register u32 state asm("r0") = *state_slot;

    switch (state) {
    case 0: {
        register char *x_ptr asm("r0") = owner + 0x90;
        register s32 x_value asm("r3");
        register s32 y_offset asm("r2");
        void *created;

        x_value = *(s32 *)x_ptr;
        asm volatile("" : "+r"(x_ptr));
        x_value = (s16)(x_value - 0x100);
        x_ptr += 4;
        asm volatile(
            "mov %1, #0\n\t"
            "ldrsh %0, [%0, %1]"
            : "+r"(x_ptr), "=r"(y_offset));
        created = func_080D2450(owner, 0, 0, x_value, (s32)x_ptr,
            0, 0x080D2529, 1);
        *(void **)(owner + 0xC) = created;
        *(s32 *)((char *)created + 0x28) = 0x10;
        func_080D2790(0);
        {
            register s32 *slot asm("r4") = state_slot;
            *slot = *slot + 1;
        }
        break;
    }
    case 1: {
        register char *x_ptr asm("r9");
        register char *y_ptr asm("r5");
        register s32 *children asm("r9");
        register u32 *rng asm("r5");
        register void *guard asm("r7");
        s32 * volatile saved_state;
        volatile s32 angle_slot;

        guard = *(void **)(owner + 0xC);
        if (guard != 0) {
            break;
        }
        {
            register s32 x_offset asm("r1");
            register s32 x_value asm("r3");
            register char *x_view asm("r0") = (char *)0x90;
            register s32 y_offset asm("r2");
            register s32 y_value asm("r0");

            asm volatile("add %0, %0, %1"
                         : "+r"(x_view) : "r"(owner));
            x_ptr = x_view;
            asm volatile(
                "mov %0, #0\n\t"
                "ldrsh %1, [%2, %0]"
                : "=r"(x_offset), "=r"(x_value)
                : "r"(x_view));
            y_ptr = owner + 0x94;
            asm volatile(
                "mov %0, #0\n\t"
                "ldrsh %1, [%2, %0]"
                : "=r"(y_offset), "=r"(y_value)
                : "r"(y_ptr));
            {
                register volatile s32 *outgoing asm("sp");
                register char *call0 asm("r0");
                register s32 call1 asm("r1");
                register s32 call2 asm("r2");

                outgoing[0] = y_value;
                outgoing[1] = (s32)guard;
                outgoing[2] = (s32)guard;
                outgoing[3] = (s32)guard;
                call0 = owner;
                call1 = 1;
                asm volatile("mov %0, #0" : "=r"(call2));
                *(void **)(owner + 0xC) = func_080D2450(
                    call0, call1, call2, x_value);
            }
        }
        {
            register u32 *rng_view asm("r4") = &D_03000010;
            register s32 angle asm("r4");
            register s32 x_value asm("r3");
            register s32 x_offset asm("r1");
            register char *x_view asm("r0");
            register s32 y_value asm("r0");
            register s32 y_offset asm("r2");
            void *spawned;

            angle = (u32)(func_080ECD5C(*rng_view) * 0x41) >> 15;
            angle -= 0x20;
            asm volatile(
                "mov %0, %3\n\t"
                "mov %1, #0\n\t"
                "ldrsh %2, [%0, %1]"
                : "=r"(x_view), "=r"(x_offset), "=r"(x_value)
                : "r"(x_ptr));
            asm volatile(
                "mov %0, #0\n\t"
                "ldrsh %1, [%2, %0]"
                : "=r"(y_offset), "=r"(y_value)
                : "r"(y_ptr));
            {
                register volatile s32 *outgoing asm("sp");
                register char *call0 asm("r0");
                register s32 call1 asm("r1");
                register s32 call2 asm("r2");

                outgoing[0] = y_value;
                outgoing[1] = 0x100;
                outgoing[2] = angle;
                outgoing[3] = 0x800;
                outgoing[4] = (s32)guard;
                call0 = owner;
                call1 = 2;
                asm volatile("mov %0, #0" : "=r"(call2));
                spawned = func_080D2660(call0, call1, call2, x_value);
            }
            *(void **)(owner + 0x10) = spawned;
            *(s8 *)((char *)spawned + 0x11) = angle;
        }

        index = 2;
        {
            register s32 *saved_state_view asm("r4") = state_slot;
            saved_state = saved_state_view;
        }
        {
            register char *saved_x asm("r8") = x_ptr;
            register char *saved_y asm("sl") = y_ptr;

            {
                register s32 *children_init asm("r0") = (s32 *)0xC;
                asm volatile("" : "+r"(children_init));
                children_init = (s32 *)((char *)children_init + (s32)owner);
                children = children_init;
            }
            rng = &D_03000010;
            do {
                register s32 random asm("r0");
                register s32 angle asm("r4");
                register s32 priority asm("r1");
                register s32 priority_base asm("r2");
                register char *x_view asm("r4");
                register s32 x_offset asm("r0");
                register s32 x_value asm("r3");
                register char *y_view asm("r2");
                register s32 y_offset asm("r4");
                register s32 y_value asm("r0");
                register s32 child_offset asm("r1");
                void *spawned;

                random = func_080ECD5C(*rng);
                angle = random * 3;
                angle <<= 4;
                angle += random;
                angle = (u32)angle >> 15;
                angle += 0x80;
                angle_slot = angle;
                priority = (u32)(func_080ECD5C(*rng) * 0x201) >> 15;
                priority_base = 0x200;
                asm volatile("" : "+r"(priority_base));
                priority += priority_base;
                asm volatile(
                    "mov %0, %3\n\t"
                    "mov %1, #0\n\t"
                    "ldrsh %2, [%0, %1]"
                    : "=r"(x_view), "=r"(x_offset), "=r"(x_value)
                    : "r"(saved_x));
                asm volatile(
                    "mov %0, %3\n\t"
                    "mov %1, #0\n\t"
                    "ldrsh %2, [%0, %1]"
                    : "=r"(y_view), "=r"(y_offset), "=r"(y_value)
                    : "r"(saved_y));
                spawned = func_080D2660(owner, 3, 0, x_value, y_value,
                    0x500, angle_slot, priority, 0);
                child_offset = index << 2;
                asm volatile("add %0, %1" : "+r"(child_offset)
                             : "r"(children));
                *(void **)child_offset = spawned;
                index = (u8)(index + 1);
            } while (index <= 5);
        }
        func_080D12A0(6, 0);
        func_080D2790(1);
        {
            register s32 *slot asm("r1") = saved_state;
            *slot = *slot + 1;
        }
        break;
    }
    case 2:
        index = 0;
        if (*(s32 *)(owner + 0xC) == 0) {
            register char *children asm("r1") = owner + 0xC;
            do {
                index = (u8)(index + 1);
            } while (index <= 5 &&
                *(s32 *)(children + (index << 2)) == 0);
        }
        if (index == 6) {
            func_08095114(owner);
        }
        break;
    }
}
