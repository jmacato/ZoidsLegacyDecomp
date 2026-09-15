#include "m2c_prelude.h"
extern s16 func_08092A90(s16);
extern void func_08095114(void *);
extern void func_080D12A0(s32, s32);
extern void *func_080D2450();
extern void *func_080D2660();
extern void func_080D2790(s32);
extern u32 func_080ECD5C(u32);
extern s32 func_080ECD98(s32, s32);
extern s32 func_080ECF78(s32, s32);
extern u32 D_03000010;

void sub_080D6894(void *arg0) {
    char *owner = arg0;
    register u32 *state_slot asm("r5") = (u32 *)(owner + 0x8C);
    s32 outgoing_reserve;
    u32 saved_y;
    s32 zero_value;
    char *saved_children;
    s32 *count_slot;
    s32 group4;

    asm volatile("" : "=m"(outgoing_reserve), "=m"(saved_y), "=m"(zero_value),
                  "=m"(saved_children), "=m"(count_slot), "=m"(group4));

    switch (*state_slot) {
    case 0: {
        register s32 *x_slot asm("r4") = (s32 *)(owner + 0x90);
        register s32 x asm("r3") = *x_slot - 0x100;
        register s32 zero asm("r2");
        void *created;

        x = (s16)x;
        created = func_080D2450(owner, 0, 0, x,
            (s32)*(s16 *)(owner + 0x94), 0x20, 0x080D63D1, 1);
        *(void **)(owner + 0xC) = created;
        *(void **)((char *)created + 0x28) = owner;
        zero = 0;
        *(s32 *)((char *)created + 0x2C) = zero;
        *(s32 *)((char *)created + 0x30) = *x_slot;
        *(s32 *)((char *)created + 0x34) = zero;
        func_080D2790(0);
        *state_slot = *state_slot + 1;
        break;
    }
    case 1:
        if ((**(u32 **)(owner + 0xC) & 0x20000) == 0) {
            break;
        }
        {
            register s32 *count_init asm("r0") = (s32 *)(owner + 0x98);
            register u32 count asm("r1") = *count_init;
            register s32 remainder asm("r2");

            count_slot = count_init;
            if (count <= 0xC) {
                remainder = 3;
                remainder &= count;
                zero_value = remainder;

                if (remainder == 0) {
                register s32 group_init asm("r0") = (u8)(count >> 2);
                register s32 group asm("sl") = group_init;
                register s32 scaled asm("r6");
                register s32 scale_byte asm("r9");
                register s32 x_value asm("r5");
                register s32 random asm("r8");
                register s32 y_value asm("r4");
                register s32 phase asm("r0");
                register u32 index asm("r6");
                s32 trig;
                void *created;

                trig = func_08092A90((s16)func_080ECD98(
                    group_init << 7, 3));
                if (trig < 0) {
                    trig += 0xF;
                }
                scaled = trig >> 4;
                scaled <<= 24;
                {
                    register s32 scale_init asm("r4") =
                        (u32)scaled >> 24;
                    asm volatile("" : "+r"(scale_init));
                    scale_byte = scale_init;
                }
                x_value = *(s32 *)(owner + 0x90);
                {
                    register s32 group_view asm("r1") = group;
                    register s32 offset asm("r0") = group_view << 1;
                    asm volatile("" : "+r"(group_view));
                    offset += group;
                    offset <<= 2;
                    x_value += offset;
                }
                x_value = (u16)x_value;
                {
                    register u32 *rng asm("r2") = &D_03000010;
                    random = func_080ECD5C(*rng);
                }
                y_value = *(s32 *)(owner + 0x94);
                phase = (u8)func_080ECF78(group, 3);
                {
                    register s32 product asm("r1") = scale_byte;
                    asm volatile("mul %0, %1" : "+r"(product) : "r"(phase));
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
                    asm volatile("add %0, %1" : "+r"(perturb) : "r"(random));
                    perturb = (u32)perturb >> 15;
                    perturb += 0xFFFC;
                    y_value += perturb;
                }
                y_value <<= 16;
                x_value <<= 16;
                {
                    register s32 x_arg asm("r3") = x_value >> 16;
                    register u32 y_bits asm("r2") = (u32)y_value >> 16;
                    register volatile s32 *outgoing asm("sp");
                    saved_y = y_bits;
                    y_value >>= 16;
                    outgoing[0] = y_value;
                    {
                        register s32 zero_arg asm("r4") = zero_value;
                        asm volatile("" : "+r"(zero_arg));
                        outgoing[1] = zero_arg;
                        outgoing[2] = zero_arg;
                        outgoing[3] = zero_arg;
                    }
                    created = func_080D2450(owner, 2, 0, x_arg);
                }
                {
                    register s32 slot_index asm("r1") = group;
                    register s32 grouped asm("r3") = slot_index << 2;
                    register char *children asm("r2");
                    slot_index = grouped + slot_index;
                    slot_index += 1;
                    slot_index <<= 2;
                    children = owner + 0xC;
                    *(void **)(children + slot_index) = created;
                    index = 0;
                    group4 = grouped;
                    saved_children = children;
                }
                {
                    register u32 *rng_init asm("r2") = &D_03000010;
                    register u32 *rng asm("r8") = rng_init;
                    register s32 x_bits asm("r9") = x_value;
                    asm volatile("" : "+r"(rng_init));

                    do {
                        register s32 angle asm("r5");
                        register s32 random_angle asm("r4");
                        register s32 priority asm("r1");
                        void *spawned;

                        {
                            register u32 *rng_view asm("r4") = rng;
                            asm volatile("" : "+r"(rng_view));
                            random_angle = func_080ECD5C(*rng_view);
                        }
                        angle = func_080ECD98(index << 6, 3);
                        {
                            register s32 perturb asm("r0") =
                                (u32)(random_angle * 9) >> 15;
                            perturb -= 0x24;
                            angle += perturb;
                        }
                        {
                            register u32 *rng_view asm("r1") = rng;
                            asm volatile("" : "+r"(rng_view));
                            priority = ((u32)(func_080ECD5C(*rng_view) * 0x101)
                                >> 15);
                            {
                                register s32 priority_base asm("r2") = 0x100;
                                asm volatile("" : "+r"(priority_base));
                                priority += priority_base;
                            }
                        }
                        {
                            register volatile s32 *outgoing asm("sp");
                            register s32 saved_y_view asm("r4") = saved_y;
                            register s32 y_arg asm("r0") = (s16)saved_y_view;

                            asm volatile("" : "+r"(saved_y_view));
                            outgoing[0] = y_arg;
                            outgoing[1] = 0x500;
                            outgoing[2] = angle;
                            outgoing[3] = priority;
                            outgoing[4] = 0;
                            {
                                register void *owner_arg asm("r0") = owner;
                                register s32 type_arg asm("r1") = 3;
                                register s32 zero_arg asm("r2") = 0;
                                register s32 x_view asm("r4") = x_bits;
                                register s32 x_arg asm("r3") = x_view >> 16;
                                asm volatile("" : "+r"(owner_arg),
                                    "+r"(type_arg), "+r"(zero_arg));
                                asm volatile("" : "+r"(x_view));
                                spawned = func_080D2660(
                                    owner_arg, type_arg, zero_arg, x_arg);
                            }
                        }
                        {
                            register s32 slot_index asm("r1") = group4;
                            register char *children asm("r2");
                            slot_index += group;
                            slot_index = index + slot_index;
                            slot_index += 2;
                            slot_index <<= 2;
                            children = saved_children;
                            *(void **)(children + slot_index) = spawned;
                        }
                        {
                            register u32 next asm("r0") = index + 1;
                            asm volatile("" : "+r"(next));
                            index = (u8)next;
                        }
                    } while (index <= 3);
                }
                }

                {
                    register s32 *count_view asm("r4") = count_slot;
                    asm volatile("" : "+r"(count_view));
                    if (*count_view == 0) {
                        func_080D12A0(6, 0);
                        func_080D2790(1);
                    }
                }
                *count_slot = *count_slot + 1;
            } else {
                *state_slot = 2;
            }
        }
        break;

    case 2: {
        register u32 index asm("r6") = 0x18;
        register char *parent asm("r1") = *(char **)(owner + 0xC);
        register u32 bound_bits asm("r0") = *(u32 *)(parent + 0x2C);
        register u32 bound asm("r2");
        bound_bits >>= 1;
        asm volatile("" : "+r"(bound_bits));
        bound = bound_bits;
        bound += 0x19;

        if (index < bound && *(s32 *)(owner + 0x6C) == 0) {
            register u32 scan_bound asm("r3") = bound;
            register char *children asm("r2") = owner + 0xC;
            do {
                register u32 next asm("r0") = index + 1;
                asm volatile("" : "+r"(next));
                index = (u8)next;
            } while (index < scan_bound &&
                *(s32 *)(children + (index << 2)) == 0);
        }
        if (index == ((*(u32 *)(parent + 0x2C) >> 1) + 0x19)) {
            index = 1;
            if (*(s32 *)(owner + 0x10) == 0) {
                register char *children asm("r1") = owner + 0xC;
                do {
                    register u32 next asm("r0") = index + 1;
                    asm volatile("" : "+r"(next));
                    index = (u8)next;
                } while (index <= 0x14 &&
                    *(s32 *)(children + (index << 2)) == 0);
            }
            if (index == 0x15) {
                func_08095114(owner);
            }
        }
        break;
    }
    }
}
