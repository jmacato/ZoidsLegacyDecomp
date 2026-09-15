#include "m2c_prelude.h"

struct SceneFlags {
    u8 pad0;
    u8 field1;
    u8 screen;
};

struct ViewState {
    s32 x;
    s32 y;
    s32 z;
    s16 field0C;
    s16 field0E;
    s16 field10;
    u8 pad12[2];
    s32 field14;
    s32 field18;
    s32 field1C;
    u8 pad20[0x40];
    s32 flags;
};

struct Sprite {
    u8 pad00[0xA];
    s16 y;
    u8 pad0C[0x1C];
    s32 field28;
    s32 field2C;
    s32 field30;
};

struct Task {
    u8 type;
    u8 flags;
    s16 value;
    s32 callback;
    s32 field8;
    s32 fieldC;
};

extern s32 D_02021690;
extern s32 D_02030558;
extern struct SceneFlags D_0203055C;
extern struct ViewState D_030033C4;
extern struct Sprite *D_02032E8C;
extern u8 D_02032EEC;
extern struct Task D_020314A4;
extern struct Task D_020314B4;
extern s32 D_03000054[];

void func_0809258C(void);
void func_080925A4(void);
void func_08092E0C(s32);
void func_08094330(void);
struct Sprite *func_08094484(s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_08096308(s32, s32);
s32 func_0809669C(void);
void func_08098BB4(s32);
void func_0809A1F8(s32, s32, s32, s32, s32, s32);
void func_0809A4CC(s32, s32, s32, s32);
void func_0809A5B4(u8, s32, s32, s32, s32);
void func_0809A9C8(s32, s32, s32, s32, s32, s32);
void func_080D0AF0(s32);
void func_080D12A0(s32, s32);
void func_080ED17C(s32);

void sub_080A7A98(void)
{
    struct Sprite *sprite;
    s32 task_mask;

    D_02021690 = 9;
    D_02030558 = 0xFF10;
    D_0203055C.field1 = 0;
    D_030033C4.x = 0xFFFFC000;
    D_030033C4.y = 0;
    D_030033C4.z = 0x8000;
    D_030033C4.field0C = 0x20;
    D_030033C4.field10 = 0;
    D_030033C4.field0E = 0;
    D_030033C4.field14 = 0x78;
    D_030033C4.field18 = 0x78;
    D_030033C4.field1C = 0x80;
    D_030033C4.flags = 0x20000;
    func_080ED17C(1);
    func_0809A4CC(0x95, 0, 0, 0);

    sprite = func_08094484(0x0821024C, 0x08210258, 0, 0, 0, 0, 0,
        0x2C8, 0x080BADD5);
    D_02032E8C = sprite;
    sprite->field28 = 0;
    sprite->field2C = 0;
    sprite->field30 = 0;
    sprite->y = -0x20;
    D_02032EEC = 0;

    func_08096308(1, 0x10);
    while ((func_0809669C() << 24) == 0) {
        func_080ED17C(1);
    }

    func_08094484(0x08359850, 0x0835985C, 0, 8, 0x68, 0x3C2, 0xD, 8, 0);
    func_08098BB4(0x08017BD3);
    func_0809A9C8(0x31, 0, 0, 0x3C2, 0xD, 0x02002880);
    func_08098BB4(0x080188CF);
    func_08096308(2, 0x10);
    while ((func_0809669C() << 24) == 0) {
        func_080ED17C(1);
    }

    D_0203055C.screen = 0xFF;
    D_02021690 = 0xA;
    func_080ED17C(1);
    func_08094330();
    func_0809A1F8(0x74, 0, 1, 0, 0, 0x02002880);
    func_080D0AF0(0xFFFFFF00);
    func_080D12A0(0xE, 0);
    func_0809A5B4(D_0203055C.screen, 2, 3, 2, 1);

    {
        register struct Task *task asm("r0") = &D_020314A4;
        register u8 flags asm("r2");
        task->type = 0x5F;
        flags = task->flags;
        task_mask = -2;
        task->flags = task_mask & flags;
        task->value = 0;
        task->callback = 0x080A0099;
        task->fieldC = 0;
        task->field8 = 0;
    }
    func_080925A4();

    D_020314B4.type = 0xA0;
    D_020314B4.flags = task_mask & D_020314B4.flags;
    D_020314B4.value = 0;
    D_020314B4.callback = 0x080A00D5;
    D_020314B4.fieldC = 0;
    D_020314B4.field8 = 0;
    func_080925A4();

    func_08096308(1, 0x10);
    {
        s32 *scroll = D_03000054;
        s32 finished = 0x1000;
wait_scroll:
        if (*scroll != finished) {
            func_080ED17C(1);
            goto wait_scroll;
        }
    }
    func_0809258C();

    func_08094484(0x08359850, 0x0835985C, 0, 8, 0x68, 0x3C2, 0xD, 8, 0);
    func_08098BB4(0x08017BD3);
    func_0809A9C8(1, 3, 0, 0x3C2, 0xD, 0x02002880);
    func_08098BB4(0x08018935);
    func_08096308(2, 0x10);
    while ((func_0809669C() << 24) == 0) {
        func_080ED17C(1);
    }

    func_08092E0C(7);
    D_02021690 = -1;
    func_080ED17C(1);
}
