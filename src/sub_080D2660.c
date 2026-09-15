#include "m2c_prelude.h"

struct OwnerD2660 {
    u32 flags;
    u8 pad_04[0xA4];
    u32 extra_flags;
};

void *func_080D22B4(void *, s32, s32, s32);
extern u16 D_02034874[][2];
extern u16 D_02034894[][2];
extern u16 D_020348B4[][2];

void *sub_080D2660(struct OwnerD2660 *owner, s32 type, s32 arg2, s32 arg3)
{
    volatile s32 reserve0;
    volatile s32 reserve1;
    volatile s32 reserve2;
    volatile s32 reserve3;
    volatile s32 reserve4;
    volatile s32 reserve5;
    volatile s32 saved_arg3;
    register struct OwnerD2660 *saved_owner asm("r6");
    register s32 saved_type asm("r8");
    register u32 saved_arg2 asm("r9");
    register u32 saved_arg4 asm("ip");
    register s32 saved_arg5 asm("r4");
    register s32 saved_arg8 asm("r5");
    register u32 direction asm("r2");
    register u32 owner_flags asm("r3");
    register volatile s32 *outgoing asm("sp");

    asm volatile("" : "=m"(reserve0), "=m"(reserve1), "=m"(reserve2),
                       "=m"(reserve3), "=m"(reserve4), "=m"(reserve5));
    saved_owner = owner;
    saved_type = type;
    {
        register u32 arg4_input asm("r0") = outgoing[15];

        saved_arg5 = outgoing[16];
        saved_arg8 = outgoing[19];
        asm volatile("" : "+r"(arg4_input), "+r"(saved_arg5),
                           "+r"(saved_arg8));
        arg2 <<= 16;
        saved_arg2 = (u32)arg2 >> 16;
        arg3 <<= 16;
        arg3 = (u32)arg3 >> 16;
        saved_arg3 = arg3;
        arg4_input <<= 16;
        arg4_input >>= 16;
        saved_arg4 = arg4_input;
    }

    if ((saved_arg8 & 1) == 0) {
        register u32 flags asm("r0") = saved_owner->flags;
        register s32 test asm("r1") = 2;
        register s32 sign asm("r2");
        register u32 mask asm("r1");

        test &= flags;
        test = -test;
        sign = test >> 31;
        mask = 0x80;
        mask <<= 8;
        direction = sign & mask;
        owner_flags = flags;
    } else {
        register u32 flags asm("r1") = saved_owner->flags;
        register u32 test asm("r0") = 2;

        test &= flags;
        direction = 0;
        owner_flags = flags;
        if (test == 0) {
            direction = 0x80;
            direction <<= 8;
        }
    }

    {
        register void *base asm("sl") = (void *)0x087ACDD8;
        register u8 *first_table asm("r0") = (u8 *)D_02034874;
        register s32 offset asm("r1");
        register s32 selected asm("r8");
        register void *result;

        asm volatile("" : "+r"(first_table));
        offset = saved_type << 2;
        selected = *(u16 *)(offset + (s32)first_table);
        {
            register s32 arg3_reload asm("r7") = saved_arg3;
            register s32 normalized asm("r0");

            asm volatile("" : "+r"(arg3_reload));
            normalized = arg3_reload << 16;
            normalized >>= 16;
            saved_arg3 = normalized;
        }
        {
            register s32 arg4_reload asm("r7") = saved_arg4;
            register s32 normalized asm("r0");

            asm volatile("" : "+r"(arg4_reload));
            normalized = arg4_reload << 16;
            normalized >>= 16;
            outgoing[0] = normalized;
        }
        outgoing[1] = *(u16 *)((u8 *)D_02034894 + offset);
        outgoing[2] = *(u16 *)((u8 *)D_020348B4 + offset);
        {
            register u8 *owner_view asm("r0") = (u8 *)saved_owner;

            owner_view += 0xA8;
            saved_arg5 |= *(u32 *)owner_view;
        }
        saved_arg5 |= direction;
        outgoing[3] = saved_arg5;
        outgoing[4] = 0x080D2571;
        {
            register s32 boolean asm("r1") = 0;
            register s32 two asm("r0") = 2;

            owner_flags &= two;
            if (owner_flags != 0) {
                saved_arg8 &= two;
                if (saved_arg8 == 0) {
                    boolean = 1;
                }
            }
            outgoing[5] = boolean;
        }
        {
            register void *call0 asm("r0") = base;
            register s32 call1 asm("r1") = selected;
            register s32 call2 asm("r2") = saved_arg2;
            register s32 call3 asm("r3");

            asm volatile("" : "+r"(call0), "+r"(call1), "+r"(call2));
            call3 = saved_arg3;
            result = func_080D22B4(call0, call1, call2, call3);
        }
        {
            register s32 half_offset = 4;
            register s32 value = *(s16 *)((u8 *)result + half_offset);

            value <<= 8;
            *(s32 *)((u8 *)result + 0x28) = value;
        }
        {
            register s32 value = *(s16 *)((u8 *)result + 6);

            value <<= 8;
            *(s32 *)((u8 *)result + 0x2C) = value;
        }
        *(s32 *)((u8 *)result + 0x30) = outgoing[17];
        *(s32 *)((u8 *)result + 0x34) = outgoing[18];
        return result;
    }
}
