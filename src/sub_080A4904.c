#include "m2c_prelude.h"
extern void func_809F94C();
extern void func_80A016C();
extern void func_8094564();
extern s32 D_02031940[];

s32 sub_080A4904(u8 arg0, u8 **arg1) {
    u8 *p;
    p = *arg1;
    func_809F94C(p[1], p[2], p[3],
                 (s16)((p[5] << 8) + p[4]),
                 (s32)(s16)((p[7] << 8) + p[6]),
                 (s32)p[8]);
    func_80A016C(arg0, -1, 0);
    return 0;
}

s32 sub_080A4958(u8 arg0, u8 **arg1) {
    s32 *base;
    u8 *p;
    base = D_02031940;
    p = *arg1;
    func_8094564(base[p[1]], p[2]);
    func_80A016C(arg0, -1, 0);
    return 0;
}
