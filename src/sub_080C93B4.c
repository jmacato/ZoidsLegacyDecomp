#include "m2c_prelude.h"
extern void func_08098284(s32, s32, s32, s32);
extern void func_08099F5C(s32, s32);
extern void func_080C8F48(s32, void *, s32);
extern void func_080ED038(s32, s32, s32);

void sub_080C93B4(void *arg0) {
    func_080ED038(0x02030564, 0x08108134, 3);
    func_08098284(*(s32 *)((u8 *)arg0 + 0xA0), 4, 0xC, 0x020305E4);
    func_08099F5C(0x02030564, 0x020305E4);
    func_080C8F48(0x02030564, arg0, 0);
    *(s32 *)((u8 *)arg0 + 0x8C) = 0;
}
