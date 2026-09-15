#include "m2c_prelude.h"

struct Vec3sDD298 {
    s16 x;
    s16 y;
    s16 z;
};

struct OwnerDD298 {
    u32 flags;
    s32 x;
    s32 y;
    void *children[32];
    u32 state;
    s32 timer;
    s32 saved_x;
    u32 tilt;
};

struct FrameDD298 {
    s16 matrix[16];
    u32 angles[2];
    struct Vec3sDD298 transformed;
    s32 sine;
    u32 counter;
    s32 cosine;
    s32 signed_sine;
    s32 *timer;
    u32 *tilt;
    s16 *records;
};

void func_08095114(void *);
void func_0809534C(void);
void func_080955A0(void *, s32, s32, s32);
void func_08093678(s16 *, void *, struct Vec3sDD298 *);
void func_0809378C(u32 *, s16 *);
s32 func_08092A90(u32);
u16 func_08092ADC(u32);
void *func_080D2450(void *, s32, s32, s32, s32, s32, s32, s32);
void func_080D2660(void *, s32, s32, s32, s32, s32, s32, s32, s32);
void func_080D12A0(s32, s32);
void func_080D2790(s32);
s32 func_080ECD24(s32, s32);
u32 func_080ECD5C(u32);
s32 func_080ECD98(s32, s32);
s32 func_080ECF78(s32, s32);

extern u32 D_03000010;
extern s32 D_02034034;
extern s32 D_03000054[];
extern volatile u16 D_0300004E;
extern volatile u16 D_03000050;

void sub_080DD298(struct OwnerDD298 *owner)
{
    struct FrameDD298 frame;
    register u32 next asm("r0");

    switch (owner->state) {
    case 0:
        func_080955A0((void *)0x02034AF4, 0x3F3F, 0x1F1F, 8);
        *(volatile u16 *)0x0300004E = 0x3757;
        *(volatile u16 *)0x05000000 = 0x7FFF;
        *(u8 *)0x03000075 = 2;
        *(u8 *)0x0300603D = 2;
        func_080D2790(0);
        owner->state++;
        /* fall through */
    case 1: {
        register s32 *timer asm("r2") = &owner->timer;
        register u32 lower asm("r0") = *timer + 4;

        lower <<= 16;
        lower >>= 16;
        {
        register u32 mask asm("r6") = 0xFFFF0000;
        register u32 packed asm("r4") = frame.angles[0];

        packed &= mask;
        packed |= lower;
        frame.angles[0] = packed;
        {
            register s32 upper asm("r3") = owner->saved_x;
            register u32 shifted asm("r1");
            register u32 flags asm("r0") = owner->flags;
            register u32 bit asm("r1") = 2;

            flags &= bit;
            frame.timer = timer;
            if (flags != 0) {
                upper += 0x80;
            }
            shifted = upper << 16;
            {
                register u32 low asm("r0") = 0xFFFF;

                low &= packed;
                low |= shifted;
                frame.angles[0] = low;
            }
        }
        {
            register u32 *tilt asm("r3") = &owner->tilt;
            register u32 value asm("r2") = *(u16 *)tilt;
            register u32 *angles asm("r1") = frame.angles;
            register u32 second asm("r0") = angles[1];
            register u32 zero asm("r4");

            second &= mask;
            second |= value;
            angles[1] = second;
            zero = 0;
            frame.counter = zero;
            frame.tilt = tilt;
        }
        }

        {
        register struct Vec3sDD298 *transformed asm("r8") =
            &frame.transformed;
        register s16 *records asm("r3");

        for (;;) {
            register s32 record_index asm("r6");
            register s16 *record2 asm("sl");
            register s16 *record_out asm("r7");
            register u32 projection_r4 asm("r4");
            u16 direction;

            {
                register u32 *angles asm("r0");

                asm volatile("add %0, sp, #52" : "=r"(angles));
                func_0809378C(angles, frame.matrix);
            }
            func_08093678(frame.matrix, (void *)0x087A2B04,
                transformed);
            {
                register struct Vec3sDD298 *z_base asm("r2") =
                    transformed;
                register u32 z asm("r1") = (u16)z_base->z;
                register s32 new_z asm("r0") = 0x80 - z;

                z_base->z = new_z;
            }
            {
                register s32 projected_x asm("r0");
                register u32 x_offset asm("r3");
                register struct Vec3sDD298 *y_base asm("r2") =
                    transformed;
                register s32 projected_y asm("r1");
                register u32 y_offset asm("r4");

                asm volatile(
                    "add %0, sp, #60\n\t"
                    "mov %1, #0\n\t"
                    "ldrsh %0, [%0, %1]"
                    : "=r"(projected_x), "=r"(x_offset));
                asm volatile(
                    "mov %1, #2\n\t"
                    "ldrsh %0, [%2, %1]"
                    : "=r"(projected_y), "=r"(y_offset)
                    : "r"(y_base));
                direction = func_080ECD24(projected_x, projected_y);
            }
            direction >>= 8;
            {
                register u16 cosine asm("r9");
                register u32 cosine_result asm("r0") =
                    func_08092A90(direction);
                register s32 projection asm("r0");

                cosine_result <<= 16;
                cosine_result >>= 16;
                cosine = cosine_result;
                frame.sine = (u16)func_08092ADC(direction);
                {
                    register u32 base asm("r3") = 0x02034AF4;
                    register u32 counter asm("r1") = frame.counter;
                    register u32 index asm("r0") = counter << 3;
                    register u32 record1_address asm("r2");

                    index -= counter;
                    counter = index << 1;
                    counter += base;
                    *(s16 *)counter = 3;
                    index += 1;
                    index <<= 1;
                    record1_address = index + base;
                    if (!(owner->flags & 2)) {
                        *(u16 *)record1_address = *(u16 *)&owner->x;
                    } else {
                        *(u16 *)record1_address = 0xF0 - owner->x;
                    }
                }
                {
                    register u32 base asm("r1") = 0x02034AF4;
                    register u32 counter asm("r2") = frame.counter;
                    register u32 scaled asm("r0") = counter << 3;
                    register u32 address asm("r0");

                    record_index = scaled - counter;
                    address = record_index + 2;
                    address <<= 1;
                    address += base;
                    record2 = (s16 *)address;
                    {
                        register s32 owner_y asm("r0") = owner->y;
                        register s16 *record2_store asm("r3") = record2;

                        *record2_store = owner_y;
                    }
                    address = record_index + 3;
                    address <<= 1;
                    address += base;
                    record_out = (s16 *)address;

                    {
                        register struct Vec3sDD298 *x_base asm("r4") =
                            transformed;
                        register u32 x_offset asm("r0");
                        register s32 projected_x asm("r2");
                        register s32 factor_r0 asm("r0");

                        asm volatile(
                            "mov %1, #0\n\t"
                            "ldrsh %0, [%2, %1]"
                            : "=r"(projected_x), "=r"(x_offset)
                            : "r"(x_base));
                        {
                            register s32 cosine_source asm("r3") = cosine;
                            register s32 signed_cosine asm("r0") =
                                (s16)cosine_source;

                            frame.cosine = signed_cosine;
                        }
                        {
                            register u32 *tilt_ptr asm("r4") = frame.tilt;
                            register u32 tilt_value asm("r0") =
                                *(u16 *)tilt_ptr;
                            register s32 sixty_four asm("r3") = 0x40;

                            factor_r0 = sixty_four - tilt_value;
                        }
                        {
                            register s32 multiplier asm("r4") = frame.cosine;

                            factor_r0 *= multiplier;
                        }
                        {
                            register u32 base_saved asm("r3") = base;

                            if (factor_r0 < 0) {
                                factor_r0 += 0x1FF;
                            }
                            factor_r0 >>= 9;
                            factor_r0 = projected_x + factor_r0;
                            factor_r0 <<= 7;
                            {
                                register u32 z_offset asm("r2");
                                register s32 z asm("r1");

                                projection_r4 = (u32)transformed;
                                asm volatile(
                                    "mov %1, #4\n\t"
                                    "ldrsh %0, [%2, %1]"
                                    : "=r"(z), "=r"(z_offset)
                                    : "r"(projection_r4));
                                frame.records = (s16 *)base_saved;
                                projection = func_080ECD98(factor_r0, z);
                            }
                        }
                    }
                }
                {
                    register s16 *record1_saved asm("r9");
                    register u32 address asm("r1") = record_index + 1;
                    register u32 base asm("r3");

                    address <<= 1;
                    base = (u32)frame.records;
                    address += base;
                    record1_saved = (s16 *)address;
                    {
                        register u32 value asm("r1") =
                            *(u16 *)record1_saved;

                        value += projection;
                        asm volatile("strh %0, [%1]"
                            :
                            : "l"(value), "l"(record_out)
                            : "memory");
                    }

            {
                register u32 address asm("r0") = record_index + 4;

                address <<= 1;
                record_out = (s16 *)(address + base);
                {
                    register u32 y_offset asm("r0");
                    register s32 projected_y asm("r1");
                    register s32 factor_r0 asm("r0");

                    asm volatile(
                        "mov %1, #2\n\t"
                        "ldrsh %0, [%2, %1]"
                        : "=r"(projected_y), "=r"(y_offset)
                        : "r"(projection_r4));
                    {
                        register s32 sine_source asm("r2") = frame.sine;
                        register s32 signed_sine asm("r0") =
                            (s16)sine_source;

                        frame.signed_sine = signed_sine;
                    }
                    {
                        register u32 phase_r2 asm("r2") =
                            (u32)frame.tilt;
                        register u32 tilt_value asm("r0") =
                            *(u16 *)phase_r2;

                        phase_r2 = 0x40;
                        factor_r0 = phase_r2 - tilt_value;
                    }
                    {
                        register s32 multiplier asm("r2") =
                            frame.signed_sine;

                        factor_r0 *= multiplier;
                    }
                    if (factor_r0 < 0) {
                        factor_r0 += 0x1FF;
                    }
                    factor_r0 >>= 9;
                    factor_r0 = projected_y - factor_r0;
                    factor_r0 <<= 7;
                    {
                        register u32 z_offset asm("r2");
                        register s32 z asm("r1");

                        asm volatile(
                            "mov %1, #4\n\t"
                            "ldrsh %0, [%2, %1]"
                            : "=r"(z), "=r"(z_offset)
                            : "r"(projection_r4));
                        frame.records = (s16 *)base;
                        projection = func_080ECD98(factor_r0, z);
                    }
                }
                {
                    register u16 *record2_load asm("r2") = (u16 *)record2;
                    register u32 value asm("r1") = *record2_load;

                    value += projection;
                    asm volatile("strh %0, [%1]"
                        :
                        : "l"(value), "l"(record_out)
                        : "memory");
                }
            }

            {
                register u32 address asm("r0") =
                    (record_index + 5) << 1;
                register u32 base asm("r3") = (u32)frame.records;
                register s16 *record5 asm("r7");

                record5 = (s16 *)(address + base);
                {
                    register u32 x_offset asm("r0");
                    register s32 projected_x asm("r1");
                    register s32 factor_r0 asm("r0");

                    asm volatile(
                        "mov %1, #0\n\t"
                        "ldrsh %0, [%2, %1]"
                        : "=r"(projected_x), "=r"(x_offset)
                        : "r"(projection_r4));
                    {
                        register u32 phase_r2 asm("r2") =
                            (u32)frame.tilt;
                        register u32 tilt_value asm("r0") =
                            *(u16 *)phase_r2;

                        phase_r2 = 0x40;
                        factor_r0 = phase_r2 - tilt_value;
                    }
                    {
                        register s32 multiplier asm("r2") = frame.cosine;

                        factor_r0 *= multiplier;
                    }
                    if (factor_r0 < 0) {
                        factor_r0 += 0x1FF;
                    }
                    factor_r0 >>= 9;
                    factor_r0 = projected_x - factor_r0;
                    factor_r0 <<= 7;
                    {
                        register u32 z_offset asm("r2");
                        register s32 z asm("r1");

                        asm volatile(
                            "mov %1, #4\n\t"
                            "ldrsh %0, [%2, %1]"
                            : "=r"(z), "=r"(z_offset)
                            : "r"(projection_r4));
                        frame.records = (s16 *)base;
                        projection = func_080ECD98(factor_r0, z);
                    }
                }
                {
                    register u16 *record1_load asm("r2") =
                        (u16 *)record1_saved;
                    register u32 value asm("r1") = *record1_load;

                    value += projection;
                    asm volatile("strh %0, [%1]"
                        :
                        : "l"(value), "l"(record5)
                        : "memory");
                }
            }
                }
            }

            {
                register u32 address asm("r0") =
                    (record_index + 6) << 1;
                register u32 base asm("r3") = (u32)frame.records;

                record_index = address + base;
                {
                    register u32 y_offset asm("r0");
                    register s32 projected_y asm("r1");
                    register s32 factor_r0 asm("r0");
                    register s32 projection asm("r0");

                    asm volatile(
                        "mov %1, #2\n\t"
                        "ldrsh %0, [%2, %1]"
                        : "=r"(projected_y), "=r"(y_offset)
                        : "r"(projection_r4));
                    {
                        register u32 *tilt_ptr asm("r2") = frame.tilt;
                        register u32 tilt_value asm("r0") =
                            *(u16 *)tilt_ptr;

                        projection_r4 = 0x40;
                        factor_r0 = projection_r4 - tilt_value;
                    }
                    {
                        register s32 multiplier asm("r2") =
                            frame.signed_sine;

                        factor_r0 *= multiplier;
                    }
                    if (factor_r0 < 0) {
                        projection_r4 = 0x1FF;
                        asm volatile("" : "+r"(projection_r4));
                        factor_r0 += projection_r4;
                    }
                    factor_r0 >>= 9;
                    factor_r0 = projected_y + factor_r0;
                    factor_r0 <<= 7;
                    {
                        register struct Vec3sDD298 *z_base asm("r2") =
                            transformed;
                        register u32 z_offset asm("r4");
                        register s32 z asm("r1");

                        asm volatile(
                            "mov %1, #4\n\t"
                            "ldrsh %0, [%2, %1]"
                            : "=r"(z), "=r"(z_offset)
                            : "r"(z_base));
                        frame.records = (s16 *)base;
                        projection = func_080ECD98(factor_r0, z);
                    }
                    {
                        register u16 *record2_load asm("r2") =
                            (u16 *)record2;
                        register u32 value asm("r1") = *record2_load;

                        value += projection;
                        *(s16 *)record_index = value;
                    }
                }
            }

            {
                register u8 *angle_load_base asm("r4");
                register u32 angle asm("r0");
                register u16 *angle_store asm("r1");

                asm volatile("mov %0, sp" : "=r"(angle_load_base));
                angle = *(u16 *)(angle_load_base + 52);
                angle += 0x55;
                asm volatile("add %0, sp, #52" : "=r"(angle_store));
                *angle_store = angle;
            }
            next = frame.counter + 1;
            next <<= 24;
            next >>= 24;
            frame.counter = next;
            records = frame.records;
            if (next > 2) {
                break;
            }
        }

        {
            register u32 stored_counter asm("r1");

            next <<= 3;
            stored_counter = frame.counter;
            next -= stored_counter;
            next <<= 1;
            next += (u32)records;
            *(s16 *)next = 0;
        }
        }
        {
            register volatile u16 *blend asm("r3") =
                (volatile u16 *)0x03000050;
            register u32 *tilt_ptr asm("r4") = frame.tilt;
            register u32 tilt_value asm("r2") = *tilt_ptr;

            *blend = ((tilt_value >> 2) << 8) | 0x10;
            if (tilt_value == 0x40) {
                goto advance;
            }
        }
        if (!(owner->flags & 2)) {
            register s32 *timer_add asm("r1") = frame.timer;

            *timer_add += 8;
        } else {
            register s32 *timer_sub asm("r2") = frame.timer;

            *timer_sub -= 8;
        }
        {
            register u32 *tilt_update asm("r3") = frame.tilt;

            *tilt_update += 1;
        }
        break;
    }
    case 2:
        owner->timer = 0x80;
        *(u8 *)0x03000075 = 1;
        *(u8 *)0x0300603D = 1;
        owner->state++;
        /* fall through */
    case 3: {
        register s32 *timer asm("r0") = &owner->timer;
        register s32 timer_value asm("r4") = *timer;

        frame.timer = timer;
        if (timer_value == 0) {
            func_0809534C();
            {
                register volatile u16 *display_control asm("r0") =
                    (volatile u16 *)0x0300004E;

                *display_control = timer_value;
            }
            goto advance;
        }
        {
            register s16 *records2 asm("r2");
            register s16 *records3 asm("r3");
            register s16 *records6 asm("r6");
            register u32 saved_flags asm("r4");
            s32 x;

            {
                register s16 *records1 asm("r1") =
                    (s16 *)0x02034AF4;

                records1[0] = 4;
                records2 = records1;
                records6 = records2;
            }
            {
                register u32 flags asm("r1") = owner->flags;
                register u32 masked asm("r0") = 2;

                masked &= flags;
                records3 = records2;
                saved_flags = flags;
                if (masked == 0) {
                    x = (u16)owner->x;
                } else {
                    x = 0xF0 - owner->x;
                }
            }
            records6[7] = x;
            records2[1] = x;
            {
                register s16 *records7 asm("r7") = records3;
                register s32 stored_x asm("r1");
                register u32 zero asm("r2");
                register s32 side_x asm("r0");

                records6 = records3;
                {
                    register u32 x_offset asm("r0");

                    asm volatile(
                        "mov %1, #2\n\t"
                        "ldrsh %0, [%2, %1]"
                        : "=r"(stored_x), "=r"(x_offset)
                        : "r"(records3));
                }
                {
                    register u32 masked asm("r0") = 2;

                    masked &= saved_flags;
                    if (masked == 0) {
                        register s32 *timer_sub asm("r2") = frame.timer;
                        register s32 value asm("r0") = *timer_sub;

                        side_x = stored_x - value;
                    } else {
                        register s32 *timer_add asm("r4") = frame.timer;
                        register s32 value asm("r0") = *timer_add;

                        side_x = stored_x + value;
                    }
                    zero = 0;
                    records6[5] = side_x;
                    asm volatile("strh %0, [%1, #6]"
                        :
                        : "l"(side_x), "l"(records7)
                        : "memory");
                }
                {
                    register s32 y asm("r0") = owner->y;
                    register s32 y_minus_one asm("r1") = y - 1;

                    records3[4] = y_minus_one;
                    records3[2] = y_minus_one;
                    y += 1;
                    records3[8] = y;
                    records3[6] = y;
                    records3[9] = zero;
                }
            }
            {
                register s32 *timer_tail asm("r1") = frame.timer;

                *timer_tail -= 0x10;
            }
        }
        break;
    }
    case 4:
        owner->timer++;
        if (owner->timer != 0x1E) {
            break;
        }
        {
            register volatile u16 *display_control asm("r1") =
                &D_0300004E;
            register u32 display_value asm("r3") = 0x740;
            register u32 store_value asm("r0");

            asm volatile("" : "+r"(display_value));
            store_value = display_value;
            *display_control = store_value;
        }
        {
            register volatile u16 *blend asm("r1") = &D_03000050;
            register u32 blend_value asm("r4") = 0x810;
            register u32 store_value asm("r0");

            asm volatile("" : "+r"(blend_value));
            store_value = blend_value;
            *blend = store_value;
        }
        owner->timer = 0;
        goto advance;
    case 5: {
        s32 base_x;
        s32 base_y;
        s32 camera_x;
        s32 camera_y;
        s32 *camera_x_ptr;
        s32 *camera_y_base;
        s32 x;
        s32 y;

        owner->children[0] = func_080D2450(owner, 0, 0,
            (s16)owner->x, (s16)owner->y, 0x600, 0, 0);
        base_x = owner->x;
        camera_x_ptr = &D_02034034;
        camera_x = *camera_x_ptr;
        if (camera_x < 0) {
            camera_x += 0xFF;
        }
        camera_x >>= 8;
        camera_x -= 0x80;
        asm volatile("add %0, %1, %0"
            : "+r"(camera_x)
            : "r"(base_x));
        x = (s16)camera_x;
        base_y = owner->y;
        camera_y_base = D_03000054;
        camera_y = camera_y_base[1];
        if (camera_y < 0) {
            camera_y += 0xFF;
        }
        camera_y >>= 8;
        asm volatile("add %0, %1, %0"
            : "+r"(camera_y)
            : "r"(base_y));
        y = (s16)camera_y;
        owner->children[1] =
            func_080D2450(owner, 1, 0, x, y, 0x1500, 0, 0);
        owner->saved_x = *camera_x_ptr;
        owner->tilt = camera_y_base[1];
        func_080D12A0(0xC, 0);
        func_080D2790(1);
        goto advance;
    }
    case 6:
        if (*(u16 *)((u8 *)owner->children[1] + 0x14) > 0x17) {
            goto advance;
        }
        {
            register s32 *timer asm("r1") = &owner->timer;
            register s32 phase asm("r6") = *timer;

            phase &= 3;
            frame.timer = timer;
            if (phase == 0) {
                register u32 random asm("r7") =
                    func_080ECD5C(D_03000010);
                register s32 y asm("r4");
                s32 perturb;

                {
                    register s32 base_y asm("r3") = owner->y;
                    register s32 *field_ptr asm("r0");
                    register s32 *camera_base asm("r1");
                    register s32 delta asm("r2");

                    field_ptr = (s32 *)&owner->tilt;
                    camera_base = D_03000054;
                    delta = *field_ptr;
                    delta -= camera_base[1];
                    if (delta < 0) {
                        delta += 0xFF;
                    }
                    y = delta >> 8;
                    asm volatile("add %0, %1, %0"
                        : "+r"(y)
                        : "r"(base_y));
                }
                {
                    register s32 *timer_call asm("r2") = frame.timer;

                    perturb = func_080ECF78(*timer_call, 6);
                }
                perturb += random >> 14;
                {
                    register s32 perturb_bias asm("r3") = 0xFFFE;

                    asm volatile("" : "+r"(perturb_bias));
                    perturb += perturb_bias;
                }
                y += perturb;
                y <<= 16;
                y >>= 16;

                {
                    register s32 base_x asm("r7") = owner->x;
                    register s32 *field_ptr asm("r0");
                    register s32 *camera_ptr asm("r1");
                    register s32 delta asm("r2");
                    register s32 x asm("r3");

                    field_ptr = &owner->saved_x;
                    camera_ptr = &D_02034034;
                    delta = *field_ptr;
                    delta -= *camera_ptr;
                    if (delta < 0) {
                        delta += 0xFF;
                    }
                    x = delta >> 8;
                    asm volatile("add %0, %1, %0"
                        : "+r"(x)
                        : "r"(base_x));
                    x <<= 16;
                    x >>= 16;
                    func_080D2660(owner, 2, 0, x, y,
                        0x400, 0x80, 0x180, phase);
                }
            }
            {
                register s32 *timer_update asm("r4") = frame.timer;

                *timer_update += 1;
            }
            break;
        }
advance:
        owner->state++;
        break;
    case 7:
        if (owner->children[0] == 0 && owner->children[1] == 0) {
            func_08095114(owner);
        }
        break;
    }
}
