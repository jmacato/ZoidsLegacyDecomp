#include "m2c_prelude.h"

void func_08096308(s32, s32);
s32 func_0809669C(void);
void func_080A016C(u8, s32, s32);
void func_080ED17C(s32);

s32 sub_080A1AE8(s32 arg0)
{
    u8 id;

    arg0 <<= 24;
    id = (u32)arg0 >> 24;
    *(u8 *)0x02030664 = 1;
    if ((func_0809669C() << 24) == 0) {
        goto inactive;
    }

    func_08096308(0xE, 0);
    {
        register s32 *target asm("r2") = *(s32 **)0x02032990;

        if (target == 0) {
            goto scan;
        }
        {
            register s16 *output asm("r4") = (s16 *)0x03005F74;
            register s32 *camera asm("r3") = (s32 *)0x03000054;
            register s32 value asm("r0");

            value = target[2] - camera[0];
            if (value < 0) {
                value += 0xFF;
            }
            *output = value >> 8;
            output = (s16 *)0x03005F76;
            value = target[3] - camera[1];
            if (value < 0) {
                value += 0xFF;
            }
            *output = value >> 8;
        }
        goto trigger;
    }

scan:
    {
        register u32 i asm("r2") = 0;
        register u8 *record asm("r3") = (u8 *)0x020325A0;
        register s16 *output_x asm("r4");
        register s16 *output_y asm("r6");
        register u8 *base asm("r5");
        register u32 active asm("r1") = *(u32 *)record;
        register u32 one asm("r0") = 1;

        active &= one;
        asm volatile("" : "+r"(active));
        output_x = (s16 *)0x03005F74;
        asm volatile("" : "+r"(output_x));
        output_y = (s16 *)0x03005F76;
        asm volatile("" : "+r"(output_y));
        base = record;
        if (active != 0) {
            goto check_type;
        }
scan_next:
        i++;
        if (i > 13) {
            goto fallback;
        }
        {
            register u32 offset asm("r0") = i << 3;
            offset += i;
            offset <<= 3;
            record = (u8 *)(offset + (u32)base);
        }
        if ((*(u32 *)record & 1) == 0) {
            goto scan_next;
        }
check_type:
        if (*(u16 *)(record + 6) != 6) {
            goto scan_next;
        }
        if (i > 13) {
            goto fallback;
        }
        {
            register s32 *camera asm("r2") = (s32 *)0x03000054;
            register s32 value asm("r0");

            value = *(s32 *)(record + 8) - camera[0];
            if (value < 0) {
                value += 0xFF;
            }
            *output_x = value >> 8;
            value = *(s32 *)(record + 0xC) - camera[1];
            if (value < 0) {
                value += 0xFF;
            }
            value >>= 8;
            *output_y = value;
        }
        goto trigger;

fallback:
        *output_x = 0x78;
        *output_y = 0x50;
    }

trigger:
    func_080A016C(id, -1, 0);
    goto done;

inactive:
    func_080ED17C(1);

done:
    return 0;
}
