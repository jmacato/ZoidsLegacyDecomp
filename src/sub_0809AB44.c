#include "m2c_prelude.h"

M2C_UNK func_0809A1BC(M2C_UNK, s32, M2C_UNK);
M2C_UNK func_080ECD34(M2C_UNK, u16 *);

void sub_0809AB44(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    u16 *var_r7;
    u16 temp_r2;
    u16 var_r0;
    u16 var_r1;
    u8 temp_r0;
    register u32 vram asm("r8");

    arg0 <<= 24;
    temp_r0 = (u32)arg0 >> 24;
    arg1 <<= 16;
    arg1 = (u32)arg1 >> 16;
    arg2 <<= 16;
    arg2 = (u32)arg2 >> 16;
    temp_r2 = arg2;
    asm volatile("" : "+r"(arg2), "+r"(temp_r2));
    arg3 <<= 16;
    arg3 = (u32)arg3 >> 16;
    arg4 <<= 16;
    arg4 = (u32)arg4 >> 16;
    asm volatile("" : : "r"(arg3), "r"(arg3), "r"(arg3), "r"(arg3),
                          "r"(arg3), "r"(arg3), "r"(arg3), "r"(arg3));
    asm volatile("" : : "r"(arg3), "r"(arg3), "r"(arg3), "r"(arg3),
                          "r"(arg3));
    asm volatile("" : : "r"(arg4), "r"(arg4), "r"(arg4), "r"(arg4),
                          "r"(arg4), "r"(arg4), "r"(arg4), "r"(arg4));
    asm volatile("" : : "r"(arg4), "r"(arg4), "r"(arg4), "r"(arg4),
                          "r"(arg4), "r"(arg4), "r"(arg4), "r"(arg4));
    asm volatile("" : : "r"(arg4));
    asm volatile("" : : "r"(arg3), "r"(arg3), "r"(arg3), "r"(arg3),
                          "r"(arg3), "r"(arg3), "r"(arg3), "r"(arg3));
    asm volatile("" : : "r"(arg1), "r"(arg1), "r"(arg1), "r"(arg1));
    asm volatile("" : : "r"(arg1), "r"(arg1), "r"(arg1), "r"(arg1),
                          "r"(arg1), "r"(arg1), "r"(arg1), "r"(arg1));
    asm volatile("" : : "r"(arg1), "r"(arg1), "r"(arg1), "r"(arg1),
                          "r"(arg1), "r"(arg1), "r"(arg1), "r"(arg1));
    {
        register u32 call0 asm("r0") = 0x080F1548;
        register u32 call1 asm("r1") = arg1 << 14;
        register u32 offset asm("r2") = arg2 << 5;
        register u32 base asm("r3") = 0xC0;

        base <<= 19;
        vram = base;
        offset += vram;
        call1 += offset;
        func_080ECD34(call0, call1);
    }
    func_0809A1BC(0x080F1640, (arg3 << 5) + 0x05000000, 0x02002880);
    var_r7 = (arg4 << 11) + vram;
    func_080ECD34(0x080F1668, var_r7);
    {
        register volatile u16 *flags asm("ip");
        register u32 index2 asm("r1") = temp_r0;
        register u32 bg_offset asm("r8");
        register u32 index8_input asm("r3");
        register u32 state_offset asm("r2");

        var_r0 = 0;
        arg3 <<= 12;
        flags = (u16 *)0x0300004C;
        index2 <<= 1;
        bg_offset = index2;
        arg4 <<= 8;
        arg1 <<= 2;
        index8_input = temp_r0;
        state_offset = index8_input << 3;
        do {
            var_r1 = 0;
            do {
                *var_r7 = (*var_r7 + temp_r2) | arg3;
                var_r7++;
                var_r1 += 1;
            } while ((u32)var_r1 <= 31);
            var_r0 += 1;
        } while ((u32)var_r0 <= 19);

        asm volatile("" : "+r"(arg1), "+r"(arg4));
        {
            register u32 mask asm("r0") = 0x80;
            register u32 shift asm("r1") = temp_r0;
            register volatile u16 *flag_ptr asm("r3");
            register u32 current asm("r1");

            mask <<= 1;
            mask <<= shift;
            flag_ptr = flags;
            current = *flag_ptr;
            mask |= current;
            *flag_ptr = mask;
        }
        *(volatile u16 *)(0x04000008 + bg_offset) = arg4 | arg1 | 3;
        {
            register u32 state_base asm("r0") = 0x03000054;

            asm volatile("" : "+r"(state_base));
            state_offset += state_base;
            asm volatile("" : "+r"(state_offset) : : "memory");
        }
        {
            register u32 second_offset asm("r0") = bg_offset;

            second_offset += 1;
            second_offset <<= 2;
            {
                register u32 state_base asm("r1") = 0x03000054;

                asm volatile("" : "+r"(state_base));
                second_offset += state_base;
            }
            {
                register s32 zero asm("r1") = 0;

                *(s32 *)second_offset = zero;
                *(s32 *)state_offset = zero;
            }
        }
    }
}
