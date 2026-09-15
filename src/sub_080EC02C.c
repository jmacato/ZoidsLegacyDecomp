#include "m2c_prelude.h"

void sub_080EC02C(s32 arg0, void *arg1) {
    register void *base asm("r2");
    register s32 work asm("r0");
    register s32 value asm("r1");
    register s32 retained asm("r3");
    register s32 mode asm("r4");

    base = arg1;
    work = 1;
    value = M2C_FIELD(base, u8 *, 0);
    work &= value;
    if (work != 0) {
        retained = M2C_FIELD(base, u8 *, 0x13);
        asm volatile("" : "+r"(retained));
        value = M2C_FIELD(base, u8 *, 0x12);
        work = retained;
        work *= value;
        retained = (u32)work >> 5;
        mode = M2C_FIELD(base, u8 *, 0x18);
        if (mode == 1) {
            work = 0x16;
            work = M2C_FIELD(base, s8 *, work);
            work += 0x80;
            work *= retained;
            retained = (u32)work >> 7;
        }

        work = 0x14;
        work = M2C_FIELD(base, s8 *, work);
        work <<= 1;
        value = 0x15;
        value = M2C_FIELD(base, s8 *, value);
        value = work + value;
        if (mode == 2) {
            work = 0x16;
            work = M2C_FIELD(base, s8 *, work);
            value += work;
        }
        work = 0x80;
        work = -work;
        if (value < work) {
            value = work;
        } else if (value > 0x7F) {
            value = 0x7F;
        }

        work = value;
        work += 0x80;
        work *= retained;
        work = (u32)work >> 8;
        M2C_FIELD(base, u8 *, 0x10) = work;
        work = 0x7F;
        work -= value;
        work *= retained;
        work = (u32)work >> 8;
        M2C_FIELD(base, u8 *, 0x11) = work;
    }

    value = M2C_FIELD(base, u8 *, 0);
    work = 4;
    work &= value;
    retained = value;
    if (work != 0) {
        work = 0x0E;
        work = M2C_FIELD(base, s8 *, work);
        value = M2C_FIELD(base, u8 *, 0x0F);
        work *= value;
        value = 0x0C;
        value = M2C_FIELD(base, s8 *, value);
        value += work;
        value <<= 2;
        work = 0x0A;
        work = M2C_FIELD(base, s8 *, work);
        work <<= 8;
        value += work;
        work = 0x0B;
        work = M2C_FIELD(base, s8 *, work);
        work <<= 8;
        value += work;
        work = M2C_FIELD(base, u8 *, 0x0D);
        value = work + value;
        work = M2C_FIELD(base, u8 *, 0x18);
        if (work == 0) {
            work = 0x16;
            work = M2C_FIELD(base, s8 *, work);
            work <<= 4;
            value += work;
        }
        work = value >> 8;
        M2C_FIELD(base, u8 *, 8) = work;
        M2C_FIELD(base, u8 *, 9) = value;
    }

    work = 0xFA;
    work &= retained;
    M2C_FIELD(base, u8 *, 0) = work;
}
