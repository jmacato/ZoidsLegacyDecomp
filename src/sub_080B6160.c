#include "m2c_prelude.h"

s32 sub_080B6160(u8 *arg0, s32 arg1) {
    s32 adjusted;
    s32 initial_stride;
    u8 index;
    register s32 saved asm("r6");
    register u8 *table asm("r5");
    register s32 twice asm("r3");
    register u8 *table_base asm("r2");

    saved = (s32)arg0;
    arg1 <<= 24;
    arg1 = (u32)arg1 >> 24;
    if ((u32)arg1 <= 0xC7) {
        s32 result;

        result = 0;
        saved = *(u8 *)saved;
        if (arg1 == saved) {
            result = 1;
        }
        return result;
    }

    adjusted = arg1;
    adjusted += 0x38;
    arg1 = (u8)adjusted;
    index = 0;
    table_base = (u8 *)0x087A1F8C;
    twice = arg1 << 1;
    initial_stride = (twice + arg1) << 1;
    if (*(u8 *)(initial_stride + (s32)table_base) != 0) {
        s32 loop_stride;

        table = table_base;
        saved = *(u8 *)saved;
        do {
            asm volatile("" : "+r"(twice));
            loop_stride = (twice + arg1) << 1;
            if (saved == *(u8 *)(index + loop_stride + (s32)table)) {
                return 1;
            }
            index += 1;
            if ((u32)index > 5) {
                break;
            }
        } while (*(u8 *)(index + loop_stride + (s32)table) != 0);
    }
    return 0;
}
