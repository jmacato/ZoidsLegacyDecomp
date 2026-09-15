#include "m2c_prelude.h"

extern void func_0809B180(void);
extern void func_0809BB74(void);
extern void func_0809C1D4(void);
extern void func_0809D288(void);
extern void func_0809EC20(void);
extern void func_080A68F0(void);
extern void func_080B571C(void);
extern void func_080B5EA8(void);
extern void func_080B68F8(void);
extern void func_080B7390(void);
extern void func_080BA588(void);
extern void func_080BBA04(void);
extern void func_080CD6D8(void);
extern void func_080CFEE4(void);
extern void func_080E155C(void);
extern void func_080E1F40(void);
extern void func_080E3EA0(void);
extern void func_080E4A44(void);
extern void func_080E5000(void);
extern void func_080E6690(void);
extern void func_080ED17C(s32);

void sub_0809A0B0(void) {
    u32 state;

    func_080E6690();
    *(u8 *)0x02030665 = 0;
    *(u8 *)0x03000075 = 1;
    for (;;) {
        state = *(u32 *)0x02021690;
        switch (state) {
        case 0: func_0809B180(); break;
        case 1: func_0809BB74(); break;
        case 2: func_0809D288(); break;
        case 3: func_0809EC20(); break;
        case 4: func_080B571C(); break;
        case 5: func_080B68F8(); break;
        case 6:
        case 7: func_080B7390(); break;
        case 8: func_080BA588(); break;
        case 9: func_080BBA04(); break;
        case 10: func_080CD6D8(); break;
        case 11: func_080CFEE4(); break;
        case 12: func_080B5EA8(); break;
        case 13: func_080E155C(); break;
        case 14: func_080E1F40(); break;
        case 15: func_080E3EA0(); break;
        case 16: func_080E4A44(); break;
        case 17: func_0809C1D4(); break;
        case 18: func_080A68F0(); break;
        case 19: func_080E5000(); break;
        case (u32)-1: func_080ED17C(1); break;
        }
    }
}
