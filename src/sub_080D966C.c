#include "m2c_prelude.h"
extern void func_08095114();
extern void *func_080D2450();
extern void func_080D2790();
void sub_080D966C(void *arg0) {
  s32 *p8C = (s32 *)((char *)arg0 + 0x8C);
  s32 temp_r5 = *p8C;
  void *temp_r0, *temp_r0_2;
  u32 temp_r0_3, temp_r2;
  u8 var_r1;
  s32 off;
  if (temp_r5 == 0) {
    temp_r0 = func_080D2450(
        arg0, 0, 0,
        (s16)(*(s32 *)((char *)arg0 + 4) + (*(s32 *)((char *)arg0 + 0x94) * 2)),
        (s32) * (s16 *)((char *)arg0 + 8), 0x20, 0x080D8C39, 1);
    *(void **)((char *)arg0 + 0xC) = temp_r0;
    *(void **)((char *)temp_r0 + 0x28) = arg0;
    *(s32 *)((char *)temp_r0 + 0x2C) = temp_r5;
    *(s32 *)((char *)temp_r0 + 0x30) = temp_r5;
    func_080D2790(0);
    *p8C = *p8C + 1;
    return;
  }
  {
    register void *t asm("r0") = *(void **)((char *)arg0 + 0xC);
    s32 c = *(s32 *)t & 0x20000;
    temp_r0_2 = t;
    if (c) {
      var_r1 = 0x10;
      __asm__ volatile("" : "+r"(var_r1));
      temp_r0_3 = *(u32 *)((char *)temp_r0_2 + 0x2C);
      temp_r2 = (temp_r0_3 >> 1) + 0x11;
      if (((u32)var_r1 < temp_r2) && (*(s32 *)((char *)arg0 + 0x4C) == 0)) {
        u32 bound2 = temp_r2;
        s32 *arr = (s32 *)((char *)arg0 + 0xC);
        do {
          var_r1 += 1;
        } while (((u32)var_r1 < bound2) &&
                 ((off = var_r1 << 2, *(s32 *)((char *)arr + off)) == 0));
      }
      if (var_r1 == ((*(volatile u32 *)((char *)temp_r0_2 + 0x2C) >> 1) + 0x11))
        func_08095114(arg0);
    }
  }
}
