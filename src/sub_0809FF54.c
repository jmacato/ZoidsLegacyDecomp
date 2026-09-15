#include "m2c_prelude.h"

extern s32 func_080ECD5C(s32);
extern void func_080ED17C(s32);

extern s32 D_02021690;
extern s32 D_02031980;
extern s32 D_02031984;
extern s32 D_03000010;
extern s32 D_03000054[];
extern u8 D_020316F4;
extern s32 D_02032E88[];
extern u16 D_020324A4[];
extern s32 D_030033C4[];

void sub_0809FF54(void) {
    if (D_02021690 == 3) {
        register s32 *velocity_x asm("r2") = &D_02031980;
        s32 *rng;
        register s32 *velocity_base asm("r6");

        *velocity_x = 0;
        D_02031984 = 0;
        rng = &D_03000010;
        velocity_base = velocity_x;

        for (;;) {
            register s32 delta_x asm("r4");
            register s32 delta_y asm("r2");
            register s32 random_value asm("r1");
            register s32 current asm("r2");
            register s32 rounded asm("r0");

            random_value = ((u32)(func_080ECD5C(*rng) * 7) >> 15) - 3;
            random_value <<= 8;
            current = *velocity_base;
            rounded = current;
            if (current < 0) {
                rounded += 0xFF;
            }
            delta_x = random_value - ((rounded >> 8) << 8);

            random_value = ((u32)(func_080ECD5C(*rng) * 7) >> 15) - 3;
            random_value <<= 8;
            {
                register s32 *velocity_y asm("r5") = &D_02031984;
                register s32 y_current asm("r3") = *velocity_y;
                register s32 y_rounded asm("r2") = y_current;
                register s32 new_y asm("r0");

                if (y_current < 0) {
                    y_rounded += 0xFF;
                }
                delta_y = random_value - ((y_rounded >> 8) << 8);
                *velocity_base += delta_x;
                new_y = y_current + delta_y;
                *velocity_y = new_y;
            }

            {
                register s32 *camera asm("r1") = D_03000054;
                register s32 camera_current asm("r0") = camera[0];
                register s32 camera_x asm("r3") = camera_current + delta_x;

                camera[0] = camera_x;
                camera[1] += delta_y;
                if (D_020316F4 != 0 && D_02032E88[1] != 0) {
                    s32 limit;

                    if (camera_x < 0) {
                        limit = 0;
                    } else {
                        limit = (D_020324A4[0] << 11) - 0xF000;
                        if (camera_x <= limit) {
                            goto clamp_y;
                        }
                    }
                    camera[0] = limit;

clamp_y:
                    {
                        register s32 *camera_y asm("r3") = camera;
                        register s32 y asm("r2") = camera_y[1];

                        if (y < 0) {
                            camera_y[1] = 0;
                        } else {
                            limit = (D_020324A4[1] << 11) - 0xA000;
                            if (y > limit) {
                                camera[1] = limit;
                            }
                        }
                    }
                    {
                        register s32 *copy asm("r0") = D_03000054;
                        copy[2] = copy[0];
                        copy[3] = copy[1];
                    }
                }
            }
            func_080ED17C(1);
        }
    }

    if (D_02021690 == 9) {
        register s32 *rng asm("r5") = &D_03000010;
        register s32 *state asm("r4") = D_030033C4;

        for (;;) {
            state[5] = ((u32)(func_080ECD5C(*rng) * 7) >> 15) + 0x75;
            state[6] = ((u32)(func_080ECD5C(*rng) * 7) >> 15) + 0x55;
            func_080ED17C(1);
        }
    }
}
