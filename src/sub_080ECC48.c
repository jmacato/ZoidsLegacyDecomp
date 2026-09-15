#include "m2c_prelude.h"

void sub_080ECC48(void) {
    register u32 work asm("r0");
    register u32 temp asm("r1");
    register u16 *src asm("r2");
    register u16 *dst asm("r3");

    src = (u16 *)0x080ECB7D;
    work = 1;
    asm volatile("" : "+r"(src), "+r"(work));
    src = (u16 *)((u32)src & ~work);
    dst = (u16 *)0x03006AB0;
    work = 0x080ECBBD;
    temp = 0x080ECB7D;
    asm volatile("" : "+r"(work), "+r"(temp));
    work -= temp;
    work <<= 15;
    goto test_first;
copy_first:
    work = *src;
    *dst = work;
    src++;
    dst++;
    work = temp - 1;
    work <<= 16;
test_first:
    temp = work >> 16;
    if (temp != 0) {
        goto copy_first;
    }

    *(s32 *)0x03007750 = 0x03006AB1;
    src = (u16 *)0x080ECBFD;
    work = 1;
    asm volatile("" : "+r"(src), "+r"(work));
    src = (u16 *)((u32)src & ~work);
    dst = (u16 *)0x03006A10;
    work = 0x080ECC49;
    temp = 0x080ECBFD;
    asm volatile("" : "+r"(work), "+r"(temp));
    work -= temp;
    work <<= 15;
    goto test_second;
copy_second:
    work = *src;
    *dst = work;
    src++;
    dst++;
    work = temp - 1;
    work <<= 16;
test_second:
    temp = work >> 16;
    if (temp != 0) {
        goto copy_second;
    }

    *(s32 *)0x03007754 = 0x03006A11;
    src = (u16 *)0x04000204;
    work = *src;
    temp = 0xFFFC;
    work &= temp;
    temp = 3;
    work |= temp;
    *src = work;
}
