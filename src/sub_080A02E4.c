#include "m2c_prelude.h"
extern u32 D_02021690;
extern u8 D_02030664;
extern u16 D_0202ECF4;
extern u8 D_020316F5;
extern u32 D_087A0BF8[];

extern void func_080A0114(void);
extern void func_0809FCB0(void);
extern void func_0809FD3C(int, int);

int sub_080A02E4(int arg0, int *arg1) {
    if (D_02021690 == 3) {
        func_080A0114();
        *arg1 = 0;
        D_02030664 = 0;
        if (D_0202ECF4 != D_020316F5) {
            func_0809FCB0();
            func_0809FD3C(D_0202ECF4, D_087A0BF8[D_0202ECF4]);
        }
    }
    return 1;
}
