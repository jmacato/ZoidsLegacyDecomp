#include "m2c_prelude.h"

M2C_UNK func_080BF4C0(u8, u8, void *);
M2C_UNK func_080BF514(u8, u8, u8);
M2C_UNK func_080E8B08(u8, u8);
s32 func_080E9D88(u8, u8);
extern u8 D_02034B4C;

struct E {
    u8 pad[4];
    u16 field;
    u8 rest[6];
};

struct I {
    u8 hdr[0xE4];
    struct E e[32];
    u8 rest[12];
};

struct M {
    struct I i[8];
};

void sub_080BF984(s32 arg0, s32 arg1) {
    u16 temp_r1;
    u8 temp_r0;
    u8 temp_r6;
    u8 temp_r7;
    u8 var_r8;
    struct I *temp_r2;
    struct E *temp_r5;
    register s32 row4 asm("r10");
    register s32 col4 asm("r9");
    register u16 parent_value asm("r12");

    arg0 <<= 24;
    temp_r7 = (u32)arg0 >> 24;
    arg1 <<= 24;
    temp_r6 = (u32)arg1 >> 24;
    if ((func_080E9D88(temp_r7, temp_r6) << 24) != 0) {
        var_r8 = 0;
        row4 = temp_r7 << 2;
        {
            register s32 col_tmp asm("r3");

            col_tmp = temp_r6 << 2;
            asm volatile("" : "+r"(col_tmp));
            col4 = col_tmp;
        }
        do {
            temp_r2 = (struct I *)((u8 *)&D_02034B4C
                + (((row4 + temp_r7) * 8 - temp_r7) << 7)
                + (((col4 + temp_r6) * 8 - temp_r6) << 4));
            {
                register s32 index_tmp asm("r3");
                s32 index_offset;

                index_tmp = var_r8;
                index_offset = ((index_tmp << 1) + var_r8) << 2;
                index_offset += 0xE4;
                temp_r5 = (struct E *)((u8 *)temp_r2 + index_offset);
                asm volatile("" :: "r"(index_tmp));
            }
            temp_r1 = temp_r5->field;
            if (temp_r1 != 0) {
                if ((temp_r1 & 0x7F) == 0x1A) {
                    goto activate;
                }
                {
                    register s32 mask asm("r4");
                    register s32 bits asm("r0");

                    mask = 0xE000;
                    asm volatile("" : "+r"(mask));
                    bits = mask;
                    bits &= temp_r1;
                    if (bits != 0x4000) {
                        goto after_effect;
                    }
                }
                {
                    register u16 parent_input asm("r3");

                    parent_input = *(u16 *)((u8 *)temp_r2 + 8);
                    asm volatile("" : "+r"(parent_input));
                    parent_value = parent_input;
                }
                if (*(s16 *)((u8 *)temp_r2 + 8) >=
                    (s16)*(u16 *)((u8 *)temp_r5 + 8)) {
                    goto subtract;
                }
activate:
                func_080BF514(temp_r7, temp_r6, var_r8);
                goto after_effect;
subtract:
                *(u16 *)((u8 *)temp_r2 + 8) = parent_value -
                    *(u16 *)((u8 *)temp_r5 + 8);
after_effect:
                func_080BF4C0(temp_r7, temp_r6, temp_r5);
            }
            temp_r0 = var_r8 + 1;
            var_r8 = temp_r0;
        } while ((u32)temp_r0 <= 0x1F);
        func_080E8B08(temp_r7, temp_r6);
    }
}
