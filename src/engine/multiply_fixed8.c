#include "m2c_prelude.h"

s32 MultiplyFixed8(s16 left, s16 right) asm("func_08092AF4");

s32 MultiplyFixed8(s16 left, s16 right) {
    return (s16)((left * right) >> 8);
}
