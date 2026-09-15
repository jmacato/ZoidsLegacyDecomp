/* Zoids Legacy (USA) - function @ 0x080925A4.  MATCHING.
 * Sorted doubly-linked-list insert (descending key), walking the prev chain
 * from the head. -1 is the end sentinel. Matching required forcing the agbcc
 * register allocation (explicit `register ... asm("rN")`), a goto-rotated loop
 * to reproduce the block layout, and materializing -1 before caching the head
 * pointer so the `adds r5,r2,#0` schedules after `negs`. */

typedef unsigned char u8;
struct Node { u8 key; u8 pad[7]; struct Node *next; struct Node *prev; };

extern struct Node *gNodeListHead;   /* 0x03000880 */
extern unsigned char gByte_03000888; /* 0x03000888 */

void sub_080925A4(struct Node *a)
{
    register struct Node *node asm("r3") = a;
    register struct Node **base asm("r2") = &gNodeListHead;
    register struct Node *cur asm("r1") = *base;
    register struct Node *m1 asm("r0") = (struct Node *)-1;
    register struct Node **head asm("r5") = base;
    register u8 key asm("r4");
    register struct Node *prev asm("r2");

    if (cur != m1) {
        key = node->key;
        goto test;
    cont:
        cur = prev;
    test:
        if (cur->key <= key) goto else_prev;
        node->next = cur->next;
        cur->next = node;
        node->prev = cur;
        if (*head == cur) *head = node;
        goto done;
    else_prev:
        prev = cur->prev;
        if (prev != (struct Node *)-1) goto cont;
        cur->prev = node;
        node->next = cur;
        node->prev = prev;
    } else {
        *base = node;
        node->prev = cur;
        node->next = cur;
        gByte_03000888 = 1;
    }
done: ;
}
