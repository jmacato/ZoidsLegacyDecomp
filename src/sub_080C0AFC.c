#include "m2c_prelude.h"

extern void func_08092E84(s32);
extern void func_080972C8(void);
extern void func_08098834(s32);
extern void func_08098BB4(s32);
extern void func_080C0930(s32);
extern void func_080C098C(s32);
extern void func_080C0A9C(u8);
extern void func_080ED17C(s32);

extern volatile u8 D_0200A880;
extern volatile u8 D_0200A882;
extern volatile u16 D_0200A884;
extern u8 D_020281F6[];

void sub_080C0AFC(void) {
    register u8 *selected_base asm("r9");

    func_08098BB4(0x08019997);
    func_080C0930(0);
    func_080C098C(0);
    selected_base = D_020281F6;

outer_loop:
    func_08098BB4(0x080199CF);
    if (D_0200A882 == 1) {
        u8 *index_ptr;
        register u8 *index_init asm("r0") = (u8 *)&D_0200A880;
        register u32 initial_index asm("r1") = *index_init;
        register u8 *selected asm("r5");
        register u8 *slot_init asm("r1");
        register u8 *target_slot asm("r8");
        register u32 *available asm("r6");

        index_ptr = index_init;
        asm volatile("" : : "r"(index_ptr));
        selected = D_020281F6;
        slot_init = (u8 *)(initial_index + (u32)selected);
        target_slot = slot_init;
        available = (u32 *)((u8 *)selected + 0xEA);

inner_loop:
        func_08098BB4(0x08019A0A);
        {
            register u8 *table asm("r0");
            register u32 index asm("r1");
            register u32 value asm("r4");
            register u32 state asm("r2");

            table = (u8 *)0x087A2820;
            asm volatile("" : "+r"(table));
            index = *index_ptr;
            asm volatile("add %0, %1, %0"
                         : "+r"(table) : "r"(index));
            value = *table;
            state = D_0200A882;

            if (state == 1) {
                if (index != 0) {
                    register u32 word asm("r0") = value >> 5;

                    word <<= 2;
                    word += (u32)available;
                    {
                        register u32 shift asm("r1") = 0x1F;
                        shift &= value;
                        state <<= shift;
                    }
                    word = *(u32 *)word;
                    word &= state;
                    if (word == 0) {
                        goto inner_loop;
                    }
                    {
                        register u32 i asm("r1") = 0;

                        if (selected[0] != value) {
                            register u8 *scan asm("r2") = D_020281F6;

                            do {
                                register u32 next asm("r0") = i + 1;

                                next <<= 24;
                                i = next >> 24;
                                if (i > 9U) {
                                    break;
                                }
                            } while (*(u8 *)(i + (u32)scan) != value);
                        }
                        if (i <= 9U) {
                            *(u8 *)(i + (u32)selected) = 0;
                        }
                    }
                }

                *target_slot = value;
                func_08098834(4);
                func_080C098C(0);
                func_080972C8();
                func_080ED17C(1);
                func_08098834(3);
                func_080C0930(0);
                goto outer_loop;
            }

            if ((D_0200A884 & 8) != 0) {
                func_08092E84(0x41);
                if (*index_ptr != 0) {
                    register u32 word asm("r2") = value >> 5;

                    word <<= 2;
                    word += (u32)available;
                    {
                        register u32 shift asm("r0") = 0x1F;
                        register u32 one asm("r1");
                        register u32 bits asm("r0");

                        shift &= value;
                        one = 1;
                        one <<= shift;
                        bits = *(u32 *)word;
                        bits &= one;
                        if (bits != 0) {
                        func_080C0A9C(value);
                        } else {
                        func_080C0A9C(0);
                        }
                    }
                }
                goto inner_loop;
            }
        }
        goto outer_loop;
    }

    if ((D_0200A884 & 8) != 0) {
        func_08092E84(0x41);
        func_080C0A9C(selected_base[D_0200A880]);
        goto outer_loop;
    }
    func_08098BB4(0x08019A3F);
}
