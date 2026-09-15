#include "m2c_prelude.h"
extern u8 D_02034B4C[];
extern u8 D_0203055C[];

u8 func_080BF464(u8, u8, s32);
M2C_UNK func_080BFD20(u8, u8);
M2C_UNK func_080BFE30(u8, u8);
M2C_UNK func_080E5538(void *);
M2C_UNK func_080E5674(void *);
M2C_UNK func_080E570C(void *, void *, s32);
M2C_UNK func_080E57D0(void *);
M2C_UNK func_080E6830(void *, void *, s32);

void sub_080E8B08(s32 arg0, s32 arg1) {
    s16 temp_r1;
    s32 var_r7;
    register u32 temp_r0 asm("r0");
    u8 temp_r5;
    u8 temp_r6;
    void *temp_r4;
    void *var_r8;

    arg0 <<= 24;
    temp_r6 = (u32)arg0 >> 24;
    arg1 <<= 24;
    temp_r5 = (u32)arg1 >> 24;
    {
        u32 row_offset;
        u32 col_offset;
        u8 *base;

        row_offset = temp_r6 * 0x1380;
        col_offset = temp_r5 * 0x270;
        base = (u8 *)0x02034B4C;
        asm volatile("" : "+r"(base));
        col_offset += (u32)base;
        temp_r4 = row_offset + col_offset;
    }
    if (func_080BF464(temp_r6, temp_r5, 0x18) == 0xFF) {
        var_r8 = temp_r4 + 0x70;
    } else {
        var_r8 = 0;
    }
    if (M2C_FIELD(var_r8, u8 *, 0x31) == 0) {
        goto no_aux;
    }
    if (func_080BF464(temp_r6, temp_r5, 0x17) == 0xFF) {
        goto no_aux;
    }
    {
        register s32 selected asm("r7");

        selected = (s32)temp_r4 + 0xB0;
        asm volatile("" : "+r"(selected));
        var_r7 = selected;
    }
    goto aux_done;
no_aux:
    {
        register s32 selected asm("r7");

        selected = 0;
        asm volatile("" : "+r"(selected));
        var_r7 = selected;
    }
aux_done:
    func_080E5538(temp_r4);
    func_080BFD20(temp_r6, temp_r5);
    func_080E5674(temp_r4);
    func_080E6830(temp_r4, var_r8, var_r7);
    if ((D_0203055C[1] == 0xB) && !(0xC0 & M2C_FIELD(temp_r4, u8 *, 0x36))) {
        temp_r1 = M2C_FIELD(temp_r4, s16 *, 0x44);
        M2C_FIELD(temp_r4, s16 *, 0x44) = (s16)((s32)(temp_r1 + ((u32)temp_r1 >> 31)) >> 1);
    }
    temp_r0 = func_080BF464(temp_r6, temp_r5, 0x14);
    if (temp_r0 != 0xFF) {
        register u32 offset asm("r1");
        register u32 work asm("r0");
        register u8 *base asm("r2");

        base = D_02034B4C;
        asm volatile("" : "+r"(base));
        offset = temp_r0 * 0xC;
        work = temp_r5 * 0x270;
        offset += work;
        work = temp_r6 * 0x1380;
        offset += work;
        offset += (u32)base;
        offset += 0xEA;
        temp_r0 = *(u16 *)offset;
        {
            register u16 *dest asm("r2");

            dest = (u16 *)((u8 *)temp_r4 + 0x4A);
            *dest = temp_r0;
        }
    }
    func_080E57D0(temp_r4);
    func_080E570C(temp_r4, var_r8, var_r7);
    func_080BFE30(temp_r6, temp_r5);
    func_080E57D0(temp_r4);
    if ((s32)M2C_FIELD(temp_r4, s16 *, 6) > (s32)(s16)M2C_FIELD(temp_r4, u16 *, 0x3A)) {
        M2C_FIELD(temp_r4, s16 *, 6) = (s16)M2C_FIELD(temp_r4, u16 *, 0x3A);
    }
    if ((s32)M2C_FIELD(temp_r4, s16 *, 8) > (s32)(s16)M2C_FIELD(temp_r4, u16 *, 0x3E)) {
        M2C_FIELD(temp_r4, s16 *, 8) = (s16)M2C_FIELD(temp_r4, u16 *, 0x3E);
    }
}
