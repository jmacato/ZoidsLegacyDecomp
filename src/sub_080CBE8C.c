#include "m2c_prelude.h"

s32 func_080CBE08(s32, s32);
s32 func_080ECE30(s8, s32);
s32 func_080ECF78(u8, s32);
extern u8 D_02034B4C[];

void sub_080CBE8C(u8 arg0, s32 arg1, s32 arg2, M2C_UNK arg3)
{
    u32 saved_arg0 = arg0;
    register u32 arg2_value asm("r2");
    register u32 arg1_shifted asm("r1");
    register u32 arg1_value asm("r0");
    __asm__ volatile("" : "+r"(saved_arg0));
    __asm__ volatile("" : "=r"(arg1_shifted)
                         : "0"(arg1), "r"(saved_arg0));
    arg1_shifted <<= 24;
    __asm__ volatile("" : "+r"(arg1_shifted));
    __asm__ volatile("" : "=r"(arg2_value)
                         : "0"(arg2), "r"(arg1_shifted));
    arg2_value <<= 24;
    arg2_value >>= 24;
    __asm__ volatile("" : "+r"(arg2_value));
    arg1_value = arg1_shifted >> 24;

    if (arg1_shifted == 0 && arg2_value == 0) {
        register u32 candidate asm("r5") = 0;
        register u32 selected asm("r6");

auto_loop:
        {
            register u32 candidate_narrow asm("r0") = candidate << 24;
            register s32 signed_candidate asm("r4") =
                (s32)candidate_narrow >> 24;
            register s32 remainder asm("r0");
            register s32 choice asm("r1");

            remainder = func_080ECE30(signed_candidate, 3);
            choice = signed_candidate - remainder;
            choice += 2;
            choice -= remainder;
            selected = (u8)choice;
            if ((func_080CBE08(saved_arg0, (s8)selected) << 24) == 0) {
                register u32 next asm("r0") = signed_candidate + 1;
                next <<= 24;
                candidate = next >> 24;
                next = (s32)next >> 24;
                if ((s32)next <= 5) {
                    goto auto_loop;
                }
            }
        }

        {
            register u32 narrow asm("r0") = candidate << 24;
            narrow = (s32)narrow >> 24;
            if ((s32)narrow > 5) {
                return;
            }
        }
        {
            register u8 *base asm("r0") = D_02034B4C;
            register u32 offset asm("r2") = 0xA1AF;
            register u8 *count_ptr asm("r1");
            register u8 *selection_ptr asm("r0");
            register u32 count asm("r1");

            __asm__("" : "+r"(base));
            __asm__("" : "+r"(offset));
            count_ptr = base + offset;
            offset += 4;
            selection_ptr = base + offset;
            count = *count_ptr;
            selection_ptr += count;
            *selection_ptr = selected;
        }
        return;
    }

    {
        register s32 vertical asm("r0") = (s8)arg1_value;
        register u32 candidate asm("r5");

        if (vertical == 1) {
            register u8 *base asm("r1") = D_02034B4C;
            register u32 count_offset asm("r0") = 0xA1AF;
            register u8 *count_ptr asm("r5");
            register u32 selection_offset asm("r2");
            register u8 *selection_base asm("r4");
            register u32 count asm("r0");
            register u32 current asm("r0");

            __asm__("" : "+r"(base));
            __asm__("" : "+r"(count_offset));
            count_ptr = base + count_offset;
            count = *count_ptr;
            selection_offset = 0xA1B3;
            __asm__("" : "+r"(selection_offset));
            selection_base = base + selection_offset;
            current = count;
            current += (u32)selection_base;
            current = *(u8 *)current;
            if (current <= 2) {
                return;
            }
            if ((func_080CBE08(saved_arg0, (s8)(current - 3)) << 24) != 0) {
                register u32 count2 asm("r1") = *count_ptr;
                register u8 *destination asm("r1") =
                    (u8 *)((u32)count2 + (u32)selection_base);
                register u32 value asm("r0") = *destination;
                value -= 3;
                *destination = value;
                return;
            }
            {
                register u32 count2 asm("r0") = *count_ptr;
                register u32 current2 asm("r0") = count2;
                current2 += (u32)selection_base;
                current2 = *(u8 *)current2;

                if (current2 <= 4) {
                    candidate = 0;
                    goto up_forward_test;
up_forward_next:
                    {
                        register s32 previous asm("r4");
                        register u32 next asm("r0");
                        __asm__("" : "=r"(previous));
                        next = (u32)previous + 1;
                        next <<= 24;
                        candidate = next >> 24;
                    }
up_forward_test:
                    {
                        register u32 narrow asm("r0") = candidate << 24;
                        register s32 signed_candidate asm("r4") =
                            (s32)narrow >> 24;
                        if (signed_candidate > 2) {
                            return;
                        }
                        if ((func_080CBE08(saved_arg0,
                                          signed_candidate) << 24) == 0) {
                            goto up_forward_next;
                        }
                        goto vertical_found;
                    }
                } else {
                    candidate = 2;
                    goto up_reverse_test;
up_reverse_next:
                    {
                        register s32 previous asm("r4");
                        register u32 next asm("r0");
                        __asm__("" : "=r"(previous));
                        next = (u32)previous - 1;
                        next <<= 24;
                        candidate = next >> 24;
                    }
up_reverse_test:
                    {
                        register u32 narrow asm("r0") = candidate << 24;
                        register s32 signed_candidate asm("r4") =
                            (s32)narrow >> 24;
                        if (signed_candidate < 0) {
                            return;
                        }
                        if ((func_080CBE08(saved_arg0,
                                          signed_candidate) << 24) == 0) {
                            goto up_reverse_next;
                        }
                        goto vertical_found;
                    }
                }

            }
        }

        {
            register s32 minus_one asm("r1") = -1;
            if (vertical == minus_one) {
                register u8 *base asm("r1") = D_02034B4C;
                register u32 count_offset asm("r0") = 0xA1AF;
                register u8 *count_ptr asm("r5");
                register u32 selection_offset asm("r2");
                register u8 *selection_base asm("r4");
                register u32 count asm("r0");
                register u32 current asm("r0");

                __asm__("" : "+r"(base));
                __asm__("" : "+r"(count_offset));
                count_ptr = base + count_offset;
                count = *count_ptr;
                selection_offset = 0xA1B3;
                __asm__("" : "+r"(selection_offset));
                selection_base = base + selection_offset;
                current = count;
                current += (u32)selection_base;
                current = *(u8 *)current;
                if (current > 2) {
                    return;
                }
                if ((func_080CBE08(saved_arg0, (s8)(current + 3)) << 24) != 0) {
                    register u32 count2 asm("r1") = *count_ptr;
                    register u8 *destination asm("r1") =
                        (u8 *)((u32)count2 + (u32)selection_base);
                    register u32 value asm("r0") = *destination;
                    value += 3;
                    *destination = value;
                    return;
                }
                {
                    register u32 count2 asm("r0") = *count_ptr;
                    register u32 current2 asm("r0") = count2;
                    current2 += (u32)selection_base;
                    current2 = *(u8 *)current2;

                    if (current2 <= 1) {
                        candidate = 3;
                        goto down_forward_test;
down_forward_next:
                        {
                            register s32 previous asm("r4");
                            register u32 next asm("r0");
                            __asm__("" : "=r"(previous));
                            next = (u32)previous + 1;
                            next <<= 24;
                            candidate = next >> 24;
                        }
down_forward_test:
                        {
                            register u32 narrow asm("r0") = candidate << 24;
                            register s32 signed_candidate asm("r4") =
                                (s32)narrow >> 24;
                            if (signed_candidate > 5) {
                                return;
                            }
                            if ((func_080CBE08(saved_arg0,
                                              signed_candidate) << 24) == 0) {
                                goto down_forward_next;
                            }
                            goto vertical_found;
                        }
                    } else {
                        candidate = 5;
                        goto down_reverse_test;
down_reverse_next:
                        {
                            register s32 previous asm("r4");
                            register u32 next asm("r0");
                            __asm__("" : "=r"(previous));
                            next = (u32)previous - 1;
                            next <<= 24;
                            candidate = next >> 24;
                        }
down_reverse_test:
                        {
                            register u32 narrow asm("r0") = candidate << 24;
                            register s32 signed_candidate asm("r4") =
                                (s32)narrow >> 24;
                            register s32 result asm("r0");
                            __asm__ volatile("" : "+r"(signed_candidate));
                            if (signed_candidate <= 2) {
                                return;
                            }
                            result = func_080CBE08(saved_arg0,
                                                  signed_candidate);
                            result <<= 24;
                            __asm__ volatile("" : "+r"(result));
                            if (result == 0) {
                                goto down_reverse_next;
                            }
                            goto vertical_found;
                        }
                    }
                }
            }

            goto horizontal_start;

vertical_found:
            {
                register u8 *store_base asm("r0") = D_02034B4C;
                register u32 offset asm("r2") = 0xA1AF;
                register u8 *count_ptr2 asm("r1");
                register u8 *destination asm("r0");
                register u32 count3 asm("r1");

                __asm__("" : "+r"(store_base));
                __asm__("" : "+r"(offset));
                count_ptr2 = store_base + offset;
                offset += 4;
                destination = store_base + offset;
                count3 = *count_ptr2;
                destination += count3;
                *destination = candidate;
            }
            return;

horizontal_start:

            {
                register u32 base_shift asm("r6");
                register s32 base_value asm("r8");
                register s32 direction asm("r0") = (s8)arg2_value;

            if (direction == 1) {
                register u32 current asm("r4");

                {
                    register u8 *base asm("r0") = D_02034B4C;
                    register u32 offset asm("r2") = 0xA1AF;
                    register u8 *count_ptr asm("r1");
                    register u8 *selection_ptr asm("r0");
                    register u32 count asm("r1");
                    __asm__("" : "+r"(base));
                    __asm__("" : "+r"(offset));
                    count_ptr = base + offset;
                    offset += 4;
                    selection_ptr = base + offset;
                    count = *count_ptr;
                    selection_ptr += count;
                    current = *selection_ptr;
                }
                {
                    register u32 remainder asm("r0") =
                        func_080ECF78(current, 3);
                    current -= remainder;
                    current <<= 24;
                    candidate = (u8)(remainder - 1);
                }
                base_shift = current >> 24;
                base_value = (s32)current >> 24;
                goto left_first_test;

left_first_next:
                {
                    register s32 previous asm("r4");
                    register u32 next asm("r0");
                    __asm__("" : "=r"(previous));
                    next = (u32)previous - 1;
                    next <<= 24;
                    candidate = next >> 24;
                }
left_first_test:
                {
                    register u32 narrow asm("r0") = candidate << 24;
                    register s32 step asm("r4") = (s32)narrow >> 24;
                    candidate = base_shift << 24;
                    if (step < 0) {
                        goto left_first_exhausted;
                    }
                    if ((func_080CBE08(saved_arg0,
                                      (s8)(base_value + step)) << 24) == 0) {
                        goto left_first_next;
                    }
                    goto horizontal_store;
                }
left_first_exhausted:
                {
                    register u32 three asm("r0") = 3;
                    register s32 signed_base asm("r1") =
                        (s32)candidate >> 24;
                    three -= signed_base;
                    three <<= 24;
                    base_shift = three >> 24;
                }
                {
                    register u32 current2 asm("r0");
                    register u8 *base asm("r0") = D_02034B4C;
                    register u32 offset asm("r2") = 0xA1AF;
                    register u8 *count_ptr asm("r1");
                    register u8 *selection_ptr asm("r0");
                    register u32 count asm("r1");
                    __asm__("" : "+r"(base));
                    __asm__("" : "+r"(offset));
                    count_ptr = base + offset;
                    offset += 4;
                    selection_ptr = base + offset;
                    count = *count_ptr;
                    selection_ptr += count;
                    current2 = *selection_ptr;
                    candidate = (u8)(func_080ECF78(current2, 3) - 1);
                    base_value = (s8)base_shift;
                }
                goto left_second_test;
left_second_next:
                {
                    register s32 previous asm("r4");
                    register u32 next asm("r0");
                    __asm__("" : "=r"(previous));
                    next = (u32)previous - 1;
                    next <<= 24;
                    candidate = next >> 24;
                }
left_second_test:
                {
                    register u32 narrow asm("r0") = candidate << 24;
                    register s32 step asm("r4") = (s32)narrow >> 24;
                    __asm__ volatile("cmp r4, #0\n\tblt .L2"
                                     : : "r"(step) : "cc");
                    direction = func_080CBE08(saved_arg0,
                                              (s8)(base_value + step));
                    direction <<= 24;
                    candidate = base_shift << 24;
                    __asm__ volatile("" : "+r"(candidate));
                    __asm__ volatile("" : "=r"(minus_one));
                    if (direction == 0) {
                        goto left_second_next;
                    }
                    goto horizontal_store;
                }

            } else {
horizontal_direction_test:
                if (direction != minus_one) {
                    return;
                }

                {
                    register u32 current asm("r4");
                    register u32 remainder asm("r0");

                    {
                        register u8 *base asm("r0") = D_02034B4C;
                        register u32 offset asm("r2") = 0xA1AF;
                        register u8 *count_ptr asm("r1");
                        register u8 *selection_ptr asm("r0");
                        register u32 count asm("r1");
                        __asm__("" : "+r"(base));
                        __asm__("" : "+r"(offset));
                        count_ptr = base + offset;
                        offset += 4;
                        selection_ptr = base + offset;
                        count = *count_ptr;
                        selection_ptr += count;
                        current = *selection_ptr;
                    }
                    remainder = func_080ECF78(current, 3);
                    current -= remainder;
                    current <<= 24;
                    candidate = (u8)(remainder + 1);
                    base_shift = current >> 24;
                    base_value = (s32)current >> 24;
                    goto right_first_test;

right_first_next:
                    {
                        register s32 previous asm("r4");
                        register u32 next asm("r0");
                        __asm__("" : "=r"(previous));
                        next = (u32)previous + 1;
                        next <<= 24;
                        candidate = next >> 24;
                    }
right_first_test:
                    {
                        register u32 narrow asm("r0") = candidate << 24;
                        register s32 step asm("r4") = (s32)narrow >> 24;
                        candidate = base_shift << 24;
                        if (step > 2) {
                            goto right_first_exhausted;
                        }
                        if ((func_080CBE08(saved_arg0,
                                          (s8)(base_value + step)) << 24) == 0) {
                            goto right_first_next;
                        }
                        goto horizontal_store;
                    }
right_first_exhausted:
                    {
                        register u32 three asm("r0") = 3;
                        register s32 signed_base asm("r1") =
                            (s32)candidate >> 24;
                        three -= signed_base;
                        three <<= 24;
                        base_shift = three >> 24;
                    }
                    {
                        register u8 *first asm("r0") = D_02034B4C;
                        register u32 offset asm("r2") = 0xA1AF;
                        register u8 *count_ptr asm("r1");
                        register u8 *selection_ptr asm("r0");
                        register u32 count asm("r1");
                        register u32 current2 asm("r0");
                        __asm__("" : "+r"(first));
                        __asm__("" : "+r"(offset));
                        count_ptr = first + offset;
                        offset += 4;
                        selection_ptr = first + offset;
                        count = *count_ptr;
                        selection_ptr += count;
                        current2 = *selection_ptr;
                        candidate = (u8)(func_080ECF78(current2, 3) + 1);
                        base_value = (s8)base_shift;
                        __asm__ volatile("" : "+r"(candidate));
                        __asm__ volatile("" : "+r"(base_value));
                    }
                    goto right_second_test;
right_second_next:
                    {
                        register s32 previous asm("r4");
                        register u32 next asm("r0");
                        __asm__("" : "=r"(previous));
                        next = (u32)previous + 1;
                        next <<= 24;
                        candidate = next >> 24;
                    }
right_second_test:
                    {
                        register u32 narrow asm("r0") = candidate << 24;
                        register s32 step asm("r4") = (s32)narrow >> 24;
                        register s32 probe asm("r1");
                        if (step > 2) {
                            return;
                        }
                        probe = (s8)(base_value + step);
                        __asm__ volatile("" : "+r"(probe));
                        direction = func_080CBE08(saved_arg0, probe);
                        direction <<= 24;
                        candidate = base_shift << 24;
                        if (direction == 0) {
                            goto right_second_next;
                        }
                        goto horizontal_store;
                    }

                }
            }

horizontal_store:
                {
                    register u8 *store_base asm("r0") = D_02034B4C;
                    register u32 offset asm("r2") = 0xA1AF;
                    register u8 *count_ptr asm("r1");
                    register u8 *destination asm("r0");
                    register u32 count asm("r1");
                    register s32 value asm("r1");
                    register s32 step asm("r4");

                    __asm__("" : "+r"(store_base));
                    __asm__("" : "+r"(offset));
                    count_ptr = store_base + offset;
                    offset += 4;
                    destination = store_base + offset;
                    count = *count_ptr;
                    destination += count;
                    __asm__("" : "=r"(step));
                    value = (s32)candidate >> 24;
                    value += step;
                    *destination = value;
                }
                return;
            }
        }
    }
}
