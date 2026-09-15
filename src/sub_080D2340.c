#include "m2c_prelude.h"

void func_0809AA64(u8 *, u8, u16, u16);

extern s32 D_02034874[];
extern s32 D_02034894[];
extern s32 D_020348B4[];
extern u16 D_020348D4[];

void sub_080D2340(s32 arg0)
{
    register s16 *entry asm("r4");
    u8 count;
    register u16 value asm("r1");

    {
        register s32 a28 asm("r0") = arg0 * 28;

        entry = (s16 *)(a28 + 0x087D233A);
    }
    count = 0;
    value = *entry;
    {
        register s32 s0 asm("r0") = *entry;

        if (s0 == -1) {
            goto pass2;
        }
    }
    {
        u8 *table = (u8 *)0x087AC9F8;
        s32 *first = (s32 *)0x0203486C;
        s32 *second = (s32 *)0x02034870;

loop_1:
        {
            s32 fv;
            register s32 sv asm("r3");
            register u8 *res asm("r1");
            register s32 packed asm("r2");
            register s32 upd asm("r0");

            func_0809AA64(table, value, *(u16 *)first, *(u16 *)second);
            {
                s32 *o0_base = D_02034874;
                s32 *o0 = o0_base + count;
                register s32 e0 asm("r0") = *entry;

                *o0 = e0;
            }
            {
                s32 *o1 = &D_02034894[count];

                fv = *first;
                *o1 = fv;
            }
            {
                s32 *o2 = &D_020348B4[count];

                sv = *second;
                *o2 = sv;
            }
            res = *(u8 **)(table + *entry * 8);
            packed = res[1];
            upd = res[2];
            upd <<= 8;
            packed |= upd;
            upd = res[3];
            upd <<= 16;
            packed |= upd;
            upd = fv + (packed >> 5);
            *first = upd;
            upd = sv + 1;
            *second = upd;
            entry++;
            count++;
            if (count <= 7) {
                value = *entry;
                {
                    register s32 s1 asm("r0") = *entry;

                    if (s1 != -1) {
                        goto loop_1;
                    }
                }
            }
        }
    }

pass2:
    {
        s16 *entry2;
        u16 value2;
        s32 neg;

        {
            register s32 a28_2 asm("r0") = arg0 * 28;
            register s32 entry2_base asm("r1") = 0x087D234A;

            asm volatile("" : "+r"(entry2_base));
            entry2 = (s16 *)(a28_2 + entry2_base);
        }
        count = 0;
        value2 = *entry2;
        {
            register s32 s2 asm("r0") = *entry2;

            neg = -1;
            if (s2 == neg) {
                goto done;
            }
        }
        {
            u16 *out = (u16 *)0x020348D4;

loop_2:
            out[count] = value2;
            entry2++;
            count++;
            if (count <= 7) {
                value2 = *entry2;
                {
                    register s32 s3 asm("r0") = *entry2;

                    if (s3 != neg) {
                        goto loop_2;
                    }
                }
            }
        }
    }
done:;
}
