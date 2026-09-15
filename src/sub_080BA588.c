#include "m2c_prelude.h"

extern volatile u16 D_0300004C;
extern s32 D_02021690;
extern u8 D_0200A880;
extern u8 D_0200A882;
extern u8 D_02032272;
extern u8 D_02030664;
extern u8 D_020218E4[];

void func_08096FBC(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_08098BB4(s32);
void func_080ECD34(s32, s32);
void func_0809AB44(s32, s32, s32, s32, s32);
void func_08094330(void);
void func_08096308(s32, s32);
s32 func_08094484(s32, s32, s32, s32, s32, s32, s32, s32, s32);
u8 *func_0809716C(s32);
void func_0809844C(s32, s32, s32, s32, s32, s32, s32);
void func_080B61C8(s32, s32, s32);
void func_080B65E4(s32);
void func_080B7DC0(void);
void func_080B8280(void);
void func_080B89C8(void);
void func_080B9174(void);
void func_080B9ED0(void);
void func_08094554(s32);
u8 func_080BA540(void);
u8 func_0809669C(void);
void func_080ED17C(s32);

void sub_080BA588(void)
{
    s32 state;
    u8 choice;

    D_0300004C = 0x1840;
    func_08096FBC(3, 1, 0, 0x3C0, 0x3C0, 0, 0xE, 0, 0x3E6, 0xF);
    func_08098BB4(0x08004EB9);
    func_080ECD34(0x081046A8, 0x06015840);
    func_0809AB44(2, 0, 0x1EF, 4, 4);
    func_08094330();
    func_08096308(0xF, 0);

    choice = 0;
    state = 0;
    if (D_02021690 == 8) {
        do {
            switch (state) {
            case 0:
                func_08098BB4(0x08004EC1);
                state = 5;
                break;

            case 5:
                *(s32 *)0x02032B94 = func_08094484(
                    0x08105724, 0x08105758, 0, 0xA0, 0x6C,
                    0x2EA, 0xF, 0x20, 0);
                state = 0x10;
                break;

            case 0x10: {
                u8 *record;
                u8 response;
                s32 offset;
                u8 *base;
                s32 value;
                s32 zero;
                s32 one;

                record = func_0809716C(2);
                zero = 0;
                record[0x16] = choice;
                base = D_020218E4;
                offset = 0x6A04;
                value = *(s32 *)(base + offset);
                one = 1;
                func_0809844C(value, 7, zero, 2, one, one, zero);
                func_08098BB4(0x08004F94);
                func_08098BB4(0x08004F89);
                if (D_0200A882 == 1) {
                    response = D_0200A880;
                    choice = response;
                    switch (choice) {
                    case 0:
                        func_080B61C8(8, 0, 0);
                        if (D_02032272 == 0) {
                            func_08098BB4(0x08004FAE);
                        } else {
                            state = 0x1000;
                        }
                        break;

                    case 1:
                        func_080B65E4(1);
                        if (*(u8 *)0x02032411 == 0) {
                            func_08098BB4(0x08004FE4);
                        } else {
                            state = 0x2000;
                        }
                        break;

                    case 2:
                        func_080B65E4(2);
                        if (*(u8 *)0x02032411 == 0) {
                            func_08098BB4(0x08005010);
                        } else {
                            state = 0x3000;
                        }
                        break;

                    case 3:
                        state = 0x4000;
                        break;

                    case 4:
                        state = 0x5000;
                        break;
                    }
                } else {
                    if (func_080BA540()) {
                        func_08098BB4(0x0800503C);
                    }
                    D_02021690 = 3;
                    func_08096308(0x10, 0);
                }
                break;
            }

            case 0x1000:
                func_080B7DC0();
                state = 0x10;
                break;

            case 0x2000:
                func_08094554(*(s32 *)0x02032B94);
                func_08098BB4(0x08004F8D);
                func_080B8280();
                state = 0;
                break;

            case 0x3000:
                func_08094554(*(s32 *)0x02032B94);
                func_08098BB4(0x08004F8D);
                func_080B89C8();
                state = 0;
                break;

            case 0x4000:
                func_080B9174();
                state = 0x10;
                break;

            case 0x5000:
                func_08094554(*(s32 *)0x02032B94);
                func_080B9ED0();
                state = 5;
                break;
            }
        } while (D_02021690 == 8);
    }

    while (!func_0809669C()) {
        func_080ED17C(1);
    }
    if (D_02030664 == 2) {
        D_02030664 = 1;
        func_080ED17C(1);
    }
}
