#include "m2c_prelude.h"

asm(
    ".macro AF924_ARM_CALLBACK_COMPARE\n"
    ".macro bl target\n"
    ".purgem bl\n"
    "bl \\target\n"
    "add r1, r5, #0\n"
    ".macro cmp lhs, rhs\n"
    ".purgem cmp\n"
    "cmp r1, \\rhs\n"
    ".set af924_seven_mov_count, 0\n"
    ".macro mov args:vararg\n"
    ".if af924_seven_mov_count == 0\n"
    ".short 0x2701\n"
    ".elseif af924_seven_mov_count == 1\n"
    ".short 0x2307\n"
    ".elseif af924_seven_mov_count == 2\n"
    ".short 0x4698\n"
    ".else\n"
    ".purgem mov\n"
    "AF924_FLAG_MOV_STAGE1\n"
    ".endif\n"
    ".set af924_seven_mov_count, af924_seven_mov_count + 1\n"
    ".endm\n"
    ".endm\n"
    ".endm\n"
    ".endm\n");
asm(
    ".macro AF924_FIRST_VALUE_LOAD\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov r0, #6\n"
    ".macro ldrsh args:vararg\n"
    ".purgem ldrsh\n"
    "ldrsh r5, [r4, r0]\n"
    ".endm\n"
    ".endm\n"
    ".endm\n");
asm(
    ".macro AF924_BOUNDARY_MOV_STAGE2\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    ".short 0x2206\n"
    ".macro ldrsh args:vararg\n"
    ".purgem ldrsh\n"
    ".short 0x5EA1\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    ".short 0x233A\n"
    ".macro ldrsh args:vararg\n"
    ".purgem ldrsh\n"
    ".short 0x5EE0\n"
    "AF924_AFD_MOV_STAGE1\n"
    ".endm\n"
    ".endm\n"
    ".endm\n"
    ".endm\n"
    ".endm\n");
asm(
    ".macro AF924_BOUNDARY_MOV_STAGE1\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_BOUNDARY_MOV_STAGE2\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_FLAG_MOV_STAGE12\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    ".short 0x4651\n"
    ".macro and args:vararg\n"
    ".purgem and\n"
    ".short 0x4008\n"
    "AF924_BOUNDARY_MOV_STAGE1\n"
    ".endm\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_FLAG_MOV_STAGE11\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_FLAG_MOV_STAGE12\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_FLAG_MOV_STAGE10\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_FLAG_MOV_STAGE11\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_FLAG_MOV_STAGE9\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_FLAG_MOV_STAGE10\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_FLAG_MOV_STAGE8\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_FLAG_MOV_STAGE9\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_FLAG_MOV_STAGE7\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_FLAG_MOV_STAGE8\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_FLAG_MOV_STAGE6\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_FLAG_MOV_STAGE7\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_FLAG_MOV_STAGE5\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_FLAG_MOV_STAGE6\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_FLAG_MOV_STAGE4\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_FLAG_MOV_STAGE5\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_FLAG_MOV_STAGE3\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_FLAG_MOV_STAGE4\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_FLAG_MOV_STAGE2\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_FLAG_MOV_STAGE3\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_FLAG_MOV_STAGE1\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_FLAG_MOV_STAGE2\n"
    ".endm\n"
    ".endm\n");
asm(
    ".macro AF924_AFD_FINAL_ARGS\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov r3, r8\n"
    ".macro str args:vararg\n"
    ".purgem str\n"
    "str r3, [sp]\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov r1, sl\n"
    ".macro str args:vararg\n"
    ".purgem str\n"
    "str r1, [sp, #4]\n"
    "AF924_AFE_MOV_STAGE1\n"
    ".endm\n"
    ".endm\n"
    ".endm\n"
    ".endm\n"
    ".endm\n");
asm(
    ".macro AF924_AFD_TAIL_MOV_STAGE3\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov r2, #58\n"
    ".macro ldrsh args:vararg\n"
    ".purgem ldrsh\n"
    "ldrsh r0, [r4, r2]\n"
    "AF924_AFD_FINAL_ARGS\n"
    ".endm\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_AFD_TAIL_MOV_STAGE2\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_AFD_TAIL_MOV_STAGE3\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_AFD_TAIL_MOV_STAGE1\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_AFD_TAIL_MOV_STAGE2\n"
    ".endm\n"
    ".endm\n");
asm(
    ".macro AF924_AFD_STACK_MOV_STAGE2\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov r0, r8\n"
    ".macro str args:vararg\n"
    ".purgem str\n"
    "str r0, [sp]\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov r1, #3\n"
    ".macro str args:vararg\n"
    ".purgem str\n"
    "str r1, [sp, #4]\n"
    "AF924_AFD_TAIL_MOV_STAGE1\n"
    ".endm\n"
    ".endm\n"
    ".endm\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_AFD_STACK_MOV_STAGE1\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_AFD_STACK_MOV_STAGE2\n"
    ".endm\n"
    ".endm\n");
asm(
    ".macro AF924_AFD_THIRD_MOV_STAGE2\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov r3, #6\n"
    ".macro ldrsh args:vararg\n"
    ".purgem ldrsh\n"
    "ldrsh r1, [r4, r3]\n"
    "AF924_AFD_STACK_MOV_STAGE1\n"
    ".endm\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_AFD_THIRD_MOV_STAGE1\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_AFD_THIRD_MOV_STAGE2\n"
    ".endm\n"
    ".endm\n");
asm(
    ".macro AF924_AFD_SECOND_MOV_STAGE2\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov r3, #58\n"
    ".macro ldrsh args:vararg\n"
    ".purgem ldrsh\n"
    "ldrsh r0, [r4, r3]\n"
    "AF924_AFD_THIRD_MOV_STAGE1\n"
    ".endm\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_AFD_SECOND_MOV_STAGE1\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_AFD_SECOND_MOV_STAGE2\n"
    ".endm\n"
    ".endm\n");
asm(
    ".macro AF924_AFD_MOV_STAGE7\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov r2, #6\n"
    ".macro ldrsh args:vararg\n"
    ".purgem ldrsh\n"
    "ldrsh r7, [r4, r2]\n"
    "AF924_AFD_SECOND_MOV_STAGE1\n"
    ".endm\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_AFD_MOV_STAGE6\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_AFD_MOV_STAGE7\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_AFD_MOV_STAGE5\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_AFD_MOV_STAGE6\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_AFD_MOV_STAGE4\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_AFD_MOV_STAGE5\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_AFD_MOV_STAGE3\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_AFD_MOV_STAGE4\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_AFD_MOV_STAGE2\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_AFD_MOV_STAGE3\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_AFD_MOV_STAGE1\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_AFD_MOV_STAGE2\n"
    ".endm\n"
    ".endm\n");
asm(
    ".macro AF924_AFF_CONST_LDR_STAGE2\n"
    ".macro ldr dst, src\n"
    ".purgem ldr\n"
    "ldr r4, \\src\n"
    ".macro add args:vararg\n"
    ".purgem add\n"
    "add r0, r4, #0\n"
    "AF924_GRAPHICS_BASE_LDR_STAGE1\n"
    ".endm\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_AFF_CONST_LDR_STAGE1\n"
    ".macro ldr args:vararg\n"
    ".purgem ldr\n"
    "ldr \\args\n"
    "AF924_AFF_CONST_LDR_STAGE2\n"
    ".endm\n"
    ".endm\n");
asm(
    ".macro AF924_GRAPHICS_BASE_LDR_STAGE3\n"
    ".macro ldr dst, src\n"
    ".purgem ldr\n"
    "ldr r0, \\src\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov r8, r0\n"
    ".macro ldr next_dst, next_src\n"
    ".purgem ldr\n"
    "ldr r1, \\next_src\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov r9, r1\n"
    "AF924_FIRST_POS_LDR_STAGE1\n"
    ".endm\n"
    ".endm\n"
    ".endm\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_GRAPHICS_BASE_LDR_STAGE2\n"
    ".macro ldr args:vararg\n"
    ".purgem ldr\n"
    "ldr \\args\n"
    "AF924_GRAPHICS_BASE_LDR_STAGE3\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_GRAPHICS_BASE_LDR_STAGE1\n"
    ".macro ldr args:vararg\n"
    ".purgem ldr\n"
    "ldr \\args\n"
    "AF924_GRAPHICS_BASE_LDR_STAGE2\n"
    ".endm\n"
    ".endm\n");
asm(
    ".macro AF924_FIRST_POS_LDR_STAGE2\n"
    ".macro ldr args:vararg\n"
    ".purgem ldr\n"
    "ldr r0, [r4, #12]\n"
    ".macro cmp args:vararg\n"
    ".purgem cmp\n"
    "cmp r0, #0\n"
    ".macro ldr mask_dst, mask_src\n"
    ".purgem ldr\n"
    "ldr r2, \\mask_src\n"
    ".macro add args:vararg\n"
    ".purgem add\n"
    "add r0, r0, r2\n"
    ".macro asr args:vararg\n"
    ".purgem asr\n"
    "asr r0, r0, #13\n"
    "AF924_SECOND_POS_LDR_STAGE1\n"
    ".endm\n"
    ".endm\n"
    ".endm\n"
    ".endm\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_FIRST_POS_LDR_STAGE1\n"
    ".macro ldr args:vararg\n"
    ".purgem ldr\n"
    "ldr \\args\n"
    "AF924_FIRST_POS_LDR_STAGE2\n"
    ".endm\n"
    ".endm\n");
asm(
    ".macro AF924_SECOND_POS_LDR_STAGE3\n"
    ".macro ldr args:vararg\n"
    ".purgem ldr\n"
    "ldr r0, [r4, #20]\n"
    ".macro cmp args:vararg\n"
    ".purgem cmp\n"
    "cmp r0, #0\n"
    ".macro ldr next_args:vararg\n"
    ".purgem ldr\n"
    "ldr \\next_args\n"
    ".macro add args:vararg\n"
    ".purgem add\n"
    "add r0, r0, r2\n"
    ".macro asr args:vararg\n"
    ".purgem asr\n"
    "asr r0, r0, #13\n"
    "AF924_FINAL_MASK_LDR_STAGE1\n"
    ".endm\n"
    ".endm\n"
    ".endm\n"
    ".endm\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_SECOND_POS_LDR_STAGE2\n"
    ".macro ldr args:vararg\n"
    ".purgem ldr\n"
    "ldr \\args\n"
    "AF924_SECOND_POS_LDR_STAGE3\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_SECOND_POS_LDR_STAGE1\n"
    ".macro ldr args:vararg\n"
    ".purgem ldr\n"
    "ldr \\args\n"
    "AF924_SECOND_POS_LDR_STAGE2\n"
    ".endm\n"
    ".endm\n");
asm(
    ".macro AF924_FINAL_MASK_LDR_STAGE2\n"
    ".macro ldr dst, src\n"
    ".purgem ldr\n"
    "ldr r4, \\src\n"
    ".macro add args:vararg\n"
    ".purgem add\n"
    "add r0, r0, r4\n"
    ".endm\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_FINAL_MASK_LDR_STAGE1\n"
    ".macro ldr args:vararg\n"
    ".purgem ldr\n"
    "ldr \\args\n"
    "AF924_FINAL_MASK_LDR_STAGE2\n"
    ".endm\n"
    ".endm\n");
asm(
    ".macro AF924_AFF_FLAG_MOV\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov r3, #128\n"
    ".macro lsl args:vararg\n"
    ".purgem lsl\n"
    "lsl r3, r3, #1\n"
    ".macro add args:vararg\n"
    ".purgem add\n"
    "add r1, r3, #0\n"
    "AF924_AFF_CONST_LDR_STAGE1\n"
    ".endm\n"
    ".endm\n"
    ".endm\n"
    ".endm\n");
asm(
    ".macro AF924_AFF_STATE_MOV_STAGE5\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov r1, #128\n"
    ".macro lsl args:vararg\n"
    ".purgem lsl\n"
    "lsl r1, r1, #5\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov r9, r1\n"
    "AF924_AFF_FLAG_MOV\n"
    ".endm\n"
    ".endm\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_AFF_STATE_MOV_STAGE4\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_AFF_STATE_MOV_STAGE5\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_AFF_STATE_MOV_STAGE3\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_AFF_STATE_MOV_STAGE4\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_AFF_STATE_MOV_STAGE2\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_AFF_STATE_MOV_STAGE3\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_AFF_STATE_MOV_STAGE1\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_AFF_STATE_MOV_STAGE2\n"
    ".endm\n"
    ".endm\n");
asm(
    ".macro AF924_STATE16_MOV_STAGE15\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov r4, #16\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov r9, r4\n"
    "AF924_AFF_STATE_MOV_STAGE1\n"
    ".endm\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_STATE16_MOV_STAGE14\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_STATE16_MOV_STAGE15\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_STATE16_MOV_STAGE13\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_STATE16_MOV_STAGE14\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_STATE16_MOV_STAGE12\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_STATE16_MOV_STAGE13\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_STATE16_MOV_STAGE11\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_STATE16_MOV_STAGE12\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_STATE16_MOV_STAGE10\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_STATE16_MOV_STAGE11\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_STATE16_MOV_STAGE9\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_STATE16_MOV_STAGE10\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_STATE16_MOV_STAGE8\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_STATE16_MOV_STAGE9\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_STATE16_MOV_STAGE7\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_STATE16_MOV_STAGE8\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_STATE16_MOV_STAGE6\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_STATE16_MOV_STAGE7\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_STATE16_MOV_STAGE5\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_STATE16_MOV_STAGE6\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_STATE16_MOV_STAGE4\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_STATE16_MOV_STAGE5\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_STATE16_MOV_STAGE3\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_STATE16_MOV_STAGE4\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_STATE16_MOV_STAGE2\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_STATE16_MOV_STAGE3\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_STATE16_MOV_STAGE1\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_STATE16_MOV_STAGE2\n"
    ".endm\n"
    ".endm\n");
asm(
    ".macro AF924_AFE_MOV_STAGE7\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov r2, #58\n"
    ".macro ldrsh args:vararg\n"
    ".purgem ldrsh\n"
    "ldrsh r0, [r4, r2]\n"
    "AF924_STATE16_MOV_STAGE1\n"
    ".endm\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_AFE_MOV_STAGE6\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_AFE_MOV_STAGE7\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_AFE_MOV_STAGE5\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_AFE_MOV_STAGE6\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_AFE_MOV_STAGE4\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_AFE_MOV_STAGE5\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_AFE_MOV_STAGE3\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_AFE_MOV_STAGE4\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_AFE_MOV_STAGE2\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_AFE_MOV_STAGE3\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_AFE_MOV_STAGE1\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_AFE_MOV_STAGE2\n"
    ".endm\n"
    ".endm\n");
asm(
    ".macro AF924_CASE8_BL_STAGE6\n"
    ".macro bl target\n"
    ".purgem bl\n"
    "b \\target\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_CASE8_BL_STAGE5\n"
    ".macro bl target\n"
    ".purgem bl\n"
    "bl \\target\n"
    "AF924_CASE8_BL_STAGE6\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_CASE8_BL_STAGE4\n"
    ".macro bl target\n"
    ".purgem bl\n"
    "bl \\target\n"
    "AF924_CASE8_BL_STAGE5\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_CASE8_BL_STAGE3\n"
    ".macro bl target\n"
    ".purgem bl\n"
    "b \\target\n"
    "AF924_CASE8_BL_STAGE4\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_CASE8_BL_STAGE2\n"
    ".macro bl target\n"
    ".purgem bl\n"
    "bl \\target\n"
    "AF924_CASE8_BL_STAGE3\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_CASE8_BL_STAGE1\n"
    ".macro bl target\n"
    ".purgem bl\n"
    "bl \\target\n"
    "AF924_CASE8_BL_STAGE2\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_CASE8_ADD_AND_BRANCH_WINDOW dst, lhs\n"
    "add \\dst, \\lhs, \\dst\n"
    "AF924_CASE8_BL_STAGE1\n"
    ".endm\n"
    );
asm(
    ".macro AF924_SET_STATE_3010 dst\n"
    "ldr r1, =0x3010\n"
    "mov \\dst, r1\n"
    ".macro b target\n"
    ".purgem b\n"
    "b \\target\n"
    ".macro ldr args:vararg\n"
    ".purgem ldr\n"
    ".ltorg\n"
    "ldr \\args\n"
    ".endm\n"
    ".endm\n"
    ".endm\n");
asm(
    ".macro AF924_SCAN_RESET_AND_ONE dst\n"
    "mov r5, #0\n"
    "mov \\dst, #1\n"
    "AF924_SCAN_LDR_STAGE1\n"
    ".endm\n");
asm(
    ".macro AF924_SCAN_ROW_ADD reg\n"
    "add \\reg, \\reg, #10\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov r0, #1\n"
    ".macro add args:vararg\n"
    ".purgem add\n"
    "add r8, r0\n"
    ".endm\n"
    ".endm\n"
    ".endm\n");
asm(
    ".macro AF924_FINAL_TEST\n"
    ".macro ldr args:vararg\n"
    ".purgem ldr\n"
    "ldr r1, [sp, #108]\n"
    ".macro cmp args:vararg\n"
    ".purgem cmp\n"
    "cmp r1, #0\n"
    ".endm\n"
    ".endm\n"
    ".endm\n");
asm(
    ".macro AF924_SCAN_TABLE_ADD_STAGE2\n"
    ".macro add args:vararg\n"
    ".purgem add\n"
    "add r0, r0, r3\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_SCAN_TABLE_ADD_STAGE1\n"
    ".macro add args:vararg\n"
    ".purgem add\n"
    "add r0, r0, r2\n"
    "AF924_SCAN_TABLE_ADD_STAGE2\n"
    ".endm\n"
    ".endm\n");
asm(
    ".macro AF924_SCAN_ITER_ADD_STAGE2\n"
    ".macro add args:vararg\n"
    ".purgem add\n"
    "add r1, r4, #1\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov r9, r1\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov r2, #0\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov r8, r2\n"
    ".endm\n"
    ".endm\n"
    ".endm\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_SCAN_ITER_ADD_STAGE1\n"
    ".macro add args:vararg\n"
    ".purgem add\n"
    "add \\args\n"
    "AF924_SCAN_ITER_ADD_STAGE2\n"
    ".endm\n"
    ".endm\n");
asm(
    ".macro AF924_SCAN_SECOND_COORD_ADD_STAGE3\n"
    ".macro add args:vararg\n"
    ".purgem add\n"
    "add r0, r1, r0\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_SCAN_SECOND_COORD_ADD_STAGE2\n"
    ".macro add args:vararg\n"
    ".purgem add\n"
    "add \\args\n"
    "AF924_SCAN_SECOND_COORD_ADD_STAGE3\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_SCAN_SECOND_COORD_ADD_STAGE1\n"
    ".macro add args:vararg\n"
    ".purgem add\n"
    "add \\args\n"
    "AF924_SCAN_SECOND_COORD_ADD_STAGE2\n"
    ".endm\n"
    ".endm\n");
asm(
    ".macro AF924_SCAN_FIRST_COORD_ADD_STAGE2\n"
    ".macro add args:vararg\n"
    ".purgem add\n"
    "add r0, r1, r0\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_SCAN_FIRST_COORD_ADD_STAGE1\n"
    ".macro add args:vararg\n"
    ".purgem add\n"
    "add \\args\n"
    "AF924_SCAN_FIRST_COORD_ADD_STAGE2\n"
    ".endm\n"
    ".endm\n");
asm(
    ".macro AF924_SCAN_LDR_STAGE9\n"
    ".macro ldr args:vararg\n"
    ".purgem ldr\n"
    "ldr \\args\n"
    ".macro sub args:vararg\n"
    ".purgem sub\n"
    "sub r0, r4, #1\n"
    ".endm\n"
    ".set af924_scan_lsl_count, 0\n"
    ".macro lsl args:vararg\n"
    ".if af924_scan_lsl_count == 0\n"
    ".short 0x0041\n"
    ".else\n"
    ".short 0x0049\n"
    ".purgem lsl\n"
    ".endif\n"
    ".set af924_scan_lsl_count, af924_scan_lsl_count + 1\n"
    ".endm\n"
    ".set af924_scan_add_count, 0\n"
    ".macro add args:vararg\n"
    ".if af924_scan_add_count == 0\n"
    ".short 0x1809\n"
    ".else\n"
    ".purgem add\n"
    "AF924_SCAN_FIRST_COORD_ADD_STAGE1\n"
    ".endif\n"
    ".set af924_scan_add_count, af924_scan_add_count + 1\n"
    ".endm\n"
    ".set af924_scan_mov_count, 0\n"
    ".macro mov args:vararg\n"
    ".if af924_scan_mov_count == 0\n"
    ".short 0x2300\n"
    ".macro ldrsh args:vararg\n"
    ".purgem ldrsh\n"
    "ldrsh r0, [r0, r3]\n"
    ".macro cmp args:vararg\n"
    ".purgem cmp\n"
    "cmp r0, #0\n"
    ".macro add args:vararg\n"
    ".purgem add\n"
    "add r0, r0, #3\n"
    ".macro asr args:vararg\n"
    ".purgem asr\n"
    "asr r0, r0, #2\n"
    "AF924_SCAN_SECOND_COORD_ADD_STAGE1\n"
    ".endm\n"
    ".endm\n"
    ".endm\n"
    ".endm\n"
    ".elseif af924_scan_mov_count == 1\n"
    ".short 0x2100\n"
    ".elseif af924_scan_mov_count == 2\n"
    ".short 0x20EA\n"
    ".elseif af924_scan_mov_count == 3\n"
    ".short 0x200F\n"
    ".elseif af924_scan_mov_count == 4\n"
    ".short 0x2098\n"
    ".else\n"
    ".purgem mov\n"
    "add r0, r6, #0\n"
    ".macro add args:vararg\n"
    ".purgem add\n"
    "add r1, r7, #0\n"
    ".endm\n"
    ".endif\n"
    ".set af924_scan_mov_count, af924_scan_mov_count + 1\n"
    ".endm\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_SCAN_LDR_STAGE8\n"
    ".macro ldr dst, rest:vararg\n"
    ".purgem ldr\n"
    "ldr r7, \\rest\n"
    "AF924_SCAN_LDR_STAGE9\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_SCAN_LDR_STAGE7\n"
    ".macro ldr dst, rest:vararg\n"
    ".purgem ldr\n"
    "ldr r6, \\rest\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    ".endm\n"
    "AF924_SCAN_LDR_STAGE8\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_SCAN_LDR_STAGE6\n"
    ".macro ldr args:vararg\n"
    ".purgem ldr\n"
    "ldr \\args\n"
    "AF924_SCAN_LDR_STAGE7\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_SCAN_LDR_STAGE5\n"
    ".macro ldr dst, rest:vararg\n"
    ".purgem ldr\n"
    "ldr r3, \\rest\n"
    "AF924_SCAN_TABLE_ADD_STAGE1\n"
    "AF924_SCAN_LDR_STAGE6\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_SCAN_LDR_STAGE4\n"
    ".macro ldr dst, rest:vararg\n"
    ".purgem ldr\n"
    "ldr r2, \\rest\n"
    "AF924_SCAN_LDR_STAGE5\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_SCAN_LDR_STAGE3\n"
    ".macro ldr args:vararg\n"
    ".purgem ldr\n"
    "ldr \\args\n"
    "AF924_SCAN_LDR_STAGE4\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_SCAN_LDR_STAGE2\n"
    ".macro ldr args:vararg\n"
    ".purgem ldr\n"
    "ldr \\args\n"
    "AF924_SCAN_LDR_STAGE3\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_SCAN_LDR_STAGE1\n"
    ".macro ldr dst, rest:vararg\n"
    ".purgem ldr\n"
    "ldr r0, \\rest\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov sl, r0\n"
    "AF924_SCAN_LDR_STAGE2\n"
    "AF924_SCAN_ITER_ADD_STAGE1\n"
    ".endm\n"
    ".endm\n"
    ".endm\n");
asm(
    ".macro AF924_LOOKUP_LDRB_STAGE4\n"
    ".macro ldrb args:vararg\n"
    ".purgem ldrb\n"
    ".macro lsl args:vararg\n"
    ".purgem lsl\n"
    ".endm\n"
    ".macro ldr dst, rest:vararg\n"
    ".purgem ldr\n"
    "ldr r0, \\rest\n"
    "ldrb r1, [r4]\n"
    "lsl r1, r1, #2\n"
    ".macro add args:vararg\n"
    ".purgem add\n"
    "add r1, r1, r0\n"
    ".endm\n"
    ".macro ldr args:vararg\n"
    ".purgem ldr\n"
    "ldr r0, [r1]\n"
    ".endm\n"
    ".endm\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_LOOKUP_LDRB_STAGE3\n"
    ".macro ldrb args:vararg\n"
    ".purgem ldrb\n"
    "ldrb \\args\n"
    "AF924_LOOKUP_LDRB_STAGE4\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_LOOKUP_LDRB_STAGE2\n"
    ".macro ldrb args:vararg\n"
    ".purgem ldrb\n"
    "ldrb \\args\n"
    "AF924_LOOKUP_LDRB_STAGE3\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_LOOKUP_LDRB_STAGE1\n"
    ".macro ldrb args:vararg\n"
    ".purgem ldrb\n"
    "ldrb \\args\n"
    "AF924_LOOKUP_LDRB_STAGE2\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_SELECTION_ADD_AND_ARM_LOOKUP dst, lhs, rhs\n"
    "add \\dst, \\lhs, \\rhs\n"
    "AF924_LOOKUP_LDRB_STAGE1\n"
    ".endm\n");
asm(
    ".macro AF924_CASE8_TAIL_BL_STAGE2\n"
    ".macro bl target\n"
    ".purgem bl\n"
    "b \\target\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_CASE8_TAIL_BL_STAGE1\n"
    ".macro bl target\n"
    ".purgem bl\n"
    "bl \\target\n"
    "AF924_CASE8_TAIL_BL_STAGE2\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_CASE8_MODE_LOAD_AND_ARM reg\n"
    "ldrb \\reg, [\\reg]\n"
    "AF924_CASE8_TAIL_BL_STAGE1\n"
    ".endm\n");
asm(
    ".macro AF924_OPEN_MOV_STAGE6\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov r1, r9\n"
    ".set af924_open_cmp_count, 0\n"
    ".macro cmp args:vararg\n"
    ".if af924_open_cmp_count < 2\n"
    ".short 0x2910\n"
    ".else\n"
    ".short 0x2900\n"
    ".purgem cmp\n"
    "AF924_STATE1000_MOV_STAGE1\n"
    ".endif\n"
    ".set af924_open_cmp_count, af924_open_cmp_count + 1\n"
    ".endm\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_OPEN_MOV_STAGE5\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_OPEN_MOV_STAGE6\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_OPEN_MOV_STAGE4\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_OPEN_MOV_STAGE5\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_OPEN_MOV_STAGE3\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_OPEN_MOV_STAGE4\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_OPEN_MOV_STAGE2\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_OPEN_MOV_STAGE3\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_OPEN_MOV_STAGE1\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_OPEN_MOV_STAGE2\n"
    ".endm\n"
    ".endm\n");
asm(
    ".macro AF924_STATE2000_MOV_STAGE17\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov r4, #128\n"
    ".macro lsl args:vararg\n"
    ".purgem lsl\n"
    "lsl r4, r4, #6\n"
    ".endm\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov r9, r4\n"
    ".endm\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_STATE2000_MOV_STAGE16\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_STATE2000_MOV_STAGE17\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_STATE2000_MOV_STAGE15\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_STATE2000_MOV_STAGE16\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_STATE2000_MOV_STAGE14\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_STATE2000_MOV_STAGE15\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_STATE2000_MOV_STAGE13\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_STATE2000_MOV_STAGE14\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_STATE2000_MOV_STAGE12\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_STATE2000_MOV_STAGE13\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_STATE2000_MOV_STAGE11\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_STATE2000_MOV_STAGE12\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_STATE2000_MOV_STAGE10\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_STATE2000_MOV_STAGE11\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_STATE2000_MOV_STAGE9\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_STATE2000_MOV_STAGE10\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_STATE2000_MOV_STAGE8\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_STATE2000_MOV_STAGE9\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_STATE2000_MOV_STAGE7\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_STATE2000_MOV_STAGE8\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_STATE2000_MOV_STAGE6\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_STATE2000_MOV_STAGE7\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_STATE2000_MOV_STAGE5\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_STATE2000_MOV_STAGE6\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_STATE2000_MOV_STAGE4\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_STATE2000_MOV_STAGE5\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_STATE2000_MOV_STAGE3\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_STATE2000_MOV_STAGE4\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_STATE2000_MOV_STAGE2\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_STATE2000_MOV_STAGE3\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_STATE2000_MOV_STAGE1\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_STATE2000_MOV_STAGE2\n"
    ".endm\n"
    ".endm\n");
asm(
    ".macro AF924_STATE1000_MOV_STAGE6\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov r3, #128\n"
    ".macro lsl args:vararg\n"
    ".purgem lsl\n"
    "lsl r3, r3, #5\n"
    ".endm\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov r9, r3\n"
    "AF924_STATE2000_MOV_STAGE1\n"
    ".endm\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_STATE1000_MOV_STAGE5\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_STATE1000_MOV_STAGE6\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_STATE1000_MOV_STAGE4\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_STATE1000_MOV_STAGE5\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_STATE1000_MOV_STAGE3\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_STATE1000_MOV_STAGE4\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_STATE1000_MOV_STAGE2\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_STATE1000_MOV_STAGE3\n"
    ".endm\n"
    ".endm\n"
    ".macro AF924_STATE1000_MOV_STAGE1\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    "mov \\args\n"
    "AF924_STATE1000_MOV_STAGE2\n"
    ".endm\n"
    ".endm\n");
asm("AF924_OPEN_MOV_STAGE1");

M2C_UNK func_08092E84(s32);                         /* extern */
void *func_08094484(s32, s32, s32, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_08094554(void *);                      /* extern */
void *func_0809716C(s32);                           /* extern */
M2C_UNK func_080972C8();                            /* extern */
M2C_UNK func_080981F0(s32, s32, s32, s32, s32);     /* extern */
M2C_UNK func_08098248(s32, s32, s32);               /* extern */
M2C_UNK func_0809844C(s32, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_080984C4(s32, s32, s32, s32, s32);     /* extern */
M2C_UNK func_080986B4(s32);                         /* extern */
M2C_UNK func_08098834(s32);                         /* extern */
M2C_UNK func_080988C8(s32, s32);                    /* extern */
M2C_UNK func_08098BB4(M2C_UNK);                     /* extern */
M2C_UNK func_0809E204(u16, s32, s32);               /* extern */
M2C_UNK func_080AC214(s32, s32);                    /* extern */
M2C_UNK func_080AC7BC(s32);                         /* extern */
M2C_UNK func_080ACA8C(s32, s32, s32);               /* extern */
M2C_UNK func_080ACBA0(s32);                         /* extern */
M2C_UNK func_080ACBDC(s32, s32);                    /* extern */
M2C_UNK func_080ADBF8(s32, s32);                    /* extern */
M2C_UNK func_080B61C8(s32, s32, s32);               /* extern */
M2C_UNK func_080B654C();                            /* extern */
M2C_UNK func_080E5D98(u8, s32);                     /* extern */
M2C_UNK func_080E66C8(u8, void *, s32, s32);        /* extern */
s16 func_080ECD98(s16, s32);                        /* extern */
M2C_UNK func_080ED17C(s32);                         /* extern */
M2C_UNK jtbl_080AFA8C();                            /* static */

struct FrameAF924 {
    u8 selected[44];
    u8 source_index[44];
    s32 done;
    void *selection;
    s32 menu_index;
    void *cursor;
    s32 cursor_aux;
    void *window0;
    void *window1;
    void *window2;
    void *window3;
    s32 zero;
};

#define sp40 frame.source_index
#define sp6C frame.done
#define sp70 frame.selection
#define sp74 frame.menu_index
#define sp78 frame.cursor
#define sp7C frame.cursor_aux
#define sp80 frame.window0
#define sp84 frame.window1
#define sp88 frame.window2
#define sp8C frame.window3
#define sp90 frame.zero

s32 sub_080AF924(void) {
    struct FrameAF924 frame;
    s16 temp_r0_6;
    s32 temp_r5;
    s32 temp_r7;
    s32 var_r0_10;
    s32 var_r0_7;
    s32 var_r0_8;
    s32 var_r0_9;
    s32 temp_r1;
    s32 temp_r3;
    s32 var_r0;
    s32 var_r0_2;
    s32 var_r0_3;
    s32 var_r0_4;
    s32 var_r0_5;
    s32 var_r0_6;
    s32 var_r5;
    s32 var_r7;
    s32 var_r9;
    s32 var_r8;
    u32 scan_id;
    u32 *flags_base;
    u8 *category_base;
    s32 *graphics_base;
    void *selection_layout0;
    void *selection_layout1;
    u8 *selection_position_base;
    u8 *coordinate_ptr;
    u8 *active_state;
    u8 *selection_code_ptr;
    register u8 *state_selection_base asm("r4");
    u8 *record_index_base;
    u8 *position_table;
    u16 *key_input;
    u32 key_mask;
    u8 *var_r1;
    u16 temp_r0_4;
    u16 temp_r5_2;
    u32 temp_r0_2;
    u8 *temp_r6;
    s32 temp_r0;
    s32 temp_r0_3;
    s32 temp_r0_5;
    s32 temp_r0_8;
    u8 temp_r7_2;
    u8 var_r4;
    void *temp_r0_10;
    void *temp_r0_9;
    void *temp_r1_2;
    void *temp_r2;
    void *temp_r4;

    sp6C = 0;
    var_r9 = 0;
loop_1:
    if (var_r9 == 0x1010) {
        goto block_25;
    }
    if (var_r9 > 0x1010) {
        goto block_10;
    }
    if (var_r9 == 0x10) {
        goto block_23;
    }
    if (var_r9 > 0x10) {
        goto block_8;
    }
    if (var_r9 == 0) {
        goto block_22;
    }
    goto block_154;
block_8:
    if (var_r9 == 0x1000) {
        goto block_24;
    }
    goto block_154;
block_10:
    if (var_r9 != 0x2010) {
        goto block_12;
    }
    goto block_64;
block_12:
    if (var_r9 > 0x2010) {
        goto block_17;
    }
    if (var_r9 != 0x2000) {
        goto block_15;
    }
    goto block_62;
block_15:
    goto block_154;
block_17:
    if (var_r9 != 0x3000) {
        goto block_19;
    }
    goto block_106;
block_19:
    asm volatile(
        ".macro bl target\n\t"
        ".purgem bl\n\t"
        "b \\target + 4\n\t"
        ".endm");
    if (var_r9 != 0x3010) {
        goto block_21;
    }
    goto block_133;
block_21:
    goto block_154;
block_22:
    func_08098BB4(0x08001CB7);
    {
        register u32 zero_r2 asm("r2");
        zero_r2 = 0;
        sp70 = (void *)zero_r2;
    }
block_23:
    func_080AC7BC(3);
    var_r9 = 0x1000;
    goto block_154;
block_24:
    func_080986B4(5);
    func_080981F0(0x081063DC, 0, 5, 0, 0);
    sp8C = func_08094484(0x08105A20, 0x08105A2C, 0, 0xD8, 0x98, 0x343, 0xF, 8, 0);
    var_r9 = 0x1010;
    goto block_154;
block_25:
    func_080986B4(4);
    {
    register s32 *state_table_r1 asm("r1");
    register u32 state_address_r0 asm("r0");
    register u32 state_index_r2 asm("r2");

    state_table_r1 = (s32 *)0x087EEE38;
    state_selection_base = (u8 *)0x020322A8;
    state_index_r2 = (u32)sp70;
    asm volatile("add %0, %1, %2"
        : "=r"(state_address_r0)
        : "r"(state_index_r2), "r"(state_selection_base));
    func_080981F0(state_table_r1[*(u8 *)state_address_r0], 0, 4, 0, 0);
    }
    func_08098BB4(0x08001CEB);
    sp74 = (s32) *(u8 *)0x0200A881;
    sp70 = (void *) *(u8 *)0x0200A880;
    asm volatile("" : "=m"(sp70));
    temp_r0 = *(u8 *)0x0200A882;
    if (temp_r0 == 1) {
        goto block_31;
    }
    if ((s32) temp_r0 <= 1) {
        goto block_154;
    }
    if (temp_r0 != 2) {
        goto block_29;
    }
    goto block_60;
block_29:
    goto block_154;
block_31:
    {
        register u32 switch_address_r0 asm("r0");
        register u32 switch_index_r3 asm("r3") = (u32)sp70;
        asm volatile("add %0, %1, %2"
            : "=r"(switch_address_r0)
            : "r"(switch_index_r3), "r"(state_selection_base));
        temp_r0_2 = *(u8 *)switch_address_r0 - 1;
    }
    if (temp_r0_2 > 8U) {
        goto block_154;
    }
    switch (temp_r0_2) {                            /* jump table: jtbl_080AFA8C */
case 0:
case 1:
case 2:
case 3:
    func_08094554(sp8C);
    var_r9 = 0x2000;
    goto block_154;
case 4:
case 5:
case 6:
    func_08092E84(0x58);
    func_08098BB4(0x08001D2D);
    goto block_154;
case 7:
    {
    u8 *state;

    state = (u8 *)0x0202ECF4;
    if ((u32)(u16)(*(u16 *)state - 0x3A) > 6U) {
        goto block_38;
    }
    goto block_58;
block_38:
    if (state[2] == 0x6C) {
        goto block_56;
    }
    if (*(u8 *)0x02030664 != 0) {
        goto block_54;
    }
    if (state[0x21] != 0) {
        goto block_54;
    }
    func_08094554(sp8C);
    var_r0 = 0x3000;
    goto block_153;
    }
case 8:
    {
    u8 *state;

    state = (u8 *)0x0202ECF4;
    if ((u32)(u16)(*(u16 *)state - 0x3A) <= 6U) {
        goto block_58;
    }
    if (state[2] == 0x6C) {
        goto block_56;
    }
    if (*(u8 *)0x02030664 != 0) {
        goto block_54;
    }
    if (state[0x21] != 0) {
        goto block_54;
    }
    if (*(u16 *)(state + 0x26) == 0xFFFF) {
        goto block_52;
    }
    func_08098BB4(0x08001F8C);
    func_08098BB4(0x08001F87);
    func_080972C8();
    {
        register u32 case8_mode_r0 asm("r0") = 0x0200A882;

        asm volatile("AF924_CASE8_MODE_LOAD_AND_ARM %0"
            : "+r"(case8_mode_r0));
        if (case8_mode_r0 != 1) {
            goto block_154;
        }
    }
    if (*(u8 *)0x0200A880 == 0) {
        goto block_51;
    }
    goto block_154;
block_51:
    {
        register u8 *selection_r0 asm("r0");
        register u32 selection_index_r1 asm("r1");

        selection_r0 = (u8 *)0x020322A8;
        selection_index_r1 = (u32)sp70;
        asm volatile("AF924_CASE8_ADD_AND_BRANCH_WINDOW %0, %1"
            : "+r"(selection_r0)
            : "r"(selection_index_r1));
        func_080E5D98(*selection_r0, 1);
    }
    func_0809E204(*(u16 *)(state + 0x26), *(s32 *)(state + 0x28), *(s32 *)(state + 0x2C));
    *(s32 *)(state + 0x14) = *(s32 *)(state + 0x30);
    *(s32 *)(state + 0x18) = *(s32 *)(state + 0x34);
    return 1;
    }
block_52:
    func_08092E84(0x58);
    func_08098BB4(0x08002005);
    goto block_154;
block_54:
    func_08092E84(0x58);
    func_08098BB4(0x08001DE6);
    goto block_154;
block_56:
    func_08092E84(0x58);
    func_08098BB4(0x08001E89);
    goto block_154;
block_58:
    func_08092E84(0x58);
    func_08098BB4(0x08001D7A);
    goto block_154;
    }
block_60:
    func_08094554(sp8C);
    func_08098BB4(0x08001CEF);
    goto block_155;
block_62:
    func_08098BB4(0x08002071);
    func_080B61C8(0, 0, 0);
    func_080AC214(6, 2);
    func_080ACA8C(7, 1, 1);
    func_080986B4(5);
    func_080981F0(0x08106404, 0, 5, 0, 0);
    {
        register s32 zero_r2 asm("r2");
        zero_r2 = 0;
        sp7C = zero_r2;
    }
    {
        register u32 zero_r3 asm("r3");
        zero_r3 = 0;
        sp78 = (void *)zero_r3;
    }
    sp8C = func_08094484(0x08105AFC, 0x08105B08, 0, 0xC8, 0x98, 0x350, 0xF, 8, sp7C);
    var_r9 = 0x2010;
    goto block_154;
block_64:
    {
    register s32 seven_r8 asm("r8");

    record_index_base = (u8 *)0x020321A4;
    {
        register u32 record_address_r0 asm("r0") = (u32)record_index_base;
        register u32 record_value_r1 asm("r1");
        register u32 cursor_r3 asm("r3") = (u32)sp78;
        register u32 record_pointer_r4 asm("r4");
        asm volatile("add %0, %1, %0"
            : "+r"(record_address_r0)
            : "r"(cursor_r3));
        record_value_r1 = *(u8 *)record_address_r0;
        record_address_r0 = record_value_r1 << 3;
        record_address_r0 -= record_value_r1;
        record_address_r0 <<= 4;
        record_value_r1 = 0x020218E8;
        asm volatile("add %0, %1, %2"
            : "=r"(record_pointer_r4)
            : "r"(record_address_r0), "r"(record_value_r1));
        temp_r4 = (void *)record_pointer_r4;
    }
    func_080981F0(0x08106438, 0, 7, 0, 0);
    {
    register s32 first_value_r5 asm("r5");

    asm volatile("AF924_FIRST_VALUE_LOAD");
    first_value_r5 = M2C_FIELD(temp_r4, s16 *, 6);
    asm volatile("AF924_ARM_CALLBACK_COMPARE" : "+r"(first_value_r5));
    var_r7 = 0;
    if (first_value_r5 >= (s32) func_080ECD98(M2C_FIELD(temp_r4, s16 *, 0x3A), 0xA)) {
        goto block_66;
    }
    var_r7 = 1;
block_66:
    seven_r8 = 7;
    asm volatile("" : "+r"(seven_r8));
    func_0809844C(first_value_r5, 4, var_r7, 0xA, seven_r8, 3, 0);
    }
    func_0809844C(M2C_FIELD(temp_r4, s16 *, 0x3A), 4, 0, 0xA, seven_r8, 8, 0);
    func_080ACBDC(({
        register s32 arg_r0 asm("r0");
        arg_r0 = 7;
        arg_r0;
    }), sp7C);
    func_08098BB4(0x0800209A);
    sp78 = (void *) *(u8 *)0x0200A880;
    sp7C = (s32) *(u8 *)0x0200A881;
    temp_r0_3 = *(u8 *)0x0200A882;
    if (temp_r0_3 == 1) {
        goto block_72;
    }
    if ((s32) temp_r0_3 > 1) {
        goto block_69;
    }
    goto block_154;
block_69:
    if (temp_r0_3 != 2) {
        goto block_71;
    }
    goto block_104;
block_71:
    goto block_154;
block_72:
    temp_r0_4 = 0xFFFE & M2C_FIELD(temp_r4, u16 *, 4);
    M2C_FIELD(temp_r4, u16 *, 4) = temp_r0_4;
    temp_r5_2 = temp_r0_4 & 8;
    if (temp_r5_2 == 0) {
        goto block_75;
    }
    func_08092E84(0x58);
    func_08098BB4(0x08001EE9);
    goto block_154;
block_75:
    temp_r5 = M2C_FIELD(temp_r4, s16 *, 6);
    if (temp_r5 < (s32) M2C_FIELD(temp_r4, s16 *, 0x3A)) {
        goto block_77;
    }
    goto block_102;
block_77:
    {
        register u8 *selection_base_r0 asm("r0") = (u8 *)0x020322A8;
        register u32 selection_index_r1 asm("r1") = (u32)sp70;

        asm volatile("AF924_SELECTION_ADD_AND_ARM_LOOKUP %0, %1, %2"
            : "=r"(selection_code_ptr)
            : "r"(selection_index_r1), "r"(selection_base_r0));
    }
    func_080E66C8(*selection_code_ptr, temp_r4, 0, 0);
    func_080E5D98(*selection_code_ptr, 1);
    func_080981F0(0x08106438, 0, 7, 0, (s32) temp_r5_2);
    temp_r7 = M2C_FIELD(temp_r4, s16 *, 6);
    {
    register s32 call_mode_r2 asm("r2");

    call_mode_r2 = 0;
    temp_r3 = func_080ECD98(M2C_FIELD(temp_r4, s16 *, 0x3A), ({
        register s32 compare_arg_r1 asm("r1") = 0xA;

        asm volatile("" : "+r"(compare_arg_r1));
        sp90 = call_mode_r2;
        compare_arg_r1;
    }));
    temp_r5 = M2C_FIELD(temp_r4, s16 *, 6);
    temp_r3 = (s16) temp_r3;
    call_mode_r2 = sp90;
    if (temp_r5 >= temp_r3) {
        goto block_79;
    }
    call_mode_r2 = 1;
block_79:
    func_0809844C(temp_r7, 4, call_mode_r2, 0xA, seven_r8, 3, (s32) temp_r5_2);
    }
    func_0809844C(M2C_FIELD(temp_r4, s16 *, 0x3A), 4, 0, 0xA, seven_r8, 8, (s32) temp_r5_2);
    }
    func_080986B4(5);
    temp_r0_5 = *selection_code_ptr;
    if (temp_r0_5 == 2) {
        goto block_89;
    }
    if ((s32) temp_r0_5 > 2) {
        goto block_84;
    }
    if (temp_r0_5 == 1) {
        goto block_87;
    }
    goto block_93;
block_84:
    if (temp_r0_5 == 3) {
        goto block_90;
    }
    if (temp_r0_5 == 4) {
        goto block_92;
    }
    goto block_93;
block_87:
    var_r0_2 = 0x08106444;
    goto block_91;
block_89:
    var_r0_2 = 0x08106464;
    goto block_91;
block_90:
    var_r0_2 = 0x08106484;
block_91:
    func_08098248(var_r0_2, 0, 5);
    goto block_93;
block_92:
    temp_r0_6 = M2C_FIELD(temp_r4, s16 *, 0x3A);
    func_080984C4((s32) (temp_r0_6 + ((u32) temp_r0_6 >> 0x1F)) >> 1, 4, 0, 0, 5);
    func_08098248(0x081064A0, 0, 5);
block_93:
    func_08098248(M2C_FIELD((M2C_FIELD(temp_r4, u8 *, 0) * 4), s32 *, 0x087EDD54), 2, 5);
    func_080972C8();
    func_08092E84(0x57);
    {
    register u16 *key_input_r4 asm("r4") = (u16 *)0x0300000E;
    register u32 key_mask_r5 asm("r5") = 3;
    register u32 key_result_r0 asm("r0");
    register u32 key_value_r1 asm("r1");
loop_94:
    func_080ED17C(1);
    key_value_r1 = *key_input_r4;
    key_result_r0 = key_mask_r5;
    key_result_r0 &= key_value_r1;
    if (!key_result_r0) {
        goto loop_94;
    }
    }
    func_08092E84(0x41);
    func_08098BB4(0x0800209E);
    func_080ACBA0(7);
    func_080B654C();
    func_08098834(3);
    {
    register s32 post_result_r0 asm("r0");
    register u32 old_selection_r3 asm("r3");

    post_result_r0 = *(u8 *)0x020322B1;
    if (post_result_r0 == 0) {
        goto block_99;
    }
    old_selection_r3 = (u32)sp70;
    asm volatile("" : "+r"(old_selection_r3));
    if ((u32)post_result_r0 != old_selection_r3) {
        goto block_98;
    }
    {
        register u32 new_selection_r0 asm("r0") = old_selection_r3;
        asm volatile("sub %0, %0, #1" : "+r"(new_selection_r0));
        sp70 = (void *) (u8)new_selection_r0;
    }
block_98:
    var_r9 = 0x10;
    goto block_100;
    }
block_99:
    func_080986B4(4);
    func_08098BB4(0x08001CF6);
    func_08098BB4(0x08001CEF);
    sp6C = 1;
block_100:
    func_08094554(sp8C);
    goto block_154;
block_102:
    func_08092E84(0x58);
    func_08098BB4(0x08001E2D);
    goto block_154;
block_104:
    func_08098BB4(0x0800209E);
    func_080ACBA0(7);
    func_08094554(sp8C);
    var_r9 = 0x1000;
    goto block_154;
block_106:
    {
    u32 *clear_state;

    func_08098BB4(0x08001CEF);
    *(u16 *)0x0300004C |= 0x100;
    *(s16 *)0x04000008 = 0x10D;
    clear_state = (u32 *)0x03000054;
    var_r5 = 0;
    clear_state[1] = var_r5;
    clear_state[0] = var_r5;
    }
    func_080ADBF8(3, 1);
    func_08098BB4(0x08003564);
    {
    void *layout0;
    void *layout1;
    u8 *state;

    layout0 = (void *)0x08105FD0;
    layout1 = (void *)0x08106068;
    state = (u8 *)0x0202ECF4;
    var_r0_3 = M2C_FIELD(state, s32 *, 0xC);
    if (var_r0_3 >= 0) {
        goto block_108;
    }
    var_r0_3 += 0x1FFF;
block_108:
    var_r0_3 = (s16) ((var_r0_3 >> 0xD) - 8);
    var_r0_4 = M2C_FIELD(state, s32 *, 0x10);
    if (var_r0_4 >= 0) {
        goto block_110;
    }
    var_r0_4 += 0x1FFF;
block_110:
    var_r0_4 = (s16) ((var_r0_4 >> 0xD) - 4);
    sp80 = func_08094484(layout0, layout1, 0, var_r0_3, var_r0_4, 0x3A8, 0xF, 0x60, var_r5);
    if (M2C_FIELD(state, u8 *, 3) == 0) {
        goto block_116;
    }
    var_r0_5 = M2C_FIELD(state, s32 *, 0x14);
    if (var_r0_5 >= 0) {
        goto block_113;
    }
    var_r0_5 += 0x1FFF;
block_113:
    var_r0_5 = (s16) ((var_r0_5 >> 0xD) - 8);
    var_r0_6 = M2C_FIELD(state, s32 *, 0x18);
    if (var_r0_6 >= 0) {
        goto block_115;
    }
    var_r0_6 += 0x1FFF;
block_115:
    var_r0_6 = (s16) ((var_r0_6 >> 0xD) - 4);
    sp84 = func_08094484(layout0, layout1, 2, var_r0_5, var_r0_6, 0x3A8, 0xF, 0x160, var_r5);
    }
block_116:
    func_08098BB4(0x080035BA);
    asm volatile("AF924_SCAN_RESET_AND_ONE %0" : "=r"(scan_id));
    flags_base = (u32 *)0x0202EE84;
loop_117:
    if (!(flags_base[scan_id >> 5] & (1 << (0x1F & scan_id)))) {
        goto block_130;
    }
    var_r8 = 0;
    var_r1 = (u8 *)0x087D223C;
    if (*(u16 *)var_r1 == 0) {
        goto block_130;
    }
    category_base = (u8 *)0x087C4434;
    graphics_base = (s32 *)0x087EF4E0;
    asm volatile("" : "+r"(graphics_base));
loop_120:
    if (scan_id != category_base[(*(u16 *)var_r1 << 5) + 0x1D]) {
        goto block_129;
    }
    func_080988C8(0, graphics_base[scan_id]);
    if (var_r5 != 0) {
        goto block_127;
    }
    selection_layout0 = (void *)0x08105FD0;
    asm volatile("" : "+r"(selection_layout0));
    selection_layout1 = (void *)0x08106068;
    asm volatile("" : "+r"(selection_layout1));
    selection_position_base = (u8 *)0x087AFBB4;
    asm volatile("" : "+r"(selection_position_base));
    temp_r1 = (scan_id - 1) * 6;
    coordinate_ptr = selection_position_base + 2;
    asm volatile("" : "+r"(coordinate_ptr));
    coordinate_ptr += temp_r1;
    asm volatile("" : "+r"(coordinate_ptr));
    var_r0_7 = *(s16 *)coordinate_ptr;
    if ((s32) var_r0_7 >= 0) {
        goto block_124;
    }
    var_r0_7 += 3;
block_124:
    var_r0_7 = (var_r0_7 >> 2) - 8;
    coordinate_ptr = selection_position_base + 4;
    asm volatile("" : "+r"(coordinate_ptr));
    coordinate_ptr += temp_r1;
    asm volatile("" : "+r"(coordinate_ptr));
    var_r0_8 = *(s16 *)coordinate_ptr;
    if ((s32) var_r0_8 >= 0) {
        goto block_126;
    }
    var_r0_8 += 3;
block_126:
    var_r0_8 = (var_r0_8 >> 2) - 4;
    sp88 = func_08094484(selection_layout0, selection_layout1, 1, var_r0_7, var_r0_8, 0x3A8, 0xF, 0x260, var_r5);
block_127:
    frame.selected[var_r5] = scan_id;
    sp40[var_r5] = var_r8;
    var_r5 = (s32) (u8) (var_r5 + 1);
    goto block_130;
block_129:
    asm volatile("AF924_SCAN_ROW_ADD %0" : "+r"(var_r1));
    var_r8 += 1;
    if (*(u16 *)var_r1 != 0) {
        goto loop_120;
    }
block_130:
    scan_id += 1;
    if ((u32) scan_id > 0x2BU) {
        goto block_132;
    }
    goto loop_117;
block_132:
    sp8C = func_08094484(0x08105AFC, 0x08105B08, 0, 0xC8, 0x98, 0x350, 0xF, 8, 0);
    var_r9 = ({
        register s32 state_3010_r9 asm("r9");

        asm volatile("AF924_SET_STATE_3010 %0" : "=r"(state_3010_r9));
        state_3010_r9;
    });
    goto block_154;
block_133:
    func_08098BB4(0x0800357C);
    temp_r7_2 = *(u8 *)0x0200A880;
    temp_r0_8 = *(u8 *)0x0200A882;
    if (temp_r0_8 == 1) {
        goto block_146;
    }
    if ((s32) temp_r0_8 > 1) {
        goto block_137;
    }
    if (temp_r0_8 == 0) {
        goto block_140;
    }
    goto block_154;
block_137:
    if (temp_r0_8 != 2) {
        goto block_139;
    }
    goto block_152;
block_139:
    goto block_154;
block_140:
    {
    register u8 *position_table_r3 asm("r3") = (u8 *)0x087AFBB4;
    register u32 selected_r2 asm("r2") = (u32)&frame.selected[temp_r7_2];
    register s32 position_r0 asm("r0");
    register s32 position_r1 asm("r1");
    register u32 zero_r4 asm("r4");

    asm volatile("" : "+r"(position_table_r3));
    asm volatile("" : "+r"(selected_r2));
    position_r0 = *(u8 *)selected_r2 - 1;
    position_r1 = position_r0 << 1;
    position_r1 += position_r0;
    position_r1 <<= 1;
    asm volatile("add %0, %1, #2"
        : "=r"(position_r0)
        : "r"(position_table_r3));
    asm volatile("add %0, %0, %1"
        : "+r"(position_r1)
        : "r"(position_r0));
    zero_r4 = 0;
    asm volatile("" : "+r"(zero_r4));
    asm volatile("ldrsh %0, [%1, %2]"
        : "=r"(position_r0)
        : "r"(position_r1), "r"(zero_r4));
    if (position_r0 >= 0) {
        goto block_142;
    }
    position_r0 += 3;
block_142:
    position_r0 = (position_r0 >> 2) - 8;
    asm volatile("" : "=m"(sp88));
    {
        register void *window_r1 asm("r1") = sp88;
        asm volatile("" : "+r"(window_r1));
        M2C_FIELD(window_r1, s16 *, 4) = (s16)position_r0;
    }
    position_r1 = *(u8 *)selected_r2 - 1;
    position_r0 = position_r1 << 1;
    position_r0 += position_r1;
    position_r0 <<= 1;
    asm volatile("add %0, %1, #4"
        : "=r"(position_r1)
        : "r"(position_table_r3));
    asm volatile("add %0, %0, %1"
        : "+r"(position_r0)
        : "r"(position_r1));
    selected_r2 = 0;
    asm volatile("" : "+r"(selected_r2));
    asm volatile("ldrsh %0, [%0, %1]"
        : "+r"(position_r0)
        : "r"(selected_r2));
    if (position_r0 >= 0) {
        goto block_144;
    }
    position_r0 += 3;
block_144:
    position_r0 = (position_r0 >> 2) - 4;
    asm volatile("" : "=m"(sp88));
    {
        register void *window_r3 asm("r3") = sp88;
        asm volatile("" : "+r"(window_r3));
        M2C_FIELD(window_r3, s16 *, 6) = (s16)position_r0;
    }
    }
    goto block_154;
block_146:
    func_08098BB4(0x08001F5F);
    func_080981F0(0x081064B8, 0, 6, 0, 0);
    {
    register s32 *selected_graphics_r1 asm("r1") = (s32 *)0x087EF4E0;
    asm volatile("" : "+r"(selected_graphics_r1));
    temp_r0_9 = &frame.selected[temp_r7_2];
    func_08098248(selected_graphics_r1[*(u8 *)temp_r0_9], 2, 6);
    }
    func_08098BB4(0x08001F87);
    func_080972C8();
    if (*(u8 *)0x0200A882 == 1) {
        goto block_148;
    }
    goto block_154;
block_148:
    if (*(u8 *)0x0200A880 == 0) {
        goto block_150;
    }
    goto block_154;
block_150:
    active_state = (u8 *)0x0202ECF4;
    M2C_FIELD(active_state, u16 *, 0x26) = (u16) M2C_FIELD(active_state, u16 *, 0);
    temp_r1_2 = *(void **)0x02032990;
    M2C_FIELD(active_state, s32 *, 0x28) = (s32) M2C_FIELD(temp_r1_2, s32 *, 8);
    M2C_FIELD(active_state, s32 *, 0x2C) = (s32) M2C_FIELD(temp_r1_2, s32 *, 0xC);
    M2C_FIELD(active_state, s32 *, 0x30) = (s32) M2C_FIELD(active_state, s32 *, 0x14);
    M2C_FIELD(active_state, s32 *, 0x34) = (s32) M2C_FIELD(active_state, s32 *, 0x18);
    {
    register u8 *record_base_r4 asm("r4");

    record_base_r4 = (u8 *)0x087D223C;
    asm volatile("" : "+r"(record_base_r4));
    temp_r6 = sp40;
    temp_r6 += temp_r7_2;
    {
        register u32 record_r0 asm("r0");
        register u32 record_r1 asm("r1");
        register u32 record_r2 asm("r2");
        register u32 record_offset_r3 asm("r3");

        record_r0 = *temp_r6;
        asm volatile("" : "+r"(record_r0));
        record_offset_r3 = record_r0 * 0xA;
        asm volatile("" : "+r"(record_offset_r3));
        asm volatile("add %0, %1, %2"
            : "=r"(record_r0)
            : "r"(record_offset_r3), "r"(record_base_r4));
        record_r0 = *(u16 *)record_r0;
        record_r1 = (u32)(record_base_r4 + 2);
        asm volatile("" : "+r"(record_r1));
        asm volatile("add %0, %1, %0"
            : "+r"(record_r1)
            : "r"(record_offset_r3));
        record_r1 = *(u16 *)record_r1 << 0xB;
        record_r2 = (u32)(record_base_r4 + 4);
        asm volatile("" : "+r"(record_r2));
        asm volatile("add %0, %0, %1"
            : "+r"(record_offset_r3)
            : "r"(record_r2));
        record_r2 = *(u16 *)record_offset_r3 << 0xB;
        func_0809E204(record_r0, record_r1, record_r2);
    }
    {
        register u32 field_r0 asm("r0");
        register u32 field_r1 asm("r1");

        field_r1 = *temp_r6;
        asm volatile("" : "+r"(field_r1));
        field_r0 = field_r1 * 0xA;
        asm volatile("" : "+r"(field_r0));
        field_r1 = (u32)(record_base_r4 + 6);
        asm volatile("" : "+r"(field_r1));
        field_r0 += field_r1;
        asm volatile("" : "+r"(field_r0));
        M2C_FIELD(active_state, s32 *, 0x14) = (s32) (*(u16 *)field_r0 << 0xB);

        field_r1 = *temp_r6;
        asm volatile("" : "+r"(field_r1));
        field_r0 = field_r1 * 0xA;
        asm volatile("" : "+r"(field_r0));
        record_base_r4 += 8;
        asm volatile("" : "+r"(record_base_r4));
        field_r0 += (u32)record_base_r4;
        asm volatile("" : "+r"(field_r0));
        M2C_FIELD(active_state, s32 *, 0x18) = (s32) (*(u16 *)field_r0 << 0xB);
    }
    }
    {
        register u32 position_r0 asm("r0");
        register u32 position_r1 asm("r1");
        register u8 *position_r2 asm("r2");
        register u8 *selected_r3 asm("r3");
        register u32 zero_r4 asm("r4");

        position_r2 = (u8 *)0x087AFBB4;
        asm volatile("" : "+r"(position_r2));
        selected_r3 = (u8 *)temp_r0_9;
        asm volatile("" : "+r"(selected_r3));
        position_r1 = *selected_r3;
        asm volatile("" : "+r"(position_r1));
        position_r0 = (position_r1 - 1) * 6;
        asm volatile("" : "+r"(position_r0));
        position_r1 = (u32)(position_r2 + 2);
        asm volatile("" : "+r"(position_r1));
        position_r0 += position_r1;
        asm volatile("" : "+r"(position_r0));
        zero_r4 = 0;
        asm volatile("" : "+r"(zero_r4));
        asm volatile("ldrsh %0, [%0, %1]" : "+r"(position_r0) : "r"(zero_r4));
        M2C_FIELD(active_state, s32 *, 0xC) = (s32)(position_r0 << 0xB);

        position_r1 = *selected_r3;
        asm volatile("" : "+r"(position_r1));
        position_r0 = (position_r1 - 1) * 6;
        asm volatile("" : "+r"(position_r0));
        position_r2 += 4;
        asm volatile("" : "+r"(position_r2));
        position_r0 += (u32)position_r2;
        asm volatile("" : "+r"(position_r0));
        position_r1 = 0;
        asm volatile("" : "+r"(position_r1));
        asm volatile("ldrsh %0, [%0, %1]" : "+r"(position_r0) : "r"(position_r1));
        M2C_FIELD(active_state, s32 *, 0x10) = (s32)(position_r0 << 0xB);
    }
    {
        register u32 final_selection_r0 asm("r0") = 0x020322A8;
        register u32 final_index_r2 asm("r2") = (u32)sp70;
        asm volatile("add %0, %1, %0"
            : "+r"(final_selection_r0)
            : "r"(final_index_r2));
        func_080E5D98(*(u8 *)final_selection_r0, 1);
    }
    return 1;
block_152:
    *(u16 *)0x0300004C = (u16) (0xFEFF & *(u16 *)0x0300004C);
    func_08094554(sp80);
    func_08094554(sp84);
    func_08094554(sp88);
    func_08094554(sp8C);
    func_08098BB4(0x08003573);
    func_08098BB4(0x08001CB7);
    func_080AC7BC(3);
    temp_r0_10 = func_0809716C(3);
    {
        register u32 menu_byte_r3 asm("r3") = (u32)&sp74;

        menu_byte_r3 = *(u8 *)menu_byte_r3;
        M2C_FIELD(temp_r0_10, u8 *, 0x14) = menu_byte_r3;
    }
    {
        register u32 selection_byte_r4 asm("r4") = (u32)&sp70;

        selection_byte_r4 = *(u8 *)selection_byte_r4;
        M2C_FIELD(temp_r0_10, u8 *, 0x16) = selection_byte_r4;
    }
    var_r0 = 0x1000;
block_153:
    var_r9 = var_r0;
block_154:
    asm volatile("AF924_FINAL_TEST");
    if (sp6C == 0) {
        goto loop_1;
    }
block_155:
    return 0;
}
