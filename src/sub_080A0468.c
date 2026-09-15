#include "m2c_prelude.h"
extern void func_0809F850(void);
extern void func_080A016C(u8, s32, s32);
extern void func_080ED17C(s32);
extern u8 D_02030664;
extern s32 D_02021690;
extern u8 D_02030666;
extern s32 D_02031744;
extern u8 D_0203055C[];
extern u8 D_02031748;
extern u8 D_020317D8;
extern u8 D_020317D9;
extern u8 D_02033F34;

s32 sub_080A0468(u8 arg0, u8 **arg1) {
    s32 *p690;
    u8 *p666;
    s32 *p744;
    int zero;
    D_02030664 = 1;
    p690 = &D_02021690;
    if (*p690 != 0xA) {
        p666 = &D_02030666;
        *p666 = 0;
        p744 = &D_02031744;
        zero = 0;
        *p744 = zero;
        func_0809F850();
        D_0203055C[2] = (*arg1)[1];
        D_02031748 = (*arg1)[2];
        D_020317D8 = zero;
        D_020317D9 = zero;
        *p690 = 0xA;
        D_02033F34 = zero;
        func_080ED17C(1);
        *p666 = zero;
        *p744 = zero;
    }
    func_080A016C(arg0, -1, 0);
    return 0;
}
