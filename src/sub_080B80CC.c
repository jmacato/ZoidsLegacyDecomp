#include "m2c_prelude.h"

M2C_UNK func_08092E84(s32);                         /* extern */
s32 func_08094484(M2C_UNK, M2C_UNK, u8, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_08094554(s32);                         /* extern */
M2C_UNK func_08094564(s32, u8);                     /* extern */
M2C_UNK func_08095114(s32);                         /* extern */
M2C_UNK func_08095208(M2C_UNK, M2C_UNK, s32);       /* extern */
M2C_UNK func_0809534C();                            /* extern */
M2C_UNK func_0809538C(s32, s32, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_08096F3C();                            /* extern */
M2C_UNK func_08098BB4(M2C_UNK);                     /* extern */
M2C_UNK func_0809A1BC(M2C_UNK, M2C_UNK, s32);       /* extern */
s32 func_0809A35C();                                 /* extern */
M2C_UNK func_080ECD34(M2C_UNK, M2C_UNK);            /* extern */
M2C_UNK func_080ECD38(s32, s32);                    /* extern */
M2C_UNK func_080ED17C(s32);                         /* extern */

u8 sub_080B80CC(u32 arg0, u32 arg1) {
    s32 temp_r7;
    register u32 temp_r0 asm("r9");
    u8 temp_r4;
    u8 var_r6;
    void *temp_r4_2;
    register u8 *palette2 asm("r8");

    temp_r0 = (u8)arg0;
    var_r6 = arg1;
    func_080ECD34(0x081065C8, 0x060177C0);
    func_0809A1BC(0x081067EC, 0x050003C0, 0x02002880);
    func_0809538C(1, 0xF0, 0x80, 0, 0, 0, 0x37, 0x3F);
    /* The final two arguments occupy the existing outgoing stack area. */
    asm volatile(
        "str r4, [sp, #0]\n\t"
        "str r5, [sp, #4]"
        :
        :
        : "memory");
    *(s32 *)0x02033F3C = func_0809A35C(temp_r0, var_r6, 3, 1);
    *(s16 *)0x04000008 = 0x18D;
    *(u16 *)0x0300004C |= 0x100;
    {
        s32 *display_state = (s32 *)0x03000054;
        display_state[0] = 0x1000;
        display_state[1] = 0;
    }
    func_08098BB4(0x08005629);
    temp_r7 = func_08094484(0x08106DD4, 0x08106E34, var_r6, 4, 4, 0x3BE, 0xE, 8, 0);
    func_08096F3C();
    {
        register u32 palette2_value asm("r0") = 0x80;
        asm volatile(
            "add r0, r0, r5\n\t"
            "mov r8, r0"
            : "+r"(palette2_value), "=r"(palette2)
            :
            : "cc");
    }
    do {
        func_080ED17C(1);
        temp_r4 = var_r6;
        if ((0x40 & *(u16 *)0x03006034) && (var_r6 != 0)) {
            var_r6 -= 1;
            func_08092E84(0x40);
        }
        if ((0x80 & *(u16 *)0x03006034) && ((u32)var_r6 <= 6U)) {
            var_r6 += 1;
            func_08092E84(0x40);
        }
        if (var_r6 != temp_r4) {
            s32 *first_table = (s32 *)0x087A641C;
            s32 *second_table;

            asm volatile("" : "+r"(first_table));
            temp_r4_2 = (void *)((var_r6 * 4) + (temp_r0 << 5));
            func_080ECD38(*(s32 *)((u32)temp_r4_2 + (u32)first_table), 0x02002880);
            *(u16 *)0x02002880 = *(u16 *)0x05000000;
            func_08095208(0x02002880, 0x05000000, 0x80);
            second_table = (s32 *)0x087A8F24;
            asm volatile("" : "+r"(second_table));
            temp_r4_2 = (void *)((u32)temp_r4_2 + (u32)second_table);
            func_080ECD38(*(s32 *)temp_r4_2, (s32)palette2);
            func_08095208((s32)palette2, 0x05000200, 0x20);
            func_08094564(temp_r7, var_r6);
        }
    } while (!(3 & *(u16 *)0x0300000E));
    func_0809534C();
    *(u16 *)0x0300004C = 0xFEFF & *(u16 *)0x0300004C;
    func_08094554(temp_r7);
    func_08095114(*(s32 *)0x02033F3C);
    return var_r6;
}
