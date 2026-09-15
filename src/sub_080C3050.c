#include "m2c_prelude.h"
#define NULL ((void *)0)

M2C_UNK func_08093AE8(M2C_UNK, s32);                /* extern */
void *func_08094374(); /* extern */
M2C_UNK func_08094554();                            /* extern */
M2C_UNK func_08096308(s32, s32);                    /* extern */
s32 func_0809669C();                                /* extern */
M2C_UNK func_080BAF2C(); /* extern */
M2C_UNK func_080BB224(s32, u8, s32, s32);           /* extern */
s32 func_080BB654();                                /* extern */
M2C_UNK func_080C9F00(u8, s32);                     /* extern */
s32 func_080E9D88(s32, void *);                      /* extern */
u8 func_080ECF78(void *, s32);                      /* extern */
M2C_UNK func_080ED17C(s32);                         /* extern */

struct Rec { u8 f0; u8 f1; u8 pad[0x36]; u8 f38; };
extern u8 D_02032F7C[];
extern s16 D_03000050[];
void sub_080C3050(u8 arg0) {
    void *sp14[6];
    s32 sp04;
    s32 sp08;
    s32 zero;
    s32 *temp_r2_3;
    s32 *temp_r2_6;
    s32 *var_r2;
    s32 loop48_r018;
    s32 loop48_base;
    s32 loop59_r018;
    s32 loop59_base;
    s32 loop64_r018;
    s32 loop64_base;
    s16 *addr050;
    s32 temp_r0_2;
    s32 base1;
    s32 idx1;
    s32 loop36_base;
    s32 temp_r0_4;
    s32 temp_r1_2;
    void *sysbase;
    register s32 temp_r2_4 asm("r2");
    s32 temp_r2_5;
    s32 tt;
    register s32 tbl asm("r3");
    register s32 tb2 asm("r1");
    register s32 idx2 asm("r8");
    register u8 b0 asm("r4");
    u8 b1;
    u8 b2;
    s32 temp_r4;
    s32 var_r0;
    register s32 var_r0_3 asm("r0");
    s32 var_r0_4;
    s32 var_r4;
    s32 var_r4_2;
    u8 temp_r0_3;
    register s32 temp_r4_2 asm("r4");
    u8 temp_r6;
    u8 var_r4_3;
    u8 var_r5_3;
    void *temp_r0;
    register void *temp_r1 asm("r1");
    void *temp_r1_3;
    void *temp_r1_4;
    register void *temp_r1_5 asm("r1");
    void *temp_r2;
    void *temp_r2_2;
    void *temp_r2_7;
    void *temp_r2_8;
    void *var_fnaddr;
    void *var_r0_2;
    void *var_r4_4;
    void *var_r4_5;
    void *var_r5;
    void *var_r5_2;
    void *var_r5_4;

    temp_r6 = arg0;
    func_080C9F00(temp_r6, 3);
    var_r5 = NULL;
loop_1:
    asm("" :: "r"(var_r5));
    asm("" :: "r"(var_r5));
    asm("" :: "r"(var_r5));
    asm("" :: "r"(var_r5));
    asm("" :: "r"(var_r5));
    asm("" :: "r"(var_r5));
    asm("" :: "r"(var_r5));
    asm("" :: "r"(var_r5));
    asm("" :: "r"(var_r5));
    asm("" :: "r"(var_r5));
    asm("" :: "r"(var_r5));
    asm("" :: "r"(var_r5));
    asm("" :: "r"(var_r5));
    asm("" :: "r"(var_r5));
    asm("" :: "r"(var_r5));
    asm("" :: "r"(var_r5));
    asm("" :: "r"(var_r5));
    asm("" :: "r"(var_r5));
    asm("" :: "r"(var_r5));
    asm("" :: "r"(var_r5));
    if ((func_080E9D88(temp_r6, var_r5) << 0x18) != 0) {
        goto block_3;
    }
    goto block_17;
block_3:
    if (D_02032F7C[(s32) var_r5] == 0xFF) {
        goto block_5;
    }
    goto block_17;
block_5:
    temp_r4 = (s32) var_r5 * 4;
    temp_r2 = (void *) (temp_r4 + (s32) var_r5);
    temp_r2 = (void *) ((s32) temp_r2 * 8);
    asm("" : "+r"(temp_r2));
    temp_r2 = (void *) ((s32) temp_r2 - (s32) var_r5);
    temp_r2 = (void *) ((s32) temp_r2 * 0x10);
    asm("" : "+r"(temp_r2));
    temp_r2 = (void *) ((s32) temp_r2 + (temp_r6 * 0x1380));
    temp_r2 = (void *) ((s32) temp_r2 + 0x02034B4C);
    asm("" : "+r"(temp_r2));
    func_080BAF2C(((struct Rec *)temp_r2)->f0, ((struct Rec *)temp_r2)->f1, ((struct Rec *)temp_r2)->f38, temp_r6, var_r5, (zero = 0), zero);
    base1 = 0x02032E8C;
    asm("" : "+r"(base1));
    idx1 = temp_r4 + (temp_r6 * 0x18);
    temp_r2_3 = *(s32 **)(idx1 + base1);
    *temp_r2_3 |= 0x80000;
    var_fnaddr = (void *)0x087AD1D0;
    asm("" : "+r"(var_fnaddr));
    asm("" :: "r"(temp_r4));
    asm("" :: "r"(temp_r4));
    asm("" :: "r"(temp_r4));
    asm("" :: "r"(temp_r4));
    temp_r0 = func_08094374(var_fnaddr, 2, 0, 0, zero,
                           (temp_r6 == 0 ? 0x180 : 0),
                           (temp_r6 != 0) ? 0 : 6,
                           ({ register s32 v asm("r4");
                              if (temp_r6 == 0) {
                                  v = 3;
                                  v -= func_080ECF78(var_r5, 3);
                                  v <<= 6;
                              } else {
                                  v = ((u32) (func_080ECF78(var_r5, 3) << 0x18) >> 0x12) + 0x40;
                              }
                              v |= 0x80220;
                              if (temp_r6 != 0) {
                                  v |= 0x8000;
                              }
                              v; }),
                           0x080BADD5);
    sp14[(s32) var_r5] = temp_r0;
    temp_r1 = (void *) (temp_r6 * 6);
    temp_r1 = (void *) ((s32) temp_r1 + (s32) var_r5);
    temp_r2_4 = (s32) temp_r1 * 12;
    asm("" :: "r"(temp_r1));
    tbl = 0x087A2790;
    M2C_FIELD(temp_r0, s32 *, 0x28) = (s32) M2C_FIELD(temp_r2_4, s32 *, tbl);
    tb2 = tbl;
    asm("" : "+r"(tb2));
    tb2 += 4;
    M2C_FIELD(temp_r0, s32 *, 0x2C) = (s32) (M2C_FIELD(temp_r2_4, s32 *, tb2) + 0xFFFFE000);
    M2C_FIELD(temp_r0, s32 *, 0x30) = (s32) M2C_FIELD(temp_r2_4, s32 *, 0x087A2798);
    goto block_18;
block_17:
    sp14[(s32) var_r5] = 0;
block_18:
    var_r5 = (void *) (u8) (var_r5 + 1);
    if ((u32) var_r5 > 5U) {
        goto block_20;
    }
    goto loop_1;
block_20:
    func_08093AE8(0x0202F094, 1);
    *(u8 *)0x03000074 |= 1;
    func_08096308(1, 8);
    goto loop_22;
block_21:
    func_080ED17C(1);
loop_22:
    if ((func_0809669C() << 0x18) == 0) {
        goto block_21;
    }
    func_080BB224(2, temp_r6, 0, 0);
    goto loop_30;
block_24:
    if (*(u8 *)0x02030664 != 1) {
        goto block_29;
    }
    sysbase = (void *)0x030033C4;
    temp_r1_2 = M2C_FIELD(sysbase, s32 *, 0x18);
    if (temp_r1_2 <= 0x58) {
        goto block_29;
    }
    var_r0 = 0x58 - temp_r1_2;
    if (var_r0 >= 0) {
        goto block_28;
    }
    var_r0 += 3;
block_28:
    M2C_FIELD(sysbase, s32 *, 0x18) = (s32) (temp_r1_2 + (var_r0 >> 2));
block_29:
    func_080ED17C(1);
loop_30:
    if ((func_080BB654() << 0x18) == 0) {
        goto block_24;
    }
    var_r4_3 = 0;
loop_32:
    if (((s32) sp14[var_r4_3]) == 0) {
        goto block_34;
    }
    func_08094554();
block_34:
    var_r4_3 += 1;
    if ((u32) var_r4_3 <= 5U) {
        goto loop_32;
    }
    asm("" : "+r"(temp_r6));
    var_r5_2 = NULL;
    loop36_base = 0x02032E8C;
    asm("" : "+r"(loop36_base));
    temp_r0_2 = temp_r6 * 0x18;
loop_36:
    if ((func_080E9D88(temp_r6, var_r5_2) << 0x18) == 0) {
        goto block_46;
    }
    temp_r0_3 = D_02032F7C[(s32) var_r5_2];
    if (temp_r0_3 != 0x80) {
        goto block_43;
    }
    temp_r2_5 = (s32) var_r5_2 * 4;
    tt = temp_r2_5 + (s32) var_r5_2;
    temp_r1_3 = (((tt * 8) - (s32) var_r5_2) * 0x10) + (temp_r6 * 0x1380);
    temp_r1_4 = temp_r1_3 + 0x02034B4C;
    asm("" : "+r"(temp_r1_4));
    b0 = ((struct Rec *)temp_r1_4)->f0;
    b1 = ((struct Rec *)temp_r1_4)->f1;
    b2 = ((struct Rec *)temp_r1_4)->f38;
    func_080BAF2C(b0, b1, b2, temp_r6, var_r5_2,
                  ((idx2 = temp_r2_5, temp_r6) == 0) ? (void *)0x2000 : (void *)0xFFFFE000, 0);
    var_r2 = M2C_FIELD((idx2 + temp_r0_2), s32 **, loop36_base);
    var_r0_3 = *var_r2 | 0x400;
    goto block_45;
block_43:
    if (temp_r0_3 != 0xFF) {
        goto block_46;
    }
    var_r2 = M2C_FIELD((((s32) var_r5_2 * 4) + temp_r0_2), s32 **, loop36_base);
    var_r0_3 = *var_r2 & 0xFFF7FFFF;
block_45:
    *var_r2 = var_r0_3;
block_46:
    var_r5_2 = (void *) (u8) (var_r5_2 + 1);
    if ((u32) var_r5_2 <= 5U) {
        goto loop_36;
    }
    *(s16 *)0x0300004E = 0x540;
    *(s16 *)D_03000050 = 0x1000;
    var_r5_3 = 0;
    loop48_base = 0x02032E8C;
    asm("" : "+r"(loop48_base));
    loop48_r018 = temp_r6 * 0x18;
    addr050 = (s16 *)D_03000050;
loop_48:
    var_r4_4 = NULL;
loop_49:
    if ((func_080E9D88(temp_r6, var_r4_4) << 0x18) == 0) {
        goto block_56;
    }
    if (D_02032F7C[(s32) var_r4_4] != 0x80) {
        goto block_56;
    }
    temp_r1_5 = M2C_FIELD((((s32) var_r4_4 * 4) + loop48_r018), void **, loop48_base);
    temp_r0_4 = M2C_FIELD(temp_r1_5, s32 *, 0x28);
    if (temp_r6 != 0) {
        goto block_54;
    }
    var_r0_4 = temp_r0_4 + 0xFFFFFE00;
    goto block_55;
block_54:
    var_r0_4 = temp_r0_4 + 0x200;
block_55:
    M2C_FIELD(temp_r1_5, s32 *, 0x28) = var_r0_4;
block_56:
    var_r4_4 = (void *) (u8) (var_r4_4 + 1);
    if ((u32) var_r4_4 <= 5U) {
        goto loop_49;
    }
    *addr050 = ((0x10 - var_r5_3) << 8) | var_r5_3;
    func_080ED17C(1);
    var_r5_3 += 1;
    if ((u32) var_r5_3 <= 0xFU) {
        goto loop_48;
    }
    *(u16 *)0x0300004E = 0;
    var_r4_5 = NULL;
    asm("" : "+r"(temp_r6));
    loop59_base = 0x02032E8C;
    loop59_r018 = temp_r6 * 0x18;
loop_59:
    if ((func_080E9D88(temp_r6, var_r4_5) << 0x18) == 0) {
        goto block_62;
    }
    if (D_02032F7C[(s32) var_r4_5] != 0x80) {
        goto block_62;
    }
    temp_r2_6 = M2C_FIELD((((s32) var_r4_5 * 4) + loop59_r018), s32 **, loop59_base);
    *temp_r2_6 &= 0xFFFFFBFF;
block_62:
    var_r4_5 = (void *) (u8) (var_r4_5 + 1);
    if ((u32) var_r4_5 <= 5U) {
        goto loop_59;
    }
    var_r5_4 = NULL;
    temp_r4_2 = temp_r6;
    temp_r4_2 ^= 1;
    loop64_base = 0x02034B4C;
    loop64_r018 = temp_r4_2 * 0x1380;
loop_64:
    if ((func_080E9D88(temp_r4_2, var_r5_4) << 0x18) == 0) {
        goto block_66;
    }
    temp_r2_7 = ((((s32) var_r5_4 * 5 * 8) - (s32) var_r5_4) * 0x10) + loop64_r018;
    temp_r2_8 = temp_r2_7 + loop64_base;
    asm("" : "+r"(temp_r2_8));
    func_080BAF2C(((struct Rec *)temp_r2_8)->f0, ((struct Rec *)temp_r2_8)->f1, ((struct Rec *)temp_r2_8)->f38, temp_r4_2, var_r5_4, 0, 0);
block_66:
    var_r5_4 = (void *) (u8) (var_r5_4 + 1);
    if ((u32) var_r5_4 <= 5U) {
        goto loop_64;
    }
    return;
}
