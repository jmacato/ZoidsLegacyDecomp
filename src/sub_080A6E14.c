#include "m2c_prelude.h"

void func_80ECD28(void *, void *, s32);
void func_8092E84(s32);
void func_8095208(void *, void *, s32);
void func_80ED17C(s32);

void sub_080A6E14(void)
{
    u16 source[16];
    u16 output[16];
    volatile u32 shifted_spill;
    register u32 phase asm("r4");
    register u16 *output_base asm("r9");
    register u32 max_component asm("r8");
    u8 index;

    func_80ECD28((void *)0x05000200, source, 8);
    phase = 0;
    output_base = output;
    {
        register u32 max_load asm("r1") = 31;
        asm volatile("" : "+r"(max_load));
        max_component = max_load;
    }

outer:
    index = 0;
    {
        register u32 next_phase asm("r10");
        register u32 next_load asm("r2") = phase + 1;
        register u32 max_view asm("r0");
        register u32 shifted asm("r3");

        asm volatile("" : "+r"(next_load));
        next_phase = next_load;
        max_view = max_component;
        asm volatile("" : "+r"(max_view));
        phase &= max_view;
        shifted = phase << 24;
        do {
            register u32 offset_work asm("r0") = index << 1;
            register u8 *source_base asm("r2") = (u8 *)source;
            register u8 *byte_address asm("r1");
            register u32 byte_value asm("r1");
            register u32 offset asm("r6");
            register u32 component asm("r5");
            register u32 current asm("r4");
            register s32 delta asm("r0");

            byte_address = source_base + offset_work;
            byte_value = *byte_address;
            component = max_component;
            component &= byte_value;
            current = shifted >> 24;
            offset = offset_work;
            if (current == 0) {
                register s32 call_arg asm("r0") = 0x7F;
                asm volatile("" : "+r"(call_arg));
                shifted_spill = shifted;
                func_8092E84(call_arg);
                shifted = shifted_spill;
            }

            if ((u8)(current - 9) <= 7) {
                current = (u8)(16 - current);
            } else if (current > 16) {
                current = 0;
            }

            {
                register u32 max_view asm("r1") = max_component;
                asm volatile("" : "+r"(max_view));
                delta = max_view - component;
            }
            delta *= current;
            if (delta < 0) {
                delta += 7;
            }
            delta >>= 3;
            asm volatile("add %0, %1, %0"
                         : "+r"(delta)
                         : "r"(component));
            delta <<= 24;
            component = (u32)delta >> 24;
            {
                register u16 *destination asm("r2");

                {
                    register u16 *output_view asm("r4") = output_base;
                    asm volatile("" : "+r"(output_view));
                    destination = (u16 *)((u8 *)output_view + offset);
                }
                {
                    register u16 *source_view asm("r1") = source;
                    register u16 *source_address asm("r0");
                    register u32 source_value asm("r0");
                    asm volatile("" : "+r"(source_view));
                    asm volatile("add %0, %1, %2"
                                 : "=r"(source_address)
                                 : "r"(source_view), "r"(offset));
                    source_value = *source_address;
                    {
                        register u32 color_mask asm("r4") = 0xFFE0;
                        register u32 mask_view asm("r1");
                        asm volatile("" : "+r"(color_mask));
                        mask_view = color_mask;
                        asm volatile("" : "+r"(mask_view));
                        source_value &= mask_view;
                    }
                    component |= source_value;
                    *destination = component;
                }
            }
            index++;
        } while (index <= 15);

        {
            register u16 *upload_source asm("r0") = output_base;
            asm volatile("" : "+r"(upload_source));
            func_8095208(upload_source, (void *)0x05000200, 32);
        }
        {
            register u32 next_view asm("r1") = next_phase;
            register u32 wrapped asm("r0");
            asm volatile("" : "+r"(next_view));
            wrapped = next_view << 24;
            phase = wrapped >> 24;
        }
    }
    func_80ED17C(1);
    goto outer;
}
