#include "m2c_prelude.h"

typedef struct LinkNode LinkNode;

struct LinkNode {
    u8 pad00[0x20];
    LinkNode *first;
    u8 pad24[8];
    LinkNode *owner;
    LinkNode *previous;
    LinkNode *next;
};

void sub_080EAE70(LinkNode *node)
{
    register LinkNode *state asm("r0") = node;
    register LinkNode *owner asm("r3") = state->owner;

    if (owner != 0) {
        register LinkNode *next asm("r1") = state->next;
        register LinkNode *previous asm("r2") = state->previous;

        if (previous != 0) {
            previous->next = next;
        } else {
            owner->first = next;
        }
        if (next != 0) {
            next->previous = previous;
        }
        state->owner = 0;
    }
}
