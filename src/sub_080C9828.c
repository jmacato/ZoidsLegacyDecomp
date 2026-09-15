#include "m2c_prelude.h"
extern void func_080ED038(int, int, int);
extern void func_08098284(int, int, int, int);
extern void func_08099F5C(int, int);
extern void func_080C8F48(int, void *, int);

void sub_080C9828(void *arg0) {
    func_080ED038(0x02030564, 0x08108178, 3);
    func_08098284(*(int *)((char *)arg0 + 0xA0), 4, 12, 0x020305E4);
    func_08099F5C(0x02030564, 0x020305E4);
    func_080C8F48(0x02030564, arg0, 0);
    *(int *)((char *)arg0 + 0x8C) = 0;
}
