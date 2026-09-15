#include "m2c_prelude.h"

extern s32 func_08094098(void);
extern s32 func_080940AC(void);
extern s32 func_080940C0(void);
extern s32 func_080940D4(void);
extern s32 func_080940E8(void);
extern s32 func_080940FC(void);
extern void func_08094330(void);
extern void func_08096308(s32, s32);
extern s32 func_0809669C(void);
extern void func_08096FBC(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern void func_08098BB4(s32);
extern void func_0809AB44(s32, s32, s32, s32, s32);
extern void func_0809C1D4(void);
extern void func_0809F7F0(s32);
extern void func_080ECD34(s32, s32);
extern void func_080ED17C(s32);
extern u8 D_0200A880;
extern u8 D_0200A882;
extern u8 D_02021699;

void sub_080A68F0(void) {
    s32 zero;
    u32 clear_mask;
    u8 *first_flag;
    u8 index;
    u8 *records;
    u8 *scan_base;
    register u8 *record asm("r2");
    register u32 scan_offset asm("r0");
    u32 record_mask;
    u32 expected;

    *(s16 *)0x0300004C = 0x1840;
    func_08096FBC(3, 1, 0, 0x35C, 0x3C0, 0, 0xE, 0, 0x3E6, 0xF);
    func_080ECD34(0x081046A8, 0x06015840);
    func_0809AB44(2, 3, 0, 0, 1);
    func_08094330();
    func_08096308(0xF, 0x10);

    zero = 0;
    clear_mask = 0xFFFD;
    first_flag = &D_02021699;

retry:
    func_08098BB4(0x08017AD6);
    if (D_0200A882 != 1) {
        goto done;
    }
    if (D_0200A880 != 0) {
        goto done;
    }
    *(u8 *)0x02021770 = 1;
    index = 1;
    records = (u8 *)0x02027378;
    scan_base = records;
    record_mask = 0x200FF;
    expected = 0x2001E;
scan:
    scan_offset = (u32)index << 6;
    record = (u8 *)(scan_offset + (u32)scan_base);
    if ((*(u32 *)record & record_mask) == expected) {
        goto found;
    }
    index++;
    if (index <= 0x34) {
        goto scan;
    }

selected:
    func_0809F7F0(0x8A);
    {
        u8 *state;
        u8 *entries;
        u8 i;
        s32 loop_zero;

        state = (u8 *)0x0202ECF4;
        *(s16 *)(state + 0) = zero;
        *(s32 *)(state + 4) = 0x81000;
        *(s32 *)(state + 8) = 0xB6000;
        i = 0;
        entries = state;
        entries += 0x38;
        loop_zero = 0;
        do {
            *(s32 *)(entries + (i * 0x14)) = loop_zero;
            i++;
        } while (i <= 0xD);
    }

    if ((func_08094098() << 24) == 0 ||
        (func_080940AC() << 24) == 0 ||
        (func_080940C0() << 24) == 0 ||
        (func_080940D4() << 24) == 0 ||
        (func_080940E8() << 24) == 0 ||
        (func_080940FC() << 24) == 0) {
        goto checks_failed;
    }
    {
        u8 *flag_a;
        u8 *flag_b;
        u8 *flag_c;
        u8 *flag_d;
        u8 *flag_e;
        s32 one;

        flag_a = (u8 *)0x0202169A;
        flag_b = (u8 *)0x0202169B;
        flag_c = (u8 *)0x0202169C;
        flag_d = (u8 *)0x0202169D;
        flag_e = (u8 *)0x0202169E;
        one = 1;
        *flag_e = one;
        *flag_d = one;
        *flag_c = one;
        *flag_b = one;
        *flag_a = one;
        *first_flag = one;
        func_08098BB4(0x08017B38);
    }
    goto done;

found:
    {
        {
            register u32 loaded asm("r1");
            register u32 flags asm("r0");

            loaded = *(u16 *)(record + 2);
            flags = clear_mask;
            flags &= loaded;
            *(u16 *)(record + 2) = flags;
        }
        {
            register u32 id asm("r0");
            register u32 offset asm("r2");
            register s32 delta asm("r1");
            register u32 base asm("r0");
            register u32 loaded asm("r1");
            register u32 flags asm("r0");

            id = *(u8 *)(record + 1);
            offset = id << 3;
            offset -= id;
            offset <<= 4;
            delta = -0x5A90;
            base = (u32)records;
            base += delta;
            offset += base;
            loaded = *(u16 *)(offset + 4);
            flags = clear_mask;
            flags &= loaded;
            loaded = 0x10;
            flags |= loaded;
            *(u16 *)(offset + 4) = flags;
        }
    }
    goto selected;

checks_failed:
    func_08098BB4(0x08017B6B);
    goto retry;

done:
    func_08096308(0x10, 0x10);
    goto poll;
wait:
    func_080ED17C(1);
poll:
    if ((func_0809669C() << 24) == 0) {
        goto wait;
    }
    func_0809C1D4();
    *(s32 *)0x02021690 = -1;
}
