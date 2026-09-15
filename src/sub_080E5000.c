#include "m2c_prelude.h"

void func_08096FBC(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
u8 func_0809669C(void);
void func_08097980(s32);
void func_08097B2C(s32, s32, u16 *);
void func_080ECD28(const void *, void *, s32);
void func_080ED17C(s32);
void func_08096308(s32, s32);

void sub_080E5000(void)
{
    u16 decoded[2];
    u32 fill_word;
    s32 end_offset;
    s32 palette;
    s32 *scroll;
    u8 *stream;

    *(u16 *)0x0300004C = 0x1140;
    func_08096FBC(0, 1, 0, 0x3C0, 0x3C0, 0, 14, 0, 0x3E6, 15);
    func_080ECD28((void *)0x087A57F0, (void *)0x050001C0, 8);
    fill_word = 0xE3C1E3C1;
    func_080ECD28(&fill_word, (void *)0x06000000, 0x01000200);
    func_08096308(1, 60);

    while (func_0809669C() == 0) {
        func_080ED17C(1);
    }

    {
        s32 *scroll_init = (s32 *)0x03000054;

        scroll_init[1] = 0;
        scroll_init[0] = 0;
        end_offset = -1;
        stream = (u8 *)0x08029043;
        palette = 0;
        scroll = scroll_init;
    }

    do {
        s32 adjusted;
        u16 *tiles;
        u8 i;
        s32 command;
        s32 command_check;
        u8 *commandp;

        adjusted = scroll[1] - 0x1000;
        if (adjusted < 0) {
            adjusted += 0x7FF;
        }
        tiles = (u16 *)0x06000000 + (((adjusted >> 11) & 0x1F) << 5);

        i = 0;
        do {
            register u16 value asm("r1") = tiles[0];
            if (value != 0xE3C1) {
                func_08097980(value & 0x3FF);
                func_08097980(tiles[32] & 0x3FF);
                tiles[0] = 0xE3C1;
                tiles[32] = 0xE3C1;
            }
            tiles++;
            i++;
        } while (i <= 31);

        {
            register s32 loaded_r0 asm("r0");
            commandp = stream;
            loaded_r0 = *commandp;
            command_check = loaded_r0;
            command = loaded_r0;
        }
        if (command_check != 0) {
            s32 scroll_value = scroll[1];
            if ((scroll_value & 0xFFF) == 0) {
                adjusted = scroll_value + 0xA000;
                if (adjusted < 0) {
                    adjusted += 0x7FF;
                }
                tiles = (u16 *)0x06000000 +
                        (((adjusted >> 11) & 0x1F) << 5);

                if (command_check != 10) {
                    u16 *decodedp = decoded;

decode_command:
                    {
                        if (command == 1) {
                            palette = stream[1];
                            stream += 2;
                        }

                        func_08097B2C((stream[0] << 8) | stream[1],
                                      palette, decoded);
                        tiles[0] = decodedp[0];
                        tiles[32] = decodedp[1];
                        stream += 2;
                        tiles++;
                        {
                            register s32 loaded_r0 asm("r0") = *stream;
                            s32 next_check;
                            next_check = loaded_r0;
                            if (next_check == 0)
                                goto command_zero;
                            command = loaded_r0;
                            if (next_check != 10)
                                goto decode_command;
                        }
                    }
                }

                {
                    register s32 final_command asm("r0") = command;
                    if (final_command == 0) {
command_zero:
                        end_offset = scroll[1] + 0xB000;
                    } else if (final_command == 10) {
                        stream++;
                    }
                }

                i = 0;
                do {
                    u32 *current = (u32 *)0x0200DD90 + i;
                    u32 *pending = (u32 *)0x0200DE10 + i;
                    *current ^= *pending;
                    *pending = 0;
                    i++;
                } while (i <= 31);
            }
        }

        asm volatile("" : "+r"(stream));
        asm volatile("" : "+r"(stream));
        scroll[1] += 0x80;
        func_080ED17C(1);
    } while (scroll[1] != end_offset);

    func_08096308(2, 8);
    while (func_0809669C() == 0) {
        func_080ED17C(1);
    }

    *(u8 *)0x02021694 = 1;
    asm volatile("" ::: "r1");
    *(s32 *)0x02021690 = 0;
}
