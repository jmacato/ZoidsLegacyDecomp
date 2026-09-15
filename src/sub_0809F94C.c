#include "m2c_prelude.h"
void *func_08094374(s32, u8, u8, s16, s32, s32, s32, s32, s32);
extern void *D_02031940[];
extern u16 D_020317DC[];
extern u16 D_020317FC[];
extern u16 D_0203181C[];
extern s32 D_087AFA94;

void sub_0809F94C(u8 arg0, u8 arg1, u8 arg2, u16 arg3, u16 arg4, u8 arg5) {
    u8 i;
    s32 flags;
    s32 mode = arg5;

    if (D_02031940[arg0] == 0) {
        i = 0;
        do {
            if (D_020317DC[i] == arg1) {
                flags = 0x10C0;
                if (mode == 1) goto mode_1;
                if (mode <= 1) goto have_flags;
                if (mode == 2) goto mode_2;
                goto have_flags;
mode_1:
                flags |= 0x20;
                goto have_flags;
mode_2:
                flags |= 0x10;
have_flags:
                D_02031940[arg0] = func_08094374((s32)&D_087AFA94,
                    arg1, arg2, (s16)arg3, (s16)arg4,
                    D_020317FC[i], D_0203181C[i], flags, 0);
                return;
            }
            i += 1;
        } while ((u32)i <= 0xFU);
    }
}
