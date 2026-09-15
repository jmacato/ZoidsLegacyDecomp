#include "m2c_prelude.h"

void sub_080EC71C(void *arg0, s32 arg1, s32 arg2) {
    register void *base asm("r4");
    register s32 bits asm("r12");
    register s32 temp_r6 asm("r6");
    register s32 count asm("r2");
    register u8 *entry asm("r3");
    register s32 mask asm("r5");
    s32 high;
    register s32 flag_mask asm("r9");
    register s32 set_mask asm("r8");

    asm volatile("" ::: "r10");
    base = arg0;
    arg1 <<= 16;
    arg1 = (u32)arg1 >> 16;
    bits = arg1;
    arg2 <<= 16;
    temp_r6 = (u32)arg2 >> 16;
    entry = (u8 *)M2C_FIELD(base, s32 *, 0x34);
    if ((s32)entry == 0x68736D53) {
        {
            register s32 next asm("r0");
            next = (s32)entry + 1;
            asm volatile("" : "+r"(next));
            M2C_FIELD(base, s32 *, 0x34) = next;
        }
        count = M2C_FIELD(base, u8 *, 8);
        entry = M2C_FIELD(base, u8 **, 0x2C);
        mask = 1;
        if (count > 0) {
            flag_mask = 0x80;
            high = (s32)(temp_r6 << 16) >> 24;
            set_mask = 0xC;
            do {
                {
                    register s32 test asm("r0");
                    register s32 flags asm("r1");
                    test = bits;
                    asm volatile("" : "+r"(test));
                    test &= mask;
                    if (test) {
                        flags = entry[0];
                        test = flag_mask;
                        asm volatile("" : "+r"(test));
                        test &= flags;
                        if (test) {
                            entry[0xB] = high;
                            entry[0xD] = temp_r6;
                            test = set_mask;
                            asm volatile("" : "+r"(test));
                            test |= flags;
                            entry[0] = test;
                        }
                    }
                }
                count--;
                entry += 0x50;
                mask <<= 1;
            } while (count > 0);
        }
        M2C_FIELD(base, s32 *, 0x34) = 0x68736D53;
    }
}
