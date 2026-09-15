#include "m2c_prelude.h"

struct A0B8Record {
    u8 pad00[0x10];
    s32 output_x;
    s32 output_y;
    u8 mode;
    u8 previous_mode;
    u8 selected;
    u8 current;
    u8 timer;
    u8 pad1d[3];
    void *callback_target;
};

extern s32 D_087A1B98[][2];
extern u16 func_080A9A54(struct A0B8Record *);
extern void func_08094564(void *, u16);

void sub_080AA0B8(struct A0B8Record *record)
{
    u8 old_current = record->current;

    if (record->selected != old_current) {
        if (++record->timer != 3) goto timer_done;
        {
            if (record->selected > record->current) {
                if (record->selected - record->current <= 3) {
                    record->current = record->current + 1;
                } else {
                    record->current = (record->current - 1) & 7;
                }
            } else {
                if (record->current - record->selected <= 4) {
                    record->current = record->current - 1;
                } else {
                    record->current = (record->current + 1) & 7;
                }
            }
        }
    }
    record->timer = 0;
timer_done:

    {
        register s32 mode_r0 asm("r0");
        mode_r0 = record->mode;
        asm volatile("" : "+r"(mode_r0));
        if (mode_r0 == 0) goto mode_zero;
        if (mode_r0 < 0) goto mode_done;
        if (mode_r0 > 3) goto mode_done;
    }
    if (old_current != record->current) goto nonzero_callback;
    if (record->previous_mode != 0) goto mode_switch;
    goto nonzero_callback;

mode_zero:
    if (old_current != record->current) goto zero_callback;
    if (record->previous_mode == 0) goto zero_finish;
zero_callback:
    func_08094564(record->callback_target, func_080A9A54(record));
zero_finish:
    record->output_y = 0;
    record->output_x = 0;
    goto mode_done;

nonzero_callback:
    func_08094564(record->callback_target, func_080A9A54(record));
mode_switch:
    switch (record->mode) {
    case 1:
        record->output_x = D_087A1B98[record->selected][0] / 2;
        record->output_y = D_087A1B98[record->selected][1] / 2;
        break;
    case 2:
        record->output_x = D_087A1B98[record->selected][0];
        record->output_y = D_087A1B98[record->selected][1];
        break;
    case 3:
        record->output_x = D_087A1B98[record->selected][0] * 2;
        record->output_y = D_087A1B98[record->selected][1] * 2;
        break;
    }
mode_done:
    record->previous_mode = record->mode;
}
