#include "m2c_prelude.h"

s32 func_08092E84(s32);                             /* extern */
s32 func_080972C8();                                /* extern */
s32 func_080981F0(s32, s32, s32, s32, s32);         /* extern */
s32 func_08098248(s32, s32, s32);                   /* extern */
s32 func_08098514(s32, s32, s32, s32, u32, s32);    /* extern */
s32 func_08098754(s32);                             /* extern */
s32 func_08098BB4(s32);                             /* extern */
s32 func_080C0930(s32);                             /* extern */
s32 func_080C0A9C(u8);                              /* extern */
u8 func_080C0C54(s32, s32, s32);                    /* extern */
s32 func_080E6664(s32);                             /* extern */
void *func_080E669C();                              /* extern */
s32 func_080E66B8();                                /* extern */
s32 func_080E74F0(s32, s32, s32);                   /* extern */
s32 func_080E7B64(s32);                             /* extern */
s32 func_080E8C90(s32, u32, u8, s32, void *);       /* extern */
s32 func_080E9D88(s32, u32);                        /* extern */
s32 func_080ED17C(s32);                             /* extern */
M2C_UNK jtbl_080C148C();                            /* static */
extern u8 D_000002C2[];
extern u8 D_000002C6[];
extern u8 D_000002CA[];

typedef struct {
    u16 unk0;
    u16 flags;
    u32 attributes;
} Case43Scratch;

s32 sub_080C1414(void) {
    s32 temp_r0_4;
    s32 var_r4;
    u32 temp_r0_3;
    u32 var_r4_10;
    u32 var_r4_11;
    u32 var_r4_12;
    u32 var_r4_13;
    u32 var_r4_14;
    u32 var_r4_2;
    u32 var_r4_3;
    u32 var_r4_5;
    u32 var_r4_6;
    u32 var_r4_7;
    u32 var_r4_8;
    u32 var_r4_9;
    u8 temp_r0;
    u8 temp_r0_2;
    u8 temp_r0_5;
    u8 temp_r0_6;
    u8 temp_r0_7;
    u8 temp_r0_8;
    u8 temp_r1_2;
    u8 temp_r1_3;
    u8 temp_r1_4;
    u8 temp_r1_5;
    u8 temp_r1_6;
    u8 temp_r1_7;
    u8 temp_r1_8;
    register u32 var_r4_4 asm("r4");
    u8 var_r5;
    register u8 *dispatch_base asm("r0");
    register u8 *dispatch_index_ptr asm("r1");
    register u32 dispatch_offset asm("r2");
    register u32 dispatch_index asm("r1");
    register u8 *exit_base asm("r1");
    register u8 *exit_index_ptr asm("r2");
    register u32 exit_offset asm("r3");
    register u32 exit_index asm("r0");
    register u32 exit_dest_offset asm("r2");
    register s32 case23_addr asm("r0");
    register s32 case23_base asm("r1");
    register u8 *case44_base asm("r4");
    register u32 case44_offset asm("r3");
    register u8 *case44_addr asm("r0");
    register u32 case44_status_offset asm("r1");
    register u8 *case40_state asm("r1");
    register u8 *case20_state asm("r0");
    register Case43Scratch *case43_temp asm("r2");
    register u32 case43_attrs asm("r1");
    register u32 case43_mask asm("r0");
    register u8 *case1_base asm("r2");
    register u32 case1_mask asm("r3");
    register u8 *case1_addr asm("r1");
    u8 *case0_records;
    u8 *case33_records;
    u8 *case33_records2;
    u32 case43_row_offset;
    u8 *case43_records;
    register Case43Scratch *temp_r8 asm("r8");

    temp_r8 = func_080E669C();
    func_08098BB4(0x08019A46);
    func_08098BB4(0x08019A4E);
    func_080C0930(1);
loop_1:
    func_08098BB4(0x08019A82);
    temp_r0 = *(u8 *)0x0200A882;
    if (temp_r0 == 1) {
        dispatch_base = (u8 *)0x02034B4C;
        asm volatile("" : "+r"(dispatch_base));
        dispatch_index_ptr = (u8 *)0x0200A880;
        asm volatile("" : "+r"(dispatch_index_ptr));
        dispatch_offset = 0x27B4;
        asm volatile("" : "+r"(dispatch_offset));
        dispatch_base += dispatch_offset;
        asm volatile("" : "+r"(dispatch_base));
        dispatch_index = *dispatch_index_ptr;
        dispatch_index = (u32)dispatch_base + dispatch_index;
        temp_r0_2 = *(u8 *)dispatch_index;
        if (temp_r0_2 != 0) {
            temp_r0_3 = temp_r0_2 - 4;
            switch (temp_r0_3) {
            case 0:
            case 29:
                var_r4_2 = 0;
                case0_records = (u8 *)0x02034B4C;
                asm volatile("" : "+r"(case0_records));
                while (var_r4_2 <= 5U) {
                    if (((func_080E9D88(0, var_r4_2) << 0x18) != 0) &&
                        (M2C_FIELD(((var_r4_2 * 0x270) + 112), u8 *,
                                   (u32)case0_records) == 1)) {
                        break;
                    }
                    var_r4_2 = (u32) (u8) (var_r4_2 + 1);
                }
                if (var_r4_2 == 6) {
                    func_08098514(1, 4, 5, 0x16, var_r4_2, 0);
                    func_08098248(0x08107164, 0, 1);
                    func_080981F0(func_080E7B64(1), 0, 1, 0xC, 0);
                    func_080972C8();
                    do {
                        func_080ED17C(1);
                    } while (!(3 & *(u16 *)0x0300000E));
                    goto block_250;
                }
                goto block_252;
            default:
                goto block_252;
            case 1:
                var_r4_3 = 0;
                case0_records = (u8 *)0x02034B4C;
                asm volatile("" : "+r"(case0_records));
                while (var_r4_3 <= 5U) {
                    if (((func_080E9D88(0, var_r4_3) << 0x18) != 0) &&
                        (M2C_FIELD(((var_r4_3 * 0x270) + 112), u8 *,
                                   (u32)case0_records) == 1)) {
                        break;
                    }
                    var_r4_3 = (u32) (u8) (var_r4_3 + 1);
                }
                if (var_r4_3 == 6) {
                    func_08098514(1, 4, 5, 0x16, var_r4_3, 0);
                    func_08098248(0x08107164, 0, 1);
                    func_080981F0(func_080E7B64(1), 0, 1, 0xC, 0);
                    func_080972C8();
                    do {
                        func_080ED17C(1);
                    } while (!(3 & *(u16 *)0x0300000E));
                    goto block_250;
                }
                var_r4_4 = 0;
                case1_base = (u8 *)0x02034B4C;
                asm volatile("" : "+r"(case1_base));
                case1_mask = 8;
                asm volatile("" : "+r"(case1_mask));
loop_28:
                case23_addr = var_r4_4 * 0x270;
                asm volatile("" : "+r"(case23_addr));
                case1_addr = (u8 *)((u32)case23_addr + (u32)case1_base);
                asm volatile("" : "+r"(case1_addr));
                if ((*case1_addr == 0) || !({ case43_attrs = *(u16 *)(case1_addr + 4); asm volatile("" : "+r"(case43_attrs)); case43_mask = case1_mask; asm volatile("" : "+r"(case43_mask)); case43_mask & case43_attrs; })) {
                    case23_addr = var_r4_4 + 1;
                    asm volatile("" : "+r"(case23_addr));
                    var_r4_4 = (u32)(u8)case23_addr;
                    if ((u32) var_r4_4 <= 5U) {
                        goto loop_28;
                    }
                }
                if (var_r4_4 == 6) {
                    func_08098514(1, 6, 4, 0x12, 8U, 0);
                    func_08098248(0x08107194, 0, 1);
                    func_08098248(0x081071CC, 0, 1);
                    func_080972C8();
                    do {
                        func_080ED17C(1);
                    } while (!(3 & *(u16 *)0x0300000E));
                    goto block_250;
                }
                goto block_252;
            case 4:
                var_r4_5 = 3;
                while (var_r4_5 <= 5U) {
                    if ((func_080E9D88(0, var_r4_5) << 0x18) != 0) {
                        break;
                    }
                    var_r4_5 = (u32) (u8) (var_r4_5 + 1);
                }
                if (var_r4_5 == 6) {
                    func_08098514(1, 6, 4, 0x12, 8U, 0);
                    func_08098248(0x081071EC, 0, 1);
                    func_08098248(0x08107210, 0, 1);
                    func_080972C8();
                    do {
                        func_080ED17C(1);
                    } while (!(3 & *(u16 *)0x0300000E));
                    goto block_250;
                }
                goto block_252;
            case 20:
            case 21:
            case 22:
                var_r4_6 = 0;
                while (var_r4_6 <= 5U) {
                    if (((func_080E9D88(0, var_r4_6) << 0x18) != 0) &&
                        ((func_080E74F0((var_r4_6 * 0x270) + 0x02034BBC,
                                       0x11, 0) << 0x10) != 0)) {
                        break;
                    }
                    var_r4_6 = (u32) (u8) (var_r4_6 + 1);
                }
                if (var_r4_6 == 6) {
                    func_08098514(1, 6, 4, 0x12, 8U, 0);
                    func_08098248(0x08107240, 0, 1);
                    func_08098248(0x0810727C, 0, 1);
                    func_080972C8();
                    do {
                        func_080ED17C(1);
                    } while (!(3 & *(u16 *)0x0300000E));
                    goto block_250;
                }
                case20_state = (u8 *)0x0203055C;
                asm volatile("" : "+r"(case20_state));
                if ((u32) (u8) (case20_state[5] - 7) <= 2U) {
                    func_08098514(1, 7, 4, 0x10, 8U, 0);
                    func_08098248(0x08107290, 0, 1);
                    func_08098248(0x081072C8, 0, 1);
                    func_080972C8();
                    do {
                        func_080ED17C(1);
                    } while (!(3 & *(u16 *)0x0300000E));
                    goto block_250;
                }
                goto block_252;
            case 23:
            case 24:
                var_r4_7 = 0;
                while (var_r4_7 <= 5U) {
                    if ((func_080E9D88(0, var_r4_7) << 0x18) != 0) {
                        case23_addr = var_r4_7 * 0x270;
                        asm volatile("" : "+r"(case23_addr));
                        case23_base = 0x02034BBC;
                        asm volatile("" : "+r"(case23_base));
                        case23_addr += case23_base;
                        asm volatile("" : "+r"(case23_addr));
                        if ((func_080E74F0(case23_addr, 0x13, 0) << 0x10) != 0) {
                            break;
                        }
                    }
                    var_r4_7 = (u32) (u8) (var_r4_7 + 1);
                }
                if (var_r4_7 == 6) {
                    func_08098514(1, 6, 4, 0x12, 8U, 0);
                    func_08098248(0x081072E8, 0, 1);
                    func_08098248(0x08107324, 0, 1);
                    func_080972C8();
                    do {
                        func_080ED17C(1);
                    } while (!(3 & *(u16 *)0x0300000E));
                    goto block_250;
                }
                goto block_252;
            case 25:
            case 26:
            case 27:
                var_r4_8 = 0;
                while (var_r4_8 <= 5U) {
                    if ((func_080E9D88(0, var_r4_8) << 0x18) != 0) {
                        case23_addr = var_r4_8 * 0x270;
                        asm volatile("" : "+r"(case23_addr));
                        case23_base = 0x02034BBC;
                        asm volatile("" : "+r"(case23_base));
                        case23_addr += case23_base;
                        asm volatile("" : "+r"(case23_addr));
                        if ((func_080E74F0(case23_addr, 0x12, 0) << 0x10) != 0) {
                            break;
                        }
                    }
                    var_r4_8 = (u32) (u8) (var_r4_8 + 1);
                }
                if (var_r4_8 == 6) {
                    func_08098514(1, 6, 4, 0x12, 8U, 0);
                    func_08098248(0x08107338, 0, 1);
                    func_08098248(0x08107324, 0, 1);
                    func_080972C8();
                    do {
                        func_080ED17C(1);
                    } while (!(3 & *(u16 *)0x0300000E));
                    goto block_250;
                }
                goto block_252;
            case 33:
                var_r4_9 = 0;
                case33_records = (u8 *)0x02034B4C;
                asm volatile("" : "+r"(case33_records));
loop_76:
                if (((func_080E9D88(0, var_r4_9) << 0x18) == 0) || ((temp_r0_5 = M2C_FIELD(((var_r4_9 * 0x270) + 112), u8 *, (u32)case33_records), (temp_r0_5 != 0xE)) && (temp_r0_5 != 0x16))) {
                    var_r4_9 = (u32) (u8) (var_r4_9 + 1);
                    if (var_r4_9 <= 5U) {
                        goto loop_76;
                    }
                }
                if (var_r4_9 == 6) {
                    func_08098514(1, 4, 5, 0x16, var_r4_9, 0);
                    func_08098248(0x08107374, 0, 1);
                    func_08098248(0x08107394, 0, 1);
                    func_080972C8();
                    do {
                        func_080ED17C(1);
                    } while (!(3 & *(u16 *)0x0300000E));
                    goto block_250;
                }
                var_r4_10 = 0;
                case33_records2 = (u8 *)0x02034B4C;
                asm volatile("" : "+r"(case33_records2));
loop_86:
                if (((func_080E9D88(0, var_r4_10) << 0x18) == 0) || ((temp_r0_6 = M2C_FIELD(((var_r4_10 * 0x270) + 112), u8 *, (u32)case33_records2), (temp_r0_6 != 0xF)) && (temp_r0_6 != 0x17))) {
                    var_r4_10 = (u32) (u8) (var_r4_10 + 1);
                    if (var_r4_10 <= 5U) {
                        goto loop_86;
                    }
                }
                if (var_r4_10 <= 5U) {
                    func_08098514(1, 5, 5, 0x14, 6U, 0);
                    func_08098248(0x081073BC, 0, 1);
                    func_08098248(0x081073E0, 0, 1);
                    func_080972C8();
                    do {
                        func_080ED17C(1);
                    } while (!(3 & *(u16 *)0x0300000E));
                    goto block_250;
                }
                if ((func_080E6664(0x16) << 0x18) != 0) {
                    func_08098514(1, 7, 5, 0x10, 6U, 0);
                    func_08098248(0x08107400, 0, 1);
                    func_08098248(0x08107418, 0, 1);
                    func_080972C8();
                    do {
                        func_080ED17C(1);
                    } while (!(3 & *(u16 *)0x0300000E));
                    goto block_250;
                }
                goto block_252;
            case 34:
                var_r4_11 = 0;
                case0_records = (u8 *)0x02034B4C;
                asm volatile("" : "+r"(case0_records));
                while (var_r4_11 <= 5U) {
                    if (((func_080E9D88(0, var_r4_11) << 0x18) != 0) &&
                        (M2C_FIELD(((var_r4_11 * 0x270) + 112), u8 *,
                                   (u32)case0_records) == 1)) {
                        break;
                    }
                    var_r4_11 = (u32) (u8) (var_r4_11 + 1);
                }
                if (var_r4_11 == 6) {
                    func_08098514(1, 4, 5, 0x16, var_r4_11, 0);
                    func_08098248(0x08107164, 0, 1);
                    func_080981F0(func_080E7B64(1), 0, 1, 0xC, 0);
                    func_080972C8();
                    do {
                        func_080ED17C(1);
                    } while (!(3 & *(u16 *)0x0300000E));
                    goto block_250;
                }
                var_r4_12 = 0;
                case0_records = (u8 *)0x02034B4C;
                asm volatile("" : "+r"(case0_records));
loop_110:
                if (((func_080E9D88(0, var_r4_12) << 0x18) == 0) || ((temp_r0_7 = M2C_FIELD(((var_r4_12 * 0x270) + 112), u8 *, (u32)case0_records), (temp_r0_7 != 2)) && (temp_r0_7 != 0x60) && (temp_r0_7 != 0x61))) {
                    var_r4_12 = (u32) (u8) (var_r4_12 + 1);
                    if (var_r4_12 <= 5U) {
                        goto loop_110;
                    }
                }
                if (var_r4_12 <= 5U) {
                    func_08098514(1, 6, 5, 0x12, 6U, 0);
                    func_08098248(0x08107434, 0, 1);
                    func_08098248(0x081073E0, 0, 1);
                    func_080972C8();
                    do {
                        func_080ED17C(1);
                    } while (!(3 & *(u16 *)0x0300000E));
                    goto block_250;
                }
                if ((func_080E6664(0x16) << 0x18) != 0) {
                    func_08098514(1, 7, 5, 0x10, 6U, 0);
                    func_08098248(0x08107400, 0, 1);
                    func_08098248(0x08107418, 0, 1);
                    func_080972C8();
                    do {
                        func_080ED17C(1);
                    } while (!(3 & *(u16 *)0x0300000E));
                    goto block_250;
                }
                goto block_252;
            case 35: {
                register u32 case35_value asm("r1");

                if (((func_080C0C54(0, 0, 0) << 0x18) == 0) && ((func_080C0C54(0, 0, 1) << 0x18) == 0) && ((func_080C0C54(0, 0, 3) << 0x18) == 0)) {
                    case35_value = func_080C0C54(0, 0, 4);
                    if (case35_value != 0) {
                        asm volatile(".short (0xE000 | (((.Lsub_080C1414_block252 - . - 4) >> 1) & 0x7FF))");
                    }
                    func_08098514(1, 3, 5, 0x18, 6U, (s32) case35_value);
                    func_08098248(0x08107458, 0, 1);
                    func_08098248(0x08107484, 0, 1);
                    func_080972C8();
                    do {
                        func_080ED17C(1);
                    } while (!(3 & *(u16 *)0x0300000E));
                    goto block_250;
                }
                goto block_252;
            }
            case 36:
                if ((func_080C0C54(1, 0, 0) << 0x18) != 0) {
                    goto block_252;
                }
                temp_r1_2 = func_080C0C54(1, 0, 1);
                if (temp_r1_2 != 0) {
                    goto block_252;
                }
                func_08098514(1, 3, 5, 0x18, 6U, (s32) temp_r1_2);
                func_08098248(0x08107458, 0, 1);
                func_08098248(0x08107484, 0, 1);
                func_080972C8();
                do {
                    func_080ED17C(1);
                } while (!(3 & *(u16 *)0x0300000E));
                goto block_250;
            case 37:
                if ((func_080C0C54(2, 0, 0) << 0x18) != 0) {
                    goto block_252;
                }
                temp_r1_3 = func_080C0C54(2, 0, 1);
                if (temp_r1_3 != 0) {
                    goto block_252;
                }
                func_08098514(1, 3, 5, 0x18, 6U, (s32) temp_r1_3);
                func_08098248(0x08107458, 0, 1);
                func_08098248(0x08107484, 0, 1);
                func_080972C8();
                do {
                    func_080ED17C(1);
                } while (!(3 & *(u16 *)0x0300000E));
                goto block_250;
            case 38:
                temp_r1_4 = func_080C0C54(3, 0, 0);
                if (temp_r1_4 != 0) {
                    goto block_252;
                }
                func_08098514(1, 3, 5, 0x18, 6U, (s32) temp_r1_4);
                func_08098248(0x08107458, 0, 1);
                func_08098248(0x08107484, 0, 1);
                func_080972C8();
                do {
                    func_080ED17C(1);
                } while (!(3 & *(u16 *)0x0300000E));
                goto block_250;
            case 39:
                if ((func_080C0C54(6, 0, 3) << 0x18) != 0) {
                    goto block_252;
                }
                if ((func_080C0C54(6, 0, 4) << 0x18) != 0) {
                    goto block_252;
                }
                temp_r1_5 = func_080C0C54(6, 0, 5);
                if (temp_r1_5 != 0) {
                    goto block_252;
                }
                func_08098514(1, 3, 5, 0x18, 6U, (s32) temp_r1_5);
                func_08098248(0x08107458, 0, 1);
                func_08098248(0x08107484, 0, 1);
                func_080972C8();
                do {
                    func_080ED17C(1);
                } while (!(3 & *(u16 *)0x0300000E));
                goto block_250;
            case 40:
                var_r4_13 = 0;
                while (var_r4_13 <= 5U) {
                    if (((func_080E9D88(0, var_r4_13) << 0x18) != 0) &&
                        ((func_080E74F0((var_r4_13 * 0x270) + 0x02034BBC,
                                       0x11, 0) << 0x10) != 0)) {
                        break;
                    }
                    var_r4_13 = (u32) (u8) (var_r4_13 + 1);
                }
                if (var_r4_13 == 6) {
                    func_08098514(1, 6, 4, 0x12, 8U, 0);
                    func_08098248(0x08107240, 0, 1);
                    func_08098248(0x08107324, 0, 1);
                    func_080972C8();
                    do {
                        func_080ED17C(1);
                    } while (!(3 & *(u16 *)0x0300000E));
                    goto block_250;
                }
                case40_state = (u8 *)0x0203055C;
                asm volatile("" : "+r"(case40_state));
                if ((u32) (u8) (case40_state[5] - 7) <= 2U) {
                    func_08098514(1, 7, 4, 0x10, 8U, 0);
                    func_08098248(0x08107290, 0, 1);
                    func_08098248(0x081072C8, 0, 1);
                    func_080972C8();
                    do {
                        func_080ED17C(1);
                    } while (!(3 & *(u16 *)0x0300000E));
                    goto block_250;
                }
                if (((u32) case40_state[1] <= 0xDU) && (*(u8 *)0x02030664 == 0)) {
                    goto block_252;
                }
                func_08098514(1, 5, 5, 0x14, 6U, 0);
                func_08098248(0x081074A4, 0, 1);
                func_08098248(0x081074C8, 0, 1);
                func_080972C8();
                do {
                    func_080ED17C(1);
                } while (!(3 & *(u16 *)0x0300000E));
                goto block_250;
            case 41:
                if ((func_080C0C54(4, 0, 0) << 0x18) != 0) {
                    goto block_252;
                }
                if ((func_080C0C54(4, 0, 1) << 0x18) != 0) {
                    goto block_252;
                }
                temp_r1_6 = func_080C0C54(4, 0, 2);
                if (temp_r1_6 != 0) {
                    goto block_252;
                }
                func_08098514(1, 3, 5, 0x18, 6U, (s32) temp_r1_6);
                func_08098248(0x08107458, 0, 1);
                func_08098248(0x08107484, 0, 1);
                func_080972C8();
                do {
                    func_080ED17C(1);
                } while (!(3 & *(u16 *)0x0300000E));
                goto block_250;
            case 42:
                if (((func_080E9D88(0, 1U) << 0x18) != 0) && ((func_080E9D88(0, 3U) << 0x18) != 0) && ((func_080E9D88(0, 5U) << 0x18) != 0)) {
                    goto block_252;
                }
                func_08098514(1, 3, 5, 0x18, 6U, 0);
                func_08098248(0x08107458, 0, 1);
                func_08098248(0x081074E0, 0, 1);
                func_080972C8();
                do {
                    func_080ED17C(1);
                } while (!(3 & *(u16 *)0x0300000E));
                goto block_250;
            case 43:
            {
                u32 case43_address;
                u32 case43_scale;
                var_r5 = 0;
                var_r4_14 = 0;
loop_200:
                if ((func_080E9D88(0, var_r4_14) << 0x18) != 0) {
                    var_r5 = 0;
                    case43_scale = var_r4_14 << 2;
                    case43_records = (u8 *)0x02034B4C;
                    asm volatile("" : "+r"(case43_records));
                    case43_scale += var_r4_14;
                    case43_scale <<= 3;
                    case43_scale -= var_r4_14;
                    case43_row_offset = case43_scale << 4;
loop_202:
                    case43_address = (var_r5 * 4) + case43_row_offset;
                    case43_address += (u32)case43_records;
                    if ((M2C_FIELD(82, u16 *, case43_address) == 0) || (func_080E8C90(0, var_r4_14, var_r5, 0, ({ register Case43Scratch *case43_call_arg asm("r3") = temp_r8; asm volatile("" : "+r"(case43_call_arg)); case43_call_arg; })), ((1 & temp_r8->flags) != 0)) || ({ case43_temp = temp_r8; asm volatile("" : "+r"(case43_temp)); case43_attrs = case43_temp->attributes; asm volatile("" : "+r"(case43_attrs)); case43_mask = 0x10; asm volatile("" : "+r"(case43_mask)); case43_attrs & case43_mask; })) {
                        var_r5 += 1;
                        if ((u32) var_r5 <= 7U) {
                            goto loop_202;
                        }
                    }
                    if (var_r5 != 8) {
                        var_r4_14 = (u32) (u8) (var_r4_14 + 2);
                        if (var_r4_14 <= 5U) {
                            goto loop_200;
                        }
                    }
                }
                if (var_r4_14 > 5U) {
                    goto block_252;
                }
                if ((u32) var_r5 <= 7U) {
                    func_08098514(1, 3, 5, 0x18, 6U, 0);
                    func_08098248(0x08107458, 0, 1);
                    func_08098248(0x08107484, 0, 1);
                    func_080972C8();
                    do {
                        func_080ED17C(1);
                    } while (!(3 & *(u16 *)0x0300000E));
                } else {
                    func_08098514(1, 5, 4, 0x14, 8U, 0);
                    func_08098248(0x08107504, 0, 0);
                    func_08098248(0x0810752C, 1, 0);
                    func_08098248(0x08107550, 0, 0);
                    func_080972C8();
                    do {
                        func_080ED17C(1);
                    } while (!(3 & *(u16 *)0x0300000E));
                }
                goto block_250;
            }
            case 44:
                if ((func_080E9D88(0, 1U) << 0x18) == 0) {
                    goto case44_failure;
                }
                case44_base = (u8 *)0x02034B4C;
                asm volatile("" : "+r"(case44_base));
                case44_offset = 156;
                asm volatile("" : "+r"(case44_offset));
                case44_offset *= 4;
                asm volatile("" : "+r"(case44_offset));
                case44_addr = case44_base + case44_offset;
                asm volatile("" : "+r"(case44_addr));
                temp_r0_8 = *case44_addr;
                if ((temp_r0_8 != 0x30) && (temp_r0_8 != 0x8C)) {
                    goto case44_failure;
                }
                if ((func_080E9D88(0, 4U) << 0x18) == 0) {
                    goto case44_failure;
                }
                case44_status_offset = 0x9F8;
                asm volatile("" : "+r"(case44_status_offset));
                case44_addr = case44_base + case44_status_offset;
                asm volatile("" : "+r"(case44_addr));
                if ((u32)*case44_addr > 2U) {
                    goto case44_failure;
                }
                goto case44_success;
case44_failure:
                func_08098514(1, 3, 5, 0x18, 6U, 0);
                func_08098248(0x08107458, 0, 1);
                func_08098248(0x08107484, 0, 1);
                func_080972C8();
                do {
                    func_080ED17C(1);
                } while (!(3 & *(u16 *)0x0300000E));
                goto block_250;
case44_success:
                {
                register u32 case44_word_offset asm("r2") = (u32)D_000002C2;
                register u32 case44_word_address asm("r0");
                case44_word_address = (u32)case44_base + case44_word_offset;
                if (*(u16 *)case44_word_address == 0x56) {
                    goto block_252;
                }
                }
                {
                register u32 case44_word_offset asm("r3") = (u32)D_000002C6;
                register u32 case44_word_address asm("r0");
                case44_word_address = (u32)case44_base + case44_word_offset;
                if (*(u16 *)case44_word_address == 0x56) {
                    goto block_252;
                }
                }
                {
                register u32 case44_word_offset asm("r1") = (u32)D_000002CA;
                register u32 case44_word_address asm("r0");
                case44_word_address = (u32)case44_base + case44_word_offset;
                if (*(u16 *)case44_word_address == 0x56) {
                    goto block_252;
                }
                }
                asm volatile("" :: "r"(case44_base));
                func_08098514(1, 6, 4, 0x12, 8U, 0);
                func_08098248(0x0810756C, 0, 1);
                func_08098248(0x081075A0, 0, 1);
                func_080972C8();
                do {
                    func_080ED17C(1);
                } while (!(3 & *(u16 *)0x0300000E));
                goto block_250;
            case 46:
                if ((func_080C0C54(5, 0, 0) << 0x18) != 0) {
                    goto block_252;
                }
                if ((func_080C0C54(5, 0, 1) << 0x18) == 0) {
                    temp_r1_7 = func_080C0C54(5, 0, 2);
                    if (temp_r1_7 == 0) {
                        func_08098514(1, 3, 5, 0x18, 6U, (s32) temp_r1_7);
                        func_08098248(0x08107458, 0, 1);
                        func_08098248(0x08107484, 0, 1);
                        func_080972C8();
                        do {
                            func_080ED17C(1);
                        } while (!(3 & *(u16 *)0x0300000E));
                        goto block_250;
                    }
                }
                goto block_252;
            case 47:
                if (((func_080C0C54(7, 0, 0) << 0x18) == 0) && ((func_080C0C54(7, 0, 1) << 0x18) == 0) && ((func_080C0C54(7, 0, 3) << 0x18) == 0)) {
                    temp_r1_8 = func_080C0C54(7, 0, 4);
                    if (temp_r1_8 == 0) {
                        func_08098514(1, 3, 5, 0x18, 6U, (s32) temp_r1_8);
                        func_08098248(0x08107458, 0, 1);
                        func_08098248(0x08107484, 0, 1);
                        func_080972C8();
                        do {
                            func_080ED17C(1);
                        } while (!(3 & *(u16 *)0x0300000E));
                        goto block_250;
                    }
                }
                goto block_252;
            }
block_250:
            func_08098754(1);
            goto loop_1;
block_252:
            asm volatile(".Lsub_080C1414_block252:");
            exit_base = (u8 *)0x02034B4C;
            asm volatile("" : "+r"(exit_base));
            exit_index_ptr = (u8 *)0x0200A880;
            asm volatile("" : "+r"(exit_index_ptr));
            exit_offset = 0x27B4;
            asm volatile("" : "+r"(exit_offset));
            exit_index = (u32)exit_base + exit_offset;
            exit_index += *exit_index_ptr;
            temp_r0_2 = *(u8 *)exit_index;
            exit_dest_offset = 0xA07D;
            asm volatile("" : "+r"(exit_dest_offset));
            exit_base += exit_dest_offset;
            *exit_base = temp_r0_2;
            var_r4 = 1;
            goto block_254;
        } else {
            goto loop_1;
        }
    } else {
        if (temp_r0 != 2) {
            if (8 & *(u16 *)0x0200A884) {
                func_08092E84(0x41);
                dispatch_base = (u8 *)0x02034B4C;
                asm volatile("" : "+r"(dispatch_base));
                dispatch_index_ptr = (u8 *)0x0200A880;
                asm volatile("" : "+r"(dispatch_index_ptr));
                exit_offset = 0x27B4;
                asm volatile("" : "+r"(exit_offset));
                dispatch_base += exit_offset;
                dispatch_index = *dispatch_index_ptr;
                dispatch_base += dispatch_index;
                func_080C0A9C(*dispatch_base);
            }
            goto loop_1;
        }
        var_r4 = 0;
    }
block_254:
    func_08098BB4(0x08019A86);
    func_080E66B8();
    return var_r4;
}
