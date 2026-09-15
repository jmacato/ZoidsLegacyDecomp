#include "m2c_prelude.h"
#define NULL ((void *)0)

struct CategoryInfo {
    u8 pad00[0x1C];
    u8 has_data;
    u8 kind;
    u8 display;
    u8 pad1F;
};

struct LookupEntry {
    u16 category;
    u16 x;
    u16 y;
    u16 state_x;
    u16 state_y;
};

struct GameState {
    u16 category;
    u8 variant;
    u8 subvariant;
    s32 x;
    s32 y;
    s32 camera_x;
    s32 camera_y;
    s32 state_x;
    s32 state_y;
    u8 animation;
    u8 kind;
    u8 display;
    u8 pad1F[3];
    u16 lookup22;
    u16 lookup24;
    u8 pad26[0x16A];
    u32 unlocked[8];
};

struct Actor {
    u32 flags;
    u8 kind;
    u8 pad05[3];
    s32 x;
    s32 y;
    u8 pad10[0xA];
    u8 animation;
    u8 attributes;
    u8 display;
};

struct SceneFlags {
    u8 pad0;
    u8 field1;
    u8 pad2[3];
    u8 field5;
};

extern struct GameState D_0202ECF4;
extern struct CategoryInfo D_087C4434[];
extern struct LookupEntry D_087D223C[];
extern struct LookupEntry D_087D2322[];
extern u8 D_020324B0;
extern u8 D_020324B1;
extern u8 D_020324B2;
extern u16 D_020324B4;
extern u8 D_020324B6;
extern u8 D_020324B8;
extern u8 D_020324B9;
extern u8 D_020324BA;
extern volatile s32 D_02021690;
extern u8 D_02030664;
extern u8 D_02030665;
extern u8 D_02030667;
extern s32 D_02032494[2];
extern struct Actor *D_02032990;
extern struct Actor *D_02032994;
extern s32 D_03000054[];
extern s16 D_03005F74;
extern s16 D_03005F76;
extern u8 D_0203259E;
extern u8 D_020281F0[];
extern u8 D_020218E4[];
extern struct SceneFlags D_0203055C;
extern s32 D_02030558;
extern u8 D_02032A84;
extern u8 D_02032A85;
extern u32 D_087A0BF8[];

asm(".set D_020324BA, 0x020324BA\n"
    ".set D_020324B4, 0x020324B4\n"
    ".set D_020324B6, 0x020324B6\n"
    ".set D_02030665, 0x02030665\n"
    ".set D_02032994, 0x02032994\n"
    ".set D_0203259E, 0x0203259E\n"
    ".set D_020281F0, 0x020281F0\n"
    ".set D_02032A84, 0x02032A84\n"
    ".set D_02032A85, 0x02032A85\n"
    ".set D_03005F74, 0x03005F74\n"
    ".set D_03005F76, 0x03005F76\n"
    ".set D_087D223C, 0x087D223C\n"
    ".set D_087D2322, 0x087D2322");

M2C_UNK func_08092D8C(s32, M2C_UNK);                /* extern */
M2C_UNK func_08092D9C(s32, M2C_UNK, u16);           /* extern */
M2C_UNK func_08092E0C(s32);                         /* extern */
M2C_UNK func_08092E74(u8);                          /* extern */
M2C_UNK func_08092E84(s32);                         /* extern */
M2C_UNK func_08092EA0(u8);                          /* extern */
M2C_UNK func_08094330();                            /* extern */
M2C_UNK func_08096308(s32, s32);                    /* extern */
s32 func_0809669C();                                /* extern */
M2C_UNK func_080972C8();                            /* extern */
M2C_UNK func_08098BB4(M2C_UNK);                     /* extern */
M2C_UNK func_0809D938(u16, s32, s32);               /* extern */
M2C_UNK func_0809E204(u16, s32, s32, s32);          /* extern */
M2C_UNK func_0809E22C();                            /* extern */
M2C_UNK func_0809E6E0();                            /* extern */
s32 func_0809E72C();                                /* extern */
M2C_UNK func_0809EAE0();                            /* extern */
M2C_UNK func_0809EB24();                            /* extern */
M2C_UNK func_0809EB38();                            /* extern */
M2C_UNK func_0809F850();                            /* extern */
M2C_UNK func_0809FCB0();                            /* extern */
M2C_UNK func_0809FD3C(u16, s32);                    /* extern */
M2C_UNK func_080A9888();                            /* extern */
void *func_080A9D78(u8, u8, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_080A9EBC();                            /* extern */
M2C_UNK func_080B35D4(s32);                         /* extern */
M2C_UNK func_080E5FA8(s32, u8);                     /* extern */
M2C_UNK func_080E6090(s32);                         /* extern */
M2C_UNK func_080ECD34(M2C_UNK, M2C_UNK);            /* extern */
M2C_UNK func_080ED17C(s32);                         /* extern */

void sub_0809EC20(void) {
    volatile u32 sp10;
    u8 old_kind;
    s32 temp_r0_10;
    s32 temp_r0_11;
    s32 temp_r0_12;
    s32 temp_r0_9;
    s32 temp_r2_2;
    s32 temp_r2_6;
    s32 temp_r3;
    s32 temp_r4_2;
    s32 temp_r4_3;
    s32 var_r0_5;
    s32 var_r0_6;
    u16 temp_r0;
    u16 temp_r0_2;
    u16 temp_r0_3;
    u16 temp_r0_4;
    u16 temp_r1;
    u16 temp_r1_7;
    u16 temp_r5;
    u32 var_r5_5;
    u8 temp_r0_5;
    u8 temp_r0_6;
    u8 temp_r1_6;
    u8 temp_r3_2;
    u8 temp_r4_5;
    register u32 var_r1 asm("r1");
    u8 var_r5;
    u8 var_r5_2;
    u8 var_r5_3;
    u8 var_r5_4;
    u8 var_r5_6;
    u8 var_r5_7;
    u8 var_r5_8;
    u8 var_r6;
    register u32 var_r9 asm("r9");
    register u32 zero asm("r10");
    register struct CategoryInfo *category_source asm("r0");
    register struct CategoryInfo *category_table asm("r12");
    register struct GameState *state_source asm("r1");
    register void *source_r2 asm("r2");
    register u16 *selection asm("r3");
    register u32 lookup_i asm("r5");
    register u32 lookup_r0 asm("r0");
    register u32 lookup_r1 asm("r1");
    register u8 *hold_r8 asm("r8");
    u8 *hold_r7;
    register u32 lookup_scan asm("r2");
    register u32 entity_r0 asm("r0");
    register u32 entity_r1 asm("r1");
    register u32 entity_r2 asm("r2");
    register u32 entity_r3 asm("r3");
    register u8 *entity_r6 asm("r6");
    register u8 *entity_ip asm("r12");
    register struct CategoryInfo *display_table asm("r4");
    register struct GameState *display_state1 asm("r2");
    register struct GameState *display_state2 asm("r3");
    register u32 kind_copy asm("r6");
    register u32 object_r0 asm("r0");
    register u32 object_r1 asm("r1");
    register u32 object_r2 asm("r2");
    register u32 object_r3 asm("r3");
    register u32 object_r4 asm("r4");
    void *spawned;
    register struct Actor **spawn_slot asm("r1");
    void *temp_r0_7;
    void *temp_r0_8;
    void *temp_r1_2;
    void *temp_r1_3;
    void *temp_r1_4;
    void *temp_r1_5;
    void *temp_r1_8;
    void *temp_r1_9;
    void *temp_r2;
    void *temp_r2_10;
    void *temp_r2_4;
    void *temp_r2_7;
    void *temp_r2_8;
    void *temp_r2_9;
    void *temp_r4_4;

    D_020324B8 = 0;
    D_020324B9 = 0;
    D_020324BA = 0;
    if (D_02021690 != 3) {
        goto block_180;
    }
    zero = 0;
loop_2:
    D_020324B0 = 1;
    D_020324B1 = 1;
    func_08094330();
    if (D_02030664 != 0) {
        goto block_14;
    }
    if (D_020324B2 == 0) {
        goto block_14;
    }
    func_080A9888();
    if (D_020324B2 != 2) {
        goto block_15;
    }
    lookup_i = 0;
    hold_r7 = (u8 *)&D_0202ECF4;
    entity_r1 = 68;
    entity_r1 += (u32)hold_r7;
    hold_r8 = (u8 *)entity_r1;
loop_6:
    entity_r0 = lookup_i << 2;
    entity_r0 += lookup_i;
    entity_r3 = entity_r0 << 2;
    entity_r0 = (u32)hold_r7;
    entity_r0 += 56;
    entity_r6 = (u8 *)(entity_r3 + entity_r0);
    entity_r0 = *(u32 *)entity_r6;
    entity_r1 = 1;
    entity_r0 &= entity_r1;
    if (entity_r0 == 0) {
        goto block_11;
    }
    entity_r2 = entity_r3 + (u32)hold_r7;
    entity_ip = (u8 *)entity_r2;
    entity_r0 = *(u16 *)(entity_r2 + 62);
    if (entity_r0 == 0) {
        goto block_11;
    }
    if (entity_r0 == 8) {
        goto block_11;
    }
    if (entity_r0 == 5) {
        goto block_11;
    }
    entity_r0 = (u32)entity_ip;
    entity_r0 += 60;
    entity_r0 = *(volatile u8 *)entity_r0;
    entity_r1 = (u32)entity_ip;
    entity_r1 += 61;
    entity_r1 = *(volatile u8 *)entity_r1;
    entity_r2 = (u32)hold_r7;
    entity_r2 += 64;
    entity_r2 = entity_r3 + entity_r2;
    entity_r2 = *(u32 *)entity_r2;
    entity_r3 += (u32)hold_r8;
    entity_r3 = *(u32 *)entity_r3;
    func_080A9D78(entity_r0, entity_r1, entity_r2, entity_r3,
        (s32)*(u8 *)(entity_ip + 72), *(s32 *)entity_r6,
        (s32)(entity_r6 = entity_ip, *(u16 *)(entity_r6 + 62)), zero);
block_11:
    lookup_r0 = lookup_i + 1;
    lookup_i = (u8)lookup_r0;
    if (lookup_i <= 0xDU) {
        goto loop_6;
    }
    goto block_15;
block_14:
    func_080A9EBC();
block_15:
    func_080ECD34(0x0832BB4C, 0x06017640);
    if (D_020324B2 != 0) {
        goto block_17;
    }
    goto block_47;
block_17:
    category_source = D_087C4434;
    source_r2 = &D_020324B4;
    var_r6 = category_source[*(u16 *)source_r2].kind;
    category_table = category_source;
    selection = source_r2;
    if (var_r6 != 0) {
        goto block_19;
    }
    goto block_42;
block_19:
    state_source = &D_0202ECF4;
    old_kind = category_table[state_source->category].kind;
    source_r2 = state_source;
    asm volatile("" : "+r"(source_r2));
    var_r9 = (u32)source_r2;
    if (old_kind != var_r6) {
        goto block_22;
    }
    if (var_r6 == 0x1D) {
        goto block_22;
    }
    if ((u32) (u8) (var_r6 - 0x21) > 9U) {
        goto block_41;
    }
block_22:
    if (D_02030664 != 0) {
        goto block_41;
    }
    object_r4 = var_r9;
    if (((struct GameState *)object_r4)->category != 0x40) {
        goto block_25;
    }
    if (*selection == 0x3F) {
        goto block_26;
    }
block_25:
    {
        register s32 word_offset asm("r2");
        register u32 work asm("r0");
        register u32 bit asm("r1");

        word_offset = var_r6 >> 5;
        word_offset <<= 2;
        work = 200;
        work <<= 1;
        work += var_r9;
        word_offset += work;
        work = 0x1F;
        work &= var_r6;
        bit = 1;
        bit <<= work;
        work = *(u32 *)word_offset;
        work |= bit;
        *(u32 *)word_offset = work;
    }
block_26:
    state_source = (struct GameState *)var_r9;
    if ((u32)(u16)(state_source->category - 0x3A) <= 6U) {
        goto block_33;
    }
    lookup_i = 0;
    lookup_r0 = 0x087D223C;
    lookup_r1 = *(u16 *)lookup_r0;
    hold_r8 = (u8 *)lookup_r0;
    if (lookup_r1 == 0) {
        goto block_42;
    }
    lookup_scan = (u32)hold_r8;
    lookup_r0 = (u32)&D_020324B4;
    lookup_r1 = *(u16 *)lookup_r0;
loop_29:
    lookup_r0 = lookup_i << 2;
    lookup_r0 += lookup_i;
    lookup_r0 <<= 1;
    lookup_r0 = *(u16 *)(lookup_r0 + lookup_scan);
    if (lookup_r0 == lookup_r1) {
        goto block_39;
    }
    lookup_r0 = lookup_i + 1;
    lookup_i = (u8)lookup_r0;
    lookup_r0 = lookup_i << 2;
    lookup_r0 += lookup_i;
    lookup_r0 <<= 1;
    lookup_r0 += (u32)hold_r8;
    lookup_r0 = *(u16 *)lookup_r0;
    if (lookup_r0 != 0) {
        goto loop_29;
    }
    goto block_42;
block_33:
    lookup_i = 0;
    lookup_r0 = 0x087D2322;
    lookup_r1 = *(u16 *)lookup_r0;
    hold_r7 = (u8 *)lookup_r0;
    if (lookup_r1 == 0) {
        goto block_42;
    }
    lookup_scan = (u32)hold_r7;
    lookup_r0 = (u32)&D_020324B4;
    lookup_r1 = *(u16 *)lookup_r0;
loop_35:
    lookup_r0 = lookup_i << 2;
    lookup_r0 += lookup_i;
    lookup_r0 <<= 1;
    lookup_r0 = *(u16 *)(lookup_r0 + lookup_scan);
    if (lookup_r0 == lookup_r1) {
        goto block_40;
    }
    lookup_r0 = lookup_i + 1;
    lookup_i = (u8)lookup_r0;
    lookup_r0 = lookup_i << 2;
    lookup_r0 += lookup_i;
    lookup_r0 <<= 1;
    lookup_r0 += (u32)hold_r7;
    lookup_r0 = *(u16 *)lookup_r0;
    if (lookup_r0 != 0) {
        goto loop_35;
    }
    goto block_42;
block_39:
    source_r2 = (void *)var_r9;
    ((struct GameState *)source_r2)->lookup22 = (u16)lookup_r0;
    goto block_42;
block_40:
    object_r4 = var_r9;
    ((struct GameState *)object_r4)->lookup24 = (u16)lookup_r0;
    goto block_42;
block_41:
    var_r6 = 0;
block_42:
    object_r4 = (u32)&D_0202ECF4;
    ((struct GameState *)object_r4)->category = *selection;
    D_02032494[0] = ((struct GameState *)object_r4)->x;
    D_02032494[1] = ((struct GameState *)object_r4)->y;
    lookup_r1 = ((struct GameState *)object_r4)->category;
    temp_r0_5 = category_table[lookup_r1].has_data;
    var_r9 = 1;
    if (temp_r0_5 == 0) {
        goto block_48;
    }
    object_r3 = ((struct GameState *)object_r4)->variant;
    var_r9 = object_r3;
    if (((struct GameState *)object_r4)->subvariant == 0) {
        goto block_48;
    }
    if (lookup_r1 != 0) {
        goto block_48;
    }
    if (object_r3 == 0x6C) {
        goto block_48;
    }
    func_080A9D78(0x6CU, 0xDU,
        ((struct GameState *)object_r4)->state_x,
        ((struct GameState *)object_r4)->state_y,
        (s32)((struct GameState *)object_r4)->kind,
        2, 0xFF, (s32)lookup_r1);
    goto block_48;
block_47:
    var_r6 = 0;
block_48:
    if (D_02030664 != 0) {
        goto block_54;
    }
    if (D_020324B2 == 0) {
        goto block_52;
    }
    func_0809FCB0();
    object_r4 = (u32)&D_0202ECF4;
    temp_r0_4 = *(u16 *)object_r4;
    func_0809FD3C(temp_r0_4, D_087A0BF8[temp_r0_4]);
    goto block_53;
block_51:
    {
        register volatile u32 *outgoing asm("sp");

        entity_r6 = (u8 *)&D_0202ECF4;
        object_r2 = *(u32 *)(entity_r6 + 4);
        object_r3 = *(u32 *)(entity_r6 + 8);
        object_r0 = *(u8 *)(entity_r6 + 0x1C);
        outgoing[0] = object_r0;
        object_r0 = zero;
        outgoing[1] = object_r0;
        object_r0 = 8;
        outgoing[2] = object_r0;
        object_r1 = zero;
        outgoing[3] = object_r1;
        object_r0 = 0x4B;
        object_r1 = 0xD;
        spawned = ((void *(*)())func_080A9D78)(object_r0, object_r1,
            object_r2, object_r3);
        spawn_slot = &D_02032994;
        *spawn_slot = spawned;
        goto block_66;
    }
block_52:
    func_0809F850();
block_53:
    object_r0 = 3;
    object_r1 = 0x080A67E5;
    func_08092D8C(object_r0, object_r1);
    display_table = D_087C4434;
    display_state1 = &D_0202ECF4;
    func_08092E74(display_table[display_state1->category].display);
    object_r1 = (u32)&D_02030667;
    display_state2 = &D_0202ECF4;
    *(u8 *)object_r1 = display_table[display_state2->category].display;
    func_080ED17C(1);
block_54:
    if (var_r6 == 0) {
        goto block_56;
    }
    object_r4 = (u32)&D_0202ECF4;
    object_r2 = *(volatile u16 *)object_r4;
    object_r0 = 7;
    object_r1 = 0x0809E8CD;
    func_08092D9C(object_r0, object_r1, object_r2);
block_56:
    lookup_i = (u32)&D_0202ECF4;
    func_0809D938(((struct GameState *)lookup_i)->category,
        D_02032494[0], D_02032494[1]);
    object_r4 = D_02030664;
    if (object_r4 == 0) {
        goto block_58;
    }
    goto block_76;
block_58:
    if (D_020324B2 == 0) {
        goto block_72;
    }
    var_r1 = 0;
    kind_copy = var_r9;
    asm volatile("" : "+r"(kind_copy));
    if (kind_copy != 0x6C) {
        goto block_61;
    }
    var_r1 = 0xD;
block_61:
    spawned = ((void *(*)())func_080A9D78)(var_r9, var_r1,
        ((struct GameState *)lookup_i)->x,
        ((struct GameState *)lookup_i)->y,
        (s32)((struct GameState *)lookup_i)->animation,
        (s32)object_r4, (s32)object_r4, (s32)object_r4);
    spawn_slot = &D_02032990;
    *spawn_slot = spawned;
    {
        register u32 kind_test asm("r2") = var_r9;

        asm volatile("" : "+r"(kind_test));
        if (kind_test != 1) {
            goto block_66;
        }
    }
    lookup_i = 1;
    object_r3 = (u32)D_020218E4;
    object_r2 = 0x5A94;
loop_63:
    object_r0 = lookup_i << 6;
    object_r1 = object_r0 + object_r3;
    object_r0 = object_r1 + object_r2;
    if (*(u8 *)object_r0 != 1) {
        goto block_65;
    }
    object_r4 = 0x5AC5;
    object_r0 = object_r1 + object_r4;
    if (*(u8 *)object_r0 == 1) {
        goto block_51;
    }
block_65:
    object_r0 = lookup_i + 1;
    lookup_i = (u8)object_r0;
    if (lookup_i <= 0x34U) {
        goto loop_63;
    }
block_66:
    func_08096308(0xD, 0);
    object_r4 = (u32)&D_03005F74;
    entity_r6 = (u8 *)&D_02032990;
    object_r2 = *(u32 *)entity_r6;
    entity_r3 = (u32)D_03000054;
    entity_r1 = *(u32 *)(object_r2 + 8);
    entity_r0 = *(u32 *)entity_r3;
    entity_r0 = entity_r1 - entity_r0;
    if ((s32)entity_r0 >= 0) {
        goto block_68;
    }
    entity_r0 += 0xFF;
block_68:
    *(s16 *)object_r4 = (s16)((s32)entity_r0 >> 8);
    object_r4 = (u32)&D_03005F76;
    entity_r1 = *(u32 *)(object_r2 + 0xC);
    entity_r0 = *(u32 *)(entity_r3 + 4);
    entity_r0 = entity_r1 - entity_r0;
    if ((s32)entity_r0 >= 0) {
        goto block_70;
    }
    entity_r0 += 0xFF;
block_70:
    *(s16 *)object_r4 = (s16)((s32)entity_r0 >> 8);
    goto block_76;
block_72:
    temp_r2_4 = ((s32)D_02032990);
    M2C_FIELD(temp_r2_4, s32 *, 0) = (s32) (M2C_FIELD(temp_r2_4, s32 *, 0) & ~2);
    if (D_020324B6 != 0) {
        goto block_75;
    }
    func_08096308(0xF, 0);
    goto block_76;
block_74:
    object_r0 = (u32)&D_020324B6;
    object_r1 = zero;
    *(volatile u8 *)object_r0 = object_r1;
    goto block_171;
block_75:
    func_08096308(7, 0);
block_76:
    object_r0 = 2;
    object_r1 = 0x0809E1CD;
    func_08092D8C(object_r0, object_r1);
    {
        u32 clear_address;
        register u32 clear_r2 asm("r2");

        clear_address = (u32)&D_020324B2;
        clear_r2 = zero;
        asm volatile("" : "+r"(clear_r2) : "r"(clear_address));
        *(u8 *)clear_address = clear_r2;
        clear_address = (u32)&D_0203259E;
        asm volatile("" : "+r"(clear_r2) : "r"(clear_address));
        *(u8 *)clear_address = clear_r2;
    }
    func_0809E6E0();
    if (D_02021690 == 3) {
        goto block_78;
    }
    goto block_171;
block_78:
    object_r3 = (u32)&D_0202ECF4;
    asm volatile("" : "+r"(object_r3));
    hold_r8 = (u8 *)object_r3;
loop_79:
    object_r4 = (u32)hold_r8;
    if (((struct GameState *)object_r4)->category == 0) {
        goto block_81;
    }
    goto block_89;
block_81:
    if (4 & D_020324B0) {
        goto block_83;
    }
    goto block_89;
block_83:
    if (D_020324B8 == 0) {
        goto block_85;
    }
    goto block_91;
block_85:
    func_0809EAE0();
    goto block_91;
block_86:
    {
        register u32 arg0 asm("r0"); register u32 arg1 asm("r1"); register u32 arg2 asm("r2");
        arg0 = *(u16 *)entity_r6; asm volatile("" : : "r"(arg0));
        arg1 = (u32)hold_r7 + 2; arg1 = object_r4 + arg1; arg1 = *(u16 *)arg1; arg1 <<= 0xB;
        arg2 = (u32)hold_r7 + 4; arg2 = object_r4 + arg2; arg2 = *(u16 *)arg2; arg2 <<= 0xB;
        func_0809E204(arg0, arg1, arg2, 0);
    }
    {
        register u32 value asm("r0"); register u8 *state_view asm("r1");
        value = (u32)hold_r7 + 6; value = object_r4 + value; value = *(u16 *)value; value <<= 0xB;
        state_view = (u8 *)var_r9; *(u32 *)(state_view + 0x14) = value;
        value = (u32)hold_r7; value += 8; value = object_r4 + value; value = *(u16 *)value; value <<= 0xB;
        *(u32 *)(state_view + 0x18) = value;
    }
    {
        register u8 *position_base asm("r1");
        register u8 *category_base asm("r2");
        register u32 work asm("r0"); register u32 kind asm("r1");
        register u32 first_zero asm("r3"); register u32 *state_words asm("r4");
        register u8 *second_position asm("r6"); register u32 second_zero asm("r1");
        work = *(u16 *)entity_r6; work <<= 5;
        category_base = (u8 *)0x087C4434;
        asm volatile("" : "+r"(category_base));
        work += (u32)category_base;
        kind = *(u8 *)(work + 0x1D); kind -= 1; work = kind << 1; work += kind; work <<= 1;
        position_base = (u8 *)0x087AFBB4;
        asm volatile("" : "+r"(position_base));
        position_base += 2; work += (u32)position_base;
        asm volatile("mov %1, #0\n\tldrsh %0, [%0, %1]" : "+r"(work), "=r"(first_zero));
        work <<= 0xB; state_words = (u32 *)var_r9; state_words[3] = work;
        work = *(u16 *)entity_r6; work <<= 5; work += (u32)category_base;
        kind = *(u8 *)(work + 0x1D); kind -= 1; work = kind << 1; work += kind; work <<= 1;
        second_position = (u8 *)0x087AFBB8;
        asm volatile("" : "+r"(second_position));
        work += (u32)second_position;
        asm volatile("mov %1, #0\n\tldrsh %0, [%0, %1]" : "+r"(work), "=r"(second_zero));
        work <<= 0xB; state_words[4] = work;
    }
    goto block_122;
block_87:
    {
        register u32 arg0 asm("r0"); register u32 arg1 asm("r1"); register u32 arg2 asm("r2");
        arg0 = *(u16 *)entity_r6; asm volatile("" : : "r"(arg0));
        arg1 = (u32)hold_r8 + 2; arg1 = object_r4 + arg1; arg1 = *(u16 *)arg1; arg1 <<= 0xB;
        arg2 = (u32)hold_r8 + 4; arg2 = object_r4 + arg2; arg2 = *(u16 *)arg2; arg2 <<= 0xB;
        func_0809E204(arg0, arg1, arg2, 0);
    }
    {
        register u32 value asm("r0");
        value = (u32)hold_r8 + 6; value = object_r4 + value; value = *(u16 *)value; value <<= 0xB;
        *(u32 *)(hold_r7 + 0x14) = value;
        value = (u32)hold_r8; value += 8; value = object_r4 + value; value = *(u16 *)value; value <<= 0xB;
        *(u32 *)(hold_r7 + 0x18) = value;
    }
    {
        register u8 *position_base asm("r1");
        register u8 *category_base asm("r2");
        register u32 work asm("r0"); register u32 kind asm("r1");
        register u32 first_zero asm("r3"); register u8 *second_position asm("r4");
        register u32 second_zero asm("r6");
        work = *(u16 *)entity_r6; work <<= 5;
        category_base = (u8 *)0x087C4434;
        asm volatile("" : "+r"(category_base));
        work += (u32)category_base;
        kind = *(u8 *)(work + 0x1D); kind -= 1; work = kind << 1; work += kind; work <<= 1;
        position_base = (u8 *)0x087AFBB4;
        asm volatile("" : "+r"(position_base));
        position_base += 2; work += (u32)position_base;
        asm volatile("mov %1, #0\n\tldrsh %0, [%0, %1]" : "+r"(work), "=r"(first_zero));
        work <<= 0xB; *(u32 *)(hold_r7 + 0xC) = work;
        work = *(u16 *)entity_r6; work <<= 5; work += (u32)category_base;
        kind = *(u8 *)(work + 0x1D); kind -= 1; work = kind << 1; work += kind; work <<= 1;
        second_position = (u8 *)0x087AFBB8;
        asm volatile("" : "+r"(second_position));
        work += (u32)second_position;
        asm volatile("mov %1, #0\n\tldrsh %0, [%0, %1]" : "+r"(work), "=r"(second_zero));
        work <<= 0xB; *(u32 *)(hold_r7 + 0x10) = work;
    }
    goto block_129;
block_89:
    if (D_020324B8 == 0) {
        goto block_91;
    }
    func_0809EB24();
block_91:
    if (D_02030664 == 0) {
        goto block_93;
    }
    goto block_146;
block_93:
    object_r0 = (u32)&D_02030665;
    object_r1 = *(u8 *)object_r0;
    object_r4 = object_r0;
    if (object_r1 != 0) {
        goto block_95;
    }
    goto block_146;
block_95:
    lookup_i = 1;
    object_r3 = (u32)D_020218E4;
    object_r2 = object_r3;
loop_96:
    object_r0 = lookup_i << 6;
    object_r1 = object_r0 + object_r2;
    kind_copy = 0x5A94;
    object_r0 = object_r1 + kind_copy;
    object_r0 = *(u8 *)object_r0;
    if (object_r0 == 0) {
        goto block_101;
    }
    if (object_r0 != 1) {
        goto block_99;
    }
    sp10 = lookup_i;
block_99:
    object_r0 = 0x5A95;
    object_r1 += object_r0;
    object_r0 = *(u8 *)object_r1;
    if (object_r0 == 0) {
        goto block_101;
    }
    object_r1 = object_r0;
    object_r0 = object_r1 << 3;
    object_r0 -= object_r1;
    object_r0 <<= 4;
    object_r0 += object_r2;
    object_r1 = *(u16 *)(object_r0 + 8);
    object_r0 = 8;
    object_r0 &= object_r1;
    if (object_r0 == 0) {
        goto block_102;
    }
block_101:
    object_r0 = lookup_i + 1;
    lookup_i = (u8)object_r0;
    if (lookup_i <= 0x34U) {
        goto loop_96;
    }
block_102:
    if (lookup_i == 0x35) {
        goto block_104;
    }
    goto block_131;
block_104:
    {
        register u32 slot_r1 asm("r1") = (u32)&D_02032990;
        register u32 actor_r0 asm("r0");

        asm volatile("" : "+r"(slot_r1));
        actor_r0 = *(u32 *)slot_r1;
        asm volatile("" : "+r"(actor_r0));
        temp_r0_7 = (void *)actor_r0;
    }
    M2C_FIELD(temp_r0_7, s32 *, 0) = (s32) (M2C_FIELD(temp_r0_7, s32 *, 0) | 2);
    {
        register u32 selected_r2 asm("r2") = sp10;

        asm volatile("" : "+r"(selected_r2));
        lookup_i = selected_r2 << 6;
    }
    goto loop_106;
block_105:
    func_080ED17C(1);
loop_106:
    if ((func_0809669C() << 0x18) == 0) {
        goto block_105;
    }
    D_020324BA = 1;
    func_08098BB4(0x080177ED);
    func_08098BB4(0x08017940);
    {
        register u32 clear_r3 asm("r3") = zero;

        asm volatile("" : "+r"(clear_r3));
        D_020324BA = clear_r3;
    }
    func_08098BB4(0x080177FA);
    func_080972C8();
    func_08096308(0xE, 0);
    object_r4 = (u32)&D_03005F74;
    entity_r6 = (u8 *)&D_02032990;
    object_r2 = *(u32 *)entity_r6;
    entity_r3 = (u32)D_03000054;
    entity_r1 = *(u32 *)(object_r2 + 8);
    entity_r0 = *(u32 *)entity_r3;
    entity_r0 = entity_r1 - entity_r0;
    if ((s32)entity_r0 >= 0) {
        goto block_109;
    }
    entity_r0 += 0xFF;
block_109:
    *(s16 *)object_r4 = (s16)((s32)entity_r0 >> 8);
    object_r4 = (u32)&D_03005F76;
    entity_r1 = *(u32 *)(object_r2 + 0xC);
    entity_r0 = *(u32 *)(entity_r3 + 4);
    entity_r0 = entity_r1 - entity_r0;
    if ((s32)entity_r0 >= 0) {
        goto block_111;
    }
    entity_r0 += 0xFF;
block_111:
    *(s16 *)object_r4 = (s16)((s32)entity_r0 >> 8);
    goto loop_113;
block_112:
    func_080ED17C(1);
loop_113:
    if ((func_0809669C() << 0x18) == 0) {
        goto block_112;
    }
    object_r2 = (u32)D_020218E4;
    object_r4 = lookup_i + object_r2;
    object_r0 = 0x5A95;
    asm volatile("" : "+r"(object_r0));
    object_r4 += object_r0;
    object_r1 = *(u8 *)object_r4;
    object_r0 = object_r1 << 3;
    object_r0 -= object_r1;
    object_r0 <<= 4;
    object_r2 += 4;
    object_r0 += object_r2;
    func_080E6090(object_r0);
    object_r1 = *(volatile u8 *)object_r4;
    object_r0 = 1;
    func_080E5FA8(object_r0, object_r1);
    if (D_020324B8 == 0) {
        goto block_116;
    }
    func_0809EB38();
block_116:
    func_08092E0C(2);
    object_r1 = (u32)hold_r8;
    asm volatile("" : "+r"(object_r1));
    if ((u32) (u16) (((struct GameState *)object_r1)->category - 0x3A) > 6U) {
        goto block_124;
    }
    lookup_i = 0;
    lookup_r0 = (u32)D_087D2322;
    lookup_r1 = *(u16 *)lookup_r0;
    object_r2 = (u32)&D_0202ECF4;
    asm volatile("" : "+r"(object_r2));
    var_r9 = object_r2;
    hold_r7 = (u8 *)lookup_r0;
    if (lookup_r1 == 0) {
        goto block_122;
    }
    lookup_scan = (u32)hold_r7;
    object_r3 = (u32)&D_0202ECF4;
    lookup_r1 = *(u16 *)(object_r3 + 0x24);
loop_119:
    lookup_r0 = lookup_i << 2; lookup_r0 += lookup_i;
    object_r4 = lookup_r0 << 1;
    entity_r6 = (u8 *)(object_r4 + lookup_scan);
    lookup_r0 = *(u16 *)entity_r6;
    asm volatile("" : "+r"(lookup_r0));
    if (lookup_r1 != lookup_r0) {
        goto block_121;
    }
    goto block_86;
block_121:
    lookup_r0 = lookup_i + 1; lookup_r0 <<= 24; lookup_i = lookup_r0 >> 24;
    lookup_r0 = lookup_i << 2; lookup_r0 += lookup_i; lookup_r0 <<= 1;
    lookup_r0 += (u32)hold_r7;
    if (*(u16 *)lookup_r0 != 0) {
        goto loop_119;
    }
block_122:
    object_r1 = (u32)hold_r8;
    asm volatile("" : "+r"(object_r1));
    if ((u32) (u16) (((struct GameState *)object_r1)->category - 0x3A) > 6U) {
        goto block_124;
    }
    lookup_r0 = (u32)D_087D2322;
    lookup_r1 = lookup_i << 2; lookup_r1 += lookup_i; lookup_r1 <<= 1;
    lookup_r1 += lookup_r0; lookup_r0 = *(u16 *)lookup_r1;
    if (lookup_r0 != 0) {
        goto block_129;
    }
block_124:
    lookup_i = 0;
    lookup_r0 = (u32)D_087D223C;
    lookup_r1 = *(u16 *)lookup_r0;
    hold_r8 = (u8 *)lookup_r0;
    if (lookup_r1 == 0) {
        goto block_129;
    }
    hold_r7 = (u8 *)&D_0202ECF4;
    lookup_scan = (u32)hold_r8;
    lookup_r1 = ((struct GameState *)hold_r7)->lookup22;
loop_126:
    lookup_r0 = lookup_i << 2; lookup_r0 += lookup_i;
    object_r4 = lookup_r0 << 1;
    entity_r6 = (u8 *)(object_r4 + lookup_scan);
    object_r3 = *(u16 *)entity_r6;
    asm volatile("" : "+r"(object_r3));
    if (lookup_r1 != object_r3) {
        goto block_128;
    }
    goto block_87;
block_128:
    lookup_r0 = lookup_i + 1; lookup_r0 <<= 24; lookup_i = lookup_r0 >> 24;
    lookup_r0 = lookup_i << 2; lookup_r0 += lookup_i; lookup_r0 <<= 1;
    lookup_r0 += (u32)hold_r8;
    if (*(u16 *)lookup_r0 != 0) {
        goto loop_126;
    }
block_129:
    {
        u32 clear_address;
        register u32 clear_r4 asm("r4");

        clear_address = (u32)&D_020324B6;
        clear_r4 = zero;
        asm volatile("" : "+r"(clear_r4) : "r"(clear_address));
        *(u8 *)clear_address = clear_r4;
    }
    return;
block_131:
    lookup_i = 0;
    kind_copy = 0x690C;
    asm volatile("" : "+r"(kind_copy));
    object_r1 = object_r3 + kind_copy;
    if (*(u8 *)object_r1 != 0) {
        goto block_134;
    }
loop_132:
    object_r0 = lookup_i + 1;
    lookup_i = (u8)object_r0;
    if (lookup_i > 5U) {
        goto block_134;
    }
    object_r0 = lookup_i + object_r1;
    if (*(u8 *)object_r0 == 0) {
        goto loop_132;
    }
block_134:
    if (lookup_i != 6) {
        goto block_145;
    }
    {
        register u32 slot_r1 asm("r1") = (u32)&D_02032990;
        register u32 actor_r0 asm("r0");
        register u32 flags_r1 asm("r1");
        register u32 mask_r2 asm("r2");

        asm volatile("" : "+r"(slot_r1));
        actor_r0 = *(u32 *)slot_r1;
        asm volatile("" : "+r"(actor_r0));
        flags_r1 = *(u32 *)actor_r0;
        mask_r2 = 2;
        asm volatile("" : "+r"(flags_r1), "+r"(mask_r2));
        flags_r1 |= mask_r2;
        *(u32 *)actor_r0 = flags_r1;
    }
    goto loop_137;
block_136:
    func_080ED17C(1);
loop_137:
    if ((func_0809669C() << 0x18) == 0) {
        goto block_136;
    }
    D_020324BA = 1;
    func_08098BB4(0x080177ED);
    func_08098BB4(0x0801798D);
    {
        register u32 clear_r2 asm("r2") = zero;
        asm volatile("" : "+r"(clear_r2));
        D_020324BA = clear_r2;
    }
    func_08098BB4(0x080177FA);
    func_080972C8();
    func_08096308(0x10, 0);
    goto loop_141;
block_140:
    func_080ED17C(1);
loop_141:
    if ((func_0809669C() << 0x18) == 0) {
        goto block_140;
    }
    func_08092E0C(2);
    if (D_020324B8 == 0) {
        goto block_144;
    }
    func_0809EB38();
block_144:
    func_080B35D4(1);
    object_r2 = (u32)D_02032494;
    object_r3 = (u32)&D_02032990;
    object_r1 = *(u32 *)object_r3;
    object_r0 = *(u32 *)(object_r1 + 8);
    *(u32 *)object_r2 = object_r0;
    object_r4 = (u32)hold_r8;
    *(u32 *)(object_r4 + 4) = object_r0;
    object_r0 = *(u32 *)(object_r1 + 0xC);
    *(u32 *)(object_r2 + 4) = object_r0;
    *(u32 *)(object_r4 + 8) = object_r0;
    object_r0 = *(u8 *)(object_r1 + 0x1A);
    *(u8 *)(object_r4 + 0x1C) = object_r0;
    object_r0 = (u32)&D_020324B6;
    entity_r6 = (u8 *)zero;
    *(u8 *)object_r0 = (u32)entity_r6;
    return;
block_145:
    object_r0 = zero;
    *(u8 *)object_r4 = object_r0;
block_146:
    func_080ED17C(1);
    temp_r1_5 = ((s32)D_02032990);
    if (temp_r1_5 != NULL) {
        goto block_148;
    }
    goto block_167;
block_148:
    if (D_02030664 == 0) {
        goto block_150;
    }
    goto block_167;
block_150:
    if (M2C_FIELD(temp_r1_5, u8 *, 4) == 0x6C) {
        goto block_158;
    }
    temp_r1_6 = M2C_FIELD(temp_r1_5, u8 *, 0x1D);
    if (!(0x40 & temp_r1_6)) {
        goto block_158;
    }
    object_r3 = 0x087C5CB4;
    object_r0 = 0x3F; object_r0 &= temp_r1_6;
    object_r1 = object_r0 << 1; object_r1 += object_r0;
    object_r2 = (u32)hold_r8; object_r0 = *(u16 *)object_r2;
    object_r2 = object_r0 << 7; object_r2 += object_r0; object_r2 += object_r1; object_r2 <<= 1;
    object_r0 = object_r2 + object_r3; object_r0 = *(volatile u16 *)object_r0;
    object_r1 = object_r3 + 2; object_r1 = object_r2 + object_r1;
    object_r1 = *(u16 *)object_r1; object_r1 <<= 0xB;
    object_r3 += 4; object_r2 += object_r3; object_r2 = *(u16 *)object_r2; object_r2 <<= 0xB;
    object_r3 = 0;
    func_0809E204(object_r0, object_r1, object_r2, object_r3);
    func_08096308(0xE, 0);
    object_r4 = (u32)&D_03005F74;
    entity_r6 = (u8 *)&D_02032990;
    object_r2 = *(u32 *)entity_r6;
    entity_r3 = (u32)D_03000054;
    entity_r1 = *(u32 *)(object_r2 + 8);
    entity_r0 = *(u32 *)entity_r3;
    entity_r0 = entity_r1 - entity_r0;
    if ((s32)entity_r0 >= 0) {
        goto block_154;
    }
    entity_r0 += 0xFF;
block_154:
    *(s16 *)object_r4 = (s16)((s32)entity_r0 >> 8);
    object_r4 = (u32)&D_03005F76;
    entity_r1 = *(u32 *)(object_r2 + 0xC);
    entity_r0 = *(u32 *)(entity_r3 + 4);
    entity_r0 = entity_r1 - entity_r0;
    if ((s32)entity_r0 >= 0) {
        goto block_156;
    }
    entity_r0 += 0xFF;
block_156:
    *(s16 *)object_r4 = (s16)((s32)entity_r0 >> 8);
    func_08092E84(0x45);
    goto block_167;
block_158:
    object_r0 = func_0809E72C();
    object_r0 <<= 24;
    object_r4 = object_r0 >> 24;
    if (object_r4 == 0) {
        goto block_160;
    }
    object_r2 = (u32)&D_0203055C;
    object_r3 = (u32)&D_02032990;
    object_r0 = *(u32 *)object_r3;
    object_r1 = *(u8 *)(object_r0 + 0x1E);
    object_r0 = 0x1F; object_r0 &= object_r1;
    ((struct SceneFlags *)object_r2)->field1 = object_r0;
    object_r4 = zero;
    ((struct SceneFlags *)object_r2)->field5 = object_r4;
    object_r0 = (u32)&D_02030558;
    kind_copy = zero;
    *(u32 *)object_r0 = kind_copy;
    object_r1 = (u32)&D_02021690;
    object_r0 = 9;
    *(u32 *)object_r1 = object_r0;
    func_08096308(8, 0);
    D_020324B6 = 1U;
    object_r1 = (u32)hold_r8;
    asm volatile("" : "+r"(object_r1));
    object_r0 = *(u16 *)object_r1;
    object_r0 <<= 5;
    object_r2 = 0x087C4434;
    asm volatile("" : "+r"(object_r2));
    object_r0 += object_r2;
    object_r0 = *(u8 *)(object_r0 + 0x1E);
    func_08092EA0(object_r0);
    func_08092E84(0x52);
    goto block_167;
block_160:
    func_0809E22C();
    temp_r1_7 = *(u16 *)0x0300000E;
    temp_r5 = 8 & temp_r1_7;
    if (temp_r5 == 0) {
        goto block_162;
    }
    D_02021690 = 4;
    D_02032A85 = object_r4;
    D_02032A84 = object_r4;
    func_08096308(0x10, 0x10);
    D_020324B6 = object_r4;
    goto block_167;
block_162:
    object_r3 = 0x82; object_r3 <<= 1;
    asm volatile("" : "+r"(object_r3));
    object_r0 = object_r3; object_r0 &= temp_r1_7;
    if (object_r0 == 0) {
        goto block_167;
    }
    {
        register struct GameState *late_state asm("r4") = (struct GameState *)hold_r8;
        asm volatile("" : "+r"(late_state));
        if ((u32)(u16)(late_state->category - 0x3A) > 6U) goto block_166;
    }
    entity_r6 = (u8 *)&D_02032990;
    object_r2 = *(u32 *)entity_r6;
    object_r0 = *(u32 *)object_r2;
    object_r1 = 2;
    object_r0 |= object_r1;
    *(u32 *)object_r2 = object_r0;
    func_08098BB4(0x080177ED);
    func_08098BB4(0x080178BA);
    func_08098BB4(0x080177FA);
    func_080972C8();
    object_r2 = *(u32 *)entity_r6;
    object_r0 = *(u32 *)object_r2;
    object_r1 = ~2;
    object_r0 &= object_r1;
    *(u32 *)object_r2 = object_r0;
    goto block_167;
block_166:
    D_02021690 = 0xC;
    func_08096308(0x10, 0x10);
    D_020324B6 = (u8) temp_r5;
block_167:
    if (D_020324B2 == 0) {
        goto block_169;
    }
    goto block_74;
block_169:
    if (D_02021690 != 3) {
        goto block_171;
    }
    goto loop_79;
block_171:
    temp_r2_10 = ((s32)D_02032990);
    if (temp_r2_10 == NULL) {
        goto loop_174;
    }
    M2C_FIELD(temp_r2_10, s32 *, 0) = (s32) (M2C_FIELD(temp_r2_10, s32 *, 0) | 2);
    goto loop_174;
block_173:
    func_080ED17C(1);
loop_174:
    if ((func_0809669C() << 0x18) == 0) {
        goto block_173;
    }
    temp_r1_8 = ((s32)D_02032990);
    if (temp_r1_8 == NULL) {
        goto block_179;
    }
    if (D_0202ECF4.category != 0) {
        goto block_178;
    }
    D_0202ECF4.camera_x = (s32) M2C_FIELD(temp_r1_8, s32 *, 8);
    D_0202ECF4.camera_y = (s32) M2C_FIELD(temp_r1_8, s32 *, 0xC);
block_178:
    D_0202ECF4.animation = (u8) M2C_FIELD(((s32)D_02032990), u8 *, 0x1A);
block_179:
    func_08092E0C(2);
    func_08092E0C(7);
    if (D_02021690 == 3) {
        goto loop_2;
    }
block_180:
    if (D_020324B8 == 0) {
        goto block_182;
    }
    func_0809EB38();
block_182:
    if (D_02030664 != 0) {
        goto block_185;
    }
    object_r3 = (u32)&D_0202ECF4;
    object_r2 = (u32)D_02032494;
    object_r0 = (u32)&D_02032990;
    object_r1 = *(u32 *)object_r0;
    object_r0 = *(u32 *)(object_r1 + 8);
    *(u32 *)object_r2 = object_r0;
    *(u32 *)(object_r3 + 4) = object_r0;
    object_r0 = *(u32 *)(object_r1 + 0xC);
    *(u32 *)(object_r2 + 4) = object_r0;
    *(u32 *)(object_r3 + 8) = object_r0;
    object_r0 = 3;
    func_08092E0C(object_r0);
    return;
block_185:
    D_02032494[0] = (s32) (D_03000054[0] + 0x7800);
    D_02032494[1] = (s32) (D_03000054[1] + 0x5000);
    return;
}
