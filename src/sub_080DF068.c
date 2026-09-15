#include "m2c_prelude.h"
void sub_080DF068(int arg0) {
    s32 *p8c = (s32 *)(arg0 + 0x8C);
    s32 *p90 = (s32 *)(arg0 + 0x90);
    s32 *p94 = (s32 *)(arg0 + 0x94);
    *p94 = 0;
    *p90 = 0;
    *p8c = 0;
    *(s16 *)0x03000050 = 0x1010;
}
