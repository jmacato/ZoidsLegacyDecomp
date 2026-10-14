#include <stdint.h>

#include "text_core.h"

#if defined(__GNUC__) && !defined(__clang__)
#define RUNTIME_O2 __attribute__((optimize("O2,no-tree-loop-distribute-patterns")))
#else
#define RUNTIME_O2
#endif

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

typedef struct {
    u32 flags;
    int16_t x, y;
    u16 width, height;
    int16_t column, row;
    u16 lines;
    u8 color, slot, top, prior_top, selected, prior_selected;
    u8 style, extra, tail, repeat;
    u16 keys;
    u16 tiles[];
} Window;

extern const u16 compact_indices[256];
extern const TextFont runtime_font_data;

#define MEM(type, address) (*(volatile type *)(address))
#define CALL(address, type) ((type)((address) | 1))
#define allocate CALL(0x080979A4, u32 (*)(u32, u16 *))
#define reserve CALL(0x0809795C, void (*)(u16))
#define release CALL(0x08097980, void (*)(u16))
#define get_window CALL(0x0809716C, Window *(*)(u32))
#define order_window_native CALL(0x080971AC, void (*)(u32))
#define refresh CALL(0x080972C8, void (*)(void))
#define wait_frame CALL(0x080ED17C, void (*)(u32))
#define sound CALL(0x08092E84, void (*)(u32))
#define make_arrow CALL(0x08094484, u32 (*)(u32,u32,u32,int,int,u32,u32,u32,u32))
#define drop_arrow CALL(0x08094554, void (*)(u32))
#define udiv CALL(0x080ECF00, u32 (*)(u32, u32))
#define umod CALL(0x080ECF78, u32 (*)(u32, u32))

// The native call copies a frontmost window out and back before setting flag 2.
static void order_window(u32 slot) {
    Window *front = (Window *)0x0200A8A0;
    if (front->slot != (u8)slot) {
        order_window_native(slot);
        return;
    }
    if (!(front->flags & 0x200))
        front->flags |= 2;
}

static __attribute__((always_inline)) inline u32 div3(u32 value) {
    return value < 65536 ? (value * 43691u) >> 17 : udiv(value, 3);
}

#define CURSOR_MARK 0x80000000u
#define CURSOR_STATES ((CursorState *)0x0203EFC0)
#define INDEXED_FORMAT_MAGIC 0x7f7fu
#define ROW_FORMAT_FRAGMENTS 16
#define FORMAT_DIRTY 0x20
#define FORMAT_READY 0x40
#define FORMAT_ROW 2
#define FORMAT_REPEAT 1
#define FORMAT_ROW_RESTART 4
#define FORMAT_ROW_PADDING 8
#define ROW_ROM_TEXT 0x80
#define FLOOR_SUFFIX ((const u8 *)0x08103AE0)
#define FLOOR_BASEMENT_LITERAL 0x0809E90Cu
// Menus and credits share the final 4 KB of EWRAM as scratch space.
#define FORMAT_OUTPUT ((u8 *)0x0203FC00)
#define FORMAT_PIXELS ((u32 *)0x0203F000)
#define FORMAT_ROWS 20
#define MAX_LINE_TILES 64
#define WINDOW_RECORD_SIZE 0x4d0
#define MENU_COUNTS ((volatile u8 *)0x0200E6C4)
#define MENU_LOOKUP ((volatile u8 *)0x0200DE90)
#define MENU_RECORDS ((u8 *)0x0200E6CE)
#define MENU_SLOTS 10
#define MENU_ROWS 210
#define MENU_RECORD_SIZE 0x25
#define MENU_BANK_SIZE 0x1E5A
#define MENU_PACKED 0x1f
#define MENU_TEXT_LIMIT (MENU_RECORD_SIZE * 2 - 1)

typedef struct {
    int16_t x;
    int16_t previous;
    u8 column;
    u8 row;
} CursorState;

typedef struct __attribute__((packed)) {
    u32 value;
    // The upper bits retain the declared field type between updates.
    u8 digits;
    u8 flags;
} IndexedValue;

typedef struct __attribute__((packed)) {
    u16 magic;
    u8 next;
    u8 count;
    u32 address;
    u8 base_color;
    u8 repeat;
    u16 string_bytes;
    u8 cursor_column;
    u8 cursor_row;
    IndexedValue values[];
} IndexedFormat;

typedef struct {
    u32 hash;
    u32 changed[2];
    u8 simple;
    u8 left[FORMAT_ROWS];
    u8 right[FORMAT_ROWS];
    u8 field_tag;
    u8 field_count;
    u8 field_used;
} FormatCache;

#define FORMAT_CACHE ((FormatCache *)0x0203F800)
typedef char FormatCacheFits[(sizeof(FormatCache) * 10 <= 0x230) ? 1 : -1];

static void format_changed(Window *window, u32 index) {
    FORMAT_CACHE[window->slot].changed[index >> 5] |= 1u << (index & 31);
}

typedef struct {
    u8 key_low;
    u8 key_high;
    u8 left;
    u8 right;
    int16_t top;
    int16_t bottom;
} FieldState;

#define FIELD_ACTIVE 0x4000u
#define FIELD_KEY_MASK 0x9fffu

typedef struct {
    union {
        Window *window;
        u16 *credit_tiles;
    };
    TextLayoutState state;
    const FieldState *prior;
    u8 replace;
    u8 cleared;
    u8 palette;
    u8 tile_columns;
    u8 tile_rows;
    u8 direct;
    int16_t surface_top;
    u16 *cells;
    u8 stride;
    int8_t top_tile;
    u8 clip_right;
} RenderContext;

typedef struct __attribute__((may_alias)) {
    TextDecoder decoder;
    TextProfile profile;
    TextLayoutResult result;
    TextEvent event;
    TextLayoutCursor cursor;
    RenderContext context;
} WindowWorkspace;

#define WINDOW_WORKSPACE_OFFSET \
    ((WINDOW_RECORD_SIZE - sizeof(WindowWorkspace)) & ~3u)
#define MENU_WORKSPACE ((WindowWorkspace *)0x0200D8C0)
typedef char WindowWorkspaceFits[(sizeof(WindowWorkspace) <= 0x340) ? 1 : -1];

typedef struct __attribute__((may_alias)) {
    TextDecoder decoder;
    TextProfile profile;
    TextLayoutResult result;
    TextEvent event;
    TextLayoutCursor cursor;
    RenderContext context;
} CreditsWorkspace;

#define CREDITS_WORKSPACE ((CreditsWorkspace *)0x0203FB00)
typedef char CreditsWorkspaceFits[(sizeof(CreditsWorkspace) <= 0x100) ? 1 : -1];

static __attribute__((always_inline)) inline int surface_width(const RenderContext *context) {
    return context->tile_columns * 8;
}

static __attribute__((always_inline)) inline int surface_height(const RenderContext *context) {
    return context->tile_rows * 8;
}

static __attribute__((always_inline)) inline int colour_fits(u32 colour) {
    return MEM(u16, 0x02021668) + (div3(colour) << 12) <= 0xffff;
}

static __attribute__((always_inline)) inline int text_inset(const Window *window) {
    return (window->flags & 0x10) ? 2 : 0;
}

static __attribute__((always_inline)) inline int tile_buffer_id(u16 tile) {
    u32 id = tile & 1023;
    u32 base = MEM(u32, 0x02021670);
    u32 limit = MEM(u32, 0x02021658);
    if (id < base || id - base >= limit)
        return -1;
    return (int)(id - base);
}

static __attribute__((always_inline)) inline u16 *surface_cell(
        RenderContext *context, int tile_x, int tile_y) {
    if (tile_x < 0 || tile_y < context->top_tile ||
            tile_x >= context->tile_columns || tile_y >= context->tile_rows)
        return 0;
    return &context->cells[tile_y * context->stride + tile_x];
}

// Caches the surface origin, row stride, and first tile row for surface_cell.
static void bind_surface(RenderContext *context, int surface_top) {
    context->surface_top = (int16_t)surface_top;
    context->top_tile = (int8_t)(surface_top / 8);
    if (context->direct) {
        context->cells = context->credit_tiles;
        context->stride = 32;
    } else {
        context->cells = &context->window->tiles[context->window->width + 1];
        context->stride = (u8)context->window->width;
    }
}

static RUNTIME_O2 u32 *surface_tile_words(void *opaque, int x, int y) {
    RenderContext *context = opaque;
    u16 *cell = surface_cell(context, x >> 3, y >> 3);
    if (!cell)
        return 0;
    int id = tile_buffer_id(*cell);
    if (id < 0)
        return 0;
    return &((u32 *)MEM(u32, 0x02021654))[id * 8];
}

static int tile_has_unowned_ink(int id, int x, int y,
                                 const FieldState *field) {
    u32 *buffer = (u32 *)MEM(u32, 0x02021654);
    u32 owned = 0;
    if (field) {
        for (int column = 0; column < 8; ++column)
            if (x + column >= field->left && x + column < field->right)
                owned |= 15u << (column * 4);
    }
    for (int row = 0; row < 8; ++row) {
        u32 mask = field && y + row >= field->top &&
                   y + row < field->bottom ? ~owned : 0xffffffffu;
        if (buffer[id * 8 + row] & mask & 0x33333333u)
            return 1;
    }
    return 0;
}

static RUNTIME_O2 int free_tiles_at_least(int needed) {
    if (needed <= 0)
        return 1;
    volatile const u8 *live = (const u8 *)0x0200DD90;
    int limit = (int)MEM(u32, 0x02021658);
    int free = 0;
    int id = 0;
    for (; id + 8 <= limit; id += 8) {
        u32 used = live[id >> 3];
        if (used == 0xff)
            continue;
        used = used - ((used >> 1) & 0x55);
        used = (used & 0x33) + ((used >> 2) & 0x33);
        free += 8 - (int)((used + (used >> 4)) & 0x0f);
        if (free >= needed)
            return 1;
    }
    for (; id < limit; ++id)
        if (!(live[id >> 3] & (1u << (id & 7))) && ++free >= needed)
            return 1;
    return 0;
}

static int take_released_tile(u16 *out) {
    u32 *pending = (u32 *)0x0200DE10;
    u32 limit = MEM(u32, 0x02021658);
    for (u32 id = 0; id < limit; ++id)
        if (pending[id >> 5] & (1u << (id & 31))) {
            pending[id >> 5] &= ~(1u << (id & 31));
            *out = (u16)id;
            return 1;
        }
    return 0;
}

static void clear_dynamic(RenderContext *context, int left, int top,
                          int right, int bottom, u8 value);
static void tick(Window *window);

static __attribute__((noinline)) int reclaim_released_tiles(
        RenderContext *context, int needed) {
    const u32 *pending = (const u32 *)0x0200DE10;
    u32 any = 0;
    for (int word = 0; word < 0x20; ++word)
        any |= pending[word];
    if (!any || context->direct)
        return 0;
    tick(context->window);
    return free_tiles_at_least(needed);
}

static __attribute__((noinline)) RUNTIME_O2 TextStatus prepare_rect(
        RenderContext *context, const TextEvent *event) {
    u8 palette = (u8)div3(event->value);
    if (MEM(u16, 0x02021668) + ((u32)palette << 12) > 0xffff)
        return TEXT_LAYOUT_OVERFLOW;
    int left = event->left;
    int top = event->top;
    int right = event->right;
    int bottom = event->bottom;
    u8 variant = (u8)(event->value - palette * 3 + 1);
    if (left < 0)
        left = 0;
    if (top < context->surface_top)
        top = context->surface_top;
    if (right > surface_width(context))
        right = surface_width(context);
    if (bottom > surface_height(context))
        bottom = surface_height(context);
    if (right <= left || bottom <= top) {
        context->palette = palette;
        return TEXT_OK;
    }
    int first_x = left >> 3;
    int last_x = (right - 1) >> 3;
    int first_y = top >> 3;
    int last_y = (bottom - 1) >> 3;
    int count = 0;
    int needed = 0;
    u16 field = (u16)(MEM(u16, 0x02021668) + ((u32)palette << 12));
    u32 base = MEM(u32, 0x02021670);
    u32 limit = MEM(u32, 0x02021658);
    for (int y = first_y; y <= last_y; ++y) {
        u16 *cell = surface_cell(context, first_x, y);
        for (int x = first_x; x <= last_x; ++x, ++cell) {
            if (count >= MAX_LINE_TILES || !cell)
                return TEXT_LAYOUT_OVERFLOW;
            u32 index = *cell & 1023;
            int id = index < base || index - base >= limit ? -1 : (int)(index - base);
            if (id >= 0) {
                if ((*cell & 0xf000) != (field & 0xf000) &&
                        tile_has_unowned_ink(id, x * 8, y * 8,
                            context->replace && !context->cleared
                                ? context->prior : 0))
                    return TEXT_LAYOUT_OVERFLOW;
            } else {
                ++needed;
            }
            ++count;
        }
    }
    if (!free_tiles_at_least(needed) && !reclaim_released_tiles(context, needed))
        return TEXT_TILE_EXHAUSTED;
    u32 *buffer = (u32 *)MEM(u32, 0x02021654);
    u32 tile_base = MEM(u32, 0x02021670);
    for (int y = first_y; y <= last_y; ++y) {
        for (int x = first_x; x <= last_x;) {
            u16 *cell = surface_cell(context, x, y);
            int old_id = tile_buffer_id(*cell);
            if (old_id >= 0) {
                if ((*cell & 0xf000) != (field & 0xf000)) {
                    for (int row = 0; row < 8; ++row)
                        buffer[old_id * 8 + row] = variant * 0x44444444u;
                    *cell = (u16)((tile_base + old_id) | field);
                }
                ++x;
                continue;
            }
            int run = 0;
            do {
                u16 prior = cell[run];
                old_id = tile_buffer_id(prior);
                if (old_id >= 0)
                    break;
                ++run;
            } while (x + run <= last_x);
            if (!allocate((u32)run, cell))
                return TEXT_TILE_EXHAUSTED;
            for (int index = 0; index < run; ++index) {
                u16 fresh = cell[index];
                reserve(fresh);
                for (int row = 0; row < 8; ++row)
                    buffer[fresh * 8 + row] = variant * 0x44444444u;
                cell[index] = (u16)((tile_base + fresh) | field);
            }
            x += run;
        }
    }
    context->palette = palette;
    return TEXT_OK;
}

static RUNTIME_O2 void clear_dynamic(RenderContext *context, int left, int top,
                                     int right, int bottom, u8 value) {
    if (left < 0)
        left = 0;
    if (top < context->surface_top)
        top = context->surface_top;
    if (right > surface_width(context))
        right = surface_width(context);
    if (bottom > surface_height(context))
        bottom = surface_height(context);
    if (right <= left || bottom <= top)
        return;
    u32 fill = value * 0x11111111u;
    u32 *buffer = (u32 *)MEM(u32, 0x02021654);
    u32 base = MEM(u32, 0x02021670);
    u32 limit = MEM(u32, 0x02021658);
    int first_x = left >> 3;
    int last_x = (right - 1) >> 3;
    for (int tile_y = top >> 3; tile_y <= (bottom - 1) >> 3; ++tile_y) {
        u16 *cell = surface_cell(context, first_x, tile_y);
        if (!cell)
            continue;
        int row_top = tile_y << 3;
        int row_bottom = row_top + 8;
        if (row_top < top)
            row_top = top;
        if (row_bottom > bottom)
            row_bottom = bottom;
        for (int tile_x = first_x; tile_x <= last_x; ++tile_x, ++cell) {
            u32 id = (*cell & 1023) - base;
            if ((*cell & 1023) < base || id >= limit)
                continue;
            u32 *tile = &buffer[id * 8];
            int column_left = tile_x << 3;
            int column_right = column_left + 8;
            if (column_left < left)
                column_left = left;
            if (column_right > right)
                column_right = right;
            int count = column_right - column_left;
            if (count == 8) {
                for (int y = row_top; y < row_bottom; ++y)
                    tile[y & 7] = fill;
                continue;
            }
            u32 mask = ((1u << (count * 4)) - 1) << ((column_left & 7) * 4);
            for (int y = row_top; y < row_bottom; ++y) {
                u32 *word = &tile[y & 7];
                *word = (*word & ~mask) | (fill & mask);
            }
        }
    }
}

static __attribute__((noinline)) void release_empty_rect(
        RenderContext *context, int left, int top, int right, int bottom,
        const TextEvent *pending) {
    if (left < 0)
        left = 0;
    if (top < context->surface_top)
        top = context->surface_top;
    if (right > surface_width(context))
        right = surface_width(context);
    if (bottom > surface_height(context))
        bottom = surface_height(context);
    for (int y = top; y < bottom; y = (y | 7) + 1) {
        for (int x = left; x < right; x = (x | 7) + 1) {
            if (pending && pending->right > pending->left &&
                    (x & ~7) < pending->right && (x | 7) >= pending->left &&
                    (y & ~7) < pending->bottom && (y | 7) >= pending->top)
                continue;
            u16 *cell = surface_cell(context, x >> 3, y >> 3);
            int id = cell ? tile_buffer_id(*cell) : -1;
            if (id < 0 || tile_has_unowned_ink(id, x, y, 0))
                continue;
            release((u16)id);
            *cell = (u16)((MEM(u32, 0x02021664) + 1) | MEM(u16, 0x02021668));
        }
    }
}

static void release_empty_field_tiles(RenderContext *context) {
    const FieldState *field = context->prior;
    if (field)
        release_empty_rect(context, field->left, field->top,
                            field->right, field->bottom, 0);
}

static void tick(Window *window) {
    window->flags |= 2;
    refresh();
    wait_frame(MEM(u8, 0x03000075) == 1 ? 2 : 1);
}

static __attribute__((noinline)) void scroll_window(Window *window, int rows) {
    for (int scrolled = 0; scrolled < rows; ++scrolled) {
        for (int x = 1; x < window->width - 1; ++x) {
            int id = tile_buffer_id(window->tiles[window->width + x]);
            if (id >= 0)
                release((u16)id);
        }
        for (int y = 1; y < window->height - 2; ++y) {
            for (int x = 1; x < window->width - 1; ++x) {
                u16 *destination = &window->tiles[y * window->width + x];
                *destination = destination[window->width];
            }
        }
        for (int x = 1; x < window->width - 1; ++x)
            window->tiles[(window->height - 2) * window->width + x] =
                (u16)((MEM(u32, 0x02021664) + 1) | MEM(u16, 0x02021668));
        --window->row;
        tick(window);
    }
}

static __attribute__((noinline)) void fit_window_line(
        RenderContext *context, TextEvent *event) {
    if (context->direct || !(context->window->flags & 0x10))
        return;
    int excess = event->bottom - surface_height(context);
    if (excess <= 0 || context->state.y <= 0)
        return;
    int rows = (excess + 7) >> 3;
    if (rows > context->state.y / 8)
        rows = context->state.y / 8;
    scroll_window(context->window, rows);
    context->state.y -= rows * 8;
    event->top -= rows * 8;
    event->bottom -= rows * 8;
}

static __attribute__((noinline)) void next_line(Window *window, int step) {
    if (window->flags & 0x10) {
        window->lines += step;
        if (window->row + step >= window->height - 2 &&
                (window->lines & 0x1f) >= window->height - 2) {
            u32 arrow = make_arrow(0x080ED620, 0x080ED648, 1,
                (window->column + 1 + window->x) * 8,
                (window->row + 2 + window->y) * 8,
                MEM(u16, 0x0202166A) + 2, MEM(u16, 0x0202166C), 32, 0);
            MEM(u32, 0x0200A894) = arrow;
            while (!(MEM(u16, 0x0300000E) & 3))
                wait_frame(1);
            drop_arrow(arrow);
            window->lines = 0;
            sound(0x41);
        }
    }
    window->row += step;
    window->column = 0;
}

static __attribute__((always_inline)) inline TextStatus render_glyph(
        RenderContext *context, const TextEvent *event) {
    u8 relative = (u8)(event->glyph.color - context->palette * 3);
    if (relative >= 3)
        return TEXT_LAYOUT_OVERFLOW;
    TextTileSurface surface;
    surface.context = context;
    surface.get = surface_tile_words;
    TextStatus status = context->direct
        ? text_compose_glyph_tiles_uniform(
            &runtime_font_data, &event->glyph, &surface,
            (u8)(relative + 1))
        : text_compose_glyph_tiles_blended(
            &runtime_font_data, &event->glyph, &surface,
            (u8)(relative + 1));
    if (status != TEXT_OK)
        return status;
    if (!context->direct) {
        int right = event->glyph.ink_x + event->glyph.width;
        if (context->window->flags & 0x10) {
            context->window->column = (int16_t)((right + 7) >> 3);
            tick(context->window);
        } else {
            ++context->window->column;
        }
    }
    return TEXT_OK;
}

static __attribute__((noinline)) void clear_previous_field(
        RenderContext *context, u8 color) {
    if (context->replace && !context->cleared) {
        u8 variant = (u8)(color - div3(color) * 3 + 1);
        const FieldState *prior = context->prior;
        clear_dynamic(context, prior->left, prior->top,
                      prior->right, prior->bottom, variant * 4);
        context->cleared = 1;
    }
}

static __attribute__((noinline,noipa)) TextStatus render_event(
        void *opaque, const TextEvent *event) {
    RenderContext *context = opaque;
    if (event->kind == TEXT_EVENT_COLOR) {
        if (!context->direct)
            context->window->color = event->value;
        return colour_fits(event->value) ? TEXT_OK : TEXT_LAYOUT_OVERFLOW;
    }
    if (event->kind == TEXT_EVENT_POSITION) {
        if (!context->direct) {
            context->window->column = event->x >> 3;
            context->window->row = event->y >> 3;
        }
        return TEXT_OK;
    }
    if (event->kind == TEXT_EVENT_LINE || event->kind == TEXT_EVENT_PAGE) {
        if (!context->direct) {
            int step = (event->value + 7) >> 3;
            if (step < 1)
                step = 1;
            next_line(context->window, step);
            context->state.x = text_inset(context->window);
            context->state.y = context->window->row * 8;
            context->state.previous = -1;
        }
        return TEXT_OK;
    }
    if (event->kind != TEXT_EVENT_GLYPH)
        return TEXT_OK;
    return render_glyph(context, event);
}

static __attribute__((always_inline)) inline size_t input_capacity(const u8 *text) {
    u32 address = (u32)text;
    if ((address >> 24) == 8) {
        size_t remaining = 0x09000000 - address;
        return remaining < 4096 ? remaining : 4096;
    }
    if ((address >> 24) != 2)
        return 0;
    if (address == 0x02021774)
        return 0x12;
    if (address >= 0x02021676 && address < 0x02021690)
        return 0x02021690 - address;
    if (address >= 0x02030564 && address < 0x02030664)
        return 0x02030664 - address;
    if (address >= 0x02031756 && address < 0x020317d6)
        return 0x020317d6 - address;
    if (address >= 0x0200e6ce && address < 0x02021652) {
        u32 offset = address - 0x0200E6CE;
        u32 bank_offset = offset - udiv(offset, MENU_BANK_SIZE) * MENU_BANK_SIZE;
        u32 record_offset = bank_offset -
            udiv(bank_offset, MENU_RECORD_SIZE) * MENU_RECORD_SIZE;
        size_t capacity = MENU_RECORD_SIZE * 2 - record_offset;
        size_t remaining = MENU_BANK_SIZE - bank_offset;
        return capacity < remaining ? capacity : remaining;
    }
    if (address >= 0x08000000 && address < 0x09000000) {
        size_t remaining = 0x09000000 - address;
        return remaining < 4096 ? remaining : 4096;
    }
    return 0;
}

static __attribute__((always_inline)) inline size_t read_capacity(const u8 *text) {
    size_t capacity = input_capacity(text);
    if (capacity)
        return capacity;
    u32 address = (u32)text;
    if (address >= 0x02000000 && address < 0x02040000) {
        size_t remaining = 0x02040000 - address;
        return remaining < 4096 ? remaining : 4096;
    }
    if (address >= 0x03000000 && address < 0x03008000) {
        size_t remaining = 0x03008000 - address;
        return remaining < 4096 ? remaining : 4096;
    }
    return 0;
}

static RUNTIME_O2 size_t terminated_length(const u8 *text, size_t capacity) {
    size_t position = 0;
    while (position < capacity) {
        u8 value = text[position];
        if (!value)
            return position + 1;
        size_t length;
        if (value == 1 || value == 4 || value == 6)
            length = 2;
        else if (value == 2 || value == 7 || value == 8)
            length = 3;
        else if (value == 3 || value == 10 || value >= 0x20)
            length = value >= 0x80 && value <= 0x9f ? 2 : 1;
        else
            return 0;
        if (position + length >= capacity)
            return 0;
        if (length == 2 && value >= 0x80 && value <= 0x9f &&
                !text[position + 1])
            return 0;
        position += length;
    }
    return 0;
}

static __attribute__((always_inline)) inline u32 window_tile_end(const Window *window) {
    return 0x1e + window->width * window->height * 2 +
           ((window->flags & 8) ? window->tail * 6 : 0);
}

static WindowWorkspace *window_workspace(Window *window) {
    u32 tile_end = window_tile_end(window);
    u32 limit = (window->flags & 0x10) ? WINDOW_WORKSPACE_OFFSET : WINDOW_RECORD_SIZE;
    if (tile_end > limit)
        return 0;
    // Non-animated text finishes before the reorder buffer can be reused.
    if (!(window->flags & 0x10))
        return MENU_WORKSPACE;
    return (WindowWorkspace *)((u8 *)window + WINDOW_WORKSPACE_OFFSET);
}

static __attribute__((always_inline)) inline FieldState *field_states(Window *window, int *count) {
    u32 tile_end = window_tile_end(window);
    u32 limit = (window->flags & 0x10) ? WINDOW_WORKSPACE_OFFSET : WINDOW_RECORD_SIZE;
    if (tile_end + sizeof(IndexedFormat) <= limit &&
            *(u16 *)((u8 *)window + tile_end) == INDEXED_FORMAT_MAGIC) {
        *count = 0;
        return 0;
    }
    int available = (int)(limit - tile_end);
    *count = available > 0
        ? (int)((u32)available / (u32)sizeof(FieldState)) : 0;
    if (!*count)
        return 0;
    return (FieldState *)((u8 *)window + tile_end);
}

static __attribute__((always_inline)) inline IndexedFormat *indexed_format(Window *window) {
    u32 tile_end = window_tile_end(window);
    u32 limit = (window->flags & 0x10) ? WINDOW_WORKSPACE_OFFSET : WINDOW_RECORD_SIZE;
    if (tile_end + sizeof(IndexedFormat) > limit)
        return 0;
    return (IndexedFormat *)((u8 *)window + tile_end);
}

typedef u16 __attribute__((may_alias)) FieldKey;

static __attribute__((always_inline)) inline u16 field_state_key(const FieldState *state) {
    return *(const FieldKey *)state;
}

static __attribute__((always_inline)) inline int field_is_active(const FieldState *state) {
    return state && field_state_key(state) != 0xffff &&
           (field_state_key(state) & FIELD_ACTIVE);
}

static __attribute__((always_inline)) inline int field_matches_scope(const FieldState *state, int scope) {
    return field_is_active(state) &&
           ((field_state_key(state) & 0x8000) != 0) == (scope == 2);
}

#define FIELD_TAG 0xa5

// Slots at or past field_used stay free until the next reset.
static FieldState *used_field_states(Window *window, int *used, int *count) {
    FieldState *states = field_states(window, count);
    *used = *count;
    if (states && window->slot < 10) {
        const FormatCache *cache = &FORMAT_CACHE[window->slot];
        if (cache->field_tag == FIELD_TAG && cache->field_count == *count &&
                cache->field_used <= *count)
            *used = cache->field_used;
    }
    return states;
}

static void end_field(Window *window) {
    int count, used;
    FieldState *states = used_field_states(window, &used, &count);
    for (int index = 0; index < used; ++index)
        if (field_is_active(&states[index]))
            states[index].key_high &= (u8)~(FIELD_ACTIVE >> 8);
}

static void set_field_state_key(FieldState *state, u16 key) {
    state->key_low = (u8)key;
    state->key_high = (u8)(key >> 8);
}

static void reset_field_states(Window *window) {
    int count, used;
    FieldState *states = used_field_states(window, &used, &count);
    if (!states)
        return;
    for (int index = 0; index < used; ++index)
        set_field_state_key(&states[index], 0xffff);
    if (window->slot < 10) {
        FormatCache *cache = &FORMAT_CACHE[window->slot];
        cache->field_tag = FIELD_TAG;
        cache->field_count = (u8)count;
        cache->field_used = 0;
    }
}

static __attribute__((always_inline)) inline u16 field_key(int x, int y, int scope) {
    return (u16)((((u16)((y + 8) >> 3) << 8) | (x & 0xff)) ^
                 (scope == 2 ? 0x8000 : 0));
}

static RUNTIME_O2 const FieldState *previous_field_bounds(Window *window, int x, int y,
                                                int scope, int *available) {
    *available = 0;
    int count, used;
    FieldState *states = used_field_states(window, &used, &count);
    if (!states)
        return 0;
    if (scope)
        for (int index = 0; index < used; ++index)
            if (field_matches_scope(&states[index], scope)) {
                *available = 1;
                return &states[index];
            }
    if (used < count)
        *available = 1;
    u16 key = field_key(x, y, scope);
    for (int index = 0; index < used; ++index) {
        u16 saved_key = field_state_key(&states[index]);
        if ((saved_key & FIELD_KEY_MASK) == key) {
            *available = 1;
            return &states[index];
        }
        if (saved_key == 0xffff || states[index].right <= states[index].left)
            *available = 1;
    }
    return 0;
}

static void extend_field_bounds(FieldState *bounds, int left, int top,
                                 int right, int bottom) {
    if (left < 0)
        left = 0;
    if (right > 255)
        right = 255;
    if (right <= left || bottom <= top)
        return;
    if (bounds->right <= bounds->left) {
        bounds->left = (u8)left;
        bounds->right = (u8)right;
        bounds->top = (int16_t)top;
        bounds->bottom = (int16_t)bottom;
        return;
    }
    if (left < bounds->left)
        bounds->left = (u8)left;
    if (right > bounds->right)
        bounds->right = (u8)right;
    if (top < bounds->top)
        bounds->top = (int16_t)top;
    if (bottom > bounds->bottom)
        bounds->bottom = (int16_t)bottom;
}

static RUNTIME_O2 void save_field_bounds(Window *window, int x, int y,
                              const TextLayoutResult *result, int scope) {
    int count, used;
    FieldState *states = used_field_states(window, &used, &count);
    if (!states)
        return;
    u16 key = field_key(x, y, scope);
    int free_index = -1;
    for (int index = 0; index < used; ++index) {
        u16 saved_key = field_state_key(&states[index]);
        if (field_matches_scope(&states[index], scope)) {
            extend_field_bounds(&states[index], result->ink_left, result->ink_top,
                                 result->ink_right, result->ink_bottom);
            return;
        }
        if ((saved_key & FIELD_KEY_MASK) == key) {
            free_index = index;
            break;
        }
        if (free_index < 0 && (saved_key == 0xffff ||
                states[index].right <= states[index].left))
            free_index = index;
    }
    if (free_index < 0 && used < count)
        free_index = used;
    if (free_index < 0)
        return;
    if (free_index >= used && window->slot < 10)
        FORMAT_CACHE[window->slot].field_used = (u8)(free_index + 1);
    states[free_index].left = states[free_index].right = 0;
    states[free_index].top = states[free_index].bottom = 0;
    extend_field_bounds(&states[free_index], result->ink_left, result->ink_top,
                         result->ink_right, result->ink_bottom);
    set_field_state_key(&states[free_index], key | FIELD_ACTIVE);
}

static void clear_unwritten_field(RenderContext *context,
                                  int left, int top, int right, int bottom,
                                  u8 value) {
    const FieldState *prior = context->prior;
    if (!field_is_active(prior)) {
        clear_dynamic(context, left, top, right, bottom, value);
        return;
    }
    clear_dynamic(context, left, top,
                  right < prior->left ? right : prior->left, bottom, value);
    clear_dynamic(context, left > prior->right ? left : prior->right,
                  top, right, bottom, value);
    if (left < prior->left)
        left = prior->left;
    if (right > prior->right)
        right = prior->right;
    clear_dynamic(context, left, top, right,
                  bottom < prior->top ? bottom : prior->top, value);
    clear_dynamic(context, left, top > prior->bottom ? top : prior->bottom,
                  right, bottom, value);
}

static RUNTIME_O2 __attribute__((noinline)) void replace_line_field(
        RenderContext *context, const TextEvent *event) {
    int count, used;
    FieldState *states = used_field_states(context->window, &used, &count);
    u16 key = field_key(context->state.x, context->state.y, context->replace);
    const FieldState *prior = context->prior;
    for (int index = 0; index < used; ++index) {
        FieldState *field = &states[index];
        u16 saved = field_state_key(field);
        if ((saved & FIELD_KEY_MASK) != key || field == prior ||
                (saved != 0xffff && (saved & FIELD_ACTIVE)))
            continue;
        u8 variant = (u8)(event->value - div3(event->value) * 3 + 1);
        clear_dynamic(context, field->left, field->top,
                      field->right, field->bottom, variant * 4);
        release_empty_rect(context, field->left, field->top,
                            field->right, field->bottom, event);
        set_field_state_key(field, 0xffff);
    }
}

static __attribute__((noinline)) void prepare_field_line(
        RenderContext *context, const TextEvent *event) {
    if (!context->replace)
        return;
    int left = event->advance_left < event->left ? event->advance_left : event->left;
    int right = event->advance_right > event->right ? event->advance_right : event->right;
    if (left < 0)
        left = 0;
    if (right > surface_width(context))
        right = surface_width(context);
    if (context->clip_right && right > context->clip_right)
        right = context->clip_right;
    int top = event->top < context->surface_top ? context->surface_top : event->top;
    int bottom = event->bottom > surface_height(context)
        ? surface_height(context) : event->bottom;
    if (context->replace == 1) {
        u8 variant = (u8)(event->value - div3(event->value) * 3 + 1);
        if (event->right <= event->left) {
            clear_dynamic(context, left, top, right, bottom, variant * 4);
            release_empty_rect(context, left, top, right, bottom, 0);
        } else {
            clear_unwritten_field(context, left, top, right, bottom, variant * 4);
        }
    }
}

static TextSpan bounded_span(const u8 *text) {
    TextSpan span;
    span.data = text;
    span.length = terminated_length(text, read_capacity(text));
    span.field_id = 0xff;
    return span;
}

static size_t bounded_length(const u8 *text) {
    return terminated_length(text, read_capacity(text));
}

static TextStatus write_plain(TextWriter *writer, TextSpan span) {
    TextTemplatePart part;
    part.kind = TEXT_TEMPLATE_LITERAL;
    part.field_kind = 0;
    part.field_id = 0;
    part.a = 0;
    part.b = 0;
    part.literal = span;
    return text_template_write(writer, &part, 1, 0, 0);
}

#define LIKELY(x) __builtin_expect(!!(x), 1)

typedef u16 __attribute__((may_alias)) HalfWord;

static RUNTIME_O2 __attribute__((noinline)) void copy_text(
        u8 *output, const u8 *input, size_t length) {
    if (((u32)output & 1) && length) {
        *output++ = *input++;
        --length;
    }
    for (; length >= 2; length -= 2, output += 2, input += 2)
        *(HalfWord *)output = (u16)(input[0] | (input[1] << 8));
    if (length)
        *output = *input;
}

// Matches text_writer_span; returns the terminator index or -1.
static __attribute__((always_inline)) inline int strict_length(
        const u8 *text, size_t capacity, size_t *trim) {
    size_t position = 0;
    size_t spaces = 0;
    if (!capacity)
        return -1;
    for (;;) {
        u8 value = text[position];
        if (LIKELY((u32)(value - 0x80) < 0x20)) {
            u8 trail = text[position + 1];
            if (position + 2 >= capacity || !trail)
                return -1;
            if (trim && (value != 0x81 || trail != 0x40))
                spaces = position + 2;
            position += 2;
            continue;
        }
        if (!value)
            break;
        size_t length;
        if (value >= 0x20 || value == 3 || value == 10)
            length = 1;
        else if (value == 1 || value == 4 || value == 6)
            length = 2;
        else if (value == 2 || value == 7 || value == 8)
            length = 3;
        else
            return -1;
        if (position + length >= capacity)
            return -1;
        if ((value == 4 && text[position + 1] > TEXT_ALIGN_RIGHT) ||
                (value == 8 && text[position + 1] >= text[position + 2]))
            return -1;
        position += length;
        spaces = position;
    }
    if (trim)
        *trim = spaces;
    return (int)position;
}

// Matches writer_plain_span; returns the terminator index or -1.
static RUNTIME_O2 __attribute__((noinline)) int plain_length(
        const u8 *source, size_t source_capacity, int newlines) {
    size_t position = 0;
    if (!source_capacity)
        return -1;
    for (;;) {
        u8 value = source[position];
        if (LIKELY((u32)(value - 0x80) < 0x20)) {
            if (position + 2 >= source_capacity || !source[position + 1])
                return -1;
            position += 2;
            continue;
        }
        if (!value)
            break;
        if ((value < 0x20 && (!newlines || value != 10)) ||
                position + 1 >= source_capacity)
            return -1;
        ++position;
    }
    return (int)position;
}

static RUNTIME_O2 __attribute__((noinline)) int strict_length_plain(
        const u8 *text, size_t capacity) {
    return strict_length(text, capacity, 0);
}

static RUNTIME_O2 __attribute__((noinline)) int strict_length_trim(
        const u8 *text, size_t capacity, size_t *trim) {
    return strict_length(text, capacity, trim);
}

static int append_plain(u8 *destination, size_t length, size_t capacity,
                        const u8 *source, size_t source_capacity) {
    int result = plain_length(source, source_capacity, 1);
    if (result < 0)
        return 0;
    size_t position = (size_t)result;
    if (length + position + 1 > capacity)
        return 0;
    copy_text(destination + length, source, position);
    destination[length + position] = 0;
    return 1;
}

u8 *vwf_bounded_copy(u8 *destination, const u8 *source) {
    size_t capacity = input_capacity(destination);
    size_t source_capacity = read_capacity(source);
    if (!capacity || !source_capacity) {
        u8 *output = destination;
        while ((*output++ = *source++)) {}
        return destination;
    }
    destination[0] = 0;
    append_plain(destination, 0, capacity, source, source_capacity);
    return destination;
}

static __attribute__((noinline)) int floor_ordinal(u8 *destination,
                                                  size_t capacity) {
    size_t length = terminated_length(destination, capacity);
    if (!length)
        return 0;
    size_t start = length - 1;
    u32 ones = 0, tens = 0, digits = 0;
    while (start >= 2 && destination[start - 2] == 0x82 &&
            destination[start - 1] >= 0x4f && destination[start - 1] <= 0x58) {
        u32 digit = destination[start - 1] - 0x4fu;
        if (digits == 0)
            ones = digit;
        else if (digits == 1)
            tens = digit;
        ++digits;
        start -= 2;
    }
    if (!digits)
        return 0;
    const u8 *basement = *(const u8 *const *)FLOOR_BASEMENT_LITERAL;
    size_t prefix = bounded_length(basement);
    if (prefix > 1 && start >= prefix - 1) {
        size_t match = 0;
        while (match < prefix - 1 &&
                destination[start - (prefix - 1) + match] == basement[match])
            ++match;
        if (match == prefix - 1)
            return 1;
    }
    static const u16 ordinals[4][2] = {
        {0x8294, 0x8288}, {0x8293, 0x8294}, {0x828e, 0x8284}, {0x8292, 0x8284}};
    u32 kind = tens == 1 || ones > 3 ? 0 : ones;
    TextWriter writer;
    if (text_writer_open(&writer, destination, capacity) == TEXT_OK) {
        text_writer_code(&writer, ordinals[kind][0]);
        text_writer_code(&writer, ordinals[kind][1]);
    }
    return 0;
}

u8 *vwf_bounded_concat(u8 *destination, const u8 *source) {
    size_t capacity = input_capacity(destination);
    size_t source_capacity = read_capacity(source);
    if (!capacity || !source_capacity) {
        u8 *output = destination;
        while (*output)
            ++output;
        while ((*output++ = *source++)) {}
        return destination;
    }
    if (source != FLOOR_SUFFIX && source != (const u8 *)0x081061C8) {
        int length = strict_length_plain(destination, capacity);
        if (length >= 0)
            append_plain(destination, (size_t)length, capacity,
                         source, source_capacity);
        return destination;
    }
    TextSpan span = {source, source_capacity, 0xff};
    if (source == FLOOR_SUFFIX) {
        span = bounded_span(source);
        if (!span.length || floor_ordinal(destination, capacity))
            return destination;
    }
    TextWriter writer;
    if (source == (const u8 *)0x081061C8) {
        size_t trim;
        int valid = strict_length_trim(destination, capacity, &trim);
        size_t length = valid < 0 ? 0 : (size_t)valid;
        while (length >= 2 && destination[length - 2] == 0x81 &&
                destination[length - 1] == 0x40)
            length -= 2;
        if (valid >= 0 && length == trim) {
            destination[length] = 0;
            if (length + 3 <= capacity) {
                destination[length] = 4;
                destination[length + 1] = TEXT_ALIGN_RIGHT;
                destination[length + 2] = 0;
                append_plain(destination, length + 2, capacity,
                             source, source_capacity);
            }
            return destination;
        }
    }
    if (source == (const u8 *)0x081061C8) {
        size_t length = bounded_length(destination);
        if (!length)
            return destination;
        --length;
        while (length >= 2 && destination[length - 2] == 0x81 &&
                destination[length - 1] == 0x40)
            length -= 2;
        destination[length] = 0;
        if (text_writer_open(&writer, destination, capacity) == TEXT_OK &&
                text_writer_control(&writer, 4, TEXT_ALIGN_RIGHT, 0) == TEXT_OK)
            write_plain(&writer, span);
    } else if (text_writer_open(&writer, destination, capacity) == TEXT_OK) {
        write_plain(&writer, span);
    }
    return destination;
}

typedef struct {
    u8 offsets[40];
    char chars[40];
    u32 count;
    u32 end;
} PlainUnits;

static int plain_char(u32 code) {
    if (code >= 0x8260 && code <= 0x8279)
        return 'A' + (int)(code - 0x8260);
    if (code >= 0x8281 && code <= 0x829a)
        return 'a' + (int)(code - 0x8281);
    if (code >= 0x824f && code <= 0x8258)
        return '0' + (int)(code - 0x824f);
    if (code == 0x8140)
        return ' ';
    if (code == 0x817c)
        return '-';
    if (code == 0x8144)
        return '.';
    return 0;
}

static int plain_units(const u8 *text, PlainUnits *units) {
    u32 at = 0, count = 0;
    while (text[at]) {
        u32 lead = text[at], size = 1;
        int value = (int)lead;
        if (lead >= 0x81 && lead <= 0x9f) {
            if (!text[at + 1])
                return 0;
            value = plain_char(lead << 8 | text[at + 1]);
            size = 2;
        } else if (lead < 0x20 || lead >= 0x7f) {
            return 0;
        }
        if (count == sizeof(units->offsets))
            return 0;
        units->offsets[count] = (u8)at;
        units->chars[count++] = (char)value;
        at += size;
    }
    units->count = count;
    units->end = at;
    return count != 0;
}

static int is_upper(int c) {
    return c >= 'A' && c <= 'Z';
}

static int is_lower(int c) {
    return c >= 'a' && c <= 'z';
}

static int is_digit(int c) {
    return c >= '0' && c <= '9';
}

static int is_vowel(int c) {
    if (is_upper(c))
        c += 'a' - 'A';
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

static int word_ends_with(const char *word, u32 length, const char *suffix) {
    u32 size = 0;
    while (suffix[size])
        ++size;
    if (size > length)
        return 0;
    for (u32 i = 0; i < size; ++i) {
        int c = word[length - size + i];
        if (is_upper(c))
            c += 'a' - 'A';
        if (c != suffix[i])
            return 0;
    }
    return 1;
}

static int word_is_code(const char *word, u32 length) {
    int marks = 0;
    for (u32 i = 0; i < length; ++i) {
        if (is_upper(word[i]) || is_digit(word[i]))
            marks = 1;
        else if (word[i] != '-')
            return 0;
    }
    return marks;
}

static int vowel_sound(const u8 *text) {
    PlainUnits units;
    int first = text[0] == 0x82 ? plain_char(0x8200u | text[1]) : text[0];
    if (plain_units(text, &units)) {
        const char *word = units.chars;
        u32 length = 0;
        while (length < units.count && word[length] != ' ')
            ++length;
        first = word[0];
        if (first == '8' || (first == '1' && length >= 2 &&
                (word[1] == '1' || word[1] == '8') &&
                (length == 2 || !is_digit(word[2]))))
            return 1;
        if (is_upper(first) && (length == 1 || word_is_code(word, length)))
            return first == 'A' || first == 'E' || first == 'F' ||
                   first == 'H' || first == 'I' || first == 'L' ||
                   first == 'M' || first == 'N' || first == 'O' ||
                   first == 'R' || first == 'S' || first == 'X';
    }
    return is_vowel(first);
}

static __attribute__((noinline)) int plural_text(const u8 *name, u8 *output,
                                                 u32 capacity) {
    PlainUnits units;
    if (!plain_units(name, &units))
        return 0;
    u32 start = units.count;
    while (start && units.chars[start - 1] != ' ')
        --start;
    const char *word = units.chars + start;
    u32 length = units.count - start;
    if (!length)
        return 0;
    int last = word[length - 1];
    int before = length > 1 ? word[length - 2] : 0;
    const char *suffix = "s";
    u32 drop = 0;
    if (word_ends_with(word, length, "data") ||
            word_ends_with(word, length, "parts") ||
            word_ends_with(word, length, "scissors") ||
            word_ends_with(word, length, "guns") ||
            word_ends_with(word, length, "series")) {
        suffix = "";
    } else if (word_is_code(word, length)) {
        suffix = "s";
    } else if (word_ends_with(word, length, "wolf")) {
        drop = 1;
        suffix = "ves";
    } else if (last == 's' || last == 'x' || last == 'z' ||
               word_ends_with(word, length, "ch") ||
               word_ends_with(word, length, "sh")) {
        suffix = "es";
    } else if (last == 'y' && is_lower(before) && !is_vowel(before)) {
        drop = 1;
        suffix = "ies";
    }
    u32 keep = drop ? units.offsets[units.count - drop] : units.end;
    u32 extra = 0;
    while (suffix[extra])
        ++extra;
    if (keep + extra * 2 + 1 > capacity)
        return 0;
    for (u32 i = 0; i < keep; ++i)
        output[i] = name[i];
    for (u32 i = 0; i < extra; ++i) {
        output[keep + i * 2] = 0x82;
        output[keep + i * 2 + 1] = (u8)(0x81 + suffix[i] - 'a');
    }
    output[keep + extra * 2] = 0;
    return 1;
}

u32 vwf_menu_prefix(u8 *destination, const u8 *source) {
    size_t capacity = input_capacity(destination);
    TextSpan span = bounded_span(source);
    if (!capacity || span.length < 3)
        return 0;
    TextWriter writer;
    text_writer_init(&writer, destination, capacity);
    text_writer_code(&writer, 0x8281);
    if (vowel_sound(source))
        text_writer_code(&writer, 0x828e);
    return writer.status == TEXT_OK ? writer.length >> 1 : 0;
}

u8 vwf_storage_cells(const u8 *text) {
    int length = plain_length(text, read_capacity(text), 0);
    if (length < 0 || (length & 1) || length > 510)
        return 0;
    return (u8)(length >> 1);
}

// validate_palettes read straight from the input when it holds only glyphs,
// colors, and newlines; returns -1 when the token decoder must decide.
static RUNTIME_O2 int validate_simple_palettes(const TextDecoder *decoder,
                                               u8 color) {
    if (decoder->depth || decoder->ended || decoder->invalid ||
            decoder->limit_end)
        return -1;
    const u8 *data = decoder->data[0];
    u32 length = decoder->lengths[0];
    u32 position = decoder->positions[0];
    int glyph_bank = -1;
    int bank = (int)div3(color);
    for (;;) {
        if (position >= length)
            return TEXT_MALFORMED_INPUT;
        u8 value = data[position];
        if (value >= 0x20) {
            if (value >= 0x80 && value <= 0x9f) {
                if (position + 1 >= length || !data[position + 1])
                    return TEXT_MALFORMED_INPUT;
                position += 2;
            } else {
                ++position;
            }
            if (glyph_bank >= 0 && glyph_bank != bank)
                return TEXT_LAYOUT_OVERFLOW;
            glyph_bank = bank;
        } else if (value == 0) {
            return TEXT_END;
        } else if (value == 1) {
            if (position + 1 >= length)
                return TEXT_MALFORMED_INPUT;
            u8 next = data[position + 1];
            position += 2;
            if (!colour_fits(next))
                return TEXT_LAYOUT_OVERFLOW;
            bank = (int)div3(next);
        } else if (value == 10) {
            ++position;
        } else {
            return -1;
        }
    }
}

static __attribute__((noinline)) TextStatus validate_palettes(
        TextDecoder *decoder, u8 initial_color) {
    int simple = validate_simple_palettes(decoder, initial_color);
    if (simple >= 0)
        return (TextStatus)simple;
    TextDecoder cursor = *decoder;
    u8 color = initial_color;
    int glyph_bank = -1;
    for (;;) {
        TextToken token;
        TextStatus status = text_decoder_next(&cursor, &token);
        if (status == TEXT_END)
            return TEXT_END;
        if (status != TEXT_OK)
            return status;
        if (token.kind == TEXT_TOKEN_GLYPH) {
            int bank = (int)div3(color);
            if (glyph_bank >= 0 && glyph_bank != bank)
                return TEXT_LAYOUT_OVERFLOW;
            glyph_bank = bank;
        } else if (token.kind == TEXT_TOKEN_COLOR) {
            if (!colour_fits(token.a))
                return TEXT_LAYOUT_OVERFLOW;
            color = token.a;
        }
    }
}

static __attribute__((always_inline)) inline CursorState *cursor_state(Window *window) {
    if (window->slot >= 10)
        return 0;
    return &CURSOR_STATES[window->slot];
}

static void set_cursor(Window *window, int column, int row) {
    if (!(window->flags & CURSOR_MARK))
        reset_field_states(window);
    else
        end_field(window);
    window->column = (int16_t)column;
    window->row = (int16_t)row;
    CursorState *saved = cursor_state(window);
    if (!saved) {
        window->flags &= ~CURSOR_MARK;
        return;
    }
    saved->x = (int16_t)(column * 8 + text_inset(window));
    saved->previous = -1;
    saved->column = (u8)column;
    saved->row = (u8)row;
    window->flags |= CURSOR_MARK;
}

static void load_state(Window *window, TextLayoutState *state) {
    CursorState *saved = cursor_state(window);
    int valid = saved && (window->flags & CURSOR_MARK) &&
                saved->column == window->column && saved->row == window->row;
    state->x = (int16_t)(window->column * 8 + text_inset(window));
    state->y = (int16_t)(window->row * 8);
    state->previous = -1;
    state->color = window->color;
    state->initialized = 1;
    if (valid) {
        state->x = saved->x;
        state->previous = saved->previous;
    } else {
        end_field(window);
    }
    window->flags &= ~CURSOR_MARK;
}

static void save_state(Window *window, const TextLayoutState *state) {
    CursorState *saved = cursor_state(window);
    if (window->flags & 0x10) {
        int column = (state->x - text_inset(window) + 7) >> 3;
        if (column < 0)
            column = 0;
        if (column > 31)
            column = 31;
        window->column = (int16_t)column;
    }
    window->row = (int16_t)(state->y >> 3);
    if (saved) {
        saved->x = state->x;
        saved->previous = state->previous;
        saved->column = (u8)window->column;
        saved->row = (u8)window->row;
        window->flags |= CURSOR_MARK;
    }
}

static __attribute__((always_inline)) inline TextStatus render_layout_work(
        const TextProfile *profile, TextDecoder *decoder,
        RenderContext *context, TextLayoutResult *result,
        TextLayoutCursor *cursor, TextEvent *event, u32 blank) {
    TextStatus status = text_layout_begin(profile, decoder, &context->state,
                                          cursor, result);
    while (status == TEXT_OK) {
        u16 blank_count = (u16)blank;
        u8 blank_unit = (u8)(blank >> 16);
        u16 blank_code = blank_unit == 2 ? 0x8140 : 0x20;
        if (text_layout_scanning(cursor)) {
            int peek = blank ? text_layout_blank_peek(
                &runtime_font_data, profile, decoder, &context->state,
                cursor, result, event, blank_code, blank_unit, blank_count) : -1;
            if (peek < 0) {
                blank = 0;
                // Frame waits let window reordering overwrite the cached glyph plan.
                if (context->direct || !(context->window->flags & 0x10))
                    peek = text_layout_simple_peek(
                        &runtime_font_data, profile, decoder, &context->state,
                        cursor, result, event);
            }
            status = peek < 0 ? text_layout_scan_peek(
                &runtime_font_data, profile, decoder, &context->state,
                cursor, result, event) : (TextStatus)peek;
        } else if (blank) {
            if ((u8)(context->state.color - context->palette * 3) >= 3) {
                status = TEXT_LAYOUT_OVERFLOW;
                break;
            }
            text_layout_blank_commit(&runtime_font_data, profile, decoder,
                                     &context->state, cursor, result,
                                     blank_code, blank_unit, blank_count);
            context->window->column =
                (int16_t)(context->window->column + blank_count);
            blank = 0;
            status = text_layout_emit_peek(
                &runtime_font_data, profile, decoder, &context->state,
                cursor, result, event);
        } else if (text_layout_simple_emit(&runtime_font_data, profile, decoder,
                                           &context->state, cursor, event) < 0) {
            status = text_layout_emit_peek(
                &runtime_font_data, profile, decoder, &context->state,
                cursor, result, event);
        }
        if (status != TEXT_OK)
            break;
        int commit_first = event->kind == TEXT_EVENT_COLOR ||
                           event->kind == TEXT_EVENT_POSITION ||
                           event->kind == TEXT_EVENT_ALIGN ||
                           event->kind == TEXT_EVENT_REGION ||
                           event->kind == TEXT_EVENT_LINE ||
                           event->kind == TEXT_EVENT_PAGE;
        if (event->kind == TEXT_EVENT_LINE_BEGIN) {
            fit_window_line(context, event);
            status = prepare_rect(context, event);
            if (status == TEXT_OK && event->advance_right > event->advance_left)
                clear_previous_field(context, event->value);
            if (status == TEXT_OK && context->replace)
                replace_line_field(context, event);
            if (status == TEXT_OK)
                prepare_field_line(context, event);
            if (status == TEXT_OK)
                status = text_layout_commit(&runtime_font_data, profile,
                                            decoder, &context->state,
                                            cursor, result, event);
        } else if (commit_first) {
            status = text_layout_commit(&runtime_font_data, profile, decoder,
                                        &context->state, cursor, result,
                                        event);
            if (status == TEXT_OK)
                status = render_event(context, event);
        } else {
            status = render_event(context, event);
            if (status == TEXT_OK)
                status = text_layout_commit(&runtime_font_data, profile,
                                            decoder, &context->state,
                                            cursor, result, event);
        }
    }
    if (status != TEXT_END) {
        result->status = (u8)status;
        result->consumed = decoder->positions[0];
    }
    return status;
}

static __attribute__((always_inline)) inline TextStatus render_layout(
        const TextProfile *profile, TextDecoder *decoder,
        RenderContext *context, TextLayoutResult *result,
        TextLayoutCursor *cursor, TextEvent *event, u32 blank) {
    return render_layout_work(profile, decoder, context, result,
                              cursor, event, blank);
}

static __attribute__((always_inline)) inline TextStatus measure_layout(
        const TextProfile *profile, TextDecoder *decoder,
        TextLayoutState *state, TextLayoutResult *result) {
    TextLayoutCursor cursor;
    TextEvent event;
    TextStatus status = text_layout_begin(profile, decoder, state,
                                          &cursor, result);
    while (status == TEXT_OK) {
        if (text_layout_scanning(&cursor)) {
            int peek = text_layout_simple_peek(
                &runtime_font_data, profile, decoder, state,
                &cursor, result, &event);
            status = peek < 0 ? text_layout_scan_peek(
                &runtime_font_data, profile, decoder, state,
                &cursor, result, &event) : (TextStatus)peek;
        } else if (text_layout_simple_emit(&runtime_font_data, profile, decoder,
                                           state, &cursor, &event) < 0) {
            status = text_layout_emit_peek(
                &runtime_font_data, profile, decoder, state,
                &cursor, result, &event);
        }
        if (status == TEXT_OK)
            status = text_layout_commit(&runtime_font_data, profile, decoder,
                                        state, &cursor, result, &event);
    }
    if (status != TEXT_END) {
        result->status = (u8)status;
        result->consumed = decoder->positions[0];
    }
    return status;
}

// Packs the count of a text made only of one space unit with the unit size
// in bits 16 and up, or returns 0.
static u32 blank_units(const u8 *text, size_t input_length) {
    if (input_length < 2)
        return 0;
    size_t length = input_length - 1;
    if (text[0] == 0x81) {
        if (length & 1)
            return 0;
        for (size_t at = 0; at < length; at += 2)
            if (text[at] != 0x81 || text[at + 1] != 0x40)
                return 0;
        return (u32)(length >> 1) | (2u << 16);
    }
    for (size_t at = 0; at < length; ++at)
        if (text[at] != 0x20)
            return 0;
    return (u32)length | (1u << 16);
}

static size_t speaker_field_length(const u8 *text, size_t length) {
    if (length < 5 || text[0] != 1 || text[1] != 2)
        return 0;
    size_t position = 2;
    while (position < length) {
        u8 value = text[position];
        if (value == 10)
            return position + 2 < length && text[position + 1] == 1
                ? position : 0;
        if (!value)
            return 0;
        size_t unit = value == 1 || value == 4 || value == 6 ? 2 :
            value == 2 || value == 7 || value == 8 ? 3 :
            value >= 0x80 && value <= 0x9f ? 2 : 1;
        if (position + unit >= length)
            return 0;
        position += unit;
    }
    return 0;
}

static __attribute__((always_inline)) inline const u8 *render_window_profile(
        Window *window, const u8 *text,
        int field_right, int tabular_advance, u8 alignment,
        int track_field) {
    size_t input_length = bounded_length(text);
    if (!input_length || !colour_fits(window->color) || window->column < 0 ||
            window->row < -1 || window->width < 3 || window->width > 30 ||
            window->height < 3 ||
            window->width * window->height > (0x4d0 - 0x1e) / 2)
        return text;
    WindowWorkspace *workspace = window_workspace(window);
    if (!workspace)
        return text;
    int blank = blank_units(text, input_length) != 0;
    const u8 *field = (const u8 *)0x02021774;
    size_t field_length = blank ? 0 : bounded_length(field);
    TextDecoder *decoder = &workspace->decoder;
    TextProfile *profile = &workspace->profile;
    TextLayoutResult *result = &workspace->result;
    text_decoder_init_raw(decoder, text, input_length,
                          field, field_length, 0);
    if (!blank && validate_palettes(decoder, window->color) != TEXT_END)
        return text;
    int title = window->row == -1;
    if (title)
        track_field = 0;
    TextProfileKind kind = title ? TEXT_PROFILE_COMPACT_ROW :
        tabular_advance ? TEXT_PROFILE_NUMBER :
        (window->flags & 0x40) ?
            (window->width <= 22 ? TEXT_PROFILE_PORTRAIT_DIALOGUE :
                                   TEXT_PROFILE_FULL_DIALOGUE) :
            TEXT_PROFILE_LABEL;
    if (!(window->flags & CURSOR_MARK))
        reset_field_states(window);
    RenderContext *context = &workspace->context;
    u32 saved_flags = window->flags;
    load_state(window, &context->state);
    int field_left = context->state.x;
    int field_top = context->state.y;
    context->window = window;
    int available = 1;
    if (!(window->flags & 0x10) &&
            (field_left < 0 || field_left > (window->width - 2) * 8 ||
             field_top < -8 || field_top >= (window->height - 2) * 8)) {
        window->flags = saved_flags;
        return text;
    }
    context->prior = track_field
        ? previous_field_bounds(window, field_left, field_top, track_field, &available) : 0;
    if (track_field && !(window->flags & 0x10) && !available) {
        window->flags = saved_flags;
        return text;
    }
    context->replace = (window->flags & 0x10) ? 0 : (u8)track_field;
    context->cleared = !context->prior || field_is_active(context->prior);
    context->palette = (u8)div3(window->color);
    context->tile_columns = (u8)(window->width - 2);
    context->tile_rows = (u8)(window->height - 2);
    context->direct = 0;
    // Right-aligned glyphs end on their ink, so their advance boxes pass the field edge.
    context->clip_right = alignment == TEXT_ALIGN_RIGHT && field_right < 255
        ? (u8)(field_right + 1) : 0;
    TextStatus status;
    const u8 *render_text = text;
    size_t speaker_length = kind == TEXT_PROFILE_PORTRAIT_DIALOGUE ||
                            kind == TEXT_PROFILE_FULL_DIALOGUE
        ? speaker_field_length(text, input_length) : 0;
    if (speaker_length) {
        text_profile_init(profile, TEXT_PROFILE_SPEAKER,
                          (int16_t)((window->width - 2) * 8),
                          (int16_t)(context->state.y + 16));
        profile->left = (int16_t)text_inset(window);
        profile->top = context->state.y;
        bind_surface(context, profile->top);
        text_decoder_init_raw(decoder, text, speaker_length,
                              field, field_length, 1);
        status = render_layout(profile, decoder, context, result,
                               &workspace->cursor, &workspace->event, 0);
        if (status != TEXT_END) {
            window->flags |= 2;
            save_state(window, &context->state);
            return text + result->consumed;
        }
        next_line(window, 2);
        context->state.x = profile->left;
        context->state.y = (int16_t)(window->row * 8);
        context->state.previous = -1;
        context->cleared = 0;
        render_text = text + speaker_length + 1;
        input_length -= speaker_length + 1;
    }
    if (text_profile_init(profile, kind,
            (int16_t)((window->width - 2) * 8),
            (int16_t)(title ? 8 : (window->height - 2) * 8)) != TEXT_OK)
        return text;
    profile->left = (int16_t)text_inset(window);
    profile->top = (int16_t)(title ? -8 : 0);
    profile->bottom = (int16_t)(title ? 0 : (window->height - 2) * 8);
    profile->wrap = (window->flags & 0x50) ? TEXT_WRAP_WORD : TEXT_WRAP_NONE;
    profile->tabular_advance = (u8)tabular_advance;
    profile->paginate = (window->flags & 0x10) != 0;
    if (alignment != TEXT_ALIGN_LEFT) {
        profile->left = (int16_t)field_left;
        profile->right = (int16_t)field_right;
        profile->alignment = alignment;
    }
    bind_surface(context, profile->top);
    text_decoder_init_raw(decoder, render_text, input_length,
                          field, field_length, 0);
    status = render_layout(profile, decoder, context, result,
                           &workspace->cursor, &workspace->event,
                           !speaker_length && !(window->flags & 0x10) &&
                           profile->wrap == TEXT_WRAP_NONE
                               ? blank_units(render_text, input_length) : 0);
    window->flags |= 2;
    if (context->replace && (status == TEXT_END ||
            (context->cleared && result->glyph_count))) {
        clear_previous_field(context, context->state.color);
        release_empty_field_tiles(context);
        save_field_bounds(window, field_left, field_top,
                          result, track_field);
    }
    save_state(window, &context->state);
    if (status == TEXT_END)
        return render_text + (result->consumed ? result->consumed - 1 : 0);
    return render_text + result->consumed;
}

static const u8 *unpack_menu_row(const u8 *text, const u8 **stored_end);

static int in_menu_records(const u8 *text) {
    return (u32)text >= (u32)MENU_RECORDS &&
           (u32)text < (u32)MENU_RECORDS + MENU_SLOTS * MENU_BANK_SIZE;
}

// A list row's leading full-width space reserves the native icon column.
static __attribute__((noinline)) const u8 *reserve_icon_column(
        Window *window, const u8 *text) {
    size_t prefix = text[0] == 1 ? 2 : 0;
    if (text[prefix] != 0x81 || text[prefix + 1] != 0x40)
        return text;
    size_t at = 0;
    for (size_t i = 0; i < prefix; ++i)
        FORMAT_OUTPUT[at++] = text[i];
    for (const u8 *rest = text + prefix + 2; *rest && at < MENU_TEXT_LIMIT; ++rest)
        FORMAT_OUTPUT[at++] = *rest;
    FORMAT_OUTPUT[at] = 0;
    set_cursor(window, window->column + 1, window->row);
    return FORMAT_OUTPUT;
}

__attribute__((noinline)) RUNTIME_O2 const u8 *vwf_render(
        Window *window, const u8 *text) {
    const u8 *stored_end = 0;
    const u8 *decoded = unpack_menu_row(text, &stored_end);
    if (!decoded)
        return text;
    if (in_menu_records(text) && window->row != -1) {
        const u8 *row = decoded;
        decoded = reserve_icon_column(window, decoded);
        if (decoded != row && !stored_end)
            stored_end = text + bounded_length(text) - 1;
    }
    text = decoded;
    size_t title_length = window->row == -1 ? bounded_length(text) : 0;
    const u8 *end = render_window_profile(window, text, 0, 0, TEXT_ALIGN_LEFT, 2);
    if (stored_end)
        return stored_end;
    return title_length ? text + title_length - 1 : end;
}

static TextStatus write_menu_units(TextWriter *writer, const u8 *text,
                                   size_t length);
void vwf_clear_window_all(u32 slot);
void vwf_clear_window(u32 slot);

static const u8 *indexed_format_field(const u8 *text, size_t length,
                                      u32 *ordinal, int *kind, size_t *size) {
    for (size_t position = 0; position + 3 < length; ++position) {
        u8 value = text[position];
        if (value == 2 || value == 7 || value == 8) {
            position += 2;
            continue;
        }
        if (value == 1 || value == 4 || value == 6 ||
                (value >= 0x80 && value <= 0x9f)) {
            ++position;
            continue;
        }
        if (text[position] != '%' || text[position + 1] < '1' ||
                text[position + 1] > '9')
            continue;
        u32 number = 0;
        size_t cursor = position + 1;
        while (cursor < length && text[cursor] >= '0' && text[cursor] <= '9') {
            number = number * 10 + text[cursor] - '0';
            if (number > 63)
                break;
            ++cursor;
        }
        if (number && number <= 63 && cursor + 1 < length &&
                text[cursor] == '$' &&
                (text[cursor + 1] == 'd' || text[cursor + 1] == 's' ||
                 text[cursor + 1] == 'v')) {
            *ordinal = number;
            *kind = text[cursor + 1];
            *size = cursor + 2 - position;
            return text + position;
        }
    }
    return 0;
}

static u32 menu_format_address(const u8 *text) {
    u32 address = (u32)text;
    return address >= 0x08000000u && address < 0x09000000u ? address : 0;
}

static const u8 *menu_format_start(u32 address) {
    return (const u8 *)address;
}

typedef struct {
    Window *window;
    FormatCache *cache;
    u32 visited;
    int band;
    u8 color;
} FormatSurface;

typedef struct {
    const u8 *text;
    size_t length, start, at;
    u32 slot, column, row, height, color, next_color;
} RowCapture;

typedef struct {
    FormatSurface surface;
    TextLayoutState state;
    TextTileSurface tiles;
    TextWriter writer;
    u16 starts[FORMAT_ROWS];
    u16 ends[FORMAT_ROWS];
    u32 rows;
    int16_t glyph_top, glyph_bottom, glyph_left, glyph_right;
    RowCapture capture;
    u8 complex;
} FormatWorkspace;

#define FORMAT_WORKSPACE ((FormatWorkspace *)0x0203FA30)
typedef char FormatWorkspaceFits[(sizeof(FormatWorkspace) <= 0xd0) ? 1 : -1];

static RUNTIME_O2 TextStatus flush_format_band(FormatSurface *surface) {
    if (surface->band < 0)
        return TEXT_OK;
    Window *window = surface->window;
    int columns = window->width - 2;
    u32 *buffer = (u32 *)MEM(u32, 0x02021654);
    for (int row = 0; row < 2; ++row) {
        int y = surface->band + row;
        if (y >= window->height - 2)
            break;
        for (int x = 0; x < columns; ++x) {
            u16 *cell = &window->tiles[(y + 1) * window->width + x + 1];
            u32 *pixels = FORMAT_PIXELS + (row * 32 + x) * 8;
            int id = tile_buffer_id(*cell);
            u32 ink = 0;
            for (int i = 0; i < 8; ++i)
                ink |= pixels[i];
            if (!(ink & 0x33333333u)) {
                if (id >= 0) {
                    release((u16)id);
                    *cell = (u16)((MEM(u32, 0x02021664) + 1) |
                                   MEM(u16, 0x02021668));
                }
                continue;
            }
            if (id < 0) {
                u16 fresh;
                if (!allocate(1, &fresh) && !take_released_tile(&fresh))
                    return TEXT_TILE_EXHAUSTED;
                reserve(fresh);
                id = fresh;
                *cell = (u16)((MEM(u32, 0x02021670) + fresh) |
                    (MEM(u16, 0x02021668) +
                     (div3(surface->color) << 12)));
            }
            for (int i = 0; i < 8; ++i)
                if (buffer[id * 8 + i] != pixels[i])
                    buffer[id * 8 + i] = pixels[i];
        }
    }
    window->flags |= 2;
    return TEXT_OK;
}

static RUNTIME_O2 TextStatus load_format_band(FormatSurface *surface, int y) {
    int band = y >> 3;
    if (surface->band >= 0 && band >= surface->band && band < surface->band + 2)
        return TEXT_OK;
    if (band == surface->band)
        return TEXT_OK;
    surface->band = band;
    Window *window = surface->window;
    int columns = window->width - 2;
    u32 *buffer = (u32 *)MEM(u32, 0x02021654);
    u32 fill = (surface->color - div3(surface->color) * 3 + 1) * 0x44444444u;
    for (int row = 0; row < 2; ++row) {
        int tile_y = band + row;
        if (tile_y >= window->height - 2)
            break;
        int first_visit = !(surface->visited & (1u << tile_y));
        int left = surface->cache->left[tile_y];
        int right = surface->cache->right[tile_y];
        for (int x = 0; x < columns; ++x) {
            int id = tile_buffer_id(window->tiles[
                (tile_y + 1) * window->width + x + 1]);
            u32 mask = 0;
            int from = left - x * 8;
            int to = right - x * 8;
            if (first_visit && from < 8 && to > 0 && from < to) {
                mask = 0xffffffffu;
                if (from > 0)
                    mask <<= from * 4;
                if (to < 8)
                    mask &= 0xffffffffu >> ((8 - to) * 4);
            }
            for (int i = 0; i < 8; ++i) {
                u32 prior = id < 0 ? fill : buffer[id * 8 + i];
                FORMAT_PIXELS[(row * 32 + x) * 8 + i] =
                    (prior & ~mask) | (fill & mask);
            }
        }
        if (first_visit) {
            surface->cache->left[tile_y] = 255;
            surface->cache->right[tile_y] = 0;
            surface->visited |= 1u << tile_y;
        }
    }
    return TEXT_OK;
}

static u32 *format_tile_words(void *opaque, int x, int y) {
    FormatSurface *surface = opaque;
    if (x < 0 || x >= (surface->window->width - 2) * 8 ||
            y < surface->band * 8 || y >= (surface->band + 2) * 8 ||
            y >= (surface->window->height - 2) * 8)
        return 0;
    return FORMAT_PIXELS + (((y >> 3) - surface->band) * 32 + (x >> 3)) * 8;
}

static __attribute__((noinline)) RUNTIME_O2 TextStatus paint_format_glyph(
        FormatSurface *surface, const TextPlacement *glyph) {
    int top = glyph->ink_y;
    int bottom = top + glyph->height;
    int left = glyph->ink_x + glyph->clip_left;
    if (left < 0)
        left = 0;
    int right = glyph->ink_x + glyph->width - glyph->clip_right;
    int width = (surface->window->width - 2) * 8;
    int height = (surface->window->height - 2) * 8;
    if (right > width)
        right = width;
    if (bottom > height)
        bottom = height;
    if (top < 0)
        top = 0;
    if (right <= left || bottom <= top)
        return TEXT_OK;
    FORMAT_WORKSPACE->glyph_top = (int16_t)top;
    FORMAT_WORKSPACE->glyph_bottom = (int16_t)bottom;
    FORMAT_WORKSPACE->glyph_left = (int16_t)left;
    FORMAT_WORKSPACE->glyph_right = (int16_t)right;
    TextTileSurface *tiles = &FORMAT_WORKSPACE->tiles;
    tiles->context = surface;
    tiles->get = format_tile_words;
    for (int y = top; y < FORMAT_WORKSPACE->glyph_bottom;) {
        TextStatus status = TEXT_OK;
        if (surface->band < 0 || y < surface->band * 8 ||
                y >= (surface->band + 2) * 8)
            status = flush_format_band(surface);
        if (status != TEXT_OK)
            return status;
        status = load_format_band(surface, y);
        if (status != TEXT_OK)
            return status;
        status = text_compose_glyph_tiles_blended(&runtime_font_data, glyph, tiles,
            (u8)(glyph->color - div3(glyph->color) * 3 + 1));
        if (status != TEXT_OK)
            return status;
        for (int row = FORMAT_WORKSPACE->glyph_top >> 3;
                row <= (FORMAT_WORKSPACE->glyph_bottom - 1) >> 3; ++row) {
            if (row < surface->band || row >= surface->band + 2)
                continue;
            if (FORMAT_WORKSPACE->glyph_left < surface->cache->left[row])
                surface->cache->left[row] = (u8)FORMAT_WORKSPACE->glyph_left;
            if (FORMAT_WORKSPACE->glyph_right > surface->cache->right[row])
                surface->cache->right[row] = (u8)FORMAT_WORKSPACE->glyph_right;
        }
        y = (surface->band + 2) * 8;
    }
    return TEXT_OK;
}

static __attribute__((noinline)) RUNTIME_O2 TextStatus paint_format(
        Window *window, IndexedFormat *format) {
    WindowWorkspace *work = MENU_WORKSPACE;
    FormatSurface *surface = &FORMAT_WORKSPACE->surface;
    TextLayoutState *state = &FORMAT_WORKSPACE->state;
    surface->window = window;
    surface->cache = &FORMAT_CACHE[window->slot];
    surface->visited = ~FORMAT_WORKSPACE->rows;
    surface->band = -1;
    surface->color = format->base_color;
    state->x = (int16_t)text_inset(window);
    state->y = 0;
    state->previous = -1;
    state->color = format->base_color;
    state->initialized = 1;
    text_profile_init(&work->profile, TEXT_PROFILE_LABEL,
        (int16_t)((window->width - 2) * 8),
        (int16_t)((window->height - 2) * 8));
    work->profile.left = state->x;
    work->profile.wrap = window->flags & 0x50 ? TEXT_WRAP_WORD : TEXT_WRAP_NONE;
    if (format->repeat & FORMAT_ROW) {
        work->profile.tabular_advance = (u8)text_font_digit_advance(
            &runtime_font_data, TEXT_FACE_TALL);
        work->profile.compact_tabular_advance = (u8)text_font_digit_advance(
            &runtime_font_data, TEXT_FACE_COMPACT);
    }
    const u8 *player = (const u8 *)0x02021774;
    text_decoder_init_raw(&work->decoder, FORMAT_OUTPUT,
        bounded_length(FORMAT_OUTPUT), player, bounded_length(player), 0);
    TextStatus status = validate_palettes(&work->decoder, format->base_color);
    if (status != TEXT_END)
        return status;
    status = text_layout_begin(&work->profile, &work->decoder,
        state, &work->cursor, &work->result);
    while (status == TEXT_OK) {
        if (text_layout_scanning(&work->cursor)) {
            int peek = text_layout_simple_peek(&runtime_font_data, &work->profile,
                &work->decoder, state, &work->cursor, &work->result, &work->event);
            status = peek < 0 ? text_layout_scan_peek(&runtime_font_data,
                &work->profile, &work->decoder, state, &work->cursor,
                &work->result, &work->event) : (TextStatus)peek;
        } else {
            status = text_layout_emit_peek(&runtime_font_data, &work->profile,
                &work->decoder, state, &work->cursor, &work->result, &work->event);
        }
        if (status != TEXT_OK)
            break;
        if (work->event.kind == TEXT_EVENT_GLYPH) {
            status = paint_format_glyph(surface, &work->event.glyph);
            if (status != TEXT_OK)
                break;
        }
        status = text_layout_commit(&runtime_font_data, &work->profile,
            &work->decoder, state, &work->cursor, &work->result, &work->event);
    }
    if (status != TEXT_END)
        return status;
    for (int row = 0; row < window->height - 2; ++row)
        if (!(surface->visited & (1u << row)) &&
                surface->cache->right[row] > surface->cache->left[row]) {
            status = flush_format_band(surface);
            if (status != TEXT_OK)
                return status;
            status = load_format_band(surface, row * 8);
            if (status != TEXT_OK)
                return status;
        }
    return flush_format_band(surface);
}

static int compose_indexed_format(Window *window, IndexedFormat *format);

static int split_format_rows(Window *window, size_t length) {
    FormatWorkspace *work = FORMAT_WORKSPACE;
    if ((window->flags & 0x50) || work->complex ||
            (FORMAT_OUTPUT[0] != 7 && FORMAT_OUTPUT[0] != 2))
        return 0;
    for (int row = 0; row < FORMAT_ROWS; ++row)
        work->starts[row] = work->ends[row] = 0;
    int row = -1, span = 0, newline = 0;
    for (size_t at = 0; at + 1 < length;) {
        u8 value = FORMAT_OUTPUT[at];
        if (value == 2 || value == 7) {
            int next = FORMAT_OUTPUT[at + 2];
            if (next >= window->height - 2 || next < row ||
                    (next != row && row >= 0 && next < row + span))
                return 0;
            if (next != row) {
                if (row >= 0)
                    work->ends[row] = (u16)at;
                row = next;
                work->starts[row] = (u16)at;
                span = 0;
            }
            newline = 0;
        } else if (value == 1 || value == 3) {
            return 0;
        } else if (value == 10) {
            if (newline)
                return 0;
            newline = 1;
        } else if (value >= 0x20) {
            if (newline)
                return 0;
            int height = value >= 0x80 && value <= 0x9f ? 2 : 1;
            if (span < height)
                span = height;
        }
        at += value == 2 || value == 7 || value == 8 ? 3 :
              value == 4 || value == 6 ||
              (value >= 0x80 && value <= 0x9f) ? 2 : 1;
    }
    work->ends[row] = (u16)(length - 1);
    return 1;
}

static __attribute__((noinline)) void select_format_rows(Window *window, IndexedFormat *format,
                                size_t length) {
    FormatWorkspace *work = FORMAT_WORKSPACE;
    FormatCache *cache = &FORMAT_CACHE[window->slot];
    work->rows = (1u << (window->height - 2)) - 1;
    int was_simple = cache->simple;
    cache->simple = (u8)split_format_rows(window, length);
    if (!cache->hash || !was_simple || !cache->simple)
        return;
    const u8 *text = menu_format_start(format->address);
    size_t size = bounded_length(text);
    u32 dirty = 0, row = 0;
    for (size_t at = text[0] == '~' || text[0] == '^'; at + 1 < size;) {
        u8 value = text[at];
        if (value == 2 || value == 7)
            row = text[at + 2];
        if (value == '%' && text[at + 1] >= '1' && text[at + 1] <= '9') {
            u32 ordinal = 0;
            size_t end = at + 1;
            while (text[end] >= '0' && text[end] <= '9')
                ordinal = ordinal * 10 + text[end++] - '0';
            if (ordinal && ordinal <= 63 && text[end] == '$' &&
                    (cache->changed[(ordinal - 1) >> 5] &
                     (1u << ((ordinal - 1) & 31))))
                dirty |= 1u << row;
        }
        at += value == 2 || value == 7 || value == 8 ? 3 :
              value == 1 || value == 4 || value == 6 ||
              (value >= 0x80 && value <= 0x9f) ? 2 : 1;
    }
    u32 rows = 0;
    size_t output = 0;
    for (int y = 0; y < window->height - 2; ++y) {
        if (!(dirty & (1u << y)) || !work->ends[y])
            continue;
        int bottom = y + 1;
        while (bottom < window->height - 2 && !work->ends[bottom])
            ++bottom;
        rows |= ((1u << bottom) - 1) & ~((1u << y) - 1);
        for (size_t at = work->starts[y]; at < work->ends[y]; ++at)
            FORMAT_OUTPUT[output++] = FORMAT_OUTPUT[at];
    }
    if (!rows)
        return;
    FORMAT_OUTPUT[output] = 0;
    work->rows = rows;
}

static __attribute__((noinline, used)) void paint_indexed_format(u32 slot) {
    Window *window = get_window((u8)slot);
    IndexedFormat *format = indexed_format(window);
    if (format && format->magic == INDEXED_FORMAT_MAGIC)
        format->repeat |= FORMAT_DIRTY | FORMAT_READY;
}

void vwf_refresh(void) {
    for (u32 slot = 0; slot < 10; ++slot) {
        Window *window = get_window((u8)slot);
        if (!(window->flags & 1) || window->width < 3 || window->width > 30 ||
                window->height < 3 || window->height > FORMAT_ROWS + 2)
            continue;
        IndexedFormat *format = indexed_format(window);
        if (!format || format->magic != INDEXED_FORMAT_MAGIC ||
                !(format->repeat & FORMAT_DIRTY) ||
                !(format->repeat & FORMAT_READY) ||
                (!(format->repeat & FORMAT_ROW) && format->next != format->count))
            continue;
        FormatCache *cache = &FORMAT_CACHE[slot];
        if (cache->hash && !cache->changed[0] && !cache->changed[1]) {
            format->repeat &= (u8)~FORMAT_DIRTY;
            continue;
        }
        FORMAT_WORKSPACE->complex = 0;
        if (!compose_indexed_format(window, format))
            continue;
        u32 hash = 2166136261u;
        size_t length = bounded_length(FORMAT_OUTPUT);
        for (size_t i = 0; i < length; ++i)
            hash = (hash ^ FORMAT_OUTPUT[i]) * 16777619u;
        hash = (hash ^ format->base_color) * 16777619u;
        if (hash != cache->hash) {
            select_format_rows(window, format, length);
            if (paint_format(window, format) != TEXT_OK)
                continue;
            cache->hash = hash;
        }
        cache->changed[0] = cache->changed[1] = 0;
        format->repeat &= (u8)~FORMAT_DIRTY;
    }
    MEM(u8, 0x02021674) = 1;
}

static int format_has_region(const TextWriter *writer) {
    int region = 0;
    for (size_t at = 0; at < writer->length;) {
        u8 value = writer->data[at];
        if (value == 8)
            region = 1;
        else if (value == 2 || value == 7 || value == 10)
            region = 0;
        at += value == 2 || value == 7 || value == 8 ? 3 :
              value == 1 || value == 4 || value == 6 ||
              (value >= 0x80 && value <= 0x9f) ? 2 : 1;
    }
    return region;
}

static void check_format_value(const u8 *text, size_t length) {
    for (size_t at = 0; at < length;) {
        u8 value = text[at];
        if (value < 0x20) {
            FORMAT_WORKSPACE->complex = 1;
            return;
        }
        at += value >= 0x80 && value <= 0x9f ? 2 : 1;
    }
}

static const u8 *row_fragment_text(const u8 *fragment) {
    if (!(fragment[5] & ROW_ROM_TEXT))
        return fragment + 6;
    return (const u8 *)((u32)fragment[6] | ((u32)fragment[7] << 8) |
                       ((u32)fragment[8] << 16) | ((u32)fragment[9] << 24));
}

static __attribute__((noinline)) int write_row_fragments(
        TextWriter *writer, Window *window, IndexedFormat *format, u32 ordinal) {
    int previous_column = -1;
    int explicit_region = format_has_region(writer);
    for (;;) {
        int selected = -1;
        int next_column = 256;
        for (int i = 0; i < format->next; ++i) {
            const u8 *fragment = (const u8 *)format +
                sizeof(IndexedFormat) + i * format->string_bytes;
            if (fragment[0] == ordinal - 1 &&
                    fragment[1] > previous_column &&
                    fragment[1] < next_column) {
                selected = i;
                next_column = fragment[1];
            }
        }
        if (selected < 0)
            return 1;
        const u8 *fragment = (const u8 *)format +
            sizeof(IndexedFormat) + selected * format->string_bytes;
        const u8 *text = row_fragment_text(fragment);
        if (fragment[2] <= 1) {
            previous_column = next_column;
            continue;
        }
        if (!explicit_region) {
            int left = fragment[1] * 8;
            int right = (window->width - 2) * 8;
            if (fragment[4] && (fragment[5] & 3) == 2) {
                int field_right = left +
                    (fragment[4] + ((fragment[5] & 4) != 0)) * 8;
                if (field_right < right)
                    right = field_right;
            }
            if (left >= right) {
                previous_column = next_column;
                continue;
            }
            if (text_writer_control(writer, 8, (u8)left, (u8)right) != TEXT_OK)
                return 0;
            if (fragment[4] && (fragment[5] & 3) == 2 &&
                    text_writer_control(writer, 4, TEXT_ALIGN_RIGHT, 0) != TEXT_OK)
                return 0;
        } else if (previous_column >= 0) {
            if (text_writer_code(writer, text[0] >= 0x80 ? 0x8140 : ' ') != TEXT_OK)
                return 0;
        }
        if (fragment[3] != format->base_color &&
                text_writer_control(writer, 1, fragment[3], 0) != TEXT_OK)
            return 0;
        check_format_value(text, fragment[2] - 1);
        if (write_menu_units(writer, text, fragment[2] - 1) != TEXT_OK)
            return 0;
        if (fragment[3] != format->base_color &&
                text_writer_control(writer, 1, format->base_color, 0) != TEXT_OK)
            return 0;
        previous_column = next_column;
    }
}

static __attribute__((noinline)) int compose_indexed_format(
        Window *window, IndexedFormat *format) {
    const u8 *start = menu_format_start(format->address);
    size_t length = bounded_length(start);
    if (!length)
        return 0;
    const u8 *cursor = start + (start[0] == '~' || start[0] == '^');
    const u8 *end = start + length - 1;
    TextWriter *writer = &FORMAT_WORKSPACE->writer;
    text_writer_init(writer, FORMAT_OUTPUT, 1024);
    while (cursor < end) {
        u32 ordinal;
        int kind;
        size_t size;
        const u8 *field = indexed_format_field(
            cursor, (size_t)(end - cursor), &ordinal, &kind, &size);
        if (write_menu_units(writer, cursor,
                (size_t)((field ? field : end) - cursor)) != TEXT_OK)
            return 0;
        if (!field)
            break;
        if (format->repeat & FORMAT_ROW) {
            if (!write_row_fragments(writer, window, format, ordinal))
                return 0;
            cursor = field + size;
            continue;
        }
        IndexedValue *value = &format->values[ordinal - 1];
        if (kind == 'v')
            kind = value->flags & 0x80 ? 's' : 'd';
        u8 value_color = (value->flags >> 4) & 7;
        u8 value_mode = value->flags & 15;
        if (value_color != format->base_color &&
                text_writer_control(writer, 1, value_color, 0) != TEXT_OK)
            return 0;
        if (kind == 'd') {
            if (text_writer_number(writer, (int32_t)value->value,
                    value->digits & 15, value_mode,
                    value_mode & 8 ? TEXT_FACE_COMPACT : TEXT_FACE_TALL) != TEXT_OK)
                return 0;
        } else {
            const u8 *value_text = (const u8 *)window + value->value;
            size_t value_length = bounded_length(value_text);
            if (value_length)
                check_format_value(value_text, value_length - 1);
            if (!value_length || write_menu_units(
                    writer, value_text, value_length - 1) != TEXT_OK)
                return 0;
        }
        if (value_color != format->base_color &&
                text_writer_control(writer, 1,
                                    format->base_color, 0) != TEXT_OK)
            return 0;
        cursor = field + size;
    }
    return 1;
}

static u32 menu_text_columns(const u8 *text, size_t length) {
    u32 columns = 0;
    for (size_t at = 0; at + 1 < length;) {
        u8 first = text[at];
        if (first >= 0x20)
            ++columns;
        at += first == 2 || first == 7 || first == 8 ? 3 :
              first == 1 || first == 4 || first == 6 ||
              (first >= 0x80 && first <= 0x9f) ? 2 : 1;
    }
    return columns;
}

static __attribute__((noinline)) void discard_covered_fragments(
        IndexedFormat *format, u32 column, u32 row, u32 columns, u32 width,
        u32 replaced_column) {
    for (int i = 0; i < format->next;) {
        u8 *fragment = (u8 *)format + sizeof(IndexedFormat) +
            i * format->string_bytes;
        u32 span = fragment[4] ?
            (u32)fragment[4] + ((fragment[5] & 4) != 0) :
            menu_text_columns(row_fragment_text(fragment), fragment[2]);
        u32 right = fragment[1] + span;
        if (right > width)
            right = width;
        if (fragment[0] != row || fragment[1] == replaced_column ||
                fragment[1] < column || right > column + columns) {
            ++i;
            continue;
        }
        const u8 *last = (u8 *)format + sizeof(IndexedFormat) +
            --format->next * format->string_bytes;
        for (int byte = 0; byte < format->string_bytes; ++byte)
            fragment[byte] = last[byte];
    }
}

static __attribute__((noinline)) int capture_row_fragment(
                                  Window *window, int kind, int32_t number,
                                  u32 digits, u32 mode, u32 color,
                                  const u8 *text, u32 column, u32 row) {
    IndexedFormat *format = indexed_format(window);
    if (!format || format->magic != INDEXED_FORMAT_MAGIC ||
            !(format->repeat & FORMAT_ROW))
        return 0;
    if (text == (const u8 *)0x081061C4) {
        // Native padding clears the old field before its replacement moves to a new column.
        if (!(format->repeat & FORMAT_ROW_PADDING) || format->cursor_row != row) {
            format->cursor_column = (u8)column;
            format->cursor_row = (u8)row;
        }
        format->repeat |= FORMAT_ROW_PADDING;
        return 0;
    }
    if (row >= format->count || column > 255 ||
            (kind == 'd' && (!digits || digits > 10)))
        return 0;
    size_t text_length = kind == 's' ? bounded_length(text) : 0;
    // ROM text stays valid when window records move; RAM fields still need copies.
    int rom_text = kind == 's' && (u32)text >= 0x08000000u &&
        (u32)text < 0x0a000000u && text_length > format->string_bytes - 6u;
    if (kind == 's' && (!text_length || text_length > 255 ||
            (!rom_text && text_length > format->string_bytes - 6u)))
        return 0;
    if (rom_text)
        mode |= ROW_ROM_TEXT;
    u32 columns = kind == 'd' ? digits + ((mode & 4) != 0) :
        menu_text_columns(text, text_length);
    if (format->repeat & FORMAT_ROW_RESTART) {
        u32 matches = 0;
        int same_column = 0;
        for (int i = 0; i < format->next; ++i) {
            const u8 *fragment = (const u8 *)format + sizeof(IndexedFormat) +
                i * format->string_bytes;
            if (fragment[0] == row) {
                ++matches;
                same_column = fragment[1] == column;
            }
        }
        if (format->cursor_row == row && (matches != 1 || !same_column)) {
            for (int i = 0; i < format->next;) {
                u8 *fragment = (u8 *)format + sizeof(IndexedFormat) +
                    i * format->string_bytes;
                if (fragment[0] != row) {
                    ++i;
                    continue;
                }
                const u8 *last = (u8 *)format + sizeof(IndexedFormat) +
                    --format->next * format->string_bytes;
                for (int byte = 0; byte < format->string_bytes; ++byte)
                    fragment[byte] = last[byte];
                format_changed(window, row);
            }
        }
        format->repeat &= (u8)~FORMAT_ROW_RESTART;
    }
    u32 prior_count = format->next;
    u32 clear_column = column;
    if ((format->repeat & FORMAT_ROW_PADDING) && format->cursor_row == row &&
            format->cursor_column < column)
        clear_column = format->cursor_column;
    format->repeat &= (u8)~FORMAT_ROW_PADDING;
    discard_covered_fragments(format, clear_column, row,
                              column + columns - clear_column, window->width - 2, column);
    if (format->next != prior_count)
        format_changed(window, row);
    int selected = -1;
    for (int i = 0; i < format->next; ++i) {
        const u8 *fragment = (const u8 *)format +
            sizeof(IndexedFormat) + i * format->string_bytes;
        if (fragment[0] == row && fragment[1] == column) {
            selected = i;
            break;
        }
    }
    if (selected < 0) {
        if (format->next >= ROW_FORMAT_FRAGMENTS)
            return 0;
        format_changed(window, row);
        selected = format->next++;
    }
    u8 *fragment = (u8 *)format + sizeof(IndexedFormat) +
        selected * format->string_bytes;
    if (kind == 'd') {
        TextWriter *writer = &FORMAT_WORKSPACE->writer;
        text_writer_init(writer, FORMAT_OUTPUT, format->string_bytes - 6);
        if (text_writer_number(writer, number, (u8)digits,
                (u8)mode, mode & 8 ? TEXT_FACE_COMPACT : TEXT_FACE_TALL) != TEXT_OK)
            return 0;
        text = FORMAT_OUTPUT;
        text_length = writer->length + 1;
    }
    if (fragment[2] != text_length || fragment[3] != color ||
            fragment[4] != (kind == 'd' ? digits : 0) || fragment[5] != mode)
        format_changed(window, row);
    const u8 *stored_text = text;
    u32 rom_address = (u32)text;
    size_t stored_length = rom_text ? sizeof(rom_address) : text_length;
    if (rom_text)
        stored_text = (const u8 *)&rom_address;
    for (size_t i = 0; i < stored_length; ++i)
        if (fragment[6 + i] != stored_text[i]) {
            format_changed(window, row);
            break;
        }
    fragment[0] = (u8)row;
    fragment[1] = (u8)column;
    fragment[3] = (u8)color;
    fragment[4] = kind == 'd' ? (u8)digits : 0;
    fragment[5] = (u8)mode;
    for (size_t i = 0; i < stored_length; ++i)
        fragment[6 + i] = stored_text[i];
    fragment[2] = (u8)text_length;
    format->cursor_column = (u8)(column + columns);
    format->cursor_row = (u8)row;
    window->column = format->cursor_column;
    window->row = format->cursor_row;
    format->repeat |= FORMAT_DIRTY | FORMAT_READY;
    if (window != (Window *)0x0200A8A0)
        order_window(window->slot);
    return 1;
}

static __attribute__((noinline)) size_t row_lines_length(
        IndexedFormat *format, const u8 *text, u32 row) {
    size_t length = bounded_length(text);
    size_t start = 0;
    u32 next_row = row, height = 1;
    int multiline = 0;
    for (size_t at = 0; at < length;) {
        u8 value = text[at];
        if (!value || value == 10) {
            if (at - start + 1 > format->string_bytes - 6u || next_row >= format->count)
                return 0;
            if (!value)
                break;
            multiline = 1;
            next_row += height;
            height = 1;
            start = ++at;
        } else {
            if (value == 2 || value == 7 || value == 3)
                return 0;
            if (value >= 0x80 && value <= 0x9f)
                height = 2;
            at += value == 8 ? 3 : value == 1 || value == 4 || value == 6 ||
                (value >= 0x80 && value <= 0x9f) ? 2 : 1;
        }
    }
    return multiline ? length : 0;
}

static __attribute__((noinline)) int capture_row_lines(
        Window *window, u32 color, const u8 *text, u32 column, u32 row) {
    RowCapture *capture = &FORMAT_WORKSPACE->capture;
    capture->slot = window->slot;
    capture->text = text;
    capture->column = column;
    capture->row = row;
    capture->color = capture->next_color = color;
    capture->start = capture->at = 0;
    capture->height = 1;
    capture->length = row_lines_length(indexed_format(window), text, row);
    if (!capture->length)
        return 0;
    while (capture->at < capture->length) {
        u8 value = capture->text[capture->at];
        if (!value || value == 10) {
            for (size_t i = capture->start; i < capture->at; ++i)
                FORMAT_OUTPUT[i - capture->start] = capture->text[i];
            FORMAT_OUTPUT[capture->at - capture->start] = 0;
            if (!capture_row_fragment(get_window(capture->slot), 's', 0, 0, 0,
                    capture->color, FORMAT_OUTPUT, capture->column, capture->row))
                return 0;
            if (!value)
                break;
            capture->row += capture->height;
            capture->column = 0;
            capture->color = capture->next_color;
            capture->height = 1;
            capture->start = ++capture->at;
        } else {
            if (value == 1)
                capture->next_color = capture->text[capture->at + 1];
            if (value >= 0x80 && value <= 0x9f)
                capture->height = 2;
            capture->at += value == 8 ? 3 : value == 1 || value == 4 || value == 6 ||
                (value >= 0x80 && value <= 0x9f) ? 2 : 1;
        }
    }
    return 1;
}

static __attribute__((always_inline)) inline int capture_row_format(
        Window *window, int kind, int32_t number, u32 digits, u32 mode,
        u32 color, const u8 *text, u32 column, u32 row) {
    IndexedFormat *format = indexed_format(window);
    if (kind == 's' && format && format->magic == INDEXED_FORMAT_MAGIC &&
            (format->repeat & FORMAT_ROW) &&
            bounded_length(text) > format->string_bytes - 6u &&
            capture_row_lines(window, color, text, column, row))
        return 1;
    return capture_row_fragment(window, kind, number, digits, mode, color,
                                text, column, row);
}

static __attribute__((noinline)) int capture_indexed_format(
                                  Window *window, int kind, int32_t number,
                                  u32 digits, u32 mode, u32 color,
                                  const u8 *text) {
    if (text == (const u8 *)0x081061C4)
        return 0;
    IndexedFormat *format = indexed_format(window);
    if (!format || format->magic != INDEXED_FORMAT_MAGIC ||
            (format->repeat & FORMAT_ROW))
        return 0;
    if (format->next == format->count) {
        if (!(format->repeat & FORMAT_REPEAT))
            return 0;
        if (format->repeat & FORMAT_DIRTY)
            return 0;
        format->next = 0;
        format->string_bytes = 0;
    }
    IndexedValue *value = &format->values[format->next];
    u8 declared = value->digits & 0xc0;
    if ((declared == 0 && kind != 'd') ||
            (declared == 0x40 && kind != 's') ||
            (kind == 'd' && (!digits || digits > 10)))
        return 0;
    u8 flags = (u8)((mode & 15) | ((color & 7) << 4) |
                    (kind == 's' ? 0x80 : 0));
    if (value->digits != (declared | (u8)digits) || value->flags != flags)
        format_changed(window, format->next);
    if (kind == 's') {
        size_t text_length = bounded_length(text);
        u32 end = window_tile_end(window);
        u32 limit = (window->flags & 0x10) ?
            WINDOW_WORKSPACE_OFFSET : WINDOW_RECORD_SIZE;
        u32 start = end + sizeof(IndexedFormat) +
            format->count * sizeof(IndexedValue) + format->string_bytes;
        if (!text_length || start + text_length > limit)
            return 0;
        if (!FORMAT_CACHE[window->slot].hash ||
                FORMAT_CACHE[window->slot].changed[0] ||
                FORMAT_CACHE[window->slot].changed[1] || !(value->flags & 0x80) ||
                value->value + text_length > limit) {
            format_changed(window, format->next);
        } else {
            const u8 *prior = (const u8 *)window + value->value;
            for (size_t i = 0; i < text_length; ++i)
                if (prior[i] != text[i]) {
                    format_changed(window, format->next);
                    break;
                }
        }
        u8 *copy = (u8 *)window + start;
        for (size_t i = 0; i < text_length; ++i)
            copy[i] = text[i];
        // Window records move when the game changes their display order.
        value->value = start;
        format->string_bytes += text_length;
    } else {
        if (value->value != (u32)number)
            format_changed(window, format->next);
        value->value = (u32)number;
    }
    value->digits = declared | (u8)digits;
    value->flags = flags;
    ++format->next;
    if (format->next == format->count)
        format->repeat |= FORMAT_DIRTY | FORMAT_READY;
    if (window != (Window *)0x0200A8A0)
        order_window(window->slot);
    return 1;
}

static int indexed_format_active(Window *window) {
    IndexedFormat *format = indexed_format(window);
    return format && format->magic == INDEXED_FORMAT_MAGIC;
}

static __attribute__((noinline)) int start_indexed_format(Window *window, const u8 *text,
                                size_t length) {
    const u8 *cursor = text + (text[0] == '~' || text[0] == '^');
    const u8 *end = text + length - 1;
    u32 ordinal;
    int kind;
    size_t size;
    const u8 *first = indexed_format_field(
        cursor, (size_t)(end - cursor), &ordinal, &kind, &size);
    if (!first)
        return 0;
    u32 count = 0;
    for (const u8 *field = first; field; ) {
        if (ordinal > count)
            count = ordinal;
        cursor = field + size;
        field = indexed_format_field(
            cursor, (size_t)(end - cursor), &ordinal, &kind, &size);
    }
    IndexedFormat *format = indexed_format(window);
    u32 tile_end = window_tile_end(window);
    u32 limit = (window->flags & 0x10) ? WINDOW_WORKSPACE_OFFSET : WINDOW_RECORD_SIZE;
    u32 address = menu_format_address(text);
    if (!format || !address ||
            (text[0] == '^' ?
                tile_end + sizeof(IndexedFormat) + ROW_FORMAT_FRAGMENTS * 12 > limit :
                tile_end + sizeof(IndexedFormat) + count * sizeof(IndexedValue) > limit))
        return 0;
    int retain_bounds = format->magic == INDEXED_FORMAT_MAGIC;
    format->next = 0;
    format->count = (u8)count;
    format->address = address;
    format->base_color = window->color;
    format->repeat = text[0] == '^' ? 3 : text[0] == '~';
    format->string_bytes = text[0] == '^' ?
        (u16)((limit - tile_end - sizeof(IndexedFormat)) / ROW_FORMAT_FRAGMENTS) : 0;
    format->cursor_column = 0;
    format->cursor_row = 0;
    format->magic = INDEXED_FORMAT_MAGIC;
    FORMAT_CACHE[window->slot].field_tag = 0;
    if (!(format->repeat & FORMAT_ROW)) {
        cursor = text + (text[0] == '~');
        while (cursor < end) {
            const u8 *field = indexed_format_field(
                cursor, (size_t)(end - cursor), &ordinal, &kind, &size);
            if (!field)
                break;
            format->values[ordinal - 1].digits =
                kind == 's' ? 0x40 : kind == 'v' ? 0x80 : 0;
            cursor = field + size;
        }
    }
    FormatCache *cache = &FORMAT_CACHE[window->slot];
    cache->hash = 0;
    cache->changed[0] = cache->changed[1] = 0xffffffffu;
    cache->simple = 0;
    if (!retain_bounds)
        for (int row = 0; row < FORMAT_ROWS; ++row) {
            cache->left[row] = 255;
            cache->right[row] = 0;
        }
    return 1;
}

__attribute__((noinline)) const u8 *vwf_menu_render(
        Window *window, const u8 *text) {
    size_t length = bounded_length(text);
    if (length && start_indexed_format(window, text, length))
        return text + length - 1;
    IndexedFormat *indexed = indexed_format(window);
    if (indexed && indexed->magic == INDEXED_FORMAT_MAGIC) {
        // Pulse's Emotion heading follows its numbers before the next refresh.
        vwf_refresh();
        indexed->magic = 0;
    }
    render_window_profile(window, text, 0, 0, TEXT_ALIGN_LEFT, 0);
    return length ? text + length - 1 : text;
}

void vwf_cursor_set(u32 slot, u32 column, u32 row) {
    Window *window = get_window((u8)slot);
    IndexedFormat *format = indexed_format(window);
    if (format && format->magic == INDEXED_FORMAT_MAGIC &&
            (format->repeat & FORMAT_ROW)) {
        format->repeat &= (u8)~FORMAT_ROW_RESTART;
        if (!column) {
            format->repeat |= FORMAT_ROW_RESTART;
            format->cursor_row = (u8)row;
        }
    }
    set_cursor(window, (u16)column, (u16)row);
}

void vwf_reset_window_fields(u32 slot) {
    Window *window = get_window((u8)slot);
    window->flags &= ~CURSOR_MARK;
    IndexedFormat *format = indexed_format(window);
    if (format && format->magic == INDEXED_FORMAT_MAGIC)
        format->magic = 0;
    reset_field_states(window);
    FormatCache *cache = &FORMAT_CACHE[(u8)slot];
    cache->hash = 0;
    cache->changed[0] = cache->changed[1] = 0;
    cache->simple = 0;
    for (int row = 0; row < FORMAT_ROWS; ++row) {
        cache->left[row] = 255;
        cache->right[row] = 0;
    }
}

// Window creation replaces the tile map but leaves our text state behind.
__attribute__((naked)) void vwf_window_created(void) {
    __asm__ volatile(
        "str r5, [r6]\n"
        "push {r0, r1, r2, lr}\n"
        "ldrb r0, [r6, #19]\n"
        "bl vwf_reset_window_fields\n"
        "pop {r0, r1, r2, r3}\n"
        "mov lr, r3\n"
        "mov r2, r6\n"
        "add r2, #30\n"
        "movs r5, #0\n"
        "ldr r3, 1f\n"
        "bx r3\n"
        ".balign 4\n"
        "1: .word 0x0809856d\n");
}

static __attribute__((noinline, used)) int clear_row_format(u32 slot, u32 caller) {
    if (caller == 0x08098C3F)
        return 0;
    Window *window = get_window((u8)slot);
    IndexedFormat *format = indexed_format(window);
    if (!format || format->magic != INDEXED_FORMAT_MAGIC ||
            !(format->repeat & FORMAT_REPEAT))
        return 0;
    format->next = 0;
    FORMAT_CACHE[(u8)slot].changed[0] = 0xffffffffu;
    FORMAT_CACHE[(u8)slot].changed[1] = 0xffffffffu;
    if (!(format->repeat & FORMAT_ROW))
        format->string_bytes = 0;
    format->repeat |= FORMAT_DIRTY | FORMAT_READY;
    window->column = window->row = 0;
    window->flags &= ~CURSOR_MARK;
    return 1;
}

__attribute__((naked)) void vwf_clear_window(u32 slot __attribute__((unused))) {
    __asm__ volatile(
        "push {r0, lr}\n"
        "mov r1, lr\n"
        "bl clear_row_format\n"
        "cmp r0, #0\n"
        "beq 2f\n"
        "pop {r0, pc}\n"
        "2:\n"
        "ldr r0, [sp]\n"
        "bl vwf_reset_window_fields\n"
        "pop {r0, r3}\n"
        "mov lr, r3\n"
        "push {r4, r5, r6, r7, lr}\n"
        "mov r7, r8\n"
        "push {r7}\n"
        "lsl r0, r0, #24\n"
        "ldr r3, 1f\n"
        "bx r3\n"
        ".balign 4\n"
        "1: .word 0x080986bd\n");
}

__attribute__((naked)) void vwf_clear_window_all(u32 slot __attribute__((unused))) {
    __asm__ volatile(
        "push {r0, lr}\n"
        "bl vwf_reset_window_fields\n"
        "pop {r0, r3}\n"
        "mov lr, r3\n"
        "push {r4, r5, r6, r7, lr}\n"
        "sub sp, #4\n"
        "lsl r0, r0, #24\n"
        "lsr r0, r0, #24\n"
        "ldr r3, 1f\n"
        "bx r3\n"
        ".balign 4\n"
        "1: .word 0x0809875d\n");
}

__attribute__((naked)) void vwf_field_at(
        const u8 *text __attribute__((unused)),
        u32 color __attribute__((unused)), u32 slot __attribute__((unused)),
        u32 column __attribute__((unused)), u32 row __attribute__((unused))) {
    __asm__ volatile(
        "push {r0, r1, r2, r3, lr}\n"
        "ldr r0, [sp, #20]\n"
        "push {r0}\n"
        "ldr r0, [sp, #4]\n"
        "bl field_at_blank\n"
        "add sp, #4\n"
        "cmp r0, #0\n"
        "beq 1f\n"
        "pop {r0, r1, r2, r3, pc}\n"
        "1:\n"
        "ldr r0, [sp, #16]\n"
        "mov lr, r0\n"
        "ldr r0, 2f\n"
        "mov ip, r0\n"
        "pop {r0, r1, r2, r3}\n"
        "add sp, #4\n"
        "bx ip\n"
        ".balign 4\n"
        "2: .word vwf_field_at_body + 1\n");
}

RUNTIME_O2 __attribute__((used)) void vwf_field_at_body(
        const u8 *text, u32 color, u32 slot, u32 column, u32 row) {
    Window *window = get_window((u8)slot);
    int captured = capture_row_format(
        window, 's', 0, 0, 0, color, text, column, row);
    if (!captured)
        captured = capture_indexed_format(window, 's', 0, 0, 0, color, text);
    if (captured == 2)
        paint_indexed_format(slot);
    if (captured)
        return;
    set_cursor(window, (u16)column, (u16)row);
    window->color = (u8)color;
    render_window_profile(window, text, 0, 0, TEXT_ALIGN_LEFT,
                          !indexed_format_active(window));
    window->flags |= 2;
    order_window((u8)slot);
}

RUNTIME_O2 void vwf_editor_text(void) {
    const u8 *text = *(const u8 *volatile *)0x0202170c;
    u32 capacity = *(volatile u8 *)0x02021710;
    u32 column = *(volatile u8 *)0x02021711;
    Window *window = get_window(0);
    window->color = 0;
    // Native cursor sprites mark eight-pixel cells, including spaces.
    for (u32 index = 0; index < capacity && text[index * 2]; ++index) {
        u8 glyph[4] = {text[index * 2], text[index * 2 + 1], 0, 0};
        set_cursor(window, (u16)(column + index), 0);
        render_window_profile(window, glyph, 0, 0, TEXT_ALIGN_LEFT, 0);
    }
    window->flags |= 2;
    order_window(0);
}

#define LINE_CACHE_SLOTS 18
#define LINE_CACHE_LINES 16
#define LINE_CACHE_TAG 0xd5c2u
#define LINE_CACHE_HEADER 23

// Description layout state lives in the payload bytes of a window's last
// free field slots, whose keys stay 0xffff so field tracking treats them as
// free. Bytes: 0 tag, 2 text, 6 hash, 10 length, 12 lines, 13 complete,
// 14 resume start, 16 resume color, 17 shown first, 18 shown, 19 tile sum,
// then five bytes per line: start, end, color.
static u8 *line_cache_byte(FieldState *slots, u32 index) {
    u32 slot = (index * 43) >> 8;
    return (u8 *)&slots[slot] + 2 + (index - slot * 6);
}

static u32 line_cache_get(FieldState *slots, u32 index, u32 size) {
    u32 value = 0;
    for (u32 i = 0; i < size; ++i)
        value |= (u32)*line_cache_byte(slots, index + i) << (i * 8);
    return value;
}

static void line_cache_set(FieldState *slots, u32 index, u32 size, u32 value) {
    for (u32 i = 0; i < size; ++i)
        *line_cache_byte(slots, index + i) = (u8)(value >> (i * 8));
}

static FieldState *line_cache_slots(Window *window) {
    int count, used;
    FieldState *states = used_field_states(window, &used, &count);
    if (!states || count < LINE_CACHE_SLOTS + 16 ||
            used > count - LINE_CACHE_SLOTS)
        return 0;
    FieldState *slots = states + count - LINE_CACHE_SLOTS;
    for (int i = 0; i < LINE_CACHE_SLOTS; ++i)
        if (field_state_key(&slots[i]) != 0xffff)
            return 0;
    return slots;
}

static u32 line_cache_hash(const u8 *text, size_t length, Window *window) {
    u32 hash = 2166136261u ^ ((u32)window->width << 8) ^
               (u32)text_inset(window);
    if ((u32)text >> 24 == 8)
        return hash;
    for (size_t i = 0; i < length; ++i)
        hash = (hash ^ text[i]) * 16777619u;
    return hash;
}

static u32 description_tile_sum(Window *window, u32 rows) {
    u32 sum = 2166136261u;
    u32 width = window->width;
    const u16 *cell = &window->tiles[width];
    for (u32 y = 0; y < rows * 2; ++y, cell += width)
        for (u32 x = 1; x + 1 < width; ++x)
            sum = (sum ^ cell[x]) * 16777619u;
    return sum;
}

// Lays out description lines from a line start until have lines exist or the
// text ends; returns the line count, or 0 when the text does not lay out
// cleanly within the cache limits.
static __attribute__((noinline)) u32 measure_description_lines(
        const u8 *text, size_t length, Window *window, u32 have, u32 want,
        u32 *resume_start, u32 *resume_color, u32 *complete,
        u16 *starts, u16 *ends, u8 *colors) {
    WindowWorkspace *work = MENU_WORKSPACE;
    text_profile_init(&work->profile, TEXT_PROFILE_LABEL,
        (int16_t)((window->width - 2) * 8), 32767);
    work->profile.left = (int16_t)text_inset(window);
    work->profile.wrap = TEXT_WRAP_WORD;
    text_decoder_init_raw(&work->decoder, text, length, 0, 0, 0);
    work->decoder.positions[0] = (u16)*resume_start;
    TextLayoutState *state = &work->context.state;
    state->x = work->profile.left;
    state->y = 0;
    state->previous = -1;
    state->color = (u8)*resume_color;
    state->initialized = 1;
    u32 line = have, start = *resume_start, color = *resume_color;
    TextStatus status = text_layout_begin(&work->profile, &work->decoder,
        state, &work->cursor, &work->result);
    while (status == TEXT_OK && line < want) {
        if (text_layout_scanning(&work->cursor)) {
            int peek = text_layout_simple_peek(&runtime_font_data, &work->profile,
                &work->decoder, state, &work->cursor, &work->result, &work->event);
            status = peek < 0 ? text_layout_scan_peek(&runtime_font_data,
                &work->profile, &work->decoder, state, &work->cursor,
                &work->result, &work->event) : (TextStatus)peek;
        } else {
            status = text_layout_emit_peek(&runtime_font_data, &work->profile,
                &work->decoder, state, &work->cursor, &work->result, &work->event);
        }
        if (status != TEXT_OK)
            break;
        if (work->event.kind == TEXT_EVENT_LINE) {
            if (line >= LINE_CACHE_LINES - 1)
                return 0;
            starts[line] = (u16)start;
            ends[line] = work->event.consumed;
            colors[line++] = (u8)color;
            start = work->event.next_consumed;
            color = state->color;
        }
        status = text_layout_commit(&runtime_font_data, &work->profile,
            &work->decoder, state, &work->cursor, &work->result, &work->event);
        if (status == TEXT_OK && work->event.kind == TEXT_EVENT_LINE_BEGIN)
            text_layout_skip_line(&work->decoder, state, &work->cursor);
    }
    *resume_start = start;
    *resume_color = color;
    if (status == TEXT_OK)
        return line;
    if (status != TEXT_END)
        return 0;
    starts[line] = (u16)start;
    ends[line] = (u16)(length - 1);
    colors[line++] = (u8)color;
    *complete = 1;
    return line;
}

// Returns the measured line count, at least want unless the text ends first,
// or 0 when the caller must measure with the early-exit loop.
static u32 description_lines(const u8 *text, size_t length, Window *window,
                             FieldState *slots, u32 want, u32 *complete,
                             u16 *starts, u16 *ends, u8 *colors) {
    u32 hash = line_cache_hash(text, length, window);
    u32 have = 0, resume_start = 0, resume_color = 0;
    *complete = 0;
    if (slots && line_cache_get(slots, 0, 2) == LINE_CACHE_TAG &&
            line_cache_get(slots, 2, 4) == (u32)text &&
            line_cache_get(slots, 6, 4) == hash &&
            line_cache_get(slots, 10, 2) == length) {
        have = line_cache_get(slots, 12, 1);
        *complete = line_cache_get(slots, 13, 1);
        resume_start = line_cache_get(slots, 14, 2);
        resume_color = line_cache_get(slots, 16, 1);
        if (have > LINE_CACHE_LINES)
            have = *complete = 0;
        for (u32 i = 0; i < have; ++i) {
            starts[i] = (u16)line_cache_get(slots, LINE_CACHE_HEADER + i * 5, 2);
            ends[i] = (u16)line_cache_get(slots, LINE_CACHE_HEADER + 2 + i * 5, 2);
            colors[i] = (u8)line_cache_get(slots, LINE_CACHE_HEADER + 4 + i * 5, 1);
        }
    } else if (slots) {
        line_cache_set(slots, 17, 2, 0);
    }
    if (*complete || have >= want)
        return have;
    u32 lines = measure_description_lines(text, length, window, have, want,
        &resume_start, &resume_color, complete, starts, ends, colors);
    if (!lines)
        return 0;
    if (!slots) {
        // The caller redraws the whole window, which resets its fields too.
        reset_field_states(window);
        slots = line_cache_slots(window);
        if (slots)
            line_cache_set(slots, 17, 2, 0);
    }
    if (slots) {
        line_cache_set(slots, 0, 2, LINE_CACHE_TAG);
        line_cache_set(slots, 2, 4, (u32)text);
        line_cache_set(slots, 6, 4, hash);
        line_cache_set(slots, 10, 2, (u32)length);
        line_cache_set(slots, 12, 1, lines);
        line_cache_set(slots, 13, 1, *complete);
        line_cache_set(slots, 14, 2, resume_start);
        line_cache_set(slots, 16, 1, resume_color);
        for (u32 i = have; i < lines; ++i) {
            line_cache_set(slots, LINE_CACHE_HEADER + i * 5, 2, starts[i]);
            line_cache_set(slots, LINE_CACHE_HEADER + 2 + i * 5, 2, ends[i]);
            line_cache_set(slots, LINE_CACHE_HEADER + 4 + i * 5, 1, colors[i]);
        }
    }
    return lines;
}

// Moves the shown description rows one row up or down, releasing the tiles
// that scroll out, as the window clear would for the rows it redraws.
static __attribute__((noinline)) void scroll_description(Window *window,
                                                         u32 rows, int up) {
    u32 width = window->width;
    u16 *top = &window->tiles[width];
    u32 inner = width - 2;
    u16 blank = (u16)((MEM(u32, 0x02021664) + 1) | MEM(u16, 0x02021668));
    u16 *gone = up ? top : top + (rows - 1) * 2 * width;
    for (u32 y = 0; y < 2; ++y)
        for (u32 x = 1; x <= inner; ++x) {
            u32 id = gone[y * width + x] & 0x3ff;
            u32 base = MEM(u32, 0x02021664);
            if (id < base || id >= base + 0x40)
                release((u16)(id - MEM(u32, 0x02021670)));
        }
    if (up) {
        for (u32 y = 0; y + 2 < rows * 2; ++y)
            for (u32 x = 1; x <= inner; ++x)
                top[y * width + x] = top[(y + 2) * width + x];
    } else {
        for (u32 y = rows * 2 - 1; y >= 2; --y)
            for (u32 x = 1; x <= inner; ++x)
                top[y * width + x] = top[(y - 2) * width + x];
    }
    u16 *fresh = up ? top + (rows - 1) * 2 * width : top;
    for (u32 y = 0; y < 2; ++y)
        for (u32 x = 1; x <= inner; ++x)
            fresh[y * width + x] = blank;
    window->column = 0;
    window->row = 0;
    window->flags |= 2;
    reset_field_states(window);
}

typedef struct {
    u16 starts[20];
    u16 ends[20];
    u8 colors[20];
    u8 count;
    u8 line;
    u8 mode;
    u8 cached;
} DescriptionPlan;

#define DESCRIPTION_PLAN ((DescriptionPlan *)FORMAT_WORKSPACE)
typedef char DescriptionPlanFits[(sizeof(DescriptionPlan) <= 0x70) ? 1 : -1];

// Chooses the visible description rows and whether the shown rows can scroll
// by one; returns 0 when the text cannot be laid out.
static __attribute__((noinline)) int plan_description(
        Window *window, const u8 *text, size_t length, u32 first, u32 rows) {
    DescriptionPlan *plan = DESCRIPTION_PLAN;
    u16 *starts = plan->starts;
    u16 *ends = plan->ends;
    u8 *colors = plan->colors;
    u32 line = 0, count = 0, complete = 0;
    FieldState *slots = line_cache_slots(window);
    u32 lines = description_lines(text, length, window, slots,
                                  first + rows + 1, &complete,
                                  starts, ends, colors);
    plan->mode = 0;
    plan->cached = lines != 0;
    if (lines) {
        count = first < lines ? lines - first : 0;
        if (count > rows)
            count = rows;
        for (u32 i = 0; i < count; ++i) {
            starts[i] = starts[first + i];
            ends[i] = ends[first + i];
            colors[i] = colors[first + i];
        }
        line = lines - 1 >= first + rows ? first + rows : lines - 1;
        u32 shown = slots ? line_cache_get(slots, 17, 2) : 0;
        if (rows >= 2 && shown >> 8 &&
                (first == (shown & 0xff) + 1 || first + 1 == (shown & 0xff)) &&
                line_cache_get(slots, 19, 4) == description_tile_sum(window, rows))
            plan->mode = first == (shown & 0xff) + 1 ? 1 : 2;
    } else {
        u32 start = 0, color = 0;
        WindowWorkspace *work = MENU_WORKSPACE;
        text_profile_init(&work->profile, TEXT_PROFILE_LABEL,
            (int16_t)((window->width - 2) * 8), 32767);
        work->profile.left = (int16_t)text_inset(window);
        work->profile.wrap = TEXT_WRAP_WORD;
        text_decoder_init_raw(&work->decoder, text, length, 0, 0, 0);
        work->context.state.initialized = 0;
        TextLayoutState *state = &work->context.state;
        TextStatus status = text_layout_begin(&work->profile, &work->decoder,
            state, &work->cursor, &work->result);
        while (status == TEXT_OK) {
            if (text_layout_scanning(&work->cursor)) {
                int peek = text_layout_simple_peek(&runtime_font_data, &work->profile,
                    &work->decoder, state, &work->cursor, &work->result, &work->event);
                status = peek < 0 ? text_layout_scan_peek(&runtime_font_data,
                    &work->profile, &work->decoder, state, &work->cursor,
                    &work->result, &work->event) : (TextStatus)peek;
            } else {
                status = text_layout_emit_peek(&runtime_font_data, &work->profile,
                    &work->decoder, state, &work->cursor, &work->result, &work->event);
            }
            if (status != TEXT_OK)
                break;
            if (work->event.kind == TEXT_EVENT_LINE) {
                if (line >= first && count < rows) {
                    starts[count] = (u16)start;
                    ends[count] = work->event.consumed;
                    colors[count++] = (u8)color;
                }
                start = work->event.next_consumed;
                color = state->color;
                if (++line == first + rows)
                    break;
            }
            status = text_layout_commit(&runtime_font_data, &work->profile,
                &work->decoder, state, &work->cursor, &work->result, &work->event);
            if (status == TEXT_OK && work->event.kind == TEXT_EVENT_LINE_BEGIN)
                text_layout_skip_line(&work->decoder, state, &work->cursor);
        }
        if (status != TEXT_END && line != first + rows)
            return 0;
        if (status == TEXT_END && line >= first && count < rows) {
            starts[count] = (u16)start;
            ends[count] = (u16)(length - 1);
            colors[count++] = (u8)color;
        }
    }
    plan->count = (u8)count;
    plan->line = (u8)(line > 255 ? 255 : line);
    return 1;
}

static __attribute__((noinline)) void finish_description(Window *window,
                                                         u32 first, u32 rows) {
    FieldState *slots = line_cache_slots(window);
    if (!slots || !DESCRIPTION_PLAN->cached)
        return;
    line_cache_set(slots, 17, 1, first);
    line_cache_set(slots, 18, 1, 1);
    line_cache_set(slots, 19, 4, description_tile_sum(window, rows));
}

RUNTIME_O2 void vwf_description(void) {
    u32 slot = MEM(u8, 0x02032e64);
    u32 first = MEM(u8, 0x02032e65);
    const u8 *text = (const u8 *)MEM(u32, 0x02032e60);
    Window *window = get_window(slot);
    u32 rows = (window->height - 2) / 2;
    if (!rows || rows > 20)
        return;
    size_t length = bounded_length(text);
    if (!length || !plan_description(window, text, length, first, rows))
        return;
    DescriptionPlan *plan = DESCRIPTION_PLAN;
    u32 mode = plan->mode;
    if (mode)
        scroll_description(window, rows, mode == 1);
    else
        vwf_clear_window(slot);
    u32 wrap_flags = window->flags & 0x50;
    window->flags &= ~0x50u;
    for (u32 row = 0; row < plan->count; ++row) {
        if (mode == 1 ? row != rows - 1 : mode == 2 && row)
            continue;
        u32 bytes = plan->ends[row] - plan->starts[row];
        if (bytes >= 1024)
            break;
        for (u32 i = 0; i < bytes; ++i)
            FORMAT_OUTPUT[i] = text[plan->starts[row] + i];
        FORMAT_OUTPUT[bytes] = 0;
        vwf_field_at(FORMAT_OUTPUT, plan->colors[row], slot, 0, row * 2);
    }
    window = get_window(slot);
    window->flags |= wrap_flags;
    finish_description(window, first, rows);
    u32 *up = (u32 *)MEM(u32, 0x02032e68);
    u32 *down = (u32 *)MEM(u32, 0x02032e6c);
    *up = first ? *up & ~0x20000u : *up | 0x20000u;
    *down = plan->line + 1u > first + rows ? *down & ~0x20000u
                                           : *down | 0x20000u;
    refresh();
}

static const TextProfile blank_label_profile = {
    0, 0, 224, 16, 7, 8, 0, TEXT_FACE_AUTO, 8, TEXT_ALIGN_LEFT,
    TEXT_BOUND_INK, TEXT_WRAP_NONE, TEXT_OVERFLOW_CLIP, 0, 0, 0,
};

// Checks, without side effects, that render_window_profile would lay out
// text as one line of spaces in a plain label window; returns the run.
static u32 blank_field_run(Window *window, const u8 *text, u32 color,
                           int column, int row) {
    IndexedFormat *format = indexed_format(window);
    if (format && format->magic == INDEXED_FORMAT_MAGIC)
        return 0;
    int pad = text == (const u8 *)0x081061C4 && text[0] == 0x81 &&
              text[1] == 0x40 && !text[2];
    u32 blank = pad ? 1 | (2u << 16) : blank_units(text, bounded_length(text));
    if (!blank || !colour_fits(color) || column < 0 || row < 0 ||
            window->width < 3 || window->width > 30 || window->height < 3 ||
            window->width * window->height > (0x4d0 - 0x1e) / 2 ||
            (window->flags & 0x50) || !window_workspace(window) ||
            text_blank_glyph(&runtime_font_data, &blank_label_profile,
                             (blank >> 16) == 2 ? 0x8140 : 0x20) < 0)
        return 0;
    return blank;
}

// render_window_profile for a space-only field in a plain label window: the
// same field bookkeeping, clears, and cursor moves without the layout engine.
static void render_blank_field(Window *window, u32 color, u32 blank) {
    WindowWorkspace *workspace = window_workspace(window);
    RenderContext *context = &workspace->context;
    u16 code = (blank >> 16) == 2 ? 0x8140 : 0x20;
    window->color = (u8)color;
    if (!(window->flags & CURSOR_MARK))
        reset_field_states(window);
    u32 saved_flags = window->flags;
    load_state(window, &context->state);
    int field_left = context->state.x;
    int field_top = context->state.y;
    context->window = window;
    int available = 1;
    if (field_left < 0 || field_left > (window->width - 2) * 8 ||
            field_top < -8 || field_top >= (window->height - 2) * 8) {
        window->flags = saved_flags;
        return;
    }
    context->prior = previous_field_bounds(window, field_left, field_top, 1,
                                           &available);
    if (!available) {
        window->flags = saved_flags;
        return;
    }
    context->replace = 1;
    context->cleared = !context->prior || field_is_active(context->prior);
    context->palette = (u8)div3(window->color);
    context->tile_columns = (u8)(window->width - 2);
    context->tile_rows = (u8)(window->height - 2);
    context->direct = 0;
    context->clip_right = 0;
    bind_surface(context, 0);
    int count = (u16)blank;
    TextLayoutState end = context->state;
    int line_height = text_blank_run(&runtime_font_data, &blank_label_profile,
                                     &end, code, count);
    TextEvent *event = &workspace->event;
    event->kind = TEXT_EVENT_LINE_BEGIN;
    event->advance_left = (int16_t)field_left;
    event->advance_right = end.x;
    event->left = event->right = (int16_t)field_left;
    event->top = (int16_t)field_top;
    event->bottom = (int16_t)(field_top + line_height);
    event->value = context->state.color;
    prepare_rect(context, event);
    if (event->advance_right > event->advance_left)
        clear_previous_field(context, event->value);
    replace_line_field(context, event);
    prepare_field_line(context, event);
    context->state.x = end.x;
    context->state.previous = end.previous;
    window->column = (int16_t)(window->column + count);
    window->flags |= 2;
    TextLayoutResult *result = &workspace->result;
    result->ink_left = result->ink_right = context->state.x;
    result->ink_top = result->ink_bottom = context->state.y;
    clear_previous_field(context, context->state.color);
    const FieldState *prior = context->prior;
    // An active field only grows from inkless text, so these would not change it.
    if (!prior || prior->right > prior->left)
        release_empty_field_tiles(context);
    if (!prior || !field_is_active(prior) || (field_state_key(prior) & 0x8000))
        save_field_bounds(window, field_left, field_top, result, 1);
    save_state(window, &context->state);
}

static __attribute__((noinline, used)) int field_current_blank(
        const u8 *text, u32 color, u32 slot) {
    Window *window = get_window((u8)slot);
    u32 blank = blank_field_run(window, text, color, window->column,
                                window->row);
    if (!blank)
        return 0;
    render_blank_field(window, color, blank);
    window->flags |= 2;
    order_window((u8)slot);
    return 1;
}

static __attribute__((noinline, used)) int field_at_blank(
        const u8 *text, u32 color, u32 slot, u32 column, u32 row) {
    Window *window = get_window((u8)slot);
    u32 blank = blank_field_run(window, text, color, (int16_t)(u16)column,
                                (int16_t)(u16)row);
    if (!blank)
        return 0;
    set_cursor(window, (u16)column, (u16)row);
    render_blank_field(window, color, blank);
    window->flags |= 2;
    order_window((u8)slot);
    return 1;
}

__attribute__((naked)) void vwf_field_current(
        const u8 *text __attribute__((unused)),
        u32 color __attribute__((unused)), u32 slot __attribute__((unused))) {
    __asm__ volatile(
        "push {r0, r1, r2, lr}\n"
        "bl field_current_blank\n"
        "cmp r0, #0\n"
        "pop {r0, r1, r2, r3}\n"
        "mov lr, r3\n"
        "bne 1f\n"
        "ldr r3, 2f\n"
        "bx r3\n"
        "1:\n"
        "bx lr\n"
        ".balign 4\n"
        "2: .word vwf_field_current_body + 1\n");
}

RUNTIME_O2 void vwf_field_current_body(const u8 *text, u32 color, u32 slot) {
    Window *window = get_window((u8)slot);
    int captured = capture_row_format(window, 's', 0, 0, 0, color, text,
                                      window->column, window->row);
    if (!captured)
        captured = capture_indexed_format(window, 's', 0, 0, 0, color, text);
    if (captured == 2)
        paint_indexed_format(slot);
    if (captured)
        return;
    size_t length = bounded_length(text);
    if (length && start_indexed_format(window, text, length))
        return;
    window->color = (u8)color;
    render_window_profile(window, text, 0, 0, TEXT_ALIGN_LEFT,
                          !indexed_format_active(window));
    window->flags |= 2;
    order_window((u8)slot);
}

#define ASSET_MESSAGE ((u8 *)0x02031756)
#define ASSET_MESSAGE_CAPACITY 0x80
#define ASSET_MESSAGE_WIDTH 30

static u32 message_unit_size(const u8 *text) {
    u8 value = *text;
    if (!value)
        return 0;
    if (value == 2 || value == 7 || value == 8)
        return 3;
    if (value == 1 || value == 4 || value == 6 || (value >= 0x80 && value <= 0x9f))
        return 2;
    return 1;
}

static int plural_name(const u8 *argument, u32 length) {
    u8 plain[ASSET_MESSAGE_CAPACITY];
    u32 size = 0;
    for (u32 at = 0; at < length;) {
        u32 unit = message_unit_size(argument + at);
        if (!unit) {
            ++at;
            continue;
        }
        if (argument[at] >= 0x20 && size + unit < sizeof(plain))
            for (u32 i = 0; i < unit; ++i)
                plain[size++] = argument[at + i];
        at += unit;
    }
    plain[size] = 0;
    PlainUnits units;
    if (!plain_units(plain, &units))
        return 0;
    u32 start = units.count;
    while (start && units.chars[start - 1] != ' ')
        --start;
    const char *word = units.chars + start;
    u32 count = units.count - start;
    return word_ends_with(word, count, "data") || word_ends_with(word, count, "parts") ||
           word_ends_with(word, count, "scissors") || word_ends_with(word, count, "guns") ||
           word_ends_with(word, count, "series");
}

// %1$s is what the game wrote between argument_start and end, minus zero padding;
// a template "singular|plural" picks its form by the argument's last word.
void vwf_compose_message(const u8 *end, const u8 *template_text, u32 argument_start) {
    u8 argument[ASSET_MESSAGE_CAPACITY];
    u32 argument_length = 0;
    for (const u8 *at = ASSET_MESSAGE + argument_start; at < end;) {
        u32 size = message_unit_size(at);
        if (!size) {
            ++at;
            continue;
        }
        if (at + size > end || argument_length + size > sizeof(argument))
            break;
        for (u32 i = 0; i < size; ++i)
            argument[argument_length++] = at[i];
        at += size;
    }
    const u8 *template_end = 0;
    for (const u8 *at = template_text; *at; at += message_unit_size(at)) {
        if (*at == '|') {
            if (plural_name(argument, argument_length))
                template_text = at + 1;
            else
                template_end = at;
            break;
        }
    }
    u32 length = 0;
    for (const u8 *cursor = template_text; *cursor && cursor != template_end;) {
        const u8 *source = cursor;
        u32 size;
        if (cursor[0] == '%' && cursor[1] == '1' && cursor[2] == '$' && cursor[3] == 's') {
            source = argument;
            size = argument_length;
            cursor += 4;
        } else {
            size = message_unit_size(cursor);
            cursor += size;
        }
        if (length + size >= ASSET_MESSAGE_CAPACITY)
            break;
        for (u32 i = 0; i < size; ++i)
            ASSET_MESSAGE[length++] = source[i];
    }
    ASSET_MESSAGE[length] = 0;

    u16 starts[LINE_CACHE_LINES], ends[LINE_CACHE_LINES];
    u8 colors[LINE_CACHE_LINES];
    u32 resume_start = 0, resume_color = 0, complete = 0;
    Window window;
    window.flags = 0;
    window.width = ASSET_MESSAGE_WIDTH;
    u32 lines = measure_description_lines(ASSET_MESSAGE, bounded_length(ASSET_MESSAGE),
        &window, 0, LINE_CACHE_LINES - 1,
        &resume_start, &resume_color, &complete, starts, ends, colors);
    if (!complete || lines < 2)
        return;
    length = 0;
    for (u32 line = 0; line < lines; ++line) {
        for (u32 at = starts[line]; at < ends[line] && length + 2 < sizeof(argument); ++at)
            argument[length++] = ASSET_MESSAGE[at];
        if (line + 1 < lines)
            argument[length++] = '\n';
    }
    for (u32 i = 0; i < length; ++i)
        ASSET_MESSAGE[i] = argument[i];
    ASSET_MESSAGE[length] = 0;
}

RUNTIME_O2 void vwf_field_counted(const u8 *text, u32 color, u32 slot,
                                  u32 count) {
    u8 plural[80];
    if (count > 1 && plural_text(text, plural, sizeof(plural)))
        text = plural;
    vwf_field_current(text, color, slot);
}

static TextStatus measure_text(const u8 *text, TextLayoutState *state,
                               TextLayoutResult *result) {
    size_t input_length = bounded_length(text);
    if (!input_length)
        return TEXT_MALFORMED_INPUT;
    const u8 *field = (const u8 *)0x02021774;
    TextDecoder decoder;
    text_decoder_init_raw(&decoder, text, input_length, field,
                          bounded_length(field), 0);
    TextProfile profile;
    text_profile_init(&profile, TEXT_PROFILE_LABEL, 0x7fff, 0x7fff);
    profile.alignment_bound = TEXT_BOUND_ADVANCE;
    state->initialized = 0;
    return measure_layout(&profile, &decoder, state, result);
}

u8 vwf_measure_cells(const u8 *text) {
    TextLayoutState state;
    TextLayoutResult result;
    TextStatus status = measure_text(text, &state, &result);
    if (status != TEXT_END)
        return 0;
    int width = state.x;
    if (result.ink_right > width)
        width = result.ink_right;
    width = (width + 7) >> 3;
    return (u8)(width > 255 ? 255 : width);
}

void vwf_format_number(int32_t value, u32 digits, u32 mode, u8 *destination) {
    size_t capacity = input_capacity(destination);
    if (!capacity)
        return;
    TextWriter writer;
    text_writer_init(&writer, destination, capacity);
    if (!digits || digits > 10)
        return;
    text_writer_number(&writer, value, (u8)digits, (u8)mode,
                       mode & 8 ? TEXT_FACE_COMPACT : TEXT_FACE_TALL);
}

static __attribute__((noinline, used)) RUNTIME_O2 int vwf_number_at_try(
        int32_t value, u32 digits, u32 color, u32 mode, u32 slot) {
    Window *window = get_window((u8)slot);
    IndexedFormat *format = indexed_format(window);
    if (format && format->magic == INDEXED_FORMAT_MAGIC &&
            (format->repeat & FORMAT_ROW))
        return 3;
    int captured = capture_indexed_format(
        window, 'd', value, digits, mode, color, 0);
    if (captured)
        return captured;
    return 0;
}

static __attribute__((noinline, used)) int vwf_row_number_at_try(
        int32_t value, u32 digits, u32 color, u32 mode,
        const u32 *position) {
    Window *window = get_window((u8)position[0]);
    return capture_row_format(window, 'd', value, digits,
                              mode, color, 0, position[1], position[2]);
}

static __attribute__((noinline, used)) RUNTIME_O2 void vwf_number_at_plain(
        int32_t value, u32 digits, u32 color, u32 mode,
        u32 slot, u32 column, u32 row) {
    Window *window = get_window((u8)slot);
    u8 *scratch = (u8 *)0x02021676;
    vwf_format_number(value, digits, mode, scratch);
    set_cursor(window, (u16)column, (u16)row);
    window->color = (u8)color;
    int tabular_advance = text_font_digit_advance(
        &runtime_font_data, mode & 8 ? TEXT_FACE_COMPACT : TEXT_FACE_TALL);
    render_window_profile(window, scratch,
                          (int)((column + digits + ((mode & 4) != 0)) * 8),
                          tabular_advance,
                          (mode & 3) == 2 ? TEXT_ALIGN_RIGHT : TEXT_ALIGN_LEFT,
                          !indexed_format_active(window));
    window->flags |= 2;
    order_window((u8)slot);
}

__attribute__((naked)) void vwf_number_at(
        int32_t value __attribute__((unused)),
        u32 digits __attribute__((unused)),
        u32 color __attribute__((unused)),
        u32 mode __attribute__((unused)),
        u32 slot __attribute__((unused)),
        u32 column __attribute__((unused)),
        u32 row __attribute__((unused))) {
    __asm__ volatile(
        "push {r0, r1, r2, r3, r4, r5, lr}\n"
        "ldr r4, [sp, #28]\n"
        "push {r4}\n"
        "bl vwf_number_at_try\n"
        "add sp, #4\n"
        "cmp r0, #3\n"
        "bne 6f\n"
        "ldr r0, [sp, #0]\n"
        "ldr r1, [sp, #4]\n"
        "ldr r2, [sp, #8]\n"
        "ldr r3, [sp, #12]\n"
        "add r4, sp, #28\n"
        "push {r4}\n"
        "bl vwf_row_number_at_try\n"
        "add sp, #4\n"
        "6:\n"
        "cmp r0, #2\n"
        "beq 3f\n"
        "cmp r0, #0\n"
        "beq 1f\n"
        "pop {r0, r1, r2, r3, r4, r5, pc}\n"
        "3:\n"
        "ldr r0, [sp, #28]\n"
        "ldr r4, [sp, #24]\n"
        "mov lr, r4\n"
        "ldr r4, 4f\n"
        "mov ip, r4\n"
        "ldr r4, [sp, #16]\n"
        "ldr r5, [sp, #20]\n"
        "add sp, #28\n"
        "bx ip\n"
        "1:\n"
        "ldr r4, [sp, #24]\n"
        "mov lr, r4\n"
        "ldr r4, 2f\n"
        "mov ip, r4\n"
        "pop {r0, r1, r2, r3, r4, r5}\n"
        "add sp, #4\n"
        "bx ip\n"
        ".balign 4\n"
        "2: .word vwf_number_at_plain + 1\n"
        "4: .word paint_indexed_format + 1\n");
}

RUNTIME_O2 void vwf_number_current(int32_t value, u32 digits, u32 color,
                        u32 mode, u32 slot) {
    Window *window = get_window((u8)slot);
    int captured = capture_row_format(window, 'd', value, digits,
                                      mode, color, 0,
                                      window->column, window->row);
    if (!captured)
        captured = capture_indexed_format(
            window, 'd', value, digits, mode, color, 0);
    if (captured == 2)
        paint_indexed_format(slot);
    if (captured)
        return;
    u8 *scratch = (u8 *)0x02021676;
    vwf_format_number(value, digits, mode, scratch);
    window->color = (u8)color;
    int right = (window->column + digits + ((mode & 4) != 0)) * 8;
    int tabular_advance = text_font_digit_advance(
        &runtime_font_data, mode & 8 ? TEXT_FACE_COMPACT : TEXT_FACE_TALL);
    render_window_profile(window, scratch, right, tabular_advance,
                          (mode & 3) == 2 ? TEXT_ALIGN_RIGHT : TEXT_ALIGN_LEFT,
                          !indexed_format_active(window));
    window->flags |= 2;
    order_window((u8)slot);
}

static u8 *menu_record(u32 slot, u32 physical) {
    return MENU_RECORDS + slot * MENU_BANK_SIZE +
           physical * MENU_RECORD_SIZE;
}

// Native scrolling still addresses 37-byte records. Pack tall Latin glyphs
// inside those records, then restore their original codes before rendering.
static u8 pack_menu_code(u16 code) {
    if (code >= 0x8260 && code <= 0x8279)
        return (u8)(code - 0x8260 + 0xc1);
    if (code >= 0x8281 && code <= 0x829a)
        return (u8)(code - 0x8281 + 0xe1);
    if (code >= 0x824f && code <= 0x8258)
        return (u8)(code - 0x824f + 0xb0);
    if (code == 0x8140) return 0xa0;
    if (code == 0x8144) return 0xae;
    if (code == 0x817c) return 0xad;
    if (code == 0x815e) return 0xaf;
    return 0;
}

static u16 unpack_menu_code(u8 code) {
    if (code >= 0xc1 && code <= 0xda)
        return (u16)(code - 0xc1 + 0x8260);
    if (code >= 0xe1 && code <= 0xfa)
        return (u16)(code - 0xe1 + 0x8281);
    if (code >= 0xb0 && code <= 0xb9)
        return (u16)(code - 0xb0 + 0x824f);
    if (code == 0xa0) return 0x8140;
    if (code == 0xae) return 0x8144;
    if (code == 0xad) return 0x817c;
    if (code == 0xaf) return 0x815e;
    return 0;
}

// Returns the packed size, or limit once packing cannot save space.
static RUNTIME_O2 size_t pack_menu_row(u8 *output, const u8 *text, size_t length,
                            size_t limit) {
    size_t used = 1;
    if (output)
        output[0] = MENU_PACKED;
    for (size_t at = 0; at < length;) {
        u8 value = text[at];
        size_t size = value == 1 || value == 4 || value == 6 ? 2 :
            value == 2 || value == 7 || value == 8 ? 3 :
            value >= 0x80 && value <= 0x9f ? 2 : 1;
        u8 packed = value >= 0x80 && value <= 0x9f
            ? pack_menu_code((u16)((value << 8) | text[at + 1])) : 0;
        size_t needed = packed ? 1 : size + (value >= 0xa0);
        if (used + needed > limit)
            return limit;
        if (packed) {
            if (output)
                output[used] = packed;
            ++used;
        } else {
            if (value >= 0xa0) {
                if (output)
                    output[used] = MENU_PACKED;
                ++used;
            }
            for (size_t i = 0; i < size; ++i) {
                if (output)
                    output[used] = text[at + i];
                ++used;
            }
        }
        at += size;
    }
    return used < limit ? used : limit;
}

static size_t menu_stored_length(const u8 *text, size_t length) {
    return pack_menu_row(0, text, length, length) + 1;
}

static size_t store_menu_row(u8 *output, const u8 *text, size_t length) {
    size_t stored = pack_menu_row(output, text, length, length) + 1;
    if (stored > length)
        for (size_t i = 0; i < length; ++i)
            output[i] = text[i];
    output[stored - 1] = 0;
    return stored;
}

static const u8 *unpack_menu_row(const u8 *text, const u8 **stored_end) {
    if ((u32)text < (u32)MENU_RECORDS ||
            (u32)text >= (u32)MENU_RECORDS + MENU_SLOTS * MENU_BANK_SIZE ||
            text[0] != MENU_PACKED)
        return text;
    size_t capacity = input_capacity(text);
    size_t used = 0;
    for (size_t at = 1; at < capacity;) {
        u8 value = text[at++];
        if (!value) {
            FORMAT_OUTPUT[used] = 0;
            *stored_end = text + at - 1;
            return FORMAT_OUTPUT;
        }
        if (value == MENU_PACKED) {
            if (at >= capacity || text[at] < 0xa0 || used >= MENU_TEXT_LIMIT)
                return 0;
            FORMAT_OUTPUT[used++] = text[at++];
            continue;
        }
        u16 code = unpack_menu_code(value);
        if (code) {
            if (used + 2 > MENU_TEXT_LIMIT)
                return 0;
            FORMAT_OUTPUT[used++] = (u8)(code >> 8);
            FORMAT_OUTPUT[used++] = (u8)code;
            continue;
        }
        size_t size = value == 1 || value == 4 || value == 6 ? 2 :
            value == 2 || value == 7 || value == 8 ? 3 :
            value >= 0x80 && value <= 0x9f ? 2 : 1;
        if (at + size - 1 > capacity || used + size > MENU_TEXT_LIMIT ||
                (value < 0x20 && value != 3 && value != 10 && size == 1) ||
                value >= 0xa0)
            return 0;
        FORMAT_OUTPUT[used++] = value;
        for (size_t i = 1; i < size; ++i)
            FORMAT_OUTPUT[used++] = text[at++];
    }
    return 0;
}

static RUNTIME_O2 int menu_bytes_valid(const u8 *text, size_t length) {
    size_t position = 0;
    while (position < length) {
        u8 value = text[position];
        size_t unit;
        if (value == 1 || value == 4 || value == 6)
            unit = 2;
        else if (value == 2 || value == 7 || value == 8)
            unit = 3;
        else if (value == 3 || value == 10 || value >= 0x20)
            unit = value >= 0x80 && value <= 0x9f ? 2 : 1;
        else
            return 0;
        if (position + unit > length ||
                (value == 4 && text[position + 1] > TEXT_ALIGN_RIGHT) ||
                (unit == 2 && value >= 0x80 && value <= 0x9f &&
                 !text[position + 1]))
            return 0;
        position += unit;
    }
    return 1;
}

static TextStatus write_menu_units(TextWriter *writer, const u8 *text,
                                   size_t length) {
    size_t position = 0;
    while (position < length) {
        u8 value = text[position];
        size_t size = value == 1 || value == 4 || value == 6 ? 2 :
                      value == 2 || value == 7 || value == 8 ? 3 :
                      value >= 0x80 && value <= 0x9f ? 2 : 1;
        if (position + size > length)
            return writer->status = TEXT_MALFORMED_INPUT;
        TextStatus status;
        if (value == 1 || value == 2 || value == 4 || value == 6 ||
                value == 7 || value == 8 || value == 3 || value == 10)
            status = text_writer_control(writer, value,
                size > 1 ? text[position + 1] : 0,
                size > 2 ? text[position + 2] : 0);
        else if (value >= 0x80 && value <= 0x9f)
            status = text_writer_code(writer,
                (u16)((value << 8) | text[position + 1]));
        else if (value >= 0x20)
            status = text_writer_byte(writer, value);
        else
            return writer->status = TEXT_MALFORMED_INPUT;
        if (status != TEXT_OK)
            return status;
        position += size;
    }
    return TEXT_OK;
}

static int menu_can_append(u32 slot, u32 count, u32 physical,
                           const u8 *text, size_t length) {
    if (length > MENU_TEXT_LIMIT || !menu_bytes_valid(text, length))
        return 0;
    u32 records = menu_stored_length(text, length) <= MENU_RECORD_SIZE ? 1 : 2;
    return slot < MENU_SLOTS && count + 1 < MENU_ROWS &&
           physical < MENU_ROWS && physical + records <= MENU_ROWS;
}

static __attribute__((noinline)) int menu_commit(u32 slot,
                       const u8 *text, size_t length) {
    u32 count = MENU_COUNTS[slot];
    u32 physical = MENU_LOOKUP[slot * MENU_ROWS + count];
    u8 *destination = menu_record(slot, physical);
    u8 encoded[MENU_TEXT_LIMIT + 1];
    size_t stored = store_menu_row(encoded, text, length);
    for (size_t i = 0; i < stored; ++i)
        destination[i] = encoded[i];
    MENU_LOOKUP[slot * MENU_ROWS + count + 1] =
        (u8)(physical + (stored <= MENU_RECORD_SIZE ? 1 : 2));
    return 1;
}

void vwf_list_render_next(Window *window) {
    u32 slot = window->slot;
    if (slot >= MENU_SLOTS)
        return;
    u32 current = MENU_COUNTS[slot];
    u32 top = window->top;
    u32 visible = window->height >= 2 ? (window->height - 2) / 2 : 0;
    if (current < top || current - top >= visible || current >= MENU_ROWS)
        return;
    u32 physical = MENU_LOOKUP[slot * MENU_ROWS + current];
    if (physical >= MENU_ROWS)
        return;
    const u8 *stored_end = 0;
    const u8 *text = unpack_menu_row(menu_record(slot, physical), &stored_end);
    if (!text)
        return;
    set_cursor(window, 0, window->row);
    text = reserve_icon_column(window, text);
    render_window_profile(window, text,
                          (window->width - 2) * 8, 0, TEXT_ALIGN_LEFT, 1);
    set_cursor(window, 0, window->row + 2);
}

static void menu_append_segment(u32 slot, const u8 *text, size_t length) {
    if (!menu_commit(slot, text, length))
        return;
    Window *window = get_window(slot);
    window->flags |= 2;
    vwf_list_render_next(window);
    ++MENU_COUNTS[slot];
}

static __attribute__((always_inline)) inline u8 pack_menu_pair(u8 lead, u8 trail) {
    if (lead == 0x82) {
        if ((u32)(trail - 0x60) <= 0x19)
            return (u8)(trail - 0x60 + 0xc1);
        if ((u32)(trail - 0x81) <= 0x19)
            return (u8)(trail - 0x81 + 0xe1);
        if ((u32)(trail - 0x4f) <= 9)
            return (u8)(trail - 0x4f + 0xb0);
        return 0;
    }
    if (lead != 0x81)
        return 0;
    return trail == 0x40 ? 0xa0 : trail == 0x44 ? 0xae :
           trail == 0x7c ? 0xad : trail == 0x5e ? 0xaf : 0;
}

// Validates like bounded_length plus menu_bytes_valid and stores like store_menu_row.
static RUNTIME_O2 __attribute__((noinline)) size_t encode_menu_text(
        const u8 *text, size_t capacity, u8 *encoded) {
    size_t position = 0;
    size_t used = 1;
    encoded[0] = MENU_PACKED;
    if (!capacity)
        return 0;
    for (;;) {
        u8 value = text[position];
        if (LIKELY((u32)(value - 0x80) < 0x20)) {
            u8 trail = text[position + 1];
            if (position + 2 >= capacity || !trail)
                return 0;
            u8 packed = pack_menu_pair(value, trail);
            if (packed) {
                if (used < MENU_TEXT_LIMIT)
                    encoded[used] = packed;
                ++used;
            } else {
                if (used + 2 <= MENU_TEXT_LIMIT) {
                    encoded[used] = value;
                    encoded[used + 1] = trail;
                }
                used += 2;
            }
            position += 2;
            continue;
        }
        if (!value)
            break;
        size_t unit;
        if (value >= 0x20 || value == 3 || value == 10)
            unit = 1;
        else if (value == 1 || value == 4 || value == 6)
            unit = 2;
        else if (value == 2 || value == 7 || value == 8)
            unit = 3;
        else
            return 0;
        if (position + unit >= capacity ||
                (value == 4 && text[position + 1] > TEXT_ALIGN_RIGHT))
            return 0;
        if (value >= 0xa0) {
            if (used + 2 <= MENU_TEXT_LIMIT) {
                encoded[used] = MENU_PACKED;
                encoded[used + 1] = value;
            }
            used += 2;
        } else {
            for (size_t i = 0; i < unit; ++i, ++used)
                if (used < MENU_TEXT_LIMIT)
                    encoded[used] = text[position + i];
        }
        position += unit;
    }
    if (position > MENU_TEXT_LIMIT)
        return 0;
    if (used < position) {
        encoded[used] = 0;
        return used + 1;
    }
    for (size_t i = 0; i < position; ++i)
        encoded[i] = text[i];
    encoded[position] = 0;
    return position + 1;
}

static __attribute__((noinline)) int menu_add_row(u32 slot, const u8 *text) {
    u32 count = MENU_COUNTS[slot];
    if (count + 1 >= MENU_ROWS)
        return 0;
    u32 physical = MENU_LOOKUP[slot * MENU_ROWS + count];
    u8 encoded[MENU_TEXT_LIMIT + 1];
    size_t stored = encode_menu_text(text, read_capacity(text), encoded);
    if (!stored)
        return 0;
    u32 records = stored <= MENU_RECORD_SIZE ? 1 : 2;
    if (physical >= MENU_ROWS || physical + records > MENU_ROWS)
        return 0;
    copy_text(menu_record(slot, physical), encoded, stored);
    MENU_LOOKUP[slot * MENU_ROWS + count + 1] = (u8)(physical + records);
    return 1;
}

void vwf_list_add(u32 slot, const u8 *text) {
    if (slot >= MENU_SLOTS || !menu_add_row(slot, text))
        return;
    Window *window = get_window(slot);
    window->flags |= 2;
    vwf_list_render_next(window);
    ++MENU_COUNTS[slot];
}

static size_t menu_unit_size(const u8 *text, size_t remaining) {
    u8 value = *text;
    if (value == 1 || value == 4 || value == 6)
        return remaining >= 2 && (value != 4 || text[1] <= TEXT_ALIGN_RIGHT) ? 2 : 0;
    if (value == 2 || value == 7 || value == 8)
        return remaining >= 3 ? 3 : 0;
    if (value == 3 || value >= 0x20) {
        if (value >= 0x80 && value <= 0x9f)
            return remaining >= 2 && text[1] ? 2 : 0;
        return 1;
    }
    return 0;
}

static __attribute__((noinline)) int menu_script_plan(u32 slot, const u8 *text,
                            const u8 **end_result) {
    size_t capacity = input_capacity(text);
    if (slot >= MENU_SLOTS || !capacity)
        return 0;
    u32 count = MENU_COUNTS[slot];
    if (count >= MENU_ROWS)
        return 0;
    u32 physical = MENU_LOOKUP[slot * MENU_ROWS + count];
    const u8 *row = text;
    size_t row_length = 0;
    for (size_t position = 0; position < capacity;) {
        u8 value = text[position];
        if (!value || value == 10) {
            if ((row_length || value == 10) &&
                    !menu_can_append(slot, count, physical,
                                     row, row_length))
                return 0;
            if (row_length || value == 10) {
                physical += menu_stored_length(row, row_length) <= MENU_RECORD_SIZE ? 1 : 2;
                ++count;
            }
            if (!value) {
                *end_result = text + position;
                return 1;
            }
            ++position;
            row = text + position;
            row_length = 0;
            continue;
        }
        size_t unit = menu_unit_size(text + position, capacity - position);
        if (!unit || position + unit >= capacity)
            return 0;
        position += unit;
        row_length += unit;
        if (row_length > MENU_TEXT_LIMIT)
            return 0;
    }
    return 0;
}

const u8 *vwf_menu_list_command(Window *window, const u8 *text) {
    const u8 *end;
    if (!menu_script_plan(window->slot, text, &end)) {
        size_t length = bounded_length(text);
        return length ? text + length - 1 : text;
    }
    const u8 *row = text;
    const u8 *cursor = text;
    while (cursor < end) {
        size_t unit = menu_unit_size(cursor, (size_t)(end - cursor));
        if (!unit) {
            menu_append_segment(window->slot, row,
                                (size_t)(cursor - row));
            row = cursor + 1;
            unit = 1;
        }
        cursor += unit;
    }
    if (row < end)
        menu_append_segment(window->slot, row, (size_t)(end - row));
    return end;
}

// Keep normal rendering on the menu interpreter's original call frame.
__attribute__((naked)) const u8 *vwf_menu_command(
        Window *window __attribute__((unused)),
        const u8 *text __attribute__((unused))) {
    __asm__ volatile(
        "ldr r2, [r0]\n"
        "movs r3, #128\n"
        "tst r2, r3\n"
        "bne 1f\n"
        "ldr r3, 2f\n"
        "bx r3\n"
        "1:\n"
        "ldr r3, 3f\n"
        "bx r3\n"
        ".balign 4\n"
        "2: .word vwf_menu_render + 1\n"
        "3: .word vwf_menu_list_command + 1\n");
}

static __attribute__((noinline)) u8 *replace_menu_row(
        u32 slot, u32 row, const u8 *text) {
    if (slot >= MENU_SLOTS)
        return 0;
    u32 count = MENU_COUNTS[slot];
    if (row >= count || count >= MENU_ROWS)
        return 0;
    const u8 *stored_end = 0;
    text = unpack_menu_row(text, &stored_end);
    if (!text)
        return 0;
    size_t source_length = bounded_length(text);
    if (!source_length)
        return 0;
    size_t length = source_length - 1;
    u32 lookup = slot * MENU_ROWS;
    u32 physical = MENU_LOOKUP[lookup + row];
    u32 next = MENU_LOOKUP[lookup + row + 1];
    u32 used = MENU_LOOKUP[lookup + count];
    if (physical >= MENU_ROWS || next <= physical || next > MENU_ROWS ||
            next - physical > 2 || used < next || used > MENU_ROWS ||
            length > MENU_TEXT_LIMIT ||
            !menu_bytes_valid(text, length))
        return 0;
    u8 encoded[MENU_TEXT_LIMIT + 1];
    size_t stored = store_menu_row(encoded, text, length);
    int records = stored <= MENU_RECORD_SIZE ? 1 : 2;
    int change = records - (int)(next - physical);
    if ((int)used + change > MENU_ROWS)
        return 0;
    for (u32 i = row + 1; i < count; ++i)
        if (MENU_LOOKUP[lookup + i + 1] <= MENU_LOOKUP[lookup + i] ||
                MENU_LOOKUP[lookup + i + 1] > used)
            return 0;
    u8 *tail = menu_record(slot, next);
    size_t tail_length = (used - next) * MENU_RECORD_SIZE;
    if (change > 0)
        for (size_t i = tail_length; i; --i)
            tail[i - 1 + MENU_RECORD_SIZE] = tail[i - 1];
    else if (change < 0)
        for (size_t i = 0; i < tail_length; ++i)
            (tail - MENU_RECORD_SIZE)[i] = tail[i];
    if (change)
        for (u32 i = row + 1; i <= count; ++i)
            MENU_LOOKUP[lookup + i] = (u8)(MENU_LOOKUP[lookup + i] + change);
    u8 *destination = menu_record(slot, physical);
    for (size_t i = 0; i < stored; ++i)
        destination[i] = encoded[i];
    return destination;
}

void vwf_list_replace(u32 slot, u32 row, const u8 *text) {
    u8 *destination = replace_menu_row(slot, row, text);
    if (!destination)
        return;
    Window *window = get_window(slot);
    u32 top = window->top;
    u32 visible = window->height >= 2 ? (window->height - 2) / 2 : 0;
    if (row >= top && row - top < visible) {
        const u8 *stored_end = 0;
        text = unpack_menu_row(destination, &stored_end);
        if (!text)
            return;
        int saved_column = window->column;
        int saved_row = window->row;
        set_cursor(window, 0, (int)(row - top) * 2);
        text = reserve_icon_column(window, text);
        render_window_profile(window, text,
                              (window->width - 2) * 8, 0, TEXT_ALIGN_LEFT, 1);
        set_cursor(window, saved_column, saved_row);
        window->flags |= 2;
    }
}

static int raw_unit_size(const u8 *text, int remaining) {
    if (!remaining)
        return 0;
    if (*text == 1 || *text == 4 || *text == 6)
        return remaining >= 2 ? 2 : 0;
    if (*text == 2 || *text == 7)
        return remaining >= 3 ? 3 : 0;
    if (*text >= 0x80 && *text <= 0x9f)
        return remaining >= 2 && text[1] ? 2 : 0;
    return 1;
}

__attribute__((optimize("O2"))) const u8 *credits_line(
        const u8 *text, u16 *tiles, u32 *colour) {
    int length = 0;
    const u8 *end = text;
    while (length < 159 && *end && *end != 10) {
        int size = raw_unit_size(end, 159 - length);
        if (!size)
            break;
        length += size;
        end += size;
    }
    u8 line_colour = (u8)*colour;
    int prefix = 0;
    while (prefix + 1 < length && text[prefix] == 1) {
        line_colour = text[prefix + 1];
        prefix += 2;
    }
    int content = prefix;
    int leading = 0;
    while (content + 1 < length && text[content] == 0x81 &&
            text[content + 1] == 0x40) {
        ++leading;
        content += 2;
    }
    int content_end = length;
    int trailing = 0;
    while (content_end - 2 >= content && text[content_end - 2] == 0x81 &&
            text[content_end - 1] == 0x40) {
        ++trailing;
        content_end -= 2;
    }
    CreditsWorkspace *workspace = CREDITS_WORKSPACE;
    TextDecoder *decoder = &workspace->decoder;
    TextProfile *profile = &workspace->profile;
    TextLayoutResult *result = &workspace->result;
    TextEvent *event = &workspace->event;
    TextLayoutCursor *cursor = &workspace->cursor;
    RenderContext *context = &workspace->context;
    text_decoder_init_raw(decoder, text + content,
                          (size_t)(content_end - content), 0, 0, 1);
    text_profile_init(profile, TEXT_PROFILE_CREDITS, 240, 16);
    int difference = leading - trailing;
    if (difference < 0)
        difference = -difference;
    if (difference <= 1)
        profile->alignment = TEXT_ALIGN_CENTER;
    else
        profile->left = (int16_t)(leading * 8);
    context->window = 0;
    context->credit_tiles = tiles;
    context->state.x = profile->left;
    context->state.y = 0;
    context->state.previous = -1;
    context->state.color = line_colour;
    context->state.initialized = 1;
    context->prior = 0;
    context->replace = 0;
    context->cleared = 0;
    context->palette = (u8)div3(*colour);
    context->tile_columns = 30;
    context->tile_rows = 2;
    context->direct = 1;
    context->clip_right = 0;
    bind_surface(context, 0);
    render_layout_work(profile, decoder, context, result, cursor, event, 0);
    *colour = context->state.color;
    return end;
}

void compact_glyph_tile(u32 code, u32 colour, u16 *output) {
    u8 compact_code = (u8)code;
    if (compact_code == 0x20) {
        *output = (u16)((MEM(u32, 0x02021664) + 1) | MEM(u16, 0x02021668));
        return;
    }
    u16 index = compact_indices[compact_code];
    if (index == 0xffff)
        index = runtime_font_data.compact_fallback;
    u32 palette = colour < 3 ? 0 : div3(colour);
    u16 fresh;
    if (MEM(u16, 0x02021668) + (palette << 12) > 0xffff ||
            !allocate(1, &fresh)) {
        *output = (u16)((MEM(u32, 0x02021664) + 1) | MEM(u16, 0x02021668));
        return;
    }
    reserve(fresh);
    u32 variant = colour - palette * 3 + 1;
    u32 *buffer = (u32 *)MEM(u32, 0x02021654);
    u32 *tile = &buffer[fresh * 8];
    for (int row = 0; row < 8; ++row)
        tile[row] = variant * 0x44444444u;
    *output = (u16)((MEM(u32, 0x02021670) + fresh) |
                    (MEM(u16, 0x02021668) + (palette << 12)));
    TextTileSurface surface;
    surface.context = tile;
    surface.get = 0;
    const TextMetric *metric = &runtime_font_data.metrics[index];
    TextPlacement placement;
    placement.clip_left = placement.clip_right = 0;
    placement.metric = index;
    placement.ink_x = metric->bearing_x;
    placement.ink_y = (int16_t)(7 + metric->bearing_y);
    text_compose_glyph_tiles(&runtime_font_data, &placement,
                             &surface, (u8)variant);
}

static u32 *direct_tall_tile(void *context, int x, int y) {
    if (x < 0 || x >= 8 || y < 0 || y >= 16)
        return 0;
    return (u32 *)context + (y >> 3) * 8;
}

static void direct_glyph_tile(u16 index, u8 variant, u32 *output,
                              TextGetTileWords get) {
    const TextMetric *metric = &runtime_font_data.metrics[index];
    u32 background = variant * 0x44444444u;
    for (int row = 0; row < metric->line_height; ++row)
        output[row] = background;
    TextTileSurface surface;
    surface.context = output;
    surface.get = get;
    TextPlacement placement;
    placement.clip_left = placement.clip_right = 0;
    placement.metric = index;
    placement.ink_x = metric->bearing_x;
    placement.ink_y = (int16_t)(metric->baseline + metric->bearing_y);
    text_compose_glyph_tiles(&runtime_font_data, &placement,
                             &surface, variant);
}

static size_t compact_direct_length(const u8 *text) {
    size_t capacity = input_capacity(text);
    for (size_t position = 0; position < capacity; ++position)
        if (!text[position])
            return position + 1;
    return 0;
}

static size_t tall_direct_length(const u8 *text) {
    size_t capacity = input_capacity(text);
    for (size_t position = 0; position < capacity; position += 2) {
        if (!text[position])
            return position + 1;
        if (position + 1 >= capacity)
            return 0;
    }
    return 0;
}

void direct_compact_tiles(const u8 *text, u32 colour, u32 *output) {
    size_t length = compact_direct_length(text);
    if (!length)
        return;
    u8 variant = (u8)(umod((u8)colour, 3) + 1);
    for (size_t position = 0; position + 1 < length; ++position) {
        u16 index = compact_indices[text[position]];
        if (index == 0xffff)
            index = runtime_font_data.compact_fallback;
        direct_glyph_tile(index, variant, output, 0);
        output += 8;
    }
}

void direct_tall_tiles(const u8 *text, u32 colour, u32 *output) {
    size_t length = tall_direct_length(text);
    if (!length)
        return;
    u8 variant = (u8)(umod((u8)colour, 3) + 1);
    for (size_t position = 0; position + 1 < length; position += 2) {
        u16 code = (u16)((text[position] << 8) | text[position + 1]);
        int index = text_font_find(&runtime_font_data, TEXT_FACE_TALL, code);
        if (index < 0)
            index = runtime_font_data.tall_fallback;
        direct_glyph_tile((u16)index, variant, output, direct_tall_tile);
        output += 16;
    }
}
