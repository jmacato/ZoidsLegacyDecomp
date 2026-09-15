#include "m2c_prelude.h"

extern void func_08092E84(s32);
extern void *func_08094484(void *, void *, s32, s32, s32, s32, s32, s32, s32);
extern void func_08094554(void *);
extern void func_08096F3C(void);
extern void func_080972C8(void);
extern void func_080986B4(s32);
extern void func_08098BB4(s32);
extern void func_080ED17C(s32);

struct Item {
    u16 unused;
    u16 flags;
    u8 option;
    u8 pad[19];
};

void sub_080B7210(u8 arg0) {
    register u32 selection asm("r5");
    register u32 displayed asm("r8");
    register u8 category asm("r6");
    void *menu;
    void *description;
    category = arg0;
    func_08098BB4(0x080048DE);
    selection = 0;
    displayed = 1;
    menu = func_08094484((void *)0x080ED830, (void *)0x080ED864, 0,
                          120, *(u8 *)0x087A2788, 0x3EE, 15, 32, selection);
    description = func_08094484((void *)0x08105A20, (void *)0x08105A2C, 0,
                                 216, 152, 0x343, 15, 8, selection);
    func_08096F3C();

    do {
        if (selection != displayed) {
            register struct Item *items asm("r3") = (struct Item *)0x087B2524;
            register u32 item_scale asm("r0");
            register u32 item_offset asm("r2");

            item_scale = (u32)category * 3;
            item_offset = item_scale << 3;
            if ((*(u16 *)((u8 *)items + 2 + item_offset) & 1) == 0) {
                register s32 *messages asm("r0") = (s32 *)0x087A26B0;
                register u32 selected asm("r1");

                asm("" : : "r"(messages));
                selected = selection << 2;
                selected += (u32)messages;
                func_08098BB4(*(s32 *)selected);
            } else if (selection <= 1U) {
                register u32 option_address asm("r0");
                u8 option;
                s32 message;
                register u32 option_index asm("r0");

                option_address = (u32)items + 4;
                option_address = item_offset + option_address;
                option = *(u8 *)option_address;

                if (option != 0) {
                    register s32 *messages asm("r2") = (s32 *)0x087A26D8;
                    register u32 selected asm("r1");

                    asm("" : : "r"(messages));
                    selected = selection << 2;
                    option_index = (u32)option - 1;
                    option_index <<= 3;
                    selected += option_index;
                    selected += (u32)messages;
                    message = *(s32 *)selected;
                    if (message != 0) {
                        func_08098BB4(message);
                        goto message_done;
                    }
                }
                {
                    func_080986B4(7);
                    func_080972C8();
                }
            } else {
                register s32 *messages asm("r0") = (s32 *)0x087A26C8;
                register u32 selected asm("r1");

                asm("" : : "r"(messages));
                selected = (selection - 2) << 2;
                selected += (u32)messages;
                func_08098BB4(*(s32 *)selected);
            }
message_done:
            {
                register u32 selection_address asm("r0") = 0x087A2788;

                asm("" : "+r"(selection_address));
                selection_address = selection + selection_address;
                *(u16 *)((u8 *)menu + 6) = *(u8 *)selection_address;
            }
            displayed = selection;
        }
        func_080ED17C(1);
        if ((*(volatile u16 *)0x03006034 & 0x40) != 0 && selection != 0) {
            register u32 next asm("r0") = selection - 1;

            next <<= 24;
            selection = next >> 24;
            func_08092E84(0x40);
        }
        if ((*(volatile u16 *)0x03006034 & 0x80) != 0 && selection <= 4U) {
            register u32 next asm("r0") = selection + 1;

            next <<= 24;
            selection = next >> 24;
            func_08092E84(0x40);
        }
    } while ((*(volatile u16 *)0x0300000E & 2) == 0);

    func_08094554(menu);
    func_08094554(description);
    func_08098BB4(0x080048F6);
    func_08092E84(63);
}
