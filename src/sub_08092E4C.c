#include "m2c_prelude.h"
M2C_UNK func_080EB944(s32);
extern u8 D_086A46C4[];
extern s32 D_086A4694[];

void sub_08092E4C(s32 arg0) {
    s32 *table;
    u8 *entries;
    arg0 <<= 16;
    table = D_086A4694;
    entries = D_086A46C4;
    func_080EB944(table[*(u16 *)(entries + ((u32)arg0 >> 13) + 4) * 3]);
}
