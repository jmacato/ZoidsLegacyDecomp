#include "m2c_prelude.h"

M2C_UNK func_080951E8();
M2C_UNK func_08096FBC(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
M2C_UNK func_0809A1BC(s32, s32, M2C_UNK);
s16 func_0809D5F4(u8, s16, s16);
M2C_UNK func_0809D700();
s32 func_0809F818(s32);
M2C_UNK func_080A6148();
M2C_UNK func_080ECD34(s32, M2C_UNK);
M2C_UNK func_080ECD38(s32, s32);

extern u8 D_087C4434[];
extern s32 D_02032E88[];
extern s32 D_02032E90;
extern s32 D_02032E94;
extern s32 D_020314A0;
extern s16 D_0203249C[];
extern u16 D_020324A4[];
extern u8 D_020324B0;
extern u16 D_0300004C;
extern u8 D_03000054[];
extern u8 D_0202ECF4[];
extern u8 D_02021770;

void sub_0809D938(s32 arg0, s32 arg1, s32 arg2) {
    u8 *tbase;
    u8 *p49C;
    u8 *p054;
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 sp24;
    s32 sp28;
    s32 sp2C;
    s32 sp30;
    s32 sp34;
    s32 sp3C;
    s32 temp_r0_3;
    s32 temp_r4_2;
    s16 temp_r5;
    s16 var_r1;
    s16 var_r2;
    s32 temp_r0;
    s32 temp_r1;
    s32 temp_r1_2;
    s32 temp_r1_3;
    s32 temp_r1_4;
    s32 temp_r1_5;
    s32 temp_r2;
    s32 temp_r3;
    s32 temp_r4;
    s32 var_r0;
    s32 var_r3;
    register s32 hh asm("r8");
    register s32 m31 asm("r10");
    s32 var_r7;
    register s32 var_r9 asm("r9");
    u16 temp_r5_2;
    u32 temp_r0_2;
    u8 var_r7_2;

    sp18 = arg0;
    sp1C = arg1;
    sp20 = arg2;
    func_080951E8();
    p054 = D_03000054;
    func_08096FBC(3, 0, 0x100, 0xC0, 0x1C0, 3, 0xE, 0, 0x3E6, 0xF);
    tbase = D_087C4434;
    temp_r4 = arg0 << 5;
    { u8 *q4; q4 = tbase + 4; func_080ECD34(*(s32 *)(temp_r4 + q4), 0x06004000); }
    { u8 *q8; q8 = tbase + 8; func_0809A1BC(*(s32 *)(temp_r4 + q8), 0x05000000, 0x02002880); }
    if (sp18 == 0) {
        D_02032E88[0] = (s32) *(s32 *)(tbase + 0xC);
        D_02032E88[1] = sp18;
        D_02032E90 = *(s32 *)(tbase + 0x14);
        D_02032E94 = *(s32 *)(tbase + 0x18);
        if (D_0202ECF4[0x1E] != 0) {
            func_080A6148();
            var_r7 = 0;
        } else {
            D_020314A0 = sp18;
            var_r7 = 0;
        }
    } else {
        { u8 *qC; qC = tbase + 0xC; temp_r1 = *(s32 *)(temp_r4 + qC); }
        if (temp_r1 != 0) {
            func_080ECD38(temp_r1, 0x02032E98);
            D_02032E88[0] = 0x02032E98;
        } else {
            D_02032E88[0] = temp_r1;
        }
        { u8 *b2; u8 *q10; b2 = D_087C4434; temp_r1_2 = sp18 << 5; q10 = b2 + 0x10; temp_r2 = *(s32 *)(temp_r1_2 + q10); }
        var_r7 = temp_r1_2;
        if (temp_r2 != 0) {
            func_080ECD38(temp_r2, 0x02034E98);
            D_02032E88[1] = 0x02034E98;
        } else {
            D_02032E88[1] = temp_r2;
        }
        { u8 *b3; u8 *q14; u8 *q18; b3 = D_087C4434; q14 = b3 + 0x14; func_080ECD38(*(s32 *)(var_r7 + q14), 0x02036E98); q18 = b3 + 0x18; func_080ECD38(*(s32 *)(var_r7 + q18), 0x0203AE98); }
        D_02032E90 = 0x02036E98;
        D_02032E94 = 0x0203AE98;
        D_020314A0 = 0;
    }
    if ((sp18 == 0) || (sp18 == 0x40)) {
        D_0300004C = (u16) ((0xE000 & D_0300004C) | 0x1940);
        if (1 & D_020324B0) {
            func_080ECD34(0x08498FA0, 0x0600C000);
            func_080ECD34(0x08499A44, 0x06000800);
            D_0300004C = (u16) (D_0300004C | 0x200);
            *(s16 *)0x0400000A = 0x10E;
        }
        if (sp18 == 0) {
            func_080ECD34(0x08499C1C, 0x06001000);
            D_0300004C = (u16) (D_0300004C | 0x400);
            *(s16 *)0x0400000C = 0x207;
            if ((1 & D_020324B0) && ((func_0809F818(0) << 0x18) != 0) && (D_02021770 == 0)) {
                func_080ECD38(0x08499D38, 0x02032E98);
                D_02032E88[1] = 0x02032E98;
                func_080ECD38(0x0849A044, 0x02036E98);
                *(s16 *)0x0400000E = 0x1F0E;
                { u8 *d; d = D_03000054; *(s32 *)(d + 0x18) = sp1C; *(s32 *)(d + 0x1C) = sp20; }
                D_020324B0 = (u8) (D_020324B0 | 4);
            }
        }
        *(s16 *)0x04000008 = 7;
        func_0809D700();
    } else {
        temp_r1_3 = (0xE000 & D_0300004C) | 0x1840;
        D_0300004C = temp_r1_3;
        if (D_02032E88[0] != 0) {
            D_0300004C = temp_r1_3 | 0x100;
            *(s16 *)0x04000008 = 7;
        }
        if (D_02032E88[1] != 0) {
            D_0300004C |= 0x200;
            *(s16 *)0x0400000A = 0x106;
        }
        D_020324B0 = 0;
    }
    { u16 *d; u8 *w; d = D_020324A4; w = D_087C4434 + var_r7; d[0] = (u16) *(u16 *)w; d[1] = (u16) *(u16 *)(w + 2); }
    temp_r3 = sp1C + 0xFFFF8800;
    sp1C = temp_r3;
    sp20 += 0xFFFFB000;
    if (sp18 != 0) {
        if (temp_r3 < 0) {
            sp1C = 0;
        } else {
            temp_r0 = (D_020324A4[0] - 0x1E) << 0xB;
            if (sp1C > temp_r0) {
                sp1C = temp_r0;
            }
        }
        if (sp20 < 0) {
            var_r0 = 0;
            goto block_39;
        }
        var_r0 = (D_020324A4[1] - 0x14) << 0xB;
        if (sp20 > var_r0) {
block_39:
            sp20 = var_r0;
        }
    }
    p49C = (u8 *)D_0203249C;
    temp_r1_4 = sp1C >> 0xB;
    *(s16 *)(p49C + 4) = (s16) temp_r1_4;
    *(s16 *)(p49C + 0) = (s16) temp_r1_4;
    sp24 = (s32) (u16) temp_r1_4;
    temp_r1_5 = sp20 >> 0xB;
    *(s16 *)(p49C + 6) = (s16) temp_r1_5;
    *(s16 *)(p49C + 2) = (s16) temp_r1_5;
    sp28 = (s32) (u16) temp_r1_5;
    var_r7_2 = 0;
    do {
        { s32 c; c = D_02032E88[var_r7_2]; sp34 = var_r7_2 + 1;
        if (c != 0) {
            if ((sp18 != 0) || (var_r7_2 == 0)) {
                var_r9 = (var_r7_2 << 0xB) + 0x06000000;
            } else {
                var_r9 = 0x0600F800;
            }
            *(s32 *)(p054 + (var_r7_2 * 8)) = sp1C;
            *(s32 *)(p054 + (({ s32 ix; ix = (var_r7_2 * 2) + 1; ix; }) * 4)) = sp20;
            var_r2 = 0;
            { s32 t0; s32 t1; t0 = sp24 << 0x10; t1 = sp28 << 0x10; asm volatile("" : "+r"(var_r7_2)); sp34 = var_r7_2 + 1; sp2C = t0 >> 0x10; sp30 = t1 >> 0x10; }
            m31 = 0x1F;
            do {
                var_r1 = 0;
                sp3C = var_r2 << 0x10;
                temp_r0_3 = sp30 + (sp3C >> 0x10);
                hh = temp_r0_3 << 0x10;
                var_r3 = (temp_r0_3 & m31) << 6;
                do {
                    temp_r5 = var_r1;
                    temp_r4_2 = sp2C + temp_r5;
                    { u8 z; s32 a1; a1 = (s32) (s16) temp_r4_2; z = var_r7_2; asm volatile("" : "+r"(z));
                    *(s16 *)(var_r3 + (((temp_r4_2 & m31) * 2) + var_r9)) = func_0809D5F4(z, a1, (s16) (hh >> 0x10)); }
                    temp_r5_2 = temp_r5 + 1;
                    var_r1 = (s16) temp_r5_2;
                } while ((s32) (s16) temp_r5_2 <= 0x1E);
                temp_r0_2 = sp3C + 0x10000;
                var_r2 = (s16) (temp_r0_2 >> 0x10);
            } while ((s32) ((s32) temp_r0_2 >> 0x10) <= 0x14);
        }
        }
        var_r7_2 = (u8) sp34;
    } while ((u32) var_r7_2 <= 1U);
}
