#include "m2c_prelude.h"
extern void func_80E5880(void *, void *);
extern void func_80E700C(u8);

struct S4 {
    u8 _p0[2];
    u8 f2;
    u8 _p3;
    u16 f4;
    u16 f6;
    u8 _p8[0x68];
};
struct S7 {
    u8 _p0;
    u8 f1;
    u16 f2;
    u8 _p4[0x3c];
};

extern struct S4 D_020218E8[];

void sub_080E6FA0(u8 arg0, u8 arg1) {
    struct S4 *p4 = &D_020218E8[arg1];
    struct S7 *p7 = (struct S7 *)((char *)D_020218E8 + 0x5A90) + arg0;
    u16 saved = p4->f6;
    func_80E700C(arg0);
    if (p4->f2 != 0) {
        func_80E700C(p4->f2);
    }
    p4->f2 = arg0;
    p7->f1 = arg1;
    p4->f6 = saved;
    func_80E5880(p4, p7);
    if (4 & p4->f4) {
        p7->f2 |= 4;
    }
}
