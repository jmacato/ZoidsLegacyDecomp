#include "m2c_prelude.h"
void func_809A1BC(s32, s32, s32);
void func_80ECD34(s32, s32);
extern s32 D_087AF604[];
extern u8 D_087ADBB8[];

void sub_0809A94C(u16 arg0, u8 arg1, u8 arg2, u16 arg3, s32 arg4) {
    u16 temp_r6;
    void *temp_r5;
    u32 a0;
    u32 t;

    temp_r6 = (u16) arg4;
    a0 = arg0 << 6;
    t = (arg1 << 3) + (u32)D_087ADBB8;
    temp_r5 = (void *)(a0 + t);
    func_80ECD34(M2C_FIELD(temp_r5, s32 *, 0), (arg3 << 5) + 0x06010000);
    if (arg0 != 0x4B) {
        func_809A1BC(M2C_FIELD(temp_r5, s32 *, 4), (temp_r6 << 5) + 0x05000200, 0x02002880);
        return;
    }
    func_809A1BC(D_087AF604[arg2], (temp_r6 << 5) + 0x05000200, 0x02002880);
}
