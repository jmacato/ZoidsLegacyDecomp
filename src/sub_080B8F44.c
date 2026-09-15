#include "m2c_prelude.h"
M2C_UNK func_80981F0(M2C_UNK, s32, s32, s32, u32);
M2C_UNK func_8098248(M2C_UNK, s32, s32);
M2C_UNK func_809844C(u8, s32, s32, s32, s32, s32, u32);
M2C_UNK func_80984C4(s16, s32, s32, s32, s32);
M2C_UNK func_80986B4(s32);
s32 func_80E523C(u8);
M2C_UNK func_80E59BC(u8 *, M2C_UNK, s32, u8, void *);
void *func_80E669C();
M2C_UNK func_80E66B8();

void sub_080B8F44(u8 *arg0, M2C_UNK arg1) {
    u8 var_r5;
    int temp_r3;
    int off;
    void *temp_r6;

    temp_r6 = func_80E669C();
    func_80986B4(6);
    var_r5 = 0;
    do {
        temp_r3 = var_r5 + 4;
        off = temp_r3 * 4;
        if (*(u16 *)(arg0 + off + 0x52) != 0) {
            func_80E59BC(arg0, arg1, 0, temp_r3, temp_r6);
            if (!(1 & *(u16 *)((u8 *)temp_r6 + 2))) {
                u8 *base;
                u32 idx;
                func_80981F0(0x08106ED4, 0, 6, 0, var_r5);
                func_80984C4(*(s16 *)((u8 *)temp_r6 + 0xA), 4, 0, 0xA, 6);
                idx = var_r5 + ((u32)(func_80E523C(*arg0) << 0x18) >> 0x16);
                base = arg0 + 0x1E;
                func_809844C(base[idx], 1, 0, 0xA, 6, 9, var_r5);
                func_8098248(0x08106ED8, 0, 6);
            }
        }
        var_r5 = var_r5 + 1;
    } while (var_r5 <= 3);
    func_80E66B8();
}

void sub_080B8FF8(u8 *arg0, M2C_UNK arg1) {
    u8 var_r4;
    int temp_r3;
    int off;
    void *temp_r5;

    temp_r5 = func_80E669C();
    func_80986B4(6);
    var_r4 = 0;
    do {
        temp_r3 = var_r4 + 4;
        off = temp_r3 * 4;
        if (*(u16 *)(arg0 + off + 0x52) != 0) {
            func_80E59BC(arg0, arg1, 0, temp_r3, temp_r5);
            if (!(1 & *(u16 *)((u8 *)temp_r5 + 2))) {
                func_80981F0(0x08106EDC, 0, 6, 0, var_r4);
                func_80984C4(*(s16 *)((u8 *)temp_r5 + 0xC), 3, 0, 0xA, 6);
                func_8098248(0x08106EE0, 0, 6);
            }
        }
        var_r4 = var_r4 + 1;
    } while (var_r4 <= 3);
    func_80E66B8();
}
