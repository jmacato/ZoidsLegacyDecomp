#include "m2c_prelude.h"

void func_080988C8(s32, s32);
void func_080ED038(void *, s32, s32);

void sub_0809D094(void) {
    u8 temp_r0;
    u8 temp_r1;
    u16 *base;

    if (*(u8 *)0x0202169C == 1 && *(u8 *)0x0202169D == 1 &&
        (temp_r1 = *(u8 *)0x0202169E) == 1) {
        *(u16 *)0x02030564 = temp_r1;
    } else {
        register u16 *dst asm("r1") = (u16 *)0x02030564;
        register s32 value asm("r0") = 0x401;
        *dst = value;
    }

    base = (u16 *)0x02030566;
    func_080ED038(base, 0x08103A38, 33);
    base -= 1;
    {
        register s32 zero asm("r1") = 0;
        base[17] = 1;
        base[18] = zero;
    }
    func_080988C8(0, (s32)base);
    func_080988C8(0, 0x08103A5C);

    if (*(u8 *)0x0202169C == 1 && *(u8 *)0x0202169D == 1 &&
        (temp_r0 = *(u8 *)0x0202169E) == 1) {
        *(u16 *)0x02030564 = temp_r0;
    } else {
        register u16 *dst asm("r1") = (u16 *)0x02030564;
        register s32 value asm("r0") = 0x401;
        *dst = value;
    }

    base = (u16 *)0x02030566;
    func_080ED038(base, 0x08103A70, 17);
    base -= 1;
    {
        register s32 zero asm("r1") = 0;
        base[9] = 1;
        base[10] = zero;
    }
    func_080988C8(0, (s32)base);
    func_080988C8(0, 0x08103A84);
    func_080988C8(0, 0x08103A98);

    if (*(u8 *)0x02021699 <= 1 || *(u8 *)0x0202169A <= 1 ||
        *(u8 *)0x0202169B <= 1 || *(u8 *)0x0202169C <= 1 ||
        *(u8 *)0x0202169D <= 1 || *(u8 *)0x0202169E <= 1 ||
        *(u8 *)0x0202169F <= 1) {
        *(u16 *)0x02030564 = 1;
    } else {
        register s32 value asm("r0") = 0x401;
        *(u16 *)0x02030564 = value;
    }

    base = (u16 *)0x02030566;
    func_080ED038(base, 0x08103AA8, 31);
    base -= 1;
    func_080988C8(0, (s32)base);
}
