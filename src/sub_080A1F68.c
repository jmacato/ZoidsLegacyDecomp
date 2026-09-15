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

struct PositionInfo {
    s16 unused;
    s16 x;
    s16 y;
};

struct LookupEntry {
    u16 category;
    u8 pad02[8];
};

struct GameState {
    u16 category;
    u8 pad02[0xA];
    s32 x;
    s32 y;
    u8 pad14[0xE];
    u16 lookup22;
    u16 lookup24;
    u8 pad26[0x16A];
    u32 unlocked[8];
};

extern u8 D_02030664;
extern struct GameState D_0202ECF4;
extern u8 D_020316F4;
extern u8 D_020324B0;
extern struct CategoryInfo D_087C4434[];

void func_08092E0C(s32);
s32 func_0809F818(s32);
void func_08092D9C(s32, s32, u8);
void func_08094330(void);
void func_0809F850(void);
void func_080A9888(void);
void func_0809D938(u8, s32, s32);
void func_080A016C(s32, s32, s32);

s32 sub_080A1F68(s32 arg0, struct InputRecord **arg1) {
    struct InputRecord **source_slot;
    register s32 saved_arg0 asm("r9");
    register s32 scale asm("r8");
    volatile struct InputRecord *input;
    register s32 category asm("r1");

    source_slot = arg1;
    arg0 <<= 24;
    saved_arg0 = (u32)arg0 >> 24;
    func_08092E0C(7);
    D_02030664 = 1;
    input = *source_slot;
    category = input->category;
    scale = 8;
    if (category == 0) {
        scale = 0x10;
    }

    if (D_020316F4 != category) {
        u32 kind;

        kind = D_087C4434[input->category].kind;
        if (kind != 0) {
            u8 old_kind;

            old_kind = D_087C4434[D_0202ECF4.category].kind;
            if (old_kind != kind || kind == 0x1D ||
                (u8)(kind - 0x21) <= 9) {
                register s32 kind_index asm("r6");
                register s32 test_result asm("r0");

                test_result = func_0809F818(0);
                test_result <<= 24;
                kind_index = kind - 1;
                asm volatile("" : "+r"(kind));
                if (test_result != 0) {
                    test_result = func_0809F818(0x8A);
                    test_result <<= 24;
                    if (test_result == 0) {
                        register s32 current_value asm("r3");
                        struct GameState *state;
                        struct GameState *state_source;
                        s32 state_category;
                        register s32 callback asm("r12");

                        state_source = &D_0202ECF4;
                        state_category = state_source->category;
                        current_value = (s32)*source_slot;
                        state = state_source;
                        asm volatile("" : : "r"(state));
                        if (state_category != 0x40 ||
                            ((struct InputRecord *)current_value)->category !=
                                0x3F) {
                            register s32 word_offset asm("r2");
                            register s32 field_offset asm("r1");
                            register s32 address asm("r0");
                            register u32 shift asm("r0");
                            register u32 bit asm("r1");
                            register u32 value asm("r0");

                            word_offset = kind >> 5;
                            word_offset <<= 2;
                            field_offset = 200;
                            field_offset <<= 1;
                            address = (s32)state + field_offset;
                            word_offset += address;
                            shift = 0x1F;
                            shift &= kind;
                            bit = 1 << shift;
                            value = *(u32 *)word_offset;
                            value |= bit;
                            *(u32 *)word_offset = value;
                        }

                        {
                            register s32 i asm("r2");
                            register struct LookupEntry *table_source asm("r0");
                            register struct LookupEntry *table asm("r5");
                            register struct LookupEntry *scan asm("r4");
                            register u16 loaded asm("r1");

                            if ((u16)(state->category - 0x3A) <= 6) {
                                goto lookup_b_setup;
                            }
                            i = 0;
                            table_source = (struct LookupEntry *)0x087D223C;
                            loaded = table_source->category;
                            table = table_source;
                            callback = 0x0809E8CD;
                            kind_index = kind - 1;
                            if (loaded == 0) {
                                goto lookup_done;
                            }
                            scan = table;
                            current_value =
                                ((struct InputRecord *)current_value)->category;
lookup_a:
                            {
                                register s32 offset asm("r0");

                                offset = i << 2;
                                offset += i;
                                offset <<= 1;
                                loaded = *(u16 *)(offset + (s32)scan);
                            }
                            if (loaded == current_value) {
                                goto lookup_store_a;
                            }
                            {
                                register u8 next asm("r0");

                                next = i + 1;
                                i = next;
                            }
                            {
                                register s32 offset asm("r0");

                                offset = i << 2;
                                offset += i;
                                offset <<= 1;
                                if (*(u16 *)(offset + (s32)table) != 0) {
                                    goto lookup_a;
                                }
                            }
                            goto lookup_done;

lookup_store_a:
                            D_0202ECF4.lookup22 = loaded;
                            goto lookup_done;

lookup_store_b:
                            D_0202ECF4.lookup24 = loaded;
                            goto lookup_done;

lookup_b_setup:
                            i = 0;
                            table_source = (struct LookupEntry *)0x087D2322;
                            loaded = table_source->category;
                            table = table_source;
                            callback = 0x0809E8CD;
                            kind_index = kind - 1;
                            if (loaded == 0) {
                                goto lookup_done;
                            }
                            scan = table;
                            current_value =
                                ((struct InputRecord *)current_value)->category;
lookup_b:
                            {
                                register s32 offset asm("r0");

                                offset = i << 2;
                                offset += i;
                                offset <<= 1;
                                loaded = *(u16 *)(offset + (s32)scan);
                            }
                            if (loaded == current_value) {
                                goto lookup_store_b;
                            }
                            {
                                register u8 next asm("r0");

                                next = i + 1;
                                i = next;
                            }
                            {
                                register s32 offset asm("r0");

                                offset = i << 2;
                                offset += i;
                                offset <<= 1;
                                if (*(u16 *)(offset + (s32)table) != 0) {
                                    goto lookup_b;
                                }
                            }
                        }
lookup_done:
                        func_08092D9C(7, callback,
                                      (*source_slot)->category);
                    }
                }
                {
                    register struct GameState *coord_state asm("r3");
                    register u8 *position_base asm("r2");
                    register s32 offset asm("r1");
                    register s32 address asm("r0");
                    register s32 value asm("r0");

                    coord_state = &D_0202ECF4;
                    position_base = (u8 *)0x087AFBB4;
                    asm volatile("" : "+r"(position_base));
                    offset = kind_index << 1;
                    offset += kind_index;
                    offset <<= 1;
                    address = (s32)position_base + 2;
                    address = offset + address;
                    value = *(s16 *)address;
                    value <<= 11;
                    coord_state->x = value;
                    position_base += 4;
                    offset += (s32)position_base;
                    value = *(s16 *)offset;
                    value <<= 11;
                    coord_state->y = value;
                }
            }
        }
        if (D_020316F4 != (*source_slot)->category) {
            func_08094330();
            func_0809F850();
            func_080A9888();
        }
    }

    D_020324B0 = 1;
    {
        u32 end_category;

        asm volatile("" : : "r"(&D_0202ECF4), "r"(&D_020316F4));
        end_category = (*source_slot)->category;
        D_020316F4 = end_category;
        asm volatile("" : "+r"(end_category));
        end_category <<= 24;
        end_category >>= 24;
        D_0202ECF4.category = end_category;
    }
    input = *source_slot;
    func_0809D938(input->category,
                  (scale * input->x) << 8,
                  (scale * input->y) << 8);
    {
        register s32 minus_one asm("r1");

        minus_one = -1;
        func_080A016C(saved_arg0, minus_one, 0);
    }
    return 0;
}
