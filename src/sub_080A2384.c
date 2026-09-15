#include "m2c_prelude.h"
extern void func_08096308(s32, s32);
extern void func_080A016C(s32, s32, s32);
extern void func_080ED17C(s32);

s32 sub_080A2384(u8 arg0, u8 **arg1) {
    u8 *p = (u8 *)0x02030664;
    *p = 1;
    *(u8 *)0x02032B98 = (*arg1)[1];
    *(s32 *)0x02021690 = 6;
    func_08096308(0x10, 0);
    *p = 2;
    do {
        func_080ED17C(1);
    } while (*p != 1);
    func_080A016C(arg0, -1, 0);
    return 0;
}

s32 sub_080A23D8(u8 arg0, u8 **arg1) {
    u8 *p = (u8 *)0x02030664;
    *p = 1;
    *(u8 *)0x02032B98 = (*arg1)[1];
    *(s32 *)0x02021690 = 7;
    func_08096308(0x10, 0);
    *p = 2;
    do {
        func_080ED17C(1);
    } while (*p != 1);
    func_080A016C(arg0, -1, 0);
    return 0;
}
