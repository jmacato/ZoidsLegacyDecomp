#include "m2c_prelude.h"

extern u8 D_020218E4[];
extern u8 D_off_00005A96[];

s32 func_080E5A18(u8, u8);
s32 func_080E6C78(u8);
void func_080E6FA0(s32, s32);

u8 sub_080E6EEC(u8 arg0, u8 arg1, u8 arg2) {
    register s32 item asm("r6");
    s32 slot;
    s32 raw;
    u32 valid;
    s32 xor_value;
    s32 sign_value;
    register u16 *record asm("r0");
    register u8 *base asm("r3");
    u16 value;
    u16 mask;
    u8 ret;

    raw = func_080E5A18(arg0, arg1);
    raw <<= 24;
    item = (u32)raw >> 24;
    xor_value = 0xFF;
    xor_value ^= item;
    sign_value = -xor_value;
    sign_value |= xor_value;
    valid = (u32)sign_value >> 31;
    raw = func_080E6C78(arg2);
    slot = (u32)(raw << 24) >> 24;
    if (slot == 0xFF) {
        valid = 0;
    }
    if (valid == 0) {
        ret = 0;
        goto done;
    }

    {
        register s32 slot_r0 asm("r0");
        slot_r0 = slot;
        asm volatile("" : "+r"(slot_r0));
        func_080E6FA0(slot_r0, item);
    }
    base = D_020218E4;
    asm volatile("" : "+r"(base));
    record = (u16 *)(item * 0x70);
    record = (u16 *)((u8 *)record + (s32)base);
    record[5] = record[0x1F];
    record[6] = record[0x21];
    value = record[4];
    mask = 2;
    value |= mask;
    record[4] = value;

    {
        register u16 *flags asm("r0");
        register s32 offset asm("r1");
        flags = (u16 *)(slot << 6);
        flags = (u16 *)((u8 *)flags + (s32)base);
        asm volatile("" : "+r"(flags));
        asm volatile("" :: "r"(slot));
        offset = (s32)D_off_00005A96;
        asm volatile("" : "+r"(offset));
        flags = (u16 *)((u8 *)flags + offset);
        mask |= *flags;
        *flags = mask;
    }
    ret = item;

done:
    return ret;
}
