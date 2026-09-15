#include "m2c_prelude.h"

typedef struct {
    u32 word0;
    u32 flags;
    u16 unk8;
    u16 amount;
} BattleState;

typedef struct {
    u32 flags;
    u16 kind;
    u16 value;
    u32 unk8;
} Modifier;

extern BattleState *func_080E669C(u32, u32, u32, u32);
extern void func_080E66B8(void);
extern void func_080E8C90(u32, u32, u32, u32, BattleState *);
extern u8 func_080BF464(u8, u8, s32);
extern u8 D_0203055C[];
extern u8 D_02034B4C[];

s16 sub_080E813C(u32 arg0, u32 arg1, u32 arg2, u32 arg3, u32 arg4,
                 u32 arg5, u32 arg6)
{
    register u32 first asm("r4") = arg0;
    register u32 second asm("r5") = arg1;
    register u32 third asm("r6") = arg2;
    register u32 fourth asm("r3") = arg3;
    register u32 raw_unit asm("r0") = arg4;
    register u32 raw_member asm("r1") = arg5;
    register u32 raw_arg6 asm("r2") = arg6;
    register u32 unit asm("r9");
    register u32 member asm("sl");
    register u32 result asm("r8");
    volatile u32 outgoing;
    volatile u32 saved_arg6;
    u8 *volatile data;
    u32 saved_arg3;
    BattleState *state;
    register u32 flags asm("r2");
    u16 accumulator;

    first = (u8)first;
    second = (u8)second;
    third = (u8)third;
    fourth = (u8)fourth;
    raw_unit = (u8)raw_unit;
    unit = raw_unit;
    raw_member = (u8)raw_member;
    member = raw_member;
    raw_arg6 = (u8)raw_arg6;
    saved_arg6 = raw_arg6;
    saved_arg3 = fourth;
    state = func_080E669C(raw_unit, raw_member, raw_arg6, fourth);
    data = D_02034B4C + unit * 0x1380 + member * 0x270;
    asm volatile(
        "str r7, [sp]\n"
        "add r0, r4, #0\n"
        "add r1, r5, #0\n"
        "add r2, r6, #0\n"
        "ldr r3, [sp, #12]\n"
        "bl func_080E8C90"
        : "=m"(outgoing)
        : "r"(first), "r"(second), "r"(third), "r"(state),
          "m"(saved_arg3)
        : "r0", "r1", "r2", "r3", "lr", "cc", "memory");

    if (func_080BF464(first, second, 30) != 0xFF &&
        (state->flags & 0x10) != 0 &&
        (data[0x36] & 0x40) != 0) {
        state->amount += 20;
    }

    {
        register u32 amount asm("r3") = state->amount;
        register u32 loaded_flags asm("r1");

        result = amount;
        loaded_flags = state->flags;
        {
            register u32 flag_test asm("r0") = 0x40;

            flag_test &= loaded_flags;
            flags = loaded_flags;
            if (flag_test == 0 && D_0203055C[1] == 11) {
            register u32 shifted asm("r0") = amount << 16;
            register s32 half asm("r1") = (s32)shifted >> 16;

            shifted >>= 31;
            half += shifted;
            half <<= 15;
            half = (u32)half >> 16;
            result = half;
            }
        }
    }

    accumulator = 0;
    if ((flags & 0x200) == 0) {
        register u32 arg6_check asm("r4") = saved_arg6;

        if (arg6_check == 0) {
            register u32 row_offset asm("ip");
            register u32 mask asm("r7");
            register u32 flags_view asm("r6");
            register u32 expected asm("r4");
            register u32 index asm("r3");

            accumulator = *(u16 *)(data + 0x46);
            index = 0;
            {
                register u32 row_calc asm("r0");
                register u32 member_calc asm("r1");

                {
                    register u32 unit_view asm("r1") = unit;

                    asm volatile("" : "+r"(unit_view));
                    row_calc = unit_view << 2;
                }
                {
                    register u32 member_view asm("r4") = member;

                    member_calc = member_view << 2;
                }
                row_calc += unit;
                row_calc <<= 3;
                {
                    register u32 unit_again asm("r4") = unit;

                    row_calc -= unit_again;
                }
                row_calc <<= 7;
                row_offset = row_calc;
                mask = 31;
                member_calc += member;
                member_calc <<= 3;
                {
                    register u32 member_again asm("r0") = member;

                    member_calc -= member_again;
                }
                member_calc <<= 4;
                member = member_calc;
                flags_view = flags;
                expected = flags_view;
                expected &= mask;
            }

            do {
                register Modifier *entry asm("r2");
                register u32 scratch_r1 asm("r1");

                {
                    register u32 entry_offset asm("r0");

                    asm volatile("ldr %0, [pc, #120]"
                                 : "=r"(scratch_r1));
                    scratch_r1 += member;
                    scratch_r1 += row_offset;
                    entry_offset = index << 1;
                    entry_offset += index;
                    entry_offset <<= 2;
                    entry_offset += 0xE4;
                    entry = (Modifier *)(scratch_r1 + entry_offset);
                }
                {
                    scratch_r1 = entry->kind;

                    if (scratch_r1 != 0) {
                        register u32 masked_kind asm("r0") = 0x7F;

                        masked_kind &= scratch_r1;
                        if (masked_kind == 9 &&
                            ((((entry->flags & 0x1F000000) >> 24) & mask &
                              flags_view) == expected)) {
                            register s32 sum asm("r0") = (s16)accumulator;
                            register u32 addend asm("r2") = entry->value;

                            sum += addend;
                            accumulator = (u16)sum;
                        }
                    }
                }
                {
                    register u32 next asm("r0") = index + 1;

                    next <<= 24;
                    index = next >> 24;
                }
            } while (index <= 31);
        }
    }

    {
        register u8 *base asm("r1") = D_02034B4C;
        register u32 offset asm("r2") = 0x27BE;
        register u8 *kind asm("r0");

        kind = base + offset;
        kind += unit;
        if (*kind == 49) {
            register u32 stride asm("r0") = 148;
            register u32 entry_offset asm("r1") = unit;
            register u8 *entry asm("r1");

            entry_offset *= stride;
            {
                register u8 *table_base asm("r3") = D_02034B4C;
                register u32 table_offset asm("r4") = 0xA084;
                register u8 *table asm("r0");

                table = table_base + table_offset;
                entry = entry_offset + (u32)table;
            }
            {
                register u32 sum asm("r0") = accumulator << 16;
                register u32 addend asm("r1");

                sum = (s32)sum >> 16;
                addend = *(u16 *)entry;
                sum += addend;
                accumulator = (u16)sum;
            }
        }
    }

    {
        s16 signed_accumulator = accumulator;

        if (signed_accumulator < 0) {
            accumulator = 0;
        } else if (signed_accumulator > 9999) {
            accumulator = 9999;
        }
    }

    {
        register s32 difference asm("r1");
        register s32 signed_result asm("r0");

        {
            register u32 result_view asm("r0") = result;

            difference = result_view << 16;
            difference >>= 16;
        }
        {
            register s32 subtrahend asm("r0") = accumulator << 16;

            subtrahend >>= 16;
            difference -= subtrahend;
        }
        difference <<= 16;
        {
            register u32 normalized asm("r2") = (u32)difference >> 16;

            result = normalized;
        }
        signed_result = difference >> 16;
        if (signed_result <= 0) {
            register u32 one asm("r3") = 1;

            asm volatile("" : "+r"(one));
            result = one;
        } else if (signed_result > 9999) {
            result = 9999;
        }
    }

    func_080E66B8();
    {
        register u32 result_view asm("r4") = result;

        return (s16)result_view;
    }
}
