#include "mp2k_command_types.h"

__attribute__((naked)) void sub_080EAF80(
    MusicPlayerInfo *player, MusicPlayerTrack *track)
{
    register MusicPlayerInfo *live_player asm("r0") = player;
    register MusicPlayerTrack *live_track asm("r1") = track;
    register u32 value asm("r3");

    SAVE_LINK_REGISTER();
    func_80EAEF4(live_player, live_track);
    asm volatile("" : "=r"(live_player), "=r"(live_track), "=r"(value));
    live_track->priority = value;
    RETURN_THROUGH_LINK_REGISTER();
}

__attribute__((naked)) void sub_080EAF8C(
    MusicPlayerInfo *player, MusicPlayerTrack *track)
{
    register MusicPlayerInfo *live_player asm("r0") = player;
    register MusicPlayerTrack *live_track asm("r1") = track;
    register u32 value asm("r3");

    SAVE_LINK_REGISTER();
    func_80EAEF4(live_player, live_track);
    asm volatile("" : "=r"(live_player), "=r"(live_track), "=r"(value));
    value <<= 1;
    live_player->tempo = value;
    {
        register u32 scale asm("r2") = live_player->tempoScale;

        value *= scale;
    }
    value >>= 8;
    live_player->tempoInterval = value;
    RETURN_THROUGH_LINK_REGISTER();
}

__attribute__((naked)) void sub_080EAFA0(
    MusicPlayerInfo *player, MusicPlayerTrack *track)
{
    register MusicPlayerInfo *live_player asm("r0") = player;
    register MusicPlayerTrack *live_track asm("r1") = track;
    register u32 value asm("r3");

    SAVE_LINK_REGISTER();
    func_80EAEF4(live_player, live_track);
    asm volatile("" : "=r"(live_player), "=r"(live_track), "=r"(value));
    live_track->keyShift = value;
    {
        register u32 flags asm("r3") = live_track->flags;
        register u32 mask asm("r2") = 0xC;

        flags |= mask;
        live_track->flags = flags;
    }
    RETURN_THROUGH_LINK_REGISTER();
}

__attribute__((naked)) void sub_080EAFB4(
    MusicPlayerInfo *player, MusicPlayerTrack *track)
{
    register MusicPlayerInfo *live_player asm("r0") = player;
    register MusicPlayerTrack *live_track asm("r1") = track;
    register ToneData *source asm("r2");
    register u32 value asm("r3");

    SAVE_LINK_REGISTER();
    {
        register u8 *command asm("r2") = live_track->command;
        register u32 voice asm("r3") = *command;
        register u32 offset asm("r2");
        register ToneData *tone asm("r3");

        command++;
        live_track->command = command;
        offset = voice << 1;
        offset += voice;
        offset <<= 2;
        tone = live_player->tone;
        offset += (u32)tone;
        source = (ToneData *)offset;
    }

    value = source->words[0];
    func_80EAEDA_regs(live_player, live_track, source, value);
    asm volatile("" : "=r"(live_player), "=r"(live_track),
                          "=r"(source), "=r"(value));
    live_track->tone.words[0] = value;

    value = source->words[1];
    func_80EAEDA_regs(live_player, live_track, source, value);
    asm volatile("" : "=r"(live_player), "=r"(live_track),
                          "=r"(source), "=r"(value));
    live_track->tone.words[1] = value;

    value = source->words[2];
    func_80EAEDA_regs(live_player, live_track, source, value);
    asm volatile("" : "=r"(live_player), "=r"(live_track),
                          "=r"(source), "=r"(value));
    live_track->tone.words[2] = value;
    RETURN_THROUGH_LINK_REGISTER();
}

__attribute__((naked)) void sub_080EAFE4(
    MusicPlayerInfo *player, MusicPlayerTrack *track)
{
    register MusicPlayerInfo *live_player asm("r0") = player;
    register MusicPlayerTrack *live_track asm("r1") = track;
    register u32 value asm("r3");

    SAVE_LINK_REGISTER();
    func_80EAEF4(live_player, live_track);
    asm volatile("" : "=r"(live_player), "=r"(live_track), "=r"(value));
    live_track->volume = value;
    {
        register u32 flags asm("r3") = live_track->flags;
        register u32 mask asm("r2") = 3;

        flags |= mask;
        live_track->flags = flags;
    }
    RETURN_THROUGH_LINK_REGISTER();
}

__attribute__((naked)) void sub_080EAFF8(
    MusicPlayerInfo *player, MusicPlayerTrack *track)
{
    register MusicPlayerInfo *live_player asm("r0") = player;
    register MusicPlayerTrack *live_track asm("r1") = track;
    register u32 value asm("r3");

    SAVE_LINK_REGISTER();
    func_80EAEF4(live_player, live_track);
    asm volatile("" : "=r"(live_player), "=r"(live_track), "=r"(value));
    value -= 0x40;
    live_track->pan = value;
    {
        register u32 flags asm("r3") = live_track->flags;
        register u32 mask asm("r2") = 3;

        flags |= mask;
        live_track->flags = flags;
    }
    RETURN_THROUGH_LINK_REGISTER();
}

__attribute__((naked)) void sub_080EB00C(
    MusicPlayerInfo *player, MusicPlayerTrack *track)
{
    register MusicPlayerInfo *live_player asm("r0") = player;
    register MusicPlayerTrack *live_track asm("r1") = track;
    register u32 value asm("r3");

    SAVE_LINK_REGISTER();
    func_80EAEF4(live_player, live_track);
    asm volatile("" : "=r"(live_player), "=r"(live_track), "=r"(value));
    value -= 0x40;
    live_track->bend = value;
    {
        register u32 flags asm("r3") = live_track->flags;
        register u32 mask asm("r2") = 0xC;

        flags |= mask;
        live_track->flags = flags;
    }
    RETURN_THROUGH_LINK_REGISTER();
}

__attribute__((naked)) void sub_080EB020(
    MusicPlayerInfo *player, MusicPlayerTrack *track)
{
    register MusicPlayerInfo *live_player asm("r0") = player;
    register MusicPlayerTrack *live_track asm("r1") = track;
    register u32 value asm("r3");

    SAVE_LINK_REGISTER();
    func_80EAEF4(live_player, live_track);
    asm volatile("" : "=r"(live_player), "=r"(live_track), "=r"(value));
    live_track->bendRange = value;
    {
        register u32 flags asm("r3") = live_track->flags;
        register u32 mask asm("r2") = 0xC;

        flags |= mask;
        live_track->flags = flags;
    }
    RETURN_THROUGH_LINK_REGISTER();
}

__attribute__((naked)) void sub_080EB034(
    MusicPlayerInfo *player, MusicPlayerTrack *track)
{
    register MusicPlayerInfo *live_player asm("r0") = player;
    register MusicPlayerTrack *live_track asm("r1") = track;
    register u32 value asm("r3");

    SAVE_LINK_REGISTER();
    func_80EAEF4(live_player, live_track);
    asm volatile("" : "=r"(live_player), "=r"(live_track), "=r"(value));
    live_track->lfoDelay = value;
    RETURN_THROUGH_LINK_REGISTER();
}

__attribute__((naked)) void sub_080EB040(
    MusicPlayerInfo *player, MusicPlayerTrack *track)
{
    register MusicPlayerInfo *live_player asm("r0") = player;
    register MusicPlayerTrack *live_track asm("r1") = track;
    register u32 value asm("r3");

    SAVE_LINK_REGISTER();
    func_80EAEF4(live_player, live_track);
    asm volatile("" : "=r"(live_player), "=r"(live_track), "=r"(value));
    {
        register u32 current asm("r0") = live_track->modulationType;

        if (current != value) {
            live_track->modulationType = value;
            {
                register u32 flags asm("r3") = live_track->flags;
                register u32 mask asm("r2") = 0xF;

                flags |= mask;
                live_track->flags = flags;
            }
        }
    }
    RETURN_THROUGH_LINK_REGISTER();
}

__attribute__((naked)) void sub_080EB058(
    MusicPlayerInfo *player, MusicPlayerTrack *track)
{
    register MusicPlayerInfo *live_player asm("r0") = player;
    register MusicPlayerTrack *live_track asm("r1") = track;
    register u32 value asm("r3");

    SAVE_LINK_REGISTER();
    func_80EAEF4(live_player, live_track);
    asm volatile("" : "=r"(live_player), "=r"(live_track), "=r"(value));
    value -= 0x40;
    live_track->tune = value;
    {
        register u32 flags asm("r3") = live_track->flags;
        register u32 mask asm("r2") = 0xC;

        flags |= mask;
        live_track->flags = flags;
    }
    RETURN_THROUGH_LINK_REGISTER();
}

__attribute__((naked)) void sub_080EB06C(
    MusicPlayerInfo *player, MusicPlayerTrack *track)
{
    register MusicPlayerTrack *live_track asm("r1") = track;
    register u8 *command asm("r2");
    register u32 portOffset asm("r3");
    register volatile u8 *port asm("r0");

    SAVE_LINK_REGISTER();
    command = live_track->command;
    portOffset = *command;
    command++;
    port = (volatile u8 *)0x04000060;
    asm volatile("" : "+r"(port));
    port += portOffset;
    func_80EAEF6_regs(port, live_track, command, portOffset);
    asm volatile("" : "=r"(port), "=r"(live_track),
                          "=r"(command), "=r"(portOffset));
    *port = portOffset;
    RETURN_THROUGH_LINK_REGISTER();
}
