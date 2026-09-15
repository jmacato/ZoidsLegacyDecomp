#include "m2c_prelude.h"

extern s16 func_08092A90(s16);
extern void func_08095114(void *);
extern void func_080D12A0(s32, s32);
extern void *func_080D2450(void *, s32, s32, s32, s32, s32, s32, s32);
extern void *func_080D2660(void *, s32, s32, s32, s32, s32, s32, s32, s32);
extern void func_080D2790(s32);
extern u32 func_080ECD5C(u32);
extern s32 func_080ECF00(s32, s32);

extern u32 D_03000010;

struct DD06COwner {
    u8 pad0[4];
    s32 x;
    s32 y;
    void *children[32];
    s32 state;
    s32 started;
    u32 count;
};

void sub_080DD06C(struct DD06COwner *arg0) {
    struct DD06COwner *owner = arg0;
    register s32 *phase_slot asm("r4") = &owner->state;
    s32 phase = *phase_slot;

    if (phase == 0) {
        owner->children[0] = func_080D2450(
            owner, 0, 1, 0x80, (s16)owner->y, 0x600, phase, 1);
        func_080D2790(0);
        *phase_slot = *phase_slot + 1;
        asm volatile("" : "+r"(phase_slot));
        phase_slot++;
    } else {
        register s32 *started_slot asm("r0") = &owner->started;
        register s32 started_value asm("r1") = *started_slot;

        phase_slot = started_slot;
        if (started_value != 0) {
            goto active;
        }
        if (*(u16 *)((u8 *)owner->children[0] + 0x14) == 2) {
            *phase_slot = 1;
            func_080D12A0(6, 0);
            func_080D2790(1);
        }
    }

    {
        register s32 started asm("r0") = *phase_slot;
        register s32 initial_count asm("r0");
        register s32 *count_slot asm("sl");
        register s32 *count_init asm("r1") = (s32 *)0x94;

        asm volatile("add %0, %0, %1"
                     : "+r"(count_init) : "r"(owner));
        count_slot = count_init;

        if (started == 0) {
            goto spawn_done;
        }
active:
        {
            register s32 *active_count_slot asm("r0") = &owner->count;
            register s32 active_count asm("r1") = *active_count_slot;
            asm volatile("" : "+r"(active_count));
            count_slot = active_count_slot;

        if ((u32)active_count <= 0xE) {
            register s32 scaled asm("r6");
            register s32 scale_byte asm("r9");
            register s32 random asm("r8");
            register s32 x_value asm("r5");
            register s32 y_value asm("r4");
            s32 trig;

            trig = func_08092A90(
                (s16)func_080ECF00(active_count << 7, 0xE));
            if (trig < 0) {
                trig += 7;
            }
            scaled = trig >> 3;
            scaled <<= 24;
            {
                register s32 scale_init asm("r2") = (u32)scaled >> 24;
                scale_byte = scale_init;
                asm volatile("" : : "r"(scale_init));
            }

            x_value = owner->x;
            {
                register s32 *count_view asm("r1") = count_slot;
                x_value += *count_view << 3;
            }
            x_value = (u16)(x_value - 0x20);
            {
                register u32 *rng asm("r2") = &D_03000010;
                random = func_080ECD5C(*rng);
            }
            y_value = owner->y;
            {
                register s32 *count_view asm("r1") = count_slot;
                register s32 phase asm("r0") = *count_view;
                register s32 mask asm("r1") = 3;
                register s32 product asm("r2") = scale_byte;

                phase &= mask;
                product *= phase;
                y_value += func_080ECF00(product, 3);
            }
            y_value -= (u32)scaled >> 25;
            {
                register s32 perturb asm("r0") =
                    (u32)(random * 9) >> 15;
                perturb += 0xFFFC;
                y_value += perturb;
            }
            x_value = (s16)x_value;
            y_value = (s16)y_value;

            {
                register char *children asm("r6");
                register void *created asm("r0") = func_080D2450(
                    owner, 1, 0, x_value, y_value, 0x100, 0, 0);
                register s32 *count_view asm("r2") = count_slot;
                register s32 offset asm("r1") = *count_view;

                offset += 1;
                offset <<= 2;
                children = (char *)owner + 0xC;
                asm volatile("add %0, %1, %0"
                             : "+r"(offset) : "r"(children));
                *(void **)offset = created;

                {
                register u32 *rng asm("r1") = &D_03000010;
                register s32 random_scale asm("r1") =
                    ((u32)(func_080ECD5C(*rng) * 0x101) >> 15) + 0x200;
                register void *second_created asm("r0") = func_080D2660(
                    owner, 2, 0, x_value, y_value, 0x20, 0, random_scale, 0);
                register s32 *second_count_view asm("r1") = count_slot;
                register s32 count asm("r2") = *second_count_view;
                register s32 second_offset asm("r1") = count;

                second_offset += 16;
                second_offset <<= 2;
                asm volatile("add %0, %1" : "+r"(children) : "r"(second_offset));
                *(void **)children = second_created;
                count += 1;
                {
                    register s32 *count_store asm("r0") = count_slot;
                    *count_store = count;
                }
                }
            }
        }
        }
spawn_done:

        {
            register s32 *count_check asm("r1") = count_slot;
            initial_count = *count_check;
        }
        if (initial_count == 0xF) {
            u8 index = 0;
            if (owner->children[0] == 0) {
                do {
                    index = (u8)(index + 1);
                } while (index <= 0x1E && owner->children[index] == 0);
            }
            if (index == 0x1F) {
                func_08095114(owner);
            }
        }
    }
}
