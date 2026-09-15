#include "m2c_prelude.h"
extern u8 D_02032272;
extern u8 D_020321A4[];
extern u8 D_020218E8[];
extern u8 D_020218E4[];
extern u16 D_02030564;
extern u8 D_02030566[];
extern void D_081061C4;
extern u32 D_087EDD54[];

extern void func_80ED038(void *, void *, int);
extern void func_8099F5C(void *, void *);
extern void func_80988C8(int, void *);

void sub_080AC214(u8 arg0, u16 flags)
{
    u8 i;
    u8 *record;
    u8 *work;

    i = 0;
    while (i < D_02032272) {
        record = &D_020218E8[D_020321A4[i] * 0x70];
        if ((flags & 1) && record[2] == 0)
            goto rejected;
        if ((flags & 2) && (*(u16 *)(record + 4) & 8))
            goto rejected;
        if ((flags & 4) && (*(u16 *)(record + 4) & 4))
            goto rejected;
        if (flags & 8) {
            if (flags & 0x10) {
                if (record[3] & 0xfe)
                    goto after_field_check;
            }
            if (*(u16 *)(record + 4) & 2)
                goto rejected;
        }
    after_field_check:
        if ((flags & 0x20) && (*(u16 *)(record + 4) & 0x10))
            goto rejected;
        if ((flags & 0x40) && record[0x38] == 0)
            goto rejected;
        if ((flags & 0x80) && record[0x38] == 1)
            goto rejected;
        if ((flags & 0x100) && record[0x38] == 2)
            goto rejected;
        if ((flags & 0x200) && record[0x38] == 3)
            goto rejected;
        if ((flags & 0x400) && record[0x38] == 4)
            goto rejected;
        if (flags & 0x800) {
            s32 item_base = (s32)D_020218E4;
            s32 item_address = record[2] << 6;

            item_address += item_base;
            item_address += 0x5A94;
            if (*(u8 *)item_address == 1)
                goto rejected;
        }

        D_02030564 = 1;
        goto dispatch;
    rejected:
        {
            u16 *rejected_dest = &D_02030564;
            u32 rejected_value = 0x401;
            *rejected_dest = rejected_value;
        }
    dispatch:
        func_80ED038(D_02030566, &D_081061C4, 3);
        work = (u8 *)D_087EDD54[record[0]];
        func_8099F5C(D_02030566, work);
        func_80988C8(arg0, D_02030566 - 2);

        i++;
    }
}
