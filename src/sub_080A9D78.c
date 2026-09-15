#include "m2c_prelude.h"

struct Obj {
    u32 unk0;
    u8 unk4;
    u8 unk5;
    u16 unk6;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    u8 unk18;
    u8 unk19;
    u8 unk1A;
    u8 unk1B;
    u8 unk1C;
    u8 unk1D;
    u8 unk1E;
    u8 unk1F;
    u8 unk20[8];
    s32 unk28[8];
};

extern struct Obj D_020325A0[];
extern s32 D_087A1B98[];
extern s32 D_020329AC[];
extern u8 D_02032A6C[];
void func_080A9AFC(struct Obj *);
void func_080A98C4(struct Obj *);

struct Obj *sub_080A9D78(u8 arg0, u8 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5, u16 arg6, s32 arg7)
{
    u8 found;
    u8 i;
    struct Obj *slot;
    u32 zero;
    u8 bzero;

    if (arg1 > 13) {
        goto fail;
    }
    {
        register u32 base asm("r10");
        register u32 one asm("r9");

        found = 0xFF;
        i = 0;
        base = 0x020325A0;
        one = 1;
        goto cond;
inc:
        i++;
cond:
        if (i <= 13) {
            u32 offset = i << 3;
            struct Obj *entry;

            offset += i;
            offset <<= 3;
            entry = (struct Obj *)(offset + base);

            if ((entry->unk0 & one) == 0) {
                if (found != 0xFF) {
                    goto inc;
                }
                found = i;
                goto inc;
            }
            if (entry->unk5 != arg1) {
                goto inc;
            }
            goto fail;
        }
        asm volatile("" : "=r"(base));
        if (found == 0xFF) {
fail:
            return 0;
        }
        slot = &D_020325A0[found];
        slot->unk0 = arg5 | 1;
        zero = 0;
        slot->unk4 = arg0;
        slot->unk5 = arg1;
        bzero = 0;
        slot->unk6 = arg6;
        slot->unk8 = arg2;
        slot->unkC = arg3;
        if (arg6 == 4) {
            s32 tbl = (s32)D_087A1B98;
            s32 t = arg4 * 8;

            slot->unk8 = (*(s32 *)(t + tbl) << 4) + arg2;
            tbl += 4;
            slot->unkC = (*(s32 *)(t + tbl) << 4) + arg3;
        }
        slot->unk14 = zero;
        slot->unk10 = zero;
        slot->unk18 = bzero;
        slot->unk1B = arg4;
        slot->unk1A = arg4;
        slot->unk1C = bzero;
        if (arg6 != 5) {
            u8 j;

            j = 0;
            {
                register s32 *p asm("r1") = slot->unk28;

            asm volatile("" : "+r"(p));
            do {
                u32 offset = (u32)p;

                offset += j << 2;
                *(s32 *)offset = 0;
                j++;
            } while (j <= 7);
            }
            if (arg6 == 8) {
                s32 *words;
                s32 *words1;
                u8 *bytes;

                j = 0;
                words = D_020329AC;
                words1 = words + 1;
                bytes = D_02032A6C;
                do {
                    u32 offset = j << 3;

                    *(s32 *)(offset + (u32)words) = arg2;
                    *(s32 *)(offset + (u32)words1) = arg3;
                    {
                        u32 byte_offset = j;

                        byte_offset += (u32)bytes;
                        *(u8 *)byte_offset = arg4;
                    }
                    j++;
                } while (j <= 23);
            }
        } else {
            slot->unk28[0] = arg7;
        }
        func_080A9AFC(slot);
        func_080A98C4(slot);
        slot->unk1D = 0;
        return slot;
    }
    return 0;
}
