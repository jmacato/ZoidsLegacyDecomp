#include "m2c_prelude.h"

struct UnitRecord {
    u8 pad0[6];
    s16 value6;
    u8 pad8[0x32];
    s16 value3A;
    u8 pad3C[0x234];
};

extern u8 D_0200A880;
extern u8 D_0200A881;
extern u8 D_0200A882;
extern u8 D_020322A8[];
extern u8 D_020322B1;
extern u8 D_02034B4C[];

extern void func_08092E84(s32);
extern void *func_0809716C(s32);
extern void func_080981F0(s32, s32, s32, s32, s32);
extern void func_080986B4(s32);
extern void func_08098BB4(s32);
extern void func_080AC7BC(s32);
extern void func_080B654C(void);
extern u8 func_080BF464(s32, u8, s32);
extern u8 func_080C05A8(s32, u8);

static inline void reject_selection(void)
{
    func_08092E84(0x58);
    func_08098BB4(0x08003AA9);
}

s32 sub_080C598C(void)
{
    s32 message;
    s32 state;
    s32 invalid;
    s32 kind;
    s32 response;
    u8 selected;
    u8 row;
    u8 column;
    void *window;
    struct UnitRecord *record;

    func_080B654C();
    if (D_020322B1 == 0)
        goto no_units;

    column = 0;
    row = 0;

restart:
    state = 0;

state_loop:
    switch (state) {
    case 0:
        func_08098BB4(0x08003990);
        func_080AC7BC(1);
        window = func_0809716C(1);
        *(u8 *)((u8 *)window + 0x14) = column;
        *(u8 *)((u8 *)window + 0x16) = row;
        state = 0x100;
        goto state_loop;
    case 0x100: {
        register s32 *messages asm("r1");

        func_080986B4(2);
        messages = (s32 *)0x087EEE38;
        asm volatile("" : "+r"(messages));
        func_080981F0(messages[D_020322A8[row]], 0, 2, 0, 0);
        func_08098BB4(0x080039E6);
        column = D_0200A881;
        row = D_0200A880;
        response = D_0200A882;

        if (response == 1)
            goto response_one;
        if (response <= 1)
            goto state_loop;
        if (response == 2)
            goto response_two;
        goto state_loop;

response_one:
        if ((u32)(u8)(D_020322A8[row] - 8) <= 1) {
            func_08092E84(0x58);
            func_08098BB4(0x08003A60);
        } else {
            state = 0x200;
        }
        goto state_loop;

response_two:
        message = 0x080039EA;
        goto cancel;
    }
    case 0x200:
        func_08098BB4(0x08003A28);
        func_08098BB4(0x080039EA);
        selected = 0;
        state = 0x210;
        goto state_loop;
    case 0x210:
        goto select;
    default:
        goto state_loop;
    }

select:
    selected = func_080C05A8(0, selected);
    if (selected == 0xFF)
        goto restart;

    invalid = 0;
    kind = D_020322A8[row] - 1;
    switch (kind) {
    case 0:
    case 1:
    case 2:
    case 3: {
        s32 value6;
        s32 value3A;

        {
            register struct UnitRecord *record_base asm("r1") =
                (struct UnitRecord *)D_02034B4C;

            record = (struct UnitRecord *)(
                selected * sizeof(struct UnitRecord) -
                (0u - (u32)record_base));
        }
        value6 = record->value6;
        value3A = record->value3A;
        if (value6 == value3A) {
            reject_selection();
            goto state_loop;
        }
        break;
    }
    case 4:
        if (func_080BF464(0, selected, 0x19) == 0xFF) {
            reject_selection();
            goto state_loop;
        }
        break;
    case 5:
        if (func_080BF464(0, selected, 0x19) == 0xFF &&
            func_080BF464(0, selected, 0x1B) == 0xFF &&
            func_080BF464(0, selected, 0x18) == 0xFF) {
            reject_selection();
            goto state_loop;
        }
        break;
    case 6:
        if (func_080BF464(0, selected, 0x19) == 0xFF &&
            func_080BF464(0, selected, 0x1B) == 0xFF &&
            func_080BF464(0, selected, 0x18) == 0xFF) {
            s32 value6;
            s32 value3A;

            {
                register struct UnitRecord *record_base asm("r1") =
                    (struct UnitRecord *)D_02034B4C;

                record = (struct UnitRecord *)(
                    selected * sizeof(struct UnitRecord) -
                    (0u - (u32)record_base));
            }
            value6 = record->value6;
            value3A = record->value3A;
            if (value6 == value3A) {
                reject_selection();
                invalid = 1;
            }
        }
        break;
    }

    if (invalid != 0)
        goto state_loop;
    D_02034B4C[0xA07D] = D_020322A8[row];
    D_02034B4C[0xA07E] = selected;
    return 1;

no_units:
    message = 0x080039F0;
cancel:
    func_08098BB4(message);
    return 0;
}
