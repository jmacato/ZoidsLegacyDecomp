#include "m2c_prelude.h"
extern u8 D_020217F4[];
struct S { u8 pad[10]; u8 arr[1]; };
s32 sub_080E5E38(u8 arg0, u8 arg1) {
    struct S *s = (struct S *)D_020217F4;
    u8 v = s->arr[arg0];
    if (v > arg1) { v -= arg1; s->arr[arg0] = v; return 1; }
    s->arr[arg0] = 0;
    return 0;
}
