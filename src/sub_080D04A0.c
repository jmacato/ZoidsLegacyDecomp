#include "m2c_prelude.h"

struct State {
    u8 pad[0x8C];
    s32 field8C;
    s32 field90;
};

extern u8 D_02034055;
extern u8 D_02034056;
extern u8 D_02034057;
extern u8 D_02034058;
extern u16 D_0203405A;
extern u16 D_0203405C;
extern u8 D_02034060;
extern s32 *D_02033F40[];
extern u8 D_087A773C[];
extern struct State *D_02033F3C;
extern void func_080ECD38(s32, void *);

void sub_080D04A0(u8 arg0, u8 arg1) {
    s32 *entry;

    D_02034055 = arg0;
    D_02034056 = arg1;
    if (arg1 <= 3) {
        if (arg1 > 2) {
            goto default_state;
        }
        entry = D_02033F40[arg1];
        if (entry == 0) {
            goto default_state;
        }
        *entry &= ~8;
        D_02034057 = 2;
        D_02034058 = 0;
        return;
    }

    arg1 -= 4;
    {
        register u8 *base asm("r2") = D_087A773C;
        register s32 index asm("r1") = arg1 << 2;
        register s32 offset asm("r0") = arg0 << 2;
        asm volatile("" : "+r"(base));
        offset += arg0;
        offset <<= 3;
        index += offset;
        index += (s32)base;
        entry = *(s32 **)index;
    }
    if (entry != 0) {
        func_080ECD38((s32)entry, &D_02034060);
        if (arg0 == 0x40 && arg1 == 1) {
            D_02033F3C->field8C = arg1;
            D_02033F3C->field90 = 0;
        } else if (arg0 == 0x74 && arg1 == 2) {
            D_02033F3C->field8C = 1;
            D_02033F3C->field90 = 1;
        }
        D_02034057 = 1;
        D_02034058 = 0;
        D_0203405A = 0;
        D_0203405C = 0;
        return;
    }

    if (arg0 == 0x1A && arg1 == 1) {
        D_02033F3C->field8C = arg1;
        D_02034057 = 2;
        D_02034058 = (u8)(s32)entry;
        return;
    }
    if (arg0 == 0x40) {
        if (arg1 == 0) {
            D_02033F3C->field8C = 1;
            D_02033F3C->field90 = 2;
            D_02034057 = 2;
            D_02034058 = arg1;
            return;
        }
        if (arg1 == 2) {
            D_02033F3C->field8C = 1;
            D_02033F3C->field90 = 1;
            D_02034057 = arg1;
            D_02034058 = 0;
            return;
        }
    }
    if (arg0 == 0x41 && arg1 == 0) {
        D_02033F3C->field8C = 1;
        D_02034057 = 2;
        D_02034058 = arg1;
        return;
    }

default_state:
    D_02034057 = 0;
    D_02034058 = 1;
}
