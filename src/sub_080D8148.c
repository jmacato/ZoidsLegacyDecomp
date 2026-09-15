#include "m2c_prelude.h"
extern void func_08095114(void *);
extern void func_080D12A0(s32, s32);
extern void *func_080D2450();
extern void func_080D2790(s32);

void sub_080D8148(void *arg0) {
    char *owner = arg0;
    register u32 state asm("r0") = *(u32 *)(owner + 0x8C);

    switch (state) {
    case 0: {
        register s32 *coord asm("r4") = (s32 *)(owner + 0x94);
        register s32 x asm("r3") = *coord - 0x100;
        void *created;

        created = func_080D2450(owner, 0, 0, (s16)x,
            0xE0, 0x20, 0x080D6D85, 1);
        *(void **)(owner + 0xC) = created;
        *(void **)((char *)created + 0x28) = owner;
        *(s32 *)((char *)created + 0x2C) = 0;
        *(s32 *)((char *)created + 0x30) = *coord;
        func_080D2790(0);
        goto advance;
    }
    case 1:
        if ((**(u32 **)(owner + 0xC) & 0x20000) == 0) {
            break;
        }
        {
            register s16 *coord asm("r0") = (s16 *)(owner + 0x94);
            register s32 coord_offset asm("r1") = 0;
            register s32 x asm("r3") = coord[coord_offset];
            register volatile s32 *outgoing asm("sp");
            register s32 zero asm("r4");

            outgoing[0] = 0x60;
            outgoing[1] = 0x200;
            zero = 0;
            outgoing[2] = zero;
            outgoing[3] = zero;
            *(void **)(owner + 0x10) = func_080D2450(owner, 2, 1, x);
            func_080D12A0(6, 0);
            func_080D2790(1);
            *(s32 *)(owner + 0x90) = zero;
            goto advance;
        }
    case 2: {
        register s32 *timer asm("r5") = (s32 *)(owner + 0x90);
        *timer = *timer + 1;
        if (*timer != 4) {
            break;
        }
        {
            register s32 *coord asm("r0") = (s32 *)(owner + 0x94);
            register s32 x asm("r3") = *coord + 1;
            register s32 zero asm("r4");
            register volatile s32 *outgoing asm("sp");
            void *created;

            x = (s16)x;
            outgoing[0] = 0x52;
            outgoing[1] = 0x80100;
            zero = 0;
            outgoing[2] = zero;
            outgoing[3] = zero;
            created = func_080D2450(owner, 2, 1, x);
            *(void **)(owner + 0x14) = created;
            {
                register u32 field asm("r1") = 0x140;
                *(u16 *)((char *)created + 0xC) = field;
            }
            *timer = zero;
            asm volatile("");
            goto advance;
        }
    }
    case 3: {
        register s32 *timer asm("r5") = (s32 *)(owner + 0x90);
        *timer = *timer + 1;
        if (*timer != 4) {
            break;
        }
        {
            register s32 *coord asm("r0") = (s32 *)(owner + 0x94);
            register s32 x asm("r3") = *coord - 0xB;
            register s32 zero asm("r4");
            register volatile s32 *outgoing asm("sp");
            void *created;

            x = (s16)x;
            outgoing[0] = 0x34;
            outgoing[1] = 0x80000;
            zero = 0;
            outgoing[2] = zero;
            outgoing[3] = zero;
            created = func_080D2450(owner, 2, 0, x);
            *(void **)(owner + 0x18) = created;
            {
                register u32 field asm("r1") = 0x180;
                *(u16 *)((char *)created + 0xC) = field;
            }
            *timer = zero;
            goto advance;
        }
    }
    case 4: {
        register s32 *timer asm("r9") = (s32 *)(owner + 0x90);
        register s32 timer_value asm("r0") = *timer;
        timer_value += 1;
        *timer = timer_value;
        if (timer_value != 4) {
            break;
        }
        {
            register s32 *coord asm("r8");
            register s32 coord_init asm("r0") = 0x94;
            register s32 size asm("r6");
            register u32 field asm("r5");
            register s32 zero asm("r4");
            register s32 x asm("r3");
            register volatile s32 *outgoing asm("sp");
            register void *created asm("r0");

            asm volatile("" : "+r"(coord_init));
            coord_init += (s32)owner;
            coord = (s32 *)coord_init;
            x = (s16)(*(s32 *)coord_init + 0x12);
            outgoing[0] = 0x2E;
            size = 0x80100;
            outgoing[1] = size;
            zero = 0;
            outgoing[2] = zero;
            outgoing[3] = zero;
            created = func_080D2450(owner, 2, 1, x);
            asm volatile("" : "+r"(created));
            *(void **)(owner + 0x1C) = created;
            field = 0x140;
            *(u16 *)((char *)created + 0xC) = field;

            {
                register s32 *coord_reload asm("r1") = coord;
                x = (s16)(*coord_reload - 7);
            }
            outgoing[0] = 0x21;
            outgoing[1] = size;
            outgoing[2] = zero;
            outgoing[3] = zero;
            created = func_080D2450(owner, 2, 1, x);
            asm volatile("" : "+r"(created));
            *(void **)(owner + 0x20) = created;
            *(u16 *)((char *)created + 0xC) = field;
            *timer = zero;
            goto advance;
        }
    }
    case 5: {
        register s32 *timer asm("r8");
        register s32 timer_init asm("r1") = 0x90;
        register s32 timer_value asm("r0");
        asm volatile("" : "+r"(timer_init));
        timer_init += (s32)owner;
        timer = (s32 *)timer_init;
        timer_value = *(s32 *)timer_init;
        timer_value += 1;
        *(s32 *)timer_init = timer_value;
        if (timer_value != 4) {
            break;
        }
        {
            register s32 *coord asm("r6") = (s32 *)(owner + 0x94);
            register s32 size asm("r5");
            register s32 zero asm("r4");
            register s32 x asm("r3") = *coord - 0x1E;
            register volatile s32 *outgoing asm("sp");
            void *created;

            x = (s16)x;
            outgoing[0] = 0x31;
            size = 0x80200;
            outgoing[1] = size;
            zero = 0;
            outgoing[2] = zero;
            outgoing[3] = zero;
            created = func_080D2450(owner, 2, 1, x);
            *(void **)(owner + 0x24) = created;
            {
                register u32 field asm("r1") = 0x140;
                *(u16 *)((char *)created + 0xC) = field;
            }

            x = *coord + 0x14;
            x = (s16)x;
            outgoing[0] = 0x18;
            outgoing[1] = size;
            outgoing[2] = zero;
            outgoing[3] = zero;
            created = func_080D2450(owner, 2, 0, x);
            *(void **)(owner + 0x28) = created;
            {
                register u32 field asm("r1") = 0x1C0;
                *(u16 *)((char *)created + 0xC) = field;
            }
            *timer = zero;
            goto advance;
        }
    }
    case 6: {
        register s32 *timer asm("r1") = (s32 *)(owner + 0x90);
        *timer = *timer + 1;
        if (*timer != 4) {
            break;
        }
        {
            register s32 x asm("r3");
            register volatile s32 *outgoing asm("sp");
            void *created;

            {
                register s32 *coord asm("r0") = (s32 *)(owner + 0x94);
                x = *coord - 0xD;
            }
            x = (s16)x;
            outgoing[0] = 0xE;
            outgoing[1] = 0x80200;
            {
                register s32 zero asm("r0") = 0;
                outgoing[2] = zero;
                outgoing[3] = zero;
            }
            created = func_080D2450(owner, 2, 0, x);
            *(void **)(owner + 0x2C) = created;
            {
                register u32 field asm("r1") = 0x200;
                *(u16 *)((char *)created + 0xC) = field;
            }
            goto advance;
        }
    }
advance:
    {
        register s32 *state_slot asm("r1") = (s32 *)(owner + 0x8C);
        *state_slot = *state_slot + 1;
    }
    break;

    case 7: {
        register u32 index asm("r2") = 0x18;
        register char *parent asm("r1") = *(char **)(owner + 0xC);
        register u32 raw_bound asm("r0") = *(u32 *)(parent + 0x2C) >> 1;
        register u32 bound asm("r3") = raw_bound;
        asm volatile("" : "+r"(raw_bound));
        bound += 0x19;

        if (index < bound && *(s32 *)(owner + 0x6C) == 0) {
            register u32 scan_bound asm("r4") = bound;
            register char *children asm("r3") = owner + 0xC;
            do {
                register u32 next asm("r0") = index + 1;
                next <<= 24;
                index = next >> 24;
            } while (index < scan_bound &&
                *(s32 *)(children + (index << 2)) == 0);
        }
        if (index == ((*(u32 *)(parent + 0x2C) >> 1) + 0x19)) {
            index = 1;
            if (*(s32 *)(owner + 0x10) == 0) {
                register char *children asm("r1") = owner + 0xC;
                do {
                    register u32 next asm("r0") = index + 1;
                    next <<= 24;
                    index = next >> 24;
                } while (index <= 8 &&
                    *(s32 *)(children + (index << 2)) == 0);
            }
            if (index == 9) {
                func_08095114(owner);
            }
        }
        break;
    }
    }
    return;
}
