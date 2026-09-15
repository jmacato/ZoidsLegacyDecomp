#include "m2c_prelude.h"
void func_08096308(s32, s32);
s32 func_0809669C(void);
void func_080A016C(s32, s32, s32);
void func_080ED17C(s32);

s32 sub_080A1934(u8 arg0) {
    *(s8 *)0x02030664 = 1;
    if ((func_0809669C() << 0x18) != 0) {
        func_08096308(10, 0);
        func_080A016C(arg0, -1, 0);
    } else {
        func_080ED17C(1);
    }
    return 0;
}

s32 sub_080A1974(u8 arg0) {
    *(s8 *)0x02030664 = 1;
    if ((func_0809669C() << 0x18) != 0) {
        func_08096308(11, 0);
        func_080A016C(arg0, -1, 0);
    } else {
        func_080ED17C(1);
    }
    return 0;
}

s32 sub_080A19B4(u8 arg0) {
    *(s8 *)0x02030664 = 1;
    if ((func_0809669C() << 0x18) != 0) {
        func_08096308(12, 0);
        func_080A016C(arg0, -1, 0);
    } else {
        func_080ED17C(1);
    }
    return 0;
}
