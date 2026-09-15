#include "m2c_prelude.h"
extern void func_08096308(int, int);
extern void func_080ED17C(int);
extern int func_080A016C(int, int, int);

extern u8 D_02030664;
extern u32 D_02021690;

int sub_080A242C(u8 arg0)
{
    D_02030664 = 1;
    D_02021690 = 8;
    func_08096308(16, 0);
    D_02030664 = 2;
    do {
        func_080ED17C(1);
    } while (D_02030664 != 1);
    func_080A016C(arg0, -1, 0);
    return 0;
}
