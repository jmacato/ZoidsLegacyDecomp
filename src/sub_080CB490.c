#include "m2c_prelude.h"
M2C_UNK func_080972C8();                            /* extern */
M2C_UNK func_080981F0(s32, s32, s32, s32, s32);     /* extern */
M2C_UNK func_08098248(M2C_UNK, s32, s32);           /* extern */
M2C_UNK func_0809844C(s32, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_08098BB4(M2C_UNK);                     /* extern */
void *func_080E669C();                              /* extern */
M2C_UNK func_080E66B8();                            /* extern */
u16 func_080E8C90(u32, u32, u32, u32, void *);      /* extern */
M2C_UNK jtbl_080CB538();                            /* static */
M2C_UNK jtbl_080CB968();                            /* static */
M2C_UNK jtbl_080CB9E8();                            /* static */
extern u8 D_02034B4C[];
extern s32 D_087EE170[];

void sub_080CB490(void) {
    u16 temp_r8;
    register u32 temp_r0_2 asm("r3");
    u32 call0;
    u32 call1;
    register u8 *selection_base asm("r2");
    register u32 selection_offset asm("r4");
    u8 temp_r0_3;
    u8 temp_r0_4;
    void *temp_r0;

    temp_r0 = func_080E669C();
    call0 = *(u8 *)0x02033F36;
    call1 = *(u8 *)0x02033F37;
    selection_base = D_02034B4C;
    selection_offset = 0xA1AF;
    temp_r0_2 = selection_base[selection_offset];
    selection_offset++;
    selection_base += selection_offset;
    selection_base = (u8 *)(temp_r0_2 + (u32)selection_base);
    temp_r8 = func_080E8C90(call0, call1, *selection_base,
                            temp_r0_2, temp_r0);
    if (!(1 & M2C_FIELD(temp_r0, u16 *, 2))) {
        func_08098BB4(0x0800408F);
        func_0809844C(M2C_FIELD(temp_r0, s16 *, 0xA), 4, 0, 0xA, 2, 6, 2);
        func_0809844C(M2C_FIELD(temp_r0, s16 *, 0xC), 3, 0, 0xA, 2, 6, 3);
    } else {
        func_08098BB4(0x080040B9);
        switch (M2C_FIELD(temp_r0, u8 *, 4) - 1) {  /* switch 1; irregular */
        case 0:                                     /* switch 1 */
            func_080981F0(0x08108B5C, 0, 2, 0, 2);
            func_0809844C(M2C_FIELD(temp_r0, s16 *, 0xA), 4, 0, 0xE, 2, 5, 2);
            break;
        case 1:                                     /* switch 1 */
            func_080981F0(0x08108B5C, 0, 2, 0, 2);
            func_0809844C(M2C_FIELD(temp_r0, s16 *, 0xA), 4, 0, 0xE, 2, 5, 2);
            func_080981F0(0x08108B60, 0, 2, 0, 3);
            func_0809844C(M2C_FIELD(temp_r0, s16 *, 0xC), 4, 0, 0xE, 2, 5, 2);
            break;
        case 2:                                     /* switch 1 */
            func_080981F0(0x08108B64, 0, 2, 0, 2);
            func_0809844C(M2C_FIELD(temp_r0, s16 *, 0xA), 4, 0, 0xE, 2, 5, 2);
            break;
        case 3:                                     /* switch 1 */
            func_080981F0(0x08108B68, 0, 2, 0, 2);
            func_0809844C(M2C_FIELD(temp_r0, s16 *, 0xA), 4, 0, 0xE, 2, 5, 2);
            break;
        case 4:                                     /* switch 1 */
            func_080981F0(0x08108B64, 0, 2, 0, 2);
            func_0809844C(M2C_FIELD(temp_r0, s16 *, 0xA), 4, 0, 0xE, 2, 5, 2);
            func_080981F0(0x08108B68, 0, 2, 0, 3);
            func_0809844C(M2C_FIELD(temp_r0, s16 *, 0xC), 4, 0, 0xE, 2, 5, 3);
            break;
        case 5:                                     /* switch 1 */
            func_080981F0(0x08108B6C, 0, 2, 0, 2);
            func_0809844C(M2C_FIELD(temp_r0, s16 *, 0xA), 4, 0, 0xE, 2, 5, 2);
            break;
        case 6:                                     /* switch 1 */
            func_080981F0(0x08108B70, 0, 2, 0, 2);
            func_0809844C(M2C_FIELD(temp_r0, s16 *, 0xA), 4, 0, 0xE, 2, 5, 2);
            break;
        case 7:                                     /* switch 1 */
            func_080981F0(0x08108B6C, 0, 2, 0, 2);
            func_0809844C(M2C_FIELD(temp_r0, s16 *, 0xA), 4, 0, 0xE, 2, 5, 2);
            func_080981F0(0x08108B70, 0, 2, 0, 3);
            func_0809844C(M2C_FIELD(temp_r0, s16 *, 0xC), 4, 0, 0xE, 2, 5, 3);
            break;
        case 8:                                     /* switch 1 */
            func_080981F0(0x08108B70, 0, 2, 0, 2);
            func_0809844C(-M2C_FIELD(temp_r0, s16 *, 0xA), 4, 0, 0xE, 2, 5, 2);
            break;
        case 9:                                     /* switch 1 */
            func_080981F0(0x08108B74, 0, 2, 0, 2);
            func_0809844C(M2C_FIELD(temp_r0, s16 *, 0xA), 4, 0, 0xE, 2, 5, 2);
            break;
        case 10:                                    /* switch 1 */
            func_080981F0(0x08108B7C, 0, 2, 0, 2);
            func_0809844C(M2C_FIELD(temp_r0, s16 *, 0xA), 4, 0, 0xE, 2, 5, 2);
            break;
        case 11:                                    /* switch 1 */
            func_080981F0(0x08108B80, 0, 2, 0, 2);
            func_0809844C(M2C_FIELD(temp_r0, s16 *, 0xA), 4, 0, 0xE, 2, 5, 2);
            break;
        case 12:                                    /* switch 1 */
            func_080981F0(0x08108B88, 0, 2, 0, 2);
            func_0809844C(M2C_FIELD(temp_r0, s16 *, 0xA), 4, 0, 0xE, 2, 5, 2);
            break;
        case 13:                                    /* switch 1 */
            func_080981F0(0x08108B90, 0, 2, 0, 2);
            func_0809844C(M2C_FIELD(temp_r0, s16 *, 0xA), 4, 0, 0xE, 2, 5, 2);
            break;
        case 14:                                    /* switch 1 */
            func_080981F0(0x08108B88, 0, 2, 0, 2);
            func_0809844C(M2C_FIELD(temp_r0, s16 *, 0xA), 4, 0, 0xE, 2, 5, 2);
            func_080981F0(0x08108B90, 0, 2, 0, 3);
            func_0809844C(M2C_FIELD(temp_r0, s16 *, 0xC), 4, 0, 0xE, 2, 5, 3);
            break;
        case 15:                                    /* switch 1 */
            func_080981F0(0x08108B98, 0, 2, 0, 2);
            func_0809844C(M2C_FIELD(temp_r0, s16 *, 0xA), 4, 0, 0xE, 2, 5, 2);
            break;
        case 16:                                    /* switch 1 */
            func_080981F0(0x08108B9C, 0, 2, 0, 2);
            func_0809844C(M2C_FIELD(temp_r0, s16 *, 0xA), 4, 0, 0xE, 2, 5, 2);
            break;
        case 17:                                    /* switch 1 */
            func_080981F0(0x08108B98, 0, 2, 0, 2);
            func_0809844C(M2C_FIELD(temp_r0, s16 *, 0xA), 4, 0, 0xE, 2, 5, 2);
            func_080981F0(0x08108B9C, 0, 2, 0, 3);
            func_0809844C(M2C_FIELD(temp_r0, s16 *, 0xC), 4, 0, 0xE, 2, 5, 3);
            break;
        case 18:                                    /* switch 1 */
            func_080981F0(0x08108BA0, 0, 2, 0, 2);
            func_0809844C(M2C_FIELD(temp_r0, s16 *, 0xA), 4, 0, 0xA, 2, 6, 2);
            break;
        case 19:                                    /* switch 1 */
            func_080981F0(0x08108BA4, 0, 2, 0, 2);
            func_0809844C(M2C_FIELD(temp_r0, s16 *, 0xA), 4, 0, 0xA, 2, 6, 2);
            break;
        case 20:                                    /* switch 1 */
            func_080981F0(0x08108BAC, 0, 2, 0, 2);
            func_0809844C(M2C_FIELD(temp_r0, s16 *, 0xA), 3, 0, 0xA, 2, 7, 2);
            break;
        case 21:                                    /* switch 1 */
            func_080981F0(0x08108BB4, 0, 2, 0, 2);
            break;
        }
        if (M2C_FIELD(temp_r0, u32 *, 4) & 0x1000) {
            func_080981F0(0x08108BC0, 0, 2, 2, 3);
        }
    }
    if (4 & M2C_FIELD(temp_r0, u16 *, 2)) {
        temp_r0_3 = M2C_FIELD(temp_r0, u8 *, 8);
        switch (temp_r0_3) {                        /* switch 2 */
        case 0:                                     /* switch 2 */
            func_080981F0(0x08108BCC, 0, 2, 6, 4);
            break;
        case 1:                                     /* switch 2 */
            func_080981F0(0x08108BD0, 0, 2, 6, 4);
            break;
        case 2:                                     /* switch 2 */
            func_080981F0(0x08108BD4, 0, 2, 6, 4);
            break;
        case 3:                                     /* switch 2 */
            func_080981F0(0x08108BD8, 0, 2, 6, 4);
            break;
        case 4:                                     /* switch 2 */
            func_080981F0(0x08108BDC, 0, 2, 6, 4);
            break;
        case 5:                                     /* switch 2 */
            func_080981F0(0x08108BE0, 0, 2, 6, 4);
            break;
        }
    } else {
        func_080981F0(0x08108BE4, 0, 2, 4, 4);
    }
    temp_r0_4 = M2C_FIELD(temp_r0, u8 *, 9);
    switch (temp_r0_4) {                            /* switch 3 */
    case 0:                                         /* switch 3 */
        func_08098248(0x08108BEC, 0, 2);
        break;
    case 1:                                         /* switch 3 */
        func_08098248(0x08108BF0, 0, 2);
        break;
    case 2:                                         /* switch 3 */
        func_08098248(0x08108BF4, 0, 2);
        break;
    case 3:                                         /* switch 3 */
        func_08098248(0x08108BF8, 0, 2);
        break;
    case 4:                                         /* switch 3 */
        func_08098248(0x08108BFC, 0, 2);
        break;
    case 5:                                         /* switch 3 */
        func_08098248(0x08108C00, 0, 2);
        break;
    case 7:                                         /* switch 3 */
        func_080981F0(0x08108C04, 0, 2, 3, 4);
        break;
    case 6:                                         /* switch 3 */
        func_080981F0(0x08108C0C, 0, 2, 3, 4);
        break;
    }
    {
        register u32 state_offset asm("r4") = 0x10;
        register s32 state_value asm("r0");

        asm volatile("ldrsh %0, [%1, %2]"
                     : "=l"(state_value)
                     : "l"(temp_r0), "l"(state_offset)
                     : "memory");
        func_0809844C(state_value, 3, 0, 0xA, 2, 7, 5);
    }
    func_080981F0(D_087EE170[temp_r8], 0, 2, 0, 0);
    func_080972C8();
    func_080E66B8();
}
