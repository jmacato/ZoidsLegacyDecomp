#include "m2c_prelude.h"

struct Vec3sD2810 {
    s16 x;
    s16 y;
    s16 z;
};

struct EffectD2810 {
    u8 filler00[4];
    s32 x;
    s32 y;
    u8 filler0C[0x80];
    s32 initialized;
    s32 angle;
    u16 tilt;
    u16 filler96;
    s32 progress;
};

struct FrameD2810 {
    s16 matrix[16];
    u32 angles[2];
    struct Vec3sD2810 transformed;
    u32 counter;
    s32 cosine_delta;
    struct Vec3sD2810 *transformed_ptr;
};

void func_0809378C(s16 *, s16 *);
void func_08093678(void *, void *, struct Vec3sD2810 *);
s32 func_080ECD24(s32, s32);
s32 func_080ECD98(s32, s32);
s32 func_08092A90(s32);
s32 func_08092ADC(s32);
void func_0809534C(void);
void func_08095114(void *);
void func_080955A0(void *, s32, s32, s32);
extern s16 D_020348E4[];

void sub_080D2810(struct EffectD2810 *arg0)
{
    register struct EffectD2810 *effect asm("r8") = arg0;
    struct FrameD2810 frame;
    register struct Vec3sD2810 *transformed asm("sl");
    register struct EffectD2810 *tail_effect asm("r3");
    register u32 next asm("r0");

    {
        register u32 lower asm("r0") = effect->angle;
        register u32 upper asm("r1");
        register u32 mask asm("r3");
        register u32 *angles asm("r1");

        lower += 4;
        lower <<= 16;
        mask = 0xFFFF0000;
        upper = effect->tilt;
        upper <<= 16;
        lower >>= 16;
        lower |= upper;
        frame.angles[0] = lower;
        {
            register struct EffectD2810 *progress_base asm("r0") = effect;
            register u32 progress asm("r2") = (u16)progress_base->progress;
            register u32 packed asm("r0");

            angles = frame.angles;
            packed = angles[1];
            packed &= mask;
            packed |= progress;
            angles[1] = packed;
        }
        frame.counter = 0;
        angles += 2;
        frame.transformed_ptr = (struct Vec3sD2810 *)angles;
        transformed = (struct Vec3sD2810 *)angles;
    }

    for (;;) {
        register u32 loop_counter asm("r2") = frame.counter;
        s32 record_index = loop_counter * 7;
        register s16 *transformed_x asm("r6");
        register s32 cosine asm("r5");
        register s32 sine asm("r9");
        s32 direction;

        {
            register u32 record_address asm("r0") = record_index << 1;
            register u32 record_base asm("r3") = (u32)D_020348E4;
            register u32 kind asm("r1");

            record_address += record_base;
            kind = 3;
            *(s16 *)record_address = kind;
        }
        {
            register s16 *angles asm("r0");

            asm volatile("add %0, sp, #32" : "=r"(angles));
            func_0809378C(angles, frame.matrix);
        }
        func_08093678(frame.matrix, (void *)0x087A2A48, transformed);

        asm volatile("add %0, sp, #40" : "=r"(transformed_x));
        {
            register struct Vec3sD2810 *y_base asm("r2");
            register s32 projected_x asm("r0") = *transformed_x;
            register s32 projected_y asm("r1");
            register u32 y_offset asm("r3");

            y_base = transformed;
            asm volatile(
                "mov %1, #2\n\t"
                "ldrsh %0, [%2, %1]"
                : "=r"(projected_y), "=r"(y_offset)
                : "r"(y_base));
            direction = (u16)func_080ECD24(projected_x, projected_y);
        }
        {
            register struct Vec3sD2810 *z_load asm("r0") = transformed;
            register u32 z asm("r1") =
                *(u16 *)((u8 *)z_load + 4);
            register s32 new_z asm("r0") = 0x80 - z;
            register struct Vec3sD2810 *z_store asm("r1") = transformed;

            z_store->z = new_z;
        }
        direction >>= 8;
        cosine = func_08092A90(direction);
        asm volatile("" : "+r"(cosine));
        cosine = (u16)cosine;
        sine = (u16)func_08092ADC(direction);

        {
            register u32 record_base asm("r2");
            register struct EffectD2810 *effect_view asm("r3");
            register u32 record_address asm("r0");
            register u32 record3 asm("r4");
            register s32 projected_x asm("r0");
            register s32 adjusted_cosine asm("r1");

            record_address = (record_index + 1) << 1;
            record_base = (u32)D_020348E4;
            record_address += record_base;
            effect_view = effect;
            *(s16 *)record_address = effect_view->x;
            record_address = (record_index + 2) << 1;
            record_address += record_base;
            *(s16 *)record_address = effect_view->y;
            record_address = (record_index + 3) << 1;
            asm volatile("" : "+r"(record_address));
            record3 = record_address;
            record3 += record_base;
            {
                register u32 x_offset asm("r1");

                asm volatile(
                    "mov %1, #0\n\t"
                    "ldrsh %0, [%2, %1]"
                    : "=r"(projected_x), "=r"(x_offset)
                    : "r"(transformed_x));
            }
            cosine = (s16)cosine;
            adjusted_cosine = cosine;
            if (cosine < 0) {
                adjusted_cosine += 15;
            }
            frame.cosine_delta = adjusted_cosine >> 4;
            projected_x += frame.cosine_delta;
            {
                s32 projection;

                {
                    register s32 call_x asm("r0") = projected_x << 7;
                    register struct Vec3sD2810 *z_base asm("r2") = transformed;
                    register u32 z_offset asm("r3");
                    register s32 z asm("r1");

                    asm volatile(
                        "mov %1, #4\n\t"
                        "ldrsh %0, [%2, %1]"
                        : "=r"(z), "=r"(z_offset)
                        : "r"(z_base));
                    projection = func_080ECD98(call_x, z);
                }
                {
                    register struct EffectD2810 *effect_after asm("r2") =
                        effect;

                    *(s16 *)record3 = effect_after->x + projection;
                }
            }
        }

        {
            register u32 record_address asm("r0") =
                (record_index + 4) << 1;
            register u32 record4 asm("r6");
            register u32 record_base asm("r3") = (u32)D_020348E4;

            record4 = record_address + record_base;
            {
                register s32 projected_y asm("r1") = transformed->y;
                register s32 sine_source asm("r3") = sine;
                register s32 sine_shift asm("r0") = sine_source << 16;
                register s32 signed_sine asm("r4") = sine_shift >> 16;
                register s32 adjusted_sine asm("r0") = signed_sine;

                asm volatile("" : "+r"(sine_source));
                if (signed_sine < 0) {
                    adjusted_sine += 15;
                }
                adjusted_sine >>= 4;
                sine = adjusted_sine;
                {
                    register s32 call_x asm("r0") =
                        (projected_y - sine) << 7;
                    register struct Vec3sD2810 *z_base asm("r2") =
                        transformed;
                    register u32 z_offset asm("r3");
                    register s32 z asm("r1");
                    s32 projection;

                    asm volatile(
                        "mov %1, #4\n\t"
                        "ldrsh %0, [%2, %1]"
                        : "=r"(z), "=r"(z_offset)
                        : "r"(z_base));
                    projection = func_080ECD98(call_x, z);
                    {
                        register struct EffectD2810 *effect_after asm("r2") =
                            effect;

                        *(s16 *)record4 = effect_after->y + projection;
                    }
                }
            }
        }
        {
            register u32 record_address asm("r0") =
                (record_index + 5) << 1;
            register u32 record5 asm("r6");
            register u32 record_base asm("r3") = (u32)D_020348E4;

            record5 = record_address + record_base;
            {
                register s32 projected_x asm("r0");
                s32 projection;

                {
                    register struct Vec3sD2810 *x_base asm("r1") =
                        frame.transformed_ptr;
                    register u32 x_offset asm("r2");

                    asm volatile(
                        "mov %1, #0\n\t"
                        "ldrsh %0, [%2, %1]"
                        : "=r"(projected_x), "=r"(x_offset)
                        : "r"(x_base));
                }
                {
                    register s32 cosine_delta asm("r3") =
                        frame.cosine_delta;

                    projected_x -= cosine_delta;
                }
                projected_x <<= 7;
                {
                    register struct Vec3sD2810 *z_base asm("r2") =
                        transformed;
                    register u32 z_offset asm("r3");
                    register s32 z asm("r1");

                    asm volatile(
                        "mov %1, #4\n\t"
                        "ldrsh %0, [%2, %1]"
                        : "=r"(z), "=r"(z_offset)
                        : "r"(z_base));
                    projection = func_080ECD98(projected_x, z);
                }
                {
                    register struct EffectD2810 *effect_after asm("r2") =
                        effect;

                    *(s16 *)record5 = effect_after->x + projection;
                }
            }
        }
        {
            register u32 record_address asm("r0") =
                (record_index + 6) << 1;
            register u32 record6 asm("r5");
            register u32 record_base asm("r3") = (u32)D_020348E4;

            asm volatile("" : "+r"(record_index));
            record6 = record_address + record_base;
            {
                register s32 projected_y asm("r0");
                s32 projected;

                {
                    register struct Vec3sD2810 *y_base asm("r1") =
                        transformed;
                    register u32 y_offset asm("r2");

                    asm volatile(
                        "mov %1, #2\n\t"
                        "ldrsh %0, [%2, %1]"
                        : "=r"(projected_y), "=r"(y_offset)
                        : "r"(y_base));
                }
                projected_y += sine;
                projected_y <<= 7;
                {
                    register struct Vec3sD2810 *z_base asm("r3") =
                        transformed;
                    register u32 z_offset asm("r2");
                    register s32 z asm("r1");

                    asm volatile(
                        "mov %1, #4\n\t"
                        "ldrsh %0, [%2, %1]"
                        : "=r"(z), "=r"(z_offset)
                        : "r"(z_base));
                    projected = func_080ECD98(projected_y, z);
                }

                tail_effect = effect;
                *(s16 *)record6 = tail_effect->y + projected;
            }
        }

        {
            register u8 *angle_load_base asm("r1") = (u8 *)&frame;
            register u32 angle asm("r0") =
                *(u16 *)(angle_load_base + 32);
            register u16 *angle_store asm("r1");

            angle += 0x55;
            asm volatile("add %0, sp, #32" : "=r"(angle_store));
            *angle_store = angle;
        }
        next = frame.counter + 1;
        next <<= 24;
        next >>= 24;
        frame.counter = next;
        if (next > 2) {
            break;
        }
    }

    {
        register s16 *records asm("r5") = D_020348E4;
        register u32 stored_counter asm("r2");

        next <<= 3;
        stored_counter = frame.counter;
        next -= stored_counter;
        next <<= 1;
        next += (u32)records;
        *(s16 *)next = 0;
        {
            register volatile u16 *blend asm("r6") =
                (volatile u16 *)0x03000050;
            register s32 *progress_ptr asm("r3") = &tail_effect->progress;
            register u32 progress asm("r2") = *progress_ptr;

            *blend = ((0x10 - (progress >> 2)) << 8) | 0x10;
            if (progress == 0x40) {
                func_0809534C();
                *(volatile u16 *)0x0300004E = 0;
                func_08095114(effect);
            } else {
                register s32 *angle_ptr asm("r1") = &effect->angle;

                *angle_ptr += 8;
                *progress_ptr += 1;
                {
                    register s32 *initialized_ptr asm("r4") =
                        &effect->initialized;

                    if (*initialized_ptr == 0) {
                        func_080955A0(records, 0x3F3F, 0x1F1F, 8);
                        {
                            register volatile u16 *display_control asm("r1") =
                                (volatile u16 *)0x0300004E;
                            register u32 value asm("r3") = 0x3757;
                            register u32 store_value asm("r0");

                            asm volatile("" : "+r"(value));
                            store_value = value;
                            *display_control = store_value;
                        }
                        *blend = 0x1010;
                        *(volatile u16 *)0x05000000 = 0x3FF;
                        *initialized_ptr += 1;
                    }
                }
            }
        }
    }
}
