#include "m2c_prelude.h"

s32 func_080E67F0(void);

s32 sub_080E13C4(void) {
    register s32 work asm("r0");
    register s32 outer asm("r1");
    register s32 inner asm("r2");
    register s32 stride asm("r3");
    register u8 *current asm("r4");
    register s32 sum asm("r5");
    register s32 next asm("r6");
    u8 *base;
    register u8 *statuses asm("r8");

    sum = 0;
    outer = 0;
    work = 0x020218E4;
    inner = 0x690C;
    asm volatile("" : "+r"(work), "+r"(inner));
    inner += work;
    statuses = (u8 *)inner;
outer_loop:
    work = (s32)statuses;
    current = (u8 *)(outer + work);
    work = *current;
    next = outer + 1;
    if (work != 0) {
        sum += func_080E67F0();
        inner = 0;
        base = (u8 *)0x020218E4;
        outer = *current;
        work = outer << 3;
        work -= outer;
        stride = work << 4;
        current = (u8 *)0x087A2390;
inner_loop:
        work = inner << 2;
        work += stride;
        work += (s32)base;
        asm volatile("" : "+r"(work));
        outer = work;
        outer += 0x56;
        work = *(u16 *)outer;
        if (work != 0) {
            work <<= 2;
            work += (s32)current;
            work = *(s32 *)work;
            sum += work;
        }
        work = inner + 1;
        work <<= 24;
        inner = (u32)work >> 24;
        if ((u32)inner <= 3) {
            goto inner_loop;
        }
    }
    work = next << 24;
    outer = (u32)work >> 24;
    if ((u32)outer <= 5) {
        goto outer_loop;
    }
    return sum;
}
