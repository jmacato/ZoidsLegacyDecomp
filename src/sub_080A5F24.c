#include "m2c_prelude.h"

s32 func_809669C(void);
void func_80A016C(u8, s32, s32);
void func_80ED17C(s32);

s32 sub_080A5F24(u8 arg0, void **arg1) {
    s32 previous;

    *(u8 *)0x02030664 = 1;
    previous = *(s32 *)0x02021690;
    *(s32 *)0x02021690 = 4;
    *(u8 *)0x02032A85 = *((u8 *)*arg1 + 1);
    do {
        func_80ED17C(1);
    } while (*(s32 *)0x02021690 != 3);

    goto check;
wait:
    func_80ED17C(1);
check:
    if ((func_809669C() << 24) == 0) {
        goto wait;
    }
    *(s32 *)0x02021690 = previous;
    func_80A016C(arg0, -1, 0);
    return 0;
}
