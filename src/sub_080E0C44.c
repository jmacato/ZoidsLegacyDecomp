#include "m2c_prelude.h"
void func_8094564();

void sub_080E0C44(s32 *arg0) {
    s32 *pstate = (s32 *)((u8 *)arg0 + 0x8c);
    s32 state = *pstate;
    s32 result;
    if (state == 1) {
        func_8094564((s32 *)arg0[3], *(u16 *)((u8 *)arg0 + 0x90));
        func_8094564((s32 *)arg0[4], *(u16 *)((u8 *)arg0 + 0x90));
        *(s32 *)arg0[3] &= ~8;
        *(s32 *)arg0[4] &= ~8;
        result = 2;
    } else {
        if (state != 2) {
            return;
        }
        if ((*(s32 *)arg0[3] & 4) == 0) {
            return;
        }
        if ((*(s32 *)arg0[4] & 4) == 0) {
            return;
        }
        result = 0xff;
    }
    *pstate = result;
}
