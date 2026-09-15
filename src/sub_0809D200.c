#include "m2c_prelude.h"
void func_8096FBC(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_80ECD34(s32, s32);
void func_809AB44(s32, s32, s32, s32, s32);
void func_8094330(void);
void func_8098BB4(s32);
void func_809D094(void);
u8 *func_809716C(s32);
void func_8096308(s32, s32);

void sub_0809D200(void) {
    *(s16 *)0x0300004C = 0x1140;
    func_8096FBC(0, 1, 0, 0x3C0, 0x3C0, 0, 0xE, 0, 0x3E6, 0xF);
    func_80ECD34(0x081046A8, 0x06015840);
    func_809AB44(2, 3, 0, 0, 1);
    func_8094330();
    func_8098BB4(0x08000B77);
    func_809D094();
    func_809716C(0)[0x16] = *(u8 *)0x020216F4;
    func_8096308(0xF, 0);
}
