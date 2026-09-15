#include "m2c_prelude.h"

void func_08092E74(u8);
void func_08092E84(s32);
void func_08092EA0(u8);
s32 func_08094484(s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_08094554();
void func_080972C8(void);
void func_080981F0(s32, s32, s32, s32, s32);
void func_08098284(u8, s32, s32, s32);
void func_0809844C(s32, s32, s32, s32, s32, s32, s32);
M2C_UNK func_0809844C_4(s32, s32, s32, s32) asm("func_0809844C");
asm(
    ".macro A4D8C_REWARD_STACK three, five, eight\n"
    "str \\five, [sp]\n"
    "str \\eight, [sp, #4]\n"
    "movs \\three, #3\n"
    "str \\three, [sp, #8]\n"
    ".endm\n");
asm(
    ".macro A4D8C_ADD_AND_FIX_REWARD_LOAD dst, base\n"
    "add \\dst, \\base\n"
    ".macro mov args:vararg\n"
    ".short 0x2200\n"
    ".purgem mov\n"
    ".endm\n"
    ".macro ldrsh args:vararg\n"
    ".short 0x5E80\n"
    ".purgem ldrsh\n"
    ".endm\n"
    ".endm\n");
asm(
    ".macro A4D8C_SHIFT_AND_FIX_THIRD_UPDATE dst\n"
    "lsl \\dst, \\dst, #1\n"
    ".macro ldr out, addr\n"
    ".purgem ldr\n"
    "ldr r1, \\addr\n"
    ".endm\n"
    ".macro add out, lhs, rhs\n"
    ".purgem add\n"
    "add r0, r0, r1\n"
    ".endm\n"
    ".endm\n");
asm(
    ".macro A4D8C_INIT_AND_FIX_ITEM_LOOP index\n"
    "mov \\index, #0\n"
    ".set a4d8c_item_ldr_count, 0\n"
    ".macro ldr args:vararg\n"
    ".if a4d8c_item_ldr_count == 0\n"
    ".short 0x483C\n"
    ".elseif a4d8c_item_ldr_count == 1\n"
    ".short 0x483A\n"
    ".macro mov args:vararg\n"
    ".short 0x4680\n"
    ".purgem mov\n"
    ".endm\n"
    ".elseif a4d8c_item_ldr_count == 2\n"
    ".short 0x4C35\n"
    ".else\n"
    ".short 0x482E\n"
    ".purgem ldr\n"
    ".macro add args:vararg\n"
    ".short 0x1828\n"
    ".purgem add\n"
    ".endm\n"
    ".endif\n"
    ".set a4d8c_item_ldr_count, a4d8c_item_ldr_count + 1\n"
    ".endm\n"
    ".endm\n");
void func_080986B4(s32);
u8 func_08098B58(s32);
void func_08098BB4(s32);
void func_0809A9C8(u16, s32, u8, s32, s32, s32);
void func_080A016C(s32, s32, s32);
s32 func_080E79F4(void);
s32 func_080ECF78(s32, s32);
void func_080ED038(void *, s32, s32);
void func_080ED128(void *, s32);
void func_080ED17C(s32);

s32 sub_080A4D8C(u8 arg0)
{
    s32 saved_arg;
    u8 *state;

    saved_arg = arg0;
    *(u8 *)0x02030664 = 1;
    state = (u8 *)0x020280EC;
    asm volatile("" : "+r"(state));
    if (state[0] != 0 && ({
            register u32 state_limit asm("r1") = state[40];
            state_limit;
        }) <= 0x62) {
        register u32 four asm("r9");
        register u32 five asm("r5");
        register u32 eight asm("r6");
        register s16 *stat_base asm("r4");
        register s16 *stat_fourth asm("sl");
        register s16 *stat_fifth asm("r8");
        u8 menu_state;
        u32 flag_value;
        u16 kind;
        u8 kind_arg;
        u32 selected;
        u32 offset;
        register u16 *text asm("r6");
        register u32 text_index asm("r5");

        func_08092EA0(*(u8 *)0x02030667);
        func_08092E84(0x34);
        if (*(s32 *)0x02031744 != 0) {
            func_08094554();
            *(s32 *)0x02031744 = 0;
        }
        if (*(s32 *)0x02021690 != 10 || *(u8 *)0x02031748 != 0) {
            menu_state = *(u8 *)0x02030666;
            if (menu_state == 0) {
                goto open_menu;
            }
            if (menu_state == 1) {
                func_08098BB4(0x080177F5);
open_menu:
                func_08098BB4(0x080177ED);
                *(u8 *)0x02030666 = 2;
            }
        }

        flag_value = *(u8 *)0x020324B0;
        {
            register u32 four_seed asm("r0") = 4;
            four = four_seed;
            four_seed &= flag_value;
            if (four_seed != 0) {
                *(u8 *)0x020314A4 = 0xF;
            }
        }
        {
            register u16 *kind_table asm("r1") = (u16 *)0x087AF5F8;
            asm volatile("" : "+r"(kind_table));
            kind = kind_table[state[0]];
        }
        kind_arg = 0;
        if (kind == 0x4B) {
            kind_arg = state[1];
        }
        func_0809A9C8(kind, 0, kind_arg, 0x3C2, 0xE, 0x02002880);

        *(s32 *)0x02031744 = func_08094484(0x08359850, 0x0835985C,
            0, 0x18, 0x18, 0x3C2, 0xE,
            ({ eight = 8; eight; }), 0);
        func_08098BB4(0x08017A3F);

        func_0809844C(M2C_FIELD(state, s16 *, 0x2A), 3, 0, 0xA,
            ({ five = 5; five; }), four, 0);
        func_0809844C(M2C_FIELD(state, s16 *, 0x2C), 3, 0, 0xA, five, four, 1);
        func_0809844C(M2C_FIELD(state, s16 *, 0x2E), 3, 0, 0xA, five, four, 2);
        func_0809844C(M2C_FIELD(state, s16 *, 0x30), 3, 0, 0xA, five, four, 3);
        func_0809844C(M2C_FIELD(state, s16 *, 0x32), 3, 0, 0xA, five, four, four);

        stat_base = (s16 *)0x087B7988;
        func_0809844C(M2C_FIELD((state[1] * 0xA), s16 *, (u32)stat_base),
            3, 0, 0xA, five, eight, 0);
        func_0809844C(M2C_FIELD((state[1] * 0xA), s16 *, 0x087B798A),
            3, 0, 0xA, five, eight, 1);
        func_0809844C(M2C_FIELD((state[1] * 0xA), s16 *, 0x087B798C),
            3, 0, 0xA, five, eight, 2);
        {
            register s32 fourth_value asm("r0");
            register s32 three asm("r1");

            fourth_value = ({
                register u32 fourth_addr asm("r0");
                {
                    register u32 fourth_index asm("r1") = state[1];
                    fourth_addr = fourth_index << 2;
                    fourth_addr += fourth_index;
                    fourth_addr <<= 1;
                }
                {
                    register u32 fourth_base asm("r1") = (u32)stat_base + 6;
                    stat_fourth = (s16 *)fourth_base;
                }
                asm volatile("A4D8C_ADD_AND_FIX_REWARD_LOAD %0, %1"
                             : "+r"(fourth_addr)
                             : "r"(stat_fourth)
                             : "cc");
                *(s16 *)fourth_addr;
            });
            asm volatile("A4D8C_REWARD_STACK %0, %1, %2"
                         : "=r"(three) : "r"(five), "r"(eight) : "memory");
            func_0809844C_4(fourth_value, three, 0, 0xA);
        }
        func_0809844C(({
            register u32 fifth_addr asm("r0");
            {
                register u32 fifth_index asm("r1") = state[1];
                fifth_addr = fifth_index << 2;
                fifth_addr += fifth_index;
                fifth_addr <<= 1;
            }
            {
                register u32 fifth_base asm("r2") = 8;
                fifth_base += (u32)stat_base;
                stat_fifth = (s16 *)fifth_base;
            }
            fifth_addr += (u32)stat_fifth;
            *(s16 *)fifth_addr;
        }),
            3, 0, 0xA, five, eight, four);

        {
            u8 *reward_count = (u8 *)0x02028114;
            asm volatile("" : "+r"(reward_count));
            *reward_count += 1;
        }
        {
            register u32 update_index asm("r1") = state[1];
            register u32 update_offset asm("r0");
            register u32 update_current asm("r2");

            update_offset = update_index << 2;
            update_offset += update_index;
            update_offset <<= 1;
            update_offset += (u32)stat_base;
            update_offset = *(u16 *)update_offset;
            update_current = M2C_FIELD(state, u16 *, 0x2A);
            update_offset += update_current;
            M2C_FIELD(state, u16 *, 0x2A) = (u16)update_offset;

            update_offset = update_index << 2;
            update_offset += update_index;
            update_offset <<= 1;
            update_index = 0x087B798A;
            update_offset += update_index;
            update_offset = *(u16 *)update_offset;
            update_current = M2C_FIELD(state, u16 *, 0x2C);
            update_offset += update_current;
            M2C_FIELD(state, u16 *, 0x2C) = (u16)update_offset;
        }
        {
            register u32 update_index asm("r1") = state[1];
            register u32 update_offset asm("r0");
            register u32 update_current asm("r2");

            update_offset = update_index << 2;
            update_offset += update_index;
            asm volatile("A4D8C_SHIFT_AND_FIX_THIRD_UPDATE %0"
                         : "+r"(update_offset));
            update_index = 0x087B798C;
            update_offset += update_index;
            update_offset = *(u16 *)update_offset;
            update_current = M2C_FIELD(state, u16 *, 0x2E);
            update_offset += update_current;
            M2C_FIELD(state, u16 *, 0x2E) = (u16)update_offset;

            update_index = *(volatile u8 *)(state + 1);
            update_offset = update_index << 2;
            asm volatile("add %0, %0, %1"
                         : "+r"(update_offset)
                         : "r"(update_index));
            update_offset <<= 1;
            update_offset += (u32)stat_fourth;
            update_offset = *(u16 *)update_offset;
            update_index = M2C_FIELD(state, u16 *, 0x30);
            update_offset += update_index;
            M2C_FIELD(state, u16 *, 0x30) = (u16)update_offset;
        }
        {
            register u32 update_index asm("r1") = state[1];
            register u32 update_offset asm("r0");
            register u32 update_current asm("r2");

            update_offset = update_index << 2;
            update_offset += update_index;
            update_offset <<= 1;
            update_offset += (u32)stat_fifth;
            update_offset = *(u16 *)update_offset;
            update_current = M2C_FIELD(state, u16 *, 0x32);
            update_offset += update_current;
            M2C_FIELD(state, u16 *, 0x32) = (u16)update_offset;
        }

        func_0809844C(M2C_FIELD(state, s16 *, 0x2A), 3, 0, 0xA, five, 0xC, 0);
        func_0809844C(M2C_FIELD(state, s16 *, 0x2C), 3, 0, 0xA, five, 0xC, 1);
        func_0809844C(M2C_FIELD(state, s16 *, 0x2E), 3, 0, 0xA, five, 0xC, 2);
        func_0809844C(M2C_FIELD(state, s16 *, 0x30), 3, 0, 0xA, five, 0xC, 3);
        func_0809844C(M2C_FIELD(state, s16 *, 0x32), 3, 0, 0xA, five, 0xC, four);

        text = (u16 *)0x02031756;
        {
            register u32 text_header asm("r0") = 0x201;
            text[0] = text_header;
        }
        func_080ED038(text + 1, 0x08103D98, 0x1D);
        text[15] = 1;
        func_080ED038(text + 16, 0x08103DB8, 0x11);
        func_080ED038(text + 24, 0x08103DCC, 7);
        func_08098284(({
                register u8 *reward_count_ptr asm("r1") = (u8 *)0x02028114;
                *reward_count_ptr;
            }), 2, 0, 0x02030564);
        {
            register u32 text_footer asm("r0") = 0x101;
            text[27] = text_footer;
        }
        func_080ED128(text + 28, 0x02030564);
        text_index = func_08098B58(0x02030564);
        {
            register u32 mark_addr asm("r0") = text_index;
            mark_addr += 28;
            mark_addr <<= 1;
            mark_addr += (u32)text;
            *(u16 *)mark_addr = ({
                register u32 mark_value asm("r2") = 1;
                mark_value;
            });
        }
        {
            register u32 suffix_addr asm("r0") = text_index << 1;
            register u32 suffix_base asm("r1") = (u32)text;
            suffix_base += 58;
            suffix_addr += suffix_base;
            func_080ED038((void *)suffix_addr, 0x08103DD4, 3);
        }
        *(u16 **)0x0200A888 = text;
        func_08098BB4(0x080177D5);

        if ((func_080E79F4() << 24) != 0) {
            register u32 i asm("r5");

            func_08098BB4(0x08017AB7);
            asm volatile("A4D8C_INIT_AND_FIX_ITEM_LOOP %0" : "=r"(i));
            if (i < *(u8 *)0x02032E35) {
                register s32 *message_table asm("r8") = (s32 *)0x087EF410;
                do {
                    u32 next;
                    s32 message;

                    next = i + 1;
                    if (i != 0 && func_080ECF78(i, 3) == 0) {
                        func_080972C8();
                        do {
                            func_080ED17C(1);
                        } while (!(3 & *(volatile u16 *)0x0300000E));
                        func_08092E84(0x41);
                        func_080986B4(5);
                    }
                    message = message_table[*(u8 *)(0x02032E36 + i)];
                    func_080981F0(message, 0, 5, 0,
                        (s32)(s16)(func_080ECF78(i, 3) * 2));
                    i = next;
                } while (i < *(u8 *)0x02032E35);
            }
            func_080972C8();
            do {
                func_080ED17C(1);
            } while (!(3 & *(volatile u16 *)0x0300000E));
            func_08092E84(0x41);
        }

        func_08094554(*(s32 *)0x02031744);
        *(s32 *)0x02031744 = 0;
        *(u8 *)0x020314A4 = 0x5F;
        func_08098BB4(0x08017AC4);
        func_08092EA0(0x34);
        func_08092E74(*(u8 *)0x02030667);
    }
    func_080A016C(saved_arg, -1, 0);
    return 0;
}
