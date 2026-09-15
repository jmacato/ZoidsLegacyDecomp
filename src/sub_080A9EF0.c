#include "m2c_prelude.h"
struct Entry {
    s32 flags;
    u8 unk4;
    u8 id;
    u8 rest[0x42];
};

extern struct Entry D_020325A0[];

u32 sub_080A9EF0(u8 arg0) {
    u8 i = 0;
    if (!(D_020325A0[i].flags & 1) || D_020325A0[i].id != arg0) {
    loop_2:
        i++;
        if ((u32)i <= 0xD) {
            if ((D_020325A0[i].flags & 1) && D_020325A0[i].id == arg0) {
                goto block_5;
            }
            goto loop_2;
        }
        goto block_6;
    }
block_5:
    if ((u32)i > 0xD) {
    block_6:
        return 0xFF;
    }
    return (u32)i;
}
