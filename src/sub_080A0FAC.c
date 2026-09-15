#include "m2c_prelude.h"
typedef struct { u8 u0; u8 u1; } E;

s32 func_080E60B0(u8);
void func_080E65B4(u8);
void func_080E6684(void);
void func_080A016C(s32, s32, s32);

s32 sub_080A0FAC(u8 arg0, E **arg1) {
    u8 temp_r5;

    temp_r5 = arg0;
    if ((func_080E60B0((*arg1)->u1) << 0x18) != 0) {
        func_080E65B4((*arg1)->u1);
        func_080A016C(temp_r5, 0xF, 0);
    } else {
        func_080E6684();
        func_080A016C(temp_r5, 0x10, 0);
    }
    return 0;
}
