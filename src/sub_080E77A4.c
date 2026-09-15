#include "m2c_prelude.h"
void func_08099F5C(s8 *, s32);
void func_080ED038(s8 *, s32, s32);
extern s32 D_08109404;
extern s32 D_087A5B29;
extern s32 D_087EF370[];

void sub_080E77A4(s32 arg0, s32 arg1, s8 *arg2) {
    register s32 temp_r5 asm("r5");
    register s32 temp_r6 asm("r6");

    arg0 = arg0 << 24;
    temp_r5 = (u32)arg0 >> 24;
    arg1 = arg1 << 16;
    temp_r6 = (u32)arg1 >> 16;

    *arg2 = 0;
    switch (temp_r5) {
    case 3:
    case 4:
    case 5: {
        register s32 signed_index asm("r0");

        func_080ED038(arg2, (s32)&D_08109404, 0xF);
        signed_index = temp_r6 << 16;
        signed_index >>= 16;
        asm volatile("" : "+r"(signed_index));
        func_08099F5C(arg2, signed_index * 0x23 + (s32)&D_087A5B29);
        break;
    }
    }
    {
        register s32 *base asm("r0");
        register s32 offset asm("r1");

        base = D_087EF370;
        asm volatile("" : "+r"(base));
        offset = temp_r5 << 2;
        asm volatile("" : "+r"(offset));
        offset += (s32)base;
        asm volatile("" : "+r"(offset));
        offset = *(s32 *)offset;
        asm volatile("" : "+r"(offset));
        func_08099F5C(arg2, offset);
    }
}
