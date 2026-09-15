#include "m2c_prelude.h"

struct Record {
    u32 flags;
    u8 pad04[4];
    s32 x;
    s32 y;
    u8 pad10[8];
    u8 status;
    u8 previous_status;
    u8 pad1A;
    u8 value;
    u8 pad1C[4];
    u8 *extra;
    u8 pad24[0x24];
};

struct Pair {
    s32 x;
    s32 y;
};

struct State {
    struct Pair pair[23];
    s32 target_x;
    s32 target_y;
};

extern struct Record D_020325A0[];
extern struct State D_020329AC;
extern u8 D_02032A6C[];
extern void func_08094564(s32, u16);
extern u16 func_080A9A54(void *);
extern u8 func_080A9EF0(s32);
extern void func_080A9F40(u8);

s32 sub_080AAD34(struct Record *arg0)
{
    u8 old_value;
    struct Record *record;
    u8 i;

    old_value = arg0->value;
    record = &D_020325A0[func_080A9EF0(0)];
    if (record->flags & 1) {
        arg0->status = 2;
        arg0->x = D_020329AC.pair[0].x;
        arg0->y = D_020329AC.pair[0].y;
        arg0->value = D_02032A6C[0];
        arg0->pad1A = D_02032A6C[0];
        i = 0;
        do {
            D_020329AC.pair[i].x = D_020329AC.pair[i + 1].x;
            D_020329AC.pair[i].y = D_020329AC.pair[i + 1].y;
            D_02032A6C[i] = D_02032A6C[i + 1];
            i++;
        } while (i <= 22);
        D_020329AC.target_x = record->x;
        D_020329AC.target_y = record->y;
        D_02032A6C[23] = record->value;
    }

    {
        register s32 status_r0 asm("r0");
        status_r0 = arg0->status;
        asm volatile("" : "+r"(status_r0));
        if (status_r0 == 0) goto status_zero;
        if (status_r0 < 0) goto done_callback;
        if (status_r0 > 3) goto done_callback;
    }
    if (old_value != arg0->value) goto nonzero_callback;
    if (arg0->previous_status != 0) goto done_callback;
    goto nonzero_callback;

status_zero:
    if (old_value != arg0->value) goto zero_callback;
    if (arg0->previous_status == 0) goto done_callback;

zero_callback:
    func_08094564((s32)arg0->extra, func_080A9A54(arg0));
    goto done_callback;

nonzero_callback:
    func_08094564((s32)arg0->extra, func_080A9A54(arg0));
done_callback:
    arg0->previous_status = arg0->status;
    if ((arg0->x == record->x) && (arg0->y == record->y)) {
        func_080A9F40(arg0->pad04[1]);
        return 1;
    }
    return 0;
}
