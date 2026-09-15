#include "m2c_prelude.h"
extern u16 D_030009EC;
extern s32 D_030009E8;
extern u8 D_0300067C;
extern u16 D_0300004C;
extern void func_0809334C(void);
extern s32 func_080ECD2C(s32, s32, s32);
extern volatile s32 D_040000D4[];
void sub_080922A4(void) {
    if (2 & D_030009EC) {
        if (D_030009E8 & 0x80) {
            func_0809334C();
        }
        if (1 & D_0300067C) {
            if (0x1000 & D_0300004C) {
                func_080ECD2C(0x0300027C, 0x07000000, 0x04000100);
            }
        }
    } else {
        if (1 & D_0300067C) {
            if (0x1000 & D_0300004C) {
                D_040000D4[0] = 0x0300027C;
                D_040000D4[1] = 0x07000000;
                D_040000D4[2] = 0x84000100;
                D_040000D4[2];
            }
        }
    }
}
