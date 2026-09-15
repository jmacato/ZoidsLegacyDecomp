#include "m2c_prelude.h"
extern u8 D_02034B4C[];

void sub_080BFE30(u8 arg0, u8 arg1) {
    s32 type;
    u32 offset;
    u32 row;
    u8 i;
    u8 *loop_base;
    u8 *entry;

    offset = arg0 * 0x1380;
    row = arg1 * 0x270;
    row += (u32)D_02034B4C;
    offset += row;
    i = 0;
    loop_base = (u8 *)offset;
    do {
        entry = &loop_base[i * 0xC + 0xE4];
        type = *(u16 *)&entry[4] & 0x7F;
        if (type != 0xD) {
            if (type == 0xE && !(*(u32 *)entry & 0xFF0000)) {
                *(u16 *)((u8 *)offset + 0xC) += *(u16 *)&entry[6];
            }
        } else {
            *(u16 *)((u8 *)offset + 0xA) += *(u16 *)&entry[6];
        }
        i++;
    } while (i <= 0x1F);
}
