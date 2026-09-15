#include "m2c_prelude.h"
extern s8 D_0300605A;
extern s8 D_0300605B;
extern s8 D_03006058;
extern s8 D_03006059;
extern s8 D_0300603D;

void sub_0809AC98(void)
{
    register s8 z asm("r2");
    register s8 *pA asm("r1") = &D_0300605A;
    z = 0;
    *pA = z;
    { register s8 *pB asm("r1") = &D_0300605B; *pB = z; }
    {
        register s8 *p8 asm("r3") = &D_03006058;
        register s8 *p9 asm("r1") = &D_03006059;
        *p9 = z;
        *p8 = z;
    }
    { register s8 *pD asm("r1") = &D_0300603D; *pD = z; }
}
