#include "m2c_prelude.h"

u8 func_0809ACC4(s32);

extern u8 D_03006058;
extern s32 D_03006050;
extern u8 D_030009A8[];
extern u8 D_0300603C;
extern u8 D_030009B8;
extern u8 D_03000999;
extern u8 D_0300099A[];
extern u8 *D_03006040;
extern u8 *D_03006048;

u8 sub_0809AEF4(void) {
    u8 *state;
    u8 *state_load;
    u8 value;
    u8 *src;
    u8 *dst;
    u8 *first;
    u8 *check;
    u8 count;

    if (func_0809ACC4(0) != 1) goto done;

    state_load = &D_03006058;
    value = *state_load;
    state = state_load;
    asm volatile("" : "+&r"(state) : "r"(state_load));
    if (value == 0) {
        return 1;
    }

    if (value > 1 && D_03006050 <= 0) {
        if (D_0300603C != 0) {
            value = D_030009B8;
            if (value != 0) goto done;
            check = &D_030009B8;
            check -= 15;
            if (*check == 0) {
                goto clear_state;
            }
            goto clear_marker;
        }
        value = D_030009A8[0];
        if (value != 0) goto done;
        if (D_030009A8[17] != 0) goto clear_marker;
clear_state:
        *state = value;
        return 1;
clear_marker:
        D_03000999 = value;
        goto done;
    }

    if (D_0300603C != 0) {
        {
            register u8 check_value asm("r0");
            check_value = D_030009B8;
            if (check_value == *state) goto copy;
        }
        goto done;
    }
    {
        register u8 check_value asm("r0");
        check_value = D_030009A8[0];
        if (check_value != *state) goto done;
    }

copy:
    {
        register u8 state_value asm("r0");
        state_value = *state;
        if (state_value == 1) goto fixed_copy;
    }
    goto streaming_copy;
fixed_copy:
    {
        src = D_03006040;
        dst = D_0300099A;
        count = 0;
        first = dst - 1;
        do {
            *dst = *src;
            src++;
            dst++;
            count++;
        } while (count <= 13);
    }
    goto after_copy;
streaming_copy:
    {
        dst = D_0300099A;
        count = 0;
        first = dst - 1;
        do {
            *dst = *D_03006048;
            D_03006048 += 1;
            dst++;
            D_03006050--;
            count++;
        } while (count <= 13);
    }
after_copy:
    {
        register u8 state_value asm("r0");
        state_value = *state;
        *first = state_value;
        state_value++;
        *state = state_value;
    }
done:
    return 0;
}
