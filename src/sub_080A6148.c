#include "m2c_prelude.h"
extern void func_809AA64(void *, int, int, int);
extern void *func_8094374(void *, int, int, int, int, int, int, int, int);

struct R {
    u8 pad[10];
    u16 f10;
};

void sub_080A6148(void) {
    void *a0 = (void *)0x087af9d4;
    u8 *base = (u8 *)0x0202ecf4;
    struct R *r;
    func_809AA64(a0, (u8)(base[30] + 11), 0x398, 10);
    r = func_8094374((void *)0x087afa94, 12, 4, base[31] << 4, base[32] << 4, 0x398, 10, 0x410c8, 0);
    *(struct R **)0x020314a0 = r;
    r->f10 = 0xfff8;
}
