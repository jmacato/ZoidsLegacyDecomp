#include "m2c_prelude.h"
extern u8 D_02031940[]; extern u8 D_02031840[];
void func_8094554(void);
void sub_0809FB78(u8 arg0) {
    u8 i = arg0;
    s32 *base = (s32 *)D_02031940;
    if (base[i] != 0) {
        func_8094554();
        base[i] = 0;
        D_02031840[arg0 * 0x10] = 0;
    }
}
