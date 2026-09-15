#include "m2c_prelude.h"

struct TextRecordAC87C {
    u8 first;
    u8 second;
    u8 third;
    u8 pad3;
    s32 value;
};

extern void func_080981D0(s32, s32, s32);
extern void func_080981F0(const void *, s32, s32, s32, s32);
extern void func_08098248(const void *, s32, s32);
extern void func_0809844C(s32, s32, s32, s32, s32, s32, s32);
extern u8 func_08098B58(const void *);
extern void func_080ED038(void *, const void *, s32);
extern void func_080ED128(void *, const void *);

extern u8 D_02030564[];
extern u8 D_081061C4[];
extern const void *D_087EDD54[];
extern const void *D_087EEE60[];

void sub_080AC87C(struct TextRecordAC87C *arg0, s32 arg1)
{
    struct TextRecordAC87C *record = arg0;
    register u32 style asm("r5");
    register u32 i asm("r4");
    const void *text;

    arg1 <<= 24;
    style = (u32)arg1 >> 24;
    func_080981D0(style, 0, 2);

    {
        register u32 first asm("r0");

        asm volatile("ldrb %0, [%1]"
                     : "=r"(first)
                     : "r"(record));
        if (first <= 0xC7) {
            register void *destination asm("r0") = D_02030564;
            register const void **table asm("r2") = D_087EDD54;
            register u32 table_index asm("r1");

            asm volatile("ldrb %0, [%1]"
                         : "=r"(table_index)
                         : "r"(record), "r"(destination), "r"(table));
            func_080ED128(destination, table[table_index]);
        } else {
            register u32 command asm("r0");

            asm volatile("ldrb %0, [%1]"
                         : "=r"(command)
                         : "r"(record));

            switch (command) {
            case 0xC8:
                func_080ED038(D_02030564, (const void *)0x081061CC, 0x1B);
                break;
            case 0xC9:
                func_080ED038(D_02030564, (const void *)0x081061E8, 0x17);
                break;
            }
        }
    }

    {
        register u32 result asm("r0") = func_08098B58(D_02030564);
        register u32 width asm("r1");
        register u32 remaining asm("r0");

        result <<= 24;
        width = result >> 24;
        i = 0;
        remaining = 0xD - width;
        if (i < remaining) {
            register u32 bound asm("r6") = remaining;

            do {
                func_08098248(D_081061C4, 0, style);
                i++;
            } while (i < bound);
        }
    }
    func_08098248(D_02030564, 0, style);
    func_080981D0(style, 0, 6);

    if ((*(u32 *)record & 0xFFFF00) == 0) {
        text = (const void *)0x08106200;
        goto draw_text;
    }

    {
        register u32 second asm("r0");

        asm volatile("ldrb %0, [%1, #1]"
                     : "=r"(second)
                     : "r"(record));
        if (second != 0) {
        {
            register const void **table asm("r1") = D_087EEE60;
            register u32 width asm("r1");
            register u32 remaining asm("r0");

            asm volatile("" : "+r"(second) : "r"(table));
            second = func_08098B58(table[second]);
            second <<= 24;
            width = second >> 24;
            i = 0;
            remaining = 0xD - width;
            if (i < remaining) {
                register u32 bound asm("r6") = remaining;

                do {
                    func_08098248(D_081061C4, 0, style);
                    i++;
                } while (i < bound);
            }
        }
        {
            register const void **table asm("r4") = D_087EEE60;
            register u32 table_index asm("r0");

            asm volatile("ldrb %0, [%1, #1]"
                         : "=r"(table_index)
                         : "r"(record), "r"(table));
            func_08098248(table[table_index], 0, style);
            func_080981D0(style, 0, 8);

        {
            register u32 third asm("r0");

            asm volatile("ldrb %0, [%1, #2]"
                         : "=r"(third)
                         : "r"(record));
            if (third != 0) {
            {
                register u32 width asm("r1");
                register u32 remaining asm("r0");

                third = func_08098B58(table[third]);
                third <<= 24;
                width = third >> 24;
                i = 0;
                remaining = 0xD - width;
                if (i < remaining) {
                    register u32 bound asm("r6") = remaining;

                    do {
                        func_08098248(D_081061C4, 0, style);
                        i++;
                    } while (i < bound);
                }
            }
                {
                    register const void **table asm("r0") = D_087EEE60;
                    register u32 table_index asm("r1");

                    asm volatile("ldrb %0, [%1, #2]"
                                 : "=r"(table_index)
                                 : "r"(record), "r"(table));
                    text = table[table_index];
                }
            } else {
                text = (const void *)0x08106238;
            }
        }
        }

draw_text:
        func_08098248(text, 0, style);
    } else {
        {
            register const void **table asm("r1") = D_087EEE60;
            register u32 result asm("r0");
            register u32 width asm("r1");
            register u32 remaining asm("r0");

            asm volatile("ldrb %0, [%1, #2]"
                         : "=r"(result)
                         : "r"(record), "r"(table));
            result = func_08098B58(table[result]);
            result <<= 24;
            width = result >> 24;
            i = 0;
            remaining = 0xD - width;
            if (i < remaining) {
                register u32 bound asm("r6") = remaining;

                do {
                    func_08098248(D_081061C4, 0, style);
                    i++;
                } while (i < bound);
            }
        }
        {
            register const void **table asm("r1") = D_087EEE60;
            register u32 table_index asm("r0");

            asm volatile("ldrb %0, [%1, #2]"
                         : "=r"(table_index)
                         : "r"(record), "r"(table));
            func_08098248(table[table_index], 0, style);
        }
        func_080981F0((const void *)0x08106238, 0, style, 0, 8);
    }
    }

    func_0809844C(record->value, 7, 0, 2, style, 5, 0xA);
    {
        register u32 first asm("r0");

        asm volatile("ldrb %0, [%1]"
                     : "=r"(first)
                     : "r"(record));
        if ((u8)(first + 0x38) <= 1) {
        func_080981F0((const void *)0x08106254, 1, style, 0, 0xC);
        } else {
        func_080981F0((const void *)0x08106238, 1, style, 0, 0xC);
        }
    }
}
