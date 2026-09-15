#include "m2c_prelude.h"

struct RecordA6570 {
    u8 state;
    u8 unk1;
    u8 object_index;
    u8 flags;
    u8 rest[0x6C];
};

struct InputA6570 {
    u8 unk0;
    u8 mask;
};

u8 func_080E5320(void *, u8);
void func_080E5880(void *, s32);
void func_080A016C(s32, s32, s32);

s32 sub_080A6570(s32 arg0, struct InputA6570 **arg1)
{
    struct InputA6570 **saved_arg1 = arg1;
    register u32 saved_arg0 asm("r8");
    register u32 index asm("r3");
    register struct RecordA6570 *base asm("r6");
    register u8 *before_base asm("r5");
    register u8 *effect_base asm("r9");

    asm volatile("" : : "r"(saved_arg1), "r"(arg0));
    saved_arg0 = (u8)arg0;
    asm volatile("" : : "r"(saved_arg0));
    index = 1;
    base = (struct RecordA6570 *)0x020218E8;
    before_base = (u8 *)base - 4;
    effect_base = before_base + 0x5A94;

scan:
    {
        register struct RecordA6570 *record asm("r4");
        register s32 record_offset asm("r0");
        register u32 object_index asm("r0");
        register u32 kind_offset asm("r1");
        register u32 kind asm("r0");

        record_offset = index << 3;
        record_offset -= index;
        record_offset <<= 4;
        record = (struct RecordA6570 *)(record_offset + (s32)base);
        asm volatile("" : : "r"(record));
        object_index = record->object_index;
        asm volatile("" : "+r"(object_index));
        object_index <<= 6;
        object_index += (u32)before_base;
        kind_offset = 0x5A94;
        object_index += kind_offset;
        kind = *(u8 *)object_index;
        if ((kind == 0x1E || kind == 0x5F) &&
            (u8)(record->state - 0x19) <= 5) {
            register struct InputA6570 *input asm("r2") = *saved_arg1;
            register u32 flags asm("r1") = record->flags;
            register u32 mask asm("r0") = input->mask;
            asm volatile("" : "+r"(flags));
            asm volatile("" : "+r"(mask));
            mask &= flags;
            if (mask != 0) {
                register u32 effect_offset asm("r1");
                record->state = func_080E5320(record, input->mask);
                asm volatile("" : : "r"(saved_arg1));
                effect_offset = record->object_index;
                asm volatile("" : "+r"(effect_offset));
                effect_offset <<= 6;
                effect_offset += (u32)effect_base;
                func_080E5880(record, effect_offset);
                goto done;
            }
        }
    }

    {
        register u32 next_index asm("r0");
        next_index = index + 1;
        index = (u8)next_index;
    }
    if (index <= 0xCE) {
        goto scan;
    }

done:
    func_080A016C(saved_arg0, -1, 0);
    return 0;
}
