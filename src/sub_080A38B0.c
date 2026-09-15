#include "m2c_prelude.h"

extern u8 D_020317D7;
extern u8 D_02033F36;
extern u8 D_020317D6;
extern u8 D_087AFCC4[];

void func_080A016C(u8, s32, s32);
s32 func_080D1C18(void);
void func_080D1D44(void);
u8 func_080D1E38(void);
void func_080D2200(void);
s32 func_080D222C(void);
void func_080D0D50(u8, u8, u16, s32);
void func_080D0F08(u8, u8, u16, s32);
void func_080ED17C(s32);

s32 sub_080A38B0(u8 arg0, u8 **arg1)
{
    if (func_080D1E38() == 1) {
        func_080D1D44();
        while ((u32)func_080D1E38() <= 1U) {
            func_080ED17C(1);
        }
    }
    if ((func_080D222C() << 24) == 0) {
        func_080D2200();
        while ((func_080D222C() << 24) == 0) {
            func_080ED17C(1);
        }
    }
    if ((D_020317D7 & 1) == 0) {
        u8 *input;

        func_080D0D50(D_02033F36, D_020317D6, ({
            register u8 *base asm("r5") = D_087AFCC4;
            register u32 entry_offset asm("r3");
            register u32 type asm("r4");
            register u32 record_offset asm("r2");

            input = *arg1;
            entry_offset = input[2] << 2;
            type = input[1];
            record_offset = type << 3;
            record_offset -= type;
            record_offset <<= 3;
            entry_offset += record_offset;
            entry_offset += (u32)base;
            *(u16 *)(entry_offset + 26);
        }), 0);
    } else {
        u8 *input;

        func_080D0F08(D_02033F36, D_020317D6, ({
            register u8 *base asm("r5") = D_087AFCC4;
            register u32 entry_offset asm("r3");
            register u32 type asm("r4");
            register u32 record_offset asm("r2");

            input = *arg1;
            entry_offset = input[2] << 2;
            type = input[1];
            record_offset = type << 3;
            record_offset -= type;
            record_offset <<= 3;
            entry_offset += record_offset;
            entry_offset += (u32)base;
            *(u16 *)(entry_offset + 26);
        }), 0);
    }
    while ((func_080D1C18() << 24) == 0) {
        func_080ED17C(1);
    }
    func_080A016C(arg0, -1, 0);
    return 0;
}
