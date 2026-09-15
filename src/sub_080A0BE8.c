#include "m2c_prelude.h"
extern void func_080972C8(void);
extern void func_08098BB4(s32);
extern void func_080A016C(u8, s32, s32);
extern void func_080ED17C(s32);

s32 sub_080A0BE8(u8 arg0) {
    *(s8 *)0x02030664 = 1;
    if (*(u8 *)0x020324B0 & 4) {
        *(s8 *)0x020314A4 = 0x27;
    }
    func_08098BB4(0x080177FF);
    func_080972C8();
    if (*(u8 *)0x020324B0 & 4) {
        *(s8 *)0x020314A4 = 0x5F;
    }
    func_080ED17C(1);
    if (*(u8 *)0x0200A882 == 1 && *(u8 *)0x0200A880 == 0) {
        func_080A016C(arg0, 0xF, 0);
    } else {
        func_080A016C(arg0, 0x10, 0);
    }
    return 0;
}
