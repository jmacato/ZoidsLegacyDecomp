#include "m2c_prelude.h"

s16 func_08092A90(s32);                             /* extern */
s16 func_08092ADC(s32);                             /* extern */
M2C_UNK func_08095114(void *);                      /* extern */
M2C_UNK func_0809534C();                            /* extern */
s32 func_080ECD98(s32, s32);                        /* extern */
s32 func_080ECF00(s32, s32);                        /* extern */
extern s16 D_02034910[];

void sub_080DBAE8(void *input) {
    register void *owner asm("r8") = input;
    void *arg0 = owner;
    u32 *volatile sp0;
    s32 temp_r0_11;
    s32 temp_r0_2;
    s32 temp_r2;
    s32 temp_r2_2;
    s32 temp_r4_4;
    s32 temp_r5;
    s32 temp_r5_2;
    s32 temp_r5_3;
    s32 temp_trig;
    s32 var_r0;
    u32 *var_r2;
    u32 temp_r0;
    u32 temp_r0_7;
    u32 temp_r0_8;
    u32 temp_r4;
    u32 temp_r4_2;
    u32 temp_r4_3;
    u32 temp_r4_5;
    u32 temp_r4_6;
    u32 temp_r4_7;
    u32 phase_count;
    s32 temp_r6;
    s32 temp_r6_2;
    s32 temp_r6_3;
    u8 var_r7;

    temp_r0 = M2C_FIELD(arg0, u32 *, 0x8C);
    if (temp_r0 > 4U) {

    } else {
        register u32 *var_r9 asm("r9");
        /* Insert the shared phase pointer setup into agbcc's table jump. */
        asm volatile(
            ".macro mov dst, src\n\t"
            ".hword 0x2190, 0x4441, 0x4689, 0x4687\n\t"
            ".endm");
        switch (temp_r0) {
        case 0:
            asm volatile(".purgem mov");
            temp_r4 = M2C_FIELD(arg0, u32 *, 0x90);
            var_r9 = arg0 + 0x90;
            if (temp_r4 <= 0x7FU) {
                D_02034910[0] = 2;
                temp_r0_2 = M2C_FIELD(arg0, s32 *, 4);
                D_02034910[1] = (s16) temp_r0_2;
                temp_r2 = M2C_FIELD(arg0, s32 *, 8);
                D_02034910[2] = (s16) temp_r2;
                D_02034910[3] = (s16) (temp_r0_2 - temp_r4);
                D_02034910[4] = (s16) temp_r2;
                D_02034910[5] = 0;
                {
                    register u32 *phase_store asm("r5");
                    register u32 next_phase asm("r0") = temp_r4;
                    next_phase += 8;
                    phase_store = var_r9;
                    *phase_store = next_phase;
                }
            } else {
                {
                    register u32 *phase_store asm("r6");
                    register u32 zero_phase asm("r0") = 0;
                    phase_store = var_r9;
                    *phase_store = zero_phase;
                }
                M2C_FIELD(arg0, u32 *, 0x8C) = (u32) (M2C_FIELD(arg0, u32 *, 0x8C) + 1);
            case 1:
                {
                register u32 *phase_test asm("r1") = var_r9;
                if ((u32) *phase_test <= 0x1FU) {
                    register s32 temp_r0_3 asm("r0");
                    register s32 temp_r0_4 asm("r0");
                    register void *shape_owner asm("r2");
                    D_02034910[0] = 8;
                    shape_owner = arg0;
                    D_02034910[1] = (s16) M2C_FIELD(shape_owner, s32 *, 4);
                    D_02034910[2] = (s16) M2C_FIELD(shape_owner, s32 *, 8);
                    var_r7 = 0;
                    {
                    register u32 *loop_phase asm("sl") = var_r9;
                    do {
                        {
                            register u32 *phase_read asm("r5") = loop_phase;
                            temp_r4_2 = *phase_read;
                        }
                        temp_trig = func_080ECF00(var_r7 * temp_r4_2, 6);
                        temp_r4_2 >>= 1;
                        temp_r4_2 -= 0x80;
                        func_08092ADC((s16)(temp_trig - temp_r4_2));
                        asm volatile("" : "=r"(temp_r0_3));
                        temp_r6 = var_r7 + 1;
                        temp_r5 = temp_r6 * 2;
                        {
                            register s32 shape_addr asm("r2") = (temp_r5 + 1) << 1;
                            register s32 owner_value asm("r3");
                            register s32 rounded asm("r1");
                            {
                                register s16 *shape_base asm("r1") = D_02034910;
                                shape_addr += (s32)shape_base;
                            }
                            owner_value = M2C_FIELD(arg0, s32 *, 4);
                            temp_r0_3 = (u32)temp_r0_3 << 16;
                            rounded = temp_r0_3 >> 16;
                            temp_r0_3 = (u32)temp_r0_3 >> 31;
                            rounded += temp_r0_3;
                            rounded >>= 1;
                            owner_value += rounded;
                            *(s16 *)shape_addr = (s16)owner_value;
                        }
                        {
                            register u32 *phase_read asm("r2") = loop_phase;
                            temp_r4_3 = *phase_read;
                        }
                        func_08092A90((s16) (func_080ECF00(var_r7 * temp_r4_3, 6) - ((temp_r4_3 >> 1) - 0x80)));
                        asm volatile("" : "=r"(temp_r0_4));
                        {
                            register s32 shape_addr asm("r5") = (temp_r5 + 2) << 1;
                            register s32 owner_value asm("r2");
                            register s32 rounded asm("r1");
                            {
                                register s16 *shape_base asm("r1") = D_02034910;
                                shape_addr += (s32)shape_base;
                            }
                            owner_value = M2C_FIELD(arg0, s32 *, 8);
                            temp_r0_4 = (u32)temp_r0_4 << 16;
                            rounded = temp_r0_4 >> 16;
                            temp_r0_4 = (u32)temp_r0_4 >> 31;
                            rounded += temp_r0_4;
                            rounded >>= 1;
                            owner_value += rounded;
                            *(s16 *)shape_addr = (s16)owner_value;
                        }
                        var_r7 = temp_r6;
                    } while ((u32) var_r7 <= 6U);
                    }
                    D_02034910[17] = 0;
                    var_r2 = var_r9;
                    goto block_19;
                }
                {
                    register s32 *state_ptr asm("r1") = arg0 + 0x94;
                    register u32 zero asm("r0") = 0;
                    register u32 *phase_store asm("r5");
                    *state_ptr = zero;
                    phase_store = var_r9;
                    *phase_store = zero;
                    state_ptr -= 2;
                    *state_ptr += 1;
                }
                }
            case 2:
                {
                    register u32 *sp_seed asm("r0") = arg0 + 0x94;
                    register u32 phase_value asm("r1") = *sp_seed;
                    sp0 = sp_seed;
                    phase_count = phase_value;
                }
                if ((phase_count <= 3U) ||
                    (*({
                        register u32 *phase_test asm("r6") = var_r9;
                        phase_test;
                    }) != 0)) {
                    register s32 temp_r0_5 asm("r0");
                    register s32 temp_r0_6 asm("r0");
                    register s16 *shape_tail asm("r5");
                    D_02034910[0] = 8;
                    D_02034910[1] = (s16) M2C_FIELD(arg0, s32 *, 4);
                    D_02034910[2] = (s16) M2C_FIELD(arg0, s32 *, 8);
                    var_r7 = 0;
                    {
                    register u32 *loop_phase asm("sl") = var_r9;
                    do {
                        temp_r5_2 = func_080ECD98(var_r7 << 5, 6) + 0x70;
                        {
                            register u32 *phase_read asm("r6") = loop_phase;
                            func_08092ADC((s16) (*phase_read + temp_r5_2));
                        }
                        asm volatile("" : "=r"(temp_r0_5));
                        temp_r6_2 = var_r7 + 1;
                        temp_r4_4 = temp_r6_2 * 2;
                        {
                            register s32 shape_addr asm("r2") = (temp_r4_4 + 1) << 1;
                            register s32 owner_value asm("r3");
                            register s32 rounded asm("r1");
                            {
                                register s16 *shape_base asm("r1") = D_02034910;
                                shape_addr += (s32)shape_base;
                            }
                            owner_value = M2C_FIELD(arg0, s32 *, 4);
                            temp_r0_5 = (u32)temp_r0_5 << 16;
                            rounded = temp_r0_5 >> 16;
                            temp_r0_5 = (u32)temp_r0_5 >> 31;
                            rounded += temp_r0_5;
                            rounded >>= 1;
                            owner_value += rounded;
                            *(s16 *)shape_addr = (s16)owner_value;
                        }
                        {
                            register u32 *phase_read asm("r2") = loop_phase;
                            func_08092A90((s16) (*phase_read + temp_r5_2));
                        }
                        asm volatile("" : "=r"(temp_r0_6));
                        {
                            register s32 shape_addr asm("r4") = (temp_r4_4 + 2) << 1;
                            register s32 owner_value asm("r2");
                            register s32 rounded asm("r1");
                            asm volatile(""
                                         : "=r"(shape_tail)
                                         : "0"(D_02034910));
                            shape_addr += (s32)shape_tail;
                            owner_value = M2C_FIELD(arg0, s32 *, 8);
                            temp_r0_6 = (u32)temp_r0_6 << 16;
                            rounded = temp_r0_6 >> 16;
                            temp_r0_6 = (u32)temp_r0_6 >> 31;
                            rounded += temp_r0_6;
                            rounded >>= 1;
                            owner_value += rounded;
                            *(s16 *)shape_addr = (s16)owner_value;
                        }
                        var_r7 = temp_r6_2;
                    } while ((u32) var_r7 <= 6U);
                    }
                    {
                        register s16 *shape_tail_store asm("r1");
                        asm volatile("mov %0, %1"
                                     : "=r"(shape_tail_store)
                                     : "r"(shape_tail));
                        shape_tail_store[17] = 0;
                    }
                    var_r2 = sp0;
                    if (!(*var_r2 & 1)) {
                        register u32 *phase asm("r5") = var_r9;
                        temp_r0_7 = *phase + 2;
                        *phase = temp_r0_7;
                        if (temp_r0_7 != 0x20) {

                        } else {
block_19:
                            *var_r2 += 1;
                        }
                    } else {
                        register u32 *phase asm("r6") = var_r9;
                        temp_r0_8 = *phase - 2;
                        *phase = temp_r0_8;
                        if (temp_r0_8 != -0x20U) {

                        } else {
                            *sp0 += 1;
                        }
                    }
                } else {
                    register u32 *phase asm("r2");
                    register u32 reset_phase asm("r0") = 0x20;
                    phase = var_r9;
                    *phase = reset_phase;
                    M2C_FIELD(arg0, u32 *, 0x8C) = (u32) (M2C_FIELD(arg0, u32 *, 0x8C) + 1);
                case 3:
                    {
                    register u32 *phase_test asm("r5") = var_r9;
                    if (*phase_test != 0) {
                        register s32 temp_r0_9 asm("r0");
                        register s32 temp_r0_10 asm("r0");
                        register void *shape_owner asm("r6");
                        D_02034910[0] = 8;
                        shape_owner = arg0;
                        D_02034910[1] = (s16) M2C_FIELD(shape_owner, s32 *, 4);
                        D_02034910[2] = (s16) M2C_FIELD(shape_owner, s32 *, 8);
                        var_r7 = 0;
                        {
                        register u32 *loop_phase asm("sl") = var_r9;
                        do {
                            temp_r4_5 = *loop_phase;
                            func_08092ADC((s16) (func_080ECF00(var_r7 * temp_r4_5, 6) - ((temp_r4_5 >> 1) - 0x80)));
                            asm volatile("" : "=r"(temp_r0_9));
                            temp_r6_3 = var_r7 + 1;
                            temp_r5_3 = temp_r6_3 * 2;
                            {
                                register s32 shape_addr asm("r2") = (temp_r5_3 + 1) << 1;
                                register s32 owner_value asm("r3");
                                register s32 rounded asm("r1");
                                {
                                    register s16 *shape_base asm("r1") = D_02034910;
                                    shape_addr += (s32)shape_base;
                                }
                                owner_value = M2C_FIELD(arg0, s32 *, 4);
                                temp_r0_9 = (u32)temp_r0_9 << 16;
                                rounded = temp_r0_9 >> 16;
                                temp_r0_9 = (u32)temp_r0_9 >> 31;
                                rounded += temp_r0_9;
                                rounded >>= 1;
                                owner_value += rounded;
                                *(s16 *)shape_addr = (s16)owner_value;
                            }
                            {
                                register u32 *phase_read asm("r2") = loop_phase;
                                temp_r4_6 = *phase_read;
                            }
                            func_08092A90((s16) (func_080ECF00(var_r7 * temp_r4_6, 6) - ((temp_r4_6 >> 1) - 0x80)));
                            asm volatile("" : "=r"(temp_r0_10));
                            {
                                register s32 shape_addr asm("r5") = (temp_r5_3 + 2) << 1;
                                register s32 owner_value asm("r2");
                                register s32 rounded asm("r1");
                                {
                                    register s16 *shape_base asm("r1") = D_02034910;
                                    shape_addr += (s32)shape_base;
                                }
                                owner_value = M2C_FIELD(arg0, s32 *, 8);
                                temp_r0_10 = (u32)temp_r0_10 << 16;
                                rounded = temp_r0_10 >> 16;
                                temp_r0_10 = (u32)temp_r0_10 >> 31;
                                rounded += temp_r0_10;
                                rounded >>= 1;
                                owner_value += rounded;
                                *(s16 *)shape_addr = (s16)owner_value;
                            }
                            var_r7 = temp_r6_3;
                        } while ((u32) var_r7 <= 6U);
                        }
                        D_02034910[17] = 0;
                        {
                            register u32 *phase asm("r2") = var_r9;
                            register u32 next_phase asm("r0") = *phase;
                            next_phase -= 1;
                            *phase = next_phase;
                        }
                    } else {
                        register u32 *phase asm("r5");
                        register u32 reset_phase asm("r0") = 0x80;
                        phase = var_r9;
                        *phase = reset_phase;
                        M2C_FIELD(arg0, u32 *, 0x8C) = (u32) (M2C_FIELD(arg0, u32 *, 0x8C) + 1);
                    case 4:
                        {
                        register u32 *phase asm("r6") = var_r9;
                        temp_r4_7 = *phase;
                        if (temp_r4_7 != 0) {
                            D_02034910[0] = 2;
                            temp_r0_11 = M2C_FIELD(arg0, s32 *, 4);
                            D_02034910[1] = (s16) temp_r0_11;
                            temp_r2_2 = M2C_FIELD(arg0, s32 *, 8);
                            D_02034910[2] = (s16) temp_r2_2;
                            D_02034910[3] = (s16) (temp_r0_11 - temp_r4_7);
                            D_02034910[4] = (s16) temp_r2_2;
                            D_02034910[5] = 0;
                            *phase = temp_r4_7 - 8;
                        } else {
                            func_0809534C();
                            *(s16 *)0x0300004E = (s16) temp_r4_7;
                            func_08095114(arg0);
                        }
                        }
                    }
                    }
                }
            }
            break;
        }
    }
    {
        var_r7 = 0;
        {
            register s16 *shape asm("r2") = D_02034910;
            register s32 zero asm("r5") = 0;
            register s32 count asm("r0") = *(s16 *)((u8 *)shape + zero);
        if ((s32) var_r7 < count) {
            register s16 *shape_base asm("r5") = shape;
            register s32 mask asm("r4") = 2;
            register s32 limit asm("r3") = 0xF0;
            register s32 offset asm("r0");
            register u16 *shape_addr asm("r1");
            do {
                offset = ((var_r7 * 2) + 1) * 2;
                asm volatile("add %0, %1, %2"
                             : "=r"(shape_addr)
                             : "r"(offset), "r"(shape_base));
                if (!(M2C_FIELD(arg0, volatile s32 *, 0) & mask)) {
                    var_r0 = *shape_addr;
                } else {
                    var_r0 = limit - *shape_addr;
                }
                *shape_addr = var_r0;
                var_r7 += 1;
                {
                    register s32 reload_zero asm("r1") = 0;
                    count = *(s16 *)((u8 *)shape + reload_zero);
                }
            } while ((s32) var_r7 < count);
        }
        }
    }
}
