#include "m2c_prelude.h"
s32 func_8094484(s32, s32, s32, s32, s32, s32, s32, s32, s32);

void sub_0809B46C(u8 arg0) {
    register s32 base0 asm("r3");
    register s32 base1 asm("r1");

    base0 = 0x08103770;
    base1 = 0x08103794;
    *(s32 *)0x020216A4 = func_8094484(base0, base1, arg0 == 0, 0x5C, 0x50, 0x37D, 0xE, 0x210, 0);
    *(s32 *)0x020216A8 = func_8094484(0x080ED8F8, 0x080ED92C, 0, 0x58, (s32) ((*(u8 *)0x020216AC << 0x14) + 0x580000) >> 0x10, 0x3EF, 0xF, 0x120, 0);
}
