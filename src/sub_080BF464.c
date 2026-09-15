#include "m2c_prelude.h"
struct E { u8 pad0[4]; u16 f4; u8 pad2[6]; };
struct Inner { u8 hdr[0xE4]; struct E e[32]; u8 tail[0xC]; };
struct Mid { struct Inner in[8]; };

u8 sub_080BF464(u8 arg0, u8 arg1, u16 arg2) {
    u8 var_r3;
    u8 ret;
    struct Inner *base3d;
    struct E *elem;
    var_r3 = 0;
    base3d = &((struct Mid *)0x02034B4C)[arg0].in[arg1];
loop_1:
    elem = &base3d->e[var_r3];
    if ((elem->f4 & 0x7F) == arg2) {
        ret = var_r3;
        goto done;
    }
    var_r3 += 1;
    if ((u32) var_r3 <= 0x1FU) {
        goto loop_1;
    }
    ret = 0xFF;
done:
    return ret;
}
