#include "m2c_prelude.h"
extern void func_80ED128(void *, s32);
extern u8 func_8098B58(void *);
extern void func_8099F5C(void *, void *);
extern void func_8098284(u8, s32, s32, void *);
extern void func_80988C8(u8, void *);
extern u8 D_020322B1;
extern u8 D_020322A8[];
extern s32 D_087EEE10[];
extern u8 D_020217F4[];

void sub_080AC7BC(u8 arg0) {
    u8 i;
    u8 n;
    i = 0;
    while (i < D_020322B1) {
        func_80ED128((void *)0x02030564, D_087EEE10[D_020322A8[i]]);
        n = func_8098B58((void *)0x02030564);
        if (n <= 0xA) {
            do {
                func_8099F5C((void *)0x02030564, (void *)0x081061C4);
                n++;
            } while (n <= 0xA);
        }
        func_8099F5C((void *)0x02030564, (void *)0x081061C8);
        func_8098284(D_020217F4[D_020322A8[i]], 2, 2, (void *)0x020305E4);
        func_8099F5C((void *)0x02030564, (void *)0x020305E4);
        func_80988C8(arg0, (void *)0x02030564);
        i++;
    }
}
