#include "m2c_prelude.h"

void *func_0809716C(s32);
void func_08098284(s32, s32, s32, s32);
void func_080988C8(s32, s32);
void func_08098BB4(s32);
void func_08099F5C(s32, s32);
void func_080ED038(void *, s32, s32);

void sub_080E4948(void) {
    register s32 index asm("r4");
    register s16 *line asm("r6");
    s16 *output;
    register u8 *enabled asm("r8");
    register s32 one asm("r9");
    register u8 *state asm("r10");
    register u8 *scratch asm("r5");

    func_08098BB4(0x0801765B);
    index = 0;
    state = (u8 *)0x0202EE8C;
    line = (s16 *)0x02030564;
    one = 1;
    enabled = (u8 *)0x02032E83;
    output = line + 1;
loop:
    {
        register s32 option asm("r1");
        option = *(u8 *)0x02032E74;
        option = option * 5;
        if (state[index + option] != 0) {
            *line = 1;
            *(u8 *)(index + (s32)enabled) = one;
            func_080ED038(line + 1, 0x08109398, 3);
        } else {
            register s32 previous asm("r0");
            if (index == 0) {
                goto enabled_case;
            }
            previous = option - 1;
            previous = state[index + previous];
            if (previous != 0) {
enabled_case:
                *line = 1;
                *(u8 *)(index + (s32)enabled) = one;
            } else {
                register s32 disabled asm("r1");
                register s32 zero asm("r0");
                zero = 0;
                disabled = 0x401;
                *line = disabled;
                *(u8 *)(index + (s32)enabled) = zero;
            }
            func_080ED038((void *)0x02030566, 0x0810939C, 3);
        }
    }
    {
        register s32 destination asm("r0");
        register s32 text asm("r1");
        destination = (s32)output;
        asm volatile("" : "+r"(destination));
        text = 0x081093A0;
        func_08099F5C(destination, text);
    }
    index++;
    scratch = (u8 *)0x020305E4;
    func_08098284(index, 2, 2, (s32)scratch);
    func_08099F5C((s32)output, (s32)scratch);
    {
        register s32 call0 asm("r0");
        register s32 call1 asm("r1");
        call0 = 2;
        call1 = (s32)(output - 1);
        func_080988C8(call0, call1);
    }
    index <<= 24;
    index = (u32)index >> 24;
    if ((u32)index <= 4) {
        goto loop;
    }
    ((u8 *)func_0809716C(2))[22] = *(u8 *)0x02032E78;
}
