#include "m2c_prelude.h"

struct ChildEBF64 {
    u8 flags;
    u8 pad_01[0x12];
    u8 level;
    u8 pad_14[0x3C];
};

struct OwnerEBF64 {
    u8 pad_00[4];
    u32 flags;
    u8 count;
    u8 pad_09[0x1B];
    u16 timer;
    u16 countdown;
    u16 phase;
    u16 pad_2A;
    struct ChildEBF64 *children;
};

void func_080EB328(struct OwnerEBF64 *, struct ChildEBF64 *);

void sub_080EBF64(struct OwnerEBF64 *arg0)
{
    register struct OwnerEBF64 *owner asm("r6") = arg0;
    register u32 timer asm("r1") = owner->timer;

    if (timer != 0) {
        register s32 countdown asm("r0") = owner->countdown - 1;
        register u32 mask_init asm("r3");
        register u32 mask asm("r2");
        register u32 normalized_countdown asm("r3");

        owner->countdown = countdown;
        mask_init = 0xFFFF;
        asm volatile("" : "+r"(mask_init));
        mask = mask_init;
        normalized_countdown = (u16)countdown;
        if (normalized_countdown == 0) {
            u16 phase;

            owner->countdown = timer;
            phase = owner->phase;
            if ((phase & 2) != 0) {
                s32 next = phase + 0x10;

                owner->phase = next;
                next &= mask;
                if (next > 0xFFU) {
                    owner->phase = 0x100;
                    owner->timer = normalized_countdown;
                }
            } else {
                s32 next = phase - 0x10;

                owner->phase = next;
                next &= mask;
                if ((s32)(next << 16) <= 0) {
                    s32 count = owner->count;
                    struct ChildEBF64 *child = owner->children;

                    if (count > 0) {
                        do {
                            register u32 clear asm("r0");
                            register u32 phase_view asm("r7");

                            func_080EB328(owner, child);
                            clear = 1;
                            asm volatile("" : "+r"(clear));
                            phase_view = owner->phase;
                            clear &= phase_view;
                            if (clear == 0) {
                                child->flags = clear;
                            }
                            count -= 1;
                            child += 1;
                        } while (count > 0);
                    }
                    {
                        register u32 test asm("r0") = 1;
                        register u32 phase_view asm("r1");

                        asm volatile("" : "+r"(test));
                        phase_view = owner->phase;
                        test &= phase_view;
                    if (test != 0) {
                        owner->flags |= 0x80000000;
                    } else {
                        owner->flags = 0x80000000;
                    }
                    }
                    owner->timer = 0;
                    return;
                }
            }

            {
                register s32 count asm("r5") = owner->count;
                register struct ChildEBF64 *child asm("r4") = owner->children;

                if (count > 0) {
                    register u32 flag_mask asm("r3") = 0x80;
                    u32 phase_value = 0;
                    register u32 set_bits asm("r2");

                    asm volatile("" : "+r"(phase_value));
                    set_bits = 3;
                    do {
                        register u32 flags asm("r1") = child->flags;
                        register u32 test asm("r0") = flag_mask;

                        test &= flags;
                        if (test != 0) {
                            phase_value = owner->phase;
                            test = phase_value >> 2;
                            child->level = test;
                            test = flags;
                            test |= set_bits;
                            child->flags = test;
                        }
                        asm volatile("" : "+r"(phase_value));
                        count -= 1;
                        child += 1;
                    } while (count > 0);
                }
            }
        }
    }
}
