#include "m2c_prelude.h"
extern s16 func_08092A90(s16);
extern void func_08095114(void *);
extern void func_080D12A0(s32, s32);
extern void *func_080D2450();
extern s32 func_080D2754(void *, s32, s32);
extern void func_080D2790(s32);
extern u32 func_080ECD5C(u32);
extern s32 func_080ECD98(s32, s32);
extern s32 func_080ECF78(s32, s32);
extern u32 D_03000010;

void sub_080D3B00(void *arg0) {
    char *owner = arg0;
    register s32 *state_slot asm("r4") = (s32 *)(owner + 0x8C);

    if (*state_slot == 0) {
        void *created = func_080D2450(owner, 0, 0,
            (s16)(*(s32 *)(owner + 0x90) - 0x100),
            *(s16 *)(owner + 0x94), 0x110, 0x080D2529, 1);
        *(void **)(owner + 0xC) = created;
        *(s32 *)((char *)created + 0x28) = 0x10;
        func_080D2790(0);
        *state_slot = *state_slot + 1;
    }

    {
        register u32 current_state asm("r0") = *state_slot;
    if (current_state <= 7) {
        if (current_state == 1 &&
                (func_080D2754(*(void **)(owner + 0xC),
                    *(s32 *)(owner + 0x90) - 0x50,
                    *(s32 *)(owner + 0x94)) << 24) != 0) {
            func_080D12A0(6, 0);
            func_080D2790(1);
            *state_slot = *state_slot + 1;
        }
        {
            s32 *saved_state;
            register s32 *state_view asm("r0") = (s32 *)(owner + 0x8C);
            register u32 current asm("r0");
            asm volatile("" : "=m"(saved_state));
            saved_state = state_view;
            current = *state_view;

            if (current > 1) {
                register s32 step asm("sl") = (u8)(current - 2);
                register s32 scaled asm("r6");
                register s32 scale_byte asm("r9");
                register s32 x_value asm("r5");
                register s32 random asm("r8");
                register s32 y_value asm("r4");
                register s32 phase asm("r0");
                s32 trig;
                void *created;

                trig = func_08092A90((s16)func_080ECD98(step << 7, 5));
                if (trig < 0) {
                    trig += 0xF;
                }
                scaled = trig >> 4;
                scaled <<= 24;
                {
                    register s32 scale_init asm("r1") =
                        (u32)scaled >> 24;
                    asm volatile("" : "+r"(scale_init));
                    scale_byte = scale_init;
                }
                x_value = *(s32 *)(owner + 0x90);
                x_value += step << 3;
                x_value = (u16)x_value;
                random = func_080ECD5C(D_03000010);
                y_value = *(s32 *)(owner + 0x94);
                phase = (u8)func_080ECF78(step, 3);
                phase *= scale_byte;
                asm volatile("" : "+r"(phase));
                phase >>= 1;
                y_value += phase;
                y_value -= (u32)scaled >> 25;
                {
                    register s32 perturb asm("r0");
                    register s32 random_view asm("r1") = random;
                    asm volatile("" : "+r"(random_view));
                    perturb = random_view << 3;
                    asm volatile("add %0, %1"
                                 : "+r"(perturb) : "r"(random));
                    perturb = (u32)perturb >> 15;
                    perturb += 0xFFFC;
                    y_value += perturb;
                }
                x_value = (s16)x_value;
                y_value = (s16)y_value;
                created = func_080D2450(owner, 1, 0,
                    x_value, y_value, 0, 0, 0);
                {
                    register s32 offset asm("r2") = step + 1;
                    register char *slot asm("r1");
                    asm volatile("lsl %0, %0, #2" : "+r"(offset));
                    slot = owner + 0xC;
                    asm volatile("add %0, %1" : "+r"(slot) : "r"(offset));
                    *(void **)slot = created;
                }
                {
                    register s32 *saved_view asm("r1") = saved_state;
                    register s32 saved_value asm("r0");
                    asm volatile(".short 0x6808, 0x3001, 0x6008"
                                 : "=r"(saved_value)
                                 : "r"(saved_view) : "memory");
                }
            }
        }
    } else {
        u8 index = 0;
        if (*(s32 *)(owner + 0xC) == 0) {
            register char *children asm("r2") = owner + 0xC;
            do {
                index = (u8)(index + 1);
            } while (index <= 6 &&
                *(s32 *)(children + (index << 2)) == 0);
        }
        if (index == 7) {
            func_08095114(owner);
        }
    }
    }
}
