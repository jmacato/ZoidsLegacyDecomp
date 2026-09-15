#include "m2c_prelude.h"

struct ObjectA876C {
    u8 pad0[6];
    s16 display_y;
    u8 pad8[4];
    s16 scale;
};

void func_08092E84(s32);
struct ObjectA876C *func_08094484(s32, s32, s32, s32, s32,
    s32, s32, s32, s32);
void func_080ED17C(s32);

void sub_080A876C(void)
{
    struct ObjectA876C *created;
    register void **raw_slot asm("r1");
    register struct ObjectA876C **slot asm("r5");
    register u32 frame asm("r4");
    register volatile u16 *blend asm("r6");

    created = func_08094484(0x0821024C, 0x08210258, 0, 0x78,
        0x58, 0, 0, 0x887C8, 0);
    raw_slot = (void **)0x02031C94;
    asm volatile("" : "+r"(raw_slot));
    *raw_slot = created;
    asm volatile("" : "+r"(raw_slot));
    frame = 0;
    slot = (struct ObjectA876C **)raw_slot;
    asm volatile("" : "+r"(slot));
    blend = (volatile u16 *)0x03000050;

loop:
    if (frame <= 0xF) {
        struct ObjectA876C *object;
        s32 value;

        if (frame == 0) {
            func_08092E84(0x71);
        }
        object = *slot;
        object->scale = (frame << 4) + 0x100;
        value = object->scale;
        if (value < 0) {
            value += 7;
        }
        object->display_y = (value >> 3) + 0x38;
        *blend = (0x10 - frame) | 0x1000;
    } else {
        (*slot)->scale = 0;
    }

    {
        register s32 next asm("r1") = frame + 1;
        register s32 reduced asm("r0") = next;
        asm volatile("" : "+r"(reduced));
        reduced >>= 5;
        reduced <<= 5;
        reduced = next - reduced;
        frame = (u8)reduced;
    }
    func_080ED17C(1);
    goto loop;
}
