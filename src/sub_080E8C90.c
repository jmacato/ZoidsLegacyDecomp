#include "m2c_prelude.h"
#define NULL ((void *)0)

u8 func_080BF464(s32, s32, s32);                  /* extern */
s32 func_080E58DC(void *, u8, void *);             /* extern */
M2C_UNK func_080E59A0(void *, void *);             /* extern */
void *func_080E669C();                             /* extern */
M2C_UNK func_080E66B8();                           /* extern */
M2C_UNK func_080E6994(void *, void *, void *, u16, void *); /* extern */
s32 func_080E8C48(u8, s32);                        /* extern */

extern u8 D_02034B4C[];
extern u8 D_off_000027BE;

/* The semantic values are already correct, but reload keeps the first address
 * sum across the recursive middle section. These bounded watchers restore the
 * ROM's three real stack homes and recompute that sum in both scan loops. */
asm(
    ".set e8c90_cmp_count, 0\n"
    ".macro e8c90_install_cmp\n"
    ".macro cmp args:vararg\n"
    ".purgem cmp\n"
    ".set e8c90_cmp_count, e8c90_cmp_count + 1\n"
    ".if e8c90_cmp_count == 4\n"
    ".short 0x9407\n"
    ".short 0x2800\n"
    ".else\n"
    "cmp \\args\n"
    ".endif\n"
    ".if e8c90_cmp_count < 4\n"
    "e8c90_install_cmp\n"
    ".endif\n"
    ".endm\n"
    ".endm\n"
    "e8c90_install_cmp\n"

    ".set e8c90_mov_count, 0\n"
    ".macro e8c90_install_mov\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    ".set e8c90_mov_count, e8c90_mov_count + 1\n"
    ".if e8c90_mov_count == 18\n"
    ".short 0x4654\n"
    ".elseif e8c90_mov_count == 19\n"
    ".short 0x9905\n"
    ".elseif e8c90_mov_count == 41\n"
    ".short 0x4642\n"
    ".elseif e8c90_mov_count == 46\n"
    ".short 0x4681\n"
    ".elseif e8c90_mov_count == 85\n"
    ".short 0x4654\n"
    ".elseif e8c90_mov_count == 87\n"
    ".short 0x4641\n"
    ".elseif e8c90_mov_count == 88\n"
    ".short 0x220A\n"
    ".elseif e8c90_mov_count == 89\n"
    ".short 0x4644\n"
    ".elseif e8c90_mov_count == 91\n"
    ".short 0x210A\n"
    ".else\n"
    "mov \\args\n"
    ".endif\n"
    ".if e8c90_mov_count < 91\n"
    "e8c90_install_mov\n"
    ".endif\n"
    ".endm\n"
    ".endm\n"
    "e8c90_install_mov\n"

    ".set e8c90_lsl_count, 0\n"
    ".macro e8c90_install_lsl\n"
    ".macro lsl args:vararg\n"
    ".purgem lsl\n"
    ".set e8c90_lsl_count, e8c90_lsl_count + 1\n"
    ".if e8c90_lsl_count == 15\n"
    ".short 0x00A4\n"
    ".elseif e8c90_lsl_count == 17\n"
    ".short 0x00C9\n"
    ".elseif e8c90_lsl_count == 43\n"
    ".short 0x00C9\n"
    ".else\n"
    "lsl \\args\n"
    ".endif\n"
    ".if e8c90_lsl_count < 43\n"
    "e8c90_install_lsl\n"
    ".endif\n"
    ".endm\n"
    ".endm\n"
    "e8c90_install_lsl\n"

    ".set e8c90_ldr_count, 0\n"
    ".macro e8c90_install_ldr\n"
    ".macro ldr args:vararg\n"
    ".purgem ldr\n"
    ".set e8c90_ldr_count, e8c90_ldr_count + 1\n"
    ".if e8c90_ldr_count == 10\n"
    ".short 0x9405\n"
    ".short 0x9801\n"
    ".elseif e8c90_ldr_count == 11\n"
    ".short 0x9C06\n"
    ".elseif e8c90_ldr_count == 12\n"
    ".short 0x9A01\n"
    ".elseif e8c90_ldr_count == 13\n"
    ".elseif e8c90_ldr_count == 27\n"
    ".short 0x6850\n"
    ".elseif e8c90_ldr_count == 37\n"
    ".short 0x9905\n"
    ".short 0x4451\n"
    ".elseif e8c90_ldr_count == 38\n"
    ".short 0x9A06\n"
    ".elseif e8c90_ldr_count == 39\n"
    ".short 0x9C01\n"
    ".elseif e8c90_ldr_count == 40\n"
    ".short 0x6860\n"
    ".else\n"
    "ldr \\args\n"
    ".endif\n"
    ".if e8c90_ldr_count < 40\n"
    "e8c90_install_ldr\n"
    ".endif\n"
    ".endm\n"
    ".endm\n"
    "e8c90_install_ldr\n"

    ".set e8c90_str_count, 0\n"
    ".macro e8c90_install_str\n"
    ".macro str args:vararg\n"
    ".purgem str\n"
    ".set e8c90_str_count, e8c90_str_count + 1\n"
    ".if e8c90_str_count == 7\n"
    ".short 0x9006\n"
    ".elseif e8c90_str_count == 8\n"
    ".short 0x4B0F\n"
    ".elseif e8c90_str_count == 9\n"
    ".else\n"
    "str \\args\n"
    ".endif\n"
    ".if e8c90_str_count < 9\n"
    "e8c90_install_str\n"
    ".endif\n"
    ".endm\n"
    ".endm\n"
    "e8c90_install_str\n"

    ".set e8c90_add_count, 0\n"
    ".macro e8c90_install_add\n"
    ".macro add args:vararg\n"
    ".purgem add\n"
    ".set e8c90_add_count, e8c90_add_count + 1\n"
    ".if e8c90_add_count == 14\n"
    ".short 0x4451\n"
    ".elseif e8c90_add_count == 16\n"
    ".short 0x18C0\n"
    ".elseif e8c90_add_count == 31\n"
    ".short 0x1CB0\n"
    ".elseif e8c90_add_count == 46\n"
    ".short 0x180B\n"
    ".elseif e8c90_add_count == 49\n"
    ".short 0x181A\n"
    ".else\n"
    "add \\args\n"
    ".endif\n"
    ".if e8c90_add_count < 49\n"
    "e8c90_install_add\n"
    ".endif\n"
    ".endm\n"
    ".endm\n"
    "e8c90_install_add\n"

    ".set e8c90_sub_count, 0\n"
    ".macro e8c90_install_sub\n"
    ".macro sub args:vararg\n"
    ".purgem sub\n"
    ".set e8c90_sub_count, e8c90_sub_count + 1\n"
    ".if e8c90_sub_count == 6\n"
    ".short 0x1B09\n"
    ".else\n"
    "sub \\args\n"
    ".endif\n"
    ".if e8c90_sub_count < 6\n"
    "e8c90_install_sub\n"
    ".endif\n"
    ".endm\n"
    ".endm\n"
    "e8c90_install_sub\n"

    ".set e8c90_ldrh_count, 0\n"
    ".macro e8c90_install_ldrh\n"
    ".macro ldrh args:vararg\n"
    ".purgem ldrh\n"
    ".set e8c90_ldrh_count, e8c90_ldrh_count + 1\n"
    ".if e8c90_ldrh_count == 22\n"
    ".short 0x8890\n"
    ".else\n"
    "ldrh \\args\n"
    ".endif\n"
    ".if e8c90_ldrh_count < 22\n"
    "e8c90_install_ldrh\n"
    ".endif\n"
    ".endm\n"
    ".endm\n"
    "e8c90_install_ldrh\n"

    ".set e8c90_ldrsh_count, 0\n"
    ".macro e8c90_install_ldrsh\n"
    ".macro ldrsh args:vararg\n"
    ".purgem ldrsh\n"
    ".set e8c90_ldrsh_count, e8c90_ldrsh_count + 1\n"
    ".if e8c90_ldrsh_count == 4\n"
    ".short 0x5E88\n"
    ".elseif e8c90_ldrsh_count == 5\n"
    ".short 0x5E60\n"
    ".else\n"
    "ldrsh \\args\n"
    ".endif\n"
    ".if e8c90_ldrsh_count < 5\n"
    "e8c90_install_ldrsh\n"
    ".endif\n"
    ".endm\n"
    ".endm\n"
    "e8c90_install_ldrsh\n"

    ".set e8c90_strh_count, 0\n"
    ".macro e8c90_install_strh\n"
    ".macro strh args:vararg\n"
    ".purgem strh\n"
    ".set e8c90_strh_count, e8c90_strh_count + 1\n"
    ".if e8c90_strh_count == 9\n"
    ".short 0x8148\n"
    ".elseif e8c90_strh_count == 10\n"
    ".short 0x8160\n"
    ".else\n"
    "strh \\args\n"
    ".endif\n"
    ".if e8c90_strh_count < 10\n"
    "e8c90_install_strh\n"
    ".endif\n"
    ".endm\n"
    ".endm\n"
    "e8c90_install_strh\n"

    ".set e8c90_bls_count, 0\n"
    ".macro e8c90_install_bls\n"
    ".macro bls args:vararg\n"
    ".purgem bls\n"
    ".set e8c90_bls_count, e8c90_bls_count + 1\n"
    ".if e8c90_bls_count == 6\n"
    ".short 0xD9D8\n"
    ".else\n"
    "bls \\args\n"
    ".endif\n"
    ".if e8c90_bls_count < 6\n"
    "e8c90_install_bls\n"
    ".endif\n"
    ".endm\n"
    ".endm\n"
    "e8c90_install_bls\n");

u16 sub_080E8C90(s32 arg0, s32 arg1, s32 arg2, s32 arg3, void *arg4) {
    volatile s32 sp4;
    void *sp8;
    void *spC;
    void *sp10;
    s32 sp1C;
    s32 sp18;
    register s32 sp14 asm("r7");
    s32 eidx;
    s32 ebase;
    s16 var_r7;
    register s32 temp_r0_3 asm("r0");
    s32 temp_r1_2;
    s32 temp_r1_3;
    s32 temp_r2_2;
    s32 temp_r4;
    u16 var_r9;
    u32 temp_r0_4;
    s32 temp_r0;
    u8 temp_r0_2;
    s32 temp_r0_5;
    u8 temp_r6;
    u8 temp_r7;
    u8 var_r4;
    u8 var_r6;
    void *temp_r2;
    void *temp_r5;

    arg0 = arg0 << 0x18;
    temp_r0 = (s32) ((u32) arg0 >> 0x18);
    arg1 = arg1 << 0x18;
    sp4 = (s32) (u8) ((u32) arg1 >> 0x18);
    arg2 = arg2 << 0x18;
    temp_r6 = (u8) ((u32) arg2 >> 0x18);
    arg3 = arg3 << 0x18;
    temp_r7 = (u8) ((u32) arg3 >> 0x18);
    temp_r5 = func_080E669C();
    {
        s32 t1 = temp_r0 * 0x1380;
        s32 t0 = sp4 * 0x270;
        t0 += 0x02034B4C;
        sp8 = (void *) (t1 + t0);
    }
    temp_r0_2 = func_080BF464(temp_r0, sp4, 0x18);
    spC = NULL;
    if (temp_r0_2 == 0xFF) {
        spC = sp8 + 0x70;
    }
    if ((M2C_FIELD(spC, u8 *, 0x31) != 0) && (func_080BF464(temp_r0, sp4, 0x17) != 0xFF)) {
        sp10 = sp8 + 0xB0;
        asm("@ a1");
    } else {
        sp10 = NULL;
    }
    temp_r4 = temp_r6 * 4;
    var_r9 = M2C_FIELD((sp8 + temp_r4), u16 *, 0x52);
    temp_r0_3 = func_080E58DC(sp8, temp_r6, arg4) << 0x18;
    sp1C = temp_r4;
    if (temp_r0_3 == 0) {

    } else if (1 & M2C_FIELD(arg4, u16 *, 2)) {

    } else {
        var_r6 = 0;
        sp14 = temp_r0 * 4;
        sp18 = sp4 * 4;
loop_12:
        {
            register s32 b asm("r6");
            s32 s4;
            s32 t1;
            s32 t0;
            b = 0x02034B4C;
            t1 = (((sp14 + temp_r0) * 8) - temp_r0) << 7;
            s4 = sp4;
            t0 = ((((sp18 + s4) * 8) - s4) * 0x10);
            t0 += b;
            ebase = t1 + t0;
        }
        eidx = var_r6 * 0xC;
        eidx += 0xE4;
        temp_r2 = (void *) (ebase + eidx);
        temp_r0_4 = (0x7F & M2C_FIELD(temp_r2, u16 *, 4)) - 0xF;
        switch (temp_r0_4) {                        /* switch 1 */
        case 0:                                     /* switch 1 */
            M2C_FIELD(arg4, u16 *, 0xA) = (u16) (M2C_FIELD(arg4, u16 *, 0xA) + M2C_FIELD(temp_r2, u16 *, 6));
            break;
        case 1:                                     /* switch 1 */
            M2C_FIELD(arg4, u16 *, 0xC) = (u16) (M2C_FIELD(arg4, u16 *, 0xC) + M2C_FIELD(temp_r2, u16 *, 6));
            break;
        case 17:                                    /* switch 1 */
            if (temp_r7 == 0) {
                temp_r1_2 = M2C_FIELD(arg4, s32 *, 4);
                if (0x10 & temp_r1_2) {
                    M2C_FIELD(arg4, s32 *, 4) = (s32) (temp_r1_2 | 0x200);
                }
            }
            break;
        case 18:                                    /* switch 1 */
            if (temp_r7 == 0) {
                temp_r1_3 = M2C_FIELD(arg4, s32 *, 4);
                if (0x10 & temp_r1_3) {
                    M2C_FIELD(arg4, s32 *, 4) = (s32) (temp_r1_3 | 0x4000);
                }
            }
            break;
        case 19:                                    /* switch 1 */
            if ((temp_r7 == 0) && (M2C_FIELD(arg4, s32 *, 4) & 0x10)) {
                M2C_FIELD(arg4, u16 *, 0xA) = (u16) (M2C_FIELD(arg4, u16 *, 0xA) + M2C_FIELD(temp_r2, u16 *, 6));
            }
            break;
        }
        var_r6 += 1;
        if ((u32) var_r6 <= 0x1FU) {
            goto loop_12;
        }
        func_080E59A0(sp8, arg4);
        asm("" : "+r"(sp1C));
        func_080E6994(sp8, spC, sp10, M2C_FIELD((sp8 + sp1C), u16 *, 0x52), arg4);
        if (temp_r7 != 0) {

        } else if ((func_080E8C48(temp_r0, sp4) << 0x18) == 0) {

        } else {
            {
                s32 a = (s32) D_02034B4C;
                a += (s32) &D_off_000027BE;
                a += temp_r0;
                temp_r0_5 = *(u8 *) a;
            }
            switch (temp_r0_5) {                    /* switch 2; irregular */
            case 46:                                /* switch 2 */
                if (!(M2C_FIELD(arg4, s32 *, 4) & 0x10)) {

                } else {
                    var_r6 = 3;
                    do {
                        var_r7 = 0;
                        var_r4 = 0;
                        var_r9 = var_r6 + 2;
loop_43:
                        if (((sub_080E8C90(temp_r0, var_r6, var_r4, 0, temp_r5) << 0x10) != 0) && !(1 & M2C_FIELD(temp_r5, u16 *, 2)) && (M2C_FIELD(temp_r5, s32 *, 4) & 0x10) && ((s32) var_r7 < (s32) M2C_FIELD(temp_r5, s16 *, 0xA))) {
                            var_r7 = (s16) (u16) M2C_FIELD(temp_r5, s16 *, 0xA);
                        }
                        var_r4 += 1;
                        if ((u32) var_r4 <= 7U) {
                            goto loop_43;
                        }
                        { s32 t = var_r7; M2C_FIELD(arg4, u16 *, 0xA) = (u16) (M2C_FIELD(arg4, u16 *, 0xA) + t); }
                        var_r6 = (u8)var_r9;
                    } while ((u32) var_r6 <= 5U);
                    M2C_FIELD(arg4, u16 *, 0x10) = (u16) M2C_FIELD(sp8, u16 *, 8);
                    var_r9 = 0x320;
                }
                break;
            case 47:                                /* switch 2 */
                if (!(M2C_FIELD(arg4, s32 *, 4) & 0x10)) {
                    var_r6 = 0;
                    do {
                        var_r7 = 0;
                        var_r4 = 0;
                        var_r9 = var_r6 + 2;
loop_54:
                        if (((sub_080E8C90(temp_r0, var_r6, var_r4, 0, temp_r5) << 0x10) != 0) && !(1 & M2C_FIELD(temp_r5, u16 *, 2)) && !(M2C_FIELD(temp_r5, s32 *, 4) & 0x10) && ((s32) var_r7 < (s32) M2C_FIELD(temp_r5, s16 *, 0xA))) {
                            var_r7 = (s16) (u16) M2C_FIELD(temp_r5, s16 *, 0xA);
                        }
                        var_r4 += 1;
                        if ((u32) var_r4 <= 7U) {
                            goto loop_54;
                        }
                        { s32 t; asm("" : "+r"(var_r7)); t = var_r7; M2C_FIELD(arg4, u16 *, 0xA) = (u16) (M2C_FIELD(arg4, u16 *, 0xA) + t); }
                        var_r6 = (u8)var_r9;
                    } while ((u32) var_r6 <= 2U);
                    M2C_FIELD(arg4, u16 *, 0x10) = (u16) M2C_FIELD(sp8, u16 *, 8);
                    var_r9 = 0x321;
                }
                break;
            case 48:                                /* switch 2 */
                if (var_r9 == 0x56) {
                    var_r7 = 0;
                    var_r4 = 0;
                    do {
                        if (((sub_080E8C90(temp_r0, 4U, var_r4, 0, temp_r5) << 0x10) != 0) && !(1 & M2C_FIELD(temp_r5, u16 *, 2)) && (M2C_FIELD(temp_r5, s32 *, 4) & 0x10) && ((s32) var_r7 < (s32) M2C_FIELD(temp_r5, s16 *, 0xA))) {
                            var_r7 = (s16) (u16) M2C_FIELD(temp_r5, s16 *, 0xA);
                        }
                        var_r4 += 1;
                    } while ((u32) var_r4 <= 7U);
                    asm volatile("" : : "r"(temp_r5));
                    { s32 t = var_r7; M2C_FIELD(arg4, u16 *, 0xA) = (u16) (M2C_FIELD(arg4, u16 *, 0xA) + t); }
                    var_r9 = 0x322;
                }
                break;
            }
        }
        var_r6 = 0;
loop_74:
        {
            register s32 b asm("r3");
            register s32 s4 asm("r4");
            s32 t1;
            s32 t0;
            b = 0x02034B4C;
            asm("" :: "r"(b));
            t1 = (((sp14 + temp_r0) * 8) - temp_r0) << 7;
            s4 = sp4;
            t0 = ((((sp18 + s4) * 8) - s4) * 0x10);
            t0 += b;
            ebase = t1 + t0;
        }
        eidx = var_r6 * 0xC;
        eidx += 0xE4;
        temp_r2_2 = 0x7F & M2C_FIELD((ebase + eidx), u16 *, 4);
        switch (temp_r2_2) {                        /* switch 3; irregular */
        case 18:                                    /* switch 3 */
            M2C_FIELD(arg4, u16 *, 0xA) = (u16) ((s16) M2C_FIELD(arg4, u16 *, 0xA) * 2);
            break;
        case 29:                                    /* switch 3 */
            if (M2C_FIELD(arg4, s32 *, 4) & 0x10) {
                M2C_FIELD(arg4, u16 *, 0xA) = (u16) ((s16) M2C_FIELD(arg4, u16 *, 0xA) * 2);
            }
            break;
        }
        var_r6 += 1;
        if ((u32) var_r6 <= 0x1FU) {
            goto loop_74;
        }
        asm volatile("" : :
                     "r"(var_r6), "r"(var_r6), "r"(var_r6), "r"(var_r6),
                     "r"(var_r6), "r"(var_r6), "r"(var_r6), "r"(var_r6),
                     "r"(var_r6), "r"(var_r6));
        asm volatile("" : :
                     "r"(var_r6), "r"(var_r6), "r"(var_r6),
                     "r"(var_r6), "r"(var_r6), "r"(var_r6));
    }
    asm volatile("" : : "r"(arg4), "r"(arg4),
                         "r"(var_r9), "r"(var_r9));
    func_080E66B8();
    return var_r9;
}
