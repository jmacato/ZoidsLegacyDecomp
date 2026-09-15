#include "m2c_prelude.h"
extern u8 D_0203055C[];
M2C_UNK func_8092D8C(s32, M2C_UNK);                    /* extern */
M2C_UNK func_8094330();                                /* extern */
M2C_UNK func_809538C(s32, s32, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8096FBC(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_809A848(u8, s32, s32, s32, s32);          /* extern */
M2C_UNK func_80BAC54();                                /* extern */
M2C_UNK func_80C9EE0();                                /* extern */
M2C_UNK func_80ECD28(M2C_UNK, M2C_UNK, s32);           /* extern */

void sub_080BB940(void) {
    *(s16 *)0x0300004C = 0x1741;
    M2C_FIELD((void *)0x04000008, s16 *, 0) = 0x87;
    M2C_FIELD((void *)0x04000008, s16 *, 4) = 0x218B;
    func_8094330();
    func_80BAC54();
    func_8096FBC(1, 2, 0x80, 0x340, 0x3C0, 2, 0xE, 0, 0x3E6, 0xF);
    func_809A848(D_0203055C[1], 2, 1, 1, 0);
    func_809538C(1, 0, 0, 0, 0, 0, 0x3B, 0x3E);
    func_80ECD28(0x08277CE4, 0x050003C0, 8);
    func_80C9EE0();
    *(s8 *)0x03000075 = 2;
    *(s8 *)0x0300603D = 2;
    func_8092D8C(7, 0x080BB8ED);
}
