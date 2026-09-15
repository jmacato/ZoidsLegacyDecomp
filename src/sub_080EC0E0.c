#include "m2c_prelude.h"

s32 sub_080EC0E0(s32 arg0, s32 arg1, s32 arg2) {
    register s32 work asm("r0");
    register s32 value asm("r1");
    register s32 index asm("r5");
    register s32 fraction asm("r12");
    register u8 *table asm("r3");
    register u8 *curve asm("r4");
    register s32 code asm("r6");
    register s32 mask asm("r2");
    s32 offset;

    arg0 <<= 24;
    arg0 = (u32)arg0 >> 24;
    arg1 <<= 24;
    index = (u32)arg1 >> 24;
    arg2 <<= 24;
    arg2 = (u32)arg2 >> 24;
    fraction = arg2;

    if (arg0 == 4) {
        if ((u32)index <= 0x14) {
            index = 0;
        } else {
            work = index;
            work -= 0x15;
            work <<= 24;
            index = (u32)work >> 24;
            if ((u32)index > 0x3B) {
                index = 0x3B;
            }
        }
        work = 0x086A3398;
        asm volatile("" : "+r"(work));
        work = index + work;
        work = *(u8 *)work;
        return work;
    }

    if ((u32)index <= 0x23) {
        work = 0;
        asm volatile("" : "+r"(work));
        fraction = work;
        index = 0;
    } else {
        work = index;
        work -= 0x24;
        work <<= 24;
        index = (u32)work >> 24;
        if ((u32)index > 0x82) {
            index = 0x82;
            value = 0xFF;
            asm volatile("" : "+r"(value));
            fraction = value;
        }
    }

    table = (u8 *)0x086A32FC;
    work = index + (s32)table;
    code = *(u8 *)work;
    asm volatile("" : "+r"(code));
    curve = (u8 *)0x086A3380;
    asm volatile("" : "+r"(curve));
    mask = 0x0F;
    work = code;
    work &= mask;
    work <<= 1;
    work = work + (s32)curve;
    asm volatile("" : "+r"(work));
    offset = 0;
    value = M2C_FIELD(work, s16 *, offset);
    asm volatile("" : "+r"(value));
    work = code;
    work >>= 4;
    code = value;
    code >>= work;

    work = index + 1;
    work = work + (s32)table;
    value = *(u8 *)work;
    asm volatile("" : "+r"(value));
    work = value;
    work &= mask;
    work <<= 1;
    work = work + (s32)curve;
    asm volatile("" : "+r"(work));
    mask = 0;
    work = M2C_FIELD(work, s16 *, mask);
    value >>= 4;
    work >>= value;
    work -= code;
    {
        register s32 product asm("r7");
        product = fraction;
        product *= work;
        work = product;
        asm volatile("" : "+&r"(work) : "r"(product));
        work >>= 8;
        work = code + work;
        value = 0x80;
        value <<= 4;
        work += value;
        return work;
    }
}
