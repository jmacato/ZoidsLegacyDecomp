#include "m2c_prelude.h"

typedef struct {
    s32 x;
    s32 y;
    s32 x2;
    s32 y2;
    s32 x3;
    s32 y3;
    s32 x4;
    s32 y4;
} DisplayState;

extern u16 D_0202ECF4;
extern u8 D_020324B0;
extern s32 D_02032590;
extern s32 D_02032594;
extern s32 D_02032598;
extern u8 D_0203259C;
extern u8 D_0203259D;
extern u16 D_0300004E;
extern u16 D_03000050;
extern DisplayState D_03000054;

extern void func_08095208(u32, u32, u32);
extern s32 func_0809669C(void);
extern void func_0809D734(void);
extern void func_0809DD80(void);
extern void func_080A9F8C(void);

void sub_0809DFFC(void)
{
    u16 mode;

    func_080A9F8C();
    if (D_0202ECF4 == 0 && (D_020324B0 & 4) != 0) {
        DisplayState *display = &D_03000054;
        display->x4 = display->x;
        display->y4 = display->y;
    }
    func_0809DD80();
    mode = D_0202ECF4;

    if (mode == 0 || mode == 0x40) {
        register s32 var_r2 asm("r2");
        register u8 *flags_ptr asm("r4");
        register u8 *flags_addr asm("r1");
        register s32 bit_test asm("r0");
        DisplayState *display;
        s32 y2_value;

        flags_addr = &D_020324B0;
        var_r2 = *flags_addr;
        bit_test = 1;
        bit_test &= var_r2;
        flags_ptr = flags_addr;
        if (bit_test != 0) {
            register s32 var_r3 asm("r3");

            var_r3 = D_02032590 - 0x40;
            D_02032590 = var_r3;
            var_r2 = D_02032594 + 0x30;
            D_02032594 = var_r2;
            display = &D_03000054;
            display->x2 = display->x + var_r3;
            y2_value = display->y + var_r2;
            goto store_scroll_y;
        }
        bit_test = 2;
        bit_test &= var_r2;
        if (bit_test != 0) {
            display = &D_03000054;
            var_r2 = display->y2;
            if (var_r2 <= 0x4FFF) {
                display->x2 -= 0x40;
                y2_value = var_r2;
                y2_value += 0x30;
                goto store_scroll_y;
            }
        }
        goto after_scroll;
store_scroll_y:
        display->y2 = y2_value;
after_scroll:
        if (D_0202ECF4 == 0) {
            var_r2 = D_02032598 + 0x10;
            D_02032598 = var_r2;
            display = &D_03000054;
            display->x3 = display->x;
            display->y3 = display->y + var_r2;
        }
        if (*flags_ptr != 0 && (u8)func_0809669C() == 0) {
            D_0300004E = 0x1542;
            if ((*flags_ptr & 4) != 0)
                D_0300004E |= 0x0808;
            D_03000050 = 0x0C0A;
        }
        func_0809D734();
    } else if (mode == 0x7D) {
        u8 *tile_delay = &D_0203259D;
        if (*tile_delay == 0) {
            u8 *tile_index = &D_0203259C;

            func_08095208(0x085CE1FC + (*tile_index << 5), 0x05000020, 0x20);
            {
                u32 tile_offset = *tile_index << 5;
                register u32 tile_source asm("r1");

                tile_source = 0x085CE39C;
                /* Preserve the source literal in r1 without emitting code. */
                asm("" : "+r"(tile_source));
                func_08095208(tile_offset + tile_source, 0x05000040, 0x20);
            }
        }
        (*tile_delay)++;
        if (*tile_delay == 0xF) {
            *tile_delay = 0;
            {
                u8 *tile_index = &D_0203259C;

                (*tile_index)++;
                if (*tile_index == 0xD)
                    *tile_index = 0;
            }
        }
    } else if (mode == 0x7E) {
        u8 *tile_delay = &D_0203259D;
        if (*tile_delay == 0) {
            u32 tile_offset = D_0203259C << 5;
            register u32 tile_source asm("r1");

            tile_source = 0x085CE1FC;
            /* Preserve the source literal in r1 without emitting code. */
            asm("" : "+r"(tile_source));
            func_08095208(tile_offset + tile_source, 0x05000060, 0x20);
        }
        (*tile_delay)++;
        if (*tile_delay == 0xF) {
            *tile_delay = 0;
            {
                u8 *tile_index = &D_0203259C;

                (*tile_index)++;
                if (*tile_index == 6)
                    *tile_index = 0;
            }
        }
    }
}
