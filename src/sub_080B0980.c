#include "m2c_prelude.h"

M2C_UNK func_08092E84(s32);                         /* extern */
s32 *func_08094484();                               /* extern */
M2C_UNK func_08094554(s32 *);                       /* extern */
M2C_UNK func_080971AC(s32);                         /* extern */
M2C_UNK func_080981F0(s32, s32, s32, s32, s32);     /* extern */
M2C_UNK func_080986B4(s32);                         /* extern */
M2C_UNK func_08098BB4(M2C_UNK);                     /* extern */
M2C_UNK func_080AC6B8(s32);                         /* extern */
M2C_UNK func_080AC6FC(s32);                         /* extern */
M2C_UNK func_080AC87C(s32, s32);                    /* extern */
M2C_UNK func_080B0354(s32, s32);                    /* extern */
M2C_UNK func_080B65E4(s32);                         /* extern */
M2C_UNK func_080B6728();                            /* extern */
M2C_UNK func_080ED17C(s32);                         /* extern */

void sub_080B0980(void) {
    volatile s32 outgoing_reserve0;
    volatile s32 outgoing_reserve1;
    volatile s32 outgoing_reserve2;
    volatile s32 outgoing_reserve3;
    u8 *sp14;
    u8 *sp18;
    register s32 *incoming_r10 asm("r10");
    s32 *var_r7;
    register s32 state_1200 asm("r10");
    register s32 *var_r8 asm("r8");
    register s32 var_r6 asm("r6");
    register s32 var_r9 asm("r9");
    u8 temp_r0;
    u8 temp_r0_2;

    asm volatile("" : "=m"(outgoing_reserve0), "=m"(outgoing_reserve1),
                 "=m"(outgoing_reserve2), "=m"(outgoing_reserve3),
                 "=m"(sp14), "=m"(sp18), "=r"(var_r7)
                 : "r"(incoming_r10));
    var_r9 = 0;
    var_r6 = 0;
    state_1200 = 0x1200;
loop_1:
    if (var_r6 == state_1200) {
        goto state_1200_handler;
    }
    if (var_r6 > state_1200) {
        goto above_1200;
    }
    {
        register s32 state_1000 asm("r4") = 0x1000;

        if (var_r6 == state_1000) {
            goto state_1000_handler;
        }
        if (var_r6 > state_1000) {
            goto between_1000_1200;
        }
    }
    if (var_r6 == 0) {
        goto state_0_handler;
    }
    goto block_62;

between_1000_1200:
    if (var_r6 == 0x1100) {
        goto state_1100_handler;
    }
    goto block_62;

above_1200:
    if (var_r6 == 0x2100) {
        goto state_2100_handler;
    }
    if (var_r6 > 0x2100) {
        goto above_2100;
    }
    if (var_r6 == 0x2000) {
        goto state_2000_handler;
    }
    goto block_62;

above_2100:
    if (var_r6 == 0x2200) {
        goto state_2200_handler;
    }
    goto block_62;

state_0_handler:
        func_08098BB4(0x080020A3);
        func_080B65E4(0);
        func_080AC6B8(3);
        func_080B6728();
        func_080AC6FC(5);
        asm volatile(
            "mov r0, #4\n\t"
            "str r0, [sp, #0]\n\t"
            "mov r0, #188\n\t"
            "lsl r0, r0, #2\n\t"
            "str r0, [sp, #4]\n\t"
            "mov r0, #15\n\t"
            "str r0, [sp, #8]\n\t"
            "mov r0, #32\n\t"
            "str r0, [sp, #12]\n\t"
            "str r6, [sp, #16]"
            : : : "r0", "r1", "r2", "memory");
        var_r8 = func_08094484(0x0810580C, 0x08105838, 0, 0);
        {
            register u32 zero_r2 asm("r2") = 0;

            sp18 = (u8 *)zero_r2;
        }
        {
            register u32 zero_r3 asm("r3") = 0;

            sp14 = (u8 *)zero_r3;
        }
        goto block_61;
state_1000_handler: {
        register u8 menu_flag asm("r1") = *(u8 *)0x02032411;

        if (menu_flag != 0) {
            register s32 outgoing_r0 asm("r0");

            asm volatile(
                "mov %0, #152\n\t"
                "str %0, [sp, #0]"
                : "=r"(outgoing_r0) : : "memory");
            outgoing_r0 = 0x343;
            asm volatile(
                "str %0, [sp, #4]\n\t"
                "mov %0, #15\n\t"
                "str %0, [sp, #8]\n\t"
                "mov %0, #8\n\t"
                "str %0, [sp, #12]\n\t"
                "mov %0, #0\n\t"
                "str %0, [sp, #16]"
                : "+r"(outgoing_r0) : : "r1", "memory");
            var_r7 = func_08094484(0x08105A20, 0x08105A2C, 0, 0xD8);
            var_r6 = 0x1100;
        } else {
            asm volatile(
                "mov r0, #152\n\t"
                "str r0, [sp, #0]\n\t"
                "mov r0, #211\n\t"
                "lsl r0, r0, #2\n\t"
                "str r0, [sp, #4]\n\t"
                "mov r0, #15\n\t"
                "str r0, [sp, #8]\n\t"
                "mov r0, #8\n\t"
                "str r0, [sp, #12]\n\t"
                "str r1, [sp, #16]"
                : : "r"(menu_flag) : "r0", "memory");
            var_r7 = func_08094484(0x08105AC0, 0x08105ACC, 0, 0xD0);
            var_r6 = state_1200;
        }
    }
        goto block_62;
state_1100_handler: {
        register u32 table_base asm("r4") = 0x0203237A;
        {
            register u32 selector asm("r1") = (u32)sp14;
            register u32 address asm("r0");

            asm volatile("" : "+r"(table_base));
            address = selector + table_base;
            func_080AC87C((*(u8 *)address * 0xC) + 0x087B1E04, 4);
        }
        func_08098BB4(0x08002123);
        {
            register u32 selection asm("r3") = *(u8 *)0x0200A880;

            sp14 = (u8 *)selection;
        }
        temp_r0_2 = *(u8 *)0x0200A882;
        switch (temp_r0_2) {                        /* switch 2; irregular */
        case 0:                                     /* switch 2 */
        {
            register u32 flags asm("r0") = *(u16 *)0x0200A884;
            register u32 mask_r2 asm("r2") = 0x80;
            register u32 mask_r1 asm("r1");

            mask_r2 <<= 1;
            asm volatile("" : "+r"(mask_r2));
            mask_r1 = mask_r2;
            asm volatile("" : "+r"(mask_r1));
            if (!(flags & mask_r1)) {

            } else {
                func_08094554(var_r7);
                goto block_38;
            }
        }
            goto block_62;
        case 1:                                     /* switch 2 */
            {
                register s32 *modal_flags asm("r3") = var_r8;

                *modal_flags |= 0x20000;
            }
            *var_r7 |= 0x20000;
            func_080B0354((M2C_FIELD(*(u8 *)0x0200A880, u8 *, table_base) * 0x38) + 0x087AFCC4, 0);
            {
                register s32 *modal_load asm("r1");
                register s32 flags asm("r0");
                register s32 mask asm("r1");
                register s32 *modal_store asm("r2");

                modal_load = var_r8;
                flags = *modal_load;
                mask = 0xFFFDFFFF;
                flags &= mask;
                modal_store = var_r8;
                *modal_store = flags;
            }
            *var_r7 &= 0xFFFDFFFF;
            goto block_62;
        case 2:                                     /* switch 2 */
            goto action_2;
        }
        goto block_62;
}
state_1200_handler:
        func_080971AC(3);
        func_080971AC(4);
        func_08098BB4(0x08002134);
        {
            volatile u16 *keys = (volatile u16 *)0x0300000E;
            register u32 mask_seed asm("r3") = 0x103;
            register u32 mask asm("r4");

            asm volatile("" : "+r"(mask_seed));
            mask = mask_seed;
            do {
                func_080ED17C(1);
            } while (!(*keys & mask));
        }
        func_08098BB4(0x0800216C);
        func_08094554(var_r7);
        if (3 & *(u16 *)0x0300000E) {
            func_08094554(var_r8);
            func_08098BB4(0x0800212B);
            var_r9 = 1;
            asm volatile("");
            goto block_58;
        }
        goto block_38;
block_38:
        func_08092E84(0x41);
        var_r6 = 0x2000;
        goto block_62;
state_2000_handler: {
        u8 next_state_flag;

        asm volatile(
            "mov r0, #152\n\t"
            "str r0, [sp, #0]\n\t"
            "mov r0, #211\n\t"
            "lsl r0, r0, #2\n\t"
            "str r0, [sp, #4]\n\t"
            "mov r0, #15\n\t"
            "str r0, [sp, #8]\n\t"
            "mov r0, #8\n\t"
            "str r0, [sp, #12]\n\t"
            "mov r0, #0\n\t"
            "str r0, [sp, #16]"
            : : : "r0", "r1", "r2", "memory");
        var_r7 = func_08094484(
            ({ register s32 arg asm("r0") = 0x08105AC0;
               asm volatile("" : "+r"(arg)); arg; }),
            ({ register s32 arg asm("r1") = 0x08105ACC;
               asm volatile("" : "+r"(arg)); arg; }),
            0, 0xD0);
        next_state_flag = *(u8 *)0x0203246B;
        var_r6 = 0x2200;
        if (next_state_flag != 0) {
            var_r6 = 0x2100;
        }
        goto block_62;
    }
state_2100_handler:
        func_080986B4(6);
        {
            register u32 table_base asm("r1") = 0x087EEFC8;
            register u32 selector_base asm("r0") = 0x02032412;
            register u32 selector asm("r2") = (u32)sp18;
            s32 child;

            asm volatile("" : "+r"(table_base));
            asm volatile("" : "+r"(selector_base));
            asm volatile("add %0, %1, %0"
                         : "+r"(selector_base) : "r"(selector));
            selector_base = *(u8 *)selector_base;
            selector_base <<= 2;
            selector_base += table_base;
            child = *(s32 *)selector_base;
            func_080981F0(child, 0, 6, 0, 0);
        }
        func_08098BB4(0x08002127);
        sp18 = (u8 *)(u32)*(u8 *)0x0200A880;
        temp_r0 = *(u8 *)0x0200A882;
        switch (temp_r0) {                          /* switch 3; irregular */
        case 0:                                     /* switch 3 */
        {
            register u32 flags asm("r0") = *(u16 *)0x0200A884;
            register u32 mask_r3 asm("r3") = 0x80;
            register u32 mask_r1 asm("r1");

            mask_r3 <<= 2;
            asm volatile("" : "+r"(mask_r3));
            mask_r1 = mask_r3;
            asm volatile("" : "+r"(mask_r1));
            if (flags & mask_r1) {
                func_080971AC(4);
                func_08094554(var_r7);
                goto block_60;
            }
        }
            goto block_62;
        case 1:                                     /* switch 3 */
            func_08092E84(0x3F);
        case 2:                                     /* switch 3 */
action_2:
            func_08094554(var_r8);
            func_08094554(var_r7);
            func_08098BB4(0x0800212B);
            return;
        }
        goto block_62;
state_2200_handler:
        func_080971AC(5);
        func_080971AC(6);
        func_08098BB4(0x0800216F);
        {
            register volatile u16 *keys asm("r5") =
                (volatile u16 *)0x0300000E;
            register u32 mask_seed asm("r0") = 0x203;
            register u32 mask asm("r4");

            asm volatile("" : "+r"(mask_seed));
            mask = mask_seed;
            do {
                func_080ED17C(1);
            } while (!(*keys & mask));
        }
        func_08098BB4(0x080021A3);
        func_08094554(var_r7);
        if (3 & *(u16 *)0x0300000E) {
            func_08094554(var_r8);
            func_08098BB4(0x0800212B);
            var_r9 = 1;
            goto block_58;
        }
        goto block_60;
block_58:
        func_08092E84(0x3F);
        goto block_62;
block_60:
        func_08092E84(0x41);
block_61:
        var_r6 = 0x1000;
        goto block_62;
block_62:
        {
            register s32 completion asm("r2") = var_r9;

            asm volatile("" : "+r"(completion));
            if (completion == 0) {
                goto loop_1;
            }
        }
        return;
    /* bug: did not emit code for node #47; contents below: */
    /* bug: did not emit code for node #48; contents below: */
}
