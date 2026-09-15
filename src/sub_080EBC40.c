#include "m2c_prelude.h"
void func_80EBB9C(s32);
void func_80EBD2C(void);
void func_80ECD60(u8, s32);

void sub_080EBC40(s32 arg0) {
    void *p = *(void **)0x03007FF0;
    s32 v = *(s32 *)p;
    if (v == 0x68736D53) {
        u32 m;
        *(s32 *)p = v + 1;
        m = 0xFF & arg0;
        if (m != 0) {
            *(s8 *)((u8 *)p + 5) = m & 0x7F;
        }
        m = 0xF00 & arg0;
        if (m != 0) {
            u8 *q;
            *(s8 *)((u8 *)p + 6) = m >> 8;
            m = 0xC;
            q = (u8 *)p + 0x50;
            do {
                *q = 0;
                m--;
                q += 0x40;
            } while (m != 0);
        }
        m = 0xF000 & arg0;
        if (m != 0) {
            *(s8 *)((u8 *)p + 7) = m >> 0xC;
        }
        m = 0xB00000 & arg0;
        if (m != 0) {
            u32 t = 0x300000;
            t &= m;
            m = t >> 0xE;
            *(u8 *)0x04000089 = (0x3F & *(u8 *)0x04000089) | m;
        }
        m = 0xF0000 & arg0;
        if (m != 0) {
            func_80EBD2C();
            func_80EBB9C(m);
        }
        *(s32 *)p = 0x68736D53;
    }
}

void sub_080EBCD8(void) {
    void *p = *(void **)0x03007FF0;
    s32 v = *(s32 *)p;
    if (v == 0x68736D53) {
        s32 i;
        u8 *q;
        *(s32 *)p = v + 1;
        i = 0xC;
        q = (u8 *)p + 0x50;
        do {
            *q = 0;
            i--;
            q += 0x40;
        } while (i > 0);
        q = *(u8 **)((u8 *)p + 0x1C);
        if (q != 0) {
            i = 1;
            do {
                func_80ECD60((u8)i, *(s32 *)((u8 *)p + 0x2C));
                *q = 0;
                i++;
                q += 0x40;
            } while (i <= 4);
        }
        *(s32 *)p = 0x68736D53;
    }
}
