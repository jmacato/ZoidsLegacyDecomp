#include "m2c_prelude.h"

extern void func_08092E74(u8);
extern void func_08092E84(int);
extern void func_08092EA0(u8);
extern void func_08094554(void);
extern u8 func_08098B58(int);
extern void func_08098BB4(int);
extern int func_080A016C(u8, int, int);
extern void func_080E7868(u8, s16);
extern void func_080ED038(void *, int, int);
extern void func_080ED128(void *, int);

extern s32 D_02031744;
extern u8 D_02030666;
extern u16 D_02031756[];
extern s32 D_087EF410[];

s32 sub_080A5264(u8 arg0, u8 **arg1) {
    u8 st;
    u8 idx;
    u8 *ptr;

    func_08092EA0(*(u8 *)0x02030667);
    func_08092E84(0x35);
    *(u8 *)0x02030664 = 1;
    if (D_02031744 != 0) {
        func_08094554();
        D_02031744 = 0;
    }
    if ((*(s32 *)0x02021690 != 0xA) || (*(u8 *)0x02031748 != 0)) {
        st = D_02030666;
        if (st != 0) {
            if (st == 1) {
                func_08098BB4(0x080177F5);
                goto block_7;
            }
        } else {
block_7:
            func_08098BB4(0x080177ED);
            D_02030666 = 2;
        }
    }
    func_080ED038(D_02031756, 0x08103DD8, 0x15);
    D_02031756[10] = 0x201;
    func_080ED128(&D_02031756[11], D_087EF410[(*arg1)[1]]);
    idx = func_08098B58(D_087EF410[(*arg1)[1]]);
    D_02031756[idx + 11] = 1;
    func_080ED038(&D_02031756[12] + idx, 0x08103DF0, 0xE);
    *(u16 **)0x0200A888 = D_02031756;
    func_08098BB4(0x080177D5);
    ptr = *arg1;
    func_080E7868(ptr[1], (s16)(ptr[2] | (ptr[3] << 8)));
    func_08092EA0(0x35);
    func_08092E74(*(u8 *)0x02030667);
    func_080A016C(arg0, -1, 0);
    return 0;
}
