#include "m2c_prelude.h"
extern u16 D_087A1194[];
extern u16 D_087A11B6[];

extern void func_08092E84(s32);
extern void func_080940C0(void);
extern void func_080940D4(void);
extern void func_080E5DC4(s32);
extern void func_080E5E0C(s32, s32);
extern void func_080ED17C(s32);

void sub_0809BAB0(void) {
    u8 var_r4;
    u8 var_r5;
    u16 temp_r2;

    if (*(u8 *)0x02021770 != 0) {
        var_r5 = 0;
        var_r4 = 0;
        do {
            temp_r2 = *(u16 *)0x0300000E;
            if (temp_r2 != 0) {
                if (temp_r2 == D_087A1194[var_r4]) {
                    var_r4 += 1;
                    if (var_r4 == 0x11) {
                        func_080E5DC4(6);
                        func_080E5DC4(0x85);
                        func_080E5DC4(0x86);
                        func_080E5E0C(3, 1);
                        func_080E5E0C(5, 1);
                        func_080940D4();
                        func_080940C0();
                        func_08092E84(0x49);
                        var_r4 = 0;
                    }
                } else {
                    var_r4 = 0;
                }
                if (*(u16 *)0x0300000E == D_087A11B6[var_r5]) {
                    var_r5 += 1;
                    if (var_r5 == 0x11) {
                        func_080E5DC4(0x75);
                        func_080E5DC4(0x92);
                        func_080E5E0C(0xD, 1);
                        func_080E5E0C(0x11, 1);
                        func_080940D4();
                        func_080940C0();
                        func_08092E84(0x4E);
                        var_r5 = 0;
                    }
                } else {
                    var_r5 = 0;
                }
            }
            func_080ED17C(1);
        } while (1);
    }
}
