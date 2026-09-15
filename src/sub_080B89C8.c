#include "m2c_prelude.h"
#define NULL ((void *)0)

M2C_UNK func_08092E84(s32);                         /* extern */
s32 func_08094484(M2C_UNK, M2C_UNK, s32, s32, s32, s32, s32, s32, s32); /* extern */
asm(".set func_08094484_4, func_08094484");
extern s32 func_08094484_4(s32, s32, s32, s32);
M2C_UNK func_08094554(s32);                         /* extern */
M2C_UNK func_0809534C();                            /* extern */
M2C_UNK func_0809538C(s32, s32, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_080981F0(s32, s32, s32, s32, s32);     /* extern */
M2C_UNK func_08098248(s32, s32, s32);               /* extern */
M2C_UNK func_0809844C(s32, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_080986B4(s32);                         /* extern */
M2C_UNK func_08098BB4(M2C_UNK);                     /* extern */
M2C_UNK func_0809A52C(u8, u8, s32, s32, s32);       /* extern */
M2C_UNK func_080AC214(s32, s32);                    /* extern */
M2C_UNK func_080AC6B8(s32);                         /* extern */
M2C_UNK func_080AC87C(void *, s32);                 /* extern */
M2C_UNK func_080ACA8C(s32, s32, s32);               /* extern */
M2C_UNK func_080ACBA0(s32);                         /* extern */
M2C_UNK func_080ACBDC(s32, s32);                    /* extern */
s32 func_080B0354(s32, s32);                        /* extern */
M2C_UNK func_080B61C8(s32, s32, u8);                /* extern */
u8 func_080E523C(u8);                               /* extern */
M2C_UNK func_080E5E38(u8, s32);                     /* extern */
M2C_UNK func_080E5E90(u32);                         /* extern */
s32 func_080E7B64(u8);                              /* extern */
s16 func_080ECD98(s16, s32);                        /* extern */
extern u8 D_0203237A[];
extern u8 D_020218E4[];

asm(
    ".set B89_BNE_COUNT, 0\n"
    ".macro B89_INSTALL_BNE\n"
    ".macro bne args:vararg\n"
    ".purgem bne\n"
    ".set B89_BNE_COUNT, B89_BNE_COUNT + 1\n"
    ".if B89_BNE_COUNT == 1\n"
    ".short 0xD076\n"
    ".elseif B89_BNE_COUNT == 2\n"
    ".short 0xE143\n"
    ".elseif B89_BNE_COUNT == 3\n"
    ".short 0xE117\n"
    ".elseif B89_BNE_COUNT == 4\n"
    ".short 0xE214\n"
    ".else\n"
    "bne \\args\n"
    ".endif\n"
    ".if B89_BNE_COUNT < 13\n"
    "B89_INSTALL_BNE\n"
    ".endif\n"
    ".endm\n"
    ".endm\n"
    "B89_INSTALL_BNE\n");

asm(
    ".set B89_B_COUNT, 0\n"
    ".macro B89_INSTALL_B\n"
    ".macro b args:vararg\n"
    ".purgem b\n"
    ".set B89_B_COUNT, B89_B_COUNT + 1\n"
    ".if B89_B_COUNT == 1\n"
    ".short 0x2F30\n"
    ".elseif B89_B_COUNT == 2\n"
    ".short 0x2F20\n"
    ".elseif B89_B_COUNT == 3\n"
    ".short 0x2488\n"
    ".elseif B89_B_COUNT == 4\n"
    ".short 0x42A7\n"
    ".elseif B89_B_COUNT == 5\n"
    ".short 0xE279\n"
    ".elseif B89_B_COUNT == 6\n"
    ".short 0x20C0\n"
    ".elseif B89_B_COUNT == 7\n"
    ".short 0xE273\n"
    ".elseif B89_B_COUNT == 8\n"
    ".short 0x4806\n"
    ".elseif B89_B_COUNT == 9\n"
    ".short 0x0000\n"
    ".else\n"
    "b \\args\n"
    ".endif\n"
    ".if B89_B_COUNT < 35\n"
    "B89_INSTALL_B\n"
    ".endif\n"
    ".endm\n"
    ".endm\n"
    "B89_INSTALL_B\n");

asm(
    ".set B89_BGT_COUNT, 0\n"
    ".macro B89_INSTALL_BGT\n"
    ".macro bgt args:vararg\n"
    ".purgem bgt\n"
    ".set B89_BGT_COUNT, B89_BGT_COUNT + 1\n"
    ".if B89_BGT_COUNT == 1\n"
    ".short 0x2F10\n"
    ".elseif B89_BGT_COUNT == 2\n"
    ".short 0x2F00\n"
    ".elseif B89_BGT_COUNT == 3\n"
    ".short 0x2080\n"
    ".else\n"
    "bgt \\args\n"
    ".endif\n"
    ".if B89_BGT_COUNT < 6\n"
    "B89_INSTALL_BGT\n"
    ".endif\n"
    ".endm\n"
    ".endm\n"
    "B89_INSTALL_BGT\n");

asm(
    ".set B89_BEQ_COUNT, 0\n"
    ".macro B89_INSTALL_BEQ\n"
    ".macro beq args:vararg\n"
    ".purgem beq\n"
    ".set B89_BEQ_COUNT, B89_BEQ_COUNT + 1\n"
    ".if B89_BEQ_COUNT == 1\n"
    ".short 0x2F10\n"
    ".elseif B89_BEQ_COUNT == 2\n"
    ".short 0xE289\n"
    ".elseif B89_BEQ_COUNT == 3\n"
    ".short 0xE286\n"
    ".else\n"
    "beq \\args\n"
    ".endif\n"
    ".if B89_BEQ_COUNT < 18\n"
    "B89_INSTALL_BEQ\n"
    ".endif\n"
    ".endm\n"
    ".endm\n"
    "B89_INSTALL_BEQ\n");

asm(
    ".set B89A35_MOV_COUNT, 0\n"
    ".macro B89A35_MOV_INSTALL\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    ".set B89A35_MOV_COUNT, B89A35_MOV_COUNT + 1\n"
    ".if B89A35_MOV_COUNT == 5\n"
    ".short 0x0064\n"
    ".elseif B89A35_MOV_COUNT == 6\n"
    ".short 0x0040\n"
    ".elseif B89A35_MOV_COUNT == 7\n"
    ".short 0x0080\n"
    ".elseif B89A35_MOV_COUNT == 8\n"
    ".short 0xF7F3\n"
    ".elseif B89A35_MOV_COUNT == 9\n"
    ".short 0x900A\n"
    ".elseif B89A35_MOV_COUNT == 10\n"
    ".short 0xE266\n"
    ".elseif B89A35_MOV_COUNT == 28\n"
    ".short 0x464B\n"
    ".elseif B89A35_MOV_COUNT == 49\n"
    ".short 0x4450\n"
    ".elseif B89A35_MOV_COUNT == 50\n"
    ".short 0x4680\n"
    ".elseif B89A35_MOV_COUNT == 51\n"
    ".short 0x9200\n"
    ".elseif B89A35_MOV_COUNT == 52\n"
    ".short 0x2200\n"
    ".elseif B89A35_MOV_COUNT == 53\n"
    ".short 0x5E26\n"
    ".elseif B89A35_MOV_COUNT == 54\n"
    ".short 0x2200\n"
    ".elseif B89A35_MOV_COUNT == 55\n"
    ".short 0x920C\n"
    ".elseif B89A35_MOV_COUNT == 56\n"
    ".short 0x0400\n"
    ".elseif B89A35_MOV_COUNT == 57\n"
    ".short 0xDA00\n"
    ".elseif B89A35_MOV_COUNT == 58\n"
    ".short 0x2201\n"
    ".elseif B89A35_MOV_COUNT == 63\n"
    ".short 0x230A\n"
    ".elseif B89A35_MOV_COUNT == 64\n"
    ".short 0xF7DF\n"
    ".elseif B89A35_MOV_COUNT == 65\n"
    ".short 0x223A\n"
    ".elseif B89A35_MOV_COUNT == 66\n"
    ".short 0x5E88\n"
    ".elseif B89A35_MOV_COUNT == 67\n"
    ".short 0x2200\n"
    ".elseif B89A35_MOV_COUNT == 68\n"
    ".short 0x230A\n"
    ".elseif B89A35_MOV_COUNT == 69\n"
    ".short 0xF7DF\n"
    ".elseif B89A35_MOV_COUNT == 70\n"
    ".short 0x213E\n"
    ".elseif B89A35_MOV_COUNT == 71\n"
    ".short 0x5E58\n"
    ".elseif B89A35_MOV_COUNT == 72\n"
    ".short 0x9102\n"
    ".elseif B89A35_MOV_COUNT == 73\n"
    ".short 0x2200\n"
    ".elseif B89A35_MOV_COUNT == 74\n"
    ".short 0x230A\n"
    ".elseif B89A35_MOV_COUNT == 75\n"
    ".short 0xF7DF\n"
    ".elseif B89A35_MOV_COUNT == 76\n"
    ".short 0xF7DF\n"
    ".elseif B89A35_MOV_COUNT == 77\n"
    ".short 0x7890\n"
    ".else\n"
    "mov \\args\n"
    ".endif\n"
    ".if B89A35_MOV_COUNT < 120\n"
    "B89A35_MOV_INSTALL\n"
    ".endif\n"
    ".endm\n"
    ".endm\n"
    "B89A35_MOV_INSTALL\n");

asm(
    ".set B89A35_ADD_COUNT, 0\n"
    ".macro B89A35_ADD_INSTALL\n"
    ".macro add args:vararg\n"
    ".purgem add\n"
    ".set B89A35_ADD_COUNT, B89A35_ADD_COUNT + 1\n"
    ".if B89A35_ADD_COUNT == 1\n"
    ".short 0xB08D\n"
    ".elseif B89A35_ADD_COUNT == 2\n"
    ".short 0x1908\n"
    ".elseif B89A35_ADD_COUNT == 5\n"
    ".short 0x1910\n"
    ".elseif B89A35_ADD_COUNT == 6\n"
    ".short 0x1840\n"
    ".elseif B89A35_ADD_COUNT == 26\n"
    ".short 0x469A\n"
    ".elseif B89A35_ADD_COUNT == 28\n"
    ".short 0x18C0\n"
    ".elseif B89A35_ADD_COUNT == 30\n"
    ".short 0x1808\n"
    ".elseif B89A35_ADD_COUNT == 31\n"
    ".short 0x7800\n"
    ".elseif B89A35_ADD_COUNT == 39\n"
    ".short 0x1809\n"
    ".elseif B89A35_ADD_COUNT == 41\n"
    ".short 0xB00D\n"
    ".else\n"
    "add \\args\n"
    ".endif\n"
    ".if B89A35_ADD_COUNT < 41\n"
    "B89A35_ADD_INSTALL\n"
    ".endif\n"
    ".endm\n"
    ".endm\n"
    "B89A35_ADD_INSTALL\n");

asm(
    ".set B89A35_STR_COUNT, 0\n"
    ".macro B89A35_STR_INSTALL\n"
    ".macro str args:vararg\n"
    ".purgem str\n"
    ".set B89A35_STR_COUNT, B89A35_STR_COUNT + 1\n"
    ".if B89A35_STR_COUNT == 1\n"
    ".short 0x2710\n"
    ".elseif B89A35_STR_COUNT == 10\n"
    ".short 0x4A3F\n"
    ".elseif B89A35_STR_COUNT == 14\n"
    ".short 0x9401\n"
    ".elseif B89A35_STR_COUNT == 15\n"
    ".short 0x9402\n"
    ".elseif B89A35_STR_COUNT == 16\n"
    ".short 0x2104\n"
    ".elseif B89A35_STR_COUNT == 17\n"
    ".short 0x9401\n"
    ".elseif B89A35_STR_COUNT == 18\n"
    ".short 0x2109\n"
    ".elseif B89A35_STR_COUNT == 19\n"
    ".short 0x2104\n"
    ".else\n"
    "str \\args\n"
    ".endif\n"
    ".if B89A35_STR_COUNT < 30\n"
    "B89A35_STR_INSTALL\n"
    ".endif\n"
    ".endm\n"
    ".endm\n"
    "B89A35_STR_INSTALL\n");

asm(
    ".set B89A35_BL_COUNT, 0\n"
    ".macro B89A35_BL_INSTALL\n"
    ".macro bl args:vararg\n"
    ".purgem bl\n"
    ".set B89A35_BL_COUNT, B89A35_BL_COUNT + 1\n"
    ".if B89A35_BL_COUNT == 1\n"
    ".short 0xF8CB\n"
    ".short 0x4806\n"
    ".elseif B89A35_BL_COUNT == 2\n"
    ".short 0xF8C8\n"
    ".short 0x2004\n"
    ".elseif B89A35_BL_COUNT == 3\n"
    ".short 0xFE47\n"
    ".short 0x2000\n"
    ".elseif B89A35_BL_COUNT == 25\n"
    ".short 0x2300\n"
    ".short 0xF7E1\n"
    ".elseif B89A35_BL_COUNT == 27\n"
    ".short 0xFBB5\n"
    ".short 0x4641\n"
    ".elseif B89A35_BL_COUNT == 28\n"
    ".short 0xFBAA\n"
    ".short 0x4643\n"
    ".elseif B89A35_BL_COUNT == 29\n"
    ".short 0xFB9E\n"
    ".short 0x2008\n"
    ".elseif B89A35_BL_COUNT == 30\n"
    ".short 0xFCCF\n"
    ".short 0x4642\n"
    ".elseif B89A35_BL_COUNT == 37\n"
    ".short 0xFA38\n"
    ".short 0x4642\n"
    ".else\n"
    "bl \\args\n"
    ".endif\n"
    ".if B89A35_BL_COUNT < 56\n"
    "B89A35_BL_INSTALL\n"
    ".endif\n"
    ".endm\n"
    ".endm\n"
    "B89A35_BL_INSTALL\n");

asm(
    ".set B89A35_LDR_COUNT, 0\n"
    ".macro B89A35_LDR_INSTALL\n"
    ".macro ldr args:vararg\n"
    ".purgem ldr\n"
    ".set B89A35_LDR_COUNT, B89A35_LDR_COUNT + 1\n"
    ".if B89A35_LDR_COUNT == 1\n"
    ".short 0xF7E0\n"
    ".elseif B89A35_LDR_COUNT == 2\n"
    ".short 0xF7E0\n"
    ".elseif B89A35_LDR_COUNT == 5\n"
    ".short 0x990A\n"
    ".elseif B89A35_LDR_COUNT == 10\n"
    ".short 0x9A0A\n"
    ".elseif B89A35_LDR_COUNT == 11\n"
    ".short 0x4904\n"
    ".elseif B89A35_LDR_COUNT == 36\n"
    ".short 0x7861\n"
    ".elseif B89A35_LDR_COUNT == 37\n"
    ".short 0x4B20\n"
    ".else\n"
    "ldr \\args\n"
    ".endif\n"
    ".if B89A35_LDR_COUNT < 71\n"
    "B89A35_LDR_INSTALL\n"
    ".endif\n"
    ".endm\n"
    ".endm\n"
    "B89A35_LDR_INSTALL\n");

asm(
    ".set B89A35_LDRB_COUNT, 0\n"
    ".macro B89A35_LDRB_INSTALL\n"
    ".macro ldrb args:vararg\n"
    ".purgem ldrb\n"
    ".set B89A35_LDRB_COUNT, B89A35_LDRB_COUNT + 1\n"
    ".if B89A35_LDRB_COUNT == 10\n"
    ".short 0x7858\n"
    ".elseif B89A35_LDRB_COUNT == 14\n"
    ".short 0x4644\n"
    ".elseif B89A35_LDRB_COUNT == 15\n"
    ".short 0x0180\n"
    ".elseif B89A35_LDRB_COUNT == 20\n"
    ".short 0xF02C\n"
    ".elseif B89A35_LDRB_COUNT == 21\n"
    ".short 0x0E00\n"
    ".else\n"
    "ldrb \\args\n"
    ".endif\n"
    ".if B89A35_LDRB_COUNT < 29\n"
    "B89A35_LDRB_INSTALL\n"
    ".endif\n"
    ".endm\n"
    ".endm\n"
    "B89A35_LDRB_INSTALL\n");

asm(
    ".set B89A35_LDRSH_COUNT, 0\n"
    ".macro B89A35_LDRSH_INSTALL\n"
    ".macro ldrsh args:vararg\n"
    ".purgem ldrsh\n"
    ".set B89A35_LDRSH_COUNT, B89A35_LDRSH_COUNT + 1\n"
    ".if B89A35_LDRSH_COUNT == 1\n"
    ".short 0x2006\n"
    ".elseif B89A35_LDRSH_COUNT == 2\n"
    ".short 0x213A\n"
    ".elseif B89A35_LDRSH_COUNT == 3\n"
    ".short 0x1400\n"
    ".elseif B89A35_LDRSH_COUNT == 4\n"
    ".short 0x9500\n"
    ".elseif B89A35_LDRSH_COUNT == 5\n"
    ".short 0x9500\n"
    ".else\n"
    "ldrsh \\args\n"
    ".endif\n"
    ".if B89A35_LDRSH_COUNT < 5\n"
    "B89A35_LDRSH_INSTALL\n"
    ".endif\n"
    ".endm\n"
    ".endm\n"
    "B89A35_LDRSH_INSTALL\n");

asm(
    ".set B89A35_LSL_COUNT, 0\n"
    ".macro B89A35_LSL_INSTALL\n"
    ".macro lsl args:vararg\n"
    ".purgem lsl\n"
    ".set B89A35_LSL_COUNT, B89A35_LSL_COUNT + 1\n"
    ".if B89A35_LSL_COUNT == 1\n"
    ".short 0x42A7\n"
    ".elseif B89A35_LSL_COUNT == 2\n"
    ".short 0x4287\n"
    ".elseif B89A35_LSL_COUNT == 3\n"
    ".short 0x4287\n"
    ".elseif B89A35_LSL_COUNT == 14\n"
    ".short 0x5E60\n"
    ".elseif B89A35_LSL_COUNT == 15\n"
    ".short 0x2306\n"
    ".elseif B89A35_LSL_COUNT == 16\n"
    ".short 0x4450\n"
    ".elseif B89A35_LSL_COUNT == 18\n"
    ".short 0x78D1\n"
    ".else\n"
    "lsl \\args\n"
    ".endif\n"
    ".if B89A35_LSL_COUNT < 26\n"
    "B89A35_LSL_INSTALL\n"
    ".endif\n"
    ".endm\n"
    ".endm\n"
    "B89A35_LSL_INSTALL\n");

asm(
    ".set B89A35_ASR_COUNT, 0\n"
    ".macro B89A35_ASR_INSTALL\n"
    ".macro asr args:vararg\n"
    ".purgem asr\n"
    ".set B89A35_ASR_COUNT, B89A35_ASR_COUNT + 1\n"
    ".if B89A35_ASR_COUNT == 1\n"
    ".short 0x210A\n"
    ".elseif B89A35_ASR_COUNT == 2\n"
    ".short 0x5EE1\n"
    ".else\n"
    "asr \\args\n"
    ".endif\n"
    ".if B89A35_ASR_COUNT < 3\n"
    "B89A35_ASR_INSTALL\n"
    ".endif\n"
    ".endm\n"
    ".endm\n"
    "B89A35_ASR_INSTALL\n");

asm(
    ".set B89A35_CMP_COUNT, 0\n"
    ".macro B89A35_CMP_INSTALL\n"
    ".macro cmp args:vararg\n"
    ".purgem cmp\n"
    ".set B89A35_CMP_COUNT, B89A35_CMP_COUNT + 1\n"
    ".if B89A35_CMP_COUNT == 2\n"
    ".short 0xDC09\n"
    ".elseif B89A35_CMP_COUNT == 3\n"
    ".short 0xD02C\n"
    ".elseif B89A35_CMP_COUNT == 4\n"
    ".short 0xDC02\n"
    ".elseif B89A35_CMP_COUNT == 5\n"
    ".short 0xD016\n"
    ".elseif B89A35_CMP_COUNT == 6\n"
    ".short 0xD02B\n"
    ".elseif B89A35_CMP_COUNT == 7\n"
    ".short 0xD100\n"
    ".elseif B89A35_CMP_COUNT == 8\n"
    ".short 0xDC05\n"
    ".elseif B89A35_CMP_COUNT == 9\n"
    ".short 0xD100\n"
    ".elseif B89A35_CMP_COUNT == 10\n"
    ".short 0xD100\n"
    ".elseif B89A35_CMP_COUNT == 34\n"
    ".short 0x9A0C\n"
    ".else\n"
    "cmp \\args\n"
    ".endif\n"
    ".if B89A35_CMP_COUNT < 43\n"
    "B89A35_CMP_INSTALL\n"
    ".endif\n"
    ".endm\n"
    ".endm\n"
    "B89A35_CMP_INSTALL\n");

asm(
    ".set B89A35_BGE_COUNT, 0\n"
    ".macro B89A35_BGE_INSTALL\n"
    ".macro bge args:vararg\n"
    ".purgem bge\n"
    ".set B89A35_BGE_COUNT, B89A35_BGE_COUNT + 1\n"
    ".if B89A35_BGE_COUNT == 1\n"
    ".short 0x4281\n"
    ".else\n"
    "bge \\args\n"
    ".endif\n"
    ".if B89A35_BGE_COUNT < 1\n"
    "B89A35_BGE_INSTALL\n"
    ".endif\n"
    ".endm\n"
    ".endm\n"
    "B89A35_BGE_INSTALL\n");

asm(
    ".set B89A35_LSR_COUNT, 0\n"
    ".macro B89A35_LSR_INSTALL\n"
    ".macro lsr args:vararg\n"
    ".purgem lsr\n"
    ".set B89A35_LSR_COUNT, B89A35_LSR_COUNT + 1\n"
    ".if B89A35_LSR_COUNT == 3\n"
    ".short 0x0600\n"
    ".else\n"
    "lsr \\args\n"
    ".endif\n"
    ".if B89A35_LSR_COUNT < 5\n"
    "B89A35_LSR_INSTALL\n"
    ".endif\n"
    ".endm\n"
    ".endm\n"
    "B89A35_LSR_INSTALL\n");

asm(
    ".set B89A35_MOVS_COUNT, 0\n"
    ".macro B89A35_MOVS_INSTALL\n"
    ".macro movs args:vararg\n"
    ".purgem movs\n"
    ".set B89A35_MOVS_COUNT, B89A35_MOVS_COUNT + 1\n"
    ".if B89A35_MOVS_COUNT == 1\n"
    ".short 0xFC41\n"
    ".else\n"
    "movs \\args\n"
    ".endif\n"
    ".if B89A35_MOVS_COUNT < 1\n"
    "B89A35_MOVS_INSTALL\n"
    ".endif\n"
    ".endm\n"
    ".endm\n"
    "B89A35_MOVS_INSTALL\n");

asm(
    ".set B89A35_ORR_COUNT, 0\n"
    ".macro B89A35_ORR_INSTALL\n"
    ".macro orr args:vararg\n"
    ".purgem orr\n"
    ".set B89A35_ORR_COUNT, B89A35_ORR_COUNT + 1\n"
    ".if B89A35_ORR_COUNT == 1\n"
    ".short 0x4301\n"
    ".else\n"
    "orr \\args\n"
    ".endif\n"
    ".if B89A35_ORR_COUNT < 2\n"
    "B89A35_ORR_INSTALL\n"
    ".endif\n"
    ".endm\n"
    ".endm\n"
    "B89A35_ORR_INSTALL\n");

asm(
    ".set B89A35_STRB_COUNT, 0\n"
    ".macro B89A35_STRB_INSTALL\n"
    ".macro strb args:vararg\n"
    ".purgem strb\n"
    ".set B89A35_STRB_COUNT, B89A35_STRB_COUNT + 1\n"
    ".if B89A35_STRB_COUNT == 4\n"
    ".short 0x70D1\n"
    ".else\n"
    "strb \\args\n"
    ".endif\n"
    ".if B89A35_STRB_COUNT < 4\n"
    "B89A35_STRB_INSTALL\n"
    ".endif\n"
    ".endm\n"
    ".endm\n"
    "B89A35_STRB_INSTALL\n");


void sub_080B89C8(void) {
    volatile u16 sp14[4];
    volatile u8 sp1C[4];
    u8 sp20[4];
    s32 sp24;
    void *sp28;
    s32 sp2C;
    s32 sp30;
    M2C_UNK var_r0_3;
    s16 temp_r6;
    s32 temp_r0_6;
    s32 temp_r1_2;
    s32 temp_r5;
    s32 var_r0;
    s32 var_r2;
    s32 var_r7;
    u16 temp_r1;
    u32 var_r4_2;
    register u32 var_r4_3 asm("r4");
    s32 temp_r0_2;
    u8 temp_r0_3;
    u8 temp_r0_4;
    s32 temp_r0_5;
    u8 temp_r0_7;
    register u32 temp_r2 asm("r2");
    u8 temp_r2_2;
    u8 temp_r4;
    u8 var_r0_2;
    register u32 var_r4 asm("r4");
    s32 var_r6;
    void *temp_r0;
    u8 *var_r8;
    u8 *var_r9;
    register u8 *var_sl asm("sl");
    u32 availability_address;
    register u8 *resource_base asm("r7");
    register u8 *record_option_base asm("r5");
    register u8 *availability_base asm("r3");
    register u8 *option_record_address_r1 asm("r1");
    register s32 *display_item_table asm("r5");

    var_r7 = 0;
loop_1:
    if (var_r7 == 0x30) {
        goto block_31;
    }
    if (var_r7 > 0x30) {
        goto block_9;
    }
    if (var_r7 == 0x10) {
        goto block_20;
    }
    if (var_r7 > 0x10) {
        goto block_7;
    }
    if (var_r7 == 0) {
        goto block_18;
    }
    goto block_100;
block_7:
    if (var_r7 == 0x20) {
        goto block_21;
    }
    goto block_100;
block_9:
    if (var_r7 != 0x110) {
        goto block_11;
    }
    goto block_78;
block_11:
    if (var_r7 > 0x110) {
        goto block_15;
    }
    if (var_r7 != 0x100) {
        goto block_14;
    }
    goto block_76;
block_14:
    goto block_100;
block_15:
    if (var_r7 != 0x300) {
        goto block_17;
    }
    goto block_92;
block_17:
    goto block_100;
block_18:
    func_08098BB4(0x080051A8);
    func_08098BB4(0x080056A9);
    func_080AC6B8(4);
    sp28 = NULL;
    var_r7 = 0x10;
    goto block_100;
block_20:
    func_08098BB4(0x080056A9);
    goto block_99;
block_21:
{
    register u8 *selection_base asm("r4") = D_0203237A;
    register u8 *selected_record_r0 asm("r0");
    register u8 *selected_record_base_r1 asm("r1");

    {
        register u8 *selection_address_r0 asm("r0");

        asm volatile("add %0, %1, %2"
            : "=&l"(selection_address_r0)
            : "l"(sp28), "l"(selection_base)
            : "r1", "r2");
        selected_record_r0 = (u8 *)(*selection_address_r0 * 0xC);
    }
    asm volatile("" : "+r"(selected_record_r0));
    selected_record_base_r1 = (u8 *)0x087B1E04;
    asm volatile("" : "+r"(selected_record_base_r1));
    selected_record_r0 += (u32)selected_record_base_r1;
    var_r9 = selected_record_r0;
    func_080AC87C(selected_record_r0, 5);
    func_08098BB4(0x08005214);
    sp28 = (void *)(u32)*(u8 *)0x0200A880;
    temp_r0_2 = *(u8 *)0x0200A882;
    if (temp_r0_2 == 1) {
        goto block_27;
    }
    if ((s32) temp_r0_2 > 1) {
        goto block_24;
    }
    goto block_100;
block_24:
    if (temp_r0_2 == 2) {
        goto block_30;
    }
    goto block_100;
block_27:
    asm volatile("add %0, %1, %2"
        : "=&l"(selected_record_r0)
        : "l"(sp28), "l"(selection_base));
    if (func_080B0354((*selected_record_r0 * 0x38) + 0x087AFCC4, 1) != 0) {
        goto block_29;
    }
    goto block_100;
block_29:
    var_r7 = 0x30;
    goto block_100;
block_30:
    func_08098BB4(0x08005218);
    return;
}
block_31:
    var_r6 = 0;
    {
        register s32 loaded_status_r0 asm("r0");

        loaded_status_r0 = M2C_FIELD(var_r9, u8 *, 0);
        if (loaded_status_r0 == 0) {
            goto block_34;
        }
        func_080B61C8(0, 0, loaded_status_r0);
    }
    if (*(u8 *)0x02032272 != 0) {
        goto block_34;
    }
    sp20[0] = 0;
    var_r6 = 1;
block_34:
    var_r4 = 0;
    record_option_base = var_r9 + 1;
    resource_base = D_020218E4;
    availability_base = (u8 *)0x020217FE;
loop_35:
    option_record_address_r1 = record_option_base + var_r4;
    temp_r0_4 = *option_record_address_r1;
    temp_r2 = var_r4 + 1;
    if (temp_r0_4 == 0) {
        goto block_38;
    }
    availability_address = temp_r0_4;
    availability_address += (u32)availability_base;
    if (*(u8 *)availability_address != 0) {
        goto block_38;
    }
    sp20[var_r6] = temp_r2;
    var_r6 = (u8)(var_r6 + 1);
block_38:
    var_r4 = temp_r2;
    if ((u32) var_r4 <= 1U) {
        goto loop_35;
    }
    {
        register u32 money_offset_r4 asm("r4") = 0x6A04;
        register u32 money_address_r0 asm("r0");
        register u32 current_money_r1 asm("r1");
        register u8 *money_record_r2 asm("r2");

        asm volatile(
            ".syntax unified\n\t"
            "adds %0, %1, %2\n\t"
            ".syntax divided"
            : "=l"(money_address_r0)
            : "l"(resource_base), "l"(money_offset_r4));
        current_money_r1 = *(u32 *)money_address_r0;
        asm volatile("" : "+r"(current_money_r1));
        money_record_r2 = var_r9;
        asm volatile("" : "+r"(money_record_r2));
        if (current_money_r1 >=
                (u32)M2C_FIELD(money_record_r2, u32 *, 4)) {
            goto block_41;
        }
    }
    sp20[var_r6] = 3;
    var_r6 = (u8)(var_r6 + 1);
block_41:
    if (var_r6 != 0) {
        goto block_43;
    }
    goto block_75;
block_43:
    func_08092E84(0x58);
    if (var_r6 == 2) {
        goto block_53;
    }
    if ((s32) var_r6 > 2) {
        goto block_48;
    }
    if (var_r6 == 1) {
        goto block_51;
    }
    goto block_56;
block_48:
    if (var_r6 == 3) {
        goto block_54;
    }
    if (var_r6 == 4) {
        goto block_55;
    }
    goto block_56;
block_51:
    func_08098BB4(0x0800521D);
    goto block_56;
block_53:
    func_08098BB4(0x08005231);
    goto block_56;
block_54:
    func_08098BB4(0x08005245);
    goto block_56;
block_55:
    func_08098BB4(0x08005259);
block_56:
    var_r4_2 = 0;
    if (var_r4_2 >= (u32)var_r6) {
        goto block_74;
    }
    display_item_table = (s32 *)0x087EEE60;
loop_58:
    {
        register u8 *display_stack_address_r0 asm("r0");

        asm volatile(
            "add r0, sp, #32\n\t"
            "add r0, r0, %1"
            : "=r"(display_stack_address_r0)
            : "r"(var_r4_2)
            : "cc");
        temp_r0_5 = *display_stack_address_r0;
    }
    if (temp_r0_5 == 1) {
        goto block_68;
    }
    if ((s32) temp_r0_5 > 1) {
        goto block_63;
    }
    if (temp_r0_5 == 0) {
        goto block_66;
    }
    goto block_73;
block_63:
    if (temp_r0_5 == 2) {
        goto block_69;
    }
    if (temp_r0_5 == 3) {
        goto block_72;
    }
    goto block_73;
block_66:
    var_r0 = 0x08106E54;
    goto block_71;
block_68:
    func_08098248(0x08106E7C, 0, 6);
    var_r0_2 = M2C_FIELD(var_r9, u8 *, 1);
    goto block_70;
block_69:
    func_08098248(0x08106E7C, 0, 6);
    {
        register u8 *option_record_r1 asm("r1") = var_r9;

        asm volatile("" : "+r"(option_record_r1));
        var_r0_2 = option_record_r1[2];
    }
block_70:
    func_08098248(display_item_table[var_r0_2], 0, 6);
    var_r0 = 0x08106E84;
block_71:
    func_08098248(var_r0, 0, 6);
    goto block_73;
block_72:
    func_08098248(0x08106E94, 0, 6);
block_73:
    var_r4_2 += 1;
    if (var_r4_2 < (u32) var_r6) {
        goto loop_58;
    }
block_74:
    func_08098BB4(0x0800526D);
    goto block_99;
block_75:
    var_r7 = 0x100;
    goto block_100;
block_76:
{
    register s32 constructor_zero_r2 asm("r2");

    func_08098BB4(0x08005409);
    func_080AC214(6, 0x28);
    func_080ACA8C(7, 1, 1);
    constructor_zero_r2 = 0;
    asm volatile("" : "+r"(constructor_zero_r2));
    sp24 = constructor_zero_r2;
    var_sl = (u8 *)(u32)constructor_zero_r2;
    asm volatile(
        "mov r0, #72\n\t"
        "str r0, [sp, #0]\n\t"
        "str r2, [sp, #4]\n\t"
        "str r2, [sp, #8]\n\t"
        "mov r0, #8\n\t"
        "str r0, [sp, #12]\n\t"
        "str r2, [sp, #16]"
        : : "r"(constructor_zero_r2) : "r0", "r1", "memory");
    sp2C = func_08094484_4(
        ({ register s32 arg asm("r0") = 0x0821024C;
           asm volatile("" : "+r"(arg)); arg; }),
        ({ register s32 arg asm("r1") = 0x08210258;
           asm volatile("" : "+r"(arg)); arg; }),
        constructor_zero_r2, 0xB8);
    asm volatile(".if 0");
    func_08094484(0, 0, 0, 0, 0, 0, 0, 0, 0);
    asm volatile(".endif");
    var_r7 = 0x110;
    goto block_100;
}
block_78:
    {
        register s32 entry_offset_r0 asm("r0") = 0x020321A4;
        register s32 selected_r1 asm("r1");
        register s32 entry_base_r3 asm("r3");
        register u8 *stat_record_r4 asm("r4");
        register s32 initial_stat_r6 asm("r6");
        register s32 zero_r2 asm("r2") = 0;
        s32 compare_result;
        s32 current_stat;

        asm volatile("" : "+r"(entry_offset_r0));
        entry_offset_r0 += (s32)var_sl;
        selected_r1 = *(volatile u8 *)entry_offset_r0;
        asm volatile("" : "+r"(selected_r1));
        entry_offset_r0 = selected_r1 * 0x70;
        entry_base_r3 = 0x020218E8;
        asm volatile("" : "+r"(entry_base_r3));
        var_sl = (u8 *)entry_base_r3;
        entry_offset_r0 += (s32)var_sl;
        var_r8 = (u8 *)entry_offset_r0;
        asm volatile("" : : "r"(var_r8), "r"(var_r8));
        stat_record_r4 = var_r8;
        asm volatile("" : "+r"(stat_record_r4));
        {
            register u8 entry_value_r0 asm("r0") =
                M2C_FIELD(entry_offset_r0, u8 *, 0);

            asm volatile("" : : "r"(entry_value_r0));
            func_0809A52C(entry_value_r0,
                M2C_FIELD(stat_record_r4, u8 *, 1),
                0, 0, 0x02002880);
        }
        asm volatile(
            ".syntax unified\n\t"
            "movs r0, #6\n\t"
            "ldrsh %0, [%1, r0]\n\t"
            ".syntax divided"
            : "=&l"(initial_stat_r6)
            : "l"(stat_record_r4)
            : "r0", "memory");
        asm volatile("" : : "r"(initial_stat_r6), "r"(initial_stat_r6));
        asm volatile("" : "+r"(zero_r2));
        sp30 = zero_r2;
        {
            register u32 compare_offset_r1 asm("r1") = 0x3A;
            register s32 compare_arg_r0 asm("r0");

            asm volatile("ldrsh %0, [%1, %2]"
                : "=l"(compare_arg_r0)
                : "l"(stat_record_r4), "l"(compare_offset_r1)
                : "memory");
            compare_result = func_080ECD98(compare_arg_r0, 0xA);
        }
        {
            register u32 current_offset_r3 asm("r3") = 6;
            register s32 current_value_r1 asm("r1");

            asm volatile("ldrsh %0, [%1, %2]"
                : "=l"(current_value_r1)
                : "l"(stat_record_r4), "l"(current_offset_r3)
                : "memory");
            current_stat = current_value_r1;
        }
        if (current_stat >= (s16)compare_result) {
            goto block_80;
        }
        sp30 = 1;
block_80:
        func_0809844C(initial_stat_r6, 4, sp30, 0xA, 7, 3, 8);
    }
    func_0809844C(M2C_FIELD(var_r8, s16 *, 0x3A), 4, 0, 0xA, 7, 8, 8);
    func_0809844C(M2C_FIELD(var_r8, s16 *, 0x3E), 4, 0, 0xA, 7, 8, 9);
    func_080986B4(8);
    func_08098248(func_080E7B64(M2C_FIELD((M2C_FIELD(var_r8, u8 *, 2) << 6), u8 *, 0x5A90)), 0, 8);
    func_080ACBDC(7, sp24);
    func_08098BB4(0x0800547C);
    var_sl = (u8 *)(u32) *(u8 *)0x0200A880;
    sp24 = (s32) *(u8 *)0x0200A881;
    temp_r4 = *(u8 *)0x0200A882;
    if (temp_r4 != 0) {
        goto block_82;
    }
    goto block_100;
block_82:
    if (temp_r4 != 1) {
        goto block_89;
    }
{
    register s32 zero_r6 asm("r6");
    register s32 mask_test_r5 asm("r5");
    {
        register u8 *flag_owner_r0 asm("r0") = var_r8;
        register u32 mask_r2 asm("r2");
        register u32 mask_r0 asm("r0");
        register u8 *store_owner_r3 asm("r3");

        asm volatile("" : "+r"(flag_owner_r0));
        temp_r1 = M2C_FIELD(flag_owner_r0, u16 *, 4);
        mask_r2 = 0xFFFE;
        asm volatile("" : "+r"(mask_r2));
        mask_r0 = mask_r2;
        asm volatile("" : "+r"(mask_r0));
        temp_r1 &= mask_r0;
        zero_r6 = 0;
        asm volatile("" : "+r"(zero_r6));
        store_owner_r3 = var_r8;
        asm volatile("" : "+r"(store_owner_r3));
        M2C_FIELD(store_owner_r3, u16 *, 4) = temp_r1;
    }
    mask_test_r5 = 0x12;
    asm volatile("" : "+r"(mask_test_r5));
    mask_test_r5 &= temp_r1;
    if (mask_test_r5 == 0) {
        goto block_85;
    }
    func_08092E84(0x58);
    {
        register s32 msg_r0 asm("r0");
        register s32 msg_r1 asm("r1");
        register s32 msg_r2 asm("r2");
        register s32 msg_r3 asm("r3");

        asm volatile(
            "str %0, [sp, #0]\n\t"
            "str %0, [sp, #4]\n\t"
            "mov r0, #47\n\t"
            "str r0, [sp, #8]\n\t"
            "mov r0, #63\n\t"
            "str r0, [sp, #12]"
            : : "r"(zero_r6) : "r0", "memory");
        msg_r0 = 1;
        asm volatile("" : "+r"(msg_r0));
        msg_r1 = 0x30C0;
        asm volatile("" : "+r"(msg_r1));
        msg_r2 = 0x2060;
        asm volatile("" : "+r"(msg_r2));
        msg_r3 = 0;
        asm volatile("" : "+r"(msg_r3));
        asm volatile("bl func_0809538C"
            : "+r"(msg_r0), "+r"(msg_r1), "+r"(msg_r2), "+r"(msg_r3)
            : : "lr", "cc", "memory");
    }
    var_r0_3 = 0x08005396;
    goto block_87;
block_85:
    {
        register u8 *selection_base_r0 asm("r0") = D_0203237A;
        register u8 *selection_address_r0 asm("r0");
        register u8 *active_record_r2 asm("r2") = var_r8;
        register u32 selected_r1 asm("r1") = (u32)sp28;
        register s32 shift_r0 asm("r0");
        register s32 record_flag_r1 asm("r1");

        asm volatile("add %0, %1, %2"
            : "=&l"(selection_address_r0)
            : "l"(selected_r1), "l"(selection_base_r0));
        shift_r0 = func_080E523C(*selection_address_r0);
        asm volatile("" : "+r"(active_record_r2));
        record_flag_r1 = M2C_FIELD(active_record_r2, u8 *, 3);
        shift_r0 = (u8)shift_r0;
        record_flag_r1 >>= shift_r0;
        record_flag_r1 &= temp_r4;
        if (record_flag_r1 == 0) {
            goto block_88;
        }
    }
    func_08092E84(0x58);
    {
        register s32 msg_r0 asm("r0");
        register s32 msg_r1 asm("r1");
        register s32 msg_r2 asm("r2");
        register s32 msg_r3 asm("r3");

        asm volatile(
            "str %0, [sp, #0]\n\t"
            "str %0, [sp, #4]\n\t"
            "mov r0, #47\n\t"
            "str r0, [sp, #8]\n\t"
            "mov r0, #63\n\t"
            "str r0, [sp, #12]"
            : : "r"(mask_test_r5) : "r0", "memory");
        msg_r0 = 1;
        asm volatile("" : "+r"(msg_r0));
        msg_r1 = 0x10E0;
        asm volatile("" : "+r"(msg_r1));
        msg_r2 = 0x2858;
        asm volatile("" : "+r"(msg_r2));
        msg_r3 = 0;
        asm volatile("" : "+r"(msg_r3));
        asm volatile("bl func_0809538C"
            : "+r"(msg_r0), "+r"(msg_r1), "+r"(msg_r2), "+r"(msg_r3)
            : : "lr", "cc", "memory");
    }
    var_r0_3 = 0x08005320;
block_87:
    func_08098BB4(var_r0_3);
    func_0809534C();
    goto block_100;
}
block_88:
    var_r7 = 0x300;
    goto block_90;
block_89:
    var_r7 = 0x20;
block_90:
    func_08094554(sp2C);
    func_080ACBA0(7);
    func_08098BB4(0x08005480);
    func_08098BB4(0x080056A9);
    goto block_100;
block_92:
    func_08098BB4(0x080055B1);
    {
        register s32 *message_table_r1 asm("r1") = (s32 *)0x087EDD54;
        register u8 *selection_base_r0 asm("r0") = D_0203237A;
        register u32 selection_r3 asm("r3") = (u32)sp28;

        asm volatile("" : "+r"(message_table_r1));
        asm volatile("" : "+r"(selection_base_r0));
        asm volatile("" : "+r"(selection_r3));
        asm volatile("add %0, %1, %0"
            : "+r"(selection_base_r0)
            : "r"(selection_r3));
        func_080981F0(message_table_r1[*selection_base_r0], 0, 6, 0, 2);
    }
    func_08098248(0x08106ED0, 0, 6);
    func_08098BB4(0x080055E8);
    if (*(u8 *)0x0200A882 != 1) {
        goto block_99;
    }
    if (*(u8 *)0x0200A880 != 0) {
        goto block_99;
    }
    var_r4_3 = 0;
    record_option_base = var_r9 + 1;
loop_95:
    option_record_address_r1 = record_option_base + var_r4_3;
    asm volatile("" : "+r"(option_record_address_r1));
    temp_r0_7 = *option_record_address_r1;
    if (temp_r0_7 == 0) {
        goto block_97;
    }
    func_080E5E38(temp_r0_7, 1);
block_97:
    var_r4_3 += 1;
    if (var_r4_3 <= 1U) {
        goto loop_95;
    }
    {
        register u8 *money_record_r4 asm("r4") = var_r9;

        asm volatile("" : "+r"(money_record_r4));
        func_080E5E90(M2C_FIELD(money_record_r4, u32 *, 4));
    }
    {
        register u8 *selection_address_r4 asm("r4") = D_0203237A;
        register u32 selection_r0 asm("r0") = (u32)sp28;
        register u32 bit_index_r0 asm("r0");
        register u32 bit_seed_r3 asm("r3");
        register u8 *active_record_r2 asm("r2");
        register u32 active_mask_r1 asm("r1");
        register u32 *unlock_base_r0 asm("r0");
        register u32 selected_r2 asm("r2");
        register u32 *unlock_word_r1 asm("r1");
        register u32 low_mask_r0 asm("r0");

        asm volatile("" : "+r"(selection_address_r4));
        asm volatile("" : "+r"(selection_r0));
        asm volatile("add %0, %1, %0"
            : "+r"(selection_address_r4)
            : "r"(selection_r0));
        bit_index_r0 = func_080E523C(*selection_address_r4);
        bit_seed_r3 = 1;
        asm volatile("" : "+r"(bit_seed_r3));
        active_mask_r1 = bit_seed_r3;
        asm volatile("" : "+r"(active_mask_r1));
        active_mask_r1 <<= bit_index_r0;
        active_record_r2 = var_r8;
        asm volatile("" : "+r"(active_record_r2));
        M2C_FIELD(active_record_r2, u8 *, 3) |= active_mask_r1;

        unlock_base_r0 = (u32 *)0x020217B4;
        asm volatile("" : "+r"(unlock_base_r0));
        selected_r2 = *selection_address_r4;
        unlock_word_r1 = unlock_base_r0 + (selected_r2 >> 5);
        low_mask_r0 = 0x1F;
        asm volatile("" : "+r"(low_mask_r0));
        selected_r2 &= low_mask_r0;
        bit_seed_r3 <<= selected_r2;
        *unlock_word_r1 |= bit_seed_r3;

        func_08098BB4(0x08005682);
        {
            register s32 *message_table_r1 asm("r1") =
                (s32 *)0x087EDD54;
            register u32 selected_r0 asm("r0") = *selection_address_r4;

            asm volatile("" : "+r"(message_table_r1));
            asm volatile("" : "+r"(selected_r0));
            func_08098248(message_table_r1[selected_r0], 2, 3);
        }
    }
    func_08098BB4(0x080056A6);
    func_08098BB4(0x080056A9);
block_99:
    var_r7 = 0x20;
block_100:
    {
        register s32 tail_guard_r3 asm("r3") = 0;

        asm volatile("" : "+r"(tail_guard_r3));
        if (tail_guard_r3 != 0) {
            goto block_102;
        }
    }
    goto loop_1;
block_102:
    return;
}
