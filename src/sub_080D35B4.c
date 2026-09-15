#include "m2c_prelude.h"

extern void func_08095114(void *);
extern void func_08094554(void *);
extern void func_080D12A0(s32, s32);
extern void *func_080D2450();
extern void *func_080D2660();
extern s32 func_080D2754(void *, s32, s32);
extern void func_080D2790(s32);
extern u32 func_080ECD5C(u32);
extern u32 D_03000010;

void sub_080D35B4(void *arg0) {
    register char *owner asm("r6") = arg0;
    s32 *state_slot = (s32 *)(owner + 0x8C);
    register u32 state asm("r0") = *state_slot;
    u8 index;

    switch (state) {
    case 0: {
        void *created = func_080D2450(owner, 0, 0,
            (s16)(*(s32 *)(owner + 0x90) - 0x100),
            *(s16 *)(owner + 0x94), 0x410, 0x080D2529, 1);
        *(void **)(owner + 0xC) = created;
        *(s32 *)((char *)created + 0x28) = 0x10;
        func_080D2790(0);
        *state_slot = *state_slot + 1;
        break;
    }
    case 1: {
        register s32 *x_ptr asm("r5");
        register s32 *y_ptr asm("r4");
        register s32 *saved_x asm("r9");
        register s32 *saved_y asm("r8");
        register s32 *children asm("sl");
        s32 reached;
        s32 * volatile saved_state;

        reached = func_080D2754(*(void **)(owner + 0xC),
            *(x_ptr = (s32 *)(owner + 0x90)) - 0x20,
            *(y_ptr = (s32 *)(owner + 0x94))) << 24;
        saved_x = x_ptr;
        saved_y = y_ptr;
        if (reached == 0) {
            break;
        }
        func_08094554(*(void **)(owner + 0xC));
        {
            register s32 x_offset asm("r2");
            register s32 x_value asm("r3");
            register s32 y_offset asm("r1");
            register s32 y_value asm("r0");

            asm volatile(
                "mov %0, #0\n\t"
                "ldrsh %1, [%2, %0]"
                : "=r"(x_offset), "=r"(x_value)
                : "r"(x_ptr));
            asm volatile(
                "mov %0, #0\n\t"
                "ldrsh %1, [%2, %0]"
                : "=r"(y_offset), "=r"(y_value)
                : "r"(y_ptr));
            *(void **)(owner + 0xC) = func_080D2450(owner, 1, 0,
                x_value, y_value, 0, 0, 0);
        }

        index = 1;
        saved_state = state_slot;
        {
            register s32 *children_init asm("r2") = (s32 *)0xC;
            asm volatile("" : "+r"(children_init));
            children_init = (s32 *)((char *)children_init + (s32)owner);
            children = children_init;
        }
        do {
            register u32 *rng asm("r7") = &D_03000010;
            register s32 random asm("r0");
            register s32 angle asm("r4");
            register s32 priority asm("r1");
            register s32 priority_base asm("r0");
            register s32 child_offset asm("r1");
            register char *x_view asm("r2");
            register s32 x_offset asm("r7");
            register s32 x_value asm("r3");
            register char *y_view asm("r2");
            register s32 y_offset asm("r7");
            register s32 y_value asm("r0");
            void *spawned;

            random = func_080ECD5C(*rng);
            angle = (u32)(random * 0x41) >> 15;
            angle -= 0x20;
            priority = (u32)(func_080ECD5C(*rng) * 0x101) >> 15;
            priority_base = 0x100;
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
            spawned = func_080D2660(owner, 2, 0, x_value, y_value,
                0x500, angle, priority, 0);
            child_offset = index << 2;
            asm volatile("add %0, %1" : "+r"(child_offset)
                         : "r"(children));
            *(void **)child_offset = spawned;
            index = (u8)(index + 1);
        } while (index <= 4);

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
            } while (index <= 4 &&
                *(s32 *)(children + (index << 2)) == 0);
        }
        if (index == 5) {
            func_08095114(owner);
        }
        break;
    }
}
