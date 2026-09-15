#include "m2c_prelude.h"

extern s32 func_080E083C(u8, s32, s32, s32, s32);
extern u8 func_080ECF78(u8, s32);
extern u8 D_0203055C[];

struct ScriptCommand {
    s16 command;
    u16 x;
    u16 y;
    u16 parameter;
};

struct State {
    u8 status;
    u8 pad1;
    u8 object_type;
    u8 pad2a[3];
    u16 x_offset;
    u16 y_offset;
    u16 parameter_offset;
    u8 pad2[2];
    u8 counter;
    u8 pad3;
    struct ScriptCommand *script;
    struct ScriptCommand *alternate_script;
    u16 mode;
    u16 script_position;
    u16 delay;
    u16 pad4;
    void *slots[16];
};

void sub_080D1090(void)
{
    register u32 state_value asm("r4");
    register void **scan_slots;
    u8 index;

#define STATE ((struct State *)state_value)

    index = 0;
    state_value = 0x02033FD0;
    scan_slots = STATE->slots;
    {
    register u32 live_mask asm("r3") = 1;

    do {
        register void **slot_ptr asm("r0") =
            (void **)(((u32)index << 2) + (u32)scan_slots);
        register void *slot asm("r1") = *slot_ptr;

        if (slot != 0) {
            if ((*(u32 *)slot & live_mask) == 0) {
                *slot_ptr = 0;
            }
        }
        index++;
    } while (index <= 15);
    }

    if (STATE->delay == 0) {
        if (STATE->script->command != -1) {

    {
    register struct State *work_state asm("r6") = STATE;
    register void **work_slots asm("r8");

    asm volatile(
        "mov r3, #32\n\t"
        "add r3, r3, %1\n\t"
        "mov %0, r3"
        : "=r"(work_slots)
        : "r"(state_value)
        : "r3");

command_loop:
    {
                register struct ScriptCommand *script asm("r2") = work_state->script;
                register s32 command asm("r1");

                asm volatile(
                    "mov r5, #0\n\t"
                    "ldrsh %0, [%1, r5]"
                    : "=r"(command)
                    : "r"(script)
                    : "r5");

                if (command == -2) {
                    register s32 control_x_offset asm("r7");
                    register s32 control_x asm("r0");
                    register u32 current_position asm("r1");

                    STATE->script_position++;
                    control_x_offset = 2;
                    asm volatile("ldrsh %0, [%1, %2]"
                        : "=r"(control_x)
                        : "r"(script), "r"(control_x_offset));
                    asm volatile("ldrh %0, [%1, #26]"
                        : "=r"(current_position)
                        : "r"(state_value));
                    if (control_x == current_position) {
                        register struct ScriptCommand *next_script asm("r0") =
                            (struct ScriptCommand *)((u8 *)script + 4);
                        work_state->script = next_script;
                    } else {
                        work_state->script = work_state->alternate_script;
                    }
                } else {
                    register s32 x asm("r2");
                    register s32 y asm("r3");
                    register u32 parameter asm("r1");
                    void *created;

                    state_value = STATE->mode;
                    if (state_value == 1) {
                        register u32 mode_bit asm("r0") = work_state->counter;

                        mode_bit &= state_value;
                        state_value = mode_bit + 1;
                    } else if (state_value == 0x5F && func_080ECF78(work_state->counter, 3) != 0) {
                        volatile u8 *scene_base = D_0203055C;
                        u8 scene = scene_base[2];

                        state_value = 0x61;
                        if (scene == 0xD) {
                            state_value = 0x60;
                        }
                    }

                    {
                    register struct State *call_state asm("r5") =
                        (struct State *)0x02033FD0;
                    register u32 object_type asm("r0") = call_state->object_type;
                    register struct ScriptCommand *call_script asm("r1") =
                        call_state->script;
                    u32 offset;

                    asm volatile(
                        "ldrh %0, [%3, #2]\n\t"
                        "ldrh %1, [%4, #6]\n\t"
                        "add %0, %0, %1\n\t"
                        "lsl %0, %0, #16\n\t"
                        "asr %0, %0, #16\n\t"
                        "ldrh %1, [%3, #4]\n\t"
                        "ldrh %2, [%4, #8]\n\t"
                        "add %1, %1, %2\n\t"
                        "lsl %1, %1, #16\n\t"
                        "asr %1, %1, #16"
                        : "=r"(x), "=r"(y), "=&l"(offset)
                        : "r"(call_script), "r"(call_state)
                        );
                    asm volatile(
                        "ldrh %0, [%0, #6]\n\t"
                        "lsl %0, %0, #6\n\t"
                        "ldrh %1, [%2, #10]\n\t"
                        "add %0, %0, %1\n\t"
                        "lsl %0, %0, #16\n\t"
                        "lsr %0, %0, #16"
                        : "=r"(parameter), "=&l"(offset)
                        : "r"(call_state), "0"(call_script));
                    created = (void *)func_080E083C(
                        object_type, state_value, x, y, parameter);

                    index = 0;
                    if (call_state->slots[0] == 0) {
                        call_state->slots[0] = created;
                        state_value = (u32)call_state;
                    } else {
                        while (1) {
                            index++;
                            state_value = 0x02033FD0;
                            if (index > 15) {
                                break;
                            }
                            {
                            void **created_slot =
                                (void **)(((u32)index << 2) + (u32)work_slots);

                            if (*created_slot == 0) {
                                *created_slot = created;
                                break;
                            }
                            }
                        }
                    }
                    }

                    {
                    register struct ScriptCommand *advance_script asm("r1") =
                        work_state->script;

                    work_state->delay = advance_script->command;
                    advance_script += 1;
                    work_state->script = advance_script;
                    }
                    work_state->counter++;
                }
    }
    if (STATE->delay == 0) {
        register struct ScriptCommand *loop_script asm("r0") = STATE->script;
        register s32 loop_command asm("r1");

        asm volatile(
            "mov r7, #0\n\t"
            "ldrsh %0, [%1, r7]"
            : "=r"(loop_command)
            : "r"(loop_script)
            : "r7");
        if (loop_command != -1) {
            goto command_loop;
        }
    }
    }
        } else {
            goto terminal_scan;
        }
    }
    goto check_terminal;

check_terminal:
    {
    register struct ScriptCommand *tail_script asm("r0") = STATE->script;
    register s32 tail_command asm("r1");

    asm volatile(
        "mov r2, #0\n\t"
        "ldrsh %0, [%1, r2]"
        : "=r"(tail_command)
        : "r"(tail_script)
        : "r2");
    if (tail_command != -1) {
        goto decrement_delay;
    }
    }

terminal_scan:
    {
        index = 0;
        if (STATE->slots[0] == 0) {
            register void **final_slots asm("r1") = STATE->slots;

            do {
                index++;
            } while (index <= 15 && final_slots[index] == 0);
        }
        if (index == 16) {
            STATE->status = 2;
        }
    }
    goto done;

decrement_delay:
    (*(volatile u16 *)&STATE->delay)--;

done:
    ;
#undef STATE
}
