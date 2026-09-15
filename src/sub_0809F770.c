#include "m2c_prelude.h"
s32 sub_0809F770(u8 *arg0, u8 *arg1) {
    u8 temp_r1;
    arg0[0] = 0x82;
    arg0[1] = 0x81;
    if (arg1[0] == 0x82) {
        temp_r1 = arg1[1];
        if (temp_r1 == 0x60 || temp_r1 == 0x64 || temp_r1 == 0x68 || temp_r1 == 0x6E ||
            temp_r1 == 0x74 || temp_r1 == 0x81 || temp_r1 == 0x85 || temp_r1 == 0x89 ||
            temp_r1 == 0x8F || temp_r1 == 0x95) {
            arg0[2] = 0x82;
            arg0[3] = 0x8E;
            arg0[4] = 0;
            return 2;
        }
    }
    arg0[2] = 0;
    return 1;
}
