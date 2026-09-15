#include "m2c_prelude.h"

struct VecBB474 {
    s32 a;
    s32 b;
    s32 c;
};

union StateTailBB474 {
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

struct StateBB474 {
    struct VecBB474 v;
    union StateTailBB474 tail;
};

extern u8 D_02032EF9;
extern struct StateBB474 D_02032EFC;
extern u8 D_02032F62;
extern struct StateBB474 D_030033C4;

void sub_080BB474(void)
{
    u8 *done;
    u8 done_value;

    {
        register u8 *done_seed asm("r0");

        done_seed = &D_02032F62;
        done_value = *done_seed;
        done = done_seed;
    }
    if (done_value != 0) {
        return;
    }
    if (D_02032EF9 == 1 || D_02032EF9 == 8) {
        register struct StateBB474 *state_seed asm("r0");
        register struct StateBB474 *state asm("r5");
        register s32 value asm("r2");
        register s32 limit asm("r1");

        state_seed = &D_030033C4;
        value = state_seed->v.b;
        limit = 0x7FFF;
        state = state_seed;
        if (value <= limit) {
            s32 rounded;
            s32 next_value;
            u32 angle;

            rounded = value;
            if (value < 0) {
                rounded = value + 7;
            }
            next_value = value - (rounded >> 3);
            asm volatile("" : : "r"(value));
            state->v.b = next_value;
            angle = state->tail.half.d;
            if ((s16)state->tail.half.d <= 0x1F) {
                state->tail.half.d = angle + 1;
            }
        } else {
            s32 next_value;

            next_value = value + 0xFFFFF000;
            asm volatile("" : : "r"(value));
            state->v.b = next_value;
        }
        if ((s16)state->tail.half.d != 0x20) {
            return;
        }
        if (state->v.b > 0x3F) {
            return;
        }
        state->v.b = 0;
        goto complete;
    }

    {
        register struct StateBB474 *state asm("r5");
        register struct StateBB474 *target asm("r6");

        {
            register struct StateBB474 *state_seed asm("r0");
            register struct StateBB474 *target_seed asm("r1");
            register s32 target_value asm("r3");
            register s32 current_value asm("r4");
            register s32 delta asm("r2");
            s32 next;

            state_seed = &D_030033C4;
            target_seed = &D_02032EFC;
            target_value = target_seed->v.a;
            current_value = state_seed->v.a;
            delta = target_value - current_value;
            state = state_seed;
            target = target_seed;
            if (delta < 0) {
                delta += 3;
            }
            next = current_value + (delta >> 2);
            asm volatile("" : : "r"(delta), "r"(current_value));
            state->v.a = next;
            if ((target_value > next && target_value - next <= 0x7F) ||
                (target_value < next && target_value - next > -0x80)) {
                state->v.a = target->v.a;
            }
            asm volatile("" : : "r"(target_value));
        }

        {
            s32 target_value;
            s32 current_value;
            s32 delta;
            s32 next;

            target_value = target->v.b;
            current_value = state->v.b;
            delta = target_value - current_value;
            if (delta < 0) {
                delta += 3;
            }
            next = current_value + (delta >> 2);
            state->v.b = next;
            if ((target_value > next && target_value - next <= 0x7F) ||
                (target_value < next && target_value - next > -0x80)) {
                state->v.b = target->v.b;
            }
        }

        {
            s32 target_value;
            s32 current_value;
            s32 delta;
            s32 next;

            target_value = target->v.c;
            current_value = state->v.c;
            delta = target_value - current_value;
            if (delta < 0) {
                delta += 3;
            }
            next = current_value + (delta >> 2);
            state->v.c = next;
            if ((target_value > next && target_value - next <= 0x7F) ||
                (target_value < next && target_value - next > -0x80)) {
                state->v.c = target->v.c;
            }
        }
        {
            u32 current_raw;
            register u32 updated asm("r0");
            s16 current_short;
            s16 target_short;

            current_raw = state->tail.half.d;
            current_short = (s16)state->tail.half.d;
            target_short = (s16)target->tail.half.d;
            if (current_short != target_short) {
                if (current_short < target_short) {
                    if (target_short - current_short > 0x80) {
                        updated = current_raw - 1;
                    } else {
                        goto increment_d;
                    }
                } else if ((s16)state->tail.half.d -
                           (s16)target->tail.half.d <= 0x80) {
                    updated = current_raw - 1;
                    asm volatile("" : "+r"(updated));
                } else {
increment_d:
                    updated = current_raw + 1;
                }
                state->tail.half.d = updated;
            }
        }

        {
            u32 current_raw;
            register u32 updated asm("r0");
            s16 current_short;
            s16 target_short;

            current_raw = state->tail.half.e;
            current_short = (s16)state->tail.half.e;
            target_short = (s16)target->tail.half.e;
            if (current_short != target_short) {
                if (current_short < target_short) {
                    if (target_short - current_short > 0x80) {
                        updated = current_raw - 1;
                    } else {
                        goto increment_e;
                    }
                } else if ((s16)state->tail.half.e -
                           (s16)target->tail.half.e <= 0x80) {
                    updated = current_raw - 1;
                    asm volatile("" : "+r"(updated));
                } else {
increment_e:
                    updated = current_raw + 1;
                }
                state->tail.half.e = updated;
            }
        }

        {
            u32 current_raw;
            register u32 updated asm("r0");
            s16 current_short;
            s16 target_short;

            current_raw = state->tail.half.f;
            current_short = (s16)state->tail.half.f;
            target_short = (s16)target->tail.half.f;
            if (current_short != target_short) {
                if (current_short < target_short) {
                    if (target_short - current_short > 0x80) {
                        updated = current_raw - 1;
                    } else {
                        goto increment_f;
                    }
                } else if ((s16)state->tail.half.f -
                           (s16)target->tail.half.f <= 0x80) {
                    updated = current_raw - 1;
                    asm volatile("" : "+r"(updated));
                } else {
increment_f:
                    updated = current_raw + 1;
                }
                state->tail.half.f = updated;
            }
        }

        if (*(volatile s32 *)&state->v.a !=
                *(volatile s32 *)&target->v.a ||
            *(volatile s32 *)&state->v.b !=
                *(volatile s32 *)&target->v.b ||
            *(volatile s32 *)&state->v.c !=
                *(volatile s32 *)&target->v.c ||
            *(volatile s32 *)&state->tail.word.x !=
                *(volatile s32 *)&target->tail.word.x) {
            return;
        }
        {
            register s32 state_f asm("r1");
            register s32 target_f asm("r0");

            {
                register u32 state_offset asm("r0");

                state_offset = 0x10;
                state_f = *(s16 *)((u8 *)state + state_offset);
            }
            {
                register u32 target_offset asm("r2");

                target_offset = 0x10;
                target_f = *(s16 *)((u8 *)target + target_offset);
            }
            if (state_f != target_f) {
                return;
            }
        }
    }

complete:
    *done = 1;
}
