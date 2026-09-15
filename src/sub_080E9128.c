#include "m2c_prelude.h"

s32 func_080E6664(s32);                             /* extern */
M2C_UNK func_080E705C(s8 *, s32);                   /* extern */
M2C_UNK func_080E8B08(s32, u32);                    /* extern */
M2C_UNK func_080E90AC(s32, u32);                    /* extern */
M2C_UNK func_080ECD2C(void *, void *, u32);          /* extern */
M2C_UNK func_080ED038(void *, void *, s32);         /* extern */
extern u8 D_020218E4[];
extern u8 D_0202ECF4[];
extern u8 D_087AFCC4[];

void sub_080E9128(void) {
    volatile s32 sp0;
    volatile s32 sp4;
    volatile s32 sp8;
    void *volatile spC;
    volatile s32 sp10;
    s8 *volatile sp14;
    s32 *volatile sp18;
    u8 *volatile sp1C;
    s8 *volatile sp20;
    u16 *volatile sp24;
    u16 *volatile sp28;
    u16 *volatile sp2C;
    u16 *volatile sp30;
    u16 *volatile sp34;
    void *volatile sp38;
    s16 temp_r0_5;
    s16 temp_r0_9;
    register s32 temp_r0 asm("r0");
    s32 temp_r0_12;
    s32 temp_r0_14;
    s32 temp_r0_4;
    s32 temp_r1_2;
    register s32 var_r1 asm("r1");
    s8 *temp_r0_3;
    u16 *temp_r1;
    register u32 var_r8 asm("r8");
    u8 *temp_r2;
    u8 temp_r0_10;
    u8 temp_r0_11;
    u8 temp_r0_13;
    u8 temp_r0_2;
    register u32 temp_r0_7 asm("r0");
    u8 temp_r4;
    u8 var_r2;
    u8 var_r3;
    u8 var_r3_2;
    u8 var_r3_3;
    u8 *temp_r0_6;
    u8 *temp_r0_8;
    u8 *temp_r1_3;
    register u8 *temp_r4_2 asm("r4");
    register u8 *temp_r5 asm("r5");

    var_r8 = 0;
loop_1:
    temp_r0 = var_r8 * 0x270;
    temp_r5 = temp_r0 + 0x02034B4C;
    if (var_r8 <= 5U) {
        register u8 *save_base asm("r6") = D_020218E4;
        {
            register u32 offset asm("r1") = 0x690C;
            register u8 *lookup asm("r0") = save_base + offset;
            lookup += var_r8;
            temp_r4 = *lookup;
        }
        if (temp_r4 != 0) {
            {
                register u32 id asm("r1") = temp_r4;
                register u32 offset asm("r0") = id << 3;
                register u8 *base_plus4 asm("r1");
                asm volatile("" : "+r"(id));
                offset -= id;
                offset <<= 4;
                base_plus4 = save_base + 4;
                temp_r0_6 = (u8 *)(offset + (u32)base_plus4);
            }
            spC = temp_r0_6;
            temp_r4_2 = (u8 *)(M2C_FIELD(temp_r0_6, u8 *, 2) << 6);
            {
                register u32 offset asm("r2") = 0x5A94;
                register u8 *base asm("r0") = save_base + offset;
                temp_r4_2 += (u32)base;
            }
            {
                register u8 *dst asm("r0") = temp_r5;
                asm volatile("" : "+r"(dst));
                func_080ED038(dst, spC, 0x70);
            }
            func_080ED038(temp_r5 + 0x70, temp_r4_2, 0x40);
            temp_r0_7 = M2C_FIELD(temp_r4_2, u8 *, 0x31);
            if (temp_r0_7 != 0) {
                register u32 detail asm("r1") = temp_r0_7;
                register u32 stride asm("r0") = 0x34;
                register u32 offset asm("r2") = 0x67D4;
                register u8 *base asm("r0");
                register u8 *src asm("r1");
                register u8 *dst asm("r0");
                detail *= stride;
                base = save_base + offset;
                src = (u8 *)(detail + (u32)base);
                dst = temp_r5 + 0xB0;
                func_080ED038(dst, src, 0x34);
            } else {
                register u8 *dst asm("r1");
                register void *src asm("r0");
                sp0 = temp_r0_7;
                dst = temp_r5 + 0xB0;
                asm volatile("" : "+r"(dst));
                src = (void *)&sp0;
                asm volatile("" : "+r"(src));
                func_080ECD2C(src, dst, 0x0500000D);
            }
            if ((func_080E6664(0x11) << 0x18) != 0) {
                var_r3_3 = 0;
                do {
                    u8 *item;
                    temp_r0_8 = temp_r5 + (var_r3_3 * 4);
                    item = (u8 *)((M2C_FIELD(temp_r0_8, u16 *, 0x52) * 0x18) + 0x087B2524);
                    asm volatile("" : "+r"(item));
                    if (2 & M2C_FIELD(item, u16 *, 2)) {
                        u32 zero;
                        asm volatile("" : "=r"(zero));
                        zero = 0;
                        M2C_FIELD(temp_r0_8, u16 *, 0x52) = zero;
                    }
                    var_r3_3 += 1;
                } while ((u32) var_r3_3 <= 3U);
            }
            func_080E90AC(0, var_r8);
            func_080E8B08(0, var_r8);
            temp_r0_9 = M2C_FIELD(temp_r5, s16 *, 0x3E);
            M2C_FIELD(temp_r5, s16 *, 8) = (s16) ((s32) (temp_r0_9 + ((u32) temp_r0_9 >> 0x1F)) >> 1);
            if (*(u8 *)0x0203055C == 1) {
                M2C_FIELD(temp_r5, u16 *, 6) = (u16) M2C_FIELD(temp_r5, u16 *, 0x3A);
            }
        } else {
            temp_r5[0] = temp_r4;
            sp4 = (s32) temp_r4;
            {
                register u8 *dst asm("r1") = temp_r5 + 0x70;
                asm volatile("" : "+r"(dst));
                func_080ECD2C(&sp4, dst, 0x05000010);
            }
            sp8 = (s32) temp_r4;
            {
                register u8 *dst asm("r1") = temp_r5 + 0xB0;
                asm volatile("" : "+r"(dst));
                func_080ECD2C(&sp8, dst, 0x0500000D);
            }
        }
        {
            register u8 *base asm("r2") = (u8 *)0x02034B4C;
            register u32 offset asm("r1") = 0x9C;
            register u8 *dst asm("r0");
            asm volatile("" : "+r"(base), "+r"(offset));
            offset <<= 6;
            dst = base + offset;
            dst += var_r8;
            *dst = (u8)var_r8;
        }
        {
            register u8 *base asm("r0") = (u8 *)0x02034B4C;
            register u32 offset asm("r2") = 0xA31C;
            register u8 *dst asm("r1");
            register u8 *save_base asm("r0");
            register u32 save_offset asm("r2");
            asm volatile("" : "+r"(base), "+r"(offset));
            dst = base + offset;
            dst += var_r8;
            save_base = D_020218E4;
            save_offset = 0x690C;
            asm volatile("" : "+r"(save_base), "+r"(save_offset));
            save_base += save_offset;
            save_base += var_r8;
            *dst = *save_base;
        }
        {
            register u8 *dst asm("r1") = (u8 *)0x02037252;
            register u32 value asm("r0");
            dst += var_r8;
            asm volatile("" : "+r"(dst));
            value = 0xFF;
            *dst = value;
        }
    } else {
        register u32 table_shift asm("r9");
        register u8 *copy_dst asm("sl");
        register u8 *clear_first asm("ip");
        register u8 *grid asm("r6");
        u8 *clear_second;
        if (var_r8 == 6) {
            temp_r0_2 = D_0202ECF4[2];
            switch (temp_r0_2) {
            case 0x69: {
                register u32 selected asm("r2") = 0x93;
                sp10 = selected;
                goto selected_record;
            }
            case 0x6A: {
                register u32 selected asm("r0") = 0x94;
                sp10 = selected;
                goto selected_record;
            }
            case 0x6B:
            case 0x6C:
                var_r1 = 0x96;
                goto store_selection;
            default:
                goto selected_record;
            }
        } else {
            var_r1 = 0x95;
store_selection:
            sp10 = var_r1;
        }
selected_record:
        {
            register u32 stack_value asm("r2") = (u32)&sp0;
            stack_value = *(u8 *)(stack_value + 0x10);
            temp_r5[0] = stack_value;
        }
        M2C_FIELD(temp_r5, s8 *, 1) = 0;
        M2C_FIELD(temp_r5, u8 *, 2) = (u8) var_r8;
        M2C_FIELD(temp_r5, s8 *, 3) = 0;
        {
            register u32 half_zero asm("r2") = 0;
            M2C_FIELD(temp_r5, s16 *, 4) = half_zero;
            M2C_FIELD(temp_r5, s16 *, 0x10) = half_zero;
        }
        asm volatile("movs r3, #0" : : : "r3");
        {
            register u8 *p0 asm("r0");
            register u8 *p1 asm("r1");
            register u8 *p2 asm("r2");
            register u32 shift_seed asm("r0");

            p0 = temp_r5 + 0x70;
            sp14 = (s8 *)p0;
            p1 = temp_r5 + 0xB0;
            sp38 = p1;
            asm volatile(
                "mov %0, sp\n\t"
                "add %0, %0, #8"
                : "=r"(p2));
            sp18 = (s32 *)p2;
            shift_seed = sp10;
            shift_seed <<= 3;
            table_shift = shift_seed;
            asm volatile(
                "movs r1, #80\n\t"
                "add r1, r1, r5\n\t"
                "mov %0, r1"
                : "=r"(copy_dst)
                :
                : "r1");
            p2 = temp_r5 + 0xA0;
            sp1C = p2;
            p0 = temp_r5 + 0xA1;
            sp20 = (s8 *)p0;
            asm volatile("mov %0, %1" : "=r"(p1) : "r"(temp_r5));
            p1 += 0xA4;
            sp24 = (u16 *)p1;
            p2 += 6;
            sp28 = (u16 *)p2;
            p0 += 7;
            sp2C = (u16 *)p0;
            p1 += 6;
            sp30 = (u16 *)p1;
            p2 += 6;
            sp34 = (u16 *)p2;
            asm volatile(
                "movs r0, #18\n\t"
                "add r0, r0, r5\n\t"
                "mov %0, r0"
                : "=r"(clear_first)
                :
                : "r0");
        }
        {
        register u8 clear_zero asm("r1") = 0;
        grid = temp_r5 + 0x1E;
        clear_second = temp_r5 + 0x18;
        asm volatile(
            "1:\n\t"
            "mov r2, ip\n\t"
            "add r0, r2, r3\n\t"
            "strb r1, [r0, #0]\n\t"
            "add r0, r7, r3\n\t"
            "strb r1, [r0, #0]\n\t"
            "movs r2, #0\n\t"
            "lsl r4, r3, #2\n"
            "2:\n\t"
            "add r0, r2, r4\n\t"
            "add r0, r6, r0\n\t"
            "strb r1, [r0, #0]\n\t"
            "add r0, r2, #1\n\t"
            "lsl r0, r0, #24\n\t"
            "lsr r2, r0, #24\n\t"
            "cmp r2, #3\n\t"
            "bls 2b\n\t"
            "add r0, r3, #1\n\t"
            "lsl r0, r0, #24\n\t"
            "lsr r3, r0, #24\n\t"
            "cmp r3, #5\n\t"
            "bls 1b"
            :
            : "r"(clear_first), "r"(clear_zero), "r"(grid), "r"(clear_second)
            : "r0", "r2", "r3", "r4", "memory");
        }
        {
            register u32 table_addr asm("r0");
            register u32 r1_value asm("r1");
            register u32 r2_value asm("r2");
            register u32 copy_index asm("r3");
            register u8 *dst_base asm("r4");

            r1_value = table_shift;
            asm volatile("" : "+r"(r1_value));
            r2_value = sp10;
            table_addr = r1_value - r2_value;
            table_addr <<= 3;
            r1_value = (u32)D_087AFCC4;
            table_addr += r1_value;
            asm volatile("" : "+r"(table_addr));
            copy_index = 0;
            dst_base = copy_dst;
            r2_value = table_addr;
            r2_value += 0x18;
            do {
                register u32 offset asm("r0") = copy_index << 2;
                register u8 *dst asm("r1") = dst_base + offset;
                register u8 *src asm("r0") = (u8 *)r2_value + offset;
                register u32 next asm("r0");
                *(u32 *)dst = *(u32 *)src;
                next = copy_index + 1;
                next <<= 24;
                copy_index = next >> 24;
            } while ((u32)copy_index <= 7U);
        }
        temp_r1_2 = M2C_FIELD(temp_r5, u8 *, 2) * 0x10;
        temp_r1_3 = temp_r1_2 + 0x087B70E4;
        {
            register u32 value asm("r0") = 0x64;
            register u8 *dst asm("r2");
            dst = (u8 *)sp14;
            *dst = value;
        }
        {
            register u32 value asm("r0") = M2C_FIELD(temp_r1_2, u8 *, 0x087B70E4);
            register u8 *dst asm("r2");
            dst = sp1C;
            *dst = value;
        }
        {
            register u32 zero asm("r2") = 0;
            register u8 *dst asm("r0");
            dst = (u8 *)sp20;
            *dst = zero;
        }
        {
            register u32 value asm("r0") = M2C_FIELD(temp_r1_3, u16 *, 4);
            register u16 *dst asm("r2");
            dst = sp24;
            *dst = value;
        }
        {
            register u32 value asm("r0") = M2C_FIELD(temp_r1_3, u16 *, 6);
            register u16 *dst asm("r2");
            dst = sp28;
            *dst = value;
        }
        {
            register u32 value asm("r0") = M2C_FIELD(temp_r1_3, u16 *, 8);
            register u16 *dst asm("r2");
            dst = sp2C;
            *dst = value;
        }
        {
            register u32 value asm("r0") = M2C_FIELD(temp_r1_3, u16 *, 0xA);
            register u16 *dst asm("r2");
            dst = sp30;
            *dst = value;
        }
        {
            register u32 value asm("r0") = M2C_FIELD(temp_r1_3, u16 *, 0xC);
            register u16 *dst asm("r1");
            dst = sp34;
            *dst = value;
        }
        func_080E705C(sp14, 1);
        {
            register u32 zero asm("r2") = 0;
            sp8 = zero;
        }
        func_080ECD2C(sp18, sp38, 0x0500000D);
        func_080E90AC(0, var_r8);
        func_080E8B08(0, var_r8);
        {
            register u8 *record asm("r1") = spC;
            M2C_FIELD(temp_r5, u16 *, 6) = M2C_FIELD(record, u16 *, 0x3A);
            temp_r0_5 = M2C_FIELD(record, s16 *, 0x3E);
        }
        M2C_FIELD(temp_r5, s16 *, 8) = (s16) ((s32) (temp_r0_5 + ((u32) temp_r0_5 >> 0x1F)) >> 1);
    }
    asm volatile(
        "movs r1, #154\n\t"
        "lsl r1, r1, #2\n\t"
        "add r0, r5, r1\n\t"
        "movs r2, #0\n\t"
        "str r2, [r0, #0]\n\t"
        "add r1, #4\n\t"
        "add r0, r5, r1\n\t"
        "str r2, [r0, #0]\n\t"
        "movs r2, #153\n\t"
        "lsl r2, r2, #2\n\t"
        "add r0, r5, r2\n\t"
        "movs r1, #0\n\t"
        "strh r1, [r0, #0]"
        : : : "r0", "r1", "r2", "memory");
    asm volatile("" : "+r"(var_r8));
    temp_r0_10 = var_r8 + 1;
    var_r8 = (u32) temp_r0_10;
    if ((u32) temp_r0_10 <= 7U) {
        goto loop_1;
    }
    {
        register u32 zero asm("r2");
        asm volatile("movs %0, #0" : "=r"(zero));
        var_r8 = zero;
    }
    do {
        temp_r0_12 = var_r8 * 2;
        M2C_FIELD(temp_r0_12, u16 *, 0x0203EDE8) = (u16) M2C_FIELD(temp_r0_12, u16 *, 0x02021774);
        temp_r0_11 = var_r8 + 1;
        var_r8 = temp_r0_11;
    } while ((u32) temp_r0_11 <= 8U);
    var_r8 = 0;
    do {
        temp_r0_14 = var_r8 * 2;
        M2C_FIELD(temp_r0_14, u16 *, 0x0203EE0C) = (u16) M2C_FIELD(temp_r0_14, u16 *, 0x02021786);
        temp_r0_13 = var_r8 + 1;
        var_r8 = temp_r0_13;
    } while ((u32) temp_r0_13 <= 0x16U);
}
