#include "m2c_prelude.h"

struct CategoryInfo {
    u8 pad[0x1D];
    u8 kind;
    u8 tail[2];
};

void func_080972C8(void);
void func_080981F0(void *, s32, s32, s32, s32);
void func_08098284(s32, s32, s32, void *);
u8 func_08098B58(void *);
void func_08098BB4(const void *);
void func_08099F5C(void *, const void *);
void func_080ED128(void *, const void *);
void func_080ED17C(s32);

extern u8 D_02030564[];
extern u8 D_020305E4[];
extern struct CategoryInfo D_087C4434[];
extern const void *D_087EF4E0[];

void sub_0809E8CC(s32 arg0)
{
    register s32 id asm("r4") = arg0;
    u8 *output;
    u8 kind;
    s32 value;
    u32 wait;

    kind = D_087C4434[id].kind;
    output = D_02030564;
    func_080ED128(output, D_087EF4E0[kind]);
    if ((u32)(id - 0x49) <= 3) {
        func_08099F5C(output, (void *)0x08103AC8);
        value = id - 0x48;
        goto format_value;
    }
    if ((u32)(id - 0x80) <= 4) {
        func_08099F5C(output, (void *)0x08103AC8);
        value = id - 0x7F;
        goto format_value;
    }
    if ((u32)(id - 0x8C) <= 4) {
        func_08099F5C(output, (void *)0x08103AF0);
        value = id - 0x8B;
        goto format_value;
    }
    if ((u32)(id - 0x96) <= 3) {
        func_08099F5C(output, (void *)0x08103AC8);
        value = id - 0x95;
        goto format_value;
    }
    if ((u32)(id - 0x9A) <= 4) {
        func_08099F5C(output, (void *)0x08103AC8);
        value = id - 0x99;
        goto format_value;
    }
    if ((u32)(id - 0xA0) <= 6) {
        func_08099F5C(output, (void *)0x08103AC8);
        value = id - 0x9F;
        goto format_value;
    }
    if ((u32)(id - 0xA9) <= 3) {
        func_08099F5C(output, (void *)0x08103AC8);
        value = id - 0xA8;
        goto format_value;
    }
    if ((u32)(id - 0xAE) <= 1) {
        func_08099F5C(output, (void *)0x08103AC8);
        value = id - 0xAD;
format_value:
        {
            u8 *scratch = D_020305E4;

            func_08098284(value, 1, 0, scratch);
            func_08099F5C(output, scratch);
            func_08099F5C(output, (void *)0x08103AE0);
        }
    } else {
        u32 final_test = id;

        final_test -= 0xB0;
        if (final_test <= 2) {
            func_08099F5C(output, (void *)0x08103AC8);
            value = id - 0xAF;
            {
                u8 *scratch = D_020305E4;

                func_08098284(value, 1, 0, scratch);
                func_08099F5C(output, scratch);
                func_08099F5C(output, (void *)0x08103AE0);
            }
        }
    }

    func_08098BB4((void *)0x08017ACA);
    {
        u8 *measure_output = D_02030564;
        s32 center;

        center = 0x1C - func_08098B58(measure_output);
        center += (u32)center >> 31;
        center >>= 1;
        func_080981F0(measure_output, 0, 9, center, 0);
    }
    func_080972C8();
    wait = 0;
    do {
        func_080ED17C(1);
        wait++;
    } while (wait <= 0xEF);
    func_08098BB4((void *)0x08017AD2);
}
