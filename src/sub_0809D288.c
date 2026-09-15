#include "m2c_prelude.h"

M2C_UNK func_08092E74(s32);                         /* extern */
M2C_UNK func_0809423C();                            /* extern */
s32 func_08094484(M2C_UNK, M2C_UNK, s32, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_08094554(s32);                         /* extern */
M2C_UNK func_08096308(s32, s32);                    /* extern */
s32 func_0809669C();                                /* extern */
void *func_0809716C(s32);                           /* extern */
M2C_UNK func_08098834(s32);                         /* extern */
M2C_UNK func_08098BB4(M2C_UNK);                     /* extern */
M2C_UNK func_08099F80();                            /* extern */
M2C_UNK func_08099F8C();                            /* extern */
M2C_UNK func_08099FCC();                            /* extern */
M2C_UNK func_08099FEC();                            /* extern */
M2C_UNK func_0809A00C();                            /* extern */
M2C_UNK func_0809A048();                            /* extern */
M2C_UNK func_0809A0A0();                            /* extern */
M2C_UNK func_0809CC94(s32);                         /* extern */
M2C_UNK func_0809CED8();                            /* extern */
M2C_UNK func_0809D094();                            /* extern */
M2C_UNK func_0809D200();                            /* extern */
M2C_UNK func_080ED17C(s32);                         /* extern */
M2C_UNK jtbl_0809D33C();                            /* static */
extern s8 D_02021698;
extern s16 D_02032E76;

void sub_0809D288(void) {
    s32 temp_r4;
    s32 temp_r4_3;
    s32 var_r7;
    s32 state_base;
    u8 temp_r0;
    u8 temp_r4_2;
    void *temp_r1;

    func_08092E74(3);
    var_r7 = 0;
    if (*(volatile s32 *)0x02021690 != 2) {
        goto loop_72;
    }
loop_2:
        state_base = 0x1000;
        switch (var_r7) {                           /* switch 1; irregular */
        case 0x0:                                   /* switch 1 */
            func_0809D200();
            goto block_67;
        case 0x1000:                                /* switch 1 */
            temp_r4_3 = func_08094484(0x08105A20, 0x08105A2C, 0, 0xD8, 0x98, 0x343, 0xF, 8, 0);
            func_08098BB4(0x08000B7F);
            if (*(u8 *)0x0200A882 != 1) {
                goto block_not_ready;
            }
            *(u8 *)0x020216F4 = *(u8 *)0x0200A880;
            temp_r0 = *(u8 *)0x0200A880;
            switch ((u32) temp_r0) {                /* switch 2; irregular */
            case 0:                                 /* switch 2 */
                if (*(u8 *)0x0202169C != 1) {
                    goto block_49;
                }
                if (*(u8 *)0x0202169D != 1) {
                    goto block_49;
                }
                if (*(u8 *)0x0202169E != 1) {
                    goto block_49;
                } else {
                    *(s32 *)0x02021690 = 0x10;
                    *(s8 *)0x02032E74 = 0;
                    {
                    D_02032E76 = 0;
                    }
                    goto block_51;
                }
                break;
            case 1:                                 /* switch 2 */
                *(s32 *)0x02021690 = 0xD;
                goto block_51;
            case 2:                                 /* switch 2 */
                if (*(u8 *)0x0202169C != 1) {
                    goto block_49;
                }
                if (*(u8 *)0x0202169D != 1) {
                    goto block_49;
                }
                if (*(u8 *)0x0202169E != 1) {
                    goto block_49;
                }
                *(s32 *)0x02021690 = 0xE;
                goto block_51;
            case 3:                                 /* switch 2 */
                *(s32 *)0x02021690 = 0xF;
                *(s8 *)0x02032E5C = 0;
                goto block_51;
            case 4:                                 /* switch 2 */
                func_08094554(temp_r4_3);
                var_r7 = 0x2000;
                break;
            case 5:                                 /* switch 2 */
                if (((u32) *(u8 *)0x02021699 <= 1U) || ((u32) *(u8 *)0x0202169A <= 1U) || ((u32) *(u8 *)0x0202169B <= 1U) || ((u32) *(u8 *)0x0202169C <= 1U) || ((u32) *(u8 *)0x0202169D <= 1U) || ((u32) *(u8 *)0x0202169E <= 1U) || ((u32) *(u8 *)0x0202169F <= 1U)) {
                    func_08094554(temp_r4_3);
                    func_08098BB4(0x08000BFB);
                    if (*(u8 *)0x0200A882 != 1) {

                    } else if (*(u8 *)0x0200A880 != 0) {

                    } else {
                        func_0809423C();
                        func_08099F80();
                        func_08099F8C();
                        func_08099FCC();
                        func_08099FEC();
                        func_0809A00C();
                        func_0809A048();
                        func_0809A0A0();
                        {
                        register u8 *status99 asm("r8") = (u8 *)0x02021699;
                        register u8 *status9A asm("r6") = (u8 *)0x0202169A;
                        register u8 *status9B asm("r5") = (u8 *)0x0202169B;
                        register u8 *status9C asm("r4") = (u8 *)0x0202169C;
                        register u8 *status9D asm("r3") = (u8 *)0x0202169D;
                        register u8 *status9E asm("r2") = (u8 *)0x0202169E;
                        register u8 *status9F asm("r1") = (u8 *)0x0202169F;
                        asm volatile("" : "+r"(status99), "+r"(status9A), "+r"(status9B),
                                             "+r"(status9C));
                        asm volatile("" : "+r"(status9D), "+r"(status9E), "+r"(status9F));
                        *status9F = 2U;
                        *status9E = 2U;
                        *status9D = 2U;
                        *status9C = 2U;
                        *status9B = 2U;
                        *status9A = 2U;
                        *status99 = 2U;
                        }
                        func_08098834(0);
                        func_0809D094();
                        func_08098BB4(0x08000C89);
                    }
                } else {
                    goto block_49;
                }
                break;
            }
            goto block_inner_done;
block_49:
            func_08098BB4(0x08000CBA);
            goto block_inner_done;
block_not_ready:
            *(s32 *)0x02021690 = 1;
            {
            D_02021698 = 1;
            }
block_51:
            func_08096308(0x10, 0);
block_inner_done:
            break;
        case 0x2000:                                /* switch 1 */
            func_08098BB4(0x08000B86);
            var_r7 = 0x2010;
            break;
        case 0x2010:                                /* switch 1 */
            temp_r4 = func_08094484(0x08105AFC, 0x08105B08, 0, 0xC8, 0x40, 0x350, 0xF, 8, 0);
            func_08098BB4(0x08000BF4);
            if (*(u8 *)0x0200A882 == 1) {
                func_08096308(0x10, 0);
                while ((func_0809669C() << 0x18) == 0) {
                    func_080ED17C(1);
                }
                temp_r4_2 = *(u8 *)0x0200A880;
                if (temp_r4_2 == 0) {
                    func_0809CC94(1);
                } else {
                    func_0809CED8();
                }
                func_0809D200();
                func_08098BB4(0x08000B86);
                temp_r1 = func_0809716C(1);
                if (temp_r4_2 == 0) {
                    M2C_FIELD(temp_r1, u8 *, 0x16) = temp_r4_2;
                } else {
                    M2C_FIELD(temp_r1, u8 *, 0x16) = 1U;
                }
            } else {
                func_08098BB4(0x08000BF8);
                func_08094554(temp_r4);
block_67:
                var_r7 = state_base;
            }
            break;
        }
        if (*(s32 *)0x02021690 == 2) {
            goto loop_2;
        }
loop_72:
    while ((func_0809669C() << 0x18) == 0) {
        func_080ED17C(1);
    }
}
