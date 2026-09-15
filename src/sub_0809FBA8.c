#include "m2c_prelude.h"

extern u8 D_0200A880;
extern u8 D_02030564[];
extern u8 D_020314A4[];
extern u8 D_020324B0[];

extern void func_080972C8(void);
extern void func_08098514(s32, s32, s32, s32, s32, s32);
extern void func_080988C8(s32, s32);
extern void func_08098BB4(s32);
extern void func_080ED17C(s32);

u8 sub_0809FBA8(u8 *script) {
    u8 *lines[4];
    register u8 *line asm("r4");
    register u8 *initial asm("r0");
    register u8 *input asm("r2") = script;
    register u32 longest asm("r6");
    register u32 width asm("r3");
    register u32 count asm("r5");

    initial = D_02030564;
    lines[0] = initial;
    line = initial;
    longest = 0;
    width = 0;
    count = 0;
    goto check;
body:
    {
        register u32 token asm("r1");
        register u32 current asm("r0") = token;

        asm volatile("" : "+r"(current));
        if (current == 1) {
            goto copy;
        }
        if (current == 10) {
            if (longest < width) {
                longest = width;
            }
            width = 0;
            {
                register u32 next asm("r0") = count + 1;

                next <<= 24;
                count = next >> 24;
            }
            *line = width;
            line++;
            lines[count] = line;
            input++;
            goto check;
        }
        {
            register u32 next asm("r0") = width + 1;

            next <<= 24;
            width = next >> 24;
        }
copy:
        *line = token;
        line[1] = input[1];
        line += 2;
        input += 2;
    }
check:
    {
        register u32 token asm("r1") = *input;

        if (token != 0) {
            goto body;
        }
        if (longest < width) {
            longest = width;
        }
    }
    {
        register u32 next asm("r0") = count + 1;

        next <<= 24;
        count = next >> 24;
    }
    *line = 0;
    {
        register u32 y asm("r1") = (u8)(28 - longest);
        register u32 height asm("r0") = count << 1;
        register u32 x asm("r2") = (u8)(9 - height);
        register u32 w asm("r3") = (u8)(longest + 2);

        height = (u8)(height + 2);
        func_08098514(3, y, x, w, height, 128);
    }
    {
        register u32 index asm("r4") = 0;

        if (index < count) {
draw:
            func_080988C8(3, (s32)lines[index]);
            {
                register u32 next asm("r0") = index + 1;

                next <<= 24;
                index = next >> 24;
            }
            if (index < count) {
                goto draw;
            }
        }
    }
    if (D_020324B0[0] & 4) {
        register u8 *position asm("r2") = D_020314A4;
        register u32 offset asm("r1") = count << 1;
        register u32 value asm("r0") = 9 - offset;

        value <<= 3;
        value -= 1;
        *position = value;
    }
    func_08098BB4(0x0801780B);
    func_080972C8();
    if (D_020324B0[0] & 4) {
        D_020314A4[0] = 95;
    }
    func_080ED17C(1);
    return D_0200A880;
}
