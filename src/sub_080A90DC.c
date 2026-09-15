#include "m2c_prelude.h"

extern void func_08092D8C(s32, void *);
extern void func_08092E0C(s32);
extern void func_08092E84(s32);
extern void func_08094330(void);
extern void func_08096308(s32, s32);
extern s32 func_0809669C(void);
extern void func_0809D938(s32, s32, s32);
extern void func_080A9888(void);
extern void func_080ECD28(const void *, void *, u32);
extern void func_080ECD2C(const void *, void *, void *);
extern void func_080ECD34(const void *, void *);
extern void func_080ED17C(s32);

void sub_080A90DC(void)
{
    register volatile u16 *tile asm("r4");
    register s32 carrier_r5 asm("r5");
    register u32 carrier_r6 asm("r6");
    register volatile u8 *flag_99 asm("r12");
    register volatile u8 *control_74 asm("r3");
    register volatile u8 *flag_98 asm("r8");
    register const void *dma_source asm("r9");
    register void *dma_destination asm("r10");
    volatile s32 zero;

    *(s32 *)0x02021690 = 3;
    func_080ED17C(1);
    func_08094330();
    func_080A9888();
    *(u8 *)0x020324B0 = 0;
    func_0809D938(0, 0, 0);
    {
        register volatile u16 *scene asm("r0") =
            (volatile u16 *)0x0202ECF4;

        carrier_r5 = 0;
        *scene = carrier_r5;
    }

    func_080ECD34((const void *)0x0842219C, (void *)0x0600C000);
    {
        register const void *tile_source asm("r0") =
            (const void *)0x0842295C;

        tile = (volatile u16 *)0x0600F000;
        func_080ECD34(tile_source, (void *)tile);
    }
    func_080ECD34((const void *)0x08422934, (void *)0x05000180);
    zero = carrier_r5;
    func_080ECD28(&zero, (void *)0x0600EFE0, 0x01000008);

    {
        register u32 limit asm("r2") = 0x1FF;
        register u32 mask_source asm("r0") = 0xC000;
        register u32 mask asm("r1");

        asm volatile("" : "+r"(limit), "+r"(mask_source));
        mask = mask_source;
        do {
            *tile |= mask;
            tile++;
            carrier_r5++;
        } while ((u32)carrier_r5 <= limit);
    }
    {
        register u32 limit asm("r1");
        register volatile u16 *display_control asm("r2");
        register u16 fill asm("r0");

        carrier_r5 = 0;
        limit = 0x5FF;
        display_control = (volatile u16 *)0x0300004C;
        carrier_r6 = 0x0203219C;
        {
            register u32 guard0 asm("r0");
            register u32 guard3 asm("r3");

            asm volatile("" : "=r"(guard0), "=r"(guard3));
            flag_99 = (volatile u8 *)0x02031C99;
            asm volatile("" :: "r"(guard0), "r"(guard3));
        }
        control_74 = (volatile u8 *)0x03000074;
        flag_98 = (volatile u8 *)0x02031C98;
        dma_source = (const void *)0x08000894;
        dma_destination = (void *)0x030060FC;
        fill = 0x017F;
        do {
            *tile = fill;
            tile++;
            carrier_r5++;
        } while ((u32)carrier_r5 <= limit);

        *display_control |= 0x0200;
    }

    *(u16 *)0x0400000A = 0x5E0E;
    {
        register s32 zero_value asm("r4") = 0;
        register s32 *global_base asm("r0") = (s32 *)0x03000054;

        global_base[2] = zero_value;
        *(volatile s32 *)carrier_r6 = 0x6000;
        {
            register volatile u8 *flag_copy asm("r1") = flag_99;

            *flag_copy = zero_value;
        }
        *control_74 |= 0x20;
        {
            register volatile u8 *flag_copy asm("r2");
            register u32 flag_value asm("r0") = 1;

            flag_copy = flag_98;
            *flag_copy = flag_value;
        }
        func_080ECD2C(dma_source, dma_destination,
            (void *)0x04000014);
        *(u8 *)0x020321A0 = zero_value;
    }
    func_08092D8C(4, (void *)0x080A8FAD);
    {
        register volatile u16 *position_x asm("r1") =
            (volatile u16 *)0x03005F74;

        asm volatile("" : "+r"(position_x));
        *position_x = 120;
    }
    {
        register volatile u16 *position_y asm("r1") =
            (volatile u16 *)0x03005F76;

        *position_y = 80;
    }
    func_08096308(13, 0);
    {
        register volatile u16 *control_a asm("r1") =
            (volatile u16 *)0x0300004E;
        register u32 value_a asm("r4") = 0x1542;
        register u32 store_value asm("r0");

        asm volatile("" : "+r"(control_a), "+r"(value_a));
        store_value = value_a;
        *control_a = store_value;
    }
    {
        register volatile u16 *control_b asm("r1") =
            (volatile u16 *)0x03000050;
        register u32 value_b asm("r7") = 0x0C0A;
        register u32 store_value asm("r0");

        store_value = value_b;
        *control_b = store_value;
    }

    carrier_r5 = -0x100;
    func_08092E84(107);
    if (*(volatile s32 *)carrier_r6 > 0x1000) {
        register volatile s32 *animation asm("r4") =
            (volatile s32 *)carrier_r6;

        carrier_r6 = 0x1000;
        do {
            *animation += carrier_r5;
            func_080ED17C(1);
        } while (*animation > (s32)carrier_r6);
    }
    if (carrier_r5 != 0) {
        register volatile s32 *animation asm("r4") =
            (volatile s32 *)0x0203219C;

        do {
            *animation += carrier_r5;
            carrier_r5 += 0x10;
            func_080ED17C(1);
        } while (carrier_r5 != 0);
    }

    carrier_r5 = 0;
    do {
        func_080ED17C(1);
        carrier_r5++;
    } while ((u32)carrier_r5 <= 59);
    *(u8 *)0x020321A0 = 1;
    carrier_r5 = 0;
    do {
        func_080ED17C(1);
        carrier_r5++;
    } while ((u32)carrier_r5 <= 44);
    func_08092E84(68);
    while (*(u8 *)0x020321A0 == 1) {
        func_080ED17C(1);
    }
    carrier_r5 = 0;
    do {
        func_080ED17C(1);
        carrier_r5++;
    } while ((u32)carrier_r5 <= 59);

    func_08096308(2, 16);
    while ((u8)func_0809669C() == 0) {
        func_080ED17C(1);
    }
    func_08092E0C(4);
    {
        register volatile u8 *final_flag asm("r1") =
            (volatile u8 *)0x02031C98;

        *final_flag = 3;
    }
    *(s32 *)0x02021690 = -1;
    func_080ED17C(1);
}
