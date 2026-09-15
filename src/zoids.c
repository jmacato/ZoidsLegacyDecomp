/* Zoids Legacy (USA) decompilation - first decompiled functions.
 *
 * These two live at 0x08092554..0x0809256C. EmptyStub is a do-nothing leaf;
 * Init3 fills three consecutive IWRAM pointers with EmptyStub's address.
 * Compiled with agbcc -O2 they reproduce the original bytes exactly.
 */

typedef void (*VoidFn)(void);

/* 0x08092554 */
void EmptyStub(void)
{
}

/* IWRAM base treated as an array of function pointers (filled by Init3). */
extern VoidFn gIwramFnTable[];

/* 0x08092558 */
void Init3(void)
{
    gIwramFnTable[0] = EmptyStub;
    gIwramFnTable[1] = EmptyStub;
    gIwramFnTable[2] = EmptyStub;
}
