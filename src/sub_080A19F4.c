#include "m2c_prelude.h"

struct CameraRecord {
    u32 flags;
    u16 unk_04;
    u16 type;
    s32 x;
    s32 y;
    u8 pad_10[0x38];
};

void func_08096308(s32, s32);
s32 func_0809669C(void);
void func_080A016C(u8, s32, s32);
void func_080ED17C(s32);

s32 sub_080A19F4(u8 arg0)
{
    *(s8 *)0x02030664 = 1;
    if ((func_0809669C() << 24) == 0) {
        goto inactive;
    }
    func_08096308(13, 0);
    func_080ED17C(1);
    {
        register struct CameraRecord *target asm("r2") =
            *(struct CameraRecord **)0x02032990;

        if (target == 0) {
            goto scan;
        }
        {
            register volatile s16 *output asm("r4") = (s16 *)0x03005F74;
            register s32 *state asm("r3") = (s32 *)0x03000054;
            register s32 value asm("r0") = target->x - state[0];

            if (value < 0) {
                value += 0xFF;
            }
            *output = value >> 8;
            output = (s16 *)0x03005F76;
            value = target->y - state[1];
            if (value < 0) {
                value += 0xFF;
            }
            *output = value >> 8;
        }
        goto start;
    }

scan:
    {
        register u32 index asm("r2") = 0;
        register struct CameraRecord *record asm("r3") =
            (struct CameraRecord *)0x020325A0;
        register volatile s16 *output_x asm("r4");
        register volatile s16 *output_y asm("r6");
        register struct CameraRecord *records asm("r5");
        register s32 value asm("r0");
        register u32 active asm("r1") = record->flags;
        register u32 one asm("r0") = 1;

        active &= one;
        output_x = (s16 *)0x03005F74;
        output_y = (s16 *)0x03005F76;
        records = record;
        if (active == 0) {
next:
            index++;
            if (index > 13) {
                goto fallback;
            }
            {
                register u32 offset asm("r0") = index << 3;

                offset += index;
                offset <<= 3;
                record = (struct CameraRecord *)(offset + (u32)records);
            }
            if ((record->flags & 1) == 0) {
                goto next;
            }
        }
        if (record->type != 6) {
            goto next;
        }
        if (index > 13) {
            goto fallback;
        }
        {
            register s32 *state asm("r2") = (s32 *)0x03000054;

            value = record->x - state[0];
            if (value < 0) {
                value += 0xFF;
            }
            *output_x = value >> 8;
            value = record->y - state[1];
            if (value < 0) {
                value += 0xFF;
            }
            value >>= 8;
            goto store_y;
        }

fallback:
        *output_x = 120;
        value = 80;
store_y:
        *output_y = value;
    }

start:
    func_080A016C(arg0, -1, 0);
    goto done;
inactive:
    func_080ED17C(1);
done:
    return 0;
}
