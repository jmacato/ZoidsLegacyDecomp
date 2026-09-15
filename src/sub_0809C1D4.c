#include "m2c_prelude.h"
M2C_UNK func_08092E84(s32);                         /* extern */
u8 func_080940AC();                                 /* extern */
u8 func_080940C0();                                 /* extern */
u8 func_08094110();                                 /* extern */
s32 func_08094124();                                /* extern */
s32 func_08094138();                                /* extern */
s32 func_0809414C();                                /* extern */
s32 func_08094160();                                /* extern */
s32 func_08094174();                                /* extern */
s32 func_08094188();                                /* extern */
s32 func_0809419C();                                /* extern */
M2C_UNK func_08094330();                            /* extern */
M2C_UNK func_08096308(s32, s32);                    /* extern */
s32 func_0809669C();                                /* extern */
M2C_UNK func_08096FBC(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_08098BB4(M2C_UNK);                     /* extern */
M2C_UNK func_08099F80();                            /* extern */
M2C_UNK func_08099F8C();                            /* extern */
M2C_UNK func_08099FCC();                            /* extern */
M2C_UNK func_08099FEC();                            /* extern */
M2C_UNK func_0809A00C();                            /* extern */
M2C_UNK func_0809A048();                            /* extern */
M2C_UNK func_0809A0A0();                            /* extern */
M2C_UNK func_0809AB44(s32, s32, s32, s32, s32);     /* extern */
M2C_UNK func_080ED17C(s32);                         /* extern */
extern s32 D_02021690;
extern s8 D_02021698;

void sub_0809C1D4(void) {
    register s32 var_r5 asm("r5");
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r0_3;
    s32 temp_r0_4;
    s32 temp_r0_5;
    s32 temp_r0_6;
    s32 temp_r0_7;

    temp_r0 = func_08094124();
    *(u8 *)0x02021699 = temp_r0;
    if ((u8)temp_r0 == 2) {
        func_08099F80();
    }
    temp_r0_2 = func_08094138();
    *(u8 *)0x0202169A = temp_r0_2;
    if ((u8)temp_r0_2 == 2) {
        func_08099F8C();
    }
    temp_r0_3 = func_0809414C();
    *(u8 *)0x0202169B = temp_r0_3;
    if ((u8)temp_r0_3 == 2) {
        func_08099FCC();
    }
    temp_r0_4 = func_08094160();
    *(u8 *)0x0202169C = temp_r0_4;
    if ((u8)temp_r0_4 == 2) {
        func_08099FEC();
    }
    temp_r0_5 = func_08094174();
    *(u8 *)0x0202169D = temp_r0_5;
    if ((u8)temp_r0_5 == 2) {
        func_0809A00C();
    }
    temp_r0_6 = func_08094188();
    *(u8 *)0x0202169E = temp_r0_6;
    if ((u8)temp_r0_6 == 2) {
        func_0809A048();
    }
    temp_r0_7 = func_0809419C();
    *(u8 *)0x0202169F = temp_r0_7;
    if ((u8)temp_r0_7 == 2) {
        func_0809A0A0();
    }
    if ((*(u8 *)0x0202169A != 0) && (*(u8 *)0x0202169B != 0) && (*(u8 *)0x0202169C != 0) && (*(u8 *)0x0202169D != 0) && (*(u8 *)0x0202169E != 0) && (*(u8 *)0x0202169F != 0)) {

    } else {
        *(s16 *)0x0300004C = 0x1840;
        func_08096FBC(3, 1, 0, 0x35C, 0x3C0, 0, 0xE, 0, 0x3E6, 0xF);
        func_0809AB44(2, 3, 0, 0, 1);
        func_08094330();
        func_08098BB4(0x08000934);
        func_08096308(0xF, 0);
        var_r5 = 0;
loop_22:
        switch (var_r5) {                           /* irregular */
        case 0:
            if (*(u8 *)0x0202169A == 0) {
                func_08092E84(0x58);
                func_08098BB4(0x08000946);
                func_08099F8C();
                *(u8 *)0x0202169A = func_080940AC();
            }
            break;
        case 1:
            if (*(u8 *)0x0202169B == 0) {
                func_08092E84(0x58);
                func_08098BB4(0x080009BE);
                func_08099FCC();
                *(u8 *)0x0202169B = func_080940C0();
            }
            break;
        case 2:
            if (*(u8 *)0x0202169F == 0) {
                func_08092E84(0x58);
                func_08098BB4(0x08000A22);
                func_0809A0A0();
                *(u8 *)0x0202169F = func_08094110();
            }
            break;
        case 3:
            if ((*(u8 *)0x0202169C == 0) || (*(u8 *)0x0202169D == 0) || (*(u8 *)0x0202169E == 0)) {
                func_08092E84(0x58);
                func_08098BB4(0x08000A7E);
                func_08099FEC();
                func_0809A00C();
                func_0809A048();
            }
            break;
        }
        {
            register s32 next asm("r0") = var_r5 + 1;

            next <<= 24;
            var_r5 = (u32)next >> 24;
        }
        if ((u32) var_r5 <= 3U) {
            goto loop_22;
        }
        func_08096308(0x10, 0);
        while ((func_0809669C() << 0x18) == 0) {
            func_080ED17C(1);
        }
    }
    D_02021690 = 1;
    D_02021698 = 0;
}
