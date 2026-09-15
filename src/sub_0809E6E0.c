#include "m2c_prelude.h"

extern u8 D_087C4434[];
extern u8 D_020324B0[];
extern u8 D_020324A4[];
extern volatile u16 D_0202ECF4;

u32 sub_0809E6E0(void) {
    register u32 index asm("r2");
    register s32 value asm("r1");
    register u8 *table asm("r4");
    register u8 *selected asm("r5");
    register u32 *clear asm("r6");
    register volatile u16 *wanted asm("r3");
    u32 wanted_value;

    asm volatile(""
                 : "=l"(wanted_value)
                 :
                 : "r0", "r1", "r2", "r3", "r4", "r5", "r6");
    index = 0;
    table = D_087C4434 - 0xBB0;
    value = *(u16 *)table;
    selected = D_020324B0 + 7;
    clear = (u32 *)(D_020324A4 + 4);
    if (value != 0) {
        wanted = &D_0202ECF4;
        goto compare;
loop:
        value = index + 1;
        value <<= 24;
        index = (u32)value >> 24;
        value = index << 1;
        value += index;
        value <<= 1;
        value += (s32)table;
        value = *(u16 *)value;
        if (value == 0) {
            goto done;
        }
compare:
        asm volatile("ldrh %0, [%1, #0]"
                     : "+r"(wanted_value)
                     : "r"(wanted));
        if (value != wanted_value) {
            goto loop;
        }
    }
done:
    *selected = index;
    value = 0;
    *clear = value;
}
