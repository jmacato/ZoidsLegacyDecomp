#include "m2c_prelude.h"

void func_08098BB4(s32);
void func_080C098C(s32);
void func_080C0A9C(u8);
void func_08092E84(s32);

extern volatile u8 D_0200A880;
extern volatile u8 D_0200A882;
extern volatile u16 D_0200A884;

s32 sub_080C2518(void)
{
    register u32 table_or_result asm("r4");
    register u32 *available asm("r6");
    register u8 *excluded asm("r5");

    func_08098BB4(0x08019A8A);
    func_080C098C(1);
    table_or_result = 0x087A2820;
    available = (u32 *)0x020282E0;
    excluded = (u8 *)0x02037300;

loop:
    {
        register u32 state asm("r2");

        func_08098BB4(0x08019A92);
        state = D_0200A882;
        if (state == 1) {
            register u32 value asm("r3");
            register u32 index asm("r0");

            index = D_0200A880;
            index += 1;
            value = *(u8 *)(index + table_or_result);
            if (value == 0) {
                goto selected;
            }
            {
                register u32 word asm("r0") = value >> 5;

                word <<= 2;
                asm volatile("" : "+r"(word));
                word += (u32)available;
                {
                    register u32 shift asm("r1") = 0x1F;

                    shift &= value;
                    state <<= shift;
                }
                word = *(u32 *)word;
                word &= state;
                if (word != 0) {
                register u32 i asm("r1") = 0;

                if (excluded[0] != value) {
                    register u8 *scan asm("r2") = (u8 *)0x02037300;

                    do {
                        register u32 next asm("r0") = i + 1;

                        next <<= 24;
                        i = next >> 24;
                        if (i > 9U) {
                            break;
                        }
                    } while (*(u8 *)(i + (u32)scan) != value);
                }
                if (i <= 9U) {
                    goto loop;
                }
selected:
                table_or_result = value;
                goto done;
                }
            }
            goto loop;
        } else {
            if ((D_0200A884 & 8) != 0) {
                register u32 index asm("r0");

                index = D_0200A880;
                index += 1;
                func_080C0A9C(*(u8 *)(index + table_or_result));
                func_08092E84(0x41);
                goto loop;
            }
            table_or_result = 0;
        }
    }

done:
    func_08098BB4(0x08019ACB);
    return table_or_result;
}
