#include "m2c_prelude.h"
struct S3008 { s32 pad[5]; s32 unk14; s32 unk18; void *unk1C; void *unk20; void *unk24; void *unk28; void *unk2C; };
extern volatile s16 D_04000208;
extern volatile u16 D_04000200;
extern volatile s16 D_04000134;
extern volatile u16 D_04000128;
extern s32 func_080ECD2C();

void sub_08093008(void) {
    s32 local;
    struct S3008 *s;
    char *p;
    D_04000208 = 0;
    D_04000200 &= 0xFF3F;
    D_04000208 = 1;
    D_04000134 = 0;
    D_04000128 = 0x2000;
    D_04000128 |= 0x4003;
    local = 0;
    s = (struct S3008 *)0x030032D4;
    func_080ECD2C(&local, s, 0x0500003C);
    func_080ECD2C((void *)0x080005F8, (void *)0x03003174, 0x04000010);
    func_080ECD2C((void *)0x080933E1, (void *)0x030031B4, 0x04000048);
    s->unk14 = 12;
    s->unk18 = 12;
    p = (char *)s + 0x30;
    s->unk1C = p;
    p += 0x18;
    s->unk20 = p;
    p += 0x18;
    s->unk24 = p;
    p += 0x30;
    s->unk28 = p;
    p += 0x30;
    s->unk2C = p;
    D_04000208 = 0;
    D_04000200 |= 0x80;
    D_04000208 = 1;
}
