/* Compatible with the m2c_prelude.h types used by tools/pmatch.py. */
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

struct WindowRecord {
    u32 flags;
    u16 field4;
    s16 field6;
    u16 field8;
    u16 fieldA;
    u16 fieldC;
    u16 fieldE;
    u8 field10;
    u8 field11;
    u16 field12;
    u16 field14;
    u16 field16;
    s32 field18;
    s32 field1C;
    s32 field20;
    s32 field24;
    s32 field28;
    s32 field2C;
    s32 field30;
    s32 field34;
};

extern u8 D_03005DE4;
extern struct WindowRecord D_03003FE4[];
extern struct WindowRecord *D_03005BE4[];

void sub_08094578(void) {
    s16 i;
    s16 j;
    struct WindowRecord *record;
    struct WindowRecord *previous;

    D_03005DE4 = 0;
    for (i = 0; i < 0x80; i++) {
        record = &D_03003FE4[i];
        if (record->flags & 1) {
            D_03005BE4[D_03005DE4] = record;
            D_03005DE4++;
        } else {
            record->flags &= ~2;
        }
    }

    for (i = 1; i < D_03005DE4; i++) {
        record = D_03005BE4[i];
        j = i - 1;
        while (j >= 0) {
            previous = D_03005BE4[j];
            if ((record->flags & 0xC0) < (previous->flags & 0xC0)) {
                /* shift */
            } else if ((record->flags & 0xC0) != (previous->flags & 0xC0)) {
                break;
            } else if ((record->flags & 0x300) < (previous->flags & 0x300)) {
                /* shift */
            } else if ((record->flags & 0x40000) == 0) {
                break;
            } else if ((previous->flags & 0x40000) == 0) {
                /* shift */
            } else if (record->field6 > previous->field6) {
                /* shift */
            } else {
                break;
            }
            D_03005BE4[j + 1] = previous;
            j--;
        }
        D_03005BE4[j + 1] = record;
    }
}
