#include "m2c_prelude.h"

typedef struct {
    u8 pad0[10];
    u8 ids[10];
    u16 values[10];
} AdmissionState;

s32 sub_080E7868(u8 id, u16 value)
{
    AdmissionState *state = (AdmissionState *)0x020280EC;
    u8 i;

    switch ((u32)id - 7) {
    case 0:
    case 1:
    case 2:
        for (i = 0; i <= 9; i++) {
            if ((u8)(state->ids[i] - 7) <= 2) {
                state->ids[i] = 0;
            }
        }
        break;
    case 3:
    case 4:
        for (i = 0; i <= 9; i++) {
            if ((u8)(state->ids[i] - 10) <= 1) {
                state->ids[i] = 0;
            }
        }
        break;
    case 6:
    case 7:
    case 8:
        for (i = 0; i <= 9; i++) {
            if ((u8)(state->ids[i] - 13) <= 2) {
                state->ids[i] = 0;
            }
        }
        break;
    case 9:
    case 10:
        for (i = 0; i <= 9; i++) {
            if ((u8)(state->ids[i] - 16) <= 1) {
                state->ids[i] = 0;
            }
        }
        break;
    case 17:
    case 18:
        for (i = 0; i <= 9; i++) {
            if ((u8)(state->ids[i] - 24) <= 1) {
                state->ids[i] = 0;
            }
        }
        break;
    default:
        for (i = 0; i <= 9; i++) {
            if (state->ids[i] == id) {
                state->ids[i] = 0;
            }
        }
        break;
    }

    i = 0;
    if (state->ids[0] != 0) {
        do {
            i++;
            if (i > 9) {
                goto no_slot;
            }
        } while (state->ids[i] != 0);
    }

    if (i <= 9) {
        goto store;
    }

no_slot:
    return 0;

store:
    state->ids[i] = id;
    state->values[i] = value;
    return 1;
}
