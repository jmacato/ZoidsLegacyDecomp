#include "m2c_prelude.h"

M2C_UNK func_0809258C();                            /* extern */
M2C_UNK func_080925A4();                            /* extern */
M2C_UNK func_08092D8C(s32, M2C_UNK);                /* extern */
M2C_UNK func_08092E0C(s32);                         /* extern */
M2C_UNK func_08092E84(s32);                         /* extern */
M2C_UNK func_08092EA0(s32);                         /* extern */
M2C_UNK func_08094330();                            /* extern */
void *func_08094484(M2C_UNK, M2C_UNK, s32, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_08094554();                            /* extern */
M2C_UNK func_08096308(s32, s32);                    /* extern */
s32 func_0809669C();                                /* extern */
M2C_UNK func_08098BB4(M2C_UNK);                     /* extern */
M2C_UNK func_0809A1F8(s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_0809A5B4(u8, s32, s32, s32, s32);      /* extern */
M2C_UNK func_0809A9C8(s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_0809AA64(M2C_UNK, s32, s32, s32);      /* extern */
M2C_UNK func_080D0AF0(M2C_UNK);                     /* extern */
M2C_UNK func_080D12A0(s32, s32);                    /* extern */
M2C_UNK func_080ED17C(s32);                         /* extern */

asm(".set sub_080A83C8_state, 0x0203055C");
asm(".set func_08094484_4, func_08094484");
extern u8 sub_080A83C8_state;
void *func_08094484_4(M2C_UNK, M2C_UNK, s32, s32);

void sub_080A83C8(void) {
    s32 temp_r1;
    s32 var_r0;
    s32 var_r0_2;
    u16 *var_r2;
    u16 var_r1;
    u16 var_r4;
    u16 var_r4_2;
    u16 var_r4_3;
    void *temp_r0;
    register void *config asm("r0");
    s32 zero;
    s32 clear_mask;
    s32 *entries;
    register u8 *motion asm("r6");
    register s32 object_zero asm("r5");

    {
        u8 *state_ptr = &sub_080A83C8_state;
        asm volatile("" : "+r"(state_ptr));
        var_r4 = 0;
        state_ptr[2] = 0xD;
    }
    *(s32 *)0x02021690 = 0xA;
    func_080ED17C(1);
    func_08094330();
    func_0809A1F8(0x74, 0, 1, 0, 0, 0x02002880);
    var_r2 = (u16 *)0x06004000;
    do {
        var_r1 = *var_r2;
        if ((var_r1 & 0xFF00) == 0x1000) {
            var_r1 &= 0xFF;
        }
        if ((var_r1 & 0xFF) == 0x10) {
            var_r1 &= 0xFF00;
        }
        *var_r2 = var_r1;
        var_r2 += 1;
        var_r4 += 1;
    } while ((u32) var_r4 <= 0x1FFFU);
    func_080D0AF0(0xFFFFFF00);
    func_080D12A0(0x10, 0);
    {
        u8 *state_ptr = &sub_080A83C8_state;
        asm volatile("" : "+r"(state_ptr));
        func_0809A5B4(state_ptr[2], 2, 3, 2, 1);
    }
    func_0809AA64(0x087AC9F8, 0x77, 0, 0);
    config = (void *)0x020314A4;
    zero = 0;
    M2C_FIELD(config, s8 *, 0) = 0x7F;
    {
    register u32 config_flags asm("r2") = M2C_FIELD(config, u8 *, 1);
    asm volatile("" : "+r"(config_flags));
    clear_mask = 2;
    asm volatile("" : "+r"(clear_mask));
    clear_mask = -clear_mask;
    {
        register u32 config_value asm("r1") = clear_mask;
        asm volatile("" : "+r"(config_value));
        config_value &= config_flags;
        M2C_FIELD(config, u8 *, 1) = config_value;
    }
    }
    M2C_FIELD(config, s16 *, 2) = zero;
    M2C_FIELD(config, s32 *, 4) = 0x080A0099;
    M2C_FIELD(config, s32 *, 0xC) = zero;
    M2C_FIELD(config, s32 *, 8) = zero;
    func_080925A4();
    config = (void *)0x020314B4;
    M2C_FIELD(config, u8 *, 0) = 0xA0;
    clear_mask &= M2C_FIELD(config, u8 *, 1);
    M2C_FIELD(config, u8 *, 1) = clear_mask;
    M2C_FIELD(config, s16 *, 2) = zero;
    M2C_FIELD(config, s32 *, 4) = 0x080A00D5;
    M2C_FIELD(config, s32 *, 0xC) = zero;
    M2C_FIELD(config, s32 *, 8) = zero;
    func_080925A4();
    func_08092D8C(4, 0x080A829D);
    func_08096308(1, 0x10);
    {
    register s32 scene_x asm("r5") = 0x3C2;
    s32 scene_y = 0xD;
    register s32 *out_args asm("sp");
    asm volatile("" : "+r"(scene_x), "+r"(scene_y));
    for (;;) {
        func_080ED17C(1);
        {
            register s32 *wait_ptr asm("r0") = (s32 *)0x02031C10;
            register s32 wait_value asm("r1");
            register s32 wait_target asm("r0");
            asm volatile("" : "+r"(wait_ptr));
            wait_value = *wait_ptr;
            asm volatile("" : "+r"(wait_value));
            wait_target = 0x96;
            asm volatile("" : "+r"(wait_target));
            wait_target <<= 1;
            if (wait_value == wait_target) {
                break;
            }
        }
    }
    func_0809258C();
    out_args[0] = 0x68;
    out_args[1] = scene_x;
    out_args[2] = scene_y;
    out_args[3] = 8;
    out_args[4] = 0;
    func_08094484_4(0x08359850, 0x0835985C, 0, 8);
    func_08098BB4(0x08017BD3);
    func_0809A9C8(1, 0, 0, scene_x, scene_y, 0x02002880);
    func_08098BB4(0x080189C6);
    func_08096308(2, 0x10);
    }
    goto poll_11;
wait_11:
    func_080ED17C(1);
poll_11:
    if ((func_0809669C() << 0x18) == 0) {
        goto wait_11;
    }
    func_08092E0C(4);
    var_r4_2 = 0;
    entries = (s32 *)0x02031C14;
    do {
        if (entries[var_r4_2] != 0) {
            func_08094554();
        }
        var_r4_2 += 1;
    } while ((u32) var_r4_2 <= 0x1FU);
    *(s32 *)0x02021690 = 9;
    *(s32 *)0x02030558 = 0xFF10;
    {
        register u8 *state_ptr asm("r0") = &sub_080A83C8_state;
        s32 motion_zero = 0;
        asm volatile("" : "+r"(state_ptr), "+r"(motion_zero));
        state_ptr[1] = motion_zero;
    motion = (u8 *)0x030033C4;
    M2C_FIELD(motion, s32 *, 0) = motion_zero;
    M2C_FIELD(motion, s32 *, 4) = 0x20000;
    M2C_FIELD(motion, s32 *, 8) = 0x8000;
    object_zero = 0;
    asm volatile("" : "+r"(object_zero));
    M2C_FIELD(motion, s16 *, 0xC) = 0x10;
    M2C_FIELD(motion, s16 *, 0x10) = motion_zero;
    M2C_FIELD(motion, s16 *, 0xE) = motion_zero;
    M2C_FIELD(motion, s32 *, 0x14) = 0x78;
    M2C_FIELD(motion, s32 *, 0x18) = 0x58;
    M2C_FIELD(motion, s32 *, 0x1C) = 0x80;
    M2C_FIELD(motion, s32 *, 0x60) = 0x20000;
    func_080ED17C(1);
    func_0809AA64(0x087AF9D4, 0x13, 0, 0);
    temp_r0 = func_08094484(0x0821024C, 0x08210258, 0, 0, motion_zero, motion_zero, motion_zero, 0x2C8, 0x080BADD5);
    *(void **)0x02032E8C = temp_r0;
    M2C_FIELD(temp_r0, s32 *, 0x28) = 0xFFFFD000;
    M2C_FIELD(temp_r0, s32 *, 0x2C) = motion_zero;
    M2C_FIELD(temp_r0, s32 *, 0x30) = motion_zero;
    *(s8 *)0x02032EEC = object_zero;
    }
    func_08096308(1, 0x10);
    if (M2C_FIELD(motion, s32 *, 4) != 0) {
        register u8 *fade_check asm("r5") = motion;
        u8 *fade_store = fade_check;
        asm volatile("" : "+r"(fade_check), "+r"(fade_store));
        do {
            temp_r1 = M2C_FIELD(fade_store, s32 *, 4);
            if (temp_r1 <= 0x7FFF) {
                var_r0 = temp_r1;
                if (temp_r1 < 0) {
                    var_r0 = temp_r1 + 7;
                }
                var_r0_2 = temp_r1 - (var_r0 >> 3);
            } else {
                var_r0_2 = temp_r1 + 0xFFFFF000;
            }
            M2C_FIELD(fade_store, s32 *, 4) = var_r0_2;
            {
                register u8 *fade_low asm("r1") = fade_check;
                asm volatile("" : "+r"(fade_low));
                if ((s32) M2C_FIELD(fade_low, s32 *, 4) <= 0x3F) {
                    M2C_FIELD(fade_low, s32 *, 4) = 0;
                }
            }
            func_080ED17C(1);
        } while (M2C_FIELD(fade_check, s32 *, 4) != 0);
    }
    func_08092D8C(5, 0x0809FF55);
    func_08092E84(0x56);
    var_r4_3 = 0;
    do {
        *(s16 *)0x0300004E = 0xBF;
        *(s16 *)0x03000052 = 0x10;
        func_080ED17C(1);
        *(s16 *)0x03000052 = 0;
        func_080ED17C(1);
        var_r4_3 += 1;
    } while ((u32) var_r4_3 <= 2U);
    *(s16 *)0x0300004E = 0;
    func_08092E84(0x4A);
    var_r4_3 = 0;
    do {
        func_080ED17C(1);
        var_r4_3 += 1;
    } while ((u32) var_r4_3 <= 0x77U);
    func_08092EA0(0x4A);
    func_08092E0C(5);
    func_08094484(0x08359850, 0x0835985C, 0, 8, 0x68, 0x3C2, 0xD, 8, 0);
    func_08098BB4(0x08017BD3);
    func_0809A9C8(1, 6, 0, 0x3C2, 0xD, 0x02002880);
    func_08098BB4(0x0801899A);
    func_08096308(2, 0x10);
    goto poll_34;
wait_34:
    func_080ED17C(1);
poll_34:
    if ((func_0809669C() << 0x18) == 0) {
        goto wait_34;
    }
    *(s32 *)0x02021690 = -1;
    func_080ED17C(1);
}
