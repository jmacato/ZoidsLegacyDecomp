#include "m2c_prelude.h"

void func_08094330(void);
s32 func_08094374(s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_08094554(void);
void *func_08095098(s32, s32, s32);
void func_08098BB4(s32);
void func_0809A5B4(u8, u8, s32, s32, s32);
void func_0809AA64(s32, s32, s32, s32);
void func_080A016C(u8, s32, s32);
void func_080CB340(s32, u8);
void func_080D0AF0(s32);
void func_080D12A0(s32, s32);

s32 sub_080A321C(u32 arg0, void **arg1) {
    register void **request asm("r6") = arg1;
    register u32 source asm("r9");
    register u8 *record_base asm("r3");
    u8 *pending;
    s32 var_r3;
    s32 temp_r4;
    u32 var_r2;
    u8 temp_r0;
    u8 temp_r1;
    register s32 temp_r1_2 asm("r1");
    void *temp_r0_2;
    register void *var_r5 asm("r5");

    asm volatile("" : "+r"(request));
    source = (u8)arg0;
    var_r2 = 1;
    record_base = (u8 *)0x02027378;
    var_r5 = record_base + 0x40;
    goto check_record;
next_record:
    var_r2 += 1;
    if (var_r2 > 0x34U) {
        goto finish;
    }
    {
        register u32 record_offset asm("r0") = var_r2 << 6;
        asm volatile(
            "add r5, r0, r3"
            : "=r"(var_r5)
            : "r"(record_offset), "r"(record_base)
            : "cc");
    }
check_record:
    if (M2C_FIELD(var_r5, u8 *, 0) != M2C_FIELD(*request, u8 *, 1)) {
        goto next_record;
    }
    if (var_r2 > 0x34U || M2C_FIELD(var_r5, u8 *, 1) == 0) {
        goto finish;
    }
    {
            register u8 *menu asm("r4");
            register u32 menu_entry asm("r0");
            func_08094330();
            *(s32 *)0x02031744 = 0;
            menu_entry = M2C_FIELD(var_r5, u8 *, 1) * 0x70;
            menu = (u8 *)0x020218E8;
            asm volatile("" : "+r"(menu_entry), "+r"(menu));
            func_080CB340((u8 *)menu_entry + (u32)menu,
                M2C_FIELD(*request, u8 *, 2));
            *(u8 *)0x02033F36 = M2C_FIELD(*request, u8 *, 2);
            {
                u8 *coordinate_destination = (u8 *)0x020317D6;
                asm volatile("" : "+r"(coordinate_destination));
                menu -= 4;
                *coordinate_destination =
                    menu[M2C_FIELD(var_r5, u8 *, 1) * 0x70 + 4];
            }
            {
                void *flags_request;
                var_r2 = 0x020317D7;
                asm volatile("" : "+r"(var_r2));
                flags_request = *request;
                temp_r1 = M2C_FIELD(flags_request, u8 *, 3);
                asm volatile("" : "+r"(flags_request));
                *(u8 *)var_r2 = temp_r1;
            }
            {
                u32 flags_test = 2;
                asm volatile("" : "+r"(flags_test));
                flags_test &= temp_r1;
                if (flags_test == 0) {
                    func_080D0AF0(0x10);
                } else {
                    func_080D0AF0(0xFFFFFF00);
                    func_080D12A0(2, 0);
                }
            }
            {
                register u8 *state asm("r0");
                register u8 *graphics asm("r3");
                u8 state_value;
                state = (u8 *)0x0203055C;
                state_value = state[2];
                graphics = (u8 *)0x087AFCC4;
                asm volatile("" : "+r"(graphics));
                var_r5 = (void *)0x020317D6;
                func_0809A5B4(state_value,
                    graphics[*(u8 *)var_r5 * 0x38 + 2], 3, 2, 1);
            }
            temp_r4 = 1 & *(u8 *)0x020317D7;
            if (temp_r4 != 0) {
                register u8 *object_data asm("r4");
                register u8 *coordinates asm("r2");
                s32 coordinate_y;
                func_0809AA64(0x087ACCB8, 0, 0x380, 0xE);
                object_data = (u8 *)0x087ACDD8;
                if (*(u8 *)0x02033F36 == 0) {
                    register u8 *coordinate_seed asm("r0") = (u8 *)0x087EB08C;
                    register s32 coordinate_x asm("r3");
                    asm volatile(
                        "ldrb r1, [r5, #0]\n\t"
                        "lsl r1, r1, #5\n\t"
                        "add r2, r0, #4\n\t"
                        "add r1, r1, r2\n\t"
                        "mov r2, #0\n\t"
                        "ldrsh r3, [r1, r2]\n\t"
                        "add r2, r0, #0"
                        : "=r"(coordinate_x), "=r"(coordinates), "+r"(coordinate_seed)
                        : "r"(var_r5)
                        : "r1", "cc", "memory");
                    var_r3 = coordinate_x;
                } else {
                    register u8 *coordinate_seed asm("r2") = (u8 *)0x087EB08C;
                    register s32 coordinate_x asm("r3");
                    asm volatile(
                        "ldrb r0, [r5, #0]\n\t"
                        "lsl r0, r0, #5\n\t"
                        "add r1, r2, #4\n\t"
                        "add r0, r0, r1\n\t"
                        "ldrh r1, [r0, #0]\n\t"
                        "mov r3, #128\n\t"
                        "lsl r3, r3, #1\n\t"
                        "add r0, r3, #0\n\t"
                        "sub r0, r0, r1\n\t"
                        "lsl r0, r0, #16\n\t"
                        "asr r3, r0, #16"
                        : "=r"(coordinate_x), "+r"(coordinate_seed)
                        : "r"(var_r5)
                        : "r0", "r1", "cc", "memory");
                    var_r3 = coordinate_x;
                    coordinates = coordinate_seed;
                }
                {
                    register u32 y_carrier asm("r0") = 0x020317D6;
                    asm volatile(
                        "ldrb r0, [r0, #0]\n\t"
                        "lsl r0, r0, #5\n\t"
                        "add r1, r2, #6\n\t"
                        "add r0, r0, r1\n\t"
                        "mov r1, #0\n\t"
                        "ldrsh r0, [r0, r1]"
                        : "+r"(y_carrier)
                        : "r"(coordinates)
                        : "r1", "cc", "memory");
                    coordinate_y = (s32)y_carrier;
                }
                *(s32 *)0x02033F4C = func_08094374(
                    (s32)object_data, 0x58, 0, var_r3,
                    coordinate_y,
                    0x380, 0xE,
                    ({
                        register s32 script asm("r0");
                        if (*(u8 *)0x02033F36 != 0) {
                            script = 0x9248;
                        } else {
                            script = 0x1248;
                        }
                        asm volatile("" : "+r"(script));
                        script;
                    }),
                    0x080DB965);
            } else {
                *(s32 *)0x02033F4C = temp_r4;
            }
            if (*(u8 *)0x02031748 == 0) {
                func_08098BB4(0x08004057);
                if (*(u8 *)0x02033F36 == 0) {
                    func_08098BB4(0x08004037);
                } else {
                    func_08098BB4(0x08004047);
                }
            } else {
                if (*(s32 *)0x02031744 != 0) {
                    func_08094554();
                    *(s32 *)0x02031744 = 0;
                }
                temp_r0 = *(u8 *)0x02030666;
                if (temp_r0 != 0) {
                    if (temp_r0 == 1) {
                        func_08098BB4(0x080177F5);
                    } else {
                        func_08098BB4(0x080177FA);
                    }
                    func_08098BB4(0x080177FD);
                    *(u8 *)0x02030666 = 0;
                }
            }
            {
                register u32 pending_value asm("r2");
                pending = (u8 *)0x020317D8;
                asm volatile("" : "+r"(pending));
                temp_r1_2 = *pending;
                pending_value = temp_r1_2;
                asm volatile("" : "+r"(pending_value));
                if (pending_value != 0) {
                    register u8 *work asm("r5") = (u8 *)0x02034B4C;
                    register u8 *side asm("r6") = (u8 *)0x02033F36;
                    register u8 *destination asm("r0");
                    register u8 *coordinate_base asm("r3");
                    register u8 *coordinate_index asm("r4");
                    register void *object asm("r0");
                    register s32 zero asm("r8");

                    asm volatile("" : "+r"(work), "+r"(side));
                    destination = (u8 *)(u32)*side;
                    work += 0x27BE;
                    asm volatile(
                        "add r0, r0, r5"
                        : "+r"(destination)
                        : "r"(work)
                        : "cc");
                    temp_r1_2 += 0xCC;
                    asm volatile(
                        "mov r3, #0\n\t"
                        "mov r8, r3"
                        : "=r"(zero)
                        :
                        : "r3");
                    *destination = temp_r1_2;
                    temp_r0_2 = func_08095098(0, 0x080CCF3D, 0x080CCF61);
                    *(void **)0x020316F8 = temp_r0_2;
                    object = temp_r0_2;
                    coordinate_base = (u8 *)0x087EB08C;
                    coordinate_index = (u8 *)0x020317D6;
                    asm volatile(
                        "ldrb r1, [r4, #0]\n\t"
                        "lsl r1, r1, #5\n\t"
                        "add r2, r3, #0\n\t"
                        "add r2, #16\n\t"
                        "add r1, r1, r2\n\t"
                        "mov r2, #0\n\t"
                        "ldrsh r1, [r1, r2]\n\t"
                        "str r1, [r0, #4]\n\t"
                        "ldrb r1, [r4, #0]\n\t"
                        "lsl r1, r1, #5\n\t"
                        "add r3, #18\n\t"
                        "add r1, r1, r3\n\t"
                        "mov r3, #0\n\t"
                        "ldrsh r1, [r1, r3]\n\t"
                        "str r1, [r0, #8]"
                        : "+r"(object), "+r"(coordinate_base),
                          "+r"(coordinate_index)
                        :
                        : "r1", "r2", "cc", "memory");
                    object = (u8 *)object + 0x8C;
                    asm volatile(
                        "ldrb r1, [r6, #0]\n\t"
                        "add r1, r1, r5\n\t"
                        "ldrb r1, [r1, #0]\n\t"
                        "sub r1, #46\n\t"
                        "str r1, [r0, #0]"
                        : "+r"(object)
                        : "r"(side), "r"(work)
                        : "r1", "cc", "memory");
                    *pending = zero;
                } else {
                    register u8 *work asm("r0") = (u8 *)0x02034B4C;
                    register u8 *side asm("r1") = (u8 *)0x02033F36;
                    register u32 work_offset asm("r3") = 0x27BE;

                    asm volatile("" : "+r"(work), "+r"(side),
                        "+r"(work_offset));
                    work += work_offset;
                    work += *side;
                    *work = (u8)pending_value;
                }
            }
    }
finish:
    {
        s32 neg_one = -1;
        asm volatile("" : "+r"(neg_one));
        func_080A016C(source, neg_one, 0);
    }
    return 0;
}
