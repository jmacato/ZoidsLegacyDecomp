#include "m2c_prelude.h"

struct SpawnedObject {
    u32 flags;
    s32 x;
    s32 y;
    u8 pad0C[0x9C];
    u32 parameter;
};

extern u8 D_02033FD0[];
extern s32 D_02034034;
extern s32 D_03000054[];
extern s16 D_087EB08C[][16];
extern s16 D_087EC38C[];

void func_080D2328(void);
struct SpawnedObject *func_08095098(s32, u32, u32);

struct SpawnedObject *sub_080E083C(u32 arg0, u32 arg1, u32 arg2,
                                    u32 arg3, s32 arg4)
{
    volatile u32 saved_arg3;
    register u32 kind asm("r4");
    u32 saved_arg0;
    register u32 saved_arg2 asm("r6");
    register u32 saved_arg4 asm("r8");
    register struct SpawnedObject *result asm("r4");
    register u8 *state asm("r5");
    register u32 saved_y asm("r3");
    register u32 arg4_temp asm("r1");
    s32 flag;
    u8 mode;

    kind = arg1;
    arg4_temp = arg4;
    saved_arg0 = (u8)arg0;
    kind = (u16)kind;
    saved_arg2 = (u16)arg2;
    saved_y = (u16)arg3;
    saved_arg4 = (u16)arg4_temp;
    saved_arg3 = saved_y;

    func_080D2328();
    state = D_02033FD0;
    flag = state[1];
    flag = ((-flag | flag) >> 31) & 2;
    {
        register u8 *pair_base asm("r2");
        register u8 *first_address asm("r1");
        register u32 first asm("r1");
        register u32 second asm("r2");

        pair_base = (u8 *)0x087A2D1C;
        kind <<= 3;
        first_address = (u8 *)kind + (u32)pair_base;
        first = *(u32 *)first_address;
        pair_base += 4;
        kind += (u32)pair_base;
        second = *(u32 *)kind;
        result = func_08095098(flag, first, second);
    }

    mode = state[5];
    saved_y = saved_arg3;
    switch (mode) {
    case 0:
        {
            register s32 x asm("r0") = (s16)saved_arg2;
            register s32 y asm("r0");

            result->x = x;
            y = (s16)saved_y;
            result->y = y;
        }
        break;
    case 4:
        {
            register s32 narrow asm("r0");
            register s32 x asm("r1");
            register s32 y asm("r1");
            register s32 adjusted asm("r0");

            narrow = saved_arg2 << 16;
            x = narrow >> 16;
            adjusted = x - D_02034034 / 0x100;
            result->x = adjusted;
            narrow = saved_y << 16;
            y = narrow >> 16;
            adjusted = y - D_03000054[1] / 0x100;
            result->y = adjusted;
        }
        break;
    case 8:
        {
            register s32 x asm("r2") = (s16)saved_arg2;
            register const s16 *values asm("r6");
            register u8 *case_state asm("r5");

            values = D_087EC38C;
            case_state = D_02033FD0;
            {
                register u32 part3 asm("r0");
                register u32 part2 asm("r1");
                register s32 table_value asm("r0");
                register s32 sum asm("r1");
                register s32 adjusted asm("r0");

                part3 = case_state[3];
                part3 <<= 2;
                part2 = case_state[2];
                part2 <<= 5;
                part3 += part2;
                part3 += (u32)values;
                part2 = 0;
                table_value = *(s16 *)((u8 *)part3 + part2);
                sum = x + table_value;
                adjusted = sum - D_02034034 / 0x100;
                result->x = adjusted;
            }
            {
                register s32 y asm("r2") = (s16)saved_y;
                register u32 offset asm("r1");
                register u32 part asm("r0");
                register s32 table_value asm("r0");
                register s32 sum asm("r1");
                register s32 adjusted asm("r0");

                offset = case_state[3];
                offset <<= 2;
                part = case_state[2];
                part <<= 5;
                offset += part;
                part = (u32)(values + 1);
                offset += part;
                table_value = *(s16 *)offset;
                sum = y + table_value;
                adjusted = sum - D_03000054[1] / 0x100;
                result->y = adjusted;
            }
        }
        break;
    case 12:
        {
            register s32 x asm("r1") = (s16)saved_arg2;
            register const u8 *values asm("r5");
            register u32 row asm("r2");
            register const u8 *field asm("r0");
            register s32 table_value asm("r0");
            register s32 y asm("r1");
            register s32 adjusted asm("r0");

            values = (const u8 *)D_087EB08C;
            row = saved_arg0 << 5;
            field = (const u8 *)row + (u32)values;
            table_value = *(s16 *)field;
            x += table_value;
            adjusted = x - D_02034034 / 0x100;
            result->x = adjusted;
            y = (s16)saved_y;
            field = values + 2;
            field = (const u8 *)row + (u32)field;
            table_value = *(s16 *)field;
            y += table_value;
            adjusted = y - D_03000054[1] / 0x100;
            result->y = adjusted;
        }
        break;
    case 16:
        {
            register s32 x asm("r1") = (s16)saved_arg2;
            register const u8 *values asm("r5");
            register u32 row asm("r2");
            register const u8 *field asm("r0");
            register s32 table_value asm("r0");
            register s32 y asm("r1");
            register s32 adjusted asm("r0");

            values = (const u8 *)D_087EB08C;
            row = saved_arg0 << 5;
            field = values + 4;
            field = (const u8 *)row + (u32)field;
            table_value = *(s16 *)field;
            x += table_value;
            adjusted = x - D_02034034 / 0x100;
            result->x = adjusted;
            y = (s16)saved_y;
            field = values + 6;
            field = (const u8 *)row + (u32)field;
            table_value = *(s16 *)field;
            y += table_value;
            adjusted = y - D_03000054[1] / 0x100;
            result->y = adjusted;
        }
        break;
    case 20:
        {
            register s32 x asm("r1") = (s16)saved_arg2;
            register const u8 *values asm("r5");
            register u32 row asm("r2");
            register const u8 *field asm("r0");
            register s32 table_value asm("r0");
            register s32 y asm("r1");
            register s32 adjusted asm("r0");

            values = (const u8 *)D_087EB08C;
            row = saved_arg0 << 5;
            field = values + 8;
            field = (const u8 *)row + (u32)field;
            table_value = *(s16 *)field;
            x += table_value;
            adjusted = x - D_02034034 / 0x100;
            result->x = adjusted;
            y = (s16)saved_y;
            field = values + 10;
            field = (const u8 *)row + (u32)field;
            table_value = *(s16 *)field;
            y += table_value;
            adjusted = y - D_03000054[1] / 0x100;
            result->y = adjusted;
        }
        break;
    case 24:
        {
            register s32 x asm("r1") = (s16)saved_arg2;
            register const u8 *values asm("r5");
            register u32 row asm("r2");
            register const u8 *field asm("r0");
            register s32 table_value asm("r0");
            register s32 y asm("r1");
            register s32 adjusted asm("r0");

            values = (const u8 *)D_087EB08C;
            row = saved_arg0 << 5;
            field = values + 12;
            field = (const u8 *)row + (u32)field;
            table_value = *(s16 *)field;
            x += table_value;
            adjusted = x - D_02034034 / 0x100;
            result->x = adjusted;
            y = (s16)saved_y;
            field = values + 14;
            field = (const u8 *)row + (u32)field;
            table_value = *(s16 *)field;
            y += table_value;
            adjusted = y - D_03000054[1] / 0x100;
            result->y = adjusted;
        }
        break;
    case 28:
        {
            register s32 x asm("r1") = (s16)saved_arg2;
            register const u8 *values asm("r5");
            register u32 row asm("r2");
            register const u8 *field asm("r0");
            register s32 table_value asm("r0");
            register s32 y asm("r1");
            register s32 adjusted asm("r0");

            values = (const u8 *)D_087EB08C;
            row = saved_arg0 << 5;
            field = values + 16;
            field = (const u8 *)row + (u32)field;
            table_value = *(s16 *)field;
            x += table_value;
            adjusted = x - D_02034034 / 0x100;
            result->x = adjusted;
            y = (s16)saved_y;
            field = values + 18;
            field = (const u8 *)row + (u32)field;
            table_value = *(s16 *)field;
            y += table_value;
            adjusted = y - D_03000054[1] / 0x100;
            result->y = adjusted;
        }
        break;
    case 32:
        {
            register s32 x asm("r1") = (s16)saved_arg2;
            register const u8 *values asm("r5");
            register u32 row asm("r2");
            register const u8 *field asm("r0");
            register s32 table_value asm("r0");
            register s32 y asm("r1");
            register s32 adjusted asm("r0");

            values = (const u8 *)D_087EB08C;
            row = saved_arg0 << 5;
            field = values + 20;
            field = (const u8 *)row + (u32)field;
            table_value = *(s16 *)field;
            x += table_value;
            adjusted = x - D_02034034 / 0x100;
            result->x = adjusted;
            y = (s16)saved_y;
            field = values + 22;
            field = (const u8 *)row + (u32)field;
            table_value = *(s16 *)field;
            y += table_value;
            adjusted = y - D_03000054[1] / 0x100;
            result->y = adjusted;
        }
        break;
    }

    {
        register u32 *parameter_slot asm("r0") = &result->parameter;
        register u32 parameter asm("r3");

        parameter = saved_arg4;
        *parameter_slot = parameter;
    }
    return result;
}
