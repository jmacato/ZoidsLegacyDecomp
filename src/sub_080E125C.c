#include "m2c_prelude.h"

extern void func_08098834(s32);
extern void func_080988C8(s32, u16 *);
extern u8 func_080E6664(s32);
extern void func_080ED038(void *, const void *, s32);
extern u16 D_02030564;
extern u16 D_02030566;

void sub_080E125C(void) {
    u16 *output;

    func_08098834(3);

    if ((func_080E6664(17) << 24) != 0) {
        u16 *status = &D_02030564;
        register s32 value asm("r0") = 0x201;
        *status = value;
    } else D_02030564 = 1;
    output = &D_02030566;
    func_080ED038(output, (const void *)0x081091C0, 45);
    output--;
    func_080988C8(3, output);

    if ((func_080E6664(18) << 24) != 0) {
        register s32 value asm("r0") = 0x201;
        *output = value;
    } else *output = 1;
    output = &D_02030566;
    func_080ED038(output, (const void *)0x0810913C, 23);
    output--;
    func_080988C8(3, output);

    if ((func_080E6664(19) << 24) != 0) {
        register s32 value asm("r0") = 0x201;
        *output = value;
    } else *output = 1;
    output = &D_02030566;
    func_080ED038(output, (const void *)0x08109154, 19);
    output--;
    func_080988C8(3, output);

    if ((func_080E6664(20) << 24) != 0) {
        register s32 value asm("r0") = 0x201;
        *output = value;
    } else *output = 1;
    output = &D_02030566;
    func_080ED038(output, (const void *)0x08109168, 23);
    output--;
    func_080988C8(3, output);

    if ((func_080E6664(21) << 24) != 0) {
        register s32 value asm("r0") = 0x201;
        *output = value;
    } else *output = 1;
    output = &D_02030566;
    func_080ED038(output, (const void *)0x08109180, 27);
    output--;
    func_080988C8(3, output);

    if ((func_080E6664(22) << 24) != 0) {
        register s32 value asm("r0") = 0x201;
        *output = value;
    } else *output = 1;
    output = &D_02030566;
    func_080ED038(output, (const void *)0x0810919C, 23);
    output--;
    func_080988C8(3, output);
}
