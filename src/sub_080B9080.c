#include "m2c_prelude.h"

M2C_UNK func_080988C8(s32, s32);
M2C_UNK func_08098BB4(M2C_UNK);
M2C_UNK func_08099F5C(s32, s32);
M2C_UNK func_080E59BC(s32, M2C_UNK, s32, u8, void *);
void *func_080E669C(void);
M2C_UNK func_080E66B8(void);
M2C_UNK func_080ED038(void *, M2C_UNK, s32);

void sub_080B9080(s32 arg0, M2C_UNK arg1)
{
    register M2C_UNK text asm("r1");
    register s32 saved_arg0 asm("r8") = arg0;
    register M2C_UNK saved_arg1 asm("sl") = arg1;
    s32 row;
    u8 index;
    void *object;
    u16 *buffer;
    register void *line_output asm("r9");
    register void *output asm("r0");

    object = func_080E669C();
    func_08098BB4(0x0800586B);
    index = 0;
    buffer = (u16 *)0x02030564;
    asm volatile("" : "+r"(buffer));
    asm volatile("" : : "r"(buffer));
    line_output = buffer + 1;
    do {
        register u32 raw_row asm("r0") = index + 4;
        register u32 field asm("r1") = raw_row << 2;

        field += saved_arg0;
        field += 0x52;
        field = *(u16 *)field;
        row = raw_row;
        asm volatile("" : : "r"(row), "r"(row));
        if (field != 0) {
            func_080E59BC(saved_arg0, saved_arg1, 0, row, object);
            {
                register u32 flags asm("r1") = M2C_FIELD(object, u16 *, 2);
                register u32 one asm("r3") = 1;
                register u32 test asm("r0") = one;

                test &= flags;
                if (test == 0) {
                    register u16 *destination asm("r2") =
                        (u16 *)0x02030564;

                    *destination = one;
                if (!(M2C_FIELD(object, s32 *, 4) & 0x10)) {
                    output = destination + 1;
                    text = 0x08106EE4;
                } else {
                    output = destination + 1;
                    text = 0x08106EEC;
                }
                } else {
                    *buffer = 0x401;
                    output = buffer + 1;
                    text = 0x08106EF4;
                }
            }
            func_080ED038(output, text, 7);
        } else {
            *buffer = 0x401;
            func_080ED038(buffer + 1, 0x08106EFC, 7);
        }
        func_08099F5C((s32)line_output,
            M2C_FIELD((M2C_FIELD(((row * 4) + saved_arg0), u16 *, 0x52) * 4),
                s32 *, 0x087EE170));
        {
            register s32 call0 asm("r0") = 8;
            register s32 call1 asm("r1") = (s32)line_output;

            call1 -= 2;
            func_080988C8(call0, call1);
        }
        index += 1;
    } while ((u32)index <= 3);
    func_080E66B8();
}
