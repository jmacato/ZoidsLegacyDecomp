#include "m2c_prelude.h"

struct TripleBB764 {
    s32 a;
    s32 b;
    s32 c;
};

struct StateBB764 {
    struct TripleBB764 head;
    s32 packed;
    s32 angle;
    struct TripleBB764 tail;
    struct TripleBB764 saved_head;
    s32 saved_packed;
    s32 saved_angle;
    struct TripleBB764 saved_tail;
    s16 matrix[16];
};

void func_0809378C(s16 *, s16 *);

void sub_080BB764(void) {
    struct StateBB764 *state;

    state = (struct StateBB764 *)0x030033C4;
    asm volatile("" : "+r"(state));
    if (state->packed != state->saved_packed) {
        goto update_matrix;
    }
    {
        register s32 angle_offset asm("r0");
        register s32 angle asm("r1");
        register s32 saved_offset asm("r2");
        register s32 saved_angle asm("r0");

        angle_offset = 0x10;
        angle = *(s16 *)((u8 *)state + angle_offset);
        saved_offset = 0x30;
        saved_angle = *(s16 *)((u8 *)state + saved_offset);
        if (angle == saved_angle) {
            goto matrix_done;
        }
    }
update_matrix:
    {
        u32 angles[2];
        register s32 upper asm("r1");
        register s32 lower asm("r0");
        register s32 mask asm("r2");
        register s16 *output asm("r1");

        mask = 0xFFFF0000;
        upper = *(u16 *)((u8 *)state + 0xE);
        upper = -upper;
        upper <<= 16;
        lower = *(u16 *)((u8 *)state + 0xC);
        lower |= upper;
        angles[0] = lower;
        angles[1] &= mask;
        output = state->matrix;
        func_0809378C((s16 *)angles, output);
        {
            register s32 packed asm("r0");
            register s32 angle asm("r1");

            packed = state->packed;
            angle = state->angle;
            state->saved_packed = packed;
            state->saved_angle = angle;
        }
    }
matrix_done:
    {
        register struct StateBB764 *base asm("r0");
        register s32 head_c asm("r2");
        register s32 saved_head_c asm("r1");
        struct StateBB764 *current;

        base = (struct StateBB764 *)0x030033C4;
        head_c = base->head.c;
        saved_head_c = base->saved_head.c;
        current = base;
        asm volatile("" : "+&r"(current) : "r"(base));
        if (head_c != saved_head_c ||
            current->tail.a != current->saved_tail.a ||
            current->tail.b != current->saved_tail.b ||
            current->tail.c != current->saved_tail.c) {
            current->saved_head = current->head;
            current->saved_tail = current->tail;
        }
    }
}
