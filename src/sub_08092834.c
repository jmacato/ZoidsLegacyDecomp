#include "m2c_prelude.h"
extern u16 D_030009EC;
extern u8 D_030009A8[];
extern s32 D_030009E8;
extern u8 D_030032D4[];
extern u8 D_03000998[];

s32 func_8093138(void *);
void func_809324C(void *);
void func_80930D0(void);

void sub_08092834(void) {
    register s32 temp_r0 asm("r1");
    register s32 var_r0 asm("r0");
    s32 *p;

    if (2 & D_030009EC) {
        temp_r0 = func_8093138(D_030009A8);
        p = &D_030009E8;
        *p = temp_r0;
        if (!(0x2000 & temp_r0)) {
            if (D_030032D4[4] == 0) {
                func_809324C(D_03000998);
                var_r0 = *p & 0x7FFFFFFF;
            } else {
                var_r0 = 0x80000000 | temp_r0;
            }
            *p = var_r0;
        }
        func_80930D0();
    }
}
