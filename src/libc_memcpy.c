#include "m2c_prelude.h"

void *sub_080ED038(u8 *arg0, const u8 *arg1, u32 arg2)
{
    u32 n = arg2;
    u8 *dest = arg0;
    const u8 *src = arg1;

    if (n > 15 && !(((u32)src | (u32)arg0) & 3)) {
        u32 *d = (u32 *)arg0;

        do {
            *d++ = *(const u32 *)src;
            src += 4;
            *d++ = *(const u32 *)src;
            src += 4;
            *d++ = *(const u32 *)src;
            src += 4;
            *d++ = *(const u32 *)src;
            src += 4;
            n -= 16;
        } while (n > 15);

        while (n > 3) {
            *d++ = *(const u32 *)src;
            src += 4;
            n -= 4;
        }
        dest = (u8 *)d;
    }

    n--;
    if (n != (u32)-1) {
        do {
            *dest++ = *src++;
            n--;
        } while (n != (u32)-1);
    }
    return arg0;
}
