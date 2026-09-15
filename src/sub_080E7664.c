#include "m2c_prelude.h"

void func_08098284(s32, s32, s32, s32);
void func_08099F5C(s32, s32);
void func_080ED128(s32, s32);

extern s32 D_087EF2D0[];
extern s32 D_087A5962;
extern s32 D_020305E4;
extern s32 D_08109400;

void sub_080E7664(u8 arg0, u16 arg1, s32 arg2) {
    u8 type;
    u16 value;
    s32 target;

    type = arg0;
    value = arg1;
    func_080ED128(arg2, D_087EF2D0[type]);

    switch (type - 3) {
    case 0:
    case 1:
    case 2:
        target = (s16)value * 0x23 + (s32)&D_087A5962;
        func_08099F5C(arg2, target);
        break;
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
    case 25:
    case 26:
    case 27:
        func_08098284(-(s16)value, 4, 4, (s32)&D_020305E4);
        func_08099F5C(arg2, (s32)&D_020305E4);
        func_08099F5C(arg2, (s32)&D_08109400);
        break;
    case 28:
    case 29:
    case 30:
    case 31:
    case 32:
    case 33:
    case 34:
    case 35:
    case 36:
        func_08098284((s16)value, 4, 4, (s32)&D_020305E4);
        func_08099F5C(arg2, (s32)&D_020305E4);
        func_08099F5C(arg2, (s32)&D_08109400);
        break;
    }
}
