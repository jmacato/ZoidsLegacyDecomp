#include "m2c_prelude.h"

struct DeferredDmaCopy {
    u32 source;
    u32 destination;
    s32 byte_count;
};

u32 RunDeferredDmaCopy(struct DeferredDmaCopy *request) asm("func_0809298C");

u32 RunDeferredDmaCopy(struct DeferredDmaCopy *request) {
    volatile u32 *dma = (volatile u32 *)0x040000D4;
    dma[0] = request->source;
    dma[1] = request->destination;
    dma[2] = (request->byte_count / 2) | 0x80000000;
    return dma[2];
}
