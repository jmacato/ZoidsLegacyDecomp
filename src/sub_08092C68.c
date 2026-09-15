#include "m2c_prelude.h"
extern u8 D_03000E3C[], D_03000E14[];
void func_80ECD60(s32, s32);
void func_8092E0C(u8);
void func_80ED17C(s32);
void sub_08092C68(s32 arg0) {
    s32 t = arg0 << 0x18;
    u8 *base2 = D_03000E14;
    s32 i = ((u32)t >> 0x16) - 4;
    s32 *p2 = (s32 *)(base2 + i), *p1 = (s32 *)(D_03000E3C + i);
    func_80ECD60(*p1, *p2);
    func_8092E0C(*(u8 *)0x03000A80);
loop_1:
    func_80ED17C(1);
    goto loop_1;
}
void sub_08092C9C(void) { sub_08092C68(1); }
void sub_08092CA8(void) { sub_08092C68(2); }
void sub_08092CB4(void) { sub_08092C68(3); }
void sub_08092CC0(void) { sub_08092C68(4); }
void sub_08092CCC(void) { sub_08092C68(5); }
void sub_08092CD8(void) { sub_08092C68(6); }
void sub_08092CE4(void) { sub_08092C68(7); }
void sub_08092CF0(void) { sub_08092C68(8); }
void sub_08092CFC(void) { sub_08092C68(9); }
void sub_08092D08(void) { sub_08092C68(10); }
void sub_08092D14(void) { sub_08092C68(11); }
