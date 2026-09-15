#include "m2c_prelude.h"

struct AB06Record {
    u32 flags;
    u8 kind;
    u8 pad05;
    u16 state;
    s32 x;
    s32 y;
    s32 x_delta;
    s32 y_delta;
    u8 pad18[0x30];
};

extern struct AB06Record D_020325A0[];
extern s32 func_080AC098(struct AB06Record *);

void sub_080AB06C(struct AB06Record *record) {
    u8 i;
    struct AB06Record *other;
    s32 record_y;
    s32 adjusted_record_y;
    s32 other_y;
    s32 dx;
    register s32 dy asm("r0");
    s32 abs_dx;
    register s32 abs_dy asm("r4");

    if ((u16)(record->state - 6) <= 1) {
        return;
    }
    if (record->state == 0xFF) {
        return;
    }
    if (record->state == 8) {
        return;
    }
    if (record->flags & 4) {
        return;
    }

    i = 0;
    do {
        other = &D_020325A0[i];
        if ((other->flags & 1) && other != record && other->state != 6 &&
            other->state != 7 && other->state != 0xFF && other->state != 8 &&
            !(other->flags & 4)) {
            record_y = record->y;
            if ((func_080AC098(record) << 24) == 0) {
                adjusted_record_y = record_y + 0x800;
            } else {
                adjusted_record_y = record_y;
            }
            other_y = other->y;
            if ((func_080AC098(other) << 24) == 0) {
                other_y += 0x800;
            }

            {
                register s32 near_dy asm("r0");
                s32 near_dx;

                near_dx = (record->x + record->x_delta) - other->x;
                near_dy = (adjusted_record_y + record->y_delta) - other_y;
                if (near_dx < 0) {
                    near_dx = -near_dx;
                }
                if (near_dy < 0) {
                    near_dy = -near_dy;
                }
                asm volatile("" :: "r"(near_dx));
                if (near_dx <= 0xFFF && near_dy <= 0xFFF) {
                    abs_dx = record->x - other->x;
                    dx = abs_dx;
                    abs_dy = adjusted_record_y - other_y;
                    dy = abs_dy;
                    if (abs_dx < 0) {
                        abs_dx = -abs_dx;
                    }
                    if (abs_dy < 0) {
                        abs_dy = -abs_dy;
                    }
                    if (abs_dx >= abs_dy) {
                        if (dx >= 0) {
                            record->x_delta = 0x1000 - abs_dx;
                        } else {
                            record->x_delta = abs_dx - 0x1000;
                        }
                    } else if (dy >= 0) {
                        record->y_delta = 0x1000 - abs_dy;
                    } else {
                        dy = abs_dy - 0x1000;
                        record->y_delta = dy;
                    }
                }
            }
        }
        i++;
    } while (i <= 13);
}
