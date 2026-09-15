#include "m2c_prelude.h"
extern void func_08095114();
extern void *func_080D2450();
extern void *func_080D2660();
extern void func_080D2790();
extern u32 func_080ECD5C(u32);
extern u32 D_03000010;

void sub_080D43E0(void *arg0) {
    register char *owner asm("r5") = arg0;
    register s32 *p8C asm("r6") = (s32 *)(owner + 0x8C);
    register s32 state asm("r4") = *p8C;

    if (state == 0) {
        void *created;
        s32 *state_slot;
        s32 *children;
        s32 size;
        s32 zero;
        u8 index;

        created = func_080D2450(owner, 0, 0, *(s16 *)(owner + 4),
            (s32)*(s16 *)(owner + 8), 0x20, 0x080D3E9D, state);
        *(void **)(owner + 0xC) = created;
        *(void **)((char *)created + 0x28) = owner;
        *(s32 *)((char *)created + 0x2C) = state;

        index = 0;
        __asm__ volatile ("" :: "r" (index));
        __asm__ volatile ("" :: "r" (index));
        __asm__ volatile ("" :: "r" (index));
        state_slot = p8C;
        children = (s32 *)(owner + 0xC);
    spawn_loop:
        {
            u32 random;
            s32 priority;
            void *spawned;
            s32 next;
            s32 child_off;

            random = func_080ECD5C(D_03000010);
            priority = ((random * 0x41) >> 0xF) + 0xC0;
            spawned = func_080D2660(owner, 2, 0,
                *(s16 *)(owner + 4), *(s16 *)(owner + 8),
                (size = 0x400), (index << 2) - 0xA, priority, (zero = 0));
            next = index + 1;
            child_off = next << 2;
            *(s32 *)((char *)children + child_off) = (s32)spawned;
            index = (u8)next;
        }
        if (index <= 5) {
            goto spawn_loop;
        }
        created = func_080D2450(owner, 3, 0, *(s16 *)(owner + 4),
            (s32)*(s16 *)(owner + 8), size, zero, zero);
        *(void **)(owner + 0x28) = created;
        func_080D2790(0);
        *state_slot = *state_slot + 1;
        return;
    }
    {
        register void *t asm("r0") = *(void **)(owner + 0xC);
        s32 c = *(s32 *)t & 0x20000;
        register void *child asm("r3") = t;

        if (c) {
            register s32 var_r4 asm("r4");
            u32 child_count;
            u32 bound;
            s32 off;

            var_r4 = 0x18;
            __asm__ volatile ("" : "+r" (var_r4));
            child_count = *(u32 *)((char *)child + 0x2C);
            bound = (child_count >> 2) + 0x19;
            if ((u32)var_r4 < bound && *(s32 *)(owner + 0x6C) == 0) {
                u32 scan_bound = bound;
                s32 *children = (s32 *)(owner + 0xC);
                do {
                    register s32 w asm("r0");
                    w = var_r4 + 1;
                    w <<= 24;
                    var_r4 = (u32)w >> 24;
                } while ((u32)var_r4 < scan_bound &&
                    (off = var_r4 << 2, *(s32 *)((char *)children + off)) == 0);
            }
            if (var_r4 == ((*(volatile u32 *)((char *)child + 0x2C) >> 2) + 0x19)) {
                var_r4 = 1;
                if (*(s32 *)(owner + 0x10) == 0) {
                    s32 *children = (s32 *)(owner + 0xC);
                    do {
                        register s32 w asm("r0");
                        w = var_r4 + 1;
                        w <<= 24;
                        var_r4 = (u32)w >> 24;
                    } while ((u32)var_r4 <= 7 &&
                        (off = var_r4 << 2, *(s32 *)((char *)children + off)) == 0);
                }
                if (var_r4 == 8) {
                    func_08095114(owner);
                }
            }
        }
    }
}
