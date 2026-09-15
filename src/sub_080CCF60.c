#include "m2c_prelude.h"

extern s32 D_03000010;
extern u8 D_02033F36;

s32 func_080ECD5C(s32);
void *func_08094374(s32, u8, s32, s16, s32, s32, s32, s32, s32);

void sub_080CCF60(void *arg0)
{
    register char *owner asm("r5") = arg0;
    void **slots;
    register s32 *rng asm("r6");
    register s32 i asm("r2");

    i = 0;
    slots = (void **)(owner + 0xC);
    rng = &D_03000010;
    do {
        register s32 offset asm("r8");
        register s32 offset_source asm("r0");
        register void *entry asm("r1");

        offset_source = i * 4;
        entry = *(void **)((u8 *)slots + offset_source);
        offset = offset_source;
        if (entry == 0) {
            register s32 frame asm("r4");
            register s32 random asm("r0");
            register s32 y asm("r2");
            register void **slot asm("r4");
            void *object;

            random = func_080ECD5C(*rng);
            frame = (u32)(random * 4) >> 16;
            random = func_080ECD5C(*rng);
            y = *(s32 *)(owner + 8);
            y += (u32)(random * 0x41) >> 15;
            y -= 0x20;
            y = (s16)y;
            object = func_08094374(0x087ACDD8, 0x77, frame, 0, y,
                0x35C, 10, D_02033F36 != 0 ? 0x9048 : 0x1048,
                0x080CCEF1);
            slot = (void **)((u8 *)slots + offset);
            *slot = object;

            if (D_02033F36 == 0) {
                register s32 *object_r2 asm("r2");
                register s32 value asm("r0");
                register s32 scaled asm("r1");

                random = func_080ECD5C(*rng);
                object_r2 = *slot;
                scaled = random << 6;
                scaled += random;
                scaled = (u32)scaled >> 15;
                value = *(s32 *)(owner + 4);
                value += scaled;
                value -= 0x20;
                value <<= 8;
                object_r2[10] = value;
            } else {
                register s32 *object_r2 asm("r2");
                register s32 value asm("r1");

                random = func_080ECD5C(*rng);
                object_r2 = *slot;
                value = random << 6;
                value += random;
                value = (u32)value >> 15;
                value -= *(s32 *)(owner + 4);
                value += 0xD0;
                value <<= 8;
                object_r2[10] = value;
            }

            random = func_080ECD5C(*rng);
            {
                register s32 offset_view asm("r2") = offset;
                register void **slot_view asm("r1");
                register s32 *object_r2 asm("r2");
                register s32 priority asm("r1");

                asm volatile("" : "+r"(offset_view));
                slot_view = (void **)((u8 *)slots + offset_view);
                object_r2 = *slot_view;
                priority = random << 8;
                priority += random;
                priority = (u32)priority >> 15;
                priority += 0x200;
                object_r2[11] = priority;
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
