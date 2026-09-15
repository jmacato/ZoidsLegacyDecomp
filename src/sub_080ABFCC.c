#include "m2c_prelude.h"

struct OutputABFCC {
    u8 pad_0[4];
    u16 x;
    u16 y;
};

struct RecordABFCC {
    u32 flags;
    u32 pad_04;
    s32 x;
    s32 y;
    u8 pad_10[0x10];
    struct OutputABFCC *output;
    struct OutputABFCC *mirror;
    u8 pad_28[0x20];
};

void sub_080ABFCC(void)
{
    register u32 i asm("r4") = 0;
    register struct RecordABFCC *base asm("r8") =
        (struct RecordABFCC *)0x020325A0;
    register s32 *camera asm("r12");
    s32 threshold;
    register s32 wrap_offset asm("r6");
    register s32 screen_offset asm("r5");

    {
        register s32 *camera_init asm("r1") = (s32 *)0x03000054;
        register s32 screen_init asm("r0");

        camera = camera_init;
        asm volatile("" : "+r"(camera));
        threshold = 0xEFFFF;
        asm volatile("" : "+r"(threshold));
        wrap_offset = -0x10000;
        asm volatile("" : "+r"(wrap_offset));
        screen_init = 0x80;
        screen_init <<= 5;
        asm volatile("" : "+r"(screen_init));
        screen_offset = screen_init;
    }

    do {
        register u32 offset asm("r0") = i << 3;
        register struct RecordABFCC *base_view asm("r1");
        register struct RecordABFCC *record asm("r3");

        offset += i;
        offset <<= 3;
        base_view = base;
        record = (struct RecordABFCC *)(offset + (u32)base_view);

        if ((record->flags & 1) != 0) {
            {
                register s32 *camera_view asm("r1") = camera;
                register s32 camera_x asm("r0");
                register s32 x asm("r2");
                register s32 x_view asm("r1");

                asm volatile("" : "+r"(camera_view));
                camera_x = camera_view[0];
                x = record->x;
                if (camera_x <= threshold) {
                    goto x_normal;
                }
                camera_x += wrap_offset;
                x_view = x;
                if (x_view < camera_x) {
                    goto x_wrap;
                }
x_normal:
                {
                    register struct OutputABFCC *output asm("r1") = record->output;
                    register s32 adjusted asm("r0") = x;

                    if (adjusted < 0) {
                        adjusted += 0xFF;
                    }
                    output->x = adjusted >> 8;
                    goto x_done;
                }
x_wrap:
                {
                    register struct OutputABFCC *output asm("r2") = record->output;
                    register s32 adjusted asm("r0") = x_view;

                    if (adjusted < 0) {
                        adjusted += 0xFF;
                    }
                    adjusted >>= 8;
                    adjusted += screen_offset;
                    output->x = adjusted;
                }
x_done:
                ;
            }

            {
                register s32 *camera_view asm("r1") = camera;
                register s32 camera_y asm("r0");
                register s32 y asm("r2");
                register s32 y_view asm("r1");

                asm volatile("" : "+r"(camera_view));
                camera_y = camera_view[1];
                y = record->y;
                if (camera_y <= threshold) {
                    goto y_normal;
                }
                camera_y += wrap_offset;
                y_view = y;
                if (y_view < camera_y) {
                    goto y_wrap;
                }
y_normal:
                {
                    register struct OutputABFCC *output asm("r1") = record->output;
                    register s32 adjusted asm("r0") = y;

                    if (adjusted < 0) {
                        adjusted += 0xFF;
                    }
                    output->y = adjusted >> 8;
                    goto y_done;
                }
y_wrap:
                {
                    register struct OutputABFCC *output asm("r2") = record->output;
                    register s32 adjusted asm("r0") = y_view;

                    if (adjusted < 0) {
                        adjusted += 0xFF;
                    }
                    adjusted >>= 8;
                    adjusted += screen_offset;
                    output->y = adjusted;
                }
y_done:
                ;
            }

            {
                register struct OutputABFCC *mirror asm("r1") = record->mirror;

                if (mirror != 0) {
                    mirror->x = record->output->x;
                    mirror = record->mirror;
                    mirror->y = record->output->y;
                }
            }
        }
        {
            register u32 next asm("r0") = i + 1;

            next <<= 24;
            i = next >> 24;
        }
    } while (i <= 13U);
}
