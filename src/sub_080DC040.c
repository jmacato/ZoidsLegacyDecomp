#include "m2c_prelude.h"

extern s16 func_08092A90(s32);
extern s16 func_08092ADC(s32);
extern void func_08094554(void *);
extern void func_08095114(void *);
extern void func_080D12A0(s32, s32);
extern void *func_080D2450();
extern void *func_080D2660();
extern void func_080D2790(s32);
extern u32 func_080ECD5C(u32);
extern u32 D_03000010;

void sub_080DC040(void *arg0) {
    char *owner = arg0;
    register s32 *state_slot asm("r8") = (s32 *)(owner + 0x8C);
    register u32 state asm("r0") = *state_slot;
    u8 index;

    switch (state) {
    case 0: {
        register s32 x_value asm("r4");
        register s32 trig asm("r0");
        register s32 coord asm("r2");
        void *created;

        trig = func_08092ADC(0x36);
        {
            register char *coord_ptr asm("r1") = owner;
            coord_ptr += 0x90;
            coord = *(s32 *)coord_ptr;
        }
        trig = (s16)trig;
        {
            register s32 work asm("r1") = trig << 1;
            work += trig;
            trig = work << 6;
        }
        if (trig < 0) {
            trig += 0xFF;
        }
        trig >>= 8;
        trig = coord - trig;
        x_value = (s16)trig;

        trig = func_08092A90(0x36);
        {
            register char *coord_ptr asm("r1") = owner;
            coord_ptr += 0x94;
            coord = *(s32 *)coord_ptr;
        }
        trig = (s16)trig;
        {
            register s32 work asm("r1") = trig << 1;
            work += trig;
            trig = work << 6;
        }
        if (trig < 0) {
            trig += 0xFF;
        }
        trig >>= 8;
        trig = coord - trig;
        trig = (s16)trig;
        created = func_080D2660(owner, 0, 0, x_value, trig,
            0x120, 0x4A, 0xC00, 1);
        *(void **)(owner + 0xC) = created;
        func_080D2790(0);
        {
            register s32 *slot asm("r1") = state_slot;
            *slot = *slot + 1;
        }
        break;
    }
    case 1: {
        s32 *counter = (s32 *)(owner + 0x98);
        register char *x_ptr asm("r5");
        register char *y_ptr asm("r4");
        register char *saved_x asm("sl");
        register char *saved_y asm("r9");
        register s32 *children asm("r8");
        s32 * volatile saved_state;
        volatile s32 angle_slot;

        *counter = *counter + 1;
        if (*counter != 0x10) {
            break;
        }
        func_08094554(*(void **)(owner + 0xC));
        x_ptr = owner + 0x90;
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
            y_ptr = owner + 0x94;
            asm volatile(
                "mov %0, #0\n\t"
                "ldrsh %1, [%2, %0]"
                : "=r"(y_offset), "=r"(y_value)
                : "r"(y_ptr));
            *(void **)(owner + 0xC) = func_080D2450(owner, 2, 0,
                x_value, y_value, 0x100, 0, 0);
        }

        index = 0;
        {
            register s32 *saved_state_view asm("r2") = state_slot;
            saved_state = saved_state_view;
        }
        saved_x = x_ptr;
        saved_y = y_ptr;
        {
            register s32 *children_init asm("r4") = (s32 *)0xC;
            asm volatile("" : "+r"(children_init));
            children_init = (s32 *)((char *)children_init + (s32)owner);
            children = children_init;
        }
        {
            register u32 *rng asm("r5") = &D_03000010;
            do {
                register s32 angle asm("r4");
                register s32 random asm("r0");
                register s32 priority asm("r1");
                register s32 priority_base asm("r0");
                register char *x_view asm("r2");
                register s32 x_offset asm("r4");
                register s32 x_value asm("r3");
                register char *y_view asm("r2");
                register s32 y_offset asm("r4");
                register s32 y_value asm("r0");
                register s32 next asm("r2");
                register s32 child_offset asm("r1");
                void *spawned;

                random = func_080ECD5C(*rng);
                angle = index << 3;
                random = (u32)random >> 13;
                random += 0x2C;
                angle += random;
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
                    0x500, angle_slot, priority, 1);
                next = index + 1;
                child_offset = next << 2;
                asm volatile("add %0, %1" : "+r"(child_offset)
                             : "r"(children));
                *(void **)child_offset = spawned;
                next <<= 24;
                index = (u32)next >> 24;
            } while (index <= 7);
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
            } while (index <= 8 &&
                *(s32 *)(children + (index << 2)) == 0);
        }
        if (index == 9) {
            func_08095114(owner);
        }
        break;
    }
}
