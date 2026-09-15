#include "m2c_prelude.h"

struct TransferDescriptor9AAA8 {
    u8 *first;
    u8 *second;
    u32 unk8;
    u8 *metadata;
};

void func_08095208(s32, s32, s32);
void func_080ECD38(void *, void *);

void sub_0809AAA8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 * volatile arg4)
{
    register s32 descriptor_value asm("r9");
    register u32 first_target asm("r6");
    register u32 second_target asm("r8");
    register u8 *source asm("r7");
    register u32 first_length asm("r4");
    register u32 second_length asm("r5");
    u8 *first;
    u8 *second_data;
    u64 save_marker;
    register u32 shared_high asm("r2");

    descriptor_value = arg0;
    asm volatile("" : : "r"(descriptor_value));
    first_target = arg2;
    asm volatile("" : : "r"(first_target));
    second_target = arg3;
    asm volatile("" : : "r"(second_target));
    source = arg4;
    arg1 <<= 24;
    first_target <<= 16;
    first_target >>= 16;
    {
        register u32 normalized_second asm("r0") = second_target;
        asm volatile("" : "+r"(normalized_second));
        normalized_second <<= 16;
        normalized_second >>= 16;
        second_target = normalized_second;
    }
    arg1 = (u32)arg1 >> 21;
    descriptor_value += arg1;

    {
        register struct TransferDescriptor9AAA8 *view asm("r1") =
            (struct TransferDescriptor9AAA8 *)descriptor_value;
        first = view->first;
    }
    first_length = first[1];
    {
        register u32 byte asm("r1") = first[2];
        byte <<= 8;
        first_length |= byte;
    }
    {
        register struct TransferDescriptor9AAA8 *view asm("r2") =
            (struct TransferDescriptor9AAA8 *)descriptor_value;
        register u8 *metadata asm("r1") = view->metadata;
        shared_high = metadata[3];
        shared_high <<= 16;
    }
    first_length |= shared_high;

    {
        register struct TransferDescriptor9AAA8 *view asm("r3") =
            (struct TransferDescriptor9AAA8 *)descriptor_value;
        second_data = view->second;
    }
    second_length = second_data[1];
    {
        register u32 byte asm("r1") = second_data[2];
        byte <<= 8;
        second_length |= byte;
    }
    second_length |= shared_high;

    func_080ECD38(first, source);
    {
        register struct TransferDescriptor9AAA8 *view asm("r1") =
            (struct TransferDescriptor9AAA8 *)descriptor_value;
        register u8 *loaded_second asm("r0") = view->second;
        register s32 next_source asm("r2");
        asm volatile("" : "+r"(loaded_second));
        next_source = (s32)(source + first_length);
        asm volatile("" : "+r"(next_source));
        descriptor_value = next_source;
        func_080ECD38(loaded_second, descriptor_value);
    }

    first_target <<= 5;
    {
        register u32 first_base asm("r3") = 0x06010000;
        asm volatile("" : "+r"(first_base));
        first_target += first_base;
    }
    first_length <<= 16;
    first_length >>= 16;
    asm volatile("" : : "r"(first_length));
    func_08095208((s32)source, first_target, first_length);
    asm volatile("" : "=l"(save_marker));

    {
        register u32 shifted_target asm("r0") = second_target;
        register u32 second_base asm("r1");
        asm volatile("" : "+r"(shifted_target));
        shifted_target <<= 5;
        second_target = shifted_target;
        second_base = 0x05000200;
        asm volatile("" : "+r"(second_base));
        second_target += second_base;
    }
    second_length <<= 16;
    second_length >>= 16;
    asm volatile("" : : "r"(second_length));
    func_08095208(descriptor_value, second_target, second_length);
    asm volatile("" : : "l"(save_marker));
}
