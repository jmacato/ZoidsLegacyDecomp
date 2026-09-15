#include "m2c_prelude.h"
#define NULL ((void *)0)

M2C_UNK func_08092E84(s32);                         /* extern */
s32 func_08094484(M2C_UNK, M2C_UNK, s32, s16, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_08094554(s32);                         /* extern */
M2C_UNK func_080972C8();                            /* extern */
M2C_UNK func_08097980(u16);                         /* extern */
M2C_UNK func_08097B2C(s32, u8, M2C_UNK *);          /* extern */
M2C_UNK func_08097CEC(u8, u8, M2C_UNK *);           /* extern */
M2C_UNK func_080ED17C(s32);                         /* extern */
u8 *sub_08097DA8(void *arg0, u8 *arg1) {
    M2C_UNK sp14;
    s32 sp18;
    s32 temp_r2;
    s32 temp_r5_3;
    s32 temp_r1_4;
    register s32 var_r2 asm("r2"); /*LOCK*/
    s32 var_r2_2;
    s32 vsl2;
    s32 var_r6;
    register s32 var_r6_2 asm("r6");
    s32 var_r7;
    s8 *temp_r5;
    s8 *temp_r5_2;
    u16 temp_r0_7;
    u16 temp_r2_2;
    u32 temp_r0_2;
    u32 temp_r0_3;
    u32 temp_r0_4;
    u32 temp_r0_6;
    u32 temp_r1;
    u32 temp_r1_2;
    u32 temp_r1_3;
    u32 temp_r1_5;
    u32 var_r1;
    register u32 var_sl asm("sl");
    u8 *var_r8;
    s32 temp_r0;
    u8 temp_r0_5;
    s32 temp_r3;
    u8 var_r0;
    s8 *temp_r5_4;
    s32 pa;
    u8 *tC;
    register s32 zz asm("r6");
    s32 qb;
    s32 rhsv;
    s8 *bp2;
    s32 w8;
    s32 tA;
    s32 tB;
    s32 *pA890;
    s32 *pA890b;
    s32 rv;
    u32 zr;
    tC = (u8 *)0x02021774;
    tA = 0x080ED620;
    tB = 0x080ED648;
    var_r8 = arg1;
    var_r0 = *arg1;
    if (var_r0 == 0) {
    } else {
loop_2:
        if ((u32) var_r0 <= 0x1FU) {
            temp_r0 = M2C_FIELD(var_r8, u8 *, 0);
            switch (temp_r0) {                      /* irregular */
            case 1:
                M2C_FIELD(arg0, u8 *, 0x12) = (u8) M2C_FIELD(var_r8, u8 *, 1);
                var_r8 += 2;
                break;
            case 2:
                M2C_FIELD(arg0, s16 *, 0xC) = (s16) M2C_FIELD(var_r8, u8 *, 1);
                M2C_FIELD(arg0, u16 *, 0xE) = (u16) M2C_FIELD(var_r8, u8 *, 2);
                var_r2 = 3;
                asm("" : "+r"(var_r2));
                var_r8 += var_r2;
                goto loop_bottom;
            case 3:
                sub_08097DA8(arg0, tC);
                { register s32 k1 asm("r3"); k1 = 1; asm("" : "+r"(k1)); var_r8 += k1; }
                { register s32 k2 asm("r0"); k2 = 2; asm("" : "+r"(k2)); var_sl = k2; }
                goto block_32;
            case 10:
                M2C_FIELD(arg0, s16 *, 0xC) = 0;
                M2C_FIELD(arg0, u16 *, 0xE) = (u16) (M2C_FIELD(arg0, u16 *, 0xE) + 2);
                M2C_FIELD(arg0, u16 *, 0x10) = (u16) (M2C_FIELD(arg0, u16 *, 0x10) + 2);
                goto block_40;
            default:
                goto block_32;
            }
        } else {
            { u8 t80; t80 = (u8) (var_r0 + 0x80);
            if ((u32) t80 <= 0x1FU) {
                if (((s32) M2C_FIELD(arg0, s16 *, 0xC) < (s32) (M2C_FIELD(arg0, u16 *, 8) - 2)) && ((s32) (s16) M2C_FIELD(arg0, u16 *, 0xE) < (s32) (M2C_FIELD(arg0, u16 *, 0xA) - 3))) {
                    { s32 hi; s32 lo; hi = M2C_FIELD(var_r8, u8 *, 0) << 8; asm("" : "+r"(hi)); lo = M2C_FIELD(var_r8, u8 *, 1); asm("" : "+r"(lo)); func_08097B2C(lo | hi, M2C_FIELD(arg0, u8 *, 0x12), &sp14); }
                    { register s32 pa asm("r2"); s32 pb; pa = M2C_FIELD(arg0, s16 *, 0xC); pb = (((s16) M2C_FIELD(arg0, u16 *, 0xE) + 1) * M2C_FIELD(arg0, u16 *, 8)); pb += 1;  temp_r5 = (s8 *) arg0 + (((pa + pb) * 2) + 0x1E); }
                    { s32 hv; register s32 mh asm("r2"); s32 ml; hv = *(u16 *) temp_r5; mh = 0x3FF; ml = mh; asm("" :: "r"(mh)); temp_r1 = hv & ml; }
                    temp_r0_2 = *(u32 *)0x02021664;
                    if ((temp_r1 < temp_r0_2) || (temp_r1 >= (u32) (temp_r0_2 + 0x40))) {
                        func_08097980((u16) (temp_r1 - *(s32 *)0x02021670));
                    }
                    { s32 hv; register s32 mh asm("r3"); s32 ml; hv = *(u16 *) ((M2C_FIELD(arg0, u16 *, 8) * 2) + temp_r5); mh = 0x3FF; ml = mh; asm("" :: "r"(mh)); temp_r1_2 = hv & ml; }
                    temp_r0_3 = *(s32 *)0x02021664;
                    if ((temp_r1_2 < temp_r0_3) || (temp_r1_2 >= (u32) (temp_r0_3 + 0x40))) {
                        func_08097980((u16) (temp_r1_2 - *(s32 *)0x02021670));
                    }
                    *(u16 *) temp_r5 = M2C_FIELD(&sp14, u16 *, 0);
                    { register u16 *dst asm("r1"); s32 v; { s32 b5; b5 = (s32) temp_r5; dst = (u16 *)((M2C_FIELD(arg0, u16 *, 8) * 2) + b5); } v = M2C_FIELD(&sp14, u16 *, 2); *dst = (u16) v; }
                    M2C_FIELD(arg0, s16 *, 0xC) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0xC) + 1);
                }
                { s32 c2; c2 = 2; asm("" : "+r"(c2)); var_r8 += c2; var_sl = c2; }
            } else {
                { s32 lhs; lhs = (s32) M2C_FIELD(arg0, s16 *, 0xC); asm volatile("" :: "r"(t80));
                if ((lhs < (s32) (M2C_FIELD(arg0, u16 *, 8) - 2)) && ((s32) (s16) M2C_FIELD(arg0, u16 *, 0xE) < (s32) (M2C_FIELD(arg0, u16 *, 0xA) - 2))) {
                    func_08097CEC(M2C_FIELD(var_r8, u8 *, 0), M2C_FIELD(arg0, u8 *, 0x12), &sp14);
                    { register s32 pa asm("r2"); s32 pb; pa = M2C_FIELD(arg0, s16 *, 0xC); pb = (((s16) M2C_FIELD(arg0, u16 *, 0xE) + 1) * M2C_FIELD(arg0, u16 *, 8)); pb += 1;  temp_r5_2 = (s8 *) arg0 + (((pa + pb) * 2) + 0x1E); }
                    { s32 hv; register s32 mh asm("r2"); s32 ml; hv = *(u16 *) temp_r5_2; mh = 0x3FF; ml = mh; asm("" :: "r"(mh)); temp_r1_3 = hv & ml; }
                    temp_r0_4 = *(s32 *)0x02021664;
                    if ((temp_r1_3 < temp_r0_4) || (temp_r1_3 >= (u32) (temp_r0_4 + 0x40))) {
                        func_08097980((u16) (temp_r1_3 - *(s32 *)0x02021670));
                    }
                    *(u16 *) temp_r5_2 = M2C_FIELD(&sp14, u16 *, 0);
                    M2C_FIELD(arg0, s16 *, 0xC) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0xC) + 1);
                }
                { register s32 c1 asm("r3"); c1 = 1; var_r8 += c1; var_sl = c1; }
            } } }
block_32:
            temp_r1_4 = M2C_FIELD(arg0, s32 *, 0);
            temp_r2 = 0x10 & temp_r1_4;
            if (temp_r2 == 0) {
                temp_r3 = *var_r8;
                if (temp_r3 != 0xA) {
                    if (!(temp_r1_4 & 0x40)) {
                    } else if (M2C_FIELD(arg0, s16 *, 0xC) != (M2C_FIELD(arg0, u16 *, 8) - 2)) {
                    } else {
                        goto block_38;
                    }
                } else {
block_38:
                    M2C_FIELD(arg0, s16 *, 0xC) = temp_r2;
                    M2C_FIELD(arg0, u16 *, 0xE) = (u16) (M2C_FIELD(arg0, u16 *, 0xE) + var_sl);
                    if (temp_r3 != 0xA) {
                    } else {
block_40:
                        var_r8 += 1;
                    }
                }
            } else {
                M2C_FIELD(arg0, s32 *, 0) = (s32) (temp_r1_4 | 2);
                func_080972C8();
                if (*(u8 *)0x03000075 == 1) {
                    func_080ED17C(2);
                } else {
                    func_080ED17C(1);
                }
                temp_r0_5 = *var_r8;
                if ((u32) temp_r0_5 <= 1U) {
                } else if (temp_r0_5 != 0xA) {
                    if (!(M2C_FIELD(arg0, s32 *, 0) & 0x40)) {
                    } else if (M2C_FIELD(arg0, s16 *, 0xC) != (M2C_FIELD(arg0, u16 *, 8) - 2)) {
                    } else {
                        goto block_52;
                    }
                } else {
block_52:
                    { s32 t10; t10 = M2C_FIELD(arg0, u16 *, 0x10) + var_sl;
                    zz = 0;
                    M2C_FIELD(arg0, u16 *, 0x10) = (u16) t10; }
                    temp_r5_3 = (s16) M2C_FIELD(arg0, u16 *, 0xE);
                    temp_r2_2 = M2C_FIELD(arg0, u16 *, 0xA);
                    vsl2 = var_sl + 2;
                    if (temp_r5_3 != (temp_r2_2 - vsl2)) {
                    } else {
                        if (M2C_FIELD(arg0, u16 *, 0x10) == (temp_r2_2 - 2)) {
                            rv = func_08094484(tA, tB, 1, (s16) (((pa = M2C_FIELD(arg0, s16 *, 0xC), pa += 1, pa) + M2C_FIELD(arg0, u16 *, 4)) * 8), (s32) ((((qb = temp_r5_3, qb += 1, qb) + M2C_FIELD(arg0, u16 *, 6)) << 0x13) + 0x80000) >> 0x10, (s32) (u16) (*(u16 *)0x0202166A + 2), (s32) *(u16 *)0x0202166C, 0x20, zz);
                            pA890 = (s32 *)0x0200A890;
                            pA890[1] = rv;
                            if (!(3 & *(u16 *)0x0300000E)) {
                                do {
                                    func_080ED17C(1);
                                } while (!(3 & *(u16 *)0x0300000E));
                            }
                            pA890b = (s32 *)0x0200A890;
                                func_08094554(pA890b[1]);
                            M2C_FIELD(arg0, u16 *, 0x10) = 0U;
                            func_08092E84(0x41);
                        }
                        var_r1 = 0;
                        zr = 0;
                        if (!(zr < var_sl)) {
                        } else {
loop_61:
                            var_r7 = 1;
                            while (var_r7 < (s32) (M2C_FIELD(arg0, u16 *, 0xA) - 2)) {
                                {
                                    var_r6 = 1;
                                    while (var_r6 < (s32) (M2C_FIELD(arg0, u16 *, 8) - 1)) {
                                        {
                                            temp_r5_4 = (s8 *) arg0 + 0x1E;
                                            if ((var_r7 == 1) && ((temp_r1_5 = ({ s32 oc; oc = (var_r6 + M2C_FIELD(arg0, u16 *, 8)) * 2; *(u16 *)(temp_r5_4 + oc); }) & 0x3FF, temp_r0_6 = *(s32 *)0x02021664, (temp_r1_5 < temp_r0_6)) || (temp_r1_5 >= (u32) (temp_r0_6 + 0x40)))) {
                                                sp18 = (var_r7 + 1);
                                                func_08097980((u16) (temp_r1_5 - *(s32 *)0x02021670));
                                            }
                                            temp_r0_7 = M2C_FIELD(arg0, u16 *, 8);
                                            { s32 od; od = (var_r6 + (var_r7 * temp_r0_7)) * 2; *(u16 *)(temp_r5_4 + od) = ({ s32 os; os = (var_r6 + (temp_r0_7 * (var_r7 + 1))) * 2; *(u16 *)(temp_r5_4 + os); }); }
                                            var_r6 += 1;
                                            asm volatile(
                                                ".macro blt target\n\t"
                                                ".purgem blt\n\t"
                                                ".short 0xdbd3\n\t"
                                                ".endm");
                                        }
                                    }
                                    var_r7 += 1;
                                }
                            }
                            var_r6_2 = 1;
                            if (var_r6_2 < (s32) ((w8 = M2C_FIELD(arg0, u16 *, 8)) - 1)) {
                                bp2 = (s8 *) arg0 + 0x1E;
                                rhsv = (*(s32 *)0x02021664 + 1) | *(u16 *)0x02021668;
                                do {
                                    { s32 off; off = (var_r6_2 + (var_r7 * w8)) * 2; *(u16 *)(bp2 + off) = rhsv; }
                                    var_r6_2 += 1;
                                } while (var_r6_2 < (s32) ((w8 = M2C_FIELD(arg0, u16 *, 8)) - 1));
                            }
                            M2C_FIELD(arg0, u16 *, 0xE) = (u16) (M2C_FIELD(arg0, u16 *, 0xE) - 1);
                            asm("" ::: "memory");
                            M2C_FIELD(arg0, s32 *, 0) = (s32) (M2C_FIELD(arg0, s32 *, 0) | 2);
                            func_080972C8();
                            if (*(u8 *)0x03000075 == 1) {
                                func_080ED17C(2);
                            } else {
                                func_080ED17C(1);
                            }
                            var_r1 += 1;
                            if (var_r1 < var_sl) {
                                goto loop_61;
                            }
                        }
                    }
                    M2C_FIELD(arg0, s16 *, 0xC) = 0;
                    M2C_FIELD(arg0, u16 *, 0xE) = (u16) (M2C_FIELD(arg0, u16 *, 0xE) + var_sl);
                    if (*var_r8 == 0xA) {
                        var_r8 += 1;
                    }
                }
            }
        }
loop_bottom:
        var_r0 = *var_r8;
        if (var_r0 != 0) {
            goto loop_2;
        }
    }
    return var_r8;
}
