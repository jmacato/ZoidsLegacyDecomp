#include "m2c_prelude.h"
/* Zoids Legacy (USA) - function @ 0x0809FD3C.
 * Stores a byte to two IWRAM flags and a word to two IWRAM fields. */

extern unsigned char D_020316F4;
extern unsigned char D_020316F5;
extern int D_020314C4;
extern int D_020315DC;

void sub_0809FD3C(int arg0, int arg1)
{
    unsigned char *p4 = &D_020316F4;
    unsigned char *p5 = &D_020316F5;
    *p5 = arg0;
    *p4 = arg0;
    {
        int *q4 = &D_020314C4;
        int *qd = &D_020315DC;
        *qd = arg1;
        *q4 = arg1;
    }
}
