#include "m2c_prelude.h"

extern void *func_080D2660();
extern u32 func_080ECD5C(u32);
extern u32 D_03000010;

struct OwnerD6BDC {
    u32 flags;
    s16 x;
    s16 y;
    u8 pad08[0x1C];
    s32 active;
    void *parent;
    u32 phase;
    s32 position_x;
    s32 position_y;
};

void sub_080D6BDC(struct OwnerD6BDC *arg0) {
    volatile s32 reserve0;
    volatile s32 reserve1;
    volatile s32 reserve2;
    volatile s32 reserve3;
    volatile s32 reserve4;
    register struct OwnerD6BDC *owner asm("r6") = arg0;
    register s32 boundary_check asm("r3") = 0;
    char *parent = owner->parent;
    u32 phase = owner->phase;

    asm volatile("" : "=m"(reserve0), "=m"(reserve1), "=m"(reserve2),
                       "=m"(reserve3), "=m"(reserve4));

    if (phase <= 0xF) {
        register u32 phase_view asm("r2");

        if (phase == 0) {
            owner->position_x = owner->x << 8;
            owner->position_y = owner->y << 8;
        }
        if ((owner->flags & 0x8000) == 0) {
            phase_view = owner->phase;
            asm volatile("" : "+r"(phase_view));
            owner->position_x -= phase_view << 7;
        } else {
            phase_view = owner->phase;
            asm volatile("" : "+r"(phase_view));
            owner->position_x += phase_view << 7;
        }
        {
            register s32 y_delta asm("r0") = phase_view << 6;
            register s32 position_y asm("r1") = owner->position_y;

            position_y -= y_delta;
            owner->position_y = position_y;
            owner->x = (u32)owner->position_x >> 8;
            owner->y = (u32)position_y >> 8;
        }

        {
            u32 modulo = 3;
            modulo &= phase_view;
            if (modulo == 0) {
                register u32 *rng asm("r5") = &D_03000010;
                register s32 x asm("r4");
                register s32 y asm("r2");
                register u32 random asm("r0");
                register volatile s32 *outgoing asm("sp");
                void *created;

                random = func_080ECD5C(*rng);
                x = (u16)owner->x - 2;
                x += (random * 5) >> 15;
                x = (s16)x;
                random = func_080ECD5C(*rng);
                y = (u16)owner->y - 2;
                y += (random * 5) >> 15;
                y = (s16)y;

                outgoing[0] = y;
                outgoing[1] = 0x500;
                outgoing[2] = 0x13;
                outgoing[3] = 0x100;
                outgoing[4] = 2;
                created = func_080D2660(parent, 2, 0, x);
                {
                    register u32 offset asm("r1") = owner->phase;
                    register char *children asm("r2");
                    offset >>= 2;
                    offset += 1;
                    offset <<= 2;
                    children = parent + 0xC;
                    children += offset;
                    *(void **)children = created;
                }
                goto check_boundary;
            }
        }
    } else {
        register u32 flags asm("r1") = owner->flags;
        register u32 direction asm("r0") = flags;
        register u32 flags_copy asm("r2");

        direction &= 0x8000;
        flags_copy = flags;
        asm volatile("" : "+r"(direction), "+r"(flags_copy));

        if (direction == 0) {
            owner->position_x -= 0x1000;
        } else {
            owner->position_x += 0x1000;
        }
        {
            register s32 position_y asm("r1") = owner->position_y;
            register s32 y_delta asm("r0") = -0x800;

            position_y += y_delta;
            owner->position_y = position_y;
            owner->x = (u32)owner->position_x >> 8;
            owner->y = (u32)position_y >> 8;
        }

        if ((owner->phase & 1) == 0) {
            register s32 x asm("r3");
            register s32 old_x asm("r1");
            register volatile s32 *outgoing asm("sp");
            void *created;

            old_x = owner->x;
            if ((flags_copy & 0x8000) == 0) {
                register s32 moved_x asm("r0") = old_x;
                moved_x += 0x20;
                x = (s16)moved_x;
            } else {
                register s32 moved_x asm("r0") = old_x;
                moved_x -= 0x20;
                x = (s16)moved_x;
            }
            outgoing[0] = (s16)((u16)owner->y + 0x10);
            outgoing[1] = 0x500;
            outgoing[2] = 0x13;
            outgoing[3] = 0x80;
            outgoing[4] = 2;
            created = func_080D2660(parent, 1, 0, x);
            {
                register u32 offset asm("r1") = owner->phase;
                register char *children asm("r2");
                offset -= 0x10;
                offset >>= 1;
                offset += 5;
                offset <<= 2;
                children = parent + 0xC;
                children += offset;
                *(void **)children = created;
            }
            boundary_check = 1;
        }
    }

    if (boundary_check == 0) {
        goto advance;
    }
check_boundary:
    {
        register u32 flags asm("r1") = owner->flags;
        register u32 direction asm("r0") = flags;
        register u32 flags_copy asm("r2");

        direction &= 0x8000;
        flags_copy = flags;
        asm volatile("" : "+r"(direction), "+r"(flags_copy));

        if (direction == 0) {
            if (owner->x < 0) {
                goto check_y;
            }
            goto advance;
        } else if (owner->x <= 0xEF) {
            goto advance;
        }
check_y:
        if (owner->y < 0) {
            owner->flags = flags_copy | 0x20000;
            owner->active = 0;
            return;
        }
    }
advance:
    owner->phase += 1;
}
