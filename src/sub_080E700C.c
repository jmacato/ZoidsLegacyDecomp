#include "m2c_prelude.h"

void func_080E5880(void *, s32);

void sub_080E700C(s32 arg0) {
    register s32 base asm("r2");
    u8 *record;
    u8 id;

    record = (u8 *)(((u32)(arg0 << 0x18) >> 0x12) + ({
        asm volatile("ldr %0, [pc, #60]" : "=r"(base));
        base;
    }));
    id = record[1];
    if (id != 0) {
        u8 captured_id;
        u8 *entry;
        register s32 offset asm("r4");
        s32 product;
        register s32 entry_base asm("r1");

        captured_id = id;
        asm volatile("" : "+&r"(captured_id) : "r"(id));
        product = captured_id * 0x70;
        asm volatile("ldr %0, [pc, #44]" : "=r"(offset));
        entry_base = base + offset;
        entry = (u8 *)(product + entry_base);
        if (*(u16 *)(entry + 4) & 4) {
            register u16 mask asm("r0");
            u16 value;

            value = *(u16 *)(record + 2);
            asm volatile("ldr %0, [pc, #32]" : "=r"(mask));
            mask &= value;
            *(u16 *)(record + 2) = mask;
        }
        record[1] = 0;
        entry[2] = 0;
        func_080E5880(entry, 0);
    }
}

asm(".align 2, 0\n"
    ".word 0x02027378\n"
    ".word 0xFFFFA570\n"
    ".word 0x0000FFFB\n");
