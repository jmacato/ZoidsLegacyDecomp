#include "m2c_prelude.h"

void ResetScanlineWindowState(void) asm("func_08095330");

void ResetScanlineWindowState(void) {
    register u8 *flags asm("r2") = (u8 *)0x03005EE8;
    register u8 *window_flags asm("r1") = (u8 *)0x03005EF7;
    register u8 zero asm("r0") = 0;

    asm("" : "+r"(window_flags));
    *window_flags = zero;
    *flags = zero;
    window_flags = (u8 *)0x03005F12;
    *window_flags = zero;
}
