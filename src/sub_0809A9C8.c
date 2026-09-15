#include "m2c_prelude.h"
void sub_0809A9C8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, void *arg5) {
    u16 id;
    u32 packed;
    u8 mode;
    u16 dst0;
    u16 dst1;
    register u32 id_offset asm("r2");
    register u8 *base asm("r0");
    u8 *p;
    id = (u16)arg0;
    packed = arg1 << 24;
    mode = (u8)arg2;
    dst0 = (u16)arg3;
    dst1 = (u16)arg4;
    id_offset = id * 64;
    asm volatile("" : "+r"(id_offset));
    packed >>= 21;
    base = (u8 *)0x087ADBB8;
    asm volatile("" : "+r"(base));
    packed += (u32)base;
    p = (u8 *)id_offset;
    p += packed;
    func_080ECD38(*(void **)p, arg5);
    if (id != 0x4B) func_080ECD38(*(void **)(p + 4), arg5 + 0x480);
    else {
        register u8 *alt_base asm("r1");
        register u32 alt_offset asm("r0");
        register void *alt_value asm("r0");
        alt_base = (u8 *)0x087AF604;
        asm volatile("" : "+r"(alt_base));
        alt_offset = mode * 4;
        asm volatile("" : "+r"(alt_offset));
        alt_offset += (u32)alt_base;
        alt_value = *(void **)alt_offset;
        asm volatile("" : "+r"(alt_value));
        func_080ECD38(alt_value, arg5 + 0x480);
    }
    func_08095208(arg5, (void *)0x06010000 + dst0 * 32, 0x480);
    func_08095208(arg5 + 0x480, (void *)0x05000200 + dst1 * 32, 0x20);
}
