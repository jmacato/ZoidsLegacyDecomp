#include "m2c_prelude.h"
extern void func_8096308(int, int);
extern void func_80ED17C(int);
extern int func_80A016C(int, int, int);

int sub_080A2330(u8 arg0, u8 **arg1) {
    u8 *p1 = (u8 *)0x02030664;
    *p1 = 1;
    *(u8 *)0x02032B98 = arg1[0][1];
    *(u32 *)0x02021690 = 5;
    func_8096308(0x10, 0);
    *p1 = 2;
    do {
        func_80ED17C(1);
    } while (*p1 != 1);
    func_80A016C(arg0, -1, 0);
    return 0;
}
