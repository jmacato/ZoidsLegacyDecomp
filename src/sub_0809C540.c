#include "m2c_prelude.h"

s32 func_0809C434(void);
void func_0809C480(void);
s32 func_080ECD98(s32, s32);
u16 func_080ECF78(u16, s32);

void sub_0809C540(s32 arg0, s32 arg1) {
    u16 value;
    u16 remainder;
    s32 adjusted;
    register volatile u8 *category asm("r4");
    register volatile u8 *page asm("r4");

    category = (u8 *)0x020216F5;
    *category = arg0;
    *(u8 *)0x020216F6 = arg1;
    if ((func_0809C434() << 24) == 0) {
        register u8 *table asm("r2");
        register s32 category_value asm("r1");
        register s32 offset asm("r0");
        register u16 *entry asm("r0");

        table = (u8 *)0x087A11D8;
        asm volatile("" : "+r"(table));
        category_value = *category;
        offset = category_value << 5;
        offset += category_value;
        offset <<= 2;
        offset -= category_value;
        offset <<= 1;
        entry = (u16 *)(offset + (s32)table);
        value = *entry;
    }

    page = (u8 *)0x02021709;
    remainder = func_080ECF78(value, 13);
    if (remainder != 0) {
        adjusted = value + 13;
        adjusted -= remainder;
    } else {
        adjusted = value;
    }
    *page = func_080ECD98(adjusted, 13);
    if (*page <= 4) {
        *(u8 *)0x02021708 = 0;
    } else {
        register volatile u8 *position asm("r2");
        register s32 current asm("r1");
        register s32 maximum asm("r0");

        position = (u8 *)0x02021708;
        current = *position;
        maximum = *page;
        maximum -= 5;
        if (current > maximum) {
            *position = maximum;
        }
    }
    func_0809C480();
}
