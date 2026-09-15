#include "m2c_prelude.h"

u8 *sub_080ED128(u8 *arg0, const u8 *arg1)
{
    u8 *dest = arg0;
    const u8 *src = arg1;

    {
        u32 alignment = (u32)src;
        alignment |= (u32)arg0;
        if (!(alignment & 3)) {
            u32 *d = (u32 *)dest;
            const u32 *s = (const u32 *)src;

            while (((*s + 0xFEFEFEFF) & ~*s & 0x80808080) == 0)
                *d++ = *s++;
            dest = (u8 *)d;
            src = (const u8 *)s;
        }
    }

    while ((*dest++ = *src++) != 0)
        ;
    return arg0;
}
