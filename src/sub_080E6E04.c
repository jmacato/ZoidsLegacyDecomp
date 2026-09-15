#include "m2c_prelude.h"

void func_080E77FC(void *);

void sub_080E6E04(s32 arg0, void *arg1) {
    register s32 work asm("r0");
    register s32 scalar asm("r1");
    register s32 record asm("r2");
    register s32 source asm("r3");
    register s32 clear asm("r4");
    register s32 index asm("r5");
    register s32 zero asm("r6");
    void *owner;

    owner = arg1;
    arg0 <<= 24;
    index = (u32)arg0 >> 24;
    work = 0x34;
    scalar = index;
    scalar *= work;
    work = 0x020280B8;
    record = scalar + work;
    work = index << 1;
    work += index;
    work <<= 2;
    scalar = 0x087B7774;
    source = work + scalar;

    work = 0;
    M2C_FIELD(record, u8 *, 0) = index;
    M2C_FIELD(record, u8 *, 1) = work;
    scalar = 0;
    clear = record + 2;
    zero = 0;
clear_loop:
    work = clear + scalar;
    M2C_FIELD(work, u8 *, 0) = zero;
    work = scalar + 1;
    work <<= 24;
    scalar = (u32)work >> 24;
    if ((u32)scalar <= 3) {
        goto clear_loop;
    }

    scalar = M2C_FIELD(source, u8 *, 0);
    work = record;
    work += 0x28;
    M2C_FIELD(work, u8 *, 0) = scalar;
    work = M2C_FIELD(source, u16 *, 2);
    M2C_FIELD(record, u16 *, 0x2A) = work;
    work = M2C_FIELD(source, u16 *, 4);
    M2C_FIELD(record, u16 *, 0x2C) = work;
    work = M2C_FIELD(source, u16 *, 6);
    M2C_FIELD(record, u16 *, 0x2E) = work;
    work = M2C_FIELD(source, u16 *, 8);
    M2C_FIELD(record, u16 *, 0x30) = work;
    work = M2C_FIELD(source, u16 *, 0x0A);
    M2C_FIELD(record, u16 *, 0x32) = work;
    work = (s32)owner;
    work += 0x31;
    M2C_FIELD(work, u8 *, 0) = index;
    work = record;
    func_080E77FC((void *)work);

    scalar = 0x020217B4;
    asm volatile("" : "+r"(scalar));
    record = 0x087AF5F8;
    asm volatile("" : "+r"(record));
    work = index;
    work <<= 1;
    work += record;
    source = M2C_FIELD(work, u16 *, 0);
    record = (u32)source >> 5;
    record <<= 2;
    scalar += 0x14;
    record += scalar;
    work = 0x1F;
    source &= work;
    scalar = 1;
    scalar <<= source;
    work = M2C_FIELD(record, s32 *, 0);
    work |= scalar;
    M2C_FIELD(record, s32 *, 0) = work;
}
