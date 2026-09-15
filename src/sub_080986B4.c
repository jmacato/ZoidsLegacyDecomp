#include "m2c_prelude.h"
struct S986 { s32 unk0; s32 pad4; u16 unk8; u16 unkA; s16 unkC; s16 unkE; };
extern struct S986 *func_0809716C(u8);
extern void func_08097980(u16);
extern u32 D_02021664;
extern u16 D_02021668;
extern s32 D_02021670;
void sub_080986B4(u8 arg0) {
    struct S986 *s = func_0809716C(arg0);
    u16 *p = (u16 *)(s->unk8 * 2 + (u32)s + 0x20);
    int i = 1;
    while (i < (s32)(s->unkA - 1)) {
        int j = 1;
        if (j < (s32)(s->unk8 - 1)) {
            do {
                u32 v = *p & 0x3FF;
                s32 sv = v;
                u32 base = D_02021664;
                if (v < base || v >= base + 0x40) {
                    func_08097980((u16)(sv - D_02021670));
                }
                *p = (D_02021664 + 1) | D_02021668;
                p += 1;
                j += 1;
            } while (j < (s32)(s->unk8 - 1));
        }
        p += 2;
        i += 1;
    }
    s->unkE = 0;
    s->unkC = 0;
    s->unk0 = s->unk0 | 2;
}
