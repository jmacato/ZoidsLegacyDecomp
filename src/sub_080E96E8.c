#include "m2c_prelude.h"

void func_080972C8(void);
void func_0809844C(s32, s32, s32, s32, s32, s32, s32);
void func_08098BB4(const void *);
void func_0809AEC0(void *, s32, const void *);
u8 func_0809AEF4(void);
void func_0809B00C(void *, s32, const void *);
u8 func_0809B040(void);
void func_080E8B08(s32, s32);
void func_080E90AC(s32, s32);
s32 func_080ECD98(s32, s32);
void func_080ED17C(s32);

void sub_080E96E8(void)
{
    u8 i;
    u8 left_ready;
    u8 right_ready;
    volatile s32 next_i;

    func_08098BB4((void *)0x08028388);
    i = 0;
    do {
        u32 offset = i * 0x270;
        u8 *base = (u8 *)0x02034B4C;
        u32 split;
        u8 *left;
        register u8 *right asm("r8");
        u8 *right3;
        u32 twice;

        left = (u8 *)(offset + (u32)base);
        split = 0x9C;
        split <<= 5;
        base += split;
        offset += (u32)base;
        right = (u8 *)offset;
        func_0809AEC0(left, 0x70, (void *)0x08109450);
        func_0809B00C(right, 0x70, (void *)0x08109450);
        twice = i << 1;
        {
            register s32 next_view asm("r1") = i + 1;
            next_i = next_view;
        }
        do {
            left_ready = func_0809AEF4();
            right_ready = func_0809B040();
            func_080ED17C(1);
        } while (left_ready == 0 || right_ready == 0);
        {
            register s32 twice_view asm("r2") = twice;
            register s32 dialog asm("r0") = twice_view + i;
            register s32 factor asm("r1");
            asm volatile("" : "+r"(twice_view));
            dialog += 1;
            factor = 100;
            dialog *= factor;
            factor = 24;
            dialog = func_080ECD98(dialog, factor);
            func_0809844C(dialog, 3, 0, 2, 8, 6, 0);
        }
        func_080972C8();

        func_0809AEC0(left + 0x70, 0x40, (void *)0x0810945C);
        func_0809B00C(right + 0x70, 0x40, (void *)0x0810945C);
        left += 0xB0;
        {
            register u8 *right3_work asm("r0") = (u8 *)0xB0;
            asm volatile("" : "+r"(right3_work));
            right3_work += (u32)right;
            right3 = right3_work;
        }
        do {
            left_ready = func_0809AEF4();
            right_ready = func_0809B040();
            func_080ED17C(1);
        } while (left_ready == 0 || right_ready == 0);
        {
            register s32 twice_view asm("r1") = twice;
            register s32 dialog asm("r0") = twice_view + i;
            register s32 factor asm("r1");
            dialog += 2;
            factor = 100;
            dialog *= factor;
            factor = 24;
            dialog = func_080ECD98(dialog, factor);
            func_0809844C(dialog, 3, 0, 2, 8, 6, 0);
        }
        func_080972C8();

        func_0809AEC0(left, 0x34, (void *)0x08109468);
        func_0809B00C(right3, 0x34, (void *)0x08109468);
        do {
            left_ready = func_0809AEF4();
            right_ready = func_0809B040();
            func_080ED17C(1);
        } while (left_ready == 0 || right_ready == 0);
        {
            register s32 twice_view asm("r2") = twice;
            register s32 dialog asm("r0") = twice_view + i;
            register s32 factor asm("r1");
            asm volatile("" : "+r"(twice_view));
            dialog += 3;
            factor = 100;
            dialog *= factor;
            factor = 24;
            dialog = func_080ECD98(dialog, factor);
            func_0809844C(dialog, 3, 0, 2, 8, 6, 0);
        }
        func_080972C8();

        {
            register u8 *right_view asm("r1") = right;
            if (right_view[0] != 0) {
                func_080E90AC(1, i);
                func_080E8B08(1, i);
                *(u32 *)(right + 0x268) = 0;
                *(u32 *)(right + 0x26C) = 0;
            }
        }
        {
            register s32 next_view asm("r2") = next_i;
            register s32 normalized asm("r0");
            normalized = next_view << 24;
            asm volatile("" : "+r"(normalized));
            i = (u32)normalized >> 24;
        }
    } while (i <= 7);

    {
        u8 *dst = (u8 *)0x0203EDE8;
        const void *asset = (void *)0x08109474;
        func_0809AEC0(dst, 0x12, asset);
        dst += 0x12;
        func_0809B00C(dst, 0x12, asset);
        do {
            left_ready = func_0809AEF4();
            right_ready = func_0809B040();
            func_080ED17C(1);
        } while (left_ready == 0 || right_ready == 0);
    }

    {
        u8 *dst = (u8 *)0x0203EE0C;
        const void *asset = (void *)0x08109480;
        func_0809AEC0(dst, 0x2E, asset);
        dst += 0x2E;
        func_0809B00C(dst, 0x2E, asset);
        do {
            left_ready = func_0809AEF4();
            right_ready = func_0809B040();
            func_080ED17C(1);
        } while (left_ready == 0 || right_ready == 0);
    }
    func_08098BB4((void *)0x080283A8);
}
