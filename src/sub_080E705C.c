#include "m2c_prelude.h"

typedef struct {
    s16 limit;
    u16 kind;
    u16 value;
    u8 pad6[54];
} AdmissionEntry;

typedef struct {
    u8 pad[2];
    u8 data[1];
} AdmissionKindBase;

typedef struct {
    u8 pad[4];
    u8 data[1];
} AdmissionValueBase;

typedef struct {
    u8 group;
    u8 pad1[7];
    u8 ids[10];
    u16 values[10];
    u8 pad2[10];
    u8 limit;
} AdmissionState;

asm(".set sub_080E705C_entries, 0x087B79B0");
extern u8 sub_080E705C_entries[];

#define OUTPUT ((u8 *)0x02032E20)
#define ENTRIES ((AdmissionEntry *)sub_080E705C_entries)

s32 sub_080E705C(AdmissionState *state, u8 reset)
{
    u8 outer;
    register u32 group asm("r2");
    s32 next;
    u8 i;
    u8 slot;
    s32 entry_offset;
    volatile s32 saved_reset;
    volatile s32 saved_outer_double;
    s32 outer_double;

    saved_reset = reset;
    if (reset != 0) {
        for (outer = 0; outer <= 9; outer++) {
            state->ids[outer] = 0;
        }
    }
    {
        register u32 initial_zero asm("r0") = 0;
        register u8 *initial_output asm("r5");

        asm volatile("" : "+r"(initial_zero));
        initial_output = OUTPUT;
        *initial_output = initial_zero;
    }
    outer = 0;
    do {
        {
        register s32 entry_limit asm("r0");
        register AdmissionEntry *entry asm("r4");
        register u32 entry_base asm("r6");
        register s32 entry_zero asm("r5");

        outer_double = outer * 2;
        entry_offset = (outer_double + outer) * 2;
        asm volatile(
            "mov r5, %1\n"
            "ldrb %0, [r5]"
            : "=l"(group)
            : "h"(state)
            : "r5", "memory");
        entry_offset += group * 0x3C;
        entry_base = (u32)sub_080E705C_entries;
        entry = (AdmissionEntry *)(entry_offset + entry_base);
        entry_zero = 0;
        asm volatile("ldrsh %0, [%1, %2]"
                     : "=r"(entry_limit)
                     : "r"(entry), "r"(entry_zero));
        next = outer + 1;
        saved_outer_double = outer_double;
        if (entry_limit == 0) goto loop_end;
        {
            register s32 initial_kind asm("r0");

            asm volatile(
                "mov %0, %1\n"
                "add %0, #2\n"
                "add %0, %2, %0\n"
                "mov %1, #0\n"
                "ldrsh %0, [%0, %1]"
                : "=&r"(initial_kind), "+r"(entry_base)
                : "r"(entry_offset));
            if (initial_kind == 0) goto loop_end;
        }
        if (saved_reset == 0) {
            if (entry->limit == state->limit) goto eligible;
            goto loop_end;
        }
        {
            register s32 compare_limit asm("r1");
            register s32 compare_zero asm("r5");

            compare_zero = 0;
            asm volatile("ldrsh %0, [%1, %2]"
                         : "=l"(compare_limit)
                         : "l"(entry), "l"(compare_zero)
                         : "memory");
            if (compare_limit <= state->limit) goto eligible;
        }
        goto loop_end;
        }
eligible:
        {
            register u8 *ids asm("r4");

            asm volatile(
                ".set e705c_dispatch_ldr_count, 0\n"
                ".macro e705c_install_dispatch_ldr\n"
                ".macro ldr dst, src:vararg\n"
                ".purgem ldr\n"
                ".if e705c_dispatch_ldr_count == 1\n"
                "ldr \\dst, .Le705c_pool\n"
                ".elseif e705c_dispatch_ldr_count == 2\n"
                "ldr \\dst, .Le705c_pool+4\n"
                ".else\n"
                "ldr \\dst, \\src\n"
                ".endif\n"
                ".set e705c_dispatch_ldr_count, e705c_dispatch_ldr_count + 1\n"
                ".if e705c_dispatch_ldr_count < 3\n"
                "e705c_install_dispatch_ldr\n"
                ".endif\n"
                ".endm\n"
                ".endm\n"
                "e705c_install_dispatch_ldr\n"
                ".macro mov dst, src\n"
                ".purgem mov\n"
                "mov r7, r9\n"
                "add r7, #1\n"
                "mov \\dst, \\src\n"
                ".align 2, 0\n"
                ".Le705c_pool:\n"
                ".word sub_080E705C_entries\n"
                ".word .Le705c_table\n"
                ".align 2, 0\n"
                ".align 2, 0\n"
                ".Le705c_table:\n"
                ".word .Le705c_case01\n"
                ".word .Le705c_case01\n"
                ".word .L30\n"
                ".word .L30\n"
                ".word .L30\n"
                ".word .L39\n"
                ".word .L39\n"
                ".word .L39\n"
                ".word .L48\n"
                ".word .L48\n"
                ".word .L48\n"
                ".word .L57\n"
                ".word .L57\n"
                ".word .L57\n"
                ".word .L65\n"
                ".word .L65\n"
                ".word .L125\n"
                ".word .L125\n"
                ".word .L125\n"
                ".word .L125\n"
                ".word .L73\n"
                ".word .L73\n"
                ".word .L125\n"
                ".word .L81\n"
                ".word .L13\n"
                ".word .L13\n"
                ".word .L90\n"
                ".word .L99\n"
                ".word .L108\n"
                ".word .L117\n"
                ".word .L125\n"
                ".word .L125\n"
                ".word .L81\n"
                ".word .L13\n"
                ".word .L13\n"
                ".word .L90\n"
                ".word .L99\n"
                ".word .L108\n"
                ".word .L117\n"
                ".pushsection .e705c_discard, \"\", %progbits\n"
                ".endm");
            switch ((s16)(({
                register u32 selector_row asm("r1");
                register u32 selector_work asm("r0");

                selector_row = saved_outer_double + outer;
                selector_row *= 2;
                selector_work = group * 0x3C;
                selector_row += selector_work;
                selector_work = (u32)ENTRIES;
                selector_work += 2;
                selector_row += selector_work;
                selector_work = *(u16 *)selector_row;
                selector_work;
            }) - 1)) {
            case 0:
            case 1:
            {
                register u8 *loop_ids asm("r2");
                register s32 zero asm("r3");
                u8 *id_address;

                asm volatile(".popsection\n.Le705c_case01:");
                i = 0;
                ids = state->ids;
                asm volatile("mov %0, %1\nadd %0, #1"
                             : "=r"(next) : "r"(outer));
                loop_ids = ids;
                zero = 0;
                do {
                    id_address = &loop_ids[i];
                    if ((u8)(*id_address - 1) <= 1) *id_address = zero;
                    i += 1;
                } while (i <= 9);
                break;
            }
            case 2:
            case 3:
            case 4:
            {
                register s32 row_offset asm("sl");
                register s16 *table_values asm("r8");
                u8 *id_address;

                i = 0;
                ids = state->ids;
                asm volatile("mov %0, %1\nadd %0, #1"
                             : "=r"(next) : "r"(outer));
                row_offset = (saved_outer_double + outer) * 2;
                {
                    register s16 *table_seed asm("r6");

                    table_seed = (s16 *)0x087B79B4;
                    asm volatile("" : "+r"(table_seed));
                    table_values = table_seed;
                }
                do {
                    id_address = &ids[i];
                    if ((u8)(*id_address - 3) <= 2 &&
                        (s16)state->values[i] ==
                            *(s16 *)((u8 *)table_values +
                                     (({
                                         register AdmissionState *group_view
                                             asm("r0");

                                         group_view = state;
                                         asm volatile("" : "+r"(group_view));
                                         group_view->group;
                                     }) * 0x3C + row_offset))) {
                        *id_address = 0;
                    }
                    i += 1;
                } while (i <= 9);
                break;
            }
            case 5:
            case 6:
            case 7:
            {
                register u8 *loop_ids asm("r2");
                register s32 zero asm("r3");
                u8 *id_address;
                i = 0;
                ids = state->ids;
                asm volatile("mov %0, %1\nadd %0, #1"
                             : "=r"(next) : "r"(outer));
                loop_ids = ids;
                zero = 0;
                do {
                    id_address = &loop_ids[i];
                    if ((u8)(*id_address - 6) <= 2) *id_address = zero;
                    i += 1;
                } while (i <= 9);
                break;
            }
            case 8:
            case 9:
            case 10:
            {
                register u8 *loop_ids asm("r2");
                register s32 zero asm("r3");
                u8 *id_address;
                i = 0;
                ids = state->ids;
                asm volatile("mov %0, %1\nadd %0, #1"
                             : "=r"(next) : "r"(outer));
                loop_ids = ids;
                zero = 0;
                do {
                    id_address = &loop_ids[i];
                    if ((u8)(*id_address - 9) <= 2) *id_address = zero;
                    i += 1;
                } while (i <= 9);
                break;
            }
            case 11:
            case 12:
            case 13:
            {
                register u8 *loop_ids asm("r2");
                register s32 zero asm("r3");
                u8 *id_address;
                i = 0;
                ids = state->ids;
                asm volatile("mov %0, %1\nadd %0, #1"
                             : "=r"(next) : "r"(outer));
                loop_ids = ids;
                zero = 0;
                do {
                    id_address = &loop_ids[i];
                    if ((u8)(*id_address - 12) <= 2) *id_address = zero;
                    i += 1;
                } while (i <= 9);
                break;
            }
            case 14:
            case 15:
            {
                register u8 *loop_ids asm("r2");
                register s32 zero asm("r3");
                u8 *id_address;
                i = 0;
                ids = state->ids;
                asm volatile("mov %0, %1\nadd %0, #1"
                             : "=r"(next) : "r"(outer));
                loop_ids = ids;
                zero = 0;
                do {
                    id_address = &loop_ids[i];
                    if ((u8)(*id_address - 15) <= 1) *id_address = zero;
                    i += 1;
                } while (i <= 9);
                break;
            }
            case 20:
            case 21:
            {
                register u8 *loop_ids asm("r2");
                register s32 zero asm("r3");
                u8 *id_address;
                i = 0;
                ids = state->ids;
                asm volatile("mov %0, %1\nadd %0, #1"
                             : "=r"(next) : "r"(outer));
                loop_ids = ids;
                zero = 0;
                do {
                    id_address = &loop_ids[i];
                    if ((u8)(*id_address - 21) <= 1) *id_address = zero;
                    i += 1;
                } while (i <= 9);
                break;
            }
            case 23:
            case 32:
            {
                register u8 *loop_ids asm("r2");
                register s32 zero asm("r3");
                u8 *id_address;
                u8 id;
                i = 0;
                ids = state->ids;
                asm volatile("mov %0, %1\nadd %0, #1"
                             : "=r"(next) : "r"(outer));
                loop_ids = ids;
                zero = 0;
                do {
                    id_address = &loop_ids[i];
                    id = *id_address;
                    if (id == 24 || id == 33) *id_address = zero;
                    i += 1;
                } while (i <= 9);
                break;
            }
            case 26:
            case 35:
            {
                register u8 *loop_ids asm("r2");
                register s32 zero asm("r3");
                u8 *id_address;
                u8 id;
                i = 0;
                ids = state->ids;
                asm volatile("mov %0, %1\nadd %0, #1"
                             : "=r"(next) : "r"(outer));
                loop_ids = ids;
                zero = 0;
                do {
                    id_address = &loop_ids[i];
                    id = *id_address;
                    if (id == 27 || id == 36) *id_address = zero;
                    i += 1;
                } while (i <= 9);
                break;
            }
            case 27:
            case 36:
            {
                register u8 *loop_ids asm("r2");
                register s32 zero asm("r3");
                u8 *id_address;
                u8 id;
                i = 0;
                ids = state->ids;
                asm volatile("mov %0, %1\nadd %0, #1"
                             : "=r"(next) : "r"(outer));
                loop_ids = ids;
                zero = 0;
                do {
                    id_address = &loop_ids[i];
                    id = *id_address;
                    if (id == 28 || id == 37) *id_address = zero;
                    i += 1;
                } while (i <= 9);
                break;
            }
            case 28:
            case 37:
            {
                register u8 *loop_ids asm("r2");
                register s32 zero asm("r3");
                u8 *id_address;
                u8 id;
                i = 0;
                ids = state->ids;
                asm volatile("mov %0, %1\nadd %0, #1"
                             : "=r"(next) : "r"(outer));
                loop_ids = ids;
                zero = 0;
                do {
                    id_address = &loop_ids[i];
                    id = *id_address;
                    if (id == 29 || id == 38) *id_address = zero;
                    i += 1;
                } while (i <= 9);
                break;
            }
            case 29:
            case 38:
            {
                register u8 *loop_ids asm("r2");
                register s32 zero asm("r3");
                u8 *id_address;
                u8 id;
                i = 0;
                ids = state->ids;
                asm volatile("mov %0, %1\nadd %0, #1"
                             : "=r"(next) : "r"(outer));
                loop_ids = ids;
                zero = 0;
                do {
                    id_address = &loop_ids[i];
                    id = *id_address;
                    if (id == 30 || id == 39) *id_address = zero;
                    i += 1;
                } while (i <= 9);
                break;
            }
            default:
            {
                register s32 row_offset asm("r6");
                register u8 *default_ids asm("r8");
                register s32 zero asm("sl");
                register s32 signed_kind asm("r0");
                register s32 kind_base_zero asm("r1");
                register u8 *id_address asm("r3");
                register s32 id asm("r2");

                i = 0;
                asm volatile("" : "+r"(i));
                ids = state->ids;
                asm volatile("mov %0, %1\nadd %0, #1"
                             : "=r"(next) : "r"(outer));
                default_ids = ids;
                {
                    register s32 row_work asm("r0");
                    row_work = saved_outer_double + outer;
                    asm volatile("" : "+r"(row_work));
                    row_offset = row_work * 2;
                }
                zero = i;
                do {
                    id_address = &default_ids[i];
                    id = *id_address;
                    signed_kind = state->group * 0x3C;
                    signed_kind = row_offset + signed_kind;
                    kind_base_zero = 0x087B79B2;
                    signed_kind += kind_base_zero;
                    kind_base_zero = 0;
                    asm volatile("ldrsh %0, [%0, %1]"
                                 : "+r"(signed_kind)
                                 : "r"(kind_base_zero));
                    if (id == signed_kind) {
                        *id_address = zero;
                    }
                    i += 1;
                } while (i <= 9);
                break;
            }
            }
        slot = 0;
        if (state->ids[0] != 0) {
            u8 *scan_ids;

            scan_ids = ids;
            do {
                slot += 1;
                if (slot > 9) goto loop_end;
            } while (scan_ids[slot] != 0);
        }
        if (slot <= 9) {
            s32 row_offset;
            u16 kind;
            u16 value;
            register u8 *kind_output asm("r3");
            register u8 *output_base asm("r6");
            register u8 *kind_output_base asm("r0");
            register u32 kind_address asm("r0");
            register u32 kind_table_base asm("r1");
            register u32 state_value_offset asm("r0");
            register u16 *state_value asm("r4");
            register u8 *value_output asm("r3");
            register u8 *value_output_base asm("r0");
            u8 *selected_id;

            selected_id = &ids[slot];
            kind_output_base = &OUTPUT[1];
            asm volatile("" : "+r"(kind_output_base));
            output_base = OUTPUT;
            kind_output = (u8 *)(u32)output_base[0];
            kind_output += (u32)kind_output_base;
            row_offset = (saved_outer_double + outer) * 2;
            kind_address = state->group * 0x3C;
            kind_address = row_offset + kind_address;
            asm volatile(
                ".macro ldr dst, src\n"
                ".purgem ldr\n"
                ".set e705c_entries_pool, \\src\n"
                "ldr \\dst, \\src\n"
                ".endm");
            kind_table_base = (u32)ENTRIES;
            kind_table_base += 2;
            kind_address += kind_table_base;
            kind = *(u16 *)kind_address;
            *kind_output = (u8)kind;
            *selected_id = (u8)kind;
            state_value_offset = slot << 1;
            state_value = state->values;
            state_value = (u16 *)((u8 *)state_value + state_value_offset);
            value_output_base = &OUTPUT[0xB];
            asm volatile("" : "+r"(value_output_base));
            value_output = (u8 *)(u32)output_base[0];
            value_output += (u32)value_output_base;
            asm volatile(
                "mov r5, %2\n"
                "ldrb r1, [r5]\n"
                "lsl %0, r1, #4\n"
                "sub %0, %0, r1\n"
                "lsl %0, %0, #2\n"
                "add %1, %1, %0\n"
                "ldr %0, e705c_entries_pool\n"
                "add %0, #4\n"
                "add %1, %1, %0\n"
                "ldrh %0, [%1]"
                : "=&l"(value), "+l"(row_offset)
                : "h"(state)
                : "r1", "r5", "cc", "memory");
            *value_output = (u8)value;
            *state_value = (u8)value;
            output_base[0] += 1;
        }
        }
loop_end:
        outer = next;
    } while (outer <= 9);
    {
        register u8 *final_output asm("r6");

        final_output = OUTPUT;
        if (final_output[0] != 0) {
            return 1;
        }
    }
    return 0;
}
