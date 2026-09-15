#include "m2c_prelude.h"

struct EntryB7DC0 {
    u8 icon;
    u8 palette;
    u8 type;
    u8 pad03;
    u16 flags;
    u8 pad06[0x33];
    u8 price;
    s16 value_a;
    u8 pad3C[2];
    s16 value_b;
    u8 pad40[0x30];
};

void func_08092E84(s32);
s32 func_08094484();
void func_08094554(s32);
void func_0809534C(void);
void func_0809538C();
s32 func_0809669C(void);
void func_080981F0(s32, s32, s32, s32, s32);
void func_08098248(s32, s32, s32);
void func_0809844C(s32, s32, s32, s32, s32, s32, s32);
void func_080986B4(s32);
void func_08098834(s32);
void func_08098BB4(s32);
void func_0809A52C(u8, u8, s32, s32, s32);
void func_080AC214(s32, s32);
void func_080ACA8C(s32, s32, s32);
void func_080ACBA0(s32);
void func_080ACBDC(s32, u32);
void func_080B61C8(s32, s32, s32);
void func_080E5E90(u32);
void func_080E6090(struct EntryB7DC0 *);
s32 func_080E7B64(u8);
void func_080ED17C(s32);

#define D_0200A880 (*(volatile u8 *)0x0200A880)
#define D_0200A881 (*(volatile u8 *)0x0200A881)
#define D_0200A882 (*(volatile u8 *)0x0200A882)
#define D_020321A4 ((volatile u8 *)0x020321A4)

void sub_080B7DC0(void)
{
    s32 frame[3];
    register s32 state asm("r5") = 0;
    register struct EntryB7DC0 *entry asm("r8");
    register u32 first_visible asm("r9");
    register u32 selected asm("sl");
    volatile u32 *money;
    register u32 price asm("r6");

    asm volatile("" : : "m"(frame[0]), "m"(frame[1]));

dispatch:
    switch (state) {
    case 0:
        func_08098BB4(0x08005074);
        func_080ACA8C(5, 1, 1);
        /* Preserve the ROM's stack-first setup for this nine-argument call. */
        asm volatile(
            "mov r0, #72\n\t"
            "str r0, [sp, #0]\n\t"
            "str r5, [sp, #4]\n\t"
            "str r5, [sp, #8]\n\t"
            "mov r0, #8\n\t"
            "str r0, [sp, #12]\n\t"
            "str r5, [sp, #16]"
            : : : "r0", "r1", "memory");
        frame[2] = func_08094484(
            ({ register s32 arg asm("r0") = 0x0821024C;
               asm volatile("" : "+r"(arg)); arg; }),
            ({ register s32 arg asm("r1") = 0x08210258;
               asm volatile("" : "+r"(arg)); arg; }),
            0, 0xB8);
        {
            register u32 zero asm("r1") = 0;
            asm volatile("" : "+r"(zero));
            first_visible = zero;
            selected = zero;
        }
        goto next_state;

    case 16:
        func_08098BB4(0x080050FE);
        func_08098834(4);
        func_080AC214(4, 0);
        state = 0x20;
        goto continue_dispatch;

    case 32:
    {
        register s32 entry_offset asm("r0");
        register s32 entry_base asm("r2");
        register struct EntryB7DC0 *entry_low asm("r0");
        register u8 icon asm("r0");
        register struct EntryB7DC0 *palette_base asm("r2");
        register u8 palette asm("r1");
        register s32 six asm("r4");

        entry_offset = D_020321A4[selected] * 0x70;
        asm volatile("" : "+r"(entry_offset));
        entry_base = 0x020218E8;
        asm volatile("" : "+r"(entry_base));
        entry_low = (struct EntryB7DC0 *)(entry_offset + entry_base);
        entry = entry_low;
        icon = entry_low->icon;
        palette_base = entry;
        palette = palette_base->palette;
        func_0809A52C(icon, palette, 0, 0, 0x02002880);
        {
            register struct EntryB7DC0 *value_base asm("r1") = entry;
            register s32 value asm("r0");
            register s32 eight asm("r1");
            asm volatile("" : "+r"(value_base));
            value = value_base->value_a;
            six = 6;
            func_0809844C(value, 4, 0, 0xA, six,
                ({ eight = 8; asm volatile("" : "+r"(eight)); eight; }),
                eight);
        }
        {
            register struct EntryB7DC0 *value_base asm("r2") = entry;
            register s32 value asm("r0");
            asm volatile("" : "+r"(value_base));
            value = value_base->value_b;
            func_0809844C(value, 4, 0, 0xA, six,
                ({ register s32 eight asm("r2") = 8;
                   asm volatile("" : "+r"(eight)); eight; }),
                9);
        }
        func_080986B4(5);
        {
            register struct EntryB7DC0 *type_entry asm("r1") = entry;
            register s32 type_address asm("r0");
            register s32 type_base asm("r2");
            register s32 type_addend asm("r1");
            asm volatile("" : "+r"(type_entry));
            type_address = type_entry->type << 6;
            asm volatile("" : "+r"(type_address));
            type_base = 0x020218E4;
            asm volatile("" : "+r"(type_base));
            type_address += type_base;
            asm volatile("" : "+r"(type_address));
            type_addend = 0x5A94;
            asm volatile("" : "+r"(type_addend));
            type_address += type_addend;
            func_08098248(func_080E7B64(*(u8 *)type_address), 0, 5);
        }
        func_080ACBDC(5, first_visible);
        func_08098BB4(0x080050BB);
        selected = D_0200A880;
        first_visible = D_0200A881;
        switch (D_0200A882) {
        case 1:
        {
            register struct EntryB7DC0 *load_base asm("r2") = entry;
            register u32 flags asm("r0");
            register u32 mask_base asm("r2");
            register u32 mask asm("r1");
            register struct EntryB7DC0 *store_base asm("r1");
            asm volatile("" : "+r"(load_base));
            flags = load_base->flags;
            mask_base = 0xFFFE;
            asm volatile("" : "+r"(mask_base));
            mask = mask_base;
            asm volatile("" : "+r"(mask));
            flags &= mask;
            store_base = entry;
            asm volatile("" : "+r"(store_base));
            store_base->flags = flags;
            state = 0x30;
            goto continue_dispatch;
        }
        case 2:
            func_080ACBA0(5);
            func_08094554(frame[2]);
            func_08098BB4(0x080050BF);
            return;
        }
        goto continue_dispatch;
    }

    case 48:
    {
        register u8 *price_ptr asm("r5") = &entry->price;
        register u32 action asm("r4");
        register u32 cursor asm("r5");
        register s32 zero_r4 asm("r4");

        goto test_ready;
wait_ready:
        func_080ED17C(1);
test_ready:
        if ((func_0809669C() << 24) == 0) {
            goto wait_ready;
        }

        /* Preserve the ROM's stack-first setup for this eight-argument call. */
        asm volatile(
            "mov r4, #0\n\t"
            "str r4, [sp, #0]\n\t"
            "str r4, [sp, #4]\n\t"
            "mov r0, #47\n\t"
            "str r0, [sp, #8]\n\t"
            "mov r0, #63\n\t"
            "str r0, [sp, #12]"
            : "=r"(zero_r4) : : "r0", "r1", "r2", "memory");
        func_0809538C(
            ({ register s32 one asm("r0") = 1;
               asm volatile("" : "+r"(one)); one; }),
            ({ register s32 arg asm("r1") = 0x20D0;
               asm volatile("" : "+r"(arg)); arg; }),
            ({ register s32 arg asm("r2") = 0x2858;
               asm volatile("" : "+r"(arg)); arg; }),
            0);
        func_08098BB4(0x08005134);
        func_08098BB4(0x080050C6);
        {
            register s32 *icon_table asm("r1") = (s32 *)0x087EDD54;
            register struct EntryB7DC0 *icon_entry asm("r2") = entry;
            register u32 icon asm("r0");
            asm volatile("" : "+r"(icon_table), "+r"(icon_entry));
            icon = icon_entry->icon;
            func_080981F0(icon_table[icon], 2, 7, 0, zero_r4);
        }
        {
            register u32 price_byte asm("r1") = *price_ptr;
            register u32 price_work asm("r0");
            asm volatile("" : "+r"(price_byte));
            price_work = price_byte * 125;
            price = price_work << 3;
        }
        func_0809844C(price, 7, 0, 2, 7, 0xC, 2);
        func_08098BB4(0x080050F2);
        action = D_0200A882;
        if (action == 1) {
            asm volatile("" : : : "r0");
            cursor = D_0200A880;
            if (cursor == 0) {
                register s32 money_base asm("r0") = 0x020218E4;
                register s32 money_offset asm("r1") = 0x6A04;
                asm volatile("" : "+r"(money_base), "+r"(money_offset));
                money = (volatile u32 *)(money_base + money_offset);
                if (*money >= price) {
                    func_080E5E90(price);
                    func_080E6090(entry);
                    {
                        register u32 current_money asm("r0") = *money;
                        asm volatile("" : "+r"(current_money));
                        func_0809844C(current_money, 7, 0, 2,
                            action, action, cursor);
                    }
                    func_08098BB4(0x08005150);
                    func_08098BB4(0x080050EF);
                    func_0809534C();
                    func_080B61C8(8, 0, 0);
                    {
                        register volatile u8 *result_ptr asm("r0") =
                            (volatile u8 *)0x02032272;
                        register u32 result asm("r0");
                        asm volatile("" : "+r"(result_ptr));
                        result = *result_ptr;
                        if (result != 0) {
                            if (result == selected) {
                                register u32 next_selected asm("r0") = selected;
                                asm volatile("" : "+r"(next_selected));
                                next_selected--;
                                next_selected <<= 24;
                                next_selected >>= 24;
                                selected = next_selected;
                            }
                            if (selected < first_visible) {
                                register u32 old_first asm("r2") = first_visible;
                                register u32 next_first asm("r0");
                                asm volatile("" : "+r"(old_first));
                                if (old_first > 4) {
                                    next_first = first_visible - 5;
                                    next_first <<= 24;
                                    next_first >>= 24;
                                } else {
                                    next_first = 0;
                                }
                                first_visible = next_first;
                            }
                            goto next_state;
                        }
                    }
                    func_080ACBA0(5);
                    func_08094554(frame[2]);
                    func_08098BB4(0x080050BF);
                    func_08098BB4(0x08004FAE);
                    return;
                }
                func_08092E84(0x58);
                func_08098BB4(0x08005180);
            }
        }
        func_08098BB4(0x080050EF);
        func_0809534C();
        goto next_state;
    }
    default:
        goto continue_dispatch;
    }

next_state:
    state = 0x10;
continue_dispatch:
    {
        register s32 zero asm("r1") = 0;
        asm volatile("" : "+r"(zero));
        if (zero != 0) {
            return;
        }
    }
    goto dispatch;
}
