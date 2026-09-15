#include "m2c_prelude.h"

struct A9FRecord {
    u32 flags;
    u8 pad04[2];
    u16 state;
    u8 pad08[0x15];
    u8 changed;
    u8 value;
    u8 previous_value;
    u8 pad20[0x28];
};

extern struct A9FRecord D_020325A0[];
extern void func_080AAE80(struct A9FRecord *);
extern void func_080AA1E4(struct A9FRecord *);
extern void func_080AA4E0(struct A9FRecord *);
extern void func_080AA0B8(struct A9FRecord *);
extern void func_080AA5C0(u8, struct A9FRecord *);
extern void func_080AABCC(struct A9FRecord *);
extern s32 func_080AAD34(struct A9FRecord *);
extern void func_080AB2EC(struct A9FRecord *);
extern void func_080AB06C(struct A9FRecord *);
extern void func_080ABE3C(struct A9FRecord *);
extern void func_080A98C4(struct A9FRecord *);
extern void func_080AAF80(struct A9FRecord *);
extern void func_080ABE70(struct A9FRecord *);
extern void func_080ABFCC(void);

void sub_080A9F8C(void) {
    u8 i;
    u32 flags;
    struct A9FRecord *record;

    i = 0;
    do {
        record = &D_020325A0[i];
        flags = record->flags;
        if (flags & 1) {
            if (flags & 8) {
                func_080AAE80(record);
            }
        }
        i++;
    } while (i <= 13);

    i = 0;
    do {
        record = &D_020325A0[i];
        if (record->flags & 1) {
            if (record->state != 0xFF && record->state != 2 &&
                record->state != 4 && record->state != 5) {
                if (!(record->flags & 0x10)) {
                    switch (record->state) {
                    case 0:
                        func_080AA1E4(record);
                        func_080AA0B8(record);
                        goto update;
                    case 1:
                        func_080AA4E0(record);
                        func_080AA0B8(record);
                        goto update;
                    case 3:
                        func_080AA0B8(record);
                        goto next_record;
                    case 6:
                    case 7:
                        func_080AA5C0(i, record);
                        goto update;
                    case 8:
                        func_080AABCC(record);
                        goto update;
                    case 9:
                        if ((func_080AAD34(record) << 24) != 0) {
                            goto next_record;
                        }
                    default:
update:
                        func_080AB2EC(record);
                        func_080AB06C(record);
                        func_080ABE3C(record);
                        record->previous_value = record->value;
                        func_080A98C4(record);
                        if (record->previous_value == record->value) {
                            record->changed = 0;
                        } else {
                            record->changed = record->value;
                        }
                        break;
                    }
                } else {
                    func_080AAF80(record);
                }
                func_080ABE70(record);
            }
        }
next_record:
        i++;
    } while (i <= 13);
    func_080ABFCC();
}
