#include "m2c_prelude.h"

struct StateE66C8 {
    u8 pad0[6];
    u16 value;
    u8 pad1[50];
    s16 maximum;
};

u8 func_080BF464(u8, u8, s32);
void func_080BF514(u8, u8, u8);

void sub_080E66C8(s32 arg0, struct StateE66C8 *arg1, s32 arg2, s32 arg3)
{
    register struct StateE66C8 *st asm("r4") = arg1;
    register s32 v asm("r0");
    s32 rv;
    u16 m;
    u8 x;
    u8 y;

    arg0 = (u8)arg0;
    x = arg2;
    y = arg3;
    switch (arg0) {
    case 1:
        {
            register s32 t asm("r1") = 300;
            asm volatile("" : "+r"(t));
            v = t;
        }
        goto add_value;
    case 2:
        v = st->value;
        v += 150;
        goto store_value;
    case 3:
        v = st->value;
        v += 50;
        goto store_value;
    case 4:
        v = st->maximum;
        v /= 2;
    add_value:
        {
            register u16 t asm("r3") = st->value;
            v += t;
        }
    store_value:
        st->value = v;
        v = (s16)v;
        m = st->maximum;
        if (v > st->maximum) {
            st->value = m;
        }
        break;
    case 5:
        rv = func_080BF464(x, y, 25);
        rv = (u8)rv;
        func_080BF514(x, y, rv);
        break;
    case 6:
        rv = func_080BF464(x, y, 25);
        rv = (u8)rv;
        func_080BF514(x, y, rv);
        rv = func_080BF464(x, y, 27);
        rv = (u8)rv;
        func_080BF514(x, y, rv);
        rv = func_080BF464(x, y, 24);
        rv = (u8)rv;
        func_080BF514(x, y, rv);
        break;
    case 7:
        rv = func_080BF464(x, y, 25);
        rv = (u8)rv;
        func_080BF514(x, y, rv);
        rv = func_080BF464(x, y, 27);
        rv = (u8)rv;
        func_080BF514(x, y, rv);
        rv = func_080BF464(x, y, 24);
        rv = (u8)rv;
        func_080BF514(x, y, rv);
        st->value = st->maximum;
        break;
    case 8:
    case 9:
        break;
    }
}
