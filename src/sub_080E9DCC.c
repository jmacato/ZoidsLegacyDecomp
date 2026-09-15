#include "m2c_prelude.h"

s32 func_080BE65C(u8, u8, s32, s32, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_080BEE04(void *, u8, u8, u8, s32);     /* extern */
u8 func_080BF464(u8, u8, s32);                      /* extern */
M2C_UNK func_080BF514(u8, u8);                      /* extern */
M2C_UNK func_080BFAD0(u8, u8, u8);                  /* extern */
M2C_UNK func_080C02B4(u8, u8);                      /* extern */
void *func_080E669C();                              /* extern */
M2C_UNK func_080E66B8();                            /* extern */
M2C_UNK func_080E8B08(u8, u8);                      /* extern */
M2C_UNK func_080E8C90(u8, u8, u8, u8, void *);      /* extern */
M2C_UNK jtbl_080E9EC4();                            /* static */
extern u8 D_02034B4C[];
extern u8 D_0203055C[];

struct FrameE9DCC {
    void *sp18;
    void *sp1C;
    void *sp20;
    s32 sp24;
    s32 sp28;
    s32 sp2C;
    s32 sp30;
};

void sub_080E9DCC(s32 arg0, s32 arg1, s32 arg2) {
    volatile struct FrameE9DCC frame;
    register s32 temp_r2_2 asm("r2");
    s16 temp_r3_3;
    s32 temp_r1_3;
    register s32 temp_r4 asm("r4");
    register u32 temp_r3 asm("r3");
    register u32 case_scaled_r8 asm("r8");
    register u32 case_factor_sl asm("sl");
    u16 var_r0;
    u32 temp_r0;
    u8 temp_r0_3;
    u8 temp_r0_4;
    u8 temp_r0_5;
    u8 temp_r0_6;
    u8 temp_r0_7;
    u8 temp_r0_8;
    u8 temp_r1_2;
    u8 temp_r1_4;
    u8 temp_r1_6;
    register u32 temp_r3_2 asm("r3");
    register u32 temp_r2 asm("r2");
    u8 temp_r5;
    u8 temp_r6;
    u8 temp_r7;
    u8 var_r4;
    register u8 *base asm("r4");
    register void *temp_r1 asm("r9");
    void *temp_r1_5;
    void *temp_r1_7;

    arg0 <<= 24;
    temp_r5 = (u32)arg0 >> 24;
    arg1 <<= 24;
    temp_r6 = (u32)arg1 >> 24;
    arg2 <<= 24;
    temp_r7 = (u32)arg2 >> 24;
    asm volatile("" : : "r"(temp_r7));
    asm volatile("" : : "r"(temp_r7));
    asm volatile("" : : "r"(temp_r7));
    asm volatile("" : : "r"(temp_r7));
    frame.sp20 = func_080E669C();
    base = D_02034B4C;
    {
        register u32 work_r0 asm("r0");
        register u32 work_r1 asm("r1");
        register u32 work_r2 asm("r2");
        register u32 work_r3 asm("r3");

        work_r1 = 0xA1B0;
        work_r0 = (u32)base + work_r1;
        work_r0 = temp_r7 + work_r0;
        work_r1 = *(u8 *)work_r0;
        work_r0 = 0xA8C;
        work_r3 = work_r1;
        work_r3 *= work_r0;

        work_r0 = temp_r7 << 3;
        work_r0 -= temp_r7;
        work_r0 <<= 5;
        work_r0 += temp_r7;
        work_r0 <<= 2;
        work_r2 = 0x27C8;
        work_r1 = (u32)base + work_r2;
        work_r0 += work_r1;
        work_r3 += work_r0;

        work_r1 = 0xA1B3;
        work_r0 = (u32)base + work_r1;
        work_r0 = temp_r7 + work_r0;
        work_r1 = *(u8 *)work_r0;
        work_r0 = 0x94;
        work_r0 *= work_r1;
        work_r0 += 0xC;
        work_r3 += work_r0;

        work_r0 = temp_r5 << 3;
        work_r0 += temp_r5;
        work_r0 <<= 3;
        work_r0 += 4;
        work_r3 += work_r0;
        work_r2 = temp_r6 << 1;
        work_r2 += temp_r6;
        work_r0 = work_r2 << 2;
        work_r3 += work_r0;
        frame.sp18 = (void *)work_r3;

        work_r1 = temp_r5 << 2;
        work_r1 += temp_r5;
        work_r1 <<= 3;
        work_r1 -= temp_r5;
        work_r1 <<= 7;
        work_r0 = temp_r6 << 2;
        work_r0 += temp_r6;
        work_r0 <<= 3;
        work_r0 -= temp_r6;
        work_r0 <<= 4;
        work_r0 += (u32)base;
        work_r1 += work_r0;
        frame.sp1C = (void *)work_r1;

        work_r0 = 0x1218;
        work_r1 = temp_r5;
        work_r1 *= work_r0;
        work_r2 <<= 6;
        work_r2 += temp_r6;
        work_r2 <<= 2;
        work_r3 = 0x7C28;
        work_r0 = (u32)base + work_r3;
        work_r2 += work_r0;
        work_r1 += work_r2;
        temp_r1 = (void *)work_r1;
        work_r1 = *(u16 *)work_r1;
        work_r0 = 1;
        work_r0 |= work_r1;
        work_r1 = (u32)temp_r1;
        *(u16 *)work_r1 = work_r0;

        work_r1 = temp_r5 << 1;
        work_r1 += temp_r5;
        work_r1 <<= 1;
        work_r1 = temp_r6 + work_r1;
        work_r0 = temp_r7 << 1;
        work_r0 += temp_r7;
        work_r0 <<= 2;
        work_r1 += work_r0;
        work_r2 = 0xA1B6;
        asm volatile("" : "+r"(work_r2));
        base += work_r2;
        work_r1 += (u32)base;
        work_r1 = *(u8 *)work_r1;
        frame.sp24 = work_r1;
        work_r3 = 7;
        work_r1 &= work_r3;
        frame.sp28 = work_r1;
        work_r0 = work_r1;
        asm volatile("" : "+r"(work_r0));
        work_r0 -= 1;
        temp_r0 = work_r0;
    }
    if (temp_r0 <= 4U) {
        goto block_2;
    }
    goto block_77;
block_2:
    switch (temp_r0) {                              /* jump table: jtbl_080E9EC4 */
case 2:
case 3:
    {
        register u32 work_r0 asm("r0");
        register u32 work_r1 asm("r1");
        register u32 case_index_r2 asm("r2");
        register u32 zero_ip asm("ip");

        base = (u8 *)temp_r1;
        work_r1 = *(u16 *)base;
        work_r0 = 8;
        case_index_r2 = 0;
        asm volatile("" : "+r"(case_index_r2));
        zero_ip = case_index_r2;
        asm volatile("" : "+r"(zero_ip));
        temp_r3 = work_r0;
        temp_r3 |= work_r1;
        *(u16 *)base = temp_r3;

        case_index_r2 = temp_r7 << 3;
        work_r0 = case_index_r2 - temp_r7;
        work_r0 <<= 5;
        work_r0 += temp_r7;
        work_r0 <<= 2;
        case_scaled_r8 = work_r0;

        base = D_02034B4C;
        work_r1 = 0xA1B0;
        work_r0 = (u32)base + work_r1;
        base = (u8 *)(temp_r7 + work_r0);
        work_r0 = *(u8 *)base;
        work_r1 = 0xA8C;
        case_factor_sl = work_r1;
        work_r1 = case_factor_sl;
        work_r1 *= work_r0;
        work_r0 = work_r1;
        work_r0 += case_scaled_r8;
        work_r1 = (u32)D_02034B4C;
        work_r0 += work_r1;
        work_r1 = 0x27C8;
        work_r0 += work_r1;
        work_r1 = *(u16 *)work_r0;
        work_r0 = 1;
        work_r0 &= work_r1;
        frame.sp2C = case_index_r2;
        if (work_r0 == 0) {
            goto block_6;
        }
    }
    goto block_53;
block_6:
    {
        register u32 work_r0 asm("r0");
        register u32 work_r1 asm("r1");
        register u32 work_r2 asm("r2");

        work_r0 = 2;
        temp_r3 |= work_r0;
        work_r2 = (u32)temp_r1;
        *(u16 *)work_r2 = temp_r3;
        work_r0 = *(u8 *)base;
        asm volatile(
            ".syntax unified\n\t"
            "mov r3, %1\n\t"
            "muls r3, r3, %0\n\t"
            "adds %0, r3, #0\n\t"
            ".syntax divided"
            : "+r"(work_r0)
            : "r"(case_factor_sl)
            : "r3", "cc");
        work_r0 += case_scaled_r8;
        base = D_02034B4C;
        work_r0 += (u32)base;
        work_r1 = 0x27C8;
        asm volatile("" : "+r"(work_r1));
        work_r0 += work_r1;
        work_r1 = *(u16 *)work_r0;
        work_r0 = 0x80;
        work_r0 <<= 1;
        work_r0 &= work_r1;
        if (work_r0 != 0) {
            goto block_9;
        }
    }
    temp_r2 = func_080BF464(temp_r5, temp_r6, 0x15);
    if (temp_r2 == 0xFF) {
        goto block_9;
    }
    goto block_47;
block_9:
    {
        register u32 work_r2 asm("r2") = frame.sp28;

        if (work_r2 != 3) {
            goto block_12;
        }
    }
    {
        register u32 work_r0 asm("r0");
        register u8 *work_r3 asm("r3") = frame.sp18;

        work_r0 = *(u16 *)(work_r3 + 4);
        var_r0 = work_r0;
    }
    goto block_13;
block_12:
    {
        register u32 work_r0 asm("r0");
        register u8 *work_r4 asm("r4") = frame.sp18;

        work_r0 = *(u16 *)(work_r4 + 8);
        var_r0 = work_r0;
    }
block_13:
    {
        register u32 work_r0 asm("r0") = var_r0;
        register u32 work_r1 asm("r1");
        register u32 current_r4 asm("r4");
        register u8 *store_r3 asm("r3");

        work_r1 = (u32)frame.sp1C;
        current_r4 = *(u16 *)(work_r1 + 6);
        work_r1 = (s32)*(s16 *)(work_r1 + 6);
        work_r0 <<= 16;
        temp_r2_2 = (s32)work_r0 >> 16;
        frame.sp30 = work_r0;
        if ((s32)work_r1 <= temp_r2_2) {
            goto block_21;
        }
        work_r0 = current_r4 - temp_r2_2;
        store_r3 = frame.sp1C;
        *(u16 *)(store_r3 + 6) = work_r0;
        current_r4 = 0x3C;
        asm volatile(
            "ldrsh %0, [%1, %2]"
            : "=r"(work_r0)
            : "r"(store_r3), "r"(current_r4));
        if (temp_r2_2 >= (s32)work_r0) {
            goto block_16;
        }
    }
    goto block_38;
block_16:
    {
        register u32 mask_r0 asm("r0") = 0x40;
        register u32 flags_r1 asm("r1") = frame.sp24;

        mask_r0 &= flags_r1;
        temp_r1_4 = mask_r0;
    }
    if (temp_r1_4 == 0) {
        goto block_18;
    }
    goto block_38;
block_18:
    if ((func_080BE65C(temp_r5, temp_r6, -1, 0x18, (s32) temp_r1_4, (s32) temp_r1_4, 0x19, (s32) temp_r1_4, (s32) temp_r1_4, (s32) temp_r1_4) << 0x18) != 0) {
        goto block_20;
    }
    goto block_38;
block_20:
    func_080C02B4(temp_r5, temp_r6);
    goto block_38;
block_21:
    {
        register u8 *state_r0 asm("r0") = D_0203055C;

        temp_r3_2 = state_r0[5];
    }
    if (temp_r3_2 != 1) {
        goto block_23;
    }
    {
        register u8 *data_r2 asm("r2") = D_02034B4C;
        register u32 address_r1 asm("r1") = temp_r6 << 2;
        register u32 value_r0 asm("r0");

        address_r1 += temp_r6;
        address_r1 <<= 3;
        address_r1 -= temp_r6;
        address_r1 <<= 4;
        value_r0 = temp_r5 << 2;
        value_r0 += temp_r5;
        value_r0 <<= 3;
        value_r0 -= temp_r5;
        value_r0 <<= 7;
        address_r1 += value_r0;
        address_r1 += (u32)data_r2;
        address_r1 += 0x70;
        value_r0 = *(u8 *)address_r1;
        if ((u32)(u8)(value_r0 - 0x36) <= 1U) {
            goto block_36;
        }
    }
block_23:
    if (temp_r3_2 != 4) {
        goto block_26;
    }
    {
        register u8 *data_r2 asm("r2") = D_02034B4C;
        register u32 address_r1 asm("r1") = temp_r6 << 2;
        register u32 value_r0 asm("r0");

        address_r1 += temp_r6;
        address_r1 <<= 3;
        address_r1 -= temp_r6;
        address_r1 <<= 4;
        value_r0 = temp_r5 << 2;
        value_r0 += temp_r5;
        value_r0 <<= 3;
        value_r0 -= temp_r5;
        value_r0 <<= 7;
        address_r1 += value_r0;
        address_r1 += (u32)data_r2;
        address_r1 += 0x70;
        value_r0 = *(u8 *)address_r1;
        if (value_r0 == 0x34) {
            goto block_36;
        }
        if (value_r0 == 0x5E) {
            goto block_36;
        }
    }
block_26:
    if (temp_r3_2 != 5) {
        goto block_29;
    }
    {
        register u8 *data_r2 asm("r2") = D_02034B4C;
        register u32 address_r1 asm("r1") = temp_r6 << 2;
        register u32 value_r0 asm("r0");

        address_r1 += temp_r6;
        address_r1 <<= 3;
        address_r1 -= temp_r6;
        address_r1 <<= 4;
        value_r0 = temp_r5 << 2;
        value_r0 += temp_r5;
        value_r0 <<= 3;
        value_r0 -= temp_r5;
        value_r0 <<= 7;
        address_r1 += value_r0;
        address_r1 += (u32)data_r2;
        address_r1 += 0x70;
        value_r0 = *(u8 *)address_r1;
        if (value_r0 == 0x34) {
            goto block_36;
        }
        if (value_r0 == 0x5E) {
            goto block_36;
        }
    }
block_29:
    if (temp_r3_2 != 8) {
        goto block_33;
    }
    {
        register u8 *data_r2 asm("r2") = D_02034B4C;
        register u32 address_r1 asm("r1") = temp_r6 << 2;
        register u32 value_r0 asm("r0");

        address_r1 += temp_r6;
        address_r1 <<= 3;
        address_r1 -= temp_r6;
        address_r1 <<= 4;
        value_r0 = temp_r5 << 2;
        value_r0 += temp_r5;
        value_r0 <<= 3;
        value_r0 -= temp_r5;
        value_r0 <<= 7;
        address_r1 += value_r0;
        address_r1 += (u32)data_r2;
        address_r1 += 0x70;
        value_r0 = *(u8 *)address_r1;
        if (value_r0 == 0x1E) {
            goto block_36;
        }
        if (value_r0 == 0x5F) {
            goto block_36;
        }
        if (value_r0 == 0x3B) {
            goto block_36;
        }
    }
block_33:
    if (temp_r3_2 != 0xA) {
        goto block_37;
    }
    {
        register u8 *data_r2 asm("r2") = D_02034B4C;
        register u32 address_r1 asm("r1") = temp_r6 << 2;
        register u32 value_r0 asm("r0");

        address_r1 += temp_r6;
        address_r1 <<= 3;
        address_r1 -= temp_r6;
        address_r1 <<= 4;
        value_r0 = temp_r5 << 2;
        value_r0 += temp_r5;
        value_r0 <<= 3;
        value_r0 -= temp_r5;
        value_r0 <<= 7;
        address_r1 += value_r0;
        address_r1 += (u32)data_r2;
        address_r1 += 0x70;
        value_r0 = *(u8 *)address_r1;
        if (value_r0 == 0x34) {
            goto block_36;
        }
        if (value_r0 != 0x5E) {
            goto block_37;
        }
    }
block_36:
    {
        register u32 value_r0 asm("r0") = 1;
        register u8 *target_r2 asm("r2") = frame.sp1C;

        *(u16 *)(target_r2 + 6) = value_r0;
    }
    goto block_38;
block_37:
    {
        register u32 value_r0 asm("r0") = 0;
        register u8 *target_r3 asm("r3") = frame.sp1C;

        *(u16 *)(target_r3 + 6) = value_r0;
    }
block_38:
    {
        register u32 work_r0 asm("r0");
        register u32 work_r1 asm("r1");
        register u32 work_r2 asm("r2");

        temp_r4 = (s32)temp_r1;
        work_r0 = *(u16 *)(temp_r4 + 2);
        work_r1 = frame.sp30;
        temp_r4 = (s32)work_r1 >> 16;
        work_r0 = temp_r4 + work_r0;
        work_r2 = (u32)temp_r1;
        *(u16 *)(work_r2 + 2) = work_r0;
    }
    {
        register u32 state_r0 asm("r0") = (u32)D_0203055C;

        state_r0 = *(u8 *)(state_r0 + 5);
        state_r0 -= 7;
        state_r0 = (u8)state_r0;
        if (state_r0 <= 1U) {
            goto block_40;
        }
    }
    goto block_52;
block_40:
    {
    register u32 phase_r3 asm("r3");
    register u32 phase_r8 asm("r8");
    register u32 phase_sl asm("sl");
    {
        register u32 work_r0 asm("r0");
        register u32 work_r1 asm("r1");
        register u32 work_r2 asm("r2");

        phase_r3 = (u32)D_02034B4C;
        asm volatile("" : "+r"(phase_r3));
        phase_sl = phase_r3;
        phase_r3 = temp_r6 << 2;
        work_r1 = phase_r3 + temp_r6;
        work_r1 <<= 3;
        work_r1 -= temp_r6;
        work_r1 <<= 4;
        work_r2 = temp_r5 << 2;
        work_r0 = work_r2 + temp_r5;
        work_r0 <<= 3;
        work_r0 -= temp_r5;
        work_r0 <<= 7;
        work_r1 += work_r0;
        work_r1 += phase_sl;
        work_r1 += 0x70;
        work_r0 = *(u8 *)work_r1;
        phase_r8 = work_r2;
        if (work_r0 == 0x1E) {
            goto block_42;
        }
        if (work_r0 != 0x5F) {
            goto block_43;
        }
    }
block_42:
    {
        register u32 work_r0 asm("r0");
        register u32 work_r1 asm("r1") = 0xA078;

        work_r1 += phase_sl;
        work_r0 = *(u16 *)work_r1;
        work_r0 = temp_r4 + work_r0;
        *(u16 *)work_r1 = work_r0;
    }
block_43:
    {
        register u32 work_r0 asm("r0");
        register u32 work_r1 asm("r1");
        register u32 work_r2 asm("r2");

        temp_r4 = (s32)D_02034B4C;
        work_r1 = 0x27A5;
        asm volatile("" : "+r"(work_r1));
        work_r0 = temp_r4 + work_r1;
        work_r0 = *(u8 *)work_r0;
        work_r1 = work_r0 << 2;
        work_r1 += work_r0;
        work_r1 <<= 3;
        work_r1 -= work_r0;
        work_r1 <<= 4;
        work_r2 = 0x27A4;
        asm volatile("" : "+r"(work_r2));
        work_r0 = temp_r4 + work_r2;
        work_r2 = *(u8 *)work_r0;
        work_r0 = work_r2 << 2;
        work_r0 += work_r2;
        work_r0 <<= 3;
        work_r0 -= work_r2;
        work_r0 <<= 7;
        work_r1 += work_r0;
        work_r1 += temp_r4;
        work_r1 += 0x70;
        work_r0 = *(u8 *)work_r1;
        if (work_r0 == 0x1E) {
            goto block_45;
        }
        if (work_r0 != 0x5F) {
            goto block_52;
        }
    }
block_45:
    {
        register u32 work_r0 asm("r0");
        register u32 work_r1 asm("r1");
        register u32 work_r2 asm("r2");

        work_r0 = phase_r3 + temp_r6;
        work_r0 <<= 3;
        work_r0 -= temp_r6;
        work_r0 <<= 4;
        phase_r3 = phase_r8;
        work_r1 = phase_r3 + temp_r5;
        work_r1 <<= 3;
        work_r1 -= temp_r5;
        work_r1 <<= 7;
        work_r0 += work_r1;
        work_r0 += temp_r4;
        work_r0 += 0x70;
        work_r0 = *(u8 *)work_r0;
        if (work_r0 != 0x22) {
            goto block_52;
        }
        work_r0 = 0xA07A;
        work_r1 = temp_r4 + work_r0;
        work_r2 = frame.sp30;
        work_r0 = (s32)work_r2 >> 16;
        phase_r3 = *(u16 *)work_r1;
        asm volatile("" : "+r"(phase_r3));
        work_r0 += phase_r3;
        *(u16 *)work_r1 = work_r0;
    }
    }
    goto block_52;
block_47:
    {
        register u32 work_r0 asm("r0");
        register u32 work_r1 asm("r1");
        register u32 work_r2 asm("r2");
        register u32 amount_r3 asm("r3");
        register u32 record_r7 asm("r7");
        register u32 record_r8 asm("r8");

        work_r1 = temp_r2 << 1;
        work_r1 += temp_r2;
        work_r1 <<= 2;
        work_r0 = temp_r6 << 2;
        work_r0 += temp_r6;
        work_r0 <<= 3;
        work_r0 -= temp_r6;
        work_r0 <<= 4;
        work_r1 += work_r0;
        work_r0 = temp_r5 << 2;
        work_r0 += temp_r5;
        work_r0 <<= 3;
        work_r0 -= temp_r5;
        work_r0 <<= 7;
        work_r1 += work_r0;
        temp_r4 = (s32)D_02034B4C;
        work_r1 += temp_r4;
        work_r1 += 0xEA;
        record_r7 = *(u16 *)work_r1;
        record_r8 = record_r7;
        asm volatile(
            "mov %1, #0\n\t"
            "ldrsh %0, [%2, %1]"
            : "=r"(work_r0), "=r"(amount_r3)
            : "r"(work_r1));
        temp_r4 = (s32)frame.sp18;
        record_r7 = 8;
        asm volatile(
            "ldrsh %0, [%1, %2]"
            : "=r"(amount_r3)
            : "r"(temp_r4), "r"(record_r7));
        if ((s32)work_r0 <= (s32)amount_r3) {
            goto block_50;
        }
        work_r2 = record_r8;
        work_r0 = work_r2 - amount_r3;
        *(u16 *)work_r1 = work_r0;
    }
    goto block_51;
block_50:
    func_080BF514(temp_r5, temp_r6);
block_51:
    func_080E66B8();
    return;
block_52:
    func_080BFAD0(temp_r5, temp_r6, temp_r7);
    goto block_54;
block_53:
    {
        register u32 work_r0 asm("r0") = 4;

        temp_r3 |= work_r0;
        temp_r4 = (s32)temp_r1;
        *(u16 *)temp_r4 = temp_r3;
    }
block_54:
    {
    register u8 *global0_r4 asm("r4");
    register u8 *global1_sl asm("sl");
    register u8 *selector_r8 asm("r8");
    {
        register u32 arg0_r0 asm("r0");
        register u32 arg1_r1 asm("r1");
        register u32 arg2_r2 asm("r2");
        register u32 arg3_r3 asm("r3");

        arg2_r2 = (u32)D_02034B4C;
        arg0_r0 = 0x27A4;
        asm volatile("" : "+r"(arg0_r0));
        global0_r4 = (u8 *)(arg2_r2 + arg0_r0);
        arg0_r0 = *global0_r4;
        asm volatile("" : : "r"(arg0_r0));
        arg1_r1 = 0x27A5;
        asm volatile("" : "+r"(arg1_r1));
        arg1_r1 += arg2_r2;
        global1_sl = (u8 *)arg1_r1;
        arg1_r1 = *global1_sl;
        asm volatile("" : : "r"(arg1_r1));
        arg3_r3 = 0xA1B0;
        arg2_r2 += arg3_r3;
        arg2_r2 += temp_r7;
        selector_r8 = (u8 *)arg2_r2;
        arg2_r2 = *selector_r8;
        func_080E8C90(arg0_r0, arg1_r1, arg2_r2, temp_r7, frame.sp20);
    }
    if (*global0_r4 != temp_r5) {
        goto block_57;
    }
    global0_r4 = global1_sl;
    if (*global0_r4 != temp_r6) {
        goto block_57;
    }
    asm volatile(
        "mov r0, %0\n\t"
        "ldrb r3, [r0]\n\t"
        "mov r0, #0\n\t"
        "str r0, [sp, #0]\n\t"
        "ldr r0, [sp, #32]\n\t"
        "add r1, %1, #0\n\t"
        "add r2, %2, #0\n\t"
        "bl func_080BEE04"
        :
        : "r"(selector_r8), "r"(temp_r5), "r"(temp_r6)
        : "r0", "r1", "r2", "r3", "lr", "cc", "memory");
    goto block_58;
block_57:
    asm volatile(
        "mov r0, #0\n\t"
        "str r0, [sp, #0]\n\t"
        "ldr r0, [sp, #32]\n\t"
        "add r1, %0, #0\n\t"
        "add r2, %1, #0\n\t"
        "mov r3, #255\n\t"
        "bl func_080BEE04"
        :
        : "r"(temp_r5), "r"(temp_r6)
        : "r0", "r1", "r2", "r3", "lr", "cc", "memory");
block_58:
    func_080E8B08(temp_r5, temp_r6);
    }
    {
        register u32 work_r0 asm("r0");
        register u32 work_r1 asm("r1");
        register u32 work_r2 asm("r2");
        register u32 work_r3 asm("r3");
        register u32 base_ip asm("ip");

        work_r1 = (u32)D_02034B4C;
        asm volatile("" : "+r"(work_r1));
        base_ip = work_r1;
        work_r2 = frame.sp2C;
        work_r1 = work_r2 - temp_r7;
        work_r1 <<= 5;
        work_r1 += temp_r7;
        work_r1 <<= 2;
        work_r0 = 0xA1B0;
        work_r0 += base_ip;
        work_r0 = temp_r7 - (0U - work_r0);
        work_r2 = *(u8 *)work_r0;
        work_r0 = 0xA8C;
        work_r0 *= work_r2;
        work_r1 += work_r0;
        work_r1 += base_ip;
        work_r3 = 0x27C8;
        asm volatile("" : "+r"(work_r3));
        work_r1 += work_r3;
        work_r1 = *(u16 *)work_r1;
        work_r0 = 1;
        work_r0 &= work_r1;
        if (work_r0 != 0) {
            goto block_67;
        }
        {
            register u32 loop_r4 asm("r4");
            register u32 loop_r7 asm("r7");
            register u32 loop_r8 asm("r8");

            work_r0 = 0x80;
            loop_r4 = frame.sp24;
            work_r0 &= loop_r4;
            if (work_r0 == 0) {
                goto block_63;
            }
            loop_r4 = 0;
            loop_r7 = temp_r5 << 2;
            asm volatile("" : "+r"(loop_r7));
            loop_r8 = loop_r7;
            work_r3 = temp_r6 << 2;
            loop_r7 = base_ip;
            work_r0 = work_r3 + temp_r6;
            work_r0 <<= 3;
            work_r0 -= temp_r6;
            work_r3 = work_r0 << 4;
            work_r1 = loop_r8;
            work_r0 = work_r1 + temp_r5;
            work_r0 <<= 3;
            work_r0 -= temp_r5;
            work_r1 = work_r0 << 7;
            work_r2 = 0;
loop_61:
            work_r0 = loop_r4 << 2;
            work_r0 += work_r3;
            work_r0 += work_r1;
            work_r0 += loop_r7;
            work_r0 += 0x52;
            *(u16 *)work_r0 = work_r2;
            work_r0 = loop_r4 + 1;
            work_r0 <<= 24;
            loop_r4 = work_r0 >> 24;
            if (loop_r4 <= 3U) {
                goto loop_61;
            }
            work_r2 = (u32)temp_r1;
            work_r1 = *(u16 *)work_r2;
            work_r0 = 0x20;
            work_r0 |= work_r1;
            *(u16 *)work_r2 = work_r0;
        }
    }
block_63:
    {
        register u32 mask_r0 asm("r0") = 0x20;
        register u32 flags_r3 asm("r3") = frame.sp24;

        flags_r3 &= mask_r0;
        if (flags_r3 != 0) {
            goto block_65;
        }
    }
    goto block_77;
block_65:
    asm volatile(
        "mov r2, #1\n\t"
        "neg r2, r2\n\t"
        "mov r1, #0\n\t"
        "str r1, [sp, #0]\n\t"
        "str r1, [sp, #4]\n\t"
        "mov r0, #9\n\t"
        "str r0, [sp, #8]\n\t"
        "sub r0, #19\n\t"
        "str r0, [sp, #12]\n\t"
        "str r1, [sp, #16]\n\t"
        "str r1, [sp, #20]\n\t"
        "add r0, %0, #0\n\t"
        "add r1, %1, #0\n\t"
        "mov r3, #0\n\t"
        "bl func_080BE65C"
        :
        : "r"(temp_r5), "r"(temp_r6)
        : "r0", "r1", "r2", "r3", "lr", "cc", "memory");
    goto block_77;
block_67:
    {
        register u8 *state_r4 asm("r4") = frame.sp20;
        register s32 state_r0 asm("r0") = *(s32 *)(state_r4 + 4);

        if (state_r0 >= 0) {
            goto block_77;
        }
    }
    asm volatile(
        "mov r0, #64\n\t"
        "ldr r7, [sp, #36]\n\t"
        "and r7, r0\n\t"
        "lsl r0, r7, #24\n\t"
        "lsr %0, r0, #24"
        : "=r"(temp_r1_6)
        :
        : "r0", "r7", "cc", "memory");
    if (temp_r1_6 != 0) {
        goto block_77;
    }
    func_080BE65C(temp_r5, temp_r6, -1, 0x18, (s32) temp_r1_6, (s32) temp_r1_6, 0x18, (s32) temp_r1_6, (s32) temp_r1_6, (s32) temp_r1_6);
    goto block_77;
case 0:
case 1:
    {
        register u32 work_r0 asm("r0");
        register u32 work_r1 asm("r1");
        register u32 work_r2 asm("r2");
        register u32 base_r3 asm("r3") = (u32)D_02034B4C;
        register u32 offset_r4 asm("r4");

        work_r0 = temp_r7 << 3;
        work_r0 -= temp_r7;
        work_r0 <<= 5;
        work_r0 += temp_r7;
        work_r0 <<= 2;
        work_r2 = 0xA1B0;
        asm volatile("" : "+r"(work_r2));
        work_r1 = base_r3 + work_r2;
        work_r1 = temp_r7 - (0U - work_r1);
        work_r2 = *(u8 *)work_r1;
        work_r1 = 0xA8C;
        work_r1 *= work_r2;
        work_r0 += work_r1;
        work_r0 += base_r3;
        offset_r4 = 0x27C8;
        asm volatile("" : "+r"(offset_r4));
        work_r0 += offset_r4;
        work_r1 = *(u16 *)work_r0;
        work_r0 = 1;
        work_r0 &= work_r1;
        if (work_r0 != 0) {
            goto block_73;
        }
    {
        asm volatile(
            "mov r7, %0\n\t"
            "ldrh r1, [r7]\n\t"
            "mov r0, #2\n\t"
            "orr r0, r1\n\t"
            "strh r0, [r7]"
            :
            : "r"(temp_r1)
            : "r0", "r1", "r7", "cc", "memory");
    }
    goto block_74;
block_73:
    {
        register u32 work_r0 asm("r0") = (u32)temp_r1;
        register u32 work_r1 asm("r1");

        work_r1 = *(u16 *)work_r0;
        work_r0 = 4;
        work_r0 |= work_r1;
        work_r1 = (u32)temp_r1;
        *(u16 *)work_r1 = work_r0;
    }
block_74:
    work_r2 = frame.sp28;
    if (work_r2 != 2) {
        goto block_77;
    }
    work_r1 = temp_r6 << 2;
    work_r1 += temp_r6;
    work_r1 <<= 3;
    work_r1 -= temp_r6;
    work_r1 <<= 4;
    work_r0 = temp_r5 << 2;
    work_r0 += temp_r5;
    work_r0 <<= 3;
    work_r0 -= temp_r5;
    work_r0 <<= 7;
    work_r1 += work_r0;
    work_r1 += base_r3;
    work_r0 = *(u16 *)(work_r1 + 8);
    work_r0 -= 2;
    base_r3 = 0;
    asm volatile("" : "+r"(base_r3));
    *(u16 *)(work_r1 + 8) = work_r0;
    func_080BE65C(temp_r5, temp_r6, -1, (s32)base_r3,
                  (s32)base_r3, (s32)base_r3, 0x23, (s32)base_r3,
                  (s32)base_r3, (s32)base_r3);
    }
    goto block_77;
case 4:
    asm volatile(
        "mov r3, %0\n\t"
        "ldrh r1, [r3]\n\t"
        "mov r0, #18\n\t"
        "orr r0, r1\n\t"
        "strh r0, [r3]"
        :
        : "r"(temp_r1)
        : "r0", "r1", "r3", "cc", "memory");
block_77:
    func_080E66B8();
    return;
    }
}
