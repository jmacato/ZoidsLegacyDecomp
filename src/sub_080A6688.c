#include "m2c_prelude.h"
extern void func_80ED17C();
extern void func_80A016C();

int sub_080A6688(u8 arg0) {
    *(u8 *)0x02030664 = 1;
    *(s32 *)0x02021690 = 19;
    do {
        func_80ED17C(1);
    } while (*(s32 *)0x02021690 != -1);
    func_80A016C(arg0, -1, 0);
    return 0;
}
