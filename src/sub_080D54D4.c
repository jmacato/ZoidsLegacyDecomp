#include "m2c_prelude.h"

struct ChildD54D4 {
    u8 pad0[0x28];
    s32 field_28;
};

struct OwnerD54D4 {
    u8 pad0[8];
    s16 y;
    u8 padA[2];
    struct ChildD54D4 *children[9];
    u8 pad30[0x5C];
    u32 state;
};

struct ChildD54D4 *func_80D2450(struct OwnerD54D4 *, s32, s32, s32,
    s32, s32, s32, s32);
void func_80D2790(s32);
void func_8095114(struct OwnerD54D4 *);

void sub_080D54D4(struct OwnerD54D4 *owner)
{
    register struct OwnerD54D4 *saved_owner asm("r4") = owner;
    register u32 *state asm("r5") =
        (u32 *)((u8 *)saved_owner + 0x8C);

    if (*state <= 7) {
        if (*state == 0) {
            struct ChildD54D4 *child;

            child = func_80D2450(saved_owner, 1, 0, 0, saved_owner->y,
                0x110, 0x080D2529, 1);
            saved_owner->children[0] = child;
            child->field_28 = 0x20;
            func_80D2790(0);
        }

        {
            u32 current = *state;
            struct ChildD54D4 *child;
            register u32 next asm("r2");
            register u32 offset asm("r3");
            register struct ChildD54D4 **slot asm("r1");

            child = func_80D2450(saved_owner, 0, 0,
                (s16)(current << 5), saved_owner->y, 0x400, 0, 1);
            next = *state;
            next++;
            asm volatile("" : "+r"(next));
            offset = next << 2;
            asm volatile("" : "+r"(offset));
            slot = &saved_owner->children[0];
            asm volatile("" : "+r"(slot));
            slot = (struct ChildD54D4 **)((u8 *)slot + offset);
            *slot = child;
            *state = next;
        }
    } else {
        u8 i = 0;

        if (saved_owner->children[0] == 0) {
            register struct ChildD54D4 **slots asm("r2") =
                &saved_owner->children[0];

scan_next:
            i++;
            if (i > 8) {
                goto scan_done;
            }
            {
                register u32 slot_address asm("r0") = i << 2;
                asm volatile("add %0, %1, %0"
                             : "+r"(slot_address)
                             : "r"(slots));
                if (*(struct ChildD54D4 **)slot_address == 0) {
                    goto scan_next;
                }
            }
        }
scan_done:
        if (i == 9) {
            func_8095114(saved_owner);
        }
    }
}
