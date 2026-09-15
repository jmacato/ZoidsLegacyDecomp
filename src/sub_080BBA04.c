#include "m2c_prelude.h"

struct ViewStateBBA04 {
    s32 x;
    s32 y;
    s32 scale;
    s16 width;
    s16 field0E;
    s16 field10;
    u8 pad12[2];
    s32 center_x;
    s32 center_y;
    s32 size;
    u8 pad20[0x40];
    s32 flags;
};

M2C_UNK func_08092E0C(s32);                         /* extern */
M2C_UNK func_08092E74(u8);                          /* extern */
M2C_UNK func_08092E84(s32);                         /* extern */
M2C_UNK func_08092EA0(u8);                          /* extern */
s32 func_08092EB0(s32);                             /* extern */
M2C_UNK func_08093AE8(M2C_UNK, s32);                /* extern */
M2C_UNK func_08093B54();                            /* extern */
M2C_UNK func_08093B7C();                            /* extern */
s32 func_08094110();                                /* extern */
s32 func_08094484(M2C_UNK, M2C_UNK, s32, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_08094554(s32);                         /* extern */
M2C_UNK func_0809534C();                            /* extern */
M2C_UNK func_08096308(s32, s32);                    /* extern */
s32 func_0809669C();                                /* extern */
s32 *func_0809716C(s32);                            /* extern */
M2C_UNK func_080972C8();                            /* extern */
M2C_UNK func_080981F0(M2C_UNK, s32, s32, s32, s32); /* extern */
M2C_UNK func_08098248(s32, s32, s32);               /* extern */
M2C_UNK func_080984C4(u8, s32, s32, s32, s32);      /* extern */
M2C_UNK func_08098514(s32, s32, u32, s32, s32, s32); /* extern */
M2C_UNK func_080986B4(s32);                         /* extern */
M2C_UNK func_080988C8(s32, s32);                    /* extern */
M2C_UNK func_08098BB4(M2C_UNK);                     /* extern */
M2C_UNK func_0809A9C8(s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_0809AEA0();                            /* extern */
M2C_UNK func_0809AEC0(M2C_UNK, s32, s32);           /* extern */
u8 func_0809AEF4();                                 /* extern */
M2C_UNK func_0809B00C(s32, s32, s32);               /* extern */
u8 func_0809B040();                                 /* extern */
M2C_UNK func_0809E204(u16, s32, s32, s32);          /* extern */
M2C_UNK func_080B35D4(s32);                         /* extern */
M2C_UNK func_080B6768(void *);                      /* extern */
M2C_UNK func_080BAB3C();                            /* extern */
M2C_UNK func_080BAF2C(s32, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_080BB224(s32, u8, u8, s32);            /* extern */
s32 func_080BB654();                                /* extern */
u8 func_080BB660();                                 /* extern */
M2C_UNK func_080BB764();                            /* extern */
M2C_UNK func_080BB7EC();                            /* extern */
M2C_UNK func_080BB940();                            /* extern */
M2C_UNK func_080BE560(u8, u8);                      /* extern */
M2C_UNK func_080BE600();                            /* extern */
M2C_UNK func_080BE65C(u8, u8, s32, s32, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_080BE9D8(u8, u8, s32, s32, s32, s32, s32, s32, s32, s32); /* extern */
u8 func_080BF464(u32, u32, s32);                    /* extern */
M2C_UNK func_080BF858();                            /* extern */
M2C_UNK func_080BF984(u8, u8);                      /* extern */
M2C_UNK func_080BFA4C(u8, u8);                      /* extern */
M2C_UNK func_080BFB90();                            /* extern */
M2C_UNK func_080BFCD8();                            /* extern */
M2C_UNK func_080BFD1C(u8, u8);                      /* extern */
M2C_UNK func_080C030C(s32);                         /* extern */
M2C_UNK func_080C0AFC();                            /* extern */
s32 func_080C1414();                                /* extern */
s32 func_080C25DC(s32);                             /* extern */
M2C_UNK func_080C2DD0(u8);                          /* extern */
M2C_UNK func_080C3050(u8);                          /* extern */
M2C_UNK func_080C35C4(u8);                          /* extern */
M2C_UNK func_080C577C(s32);                         /* extern */
s32 func_080C598C();                                /* extern */
M2C_UNK func_080C5C00(u8, u8, u8);                  /* extern */
M2C_UNK func_080C5D14();                            /* extern */
M2C_UNK func_080C5DB4(s32);                         /* extern */
u8 func_080C682C();                                 /* extern */
M2C_UNK func_080C7190(s32);                         /* extern */
M2C_UNK func_080C8538(s32, u8);                     /* extern */
M2C_UNK func_080CA1A0();                            /* extern */
u8 func_080E5320(void *, u8);                       /* extern */
M2C_UNK func_080E5D98(u8, s32);                     /* extern */
s32 func_080E6664(s32);                             /* extern */
M2C_UNK func_080E6684();                            /* extern */
M2C_UNK func_080E83A4(u8, s32, s32, s32, s32, s32, u32); /* extern */
M2C_UNK func_080E8554(s32, s32);                    /* extern */
M2C_UNK func_080E8B08(u8, u8);                      /* extern */
M2C_UNK func_080E90AC(u8, u8);                      /* extern */
M2C_UNK func_080E9128();                            /* extern */
M2C_UNK func_080E94A0(u8, u8);                      /* extern */
M2C_UNK func_080E9998();                            /* extern */
M2C_UNK func_080E9D48();                            /* extern */
s32 func_080E9D88(u32, u32);                        /* extern */
M2C_UNK func_080EA408(u8, u8);                      /* extern */
M2C_UNK func_080ECD34(M2C_UNK, M2C_UNK);            /* extern */
u32 func_080ECD5C(s32);                             /* extern */
M2C_UNK func_080ED17C(s32);                         /* extern */
M2C_UNK jtbl_080BD764();                            /* static */
M2C_UNK jtbl_080BD9A4();                            /* static */
extern u8 D_02034B4C[];
asm(".set D_off_27A4_BBA04, 0x000027A4");
extern u8 D_off_27A4_BBA04[];
asm(".set D_off_27A5_BBA04, 0x000027A5");
extern u8 D_off_27A5_BBA04[];
asm(".set D_off_27A8_BBA04, 0x000027A8");
extern u8 D_off_27A8_BBA04[];
asm(".set D_off_27AC_BBA04, 0x000027AC");
extern u8 D_off_27AC_BBA04[];
asm(".set D_off_27B0_BBA04, 0x000027B0");
extern u8 D_off_27B0_BBA04[];
asm(".set D_off_A07C_BBA04, 0x0000A07C");
extern u8 D_off_A07C_BBA04[];
asm(".set D_off_A07E_BBA04, 0x0000A07E");
extern u8 D_off_A07E_BBA04[];
asm(".set D_02032E89, 0x02032E89");
extern u8 D_02032E89;
asm(".set D_0202F08C_BBA04, 0x0202F08C");
extern u16 D_0202F08C_BBA04[];
asm(".set D_02021690_BBA04, 0x02021690");
extern u32 D_02021690_BBA04;
asm(".set D_02021698_BBA04, 0x02021698");
extern u8 D_02021698_BBA04;
extern u8 D_02032EEC[2][6];
extern u8 *D_02032EBC[2][6];

void sub_080BBA04(void) {
    struct {
        u8 pad[12];
        u8 sp24[8];
        u8 sp2C[8];
        u8 sp34[8];
        volatile s32 sp3C;
        u8 tail[4];
    } stack;
    s16 temp_r5_8;
    register s32 *temp_r0 asm("r9");
    s32 temp_r0_10;
    s32 temp_r0_21;
    s32 temp_r2_17;
    s32 temp_r2_2;
    s32 temp_r4_16;
    s32 temp_r4_17;
    s32 temp_r4_2;
    s32 temp_r4_3;
    s32 base_200;
    s32 outer_200;
    s32 end_base_200;
    s32 outer_192;
    s32 outer_326;
    s32 outer_362;
    s32 base_183;
    s32 outer_183;
    s32 base_307;
    s32 outer_data_307;
    s32 outer_ptr_307;
    s32 zero_307;
    s32 slot_base_307;
    u32 next_307;
    s32 base_316;
    s32 outer_data_316;
    s32 outer_ptr_316;
    s32 zero_316;
    s32 slot_base_316;
    u32 next_316;
    s32 base_475;
    s32 outer_data_475;
    s32 outer_ptr_475;
    s32 zero_475;
    s32 slot_base_475;
    u32 next_475;
    s32 temp_r7;
    s32 temp_r7_2;
    s32 temp_r8;
    register s32 *mode_base asm("r4");
    register s32 var_r0_11 asm("r0");
    register s32 var_r0_12 asm("r0");
    s32 var_r0_13;
    s32 var_r0_3;
    s32 var_r0_8;
    s32 var_r2;
    s32 var_r2_3;
    s32 var_r2_4;
    s32 var_r5_12;
    s32 var_r5_6;
    s32 temp_r0_18;
    s32 temp_r0_20;
    u16 temp_r0_6;
    u16 temp_r1_3;
    u16 temp_r1_8;
    u16 var_r0_9;
    u32 temp_r0_13;
    u32 temp_r1;
    register u32 var_r0 asm("r0");
    u32 var_r0_10;
    u32 var_r0_2;
    register u32 var_r0_4 asm("r0");
    register u32 state_2300 asm("r5");
    register u32 var_r0_5 asm("r0");
    register u32 var_r0_6 asm("r0");
    u32 var_r4;
    u32 var_r4_4;
    u32 var_r5;
    u32 var_r5_10;
    u32 var_r5_11;
    u32 var_r5_13;
    u32 var_r5_3;
    u32 var_r5_4;
    u32 var_r5_5;
    u32 var_r5_8;
    u32 var_r5_9;
    u32 var_r6;
    u32 var_r6_10;
    register u32 var_r6_2 asm("r6");
    register u8 *base_113 asm("sl");
    register u32 next_113 asm("r7");
    u32 predicate_113;
    u32 var_r6_4;
    register u32 var_r8 asm("r8");
    u8 *temp_r1_2;
    u8 *temp_r4;
    u8 *scan_state;
    u16 *scan_table;
    u8 temp_r0_11;
    u8 temp_r0_14;
    s32 temp_r0_17;
s32 temp_r0_19;
    u8 temp_r0_2;
    s32 temp_r0_3;
    u8 temp_r0_4;
    u8 temp_r0_5;
    s32 temp_r0_7;
    u8 temp_r0_8;
    u8 temp_r0_9;
    u8 temp_r1_4;
    u8 temp_r1_5;
    u8 temp_r1_6;
    u8 temp_r1_7;
    u8 temp_r1_9;
    u8 temp_r2_12;
    u8 temp_r2_7;
    u8 temp_r4_10;
    u8 temp_r4_11;
    u8 temp_r4_12;
    u8 temp_r4_13;
    u8 temp_r4_14;
    u8 temp_r4_15;
    u8 temp_r4_18;
    u8 temp_r4_19;
    u8 temp_r4_20;
    u8 temp_r4_4;
    u8 temp_r4_5;
    u8 temp_r4_6;
    u8 temp_r4_7;
    u8 temp_r4_8;
    register u32 temp_r4_9 asm("r4");
    u8 temp_r5;
    u8 temp_r5_10;
    u8 temp_r5_11;
    u8 temp_r5_12;
    u8 temp_r5_2;
    u8 temp_r5_3;
    u8 temp_r5_4;
    u8 temp_r5_5;
    u8 temp_r5_6;
    u8 temp_r5_9;
    u8 var_r1;
    u8 var_r2_2;
    u8 var_r4_2;
    u8 var_r4_3;
    register u32 var_r5_2 asm("r5");
    u8 var_r5_7;
    u8 var_r6_11;
    u8 var_r6_12;
    u8 var_r6_13;
    u8 var_r6_14;
    u8 var_r6_16;
    u8 var_r6_17;
    u8 var_r6_18;
    u8 var_r6_19;
    u8 var_r6_3;
    u8 var_r6_7;
    u8 var_r6_8;
    u8 var_r6_9;
    void *temp_r0_12;
    void *temp_r0_15;
    void *temp_r0_16;
    void *temp_r2;
    void *temp_r2_10;
    void *temp_r2_11;
    void *temp_r2_13;
    void *temp_r2_14;
    void *temp_r2_16;
    void *temp_r2_3;
    void *temp_r2_4;
    void *temp_r2_5;
    void *temp_r2_6;
    void *temp_r2_8;
    void *temp_r2_9;
    void *temp_r5_7;
    void *var_r6_15;
    void *var_r6_5;

    {
        register s32 mode asm("r0");
        register s32 *saved_mode_base asm("r6");

        mode_base = (s32 *)0x02021690;
        mode = *mode_base;
        saved_mode_base = mode_base;

        if (mode != 9) {
            goto loop_647;
        }
    }
loop_1:
    {
        register s32 *state_seed asm("r0") = (s32 *)0x02030558;
        register u32 state_code asm("r2");
        temp_r1 = *state_seed;
        state_code = 0x2010;
        temp_r0 = state_seed;
        if (temp_r1 == state_code) {
            goto block_360;
        }
        if (temp_r1 <= state_code) {
            goto block_4;
        }
    }
    goto block_55;
block_4:
    if (temp_r1 == 0x1100) {
        goto block_237;
    }
    if (temp_r1 > 0x1100U) {
        goto block_33;
    }
    asm volatile(".macro bl target\n\tb \\target\n\t.endm");
    if (temp_r1 != 0x50) {
        goto block_8;
    }
    goto block_152;
block_8:
    asm volatile(".purgem bl");
    if (temp_r1 > 0x50U) {
        goto block_22;
    }
    if (temp_r1 != 0x20) {
        goto block_11;
    }
    goto block_130;
block_11:
    if (temp_r1 > 0x20U) {
        goto block_17;
    }
    if (temp_r1 != 0) {
        goto block_14;
    }
    goto block_101;
block_14:
    if (temp_r1 != 0x10) {
        goto block_16;
    }
    goto block_113;
block_16:
    goto block_643;
block_17:
    if (temp_r1 != 0x30) {
        goto block_19;
    }
    goto block_136;
block_19:
    if (temp_r1 != 0x40) {
        goto block_21;
    }
    goto block_141;
block_21:
    goto block_643;
block_22:
    if (temp_r1 == 0x1000) {
        goto block_192;
    }
    if (temp_r1 > 0x1000U) {
        goto block_27;
    }
    if (temp_r1 == 0x100) {
        goto block_179;
    }
    if (temp_r1 == 0x200) {
        goto block_190;
    }
    goto block_643;
block_27:
    if (temp_r1 == 0x1020) {
        goto block_208;
    }
    if (temp_r1 > 0x1020U) {
        goto block_31;
    }
    if (temp_r1 == 0x1010) {
        goto block_200;
    }
    goto block_643;
block_31:
    if (temp_r1 == 0x1030) {
        goto block_214;
    }
    goto block_643;
block_33:
    if (temp_r1 == 0x1330) {
        goto block_316;
    }
    if (temp_r1 > 0x1330U) {
        goto block_43;
    }
    if (temp_r1 == 0x1300) {
        goto block_280;
    }
    if (temp_r1 > 0x1300U) {
        goto block_40;
    }
    if (temp_r1 == 0x1200) {
        goto block_242;
    }
    if (temp_r1 == 0x1210) {
        goto block_266;
    }
    goto block_643;
block_40:
    if (temp_r1 == 0x1310) {
        goto block_307;
    }
    if (temp_r1 == 0x1320) {
        goto block_315;
    }
    goto block_643;
block_43:
    if (temp_r1 == 0x13F0) {
        goto block_333;
    }
    if (temp_r1 > 0x13F0U) {
        goto block_49;
    }
    if (temp_r1 == 0x1340) {
        goto block_323;
    }
    if (temp_r1 == 0x1350) {
        goto block_325;
    }
    goto block_643;
block_49:
    var_r5 = 0x1500;
    if (temp_r1 == 0x1500) {
        goto block_347;
    }
    if (temp_r1 > 0x1500U) {
        goto block_53;
    }
    if (temp_r1 == 0x1400) {
        goto block_335;
    }
    goto block_643;
block_53:
    if (temp_r1 == 0x2000) {
        goto block_351;
    }
    goto block_643;
block_55:
    if (temp_r1 == 0x3400) {
        goto block_517;
    }
    if (temp_r1 > 0x3400U) {
        goto block_79;
    }
    state_2300 = 0x2300;
    if (temp_r1 == state_2300) {
        goto loop_454;
    }
    if (temp_r1 > state_2300) {
        goto block_67;
    }
    if (temp_r1 == 0x2040) {
        goto block_390;
    }
    if (temp_r1 > 0x2040U) {
        goto block_64;
    }
    if (temp_r1 == 0x2020) {
        goto block_361;
    }
    if (temp_r1 == 0x2030) {
        goto block_368;
    }
    goto block_643;
block_64:
    if (temp_r1 == 0x2100) {
        goto block_443;
    }
    if (temp_r1 == 0x2200) {
        goto block_445;
    }
    goto block_643;
block_67:
    if (temp_r1 == 0x3010) {
        goto block_486;
    }
    if (temp_r1 > 0x3010U) {
        goto block_73;
    }
    if (temp_r1 == 0x2400) {
        goto block_462;
    }
    if (temp_r1 == 0x3000) {
        goto block_475;
    }
    goto block_643;
block_73:
    if (temp_r1 == 0x3200) {
        goto block_501;
    }
    if (temp_r1 > 0x3200U) {
        goto block_77;
    }
    if (temp_r1 == 0x3100) {
        goto block_495;
    }
    goto block_643;
block_77:
    if (temp_r1 == 0x3300) {
        goto block_512;
    }
    goto block_643;
block_79:
    var_r5 = 0x7000;
    if (temp_r1 == 0x7000) {
        goto block_606;
    }
    if (temp_r1 > 0x7000U) {
        goto block_89;
    }
    if (temp_r1 == 0x4000) {
        goto block_541;
    }
    if (temp_r1 > 0x4000U) {
        goto block_86;
    }
    if (temp_r1 == 0x3500) {
        goto block_522;
    }
    if (temp_r1 == 0x3600) {
        goto block_527;
    }
    goto block_643;
block_86:
    if (temp_r1 == 0x5000) {
        goto block_558;
    }
    if (temp_r1 == 0x6000) {
        goto block_569;
    }
    goto block_643;
block_89:
    if (temp_r1 == 0xA000) {
        goto block_630;
    }
    if (temp_r1 > 0xA000U) {
        goto block_94;
    }
    if (temp_r1 == 0x8000) {
        goto block_621;
    }
    if (temp_r1 == 0x9000) {
        goto block_625;
    }
    goto block_643;
block_94:
    if (temp_r1 == 0xFF10) {
        goto block_637;
    }
    if (temp_r1 > 0xFF10U) {
        goto block_98;
    }
    if (temp_r1 == 0xFF00) {
        goto block_635;
    }
    goto block_643;
block_98:
    if (temp_r1 == 0xFF20) {
        goto block_640;
    }
    goto block_643;
block_101:
    if (M2C_FIELD((void *)0x0203055C, u8 *, 0) != 0) {
        goto block_107;
    }
    goto loop_105;
block_104:
    func_080ED17C(1);
loop_105:
    if (func_08092EB0(0x52) == 0) {
        goto block_104;
    }
    {
        u8 *state_base;
        register u8 *table asm("r5");
        u8 *output;
        register u32 value asm("r1");
        register u32 column_term asm("r2");
        register u32 hundred asm("r0");
        u32 row_term;

        output = (u8 *)0x02032EF8;
        table = (u8 *)0x087B9454;
        state_base = (u8 *)0x0203055C;
        value = state_base[4];
        asm volatile("" : "+r"(value));
        hundred = 100;
        column_term = value;
        column_term *= hundred;
        value = state_base[3];
        row_term = value << 5;
        row_term -= value;
        row_term <<= 2;
        row_term += value;
        row_term <<= 4;
        column_term += row_term;
        column_term += (u32)table;
        *output = *(u8 *)column_term;
        func_08092E74(*output);
        func_080BE600();
        func_080E9128();
        func_080E94A0(state_base[3], state_base[4]);
    }
block_107:
    {
    register u8 *base asm("r4");
    register u32 zero asm("r5");
    register u32 counter asm("r6");
    register s32 offset_a070 asm("r3");
    {
        register s32 offset asm("r1");
        register u8 *address asm("r0");
        base = D_02034B4C;
        offset = 0x270C;
        asm volatile("" : "+r"(offset));
        address = base + offset;
        zero = 0;
        *address = zero;
    }
    {
        u32 value;
        register s32 offset asm("r2");
        register u8 *address asm("r1");
        value = (u32)(func_080ECD5C(*(u32 *)0x03000010) * 100) >> 15;
        offset = 0x270D;
        asm volatile("" : "+r"(offset));
        address = base + offset;
        *address = value;
    }
    {
        register u8 *address_a070 asm("r1");
        register s32 offset_a074 asm("r2");
        register u8 *address_a074 asm("r0");
        offset_a070 = 0xA070;
        asm volatile("" : "+r"(offset_a070));
        address_a070 = base + offset_a070;
        offset_a074 = 0xA074;
        asm volatile("" : "+r"(offset_a074));
        address_a074 = base + offset_a074;
        *(u32 *)address_a074 = zero;
        *(u32 *)address_a070 = zero;
    }
    {
        register u8 *state asm("r0");
        state = (u8 *)0x0203055C;
        state[6] = zero;
    }
    {
        register u8 *address asm("r0");
        offset_a070 += 10;
        address = base + offset_a070;
        *(u16 *)address = zero;
    }
    {
        register s32 offset asm("r1");
        register u8 *address asm("r0");
        offset = 0xA078;
        asm volatile("" : "+r"(offset));
        address = base + offset;
        *(u16 *)address = zero;
    }
    func_080BB940();
    counter = 0;
loop_108:
    if ((func_080E9D88(1U, counter) << 0x18) == 0) {
        goto block_110;
    }
    {
        register u8 *record asm("r2");
        register s32 field_offset asm("r3");
        register u32 first asm("r0");
        register u32 second asm("r1");
        register u32 third asm("r2");

        record = (u8 *)(counter * 0x270);
        record = (u8 *)((u32)record + (u32)base);
        field_offset = 0x1380;
        first = record[field_offset];
        field_offset += 1;
        second = record[field_offset];
        field_offset += 55;
        third = record[field_offset];
        asm volatile(
            "str %3, [sp]\n\t"
            "movs r3, #0\n\t"
            "str r3, [sp, #4]\n\t"
            "str r3, [sp, #8]\n\t"
            "movs r3, #1\n\t"
            "bl func_080BAF2C"
            : "+r"(first), "+r"(second), "+r"(third)
            : "r"(counter)
            : "r3", "lr", "cc", "memory");
    }
block_110:
    {
        register u32 next asm("r0");
        next = counter + 1;
        next <<= 24;
        counter = next >> 24;
    }
    if (counter <= 5U) {
        goto loop_108;
    }
    }
    {
        register struct ViewStateBBA04 *config asm("r1");
        config = (struct ViewStateBBA04 *)0x030033C4;
        config->center_x = 0x78;
        config->center_y = 0x78;
        config->size = 0x80;
        config->flags = 0x20000;
    }
    func_080BB224(1, 0U, 0U, 1);
    func_08093AE8(0x0202F094, 1);
    *(u8 *)0x03000074 = (u8) (*(u8 *)0x03000074 | 1);
    func_08098BB4(0x080036D3);
    func_08096308(1, 8);
    *(u32 *)0x02030558 = 0x10U;
    goto block_643;
block_113:
    {
        register s32 *returned asm("r0") = func_0809716C(0);
        register s32 flags asm("r0");
        register s32 *flag_view asm("r4");

        temp_r0 = returned;
        flags = *returned;
        flags |= 0x20;
        flag_view = temp_r0;
        *flag_view = flags;
    }
    var_r8 = 0;
    var_r6_2 = 0;
    {
        register u8 *base_seed asm("r4");
        base_seed = D_02034B4C;
        base_113 = base_seed;
    }
loop_114:
    predicate_113 = func_080E9D88(1U, var_r6_2) << 0x18;
    next_113 = var_r6_2 + 1;
    if (predicate_113 == 0) {
        goto block_122;
    }
    var_r5_2 = 0;
    if (var_r5_2 >= var_r8) {
        goto block_120;
    }
    {
        register u8 *record_row_117 asm("r0");
        register u8 *stack_base_117 asm("r2");
        register u32 record_work_117 asm("r3");
        register u8 *record_address_117 asm("r1");

        record_row_117 = base_113 + var_r6_2 * 0x270;
        stack_base_117 = stack.sp2C;
        record_work_117 = 0x1380;
        record_address_117 = record_row_117 + record_work_117;
loop_117:
        {
            register u8 *stack_address_117 asm("r0") = stack_base_117 + var_r5_2;
            register u32 stack_value_117 asm("r0");
            register u32 record_value_117 asm("r3");

            stack_value_117 = *stack_address_117;
            record_value_117 = *record_address_117;
            if (stack_value_117 != record_value_117) {
                goto block_119;
            }
        }
    }
    asm volatile(
        "add r1, sp, #52\n\t"
        "add r1, r1, %0\n\t"
        "ldrb r0, [r1]\n\t"
        "add r0, #1\n\t"
        "strb r0, [r1]"
        :
        : "r"(var_r5_2)
        : "r0", "r1", "cc", "memory");
    goto block_120;
block_119:
    {
        register u32 next_inner asm("r0");
        next_inner = var_r5_2 + 1;
        var_r5_2 = (u8)next_inner;
    }
    if ((u32) var_r5_2 < var_r8) {
        goto loop_117;
    }
block_120:
    if (var_r5_2 != var_r8) {
        goto block_122;
    }
    {
        register u8 *destination_120 asm("r1");
        register u8 *record_base_120 asm("r4");
        register u32 field_offset_120 asm("r2");
        register u8 *record_address_120 asm("r0");

        destination_120 = stack.sp2C;
        destination_120 += var_r5_2;
        record_address_120 = (u8 *)(var_r6_2 * 0x270 + (u32)record_base_120);
        field_offset_120 = 0x1380;
        asm volatile("" : "+r"(field_offset_120));
        record_address_120 += field_offset_120;
        *destination_120 = *record_address_120;
    }
    stack.sp34[var_r5_2] = 1;
    {
        register u32 next_count asm("r0");
        next_count = var_r5_2 + 1;
        var_r8 = (u8)next_count;
    }
block_122:
    {
        register u32 normalized_outer asm("r0");
        normalized_outer = next_113 << 24;
        var_r6_2 = normalized_outer >> 24;
    }
    if (var_r6_2 <= 5U) {
        goto loop_114;
    }
    var_r6_2 = 0;
    if (var_r6_2 >= var_r8) {
        goto block_128;
    }
    {
        register s32 message_125 asm("r5") = 0x08107058;
        register s32 *table_125 asm("r7") = (s32 *)0x087EDD54;
loop_125:
        {
            register u8 *count_125 asm("r4");

            func_080986B4(0);
            count_125 = stack.sp34;
            count_125 += var_r6_2;
            func_080984C4(*count_125, 1, 0, 0, 0);
            func_08098248(message_125, 0, 0);
            func_08098248(table_125[stack.sp2C[var_r6_2]], 2, 0);
            if ((u32)*count_125 <= 1U) {
                goto block_127;
            }
            func_08098248(0x0810705C, 2, 0);
        }
block_127:
        func_08098248(message_125, 0, 0);
        func_08098BB4(0x080036DC);
        {
            register u32 next_125 asm("r0") = var_r6_2 + 1;

            next_125 <<= 24;
            var_r6_2 = next_125 >> 24;
        }
        if ((u32)var_r6_2 < var_r8) {
            goto loop_125;
        }
    }
block_128:
    {
        register s32 *clear_ptr_128 asm("r3") = temp_r0;
        register s32 clear_value_128 asm("r0") = *clear_ptr_128;

        clear_value_128 &= ~0x20;
        *clear_ptr_128 = clear_value_128;
    }
    *(u32 *)0x02030558 = 0x20U;
    goto block_643;
block_130:
    {
    register u32 counter_130 asm("r6") = 0;
    register u8 *base_130 asm("r4") = D_02034B4C;
loop_131:
    if ((func_080E9D88(0U, counter_130) << 0x18) == 0) {
        goto block_133;
    }
    {
        register u32 carrier_130 asm("r2") = counter_130 * 0x270;
        register u32 first_130 asm("r0");
        register u32 second_130 asm("r1");

        carrier_130 += (u32)base_130;
        first_130 = *(u8 *)carrier_130;
        second_130 = *(u8 *)(carrier_130 + 1);
        carrier_130 += 0x38;
        carrier_130 = *(u8 *)carrier_130;
        func_080BAF2C(first_130, second_130, carrier_130, 0,
            counter_130, 0x10000U, 0);
    }
    {
        register u8 *status_130 asm("r0");
        register u32 one_130 asm("r1");

        status_130 = (u8 *)D_02032EEC;
        status_130 = (u8 *)(counter_130 + (u32)status_130);
        one_130 = 1;
        *status_130 = one_130;
    }
block_133:
    {
        register u32 next_130 asm("r0") = counter_130 + 1;

        next_130 <<= 24;
        counter_130 = next_130 >> 24;
    }
    if (counter_130 <= 5U) {
        goto loop_131;
    }
    }
    func_080BB224(3, 0U, 0U, 0);
    goto block_191;
block_136:
    if (M2C_FIELD((void *)0x0203055C, u8 *, 0) == 2) {
        goto block_139;
    }
    {
    register u32 copy_index_136 asm("r6") = 0;
    register u8 *copy_base_136 asm("r7") = D_02034B4C;
    register u32 copy_offset_136 asm("r4") = 0x27B4;
    register u8 *copy_dest_136 asm("r2");
    register u8 *copy_source_136 asm("r3");

    asm volatile("" : "+r"(copy_base_136), "+r"(copy_offset_136));
    copy_dest_136 = copy_base_136 + copy_offset_136;
    copy_source_136 = (u8 *)0x020281F6;
loop_138:
    {
        register u8 *dest_136 asm("r1") = (u8 *)(copy_index_136 + (u32)copy_dest_136);
        register u8 *source_136 asm("r0") = (u8 *)(copy_index_136 + (u32)copy_source_136);

        *dest_136 = *source_136;
    }
    {
        register u32 next_136 asm("r0") = copy_index_136 + 1;

        next_136 <<= 24;
        copy_index_136 = next_136 >> 24;
    }
    if (copy_index_136 <= 9U) {
        goto loop_138;
    }
    }
block_139:
    var_r0 = 0x40;
    goto block_543;
block_141:
    {
        register u32 *state_base_141 asm("r0") = (u32 *)0x0203055C;
        register u32 flags_141 asm("r1") = state_base_141[1];
        register u32 compare_141 asm("r0") = 0x1FF00;

        flags_141 &= compare_141;
        compare_141 = 0x700;
        if (flags_141 == compare_141) {
            goto block_143;
        }
    }
    goto block_189;
block_143:
    {
    register u32 counter_143 asm("r6") = 0;
    register u8 *base_143 asm("r4") = D_02034B4C;
loop_144:
    if ((func_080E9D88(0U, counter_143) << 0x18) == 0) {
        goto block_147;
    }
    temp_r0_2 = base_143[(counter_143 * 0x270) + 0x70];
    if (temp_r0_2 == 0x1E) {
        goto block_148;
    }
    if (temp_r0_2 == 0x5F) {
        goto block_148;
    }
block_147:
    {
        register u32 next_143 asm("r0") = counter_143 + 1;

        next_143 <<= 24;
        counter_143 = next_143 >> 24;
    }
    if (counter_143 <= 5U) {
        goto loop_144;
    }
block_148:
    if (counter_143 <= 5U) {
        goto block_150;
    }
    goto block_189;
block_150:
    temp_r8 = func_08094484(0x08359850, 0x0835985C, 0, 8, 0x68, 0x3C2, 0xD, 8, 0);
    func_08098BB4(0x08017BD3);
    func_0809A9C8(0x23, 3, 0, 0x3C2, 0xD, 0x02002880);
    func_08098BB4(0x08018B16);
    func_0809A9C8(0x22, 0, 0, 0x3C2, 0xD, 0x02002880);
    func_08098BB4(0x08018B89);
    func_0809A9C8(0x22, 3, 0, 0x3C2, 0xD, 0x02002880);
    func_08098BB4(0x08018BBC);
    func_0809A9C8(0x1E, 0, 0, 0x3C2, 0xD, 0x02002880);
    func_08098BB4(0x08018C4E);
    func_0809A9C8(0x22, 0, 0, 0x3C2, 0xD, 0x02002880);
    func_08098BB4(0x08018C79);
    func_0809A9C8(0x1E, 0, 0, 0x3C2, 0xD, 0x02002880);
    func_08098BB4(0x08018CF6);
    func_0809A9C8(0x1E, 0, 0, 0x3C2, 0xD, 0x02002880);
    func_08098BB4(0x08018D61);
    func_0809A9C8(0x22, 0, 0, 0x3C2, 0xD, 0x02002880);
    func_08098BB4(0x08018DAF);
    asm volatile(
        "str r5, [sp]\n\t"
        "str r4, [sp, #4]\n\t"
        "movs r0, #0x22\n\t"
        "movs r1, #3\n\t"
        "movs r2, #0\n\t"
        "add r3, r6, #0\n\t"
        "bl func_0809A9C8"
        :
        :
        : "r0", "r1", "r2", "r3", "lr", "cc", "memory");
    func_08098BB4(0x08018DE2);
    func_0809A9C8(0x1E, 0, 0, 0x3C2, 0xD, 0x02002880);
    func_08098BB4(0x08018E74);
    func_0809A9C8(0x1E, 3, 0, 0x3C2, 0xD, 0x02002880);
    func_08098BB4(0x08018EA1);
    func_08094554(temp_r8);
    func_08098BB4(0x08017BE6);
    {
        register u8 *state_150 asm("r2") = (u8 *)0x0203055C;
        register u32 old_flags_150 asm("r1") = state_150[6];
        register u32 new_flags_150 asm("r0") = 1;

        new_flags_150 |= old_flags_150;
        state_150[6] = new_flags_150;
    }
    }
    goto block_189;
block_152:
asm volatile(".Lsub_080BBA04_block152:");
{
    register s32 gate_152 asm("r0") = *(s32 *)0x0202F090;
    register u8 *state_base_152 asm("r6") = (u8 *)0x0203055C;
    if (gate_152 != 0) {
        goto block_169;
    }
    if (*state_base_152 != 0) {
        goto block_169;
    }
    if (*(u8 *)0x02030664 != 0) {
        goto block_156;
    }
    func_08098BB4(0x080036F6);
    goto block_157;
block_156:
    func_08098BB4(0x08003789);
block_157:
    temp_r0_3 = *(u8 *)0x0200A880;
    if (temp_r0_3 == 1) {
        goto block_165;
    }
    if ((s32) temp_r0_3 > 1) {
        goto block_162;
    }
    if (temp_r0_3 == 0) {
        goto block_568;
    }
    goto block_643;
block_162:
    if (temp_r0_3 == 2) {
        goto block_177;
    }
    if (temp_r0_3 == 3) {
        goto block_166;
    }
    goto block_643;
block_165:
    *(u32 *)0x02030558 = 0x100U;
    goto block_643;
block_166:
    {
        register u32 random_166 asm("r0") =
            ((u32 (*)())func_080BB660)();
        register u8 *limit_base_166 asm("r1") = D_02034B4C;
        register s32 limit_offset_166 asm("r2") = 0x270D;
        register u8 *limit_166 asm("r1");

        asm volatile("" : "+r"(limit_offset_166));
        limit_166 = limit_base_166 + limit_offset_166;
        asm volatile(
            ".syntax unified\n\t"
            "lsls %0, %0, #24\n\t"
            "lsrs %0, %0, #24\n\t"
            ".syntax divided"
            : "+r"(random_166) : "r"(limit_166) : "cc");
        if (random_166 <= *limit_166) {
            goto block_168;
        }
    }
    goto block_277;
block_168:
    func_08092E84(0x58);
    func_080986B4(0);
    func_08098BB4(0x08003DA8);
    asm volatile("");
    goto block_568;
block_169:
    if (*state_base_152 != 2) {
        goto block_175;
    }
    func_08098BB4(0x0800387A);
    temp_r0_4 = *(u8 *)0x0200A880;
    if (temp_r0_4 == 0) {
        goto block_568;
    }
    if (temp_r0_4 != 1) {
        goto block_643;
    }
    {
        register u32 random_174 asm("r0") =
            ((u32 (*)())func_080BB660)();
        register u8 *limit_base_174 asm("r1") = D_02034B4C;
        register s32 limit_offset_174 asm("r3") = 0x270D;
        register u8 *limit_174 asm("r1");

        asm volatile("" : "+r"(limit_offset_174));
        limit_174 = limit_base_174 + limit_offset_174;
        asm volatile(
            ".syntax unified\n\t"
            "lsls %0, %0, #24\n\t"
            "lsrs %0, %0, #24\n\t"
            ".syntax divided"
            : "+r"(random_174) : "r"(limit_174) : "cc");
        if (random_174 <= *limit_174) {
            goto block_174;
        }
    }
    goto block_277;
block_174:
    func_08092E84(0x58);
    func_080986B4(0);
    func_08098BB4(0x08003DA8);
    goto block_568;
block_175:
    func_08098BB4(0x0800380D);
    temp_r0_5 = *(u8 *)0x0200A880;
    if (temp_r0_5 == 0) {
        goto block_568;
    }
    if (temp_r0_5 != 1) {
        goto block_643;
    }
block_177:
    *(u32 *)0x02030558 = 0x200U;
    goto block_643;
}
block_179:
    func_08096308(2, 8);
    goto loop_181;
block_180:
    func_080ED17C(1);
loop_181:
    if ((func_0809669C() << 0x18) == 0) {
        goto block_180;
    }
    func_08092E0C(7);
    func_08093B54();
    *(u8 *)0x03000074 = 0U;
    func_0809534C();
    *(s8 *)0x03000075 = 1;
    *(s8 *)0x0300603D = 1;
    func_080B35D4(1);
    func_080BE600();
    func_080E9128();
    func_080BB940();
    {
    register u32 outer asm("r6");
    register u8 *base_seed asm("r4");
    register u8 *base asm("r8");

    outer = 0;
    base_seed = D_02034B4C;
    asm volatile("" : "+r"(base_seed));
    base = base_seed;
loop_183:
    {
    register u32 inner asm("r5");
    register u32 next_outer asm("r7");
    register u32 outer_offset asm("r4");
    {
        register u32 work asm("r0");
        inner = 0;
        next_outer = outer + 1;
        work = outer << 2;
        work += outer;
        work <<= 3;
        work -= outer;
        outer_offset = work << 7;
    }
loop_184:
    if ((func_080E9D88(outer, inner) << 0x18) == 0) {
        goto block_186;
    }
    {
        register u8 *record asm("r2");
        register u32 first asm("r0");
        register u32 second asm("r1");
        register u32 third asm("r2");
        record = (u8 *)(inner * 0x270);
        record = (u8 *)((u32)record + outer_offset);
        record += (u32)base;
        first = record[0];
        second = record[1];
        record += 0x38;
        third = record[0];
        func_080BAF2C(first, second, third, outer, inner, 0, 0);
    }
block_186:
    {
        register u32 next asm("r0");
        next = inner + 1;
        next <<= 24;
        inner = next >> 24;
    }
    if (inner <= 5U) {
        goto loop_184;
    }
    {
        register u32 next asm("r0");
        next = next_outer << 24;
        outer = next >> 24;
    }
    }
    if (outer <= 1U) {
        goto loop_183;
    }
    }
    func_080BB224(3, 0U, 0U, 1);
    func_08093AE8(0x0202F094, 1);
    *(u8 *)0x03000074 = (u8) (*(u8 *)0x03000074 | 1);
    func_08098BB4(0x080036D3);
    func_08096308(1, 8);
block_189:
    *(u32 *)0x02030558 = 0x50U;
    goto block_643;
block_190:
    func_080ECD34(0x08106F60, 0x06017B20);
    {
        register s32 first_result_190 asm("r7");
        register u32 asset0_190 asm("r0");
        register u32 asset1_190 asm("r1");
        register u32 first_stack_190 asm("r2");
        register u32 saved_stack_190 asm("r8");
        register u32 second_stack_190 asm("r3");

        asset0_190 = 0x08105DA4;
        asset1_190 = 0x08105DB0;
        first_stack_190 = 0x98;
        saved_stack_190 = first_stack_190;
        first_result_190 = func_08094484(asset0_190, asset1_190, 0, 0x88,
            first_stack_190, 0x3DC, 0xF, 8, 0);
        asset0_190 = 0x08105A20;
        asset1_190 = 0x08105A2C;
        second_stack_190 = saved_stack_190;
        asm volatile("" : "+r"(second_stack_190));
        temp_r4_2 = func_08094484(asset0_190, asset1_190, 0, 0xD8,
            second_stack_190, 0x3D9, 0xF, 8, 0);
        func_080C0AFC();
        func_08094554(first_result_190);
        func_08094554(temp_r4_2);
    }
block_191:
    *(u32 *)0x02030558 = 0x30U;
    goto block_643;
block_192:
    {
        register u32 outer_192 asm("r6") = 0;
        register u8 ***slot_base_192 asm("r2") = D_02032EBC;
loop_193:
        {
            register u32 inner_192 asm("r5") = 0;
            register u32 next_outer_192 asm("r7") = outer_192 + 1;
            register u32 row_offset_192 asm("r4");
            register u32 row_work_192 asm("r0") = outer_192 << 1;

            row_work_192 += outer_192;
            row_offset_192 = row_work_192 << 3;
loop_194:
            {
                register u32 active_192 asm("r0");
                register u32 call_outer_192 asm("r0") = outer_192;
                register u32 call_inner_192 asm("r1") = inner_192;

                stack.sp3C = (s32)slot_base_192;
                active_192 = func_080E9D88(call_outer_192, call_inner_192);
                active_192 <<= 24;
                slot_base_192 = (u8 ***)stack.sp3C;
                if (active_192 != 0) {
                    register u32 slot_offset_192 asm("r0") = inner_192 << 2;
                    register u8 *record_192 asm("r1");

                    slot_offset_192 += row_offset_192;
                    slot_offset_192 += (u32)slot_base_192;
                    record_192 = *(u8 **)slot_offset_192;
                    *(s32 *)(record_192 + 0x2C) = 0;
                }
            }
block_196:
            {
                register u32 next_inner_192 asm("r0") = inner_192 + 1;
                inner_192 = (u8)next_inner_192;
                if (inner_192 <= 5U)
                    goto loop_194;
            }
            {
                register u32 outer_successor_192 asm("r0") = next_outer_192 << 24;
                outer_192 = outer_successor_192 >> 24;
                if (outer_192 <= 1U)
                    goto loop_193;
            }
        }
    }
    func_080BAB3C();
    func_080C577C(0);
    *(u32 *)0x02030558 = 0x1010U;
    goto block_643;
block_200:
    func_080C030C(0);
    {
    register u32 outer asm("r6");
    register u8 *base_seed asm("r4");
    register u8 *base asm("r8");

    outer = 0;
    base_seed = D_02034B4C;
    base = base_seed;
loop_201:
    {
    register u32 inner asm("r5");
    register u32 next_outer asm("r7");
    register u32 outer_offset asm("r9");
    register u32 work asm("r0");

    inner = 0;
    next_outer = outer + 1;
    work = outer << 2;
    work += outer;
    work <<= 3;
    work -= outer;
    work <<= 7;
    outer_offset = work;
loop_202:
    if ((func_080E9D88(outer, inner) << 0x18) == 0) {
        goto block_205;
    }
    {
    register u8 *record asm("r2");
    register u32 offset asm("r0");
    register u8 *base_view asm("r1");
    register u32 sum asm("r0");
    register u32 current_value asm("r3");
    register u32 raw_limit asm("r3");
    register u32 signed_limit asm("r1");
    register u32 limit_offset asm("r4");

    offset = inner * 0x270;
    offset += outer_offset;
    base_view = base;
    record = (u8 *)(offset + (u32)base_view);
    sum = (u32)record;
    sum += 0x40;
    sum = *(u16 *)sum;
    current_value = *(u16 *)(record + 8);
    sum += current_value;
    *(u16 *)(record + 8) = (u16)sum;
    sum = (s32)(s16)sum;
    raw_limit = *(u16 *)(record + 0x3E);
    limit_offset = 0x3E;
    signed_limit = (s32)*(s16 *)(record + limit_offset);
    if ((s32)sum <= (s32)signed_limit) {
        goto block_205;
    }
    *(u16 *)(record + 8) = (u16)raw_limit;
    }
block_205:
    {
        register u32 next asm("r0");
        next = inner + 1;
        next <<= 24;
        inner = next >> 24;
    }
    if (inner <= 5U) {
        goto loop_202;
    }
    {
        register u32 next asm("r0");
        next = next_outer << 24;
        outer = next >> 24;
    }
    }
    if (outer <= 1U) {
        goto loop_201;
    }
    }
    end_base_200 = (s32)D_02034B4C;
    M2C_FIELD(end_base_200, u8 *, 0x27BF) = 0;
    M2C_FIELD(end_base_200, u8 *, 0x27BE) = 0;
    *(u32 *)0x02030558 = 0x1020U;
    goto block_643;
block_208:
    func_080BB224(3, 1U, 0U, 0);
    if (*(u8 *)0x02030664 != 0) {
        goto block_211;
    }
    if (M2C_FIELD((void *)0x0203055C, u8 *, 0) == 1) {
        goto block_211;
    }
    func_08098BB4(0x080038D7);
    goto block_212;
block_211:
    func_08098BB4(0x0800391E);
block_212:
    func_08098BB4(0x08003956);
    *(u32 *)0x02030558 = 0x1030U;
    goto block_643;
block_214:
    func_08098BB4(0x08003980);
    {
        register u8 *destination_base asm("r1");
        register u32 selection_address asm("r0");
        register u32 selected asm("r2");
        register u32 destination_offset asm("r4");

        destination_base = D_02034B4C;
        selection_address = 0x0200A880;
        asm volatile("" : "+r"(selection_address));
        selected = *(u8 *)selection_address;
        destination_offset = 0xA07C;
        asm volatile("" : "+r"(destination_offset));
        destination_base += destination_offset;
        *destination_base = selected;
        asm volatile("" : "+r"(selected));
        if (*(u8 *)0x0200A882 == 0) {
            goto block_222;
        }
        selection_address = selected << 24;
        selection_address >>= 24;
        if (selection_address != 1) {
            goto block_219;
        }
    }
    if ((func_080E6664(0x15) << 0x18) != 0) {
        goto block_402;
    }
    {
        register u32 *state asm("r1");
        register u32 value asm("r0");

        state = (u32 *)0x02030558;
        value = 0x1100;
        *state = value;
    }
    goto block_220;
block_219:
    {
        register u32 *state asm("r1");
        register u32 value asm("r0");

        state = (u32 *)0x02030558;
        value = 0x1200;
        *state = value;
    }
block_220:
    func_08098BB4(0x08003984);
    goto block_643;
block_222:
    temp_r1_3 = *(u16 *)0x0200A884;
    if (!(0x200 & temp_r1_3)) {
        goto block_227;
    }
    var_r5_6 = 1;
    var_r4 = 0;
    goto loop_225;
block_224:
    var_r4 = (u32) (u8) (var_r4 + 1);
loop_225:
    if ((func_080E9D88(var_r5_6, var_r4) << 0x18) == 0) {
        goto block_224;
    }
    goto block_236;
block_227:
    {
        register u32 mask_227 asm("r0") = 0x100;

        mask_227 &= temp_r1_3;
        if (mask_227 == 0) {
            goto block_234;
        }
    }
    var_r5_6 = 0;
    var_r4 = 2;
    goto loop_232;
block_229:
    if (var_r4 == 0) {
        goto block_231;
    }
    var_r4 = (u32) (u8) (var_r4 - 1);
    goto loop_232;
block_231:
    var_r4 = 5;
loop_232:
    if ((func_080E9D88(var_r5_6, var_r4) << 0x18) == 0) {
        goto block_229;
    }
    goto block_236;
block_234:
    func_08098BB4(0x08003956);
    goto block_643;
block_236:
    func_08092E84(0x40);
    {
        register u32 side_236 asm("r0") = var_r5_6;
        register u32 index_236 asm("r1") = var_r4;

        func_080C8538(side_236, index_236);
    }
    var_r0_3 = 3;
    var_r1 = 1;
    var_r2_2 = 0;
    goto block_421;
block_237:
{
    func_080ECD34(0x08106F60, 0x06017B20);
    {
        register u32 asset0_237 asm("r0");
        register u32 asset1_237 asm("r1");
        register u32 first_stack_237 asm("r2");
        register u32 saved_stack_237 asm("r8");
        register u32 second_stack_237 asm("r3");

        asset0_237 = 0x08105DA4;
        asset1_237 = 0x08105DB0;
        first_stack_237 = 0x98;
        saved_stack_237 = first_stack_237;
        temp_r7_2 = func_08094484(asset0_237, asset1_237, 0, 0x88,
            first_stack_237, 0x3DC, 0xF, 8, 0);
        asset0_237 = 0x08105A20;
        asset1_237 = 0x08105A2C;
        second_stack_237 = saved_stack_237;
        asm volatile("" : "+r"(second_stack_237));
        temp_r4_3 = func_08094484(asset0_237, asset1_237, 0, 0xD8,
            second_stack_237, 0x3D9, 0xF, 8, 0);
    }
    if ((func_080C1414() << 0x18) == 0) {
        goto block_241;
    }
    func_08094554(temp_r7_2);
    func_08094554(temp_r4_3);
    if ((func_080C25DC(0) << 0x18) == 0) {
        goto block_643;
    }
    {
        register u32 value asm("r0");
        register u8 *base asm("r1");
        register u32 offset asm("r4");
        value = func_080ECD5C(*(u32 *)0x03000010);
        base = D_02034B4C;
        value >>= 7;
        offset = 0xA07E;
        base += offset;
        *base = (u8)value;
    }
    var_r0 = 0x1200;
    goto block_543;
block_241:
    func_08094554(temp_r7_2);
    func_08094554(temp_r4_3);
    var_r0_4 = 0x1020;
    goto block_549;
}
block_242:
    {
    register u8 *state asm("r0");
    register u8 *saved_state asm("r6");
    register u32 first asm("r1");
    state = (u8 *)0x0203055C;
    first = state[0];
    saved_state = state;
    if (first == 1) {
        goto block_247;
    }
    if (saved_state[5] == 2) {
        goto block_245;
    }
    {
        register u8 *base asm("r0");
        register u32 offset asm("r3");
        register u32 zero asm("r1");
        base = D_02034B4C;
        offset = 0xA080;
        asm volatile("" : "+r"(offset));
        base += offset;
        zero = 0;
        *base = zero;
    }
    goto block_264;
block_245:
    {
        register u8 *base asm("r1");
        register u32 offset asm("r4");
        register u8 *first_slot asm("r2");
        register u32 one asm("r0");
        base = D_02034B4C;
        offset = 0xA080;
        asm volatile("" : "+r"(offset));
        first_slot = base + offset;
        one = 1;
        *first_slot = one;
        one = 0xA081;
        base += one;
        one = 0x22;
        *base = one;
    }
    func_080C25DC(1);
    goto block_264;
block_247:
    {
    register u8 *transfer asm("r4");
    register u8 *asset asm("r5");
    register u32 left_ready asm("r5");
    register u32 right_ready asm("r4");
    transfer = (u8 *)0x0203EBC8;
    asset = (u8 *)0x08107060;
    func_0809AEC0(transfer, 4, asset);
    transfer += 4;
    func_0809B00C(transfer, 4, asset);
loop_248:
    left_ready = func_0809AEF4();
    left_ready = (u8)left_ready;
    right_ready = func_0809B040();
    right_ready = (u8)right_ready;
    func_080ED17C(1);
    if (left_ready == 0) {
        goto loop_248;
    }
    if (right_ready == 0) {
        goto loop_248;
    }
    {
    register u8 *base asm("r4");
    register u8 *left_flag asm("r6");
    register u8 *right_flag asm("r5");
    register u32 left_flag_offset asm("r1");
    register u32 left_data_offset asm("r2");
    register u32 right_flag_offset asm("r3");
    register u32 right_data_offset asm("r1");
    register u32 address asm("r0");
    base = D_02034B4C;
    left_flag_offset = 0xA07C;
    asm volatile("" : "+r"(left_flag_offset));
    left_flag = base + left_flag_offset;
    if (*left_flag != 1) {
        goto block_252;
    }
    left_data_offset = 0xA084;
    asm volatile("" : "+r"(left_data_offset));
    address = (u32)base + left_data_offset;
    func_0809AEC0(address, 0x94, 0x0810706C);
block_252:
    right_flag_offset = 0xA080;
    asm volatile("" : "+r"(right_flag_offset));
    right_flag = base + right_flag_offset;
    if (*right_flag != 1) {
        goto block_254;
    }
    right_data_offset = 0xA118;
    address = (u32)base + right_data_offset;
    func_0809B00C(address, 0x94, 0x0810706C);
block_254:
    {
    register u8 *left_active asm("r7");
    register u8 *right_active asm("r6");
    left_active = left_flag;
    right_active = right_flag;
loop_255:
    {
    register u32 active asm("r0");
    asm volatile("ldrb %0, [%1]"
                 : "=r"(active) : "r"(left_active) : "memory");
    if (active != 1) {
        goto block_258;
    }
    }
    left_ready = func_0809AEF4();
    left_ready = (u8)left_ready;
    goto block_259;
block_258:
    left_ready = 1;
block_259:
    if (*right_active != 1) {
        goto block_261;
    }
    right_ready = func_0809B040();
    right_ready = (u8)right_ready;
    goto block_262;
block_261:
    right_ready = 1;
block_262:
    func_080ED17C(1);
    if (left_ready == 0) {
        goto loop_255;
    }
    if (right_ready == 0) {
        goto loop_255;
    }
    }
    }
    }
block_264:
    }
    {
        register u8 *first_slot asm("r1");
        register u32 zero asm("r0");
        first_slot = (u8 *)0x02032E88;
        zero = 0;
        *first_slot = zero;
    }
    {
        register u8 *second_slot asm("r1");
        register u8 *base asm("r0");
        register u32 offset asm("r2");
        register u32 value asm("r0");
        second_slot = &D_02032E89;
        base = D_02034B4C;
        offset = 0x2712;
        asm volatile("" : "+r"(offset));
        base += offset;
        value = *base;
        *second_slot = value;
    }
    *(u32 *)0x02030558 = 0x1210U;
    goto block_643;
block_266:
    {
        register u8 *base asm("r1");
        register u8 *side_ptr asm("r4");
        register u8 *saved_base asm("r7");
        register u32 address asm("r0");
        register u32 offset asm("r3");
        base = D_02034B4C;
        side_ptr = (u8 *)0x02032E89;
        address = *side_ptr;
        address <<= 2;
        address += (u32)base;
        offset = 0xA07C;
        asm volatile("" : "+r"(offset));
        address += offset;
        temp_r0_7 = *(u8 *)address;
        saved_base = base;
    if (temp_r0_7 == 1) {
        goto block_274;
    }
    if ((s32) temp_r0_7 > 1) {
        goto block_271;
    }
    if (temp_r0_7 == 0) {
        goto block_273;
    }
    goto block_643;
block_271:
    if (temp_r0_7 == 2) {
        goto block_276;
    }
    goto block_643;
block_273:
    {
        register u32 next_state asm("r0");
        next_state = 0x1400;
        var_r0_5 = next_state;
    }
    goto block_638;
block_274:
    func_080986B4(0);
    func_080981F0(0x08107078, 0, 0, 0, 0);
    {
        register s32 *table asm("r1");
        register u32 index asm("r0");
        register u32 lookup_offset asm("r2");
        table = (s32 *)0x087EF130;
        asm volatile("" : "+r"(table));
        index = *side_ptr;
        index <<= 2;
        index += (u32)saved_base;
        lookup_offset = 0xA07D;
        index += lookup_offset;
        index = *(u8 *)index;
        index <<= 2;
        index += (u32)table;
        index = *(u32 *)index;
        func_08098248(index, 0, 0);
    }
    func_08098248(0x08107090, 0, 0);
    func_080972C8();
    *(u32 *)0x02030558 = 0x13F0U;
    func_080C5D14();
    func_080C35C4(*side_ptr);
    goto block_643;
block_276:
    {
        register u32 random_276 asm("r0") =
            ((u32 (*)())func_080BB660)();
        register s32 limit_offset_276 asm("r3") = 0x270D;
        register u8 *limit_276 asm("r1");

        limit_276 = saved_base + limit_offset_276;
        asm volatile(
            ".syntax unified\n\t"
            "lsls %0, %0, #24\n\t"
            "lsrs %0, %0, #24\n\t"
            ".syntax divided"
            : "+r"(random_276) : "r"(limit_276) : "cc");
        if (random_276 <= *limit_276) {
            goto block_279;
        }
    }
    }
block_277:
    *(u32 *)0x02030558 = 0x9000U;
    goto block_643;
block_279:
    func_08092E84(0x58);
    func_080986B4(0);
    func_08098BB4(0x08003DA8);
    goto block_332;
block_280:
    {
    register u8 *base_280 asm("r4") = D_02034B4C;
    register u32 row_280 asm("r7");
    register u8 **active_slot_280 asm("r5");
    register u8 *col_280 asm("r3");
    register u32 selected_280 asm("r0");
    register u32 row_work_280 asm("r1");
    register u32 active_offset_280 asm("r2");
    register u32 col_offset_280 asm("r0");
    register u32 col_value_280 asm("r2");
    register u32 col_work_280 asm("r0");

    selected_280 = *(u8 *)0x02032E89;
    row_work_280 = 0x27A4;
    asm volatile("" : "+r"(row_work_280));
    row_280 = (u32)base_280 + row_work_280;
    asm volatile("strb %1, [%0]"
                 : : "r"(row_280), "r"(selected_280) : "memory");

    active_offset_280 = 0x27A8;
    asm volatile("" : "+r"(active_offset_280));
    active_slot_280 = (u8 **)(base_280 + active_offset_280);

    asm volatile("ldrb %0, [%1]"
                 : "=r"(selected_280) : "r"(row_280) : "memory");
    row_work_280 = selected_280;
    row_work_280 <<= 2;
    row_work_280 += selected_280;
    row_work_280 <<= 3;
    row_work_280 -= selected_280;
    row_work_280 <<= 7;

    col_offset_280 = 0x27A5;
    col_280 = base_280 + col_offset_280;
    col_value_280 = *col_280;
    col_work_280 = col_value_280;
    col_work_280 <<= 2;
    col_work_280 += col_value_280;
    col_work_280 <<= 3;
    col_work_280 -= col_value_280;
    col_work_280 <<= 4;
    col_work_280 += (u32)base_280;
    row_work_280 += col_work_280;
    *active_slot_280 = (u8 *)row_work_280;

    {
        register u32 row_arg_280 asm("r0");

        asm volatile("ldrb %0, [%1]"
                     : "=r"(row_arg_280) : "r"(row_280) : "memory");
        func_080E8554(row_arg_280, *col_280);
    }
    {
        register u32 lookup_280 asm("r0");
        register u32 lookup_offset_280 asm("r1");

        asm volatile("ldrb %0, [%1]"
                     : "=r"(lookup_280) : "r"(row_280) : "memory");
        lookup_280 <<= 2;
        lookup_280 += (u32)base_280;
        lookup_offset_280 = 0xA07D;
        lookup_280 += lookup_offset_280;
        lookup_280 = *(u8 *)lookup_280;
        if (lookup_280 != 0x19) {
            goto block_285;
        }
    }
    {
    register u32 counter_280 asm("r6") = 0;
    register u32 loop_row_280 asm("r4") = row_280;
loop_282:
    if ((func_080ECD5C(*(u32 *)0x03000010) >> 0xE) == 0) {
        goto block_284;
    }
    func_080E83A4(*(u8 *)loop_row_280, 6, 4, 0, 0,
                  (s32)*(u8 *)loop_row_280, counter_280);
block_284:
    {
        register u32 next_counter_280 asm("r0") = counter_280 + 1;

        counter_280 = (u8)next_counter_280;
    }
    if (counter_280 <= 5U) {
        goto loop_282;
    }
    }
    }
block_285:
    if (M2C_FIELD((void *)0x0203055C, u8 *, 0) != 1) {
        goto block_287;
    }
    if (*(u8 *)0x02032E89 != 0) {
        goto block_288;
    }
block_287:
    func_080CA1A0();
    func_080E9998();
block_288:
    if (M2C_FIELD((void *)0x0203055C, u8 *, 0) != 1) {
        goto block_305;
    }
    func_080BFB90();
    if (*(u8 *)0x02032E89 != 0) {
        goto block_298;
    }
    {
    register u32 ready asm("r5");
    func_0809AEC0(0x0203EBC8, 4, 0x08107094);
    asm volatile(
        "1:\n\t"
        "bl func_0809AEF4\n\t"
        "lsl r0, r0, #24\n\t"
        "lsr %0, r0, #24\n\t"
        "mov r0, #1\n\t"
        "bl func_080ED17C\n\t"
        "cmp %0, #0\n\t"
        "beq 1b"
        : "=r"(ready)
        :
        : "r0", "r1", "r2", "r3", "lr", "cc", "memory");
    func_0809AEC0(0x0203ECF8, 0x2E, 0x0810709C);
    asm volatile(
        "1:\n\t"
        "bl func_0809AEF4\n\t"
        "lsl r0, r0, #24\n\t"
        "lsr %0, r0, #24\n\t"
        "mov r0, #1\n\t"
        "bl func_080ED17C\n\t"
        "cmp %0, #0\n\t"
        "beq 1b"
        : "=r"(ready)
        :
        : "r0", "r1", "r2", "r3", "lr", "cc", "memory");
    func_0809AEC0(0x0203ED28, 0xC0, 0x081070A8);
    asm volatile(
        "1:\n\t"
        "bl func_0809AEF4\n\t"
        "lsl r0, r0, #24\n\t"
        "lsr %0, r0, #24\n\t"
        "mov r0, #1\n\t"
        "bl func_080ED17C\n\t"
        "cmp %0, #0\n\t"
        "beq 1b"
        : "=r"(ready)
        :
        : "r0", "r1", "r2", "r3", "lr", "cc", "memory");
    }
    goto block_305;
block_298:
    {
    register u32 ready asm("r4");
    func_0809B00C(0x0203EBCC, 4, 0x08107094);
loop_299:
    ready = func_0809B040();
    ready = (u8)ready;
    func_080ED17C(1);
    if (ready == 0) {
        goto loop_299;
    }
    func_0809B00C(0x0203ECF8, 0x2E, 0x0810709C);
loop_301:
    ready = func_0809B040();
    ready = (u8)ready;
    func_080ED17C(1);
    if (ready == 0) {
        goto loop_301;
    }
    func_080E9D48();
    func_0809B00C(0x0203ED28, 0xC0, 0x081070A8);
loop_303:
    ready = func_0809B040();
    ready = (u8)ready;
    func_080ED17C(1);
    if (ready == 0) {
        goto loop_303;
    }
    func_080BFCD8();
    }
block_305:
    *(u32 *)0x02030558 = 0x1310U;
    *(u32 *)0x02021690 = 0xA;
    *(u8 *)0x02033F34 = 0U;
    goto block_633;
block_307:
    func_080BB940();
    {
    register u32 outer_307 asm("r6") = 0;
    register u32 zero_307_local asm("r8");
    register u8 ***slot_base_307_local asm("sl");

    zero_307_local = outer_307;
    {
        register u8 ***slot_seed_307 asm("r2") = D_02032EBC;

        slot_base_307_local = slot_seed_307;
    }
loop_308:
    {
    register u32 inner_307 asm("r5") = 0;
    register u32 next_outer_307 asm("r7") = outer_307 + 1;
    register u32 outer_offset_307 asm("r9");
    {
        register u32 outer_work_307 asm("r0") = outer_307 << 2;

        outer_work_307 += outer_307;
        outer_work_307 <<= 3;
        outer_work_307 -= outer_307;
        outer_work_307 <<= 7;
        outer_offset_307 = outer_work_307;
    }
loop_309:
    if ((func_080E9D88(outer_307, inner_307) << 0x18) == 0) {
        goto block_311;
    }
    {
        register u32 slot_offset_307_local asm("r4") = inner_307 << 2;
        register u32 record_307 asm("r2");
        register u32 base_307_local asm("r3");
        register u32 first_307 asm("r0");
        register u32 second_307 asm("r1");

        record_307 = slot_offset_307_local + inner_307;
        record_307 <<= 3;
        record_307 -= inner_307;
        record_307 <<= 4;
        record_307 += outer_offset_307;
        base_307_local = (u32)D_02034B4C;
        asm volatile("add %0, %0, %1"
                     : "+r"(record_307)
                     : "r"(base_307_local)
                     : "cc");
        first_307 = *(u8 *)record_307;
        second_307 = *(u8 *)(record_307 + 1);
        record_307 += 0x38;
        record_307 = *(u8 *)record_307;
        func_080BAF2C(first_307, second_307, record_307, outer_307,
            inner_307, zero_307_local, zero_307_local);
        {
            register u32 slot_outer_307 asm("r0") = outer_307 << 1;
            register u8 *slot_record_307 asm("r0");

            slot_outer_307 += outer_307;
            slot_outer_307 <<= 3;
            slot_offset_307_local += slot_outer_307;
            slot_offset_307_local += (u32)slot_base_307_local;
            slot_record_307 = *(u8 **)slot_offset_307_local;
            slot_offset_307_local = zero_307_local;
            *(u32 *)(slot_record_307 + 0x2C) = slot_offset_307_local;
        }
    }
block_311:
    {
        register u32 next_inner_307 asm("r0") = inner_307 + 1;

        next_inner_307 <<= 24;
        inner_307 = next_inner_307 >> 24;
    }
    if (inner_307 <= 5U) {
        goto loop_309;
    }
    {
        register u32 normalized_outer_307 asm("r0") =
            next_outer_307 << 24;

        outer_307 = normalized_outer_307 >> 24;
    }
    }
    if (outer_307 <= 1U) {
        goto loop_308;
    }
    }
    func_080BAB3C();
    func_08093AE8(0x0202F094, 1);
    *(u8 *)0x03000074 = (u8) (*(u8 *)0x03000074 | 1);
    func_08098BB4(0x080036D3);
    func_08096308(1, 8);
    func_080C5DB4(1);
    asm volatile("");
    goto block_332;
block_315:
    {
        u8 *base;
        u32 offset;
        u8 *row;
        u8 **active_slot;
        u32 row_offset;
        u32 col;
        u32 col_offset;

        base = D_02034B4C;
        {
            register u32 selected asm("r0");
            selected = *(u8 *)0x02032E89;
            offset = 0x27A4;
            row = base + offset;
            *row = selected;
        }
        active_slot = (u8 **)(base + 0x27A8);
        row_offset = *row * 0x1380;
        offset += 1;
        {
            register u8 *col_address_315 asm("r0") = base + offset;

            col = *col_address_315;
        }
        col_offset = col * 0x270;
        col_offset += (u32)base;
        row_offset += col_offset;
        *active_slot = (u8 *)row_offset;
    }
    {
        register s32 *state_store_315 asm("r3") = temp_r0;

        *state_store_315 = 0x1330;
    }
    {
        register s32 *saved_mode_315 asm("r6");

        *saved_mode_315 = 0xA;
    }
    *(u8 *)0x02033F34 = 1U;
    asm volatile("");
    goto block_633;
block_316:
    func_080BB940();
    {
    register u32 outer_316_local asm("r6") = 0;
    register u32 zero_316_local asm("r8");
    register u8 ***slot_base_316_local asm("sl");

    zero_316_local = outer_316_local;
    {
        register u8 ***slot_seed_316 asm("r4") = D_02032EBC;

        asm volatile("" : "+r"(slot_seed_316));
        slot_base_316_local = slot_seed_316;
    }
loop_317:
    {
    register u32 inner_316_local asm("r5") = 0;
    register u32 next_outer_316 asm("r7") = outer_316_local + 1;
    register u32 outer_offset_316_local asm("r9");
    {
        register u32 outer_work_316 asm("r0") = outer_316_local << 2;

        outer_work_316 += outer_316_local;
        outer_work_316 <<= 3;
        outer_work_316 -= outer_316_local;
        outer_work_316 <<= 7;
        outer_offset_316_local = outer_work_316;
    }
loop_318:
    if ((func_080E9D88(outer_316_local, inner_316_local) << 0x18) == 0) {
        goto block_320;
    }
    {
        register u32 slot_offset_316_local asm("r4") = inner_316_local << 2;
        register u32 record_316_local asm("r2");
        register u32 first_316_local asm("r0");
        register u32 second_316_local asm("r1");

        record_316_local = slot_offset_316_local + inner_316_local;
        record_316_local <<= 3;
        record_316_local -= inner_316_local;
        record_316_local <<= 4;
        record_316_local += outer_offset_316_local;
        first_316_local = (u32)D_02034B4C;
        asm volatile("add %0, %0, %1"
                     : "+r"(record_316_local)
                     : "r"(first_316_local)
                     : "cc");
        first_316_local = *(u8 *)record_316_local;
        second_316_local = *(u8 *)(record_316_local + 1);
        record_316_local += 0x38;
        record_316_local = *(u8 *)record_316_local;
        func_080BAF2C(first_316_local, second_316_local, record_316_local,
            outer_316_local, inner_316_local, zero_316_local, zero_316_local);
        {
            register u32 slot_outer_316 asm("r0") = outer_316_local << 1;
            register u8 *slot_record_316 asm("r0");

            slot_outer_316 += outer_316_local;
            slot_outer_316 <<= 3;
            slot_offset_316_local += slot_outer_316;
            slot_offset_316_local += (u32)slot_base_316_local;
            slot_record_316 = *(u8 **)slot_offset_316_local;
            slot_offset_316_local = zero_316_local;
            *(u32 *)(slot_record_316 + 0x2C) = slot_offset_316_local;
        }
    }
block_320:
    {
        register u32 next_inner_316 asm("r0") = inner_316_local + 1;

        next_inner_316 <<= 24;
        inner_316_local = next_inner_316 >> 24;
    }
    if (inner_316_local <= 5U) {
        goto loop_318;
    }
    {
        register u32 normalized_outer_316 asm("r0") =
            next_outer_316 << 24;

        outer_316_local = normalized_outer_316 >> 24;
    }
    }
    if (outer_316_local <= 1U) {
        goto loop_317;
    }
    }
    func_080BAB3C();
    func_08093AE8(0x0202F094, 1);
    *(u8 *)0x03000074 = (u8) (*(u8 *)0x03000074 | 1);
    func_08098BB4(0x080036D3);
    func_08096308(1, 8);
    {
        register u32 row_316_tail asm("r0");
        register u32 col_316_tail asm("r1") = (u32)D_02034B4C;
        register u32 row_offset_316_tail asm("r2") =
            (u32)D_off_27A4_BBA04;
        register u32 col_offset_316_tail asm("r3");

        row_316_tail = col_316_tail + row_offset_316_tail;
        row_316_tail = *(u8 *)row_316_tail;
        asm volatile("" : : "r"(row_316_tail));
        col_offset_316_tail = (u32)D_off_27A5_BBA04;
        col_316_tail += col_offset_316_tail;
        col_316_tail = *(u8 *)col_316_tail;
        func_080EA408(row_316_tail, col_316_tail);
    }
    func_080C5DB4(1);
    goto block_332;
block_323:
    {
        u32 carrier;
        register u8 *base asm("r3");
        register u8 *row asm("r1");

        carrier = 0x02032E89;
        func_080C2DD0(*(u8 *)carrier);
        base = D_02034B4C;
        {
            register u32 selected_323 asm("r0") = *(u8 *)carrier;
            register u32 row_offset_323 asm("r4") =
                (u32)D_off_27A4_BBA04;

            row = base + row_offset_323;
            *row = selected_323;
        }
        {
            register u32 active_offset_323 asm("r0") =
                (u32)D_off_27A8_BBA04;
            register u8 **active_slot_323 asm("r4") =
                (u8 **)(base + active_offset_323);
            register u32 row_value_323 asm("r0") = *row;
            register u32 row_work_323 asm("r1") =
                row_value_323 * 0x1380;
            register u32 col_carrier_323 asm("r2") =
                (u32)D_off_27A5_BBA04;
            register u32 col_work_323 asm("r0") =
                (u32)base + col_carrier_323;

            col_carrier_323 = *(u8 *)col_work_323;
            col_work_323 = col_carrier_323 * 0x270;
            col_work_323 += (u32)base;
            row_work_323 += col_work_323;
            *active_slot_323 = (u8 *)row_work_323;
        }
    }
    {
        register u32 state_value_323 asm("r0") = 0x1350;

        {
            register s32 *state_slot_323 asm("r3") = temp_r0;

            *state_slot_323 = state_value_323;
        }
    }
    *(u32 *)0x02021690 = 0xA;
    *(u8 *)0x02033F34 = 2U;
    goto block_643;
block_325:
    func_080BB940();
    func_08098BB4(0x080036D3);
    {
        register u8 *selection asm("r0") = D_02034B4C;
        register u32 selection_offset asm("r4") = 0x27A4;

        asm volatile("" : "+r"(selection_offset));
        selection += selection_offset;
        func_080C3050(*selection);
    }
    {
        register u32 outer_325 asm("r6") = 0;
        register u8 ***slot_base_325 asm("r2") = D_02032EBC;
loop_326:
        {
            register u32 inner_325 asm("r5") = 0;
            register u32 next_outer_325 asm("r7") = outer_325 + 1;
            register u32 row_offset_325 asm("r4");
            register u32 row_work_325 asm("r0") = outer_325 << 1;

            row_work_325 += outer_325;
            row_offset_325 = row_work_325 << 3;
loop_327:
            {
                register u32 active_325 asm("r0");
                register u32 call_outer_325 asm("r0") = outer_325;
                register u32 call_inner_325 asm("r1") = inner_325;

                stack.sp3C = (s32)slot_base_325;
                active_325 = func_080E9D88(call_outer_325, call_inner_325);
                active_325 <<= 24;
                slot_base_325 = (u8 ***)stack.sp3C;
                if (active_325 != 0) {
                    register u32 slot_offset_325 asm("r0") = inner_325 << 2;
                    register u8 *record_325 asm("r1");

                    slot_offset_325 += row_offset_325;
                    slot_offset_325 += (u32)slot_base_325;
                    record_325 = *(u8 **)slot_offset_325;
                    *(s32 *)(record_325 + 0x2C) = 0;
                }
            }
block_329:
            {
                register u32 next_inner_325 asm("r0") = inner_325 + 1;
                inner_325 = (u8)next_inner_325;
                if (inner_325 <= 5U)
                    goto loop_327;
            }
            {
                register u32 outer_successor_325 asm("r0") = next_outer_325 << 24;
                outer_325 = outer_successor_325 >> 24;
                if (outer_325 <= 1U)
                    goto loop_326;
            }
        }
    }
    func_080BAB3C();
block_332:
    *(u32 *)0x02030558 = 0x1400U;
    goto block_643;
block_333:
    {
        register u8 *destination_base asm("r1");
        register u32 selection_address asm("r0");
        register u32 destination_offset asm("r2");

        destination_base = D_02034B4C;
        selection_address = 0x02032E89;
        selection_address = *(u8 *)selection_address;
        destination_offset = 0x27A4;
        asm volatile("" : "+r"(destination_offset));
        destination_base += destination_offset;
        *destination_base = selection_address;
    }
    func_080C5DB4(2);
    var_r0_6 = 0x1400;
    goto block_494;
block_335:
    {
    register u8 *state_base_335 asm("r0");
    register u8 *saved_state_335 asm("r6");
    register u32 state_mode_335 asm("r1");

    temp_r4_8 = func_080C682C();
    if (temp_r4_8 == 0) {
        goto block_556;
    }
    state_base_335 = (u8 *)0x0203055C;
    state_mode_335 = state_base_335[5];
    saved_state_335 = state_base_335;
    if (state_mode_335 != 0xA) {
        goto block_338;
    }
    func_080BB7EC();
block_338:
    if (!(4 & temp_r4_8)) {
        goto block_341;
    }
    *(u32 *)0x02030558 = 0xA000U;
    goto block_643;
block_341:
    if (!(1 & temp_r4_8)) {
        goto block_345;
    }
    if (saved_state_335[0] != 1) {
        goto block_553;
    }
    {
        register u32 final_flags_335 asm("r4") = temp_r4_8;
        register u32 final_mask_335 asm("r0") = 2;

        final_flags_335 &= final_mask_335;
        if (final_flags_335 == 0) {
            goto block_553;
        }
    }
    goto block_554;
block_345:
    *(u32 *)0x02030558 = 0x7000U;
    goto block_643;
    }
block_347:
    {
        register u8 *slot_347 asm("r1") = (u8 *)0x02032E88;
        register u32 incremented_347 asm("r0") = *slot_347 + 1;

        *slot_347 = incremented_347;
        temp_r0_8 = incremented_347;
    }
    if (temp_r0_8 != 2) {
        goto block_350;
    }
    func_080C577C(1);
    var_r0_5 = 0x2000;
    goto block_638;
block_350:
    {
        register u8 *toggle_slot_350 asm("r2") = (u8 *)0x02032E89;
        register u32 toggle_value_350 asm("r0") = *toggle_slot_350;
        register u32 toggle_mask_350 asm("r1") = 1;

        toggle_value_350 ^= toggle_mask_350;
        *toggle_slot_350 = toggle_value_350;
    }
    var_r0 = 0x1210;
    goto block_543;
block_351:
    {
        register u8 *setup_base asm("r0");
        register s32 selection_offset asm("r3");
        register u8 *selection asm("r2");
        register u8 *base asm("r7");
        register u32 current asm("r1");
        register u8 *row_values asm("r3");
        register u8 *col_values asm("r4");

        setup_base = D_02034B4C;
        selection_offset = 0x2710;
        asm volatile("" : "+r"(selection_offset));
        selection = setup_base + selection_offset;
        current = *selection;
        base = setup_base;
        if (current > 0x23U) {
            goto block_359;
        }
        {
            register u32 index asm("r0");
            register s32 row_offset asm("r4");
            register u8 *row_setup asm("r1");

            index = current;
            asm volatile("" : "+r"(index));
            index <<= 1;
            row_offset = 0x2713;
            asm volatile("" : "+r"(row_offset));
            row_setup = base + row_offset;
            index += (u32) row_setup;
            if (*(u8 *)index != 0xFF) {
                row_values = row_setup;
                goto block_357;
            }
            {
                register s32 col_offset asm("r0");
                col_offset = 0x2714;
                col_values = base + col_offset;
            }
            row_values = row_setup;
        }
loop_354:
        current = *(volatile u8 *)selection;
        {
            register u32 index asm("r0");
            index = current;
            index <<= 1;
            index += (u32) col_values;
            if (*(u8 *)index != 0xFF) {
                goto block_357;
            }
        }
        {
            register u32 next asm("r0");
            next = current + 1;
            *selection = next;
            next = (u8) next;
            if (next > 0x23U) {
                goto block_359;
            }
        }
        {
            register u32 index asm("r0");
            index = *selection;
            index <<= 1;
            index += (u32) row_values;
            if (*(u8 *)index == 0xFF) {
                goto loop_354;
            }
        }
block_357:
        {
            register s32 offset asm("r1");
            register u8 *address asm("r0");
            offset = 0x2710;
            asm volatile("" : "+r"(offset));
            address = base + offset;
            if ((u32) *address > 0x23U) {
                goto block_359;
            }
        }
        var_r0_4 = 0x2010;
        goto block_549;
    }
block_359:
    var_r0_6 = 0x5000;
    goto block_494;
block_360:
    {
        register u8 *base_360 asm("r3") = D_02034B4C;
        register u32 selection_offset_360 asm("r4") = 0x2710;
        register u8 *selection_360 asm("r2") = base_360 + selection_offset_360;
        register volatile u8 *row_360 asm("r5");
        register volatile u8 *col_360 asm("r4");
        register u8 **active_slot_360 asm("r6");
        register u32 table_index_360 asm("r0");
        register u8 *table_360 asm("r1");
        register u32 offset_360 asm("r2");
        u32 row_offset_360;
        u32 col_offset_360;

        table_index_360 = *selection_360;
        table_index_360 <<= 1;
        selection_offset_360 += 3;
        asm volatile("" : "+r"(selection_offset_360));
        table_360 = base_360 + selection_offset_360;
        table_index_360 += (u32)table_360;
        table_index_360 = *(u8 *)table_index_360;
        row_360 = base_360 + 0x27A4;
        *row_360 = table_index_360;

        table_index_360 = *selection_360;
        table_index_360 <<= 1;
        offset_360 = 0x2714;
        table_360 = base_360 + offset_360;
        table_index_360 += (u32)table_360;
        table_index_360 = *(u8 *)table_index_360;
        col_360 = base_360 + 0x27A5;
        *col_360 = table_index_360;

        offset_360 += 0x94;
        active_slot_360 = (u8 **)(base_360 + offset_360);
        row_offset_360 = *row_360 * 0x1380;
        col_offset_360 = *col_360 * 0x270;
        col_offset_360 += (u32)base_360;
        row_offset_360 += col_offset_360;
        *active_slot_360 = (u8 *)row_offset_360;
        {
            register u32 work_r0_360_b asm("r0") =
                (u32)D_off_27AC_BBA04;
            register u32 work_r1_360_b asm("r1");
            register u32 work_r2_360_b asm("r2");
            register u8 **slot_360_b asm("r6");

            slot_360_b = (u8 **)(base_360 + work_r0_360_b);
            work_r0_360_b = *row_360;
            work_r1_360_b = work_r0_360_b << 2;
            work_r1_360_b += work_r0_360_b;
            work_r1_360_b <<= 3;
            work_r1_360_b -= work_r0_360_b;
            work_r1_360_b <<= 7;
            work_r2_360_b = *col_360;
            work_r0_360_b = work_r2_360_b << 2;
            work_r0_360_b += work_r2_360_b;
            work_r0_360_b <<= 3;
            work_r0_360_b -= work_r2_360_b;
            work_r0_360_b <<= 4;
            work_r0_360_b += (u32)base_360;
            work_r1_360_b += work_r0_360_b;
            work_r1_360_b += 0x70;
            *slot_360_b = (u8 *)work_r1_360_b;
        }
        {
            register u32 work_r0_360_c asm("r0");
            register u32 work_r1_360_c asm("r1") =
                (u32)D_off_27B0_BBA04;
            register u32 work_r2_360_c asm("r2");
            register u8 **slot_360_c asm("r6");

            slot_360_c = (u8 **)(base_360 + work_r1_360_c);
            work_r0_360_c = *row_360;
            work_r1_360_c = work_r0_360_c << 2;
            work_r1_360_c += work_r0_360_c;
            work_r1_360_c <<= 3;
            work_r1_360_c -= work_r0_360_c;
            work_r1_360_c <<= 7;
            work_r2_360_c = *col_360;
            work_r0_360_c = work_r2_360_c << 2;
            work_r0_360_c += work_r2_360_c;
            work_r0_360_c <<= 3;
            work_r0_360_c -= work_r2_360_c;
            work_r0_360_c <<= 4;
            work_r0_360_c += (u32)base_360;
            work_r1_360_c += work_r0_360_c;
            work_r1_360_c += 0xB0;
            *slot_360_c = (u8 *)work_r1_360_c;
        }
        func_080C5D14();
        func_080BF984(*row_360, *col_360);
        func_080C5DB4(1);
        func_080E8554(*row_360, *col_360);
        var_r0_4 = 0x2020;
        goto block_549;
    }
block_361:
    {
        register u32 outer_361 asm("r6") = 0;
        register u8 ***slot_base_361 asm("r2") = D_02032EBC;
loop_362:
        {
            register u32 inner_361 asm("r5") = 0;
            register u32 next_outer_361 asm("r7") = outer_361 + 1;
            register u32 row_offset_361 asm("r4");
            register u32 row_work_361 asm("r0") = outer_361 << 1;

            row_work_361 += outer_361;
            row_offset_361 = row_work_361 << 3;
loop_363:
            {
                register u32 active_361 asm("r0");
                register u32 call_outer_361 asm("r0") = outer_361;
                register u32 call_inner_361 asm("r1") = inner_361;

                stack.sp3C = (s32)slot_base_361;
                active_361 = func_080E9D88(call_outer_361, call_inner_361);
                active_361 <<= 24;
                slot_base_361 = (u8 ***)stack.sp3C;
                if (active_361 != 0) {
                    register u32 slot_offset_361 asm("r0") = inner_361 << 2;
                    register u8 *record_361 asm("r1");

                    slot_offset_361 += row_offset_361;
                    slot_offset_361 += (u32)slot_base_361;
                    record_361 = *(u8 **)slot_offset_361;
                    *(s32 *)(record_361 + 0x2C) = 0;
                }
            }
block_365:
            {
                register u32 next_inner_361 asm("r0") = inner_361 + 1;
                inner_361 = (u8)next_inner_361;
                if (inner_361 <= 5U)
                    goto loop_363;
            }
            {
                register u32 outer_successor_361 asm("r0") = next_outer_361 << 24;
                outer_361 = outer_successor_361 >> 24;
                if (outer_361 <= 1U)
                    goto loop_362;
            }
        }
    }
    func_080BAB3C();
    goto block_451;
block_368:
{
    register u32 base_368 asm("r5") = (u32)D_02034B4C;
    register u32 row_offset_368 asm("r3") = (u32)D_off_27A4_BBA04;
    register u32 row_address_368 asm("r6") = base_368 + row_offset_368;
    register u32 col_offset_368 asm("r1");
    register u32 col_address_368 asm("r7");

    temp_r4_9 = *(u8 *)row_address_368;
    if (temp_r4_9 == 0) {
        goto block_370;
    }
    goto block_388;
block_370:
    {
        register u32 call_row_370 asm("r0");
        register u32 call_col_370 asm("r1");

        asm volatile("add %0, %1, #0"
                     : "=r"(call_row_370)
                     : "r"(temp_r4_9));
        col_offset_368 = (u32)D_off_27A5_BBA04;
        col_address_368 = base_368 + col_offset_368;
        asm volatile("ldrb %0, [%1]"
                     : "=r"(call_col_370)
                     : "r"(col_address_368));
        if (func_080BF464(call_row_370, call_col_370, 0x23) == 0xFF) {
            goto block_372;
        }
    }
    goto block_388;
block_372:
    {
        register u32 call_row_372 asm("r0");
        register u32 call_col_372 asm("r1");

        asm volatile("ldrb %0, [%1]"
                     : "=r"(call_row_372)
                     : "r"(row_address_368));
        asm volatile("ldrb %0, [%1]"
                     : "=r"(call_col_372)
                     : "r"(col_address_368));
        if (func_080BF464(call_row_372, call_col_372, 0x1B) == 0xFF) {
            goto block_374;
        }
    }
    goto block_388;
block_374:
    {
    register u8 *list_head_374 asm("r1");
    register u8 *list_374 asm("r8");
    register u32 mode_374 asm("r0");
    func_080986B4(0);
    func_08098248(0x081070B0, 0, 0);
    {
        register u32 *table_374 asm("r1") = (u32 *)0x087EDD54;
        register u32 record_offset_374 asm("r2") = (u32)D_off_27A8_BBA04;
        register u32 record_374 asm("r0");

        asm volatile("" : "+r"(table_374));
        record_374 = base_368 + record_offset_374;
        record_374 = *(u32 *)record_374;
        record_374 = *(u8 *)record_374;
        record_374 <<= 2;
        record_374 += (u32)table_374;
        record_374 = *(u32 *)record_374;
        func_08098248(record_374, 0, 0);
    }
    list_head_374 = stack.sp24;
    list_head_374[0] = temp_r4_9;
    list_head_374[1] = 1;
    var_r4_3 = 2;
    mode_374 = M2C_FIELD((void *)0x0203055C, u8 *, 0);
    list_374 = list_head_374;
    asm volatile("" : : "h"(list_374));
    if (mode_374 == 1) {
        goto block_376;
    }
    {
        register u8 *physical_slot_374 asm("r0");

        asm volatile("mov %0, sp\n\tadd %0, #38"
                     : "=r"(physical_slot_374));
        *physical_slot_374 = var_r4_3;
    }
    var_r4_3 = 3;
block_376:
    {
        register u32 record_offset_376 asm("r3") = (u32)D_off_27AC_BBA04;
        register u32 record_376 asm("r0") = base_368 + record_offset_376;

        record_376 = *(u32 *)record_376;
        record_376 += 0x31;
        if (*(u8 *)record_376 == 0) {
            goto block_379;
        }
    }
    {
        register u32 call_row_376 asm("r0");
        register u32 call_col_376 asm("r1");

        asm volatile("ldrb %0, [%1]"
                     : "=r"(call_row_376)
                     : "r"(row_address_368));
        asm volatile("ldrb %0, [%1]"
                     : "=r"(call_col_376)
                     : "r"(col_address_368));
        if (func_080BF464(call_row_376, call_col_376, 0x17) != 0xFF) {
            goto block_379;
        }
    }
    {
        register u8 *list_base_376 asm("r0");
        register u8 *list_slot_376 asm("r1");

        asm volatile("mov %0, r8" : "=r"(list_base_376));
        list_slot_376 = list_base_376 + var_r4_3;
        *list_slot_376 = 4;
    }
    var_r4_3 += 1;
block_379:
    {
        register u32 base_379 asm("r5") = (u32)D_02034B4C;
        register u32 record_offset_379 asm("r1") = (u32)D_off_27A8_BBA04;
        register u32 record_379 asm("r0") = base_379 + record_offset_379;

        record_379 = *(u32 *)record_379;
        func_080B6768((void *)record_379);
    if (*(u8 *)0x02032472 == 0) {
        goto block_381;
    }
    {
        register u8 *list_base_379 asm("r2");
        register u8 *list_slot_379 asm("r1");

        asm volatile("mov %0, r8" : "=r"(list_base_379));
        list_slot_379 = list_base_379 + var_r4_3;
        *list_slot_379 = 5;
    }
    var_r4_3 += 1;
block_381:
    temp_r0_10 = var_r4_3 * 2;
    func_08098514(1, 0, (u32) ((0xE - temp_r0_10) << 0x17) >> 0x18, 0xA, (s32) (u8) (temp_r0_10 + 2), 0x80);
    func_080988C8(1, 0x081070D0);
    func_080988C8(1, 0x081070E0);
    if (M2C_FIELD((void *)0x0203055C, u8 *, 0) == 1) {
        goto block_383;
    }
    func_080988C8(1, 0x081070F0);
block_383:
    {
        register u32 record_offset_383 asm("r3") = (u32)D_off_27AC_BBA04;
        register u32 record_383 asm("r0") = base_379 + record_offset_383;

        record_383 = *(u32 *)record_383;
        record_383 += 0x31;
        if (*(u8 *)record_383 == 0) {
            goto block_386;
        }
    }
    {
        register u32 row_offset_383 asm("r4") = (u32)D_off_27A4_BBA04;
        register u32 row_383 asm("r0") = base_379 + row_offset_383;
        register u32 col_offset_383 asm("r2");
        register u32 col_383 asm("r1");

        row_383 = *(u8 *)row_383;
        col_offset_383 = (u32)D_off_27A5_BBA04;
        col_383 = base_379 + col_offset_383;
        col_383 = *(u8 *)col_383;
        if (func_080BF464(row_383, col_383, 0x17) != 0xFF) {
            goto block_386;
        }
    }
    func_080988C8(1, 0x081070FC);
block_386:
    if (*(u8 *)0x02032472 == 0) {
        goto block_389;
    }
    func_080988C8(1, 0x08107110);
    goto block_389;
    }
    }
}
block_388:
    func_080986B4(0);
    func_08098248(0x08107118, 0, 0);
    {
        register u32 *table_388 asm("r1") = (u32 *)0x087EDD54;
        register u32 carrier_388 asm("r0") = (u32)D_02034B4C;
        register u32 active_offset_388 asm("r3") = 0x27A8;

        asm volatile("" : "+r"(table_388));
        carrier_388 += active_offset_388;
        carrier_388 = *(u32 *)carrier_388;
        carrier_388 = *(u8 *)carrier_388;
        carrier_388 <<= 2;
        carrier_388 += (u32)table_388;
        carrier_388 = *(u32 *)carrier_388;
        func_08098248(carrier_388, 0, 0);
    }
    func_080972C8();
block_389:
    {
        register u32 carrier_389 asm("r2") = (u32)D_02034B4C;
        register u32 row_offset_389 asm("r4") = 0x27A4;
        register u32 address_389 asm("r0");
        register u32 row_389 asm("r1");
        register u32 col_offset_389 asm("r0");

        asm volatile("" : "+r"(row_offset_389));
        address_389 = carrier_389 + row_offset_389;
        row_389 = *(u8 *)address_389;
        col_offset_389 = 0x27A5;
        asm volatile("" : "+r"(col_offset_389));
        carrier_389 += col_offset_389;
        carrier_389 = *(u8 *)carrier_389;
        func_080BB224(5, row_389, carrier_389, 0);
    }
    *(u32 *)0x02030558 = 0x2040U;
    goto block_643;
block_390:
{
    register u32 base_390 asm("r7") = (u32)D_02034B4C;
    register u32 row_offset_390 asm("r1") = (u32)D_off_27A4_BBA04;
    register u32 row_address_390 asm("r4");
    register u32 row_value_390 asm("r0");
    register u32 col_offset_390 asm("r2");
    register u32 col_address_390 asm("r6");

    asm volatile("add %0, %1, %2"
                 : "=r"(row_address_390)
                 : "r"(base_390), "r"(row_offset_390)
                 : "cc");
    row_value_390 = *(u8 *)row_address_390;
    temp_r0_11 = row_value_390;
    if (row_value_390 == 0) {
        goto block_392;
    }
    goto loop_426;
block_392:
    col_offset_390 = (u32)D_off_27A5_BBA04;
    asm volatile("add %0, %1, %2"
                 : "=r"(col_address_390)
                 : "r"(base_390), "r"(col_offset_390)
                 : "cc");
    {
        register u32 call_col_392 asm("r1");

        asm volatile("ldrb %0, [%1]"
                     : "=r"(call_col_392)
                     : "r"(col_address_390));
        if (func_080BF464(temp_r0_11, call_col_392, 0x23) == 0xFF) {
            goto block_394;
        }
    }
    goto block_422;
block_394:
    {
        register u32 call_row_394 asm("r0");
        register u32 call_col_394 asm("r1");

        asm volatile("ldrb %0, [%1]"
                     : "=r"(call_row_394)
                     : "r"(row_address_390));
        asm volatile("ldrb %0, [%1]"
                     : "=r"(call_col_394)
                     : "r"(col_address_390));
        if (func_080BF464(call_row_394, call_col_394, 0x1B) == 0xFF) {
            goto block_396;
        }
    }
    goto block_422;
block_396:
    func_08098BB4(0x08003988);
    if (*(u8 *)0x0200A882 == 0) {
        goto block_412;
    }
    {
        register u32 selected_396 asm("r1") = 0x0200A880;
        register u32 stack_slot_396 asm("r0");
        register u32 store_offset_396 asm("r3");
        register u32 store_address_396 asm("r0");

        asm volatile("add %1, sp, #36\n\t"
                     "ldrb %0, [%0]\n\t"
                     "add %1, %1, %0\n\t"
                     "ldrb %0, [%1]"
                     : "+r"(selected_396), "=r"(stack_slot_396)
                     :
                     : "cc", "memory");
        store_offset_396 = (u32)D_off_A07C_BBA04;
        asm volatile("add %0, %1, %2"
                     : "=r"(store_address_396)
                     : "r"(base_390), "r"(store_offset_396)
                     : "cc");
        *(u8 *)store_address_396 = selected_396;
        selected_396 <<= 24;
        selected_396 >>= 24;
    if (selected_396 != 2) {
        goto block_400;
    }
    if ((func_080E6664(0x14) << 0x18) != 0) {
        goto block_402;
    }
    {
        register u32 *state_slot_396 asm("r1") = (u32 *)0x02030558;
        register u32 state_value_396 asm("r0") = 0x2100;

        asm volatile("str %1, [%0]"
                     :
                     : "r"(state_slot_396), "r"(state_value_396)
                     : "memory");
    }
    goto block_410;
block_400:
    if (selected_396 != 4) {
        goto block_406;
    }
    if ((func_080E6664(0x16) << 0x18) == 0) {
        goto block_404;
    }
block_402:
    func_08092E84(0x58);
    func_080986B4(0);
    func_08098BB4(0x08003F8B);
    goto block_643;
block_404:
    {
        register u32 value_404 asm("r0") = func_080ECD5C(*(s32 *)0x03000010);
        register u32 offset_404 asm("r4");
        register u32 address_404 asm("r1");

        value_404 >>= 7;
        offset_404 = (u32)D_off_A07E_BBA04;
        asm volatile("add %0, %1, %2"
                     : "=r"(address_404)
                     : "r"(base_390), "r"(offset_404)
                     : "cc");
        *(u8 *)address_404 = value_404;
    }
    goto block_409;
block_406:
    if (selected_396 != 5) {
        goto block_409;
    }
    *(u32 *)0x02030558 = 0x2200U;
    goto block_410;
block_409:
    {
        register u32 *state_slot_409 asm("r0") = (u32 *)0x02030558;
        *state_slot_409 = state_2300;
    }
block_410:
    func_08098BB4(0x0800398C);
    goto block_643;
    }
block_412:
    temp_r1_8 = *(u16 *)0x0200A884;
    if (!(0x200 & temp_r1_8)) {
        goto block_417;
    }
    var_r5_12 = 1;
    var_r4_4 = 0;
    goto loop_415;
block_414:
    var_r4_4 = (u32) (u8) (var_r4_4 + 1);
loop_415:
    if ((func_080E9D88(var_r5_12, var_r4_4) << 0x18) == 0) {
        goto block_414;
    }
    goto block_420;
block_417:
    {
        register u32 mask_417 asm("r0") = 0x100;

        mask_417 &= temp_r1_8;
        if (mask_417 != 0) {
            goto block_419;
        }
    }
    func_080986B4(0);
    func_08098248(0x081070B0, 0, 0);
    {
        register u32 *table_417 asm("r1") = (u32 *)0x087EDD54;
        register u32 record_offset_417 asm("r2") = (u32)D_off_27A8_BBA04;
        register u32 record_417 asm("r0");

        asm volatile("add %0, %1, %2"
                     : "=r"(record_417)
                     : "r"(base_390), "r"(record_offset_417)
                     : "cc");
        record_417 = *(u32 *)record_417;
        record_417 = *(u8 *)record_417;
        record_417 <<= 2;
        record_417 += (u32)table_417;
        record_417 = *(u32 *)record_417;
        func_08098248(record_417, 0, 0);
    }
    goto block_643;
block_419:
    var_r5_12 = 0;
    var_r4_4 = (u32) *(u8 *)col_address_390;
block_420:
    func_08092E84(0x40);
    {
        register u32 first_420 asm("r0") = var_r5_12;
        register u32 second_420 asm("r1") = (u8) var_r4_4;

        func_080C8538(first_420, second_420);
    }
    {
        register u32 carrier_420 asm("r2") = (u32)D_02034B4C;
        register u32 row_offset_420 asm("r3") = (u32)D_off_27A4_BBA04;
        register u32 address_420 asm("r0");
        register u32 row_420 asm("r1");

        asm volatile("add %0, %1, %2"
                     : "=r"(address_420)
                     : "r"(carrier_420), "r"(row_offset_420)
                     : "cc");
        row_420 = *(u8 *)address_420;
        {
            register u32 col_offset_420 asm("r4") = (u32)D_off_27A5_BBA04;

            asm volatile("add %0, %0, %1"
                         : "+r"(carrier_420)
                         : "r"(col_offset_420)
                         : "cc");
            carrier_420 = *(u8 *)carrier_420;
            func_080BB224(5, row_420, carrier_420, 1);
        }
    }
    goto block_643;
}
block_421:
    func_080BB224(var_r0_3, var_r1, var_r2_2, 1);
    goto block_643;
block_422:
    {
        register u32 row_address_422 asm("r0") = (u32)D_02034B4C;
        register u32 row_offset_422 asm("r1") = (u32)D_off_27A4_BBA04;

        asm volatile("add %0, %0, %1"
                     : "+r"(row_address_422)
                     : "r"(row_offset_422)
                     : "cc");
        if (*(u8 *)row_address_422 != 0) {
            goto loop_426;
        }
    }
    func_080CA1A0();
    goto block_450;
block_425:
    func_080ED17C(1);
loop_426:
    if ((func_080BB654() << 0x18) == 0) {
        goto block_425;
    }
    if (M2C_FIELD((void *)0x0203055C, u8 *, 0) == 1) {
        goto block_432;
    }
    func_080CA1A0();
    {
        register u32 base_426 asm("r1") = (u32)D_02034B4C;
        register u32 row_offset_426 asm("r2") = (u32)D_off_27A4_BBA04;
        register u32 address_426 asm("r0");

        asm volatile("add %0, %1, %2"
                     : "=r"(address_426)
                     : "r"(base_426), "r"(row_offset_426)
                     : "cc");
        address_426 = *(u8 *)address_426;
        address_426 <<= 2;
        asm volatile("add %0, %0, %1"
                     : "+r"(address_426)
                     : "r"(base_426)
                     : "cc");
        {
            register u32 flag_offset_426 asm("r3") = (u32)D_off_A07C_BBA04;

            asm volatile("add %0, %0, %1"
                         : "+r"(address_426)
                         : "r"(flag_offset_426)
                         : "cc");
        }
        if (*(u8 *)address_426 == 0) {
            goto block_430;
        }
    }
    goto block_461;
block_430:
    func_080E9998();
    goto block_461;
block_432:
{
    register u32 ready_432 asm("r4");

    func_0809B00C(0x0203EBCC, 4, 0x08107094);
loop_433:
    ready_432 = func_0809B040();
    ready_432 = (u8)ready_432;
    func_080ED17C(1);
    if (ready_432 == 0) {
        goto loop_433;
    }
    {
        register u32 base_432 asm("r1") = (u32)D_02034B4C;
        register u32 transfer_address_432 asm("r0");

        ready_432 = 0xA080;
        asm volatile("add %0, %1, %2"
                     : "=r"(transfer_address_432)
                     : "r"(base_432), "r"(ready_432)
                     : "cc");
        if (*(u8 *)transfer_address_432 != 0) {
            goto block_440;
        }
        {
            register u32 transfer_offset_432 asm("r2") = 0xA1AC;

            asm volatile("add %0, %1, %2"
                         : "=r"(transfer_address_432)
                         : "r"(base_432), "r"(transfer_offset_432)
                         : "cc");
            func_0809B00C(transfer_address_432, 0x2E, 0x0810709C);
        }
loop_436:
    ready_432 = func_0809B040();
    ready_432 = (u8)ready_432;
    func_080ED17C(1);
    if (ready_432 == 0) {
        goto loop_436;
    }
    func_080E9D48();
    func_0809B00C(0x0203ED28, 0xC0, 0x081070A8);
loop_438:
    ready_432 = func_0809B040();
    ready_432 = (u8)ready_432;
    func_080ED17C(1);
    if (ready_432 == 0) {
        goto loop_438;
    }
    func_080BFCD8();
    goto block_461;
block_440:
    {
        register u32 transfer_offset_440 asm("r3") = 0xA1DC;

        asm volatile("add %0, %1, %2"
                     : "=r"(transfer_address_432)
                     : "r"(base_432), "r"(transfer_offset_440)
                     : "cc");
        func_0809B00C(transfer_address_432, 0x30, 0x081070A8);
    }
loop_441:
    ready_432 = func_0809B040();
    ready_432 = (u8)ready_432;
    func_080ED17C(1);
    if (ready_432 == 0) {
        goto loop_441;
    }
    func_080BFCD8();
    goto block_461;
    }
}
block_443:
    if (func_080C598C() == 0) {
        goto block_451;
    }
    {
        register s32 *state_slot_443 asm("r4") = temp_r0;

        *state_slot_443 = state_2300;
    }
    goto block_643;
block_445:
    func_08098BB4(0x08003AF5);
    {
        register u32 index asm("r6");
        register s32 *table asm("r5");
        register void **record_slot asm("r4");

        index = 0;
        if (index >= (u32)*(u8 *)0x02032472) {
            goto block_448;
        }
        table = (s32 *)0x087EDD54;
        record_slot = (void **)0x020372F4;
loop_447:
        {
            u32 selected;
            register void *record asm("r0");
            register u8 *list_value asm("r1");
            record = *record_slot;
            list_value = (u8 *)0x0203246C;
            asm volatile("" : "+r"(list_value));
            list_value = (u8 *)((u32)index + (u32)list_value);
            list_value = (u8 *)(u32)*list_value;
            selected = func_080E5320(record, (u32)list_value);
            selected <<= 24;
            selected >>= 22;
            func_080988C8(1, table[selected / 4]);
        }
        {
            register u32 next asm("r0");
            next = index + 1;
            next <<= 24;
            index = next >> 24;
        }
        if (index < (u32)*(u8 *)0x02032472) {
            goto loop_447;
        }
    }
block_448:
    func_08098BB4(0x08003AFD);
    if (*(u8 *)0x0200A882 != 1) {
        goto block_451;
    }
    {
        register u8 *destination_base asm("r1");
        register u32 carrier asm("r2");
        register u32 value asm("r0");

        destination_base = D_02034B4C;
        carrier = 0x0203246C;
        asm volatile("" : "+r"(carrier));
        value = 0x0200A880;
        value = *(u8 *)value;
        value += carrier;
        value = *(u8 *)value;
        carrier = 0xA07D;
        asm volatile("" : "+r"(carrier));
        destination_base += carrier;
        *destination_base = value;
    }
block_450:
    *(u32 *)0x02030558 = 0x2300U;
    goto block_643;
block_451:
    *(u32 *)0x02030558 = 0x2030U;
    goto block_643;
block_453:
    func_080ED17C(1);
loop_454:
    if ((func_080BB654() << 0x18) == 0) {
        goto block_453;
    }
    func_080BFB90();
    if (M2C_FIELD((void *)0x0203055C, u8 *, 0) != 1) {
        goto block_461;
    }
    {
        register u32 ready_453 asm("r5");
        register u32 base_453 asm("r0") = (u32)D_02034B4C;
        register u32 flag_offset_453 asm("r3") = 0xA07C;
        register u32 flag_address_453 asm("r1");

        asm volatile("add %0, %1, %2"
                     : "=r"(flag_address_453)
                     : "r"(base_453), "r"(flag_offset_453)
                     : "cc");
        {
            register u32 active_453 asm("r0") = *(u8 *)flag_address_453;

            if (active_453 == 0) {
                goto block_461;
            }
        }
        func_0809AEC0(flag_address_453, 4, 0x08107094);
loop_458:
        ready_453 = func_0809AEF4();
        ready_453 = (u8)ready_453;
        func_080ED17C(1);
        if (ready_453 == 0) {
            goto loop_458;
        }
        func_0809AEC0(0x0203ED28, 0x30, 0x081070A8);
loop_460:
        ready_453 = func_0809AEF4();
        ready_453 = (u8)ready_453;
        func_080ED17C(1);
        if (ready_453 == 0) {
            goto loop_460;
        }
    }
block_461:
    *(u32 *)0x02030558 = 0x2400U;
    goto block_643;
block_462:
    func_080C5D14();
    {
        register u32 base_462 asm("r1") = (u32)D_02034B4C;
        register u32 row_offset_462 asm("r4") = (u32)D_off_27A4_BBA04;
        register u32 state_address_462 asm("r0");
        register u32 state_value_462 asm("r2");

        asm volatile("add %0, %1, %2"
                     : "=r"(state_address_462)
                     : "r"(base_462), "r"(row_offset_462)
                     : "cc");
        state_address_462 = *(u8 *)state_address_462;
        state_address_462 <<= 2;
        asm volatile("add %0, %0, %1"
                     : "+r"(state_address_462)
                     : "r"(base_462)
                     : "cc");
        {
            register u32 flag_offset_462 asm("r1") = (u32)D_off_A07C_BBA04;

            asm volatile("add %0, %0, %1"
                         : "+r"(state_address_462)
                         : "r"(flag_offset_462)
                         : "cc");
        }
        state_value_462 = *(volatile u8 *)state_address_462;
        if (state_value_462 == 0) {
            register u32 next_state_462 asm("r0") = 0x3000;
            register s32 *state_slot_462 asm("r3") = temp_r0;

            *state_slot_462 = next_state_462;
            {
                register u32 *mode_slot_462 asm("r1") = (u32 *)0x02021690;
                register u32 mode_value_462 asm("r0") = 0xA;

                *mode_slot_462 = mode_value_462;
            }
            *(u8 *)0x02033F34 = state_value_462;
            goto block_633;
        }
        switch (*(volatile u8 *)state_address_462) { /* switch 1; jump table: jtbl_080BD764 */
case 1:                                             /* switch 1 */
    *(u32 *)0x02030558 = 0x3010U;
    goto block_643;
case 2:                                             /* switch 1 */
    *(u32 *)0x02030558 = 0x3010U;
    goto block_643;
case 3:                                             /* switch 1 */
    *(u32 *)0x02030558 = 0x3010U;
    goto block_643;
case 4:                                             /* switch 1 */
    *(u32 *)0x02030558 = 0x3000U;
    *(u32 *)0x02021690 = 0xA;
    *(u8 *)0x02033F34 = 1U;
    goto block_633;
case 5:                                             /* switch 1 */
    {
        register u8 *(*slot_base)[6] asm("r4") = D_02032EBC;
        register u8 *case_base asm("r6");
        register u8 *row asm("r5");
        register u8 *col asm("r3");

        case_base = D_02034B4C;
        {
            register u32 col_offset_462 asm("r0") = (u32)D_off_27A5_BBA04;

            asm volatile("add %0, %1, %2"
                         : "=r"(col)
                         : "r"(case_base), "r"(col_offset_462)
                         : "cc");
        }
        {
            register u32 slot_offset asm("r1") = *col;
            register u32 row_index asm("r2");
            register u32 row_offset asm("r0");

            slot_offset <<= 2;
            row = case_base + 0x27A4;
            row_index = *row;
            row_offset = row_index << 1;
            row_offset += row_index;
            row_offset <<= 3;
            slot_offset += row_offset;
            slot_offset += (u32)slot_base;
            *(s32 *)(*(u8 **)slot_offset + 0x2C) = 0x20000;
        }
        {
            register u8 *flag_base asm("r2") = &D_02032EEC[0][0];

            {
                register u32 row_value asm("r1") = *row;
                register u32 flag_address asm("r0");
                register u32 col_value asm("r4");
                register u32 flag_value asm("r1");

                flag_address = row_value << 1;
                flag_address += row_value;
                flag_address <<= 1;
                col_value = *col;
                flag_address += col_value;
                flag_address += (u32)flag_base;
                flag_value = 2;
                *(u8 *)flag_address = flag_value;
            }
            {
                register u32 test_row_462 asm("r1") = *row;
                register u32 test_address_462 asm("r0");
                register u32 test_col_462 asm("r3");

                test_address_462 = test_row_462 << 1;
                test_address_462 += test_row_462;
                test_address_462 <<= 1;
                test_col_462 = *col;
                test_address_462 += test_col_462;
                asm volatile("add %0, %0, %1"
                             : "+r"(test_address_462)
                             : "r"(flag_base)
                             : "cc");
                if (*(u8 *)test_address_462 != 0) {
                    register u8 *loop_flags asm("r7") = flag_base;
                    register u8 *loop_row asm("r4") = row;

                    do {
                        register u8 *loop_col asm("r2");
                        register u32 row_value asm("r1");
                        register u32 flag_offset asm("r0");

                        func_080ED17C(1);
                        flag_offset = (u32)D_off_27A5_BBA04;
                        asm volatile("add %0, %1, %2"
                                     : "=r"(loop_col)
                                     : "r"(case_base), "r"(flag_offset)
                                     : "cc");
                        row_value = *loop_row;
                        flag_offset = row_value << 1;
                        flag_offset += row_value;
                        flag_offset <<= 1;
                        flag_offset += *loop_col;
                        flag_offset += (u32)loop_flags;
                        if (*(u8 *)flag_offset == 0) {
                            break;
                        }
                    } while (1);
                }
            }
        }
        {
            register u8 *call_base asm("r4") = D_02034B4C;
            register u32 record_offset asm("r1") = 0x27A8;
            register u8 *record asm("r0");
            register u32 row_offset asm("r2") = 0x27A4;
            register u8 *value_address asm("r1");
            register u32 value_offset asm("r1");
            register u32 value_bias asm("r3") = 0xA07D;
            register u8 result asm("r0");

            record = *(u8 **)(call_base + record_offset);
            value_address = call_base + row_offset;
            value_offset = *value_address;
            value_offset <<= 2;
            value_offset += (u32)call_base;
            value_offset += value_bias;
            result = func_080E5320(record, *(u8 *)value_offset);
            {
                register u32 store_offset asm("r1") = 0x270E;
                call_base += store_offset;
                *call_base = result;
            }
        }
    }
    *(u32 *)0x02030558 = 0x3000U;
    *(u32 *)0x02021690 = 0xB;
    goto block_633;
default:
    goto block_643;
        }
    }
block_475:
    func_080BB940();
    {
    register u32 outer_475 asm("r6") = 0;
    register u32 zero_475_local asm("r8");
    register u8 ***slot_base_475_local asm("sl");

    zero_475_local = outer_475;
    {
        register u8 ***slot_seed_475 asm("r2") = D_02032EBC;

        slot_base_475_local = slot_seed_475;
    }
loop_476:
    {
    register u32 inner_475 asm("r5") = 0;
    register u32 next_outer_475 asm("r7") = outer_475 + 1;
    register u32 outer_offset_475 asm("r9");
    {
        register u32 outer_work_475 asm("r0") = outer_475 << 2;

        outer_work_475 += outer_475;
        outer_work_475 <<= 3;
        outer_work_475 -= outer_475;
        outer_work_475 <<= 7;
        outer_offset_475 = outer_work_475;
    }
loop_477:
    if ((func_080E9D88(outer_475, inner_475) << 0x18) == 0) {
        goto block_479;
    }
    {
        register u32 slot_offset_475_local asm("r4") = inner_475 << 2;
        register u32 record_475 asm("r2");
        register u32 base_475_local asm("r3");
        register u32 first_475 asm("r0");
        register u32 second_475 asm("r1");

        record_475 = slot_offset_475_local + inner_475;
        record_475 <<= 3;
        record_475 -= inner_475;
        record_475 <<= 4;
        record_475 += outer_offset_475;
        base_475_local = (u32)D_02034B4C;
        asm volatile("add %0, %0, %1"
                     : "+r"(record_475)
                     : "r"(base_475_local)
                     : "cc");
        first_475 = *(u8 *)record_475;
        second_475 = *(u8 *)(record_475 + 1);
        record_475 += 0x38;
        record_475 = *(u8 *)record_475;
        func_080BAF2C(first_475, second_475, record_475, outer_475,
            inner_475, zero_475_local, zero_475_local);
        {
            register u32 slot_outer_475 asm("r0") = outer_475 << 1;
            register u8 *slot_record_475 asm("r0");

            slot_outer_475 += outer_475;
            slot_outer_475 <<= 3;
            slot_offset_475_local += slot_outer_475;
            slot_offset_475_local += (u32)slot_base_475_local;
            slot_record_475 = *(u8 **)slot_offset_475_local;
            slot_offset_475_local = zero_475_local;
            *(u32 *)(slot_record_475 + 0x2C) = slot_offset_475_local;
        }
    }
block_479:
    {
        register u32 next_inner_475 asm("r0") = inner_475 + 1;

        next_inner_475 <<= 24;
        inner_475 = next_inner_475 >> 24;
    }
    if (inner_475 <= 5U) {
        goto loop_477;
    }
    {
        register u32 normalized_outer_475 asm("r0") = next_outer_475 << 24;

        outer_475 = normalized_outer_475 >> 24;
    }
    }
    if (outer_475 <= 1U) {
        goto loop_476;
    }
    }
    func_080BAB3C();
    if (*(u8 *)0x02033F35 != 0) {
        goto block_483;
    }
    {
        register u32 *state_slot asm("r1") = (u32 *)0x02030558;
        register u32 state_value asm("r0") = 0x3010;
        *state_slot = state_value;
    }
    goto block_484;
block_483:
    {
        register u32 carrier asm("r2") = (u32)D_02034B4C;
        register u32 row_offset asm("r1") = 0x27A4;
        register u32 address asm("r0");
        register u32 row asm("r1");
        register u32 col_offset asm("r3");

        address = carrier + row_offset;
        row = *(u8 *)address;
        col_offset = 0x27A5;
        asm volatile("" : "+r"(col_offset));
        carrier += col_offset;
        carrier = *(u8 *)carrier;
        func_080BB224(5, row, carrier, 1);
    }
    {
        register u32 *state_slot asm("r1") = (u32 *)0x02030558;
        register u32 state_value asm("r0") = 0x2030;
        *state_slot = state_value;
    }
block_484:
    func_08093AE8(0x0202F094, 1);
    *(u8 *)0x03000074 |= 1;
    func_08098BB4(0x080036D3);
    var_r0_8 = 1;
    goto block_634;
block_486:
{
    register u32 base_486 asm("r1") = (u32)D_02034B4C;
    register u32 row_offset_486 asm("r4") = (u32)D_off_27A4_BBA04;
    register u32 selector_486 asm("r0");

    asm volatile("add %0, %1, %2"
                 : "=r"(selector_486)
                 : "r"(base_486), "r"(row_offset_486)
                 : "cc");
    selector_486 = *(u8 *)selector_486;
    selector_486 <<= 2;
    asm volatile("add %0, %0, %1"
                 : "+r"(selector_486)
                 : "r"(base_486)
                 : "cc");
    {
        register u32 flag_offset_486 asm("r1") = (u32)D_off_A07C_BBA04;

        asm volatile("add %0, %0, %1"
                     : "+r"(selector_486)
                     : "r"(flag_offset_486)
                     : "cc");
    }
    selector_486 = *(u8 *)selector_486;
    switch (selector_486) {                         /* switch 2; jump table: jtbl_080BD9A4 */
default:                                            /* switch 2 */
    goto block_643;
case 0:                                             /* switch 2 */
    var_r0_4 = 0x3100;
    goto block_549;
case 1:                                             /* switch 2 */
    var_r0_6 = 0x3200;
    goto block_494;
case 2:                                             /* switch 2 */
    var_r0_5 = 0x3300;
    goto block_638;
case 3:                                             /* switch 2 */
    var_r0 = 0x3400;
    goto block_543;
case 4:                                             /* switch 2 */
    var_r0_4 = 0x3500;
    goto block_549;
case 5:                                             /* switch 2 */
    var_r0_6 = 0x3600;
block_494:
    {
        register s32 *state_slot_494 asm("r3") = temp_r0;

        *state_slot_494 = var_r0_6;
    }
    goto block_643;
    }
}
block_495:
    {
        register u32 base_495_first asm("r1") = (u32)D_02034B4C;
        register u32 row_offset_495_first asm("r4") =
            (u32)D_off_27A4_BBA04;
        register u32 row_495_first asm("r0");
        register u32 col_offset_495_first asm("r2");

        row_495_first = base_495_first + row_offset_495_first;
        row_495_first = *(u8 *)row_495_first;
        asm volatile("" : : "r"(row_495_first));
        col_offset_495_first = (u32)D_off_27A5_BBA04;
        base_495_first += col_offset_495_first;
        base_495_first = *(u8 *)base_495_first;
        func_080BFD1C(row_495_first, base_495_first);
    }
    goto loop_497;
block_496:
    func_080ED17C(1);
loop_497:
    if ((func_0809669C() << 0x18) == 0) {
        goto block_496;
    }
    {
        register u32 base_495_second asm("r1") = (u32)D_02034B4C;
        register u32 row_offset_495_second asm("r3") =
            (u32)D_off_27A4_BBA04;
        register u32 row_495_second asm("r0");
        register u32 col_offset_495_second asm("r4");

        row_495_second = base_495_second + row_offset_495_second;
        row_495_second = *(u8 *)row_495_second;
        asm volatile("" : : "r"(row_495_second));
        col_offset_495_second = (u32)D_off_27A5_BBA04;
        base_495_second += col_offset_495_second;
        base_495_second = *(u8 *)base_495_second;
        func_080BFA4C(row_495_second, base_495_second);
    }
block_499:
    func_080C5DB4(1);
    goto block_539;
block_501:
    func_080BFD1C(D_02034B4C[0x27A4], D_02034B4C[0x27A5]);
    goto loop_503;
block_502:
    func_080ED17C(1);
loop_503:
    if ((func_0809669C() << 0x18) == 0) {
        goto block_502;
    }
    func_080BE65C(D_02034B4C[0x27A4], D_02034B4C[0x27A5], -1, 0, 0, 0, 0x1A, 0, 1, 0);
    temp_r5_7 = *(void **)&D_02034B4C[0x27A8];
    if ((s32) (M2C_FIELD(temp_r5_7, s16 *, 8) + M2C_FIELD(temp_r5_7, s16 *, 0x40)) > (s32) M2C_FIELD(temp_r5_7, s16 *, 0x3E)) {
        goto block_507;
    }
    var_r0_9 = (u16) M2C_FIELD(temp_r5_7, s16 *, 0x40);
    goto block_508;
block_507:
    var_r0_9 = (u16) M2C_FIELD(temp_r5_7, s16 *, 0x3E) - (u16) M2C_FIELD(temp_r5_7, s16 *, 8);
block_508:
    temp_r5_8 = (s16) var_r0_9;
    if (temp_r5_8 == 0) {
        goto block_510;
    }
    {
        register u8 *base asm("r1") = D_02034B4C;
        register u32 zero asm("r4");

        {
            register u32 record_offset asm("r2") = 0x27A8;
            register u8 *record_address asm("r0") = base + record_offset;
            register u8 *record asm("r2") = *(u8 **)record_address;
            register u32 current asm("r0") = *(u16 *)(record + 8);

            current = temp_r5_8 + current;
            zero = 0;
            *(u16 *)(record + 8) = current;
        }
        {
            register u32 row_offset asm("r3") = 0x27A4;
            register u8 *row_address asm("r0") = base + row_offset;
            register u32 row asm("r0") = *row_address;
            register u32 col_offset asm("r2");
            register u32 col asm("r1");

            col_offset = 0x27A5;
            asm volatile("" : "+r"(col_offset));
            base += col_offset;
            col = *base;
            func_080BE9D8(row, col, -1, 0, zero, zero, 4,
                          (s32)temp_r5_8, zero, zero);
        }
    }
block_510:
    func_080C5DB4(0);
    goto block_539;
block_512:
    {
        register u8 *base asm("r4");
        register u8 *row asm("r5");

        base = D_02034B4C;
        {
            register u32 row_offset_512 asm("r3") =
                (u32)D_off_27A4_BBA04;

            row = base + row_offset_512;
        }
        {
            register u32 row_value_512 asm("r0") = *row;
            register u32 col_offset_512 asm("r2");
            register u32 col_value_512 asm("r1");

            asm volatile("" : : "r"(row_value_512));
            col_offset_512 = (u32)D_off_27A5_BBA04;
            col_value_512 = (u32)base + col_offset_512;
            col_value_512 = *(u8 *)col_value_512;
            func_080BFD1C(row_value_512, col_value_512);
        }
        {
            register u32 row_value_512 asm("r1") = *row;
            register u32 record_512 asm("r2") = row_value_512 * 4;

            record_512 += (u32)base;
            func_080C5C00(*(u8 *)(record_512 + 0xA07D), row_value_512,
                           *(u8 *)(record_512 + 0xA07E));
        }
        func_080E5D98((base + (*row * 4))[0xA07D], 1);
    }
    goto loop_515;
block_514:
    func_080ED17C(1);
loop_515:
    if ((func_0809669C() << 0x18) == 0) {
        goto block_514;
    }
    goto block_499;
block_517:
    func_080BFD1C(D_02034B4C[0x27A4], D_02034B4C[0x27A5]);
    goto loop_520;
block_519:
    func_080ED17C(1);
loop_520:
    if ((func_0809669C() << 0x18) == 0) {
        goto block_519;
    }
    goto block_510;
block_522:
    func_080BFD1C(D_02034B4C[0x27A4], D_02034B4C[0x27A5]);
    goto loop_525;
block_524:
    func_080ED17C(1);
loop_525:
    if ((func_0809669C() << 0x18) == 0) {
        goto block_524;
    }
    func_080EA408(D_02034B4C[0x27A4], D_02034B4C[0x27A5]);
    goto block_499;
block_527:
    {
        register u8 *base asm("r7");
        u8 *record;
        register u8 *row asm("r4");
        register u8 *col asm("r5");
        s32 zero;

        {
            register u8 * volatile *record_slot asm("r5");
            register u32 i asm("r6");
            register u8 *copy_src asm("r4");
            {
                register u8 *setup_base asm("r1") = D_02034B4C;
                register u32 record_offset asm("r4") =
                    (u32)D_off_27A8_BBA04;
                register u8 *slot_address asm("r3");
                register u8 *setup_record asm("r2");
                register u32 source_byte asm("r0");

                asm volatile("add %0, %1, %2"
                             : "=r"(slot_address)
                             : "r"(setup_base), "r"(record_offset)
                             : "cc");
                setup_record = *(u8 **)slot_address;
                record_offset -= 154;
                asm volatile("add %0, %1, %2"
                             : "=r"(source_byte)
                             : "r"(setup_base), "r"(record_offset)
                             : "cc");
                source_byte = *(u8 *)source_byte;
                *setup_record = source_byte;
                i = 4;
                base = setup_base;
                record_slot = (u8 * volatile *)slot_address;
            }
            copy_src = (u8 *)0x087AFCDC;
            do {
                register u8 *loop_record asm("r0") = *record_slot;
                register u32 copy_offset asm("r2") = i << 2;
                register u32 copy_dst asm("r3") = (u32)loop_record;
                register u32 kind asm("r1");
                register u32 table_offset asm("r0");

                copy_dst += 0x50;
                copy_dst += copy_offset;
                kind = *loop_record;
                table_offset = kind << 3;
                table_offset -= kind;
                table_offset <<= 3;
                copy_offset += table_offset;
                copy_offset += (u32)copy_src;
                *(u32 *)copy_dst = *(u32 *)copy_offset;
                {
                    register u32 next_i asm("r0") = i + 1;

                    next_i <<= 24;
                    i = next_i >> 24;
                }
            } while (i <= 7);
        }

        row = base + 0x27A4;
        {
            register u32 first_row_527 asm("r0") = *row;

            asm volatile("" : : "r"(first_row_527));
            col = base + 0x27A5;
            func_080BE560(first_row_527, *col);
        }
        func_080E90AC(*row, *col);
        func_080E8B08(*row, *col);
        {
            register u32 record_offset_527 asm("r2") =
                (u32)D_off_27A8_BBA04;
            register u8 *record_address_527 asm("r0");

            asm volatile("add %0, %1, %2"
                         : "=r"(record_address_527)
                         : "r"(base), "r"(record_offset_527)
                         : "cc");
            record = *(u8 **)record_address_527;
        }
        zero = 0;
        func_080BAF2C(record[0], record[1], record[0x38], *row, *col,
                     *row == 0 ? 0x10000 : 0xFFFF0000, zero);

        D_02032EEC[D_02034B4C[0x27A4]][D_02034B4C[0x27A5]] = 1;
        while ((func_0809669C() << 0x18) == 0) {
            func_080ED17C(1);
        }
        {
            register u8 *status_base_527 asm("r4") = (u8 *)D_02032EEC;
            register u8 *base_527_wait asm("r2") = D_02034B4C;
            register u8 *row_address_527 asm("r6");
            register u8 *saved_base_527 asm("r7");
            register u32 column_offset_527 asm("r0") =
                (u32)D_off_27A5_BBA04;
            register u8 *column_address_527 asm("r3");
            register u32 row_offset_527 asm("r1");
            register u32 row_527 asm("r1");
            register u32 column_527 asm("r3");
            register u32 status_index_527 asm("r0");

            column_address_527 = base_527_wait + column_offset_527;
            row_offset_527 = (u32)D_off_27A4_BBA04;
            row_address_527 = base_527_wait + row_offset_527;
            row_527 = *row_address_527;
            status_index_527 = row_527 << 1;
            status_index_527 += row_527;
            status_index_527 <<= 1;
            column_527 = *column_address_527;
            status_index_527 += column_527;
            status_index_527 += (u32)status_base_527;
            status_index_527 = *(u8 *)status_index_527;
            saved_base_527 = base_527_wait;
            if (status_index_527 == 0) {
                goto block_539;
            }
            {
                register u8 *saved_status_527 asm("r5") = status_base_527;

                status_base_527 = saved_base_527;
loop_538_local:
                func_080ED17C(1);
                {
                    register u32 loop_column_offset_527 asm("r3") =
                        (u32)D_off_27A5_BBA04;
                    register u8 *loop_column_address_527 asm("r2") =
                        status_base_527 + loop_column_offset_527;
                    register u32 loop_row_527 asm("r1") = *row_address_527;
                    register u32 loop_index_527 asm("r0") = loop_row_527 << 1;
                    register u32 loop_column_527 asm("r2");

                    loop_index_527 += loop_row_527;
                    loop_index_527 <<= 1;
                    loop_column_527 = *loop_column_address_527;
                    loop_index_527 += loop_column_527;
                    loop_index_527 += (u32)saved_status_527;
                    loop_index_527 = *(u8 *)loop_index_527;
                    if (loop_index_527 != 0) {
                        goto loop_538_local;
                    }
                }
            }
        }
        goto block_539;
    }
block_539:
    *(u32 *)0x02030558 = 0x4000U;
    goto block_643;
block_541:
    {
    register u8 *state_base_541 asm("r0");
    register u8 *saved_state_541 asm("r6");
    register u32 state_mode_541 asm("r1");

    temp_r4_14 = func_080C682C();
    if (temp_r4_14 != 0) {
        goto block_545;
    }
    {
        register u8 *count_base asm("r0") = D_02034B4C;
        register u32 count_offset asm("r4") = 0x2710;
        register u32 count asm("r1");

        asm volatile("" : "+r"(count_offset));
        count_base += count_offset;
        count = *count_base;
        count += 1;
        *count_base = count;
    }
    var_r0 = 0x2000;
block_543:
    {
        register s32 *state_slot_543 asm("r1") = temp_r0;

        *state_slot_543 = var_r0;
    }
    goto block_643;
block_545:
    state_base_541 = (u8 *)0x0203055C;
    state_mode_541 = state_base_541[5];
    saved_state_541 = state_base_541;
    if (state_mode_541 != 0xA) {
        goto block_547;
    }
    func_080BB7EC();
block_547:
    if (!(4 & temp_r4_14)) {
        goto block_550;
    }
    var_r0_4 = 0xA000;
block_549:
    {
        register s32 *state_slot_549 asm("r2") = temp_r0;

        *state_slot_549 = var_r0_4;
    }
    goto block_643;
block_550:
    if (!(1 & temp_r4_14)) {
        goto block_556;
    }
    if (saved_state_541[0] != 1) {
        goto block_553;
    }
    {
        register u32 final_flags_541 asm("r4") = temp_r4_14;
        register u32 final_mask_541 asm("r0") = 2;

        final_flags_541 &= final_mask_541;
        if (final_flags_541 != 0) {
            goto block_554;
        }
    }
block_553:
    *(u32 *)0x02030558 = 0x6000U;
    goto block_643;
block_554:
    *(u32 *)0x02030558 = 0x8000U;
    goto block_643;
block_556:
    *(u32 *)0x02030558 = var_r5;
    goto block_643;
    }
block_558:
    func_080C5D14();
    func_080BFB90();
    if (M2C_FIELD((void *)0x0203055C, u8 *, 0) != 1) {
        goto block_567;
    }
    if (*(u8 *)0x0300603C == 0) {
        goto block_564;
    }
    func_0809AEC0(0x0203ED28, 0x30, 0x081070A8);
    {
    register u32 ready_561 asm("r5");
loop_561:
    ready_561 = func_0809AEF4();
    ready_561 = (u8)ready_561;
    func_080ED17C(1);
    if (ready_561 == 0) {
        goto loop_561;
    }
    }
    goto block_567;
block_564:
    func_0809B00C(0x0203ED28, 0x30, 0x081070A8);
    {
    register u32 ready_565 asm("r4");
loop_565:
    ready_565 = func_0809B040();
    ready_565 = (u8)ready_565;
    func_080ED17C(1);
    if (ready_565 == 0) {
        goto loop_565;
    }
    }
    func_080BFCD8();
block_567:
    func_080BF858();
    func_080C5DB4(1);
    {
        register u8 *state_base asm("r4") = D_02034B4C;
        register u32 count_offset asm("r3") = 0x270C;
        register u8 *count asm("r1") = state_base + count_offset;
        register u32 value asm("r0") = *count;
        register u32 random asm("r0");

        asm volatile("" : "+r"(count_offset));
        value += 1;
        *count = value;
        random = func_080ECD5C(*(u32 *)0x03000010);
        {
            register u32 scale asm("r1") = 0x64;
            random *= scale;
        }
        random >>= 0xF;
        {
            register u32 delay_offset asm("r1") = 0x270D;

            asm volatile("" : "+r"(delay_offset));
            state_base += delay_offset;
            *state_base = random;
        }
    }
block_568:
    *(u32 *)0x02030558 = 0x1000U;
    goto block_643;
block_569:
    *(u8 *)0x02032EF8 = 6;
    func_08092E74(6U);
    temp_r0_17 = M2C_FIELD((void *)0x0203055C, u8 *, 0);
    if (temp_r0_17 != 1) {
        goto block_571;
    }
    goto block_598;
block_571:
    if ((s32) temp_r0_17 > 1) {
        goto block_576;
    }
    if (temp_r0_17 != 0) {
        goto block_574;
    }
    goto block_583;
block_574:
    goto block_643;
block_576:
    if (temp_r0_17 != 2) {
        goto block_578;
    }
    goto block_605;
block_578:
    goto block_643;
    {
    register u8 *matched_state asm("r8");
    register u8 *matched_table asm("r7");
    register u32 matched_work asm("r4");
    register u8 *matched_record asm("r5");
    register u32 scan_index asm("r6");
block_579:
    {
        register u32 arg0 asm("r0");
        register u32 arg1 asm("r1");
        register u32 arg2 asm("r2");

        arg0 = *(u16 *)matched_record;
        asm volatile("" : : "r"(arg0));
        arg1 = (u32)matched_table + 2;
        arg1 = matched_work + arg1;
        arg1 = *(u16 *)arg1;
        arg1 <<= 0xB;
        arg2 = (u32)matched_table + 4;
        arg2 = matched_work + arg2;
        arg2 = *(u16 *)arg2;
        arg2 <<= 0xB;
        func_0809E204(arg0, arg1, arg2, 0);
    }
    {
        register u32 value asm("r0");
        register u8 *state_view asm("r2");

        value = (u32)matched_table + 6;
        value = matched_work + value;
        value = *(u16 *)value;
        value <<= 0xB;
        state_view = matched_state;
        *(u32 *)(state_view + 0x14) = value;
        value = (u32)matched_table;
        value += 8;
        value = matched_work + value;
        value = *(u16 *)value;
        value <<= 0xB;
        *(u32 *)(state_view + 0x18) = value;
    }
    {
        register u8 *position_base asm("r2");
        register u8 *category_base asm("r3");
        register u32 work asm("r0");
        register u32 kind asm("r1");
        register u8 *position_entry asm("r1");
        register u32 zero asm("r4");
        register u32 *state_words asm("r1");
        register u32 *late_state_words asm("r3");

        position_base = (u8 *)0x087AFBB4;
        category_base = (u8 *)0x087C4434;
        asm volatile("" : "+r"(position_base));
        work = *(u16 *)matched_record;
        work <<= 5;
        work += (u32)category_base;
        kind = *(u8 *)(work + 0x1D);
        kind -= 1;
        work = kind << 1;
        work += kind;
        work <<= 1;
        position_entry = position_base + 2;
        work += (u32)position_entry;
        asm volatile(
            "mov %1, #0\n\t"
            "ldrsh %0, [%0, %1]"
            : "+r"(work), "=r"(zero));
        work <<= 0xB;
        state_words = (u32 *)matched_state;
        state_words[3] = work;

        work = *(u16 *)matched_record;
        work <<= 5;
        work += (u32)category_base;
        kind = *(u8 *)(work + 0x1D);
        kind -= 1;
        work = kind << 1;
        work += kind;
        work <<= 1;
        position_base += 4;
        work += (u32)position_base;
        asm volatile(
            "mov %1, #0\n\t"
            "ldrsh %0, [%0, %1]"
            : "+r"(work), "=r"(position_base));
        work <<= 0xB;
        late_state_words = (u32 *)matched_state;
        late_state_words[4] = work;
    }
    goto block_589;
block_581:
    {
        register u32 arg0 asm("r0");
        register u32 arg1 asm("r1");
        register u32 arg2 asm("r2");

        arg0 = *(u16 *)matched_record;
        asm volatile("" : : "r"(arg0));
        arg1 = (u32)matched_table + 2;
        arg1 = matched_work + arg1;
        arg1 = *(u16 *)arg1;
        arg1 <<= 0xB;
        arg2 = (u32)matched_table + 4;
        arg2 = matched_work + arg2;
        arg2 = *(u16 *)arg2;
        arg2 <<= 0xB;
        func_0809E204(arg0, arg1, arg2, 0);
    }
    {
        register u32 value asm("r0");
        register u8 *state_view asm("r1");

        value = (u32)matched_table + 6;
        value = matched_work + value;
        value = *(u16 *)value;
        value <<= 0xB;
        state_view = matched_state;
        *(u32 *)(state_view + 0x14) = value;
        value = (u32)matched_table;
        value += 8;
        value = matched_work + value;
        value = *(u16 *)value;
        value <<= 0xB;
        *(u32 *)(state_view + 0x18) = value;
    }
    {
        register u8 *position_base asm("r2");
        register u8 *category_base asm("r3");
        register u32 work asm("r0");
        register u32 kind asm("r1");
        register u8 *position_entry asm("r1");
        register u32 zero asm("r4");
        register u32 *state_words asm("r1");
        register u32 *late_state_words asm("r3");

        position_base = (u8 *)0x087AFBB4;
        category_base = (u8 *)0x087C4434;
        asm volatile("" : "+r"(position_base));
        work = *(u16 *)matched_record;
        work <<= 5;
        work += (u32)category_base;
        kind = *(u8 *)(work + 0x1D);
        kind -= 1;
        work = kind << 1;
        work += kind;
        work <<= 1;
        position_entry = position_base + 2;
        work += (u32)position_entry;
        asm volatile(
            "mov %1, #0\n\t"
            "ldrsh %0, [%0, %1]"
            : "+r"(work), "=r"(zero));
        work <<= 0xB;
        state_words = (u32 *)matched_state;
        state_words[3] = work;

        work = *(u16 *)matched_record;
        work <<= 5;
        work += (u32)category_base;
        kind = *(u8 *)(work + 0x1D);
        kind -= 1;
        work = kind << 1;
        work += kind;
        work <<= 1;
        position_base += 4;
        work += (u32)position_base;
        asm volatile(
            "mov %1, #0\n\t"
            "ldrsh %0, [%0, %1]"
            : "+r"(work), "=r"(position_base));
        work <<= 0xB;
        late_state_words = (u32 *)matched_state;
        late_state_words[4] = work;
    }
    goto block_596;
block_583:
    func_080C7190(0);
    func_080E6684();
    {
        register u8 *state_load asm("r2");
        register u32 range asm("r0");
        register u8 *table_load asm("r0");
        register u32 first asm("r1");

        state_load = (u8 *)0x0202ECF4;
        range = *(u16 *)state_load;
        range -= 0x3A;
        range <<= 16;
        range >>= 16;
        if (range > 6U) {
            goto block_591;
        }
        scan_index = 0;
        table_load = (u8 *)0x087D2322;
        first = *(u16 *)table_load;
        matched_state = state_load;
        matched_table = table_load;
        if (first == 0) {
            goto block_589;
        }
    }
    {
        register u8 *scan_base asm("r2");
        register u32 sought asm("r1");

        scan_base = matched_table;
        matched_work = (u32)matched_state;
        sought = *(u16 *)(matched_work + 0x24);
loop_586:
        {
            register u32 offset asm("r0");
            register u32 category asm("r0");

            offset = scan_index << 2;
            offset += scan_index;
            matched_work = offset << 1;
            matched_record = (u8 *)(matched_work + (u32)scan_base);
            category = *(u16 *)matched_record;
            asm volatile("" : "+r"(category));
            if (sought != category) {
                goto block_588;
            }
        }
        goto block_579;
block_588:
        {
            register u32 next asm("r0");

            next = scan_index + 1;
            next <<= 24;
            scan_index = next >> 24;
        }
        {
            register u32 offset asm("r0");

            offset = scan_index << 2;
            offset += scan_index;
            offset <<= 1;
            offset += (u32)matched_table;
            if (*(u16 *)offset != 0) {
                goto loop_586;
            }
        }
    }
block_589:
    if ((u32) (u16) (M2C_FIELD((void *)0x0202ECF4, u16 *, 0) - 0x3A) > 6U) {
        goto block_591;
    }
    {
        register u32 table_or_value asm("r0");
        register u32 offset asm("r1");

        table_or_value = 0x087D2322;
        asm volatile("" : : "r"(table_or_value));
        offset = scan_index << 2;
        offset += scan_index;
        offset <<= 1;
        offset += table_or_value;
        table_or_value = *(u16 *)offset;
        if (table_or_value != 0) {
            goto block_596;
        }
    }
block_591:
    {
        register u8 *table_load asm("r0");
        register u32 first asm("r1");

        scan_index = 0;
        table_load = (u8 *)0x087D223C;
        first = *(u16 *)table_load;
        matched_table = table_load;
        if (first == 0) {
            goto block_596;
        }
    }
    {
        register u8 *state_load asm("r1");
        register u8 *scan_base asm("r2");
        register u32 sought asm("r1");

        state_load = (u8 *)0x0202ECF4;
        matched_state = state_load;
        scan_base = matched_table;
        sought = *(u16 *)(state_load + 0x22);
loop_593:
        {
            register u32 offset asm("r0");
            register u32 category asm("r3");

            offset = scan_index << 2;
            offset += scan_index;
            matched_work = offset << 1;
            matched_record = (u8 *)(matched_work + (u32)scan_base);
            category = *(u16 *)matched_record;
            if (sought != category) {
                goto block_595;
            }
        }
        goto block_581;
block_595:
        {
            register u32 next asm("r0");

            next = scan_index + 1;
            next <<= 24;
            scan_index = next >> 24;
        }
        {
            register u32 offset asm("r0");

            offset = scan_index << 2;
            offset += scan_index;
            offset <<= 1;
            offset += (u32)matched_table;
            if (*(u16 *)offset != 0) {
                goto loop_593;
            }
        }
    }
block_596:
    func_08092E0C(3);
    *(u8 *)0x02030664 = 0;
    *(u32 *)0x02021690 = 3;
    func_08096308(2, 0x20);
    goto block_643;
    }
block_598:
    {
    register u32 zero_598 asm("r4");

    {
    register u8 *transfer_598 asm("r4") = (u8 *)0x0203EBC8;
    register u32 left_ready_598 asm("r5");
    register u32 right_ready_598 asm("r4");

    func_0809AEC0(transfer_598, 4, 0x08107130);
    transfer_598 += 4;
    func_0809B00C(transfer_598, 4, 0x0810713C);
loop_599:
    left_ready_598 = func_0809AEF4();
    left_ready_598 = (u8)left_ready_598;
    right_ready_598 = func_0809B040();
    right_ready_598 = (u8)right_ready_598;
    func_080ED17C(1);
    if (left_ready_598 == 0) {
        goto loop_599;
    }
    if (right_ready_598 == 0) {
        goto loop_599;
    }
    }
    func_0809AEA0();
    func_080986B4(0);
    func_08098BB4(0x08003CE0);
    {
        register u16 *counter_base asm("r1") = D_0202F08C_BBA04;
        register u32 counter asm("r0") = counter_base[1];

        counter += 1;
        zero_598 = 0;
        counter_base[1] = counter;
    }
    temp_r0_18 = func_08094110();
    *(s8 *)0x0202169F = temp_r0_18;
    if ((temp_r0_18 << 0x18) != 0) {
        goto block_603;
    }
    func_08092E84(0x58);
    func_08098BB4(0x08003FB7);
block_603:
    func_080E6684();
    {
        register u32 *mode_slot asm("r0") = &D_02021690_BBA04;
        register u32 one asm("r1") = 1;

        *mode_slot = one;
    }
    {
        register u8 *flag_slot asm("r0") = &D_02021698_BBA04;

        *flag_slot = zero_598;
    }
    asm volatile("");
    goto block_633;
    }
block_605:
    func_08098BB4(0x08003D4E);
    func_080E6684();
    {
        register s16 *state_slot_605 asm("r1") = (s16 *)0x02032E76;
        register u32 state_value_605 asm("r4") = 0x3000;
        register u32 store_value_605 asm("r0");

        asm volatile("" : "+r"(state_value_605));
        store_value_605 = state_value_605;
        *state_slot_605 = store_value_605;
    }
    *(u32 *)0x02021690 = 0x10;
    goto block_633;
block_606:
    *(u8 *)0x02032EF8 = 0x33U;
    func_08092E74(0x33U);
    temp_r0_19 = M2C_FIELD((void *)0x0203055C, u8 *, 0);
    if (temp_r0_19 == 1) {
        goto block_614;
    }
    if ((s32) temp_r0_19 > 1) {
        goto block_611;
    }
    if (temp_r0_19 == 0) {
        goto block_613;
    }
    goto block_643;
block_611:
    if (temp_r0_19 == 2) {
        goto block_620;
    }
    goto block_643;
block_613:
    var_r0_11 = 1;
    goto block_631;
block_614:
    {
    register u32 zero_614 asm("r4");

    {
    register u8 *transfer_614 asm("r4") = (u8 *)0x0203EBC8;
    register u32 left_ready_614 asm("r5");
    register u32 right_ready_614 asm("r4");

    func_0809AEC0(transfer_614, 4, 0x0810713C);
    transfer_614 += 4;
    func_0809B00C(transfer_614, 4, 0x08107130);
loop_615:
    left_ready_614 = func_0809AEF4();
    left_ready_614 = (u8)left_ready_614;
    right_ready_614 = func_0809B040();
    right_ready_614 = (u8)right_ready_614;
    func_080ED17C(1);
    if (left_ready_614 == 0) {
        goto loop_615;
    }
    if (right_ready_614 == 0) {
        goto loop_615;
    }
    }
    func_0809AEA0();
    func_080986B4(0);
    func_08098BB4(0x08003CB8);
    {
        register u16 *counter_base asm("r1") = D_0202F08C_BBA04;
        register u32 counter asm("r0") = counter_base[0];

        counter += 1;
        zero_614 = 0;
        counter_base[0] = counter;
    }
    temp_r0_20 = func_08094110();
    *(u8 *)0x0202169F = temp_r0_20;
    if ((temp_r0_20 << 0x18) != 0) {
        goto block_619;
    }
    func_08092E84(0x58);
    func_08098BB4(0x08003FB7);
block_619:
    func_080E6684();
    {
        register u32 *mode_slot asm("r0") = &D_02021690_BBA04;
        register u32 one asm("r1") = 1;

        *mode_slot = one;
    }
    {
        register u8 *flag_slot asm("r0") = &D_02021698_BBA04;

        *flag_slot = zero_614;
    }
    goto block_633;
    }
block_620:
    func_08098BB4(0x08003D26);
    func_080E6684();
    {
        register u16 *state_slot_620 asm("r1") = (u16 *)0x02032E76;
        register u32 state_620 asm("r2") = 0x80;
        register u32 state_out_620 asm("r0");

        state_620 <<= 6;
        asm volatile("" : "+r"(state_620));
        state_out_620 = state_620;
        *state_slot_620 = state_out_620;
    }
    var_r0_12 = 0x10;
    goto block_632;
block_621:
    {
        register u8 *mode_slot_621 asm("r1") = (u8 *)0x02032EF8;
        register u32 mode_621 asm("r0") = 6;

        *mode_slot_621 = mode_621;
    }
    asm volatile("" : : : "r0");
    func_08092E74(6U);
    {
        register u8 *transfer asm("r4") = (u8 *)0x0203EBC8;
        register void *asset asm("r5") = (void *)0x08107148;

        func_0809AEC0(transfer, 4, asset);
        transfer += 4;
        func_0809B00C(transfer, 4, asset);
    }
loop_622:
    {
    register u32 left_ready asm("r5");
    register u32 right_ready asm("r4");

    left_ready = func_0809AEF4();
    right_ready = func_0809B040();
    func_080ED17C(1);
    if (left_ready == 0) {
        goto loop_622;
    }
    if (right_ready == 0) {
        goto loop_622;
    }
    }
    func_0809AEA0();
    func_08098BB4(0x08003D0A);
    func_080E6684();
    {
        register u32 *mode_slot asm("r1") = &D_02021690_BBA04;
        register u32 one asm("r0") = 1;

        *mode_slot = one;
    }
    {
        register u8 *flag_slot asm("r1") = &D_02021698_BBA04;
        register u32 zero asm("r0") = 0;

        *flag_slot = zero;
    }
    goto block_633;
block_625:
    {
    register s32 *mode_slot_625 asm("r1");
    register s32 mode_625 asm("r0");

    if (M2C_FIELD((void *)0x0203055C, u8 *, 0) != 0) {
        goto block_627;
    }
    func_080C7190(2);
    mode_slot_625 = (s32 *)0x02021690;
    mode_625 = 3;
    goto block_628;
block_627:
    func_080986B4(0);
    func_08098BB4(0x08003D78);
    {
        register u16 *state_slot_627 asm("r1") = (u16 *)0x02032E76;
        register u32 state_value_627 asm("r3") = 0x3000;
        register u32 store_value_627 asm("r0");

        asm volatile("" : "+r"(state_value_627));
        store_value_627 = state_value_627;
        *state_slot_627 = store_value_627;
    }
    mode_slot_625 = (s32 *)0x02021690;
    mode_625 = 0x10;
block_628:
    *mode_slot_625 = mode_625;
    func_080E6684();
    goto block_633;
    }
block_630:
    var_r0_11 = 3;
block_631:
    func_080C7190(var_r0_11);
    func_080E6684();
    var_r0_12 = 3;
block_632:
    *mode_base = var_r0_12;
block_633:
    var_r0_8 = 2;
block_634:
    func_08096308(var_r0_8, 8);
    goto block_643;
block_635:
    func_080BB940();
    {
        register struct ViewStateBBA04 *view asm("r1") =
            (struct ViewStateBBA04 *)0x030033C4;

        view->center_x = 0x78;
        view->center_y = 0x58;
        view->size = 0x80;
        view->flags = 0x20000;
    }
    func_080BB224(0, 0U, 0U, 1);
    func_08093AE8(0x0202F094, 1);
    *(u8 *)0x03000074 = (u8) (*(u8 *)0x03000074 | 1);
    *(u32 *)0x02030558 = 0xFF20U;
    goto block_643;
block_637:
    func_080BB940();
    func_08093AE8(0x0202F094, 1);
    *(u8 *)0x03000074 = (u8) (*(u8 *)0x03000074 | 1);
    var_r0_5 = 0xFF20;
block_638:
    {
        register s32 *state_slot_638 asm("r4") = temp_r0;

        *state_slot_638 = var_r0_5;
    }
    goto block_643;
block_640:
    if (*(u8 *)0x02030664 != 2) {
        goto block_642;
    }
    {
        register u32 zero_640 asm("r0") = 0;
        register s32 *state_slot_640 asm("r1") = temp_r0;

        *state_slot_640 = zero_640;
    }
    goto loop_647;
block_642:
    func_080ED17C(1);
block_643:
    {
        register u32 exit_guard asm("r2") = 0;

        if (exit_guard != 0) {
            goto loop_647;
        }
    }
    {
        register s32 mode asm("r0");
        register s32 *saved_mode_base asm("r6");

        mode_base = (s32 *)0x02021690;
        mode = *mode_base;
        saved_mode_base = mode_base;
        if (mode == 9) {
            goto loop_1;
        }
    }
    goto loop_647;
block_646:
    func_08093B7C();
    func_080BB764();
    func_080ED17C(1);
loop_647:
    if ((func_0809669C() << 0x18) == 0) {
        goto block_646;
    }
    func_08092E0C(7);
    func_08093B54();
    *(u8 *)0x03000074 = 0U;
    func_0809534C();
    *(u8 *)0x03000075 = 1;
    *(u8 *)0x0300603D = 1;
    if (*(u8 *)0x02030664 == 1) {
        goto block_651;
    }
    if (*(u32 *)0x02021690 == 0xA) {
        goto block_651;
    }
    func_08092EA0(*(u8 *)0x02032EF8);
block_651:
    if (*(u8 *)0x02030664 != 2) {
        goto block_656;
    }
    temp_r0_21 = *(u32 *)0x02021690;
    if (temp_r0_21 == 9) {
        goto block_656;
    }
    if (temp_r0_21 == 0xA) {
        goto block_656;
    }
    if (temp_r0_21 == 0xB) {
        goto block_656;
    }
    *(u8 *)0x02030664 = 1U;
    func_080ED17C(1);
block_656:
    return;
}
