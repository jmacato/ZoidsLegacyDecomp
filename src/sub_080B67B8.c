#include "m2c_prelude.h"

void sub_080B67B8(s32 arg0) {
    register u8 *input asm("r12");
    register u8 *count asm("r4");
    u8 *values;
    u8 *auxiliary;
    u8 *source_values;
    register u32 index asm("r3");
    register u8 *count_init asm("r1");
    register s32 zero asm("r0");

    input = (u8 *)arg0;
    count_init = (u8 *)0x02032487;
    zero = 0;
    *count_init = zero;
    index = 0;
    values = (u8 *)0x02032473;
    count = count_init;
    auxiliary = (u8 *)0x0203247D;
    source_values = input;
    source_values += 8;

    do {
        register u8 *source asm("r0");
        s32 value;

        source = source_values + index;
        value = *source;
        if (value != 0) {
            register s32 output_offset asm("r0");
            register u8 *output asm("r0");
            register s32 auxiliary_offset asm("r1");
            register u8 *auxiliary_output asm("r1");
            register s32 input_offset asm("r2");
            register u8 *input_address asm("r0");
            register s32 auxiliary_value asm("r0");

            output_offset = *count;
            output_offset += (s32)values;
            output = (u8 *)output_offset;
            *output = value;
            auxiliary_offset = *count;
            auxiliary_offset += (s32)auxiliary;
            auxiliary_output = (u8 *)auxiliary_offset;
            input_offset = index << 1;
            input_address = input + 18;
            input_address += input_offset;
            auxiliary_value = *(u16 *)input_address;
            *auxiliary_output = auxiliary_value;
            zero = *count;
            zero += 1;
            *count = zero;
        }
        zero = index + 1;
        zero <<= 24;
        index = (u32)zero >> 24;
    } while (index <= 9);
}
