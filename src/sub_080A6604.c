#include "m2c_prelude.h"
extern int func_80ED038();
extern int func_80A016C();
extern u8 D_020282EC[];
extern u8 D_020218E4[];
extern u8 D_0202EEC0[];
extern u8 D_0202ECF4[];

int sub_080A6604(u8 arg) {
    func_80ED038(D_020282EC, D_020218E4, 0x6a08);
    func_80ED038(D_0202EEC0, D_0202ECF4, 460);
    func_80A016C(arg, -1, 0);
    return 0;
}
