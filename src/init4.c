/* Zoids Legacy (USA) - function @ 0x0809256C.
 * Resets two IWRAM longs to -1 and an IWRAM byte to 0. */

extern int gWord_03000880;
extern int gWord_03000884;
extern unsigned char gByte_03000888;

/* 0x0809256C */
void Init4(void)
{
    gWord_03000880 = gWord_03000884 = -1;
    gByte_03000888 = 0;
}
