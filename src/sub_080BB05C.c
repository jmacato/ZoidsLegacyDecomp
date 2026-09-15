#include "m2c_prelude.h"
extern void *D_02032E8C[][6];
extern void *D_02032EBC[][6];
extern s8 D_02032EEC[][6];
void sub_080BB05C(u8 arg0, u8 arg1) {
    void *p1 = D_02032E8C[arg0][arg1];
    void *p2;
    *(s32 *)((char*)p1 + 0x24) = 0;
    *(s32 *)p1 |= 0x20000;
    p2 = D_02032EBC[arg0][arg1];
    *(s32 *)((char*)p2 + 0x24) = 0;
    *(s32 *)p2 |= 0x20000;
    D_02032EEC[arg0][arg1] = 0;
}
