#include "m2c_prelude.h"

extern void func_08098248(s32, s32, s32);
extern void func_080986B4(s32);
extern void func_0809A9C8(u8, u8, s32, s32, s32, s32);

void sub_080CCBD4(u8 source, u16 id, u8 unit_arg, u32 variant_arg, s32 slot_arg)
{
    u8 unit = unit_arg;
    u8 variant = variant_arg;
    register u32 slot asm("r4") = (u8)slot_arg;
    u8 *state = (u8 *)0x0203055C;
    u8 *table = (u8 *)0x087EF590;
    register u8 *entry asm("r6");
    register u32 slot8 asm("r5");
    register u32 variant2 asm("sl");
    register u32 unit16 asm("r4");
    register u32 variant2_copy asm("r3");
    s32 value;

    asm volatile(
        "ldrb r0, [r0, #5]\n\t"
        "cmp r0, #5\n\t"
        "bne 1f\n\t"
        "cmp r2, #52\n\t"
        "beq 2f\n\t"
        "cmp r2, #94\n\t"
        "bne 1f\n"
        "2:\n\t"
        "mov r0, r9\n\t"
        "cmp r0, #2\n\t"
        "bne 1f\n\t"
        "movs r1, #97\n\t"
        "mov r8, r1\n"
        "1:"
        : "+r"(state), "+r"(unit)
        : "r"(variant), "r"(unit_arg)
        : "r1", "cc", "memory");

    {
        register u8 *initial_table asm("r2") = (u8 *)0x087EF590;
        asm volatile(
            "lsl r5, r4, #3\n\t"
            "mov r3, r9\n\t"
            "lsl r3, r3, #1\n\t"
            "mov sl, r3\n\t"
            "mov r1, sl\n\t"
            "add r1, r9\n\t"
            "lsl r1, r1, #3\n\t"
            "add r1, r5, r1\n\t"
            "mov r0, r8\n\t"
            "lsl r4, r0, #4\n\t"
            "sub r0, r4, r0\n\t"
            "lsl r0, r0, #3\n\t"
            "add r1, r1, r0\n\t"
            "add r6, r1, r2"
            : "=r"(entry), "=r"(slot8), "=r"(variant2), "=r"(unit16)
            : "r"(initial_table), "r"(slot), "r"(variant), "r"(unit)
            : "r0", "r1", "r3", "cc", "memory");
    }
    func_0809A9C8(unit, entry[4],
        0, 0x3DC, 0xF, 0x02002880);
    func_080986B4(1);
    variant2_copy = variant2;
    asm volatile("" : "+r"(variant2_copy));

    {
        register u32 unit_test asm("r1") = unit;
        asm volatile("" : "+r"(unit_test));
        if (unit_test == 0x64) {
            value = *(s32 *)entry;
            goto play;
        }
    }

    if (variant == 0) {
        if (id == 0x136) {
            value = 0x08028063;
            goto play;
        }
        if (id == 0x12B || id == 0x133 || id == 0x137 ||
            id == 0x13B || id == 0x13F || id == 0x163 ||
            id == 0x1C7 || id == 0x1CB || id == 0x1CF ||
            id == 0x1D3 || id == 0x1DB || id == 0x2A0 ||
            id == 0x2A4 || id == 0x2CF) {
            value = 0x08028088;
            goto play;
        }
        if (id == 0x1FA) {
            value = 0x080280B1;
            goto play;
        }
        if (id == 0x295) {
            value = 0x080280D8;
            goto play;
        }
        if (id == 0xEA) {
            value = 0x080280FD;
            goto play;
        }
    }
    if (variant == 1) {
            if (id == 0x320 && unit == 1) {
                value = 0x0802811E;
                goto play;
            }
            if (variant == 1) {
                if (id == 0x320 && (unit == 0xE || unit == 0x16)) {
                    value = 0x0802812B;
                    goto play;
                }
                if (variant == 1) {
                    if (id == 0x320 && unit == 0x1C) {
                        value = 0x08028136;
                        goto play;
                    }
                    if (variant == 1) {
                        if (id == 0x320 && unit == 0x1D) {
                            value = 0x08028145;
                            goto play;
                        }
                        if (variant == 1 && (u16)(id - 0xA5) <= 2) {
                            value = 0x08028158;
                            goto play;
                        }
                    }
                }
            }
    }

    if (variant == 0) {
        if (id == 0x2C7) {
            value = 0x08028167;
            goto play;
        }
        if (id == 0x2CA) {
            value = 0x08028182;
            goto play;
        }
    }

    if (unit != 1 || variant != 0) {
        register u8 *final_table asm("r2") = table;
        register s32 final_value asm("r0");
        asm volatile(
            "mov r1, r9\n\t"
            "add r0, r3, r1\n\t"
            "lsl r0, r0, #3\n\t"
            "add r0, r5, r0\n\t"
            "mov r3, r8\n\t"
            "sub r1, r4, r3\n\t"
            "lsl r1, r1, #3\n\t"
            "add r0, r0, r1\n\t"
            "add r0, r0, r2\n\t"
            "ldr r0, [r0]"
            : "=r"(final_value), "+r"(variant2_copy)
            : "r"(final_table), "r"(slot8), "r"(unit16),
              "r"(unit), "r"(variant)
            : "r1", "cc", "memory");
        value = final_value;
play:
        func_08098248(value, 0, 1);
        return;
    }

    func_08098248(source * 0x2E + 0x0203EE0C, 0, 1);
}
