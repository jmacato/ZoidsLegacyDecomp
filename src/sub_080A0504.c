#include "m2c_prelude.h"
extern u8 D_0203055C[];
extern void func_0809F850(void);
extern void func_080ED17C();
extern int func_080A016C();

s32 sub_080A0504(u8 arg0, u8 **arg1) {
    *(u8 *)0x02030664 = 2;
    *(u8 *)0x02030666 = 0;
    *(s32 *)0x02031744 = 0;
    func_0809F850();
    D_0203055C[3] = arg1[0][1];
    D_0203055C[4] = arg1[0][2];
    D_0203055C[1] = arg1[0][3];
    D_0203055C[5] = arg1[0][4];
    *(s32 *)0x02030558 = 0;
    *(s32 *)0x02021690 = 9;
    if (*(u8 *)0x02030664 == 2) {
        do {
            func_080ED17C(1);
        } while (*(u8 *)0x02030664 == 2);
    }
    *(s8 *)0x02030667 = 0;
    func_080A016C(arg0, -1, 0);
    return 0;
}
