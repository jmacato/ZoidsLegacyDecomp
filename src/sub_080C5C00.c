#include "m2c_prelude.h"

extern void func_080BE9D8(u8, u8, s32, s32, s32, s32, s32, s32, s32, s32);
extern void func_080E66C8(u8, void *, u8, u8);

void sub_080C5C00(s32 arg0, s32 arg1, s32 arg2) {
    s32 row_offset;
    s32 col_offset;
    u32 temp_r0;
    u8 temp_r4;
    u8 temp_r5;
    u8 temp_r7;
    void *temp_r6;

    arg0 <<= 24;
    temp_r7 = (u32)arg0 >> 24;
    arg1 <<= 24;
    temp_r5 = (u32)arg1 >> 24;
    arg2 <<= 24;
    temp_r4 = (u32)arg2 >> 24;
    row_offset = temp_r5 * 0x1380;
    col_offset = temp_r4 * 0x270;
    col_offset += 0x02034B4C;
    temp_r6 = (void *)(row_offset + col_offset);
    temp_r0 = temp_r7 - 1;
    switch (temp_r0) {
    case 0:
        func_080BE9D8(temp_r5, temp_r4, -1, 0, 0, 0, 1, 0x12C, 0, 0);
        break;
    case 1:
        func_080BE9D8(temp_r5, temp_r4, -1, 0, 0, 0, 1, 0x96, 0, 0);
        break;
    case 2:
        func_080BE9D8(temp_r5, temp_r4, -1, 0, 0, 0, 1, 0x32, 0, 0);
        break;
    case 3:
        func_080BE9D8(temp_r5, temp_r4, -1, 0, 0, 0, 1,
            ({ s32 value = M2C_FIELD(temp_r6, s16 *, 0x3A);
               (s32)(value + ((u32)value >> 31)) >> 1; }), 0, 0);
        break;
    case 6:
        func_080BE9D8(temp_r5, temp_r4, -1, 0, 0, 0, 1,
            (s32) (s16) ((u16) M2C_FIELD(temp_r6, s16 *, 0x3A) - M2C_FIELD(temp_r6, u16 *, 6)), 0, 0);
        break;
    case 8:
        break;
    }
    func_080E66C8(temp_r7, temp_r6, temp_r5, temp_r4);
}
