#include "m2c_prelude.h"

void func_080ED038(void *, void *, s32);

void sub_080971AC(s32 arg0) {
    u32 index;
    u8 *scratch;
    s32 stride;
    register s32 key asm("r2");
    register u8 *initial_base asm("r0");
    register s32 first asm("r1");

    arg0 <<= 24;
    key = (u32)arg0 >> 24;
    index = 0;
    initial_base = (u8 *)0x0200A8A0;
    first = initial_base[0x13];
    scratch = initial_base;
    if (first != key) {
        register u8 *loop_base asm("r3");
        register s32 search_stride asm("r1");

        loop_base = scratch;
        search_stride = 0x4D0;
        do {
            index = (u8)(index + 1);
            if (index > 9) {
                break;
            }
        } while (loop_base[index * search_stride + 0x13] != key);
    }

    stride = 0x4D0;
    {
        register s32 selected_offset asm("r0");
        register u8 *selected asm("r2");
        register s32 flags asm("r0");
        register s32 mask asm("r1");

        selected_offset = index;
        selected_offset *= stride;
        selected = (u8 *)(selected_offset + (s32)scratch);
        flags = *(s32 *)selected;
        mask = 0x200;
        flags &= mask;
        if (flags == 0) {
            {
                register u8 *first_temporary asm("r0");

                first_temporary = (u8 *)0x0200D8C0;
                asm volatile("" : "+r"(first_temporary));
                func_080ED038(first_temporary, selected, stride);
            }
            if (index != 0) {
                do {
                    register s32 destination_offset asm("r0");
                    register u8 *destination asm("r0");
                    register s32 source_offset asm("r1");
                    register u8 *source asm("r1");

                    destination_offset = index;
                    destination_offset *= stride;
                    destination = (u8 *)(destination_offset + (s32)scratch);
                    index -= 1;
                    source_offset = index;
                    source_offset *= stride;
                    source = (u8 *)(source_offset + (s32)scratch);
                    func_080ED038(destination, source, stride);
                    index <<= 24;
                    index >>= 24;
                } while (index != 0);
            }
            {
                register u8 *final_base asm("r4");
                register u8 *temporary asm("r1");
                register s32 final_stride asm("r2");
                register s32 final_flags asm("r0");
                register s32 final_mask asm("r1");

                final_base = (u8 *)0x0200A8A0;
                temporary = (u8 *)0x0200D8C0;
                final_stride = 0x4D0;
                func_080ED038(final_base, temporary, final_stride);
                final_flags = *(s32 *)final_base;
                final_mask = 2;
                final_flags |= final_mask;
                *(s32 *)final_base = final_flags;
            }
        }
    }
}
