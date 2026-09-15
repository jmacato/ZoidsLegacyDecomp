#include "m2c_prelude.h"

extern void func_08094554(void *);
extern void func_080986B4(s32);
extern void func_08098BB4(s32);
extern void func_080972C8(void);
extern void func_08096308(s32, s32);
extern void func_080ED17C(s32);
extern u8 func_0809669C(void);
extern void func_080B35D4(s32);
extern void func_080A016C(s32, s32, s32);

s32 sub_080A66C8(u8 arg0)
{
    *(u8 *)0x02030664 = 1;
    {
        register u32 index asm("r1") = 0;
        register u8 *base asm("r0") = (u8 *)0x020218E4;
        register u32 offset asm("r3") = 0x690C;
        register u8 *available asm("r2");

        asm volatile("" : "+r"(base));
        asm volatile("" : "+r"(offset));
        available = base + offset;
        if (available[0] == 0) {
scan:
            {
                register u32 next_index asm("r0");
                next_index = index + 1;
                index = (u8)next_index;
            }
            if (index <= 5) {
                register u8 *slot asm("r0") = (u8 *)index;

                slot += (u32)available;
                if (*slot == 0) {
                    goto scan;
                }
            }
        }
        if (index != 6) {
            goto done;
        }
    }

    {
        void **object = (void **)0x02031744;
        if (*object != 0) {
            func_08094554(*object);
            *object = 0;
        }
    }
    {
        u8 *state = (u8 *)0x02030666;
        if (*state == 0) {
            func_08098BB4(0x080177ED);
            *state = 2;
        } else if (*state == 1) {
            func_08098BB4(0x080177F5);
            func_08098BB4(0x080177ED);
            *state = 2;
        } else {
            func_080986B4(2);
        }
        func_08098BB4(0x0801798D);
        func_08098BB4(0x080177FA);
        func_080972C8();
        func_08096308(16, 0);
        goto first_test;
first_tick:
        func_080ED17C(1);
first_test:
        if ((func_0809669C() << 24) == 0) {
            goto first_tick;
        }
        {
            register s32 *status asm("r4") = (s32 *)0x02021690;

            *status = -1;
            func_080ED17C(1);
            func_080B35D4(1);
            *status = 3;
            func_080ED17C(1);
            func_08096308(15, 0);
        }
        goto second_test;
second_tick:
        func_080ED17C(1);
second_test:
        if ((func_0809669C() << 24) == 0) {
            goto second_tick;
        }
    }

done:
    func_080A016C(arg0, -1, 0);
    return 0;
}
