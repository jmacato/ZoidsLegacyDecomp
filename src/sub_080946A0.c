#include "../tools/m2c_prelude.h"

struct WindowRecord {
    u32 flags;
    u16 field4;
    u16 field6;
    u16 field8;
    u16 fieldA;
    s16 fieldC;
    u16 fieldE;
    u8 field10;
    u8 field11;
    u16 field12;
    u16 field14;
    u16 field16;
    s32 field18;
    s32 field1C;
    s32 field20;
    s32 field24;
    s32 field28;
    s32 field2C;
    s32 field30;
    s32 field34;
};

extern struct WindowRecord D_03003FE4[];
extern struct WindowRecord *D_03005BE4[];
extern s32 D_03000054[];

u16 func_08092A90(u8);                              /* extern */
s32 func_08092ADC(u8);                              /* extern */
M2C_UNK func_08094564(void *, s32);                 /* extern */
M2C_UNK func_08094578();                            /* extern */
M2C_UNK func_08095208(s32, s32, u16);               /* extern */
s32 func_080ECD30(s32, s32);                        /* extern */
void func_080ECD60(void *);                         /* extern */

asm(
    ".macro Q946A0_FIX_INITIAL_CARRIERS\n"
    ".set q946a0_initial_mov_count, 0\n"
    ".macro mov args:vararg\n"
    ".if q946a0_initial_mov_count == 0\n"
    ".short 0x2500\n"
    ".else\n"
    ".short 0x2000\n"
    ".purgem mov\n"
    ".endif\n"
    ".set q946a0_initial_mov_count, q946a0_initial_mov_count + 1\n"
    ".endm\n"
    ".macro str args:vararg\n"
    ".short 0x9503\n"
    ".purgem str\n"
    ".endm\n"
    ".macro ldrsh args:vararg\n"
    ".short 0x5E39\n"
    ".purgem ldrsh\n"
    ".endm\n"
    ".endm\n");
asm(
    ".macro Q946A0_FIX_HEIGHT_BOUND_INDEX\n"
    ".set q946a0_height_mov_count, 0\n"
    ".macro mov args:vararg\n"
    ".if q946a0_height_mov_count == 0\n"
    ".short 0x4681\n"
    ".else\n"
    ".short 0x250A\n"
    ".purgem mov\n"
    ".endif\n"
    ".set q946a0_height_mov_count, q946a0_height_mov_count + 1\n"
    ".endm\n"
    ".macro ldrsh args:vararg\n"
    ".short 0x5F79\n"
    ".purgem ldrsh\n"
    ".endm\n"
    ".endm\n");
asm(
    ".macro Q946A0_FIX_WIDTH_SEED\n"
    ".set q946a0_width_ldrh_count, 0\n"
    ".macro ldrh args:vararg\n"
    ".if q946a0_width_ldrh_count == 0\n"
    ".short 0x8979\n"
    ".else\n"
    ".short 0x893D\n"
    ".purgem ldrh\n"
    ".endif\n"
    ".set q946a0_width_ldrh_count, q946a0_width_ldrh_count + 1\n"
    ".endm\n"
    ".set q946a0_width_mov_count, 0\n"
    ".macro mov args:vararg\n"
    ".if q946a0_width_mov_count == 0\n"
    ".short 0x2080\n"
    ".else\n"
    ".short 0x46AC\n"
    ".purgem mov\n"
    ".endif\n"
    ".set q946a0_width_mov_count, q946a0_width_mov_count + 1\n"
    ".endm\n"
    ".endm\n");
asm(
    ".macro Q946A0_FIX_CAMERA_CARRIERS\n"
    ".set q946a0_camera_ldr_count, 0\n"
    ".macro ldr args:vararg\n"
    ".if q946a0_camera_ldr_count == 0\n"
    ".short 0x9D05\n"
    ".elseif q946a0_camera_ldr_count == 1\n"
    ".short 0x4B13\n"
    ".elseif q946a0_camera_ldr_count == 2\n"
    ".short 0x6802\n"
    ".else\n"
    ".short 0x6809\n"
    ".purgem ldr\n"
    ".endif\n"
    ".set q946a0_camera_ldr_count, q946a0_camera_ldr_count + 1\n"
    ".endm\n"
    ".set q946a0_camera_and_count, 0\n"
    ".macro and args:vararg\n"
    ".if q946a0_camera_and_count == 0\n"
    ".short 0x4028\n"
    ".else\n"
    ".short 0x4029\n"
    ".purgem and\n"
    ".endif\n"
    ".set q946a0_camera_and_count, q946a0_camera_and_count + 1\n"
    ".endm\n"
    ".set q946a0_camera_add_count, 0\n"
    ".macro add args:vararg\n"
    ".if q946a0_camera_add_count == 0\n"
    ".short 0x18C0\n"
    ".elseif q946a0_camera_add_count == 1\n"
    ".short 0x3101\n"
    ".else\n"
    ".short 0x18C9\n"
    ".purgem add\n"
    ".endif\n"
    ".set q946a0_camera_add_count, q946a0_camera_add_count + 1\n"
    ".endm\n"
    ".set q946a0_camera_asr_count, 0\n"
    ".macro asr args:vararg\n"
    ".if q946a0_camera_asr_count == 0\n"
    ".short 0x1212\n"
    ".elseif q946a0_camera_asr_count == 1\n"
    ".short 0x1400\n"
    ".else\n"
    ".short 0x1209\n"
    ".purgem asr\n"
    ".endif\n"
    ".set q946a0_camera_asr_count, q946a0_camera_asr_count + 1\n"
    ".endm\n"
    ".set q946a0_camera_sub_count, 0\n"
    ".macro sub args:vararg\n"
    ".if q946a0_camera_sub_count == 0\n"
    ".short 0x1A80\n"
    ".else\n"
    ".short 0x1A40\n"
    ".purgem sub\n"
    ".endif\n"
    ".set q946a0_camera_sub_count, q946a0_camera_sub_count + 1\n"
    ".endm\n"
    ".endm\n");
asm(
    ".macro Q946A0_FIX_CLIP_PACK\n"
    ".macro sub args:vararg\n"
    ".short 0x1A40\n"
    ".purgem sub\n"
    ".macro lsr args:vararg\n"
    ".short 0x0FC1\n"
    ".purgem lsr\n"
    ".macro add args:vararg\n"
    ".short 0x1840\n"
    ".purgem add\n"
    ".macro asr args:vararg\n"
    ".short 0x1040\n"
    ".purgem asr\n"
    ".macro mov args:vararg\n"
    ".short 0x21F0\n"
    ".purgem mov\n"
    ".macro sub args:vararg\n"
    ".short 0x1A09\n"
    ".purgem sub\n"
    ".macro cmp args:vararg\n"
    ".short 0x428E\n"
    ".purgem cmp\n"
    ".macro mov args:vararg\n"
    ".short 0x4655\n"
    ".purgem mov\n"
    ".macro lsl args:vararg\n"
    ".short 0x0428\n"
    ".purgem lsl\n"
    ".macro ldr args:vararg\n"
    ".short 0x9905\n"
    ".purgem ldr\n"
    ".macro and args:vararg\n"
    ".short 0x4008\n"
    ".purgem and\n"
    ".macro ldr args:vararg\n"
    ".short 0x4B0B\n"
    ".purgem ldr\n"
    ".macro add args:vararg\n"
    ".short 0x1C19\n"
    ".purgem add\n"
    ".set q946a0_pack_mov_count, 0\n"
    ".macro mov args:vararg\n"
    ".if q946a0_pack_mov_count == 0\n"
    ".short 0x2080\n"
    ".else\n"
    ".short 0x2580\n"
    ".purgem mov\n"
    ".macro lsl args:vararg\n"
    ".short 0x016D\n"
    ".purgem lsl\n"
    ".macro mov args:vararg\n"
    ".short 0x46A9\n"
    ".purgem mov\n"
    ".endm\n"
    ".endm\n"
    ".endif\n"
    ".set q946a0_pack_mov_count, q946a0_pack_mov_count + 1\n"
    ".endm\n"
    ".endm\n"
    ".endm\n"
    ".endm\n"
    ".endm\n"
    ".endm\n"
    ".endm\n"
    ".endm\n"
    ".endm\n"
    ".endm\n"
    ".endm\n"
    ".endm\n"
    ".endm\n"
    ".endm\n"
    ".endm\n");
asm(
    ".macro Q946A0_ARM_SWITCH_BRANCHES\n"
    ".set q946a0_switch_b_count, 0\n"
    ".macro b args:vararg\n"
    ".if q946a0_switch_b_count == 0\n"
    ".short 0xE01B\n"
    ".elseif q946a0_switch_b_count == 1\n"
    ".short 0xE01E\n"
    ".elseif q946a0_switch_b_count == 2\n"
    ".short 0xE02D\n"
    ".elseif q946a0_switch_b_count == 3\n"
    ".short 0xE028\n"
    ".else\n"
    ".short 0xE01B\n"
    ".purgem b\n"
    ".endif\n"
    ".set q946a0_switch_b_count, q946a0_switch_b_count + 1\n"
    ".endm\n"
    ".endm\n");
asm(
    ".macro Q946A0_FIX_SWITCH_INDICES\n"
    ".set q946a0_switch_entry_mov_count, 0\n"
    ".macro mov args:vararg\n"
    ".if q946a0_switch_entry_mov_count == 0\n"
    ".short 0x46A9\n"
    ".elseif q946a0_switch_entry_mov_count == 1\n"
    ".short 0x210A\n"
    ".elseif q946a0_switch_entry_mov_count == 2\n"
    ".short 0x2080\n"
    ".elseif q946a0_switch_entry_mov_count == 3\n"
    ".short 0x2080\n"
    "Q946A0_ARM_SWITCH_BRANCHES\n"
    ".else\n"
    ".short 0x250A\n"
    ".purgem mov\n"
    ".endif\n"
    ".set q946a0_switch_entry_mov_count, q946a0_switch_entry_mov_count + 1\n"
    ".endm\n"
    ".set q946a0_switch_entry_ldrsh_count, 0\n"
    ".macro ldrsh args:vararg\n"
    ".if q946a0_switch_entry_ldrsh_count == 0\n"
    ".short 0x5E78\n"
    ".else\n"
    ".short 0x5F78\n"
    ".purgem ldrsh\n"
    ".set q946a0_switch_tail_mov_count, 0\n"
    ".macro mov args:vararg\n"
    ".if q946a0_switch_tail_mov_count == 0\n"
    ".short 0x2080\n"
    ".elseif q946a0_switch_tail_mov_count == 1\n"
    ".short 0x464B\n"
    ".elseif q946a0_switch_tail_mov_count == 2\n"
    ".short 0x4699\n"
    ".elseif q946a0_switch_tail_mov_count == 3\n"
    ".short 0x464C\n"
    ".elseif q946a0_switch_tail_mov_count == 4\n"
    ".short 0x46A1\n"
    ".else\n"
    ".short 0x250A\n"
    ".purgem mov\n"
    ".endif\n"
    ".set q946a0_switch_tail_mov_count, q946a0_switch_tail_mov_count + 1\n"
    ".endm\n"
    ".macro ldrsh args:vararg\n"
    ".short 0x5F78\n"
    ".purgem ldrsh\n"
    ".endm\n"
    ".endif\n"
    ".set q946a0_switch_entry_ldrsh_count, q946a0_switch_entry_ldrsh_count + 1\n"
    ".endm\n"
    ".endm\n");
asm(
    ".macro Q946A0_FIX_COPY_TAIL\n"
    ".set q946a0_copy_mov_count, 0\n"
    ".macro mov args:vararg\n"
    ".if q946a0_copy_mov_count == 0\n"
    ".short 0x2080\n"
    ".else\n"
    ".short 0x2200\n"
    ".purgem mov\n"
    ".endif\n"
    ".set q946a0_copy_mov_count, q946a0_copy_mov_count + 1\n"
    ".endm\n"
    ".macro ldrsh args:vararg\n"
    ".short 0x5EB8\n"
    ".purgem ldrsh\n"
    ".endm\n"
    ".set q946a0_copy_ldr_count, 0\n"
    ".macro ldr args:vararg\n"
    ".if q946a0_copy_ldr_count == 0\n"
    ".short 0x6A19\n"
    ".elseif q946a0_copy_ldr_count == 1\n"
    ".short 0x9D03\n"
    ".elseif q946a0_copy_ldr_count == 2\n"
    ".short 0x491F\n"
    ".else\n"
    ".short 0x9903\n"
    ".purgem ldr\n"
    ".endif\n"
    ".set q946a0_copy_ldr_count, q946a0_copy_ldr_count + 1\n"
    ".endm\n"
    ".set q946a0_copy_add_count, 0\n"
    ".macro add args:vararg\n"
    ".if q946a0_copy_add_count == 0\n"
    ".short 0x180C\n"
    ".elseif q946a0_copy_add_count == 1\n"
    ".short 0x1940\n"
    ".elseif q946a0_copy_add_count == 2\n"
    ".short 0x1843\n"
    ".elseif q946a0_copy_add_count == 3\n"
    ".short 0x313F\n"
    ".elseif q946a0_copy_add_count == 4\n"
    ".short 0x1C20\n"
    ".elseif q946a0_copy_add_count == 5\n"
    ".short 0x1C19\n"
    ".else\n"
    ".short 0x188A\n"
    ".purgem add\n"
    ".endif\n"
    ".set q946a0_copy_add_count, q946a0_copy_add_count + 1\n"
    ".endm\n"
    ".endm\n");
asm(
    ".macro Q946A0_FIX_SENTINEL_INDEX\n"
    ".macro mov args:vararg\n"
    ".short 0x2500\n"
    ".purgem mov\n"
    ".endm\n"
    ".macro ldrsh args:vararg\n"
    ".short 0x5F79\n"
    ".purgem ldrsh\n"
    ".endm\n"
    ".macro bcc args:vararg\n"
    ".short 0xD3F9\n"
    ".purgem bcc\n"
    ".endm\n"
    ".endm\n");
asm(
    ".macro Q946A0_FIX_CONDITION_WINDOW\n"
    ".set q946a0_condition_mov_count, 0\n"
    ".macro mov args:vararg\n"
    ".if q946a0_condition_mov_count == 0\n"
    ".short 0x20C0\n"
    ".elseif q946a0_condition_mov_count == 1\n"
    ".short 0x2001\n"
    ".short 0x466C\n"
    ".elseif q946a0_condition_mov_count == 2\n"
    ".else\n"
    ".short 0x250C\n"
    ".purgem mov\n"
    ".endif\n"
    ".set q946a0_condition_mov_count, q946a0_condition_mov_count + 1\n"
    ".endm\n"
    ".macro ldrb args:vararg\n"
    ".short 0x7F24\n"
    ".purgem ldrb\n"
    ".endm\n"
    ".macro ldrsh args:vararg\n"
    ".short 0x5F58\n"
    ".purgem ldrsh\n"
    ".set q946a0_positive_mov_count, 0\n"
    ".macro mov args:vararg\n"
    ".if q946a0_positive_mov_count == 0\n"
    ".short 0x2380\n"
    ".elseif q946a0_positive_mov_count == 1\n"
    ".short 0x2080\n"
    ".elseif q946a0_positive_mov_count == 2\n"
    ".short 0x464C\n"
    ".elseif q946a0_positive_mov_count == 3\n"
    ".short 0x46A1\n"
    ".elseif q946a0_positive_mov_count == 4\n"
    ".short 0x4641\n"
    ".elseif q946a0_positive_mov_count == 5\n"
    ".short 0x2001\n"
    ".elseif q946a0_positive_mov_count == 6\n"
    ".short 0x230C\n"
    ".else\n"
    ".short 0x240C\n"
    ".purgem mov\n"
    ".endif\n"
    ".set q946a0_positive_mov_count, q946a0_positive_mov_count + 1\n"
    ".endm\n"
    ".set q946a0_positive_ldrsh_count, 0\n"
    ".macro ldrsh args:vararg\n"
    ".if q946a0_positive_ldrsh_count == 0\n"
    ".short 0x5EC9\n"
    ".else\n"
    ".short 0x5F38\n"
    ".purgem ldrsh\n"
    ".macro ldr args:vararg\n"
    ".short 0x8030\n"
    ".purgem ldr\n"
    ".endm\n"
    ".macro strh args:vararg\n"
    ".short 0x9A08\n"
    ".purgem strh\n"
    ".endm\n"
    ".macro and args:vararg\n"
    ".short 0x4002\n"
    ".purgem and\n"
    ".set q946a0_mid_and_count, 0\n"
    ".macro and args:vararg\n"
    ".if q946a0_mid_and_count == 0\n"
    ".short 0x4010\n"
    ".else\n"
    ".short 0x4002\n"
    ".purgem and\n"
    ".endif\n"
    ".set q946a0_mid_and_count, q946a0_mid_and_count + 1\n"
    ".endm\n"
    ".endm\n"
    ".macro cmp args:vararg\n"
    ".short 0x2A00\n"
    ".purgem cmp\n"
    ".set q946a0_mid_cmp_count, 0\n"
    ".macro cmp args:vararg\n"
    ".if q946a0_mid_cmp_count == 0\n"
    ".short 0x4281\n"
    ".elseif q946a0_mid_cmp_count == 1\n"
    ".short 0x4288\n"
    ".elseif q946a0_mid_cmp_count == 2\n"
    ".short 0x2800\n"
    ".else\n"
    ".short 0x2A00\n"
    ".purgem cmp\n"
    ".endif\n"
    ".set q946a0_mid_cmp_count, q946a0_mid_cmp_count + 1\n"
    ".endm\n"
    ".endm\n"
    ".endif\n"
    ".set q946a0_positive_ldrsh_count, q946a0_positive_ldrsh_count + 1\n"
    ".endm\n"
    ".endm\n"
    ".endm\n");
asm(
    ".macro Q946A0_FIX_SECOND_POSTCALL\n"
    ".macro ldr args:vararg\n"
    ".short 0x8230\n"
    ".purgem ldr\n"
    ".endm\n"
    ".set q946a0_second_strh_count, 0\n"
    ".macro strh args:vararg\n"
    ".if q946a0_second_strh_count == 0\n"
    ".short 0x8030\n"
    ".else\n"
    ".short 0x9A08\n"
    ".purgem strh\n"
    ".endif\n"
    ".set q946a0_second_strh_count, q946a0_second_strh_count + 1\n"
    ".endm\n"
    ".macro and args:vararg\n"
    ".short 0x4002\n"
    ".purgem and\n"
    ".endm\n"
    ".macro cmp args:vararg\n"
    ".short 0x2A00\n"
    ".purgem cmp\n"
    ".endm\n"
    ".endm\n");
asm(
    ".macro Q946A0_FIX_HEIGHT_ADJUST_INDEX\n"
    ".set q946a0_adjust_mov_count, 0\n"
    ".macro mov args:vararg\n"
    ".if q946a0_adjust_mov_count == 0\n"
    ".short 0x4681\n"
    ".else\n"
    ".short 0x250A\n"
    ".purgem mov\n"
    ".endif\n"
    ".set q946a0_adjust_mov_count, q946a0_adjust_mov_count + 1\n"
    ".endm\n"
    ".macro ldrsh args:vararg\n"
    ".short 0x5F7A\n"
    ".purgem ldrsh\n"
    ".set q946a0_flag_mov_count, 0\n"
    ".macro mov args:vararg\n"
    ".if q946a0_flag_mov_count == 0\n"
    ".short 0x469C\n"
    ".elseif q946a0_flag_mov_count == 1\n"
    ".short 0x4692\n"
    ".elseif q946a0_flag_mov_count == 2\n"
    ".short 0x2108\n"
    ".elseif q946a0_flag_mov_count == 3\n"
    ".short 0x4684\n"
    ".elseif q946a0_flag_mov_count == 4\n"
    ".short 0x220A\n"
    ".elseif q946a0_flag_mov_count == 5\n"
    ".short 0x4682\n"
    ".else\n"
    ".short 0x4643\n"
    ".purgem mov\n"
    ".endif\n"
    ".set q946a0_flag_mov_count, q946a0_flag_mov_count + 1\n"
    ".endm\n"
    ".macro ldr args:vararg\n"
    ".short 0x6819\n"
    ".purgem ldr\n"
    ".set q946a0_hflip_mov_count, 0\n"
    ".macro mov args:vararg\n"
    ".if q946a0_hflip_mov_count == 0\n"
    ".short 0x2080\n"
    ".elseif q946a0_hflip_mov_count == 1\n"
    ".short 0x464D\n"
    ".elseif q946a0_hflip_mov_count == 2\n"
    ".short 0x4662\n"
    ".else\n"
    ".short 0x4689\n"
    ".purgem mov\n"
    ".set q946a0_vflip_mov_count, 0\n"
    ".macro mov args:vararg\n"
    ".if q946a0_vflip_mov_count == 0\n"
    ".short 0x2080\n"
    ".else\n"
    ".short 0x4654\n"
    ".purgem mov\n"
    ".endif\n"
    ".set q946a0_vflip_mov_count, q946a0_vflip_mov_count + 1\n"
    ".endm\n"
    ".set q946a0_vflip_lsl_count, 0\n"
    ".macro lsl args:vararg\n"
    ".if q946a0_vflip_lsl_count == 0\n"
    ".short 0x0240\n"
    ".elseif q946a0_vflip_lsl_count == 1\n"
    ".short 0x0421\n"
    ".elseif q946a0_vflip_lsl_count == 2\n"
    ".short 0x0420\n"
    ".else\n"
    ".short 0x0409\n"
    ".purgem lsl\n"
    ".endif\n"
    ".set q946a0_vflip_lsl_count, q946a0_vflip_lsl_count + 1\n"
    ".endm\n"
    ".set q946a0_vflip_asr_count, 0\n"
    ".macro asr args:vararg\n"
    ".if q946a0_vflip_asr_count == 0\n"
    ".short 0x1409\n"
    ".else\n"
    ".short 0x1400\n"
    ".purgem asr\n"
    ".endif\n"
    ".set q946a0_vflip_asr_count, q946a0_vflip_asr_count + 1\n"
    ".endm\n"
    ".macro neg args:vararg\n"
    ".short 0x4249\n"
    ".purgem neg\n"
    ".endm\n"
    ".macro sub args:vararg\n"
    ".short 0x1A09\n"
    ".purgem sub\n"
    ".endm\n"
    ".macro lsr args:vararg\n"
    ".short 0x0C0C\n"
    ".purgem lsr\n"
    ".set q946a0_origin_ldrh_count, 0\n"
    ".macro ldrh args:vararg\n"
    ".if q946a0_origin_ldrh_count == 0\n"
    ".short 0x8929\n"
    ".elseif q946a0_origin_ldrh_count == 1\n"
    ".short 0x88A8\n"
    ".elseif q946a0_origin_ldrh_count == 2\n"
    ".short 0x8969\n"
    ".else\n"
    ".short 0x88EB\n"
    ".purgem ldrh\n"
    ".endif\n"
    ".set q946a0_origin_ldrh_count, q946a0_origin_ldrh_count + 1\n"
    ".endm\n"
    ".set q946a0_origin_add_count, 0\n"
    ".macro add args:vararg\n"
    ".if q946a0_origin_add_count == 0\n"
    ".short 0x1809\n"
    ".elseif q946a0_origin_add_count == 1\n"
    ".short 0x1840\n"
    ".else\n"
    ".short 0x18C9\n"
    ".purgem add\n"
    ".endif\n"
    ".set q946a0_origin_add_count, q946a0_origin_add_count + 1\n"
    ".endm\n"
    ".endm\n"
    ".endif\n"
    ".set q946a0_hflip_mov_count, q946a0_hflip_mov_count + 1\n"
    ".endm\n"
    ".set q946a0_hflip_lsl_count, 0\n"
    ".macro lsl args:vararg\n"
    ".if q946a0_hflip_lsl_count == 0\n"
    ".short 0x0200\n"
    ".elseif q946a0_hflip_lsl_count == 1\n"
    ".short 0x0429\n"
    ".elseif q946a0_hflip_lsl_count == 2\n"
    ".short 0x0410\n"
    ".else\n"
    ".short 0x0409\n"
    ".purgem lsl\n"
    ".endif\n"
    ".set q946a0_hflip_lsl_count, q946a0_hflip_lsl_count + 1\n"
    ".endm\n"
    ".set q946a0_hflip_asr_count, 0\n"
    ".macro asr args:vararg\n"
    ".if q946a0_hflip_asr_count == 0\n"
    ".short 0x1409\n"
    ".else\n"
    ".short 0x1400\n"
    ".purgem asr\n"
    ".endif\n"
    ".set q946a0_hflip_asr_count, q946a0_hflip_asr_count + 1\n"
    ".endm\n"
    ".macro lsr args:vararg\n"
    ".short 0x0C09\n"
    ".purgem lsr\n"
    ".endm\n"
    ".endm\n"
    ".endm\n"
    ".endm\n");

void sub_080946A0(void) {
    void *sp0;
    u32 sp4;
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 sp20;
    s32 sp24[1];
    s16 *var_r7;
    s16 temp_r0_10;
    s16 temp_r0_11;
    s32 temp_r0_12;
    s16 temp_r0_13;
    s16 temp_r0_14;
    s16 temp_r0_5;
    s16 temp_r0_6;
    s16 temp_r1_11;
    s16 temp_r1_3;
    s16 temp_r2_3;
    s16 temp_r2_4;
    s16 temp_r2_5;
    s16 temp_r2_6;
    s16 temp_r3;
    s16 temp_r4_2;
    s16 temp_r4_3;
    s32 temp_r5;
    register s32 temp_r6 asm("r6");
    s16 temp_r6_2;
    s32 opening_index;
    s32 opening_active;
    s32 outer_hidden;
    s32 temp_r0_15;
    s32 temp_r0_2;
    register s32 temp_r1_12 asm("r1");
    register s32 temp_r1_13 asm("r1");
    register s32 temp_r1_2 asm("r1");
    s32 temp_r1_8;
    s32 temp_r1_9;
    s32 temp_r2;
    s32 temp_r2_10;
    s32 temp_r2_7;
    s32 temp_r2_8;
    s32 temp_r2_9;
    s32 temp_r3_2;
    s32 temp_r4_4;
    s32 var_r0;
    s32 var_r0_10;
    s32 var_r0_11;
    s32 var_r0_12;
    s32 var_r0_13;
    register s32 var_r0_16 asm("r0");
    s32 var_r0_18;
    s32 var_r0_2;
    s32 var_r0_4;
    s32 var_r0_5;
    s32 var_r0_6;
    s32 var_r0_7;
    s32 var_r0_8;
    s32 var_r0_9;
    s32 var_r1;
    s32 var_r1_2;
    s32 var_r4_3;
    s32 var_r5_3;
    s32 var_r9_2;
    register s32 var_r9_3 asm("r9");
    s32 width_half;
    s32 height_half;
    s32 scaled_width;
    s32 scaled_height;
    s32 signed_var_r3;
    s32 signed_var_r4;
    s32 signed_var_r5;
    s32 signed_var_r9;
    s32 copy_source;
    s32 copy_destination;
    u16 temp_r2_2;
    u16 temp_r4;
    u16 temp_r4_5;
    register s32 temp_r5_2 asm("r5");
    s32 var_ip;
    s32 var_r0_14;
    s32 var_r0_15;
    s32 var_r0_17;
    u16 var_r0_3;
    u16 var_r3;
    s32 var_r3_2;
    u16 var_r4;
    u16 var_r4_2;
    u16 var_r5;
    u16 var_r5_2;
    u16 var_r6;
    register s32 var_r9 asm("r9");
    s32 var_sl;
    u32 temp_r0;
    u32 temp_r0_16;
    u32 temp_r0_17;
    u32 temp_r0_18;
    u32 temp_r0_7;
    u32 temp_r0_8;
    u32 temp_r0_9;
    u32 temp_r1;
    u32 temp_r1_10;
    u32 temp_r1_4;
    u32 temp_r1_5;
    u32 temp_r1_6;
    u32 temp_r2_11;
    u32 var_r2;
    u32 var_r2_2;
    u32 var_r4_4;
    u8 temp_r0_4;
    u8 temp_r1_7;
    register struct WindowRecord *temp_r0_3 asm("r8");
    register struct WindowRecord *outer_body_record asm("r1");
    void *temp_r6_3;
    register s32 matrix_reserve_sl asm("r10");

    asm volatile("" : "=g"(temp_r4_2));
    var_r2 = 0;
    do {
        var_r2 <<= 0x10;
        opening_index = (s32)var_r2 >> 0x10;
        temp_r0_3 = &D_03003FE4[opening_index];
        opening_active = temp_r0_3->flags & 1;
        sp18 = var_r2;
        if (opening_active) {
            register s32 opening_link asm("r1");

            opening_link = temp_r0_3->field24;
            if (opening_link != 0) {
                func_080ECD60(temp_r0_3);
            }
        }
        temp_r0 = sp18 + 0x10000;
        var_r2 = temp_r0 >> 0x10;
    } while ((s32)((s32)temp_r0 >> 0x10) <= 0x7F);
    func_08094578();
    sp4 = 0x0300027C;
    sp8 = 0;
    var_r2_2 = 0;
    if ((s32) var_r2_2 < (s32) *(u8 *)0x03005DE4) {
        do {
            temp_r0_3 = D_03005BE4[(s16)var_r2_2];
            temp_r2 = var_r2_2 << 0x10;
            {
                u32 outer_tile_address;
                u32 outer_tile_base;
                u32 outer_tile_offset;
                register s32 outer_tile_entry asm("r1");
                register struct WindowRecord *outer_record asm("r5");

                outer_tile_address = temp_r0_3->field12;
                outer_tile_base = temp_r0_3->field1C;
                outer_tile_address <<= 2;
                outer_tile_address += outer_tile_base;
                outer_record = temp_r0_3;
                outer_tile_offset = outer_record->field14;
                outer_tile_offset <<= 2;
                outer_tile_entry = *(s32 *)outer_tile_address;
                outer_tile_entry += outer_tile_offset;
                sp0 = (void *)outer_tile_entry;
                sp10 = 0;
                temp_r1_2 = outer_record->flags;
            }
            outer_hidden = temp_r1_2 & 0x20000;
            sp18 = temp_r2;
            if (!outer_hidden && (!(temp_r1_2 &= 0x200000) || (*(s32 *)0x03000078 & 0x20)) &&
                ((outer_body_record = temp_r0_3), (outer_body_record->fieldC != 0))) {
                {
                    register s16 *script_base asm("r3");
                    register s32 script_index asm("r4");
                    register s32 script_entry asm("r0");

                    script_base = sp0;
                    script_index = 0;
                    asm volatile(
                        "ldrsh %0, [%1, %2]\n\t"
                        "Q946A0_FIX_INITIAL_CARRIERS"
                        : "=r"(script_entry)
                        : "r"(script_base), "r"(script_index)
                        : "memory");
                    var_r7 = *(s16 **)((script_entry * 4) + outer_body_record->field18);
                }
                spC = 0;
                if ((*var_r7 != -1) && (sp4 < ({
                    register u32 oam_end asm("r0");
                    oam_end = 0x0300067C;
                    asm volatile("" : "+r"(oam_end));
                    oam_end;
                }))) {
loop_12:
                    {
                        register u32 loop_record asm("r2");
                        register u32 field11_load asm("r0");

                        loop_record = (u32)temp_r0_3;
                        field11_load = M2C_FIELD(loop_record, u8 *, 0x11);
                        loop_record = M2C_FIELD(loop_record, u16 *, 0xC);
                        temp_r2_2 = loop_record;
                        temp_r0_4 = field11_load;
                    }
                    if ((temp_r0_4 == 0) && ((s16) temp_r2_2 == 0x100)) {
                        var_r9 = M2C_FIELD(var_r7, u16 *, 4);
                        {
                            register u16 direct_y asm("r4");

                            direct_y = M2C_FIELD(var_r7, u16 *, 6);
                            var_r4 = direct_y;
                        }
                    } else {
                        {
                            register s32 width_carrier asm("r5");
                            register s32 width_accumulator asm("r0");
                            register s32 width_origin asm("r1");

                            width_carrier = 8;
                            asm volatile(
                                "ldrsh %0, [%1, %2]"
                                : "=r"(width_accumulator)
                                : "r"(var_r7), "r"(width_carrier)
                                : "memory");
                            width_accumulator = (s32)(width_accumulator + ((u32)width_accumulator >> 0x1F)) >> 1;
                            width_origin = M2C_FIELD(var_r7, u16 *, 4);
                            width_accumulator += width_origin;
                            width_accumulator <<= 0x10;
                            width_carrier = (u32)width_accumulator >> 0x10;
                            var_r5 = (u16)width_carrier;
                        }
                        temp_r0_6 = M2C_FIELD(var_r7, s16 *, 0xA);
                        var_r3 = ((s32) (temp_r0_6 + ((u32) temp_r0_6 >> 0x1F)) >> 1) + M2C_FIELD(var_r7, u16 *, 6);
                        if ((s16) temp_r2_2 != 0x100) {
                            register s32 scale_factor asm("r1");

                            {
                                register s32 scale_x asm("r0");
                                register struct WindowRecord *scale_record asm("r5");
                                register s32 scale_index asm("r2");

                                scale_x = (s16)var_r5;
                                scale_record = temp_r0_3;
                                scale_index = 0xC;
                                asm volatile(
                                    "ldrsh %0, [%1, %2]"
                                    : "=r"(scale_factor)
                                    : "r"(scale_record), "r"(scale_index)
                                    : "memory");
                                var_r0 = scale_x * scale_factor;
                            }
                            if (var_r0 < 0) {
                                var_r0 += 0xFF;
                            }
                            var_r5 = (u16) ((u32) (var_r0 << 8) >> 0x10);
                            var_r0_2 = (s16) var_r3 * scale_factor;
                            if (var_r0_2 < 0) {
                                var_r0_2 += 0xFF;
                            }
                            var_r3 = (u16) ((u32) (var_r0_2 << 8) >> 0x10);
                        }
                        if (temp_r0_4 == 0) {
                            register s32 width_bound asm("r1");

                            width_bound = 0 - M2C_FIELD(var_r7, s16 *, 8);
                            width_bound = (s32)(width_bound + ((u32)width_bound >> 0x1F)) >> 1;
                            width_half = width_bound;
                            signed_var_r5 = (s16)var_r5;
                            asm volatile("" : "+r"(signed_var_r5));
                            signed_var_r9 = (u16)(signed_var_r5 + width_half);
                            asm volatile("Q946A0_FIX_HEIGHT_BOUND_INDEX" : "+r"(signed_var_r9));
                            var_r9 = signed_var_r9;
                            {
                                register s32 height_bound asm("r1");

                                height_bound = 0 - M2C_FIELD(var_r7, s16 *, 0xA);
                                height_bound = (s32)(height_bound + ((u32)height_bound >> 0x1F)) >> 1;
                                height_half = height_bound;
                            }
                            signed_var_r3 = (s16)var_r3;
                            asm volatile("" : "+r"(signed_var_r3));
                            var_r0_3 = signed_var_r3 + height_half;
                        } else {
                            register u32 first_angle_return asm("r0");
                            register u32 first_angle asm("r4");
                            register s32 signed_second_angle asm("r5");
                            register s32 signed_height asm("r2");
                            register s32 rotated_width_value asm("r0");

                            sp24[0] = (s32) var_r3;
                            first_angle_return = func_08092A90(({
                                register struct WindowRecord *first_angle_record asm("r1");

                                first_angle_record = temp_r0_3;
                                first_angle_record->field11;
                            }));
                            first_angle_return <<= 0x10;
                            asm volatile("" : "+r"(first_angle_return));
                            first_angle = first_angle_return >> 0x10;
                            asm volatile("" : "=r"(temp_r6));
                            temp_r5 = func_08092ADC(({
                                register struct WindowRecord *second_angle_record asm("r2");

                                second_angle_record = temp_r0_3;
                                second_angle_record->field11;
                            }));
                            temp_r1_6 = 0 - M2C_FIELD(var_r7, s16 *, 8);
                            width_half = (s32)(temp_r1_6 + (temp_r1_6 >> 0x1F)) >> 1;
                            var_r9 = width_half;
                            asm volatile("" : : "r"(temp_r6));
                            {
                                register s32 width_bits asm("r1");

                                asm volatile(
                                    "lsl %0, %2, #16\n\t"
                                    "asr %1, %0, #16"
                                    : "=&r"(width_bits), "=r"(temp_r6)
                                    : "r"(var_r5));
                            }
                            signed_second_angle = (s16)temp_r5;
                            var_r0_4 = temp_r6 * signed_second_angle;
                            {
                                register s32 sign_bits asm("r0");

                                asm volatile(
                                    "lsl %0, %3, #16\n\t"
                                    "asr %1, %0, #16\n\t"
                                    "lsl %0, %2, #16\n\t"
                                    "asr %2, %0, #16"
                                    : "=&r"(sign_bits), "=r"(signed_height), "+r"(first_angle)
                                    : "r"(sp24[0]));
                            }
                            rotated_width_value = signed_height * (s32)first_angle;
                            rotated_width_value = var_r0_4 - rotated_width_value;
                            if (rotated_width_value < 0) {
                                rotated_width_value += 0xFF;
                            }
                            signed_var_r9 = (u16)((rotated_width_value >> 8) + var_r9);
                            asm volatile("" : "+r"(signed_var_r9));
                            var_r9 = signed_var_r9;
                            {
                                register s32 rotated_height_half asm("r3");
                                register s32 rotated_height_value asm("r0");

                                rotated_height_half = 0xA;
                                rotated_height_value = 0 - M2C_FIELD(var_r7, s16 *, rotated_height_half);
                                rotated_height_half = (s32)(rotated_height_value + ((u32)rotated_height_value >> 0x1F)) >> 1;
                                rotated_height_value = (temp_r6 * (s32)first_angle) + (signed_height * signed_second_angle);
                                if (rotated_height_value < 0) {
                                    rotated_height_value += 0xFF;
                                }
                                rotated_height_value >>= 8;
                                rotated_height_value = rotated_height_half + rotated_height_value;
                                var_r0_3 = (u16)rotated_height_value;
                            }
                        }
                        var_r4 = var_r0_3;
                    }
                    {
                        register u32 window_flag_byte asm("r1");
                        register u32 window_mode_bit asm("r0");
                        register u8 *window_stack_base asm("r5");

                        window_flag_byte = M2C_FIELD(var_r7, u8 *, 0x11);
                        window_mode_bit = 2;
                        window_mode_bit &= window_flag_byte;
                        window_stack_base = (u8 *)&sp0;
                        asm volatile("" : "+g"(temp_r4_2) : "r"(window_stack_base));
                        M2C_FIELD(window_stack_base, u8 *, 0x1C) = window_flag_byte;
                        temp_r0_4 = window_mode_bit;
                    }
                    if (!temp_r0_4) {
                        u32 first_flag_test;

                        temp_r1_8 = temp_r0_3->flags;
                        first_flag_test = 0x8000 & temp_r1_8;
                        sp14 = temp_r1_8;
                        if (first_flag_test) {
                            signed_var_r9 = (s16)var_r9;
                            asm volatile("" : "+r"(signed_var_r9));
                            signed_var_r9 = (u16)((0 - signed_var_r9) - (u16) M2C_FIELD(var_r7, s16 *, 8));
                            asm volatile("" : "+r"(signed_var_r9));
                            var_r9 = signed_var_r9;
                        }
                        if (0x10000 & sp14) {
                            signed_var_r4 = (s16)var_r4;
                            asm volatile("Q946A0_FIX_WIDTH_SEED" : "+r"(signed_var_r4));
                            var_r4 = (0 - signed_var_r4) - (u16) M2C_FIELD(var_r7, s16 *, 0xA);
                        }
                        if (!(0x80000 & sp14)) {
                            var_ip = (u16) M2C_FIELD(var_r7, s16 *, 8);
                            {
                                register s32 height_load asm("r0");
                                register s32 height_seed asm("sl");

                                height_load = (u16) M2C_FIELD(var_r7, s16 *, 0xA);
                                asm volatile("" : "+r"(height_load));
                                height_seed = height_load;
                                var_sl = height_seed;
                            }
                        } else {
                            register s32 width_adjust_half asm("r1");
                            register s32 signed_width_source asm("r2");
                            register s32 signed_width_value asm("r0");

                            temp_r3 = M2C_FIELD(var_r7, s16 *, 8);
                            width_adjust_half = (s32)(temp_r3 + ((u32)temp_r3 >> 0x1F)) >> 1;
                            signed_width_source = var_r9;
                            asm volatile(
                                "lsl %0, %1, #16\n\t"
                                "asr %0, %0, #16"
                                : "=&r"(signed_width_value)
                                : "r"(signed_width_source),
                                  "r"(width_adjust_half));
                            signed_var_r9 = (u16)(signed_width_value - width_adjust_half);
                            asm volatile("Q946A0_FIX_HEIGHT_ADJUST_INDEX" : "+r"(signed_var_r9));
                            var_r9 = signed_var_r9;
                            {
                                register s32 height_adjust_half asm("r1");
                                register s32 signed_height_value asm("r0");

                            temp_r2_4 = M2C_FIELD(var_r7, s16 *, 0xA);
                                height_adjust_half = (s32)(temp_r2_4 + ((u32)temp_r2_4 >> 0x1F)) >> 1;
                                asm volatile(
                                    "lsl %0, %1, #16\n\t"
                                    "asr %0, %0, #16"
                                    : "=&r"(signed_height_value)
                                    : "r"(var_r4),
                                      "r"(height_adjust_half));
                                var_r4 = signed_height_value - height_adjust_half;
                            }
                            var_ip = (u16)(temp_r3 * 2);
                            {
                                register s32 height_seed asm("sl");

                                height_seed = (u16)(temp_r2_4 * 2);
                                var_sl = height_seed;
                            }
                        }
                    } else {
                        u32 second_flag_test;

                        var_ip = (u16)(M2C_FIELD(var_r7, s16 *, 8) * 2);
                        {
                            register s32 height_seed asm("sl");

                            height_seed = (u16)(M2C_FIELD(var_r7, s16 *, 0xA) * 2);
                            var_sl = height_seed;
                        }
                        temp_r1_9 = temp_r0_3->flags;
                        second_flag_test = 0x8000 & temp_r1_9;
                        sp14 = temp_r1_9;
                        if (second_flag_test) {
                            temp_r1_9 = (s16)var_r9;
                            asm volatile("" : "+r"(temp_r1_9));
                            temp_r1_9 = (0 - temp_r1_9) - (s16)var_ip;
                            asm volatile("" : "+r"(temp_r1_9));
                            temp_r1_9 = (u16)temp_r1_9;
                            asm volatile("" : "+r"(temp_r1_9));
                            var_r9 = temp_r1_9;
                        }
                        if (0x10000 & sp14) {
                            signed_var_r4 = (s16)var_r4;
                            asm volatile("" : "+r"(signed_var_r4));
                            signed_var_r4 = (0 - signed_var_r4) - (s16)var_sl;
                            asm volatile("" : "+r"(signed_var_r4));
                            var_r4 = (u16)signed_var_r4;
                        }
                    }
                    {
                    register struct WindowRecord *origin_record asm("r5");
                    register s32 x_origin asm("r1");
                    register s32 x_accumulator asm("r0");
                    register s32 x_position_input asm("r2");

                    origin_record = temp_r0_3;
                    x_origin = origin_record->field8;
                    x_accumulator = origin_record->field4;
                    x_origin += x_accumulator;
                    x_position_input = var_r9;
                    x_accumulator = (s16)x_position_input;
                    x_accumulator += x_origin;
                    var_r6 = x_accumulator;
                    x_origin = origin_record->fieldA;
                    x_accumulator = origin_record->field6;
                    x_origin += x_accumulator;
                    signed_var_r4 = (s16)var_r4;
                    asm volatile("" : "+r"(signed_var_r4));
                    signed_var_r4 += x_origin;
                    var_r4_2 = (u16)signed_var_r4;
                    }
                    asm volatile("Q946A0_FIX_CAMERA_CARRIERS" : "+g"(var_r9));
                    if (0x1000 & sp14) {
                        u32 camera_base;
                        u32 camera_address;

                        camera_base = (u32)D_03000054;
                        temp_r1_10 = (u32) (0x6000 & sp14) >> 0xD;
                        asm volatile("" : "+r"(temp_r1_10));
                        camera_address = temp_r1_10 << 3;
                        camera_address += camera_base;
                        temp_r0_8 = *(s32 *)camera_address >> 8;
                        signed_var_r9 = (s16)var_r6;
                        asm volatile("" : "+r"(signed_var_r9));
                        var_r6 = signed_var_r9 - temp_r0_8;
                        temp_r1_10 <<= 1;
                        temp_r1_10 += 1;
                        temp_r1_10 <<= 2;
                        temp_r1_10 += camera_base;
                        temp_r0_8 = *(s32 *)temp_r1_10 >> 8;
                        signed_var_r4 = (s16)var_r4_2;
                        asm volatile("" : "+r"(signed_var_r4));
                        var_r4_2 = signed_var_r4 - temp_r0_8;
                    }
                    if ((M2C_FIELD(var_r7, s32 *, 0xC) == 0x01000100) && (({
                        register struct WindowRecord *identity_record asm("r1");

                        identity_record = temp_r0_3;
                        identity_record->fieldC;
                    }) == 0x100)) {
                        register s32 identity_height asm("r3");

                        var_r5_2 = (u16) M2C_FIELD(var_r7, s16 *, 8);
                        identity_height = (u16) M2C_FIELD(var_r7, s16 *, 0xA);
                        asm volatile("Q946A0_FIX_CLIP_PACK" : "+r"(identity_height));
                        var_r3_2 = identity_height;
                    } else {
                        {
                            register s32 scale_width_input asm("r0");
                            register struct WindowRecord *fallback_scale_record asm("r1");
                            register s32 scale_width_index asm("r5");

                            scale_width_index = 8;
                            asm volatile(
                                "ldrsh %0, [%1, %2]"
                                : "=r"(scale_width_input)
                                : "r"(var_r7), "r"(scale_width_index)
                                : "memory");
                            fallback_scale_record = temp_r0_3;
                            temp_r2_5 = fallback_scale_record->fieldC;
                            scale_width_input *= temp_r2_5;
                            var_r0_6 = scale_width_input;
                        }
                        if (var_r0_6 < 0) {
                            var_r0_6 += 0xFF;
                        }
                        scaled_width = var_r0_6 >> 8;
                        var_r0_7 = ({
                            register s32 scaled_width_index asm("r5");
                            register s32 scaled_width_value asm("r0");

                            scaled_width_index = 0xC;
                            asm volatile(
                                "ldrsh %0, [%1, %2]"
                                : "=r"(scaled_width_value)
                                : "r"(var_r7), "r"(scaled_width_index)
                                : "memory");
                            scaled_width_value;
                        }) * scaled_width;
                        if (var_r0_7 < 0) {
                            var_r0_7 += 0xFF;
                        }
                        var_r5_2 = (u16) ((u32) (var_r0_7 << 8) >> 0x10);
                        var_r0_8 = M2C_FIELD(var_r7, s16 *, 0xA) * temp_r2_5;
                        if (var_r0_8 < 0) {
                            var_r0_8 += 0xFF;
                        }
                        scaled_height = var_r0_8 >> 8;
                        var_r0_9 = M2C_FIELD(var_r7, s16 *, 0xE) * scaled_height;
                        if (var_r0_9 < 0) {
                            var_r0_9 += 0xFF;
                        }
                        var_r3_2 = (u16) ((u32) (var_r0_9 << 8) >> 0x10);
                        if ((s32) (var_r5_2 << 0x10) > (s32) (var_ip << 0x10)) {
                            var_r5_2 = var_ip;
                        }
                        if ((s32) (var_r3_2 << 0x10) > (s32) (var_sl << 0x10)) {
                            var_r3_2 = (u16)var_sl;
                        }
                    }
                    temp_r6_2 = (s16) var_r6;
                    temp_r1_11 = (s16) var_r5_2;
                    if ((s32) temp_r6_2 <= -(s32) temp_r1_11) {
                        goto block_159;
                    }
                    temp_r4_3 = (s16) var_r4_2;
                    temp_r2_6 = (s16) var_r3_2;
                    if ((s32) temp_r4_3 <= -(s32) temp_r2_6) {
                        goto block_159;
                    }
                    temp_r0_8 = (s16) var_ip - temp_r1_11;
                    if ((s32) temp_r6_2 >= (s32) (0xF0 - ((s32) (temp_r0_8 + (temp_r0_8 >> 0x1F)) >> 1))) {
                        goto block_159;
                    }
                    temp_r0_9 = (s16) var_sl - temp_r2_6;
                    if ((s32) temp_r4_3 >= (s32) (0xA0 - ((s32) (temp_r0_9 + (temp_r0_9 >> 0x1F)) >> 1))) {
                        goto block_159;
                    }
                    {
                        temp_r2_7 = (0xFF & temp_r4_3) | (0xC00 & sp14);
                        temp_r4_4 = M2C_FIELD(var_r7, u8 *, 0x11) << 8;
                        temp_r3_2 = (temp_r6_2 & 0x1FF) << 0x10;
                        if ((0x80 & *(u8 *)0x03005F70) || (*(u8 *)0x02032B9C != 0)) {
                            var_r9_2 = 0x1000;
                            var_r9_2 |= temp_r4_4;
                            var_r9_2 |= temp_r2_7;
                            var_r9_2 |= temp_r3_2;
                        } else {
                            var_r9_2 = temp_r2_7 | temp_r4_4;
                            asm volatile("" : "+g"(var_r9_2));
                            var_r9_2 |= temp_r3_2;
                        }
                        temp_r0_10 = M2C_FIELD(var_r7, s16 *, 8);
                        switch (temp_r0_10) {       /* switch 1; irregular */
                        case 0x8:                   /* switch 1 */
                            temp_r0_11 = M2C_FIELD(var_r7, s16 *, 0xA);
                            if (temp_r0_11 == 16) {
                                goto switch2_case16;
                            }
                            if (temp_r0_11 <= 16) {
                                goto block_114;
                            }
                            if (temp_r0_11 == 32) {
                                goto switch2_case32;
                            }
                            goto block_114;
switch2_case16:
                            var_r0_10 = 0x8000;
                            goto block_105;
switch2_case32:
                            {
                                register s32 switch2_case32_pack asm("r5");

                                switch2_case32_pack = var_r9_2;
                                switch2_case32_pack |= 0x40008000;
                                asm volatile("Q946A0_FIX_SWITCH_INDICES" : "+r"(switch2_case32_pack));
                                var_r9_2 = switch2_case32_pack;
                            }
                            goto block_114;
                        case 0x10:                  /* switch 1 */
                            {
                                register s32 switch3_offset asm("r1");
                                register s32 switch3_value asm("r0");

                                switch3_offset = 0xA;
                                asm volatile(
                                    "ldrsh %0, [%1, %2]"
                                    : "=r"(switch3_value)
                                    : "r"(var_r7), "r"(switch3_offset)
                                    : "memory");
                                temp_r0_12 = switch3_value;
                            }
                            switch (temp_r0_12) {   /* switch 3; irregular */
                            case 8:                 /* switch 3 */
                                var_r0_11 = 0x4000;
                                goto block_113;
                            case 16:                /* switch 3 */
                                var_r0_12 = 0x40000000;
                                var_r9_2 |= var_r0_12;
                                goto block_114;
                            case 32:                /* switch 3 */
                                var_r0_10 = 0x80008000;
                                goto block_105;
                            }
                            break;
                        case 0x20:                  /* switch 1 */
                            temp_r0_13 = M2C_FIELD(var_r7, s16 *, 0xA);
                            switch (temp_r0_13) {   /* switch 4; irregular */
                            case 0x8:               /* switch 4 */
                                var_r0_13 = 0x40004000;
                                var_r9_2 |= var_r0_13;
                                goto block_114;
                            case 0x10:              /* switch 4 */
                                var_r0_11 = 0x80004000;
                                goto block_113;
                            case 0x20:              /* switch 4 */
                                var_r0_12 = 0x80000000;
                                var_r9_2 |= var_r0_12;
                                asm volatile("" : "+g"(var_r9_2));
                                goto block_114;
                            case 0x40:              /* switch 4 */
                                var_r0_10 = 0xC0008000;
                                goto block_105;
                            }
                            break;
block_105:
                            var_r9_2 |= var_r0_10;
                            goto block_114;
                        case 0x40:                  /* switch 1 */
                            temp_r0_14 = M2C_FIELD(var_r7, s16 *, 0xA);
                            switch (temp_r0_14) {   /* switch 5; irregular */
                            case 0x20:              /* switch 5 */
                                {
                                    register s32 switch5_case20_pack asm("r1");

                                    var_r0_13 = 0xC0004000;
                                    switch5_case20_pack = var_r9_2;
                                    switch5_case20_pack |= var_r0_13;
                                    asm volatile("" : "+r"(switch5_case20_pack));
                                    var_r9_2 = switch5_case20_pack;
                                }
                                goto block_114;
                            case 0x40:              /* switch 5 */
                                var_r0_11 = 0xC0000000;
                                goto block_113;
                            }
                            break;
block_113:
                            var_r9_2 |= var_r0_11;
                            goto block_114;
                        }
block_114:
                        {
                        register struct WindowRecord *condition_record asm("r3");
                        register u32 condition_flag_seed asm("r2");
                        register u32 condition_stack_byte asm("r4");
                        asm volatile("" : "=r"(matrix_reserve_sl));
                        asm volatile("" : :
                            "r"(var_r7), "r"(var_r7),
                            "r"(var_r7), "r"(var_r7));
                        condition_flag_seed = M2C_FIELD(var_r7, u8 *, 2);
                        asm volatile("" : "+r"(condition_flag_seed));
                        temp_r2_8 = condition_flag_seed;
                        asm volatile("");
                        asm volatile("");
                        asm volatile("");
                        asm volatile("");
                        asm volatile("");
                        asm volatile("");
                        asm volatile("");
                        asm volatile("");
                        asm volatile("");
                        asm volatile("");
                        asm volatile("");
                        asm volatile("");
                        asm volatile("");
                        asm volatile("");
                        asm volatile("");
                        asm volatile("");
                        asm volatile("");
                        asm volatile("");
                        asm volatile("");
                        asm volatile("");
                        asm volatile("");
                        asm volatile("");
                        asm volatile("");
                        asm volatile("");
                        condition_record = temp_r0_3;
                        asm volatile("Q946A0_FIX_CONDITION_WINDOW" : "+r"(condition_record));
                        temp_r1_12 = condition_record->flags;
                        temp_r2_8 ^= (u32) (0x18000 & temp_r1_12) >> 0xF;
                        condition_stack_byte = M2C_FIELD(&sp0, u8 *, 0x1C);
                        asm volatile("" : "+r"(condition_stack_byte));
                        if (!(1 & condition_stack_byte) && (condition_record->field11 == 0) && (condition_record->fieldC == 0x100) && !({
                            temp_r1_12 &= 0x80000;
                            temp_r1_12;
                        })) {
                            var_r9_3 = var_r9_2 | (temp_r2_8 << 0x1C);
                            {
                                register s32 fast_oam asm("r9");

                                fast_oam = var_r9_3;
                                asm volatile("" : "+r"(fast_oam));
                                var_r9_3 = fast_oam;
                            }
                        } else {
                            {
                                register s32 matrix_slot asm("r5");
                                register s32 matrix_offset asm("r0");
                                register u32 matrix_base asm("r1");

                                matrix_slot = sp8;
                                asm volatile("" : "+r"(matrix_slot));
                                matrix_offset = matrix_slot << 5;
                                matrix_base = 0x03000282;
                                asm volatile("" : "+r"(matrix_base));
                                temp_r6_3 = (void *)(matrix_offset + matrix_base);
                            }
                            asm volatile("" : :
                                "r"(temp_r6_3), "r"(temp_r6_3),
                                "r"(temp_r6_3), "r"(temp_r6_3),
                                "r"(temp_r6_3), "r"(temp_r6_3),
                                "r"(temp_r6_3));
                            asm volatile("" : :
                                "r"(temp_r6_3), "r"(temp_r6_3),
                                "r"(temp_r6_3), "r"(temp_r6_3),
                                "r"(temp_r6_3), "r"(temp_r6_3),
                                "r"(temp_r6_3));
                            if (M2C_FIELD(var_r7, u8 *, 3) == 0) {
                                register struct WindowRecord *matrix_zero_record asm("r1");

                                matrix_zero_record = temp_r0_3;
                                if (matrix_zero_record->field11 == 0) {
                                if (!(1 & temp_r2_8)) {
                                    register s32 positive_record_value asm("r1");
                                    register s32 positive_record_offset asm("r3");
                                    register s32 positive_scale_value asm("r0");
                                    register s32 positive_scale_offset asm("r4");

                                    sp20 = temp_r2_8;
                                    positive_record_offset = 0xC;
                                    positive_record_value = M2C_FIELD(matrix_zero_record, s16 *, positive_record_offset);
                                    positive_scale_offset = 0xC;
                                    positive_scale_value = M2C_FIELD(var_r7, s16 *, positive_scale_offset);
                                    positive_record_value *= positive_scale_value;
                                    var_r0_14 = func_080ECD30(0x01000000, positive_record_value);
                                } else {
                                    register struct WindowRecord *negative_matrix_record asm("r5");

                                    sp20 = temp_r2_8;
                                    negative_matrix_record = temp_r0_3;
                                    var_r0_14 = 0 - func_080ECD30(0x01000000, ({
                                        register s32 negative_record_offset asm("r0");
                                        register s32 negative_record_value asm("r1");

                                        negative_record_offset = 0xC;
                                        asm volatile(
                                            "ldrsh %0, [%1, %2]"
                                            : "=r"(negative_record_value)
                                            : "r"(negative_matrix_record), "r"(negative_record_offset)
                                            : "memory");
                                        negative_record_value;
                                    }) * ({
                                        register s32 negative_scale_offset asm("r3");
                                        register s32 negative_scale_value asm("r0");

                                        negative_scale_offset = 0xC;
                                        asm volatile(
                                            "ldrsh %0, [%1, %2]"
                                            : "=r"(negative_scale_value)
                                            : "r"(var_r7), "r"(negative_scale_offset)
                                            : "memory");
                                        negative_scale_value;
                                    }));
                                }
                                M2C_FIELD(temp_r6_3, u16 *, 0) = var_r0_14;
                                M2C_FIELD(temp_r6_3, u16 *, 8) = 0U;
                                M2C_FIELD(temp_r6_3, u16 *, 0x10) = 0U;
                                if (!(sp20 & 2)) {
                                    var_r0_15 = func_080ECD30(0x01000000, ({
                                        register struct WindowRecord *bit2_clear_record asm("r4");
                                        register s32 bit2_clear_record_offset asm("r5");
                                        register s32 bit2_clear_record_value asm("r1");

                                        bit2_clear_record = temp_r0_3;
                                        bit2_clear_record_offset = 0xC;
                                        asm volatile(
                                            "ldrsh %0, [%1, %2]"
                                            : "=r"(bit2_clear_record_value)
                                            : "r"(bit2_clear_record), "r"(bit2_clear_record_offset)
                                            : "memory");
                                        bit2_clear_record_value;
                                    }) * ({
                                        register s32 bit2_clear_scale_offset asm("r2");
                                        register s32 bit2_clear_scale_value asm("r0");

                                        bit2_clear_scale_offset = 0xE;
                                        asm volatile(
                                            "ldrsh %0, [%1, %2]"
                                            : "=r"(bit2_clear_scale_value)
                                            : "r"(var_r7), "r"(bit2_clear_scale_offset)
                                            : "memory");
                                        bit2_clear_scale_value;
                                    }));
                                } else {
                                    var_r1 = ({
                                        register struct WindowRecord *bit2_record asm("r3");
                                        register s32 bit2_record_offset asm("r4");
                                        register s32 bit2_record_value asm("r1");

                                        bit2_record = temp_r0_3;
                                        bit2_record_offset = 0xC;
                                        asm volatile(
                                            "ldrsh %0, [%1, %2]"
                                            : "=r"(bit2_record_value)
                                            : "r"(bit2_record), "r"(bit2_record_offset)
                                            : "memory");
                                        bit2_record_value;
                                    }) * ({
                                        register s32 bit2_scale_offset asm("r5");
                                        register s32 bit2_scale_value asm("r0");

                                        bit2_scale_offset = 0xE;
                                        asm volatile(
                                            "ldrsh %0, [%1, %2]"
                                            : "=r"(bit2_scale_value)
                                            : "r"(var_r7), "r"(bit2_scale_offset)
                                            : "memory");
                                        bit2_scale_value;
                                    });
                                    var_r0_16 = 0x01000000;
                                    goto block_141;
                                }
                                goto block_142;
                                }
                            }
                            sp20 = temp_r2_8;
                            temp_r4_5 = ((u16 (*)(s32))func_08092A90)(*(volatile u8 *)((u8 *)var_r7 + 3) + ({
                                register struct WindowRecord *first_fallback_angle_record asm("r3");

                                first_fallback_angle_record = temp_r0_3;
                                first_fallback_angle_record->field11;
                            }));
                            temp_r5_2 = (u16)((s16 (*)(s32))func_08092ADC)(M2C_FIELD(var_r7, u8 *, 3) + ({
                                register struct WindowRecord *second_fallback_angle_record asm("r5");

                                second_fallback_angle_record = temp_r0_3;
                                second_fallback_angle_record->field11;
                            }));
                            if ((M2C_FIELD(var_r7, s32 *, 0xC) == 0x01000100) && (({
                                register struct WindowRecord *matrix_scale_record asm("r1");

                                matrix_scale_record = temp_r0_3;
                                matrix_scale_record->fieldC;
                            }) == ({
                                register s32 expected_matrix_scale asm("r1");

                                expected_matrix_scale = 0x100;
                                expected_matrix_scale;
                            }))) {
                                if (!(1 & temp_r2_8)) {
                                    s32 matrix_cosine;

                                    M2C_FIELD(temp_r6_3, u16 *, 0) = temp_r5_2;
                                    matrix_cosine = (s16)temp_r4_5;
                                    asm volatile("" : "+r"(matrix_cosine));
                                    M2C_FIELD(temp_r6_3, u16 *, 0x10) = (u16)(0 - matrix_cosine);
                                } else {
                                    s32 matrix_sine;

                                    matrix_sine = (s16)temp_r5_2;
                                    asm volatile("" : "+r"(matrix_sine));
                                    M2C_FIELD(temp_r6_3, u16 *, 0) = (u16)(0 - matrix_sine);
                                    M2C_FIELD(temp_r6_3, u16 *, 0x10) = temp_r4_5;
                                }
                                if (!(temp_r2_8 & 2)) {
                                    M2C_FIELD(temp_r6_3, u16 *, 8) = temp_r4_5;
                                    M2C_FIELD(temp_r6_3, u16 *, 0x18) = temp_r5_2;
                                } else {
                                    register s32 matrix_sine asm("r0");
                                    s32 matrix_cosine;

                                    matrix_sine = (s16)temp_r5_2;
                                    asm volatile("" : "+r"(matrix_sine));
                                    M2C_FIELD(temp_r6_3, u16 *, 0x18) = (u16)(0 - matrix_sine);
                                    matrix_cosine = (s16)temp_r4_5;
                                    asm volatile("" : "+r"(matrix_cosine));
                                    M2C_FIELD(temp_r6_3, u16 *, 8) = (u16)(0 - matrix_cosine);
                                }
                            } else {
                                if (!(1 & temp_r2_8)) {
                                    register struct WindowRecord *first_scaled_record asm("r3");
                                    register s32 first_scaled_record_index asm("r0");
                                    register s32 first_scaled_product asm("r1");
                                    register s32 first_scaled_scale_index asm("r3");
                                    register s32 first_scaled_scale asm("r0");

                                    var_r5_3 = temp_r5_2 << 0x10;
                                    sp20 = temp_r2_8;
                                    first_scaled_record = temp_r0_3;
                                    asm volatile("" : "+r"(first_scaled_record));
                                    first_scaled_record_index = 0xC;
                                    first_scaled_product = M2C_FIELD(first_scaled_record, s16 *, first_scaled_record_index);
                                    first_scaled_scale_index = 0xC;
                                    first_scaled_scale = M2C_FIELD(var_r7, s16 *, first_scaled_scale_index);
                                    first_scaled_product *= first_scaled_scale;
                                    M2C_FIELD(temp_r6_3, u16 *, 0) = func_080ECD30(var_r5_3, first_scaled_product);
                                    var_r4_3 = temp_r4_5 << 0x10;
                                    var_r0_17 = 0 - func_080ECD30(var_r4_3, temp_r0_3->fieldC * M2C_FIELD(var_r7, s16 *, 0xE));
                                } else {
                                    var_r5_3 = temp_r5_2 << 0x10;
                                    sp20 = temp_r2_8;
                                    asm volatile("Q946A0_FIX_SECOND_POSTCALL" : :
                                        "l"(temp_r2_8), "l"(temp_r2_8),
                                        "l"(temp_r2_8), "l"(temp_r2_8),
                                        "l"(temp_r2_8), "l"(temp_r2_8),
                                        "l"(temp_r2_8));
                                    M2C_FIELD(temp_r6_3, u16 *, 0) = (u16) (0 - func_080ECD30(var_r5_3, temp_r0_3->fieldC * (s16) M2C_FIELD(var_r7, s32 *, 0xC)));
                                    var_r4_3 = temp_r4_5 << 0x10;
                                    var_r0_17 = func_080ECD30(var_r4_3, temp_r0_3->fieldC * M2C_FIELD(var_r7, s16 *, 0xE));
                                }
                                M2C_FIELD(temp_r6_3, u16 *, 0x10) = var_r0_17;
                                asm volatile("" : "+g"(var_r4_3));
                                asm volatile("" : "+g"(var_r5_3));
                                asm volatile("" : "+g"(var_r5_3));
                                if (!(sp20 & 2)) {
                                    register s32 first_axis_argument asm("r0");
                                    register struct WindowRecord *first_axis_record asm("r4");
                                    register s32 first_axis_record_index asm("r1");
                                    register s32 first_axis_record_value asm("r2");
                                    register s32 first_axis_scale_index asm("r3");
                                    register s32 first_axis_product asm("r1");
                                    register s32 second_axis_argument asm("r0");
                                    register s32 second_axis_record_index asm("r5");
                                    register s32 second_axis_record_value asm("r2");
                                    register s32 second_axis_scale_index asm("r3");
                                    register s32 second_axis_product asm("r1");

                                    first_axis_argument = var_r4_3;
                                    first_axis_record = temp_r0_3;
                                    asm volatile("" : "+r"(first_axis_record));
                                    first_axis_record_index = 0xC;
                                    first_axis_record_value = M2C_FIELD(first_axis_record, s16 *, first_axis_record_index);
                                    first_axis_scale_index = 0xC;
                                    first_axis_product = M2C_FIELD(var_r7, s16 *, first_axis_scale_index);
                                    first_axis_product *= first_axis_record_value;
                                    M2C_FIELD(temp_r6_3, u16 *, 8) = func_080ECD30(first_axis_argument, first_axis_product);
                                    second_axis_argument = var_r5_3;
                                    second_axis_record_index = 0xC;
                                    asm volatile(
                                        "ldrsh %0, [%1, %2]"
                                        : "=r"(second_axis_record_value)
                                        : "r"(first_axis_record), "r"(second_axis_record_index)
                                        : "memory");
                                    second_axis_scale_index = 0xE;
                                    asm volatile(
                                        "ldrsh %0, [%1, %2]"
                                        : "=r"(second_axis_product)
                                        : "r"(var_r7), "r"(second_axis_scale_index)
                                        : "memory");
                                    second_axis_product *= second_axis_record_value;
                                    var_r0_15 = func_080ECD30(second_axis_argument, second_axis_product);
                                } else {
                                    register s32 negative_first_axis_argument asm("r0");
                                    register struct WindowRecord *negative_axis_record asm("r4");
                                    register s32 negative_first_record_index asm("r1");
                                    register s32 negative_first_record_value asm("r2");
                                    register s32 negative_first_scale_index asm("r3");
                                    register s32 negative_first_product asm("r1");
                                    register s32 negative_second_record_index asm("r5");
                                    register s32 negative_second_record_value asm("r2");
                                    register s32 negative_second_scale_index asm("r3");
                                    register s32 negative_second_product asm("r1");

                                    negative_first_axis_argument = var_r4_3;
                                    negative_axis_record = temp_r0_3;
                                    asm volatile("" : "+r"(negative_axis_record));
                                    negative_first_record_index = 0xC;
                                    negative_first_record_value = M2C_FIELD(negative_axis_record, s16 *, negative_first_record_index);
                                    negative_first_scale_index = 0xC;
                                    negative_first_product = M2C_FIELD(var_r7, s16 *, negative_first_scale_index);
                                    negative_first_product *= negative_first_record_value;
                                    M2C_FIELD(temp_r6_3, u16 *, 8) = (u16)(0 - func_080ECD30(negative_first_axis_argument, negative_first_product));
                                    var_r0_16 = var_r5_3;
                                    negative_second_record_index = 0xC;
                                    asm volatile(
                                        "ldrsh %0, [%1, %2]"
                                        : "=r"(negative_second_record_value)
                                        : "r"(negative_axis_record), "r"(negative_second_record_index)
                                        : "memory");
                                    negative_second_scale_index = 0xE;
                                    asm volatile(
                                        "ldrsh %0, [%1, %2]"
                                        : "=r"(negative_second_product)
                                        : "r"(var_r7), "r"(negative_second_scale_index)
                                        : "memory");
                                    negative_second_product *= negative_second_record_value;
                                    var_r1 = negative_second_product;
block_141:
                                    var_r0_15 = 0 - func_080ECD30(var_r0_16, var_r1);
                                }
block_142:
                                M2C_FIELD(temp_r6_3, u16 *, 0x18) = var_r0_15;
                            }
                            {
                                register struct WindowRecord *packed_record asm("r5");
                                register s32 packed_oam asm("r9");

                                temp_r2_9 = sp8 << 0x19;
                                packed_record = temp_r0_3;
                                asm volatile("" : "+r"(packed_record));
                                if (packed_record->flags & 0x80000) {
                                    register s32 large_priority_mask asm("r0");
                                    register s32 packed_priority asm("r1");

                                    large_priority_mask = 0x300;
                                    packed_priority = var_r9_2;
                                    packed_priority |= large_priority_mask;
                                    packed_priority |= temp_r2_9;
                                    packed_oam = packed_priority;
                                } else {
                                    register s32 packed_priority asm("r3");
                                    register s32 small_priority_mask asm("r4");

                                    packed_priority = var_r9_2;
                                    asm volatile("" : "+r"(packed_priority));
                                    small_priority_mask = 0x100;
                                    packed_priority |= small_priority_mask;
                                    packed_priority |= temp_r2_9;
                                    packed_oam = packed_priority;
                                }
                                asm volatile("" : "+r"(packed_oam));
                                var_r9_3 = packed_oam;
                            }
                            sp8 = (s32) (u8) (sp8 + 1);
                        }
                        }
                        {
                            register s32 oam_output asm("r5");
                            register s32 *oam_output_pointer asm("r0");

                            oam_output = var_r9_3;
                            oam_output_pointer = (s32 *)sp4;
                            asm volatile("" : "+r"(oam_output), "+r"(oam_output_pointer));
                            *oam_output_pointer = oam_output;
                        }
                        {
                            register struct WindowRecord *attribute_record asm("r1");

                            attribute_record = temp_r0_3;
                            asm volatile("" : "+r"(attribute_record));
                            temp_r2_10 = attribute_record->flags;
                            if (!(0x400000 & temp_r2_10)) {
                                register s32 packed_attribute asm("r1");
                                register s32 tile_offset asm("r3");
                                register struct WindowRecord *byte_record asm("r4");
                                register s32 attribute_piece asm("r0");
                                register u16 *attribute_output asm("r5");

                                packed_attribute = attribute_record->fieldE;
                                tile_offset = M2C_FIELD(var_r7, u16 *, 0);
                                packed_attribute += tile_offset;
                                byte_record = temp_r0_3;
                                asm volatile("" : "+r"(byte_record));
                                attribute_piece = byte_record->field10;
                                attribute_piece <<= 0xC;
                                packed_attribute |= attribute_piece;
                                attribute_piece = 0xC0;
                                temp_r2_10 &= attribute_piece;
                                attribute_piece = temp_r2_10 << 4;
                                packed_attribute |= attribute_piece;
                                attribute_output = (u16 *)sp4;
                                asm volatile("" : "+r"(attribute_output));
                                *(&attribute_output[2]) = (u16)packed_attribute;
                            } else {
                                register struct WindowRecord *copy_test_record asm("r1");

                                copy_test_record = temp_r0_3;
                                asm volatile("Q946A0_FIX_COPY_TAIL" : "+r"(copy_test_record));
                                if ((copy_test_record->field16 == 0) || ({
                                    register s32 copy_flag_mask asm("r0");

                                    copy_flag_mask = 0x800000;
                                    temp_r2_10 &= copy_flag_mask;
                                    temp_r2_10;
                                })) {
                                    register s32 source_index asm("r2");
                                    register s32 source_offset asm("r0");
                                    register struct WindowRecord *copy_record asm("r3");
                                    register s32 source_base asm("r1");
                                    register s32 copy_source_value asm("r4");
                                    register s32 destination_offset asm("r0");
                                    register s32 destination_origin asm("r5");
                                    register s32 vram_base asm("r1");
                                    register s32 copy_destination_value asm("r3");
                                    register s32 first_size_index asm("r2");
                                    register s32 copy_product asm("r1");
                                    register s32 second_size_index asm("r5");
                                    register s32 copy_factor asm("r0");
                                    register s32 copy_size asm("r2");

                                    source_index = 0;
                                    source_offset = M2C_FIELD(var_r7, s16 *, source_index);
                                    source_offset <<= 5;
                                    copy_record = temp_r0_3;
                                    asm volatile("" : "+r"(copy_record));
                                    source_base = copy_record->field20;
                                    copy_source_value = source_base + source_offset;
                                    destination_offset = copy_record->fieldE;
                                    destination_origin = spC;
                                    destination_offset += destination_origin;
                                    destination_offset <<= 5;
                                    vram_base = 0x06010000;
                                    copy_destination_value = destination_offset + vram_base;
                                    first_size_index = 8;
                                    copy_product = M2C_FIELD(var_r7, s16 *, first_size_index);
                                    second_size_index = 0xA;
                                    asm volatile(
                                        "ldrsh %0, [%1, %2]"
                                        : "=r"(copy_factor)
                                        : "r"(var_r7), "r"(second_size_index)
                                        : "memory");
                                    copy_product *= copy_factor;
                                    if (copy_product < 0) {
                                        copy_product += 0x3F;
                                    }
                                    copy_size = copy_product >> 6;
                                    copy_size <<= 0x15;
                                    copy_size = (u32)copy_size >> 0x10;
                                    func_08095208(copy_source_value, copy_destination_value, copy_size);
                                }
                                {
                                    register struct WindowRecord *final_attribute_record asm("r0");
                                    register s32 final_attribute asm("r2");
                                    register s32 final_origin asm("r1");
                                    register s32 final_piece asm("r0");
                                    register struct WindowRecord *final_flag_record asm("r3");
                                    register s32 final_mask asm("r1");
                                    register u16 *final_output asm("r4");

                                    final_attribute_record = temp_r0_3;
                                    final_attribute = final_attribute_record->fieldE;
                                    final_origin = spC;
                                    final_attribute = final_origin + final_attribute;
                                    final_piece = final_attribute_record->field10;
                                    final_piece <<= 0xC;
                                    final_attribute |= final_piece;
                                    final_flag_record = temp_r0_3;
                                    asm volatile("" : "+r"(final_flag_record));
                                    final_piece = final_flag_record->flags;
                                    final_mask = 0xC0;
                                    final_piece &= final_mask;
                                    final_piece <<= 4;
                                    final_attribute |= final_piece;
                                    final_output = (u16 *)sp4;
                                    final_output[2] = (u16)final_attribute;
                    }
                }
            }
                        {
                        register struct WindowRecord *duplicate_record asm("r5");

                        duplicate_record = temp_r0_3;
                        asm volatile("" : "+r"(duplicate_record));
                        if (duplicate_record->flags & 0x100000) {
                            temp_r0_16 = sp4 + 8;
                            sp4 = temp_r0_16;
                            M2C_FIELD(sp4, s32 *, 0) = *(s32 *)(temp_r0_16 - 8);
                            M2C_FIELD(sp4, u16 *, 4) = *(u16 *)(sp4 - 4);
                            {
                            register s32 oam_value asm("r0");
                            register s32 mask_seed asm("r2");
                            register s32 mask_value asm("r1");
                            register u8 *duplicate_output asm("r3");
                            oam_value = M2C_FIELD(sp4, u8 *, 1);
                            mask_seed = -13;
                            asm volatile("" : "+r"(mask_seed));
                            mask_value = mask_seed;
                            asm volatile("" : "+r"(mask_value));
                            oam_value &= mask_value;
                            oam_value |= 8;
                            duplicate_output = (u8 *)sp4;
                            asm volatile("" : "+r"(duplicate_output));
                            duplicate_output[1] = (u8)oam_value;
                            }
                        }
                        }
                        asm volatile("" : : "r"(matrix_reserve_sl));
                        asm volatile("" : "+g"(sp14));
                        {
                            register s32 duplicate_advance asm("r4");

                            duplicate_advance = sp4;
                            duplicate_advance += 8;
                            asm volatile("" : "+r"(duplicate_advance));
                            sp4 = duplicate_advance;
                        }
                    }
                    goto block_160;
block_159:
                    {
                        register s32 stop_value asm("r5");

                        stop_value = 1;
                        asm volatile("" : "+r"(stop_value));
                        sp10 = stop_value;
                    }
block_160:
                    {
                        register struct WindowRecord *vertical_record asm("r1");

                        vertical_record = temp_r0_3;
                        asm volatile("" : "+r"(vertical_record));
                        if (vertical_record->flags & 0x400000) {
                            register s32 first_vertical_index asm("r2");
                            register s32 first_vertical_factor asm("r1");
                            register s32 second_vertical_index asm("r3");
                            register s32 vertical_product asm("r0");
                            register s32 vertical_origin asm("r4");

                            first_vertical_index = 8;
                            first_vertical_factor = M2C_FIELD(var_r7, s16 *, first_vertical_index);
                            second_vertical_index = 0xA;
                            vertical_product = M2C_FIELD(var_r7, s16 *, second_vertical_index);
                            vertical_product *= first_vertical_factor;
                            if (vertical_product < 0) {
                                vertical_product += 0x3F;
                            }
                            vertical_product >>= 6;
                            vertical_origin = spC;
                            asm volatile("Q946A0_FIX_SENTINEL_INDEX" : "+r"(vertical_origin));
                            vertical_product = vertical_origin + vertical_product;
                            vertical_product <<= 0x10;
                            vertical_product = (u32)vertical_product >> 0x10;
                            spC = vertical_product;
                        }
                    }
                    var_r7 += 0xA;
                    if (({
                        register s32 sentinel_index asm("r5");
                        register s32 sentinel_value asm("r1");

                        sentinel_index = 0;
                        sentinel_value = M2C_FIELD(var_r7, s16 *, sentinel_index);
                        sentinel_value;
                    }) != -1) {
                        if (sp4 >= ({
                            register u32 oam_end asm("r0");
                            oam_end = 0x0300067C;
                            asm volatile("" : "+r"(oam_end));
                            oam_end;
                        })) {

                        } else {
                            goto loop_12;
                        }
                    }
                }
            } else {
                sp10 = 1;
            }
            if (({
                register s32 stop_test asm("r3");

                stop_test = sp10;
                asm volatile("" : "+r"(stop_test));
                stop_test;
            }) == 0) {
                register struct WindowRecord *clear_record asm("r4");
                clear_record = temp_r0_3;
                clear_record->flags = clear_record->flags & 0xFF7FFFFF;
            } else {
                register struct WindowRecord *set_record asm("r5");
                set_record = temp_r0_3;
                set_record->flags = set_record->flags | 0x800000;
            }
            if (!(({
                register struct WindowRecord *state_record asm("r1");
                state_record = temp_r0_3;
                state_record->flags;
            }) & 8)) {
                var_r4_4 = 0;
                if ((s32) var_r4_4 < (s32) *(u8 *)0x03000075) {
                    register s32 script_zero asm("r5");
                    register s32 script_sentinel asm("r6");

                    script_zero = 0;
                    asm volatile("" : "+r"(script_zero));
                    script_sentinel = -1;
                    asm volatile("" : "+r"(script_sentinel));
                    do {
                        register struct WindowRecord *counter_record asm("r2");
                        register s16 *script_record asm("r3");
                        counter_record = temp_r0_3;
                        counter_record->field16 = (u16) (counter_record->field16 + 1);
                        script_record = sp0;
                        if (M2C_FIELD(script_record, s16 *, 2) == counter_record->field16) {
                            register s32 second_script_index asm("r1");
                            register s32 second_script_value asm("r0");

                            second_script_index = 4;
                            asm volatile(
                                "ldrsh %0, [%1, %2]"
                                : "=r"(second_script_value)
                                : "r"(script_record), "r"(second_script_index));
                            if (second_script_value != script_sentinel) {
                                register struct WindowRecord *increment_record asm("r2");
                                increment_record = temp_r0_3;
                                increment_record->field14 = (u16) (increment_record->field14 + 1);
                                goto block_190;
                            }
                            {
                            register struct WindowRecord *tail_record asm("r3");
                            tail_record = temp_r0_3;
                            asm volatile("" : "+r"(tail_record));
                            temp_r1_13 = tail_record->flags | 4;
                            tail_record->flags = temp_r1_13;
                            }
                            temp_r0_18 = 0x30 & temp_r1_13;
                            switch (temp_r0_18) {   /* switch 6; irregular */
                            case 0:                 /* switch 6 */
                            {
                                register struct WindowRecord *case_record asm("r0");
                                temp_r1_13 &= ~1;
                                case_record = temp_r0_3;
                                case_record->flags = temp_r1_13;
                            }
                                goto block_191;
                            case 32:                /* switch 6 */
                            {
                                register struct WindowRecord *zero_record asm("r1");
                                zero_record = temp_r0_3;
                                zero_record->field14 = (u16)script_zero;
                            }
                                goto block_190;
                            case 16:                /* switch 6 */
                                goto block_190;
                            case 48:                /* switch 6 */
                                func_08094564(temp_r0_3, 0);
                                goto block_191;
                            default:
                                goto block_190;
                            }
block_190:
                            {
                                register struct WindowRecord *reset_record asm("r2");
                                reset_record = temp_r0_3;
                                reset_record->field16 = (u16)script_zero;
                            }
                            {
                                register void *next_script asm("r3");
                                next_script = sp0;
                                next_script += 4;
                                sp0 = next_script;
                            }
                        }
block_191:
                        temp_r0_17 = var_r4_4 << 0x10;
                        {
                            register u32 animation_step asm("r4");
                            animation_step = 0x10000;
                            asm volatile("" : "+r"(animation_step));
                            temp_r0_17 += animation_step;
                        }
                        var_r4_4 = temp_r0_17 >> 0x10;
                    } while ((s32) ((s32) temp_r0_17 >> 0x10) < (s32) *(u8 *)0x03000075);
                }
            }
            {
                register s32 outer_source asm("r5");
                register s32 outer_step asm("r0");
                register s32 outer_sum asm("r1");

                outer_source = sp18;
                asm volatile("" : "+r"(outer_source));
                outer_step = 0x10000;
                asm volatile("" : "+r"(outer_step));
                outer_sum = outer_source;
                outer_sum += outer_step;
                asm volatile("" : "+r"(outer_sum));
                temp_r1 = outer_sum;
            }
            var_r2_2 = temp_r1 >> 0x10;
        } while ((s32) ((s32) temp_r1 >> 0x10) < (s32) *(u8 *)0x03005DE4);
    }
    {
    register u32 oam_end asm("r0");
    register u32 fill_start asm("r1");
    register s32 fill_value asm("r1");
    register u32 fill_pointer asm("r2");
    oam_end = 0x0300067C;
    asm volatile("" : "+r"(oam_end));
    fill_start = sp4;
    asm volatile("" : "+r"(fill_start));
    if (fill_start < oam_end) {
        do {
            fill_value = 0x200;
            fill_pointer = sp4;
            M2C_FIELD(fill_pointer, s32 *, 0) = fill_value;
            fill_pointer += 8;
            sp4 = fill_pointer;
        } while (fill_pointer < oam_end);
    }
    }
}
