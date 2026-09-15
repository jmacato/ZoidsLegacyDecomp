#include "m2c_prelude.h"
void func_0809570C(void);
void func_08095864(void);
void func_08095B84(void);
void func_08095EE4(void);
void func_08095F9C(void);

void sub_08096278(void) {
    u8 v = *(u8 *)0x03005EE8;
    s32 m;

    if (v != 0) {
        m = 7;
        m &= v;
        switch (m) {
        case 1:
            break;
        case 2:
            func_0809570C();
            break;
        case 3:
            func_08095864();
            break;
        case 4:
            func_08095B84();
            break;
        case 5:
            func_08095EE4();
            break;
        case 6:
            func_08095F9C();
            break;
        }
    }
}
