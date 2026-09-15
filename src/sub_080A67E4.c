#include "m2c_prelude.h"

extern void func_08094554(void *);
extern void func_08098BB4(s32);
extern void func_080ED17C(s32);
extern s32 func_080ECD64(s32, void *, void *);

void sub_080A67E4(void)
{
    *(u8 *)0x020316F7 = 0;

    {
        register u32 index asm("r6");

again:
        index = 0;
loop:
        {
            register void **slot asm("r5");
            register u32 shifted_index asm("r8");
            register void **slots asm("r1") = (void **)0x020314C4;
            register u32 offset asm("r0");
            register void **handlers asm("r2");
            void *handler;
            u8 result;
            u8 type;

            offset = index << 2;
            slot = (void **)((u8 *)slots + offset);
            if (*slot != 0) {
                shifted_index = index << 24;
retry:
                handlers = (void **)0x087A190C;
                asm volatile("" : "+r"(handlers));
                type = *(u8 *)*slot;
                handler = handlers[type];
                if (type == 0x42) {
                    func_080ECD64(shifted_index >> 24, slot, handler);
                    return;
                }
                result = func_080ECD64(shifted_index >> 24, slot, handler);
                type = *(u8 *)*slot;
                if (type == 0 || type == 0xB ||
                    (type == 0xC && *(u8 *)0x020316F6 != 0) ||
                    type == 0xD || type == 0x35 || type == 0x46 ||
                    type == 0x47 || type == 0x48 || type == 0x49 ||
                    type == 0x85 || type == 0x8E || type == 0x90 ||
                    type == 0x84) {
                    if (*(s32 *)0x02021690 != 10) {
                        register void **object asm("r4") = (void **)0x02031744;
                        if (*object != 0) {
                            func_08094554(*object);
                            *object = 0;
                        }
                        {
                            u8 *state = (u8 *)0x02030666;
                            if (*state == 0) {
                                goto skip_message;
                            }
                            if (*state == 1) {
                                func_08098BB4(0x080177F5);
                            } else {
                                func_08098BB4(0x080177FA);
                            }
                            func_08098BB4(0x080177FD);
                            *(u8 *)0x02030666 = 0;
skip_message:
                            ;
                        }
                    }
                }
                if (result == 0) {
                    goto retry;
                }
            }
        }
        index++;
        if (index <= 0x45) {
            goto loop;
        }
    }
    func_080ED17C(1);
    goto again;
}
