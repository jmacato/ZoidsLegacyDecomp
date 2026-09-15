#include "m2c_prelude.h"

extern u8 D_020317D7;
extern u8 D_02033F36;
extern u8 D_020317D6;

void func_080A016C(u8, s32, s32);
s32 func_080D1C18(void);
void func_080D1D44(void);
u8 func_080D1E38(void);
void func_080D2200(void);
s32 func_080D222C(void);
void func_080D0D50(u8, u8, u16, s32);
void func_080D0F08(u8, u8, u16, s32);
void func_080ED17C(s32);

s32 sub_080A37E8(u8 arg0, u8 **arg1)
{
    if (func_080D1E38() == 1) {
        func_080D1D44();
        while ((u32)func_080D1E38() <= 1U) {
            func_080ED17C(1);
        }
    }
    if ((func_080D222C() << 24) == 0) {
        func_080D2200();
        while ((func_080D222C() << 24) == 0) {
            func_080ED17C(1);
        }
    }
    if ((D_020317D7 & 1) == 0) {
        u8 *input;
        s32 high;

        func_080D0D50(D_02033F36, D_020317D6,
            (input = *arg1, high = input[2] << 8, input[1] | high), 0);
    } else {
        u8 *input;
        s32 high;

        func_080D0F08(D_02033F36, D_020317D6,
            (input = *arg1, high = input[2] << 8, input[1] | high), 0);
    }
    while ((func_080D1C18() << 24) == 0) {
        func_080ED17C(1);
    }
    func_080A016C(arg0, -1, 0);
    return 0;
}
