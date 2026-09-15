#include "m2c_prelude.h"

typedef struct {
    u8 flags;
    u8 pad01[0x16];
    u8 field17;
    u8 field18;
    u8 field19;
    u8 field1A;
} SoundChannel;

extern void func_80EB5F8(s32 command, SoundChannel *channel);
extern void func_80EB5DC(s32 command, SoundChannel *channel);

#define SAVE_LINK_REGISTER() asm volatile("mov ip, lr")
#define RETURN_THROUGH_LINK_REGISTER() asm volatile("bx ip")

__attribute__((naked)) void sub_080EB618(s32 command, SoundChannel *channel)
{
    register s32 live_command asm("r0") = command;
    register SoundChannel *live_channel asm("r1") = channel;
    register u32 value asm("r3");

    SAVE_LINK_REGISTER();
    func_80EB5F8(live_command, live_channel);
    asm volatile("" : "=r"(live_command), "=r"(live_channel), "=r"(value));
    live_channel->field17 = value;
    if (value == 0) {
        func_80EB5DC(live_command, live_channel);
    }
    RETURN_THROUGH_LINK_REGISTER();
}
