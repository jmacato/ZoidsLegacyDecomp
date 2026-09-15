#include "m2c_prelude.h"
extern s16 D_02033F90[];
extern s16 D_02033F74[];
extern void *D_02033F58[];
extern s8 D_02033FAC[];

void sub_080CC400(u8 arg0, s16 arg1, s16 arg2) {
    register s32 temp_r4 asm("r4");
    register s32 a90 asm("r3");
    register void * volatile *p58 asm("r2");
    register s16 *d asm("r5");
    s8 zero;
    a90 = (s32)D_02033F90;
    temp_r4 = arg0 * 4;
    d = (s16 *)(temp_r4 + a90);
    zero = 0;
    *d = arg1;
    a90 += 2;
    *(s16 *)(temp_r4 + a90) = arg2;
    *(u16 *)(temp_r4 + (s32)D_02033F74) =
        *(u16 *)((s8 *)*(p58 = (void * volatile *)(temp_r4 + (s32)D_02033F58)) + 4);
    *(u16 *)(temp_r4 + ((s32)D_02033F74 + 2)) =
        *(u16 *)((s8 *)*p58 + 6);
    *(s8 *)(arg0 + (s32)D_02033FAC) = zero;
}
