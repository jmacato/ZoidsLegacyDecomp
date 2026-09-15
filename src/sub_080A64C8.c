#include "m2c_prelude.h"
struct SA { u8 unk0; u8 unk1; u8 unk2; u8 unk3; u8 rest[0x6C]; };
extern struct SA D_020218E8[];
struct SQ { u8 q0; u8 unk1; };
extern s32 D_020217B4[];

extern u8 func_080E5320(void *, u8);
extern void func_080A016C(u8, s32, s32);

s32 sub_080A64C8(u8 arg0, struct SQ **arg1) {
    u8 i = 1;
    struct SA *base = D_020218E8;
    u8 *t = (u8 *)base - 4;
    s32 one = 1;
    s32 *r7B4 = D_020217B4;
    for (; i <= 0xCE; i++) {
        struct SA *p = (struct SA *)(i * 0x70 + (s32)base);
        u8 kind = t[(p->unk2 << 6) + 0x5A94];
        if ((kind == 0x1E || kind == 0x5F) && (u8)(p->unk0 - 0x19) <= 5) {
            u32 v;
            u32 m;
            register s32 *slot asm("r3");
            p->unk3 = (one << (*arg1)->unk1) | p->unk3;
            v = func_080E5320(p, (*arg1)->unk1) << 0x18;
            slot = &r7B4[v >> 0x1D];
            m = 0x1F000000;
            m &= v;
            *slot |= one << (m >> 0x18);
            break;
        }
    }
    func_080A016C(arg0, -1, 0);
    return 0;
}
