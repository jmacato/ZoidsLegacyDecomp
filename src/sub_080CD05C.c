#include "m2c_prelude.h"

extern s32 D_03000010;
extern u8 D_02033F36;

s32 func_080ECD5C(s32);
void *func_08094374(s32, u8, s32, s16, s32, s32, s32, s32, s32);

void sub_080CD05C(s32 arg0) {
    void **slots;
    register s32 *rng asm("r5");
    register s32 i asm("r2");

    i = 0;
    slots = (void **)(arg0 + 0xC);
    rng = &D_03000010;
    do {
        register s32 offset asm("r6");
        register s32 offset_source asm("r0");
        register void *entry asm("r1");

        offset_source = i * 4;
        entry = *(void **)((u8 *)slots + offset_source);
        offset = offset_source;
        if (entry == 0) {
            register s32 frame asm("r4");
            register s32 frame_source asm("r1");
            s32 angle;
            s32 mode;
            register s32 *object asm("r1");

            frame_source = (u32)(func_080ECD5C(*rng) * 5) >> 15;
            frame = (u8)frame_source;
            angle = (func_080ECD5C(*rng) * 0x102) >> 16;
            object = func_08094374(0x087ACDD8, 0x77, frame, 0, angle,
                                    0x35C, 10,
                                    D_02033F36 != 0 ? 0x83C8 : 0x3C8,
                                    0x080CCEF1);
            *(void **)((u8 *)slots + offset) = object;
            mode = D_02033F36;
            if (mode != 0) {
                mode = 0xF000;
            }
            object[10] = mode;
            {
                register s32 **slot asm("r0");
                register s32 *reload asm("r1");
                register s32 scaled asm("r0");

                asm volatile("add %0, %1, %2"
                             : "=r"(slot)
                             : "r"(slots), "r"(offset));
                reload = *slot;
                scaled = frame + 1;
                scaled <<= 10;
                reload[11] = scaled;
            }
            return;
        }
        {
            register u8 next asm("r0");

            next = i + 1;
            i = next;
        }
    } while ((u32)i <= 0x1F);
}
