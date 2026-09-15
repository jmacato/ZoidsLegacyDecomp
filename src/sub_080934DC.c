#include "m2c_prelude.h"
void sub_080934DC(s16 *input, s16 *matrix, s16 *output)
{
    s32 value;

    value = input[0] * matrix[0] + input[3] * matrix[1] + input[6] * matrix[2];
    if (value < 0)
        value += 0xFF;
    output[0] = value >> 8;

    value = input[0] * matrix[3] + input[3] * matrix[4] + input[6] * matrix[5];
    if (value < 0)
        value += 0xFF;
    output[3] = value >> 8;

    value = input[0] * matrix[6] + input[3] * matrix[7] + input[6] * matrix[8];
    if (value < 0)
        value += 0xFF;
    output[6] = value >> 8;

    value = input[1] * matrix[0] + input[4] * matrix[1] + input[7] * matrix[2];
    if (value < 0)
        value += 0xFF;
    output[1] = value >> 8;

    value = input[1] * matrix[3] + input[4] * matrix[4] + input[7] * matrix[5];
    if (value < 0)
        value += 0xFF;
    output[4] = value >> 8;

    value = input[1] * matrix[6] + input[4] * matrix[7] + input[7] * matrix[8];
    if (value < 0)
        value += 0xFF;
    output[7] = value >> 8;

    value = input[2] * matrix[0] + input[5] * matrix[1] + input[8] * matrix[2];
    if (value < 0)
        value += 0xFF;
    output[2] = value >> 8;

    value = input[2] * matrix[3] + input[5] * matrix[4] + input[8] * matrix[5];
    if (value < 0)
        value += 0xFF;
    output[5] = value >> 8;

    value = input[2] * matrix[6] + input[5] * matrix[7] + input[8] * matrix[8];
    if (value < 0)
        value += 0xFF;
    output[8] = value >> 8;
}
