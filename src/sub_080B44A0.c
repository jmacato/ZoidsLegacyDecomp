#include "m2c_prelude.h"
extern u8 D_02032272;
extern u8 D_020321A4[];
extern u8 D_02034B4C[];
extern u16 D_02030564;
extern u8 D_02030566[];
extern void D_081061C4;
extern u32 D_087EDD54[];

extern void func_80ED038(void *, void *, int);
extern void func_8099F5C(void *, void *);
extern void func_80988C8(int, void *);

void sub_080B44A0(u8 arg0, u16 flags)
{
    u8 i;
    u8 *record;
    u8 *work;

    i = 0;
    while (i < D_02032272) {
        record = &D_02034B4C[D_020321A4[i] * 0x270];
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

        D_02030564 = 1;
        goto dispatch;
    rejected:
        {
            register u16 *rejected_dest_r1 asm("r1") = &D_02030564;
            register u32 rejected_r0 asm("r0") = 0x401;
            asm volatile("" : "+r"(rejected_dest_r1));
            asm volatile("" : "+r"(rejected_r0));
            *rejected_dest_r1 = rejected_r0;
        }
    dispatch:
        func_80ED038(D_02030566, &D_081061C4, 3);
        work = (u8 *)D_087EDD54[record[0]];
        func_8099F5C(D_02030566, work);
        func_80988C8(arg0, D_02030566 - 2);

        i++;
    }
}
