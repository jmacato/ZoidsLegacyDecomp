#include "m2c_prelude.h"
extern u8 D_020325A0[];
extern u8 D_02032998;
extern s32 D_02032990;
void sub_080A9888(void) {
    u8 i = 0;
    do {
        *(s32 *)&D_020325A0[i * 0x48] = 0;
        i++;
    } while (i <= 0xD);
    D_02032998 = 0xFF;
    D_02032990 = 0;
}
