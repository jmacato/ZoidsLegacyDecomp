#include "m2c_prelude.h"
typedef struct {
    u8 pad[8];
    u16 width;
    u16 limit;
} TextInfo;

extern u8 D_02032E60[];
extern u8 D_02032E64[];
extern u8 D_02032E65[];
extern u32 D_02032E68[];
extern u8 D_02030564[];

extern TextInfo *func_0809716C(u8);
extern void func_080972C8(void);
extern void func_080981F0(u8 *, s32, u8, s32, s32);
extern void func_080986B4(u8);

void sub_080E2C24(void) {
    TextInfo *info;
    register s32 width asm("r9");
    register s32 limit asm("r8");
    u8 *out;
    u8 *src;
    u8 columns;
    u8 page;
    u8 lines;
    u8 code;
    u32 adjusted_limit;

    info = func_0809716C(D_02032E64[0]);
    width = info->width;
    limit = info->limit;
    func_080986B4(D_02032E64[0]);
    {
        register u32 *state asm("r2");
        register u32 value asm("r0");

        if (D_02032E65[0] == 0) {
            state = (u32 *)D_02032E68[0];
            value = *state | 0x20000;
        } else {
            state = (u32 *)D_02032E68[0];
            value = *state & 0xFFFDFFFF;
        }
        *state = value;
    }

    src = *(u8 **)D_02032E60;
    out = D_02030564;
    columns = 0;
    page = 0;
    lines = 0;
    code = *src;
    if (code != 0) {
        do {
            if (code <= 31) {
                switch (*src) {
                case 1:
                    src += 2;
                    break;
                case 2:
                    src += 3;
                    break;
                case 3:
                    src += 1;
                    break;
                case 10:
                    src += 1;
                    if (lines >= D_02032E65[0]) {
                        *out = 0;
                        func_080981F0(D_02030564, 0, D_02032E64[0], 0, page * 2);
                        page += 1;
                    }
                    out = D_02030564;
                    columns = 0;
                    lines = (u8)(lines + 1);
                    break;
                }
            } else {
                columns += 1;
                if ((s32)columns > (s32)(width - 2)) {
                    if (lines >= D_02032E65[0]) {
                        *out = 0;
                        func_080981F0(D_02030564, 0, D_02032E64[0], 0, page * 2);
                        page += 1;
                    }
                    out = D_02030564;
                    columns = 0;
                    lines = (u8)(lines + 1);
                }
                out[0] = src[0];
                src += 1;
                out += 1;
                out[0] = src[0];
                src += 1;
                out += 1;
            }
            adjusted_limit = limit - 2;
            if (page == ((s32)(adjusted_limit + (adjusted_limit >> 31)) >> 1)) {
                *(u32 *)D_02032E68[1] &= 0xFFFDFFFF;
                func_080972C8();
                return;
            }
            code = *src;
        } while (code != 0);
    }

    *out = 0;
    func_080981F0(D_02030564, 0, D_02032E64[0], 0, page * 2);
    *(u32 *)D_02032E68[1] |= 0x20000;
    func_080972C8();
}
