#include "m2c_prelude.h"

M2C_UNK func_08092D8C(s32, M2C_UNK);                /* extern */
M2C_UNK func_0809538C(s32, s32, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_0809A1BC(s32, M2C_UNK, M2C_UNK);       /* extern */
M2C_UNK func_0809AA64(M2C_UNK, s32, s32, s32);      /* extern */
M2C_UNK func_080ECD34(s32, void *);                 /* extern */

void sub_0809A5B4(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    volatile s32 sp10;
    s16 *var_r4_4;
    s32 temp_r4_2;
    s32 temp_r4_3;
    s32 var_r0;
    u16 *var_r4_3;
    u16 *var_r4_5;
    u16 var_r1_2;
    u32 var_r1_4;
    u32 var_r1_6;
    u32 var_r3;
    u8 temp_r3;
    u8 temp_r5;
    u32 temp_r5_2;
    u8 temp_r6;
    u8 temp_r7;
    u8 var_r2;

    temp_r5 = arg0;
    temp_r7 = arg1;
    temp_r6 = arg2;
    temp_r3 = arg3;
    asm volatile("lsl r4, r4, #24\n\tlsr r4, r4, #24" ::: "cc");
    sp10 = arg4;
    if ((u32) temp_r5 <= 0xFCU) {
        {
            register volatile s16 *control asm("r3") = (volatile s16 *)0x0400000C;
            asm volatile("" : "+r"(control));
            asm volatile(
            "mov r0, %1\n\t"
            "lsl r2, r0, #8\n\t"
            "lsl r0, r4, #2\n\t"
            "mov r1, #128\n\t"
            "orr r0, r1\n\t"
            "orr r2, r0\n\t"
            "mov r0, #3\n\t"
            "orr r2, r0\n\t"
            "strh r2, [r3]"
            : "+r"(control)
            : "r"(temp_r3)
            : "r0", "r1", "r2", "cc", "memory");
        }
        {
            register u8 *table1 asm("r3") = (u8 *)0x087AF794;
            register s32 computed_offset asm("r2");
            register u32 twice asm("r1");
            asm volatile("" : "+r"(table1));
            twice = temp_r5 * 2;
            asm volatile("" : "+r"(twice));
            asm volatile(
                "add r0, r1, r5\n\t"
                "lsl r2, r0, #3\n\t"
                "mov r5, r1"
                : "=r"(computed_offset)
                : "r"(twice)
                : "r0", "cc");
            if ((u32) temp_r7 > 2U) {
                var_r0 = ((temp_r7 - 2) * 8) + computed_offset;
                asm volatile("" : "+r"(var_r0));
            } else {
                var_r0 = computed_offset;
                asm volatile("" : "+r"(var_r0));
            }
            {
                register u8 *address asm("r0") = table1 + var_r0;
                register s32 source asm("r0");
                register void *dest asm("r1");
                asm volatile("" : "+r"(address));
                source = *(s32 *)address;
                asm volatile("" : "+r"(source));
                asm volatile(
                    "mov r2, r9\n\t"
                    "lsl r1, r2, #14\n\t"
                    "mov r2, #192\n\t"
                    "lsl r2, r2, #19\n\t"
                    "add r1, r1, r2"
                    : "=r"(dest)
                    :
                    : "r2", "cc");
                func_080ECD34(source, dest);
            }
        }
        {
            register u8 *table asm("r2") = (u8 *)0x087AF794;
            register u8 *view asm("r0");
            register s32 table_offset asm("r1");
            asm volatile("" : "+r"(table));
            asm volatile(
                "mov r3, sl\n\t"
                "add r0, r5, r3\n\t"
                "lsl r1, r0, #3"
                : "=r"(table_offset)
                :
                : "r0", "r3", "cc");
            if ((u32) temp_r7 > 2U) {
                asm volatile(
                    "sub r0, r7, #2\n\t"
                    "lsl r0, r0, #3\n\t"
                    "add r1, r0, r1"
                    : "+r"(table_offset)
                    :
                    : "r0", "cc");
            }
            view = table + 4;
            asm volatile("" : "+r"(view));
            func_0809A1BC(M2C_FIELD(view, s32 *, table_offset), 0x05000080, 0x02002880);
        }
        {
            register u32 tilemap_high asm("r0") = temp_r3;
            register u32 tilemap_offset asm("r1");
            register u32 tilemap_base asm("r0");
            register void *tilemap asm("r4");
            asm volatile("" : "+r"(tilemap_high));
            tilemap_offset = tilemap_high << 0xB;
            asm volatile("" : "+r"(tilemap_offset));
            tilemap_base = 0x06000000;
            asm volatile("" : "+r"(tilemap_base));
            tilemap = (void *)(tilemap_offset + tilemap_base);
            asm volatile("" : "+r"(tilemap));
            {
                register s32 tile_index asm("r1") = temp_r6;
                register s32 first_visible asm("r2") = sp10;
                register s32 visible_delta asm("r0");
                asm volatile("" : "+r"(tile_index));
                asm volatile("" : "+r"(first_visible));
                visible_delta = tile_index - first_visible;
                asm volatile("" : "+r"(visible_delta));
                var_r1_2 = visible_delta << 8;
            }
            var_r3 = 0;
            do {
                var_r2 = 0;
                temp_r5_2 = var_r3 + 1;
loop_8:
                if (var_r3 <= 0xFU) {
                    M2C_FIELD(tilemap, u16 *, 0) = var_r1_2;
                    M2C_FIELD(tilemap, u16 *, 0x20) = var_r1_2;
                    var_r1_2 += 1;
                } else {
                    M2C_FIELD(tilemap, u16 *, 0x20) = 0U;
                    M2C_FIELD(tilemap, u16 *, 0) = 0U;
                }
                tilemap += 2;
                var_r2 += 1;
                if ((u32) var_r2 <= 0xFU) {
                    goto loop_8;
                }
                tilemap += 0x20;
                var_r3 = (u8) temp_r5_2;
            } while (var_r3 <= 0x1FU);
        }
        return;
    }
    if ((u32) (u8) (temp_r5 + 3) <= 1U) {
        register u32 clear_count asm("r1");
        register s16 *clear_ptr asm("r4");
        register u32 clear_zero asm("r2");
        register u32 fill_end asm("r5");
        register u32 fill_mask asm("r3");
        register u32 fill_threshold asm("r6");
        register u32 fill_value asm("r2");
        register u32 tilemap_offset asm("r5");
        *(s16 *)0x0400000C = ({
            register u32 display_config asm("r0");
            asm volatile(
                "mov r3, %1\n\t"
                "lsl r0, r3, #8\n\t"
                "lsl r1, %2, #2\n\t"
                "orr r0, r1\n\t"
                "mov r1, #3\n\t"
                "orr r0, r1"
                : "=r"(display_config)
                : "r"(temp_r3), "r"(temp_r6)
                : "r1", "r3", "cc");
            display_config;
        });
        func_080ECD34(0x08421FCC,
                      (void *)((temp_r4_2 = temp_r6 << 0xE) + 0x06000000));
        clear_ptr = (s16 *)temp_r4_2;
        asm volatile("" : "+r"(clear_ptr));
        {
            register u32 clear_base asm("r0") = 0x06000200;
            asm volatile("" : "+r"(clear_base));
            asm volatile("add r4, r4, r0"
                         : "+r"(clear_ptr)
                         : "r"(clear_base)
                         : "cc");
        }
        clear_count = 0;
        asm volatile("" : "+r"(clear_count));
        {
            register u32 tilemap_high asm("r0") = temp_r3;
            asm volatile("" : "+r"(tilemap_high));
            tilemap_offset = tilemap_high << 0xB;
            asm volatile("" : "+r"(tilemap_offset));
        }
        clear_zero = 0;
        asm volatile("" : "+r"(clear_zero));
        do {
            *clear_ptr = clear_zero;
            clear_ptr += 1;
            asm volatile(
                "add r0, r1, #1\n\t"
                "lsl r0, r0, #16\n\t"
                "lsr r1, r0, #16"
                : "+r"(clear_count)
                :
                : "r0", "cc");
        } while (clear_count <= 0xFU);
        func_080ECD34(0x084220B4, (u16 *)0x05000080);
        func_080ECD34(0x084220DC, ({
            var_r4_3 = (u16 *)0x06000000;
            asm volatile("" : "+r"(var_r4_3));
            var_r4_3 = (u16 *)(tilemap_offset - (0U - (u32)var_r4_3));
            var_r4_3;
        }));
        var_r1_4 = 0;
        fill_threshold = 0x27F;
        asm volatile("" : "+r"(fill_threshold));
        fill_end = 0x3FF;
        asm volatile("" : "+r"(fill_end));
        asm volatile(
            "mov r2, #128\n\t"
            "lsl r2, r2, #7\n\t"
            "mov r3, r2\n\t"
            "mov r2, #16"
            : "=r"(fill_mask), "=r"(fill_value)
            :
            : "cc");
        do {
            if (var_r1_4 <= fill_threshold) {
                *var_r4_3 |= fill_mask;
            } else {
                *var_r4_3 = fill_value;
            }
            var_r4_3 += 1;
            var_r1_4 = (u32) (u16) (var_r1_4 + 1);
        } while (var_r1_4 <= fill_end);
        {
            register u32 mode asm("r3") = temp_r5;
            asm volatile("" : "+r"(mode));
            if (mode == 0xFD) {
                func_0809AA64(0x087AF9D4, 9, 0x180, 3);
            }
        }
    } else {
        register u32 mode_ff asm("r0") = temp_r5;
        asm volatile("" : "+r"(mode_ff));
        if (mode_ff == 0xFF) {
        register u32 clear_count_2 asm("r1");
        register u32 char_block_2 asm("r3");
        {
            register volatile s16 *control asm("r2") = (volatile s16 *)0x0400000C;
            register u32 config asm("r0");
            register u32 high asm("r1") = temp_r3;
            asm volatile("" : "+r"(control));
            asm volatile("" : "+r"(high));
            config = high << 8;
            asm volatile("" : "+r"(config));
            char_block_2 = temp_r6;
            asm volatile("" : "+r"(char_block_2));
            {
                register u32 low asm("r1");
                low = char_block_2 << 2;
                asm volatile("" : "+r"(low));
                config |= low;
            }
            config |= 3;
            *control = config;
        }
        {
            s32 *state = (s32 *)0x03000054;
            state[1] = 0x2000;
            state[5] = 0xFFFFF000;
        }
        func_080ECD34(0x083C71E0, ({
            register void *graphics_dest asm("r1");
            register s32 graphics_block asm("r4");
            asm volatile(
                "lsl r4, r3, #14\n\t"
                "mov r1, #192\n\t"
                "lsl r1, r1, #19\n\t"
                "add r1, r4, r1"
                : "=r"(graphics_block), "=r"(graphics_dest)
                : "r"(char_block_2)
                : "cc");
            temp_r4_3 = graphics_block;
            graphics_dest;
        }));
        var_r4_4 = temp_r4_3 + 0x060007A0;
        clear_count_2 = 0;
        asm volatile("" : "+r"(clear_count_2));
        asm volatile(
            "mov r0, %0\n\t"
            "lsl r5, r0, #11"
            :
            : "r"(temp_r3)
            : "r0", "r5", "cc");
        do {
            *var_r4_4 = 0;
            var_r4_4 += 1;
            asm volatile(
                "add r0, r1, #1\n\t"
                "lsl r0, r0, #16\n\t"
                "lsr r1, r0, #16"
                : "+r"(clear_count_2)
                :
                : "r0", "cc");
        } while (clear_count_2 <= 0xFU);
        func_080ECD34(0x083C77FC, ({
            var_r4_5 = (u16 *)0x06000000;
            asm volatile("" : "+r"(var_r4_5));
            asm volatile("add r4, r5, r4"
                         : "+r"(var_r4_5)
                         :
                         : "cc");
            var_r4_5;
        }));
        {
        register u32 fill_end_2 asm("r2");
        register u32 fill_mask_2 asm("r5");
        register u32 fill_value_2 asm("r3");
        var_r1_6 = 0;
        asm volatile(
            "mov r2, #128\n\t"
            "lsl r2, r2, #7\n\t"
            "mov r5, r2\n\t"
            "mov r3, #61"
            : "=r"(fill_mask_2), "=r"(fill_value_2)
            :
            : "r2", "cc");
        fill_end_2 = 0x3FF;
        asm volatile("" : "+r"(fill_end_2));
        do {
            if (var_r1_6 <= 0xFFU) {
                *var_r4_5 |= fill_mask_2;
            } else {
                *var_r4_5 = fill_value_2;
            }
            var_r4_5 += 1;
            var_r1_6 = (u32) (u16) (var_r1_6 + 1);
        } while (var_r1_6 <= fill_end_2);
        }
        *(s16 *)0x05000000 = 0;
        func_0809538C(1, 0xF0, 0x10, 1, 0xF0, 0x5060, 0x808, 0x3F);
        *(s8 *)0x02033F54 = 0;
        func_08092D8C(7, 0x080CFD99);
        }
    }
}
