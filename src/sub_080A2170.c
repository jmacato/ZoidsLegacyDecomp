#include "m2c_prelude.h"

struct InputRecord {
    u8 value;
    u8 category;
    u8 x;
    u8 y;
};

struct CategoryInfo {
    u8 pad00[0x1D];
    u8 kind;
    u8 pad1E[2];
};

struct GameState {
    u16 category;
    u8 pad02[0xA];
    s32 x;
    s32 y;
};

extern struct GameState D_0202ECF4;
extern u8 D_02030664;
extern struct CategoryInfo D_087C4434[];

void func_0809E204(u8, s32, s32, s32);

s32 sub_080A2170(s32 arg0, struct InputRecord **arg1) {
    register struct InputRecord **source_slot asm("r4");
    register struct InputRecord *initial_input asm("r1");
    s32 initial_category;
    struct InputRecord *input;
    register s32 scale asm("r5");
    u32 kind;

    source_slot = arg1;
    initial_input = *source_slot;
    initial_category = initial_input->category;
    scale = 1;
    if (initial_category == 0) {
        scale = 2;
    }

    kind = D_087C4434[initial_input->category].kind;
    if (kind != 0) {
        struct GameState *state;

        state = &D_0202ECF4;
        if (D_087C4434[state->category].kind != kind) {
            register u8 *position_base asm("r2");
            register s32 kind_index asm("r0");
            register s32 offset asm("r1");
            register s32 address asm("r0");
            register s32 value asm("r0");

            position_base = (u8 *)0x087AFBB4;
            asm volatile("" : "+r"(position_base));
            kind_index = kind - 1;
            offset = kind_index << 1;
            offset += kind_index;
            offset <<= 1;
            address = (s32)position_base + 2;
            address = offset + address;
            value = *(s16 *)address;
            value <<= 11;
            state->x = value;
            position_base += 4;
            offset += (s32)position_base;
            value = *(s16 *)offset;
            value <<= 11;
            state->y = value;
        }
    }

    input = *source_slot;
    func_0809E204(input->category,
                  (input->x * scale) << 11,
                  (input->y * scale) << 11,
                  0);
    *source_slot = 0;
    D_02030664 = 0;
    return 1;
}
