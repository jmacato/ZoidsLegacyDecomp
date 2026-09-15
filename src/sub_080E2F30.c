#include "m2c_prelude.h"
extern s32 D_02032E68[];
M2C_UNK func_8094554(s32);
M2C_UNK func_80D12DC(void);
M2C_UNK func_80ED17C(s32);

void sub_080E2F30(void) {
    func_8094554(D_02032E68[0]);
    func_8094554(D_02032E68[1]);
}

void sub_080E2F4C(void) {
loop_1:
    func_80D12DC();
    func_80ED17C(1);
    goto loop_1;
}

void sub_080E2F5C(void) {
    *(u16 *)0x04000000 |= 0x800;
}
