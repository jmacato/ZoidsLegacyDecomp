#include "m2c_prelude.h"

extern u8 D_03000A84[];

void func_08092D8C(s32, s32);

void sub_08092D20(void) {
    s32 index;
    register s32 callback asm("r8");
    u8 *base;
    register s32 stride asm("r12");
    s32 one;
    s32 minus_one;
    s32 *field8;
    s32 *field4;

    index = 0;
    callback = 0x08092D81;
    asm volatile("" : "+r"(callback));
    base = D_03000A84;
    stride = 0x4C;
    one = 1;
    minus_one = -1;
    field8 = (s32 *)(base + 8);
    field4 = (s32 *)(base + 4);
    do {
        register s32 offset asm("r1");
        u8 *record;

        offset = stride * index;
        asm volatile("" : "+r"(offset));
        record = (u8 *)(offset + (s32)base);
        index++;
        record[0] = (u8)index;
        record[1] = one;
        *(s32 *)(offset + (s32)field4) = minus_one;
        *(s32 *)(offset + (s32)field8) = minus_one;
        asm volatile(
            "lsl %0, %0, #24\n\t"
            "lsr %0, %0, #24"
            : "+r"(index));
    } while ((u32)index <= 0xBU);
    func_08092D8C(0, callback);
    *(s32 *)0x03000E64 = (s32)D_03000A84;
}
