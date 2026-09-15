#include "m2c_prelude.h"

struct RecordAC468 {
    u8 kind;
    u8 pad1;
    u16 flags;
    u8 pad4[16];
    u8 direction;
    u8 group;
    u8 pad22[2];
};

extern void func_08098284(u8, s32, s32, void *);
extern void func_080988C8(s32, const void *);
extern u8 func_08098B58(const void *);
extern void func_08099F5C(void *, const void *);
extern void func_080ED128(void *, const void *);

extern u8 D_02032379;
extern u8 D_020322B2[];
extern u8 D_02030566[];
extern u8 D_020305E4[];
extern u8 D_020218E4[];
extern struct RecordAC468 D_087B2524[];
extern const void *D_087EE170[];
extern u8 D_081061C4[];

void sub_080AC468(s32 arg0, s32 arg1, s32 arg2)
{
    register u32 flags asm("r8");
    register u32 wanted_group asm("r9");
    u32 index;
    register u16 *line asm("sl");
    volatile u32 direction_bits;

    (void)arg0;
    arg1 <<= 24;
    flags = (u32)arg1 >> 24;
    arg2 <<= 24;
    wanted_group = (u32)arg2 >> 24;
    index = 0;
    if (index >= D_02032379) {
        return;
    }

    line = (u16 *)0x02030564;
    {
        register u32 direction_mask asm("r1") = 0x70;
        register u32 direction_flags asm("r2") = flags;

        asm volatile("" : "+r"(direction_mask), "+r"(direction_flags));
        direction_bits = direction_flags & direction_mask;
    }
    do {
        struct RecordAC468 *record;
        register u8 *status_to_set asm("r1");
        register u32 status_code asm("r0");
        register u32 group_present asm("r0");
        volatile u32 next;

        {
            register u8 *types asm("r0") = D_020322B2;
            register u32 type asm("r1");

            types = (u8 *)index + (u32)types;
            asm volatile("ldrb %0, [%1]"
                         : "=r"(type)
                         : "r"(types));
            types = (u8 *)(type << 1);
            types += type;
            types = (u8 *)((u32)types << 3);
            {
                register struct RecordAC468 *records asm("r1") = D_087B2524;
                register struct RecordAC468 *observed_record asm("r6") =
                    (struct RecordAC468 *)((u8 *)types + (u32)records);

                asm volatile("" : "+r"(records), "+r"(observed_record)
                             : "r"(types));
                record = observed_record;
            }
        }

        {
            register u8 *initial_status asm("r0") = (u8 *)0x02032AC8;
            register u32 zero asm("r3");

            asm volatile("" : "+r"(initial_status));
            initial_status = (u8 *)index + (u32)initial_status;
            zero = 0;
            asm volatile("strb %1, [%0]"
                         : "+r"(initial_status), "+r"(zero));
        }
        asm volatile("ldrb %0, [%1, #21]"
                     : "=r"(group_present)
                     : "r"(record));
        next = index + 1;
        if (group_present != 0) {
            register u32 scan asm("r4") = 0;
            register u8 *group_base asm("r0") = (u8 *)0x087A1E2F;
            register u8 *saved_base asm("ip");
            register u32 group_id asm("r2");
            register u32 group_offset asm("r3");
            register u8 *first asm("r1");

            asm volatile("" : "+r"(scan), "+r"(group_base));
            asm volatile("ldrb %0, [%1, #21]"
                         : "=r"(group_id)
                         : "r"(record), "r"(group_base));
            group_offset = group_id << 3;
            first = (u8 *)group_offset;
            first += (u32)group_base;
            asm volatile("ldrb %0, [%0]" : "+r"(first));
            saved_base = group_base;
            asm volatile("" : "+r"(saved_base));
            if ((u32)first != 0) {
                if ((u32)first == wanted_group) {
                    goto group_done;
                }
            {
                register u8 *loop_base asm("r5") = saved_base;
                register u32 loop_offset asm("r1") = group_offset;

                asm volatile("" : "+r"(loop_base), "+r"(loop_offset));
                do {
                    register u32 next_scan asm("r0") = scan + 1;
                    register u8 *current asm("r0");

                    next_scan <<= 16;
                    scan = next_scan >> 16;
                    if (scan > 7) {
                        break;
                    }
                    current = (u8 *)scan;
                    current += loop_offset;
                    current += (u32)loop_base;
                    asm volatile("ldrb %0, [%0]" : "+r"(current));
                    if ((u32)current == 0 || (u32)current == wanted_group) {
                        break;
                    }
                } while (1);
            }
            }
            {
                register u32 final_value asm("r0");

                final_value = group_id << 3;
                final_value = scan + final_value;
                asm volatile("add %0, %1"
                             : "+r"(final_value)
                             : "r"(saved_base));
                asm volatile("ldrb %0, [%0]" : "+r"(final_value));
            if (final_value != wanted_group) {
                ((u8 *)0x02032AC8)[index] = 4;
                {
                    register u32 error_line asm("r0") = 0x401;
                    register u16 *error_output asm("r3") = line;

                    asm volatile("" : "+r"(error_line), "+r"(error_output));
                    *error_output = error_line;
                }
            }
            }
group_done:
        }

        {
        register u8 *status_base asm("r1") = (u8 *)0x02032AC8;
        register u8 *status asm("r2");

        asm volatile("" : "+r"(status_base));
        status = (u8 *)index + (u32)status_base;
        asm volatile("" : "+r"(status));

        if (*status == 0) {
            register u32 raw_direction asm("r0") = record->direction;
            register u32 direction asm("r1") = raw_direction & 0x1C;

            if (direction == 0) {
                goto orientation_ok;
            }
            if (direction == 4 && direction_bits > 0x0F) {
                goto orientation_ok;
            }
            if (direction == 8 && direction_bits > 0x1F) {
                goto orientation_ok;
            }
            if (direction == 0xC && direction_bits > 0x2F) {
                goto orientation_ok;
            }
            if (direction == 0x10 && direction_bits > 0x3F) {
                goto orientation_ok;
            }
            *status = 3;
            {
                register u32 error_line asm("r3") = 0x401;
                register u16 *error_output asm("r2") = line;

                asm volatile("" : "+r"(error_line), "+r"(error_output));
                *error_output = error_line;
            }
            goto render;

orientation_ok:
            direction = raw_direction & 3;
            if (direction == 0) {
                goto availability;
            }
            if (direction == 1) {
                register u32 masked asm("r0") = flags & 0xC;

                if (masked == 4) {
                    goto availability;
                }
            }
            if (direction == 2) {
                register u32 masked asm("r0") = 0xC;
                register u32 flag_view asm("r3");

                asm volatile("" : "+r"(masked));
                flag_view = flags;
                asm volatile("" : "+r"(flag_view));
                masked &= flag_view;
                if (masked == 8 || masked == 0xC) {
                    goto availability;
                }
            }
            if (direction == 3) {
                register u32 masked asm("r0") = flags & 0xC;

                if (masked == 0xC) {
                    goto availability;
                }
            }
            status_to_set = (u8 *)0x02032AC8 + index;
            status_code = 2;
            goto set_status;

availability:
            {
                    register u32 available asm("r0");

                    if ((record->flags & 1) == 0) {
                        available = flags;
                        asm volatile("" : "+r"(available));
                        available &= 1;
                    } else {
                        available = flags & 2;
                    }
                    if (available == 0) {
                        status_to_set = (u8 *)0x02032AC8 + index;
                        status_code = 1;
                        goto set_status;
                    } else if (record->kind == 0x1A && (flags & 0x80) != 0) {
                        status_to_set = (u8 *)0x02032AC8 + index;
                        status_code = 5;
                        goto set_status;
                    } else {
                        goto set_available;
                    }
            }
        }
        }
        goto render;

set_status:
        *status_to_set = status_code;
        {
            register u32 error_line asm("r0") = 0x401;
            register u16 *error_output asm("r3") = line;

            asm volatile("" : "+r"(error_line), "+r"(error_output));
            *error_output = error_line;
        }
        goto render;

set_available:
        {
            register u32 available_line asm("r0") = 1;
            register u16 *available_output asm("r1") = line;

            asm volatile("" : "+r"(available_line), "+r"(available_output));
            *available_output = available_line;
        }

render:
        {
            register u8 *output asm("r4") = (u8 *)0x02030566;
            register u8 *types asm("r2") = D_020322B2;
            register u32 type asm("r0");
            u16 width;

            asm volatile("" : "+r"(output), "+r"(types));
            type = index;
            type += (u32)types;
            asm volatile("ldrb %0, [%0]" : "+r"(type));
            type <<= 2;
            {
                register const void **text_table asm("r3") = D_087EE170;
                register const void *text asm("r1");

                asm volatile("" : "+r"(text_table) : "r"(type));
                asm volatile("add %0, %1"
                             : "+r"(type)
                             : "r"(text_table));
                asm volatile("ldr %0, [%1]"
                             : "=r"(text)
                             : "r"(type));
                func_080ED128(output, text);
            }
            width = func_08098B58(output);

            if (width <= 9) {
                do {
                    func_08099F5C((void *)0x02030566, D_081061C4);
                    width++;
                } while (width <= 9);
            }
        }
        {
            register u8 *output asm("r5") = (u8 *)0x02030566;

            asm volatile("" : "+r"(output));
            func_08099F5C(output, (const void *)0x081061C8);
            {
                register u8 *entity_base asm("r1") = D_020218E4;
                register u8 *types asm("r0") = D_020322B2;

                asm volatile("" : "+r"(entity_base), "+r"(types));
                types = (u8 *)index + (u32)types;
                {
                    register u32 entity_offset asm("r2") = 0x6934;

                    asm volatile("" : "+r"(entity_offset)
                                 : "r"(entity_base), "r"(types));
                    entity_base += entity_offset;
                    asm volatile("ldrb %0, [%0]" : "+r"(types));
                    entity_base += (u32)types;
                    func_08098284(*entity_base, 2, 2, D_020305E4);
                }
            }
            func_08099F5C(output, D_020305E4);
            {
                register u32 zero asm("r0") = 0;
                register u8 *line_start asm("r1");

                asm volatile("" : "+r"(zero));
                line_start = output - 2;
                asm volatile("" : "+r"(line_start) : "r"(zero));
                func_080988C8(zero, line_start);
            }
        }
        {
            register u32 next_value asm("r3") = next;
            register u32 normalized asm("r0");

            asm volatile("" : "+r"(next_value));
            normalized = next_value << 16;
            index = normalized >> 16;
        }
    } while (index < D_02032379);
}
