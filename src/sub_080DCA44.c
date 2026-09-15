#include "m2c_prelude.h"
typedef struct { u8 pad[0x8c]; s32 unk8C; s32 unk90; s32 unk94; } T;

void sub_080DCA44(T *arg0) {
    s32 *p8c = &arg0->unk8C;
    s32 *p90 = &arg0->unk90;
    s32 *p94 = &arg0->unk94;
    *p94 = 0;
    *p90 = 0;
    *p8c = 0;
    *(s16 *)0x03000050 = 0x1010;
}
