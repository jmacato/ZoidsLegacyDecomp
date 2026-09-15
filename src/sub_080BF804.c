#include "m2c_prelude.h"
extern u8 D_02034B4C;

struct Wave2E { u8 pad[4]; u16 field; u8 rest[6]; };
struct Wave2I { u8 pad[0xE4]; struct Wave2E e[32]; u8 rest[12]; };
struct Wave2M { struct Wave2I i[8]; };

void sub_080BF804(u8 arg0, u8 arg1) {
    u8 var_r4;
    struct Wave2E *temp_r3;

    var_r4 = 0;
    do {
        temp_r3 = &((struct Wave2M *)&D_02034B4C)[arg0].i[arg1].e[var_r4];
        if (0x17 & temp_r3->field) {
            temp_r3->field = 0;
        }
        var_r4 += 1;
    } while ((u32)var_r4 <= 0x1FU);
}
