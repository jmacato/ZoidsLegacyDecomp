#include "m2c_prelude.h"

void func_080ED038(void *, void *, s32);

void sub_08097240(s32 arg0) {
    u8 index;
    s32 stride;
    u8 *scratch;
    u8 *temporary;
    register s32 key asm("r1");
    register u8 *initial_base asm("r2");
    register s32 first asm("r0");

    arg0 <<= 24;
    key = (u32)arg0 >> 24;
    index = 0;
    initial_base = (u8 *)0x0200A8A0;
    first = initial_base[0x13];
    temporary = (u8 *)0x0200D8C0;
    asm volatile("" : "+r"(temporary));
    if (first != key) {
        register u8 *loop_base asm("r3");
        register s32 search_stride asm("r2");

        loop_base = initial_base;
        search_stride = 0x4D0;
        do {
            index = (u8)(index + 1);
            if (index > 9) {
                break;
            }
        } while (loop_base[index * search_stride + 0x13] != key);
    }

    scratch = (u8 *)0x0200A8A0;
    stride = 0x4D0;
    func_080ED038(temporary, scratch + index * stride, stride);
    {
        register u32 current asm("r1");

        current = index;
        if (current <= 8) {
            do {
                u32 next;
                register s32 destination_offset asm("r0");
                register u8 *destination asm("r0");
                register s32 source_offset asm("r1");
                register u8 *source asm("r1");

                destination_offset = current;
                destination_offset *= stride;
                destination = (u8 *)(destination_offset + (s32)scratch);
                asm volatile("" : "+r"(destination));
                next = current + 1;
                source_offset = next;
                source_offset *= stride;
                source = (u8 *)(source_offset + (s32)scratch);
                func_080ED038(destination, source, stride);
                next <<= 24;
                current = next >> 24;
            } while (current <= 8);
        }
    }
    {
        register u8 *final_base asm("r0");
        register s32 final_offset asm("r1");
        register u8 *final_temporary asm("r1");
        register s32 final_stride asm("r2");

        final_base = (u8 *)0x0200A8A0;
        asm volatile("" : "+r"(final_base));
        final_offset = 0x2B50;
        asm volatile("" : "+r"(final_offset));
        final_base = (u8 *)((s32)final_base + final_offset);
        final_temporary = (u8 *)0x0200D8C0;
        final_stride = 0x4D0;
        func_080ED038(final_base, final_temporary, final_stride);
    }
}
