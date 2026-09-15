#include "m2c_prelude.h"
extern u32 D_02032590;
extern u32 D_02032594;
extern u32 D_02032598;
extern u8 D_0203259C;
extern u8 D_0203259D;
void func_809DFFC(void);
void func_80ED17C(int);

void sub_0809E1CC(void) {
    D_02032590 = D_02032594 = D_02032598 = 0;
    D_0203259C = D_0203259D = 0;
    for (;;) {
        func_809DFFC();
        func_80ED17C(1);
    }
}
