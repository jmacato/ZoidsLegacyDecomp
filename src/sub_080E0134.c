#include "m2c_prelude.h"

extern void func_08095114(void *);
extern void *func_080D2450();
extern void *func_080D2660();
extern void func_080D2790(s32);
extern u32 func_080ECD5C(u32);
extern s32 D_02034034;
extern u32 D_03000010;

void sub_080E0134(void *arg0)
{
    register char *owner asm("r6") = arg0;
    register s32 *state_slot asm("r4") = (s32 *)(owner + 0x8C);
    register u32 state asm("r0") = *state_slot;

    asm volatile("" ::: "r7");

    switch (state) {
    case 0: {
        register s32 scroll asm("r0") = D_02034034;
        register s32 x asm("r3");

        if (scroll < 0) {
            scroll += 0xFF;
        }
        scroll >>= 8;
        x = 0x80;
        x -= scroll;
        *(void **)(owner + 0xC) = func_080D2450(owner, 0, 0, (s16)x,
            8, 0x400, 0, 0);
        func_080D2790(0);
        *state_slot = *state_slot + 1;
        break;
    }
    case 1: {
        register u32 index asm("r1") = 1;
        register char *children asm("r2") = owner + 0xC;
        register u32 *rng asm("r3") = &D_03000010;
        u32 *rng_spill;
        s32 *slot;
        register s32 zero asm("r4");

        asm volatile("" : "=m"(rng_spill));

phase1_loop:
            slot = (s32 *)(children + (index << 2));
            zero = *slot;
            if (zero == 0) {
                register u32 angle_index asm("r5");
                register u32 random asm("r0");
                register u32 angle_raw asm("r1");
                register s32 priority asm("r1");
                register s32 scroll asm("r0");
                register u32 table asm("r0");
                register u32 table_value asm("r0");
                register s32 x_base asm("r2");
                register s32 x asm("r3");
                register s32 y asm("r0");
                register u32 rng_value asm("r0") = *rng;

                rng_spill = rng;
                random = func_080ECD5C(rng_value);
                angle_raw = random << 4;
                angle_raw += random;
                angle_raw >>= 15;
                angle_raw <<= 24;
                angle_raw >>= 24;
                angle_index = angle_raw;
                asm volatile("" : "+r"(angle_raw));
                rng = rng_spill;
                random = func_080ECD5C(*rng);
                priority = (u32)(random * 0x101) >> 15;
                priority += 0x200;
                table = 0x087A2D08;
                asm volatile("add %0, %1, %0"
                    : "+r"(table) : "r"(angle_index));
                table_value = *(u8 *)table;
                x_base = table_value;
                asm volatile("" : "+r"(table_value));
                x_base += 0x80;
                scroll = D_02034034;
                if (scroll < 0) {
                    scroll += 0xFF;
                }
                x = scroll >> 8;
                x = x_base - x;
                x = (s16)x;
                asm volatile("" : "+r"(x));
                y = angle_index;
                y += 0x10;
                *slot = (s32)func_080D2660(owner, 1, 0, x,
                    y, 0x500, zero, priority, zero);
                goto phase1_done;
            }
            {
                register u32 next asm("r0") = index + 1;
                next <<= 24;
                index = next >> 24;
            }
            if (index <= 0x1F) {
                goto phase1_loop;
            }

phase1_done:
        {
            register void *child asm("r1") = *(void **)(owner + 0xC);
            if (child == 0) {
                register void *created asm("r0");
                register s32 x_offset asm("r2") = 4;
                register s32 x asm("r3");

                asm volatile("ldrsh %0, [%1, %2]"
                    : "=r"(x) : "r"(owner), "r"(x_offset));
                created = func_080D2450(owner, 2, 0, x,
                    *(s16 *)(owner + 8), 0x420, 0x080D2529, child);
                *(void **)(owner + 0xC) = created;
                *(s32 *)((char *)created + 0x28) = 0x10;
                func_080D2790(1);
                {
                    register s32 *phase1_state asm("r1") =
                        (s32 *)(owner + 0x8C);
                    *phase1_state = *phase1_state + 1;
                }
            }
        }
        break;
    }
    case 2: {
        register u32 index asm("r1") = 0;
        if (*(void **)(owner + 0xC) == 0) {
            register char *children asm("r2") = owner + 0xC;
            do {
                register u32 next asm("r0") = index + 1;
                next <<= 24;
                index = next >> 24;
            } while ((u32)index <= 0x1F &&
                *(s32 *)(children + (index << 2)) == 0);
        }
        if (index == 0x20) {
            func_08095114(owner);
        }
        break;
    }
    }
}
