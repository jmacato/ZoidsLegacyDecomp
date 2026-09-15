#include "m2c_prelude.h"

struct ResourceEntry {
    void *value;
    u32 unused;
};

extern u16 D_0202ECF4;
extern u8 D_020324B1[];
extern u8 D_020324BB[];
extern void *D_020324E8[];
extern s32 D_03000054[];
extern s16 D_087AFBB4[];
extern s16 D_087AFCB0[];
extern struct ResourceEntry D_087AFB54[];
extern struct ResourceEntry D_087AFB58[];

extern void func_08095208(s32, s32, s32);
extern void func_08094554(void *);
extern void *func_08094484(s32, s32, u16, s32, s32, u16, u16, s32, s32);

void sub_0809D734(void)
{
    s16 *record;
    u32 limit;
    register u32 row asm("r9");

    if (D_0202ECF4 == 0) {
        record = D_087AFBB4;
        limit = 42;
    } else {
        record = D_087AFCB0;
        limit = 3;
    }

    row = 0;
    if (row < limit) {
        void **windows = D_020324E8;
        for (;;) {
            s16 *next_record;
            u32 next_row;

            if (D_020324BB[row] == 0xFF) {
                u8 active = D_020324B1[0];
                next_record = record + 3;
                next_row = row + 1;
                if (active != 0 &&
                    (record[1] + 2) * 0x800 > D_03000054[0] &&
                    (record[1] - 2) * 0x800 < D_03000054[0] + 0xF000 &&
                    (record[2] + 2) * 0x800 > D_03000054[1] &&
                    (record[2] - 2) * 0x800 < D_03000054[1] + 0xA000) {
                    u8 n;
                    u32 tile;

                    n = 0;
                    if (windows[n] != 0) {
                        register void **scan asm("r1") = D_020324E8;
                        asm volatile("" : "+r"(scan));
                        do {
                            n++;
                            if (n > 41)
                                break;
                        } while (scan[n] != 0);
                    }

                    {
                        register s32 offset asm("r0");
                        register struct ResourceEntry *base asm("r2");
                        offset = record[0] << 3;
                        asm volatile("" : "+r"(offset));
                        base = D_087AFB54;
                        asm volatile("" : "+r"(base));
                        func_08095208((s32)*(void **)(offset + (s32)base),
                            0x06010000 + ((n * 16 + 0x200) << 5), 0x200);
                    }
                    {
                        register s32 offset asm("r0");
                        register struct ResourceEntry *base asm("r2");
                        offset = record[0] << 3;
                        asm volatile("" : "+r"(offset));
                        base = D_087AFB58;
                        asm volatile("" : "+r"(base));
                        func_08095208((s32)*(void **)(offset + (s32)base),
                            ({
                                register s32 destination asm("r1");
                                register s32 destination_base asm("r3");
                                destination = (12 - n) << 5;
                                destination_base = 0x05000200;
                                asm volatile("add %0, %0, %1"
                                    : "+r"(destination)
                                    : "r"(destination_base));
                                destination;
                            }), 0x20);
                    }
                    tile = n * 16 + 0x200;
                    {
                        register s32 x asm("r3");
                        register s32 y asm("r0");
                        asm volatile(
                            "mov r0, #2\n\t"
                            "ldrsh %0, [%1, r0]"
                            : "=r"(x)
                            : "r"(record)
                            : "r0");
                        x <<= 19;
                        x >>= 16;
                        asm volatile(
                            "mov r1, #4\n\t"
                            "ldrsh %0, [%1, r1]"
                            : "=r"(y)
                            : "r"(record)
                            : "r1");
                        y <<= 19;
                        y >>= 16;
                        windows[n] = func_08094484(0x0842558C, 0x08425598, 0,
                            x, y, tile, 12 - n, 0x13C8, 0);
                    }
                    D_020324BB[row] = n;
                }
            } else {
                register s16 *pre_record asm("r8");
                register u32 pre_row asm("r7");
                if (D_020324B1[0] != 0 &&
                    (record[1] + 2) * 0x800 > D_03000054[0] &&
                    (record[1] - 2) * 0x800 < D_03000054[0] + 0xF000 &&
                    (record[2] + 2) * 0x800 > D_03000054[1]) {
                    register s32 lower asm("r0");
                    register s32 bound asm("r1");
                    lower = (record[2] - 2) * 0x800;
                    bound = D_03000054[1] + 0xA000;
                    asm volatile("" : "+r"(lower), "+r"(bound));
                    asm volatile(
                        "add r3, %2, #6\n\t"
                        "mov %0, r3\n\t"
                        "mov %1, %3\n\t"
                        "add %1, #1"
                        : "=r"(pre_record), "=r"(pre_row)
                        : "r"(record), "r"(row)
                        : "r3");
                    if (lower < bound)
                        goto visible;
                }
                {
                    u8 *slot = D_020324BB + row;
                    func_08094554(windows[*slot]);
                    windows[*slot] = 0;
                    *slot = 0xFF;
                    asm volatile(
                        "add %2, #6\n\t"
                        "mov %0, %2\n\t"
                        "mov %1, %3\n\t"
                        "add %1, #1"
                        : "=r"(pre_record), "=r"(pre_row), "+r"(record)
                        : "r"(row));
                }
visible:
                next_record = pre_record;
                next_row = pre_row;
            }

            record = next_record;
            row = (u8)next_row;
            {
                register u32 limit_view asm("r0") = limit;
                asm volatile("" : "+r"(limit_view));
                if (row >= limit_view)
                    break;
            }
        }
    }
}
