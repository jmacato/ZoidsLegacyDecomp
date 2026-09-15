#include "m2c_prelude.h"
void sub_080AA59C(int arg0) {
    if (*(u32*)(arg0 + 0x28) & 1) {
        *(u32*)arg0 ^= 0x20000;
    }
    *(u32*)(arg0 + 0x28) += 1;
}
