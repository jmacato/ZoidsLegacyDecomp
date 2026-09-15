#include "m2c_prelude.h"

struct BattleObject {
    u32 flags;
    u8 pad04[0x24];
    s32 x;
    u8 pad2C[4];
    s32 y;
};

struct ViewState {
    u8 pad00[0x18];
    s32 x;
};

extern volatile u16 D_0300004E;
extern volatile u16 D_03000050;
extern struct BattleObject *D_02032E8C[2][6];
extern u8 D_02032F7C[6];
extern u8 D_02034B4C[];
extern s32 D_087A2790[][3];
extern s32 D_087A2798[][3];
extern u8 D_02030664;
extern struct ViewState D_030033C4;

u8 func_080E9D88(u8 side, u8 slot);
void func_080ED17C(s32 frames);
void func_080BB05C(u8 side, u8 slot);
void func_080BB224(s32 kind, u8 side, u8 slot, s32 value);
void func_08096308(s32 kind, s32 duration);

void sub_080C2DD0(u8 side)
{
    u8 slot;
    u8 frame;
    u8 frame2;
    u32 frame2_next;
    u32 side3_anim;
    u32 side3_final;
    struct BattleObject **object_base;

    D_0300004E = 0x540;
    D_03000050 = 0x10;

    slot = 0;
    do {
        if (func_080E9D88(side, slot) && D_02032F7C[slot] == 0x80) {
            D_02032E8C[side][slot]->flags |= 0x400;
        }
        slot++;
    } while (slot <= 5);

    asm volatile("" : "+r"(side));
    frame = 0;
    object_base = &D_02032E8C[0][0];
    side3_anim = side * 24;
    asm volatile("" : "+r"(side3_anim));
    asm volatile("" : "+r"(side3_anim));
    do {
        asm volatile("" ::: "r2", "r3");
        slot = 0;
        do {
            if (func_080E9D88(side, slot) && D_02032F7C[slot] == 0x80) {
                register struct BattleObject *object asm("r1") = *(struct BattleObject **)((u8 *)object_base + (slot * 4 + side3_anim));
                s32 x = object->x;
                if (side == 0) {
                    x += 0x200;
                } else {
                    x -= 0x200;
                }
                object->x = x;
            }
            slot++;
        } while (slot <= 5);
        D_03000050 = (frame << 8) | (0x10 - frame);
        func_080ED17C(1);
        frame++;
    } while (frame <= 0xF);

    slot = 0;
    do {
        if (func_080E9D88(side, slot) && D_02032F7C[slot] == 0x80) {
            func_080BB05C(side, slot);
        }
        slot++;
    } while (slot <= 5);

    D_0300004E = 0;

    slot = 0;
    do {
        if (D_02032F7C[slot] != 0x80) {
            D_02032E8C[side][slot]->flags |= 0x80000;
        }
        slot++;
    } while (slot <= 5);

    slot = 0;
    if (D_02032F7C[0] != 0xFF) {
        do {
            slot++;
            if (slot > 5) {
                break;
            }
        } while (D_02032F7C[slot] != 0xFF);
    }

    D_02034B4C[0x27A5] = slot;
    func_080BB224(9, side, slot, 0);
    func_08096308(4, 0x10);

    asm volatile("" : "+r"(side));
    frame2 = 0;
    side3_final = side * 3;
    asm volatile("");
    asm volatile("");
    asm volatile("");
    asm volatile("");
    asm volatile("");
    do {
        slot = 0;
        frame2_next = frame2 + 1;
        asm volatile("" : : "r"(frame2_next));
        do {
            if (D_02032F7C[slot] != 0x80 && D_02032F7C[slot] != 0xFF) {
                struct BattleObject *object;
                s32 source;
                register s32 side6 asm("r3");
                u32 slot4;
                s32 *source_x;
                s32 *source_y;
                s32 source_y_value;
                s32 target_y_value;
                register u32 target_state asm("r1");
                s32 delta;

                slot4 = slot * 4;
                object = *(struct BattleObject **)((u8 *)&D_02032E8C[0][0] + (slot4 + (side3_final << 3)));
                side6 = side3_final * 2;
                source = side6 + slot;
                source_x = &D_087A2790[source][0];

                target_state = D_02032F7C[slot];
                delta = frame2 * (D_087A2790[side6 + target_state][0] - *source_x);
                if (delta < 0) {
                    delta += 0xF;
                }
                object->x = *source_x + (delta >> 4);

                source_y = &D_087A2798[source][0];
                target_state = D_02032F7C[slot];
                target_y_value = D_087A2798[side6 + target_state][0];
                source_y_value = *source_y;
                delta = frame2 * (target_y_value - source_y_value);
                if (delta < 0) {
                    delta += 0xF;
                }
                object->y = source_y_value + (delta >> 4);
            }
            slot++;
        } while (slot <= 5);

        if (D_02030664 == 1 && D_030033C4.x <= 0x78) {
            s32 delta = 0x78 - D_030033C4.x;
            if (delta < 0) {
                delta += 3;
            }
            D_030033C4.x += delta >> 2;
        }
        func_080ED17C(1);
        frame2 = frame2_next;
    } while (frame2 <= 0xF);
}
