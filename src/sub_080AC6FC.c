#include "m2c_prelude.h"
extern void func_80ED128(void *, s32);
extern u8 func_8098B58(void *);
extern void func_8099F5C(void *, void *);
extern void func_8098284(u8, s32, s32, void *);
extern void func_80988C8(u8, void *);
extern u8 D_0203246B;
extern u8 D_02032412[];
extern s32 D_087EEE60[];
extern u8 D_020217FE[];
void sub_080AC6FC(u8 arg0) {
    u8 i;
    u8 n;
    u8 species_index;
    i = 0;
    if (i < D_0203246B) {
        register void *base asm("r6") = (void *)0x02030564;
        register s32 *table asm("r10") = D_087EEE60;
        register void *buffer asm("r8");
        {
            register void *buffer_load asm("r1") = (void *)0x020305E4;
            __asm__ volatile ("" : "+r" (buffer_load));
            buffer = buffer_load;
        }
        do {
            func_80ED128(base, table[D_02032412[i]]);
            n = func_8098B58(base);
            if (n <= 9) {
                do { func_8099F5C((void *)0x02030564, (void *)0x081061C4); n++; } while (n <= 9);
            }
            func_8099F5C(base, (void *)0x081061C8);
            species_index = D_02032412[i];
            func_8098284(D_020217FE[species_index], 2, 2, buffer);
            func_8099F5C(base, buffer);
            func_80988C8(arg0, base);
            i++;
        } while (i < D_0203246B);
    }
}
