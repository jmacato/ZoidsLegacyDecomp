#include "m2c_prelude.h"

struct Record96FBC {
    s32 field0;
    u8 pad04[0x0F];
    u8 index;
    u8 pad14[0x4BC];
};

extern u16 D_04000008[];
extern u16 D_02021668;
extern s32 D_02021654;
extern s32 D_02021658;
extern s32 D_0202165C;
extern s32 D_02021660;
extern s32 D_02021664;
extern u16 D_0202166A;
extern u16 D_0202166C;
extern s32 D_02021670;
extern u8 D_02021674;
extern u8 D_02002880[];
extern s32 D_03000054[];

void func_0809A1BC(s32, s32, void *);
void func_080ECD28(void *, void *, s32);
void func_080ECD2C(void *, void *, s32);
void func_080ECD34();
void func_08098804(void);

void sub_08096FBC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4,
    s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9)
{
    register u32 display asm("r0") = arg0;
    s32 field4 = arg4;
    register u32 field5 asm("r8") = arg5;
    register u32 field6 asm("r9") = arg6;
    register u32 field7 asm("r6") = arg7;
    register u32 field8 asm("sl") = arg8;
    register u32 field9 asm("ip") = arg9;
    struct {
        u16 dma_value;
        u8 pad02[2];
        s32 zero_a;
        s32 zero_b;
        volatile s32 display;
    } locals;
    s32 i;
    s32 address;
    struct Record96FBC *record;
    register s32 display_offset asm("r5");
    register u16 *display_base asm("r4");
    register s32 *destination asm("r0");
    register s32 *destination60 asm("r2");
    register u16 *destination68 asm("r2");
    register u32 value68 asm("r3");
    register u32 shifted68 asm("r0");
    register void *resource1 asm("r0");
    register u32 value6c asm("r2");
    register u32 field6_shift asm("r3");
    register void *transfer_buffer asm("r5");
    register void *resource2 asm("r0");
    register u32 transfer2 asm("r1");
    register u32 transfer2_base asm("r4");
    register void *resource3 asm("r0");
    register u32 transfer3 asm("r1");
    register u32 transfer3_base asm("r2");
    register void *zero_b_tmp asm("r3");
    register s32 loop_zero asm("r3");
    register s32 *state_base asm("r2");
    register s32 end_display asm("r4");
    register s32 *even_state asm("r1");
    register s32 odd_address asm("r0");
    void *zero_a_ptr;
    void *zero_b_ptr;
    register s32 zero asm("r5");

    asm volatile("" : "+r"(display));
    display <<= 24;
    display >>= 24;
    locals.display = display;
    arg1 <<= 24;
    arg1 = (u32)arg1 >> 24;
    field5 <<= 24;
    field5 >>= 24;
    field6 <<= 24;
    field6 >>= 24;
    field7 <<= 16;
    field7 >>= 16;
    display = locals.display;
    display_offset = display << 1;
    display_base = D_04000008;
    display_offset += (s32)display_base;
    asm volatile("" : "+r"(display_offset));

    {
        u32 control = field5 << 8;

        control |= arg1 << 2;
        field7 |= control;
        *(u16 *)display_offset = field7;
    }
    D_02021670 = arg2;
    D_02021658 = arg3;
    destination = &D_02021654;
    asm volatile("" : "+r"(destination));
    arg1 <<= 14;
    arg2 <<= 5;
    arg2 += 0x06000000;
    asm volatile("add %0, %1, %0" : "+r"(arg2) : "r"(arg1));
    *destination = arg2;
    destination = &D_0202165C;
    asm volatile("" : "+r"(destination), "+r"(field5));
    field5 <<= 11;
    field5 += 0x06000000;
    *destination = field5;
    destination60 = &D_02021660;
    asm volatile("" : "+r"(destination60));
    address = (field4 << 5) + 0x06000000;
    arg1 += address;
    *destination60 = arg1;
    D_02021664 = field4;
    destination68 = &D_02021668;
    value68 = field6;
    asm volatile("" : "+r"(destination68), "+r"(value68));
    shifted68 = value68 << 12;
    *destination68 = shifted68;
    D_0202166A = field8;
    D_0202166C = (value6c = field9);

    func_080ECD34(0x080ED21C);
    resource1 = (void *)0x080ED368;
    asm volatile("" : "+r"(resource1));
    field6_shift = field6;
    asm volatile("" : "+r"(field6_shift));
    field6_shift <<= 5;
    field6 = field6_shift;
    asm volatile("" : "+r"(field6));
    field6 += 0x05000000;
    asm volatile("" : "+r"(field6));
    transfer_buffer = D_02002880;
    func_0809A1BC((s32)resource1, field6, transfer_buffer);
    resource2 = (void *)0x080ED3A4;
    asm volatile("" : "+r"(resource2));
    transfer2 = D_0202166A;
    transfer2 <<= 5;
    transfer2_base = 0x06010000;
    asm volatile("" : "+r"(transfer2), "+r"(transfer2_base));
    transfer2 += transfer2_base;
    func_080ECD34((s32)resource2, transfer2);
    resource3 = (void *)0x080ED4D8;
    asm volatile("" : "+r"(resource3));
    transfer3 = D_0202166C;
    transfer3 <<= 5;
    transfer3_base = 0x05000200;
    asm volatile("" : "+r"(transfer3), "+r"(transfer3_base));
    transfer3 += transfer3_base;
    func_0809A1BC((s32)resource3, transfer3, transfer_buffer);

    i = 0;
    zero_a_ptr = &locals.zero_a;
    zero_b_tmp = &locals.zero_b;
    asm volatile("" : "+r"(zero_b_tmp));
    zero_b_ptr = zero_b_tmp;
    loop_zero = 0;
    asm volatile("" : "+r"(loop_zero));
    record = (struct Record96FBC *)0x0200A8A0;
    do {
        record->field0 = loop_zero;
        record->index = i;
        record++;
        i++;
    } while ((u32)i <= 9);

    zero = 0;
    locals.dma_value = field4 | D_02021668;
    func_080ECD2C(&locals.dma_value, (void *)D_0202165C, 0x01000400);
    locals.zero_a = zero;
    func_080ECD28(zero_a_ptr, (void *)0x0200DD90, 0x01000020);
    locals.zero_b = zero;
    func_080ECD28(zero_b_ptr, (void *)0x0200DE10, 0x01000020);

    state_base = D_03000054;
    end_display = locals.display;
    asm volatile("" : "+r"(state_base), "+r"(end_display));
    even_state = (s32 *)((end_display << 3) + (s32)state_base);
    asm volatile("" : "+r"(even_state));
    odd_address = end_display << 1;
    asm volatile("" : "+r"(odd_address));
    odd_address += 1;
    odd_address <<= 2;
    odd_address += (s32)state_base;
    asm volatile("" : "+r"(odd_address));
    *(s32 *)odd_address = zero;
    *even_state = zero;
    func_08098804();
    D_02021674 = zero;
}
