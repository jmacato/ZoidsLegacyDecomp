#include "m2c_prelude.h"
typedef struct { u8 pad[0x8c]; s32 unk8C; s32 unk90; } T;

void func_080955A0(s32, s32, s32, s32);
void func_080D2790(s32);

void sub_080DBA90(T *arg0) {
    s32 *p8c = &arg0->unk8C;
    s32 *p90 = &arg0->unk90;
    *p90 = 0;
    *p8c = 0;
    *(s16 *)0x03000050 = 0x808;
    func_080955A0(0x02034910, 0x3F3F, 0x1F1F, 8);
    *(s16 *)0x0300004E = 0x2044;
    *(s16 *)0x05000000 = 0x1F;
    func_080D2790(0);
}
