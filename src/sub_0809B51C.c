#include "m2c_prelude.h"

extern void func_08092E0C(s32);
extern void func_0809534C(void);
extern void func_08096308(s32, s32);
extern s32 func_0809669C(void);
extern void func_0809FCB0(void);
extern void func_080D120C(void);
extern void func_080ED17C(s32);
extern u8 D_02021698;

void sub_0809B51C(void)
{
    s32 done;
    u32 choice;

    done = 0;
    goto outer_test;

outer_body:
    if ((*(u16 *)0x0300000E & 8) == 0) {
        goto tick;
    }
    if ((func_0809669C() << 24) != 0) {
        if ((*(u16 *)0x0300004E == 0xFF) &&
            (*(u16 *)0x03000052 == 0x10)) {
            goto complete;
        }
        func_08096308(0x12, 0);
        {
            u8 *current = (u8 *)0x03005F72;
            u8 *expected = (u8 *)0x03005F71;
            goto poll_first_test;
poll_first_body:
            if ((*(s32 *)0x02021690 == 0xA) &&
                (*current == *expected)) {
                func_0809534C();
                func_080D120C();
            }
            func_080ED17C(1);
poll_first_test:
            if ((func_0809669C() << 24) == 0) {
                goto poll_first_body;
            }
        }
        goto complete;
    }

    choice = (*(u8 *)0x03005F70 & 0x3F) - 2;
    switch (choice) {
    case 0:
    case 2:
    case 4:
    case 6:
    case 9:
    case 10:
    case 12:
    case 16:
        {
            u8 *current = (u8 *)0x03005F72;
            u8 *expected = (u8 *)0x03005F71;
            goto poll_selected_test;
poll_selected_body:
            if ((*(s32 *)0x02021690 == 0xA) &&
                (*current == *expected)) {
                func_0809534C();
                func_080D120C();
            }
            func_080ED17C(1);
poll_selected_test:
            if ((func_0809669C() << 24) == 0) {
                goto poll_selected_body;
            }
        }
        goto complete;
    default:
        goto wait_input_test;
wait_input_body:
        func_080ED17C(1);
wait_input_test:
        if ((func_0809669C() << 24) == 0) {
            goto wait_input_body;
        }
        func_08096308(0x12, 0);
        {
            u8 *current = (u8 *)0x03005F72;
            u8 *expected = (u8 *)0x03005F71;
            goto poll_default_test;
poll_default_body:
            if ((*(s32 *)0x02021690 == 0xA) &&
                (*current == *expected)) {
                func_0809534C();
                func_080D120C();
            }
            func_080ED17C(1);
poll_default_test:
            if ((func_0809669C() << 24) == 0) {
                goto poll_default_body;
            }
        }
        goto complete;
    }

complete:
    func_0809FCB0();
    func_08092E0C(3);
    *(u8 *)0x03000075 = 1;
    *(s32 *)0x02021690 = 1;
    D_02021698 = 0;
    done = 1;

tick:
    func_080ED17C(1);
    if (done == 0) {
outer_test:
        if (*(u8 *)0x02030664 != 0) {
            goto outer_body;
        }
    }
}
