#include "m2c_prelude.h"

struct Entry9423C {
    s32 first;
    s32 second;
};

extern struct Entry9423C D_087A0A58[];

void func_080ECCE4(s32, s32, s32);

void sub_0809423C(void) {
    s32 destination;
    u8 index;

    index = 0;
    destination = 0x0E000004;
    if ((D_087A0A58[0].first == 0) && (D_087A0A58[0].second == 0)) {
        return;
    }
loop:
    func_080ECCE4(0, destination, 1);
    {
        s32 increment;
        increment = D_087A0A58[index].second;
        increment += 0xC;
        destination += increment;
    }
    index = (u8)(index + 1);
    if (D_087A0A58[index].first != 0) {
        goto loop;
    }
    if (D_087A0A58[index].second != 0) {
        goto loop;
    }
}
