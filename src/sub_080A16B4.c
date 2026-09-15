#include "m2c_prelude.h"
extern u32 D_02031744;
extern void func_8094554(u32);
extern int func_80A016C(u8, int, int);

int sub_080A16B4(u8 arg) {
    if (D_02031744 != 0) {
        func_8094554(D_02031744);
        D_02031744 = 0;
    }
    func_80A016C(arg, -1, 0);
    return 0;
}
