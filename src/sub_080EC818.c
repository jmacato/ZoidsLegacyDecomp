#include "m2c_prelude.h"

M2C_UNK func_080EC7F8(void *);

void sub_080EC818(void *arg0, s32 arg1, s32 arg2) {
    register void *base asm("r6");
    register s32 bits asm("r10");
    register u8 value asm("r8");
    register s32 count asm("r5");
    register u8 *entry asm("r4");
    u32 bit;
    register u8 keep asm("r9");
    s32 lock;

    base = arg0;
    arg1 <<= 16;
    arg1 = (u32)arg1 >> 16;
    bits = arg1;
    arg2 <<= 24;
    value = (u32)arg2 >> 24;
    lock = M2C_FIELD(base, s32 *, 0x34);
    if (lock == 0x68736D53) {
        M2C_FIELD(base, s32 *, 0x34) = lock + 1;
        count = M2C_FIELD(base, u8 *, 8);
        entry = M2C_FIELD(base, u8 **, 0x2C);
        bit = 1;
        if (count > 0) {
            keep = value;
            do {
                {
                    register s32 test asm("r0");
                    register s32 scratch asm("r1");
                    test = bits;
                    asm volatile("" : "+r"(test));
                    test &= bit;
                    if (test) {
                        test = 0x80;
                        asm volatile("" : "+r"(test));
                        scratch = entry[0];
                        test &= scratch;
                        if (test) {
                            entry[0x17] = value;
                            scratch = keep;
                            asm volatile("" : "+r"(scratch));
                            if (scratch == 0) {
                                func_080EC7F8(entry);
                            }
                        }
                    }
                }
                count--;
                entry += 0x50;
                bit <<= 1;
            } while (count > 0);
        }
        M2C_FIELD(base, s32 *, 0x34) = 0x68736D53;
    }
}
