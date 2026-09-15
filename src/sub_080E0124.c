#include "m2c_prelude.h"
typedef struct { u8 pad[0x8c]; s32 unk8C; s32 unk90; } T;

void sub_080E0124(T *arg0) {
    s32 *p8c = &arg0->unk8C;
    s32 *p90 = &arg0->unk90;
    *p90 = 0;
    *p8c = 0;
}
