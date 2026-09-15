#include "m2c_prelude.h"
void *func_0809716C(u8);                            /* extern */
M2C_UNK func_080971AC(u8);                          /* extern */
M2C_UNK func_08097DA8(void *, M2C_UNK);             /* extern */
M2C_UNK func_08098284(M2C_UNK, u8, u8);             /* extern */

void sub_0809844C(M2C_UNK arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, u16 arg5, u16 arg6) {
    u8 temp_r3;
    void *temp_r0;
    register void *table asm("r10");

    temp_r3 = (u8) arg4;
    table = (void *)0x02021676;
    asm volatile("" : "+r"(table));
    func_08098284(arg0, arg1, arg3);
    temp_r0 = func_0809716C(temp_r3);
    M2C_FIELD(temp_r0, u16 *, 0xC) = (u16) arg5;
    M2C_FIELD(temp_r0, u16 *, 0xE) = (u16) arg6;
    M2C_FIELD(temp_r0, u8 *, 0x12) = arg2;
    func_08097DA8(temp_r0, table);
    M2C_FIELD(temp_r0, s32 *, 0) = (s32) (M2C_FIELD(temp_r0, s32 *, 0) | 2);
    func_080971AC(temp_r3);
}
