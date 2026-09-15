/* Zoids Legacy (USA) - function @ 0x0809258C.
 * Resets an IWRAM long to -1 and sets an IWRAM flag byte to 1. */

extern int gWord_03000880;
extern unsigned char gByte_03000888;

/* 0x0809258C */
void sub_0809258C(void)
{
    gWord_03000880 = -1;
    gByte_03000888 = 1;
}
