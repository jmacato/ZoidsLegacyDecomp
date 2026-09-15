#include "m2c_prelude.h"

void sub_080A016C(u16 script_id, s32 selector_arg, u8 value)
{
    u8 **script;
    u32 script_offset;
    u8 *lengths;
    u8 nesting[4];
    u8 depth;
    u8 terminators;
    u16 selector_class;
    register s32 selector_shifted asm("r5");
    s32 selector_value;

    script_offset = (u32)script_id << 2;
    script = (u8 **)0x020314C4;
    asm volatile("" : "+r"(script));
    script = (u8 **)(script_offset - (0 - (u32)script));
    terminators = 0;
    depth = 0;
    selector_shifted = (u32)(u16)selector_arg << 16;
    selector_value = selector_shifted >> 16;
    selector_class = (u32)(selector_shifted + 0xFFF10000) >> 16;
    lengths = (u8 *)0x087A17FC;
    goto check_selector_class;

decrement_terminators:
    terminators--;

check_selected_opcode:
{
    register s32 selected_selector asm("r1");

    if (selector_value == 0x12 && (*script)[0] == 0x12) {
        if (depth == 1) {
            if ((*script)[1] == value)
                return;
        } else if (--nesting[depth - 1] == 0) {
            depth--;
        }
    }

    selected_selector = selector_shifted >> 16;
    if (selected_selector == -1 || (*script)[0] == selected_selector) {
        if ((u16)(selected_selector - 0xF) <= 1)
            goto scan_terminators;
        if (selected_selector != 0x12)
            return;
    }
}

check_selector_class:
    if (selector_class > 1)
        goto check_nesting;

scan_terminators:
    if ((*script)[0] == 0xE || (*script)[0] == 0x19 ||
        (*script)[0] == 0x1A || (*script)[0] == 0x1B ||
        (*script)[0] == 0x1C)
        terminators++;

check_nesting:
    if (selector_value == 0x12 && (*script)[0] == 0x11) {
        nesting[depth] = 0;
        depth++;
    }

    switch ((*script)[0]) {
    case 9: {
        u32 i;
        u8 count = (*script)[1];

        *script += 2;
        i = 0;
        while (i < count) {
            *script += 4;
            i++;
        }
        break;
    }
    case 0x20:
        *script += 1;
        if ((*script)[0] != 0) {
            do {
                if ((*script)[0] == 1)
                    *script += 1;
                else if ((*script)[0] == 2)
                    *script += 2;
                else if ((*script)[0] == 0xD && depth != 0)
                    nesting[depth - 1]++;
                *script += 1;
            } while ((*script)[0] != 0);
        }
        *script += 1;
        break;
    default:
        *script += lengths[(*script)[0]];
        break;
    }

    {
        register s32 tail_selector asm("r1");

        asm volatile("" : "+r"(selector_shifted));
        tail_selector = selector_shifted >> 16;
        if ((u32)(selector_shifted + 0xFFF10000) >> 16 > 1)
            goto check_selected_opcode;
        if ((*script)[0] != tail_selector)
            goto check_selected_opcode;
        if (terminators == 1)
            return;
    }
    goto decrement_terminators;
}
