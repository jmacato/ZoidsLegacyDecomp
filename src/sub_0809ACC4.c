#include "m2c_prelude.h"
s32 func_0809669C(void);
void func_0809AC98(void);
void func_08092E0C(s32);
void func_08096308(s32, s32);
void func_080ED17C(s32);
void func_08092D8C(s32, s32);
void func_08098BB4(s32);

struct X {
    s32 flags;
    u8 rest[0x34];
};

void func_08094554(struct X *);

extern s32 D_02021690;
extern u8 D_02021698;

s32 sub_0809ACC4(u8 arg0) {
    u8 temp_r1;
    u8 *p;

    if ((*(s32 *)0x030009E8 & 0x3F0F) == 0x303) {
        *(u8 *)0x0300605A = 0;
        temp_r1 = *(u8 *)0x0300603D;
        if (temp_r1 != 0) {
            *(u8 *)0x03000075 = temp_r1;
            *(u8 *)0x0300603D = 0;
        }
        return 1;
    }
    p = (u8 *)0x0300605A;
    if (arg0 != 0) {
        *p = *p + 1;
    }
    if (*p <= 0x3B) {
        return 0;
    }
    return 2;
}

void sub_0809AD2C(void) {
    s32 temp_r0_2;
    s32 temp_r0_4;
    u8 temp_r0;
    u8 var_r4;
    struct X *base;
    struct X *p;

    while (1) {
        if ((func_0809669C() << 0x18) != 0) {
            temp_r0 = sub_0809ACC4(1);
            if (temp_r0 == 0) {
                if (*(u8 *)0x0300603D == 0) {
                    *(u8 *)0x0300603D = *(u8 *)0x03000075;
                    *(u8 *)0x03000075 = 1;
                }
            } else if (temp_r0 == 2) {
                func_08092E0C(1);
                func_0809AC98();
                *(u16 *)0x030009EC |= 4;
                var_r4 = 0;
                base = (struct X *)0x03003FE4;
                do {
                    p = (struct X *)(var_r4 * 0x38 + (s32)base);
                    if ((p->flags & 0xC0) == 0) {
                        func_08094554(p);
                    }
                    temp_r0_4 = var_r4 + 1;
                    temp_r0_2 = temp_r0_4 << 0x18;
                    var_r4 = temp_r0_4;
                } while (temp_r0_2 >= 0);
                func_08098BB4(0x080283AC);
                D_02021690 = -1;
                func_08096308(0x12, 0);
                while ((func_0809669C() << 0x18) == 0) {
                    func_080ED17C(1);
                }
                func_08092E0C(2);
                func_08092E0C(3);
                func_08092E0C(4);
                func_08092E0C(5);
                func_08092E0C(6);
                func_08092E0C(7);
                func_08092E0C(8);
                D_02021690 = 1;
                D_02021698 = 0;
                func_08092D8C(1, 0x0809A0B1);
                return;
            }
        }
        func_080ED17C(1);
    }
}
