#include "m2c_prelude.h"

void func_08092D8C(s32, s32);
void func_08092E0C(s32);
void func_0809538C(s32, s32, s32, s32, s32, s32, s32, s32);
void func_08096308(s32, s32);
s32 func_0809669C(void);
void func_08098BB4(s32);
void func_0809AEA0(void);
void func_0809AEC0(s32, s32, s32);
u8 func_0809AEF4(void);
void func_0809B00C(s32, s32, s32);
s32 func_0809B040(void);
void func_080ED17C(s32);

extern u8 D_02032E54;
extern u8 D_02032E55;
extern u8 D_02032E56;
extern u8 D_02032E57;
extern u8 D_02032E58;
extern s32 D_02021690;

void sub_080E1438(void) {
    s32 temp_r0;
    u8 *p = &D_02032E54;

    *p = 0;
    D_02032E55 = 0;
    D_02032E56 = 0;
    func_0809B00C((s32)&D_02032E58, 1, 0x081091F0);
    while (1) {
    if (*p == 1) {
        func_0809AEC0((s32)&D_02032E57, 1, 0x081091F0);
        *p = 2;
    }
    if (*p == 2) {
        D_02032E55 = func_0809AEF4();
    }
    temp_r0 = func_0809B040();
    D_02032E56 = temp_r0;
    if ((D_02032E55 != 0 && D_02032E57 != 0) ||
        ((temp_r0 << 24) != 0 && D_02032E58 != 0)) {
    func_08092E0C(1);
    func_0809AEA0();
    func_0809538C(1, 0x30C0, 0x2878, 0, 0, 0, 0x2F, 0x3F);
    func_08098BB4(0x08028B81);
    D_02021690 = -1;
    func_08096308(0x12, 0);
    goto poll_test;
poll_body:
    func_080ED17C(1);
poll_test:
    if ((func_0809669C() << 24) == 0) {
        goto poll_body;
    }
    func_08092E0C(3);
    func_08092E0C(4);
    func_08092E0C(5);
    func_08092E0C(6);
    func_08092E0C(7);
    func_08092E0C(8);
    D_02021690 = 2;
    func_08092D8C(1, 0x0809A0B1);
    return;
    }
    func_080ED17C(1);
    }
}
