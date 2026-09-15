#include "m2c_prelude.h"
extern void func_0809534C();
extern void func_08092E0C();
extern void func_80A016C();
extern void func_80ED17C();
extern u8 D_0203055C[];

s32 sub_080A0338(u8 arg0) {
    s32 temp_r0;
    *(s8 *)0x02030664 = 1;
    temp_r0 = *(s32 *)0x02021690;
    if (temp_r0 != 3) {
        if (temp_r0 == 0xA && D_0203055C[2] == 0xFF) {
            func_0809534C();
            func_08092E0C(7);
        }
        *(s8 *)0x02030666 = 0;
        *(s32 *)0x02031744 = 0;
        *(s32 *)0x02021690 = 3;
        func_80ED17C(1);
        *(s8 *)0x02030666 = 0;
        *(s32 *)0x02031744 = 0;
    }
    func_80A016C(arg0, -1, 0);
    return 0;
}
