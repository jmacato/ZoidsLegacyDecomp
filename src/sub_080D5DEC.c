#include "m2c_prelude.h"
M2C_UNK func_08095114(void *);                      /* extern */
u32 func_080D2450(void *, s32, u32, s16, s32, s32, u32, u32); /* extern */
void *func_080D2660(void *, s32, s32, s16, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_080D2790(s32);                         /* extern */
u32 func_080ECD5C(s32);                             /* extern */
s32 func_080ECD98(s32, s32);                        /* extern */
s32 func_080ECF78(u32, s32);                        /* extern */
M2C_UNK jtbl_080D5E14();                            /* static */

void sub_080D5DEC(void *arg0, M2C_UNK arg3) {
    s32 temp_r1;
    register s32 temp_r4 asm("r4");
    register u32 temp_r5_3 asm("r5");
    u32 temp_r0;
    u32 temp_r0_2;
    u32 temp_r0_3;
    u32 temp_r1_2;
    register u32 temp_r4_2 asm("r4");
    register s32 temp_r4_3 asm("r4");
    u32 temp_r5;
    u32 temp_r5_2;
    u8 var_r7;
    void *temp_r0_4;
    void *temp_r2;
    void *created;

    temp_r0 = M2C_FIELD(arg0, u32 *, 0x8C);
    switch (temp_r0) {                              /* irregular */
    case 0:
        M2C_FIELD(arg0, u32 *, 0xC) = func_080D2450(arg0, 0, 0U, M2C_FIELD(arg0, s16 *, 4), (s32) M2C_FIELD(arg0, s16 *, 8), 0x400, 0U, 0U);
        func_080D2790(0);
        M2C_FIELD(arg0, u32 *, 0x90) = 0U;
        M2C_FIELD(arg0, u32 *, 0x8C) = (u32) (M2C_FIELD(arg0, u32 *, 0x8C) + 1);
        /* fallthrough */
    case 1:
        temp_r0_2 = M2C_FIELD(arg0, u32 *, 0x90);
        if (temp_r0_2 <= 0x57U) {
            temp_r1 = 3 & temp_r0_2;
            if (temp_r1 == 0) {
                temp_r5 = func_080ECD5C(*(s32 *)0x03000010);
                temp_r4 = M2C_FIELD(arg0, s32 *, 8);
                func_080D2660(arg0, 1, 0, M2C_FIELD(arg0, s16 *, 4), (s32) (s16) (temp_r4 + (func_080ECF78(M2C_FIELD(arg0, u32 *, 0x90), 6) + (temp_r5 >> 0xE) + 0xFFFE)), 0x400, 0x80, 0x180, temp_r1);
            }
            M2C_FIELD(arg0, u32 *, 0x90) = (u32) (M2C_FIELD(arg0, u32 *, 0x90) + 1);
            return;
        }
        M2C_FIELD(arg0, u32 *, 0x90) = 0U;
        M2C_FIELD(arg0, u32 *, 0x8C) = (u32) (M2C_FIELD(arg0, u32 *, 0x8C) + 1);
    case 2:
        temp_r5_2 = M2C_FIELD(arg0, u32 *, 0xC);
        if (temp_r5_2 != 0) {
            return;
        }
        temp_r0_3 = M2C_FIELD(arg0, u32 *, 0x90);
        if (temp_r0_3 <= 0x1DU) {
            M2C_FIELD(arg0, u32 *, 0x90) = (u32) (temp_r0_3 + 1);
            return;
        }
        func_080D2790(1);
        M2C_FIELD(arg0, u32 *, 0x90) = temp_r5_2;
        M2C_FIELD(arg0, u32 *, 0x8C) = (u32) (M2C_FIELD(arg0, u32 *, 0x8C) + 1);
    case 3:
        {
        u32 *timer;
        register u32 *timer_init asm("r0") = (u32 *)((s32)arg0 + 0x90);
        register u32 count_init asm("r1") = *timer_init;
        asm volatile("" : "+r"(count_init));
        timer = timer_init;
        temp_r1_2 = count_init;
        if (temp_r1_2 <= 7U) {
            created = (void *)func_080D2450(arg0, 3, (u32) ((0 - temp_r1_2) | temp_r1_2) >> 0x1F, (s16) (M2C_FIELD(arg0, s32 *, 4) - (temp_r1_2 << 5)), (s32) M2C_FIELD(arg0, s16 *, 8), 0x400, 0U, 0U);
            temp_r4_2 = *timer;
            {
                register u32 child_offset asm("r1") = temp_r4_2;
                register char *children_init asm("r2") = arg0;

                child_offset <<= 2;
                children_init += 0xC;
                *(void **)(children_init + child_offset) = created;
                temp_r2 = children_init;
            }
            if (temp_r4_2 == 0) {
                M2C_FIELD(arg0, u32 *, 0x2C) = func_080D2450(arg0, 2, 0U, M2C_FIELD(arg0, s16 *, 4), (s32) M2C_FIELD(arg0, s16 *, 8), 0x400, temp_r4_2, temp_r4_2);
                var_r7 = 0;
                do {
                    temp_r5_3 = func_080ECD5C(*(s32 *)0x03000010);
                    temp_r4_3 = func_080ECD98(var_r7 << 5, 7);
                    temp_r4_3 += 0x6C;
                    temp_r4_3 += (u32)(temp_r5_3 * 9) >> 0xF;
                    temp_r4_3 = (u8)temp_r4_3;
                    temp_r0_4 = func_080D2660(arg0, 4, 0, M2C_FIELD(arg0, s16 *, 4), (s32) M2C_FIELD(arg0, s16 *, 8), 0x500, temp_r4_3, ((u32) (func_080ECD5C(*(s32 *)0x03000010) * 0x201) >> 0xF) + 0x200, 0);
                    {
                        register u32 child_offset asm("r1") = var_r7;

                        child_offset += 9;
                        child_offset <<= 2;
                        asm volatile("" : "+r"(child_offset));
                        child_offset += (u32)temp_r2;
                        *(void **)child_offset = temp_r0_4;
                    }
                    temp_r4_3 += 0x80;
                    *((u8 *)temp_r0_4 + 0x11) = temp_r4_3;
                    var_r7 += 1;
                } while ((u32) var_r7 <= 7U);
            }
            *timer = *timer + 1;
            return;
        }
        M2C_FIELD(arg0, u32 *, 0x8C) = (u32) (M2C_FIELD(arg0, u32 *, 0x8C) + 1);
        }
    case 4:
        var_r7 = 0;
        if (M2C_FIELD(arg0, u32 *, 0xC) == 0) {
            register char *children asm("r1") = arg0 + 0xC;
loop_24:
            var_r7 += 1;
            if ((u32) var_r7 <= 0x10U) {
                register u32 offset asm("r0") = var_r7;
                u32 address;

                offset <<= 2;
                address = (u32)children;
                address += offset;
                if (*(s32 *)address == 0) {
                    goto loop_24;
                }
            }
        }
        if (var_r7 == 0x11) {
            func_08095114(arg0);
        }
        return;
    }
}
