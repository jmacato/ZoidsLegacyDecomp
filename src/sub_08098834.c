#include "m2c_prelude.h"
extern s8 D_0200E6C4[];
extern s8 D_0200DE90[];
M2C_UNK func_80986B4();
void sub_08098834(u8 arg0) {
    u32 m;
    s8 *p2;
    D_0200E6C4[arg0] = 0;
    p2 = D_0200DE90;
    m = 0xD2;
    m *= arg0;
    p2[m] = 0;
    func_80986B4();
}
