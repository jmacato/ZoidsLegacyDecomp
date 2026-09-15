#include "m2c_prelude.h"
M2C_UNK func_809FB78(u8);
M2C_UNK func_809F850(void);
M2C_UNK func_80A016C(u8, s32, s32);

int sub_080A49FC(u8 arg0) {
    u32 i;
    for (i = 0; i < 16; i++) {
        func_809FB78(i);
    }
    func_809F850();
    func_80A016C(arg0, -1, 0);
    return 0;
}
