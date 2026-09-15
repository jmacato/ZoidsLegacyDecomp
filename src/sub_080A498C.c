#include "m2c_prelude.h"
extern void func_809FA24(u8, s16, s16, u8);
extern void func_8092D8C(s32, void (*)(void));
extern void func_80A016C(u8, s32, s32);
extern void func_809FA9C(void);

int sub_080A498C(u8 arg0, u8 **arg1) {
    u8 *d = *arg1;
    func_809FA24(d[1], (s16)((d[3] << 8) + d[2]), (s16)((d[5] << 8) + d[4]), d[6]);
    func_8092D8C(6, func_809FA9C);
    func_80A016C(arg0, -1, 0);
    return 0;
}
