#include "m2c_prelude.h"
extern s16 func_08092A90(s16);
extern void func_08095114(void *);
extern void func_080D12A0(s32, s32);
extern void *func_080D2450();
extern void *func_080D2660();
extern s32 func_080D2754(void *, s32, s32);
extern void func_080D2790(s32);
extern u32 func_080ECD5C(u32);
extern s32 func_080ECD98(s32, s32);
extern s32 func_080ECF78(s32, s32);
extern u32 D_03000010;

void sub_080E02E0(void *arg0) {
    char *owner = arg0;
    register s32 *state_slot asm("r4") = (s32 *)(owner + 0x8C);
    s32 outgoing_reserve;
    u32 saved_y;
    char *saved_children;
    s32 *saved_state;

    asm volatile("" : "=m"(outgoing_reserve), "=m"(saved_y),
                           "=m"(saved_children),
                           "=m"(saved_state));

    if (*state_slot == 0) {
        void *created = func_080D2450(owner, 0, 0,
            (s16)(*(s32 *)(owner + 0x90) - 0x100),
            *(s16 *)(owner + 0x94), 0x510, 0x080D2529, 1);
        *(void **)(owner + 0xC) = created;
        *(s32 *)((char *)created + 0x28) = 0x10;
        func_080D2790(0);
        *state_slot = *state_slot + 1;
    }

    {
        register u32 current_state asm("r0") = *state_slot;
    if (current_state <= 7) {
        if (current_state == 1 &&
                (func_080D2754(*(void **)(owner + 0xC),
                    *(s32 *)(owner + 0x90),
                    *(s32 *)(owner + 0x94)) << 24) != 0) {
            func_080D12A0(6, 0);
            func_080D2790(1);
            *state_slot = *state_slot + 1;
        }
        {
            register s32 *state_view asm("r0") = (s32 *)(owner + 0x8C);
            register u32 current asm("r1");
            current = *state_view;
            saved_state = state_view;

            if (current > 1) {
                register s32 step_init asm("r0") = (u8)(current - 2);
                register s32 step asm("sl") = step_init;
                register s32 scaled asm("r6");
                register s32 scale_byte asm("r9");
                register s32 x_value asm("r5");
                register s32 random asm("r8");
                register s32 y_value asm("r4");
                register s32 phase asm("r0");
                s32 trig;
                void *created;

                trig = func_08092A90((s16)func_080ECD98(
                    step_init << 7, 5));
                if (trig < 0) {
                    trig += 0xF;
                }
                scaled = trig >> 4;
                scaled <<= 24;
                {
                    register s32 scale_init asm("r2") =
                        (u32)scaled >> 24;
                    asm volatile("" : "+r"(scale_init));
                    scale_byte = scale_init;
                }
                x_value = *(s32 *)(owner + 0x90);
                {
                    register s32 step_view asm("r1") = step;
                    register s32 step_add asm("r0") = step_view << 3;
                    asm volatile("" : "+r"(step_view));
                    x_value += step_add;
                }
                x_value = (u16)x_value;
                {
                    register u32 *rng asm("r2") = &D_03000010;
                    random = func_080ECD5C(*rng);
                }
                y_value = *(s32 *)(owner + 0x94);
                phase = (u8)func_080ECF78(step, 3);
                {
                    register s32 product asm("r1") = scale_byte;
                    asm volatile("mul %0, %1"
                        : "+r"(product) : "r"(phase));
                    phase = product;
                }
                asm volatile("" : "+r"(phase));
                phase >>= 1;
                y_value += phase;
                y_value -= (u32)scaled >> 25;
                {
                    register s32 perturb asm("r0");
                    register s32 random_view asm("r2") = random;
                    asm volatile("" : "+r"(random_view));
                    perturb = random_view << 3;
                    asm volatile("add %0, %1"
                                 : "+r"(perturb) : "r"(random));
                    perturb = (u32)perturb >> 15;
                    perturb += 0xFFFC;
                    asm volatile("" : "+r"(random_view));
                    y_value += perturb;
                }
                y_value <<= 16;
                x_value <<= 16;
                {
                    register s32 x_arg asm("r3") = x_value >> 16;
                    register u32 y_bits asm("r2") = (u32)y_value >> 16;
                    saved_y = y_bits;
                    y_value >>= 16;
                    created = func_080D2450(owner, 1, 0,
                        x_arg, y_value, 0, 0, 0);
                }
                {
                    register s32 offset asm("r2") = step + 1;
                    register s32 grouped asm("r1") = offset << 2;
                    register char *children asm("r3");
                    grouped += offset;
                    grouped <<= 2;
                    children = owner + 0xC;
                    *(void **)(children + grouped) = created;
                    {
                        register u32 index asm("r6") = 0;
                        register u32 *rng asm("r9");
                        register s32 group asm("r8");

                        saved_children = children;
                        asm volatile("" : "+m"(saved_children));
                        rng = &D_03000010;
                        group = offset;

                        do {
                            register s32 angle asm("r4");
                            register s32 priority asm("r1");
                            register s32 priority_base asm("r0");
                            register s32 slot_index asm("r1");
                            void *spawned;

                            {
                                register u32 *rng_view asm("r1") = rng;
                                angle = (u32)(func_080ECD5C(*rng_view) * 0x41)
                                    >> 15;
                            }
                            angle -= 0x20;
                            {
                                register u32 *rng_view asm("r2") = rng;
                                priority = (u32)(func_080ECD5C(*rng_view) *
                                    0x101) >> 15;
                            }
                            priority_base = 0x100;
                            priority += priority_base;
                            asm volatile("" : "+r"(priority_base));
                            {
                                register volatile s32 *outgoing asm("sp");
                                register u32 y_bits asm("r2") = saved_y;
                                register s32 y_arg asm("r0");
                                register s32 size asm("r0");
                                register s32 zero asm("r0");
                                register char *call0 asm("r0");
                                register s32 call1 asm("r1");
                                register s32 call2 asm("r2");
                                register s32 x_arg asm("r3");

                                y_arg = y_bits << 16;
                                y_arg >>= 16;
                                outgoing[0] = y_arg;
                                size = 0x500;
                                outgoing[1] = size;
                                outgoing[2] = angle;
                                outgoing[3] = priority;
                                zero = 0;
                                outgoing[4] = zero;
                                call0 = owner;
                                call1 = 2;
                                call2 = 0;
                                asm volatile("asr %0, %1, #16"
                                    : "=r"(x_arg) : "r"(x_value));
                                spawned = func_080D2660(
                                    call0, call1, call2, x_arg);
                            }
                            slot_index = group << 2;
                            slot_index += group;
                            slot_index += index;
                            slot_index += 1;
                            slot_index <<= 2;
                            {
                                register char *children_view asm("r2") =
                                    saved_children;
                                asm volatile("add %0, %1, %0"
                                    : "+r"(slot_index)
                                    : "r"(children_view));
                                *(void **)slot_index = spawned;
                            }
                            {
                                register u32 next asm("r0") = index + 1;
                                next <<= 24;
                                index = next >> 24;
                            }
                        } while (index <= 3);
                    }
                }
                {
                    register s32 *saved_view asm("r1") = saved_state;
                    register s32 saved_value asm("r0");
                    asm volatile(".short 0x6808, 0x3001, 0x6008"
                                 : "=r"(saved_value)
                                 : "r"(saved_view) : "memory");
                }
            }
        }
    } else {
        register u32 index asm("r6") = 0;
        if (*(s32 *)(owner + 0xC) == 0) {
            register char *children asm("r1") = owner + 0xC;
            do {
                register u32 next asm("r0") = index + 1;
                next <<= 24;
                index = next >> 24;
            } while (index <= 0x1E &&
                *(s32 *)(children + (index << 2)) == 0);
        }
        if (index == 0x1F) {
            func_08095114(owner);
        }
    }
    }
}
