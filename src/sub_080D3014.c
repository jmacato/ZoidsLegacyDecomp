#include "m2c_prelude.h"
M2C_UNK func_08095114(void *);
void *func_080D2450(void *, s32, s32, s16, s32, s32, s32, s32);
M2C_UNK func_080D2790(s32);
void sub_080D3014(void *arg0) {
    s32 r1 = M2C_FIELD(arg0, s32 *, 0x8C);
    if (r1 == 0) {
        void *p = func_080D2450(arg0, 0, 0, (s16)(M2C_FIELD(arg0, s32 *, 4) - 0x10), M2C_FIELD(arg0, s16 *, 0x90), r1, 0x080D2529, 1);
        M2C_FIELD(arg0, void **, 0xC) = p;
        M2C_FIELD(p, s32 *, 0x28) = 0x10;
        func_080D2790(0);
        M2C_FIELD(arg0, s32 *, 0x8C)++;
        return;
    }
    if (M2C_FIELD(arg0, void **, 0xC) == 0) func_08095114(arg0);
}
