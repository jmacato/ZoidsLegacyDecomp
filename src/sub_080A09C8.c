#include "m2c_prelude.h"

extern u8 D_02030664;
extern u16 D_02030668[];
extern u32 D_02021690;
extern u8 D_02031840[][16];
extern u32 *D_02031940[];
extern u32 D_02032E8C[][6];
extern u8 D_02032EEC[][6];
extern u8 D_02031749;

u32 func_0809669C(void);
u32 func_080BB654(void);
u32 func_080D18CC(void);
u32 func_080ECF00(u32, u32);
u32 func_080ECF78(u32, u32);
void func_0809DFFC(void);
void func_0809534C(void);
void func_080D120C(void);
void func_080A016C(u8, s32, s32);
void func_080ED17C(s32);

s32 sub_080A09C8(u8 script_id)
{
    register u32 caller asm("sl") = script_id;
    u32 slot_count;
    u32 first_count;
    u32 mode;

    D_02030664 = 1;

retry:
    mode = D_02021690;
    if (mode == 3) {
        u16 *scan;

        first_count = 0;
        scan = D_02030668;
        if (*scan == 0) {
            do {
                scan = (u16 *)((u8 *)scan + 0x100);
                first_count++;
                if (first_count > 13)
                    break;
            } while (*scan == 0);
        }

        slot_count = 0;
        {
            register u32 mask asm("r2") = 1;
            register u32 **slot asm("r1") = D_02031940;

            do {
                u32 *object;

                object = *slot;
                if (object != 0 && ((*object & mask) == 0))
                    *slot = 0;
                slot++;
                slot_count++;
            } while (slot_count <= 15);
        }

        slot_count = 0;
        {
            register u32 mask asm("r3") = 4;
            register u8 *display asm("r2") = &D_02031840[0][0];
            register u32 **slot asm("r1") = D_02031940;

            do {
                u32 *object;

                object = *slot;
                if (object != 0) {
                    if ((*object & mask) == 0)
                        goto scan_done;
                    if (*display != 0)
                        goto scan_done;
                }
                display += 16;
                slot++;
                slot_count++;
            } while (slot_count <= 15);
        }
    } else if (mode == 9) {
        first_count = 0;
        {
            register u32 *state_base asm("r9") = &D_02032E8C[0][0];
            register u8 *flag_base asm("r8") = &D_02032EEC[0][0];
mode9_loop:
            {
                register u32 column asm("r5");
                register u32 state_offset asm("r4");
                register u32 row_offset asm("r1");
                register u32 row asm("r0");

                column = func_080ECF78(first_count, 6);
                state_offset = column << 2;
                row = func_080ECF00(first_count, 6);
                row_offset = row << 1;
                row_offset += row;
                row = row_offset << 3;
                state_offset += row;
                state_offset += (u32)state_base;
                if (*(u32 *)state_offset == 0)
                    goto mode9_next;
                row = row_offset << 1;
                row = column + row;
                row += (u32)flag_base;
                if (*(u8 *)row != 0)
                    goto scan_done;
            }
mode9_next:
            first_count++;
            if (first_count <= 11)
                goto mode9_loop;
        }
    }

scan_done:
    asm volatile("" : : "r"(first_count));
    if ((func_0809669C() << 24) != 0) {
        register u32 *mode_address asm("r0") = &D_02021690;
        register u32 ready_mode asm("r1") = *mode_address;
        register u32 *saved_mode_address asm("r2") = mode_address;

        if (ready_mode == 3 && first_count == 14 && slot_count == 16 &&
            D_02031749 == 0)
            goto ready;
        if (*saved_mode_address == 9 && first_count == 12 &&
            (func_080BB654() << 24) != 0)
            goto ready;
        if (D_02021690 == 10) {
            if ((func_080D18CC() << 24) == 0)
                goto not_ready;
            goto ready_fallthrough;
        }
    }

    goto not_ready;

ready:
ready_fallthrough:
    func_080A016C(caller, -1, 0);
    *(u8 *)0x020316F6 = 0;
    goto done;

not_ready:
    mode = D_02021690;
    if (mode == 3) {
        u8 *flag;

        flag = (u8 *)0x020316F6;
        if (*flag == 0) {
            func_0809DFFC();
            *flag = 1;
            goto retry;
        }
    } else if (mode == 10) {
        u8 status;

        status = *(u8 *)0x03005F70;
        if ((status == 2 || status == 4 || status == 6 || status == 8 ||
             status == 11 || status == 12 || status == 14 || status == 18) &&
            *(u8 *)0x03005F72 == *(u8 *)0x03005F71) {
            func_0809534C();
            func_080D120C();
        }
    }

    *(u8 *)0x020316F6 = 1;
    func_080ED17C(1);

done:
    return 0;
}
