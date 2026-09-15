#include "m2c_prelude.h"

struct ScrollRecord {
    u8 pad0[6];
    u16 state;
    s32 x;
    s32 y;
};

extern s32 D_03000054[];
extern u16 D_020324A4[];
extern s32 D_02032E88[];
extern u16 D_0202ECF4;

void sub_080ABE70(struct ScrollRecord *arg) {
    register struct ScrollRecord *record asm("r2") = arg;
    s32 *camera;
    register s32 base_x asm("r6");
    register s32 x_raw asm("r5");
    register s32 x_delta asm("r3");
    register s32 y_delta asm("r4");
    register s32 value asm("r0");
    s32 *camera_temp;

    if (record->state != 0 && record->state != 6) {
        return;
    }

    value = record->x + 0xFFFF8800;
    camera_temp = D_03000054;
    base_x = camera_temp[0];
    value -= base_x;
    camera = camera_temp;
    if (value < 0) {
        value += 7;
    }
    x_raw = value >> 3;
    x_delta = x_raw;
    asm volatile("" : "+r"(camera));

    value = record->y + 0xFFFFB000;
    value -= camera[1];
    if (value < 0) {
        value += 7;
    }
    y_delta = value >> 3;

    if (D_0202ECF4 == 0) {
        if (x_delta < -0x800) {
            x_delta += D_020324A4[0] << 8;
        } else if (x_delta > 0x800) {
            x_delta -= D_020324A4[0] << 8;
        }

        if (y_delta < -0x800) {
            y_delta += D_020324A4[1] << 8;
        } else if (y_delta > 0x800) {
            y_delta -= D_020324A4[1] << 8;
        }
    }

    else {
        if (x_raw < 0) {
            register s32 bound asm("r1") = -base_x;
            if (bound < 0) {
                bound += 7;
            }
            value = bound >> 3;
            if (x_delta < value) {
                x_delta = value;
            }
        } else if (x_raw > 0) {
            value = (D_020324A4[0] - 30) << 11;
            value -= base_x;
            if (value < 0) {
                value += 7;
            }
            value >>= 3;
            if (x_delta > value) {
                x_delta = value;
            }
        }

        if (y_delta < 0) {
            value = -camera[1];
            if (value < 0) {
                value += 7;
            }
            value >>= 3;
            if (y_delta < value) {
                y_delta = value;
            }
        } else if (y_delta > 0) {
            value = (D_020324A4[1] - 20) << 11;
            value -= camera[1];
            if (value < 0) {
                value += 7;
            }
            value >>= 3;
            if (y_delta > value) {
                y_delta = value;
            }
        }

    }

    if (D_02032E88[0] != 0) {
        s32 camera_x = camera[0] + x_delta;
        s32 camera_y = camera[1] + y_delta;
        camera[0] = camera_x & 0xFFFFF;
        camera[1] = camera_y & 0xFFFFF;
    }
    if (D_02032E88[1] != 0) {
        s32 camera_x = camera[2] + x_delta;
        s32 camera_y = camera[3] + y_delta;
        camera[2] = camera_x & 0xFFFFF;
        camera[3] = camera_y & 0xFFFFF;
    }
}
