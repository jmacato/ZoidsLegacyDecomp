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
    u8 padB8[0];
    s32 target_x;
    s32 target_y;
};

extern struct Record D_020325A0[];
extern struct State D_020329AC;
extern u8 D_02032A6C[];
extern void func_08094564(s32, u16);
extern u16 func_080A9A54(void *);
extern u8 func_080A9EF0(s32);

void sub_080AABCC(struct Record *arg0) {
    u8 old_value;
    struct Record *record;
    u8 i;

    old_value = arg0->value;
    record = &D_020325A0[func_080A9EF0(0)];
    if (record->flags & 1) {
        if (record->status == 0) {
            arg0->status = 0;
        } else {
            if ((arg0->x != D_020329AC.pair[0].x) ||
                (arg0->y != D_020329AC.pair[0].y)) {
                arg0->status = 2;
            } else {
                arg0->status = 0;
            }
            arg0->x = D_020329AC.pair[0].x;
            arg0->y = D_020329AC.pair[0].y;
            arg0->value = D_02032A6C[0];
            arg0->pad1A = D_02032A6C[0];
            asm volatile("" : : "r"(arg0));
            asm volatile("" : : "r"(arg0));
            i = 0;
            do {
                D_020329AC.pair[i].x = D_020329AC.pair[i + 1].x;
                D_020329AC.pair[i].y = D_020329AC.pair[i + 1].y;
                D_02032A6C[i] = D_02032A6C[i + 1];
                i++;
            } while (i <= 22);
            if (!(record->flags & 0x10)) {
                D_020329AC.target_x = record->x;
                D_020329AC.target_y = record->y;
            } else {
                D_020329AC.target_x = record->x +
                    (*(s16 *)(record->extra + 8) << 8);
                D_020329AC.target_y = record->y +
                    ((*(s16 *)(record->extra + 10) + 2) << 8);
            }
            D_02032A6C[23] = record->value;
        }
    }
    {
        register s32 status_r0 asm("r0");
        status_r0 = arg0->status;
        asm volatile("" : "+r"(status_r0));
        if (status_r0 == 0) goto status_zero;
        if (status_r0 < 0) goto done;
        if (status_r0 > 3) goto done;
    }
    if (old_value != arg0->value) goto nonzero_callback;
    if (arg0->previous_status != 0) goto done;
    goto nonzero_callback;

status_zero:
    if (old_value != arg0->value) goto zero_callback;
    if (arg0->previous_status == 0) goto done;
zero_callback:
    func_08094564((s32)arg0->extra, func_080A9A54(arg0));
    goto done;

nonzero_callback:
    func_08094564((s32)arg0->extra, func_080A9A54(arg0));
done:
    arg0->previous_status = arg0->status;
}
