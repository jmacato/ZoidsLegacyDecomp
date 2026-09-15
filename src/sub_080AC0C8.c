#include "m2c_prelude.h"

struct RecordAC0C8 {
    u8 unk0;
    u8 unk1;
    u8 object_index;
    u8 pad3[3];
    s16 value;
    u8 pad8[0x32];
    s16 limit;
    u8 pad3C[0x34];
};

extern u8 D_020218E4[];
extern struct RecordAC0C8 D_020218E8[];
extern s32 D_087EDD54[];

extern void func_080981F0(s32, s32, s32, s32, s32);
extern void func_0809844C(s32, s32, s32, s32, s32, s32, s32);
extern void func_080986B4(s32);
extern s32 func_080E7B64(u8);
extern s16 func_080ECD98(s16, s32);

void sub_080AC0C8(void)
{
    register u32 index asm("r8");
    register u8 *entity_base asm("r9");
    register s32 row_height asm("r10");
    register s32 row_height_value asm("r2");

    func_080986B4(1);
    index = 0;
    entity_base = D_020218E4;
    row_height_value = 16;
    asm volatile("" : "+r"(row_height_value));
    row_height = row_height_value;
    do {
        register s32 map_offset asm("r1");
        register u8 *map asm("r0");
        register u8 *slot asm("r1");
        register s32 entity_id asm("r0");
        register s32 index_copy asm("r3");

        map_offset = 0x690C;
        map = (u8 *)((s32)entity_base + map_offset);
        index_copy = index;
        asm volatile("" : "+r"(index_copy));
        slot = (u8 *)(index_copy + (s32)map);
        entity_id = *slot;

        if (entity_id != 0) {
            register s32 entity_copy asm("r1");
            register s32 entity_offset asm("r0");
            register struct RecordAC0C8 *record asm("r6");
            register u8 *record_base asm("r1");
            register u8 *state asm("r1");
            s32 retained_line;
            s32 signed_line;
            s32 value;
            s32 less;
            s16 second_line;

            entity_copy = entity_id;
            entity_offset = entity_copy << 3;
            entity_offset -= entity_copy;
            entity_offset <<= 4;
            record_base = entity_base + 4;
            record = (struct RecordAC0C8 *)(entity_offset + (s32)record_base);
            state = entity_base;
            asm volatile("" : "+r"(state));
            if (state[0] == 0) {
                s32 line;
                s32 shifted_line;

                func_080981F0(D_087EDD54[record->unk0], 0, 1, 0,
                    (line = index_copy * 2,
                     shifted_line = index_copy << 17,
                     shifted_line >> 16));
                asm volatile("" : "+r"(shifted_line));
                retained_line = line;
                signed_line = shifted_line >> 16;
            } else {
                register s32 row_index asm("r3");
                register u8 *object_base asm("r0");
                register s32 object_offset asm("r2");
                s32 line;
                s32 shifted_line;

                object_base = entity_base + (record->object_index << 6);
                object_offset = 0x5A94;
                asm volatile("" : "+r"(object_offset));
                func_080981F0(func_080E7B64(object_base[object_offset]),
                    0, 1, 0,
                    (row_index = index,
                     line = row_index * 2,
                     shifted_line = row_index << 17,
                     shifted_line >> 16));
                asm volatile("" : "+r"(shifted_line));
                retained_line = line;
                signed_line = shifted_line >> 16;
            }
            func_080981F0(0x081061A0, 0, 1, 14, signed_line);
            {
                register s32 occupy_r2 asm("r2");
                register s32 occupy_r3 asm("r3");

                asm volatile("" : "=r"(occupy_r2), "=r"(occupy_r3));
                value = record->value;
                asm volatile("" : : "r"(occupy_r2), "r"(occupy_r3));
            }
            less = 0;
            if (record->value < func_080ECD98(record->limit, 10)) {
                less = 1;
            }
            func_0809844C(value, 4, less, 10, 1, row_height, signed_line);
            second_line = retained_line + 1;
            func_080981F0(0x081061A4, 0, 1, 15, second_line);
            func_0809844C(record->limit, 4, 0, 10, 1, row_height, second_line);
        } else {
            register s32 occupy_r1 asm("r1");
            s32 empty_line;

            asm volatile("" : "=r"(occupy_r1));
            empty_line = index << 1;
            asm volatile("" : : "r"(occupy_r1));
            func_080981F0(0x081061A8, 0, 1, 0, empty_line);
        }
        index = (u8)(index + 1);
    } while (index <= 5);
}
