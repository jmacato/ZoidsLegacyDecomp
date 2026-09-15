#include "m2c_prelude.h"
extern void *func_80D22B4(void *, int, int, int, int, int, int, int, int, int);
extern u8 D_087AA244[];

struct T {
    u32 f0;
    u8 pad[0xc - 4];
    void *fc;
    u8 pad2[0x8c - 0x10];
    u32 f8c;
};

void sub_080E0DE8(struct T *arg0) {
    arg0->f8c = 0xff;
    arg0->fc = func_80D22B4(D_087AA244, 0x5a, 0, 0xc8, 0x60, 0, 0,
                            (arg0->f0 & 2) ? 0x9288 : 0x1288, 0, (arg0->f0 >> 1) & 1);
}
