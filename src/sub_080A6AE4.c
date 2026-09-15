#include "m2c_prelude.h"

extern s32 func_080ECD5C(s32);
extern void func_080ED17C(s32);

extern s32 D_03000010;
extern s32 D_03000054[];
extern u16 D_020324A4[];

void sub_080A6AE4(void)
{
    u32 counter;
    s32 vx;
    s32 vy;
    s32 yoff;
    s32 done;
    s32 zero;
    u16 *dims;
    s32 *cam;
    s32 limit;

    counter = 0;
    vy = 0;
    vx = 0;
    yoff = 0;
    done = 0;
    zero = 0;
    dims = D_020324A4;

loop:
    if (counter > 43) {
        yoff -= 16;
    }
    if (counter <= 0x12B) {
        s32 *rngp;
        s32 random_value;
        s32 rounded;
        s32 rounded_x;
        s32 dx;
        s32 camx;
        s32 y;

        rngp = &D_03000010;
        random_value = (u32)(func_080ECD5C(*rngp) * 7) >> 15;
        random_value -= 3;
        random_value <<= 8;
        rounded_x = vx;
        if (vx < 0) {
            rounded_x += 0xFF;
        }
        rounded_x >>= 8;
        rounded_x <<= 8;
        dx = random_value - rounded_x;

        random_value = (u32)(func_080ECD5C(*rngp) * 7) >> 15;
        random_value -= 3;
        random_value <<= 8;
        rounded = vy;
        if (vy < 0) {
            rounded += 0xFF;
        }
        rounded >>= 8;
        rounded <<= 8;
        rounded = random_value - rounded;

        vx += dx;
        vy += rounded;
        cam = D_03000054;
        camx = cam[0] + dx;
        cam[0] = camx;
        cam[1] += rounded;

        if (camx < 0) {
            limit = zero;
            goto store_x1;
        }
        limit = (dims[0] << 11) - 0xF000;
        if (camx > limit) {
store_x1:
            cam[0] = limit;
        }
        y = cam[1];
        if (y < 0) {
            cam[1] = zero;
        } else {
            limit = (dims[1] << 11) - 0xA000;
            if (y > limit) {
                cam[1] = limit;
            }
        }
        counter = (u16)(counter + 1);
    } else {
        s32 camx2;
        s32 y2;

        cam = D_03000054;
        camx2 = cam[0] - vx;
        cam[0] = camx2;
        cam[1] -= vy;

        if (camx2 < 0) {
            limit = zero;
            goto store_x2;
        }
        limit = (dims[0] << 11) - 0xF000;
        if (camx2 > limit) {
store_x2:
            cam[0] = limit;
        }
        y2 = cam[1];
        if (y2 < 0) {
            limit = zero;
            goto store_y2;
        }
        limit = (dims[1] << 11) - 0xA000;
        if (y2 > limit) {
store_y2:
            cam[1] = limit;
        }
        done = 1;
    }

    asm volatile("" : : "r"(cam), "r"(cam), "r"(cam), "r"(cam), "r"(cam), "r"(cam));
    asm volatile("" : : "r"(cam), "r"(cam), "r"(cam), "r"(cam), "r"(cam), "r"(cam));
    asm volatile("" : : "r"(cam), "r"(cam), "r"(cam), "r"(cam), "r"(cam), "r"(cam));
    cam[2] = cam[0];
    cam[3] = cam[1] + yoff;
    func_080ED17C(1);
    if (done == 0) {
        goto loop;
    }
}
