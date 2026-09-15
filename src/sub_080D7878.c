#include "m2c_prelude.h"
extern void func_08095114(void *);
extern void func_080D12A0(s32, s32);
extern void *func_080D2450();
extern void *func_080D2660();
extern void func_080D2790(s32);
extern u32 func_080ECD5C(u32);
extern s32 func_080ECD98(s32, s32);
extern u8 func_080ECF78(u8, s32);
extern s16 func_08092A90(s16);
extern u32 D_03000010;

void sub_080D7878(void *arg0) {
    char *owner = arg0;
    register s32 *p8C asm("r5") = (s32 *)(owner + 0x8C);
    u32 state = *p8C;

    switch (state) {
    case 0:
        {
            register s32 *p90 asm("r4") = (s32 *)(owner + 0x90);
            void *created;
            register s32 x asm("r3");
            register s32 *y_ptr asm("r0");
            register s32 y asm("r0");

            x = *p90;
            x -= 0x100;
            x = (s16)x;
            y_ptr = (s32 *)(owner + 0x94);
            y = *y_ptr;
            y -= 0x80;
            y = (s16)y;
            created = func_080D2450(owner, 0, 0, x,
                y, 0x20, 0x080D6E6D, 1);
            *(void **)(owner + 0xC) = created;
            *(void **)((char *)created + 0x28) = owner;
            *(s32 *)((char *)created + 0x2C) = 0;
            *(s32 *)((char *)created + 0x30) = *p90;
            func_080D2790(0);
            *p8C += 1;
            return;
        }
        return;
    case 1:
        if ((*(s32 *)*(void **)(owner + 0xC) & 0x20000) != 0) {
            u32 yu;
            s32 *p98;
            s32 *addr = (s32 *)(owner + 0x98);
            u32 counter = *addr;

            asm volatile("" : "+r"(addr));
            p98 = addr;

            if (counter <= 12) {
                s32 low2 = 3;
                low2 &= counter;
                if (low2 == 0) {
                    u8 group = counter >> 2;
                    s32 sin;
                    s32 q;
                    u8 q8;
                    s32 grp12;
                    u32 rand;
                    s32 amp;
                    u16 ampu;
                    s32 amps;
                    s32 x;
                    u16 xu;
                    s32 y;
                    s32 *children;
                    s32 g4;
                    void *created;
                    void *spawned;
                    s32 off;
                    u8 i;

                    sin = func_08092A90((s16)func_080ECD98(group << 7, 3));
                    if (sin < 0) {
                        sin += 15;
                    }
                    q = sin >> 4;
                    q8 = q;
                    grp12 = group << 1;
                    grp12 += group;
                    grp12 <<= 2;
                    rand = func_080ECD5C(D_03000010);
                    amp = q8 * func_080ECF78(group, 3);
                    amp >>= 1;
                    amp -= (u8)q >> 1;
                    amp -= 4;
                    amp += (rand * 9) >> 15;
                    ampu = amp;
                    x = *(s32 *)(owner + 0x90);
                    x += func_080ECD98(grp12 * 2, 3);
                    amps = (s16)ampu;
                    x += func_080ECD98(amps, 3);
                    xu = x;
                    y = *(s32 *)(owner + 0x94);
                    y += func_080ECD98(grp12, 3);
                    amps *= 2;
                    y += func_080ECD98(amps, 3);
                    {
                        s32 ysh = y << 16;
                        s32 xs = (s16)xu;

                        yu = (u32)ysh >> 16;
                        created = func_080D2450(owner, 2, 0, xs,
                            ysh >> 16, low2, low2, low2);
                    }
                    {
                        s32 g4tmp;
                        s32 *ctmp;
                        s32 off;

                        g4tmp = group * 4;
                        off = g4tmp + group + 1;
                        off <<= 2;
                        ctmp = (s32 *)(owner + 0xC);
                        *(s32 *)((char *)ctmp + off) = (s32)created;
                        i = 0;
                        g4 = g4tmp;
                        children = ctmp;
                    }
                    {
                        u32 *rng = &D_03000010;
                        asm volatile("" : "+r"(rng));
                        asm volatile("" :: "r"(i));
                        do {
                            u32 r = func_080ECD5C(*rng);
                            s32 a = func_080ECD98(i << 6, 3);
                            s32 p = (r * 9) >> 15;
                            s32 off;

                            p -= 0x17;
                            a += p;
                            spawned = func_080D2660(
                                owner, 3, 0, (s16)xu,
                                ({ register s32 t2 asm("r3") = yu;
                                   register s32 t5 asm("r0") = t2 << 16;
                                   t5 >>= 16; t5; }),
                                0x500, a,
                                ((func_080ECD5C(*rng) * 0x101) >> 15) + 0x100, 0);
                            off = i + (g4 + group) + 2;
                            off <<= 2;
                            *(s32 *)((char *)children + off) = (s32)spawned;
                            i += 1;
                        } while (i <= 3);
                    }
                }
                if (*p98 == 0) {
                    func_080D12A0(6, 0);
                    func_080D2790(1);
                }
                *p98 += 1;
            } else {
                *p8C = 2;
            }
            return;
        }
        return;
    case 2:
        {
            register s32 index asm("r7") = 0x18;
            register char *oc asm("r2") = (char *)owner;
            register void *child asm("r1") = ({ asm volatile("" : "+r"(oc)); *(void **)(oc + 0xC); });
            u32 child_count;
            u32 bound;
            s32 off;

            child_count = *(u32 *)((char *)child + 0x2C);
            bound = (child_count >> 1) + 0x19;
            if ((u32)index < bound && *(s32 *)(owner + 0x6C) == 0) {
                u32 scan_bound = bound;
                s32 *children = (s32 *)(owner + 0xC);
                do {
                    register s32 next asm("r0") = index + 1;
                    next <<= 24;
                    next = (u32)next >> 24;
                    index = next;
                } while ((u32)index < scan_bound &&
                    (off = index << 2,
                     *(s32 *)((char *)children + off)) == 0);
            }
            if (index == ((*(volatile u32 *)((char *)child + 0x2C) >> 1) + 0x19)) {
                index = 1;
                if (*(s32 *)(owner + 0x10) == 0) {
                    s32 *children = (s32 *)(owner + 0xC);
                    do {
                        register s32 next asm("r0") = index + 1;
                        next <<= 24;
                        next = (u32)next >> 24;
                        index = next;
                    } while ((u32)index <= 0x14 &&
                        (off = index << 2,
                         *(s32 *)((char *)children + off)) == 0);
                }
                if (index == 0x15) {
                    func_08095114(owner);
                }
            }
        }
        return;
    }
    return;
}
