#include "m2c_prelude.h"
extern void func_08096308(s32, s32);
extern s32 func_0809669C(void);
extern void func_080A016C(u8, s32, s32);
extern void func_080ED17C(s32);

s32 sub_080A18B4(u8 arg0) {
    *(s8 *)0x02030664 = 1;
    if ((func_0809669C() << 0x18) != 0) {
        func_08096308(8, 0);
        func_080A016C(arg0, -1, 0);
    } else {
        func_080ED17C(1);
    }
    return 0;
}
