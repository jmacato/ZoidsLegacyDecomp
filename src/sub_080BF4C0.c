#include "m2c_prelude.h"
extern u8 D_02034B4C[];
void sub_080BF4C0(u8 arg0, u8 arg1, void *arg2) {
    u8 *p = D_02034B4C + (arg0 * 0x1380) + (arg1 * 0x270);
    s32 sel = 0x7F & *(u16 *)((u8 *)arg2 + 4);
    switch (sel) {
    case 1:
        *(u16 *)(p + 6) = *(u16 *)(p + 6) + *(u16 *)((u8 *)arg2 + 6);
        return;
    case 4:
        *(u16 *)(p + 8) = *(u16 *)(p + 8) + *(u16 *)((u8 *)arg2 + 6);
        return;
    }
}
