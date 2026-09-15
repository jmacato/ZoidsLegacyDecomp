#include "m2c_prelude.h"
extern void func_08096308(int, int);
extern int func_0809669C(void);
extern void func_080A016C(int, int, int);
extern void func_080ED17C(int);

s32 sub_080A17B0(u8 arg0, u8 **arg1) {
    *(s8 *)0x02030664 = 1;
    if ((func_0809669C() << 0x18) != 0) {
        func_08096308(4, (*arg1)[1]);
        func_080A016C(arg0, -1, 0);
    } else {
        func_080ED17C(1);
    }
    return 0;
}
