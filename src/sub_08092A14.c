#include "m2c_prelude.h"

int sub_08092A14(int arg0, int arg1)
{
    int temp_r4;
    int temp_r7;
    int temp_r5;
    int temp_r6;

    temp_r4 = arg0;
    if (temp_r4 < 0)
        temp_r4 = -temp_r4;
    temp_r7 = arg1;
    if (temp_r7 < 0)
        temp_r7 = -temp_r7;
    if (temp_r4 == 0 || temp_r7 == 0)
        return 0;
    asm volatile("" :: "r"(temp_r4));
    temp_r5 = 0;
    asm volatile("" : "+r"(temp_r5));
    temp_r6 = temp_r5;
    do {
        temp_r5 <<= 4;
        temp_r5 += func_080ECD98(temp_r4, temp_r7);
        temp_r4 = func_080ECE30(temp_r4, temp_r7);
        temp_r4 <<= 4;
        temp_r6++;
    } while (temp_r6 <= 3 && temp_r4 != 0);
    while (temp_r6 <= 3) {
        temp_r5 <<= 4;
        temp_r6++;
    }
    if (arg0 < 0) {
        if (arg1 >= 0)
            temp_r5 = -temp_r5;
    } else if (arg1 < 0) {
        temp_r5 = -temp_r5;
    }
    return temp_r5;
}
