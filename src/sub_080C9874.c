#include "m2c_prelude.h"
extern void func_080ED038(int, int, int);
extern void func_08098284(int, int, int, int);
extern void func_08099F5C(int, int);
extern void func_080C8F48(int, void *, int);

void sub_080C9874(void *arg0) {
    func_080ED038(0x02030564, 0x0810817C, 8);
    func_08098284(*(int *)((char *)arg0 + 0xA0), 4, 12, 0x020305E4);
    func_08099F5C(0x02030564, 0x020305E4);
    func_080C8F48(0x02030564, arg0, 0);
    *(int *)((char *)arg0 + 0x8C) = 0;
}

void sub_080C98C0(void *arg0) {
    func_080C8F48(0x08108184, arg0, 0);
    *(int *)((char *)arg0 + 0x8C) = 0;
}

void sub_080C98E0(void *arg0) {
    func_080C8F48(0x0810818C, arg0, 0);
    *(int *)((char *)arg0 + 0x8C) = 0;
}

void sub_080C9900(void *arg0) {
    func_080C8F48(0x08108198, arg0, 0);
    *(int *)((char *)arg0 + 0x8C) = 0;
}

void sub_080C9920(void *arg0) {
    func_080C8F48(0x081081A0, arg0, 0);
    *(int *)((char *)arg0 + 0x8C) = 0;
}

void sub_080C9940(void *arg0) {
    func_080ED038(0x02030564, 0x081081AC, 4);
    func_08098284(*(int *)((char *)arg0 + 0xA0), 4, 8, 0x020305E4);
    func_08099F5C(0x02030564, 0x020305E4);
    func_080C8F48(0x02030564, arg0, 0);
    *(int *)((char *)arg0 + 0x8C) = 0;
}

void sub_080C998C(void *arg0) {
    func_080C8F48(0x081081B0, arg0, 0);
    *(int *)((char *)arg0 + 0x8C) = 0;
}

void sub_080C99AC(void *arg0) {
    func_080C8F48(0x081081BC, arg0, 0);
    *(int *)((char *)arg0 + 0x8C) = 0;
}
