#include "m2c_prelude.h"
void sub_080DDDD0(int arg0) {
    int v;
    *(int *)(arg0 + 0x8c) = 0;
    v = *(int *)(arg0 + 0xa8) & ~0xc0;
    if (v == 0)
        *(int *)(arg0 + 0x90) = v;
    else
        *(int *)(arg0 + 0x90) = 1;
    *(int *)(arg0 + 0xa8) = *(int *)(arg0 + 0xa8) & 0xc0;
}
