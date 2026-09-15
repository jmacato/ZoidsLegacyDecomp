#include "m2c_prelude.h"

void *func_08094374(void *, s32, u8, s32, s32, s32, s32, s32, s32);
void func_08094554(void *);
void func_08098284(s32, s32, s32, void *);
void func_08099F5C(void *, void *);
void func_080ED038(void *, void *, s32);

void sub_080CD410(void *arg0)
{
    register void **slots asm("sl");
    s32 *cnt;
    s32 *p;
    s32 t;
    register s32 v2 asm("r5");
    s32 nv;
    s32 k;
    s32 off;
    u32 d;
    u8 *str;
    u8 c;
    u8 code;
    register int j asm("r4");
    u8 i;
    s32 next;
    void *v;
    u8 *buf1;
    void *arrow;
    void *glyphs;

    buf1 = (u8 *)0x02030564;
    arrow = (void *)0x08108C14;
    glyphs = (void *)0x087AC9F0;
    i = 0;
    slots = (void **)((u8 *)arg0 + 0xC);
loop1:
    {
        u32 a = i * 4;
        void **q = (void **)((u8 *)arg0 + 0xC);
        asm volatile("" : "+r"(q));
        v = *(void **)((u32)q + a);
    }
    if (v != 0) {
        func_08094554(v);
    }
    i = i + 1;
    if (i <= 31) {
        goto loop1;
    }
    if (*(s32 *)((u8 *)arg0 + 0x94) == 0) {
        return;
    }
    i = 0;
    cnt = (s32 *)((u8 *)arg0 + 0x8C);
loop2:
    k = i + 2;
    v2 = cnt[k];
    if (v2 != -1) {
        p = &cnt[i];
        t = *p;
        d = v2 - t;
        if (d > 0x7CF) {
            nv = t + 1000;
            goto store;
        }
        if (d > 199) {
            nv = t + 100;
            goto store;
        }
        if (d > 19) {
            nv = t + 10;
            goto store;
        }
        if (v2 != t) {
            nv = t + 1;
store:
            *p = nv;
        }
        if (i == 0) {
            func_08098284(cnt[0], 4, 10, buf1);
        } else {
            u8 *buf;
            func_08098284(*(s32 *)((u8 *)cnt + (i << 2)), 3, 10, (buf = (u8 *)0x02030564));
            func_08099F5C(buf, arrow);
        }
    } else {
        func_080ED038((void *)0x02030564, (void *)0x08108C18, 5);
    }
    str = (u8 *)0x02030564;
    j = 0;
    c = *str;
    next = i + 1;
    if (c != 0) {
chartop:
        if ((u8)(c - 0x30) <= 9) {
            code = c + 0xF0;
            goto place;
        }
        code = c - 0x41;
        if ((u8)code > 0x19) {
            register s32 sel asm("r0");
            sel = c;
            if (sel == 0x2B) { code = 0x1A; goto place; }
            if (sel == 0x2D) { code = 0x1B; goto place; }
            if (sel == 0x2F) { code = 0x1C; goto place; }
            if (sel == 0x3C) { code = 0x1D; goto place; }
            if (sel == 0x3E) { code = 0x1E; goto place; }
            if (sel == 0xA0) { code = 0x1F; goto place; }
            if (sel == 0x25) { code = 0x2A; goto place; }
            if (sel == 0x3F) { code = 0x2B; goto place; }
        } else {
place:
            slots[i * 4 + j] = func_08094374(glyphs, 0, code,
                (s16)(*(s32 *)((u8 *)arg0 + 4) + j * 6),
                (s32)(s16)(*(s32 *)((u8 *)arg0 + 8) + i * 8),
                0x330, 0xB, 0x48, 0);
        }
        str += 1;
        {
            register s32 t2 asm("r0");
            t2 = j + 1;
            j = (u8)t2;
        }
        c = *str;
        if (c != 0) {
            goto chartop;
        }
    }
    i = (u8)next;
    if (i <= 1) {
        goto loop2;
    }
}
