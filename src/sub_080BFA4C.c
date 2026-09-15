#include "m2c_prelude.h"

M2C_UNK func_080BF514(u8, u8, u8);
M2C_UNK func_080E8B08(u8, u8);
s32 func_080E9D88(u8, u8);
extern u8 D_02034B4C;

struct E { u8 pad[4]; u16 field; u8 rest[6]; };
struct I { u8 hdr[0xE4]; struct E e[32]; u8 rest[12]; };
struct M { struct I i[8]; };

void sub_080BFA4C(s32 arg0, s32 arg1) {
    u8 var_r4;
    u8 temp_r5;
    u8 temp_r6;
    struct E *temp_r3;

    arg0 = arg0 << 24;
    temp_r6 = (u32)arg0 >> 24;
    arg1 = arg1 << 24;
    temp_r5 = (u32)arg1 >> 24;
    if ((func_080E9D88(temp_r6, temp_r5) << 24) != 0) {
        var_r4 = 0;
        do {
            temp_r3 = &((struct M *)&D_02034B4C)[temp_r6].i[temp_r5].e[var_r4];
            if (temp_r3->field != 0 &&
                (0xE000 & temp_r3->field) == 0x8000) {
                func_080BF514(temp_r6, temp_r5, var_r4);
            }
            var_r4 += 1;
        } while ((u32)var_r4 <= 0x1F);
        func_080E8B08(temp_r6, temp_r5);
    }
}
