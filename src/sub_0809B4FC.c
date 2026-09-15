#include "m2c_prelude.h"
extern s32 D_03000054[];
extern void func_80ED17C(int);

void sub_0809B4FC(void) {
    for (;;) {
        if (D_03000054[1] <= 0x6FFF) {
            D_03000054[1] += 0x80;
        }
        func_80ED17C(1);
    }
}
