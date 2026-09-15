#include "m2c_prelude.h"
extern u8 D_02030664;
extern u16 D_0300004E;
extern u16 D_03000052;
void func_80ED17C();
void func_80A016C();

s32 sub_080A1CD8(u8 arg0) {
    u16 saved4E, saved52;
    D_02030664 = 1;
    saved4E = D_0300004E;
    saved52 = D_03000052;
    D_0300004E = 0xbf;
    D_03000052 = 0x10;
    func_80ED17C(2);
    D_0300004E = saved4E;
    D_03000052 = saved52;
    func_80ED17C(2);
    func_80A016C(arg0, -1, 0);
    return 0;
}
