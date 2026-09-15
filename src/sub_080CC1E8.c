#include "m2c_prelude.h"

struct Obj { u16 u0; u16 u2; u16 u4; u16 u6; };
struct Pair { u16 a; u16 b; };

extern void func_0809AA64(void *, s32, s32, s32);
extern struct Obj *func_08094374(void *, s32, s32, s16, s32, s32, s32, s32, s32);

extern u8 D_02034B4C[];
extern u8 D_0203ECFC[];
extern u8 *D_02033F38;
extern s16 D_087EC38C[];
extern s16 D_087EC38E[];
extern u8 D_087AC9D8[];
extern u8 D_087AC9E0[];
extern struct Obj *D_02033F58[];
extern struct Pair D_02033F74[];
extern struct Pair D_02033F90[];
extern u16 D_02033F92[];
extern s8 D_02033FAC[];
extern s8 D_02033FB3;

void sub_080CC1E8(void) {
    u8 i;
    s32 zero;
    struct Pair *pairs74;
    struct Pair *pairs90;
    register u8 *state asm("r8");
    register s16 *tableC asm("r9");
    register u16 *pairs76 asm("r10");
    struct Obj *ret;
    s32 temp_r1;

    func_0809AA64(D_087AC9D8, 0, 0x300, 0xD);
    i = 0;
    tableC = D_087EC38C;
    {
        register u8 *state_init asm("r1") = D_02034B4C;

        asm volatile("" : "+r"(state_init));
        state = state_init;
    }
    pairs90 = D_02033F90;
    pairs74 = D_02033F74;
    {
        register u16 *pairs76_init asm("r2") = &pairs74[0].b;

        asm volatile("" : "+r"(pairs76_init));
        pairs76 = pairs76_init;
    }
    do {
        register struct Obj **slot asm("r3");
        register u8 state_byte asm("r0");
        register u8 *lookup asm("r1");
        register u8 *lookup_value asm("r0");
        register u8 lookup_result asm("r1");

        state_byte = *(u8 *)(state + 0xA1AF);
        lookup = D_0203ECFC;
        lookup_value = (u8 *)(s32)state_byte;
        lookup_value += (s32)lookup;
        lookup_result = *lookup_value;
        temp_r1 = lookup_result * 4 + (*D_02033F38 << 5);
        ret = func_08094374(D_087AC9E0, 0, 0,
                *(s16 *)(temp_r1 + (s32)tableC),
                (s32)*(s16 *)((u8 *)D_087EC38E + temp_r1),
                0x300, 0xD, 0x1060, 0);
        slot = D_02033F58;
        slot = (struct Obj **)((i << 2) + (s32)slot);
        *slot = ret;
        pairs90[i].a = ret->u4;
        {
            register u16 *pairs92 asm("r0") = D_02033F92;
            register u16 *slot92 asm("r1");

            slot92 = (u16 *)((i << 2) + (s32)pairs92);
            *slot92 = (*slot)->u6;
        }
        pairs74[i].a = (*slot)->u4;
        {
            register u16 *slot76 asm("r2");

            slot76 = (u16 *)((u8 *)pairs76 + (i << 2));
            *slot76 = (*slot)->u6;
        }
        D_02033FAC[i] = 8;
        i++;
    } while (i <= 6);
    zero = 0;
    D_02033FB3 = zero;
}
