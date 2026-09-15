#include "m2c_prelude.h"

s32 func_080ECD5C(s32);
void func_080ECD2C(void *, void *, s32);

u8 sub_0809329C(s32 arg0) {
    register s32 saved_arg asm("r9");
    register s32 *zero asm("r8");
    register s32 minus_thirteen asm("r10");
    volatile s32 scratch[2];
    u8 *initial_base;
    u8 *end_base;
    s32 random;

    saved_arg = arg0;
    asm volatile("" : "+r"(saved_arg));
    {
        s32 random_base;

        random_base = 0x03003174;
        asm volatile("" : "+r"(random_base));
        scratch[0] = 0;
        random = func_080ECD5C(random_base) << 24;
    }
    initial_base = (u8 *)0x030032D4;
    initial_base[3] = 0;
    if (random != 0) {
        u8 *base;
        s32 *zero_temp;
        s32 minus_temp;
        s32 index;

        index = 0;
        zero_temp = (s32 *)&scratch[1];
        asm volatile("" : "+r"(zero_temp));
        zero = zero_temp;
        asm volatile("" : "+r"(zero));
        base = initial_base;
        minus_temp = -13;
        asm volatile("" : "+r"(minus_temp));
        minus_thirteen = minus_temp;
        asm volatile("" : "+r"(minus_thirteen));
        do {
            u8 *block;
            u16 *cursor;
            s32 sum;
            s32 count;
            s32 next;
            s32 signed_sum;
            u8 *source;

            block = *(u8 **)(base + 0x2C) + index * 0x18;
            sum = 0;
            count = 0;
            next = index + 1;
            cursor = (u16 *)block;
            do {
                sum += *cursor;
                cursor++;
                count++;
            } while ((u32)count <= 9);
            signed_sum = (s16)sum;
            asm volatile("" : "+r"(signed_sum));
            source = block + 4;
            if (signed_sum == minus_thirteen) {
                register s32 destination asm("r1");

                destination = index << 4;
                asm volatile("" : "+r"(destination));
                destination += saved_arg;
                func_080ECD2C(source, (void *)destination, 0x04000004);
                base[3] |= 1 << index;
            }
            scratch[1] = 0;
            func_080ECD2C((void *)zero, source, 0x05000004);
            index = next;
        } while (index <= 1);
    }
    end_base = (u8 *)0x030032D4;
    end_base[2] |= end_base[3];
    return end_base[3];
}
