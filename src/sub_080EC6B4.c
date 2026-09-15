#include "m2c_prelude.h"

void sub_080EC6B4(void *arg0, s32 arg1, s32 arg2) {
    register void *base asm("r4");
    s32 bits;
    register s32 temp_r6 asm("r6");
    register s32 count asm("r2");
    register u8 *entry asm("r1");
    register s32 mask asm("r5");
    register s32 flag_mask asm("r8");
    register s32 set_mask asm("r12");
    s32 temp_r3;

    asm volatile("" ::: "r9");
    base = arg0;
    arg1 <<= 16;
    bits = (u32)arg1 >> 16;
    temp_r6 = arg2 << 16;
    temp_r3 = M2C_FIELD(base, s32 *, 0x34);
    if (temp_r3 == 0x68736D53) {
        {
            register s32 next asm("r0");
            next = temp_r3 + 1;
            asm volatile("" : "+r"(next));
            M2C_FIELD(base, s32 *, 0x34) = next;
        }
        count = M2C_FIELD(base, u8 *, 8);
        entry = M2C_FIELD(base, u8 **, 0x2C);
        mask = 1;
        if (count > 0) {
            flag_mask = 0x80;
            temp_r6 = (u32)temp_r6 >> 18;
            set_mask = 3;
            do {
                {
                    register s32 test asm("r0");
                    test = bits;
                    asm volatile("" : "+r"(test));
                    test &= mask;
                    if (test) {
                        temp_r3 = entry[0];
                        test = flag_mask;
                        asm volatile("" : "+r"(test));
                        test &= temp_r3;
                        if (test) {
                            entry[0x13] = temp_r6;
                            test = set_mask;
                            asm volatile("" : "+r"(test));
                            test |= temp_r3;
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
