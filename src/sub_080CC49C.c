#include "m2c_prelude.h"
#define NULL ((void *)0)

M2C_UNK func_080CC400(s32, s16, s16);               /* extern */
void *func_080E669C();                              /* extern */
M2C_UNK func_080E66B8();                            /* extern */
void func_080E8C90(u32, u32, u32, u32, void *);     /* extern */
s32 func_080ECD98(s32, s32);                        /* extern */
s32 func_080ECE30(s32, s32);                         /* extern */
u8 func_080ECF00(s32, s32);                          /* extern */
s32 func_080ECF78(s32, s32);                         /* extern */


extern u8 D_02034B4C[];
extern s32 *D_02033F58[];

#define SEL0() ({ u8 *b = D_02034B4C; u32 o = 0xA1AF; u8 *p1 = b + o; u32 ix = *p1; o += 1; b += o; *(u8 *)(ix + (u32) b); })
#define T38(x) var_r4 = (u16) (((2 - (x)) << 5) + 0x18)
#define T37() do { var_r5 = ((1 - func_080ECD98(var_r4, 3)) << 5) + 0x18; T38(func_080ECE30(var_r4, 3)); } while (0)
#define SEL() ({ register u8 *b asm("r0"); register u32 o asm("r2"); register u8 *p1 asm("r1"); b = D_02034B4C; o = 0xA1AF; p1 = b + o; o += 4; b += o; b[*p1]; })
void sub_080CC49C(u8 arg0) {
    s32 *temp_r2;
    s32 var_r6;
    register s32 var_r0 asm("r0");
    s32 var_r4;
    s16 var_r5;
    u32 temp_r0_3;
    u8 temp_r0_2;
    void *temp_r0;

    temp_r0 = func_080E669C();
    {
        register u8 *b asm("r2");
        register u32 o asm("r6");
        u32 ix;

        func_080E8C90(*(u8 *)0x02033F36, *(u8 *)0x02033F37,
                      ({ b = D_02034B4C; o = 0xA1AF; ix = *(b + o); o += 1; b += o; *(u8 *)(ix + (u32) b); }),
                      ix, temp_r0);
    }
    var_r6 = 1;
loop_1:
    temp_r2 = D_02033F58[var_r6];
    *temp_r2 &= 0xFFFFEFFF;
    temp_r0_2 = M2C_FIELD(temp_r0, u8 *, 9);
    if ((u32) temp_r0_2 <= 5U) {
        goto block_3;
    }
    goto block_39;
block_3:
    switch (temp_r0_2) {                            /* switch 1 */
case 0:                                             /* switch 1 */
    var_r4 = SEL();
    var_r5 = ((1 - func_080ECF00(var_r4, 3)) << 5) + 0x18;
    var_r0 = (u8) func_080ECF78(var_r4, 3);
    asm("@ e1");
    T38(var_r0);
    goto block_39;
case 1:                                             /* switch 1 */
    if ((u8) var_r6 != 1) {
        goto block_9;
    }
    var_r4 = SEL();
    var_r5 = ((var_r6 - func_080ECF00(var_r4, 3)) << 5) + 0x18;
    var_r0 = (u8) func_080ECF78(var_r4, 3);
    asm("@ e2");
    T38(var_r0);
    goto block_39;
block_9:
    var_r4 = SEL();
    var_r4 += 3;
    T37();
    goto block_39;
case 2:                                             /* switch 1 */
    if ((u8) var_r6 != 1) {
        goto block_12;
    }
    var_r4 = SEL();
    var_r5 = ((var_r6 - func_080ECF00(var_r4, 3)) << 5) + 0x18;
    var_r0 = (u8) func_080ECF78(var_r4, 3);
    asm("@ e3");
    T38(var_r0);
    goto block_39;
block_12:
    var_r4 = SEL();
    var_r4 += 1;
    T37();
    goto block_39;
case 3:                                             /* switch 1 */
    if ((u8) var_r6 == 1) {
        goto block_16;
    }
    if (var_r6 == 2) {
        goto block_24;
    }
    var_r4 = SEL();
    var_r4 += 2;
    T37();
    goto block_39;
block_16:
    var_r4 = SEL();
    var_r5 = ((var_r6 - func_080ECF00(var_r4, 3)) << 5) + 0x18;
    var_r0 = (u8) func_080ECF78(var_r4, 3);
    asm("@ e4");
    T38(var_r0);
    goto block_39;
case 4:                                             /* switch 1 */
    if (var_r6 == 2) {
        goto block_24;
    }
    if (var_r6 > 2) {
        goto block_21;
    }
    if ((u8) var_r6 == 1) {
        goto block_23;
    }
    goto block_27;
block_21:
    if (var_r6 == 3) {
        goto block_26;
    }
    goto block_27;
block_23:
    var_r4 = SEL();
    var_r5 = ((var_r6 - func_080ECF00(var_r4, 3)) << 5) + 0x18;
    var_r0 = (u8) func_080ECF78(var_r4, 3);
    asm("@ e5");
    T38(var_r0);
    goto block_39;
block_24:
    var_r4 = SEL();
    var_r4 += 1;
    var_r5 = ((1 - func_080ECD98(var_r4, 3)) << 5) + 0x18;
    var_r4 = (u16) (((var_r6 - func_080ECE30(var_r4, 3)) << 5) + 0x18);
    goto block_39;
block_26:
    var_r4 = SEL();
    var_r4 += 3;
    T37();
    goto block_39;
block_27:
    var_r4 = SEL();
    var_r4 += 4;
    T37();
    goto block_39;
case 5:                                             /* switch 1 */
    temp_r0_3 = var_r6 - 1;
    if (temp_r0_3 > 4U) {
        goto block_36;
    }
    switch (temp_r0_3) {                            /* switch 2 */
case 0:                                             /* switch 2 */
    var_r4 = SEL();
    var_r5 = ((1 - func_080ECF00(var_r4, 3)) << 5) + 0x18;
    var_r0 = (u8) func_080ECF78(var_r4, 3);
    asm("@ e6");
    T38(var_r0);
    goto block_39;
case 1:                                             /* switch 2 */
    var_r4 = SEL();
    var_r4 += 1;
    T37();
    goto block_39;
case 2:                                             /* switch 2 */
    var_r4 = SEL();
    var_r4 += 2;
    T37();
    goto block_39;
case 3:                                             /* switch 2 */
    var_r4 = SEL();
    var_r4 += 3;
    T37();
    goto block_39;
case 4:                                             /* switch 2 */
    var_r4 = SEL();
    var_r4 += 4;
    T37();
    goto block_39;
    }
block_36:
    var_r4 = SEL();
    var_r4 += 5;
    }
    T37();
block_39:
    if (arg0 != 0) {
        goto block_41;
    }
    var_r5 = 0x50 - (s16) var_r5;
    { s32 t = 0x70; t -= (s16) var_r4; var_r4 = (u16) t; }
block_41:
    func_080CC400(var_r6, (s16) var_r5, (s16) var_r4);
    var_r6 = (s32) (u8) (var_r6 + 1);
    if ((u32) var_r6 > 6U) {
        goto block_43;
    }
    goto loop_1;
block_43:
    func_080E66B8();
    return;
}
