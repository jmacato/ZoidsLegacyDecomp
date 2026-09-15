#include "m2c_prelude.h"

struct Vec {
    s32 a;
    s32 b;
    s32 c;
};

union StateTail {
    struct {
        u16 d;
        u16 e;
        u16 f;
        u16 pad;
    } half;
    struct {
        s32 x;
        s32 y;
    } word;
};

struct State {
    struct Vec v;
    union StateTail tail;
};

extern u8 D_02032EF9;
extern struct State D_02032EFC;
extern u8 D_02032F62;
extern struct State D_030033C4;
extern s32 D_087A2790[][3];

void sub_080BB224(u8 arg0, u8 arg1, u8 arg2, u8 arg3)
{
    u8 *mode_address;
    u8 *side;
    u8 *index;
    u8 mode;

    mode_address = &D_02032EF9;
    *mode_address = arg0;
    *(u8 *)0x02032F60 = arg1;
    *(u8 *)0x02032F61 = arg2;
    mode = *mode_address;
    side = (u8 *)0x02032F60;
    index = (u8 *)0x02032F61;

    switch (mode) {
    case 1:
    {
        struct State *state;

        state = &D_02032EFC;
        state->v.a = 0xFFFF3000;
        state->v.b = 0x20000;
        state->v.c = 0x8000;
        state->tail.half.d = 4;
        state->tail.half.f = 0;
        state->tail.half.e = 0;
        break;
    }
    case 8:
    {
        struct State *state;

        state = &D_02032EFC;
        state->v.a = 0;
        state->v.b = 0x20000;
        state->v.c = 0x8000;
        state->tail.half.d = 4;
        state->tail.half.f = 0;
        state->tail.half.e = 0;
        break;
    }
    case 2:
    {
        u8 side_value;

        side_value = *side;
        if (side_value == 0) {
            struct State *state;

            state = &D_02032EFC;
            state->v.a = 0xD000;
            state->v.b = side_value;
            state->v.c = 0x8000;
            state->tail.half.d = 0x20;
            state->tail.half.f = side_value;
            state->tail.half.e = side_value;
        } else {
            struct State *state;

            state = &D_02032EFC;
            state->v.a = 0xFFFF3000;
            state->v.b = 0;
            state->v.c = 0x8000;
            state->tail.half.d = 0x20;
            state->tail.half.f = 0;
            state->tail.half.e = 0;
        }
        break;
    }
    case 3:
    {
        u8 side_value;

        side_value = *side;
        if (side_value == 0) {
            struct State *state;

            state = &D_02032EFC;
            state->v.a = 0xB000;
            state->v.b = side_value;
            state->v.c = 0x8000;
            state->tail.half.d = 0x20;
            state->tail.half.f = side_value;
            state->tail.half.e = side_value;
        } else {
            struct State *state;

            state = &D_02032EFC;
            state->v.a = 0xFFFF1000;
            state->v.b = 0;
            state->v.c = 0x8000;
            state->tail.half.d = 0x20;
            state->tail.half.f = 0;
            state->tail.half.e = 0;
        }
        break;
    }
    case 4:
    {
        u8 side_value;

        side_value = *side;
        if (side_value == 0) {
            struct State *state;

            state = &D_02032EFC;
            state->v.a = 0xC000;
            state->v.b = side_value;
            state->v.c = 0x8000;
            state->tail.half.d = 0x20;
            state->tail.half.f = side_value;
            state->tail.half.e = side_value;
        } else {
            struct State *state;

            state = &D_02032EFC;
            state->v.a = 0xFFFF0000;
            state->v.b = 0;
            state->v.c = 0x8000;
            state->tail.half.d = 0x20;
            state->tail.half.f = 0;
            state->tail.half.e = 0;
        }
        break;
    }
    case 5:
    {
        register struct State *state asm("r3");
        register s32 *table asm("r2");
        s32 first_index;

        state = &D_02032EFC;
        table = D_087A2790[0];
        first_index = (*side * 6) + *index;
        state->v.a = table[first_index * 3];
        {
            register s32 second_index asm("r0");
            register s32 second_offset asm("r1");

            second_index = (*side * 6) + *index;
            second_offset = second_index * 3;
            second_offset <<= 2;
            table += 2;
            state->v.b = *(s32 *)((u32)second_offset + (u32)table);
        }
        state->v.c = 0x8000;
        state->tail.half.d = 0x20;
        state->tail.half.f = 0;
        state->tail.half.e = 0;
        break;
    }
    case 0:
    case 6:
    {
        struct State *state;

        state = &D_02032EFC;
        state->v.a = 0;
        state->v.b = 0;
        state->v.c = 0x8000;
        state->tail.half.d = 0x20;
        state->tail.half.f = 0;
        state->tail.half.e = 0;
        break;
    }
    case 7:
        break;
    case 9:
    {
        register struct State *state asm("r3");
        register s32 *table asm("r2");
        s32 first_index;

        state = &D_02032EFC;
        table = D_087A2790[0];
        first_index = (*side * 6) + *index;
        state->v.a = table[first_index * 3];
        {
            register s32 second_index asm("r0");
            register s32 second_offset asm("r1");

            second_index = (*side * 6) + *index;
            second_offset = second_index * 3;
            second_offset <<= 2;
            table += 2;
            state->v.b = *(s32 *)((u32)second_offset + (u32)table);
        }
        state->v.c = 0x4000;
        state->tail.half.d = 0x20;
        state->tail.half.f = 0;
        state->tail.half.e = 0;
        break;
    }
    default:
        break;
    }

    if (arg3 == 1) {
        s32 x;
        s32 y;

        D_030033C4.v = D_02032EFC.v;
        x = D_02032EFC.tail.word.x;
        y = D_02032EFC.tail.word.y;
        D_030033C4.tail.word.x = x;
        D_030033C4.tail.word.y = y;
    }
    D_02032F62 = 0;
}
