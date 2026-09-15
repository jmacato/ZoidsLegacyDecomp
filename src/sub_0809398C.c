#include "m2c_prelude.h"

struct Vec3s {
    s16 x;
    s16 y;
    s16 z;
};

void func_08093678(void *, s32, struct Vec3s *);
s32 func_080ECD30(s32, s32);

s16 sub_0809398C(s32 arg0, s16 *dest, u8 *source) {
    s32 coords[3];
    struct Vec3s local;

    func_08093678(source, arg0, &local);
    coords[0] = local.x + M2C_FIELD(source, s32 *, 0x14);
    coords[1] = local.y + M2C_FIELD(source, s32 *, 0x18);
    coords[2] = local.z + M2C_FIELD(source, s32 *, 0x1C);
    dest[0] = (s16)(func_080ECD30(coords[0] << 8, coords[2]) + 0x78);
    dest[1] = (s16)(func_080ECD30(coords[1] << 8, coords[2]) + 0x50);
    return (s16)coords[2];
}
