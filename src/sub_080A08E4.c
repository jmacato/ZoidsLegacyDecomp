#include "m2c_prelude.h"

extern s32 func_080A016C(u8, s32, s32);

s32 sub_080A08E4(s32 arg0, void **arg1)
{
    void **saved_arg1 = arg1;
    register u32 saved_arg0 asm("r8");
    register u32 count asm("r6");
    register u32 i asm("r2");

    asm volatile("" : : "r"(saved_arg1), "r"(arg0));
    saved_arg0 = (u8)arg0;
    asm volatile("" : : "r"(saved_arg0));
    count = ((u8 *)*saved_arg1)[1];
    asm volatile("" : : "r"(count));
    i = 0;
    asm volatile("" : : "r"(i));

    if (i < count) {
        register s32 *slots asm("ip") = (s32 *)0x020314C4;
        do {
            register u32 slot asm("r3") = 0;
            s32 *scan = slots;
            register u32 next asm("r5");

            asm volatile("" : : "r"(slot));

            if (*scan != 0) {
                scan = (s32 *)0x020314C4;
            scan_loop:
                scan++;
                slot++;
                if (slot > 69) {
                    goto scan_done;
                }
                if (*scan != 0) {
                    goto scan_loop;
                }
            }
        scan_done:
            next = i + 1;
            asm volatile("" : : "r"(next));

            if (slot != 70) {
                u32 offset = slot << 2;
                register u32 primary_base asm("r0") = (u32)slots;
                register s32 *primary asm("r4");
                register u32 secondary_base asm("r0");
                register s32 *secondary asm("r3");
                register u8 *input_base asm("r0");
                u8 *entry;
                asm volatile("" : "+r"(primary_base) : "r"(saved_arg1));
                primary = (s32 *)(offset + primary_base);
                asm volatile("" : "+r"(primary));
                secondary_base = 0x020315DC;
                asm volatile("" : "+r"(secondary_base) : "r"(primary));
                secondary = (s32 *)(offset + secondary_base);
                asm volatile("" : "+r"(secondary));
                asm volatile("" : : "r"(saved_arg1));
                input_base = (u8 *)*saved_arg1;
                asm volatile("" : "+r"(input_base) : "r"(i));
                i <<= 2;
                asm volatile("" : "+r"(i));
                i += (u32)input_base;
                entry = (u8 *)i;

                {
                    register u32 value asm("r1");
                    register u32 part asm("r0");
                    value = entry[2];
                    asm volatile("" : "+r"(value));
                    part = entry[3];
                    asm volatile("" : "+r"(part));
                    part <<= 8;
                    value |= part;
                    asm volatile("" : "+r"(value));
                    part = entry[4];
                    asm volatile("" : "+r"(part));
                    part <<= 16;
                    value |= part;
                    asm volatile("" : "+r"(value));
                    part = entry[5];
                    asm volatile("" : "+r"(part));
                    part <<= 24;
                    value |= part;

                    *secondary = value;
                    *primary = value;
                }
            }
            i = next;
            asm volatile("" : : "r"(i));
        } while (i < count);
    }

    {
        register s32 minus_one asm("r1") = -1;
        func_080A016C(saved_arg0, minus_one, 0);
    }
    return 0;
}
