#include "m2c_prelude.h"
extern u8 D_02033FD0;
extern u8 D_02034050;
s32 func_80D0AE4();                                    /* extern */
M2C_UNK func_80D1090();                                /* extern */
M2C_UNK func_80D12A0(s32, s32);                        /* extern */
s32 func_80D18CC();                                    /* extern */
M2C_UNK func_80D18F0();                                /* extern */
s32 func_80D1A24();                                    /* extern */
M2C_UNK func_80D1A44();                                /* extern */
s32 func_80D1B58();                                    /* extern */

void sub_080D1B78(void) {
    s32 temp_r0;

    func_80D18F0();
    func_80D1A44();
    if (M2C_FIELD((void *)((u32)&D_02033FD0), u8 *, 0) != 0) {
        if (((func_80D1A24() << 0x18) != 0) && ((func_80D1B58() << 0x18) != 0) && ((func_80D0AE4() << 0x18) != 0)) {
            if ((M2C_FIELD((void *)((u32)&D_02033FD0), s32 *, 0xC) & 0xFFFF00) == 0x200) {
                func_80D12A0(0xD, 0);
            }
            func_80D1090();
            if ((M2C_FIELD((void *)((u32)&D_02033FD0), u8 *, 0) == 2) && ((func_80D18CC() << 0x18) != 0)) {
                temp_r0 = *(s32 *)((u32)&D_02034050) + 1;
                *(s32 *)((u32)&D_02034050) = temp_r0;
                if (temp_r0 == 0x1E) {
                    M2C_FIELD((void *)((u32)&D_02033FD0), u8 *, 0) = 0U;
                }
            }
        }
        if ((*(u8 *)0x02030664 != 1) && (2 & *(u16 *)0x0300000C)) {
            M2C_FIELD((void *)((u32)&D_02033FD0), u8 *, 0) = 3U;
        }
    }
}
