#include "m2c_prelude.h"
struct T1 {
    u8 field0;
    u8 pad1[0xF];
    s16 field10;
    u8 pad2[0x5E];
};

struct T2 {
    u8 pad[8];
    s32 field8;
};

extern struct T1 D_020218E8[];
extern struct T2 D_087B1E04[];
extern M2C_UNK func_80E522C(s32, s32);

s32 sub_080E67F0(u8 arg0) {
    struct T1 *p = &D_020218E8[arg0];
    s32 v = p->field10;
    return func_80E522C(D_087B1E04[p->field0].field8, v / 4 + 0x64);
}
