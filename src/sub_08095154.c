#include "m2c_prelude.h"
extern u8 D_030034A4[];
typedef void (*Callback)(void *);
void func_080ECD60(void *, Callback);

void sub_08095154(void) {
    u8 i;
    u8 *p;
    u8 *q;
    u8 j;
    u32 *slot;

    for (i = 0; i <= 15; i++) {
        p = D_030034A4 + i * 180;
        if (*(u32 *)p & 1) {
            j = 0;
            q = p + 12;
            do {
                slot = (u32 *)(q + j * 4);
                if (*slot != 0 && !(*(u32 *)*slot & 1)) {
                    *slot = 0;
                }
                j++;
            } while (j <= 31);
        }
    }
    for (i = 0; i <= 15; i++) {
        p = D_030034A4 + i * 180;
        if (*(u32 *)p & 1) {
            {
                Callback value;
                value = (Callback)*(u32 *)(p + 172);
                if (value != 0) {
                    func_080ECD60(p, value);
                    *(u32 *)(p + 172) = 0;
                }
            }
            {
                Callback value;
                value = (Callback)*(u32 *)(p + 176);
                if (value != 0) {
                    func_080ECD60(p, value);
                }
            }
        }
    }
}
