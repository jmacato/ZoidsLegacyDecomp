#include <stdint.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef struct {
    u32 flags;
    int16_t x, y;
    u16 width, height;
    int16_t column, row;
    u16 lines;
    u8 color, extra[11];
    u16 tiles[];
} Window;
typedef struct { u16 code; int8_t bearing; u8 width; int8_t advance; u8 pad[3]; } Metric;
extern const Metric metrics[];
extern const int8_t pairs[];
extern const u8 glyphs[];
extern const u32 metric_count;
extern const u8 *original_render(Window *, const u8 *);
#define MEM(type, address) (*(volatile type *)(address))
#define CALL(address, type) ((type)((address) | 1))
#define allocate CALL(0x080979A4, u32 (*)(u32, u16 *))
#define reserve CALL(0x0809795C, void (*)(u16))
#define release CALL(0x08097980, void (*)(u16))
#define refresh CALL(0x080972C8, void (*)(void))
#define wait_frame CALL(0x080ED17C, void (*)(u32))
#define sound CALL(0x08092E84, void (*)(u32))
#define make_arrow CALL(0x08094484, u32 (*)(u32,u32,u32,int,int,u32,u32,u32,u32))
#define drop_arrow CALL(0x08094554, void (*)(u32))

/* Keep negative left bearings inside the window. */
static int text_inset(Window *w) { return (w->flags & 0x10) ? 2 : 0; }

/* Task stacks are 0x380 bytes. Keep only the previous glyph's tiles. */
typedef struct { Window *window; int pixel, previous; u16 owned[6]; int owned_count; } Cursor;

static int owns_tile(const Cursor *c, u32 id) {
    for (int i = 0; i < c->owned_count; ++i)
        if (c->owned[i] == id) return 1;
    return 0;
}

static int metric_index(u16 code) {
    for (u32 i = 0; i < metric_count; ++i)
        if (metrics[i].code == code) return i;
    return -1;
}

static int supported(Window *w, const u8 *p, int name) {
    while (*p) {
        if (*p == 1) { if (p[1] > 2) return 0; p += 2; }
        else if (*p == 2) {
            if (p[1] >= w->width - 2 || p[2] >= w->height - 3) return 0;
            p += 3;
        }
        else if (*p == 10) ++p;
        else if (*p == 3 && !name) {
            if (!supported(w, (const u8 *)0x02021774, 1)) return 0;
            ++p;
        } else if (*p >= 0x80 && *p <= 0x9f && p[1]) {
            if (metric_index((p[0] << 8) | p[1]) < 0) return 0;
            p += 2;
        } else return 0;
    }
    return 1;
}

static int dynamic_tile(u16 tile) {
    u32 base = MEM(u32, 0x02021664);
    tile &= 1023;
    return tile < base || tile >= base + 64;
}

static void tick(Window *w) {
    w->flags |= 2;
    refresh();
    wait_frame(MEM(u8, 0x03000075) == 1 ? 2 : 1);
}

static void next_line(Cursor *c) {
    Window *w = c->window;
    if (!(w->flags & 0x10)) {
        w->row += 2;
        w->column = 0;
        c->pixel = text_inset(w);
        c->previous = -1;
        return;
    }
    w->lines += 2;
    if (w->row == w->height - 4) {
        if (w->lines == w->height - 2) {
            u32 arrow = make_arrow(0x080ED620, 0x080ED648, 1,
                (w->column + 1 + w->x) * 8, (w->row + 2 + w->y) * 8,
                MEM(u16, 0x0202166A) + 2, MEM(u16, 0x0202166C), 32, 0);
            MEM(u32, 0x0200A894) = arrow;
            while (!(MEM(u16, 0x0300000E) & 3)) wait_frame(1);
            drop_arrow(arrow);
            w->lines = 0;
            sound(0x41);
        }
        for (int step = 0; step < 2; ++step) {
            for (int y = 1; y < w->height - 2; ++y) {
                for (int x = 1; x < w->width - 1; ++x) {
                    u16 *dst = &w->tiles[y * w->width + x];
                    if (y == 1 && dynamic_tile(*dst))
                        release((*dst & 1023) - MEM(u32, 0x02021670));
                    *dst = dst[w->width];
                }
            }
            for (int x = 1; x < w->width - 1; ++x)
                w->tiles[(w->height - 2) * w->width + x] =
                    (MEM(u32, 0x02021664) + 1) | MEM(u16, 0x02021668);
            --w->row;
            tick(w);
        }
    }
    w->row += 2;
    w->column = 0;
    c->pixel = text_inset(w);
    c->previous = -1;
}

static int draw(Cursor *c, int index) {
    Window *w = c->window;
    const Metric *m = &metrics[index];
    int pen = c->pixel;
    int x = pen + m->bearing;
    if (c->previous >= 0) {
        int previous_advance = metrics[c->previous].advance;
        int step = previous_advance + pairs[c->previous * metric_count + index];
        pen += (step < 1 ? 1 : step) - previous_advance;
        x = pen + m->bearing;
    }
    if (x + m->width > (w->width - 2) * 8) {
        if (!(w->flags & 0x50)) goto advance;
        next_line(c);
        pen = text_inset(w);
        x = pen + m->bearing;
    }
    if (w->row < 0 || w->row >= w->height - 3) goto advance;
    if (m->width) {
        const u8 *src = glyphs + index * 64;
        int first = x < 0 ? 0 : x >> 3;
        int last = (x + m->width - 1) >> 3;
        u16 slots[6];
        int count = (last - first + 1) * 2;
        int needed = 0;
        u16 fresh[6];
        u32 base = MEM(u32, 0x02021670);
        for (int i = 0; i < count; ++i) {
            u16 old = w->tiles[(w->row + i % 2 + 1) * w->width + first + i / 2 + 1];
            u32 id = (old & 1023) - base;
            if (!(w->flags & 0x10) && dynamic_tile(old) && id < 1024 && owns_tile(c, id))
                slots[i] = id;
            else { slots[i] = 0xffff; ++needed; }
        }
        if (needed && !allocate(needed, fresh)) goto advance;
        for (int i = 0, n = 0; i < count; ++i) {
            if (slots[i] != 0xffff) continue;
            u32 id = slots[i] = fresh[n++];
            reserve(id);

        }
        c->owned_count = count;
        for (int i = 0; i < count; ++i) c->owned[i] = slots[i];
        u32 *buffer = (u32 *)MEM(u32, 0x02021654);

        for (int col = first; col <= last; ++col) {
            for (int half = 0; half < 2; ++half) {
                int i = (col - first) * 2 + half;
                u16 *cell = &w->tiles[(w->row + half + 1) * w->width + col + 1];
                u16 old = *cell;
                u32 *dst = buffer + slots[i] * 8;
                int copy = dynamic_tile(old);
                for (int row = 0; row < 8; ++row) {
                    u32 value = copy ? buffer[((old & 1023) - base) * 8 + row] : 0x44444444;
                    int y = half * 8 + row;
                    for (int px = 0; px < 8; ++px) {
                        int gx = col * 8 + px - x;
                        if (gx < 0 || gx >= m->width) continue;
                        int sx = gx;
                        u32 ink = (src[y * 4 + sx / 4] >> ((sx & 3) * 2)) & 3;
                        if (ink) {
                            int shift = px * 4;
                            u32 old_ink = (value >> shift) & 15;
                            if ((old_ink >> 2) == (u32)w->color + 1 && (old_ink & 3) > ink)
                                ink = old_ink & 3;
                            value = (value & ~(15u << shift)) | ((ink + (w->color + 1) * 4) << shift);
                        }
                    }
                    dst[row] = value;
                }
                if (copy && (old & 1023) != base + slots[i])
                    release((old & 1023) - base);
                *cell = (base + slots[i]) | MEM(u16, 0x02021668);
            }
        }
    }
advance:
    c->pixel = pen + m->advance;
    c->previous = index;
    if (w->flags & 0x10) w->column = (c->pixel - text_inset(w) + 7) >> 3;
    else ++w->column;
    return 1;
}

static const u8 *render(Cursor *c, const u8 *p) {
    Window *w = c->window;
    while (*p) {
        if (*p == 1) { w->color = p[1]; p += 2; continue; }
        if (*p == 2) {
            w->column = p[1]; w->row = p[2]; c->pixel = p[1] * 8 + text_inset(w);
            c->previous = -1; p += 3; continue;
        }
        if (*p == 10) { next_line(c); ++p; continue; }
        if (*p == 3) { render(c, (const u8 *)0x02021774); ++p; }
        else {
            int index = metric_index((p[0] << 8) | p[1]);
            if (!draw(c, index)) return p;
            p += 2;
        }
        if (w->flags & 0x10) tick(w);
        if (*p > 1 && (*p == 10 || ((w->flags & 0x40) && ((w->flags & 0x10) ? c->pixel >= (w->width - 2) * 8 : w->column >= w->width - 2)))) {
            next_line(c);
            if (*p == 10) ++p;
        }
    }
    return p;
}

static void clear_menu(Window *w, const u8 *p, int *column, int *row) {
    while (*p) {
        if (*p == 1) { p += 2; continue; }
        if (*p == 2) { *column = p[1]; *row = p[2]; p += 3; continue; }
        if (*p == 10) { *column = 0; *row += 2; ++p; continue; }
        if (*p == 3) { clear_menu(w, (const u8 *)0x02021774, column, row); ++p; continue; }
        if (*column < w->width - 2 && *row < w->height - 3) {
            for (int half = 0; half < 2; ++half) {
                u16 *cell = &w->tiles[(*row + half + 1) * w->width + *column + 1];
                if (dynamic_tile(*cell)) release((*cell & 1023) - MEM(u32, 0x02021670));
                *cell = (MEM(u32, 0x02021664) + 1) | MEM(u16, 0x02021668);
            }
        }
        ++*column;
        p += 2;
        if ((w->flags & 0x40) && *column >= w->width - 2) {
            *column = 0; *row += 2;
            if (*p == 10) ++p;
        }
    }
}

const u8 *vwf_render(Window *w, const u8 *p) {
    if (w->color > 2 || w->column < 0 || w->row < 0 || w->width < 3 || w->width > 30 || w->height < ((w->flags & 0x10) ? 6 : 4) ||
        w->width * w->height > (0x4d0 - 0x1e) / 2 || !supported(w, p, 0))
        return original_render(w, p);
    if (!(w->flags & 0x10)) {
        int column = w->column, row = w->row;
        clear_menu(w, p, &column, &row);
        w->flags |= 2;
    }
    Cursor c;
    c.window = w; c.pixel = w->column * 8 + text_inset(w); c.previous = -1;
    c.owned_count = 0;
    return render(&c, p);
}
