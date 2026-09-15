#include "m2c_prelude.h"

extern void func_08092E74();
extern void func_08092E84();
extern void func_08092EA0();
extern void func_08094554();
extern void func_08098BB4();
extern void func_080A016C();

u32 sub_080A3A40(u8 arg0, u8 **arg1)
{
    u8 saved_arg0;
    u32 code;
    u32 handle;

    saved_arg0 = arg0;
    func_08092EA0(*(u8 *)0x02030667);
    func_08092E84(53);
    *(u8 *)0x02030664 = 1;
    if (*(u32 *)0x02031744 != 0) {
        func_08094554();
        *(u32 *)0x02031744 = 0;
    }
    if ((*(u32 *)0x02021690 != 10) || (*(u8 *)0x02031748 != 0)) {
        code = *(u8 *)0x02030666;
        if (code != 0) {
            if (code == 1) {
                func_08098BB4(0x080177F5);
                goto play_common_sound;
            }
        } else {
play_common_sound:
            func_08098BB4(0x080177ED);
            *(u8 *)0x02030666 = 2;
        }
    }
    code = **arg1 - 102;
    switch (code) {
    case 0:
    {
        u32 *table;
        u16 *window;
        u16 *slot;
        u32 handle;
        register u32 index asm("r0");
        register u32 address asm("r1");

        window = (u16 *)0x02031756;
        asm volatile("" : "+r"(window));
        func_080ED038(window, (void *)0x08103AF4, 23);
        asm volatile(
            ".set c0_add_fix, 0\n\t"
            ".macro add dst, args:vararg\n\t"
            ".if c0_add_fix == 0\n\t.short 0x1C34\n\t"
            ".elseif c0_add_fix == 1\n\t.short 0x3416\n\t"
            ".elseif c0_add_fix == 2\n\t.short 0x4440\n\t"
            ".elseif c0_add_fix == 3\n\t.short 0x1C20\n\t"
            ".elseif c0_add_fix == 4\n\t"
            ".elseif c0_add_fix == 5\n\t.short 0x192C\n\t"
            ".elseif c0_add_fix == 6\n\t.short 0x1C20\n\t"
            ".elseif c0_add_fix == 7\n\t.short 0x1C38\n\t"
            ".elseif c0_add_fix == 8\n\t.short 0x300C\n\t"
            ".elseif c0_add_fix == 9\n\t.short 0x1980\n\t"
            ".elseif c0_add_fix == 10\n\t.short 0x1C30\n\t"
            ".elseif c0_add_fix == 11\n\t.short 0x301A\n\t.short 0x182D\n\t"
            ".elseif c0_add_fix == 12\n\t.short 0x4440\n\t"
            ".elseif c0_add_fix == 13\n\t.short 0x1C28\n\t"
            ".elseif c0_add_fix == 14\n\t.short 0x4440\n\t"
            ".elseif c0_add_fix == 15\n\t.short 0x183F\n\t"
            ".elseif c0_add_fix == 16\n\t.short 0x1C38\n\t"
            ".elseif c0_add_fix == 17\n\t.short 0x300D\n\t"
            ".elseif c0_add_fix == 18\n\t.short 0x1980\n\t"
            ".elseif c0_add_fix == 19\n\t.short 0x1C31\n\t"
            ".elseif c0_add_fix == 20\n\t.short 0x311C\n\t"
            ".else\n\t.short 0x1840\n\t"
            ".endif\n\t"
            ".set c0_add_fix, c0_add_fix + 1\n\t"
            ".endm\n\t"
            ".set c0_lsl_fix, 0\n\t"
            ".macro lsl dst, lhs, rhs\n\t"
            ".if c0_lsl_fix == 0\n\t.short 0x0080\n\t"
            ".elseif c0_lsl_fix == 1\n\t.short 0x0600\n\t"
            ".elseif c0_lsl_fix == 2\n\t.short 0x007D\n\t"
            ".elseif c0_lsl_fix == 3\n\t.short 0x0040\n\t"
            ".elseif c0_lsl_fix == 4\n\t.short 0x0080\n\t"
            ".elseif c0_lsl_fix == 5\n\t.short 0x0080\n\t"
            ".elseif c0_lsl_fix == 6\n\t.short 0x0600\n\t"
            ".elseif c0_lsl_fix == 7\n\t.short 0x0040\n\t"
            ".else\n\t.short 0x0078\n\t"
            ".endif\n\t"
            ".set c0_lsl_fix, c0_lsl_fix + 1\n\t"
            ".endm\n\t"
            ".set c0_lsr_fix, 0\n\t"
            ".macro lsr dst, lhs, rhs\n\t"
            ".if c0_lsr_fix == 0\n\t.short 0x0E07\n\t"
            ".else\n\t.short 0x0E00\n\t"
            ".endif\n\t"
            ".set c0_lsr_fix, c0_lsr_fix + 1\n\t"
            ".endm");
        slot = window + 11;
        table = (u32 *)0x087EDD54;
        handle = (u8)func_0809F770(slot, table[(*arg1)[1]]);
        slot += handle;
        func_080ED038(slot, (void *)0x08103B0C, 3);
        index = handle + 12;
        index <<= 1;
        index += (u32)window;
        address = 0x201;
        *(u16 *)index = (u16)address;
        slot = window + 13 + handle;
        func_080ED128(slot, table[(*arg1)[1]]);
        handle += (u8)func_08098B58(table[(*arg1)[1]]);
        index = handle + 13;
        index <<= 1;
        index += (u32)window;
        *(u16 *)index = 1;
        index = handle << 1;
        address = (u32)window;
        address += 28;
        index += address;
        func_080ED038((u16 *)index, (void *)0x08103B10, 14);
        asm volatile(".purgem add\n\t.purgem lsl\n\t.purgem lsr");
        *(u16 **)0x0200A888 = window;
        func_08098BB4(0x080177D5);
        func_080E5A18((*arg1)[1], (*arg1)[2]);
        break;
    }
    case 1:
    {
        u32 *table;
        u32 accumulated;
        u16 *window;
        u16 *slot;
        register u16 *record asm("r1");
        u8 handle;
        register u32 selected asm("r4");
        register u32 record_base asm("r0");
        register u32 index asm("r0");
        register u32 address asm("r1");

        window = (u16 *)0x02031756;
        asm volatile("" : "+r"(window));
        func_080ED038(window, (void *)0x08103AF4, 23);
        asm volatile(
            ".set c1_add_fix, 0\n\t"
            ".macro add dst, args:vararg\n\t"
            ".if c1_add_fix == 0\n\t.short 0x1C34\n\t"
            ".elseif c1_add_fix == 1\n\t.short 0x3416\n\t"
            ".elseif c1_add_fix == 2\n\t.short 0x4440\n\t"
            ".elseif c1_add_fix == 3\n\t.short 0x1C20\n\t"
            ".elseif c1_add_fix == 4\n\t"
            ".elseif c1_add_fix == 5\n\t.short 0x192C\n\t"
            ".elseif c1_add_fix == 6\n\t.short 0x1C20\n\t"
            ".elseif c1_add_fix == 7\n\t.short 0x1C38\n\t"
            ".elseif c1_add_fix == 8\n\t.short 0x300C\n\t"
            ".elseif c1_add_fix == 9\n\t.short 0x1980\n\t"
            ".elseif c1_add_fix == 10\n\t.short 0x1C30\n\t"
            ".elseif c1_add_fix == 11\n\t.short 0x301A\n\t.short 0x182D\n\t"
            ".elseif c1_add_fix == 12\n\t.short 0x4440\n\t"
            ".elseif c1_add_fix == 13\n\t.short 0x1C28\n\t"
            ".elseif c1_add_fix == 14\n\t.short 0x4440\n\t"
            ".elseif c1_add_fix == 15\n\t.short 0x183F\n\t"
            ".elseif c1_add_fix == 16\n\t.short 0x1C38\n\t"
            ".elseif c1_add_fix == 17\n\t.short 0x300D\n\t"
            ".elseif c1_add_fix == 18\n\t.short 0x1980\n\t"
            ".elseif c1_add_fix == 19\n\t.short 0x1C31\n\t"
            ".elseif c1_add_fix == 20\n\t.short 0x311C\n\t"
            ".else\n\t.short 0x1840\n\t"
            ".endif\n\t"
            ".set c1_add_fix, c1_add_fix + 1\n\t"
            ".endm\n\t"
            ".set c1_lsl_fix, 0\n\t"
            ".macro lsl dst, lhs, rhs\n\t"
            ".if c1_lsl_fix == 0\n\t.short 0x0080\n\t"
            ".elseif c1_lsl_fix == 1\n\t.short 0x0600\n\t"
            ".elseif c1_lsl_fix == 2\n\t.short 0x007D\n\t"
            ".elseif c1_lsl_fix == 3\n\t.short 0x0040\n\t"
            ".elseif c1_lsl_fix == 4\n\t.short 0x0080\n\t"
            ".elseif c1_lsl_fix == 5\n\t.short 0x0080\n\t"
            ".elseif c1_lsl_fix == 6\n\t.short 0x0600\n\t"
            ".elseif c1_lsl_fix == 7\n\t.short 0x0040\n\t"
            ".else\n\t.short 0x0078\n\t"
            ".endif\n\t"
            ".set c1_lsl_fix, c1_lsl_fix + 1\n\t"
            ".endm\n\t"
            ".set c1_lsr_fix, 0\n\t"
            ".macro lsr dst, lhs, rhs\n\t"
            ".if c1_lsr_fix == 0\n\t.short 0x0E07\n\t"
            ".else\n\t.short 0x0E00\n\t"
            ".endif\n\t"
            ".set c1_lsr_fix, c1_lsr_fix + 1\n\t"
            ".endm");
        slot = window + 11;
        table = (u32 *)0x087EDD54;
        handle = func_0809F770(slot, table[(*arg1)[1]]);
        slot += handle;
        func_080ED038(slot, (void *)0x08103B0C, 3);
        index = handle + 12;
        index <<= 1;
        index += (u32)window;
        address = 0x201;
        *(u16 *)index = (u16)address;
        slot = window + 13 + handle;
        func_080ED128(slot, table[(*arg1)[1]]);
        accumulated = handle + (u8)func_08098B58(table[(*arg1)[1]]);
        index = accumulated + 13;
        index <<= 1;
        index += (u32)window;
        *(u16 *)index = 1;
        index = accumulated << 1;
        address = (u32)window;
        address += 28;
        index += address;
        func_080ED038((u16 *)index, (void *)0x08103B10, 14);
        asm volatile(".purgem add\n\t.purgem lsl\n\t.purgem lsr");
        *(u16 **)0x0200A888 = window;
        func_08098BB4(0x080177D5);
        selected = (u8)func_080E5A18((*arg1)[1], (*arg1)[2]);
        record_base = 0x020218E4;
        asm volatile("" : "+r"(record_base));
        record = (u16 *)((selected * 0x70) + record_base);
        {
            register u32 flags asm("r2") = record[4];
            register u32 mask asm("r0") = 0x10;

            mask |= flags;
            record[4] = (u16)mask;
        }
        break;
    }
    case 2:
    {
        u32 *table;
        u32 accumulated;
        u16 *window;
        u16 *slot;
        u8 handle;
        register u32 index asm("r0");
        register u32 address asm("r1");

        window = (u16 *)0x02031756;
        asm volatile("" : "+r"(window));
        window[0] = 0x201;
        asm volatile("" ::: "memory");
        asm volatile(
            ".set c2a_add_fix, 0\n\t"
            ".macro add dst, args:vararg\n\t"
            ".if c2a_add_fix == 0\n\t.short 0x1CB4\n\t"
            ".elseif c2a_add_fix == 1\n\t.short 0x1C01\n\t"
            ".elseif c2a_add_fix == 2\n\t.short 0x1C20\n\t"
            ".elseif c2a_add_fix == 3\n\t"
            ".elseif c2a_add_fix == 4\n\t.short 0x1C78\n\t"
            ".elseif c2a_add_fix == 5\n\t.short 0x1980\n\t"
            ".elseif c2a_add_fix == 6\n\t.short 0x1D31\n\t"
            ".elseif c2a_add_fix == 7\n\t.short 0x1840\n\t"
            ".else\n\t.short 0x1C30\n\t"
            ".endif\n\t"
            ".set c2a_add_fix, c2a_add_fix + 1\n\t"
            ".endm\n\t"
            ".set c2a_mov_fix, 0\n\t"
            ".macro mov dst, args:vararg\n\t"
            ".if c2a_mov_fix == 0\n\t.short 0x4651\n\t"
            ".elseif c2a_mov_fix == 1\n\t.short 0x4652\n\t"
            ".elseif c2a_mov_fix == 2\n\t.short 0x2101\n\t"
            ".elseif c2a_mov_fix == 3\n\t"
            ".elseif c2a_mov_fix == 4\n\t.short 0x2227\n\t"
            ".elseif c2a_mov_fix == 5\n\t.short 0x2035\n\t"
            ".else\n\t.short 0x2217\n\t"
            ".endif\n\t"
            ".set c2a_mov_fix, c2a_mov_fix + 1\n\t"
            ".endm\n\t"
            ".set c2a_lsl_fix, 0\n\t"
            ".macro lsl dst, lhs, rhs\n\t"
            ".if c2a_lsl_fix == 0\n\t.short 0x0600\n\t"
            ".elseif c2a_lsl_fix == 1\n\t.short 0x0040\n\t"
            ".else\n\t.short 0x0078\n\t"
            ".endif\n\t"
            ".set c2a_lsl_fix, c2a_lsl_fix + 1\n\t"
            ".endm\n\t"
            ".macro lsr dst, lhs, rhs\n\t"
            ".short 0x0E07\n\t"
            ".purgem lsr\n\t"
            ".endm\n\t"
            ".macro strh src, addr:vararg\n\t"
            ".short 0x8001\n\t"
            ".purgem strh\n\t"
            ".endm");
        slot = window + 1;
        func_080ED128(slot, func_080E7B64((*arg1)[3]));
        handle = func_08098B58(func_080E7B64((*arg1)[3]));
        index = handle + 1;
        index <<= 1;
        index += (u32)window;
        *(u16 *)index = 1;
        index = handle << 1;
        address = (u32)window + 4;
        index += address;
        func_080ED038((u16 *)index, (void *)0x08103B20, 39);
        asm volatile(
            ".macro ldr dst, addr:vararg\n\t"
            ".short 0x4A30\n\t"
            ".purgem ldr\n\t"
            ".endm\n\t"
            ".macro str src, addr:vararg\n\t"
            ".short 0x6016\n\t"
            ".purgem str\n\t"
            ".endm");
        *(u16 **)0x0200A888 = window;
        asm volatile(
            ".macro ldr dst, addr:vararg\n\t"
            ".short 0x4830\n\t.short 0x4681\n\t"
            ".purgem ldr\n\t"
            ".endm");
        func_08098BB4(0x080177D5);
        func_08092E84(53);
        func_080ED038(window, (void *)0x08103AF4, 23);
        asm volatile(".purgem add\n\t.purgem mov\n\t.purgem lsl");
        asm volatile(
            ".set c2b_add_fix, 0\n\t"
            ".macro add dst, args:vararg\n\t"
            ".if c2b_add_fix == 0\n\t.short 0x3414\n\t"
            ".elseif c2b_add_fix == 1\n\t.short 0x4440\n\t"
            ".elseif c2b_add_fix == 2\n\t.short 0x1C20\n\t"
            ".elseif c2b_add_fix == 3\n\t"
            ".elseif c2b_add_fix == 4\n\t.short 0x192C\n\t"
            ".elseif c2b_add_fix == 5\n\t.short 0x1C20\n\t"
            ".elseif c2b_add_fix == 6\n\t.short 0x1C38\n\t"
            ".elseif c2b_add_fix == 7\n\t.short 0x300C\n\t"
            ".elseif c2b_add_fix == 8\n\t.short 0x1980\n\t"
            ".elseif c2b_add_fix == 9\n\t.short 0x1C30\n\t"
            ".elseif c2b_add_fix == 10\n\t.short 0x301A\n\t.short 0x182D\n\t"
            ".elseif c2b_add_fix == 11\n\t.short 0x4440\n\t"
            ".elseif c2b_add_fix == 12\n\t.short 0x1C28\n\t"
            ".elseif c2b_add_fix == 13\n\t.short 0x4440\n\t"
            ".elseif c2b_add_fix == 14\n\t.short 0x183F\n\t"
            ".elseif c2b_add_fix == 15\n\t.short 0x1C38\n\t"
            ".elseif c2b_add_fix == 16\n\t.short 0x300D\n\t"
            ".elseif c2b_add_fix == 17\n\t.short 0x1980\n\t"
            ".elseif c2b_add_fix == 18\n\t.short 0x1C31\n\t"
            ".elseif c2b_add_fix == 19\n\t.short 0x311C\n\t"
            ".else\n\t.short 0x1840\n\t"
            ".endif\n\t"
            ".set c2b_add_fix, c2b_add_fix + 1\n\t"
            ".endm\n\t"
            ".set c2b_lsl_fix, 0\n\t"
            ".macro lsl dst, lhs, rhs\n\t"
            ".if c2b_lsl_fix == 0\n\t.short 0x0080\n\t"
            ".elseif c2b_lsl_fix == 1\n\t.short 0x0600\n\t"
            ".elseif c2b_lsl_fix == 2\n\t.short 0x007D\n\t"
            ".elseif c2b_lsl_fix == 3\n\t.short 0x0040\n\t"
            ".elseif c2b_lsl_fix == 4\n\t.short 0x0080\n\t"
            ".elseif c2b_lsl_fix == 5\n\t.short 0x0080\n\t"
            ".elseif c2b_lsl_fix == 6\n\t.short 0x0600\n\t"
            ".elseif c2b_lsl_fix == 7\n\t.short 0x0040\n\t"
            ".else\n\t.short 0x0078\n\t"
            ".endif\n\t"
            ".set c2b_lsl_fix, c2b_lsl_fix + 1\n\t"
            ".endm\n\t"
            ".set c2b_lsr_fix, 0\n\t"
            ".macro lsr dst, lhs, rhs\n\t"
            ".if c2b_lsr_fix == 0\n\t.short 0x0E07\n\t"
            ".else\n\t.short 0x0E00\n\t"
            ".endif\n\t"
            ".set c2b_lsr_fix, c2b_lsr_fix + 1\n\t"
            ".endm\n\t"
            ".set c2b_mov_fix, 0\n\t"
            ".macro mov dst, args:vararg\n\t"
            ".if c2b_mov_fix == 0\n\t.short 0x4688\n\t"
            ".elseif c2b_mov_fix == 1\n\t.short 0x4652\n\t"
            ".elseif c2b_mov_fix == 2\n\t.short 0x2203\n\t"
            ".elseif c2b_mov_fix == 3\n\t.short 0x4652\n\t"
            ".elseif c2b_mov_fix == 4\n\t.short 0x4651\n\t"
            ".elseif c2b_mov_fix == 5\n\t.short 0x2201\n\t"
            ".else\n\t.short 0x220E\n\t"
            ".endif\n\t"
            ".set c2b_mov_fix, c2b_mov_fix + 1\n\t"
            ".endm");
        slot += 10;
        table = (u32 *)0x087EDD54;
        handle = func_0809F770(slot, table[(*arg1)[1]]);
        slot = (u16 *)(((u8)handle * 2) + (u32)slot);
        func_080ED038(slot, (void *)0x08103B0C, 3);
        index = handle + 12;
        index <<= 1;
        index += (u32)window;
        *(u16 *)index = 0x201;
        func_080ED128(window + 13 + handle, table[(*arg1)[1]]);
        accumulated = handle + (u8)func_08098B58(table[(*arg1)[1]]);
        index = accumulated + 13;
        index <<= 1;
        index += (u32)window;
        *(u16 *)index = 1;
        index = accumulated << 1;
        address = (u32)window;
        asm volatile("" : "+r"(address));
        address += 28;
        index += address;
        func_080ED038((u16 *)index, (void *)0x08103B10, 14);
        asm volatile(".purgem add\n\t.purgem lsl\n\t.purgem lsr\n\t.purgem mov");
        *(u16 **)0x0200A888 = window;
        asm volatile(
            ".macro ldr dst, addr:vararg\n\t"
            ".short 0x4648\n\t"
            ".purgem ldr\n\t"
            ".endm");
        func_08098BB4(0x080177D5);
        func_080E5C8C((*arg1)[1], (*arg1)[2], (*arg1)[3]);
        break;
    }
    case 3:
    {
        register u32 *table asm("r8");
        u16 *window;
        u16 *initial_slot;
        u16 *slot;
        register u16 *record asm("r0");
        u32 handle;
        u32 selected;
        register u32 sound asm("r9");
        register u32 doubled asm("r5");
        u8 second;
        register u32 index asm("r0");
        register u32 address asm("r1");
        register u32 record_base asm("r1");
        register u32 reserve_r5 asm("r5");

        window = (u16 *)0x02031756;
        window[0] = 0x201;
        initial_slot = window + 1;
        func_080ED128(initial_slot, func_080E7B64((*arg1)[3]));
        handle = (u8)func_08098B58(func_080E7B64((*arg1)[3]));
        index = handle + 1;
        index <<= 1;
        index += (u32)window;
        *(u16 *)index = 1;
        index = handle << 1;
        address = (u32)window + 4;
        index += address;
        func_080ED038((u16 *)index, (void *)0x08103B20, 39);
        *(u16 **)0x0200A888 = window;
        sound = 0x080177D5;
        func_08098BB4(sound);
        func_08092E84(53);
        func_080ED038(window, (void *)0x08103AF4, 23);
        slot = window + 11;
        table = (u32 *)0x087EDD54;
        handle = (u8)func_0809F770(slot, table[(*arg1)[1]]);
        doubled = handle << 1;
        slot = (u16 *)(doubled + (u32)slot);
        func_080ED038(slot, (void *)0x08103B0C, 3);
        index = handle + 12;
        index <<= 1;
        index += (u32)window;
        *(u16 *)index = 0x201;
        index = (u32)window;
        index += 26;
        doubled += index;
        func_080ED128((u16 *)doubled, table[(*arg1)[1]]);
        handle += (u8)func_08098B58(table[(*arg1)[1]]);
        index = handle + 13;
        index <<= 1;
        index += (u32)window;
        *(u16 *)index = 1;
        index = handle << 1;
        address = (u32)window;
        address += 28;
        index += address;
        func_080ED038((u16 *)index, (void *)0x08103B10, 14);
        *(u16 **)0x0200A888 = window;
        func_08098BB4(sound);
        selected = (u8)func_080E5A18((*arg1)[1], (*arg1)[2]);
        if (selected != 0xFF) {
            record_base = 0x020218E4;
            asm volatile("" : "+r"(record_base));
            record = (u16 *)((selected * 0x70) + record_base);
            record[4] |= 0x10;
        }
        second = func_080E6C78((*arg1)[3]);
        if ((selected != 0xFF) && (second != 0xFF)) {
            func_080E6FA0(second, selected);
            record_base = 0x020218E4;
            asm volatile("" : "+r"(record_base));
            record = (u16 *)((selected * 0x70) + record_base);
            record[5] = record[31];
            record[6] = record[33];
        }
        break;
    }
    case 4:
    {
        register u16 *window asm("r4");
        register u32 handle asm("r7");
        register u32 index asm("r0");
        register u32 address asm("r1");

        window = (u16 *)0x02031756;
        index = 0x201;
        window[0] = (u16)index;
        asm volatile("" ::: "memory");
        func_080ED128(window + 1, func_080E7B64((*arg1)[1]));
        handle = (u8)func_08098B58(func_080E7B64((*arg1)[1]));
        index = handle + 1;
        index <<= 1;
        index += (u32)window;
        *(u16 *)index = 1;
        index = handle << 1;
        address = (u32)window + 4;
        index += address;
        func_080ED038((u16 *)index, (void *)0x08103B20, 39);
        *(u16 **)0x0200A888 = window;
        func_08098BB4(0x080177D5);
        func_080E6C78((*arg1)[1]);
        asm volatile(
            ".macro bl target\n\t"
            "b \\target\n\t"
            ".purgem bl\n\t"
            ".endm");
        break;
    }
    case 5:
    {
        u16 *window;
        register u32 index asm("r0");
        register u32 address asm("r1");
        register u8 *definition_base asm("r0");
        register u8 *definition asm("r2");

        window = (u16 *)0x02031756;
        asm volatile("" : "+r"(window));
        definition_base = (u8 *)0x201;
        window[0] = (u16)(u32)definition_base;
        func_080ED128(window + 1, func_080E7B64((*arg1)[1]));
        handle = (u8)func_08098B58(func_080E7B64((*arg1)[1]));
        index = handle + 1;
        index <<= 1;
        index += (u32)window;
        *(u16 *)index = 1;
        if (handle > 13) {
            index = handle << 1;
            address = (u32)window + 4;
            index += address;
            func_080ED038((u16 *)index, (void *)0x08103B48, 32);
        } else {
            index = handle << 1;
            address = (u32)window + 4;
            index += address;
            func_080ED038((u16 *)index, (void *)0x08103B68, 31);
        }
        address = 0x0200A888;
        definition_base = (u8 *)0x02031756;
        *(u16 **)address = (u16 *)definition_base;
        func_08098BB4(0x080177D5);
        handle = 1;
        definition_base = (u8 *)0x020218E4;
        asm volatile("" : "+r"(definition_base));
        definition = definition_base + 0x5AD4;
        goto check_case_5;
advance_case_5:
        definition += 0x40;
        handle++;
        if (handle > 0x34) {
            goto done_case_5;
        }
check_case_5:
        if (*definition != (*arg1)[1]) {
            goto advance_case_5;
        }
done_case_5:
        func_080E6E98((u8)handle);
        *(u8 *)0x02030665 = 1;
        break;
    }
    case 6:
    {
        register u32 *table asm("r8");
        u16 *window;
        register u16 *slot asm("r4");
        u32 handle;
        register u32 index asm("r0");
        register u32 address asm("r1");
        register u32 doubled asm("r5");

        asm volatile("" ::: "memory");
        window = (u16 *)0x02031756;
        window[0] = 0x201;
        slot = window + 1;
        func_080ED128(slot, func_080E7B64((*arg1)[3]));
        handle = (u8)func_08098B58(func_080E7B64((*arg1)[3]));
        index = handle + 1;
        index <<= 1;
        index += (u32)window;
        *(u16 *)index = 1;
        index = handle << 1;
        address = (u32)window + 4;
        index += address;
        func_080ED038((u16 *)index, (void *)0x08103B20, 39);
        *(u16 **)0x0200A888 = window;
        func_08098BB4(0x080177D5);
        func_08092E84(53);
        func_080ED038(window, (void *)0x08103AF4, 23);
        slot += 10;
        table = (u32 *)0x087EDD54;
        handle = (u8)func_0809F770(slot, table[(*arg1)[1]]);
        doubled = handle << 1;
        slot = (u16 *)(doubled + (u32)slot);
        func_080ED038(slot, (void *)0x08103B0C, 3);
        index = handle + 12;
        index <<= 1;
        index += (u32)window;
        *(u16 *)index = 0x201;
        index = (u32)window;
        index += 26;
        doubled += index;
        func_080ED128((u16 *)doubled, table[(*arg1)[1]]);
        handle += (u8)func_08098B58(table[(*arg1)[1]]);
        index = handle + 13;
        index <<= 1;
        index += (u32)window;
        *(u16 *)index = 1;
        index = handle << 1;
        address = (u32)window;
        address += 28;
        index += address;
        func_080ED038((u16 *)index, (void *)0x08103B10, 14);
        *(u16 **)0x0200A888 = window;
        func_08098BB4(0x080177D5);
        func_080E6EEC((*arg1)[1], (*arg1)[2], (*arg1)[3]);
        break;
    }
    case 7:
    {
        register u16 *window asm("r4");
        register u8 *slots asm("r1");
        register u32 handle asm("r7");
        register u32 result asm("r4");
        u32 index;
        register u32 draw_index asm("r0");
        register u32 draw_address asm("r1");

        asm volatile("" ::: "memory");
        window = (u16 *)0x02031756;
        draw_index = 0x201;
        window[0] = (u16)draw_index;
        func_080ED128(window + 1, func_080E7B64((*arg1)[3]));
        handle = (u8)func_08098B58(func_080E7B64((*arg1)[3]));
        draw_index = handle + 1;
        draw_index <<= 1;
        draw_index += (u32)window;
        *(u16 *)draw_index = 1;
        draw_index = handle << 1;
        draw_address = (u32)window + 4;
        draw_index += draw_address;
        func_080ED038((u16 *)draw_index, (void *)0x08103B20, 39);
        *(u16 **)0x0200A888 = window;
        func_08098BB4(0x080177D5);
        result = (u8)func_080E6EEC((*arg1)[1], (*arg1)[2], (*arg1)[3]);
        index = 0;
        asm volatile("" : "+r"(index) : : "r0", "r1", "r2", "r3", "r5", "r6");
        slots = (u8 *)0x020281F0;
        while (index <= 5) {
            if (*(u8 *)(index + (u32)slots) == 0) {
                func_080E5FA8((u8)index, result);
                break;
            }
            index++;
        }
        break;
    }
    case 8:
    {
        u16 *window;
        register u32 index asm("r0");
        register u32 address asm("r1");
        register u8 *definition_base asm("r0");
        register u8 *definition asm("r2");

        window = (u16 *)0x02031756;
        asm volatile("" : "+r"(window));
        definition_base = (u8 *)0x201;
        window[0] = (u16)(u32)definition_base;
        func_080ED128(window + 1, func_080E7B64((*arg1)[1]));
        handle = (u8)func_08098B58(func_080E7B64((*arg1)[1]));
        index = handle + 1;
        index <<= 1;
        index += (u32)window;
        *(u16 *)index = 1;
        if (handle > 13) {
            index = handle << 1;
            address = (u32)window + 4;
            index += address;
            func_080ED038((u16 *)index, (void *)0x08103B48, 32);
        } else {
            index = handle << 1;
            address = (u32)window + 4;
            index += address;
            func_080ED038((u16 *)index, (void *)0x08103B68, 31);
        }
        address = 0x0200A888;
        definition_base = (u8 *)0x02031756;
        *(u16 **)address = (u16 *)definition_base;
        func_08098BB4(0x080177D5);
        handle = 1;
        definition_base = (u8 *)0x020218E4;
        asm volatile("" : "+r"(definition_base));
        definition = definition_base + 0x5AD4;
        goto check_case_8;
advance_case_8:
        definition += 0x40;
        handle++;
        if (handle > 0x34) {
            goto done_case_8;
        }
check_case_8:
        if (*definition != (*arg1)[1]) {
            goto advance_case_8;
        }
done_case_8:
        func_080E6F6C((u8)handle);
        *(u8 *)0x02030665 = 1;
        break;
    }
    case 9:
    {
        u16 *window;
        register u8 *definition_base asm("r0");
        register u8 *definition asm("r1");
        register u32 definition_offset asm("r2");

        window = (u16 *)0x02031756;
        func_080ED038(window, (void *)0x08103B88, 23);
        definition_base = (u8 *)0x201;
        window[11] = (u16)(u32)definition_base;
        func_080ED038(window + 12, (void *)0x08103BA0, 27);
        window[25] = 1;
        func_080ED038(window + 26, (void *)0x08103BBC, 40);
        *(u16 **)0x0200A888 = window;
        func_08098BB4(0x080177D5);
        handle = 1;
        definition_base = (u8 *)0x020218E4;
        definition_offset = 0x5AD4;
        asm volatile("" : "+r"(definition_offset));
        definition = definition_base + definition_offset;
        goto check_case_9;
advance_case_9:
        definition += 0x40;
        handle++;
        if (handle > 0x34) {
            goto done_case_9;
        }
check_case_9:
        if (*definition != 1) {
            goto advance_case_9;
        }
done_case_9:
        asm volatile(
            ".macro ldr dst, addr:vararg\n\t"
            ".short 0x4802\n\t"
            ".purgem ldr\n\t"
            ".endm\n\t"
            ".macro add dst, args:vararg\n\t"
            ".short 0x1809\n\t"
            ".purgem add\n\t"
            ".endm");
        func_080E6E04(1, (handle << 6) + 0x02027378);
        break;
    }
    case 10:
    {
        register u32 *table asm("r6");
        u16 *window;
        register u16 *slot asm("r4");
        register u32 index asm("r0");
        register u32 address asm("r1");
        register u32 doubled asm("r5");

        window = (u16 *)0x02031756;
        func_080ED038(window, (void *)0x08103AF4, 23);
        slot = window + 11;
        table = (u32 *)0x087EE170;
        handle = (u8)func_0809F770(slot, table[(*arg1)[1]]);
        doubled = handle << 1;
        slot = (u16 *)(doubled + (u32)slot);
        func_080ED038(slot, (void *)0x08103B0C, 3);
        index = handle + 12;
        index <<= 1;
        index += (u32)window;
        address = 0x201;
        *(u16 *)index = (u16)address;
        index = (u32)window;
        index += 26;
        doubled += index;
        func_080ED128((u16 *)doubled, table[(*arg1)[1]]);
        handle += (u8)func_08098B58(table[(*arg1)[1]]);
        index = handle + 13;
        index <<= 1;
        index += (u32)window;
        *(u16 *)index = 1;
        index = handle << 1;
        address = (u32)window;
        address += 28;
        index += address;
        func_080ED038((u16 *)index, (void *)0x08103BE4, 16);
        *(u16 **)0x0200A888 = window;
        func_08098BB4(0x080177D5);
        if ((func_080E5CE4((*arg1)[1], 1) << 24) == 0) {
            func_080ED038(window, (void *)0x08103BF4, 51);
            func_08098BB4(0x080177D5);
        }
        break;
    }
    case 11:
    {
        u32 *table;
        u16 *window;
        u16 *slot;
        u32 handle;
        register u32 index asm("r0");
        register u32 address asm("r1");

        window = (u16 *)0x02031756;
        func_080ED038(window, (void *)0x08103AF4, 23);
        asm volatile(
            ".macro mov dst, args:vararg\n\t"
            ".short 0x4644\n\t"
            ".purgem mov\n\t"
            ".endm\n\t"
            ".macro ldr dst, args:vararg\n\t"
            ".short 0x4E2B\n\t"
            ".purgem ldr\n\t"
            ".endm\n\t"
            ".set c11_add_fix, 0\n\t"
            ".macro add dst, args:vararg\n\t"
            ".if c11_add_fix == 0\n\t.short 0x3416\n\t"
            ".elseif c11_add_fix == 1\n\t.short 0x1980\n\t"
            ".elseif c11_add_fix == 2\n\t.short 0x1C20\n\t"
            ".elseif c11_add_fix == 3\n\t"
            ".elseif c11_add_fix == 4\n\t.short 0x192C\n\t"
            ".elseif c11_add_fix == 5\n\t.short 0x1C20\n\t"
            ".elseif c11_add_fix == 6\n\t.short 0x1C38\n\t"
            ".elseif c11_add_fix == 7\n\t.short 0x300C\n\t"
            ".elseif c11_add_fix == 8\n\t.short 0x4440\n\t"
            ".elseif c11_add_fix == 9\n\t.short 0x301A\n\t"
            ".elseif c11_add_fix == 10\n\t.short 0x182D\n\t"
            ".elseif c11_add_fix == 11\n\t.short 0x1980\n\t"
            ".elseif c11_add_fix == 12\n\t.short 0x1C28\n\t"
            ".elseif c11_add_fix == 13\n\t.short 0x1980\n\t"
            ".elseif c11_add_fix == 14\n\t.short 0x183F\n\t"
            ".elseif c11_add_fix == 15\n\t.short 0x1C38\n\t"
            ".elseif c11_add_fix == 16\n\t.short 0x300D\n\t"
            ".elseif c11_add_fix == 17\n\t.short 0x4440\n\t"
            ".elseif c11_add_fix == 18\n\t.short 0x311C\n\t"
            ".else\n\t.short 0x1840\n\t"
            ".endif\n\t"
            ".set c11_add_fix, c11_add_fix + 1\n\t"
            ".endm\n\t"
            ".set c11_lsl_fix, 0\n\t"
            ".macro lsl dst, lhs, rhs\n\t"
            ".if c11_lsl_fix == 0\n\t.short 0x0080\n\t"
            ".elseif c11_lsl_fix == 1\n\t.short 0x0600\n\t"
            ".elseif c11_lsl_fix == 2\n\t.short 0x007D\n\t"
            ".elseif c11_lsl_fix == 3\n\t.short 0x0040\n\t"
            ".elseif c11_lsl_fix == 4\n\t.short 0x0080\n\t"
            ".elseif c11_lsl_fix == 5\n\t.short 0x0080\n\t"
            ".elseif c11_lsl_fix == 6\n\t.short 0x0600\n\t"
            ".elseif c11_lsl_fix == 7\n\t.short 0x0040\n\t"
            ".else\n\t.short 0x0078\n\t"
            ".endif\n\t"
            ".set c11_lsl_fix, c11_lsl_fix + 1\n\t"
            ".endm\n\t"
            ".set c11_lsr_fix, 0\n\t"
            ".macro lsr dst, lhs, rhs\n\t"
            ".if c11_lsr_fix == 0\n\t.short 0x0E07\n\t"
            ".else\n\t.short 0x0E00\n\t"
            ".endif\n\t"
            ".set c11_lsr_fix, c11_lsr_fix + 1\n\t"
            ".endm");
        slot = window + 11;
        table = (u32 *)0x087EEE10;
        handle = (u8)func_0809F770(slot, table[(*arg1)[1]]);
        slot += handle;
        func_080ED038(slot, (void *)0x08103B0C, 3);
        index = handle + 12;
        index <<= 1;
        index += (u32)window;
        address = 0x201;
        *(u16 *)index = (u16)address;
        index = (u32)window;
        index += 26;
        slot = (u16 *)((handle << 1) + index);
        func_080ED128(slot, table[(*arg1)[1]]);
        handle += (u8)func_08098B58(table[(*arg1)[1]]);
        index = handle + 13;
        index <<= 1;
        index += (u32)window;
        *(u16 *)index = 1;
        index = handle << 1;
        address = (u32)window;
        address += 28;
        index += address;
        func_080ED038((u16 *)index, (void *)0x08103C28, 13);
        asm volatile(".purgem add\n\t.purgem lsl\n\t.purgem lsr");
        *(u16 **)0x0200A888 = window;
        func_08098BB4(0x080177D5);
        if ((func_080E5D6C((*arg1)[1], 1) << 24) == 0) {
            func_080ED038(window, (void *)0x08103BF4, 51);
            func_08098BB4(0x080177D5);
        }
        break;
    }
    case 12:
    {
        u32 *table;
        u16 *window;
        register u32 index asm("r0");
        register u32 address asm("r1");

        window = (u16 *)0x02031756;
        func_080ED038(window, (void *)0x08103C38, 31);
        index = 0x201;
        window[15] = (u16)index;
        func_080ED128(window + 16,
            (table = (u32 *)0x087EDD54, table[(*arg1)[1]]));
        handle = (u8)func_08098B58(table[(*arg1)[1]]);
        index = handle + 16;
        index <<= 1;
        index += (u32)window;
        *(u16 *)index = 1;
        index = handle << 1;
        address = (u32)window;
        address += 34;
        index += address;
        func_080ED038((u16 *)index, (void *)0x08103C58, 12);
        *(u16 **)0x0200A888 = window;
        func_08098BB4(0x080177D5);
        if ((func_080E5DC4((*arg1)[1]) << 24) == 0) {
            func_080ED038(window, (void *)0x08103C64, 45);
            func_08098BB4(0x080177D5);
        }
        break;
    }
    case 13:
    {
        u32 *table;
        u16 *window;
        register u32 handle asm("r7");
        register u32 index asm("r0");
        register u32 address asm("r1");

        window = (u16 *)0x02031756;
        func_080ED038(window, (void *)0x08103C38, 31);
        index = 0x201;
        window[15] = (u16)index;
        func_080ED128(window + 16,
            (table = (u32 *)0x087EEE60, table[(*arg1)[1]]));
        handle = (u8)func_08098B58(table[(*arg1)[1]]);
        index = handle + 16;
        index <<= 1;
        index += (u32)window;
        *(u16 *)index = 1;
        index = handle << 1;
        address = (u32)window;
        address += 34;
        index += address;
        func_080ED038((u16 *)index, (void *)0x08103C94, 14);
        *(u16 **)0x0200A888 = window;
        func_08098BB4(0x080177D5);
        if ((func_080E5E0C((*arg1)[1], 1) << 24) == 0) {
            func_080ED038(window, (void *)0x08103BF4, 51);
            func_08098BB4(0x080177D5);
        }
        break;
    }
    case 14:
    {
        u32 *table;
        u16 *window;
        register u32 handle asm("r7");
        register u32 index asm("r0");
        register u32 address asm("r1");

        window = (u16 *)0x02031756;
        func_080ED038(window, (void *)0x08103CA4, 33);
        index = 0x201;
        window[16] = (u16)index;
        func_080ED128(window + 17,
            (table = (u32 *)0x087EF130, table[(*arg1)[1]]));
        handle = (u8)func_08098B58(table[(*arg1)[1]]);
        index = handle + 17;
        index <<= 1;
        index += (u32)window;
        *(u16 *)index = 1;
        index = handle << 1;
        address = (u32)window;
        address += 36;
        index += address;
        func_080ED038((u16 *)index, (void *)0x08103CC8, 29);
        *(u16 **)0x0200A888 = window;
        func_08098BB4(0x080177D5);
        if ((func_080E5EBC((*arg1)[1]) << 24) == 0) {
            func_080ED038(window, (void *)0x08103CE8, 45);
            func_08098BB4(0x080177D5);
        }
        break;
    }
    case 15:
    {
        register u16 *window asm("r5");
        register u16 *slot asm("r4");
        register u32 hundred asm("r6");
        register u32 zero asm("r8");
        register u32 marker asm("r0");
        u32 amount;

        window = (u16 *)0x02031756;
        func_080ED038(window, (void *)0x08103AF4, 23);
        zero = 0;
        marker = 0x201;
        window[11] = marker;
        amount = (*arg1)[1];
        hundred = 100;
        amount *= hundred;
        slot = window + 12;
        func_08098284(amount, 7, 0, slot);
        handle = (u8)func_08098B58(slot);
        func_080ED038((u16 *)((handle * 2) + (u32)slot),
            (void *)0x08103D18, 5);
        marker = handle + 13;
        window[marker] = 1;
        marker = handle + 14;
        window[marker] = zero;
        *(u16 **)0x0200A888 = window;
        func_08098BB4(0x080177D5);
        func_080E5E64((*arg1)[1] * hundred);
        break;
    }
    default:
        break;
    }
    func_08092EA0(53);
    func_08092E74(*(u8 *)0x02030667);
    func_080A016C(saved_arg0, -1, 0);
    return 0;
}
