#include "m2c_prelude.h"

#define NULL ((void *)0)

M2C_UNK func_08092E84(u16);                         /* extern */
M2C_UNK func_08095254(s32, s32, u16, u16);          /* extern */
M2C_UNK jtbl_080D08EC();                            /* static */

extern u8 D_02033F36;
extern u8 *D_02033F38;
extern s32 *D_02033F40[];
extern void *D_02033F3C;
extern u8 D_02034055;
extern u8 D_02034056;
extern u8 D_02034057;
extern u8 D_02034058;
extern u16 D_0203405A;
extern u16 D_0203405C;
extern u8 D_02034060[];
asm(".set D_087AC90C, 0x087AC90C");
extern s16 D_087AC90C[];
extern s16 D_087EC38C[];
extern u8 D_087ED68C[];

#define D0644_COMMAND_FIRST(base, index) ({ \
    u32 command_offset = (index); \
    command_offset <<= 3; \
    asm volatile("add %0, %0, %1" \
                 : "+r"(command_offset) \
                 : "r"((u32)(base))); \
    *(s32 *)command_offset; \
})

#define D0644_COMMAND_SECOND(base, index) ({ \
    u32 command_offset = (index); \
    command_offset <<= 1; \
    command_offset += 1; \
    command_offset <<= 2; \
    asm volatile("add %0, %0, %1" \
                 : "+r"(command_offset) \
                 : "r"((u32)(base))); \
    *(s32 *)command_offset; \
})

void sub_080D0644(void) {
    register u8 *state_ptr asm("r3");
    s16 *var_r6;
    s16 temp_r0_8;
    s32 temp_r3_4;
    s16 var_r9;
    s32 *temp_r0_2;
    s32 var_r7;
    u16 temp_r2_2;
    u16 temp_r3;
    u16 var_r0_2;
    u16 var_r3;
    u16 var_r4;
    u32 temp_r0_7;
    u32 var_r0;
    u8 temp_r0;
    u8 temp_r0_5;
    s32 temp_r1;
    s32 temp_r2_3;
    s32 temp_r2_4;
    u8 var_r5;
    u8 var_r6_2;
    void *temp_r0_3;
    void *temp_r0_9;
    void *temp_r3_2;
    void *temp_r3_5;

    state_ptr = &D_02034057;
    temp_r1 = *state_ptr;
    if (temp_r1 == 0) {
        return;
    }
    {
        register u8 *mode_ptr asm("r2") = &D_02034056;

        temp_r0 = *mode_ptr;
    }
    if ((u32) temp_r0 <= 3U) {
        if ((u32) temp_r0 > 2U) {
            return;
        }
        temp_r0_2 = D_02033F40[temp_r0];
        if (temp_r0_2 == NULL) {
            return;
        }
        if (!(*temp_r0_2 & 4)) {
            return;
        }
        goto block_93;
    }
    if (temp_r1 == 1) {
        s32 first_command;
        register u16 *active_index asm("r5");
        register u8 *command_base asm("r4");
        register u16 *command_index asm("r6");
        register u16 *elapsed_ptr asm("sl");
        register s32 initial_state asm("r3");

        {
            register u16 *elapsed_seed asm("r2") = &D_0203405C;
            register u16 elapsed asm("r3") = *elapsed_seed;
            register u8 *command_seed asm("r1") = D_02034060;
            register u16 *index_seed asm("r5") = &D_0203405A;
            s32 initial_second;

            initial_second = D0644_COMMAND_SECOND(command_seed, *index_seed);
            elapsed_ptr = elapsed_seed;
            command_base = command_seed;
            if (elapsed != initial_second) {
                goto block_88;
            }
            var_r7 = 0;
            command_index = index_seed;
        }
        goto command_increment;
command_active_test:
        if (D0644_COMMAND_SECOND(command_base, temp_r3) != 0) {
            goto block_25;
        }
command_increment:
loop_18:
        *command_index += 1;
        first_command = D0644_COMMAND_FIRST(command_base, *command_index);
        asm volatile("" : "+r"(first_command));
        if (first_command != -3) {
            goto command_calls_done;
        }
        {
            register u8 *call_base asm("r5") = D_02034060;
            register u16 *call_index asm("r4") = &D_0203405A;

command_call_loop:
            func_08092E84((u16)D0644_COMMAND_SECOND(call_base, *call_index));
            *call_index = (u16) (*call_index + 1);
            if (D0644_COMMAND_FIRST(call_base, *call_index) == -3) {
                goto command_call_loop;
            }
        }
command_calls_done:
        {
            register u8 *resume_base asm("r1") = D_02034060;
            register s32 minus_one asm("r0");
            s32 current_command;

            temp_r3 = *command_index;
            current_command = D0644_COMMAND_FIRST(resume_base, temp_r3);
            minus_one = -1;
            command_base = resume_base;
            active_index = &D_0203405A;
            if (current_command == minus_one) {
                goto command_stop;
            }
        }
        if (D0644_COMMAND_FIRST(command_base, temp_r3 + 1) == -2) {
            D_02034058 = 1;
            var_r7 = 1;
            goto block_25;
        }
        goto command_active_test;
block_25:
        temp_r0_3 = (void *)D0644_COMMAND_FIRST(command_base, *active_index);
        if (temp_r0_3 != NULL) {
            register void *descriptor_seed asm("r3");

            asm volatile("add %0, %1, %2"
                         : "=r"(descriptor_seed)
                         : "r"(temp_r0_3), "r"(command_base));
            temp_r3_2 = descriptor_seed;
            if (D_02033F36 == 0) {
                func_08095254(temp_r3_2 + 8, (((M2C_FIELD(temp_r3_2, u16 *, 2) << 5) + M2C_FIELD(temp_r3_2, u16 *, 0)) * 2) + 0x06000000, M2C_FIELD(temp_r3_2, u16 *, 4), M2C_FIELD(temp_r3_2, u16 *, 6));
            } else {
                register s16 *mirror_start asm("r8");
                register u16 *mirror_source asm("r1");
                register u16 mirror_width asm("r2");
                register u32 mirror_successor asm("r5");

                var_r6 = (s16 *)0x02002D20;
                var_r0 = 0;
                mirror_start = var_r6;
                goto mirror_outer_test;
mirror_outer_body:
                var_r0 += 1;
                mirror_width = M2C_FIELD(temp_r3_2, u16 *, 4);
                mirror_source = (u16 *)(var_r0 * mirror_width * 2);
                asm volatile("add %0, %0, %1"
                             : "+r"(mirror_source)
                             : "r"(temp_r3_2));
                mirror_source += 3;
                var_r4 = 0;
                mirror_successor = var_r0;
                if ((u32)var_r4 >= (u32)mirror_width) {
                    goto mirror_inner_done;
                }
                do {
                    *var_r6 = *mirror_source ^ 0x400;
                    var_r6 += 1;
                    mirror_source -= 1;
                    var_r4 += 1;
                } while ((u32) var_r4 < (u32) M2C_FIELD(temp_r3_2, u16 *, 4));
mirror_inner_done:
                var_r0 = (u16) mirror_successor;
                asm volatile("" :: "r"(mirror_successor));
mirror_outer_test:
                {
                    register u16 mirror_height asm("r1");

                    mirror_height = M2C_FIELD(temp_r3_2, u16 *, 6);
                    if (var_r0 < (u32)mirror_height) {
                        goto mirror_outer_body;
                    }
                }
                {
                    register u32 mirror_destination asm("r1");

                    mirror_destination = 0x20 - M2C_FIELD(temp_r3_2, u16 *, 0);
                    temp_r2_2 = M2C_FIELD(temp_r3_2, u16 *, 4);
                    mirror_destination -= temp_r2_2;
                    mirror_destination += M2C_FIELD(temp_r3_2, u16 *, 2) << 5;
                    mirror_destination *= 2;
                    mirror_destination += 0x06000000;
                    func_08095254(mirror_start, mirror_destination, temp_r2_2, M2C_FIELD(temp_r3_2, u16 *, 6));
                }
            }
            if (var_r7 != 0) {
                D_0203405A = 0U;
            }
        }
        {
            register u16 *elapsed_reload asm("r0") = &D_0203405C;

            *elapsed_reload = 0U;
            initial_state = D_02034055;
            elapsed_ptr = elapsed_reload;
        }
        if (((((initial_state != 0x4B) && (initial_state != 0x4E)) || (D_02034056 != 6)) && ((temp_r2_3 = D_02034055, (temp_r2_3 != 0x6D)) || (D_02034056 != 5)) && ((temp_r2_3 != 0x6E) || (D_02034056 != 5)) && ((temp_r2_3 != 0x6F) || (D_02034056 != 5)) && ((temp_r2_3 != 0x78) || (D_02034056 != 6))) || (D_0203405A != 2)) {
            temp_r0_5 = D_02034055;
            if ((((temp_r0_5 != 0x4B) && (temp_r0_5 != 0x4E)) || (D_02034056 != 0xB)) && ((temp_r2_4 = D_02034055, (temp_r2_4 != 0x6D)) || (D_02034056 != 0xA)) && ((temp_r2_4 != 0x6E) || (D_02034056 != 0xA)) && ((temp_r2_4 != 0x6F) || (D_02034056 != 0xA))) {
                if (temp_r2_4 != 0x78) {

                } else if (D_02034056 != 0xB) {

                } else {
                    goto block_63;
                }
            } else {
block_63:
                if (D_0203405A != 4) {

                } else {
                    goto block_65;
                }
            }
        } else {
block_65:
            var_r6_2 = 0;
loop_66:
            {
                register u32 object_offset_seed asm("r0");
                register s32 object_offset asm("r4");
                register s16 *coordinate_table asm("r2");
                register u32 coordinate_offset asm("r1");
                register u16 coordinate_result_seed asm("r3");
                register u8 *attribute_table asm("r4");
                register s32 attribute_bits asm("r2");
                void *object;
                u32 attribute_index;

                object_offset_seed = var_r6_2 * 4;
                object = M2C_FIELD(object_offset_seed, void **, (u32)D_02033F40);
                object_offset = object_offset_seed;
                if (object == NULL) {

                } else {
                temp_r0_7 = D_02034055 - 0x4B;
                switch (temp_r0_7) {                /* switch 2 */
                case 0:                             /* switch 2 */
                case 3:                             /* switch 2 */
                    var_r9 = 0xC0;
                    break;
                case 34:                            /* switch 2 */
                case 35:                            /* switch 2 */
                case 36:                            /* switch 2 */
                    var_r9 = 0xB0;
                    break;
                case 45:                            /* switch 2 */
                    var_r9 = 0xA8;
                    break;
                }
                var_r5 = var_r6_2;
                if (((u32) D_02034056 <= 8U) && (var_r6_2 != 0)) {
                    var_r5 ^= 3;
                }
                coordinate_table = D_087EC38C;
                coordinate_offset = var_r5 * 4;
                coordinate_offset += D_02034055 << 5;
                asm volatile("add %0, %0, %1"
                             : "+r"(coordinate_offset)
                             : "r"(coordinate_table));
                temp_r3_4 = *(s16 *)coordinate_offset;
                if (var_r5 == 2) {
                    register s16 *coordinate_adjust_table asm("r1");
                    s32 coordinate_adjustment;

                    coordinate_adjust_table = D_087AC90C;
                    coordinate_adjustment = *(s16 *)((u32)coordinate_adjust_table + (M2C_FIELD((D_02033F38 + object_offset), u16 *, 0x52) * 2));
                    var_r0_2 = temp_r3_4 - coordinate_adjustment;
                } else {
                    var_r0_2 = (u16) temp_r3_4;
                }
                coordinate_result_seed = var_r0_2;
                var_r3 = coordinate_result_seed;
                if ((u32) D_02034056 <= 8U) {
                    temp_r0_8 = (s16) var_r3;
                    var_r3 = temp_r0_8 + ((var_r9 - temp_r0_8) * 2);
                }
                if (D_02033F36 == 0) {
                    M2C_FIELD(M2C_FIELD(object_offset, void **, (u32)D_02033F40), u16 *, 4) = var_r3;
                } else {
                    register s32 mirror_base_seed asm("r0");
                    void *mirror_object;
                    s32 mirror_base;
                    s32 signed_coordinate;

                    mirror_object = M2C_FIELD(object_offset, void **, (u32)D_02033F40);
                    mirror_base_seed = 0x100;
                    mirror_base = mirror_base_seed;
                    asm volatile("" : "+r"(mirror_base_seed));
                    signed_coordinate = (s16) var_r3;
                    M2C_FIELD(mirror_object, u16 *, 4) = (u16) (mirror_base - signed_coordinate);
                }
                {
                    register u32 final_object_address asm("r0");

                    asm volatile("add %0, %1, %2"
                                 : "=r"(final_object_address)
                                 : "r"(object_offset), "r"(D_02033F40));
                    temp_r3_5 = *(void **)final_object_address;
                }
                attribute_bits = (M2C_FIELD(temp_r3_5, s32 *, 0) ^ 0x8000) & ~0xC0;
                M2C_FIELD(temp_r3_5, s32 *, 0) = attribute_bits;
                attribute_table = D_087ED68C;
                attribute_index = *D_02033F38 * 3;
                asm volatile("add %0, %1, %0"
                             : "+r"(attribute_index)
                             : "r"((u32)var_r5));
                asm volatile("add %0, %0, %1"
                             : "+r"(attribute_index)
                             : "r"(attribute_table));
                attribute_bits |= *(u8 *)attribute_index << 6;
                M2C_FIELD(temp_r3_5, s32 *, 0) = attribute_bits;
                }
            }
            var_r6_2 += 1;
            if ((u32) var_r6_2 <= 2U) {
                goto loop_66;
            }
        }
block_88:
        {
            register u16 *increment_ptr asm("r2") = elapsed_ptr;

            *increment_ptr += 1;
        }
        return;
command_stop:
        D_02034057 = 0U;
        goto block_94;
    }
    if (temp_r1 == 2) {
        temp_r0_9 = D_02033F3C;
        if ((temp_r0_9 == NULL) || (M2C_FIELD(temp_r0_9, s32 *, 0x8C) == 0xFF)) {
block_93:
            *state_ptr = 0;
            goto block_94;
        }
    }
    return;
block_94:
    D_02034058 = 1;
}
