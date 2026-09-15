#include "m2c_prelude.h"
extern int func_8092E0C();
extern int func_80A016C();

extern s32 D_02021690;
extern s32 D_03000054[];
extern s32 D_02031980;
extern s32 D_02031984;
extern u8  D_020316F4;
extern s32 D_02032E88[];
extern u16 D_020324A4[];
extern s32 D_030033C4[];

int sub_080A226C(u8 arg0) {
    s32 x, y, v;

    func_8092E0C(5);
    if (D_02021690 == 3) {
        x = D_03000054[0] - D_02031980;
        D_03000054[0] = x;
        D_03000054[1] = D_03000054[1] - D_02031984;
        if (D_020316F4 != 0 && D_02032E88[1] != 0) {
            if (x < 0) {
                D_03000054[0] = 0;
            } else {
                v = (D_020324A4[0] << 11) - 0xF000;
                if (x > v) {
                    D_03000054[0] = v;
                }
            }
            y = D_03000054[1];
            if (y < 0) {
                D_03000054[1] = 0;
            } else {
                v = (D_020324A4[1] << 11) - 0xA000;
                if (y > v) {
                    D_03000054[1] = v;
                }
            }
            D_03000054[2] = D_03000054[0];
            D_03000054[3] = D_03000054[1];
        }
    } else {
        D_030033C4[6] = 0x58;
    }
    func_80A016C(arg0, -1, 0);
    return 0;
}
