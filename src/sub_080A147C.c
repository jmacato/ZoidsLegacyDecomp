#include "m2c_prelude.h"
extern void func_08098BB4(int);
extern void func_080A016C(int, int, int);

s32 sub_080A147C(u8 arg0, s32 *arg1) {
    u8 temp_r1;
    s32 one;
    *(s8 *)0x02030664 = (one = 1);
    if ((*(s32 *)0x02021690 != 0xA) || (*(u8 *)0x02031748 != 0)) {
        u8 *p = (u8 *)0x02030666;
        temp_r1 = *p;
        if (temp_r1 == 0) {
            if (*(s32 *)0x02031744 != 0) {
                goto block_8;
            }
            goto block_11;
        }
        if (*(s32 *)0x02031744 != 0) {
            if (temp_r1 == 2) {
                func_08098BB4(0x080177FA);
block_8:
                func_08098BB4(0x080177DA);
                *p = one;
            }
        } else if (temp_r1 == 1) {
            func_08098BB4(0x080177F5);
block_11:
            func_08098BB4(0x080177ED);
            *p = 2;
        }
    } else {
        *(u8 *)0x02030666 = one;
    }
    *(s32 *)0x0200A888 = *arg1 + 1;
    if (*(u8 *)0x02030666 == 1) {
        func_08098BB4(0x080177D0);
    } else {
        func_08098BB4(0x080177D5);
    }
    func_080A016C(arg0, -1, 0);
    return 0;
}
