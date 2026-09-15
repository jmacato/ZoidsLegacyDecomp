#include "m2c_prelude.h"

void func_080EB328(void *, u8 *);
void func_080EBC40(u8);

void sub_080EBE40(u8 *arg0, u8 *arg1)
{
    register u8 *player asm("r5") = arg0;
    u8 *song = arg1;
    register u32 priority asm("r2");
    register s32 i asm("r6");
    register u8 *track asm("r4");
    register u32 zero asm("r8");

    if (*(u32 *)(player + 0x34) != 0x68736D53) {
        return;
    }
    asm volatile("" : "+r"(song));
    {
        register u32 mode asm("r0") = player[0xB];

        asm volatile("" : "+r"(mode));
        priority = song[2];
        asm volatile("" : "+r"(priority));
        if (mode == 0) {
            goto initialize;
        }
    }
    if (*(void **)player == 0) {
        goto status_check;
    }
    {
        register u8 *tracks asm("r1") = *(u8 **)(player + 0x2C);
        register u32 mask asm("r0") = 0x40;
        register u32 flags asm("r1") = *tracks;

        mask &= flags;
        if (mask != 0) {
            goto priority_check;
        }
    }

status_check:
    {
        register s32 status asm("r1") = *(s32 *)(player + 4);
        register u32 low asm("r0") = *(u16 *)(player + 4);

        if (low == 0) {
            goto initialize;
        }
        if (status < 0) {
            goto initialize;
        }
    }

priority_check:
    {
        register u32 loaded asm("r0") = song[2];
        asm volatile("" : "+r"(loaded));
        priority = loaded;
    }
    if (player[9] > priority) {
        return;
    }

initialize:
    (*(u32 *)(player + 0x34))++;
    {
        register u32 clear asm("r1") = 0;
        register u32 value asm("r0");

        *(u32 *)(player + 4) = clear;
        *(u8 **)player = song;
        value = *(u32 *)(song + 4);
        *(u32 *)(player + 0x30) = value;
        player[9] = priority;
        *(u32 *)(player + 0x0C) = clear;
        value = 0x96;
        *(u16 *)(player + 0x1C) = value;
        *(u16 *)(player + 0x20) = value;
        value += 0x6A;
        *(u16 *)(player + 0x1E) = value;
        *(u16 *)(player + 0x22) = clear;
        *(u16 *)(player + 0x24) = clear;
    }

    i = 0;
    track = *(u8 **)(player + 0x2C);
    {
        register s32 bound asm("r1") = song[0];
        asm volatile("" : "+r"(bound));
        if (i >= bound) {
            goto second_check;
        }
    }
    if (i >= player[8]) {
        goto loops_done;
    }
    zero = i;

first_loop:
    func_080EB328(player, track);
    track[0] = 0xC0;
    {
        register u32 value asm("r1") = zero;
        asm volatile("" : "+r"(value));
        *(u32 *)(track + 0x20) = value;
    }
    {
        register u32 offset asm("r1") = i << 2;
        register u8 *source asm("r0") = song;

        source += 8;
        asm volatile("" : "+r"(source));
        source += offset;
        *(u32 *)(track + 0x40) = *(u32 *)source;
    }
    i++;
    track += 0x50;
    if (i >= song[0]) {
        goto second_check;
    }
    {
        register s32 bound asm("r1") = player[8];
        asm volatile("" : "+r"(bound));
        if (i < bound) {
            goto first_loop;
        }
    }

second_check:
    if (i >= player[8]) {
        goto loops_done;
    }
    {
        register u32 clear asm("r1") = 0;
        asm volatile("" : "+r"(clear));
        zero = clear;
    }

second_loop:
    func_080EB328(player, track);
    track[0] = zero;
    i++;
    track += 0x50;
    {
        register s32 bound asm("r1") = player[8];
        asm volatile("" : "+r"(bound));
        if (i < bound) {
            goto second_loop;
        }
    }

loops_done:
    {
        register u32 mask asm("r0") = 0x80;
        register u32 flags asm("r1") = song[3];

        mask &= flags;
        if (mask != 0) {
            func_080EBC40(*(volatile u8 *)(song + 3));
        }
    }
    *(u32 *)(player + 0x34) = 0x68736D53;
}
