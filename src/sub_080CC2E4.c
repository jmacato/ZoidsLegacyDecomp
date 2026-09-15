#include "m2c_prelude.h"

struct Obj { u32 flags; u16 u4; u16 u6; };
struct Pair { u16 a; u16 b; };

extern struct Obj *D_02033F58[];
extern struct Pair D_02033F74[];
extern struct Pair D_02033F90[];
extern u8 D_02033FAC[];
extern u8 D_02033FB3;
extern s32 D_03000054[];

void sub_080CC2E4(u8 arg0)
{
    u8 i;
    u8 result;

    switch (D_02033FB3) {
    case 0:
        if (arg0 == 1) {
            register u8 *states asm("r9");
            register struct Obj **objects asm("r6");
            register s32 *camera asm("r4");

            i = 1;
            states = D_02033FAC;
            objects = D_02033F58;
            camera = D_03000054;
            do {
                struct Obj **slot;
                struct Obj *obj;
                s32 camera_value;

                slot = (struct Obj **)((i << 2) + (s32)objects);
                obj = *slot;
                obj->flags &= 0xFFFFEFFF;
                camera_value = camera[0];
                if (camera_value < 0)
                    camera_value += 0xFF;
                obj->u4 = obj->u4 - (camera_value >> 8);
                obj = *slot;
                camera_value = camera[1];
                if (camera_value < 0)
                    camera_value += 0xFF;
                obj->u6 = obj->u6 - (camera_value >> 8);
                *(u8 *)(i + (s32)states) = 8;
                i++;
            } while (i <= 6);
            result = 1;
            goto out;
        }
        break;
    case 1:
        if (arg0 == 0) {
            register u8 *states asm("r9");
            register struct Obj **objects asm("r6");
            register u16 *pairs90 asm("ip");
            register u16 *pairs92 asm("r10");
            register u16 *pairs74;
            register u16 *pairs76 asm("r8");

            i = 1;
            {
                register u8 *states_init asm("r0") = D_02033FAC;
                asm volatile("" : "+r"(states_init));
                states = states_init;
            }
            objects = D_02033F58;
            {
                register u16 *pairs90_init asm("r1") = &D_02033F90[0].a;
                asm volatile("" : "+r"(pairs90_init));
                pairs90 = pairs90_init;
            }
            {
                register s32 offset asm("r0") = 2;
                asm volatile("" : "+r"(offset));
                pairs92 = (u16 *)(offset + (s32)pairs90);
            }
            pairs74 = &D_02033F74[0].a;
            {
                register u16 *pairs76_init asm("r1") = &D_02033F74[0].b;
                asm volatile("" : "+r"(pairs76_init));
                pairs76 = pairs76_init;
            }
            asm volatile("" : "+r"(pairs74));
            do {
                struct Obj **slot;
                struct Obj *obj;

                slot = (struct Obj **)((i << 2) + (s32)objects);
                obj = *slot;
                obj->flags |= 0x1000;
                obj->u4 = objects[0]->u4;
                (*slot)->u6 = objects[0]->u6;
                pairs90[i * 2] = objects[0]->u4;
                pairs92[i * 2] = objects[0]->u6;
                pairs74[i * 2] = objects[0]->u4;
                pairs76[i * 2] = objects[0]->u6;
                *(u8 *)(i + (s32)states) = 8;
                i++;
            } while (i <= 6);
            result = 0;
out:
            D_02033FB3 = result;
        }
        break;
    }
}
