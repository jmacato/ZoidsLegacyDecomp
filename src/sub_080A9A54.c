#include "m2c_prelude.h"

struct CallbackDescriptorA9A54 {
    void *callback;
    u8 pad4[12];
};

extern struct CallbackDescriptorA9A54 D_087AD208[];
extern u8 D_0827A1BC[];
extern u8 D_0827A1E4[];
extern u8 D_0827A224[];
extern u8 D_08279A64[];
extern u8 D_0827A0C4[];
extern u8 D_0827A28C[];
extern u8 D_087A1BE8[];
extern u8 D_087A1BF0[];
extern u8 D_087A1BF8[];
extern u8 D_087A1C00[];

s32 sub_080A9A54(u8 *object)
{
    register struct CallbackDescriptorA9A54 *descriptors asm("r0") =
        D_087AD208;
    void *callback;
    u32 result;
    u8 *table;

    asm volatile("" : "+r"(descriptors));
    callback = descriptors[object[4]].callback;
    if (callback == (void *)D_0827A1BC) {
        goto zero;
    }
    if (callback != (void *)D_0827A1E4) {
        goto check_simple;
    }
zero:
    result = 0;
    goto done;

check_simple:
    if (callback != (void *)D_0827A224) {
        goto check_pair;
    }
    table = D_087A1BE8;
    asm volatile("" : "+r"(table));
simple_lookup:
    {
        register u32 address asm("r0") = object[0x1B];
        asm volatile("" : "+r"(address));
        address += (u32)table;
        result = *(u8 *)address;
    }
    goto done;

check_pair:
    if (callback == (void *)D_08279A64) {
        goto pair_lookup;
    }
    if (callback != (void *)D_0827A0C4) {
        goto check_single;
    }
pair_lookup:
    table = D_087A1BF8;
    asm volatile("" : "+r"(table));
    goto lookup_plus_four;

check_single:
    if (callback != (void *)D_0827A28C) {
        goto default_lookup;
    }
    table = D_087A1C00;
    asm volatile("" : "+r"(table));
    {
        register u32 address asm("r0") = object[0x1B];
        asm volatile("" : "+r"(address));
        address += (u32)table;
        result = *(u8 *)address;
    }
    if ((u8)(object[0x18] - 1) <= 2) {
        result += 1;
    }
    goto done;

default_lookup:
    table = D_087A1BF0;
    asm volatile("" : "+r"(table));
lookup_plus_four:
    {
        register u32 address asm("r0") = object[0x1B];
        asm volatile("" : "+r"(address));
        address += (u32)table;
        result = *(u8 *)address;
    }
    if ((u8)(object[0x18] - 1) <= 2) {
        result += 4;
    }

done:
    return result;
}
