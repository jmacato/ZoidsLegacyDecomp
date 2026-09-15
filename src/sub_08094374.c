#include "m2c_prelude.h"

struct WindowRecord94374 {
    s32 flags;
    u16 field4;
    u16 field6;
    u16 field8;
    u16 fieldA;
    u16 fieldC;
    u16 fieldE;
    u8 field10;
    u8 field11;
    u16 field12;
    u16 field14;
    u16 field16;
    s32 field18;
    s32 field1C;
    s32 field20;
    s32 field24;
    s32 field28;
    s32 field2C;
    s32 field30;
    s32 field34;
};

extern struct WindowRecord94374 D_03003FE4[];
void func_080ECD28(s32, void *, s32);

struct WindowRecord94374 *sub_08094374(s32 arg0, u16 arg1, u16 arg2,
    u16 arg3, u16 arg4, u16 arg5, u16 arg6, s32 arg7, s32 arg8)
{
    struct WindowRecord94374 *record;
    struct WindowRecord94374 *base;
    struct WindowRecord94374 *loop_base;
    s16 i;

    i = 0x7F;
    base = D_03003FE4;
    record = (struct WindowRecord94374 *)((s32)base + 0x1BC8);
    if (record->flags & 3) {
        loop_base = base;
        do {
            i--;
            if (i < 0) {
                break;
            }
            record = (struct WindowRecord94374 *)(i * 0x38 +
                (s32)loop_base);
        } while (record->flags & 3);
    }
    if (i == -1) {
        return 0;
    }

    record->flags = arg7 | 1;
    record->field4 = arg3;
    record->field6 = arg4;
    record->fieldA = 0;
    record->field8 = 0;
    record->field11 = 0;
    record->fieldC = 0x100;
    record->fieldE = arg5;
    record->field10 = arg6;
    record->field12 = arg2;
    record->field14 = 0;
    record->field16 = 0;

    if ((arg7 & 0x400000) == 0) {
        s32 *source = (s32 *)(arg1 * 8 + arg0);

        record->field18 = source[0];
        record->field1C = source[1];
    } else {
        s32 *source = (s32 *)(arg1 * 16 + arg0);

        record->field18 = source[0];
        record->field1C = source[1];
        record->field20 = source[2];
        func_080ECD28(source[3],
            (void *)(0x05000200 + (record->field10 << 5)), 8);
    }
    record->field24 = arg8;
    return record;
}
