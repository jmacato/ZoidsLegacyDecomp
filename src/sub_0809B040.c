#include "m2c_prelude.h"

u8 func_0809ACC4(s32);
void func_0809AC98(void);

extern u8 D_03006059;
extern s32 D_03006054;
extern u8 D_0300603C;
extern u8 D_030009B9;
extern u8 D_030009A9[];
extern u8 D_030009B8[];
extern u8 D_030009A8[];
extern u8 *D_03006044;
extern u8 *D_0300604C;
extern u8 D_03000998[];
extern u16 D_030009EC;

s32 sub_0809B040(void) {
    u8 *source;
    u8 *input;
    s32 value;
    u8 count;
    s32 remaining;

    if (func_0809ACC4(0) != 1) {
        return 0;
    }
    {
        u8 initial = D_03006059;
        u8 result;

        if (initial == 0) {
            return 1;
        }
        if (initial > 1 && D_03006054 <= 0) {
            if (D_0300603C != 0) {
                if (D_030009B9 != 0) {
                    return 0;
                }
                result = ((u8 *)&D_030009B9)[-17];
            } else {
                if (D_030009A9[0] != 0) {
                    return 0;
                }
                result = D_030009A9[15];
            }
            if (result == 0) {
                D_03006059 = result;
                return 1;
            }
            return 0;
        }
    }
    if (D_0300603C != 0) {
        source = D_030009B8;
        if (source[1] != D_03006059) {
            return 0;
        }
    } else {
        source = D_030009A8;
        if (source[1] != D_03006059) {
            return 0;
        }
    }
    if (D_03006059 == 1) {
        input = D_03006044;
        source += 2;
        count = 0;
        while (*input != 0) {
            if (*source != *input) {
                func_0809AC98();
                D_030009EC |= 4;
                return 0;
            }
            input++;
            source++;
            count++;
            if (count > 13) {
                break;
            }
        }
    } else {
        source += 2;
        count = 0;
        if (D_03006054 != 0) {
            do {
                *D_0300604C = *source;
                D_0300604C++;
                source++;
                remaining = D_03006054 - 1;
                D_03006054 = remaining;
                count++;
            } while (count <= 13 && remaining != 0);
        }
    }
    value = D_03006059 + 1;
    D_03006059 = value;
    remaining = D_03006054;
    if (remaining == 0) {
        D_03000998[0] = remaining;
    } else {
        D_03000998[0] = value;
    }
    return 0;
}
