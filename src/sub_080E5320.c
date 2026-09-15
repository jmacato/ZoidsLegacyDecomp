#include "m2c_prelude.h"
u8 sub_080E5320(u8 *arg0, u8 arg1) {
    u8 result;
    int temp_r2;
    result = arg1;
    temp_r2 = *arg0;
    switch (temp_r2) {
      case 0x19: case 0x1A: case 0x1B: case 0x1C: case 0x1D: case 0x1E:
        result += 0x19;
        return result;
      case 0x40: case 0x41: case 0x42: case 0x43:
        return arg1 + 0x40;
    }
    return *arg0;
}
