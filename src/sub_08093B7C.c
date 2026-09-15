#include "m2c_prelude.h"

extern s32 func_08092A90(s16);
extern u16 func_08092ADC(s16);
extern s32 func_080ECD30(s32, s32);

#define OBSERVE_SIGNED(value) ({ \
    s32 observed = (value); \
    asm volatile("" : "+r"(observed)); \
    observed; \
})

union PackedAngles {
    s32 packed;
    struct {
        u16 first;
        u16 second;
    } angle;
};

struct ViewState {
    s32 origin_x;
    s32 origin_y;
    s32 depth;
    union PackedAngles angles;
    s16 field_10;
    u16 pad_12;
    s32 scale;
    s32 center;
    s32 distance;
    u8 pad_20[8];
    s32 previous_depth;
    union PackedAngles previous_angles;
    s16 previous_field_10;
    u16 pad_32;
    s32 previous_scale;
    s32 previous_center;
    s32 previous_distance;
    u8 pad_40[0x20];
    s32 limit;
};

struct ProjectionRecord {
    s16 x_scale;
    s16 y_scale;
    s16 negative_y_scale;
    s16 x_scale_copy;
    s32 x;
    s32 y;
};

struct ProjectionView {
    s32 scale;
    s32 center;
    s32 distance;
};

u8 sub_08093B7C(void)
{
    register struct ViewState *state asm("r6");
    register struct ViewState *state_base asm("r8");
    u8 dirty = *(volatile u8 *)0x03005F70;
    register s32 sine asm("r10");
    register s32 cosine asm("r4");
    register s32 cosine_shifted asm("r9");
    s32 vertical_sine;
    s32 vertical_cosine;
    struct ProjectionRecord *record;
    s32 initial_numerator;
    s32 limit;
    s32 line;
    register volatile u8 *phase asm("r1");
    register u32 next_phase asm("r0");

    state = (struct ViewState *)0x030033C4;
    if (dirty != 0 ||
        state->depth != state->previous_depth ||
        state->angles.packed != state->previous_angles.packed ||
        OBSERVE_SIGNED(state->field_10) !=
            OBSERVE_SIGNED(state->previous_field_10) ||
        state->scale != state->previous_scale ||
        state->center != state->previous_center ||
        state->distance != state->previous_distance) {
        phase = (volatile u8 *)0x030034A0;
        next_phase = 0;
        goto store_phase;
    }
    phase = (volatile u8 *)0x030034A0;
    next_phase = *phase;
    if (next_phase <= 1) {
        next_phase++;
store_phase:
        *phase = next_phase;
    }

    sine = func_08092ADC(-(s16)state->angles.angle.first);
    cosine = func_08092A90(-(s16)state->angles.angle.first);
    asm volatile("" : "+r"(cosine));
    cosine = (u16)cosine;
    vertical_sine = func_08092ADC(-(s16)state->angles.angle.second);
    vertical_cosine = (u16)func_08092A90(
        -(s16)state->angles.angle.second);

    record = (struct ProjectionRecord *)(*(s32 *)0x03003428 +
        ((1 ^ *(u8 *)0x0300342C) * 0xA00));
    state_base = state;
    state = (struct ViewState *)((u8 *)state + 0x14);
    {
        register struct ViewState *limit_base asm("r3") = state_base;

        limit = limit_base->limit;
    }
    cosine <<= 16;
    {
        register s32 cosine_value asm("r1") = cosine >> 16;
        register s32 distance_value asm("r0") =
            ((struct ProjectionView *)state)->distance;
        register s32 distance_product asm("r2");
        register struct ViewState *depth_base asm("r1");
        register s32 depth_value asm("r0");
        register s32 result asm("r3");

        asm volatile("" : "+r"(cosine_value), "+r"(distance_value));
        distance_product = distance_value;
        distance_product *= cosine_value;
        depth_base = state_base;
        depth_value = depth_base->depth;
        depth_value /= 0x100;
        asm volatile("" : "+r"(depth_value));
        result = depth_value;
        result *= distance_product;
        asm volatile("" : "+r"(result));
        initial_numerator = result;
    }

    line = 0;
    cosine_shifted = cosine;
    {
        register s32 sine_shifted asm("r0") = sine;

        asm volatile("" : "+r"(sine_shifted));
        sine_shifted <<= 16;
        sine = sine_shifted;
    }
    for (; line <= 159; record++, line++) {
        register s32 division_denominator asm("r1");
        register s32 cosine_value asm("r4");
        register s32 perspective asm("r2");
        register s32 second_numerator asm("r0");

        if (*(u8 *)0x030034A0 == 2) {
            register s32 cosine_source asm("r2") = cosine_shifted;

            asm volatile("" : "+r"(cosine_source));
            division_denominator = cosine_source >> 16;
            if (division_denominator == 0) {
                goto clear_record;
            }
            second_numerator = (line -
                ((struct ProjectionView *)state)->center) << 8;
            goto project_record;
        } else {
            register s32 sine_source asm("r2");
            register s32 cosine_source asm("r3") = cosine_shifted;
            register s32 distance_value asm("r3");
            register s32 denominator asm("r0");
            register s32 cosine_component asm("r12");
            register s32 sine_value asm("r1");

            cosine_value = cosine_source >> 16;
            distance_value = ((struct ProjectionView *)state)->distance;
            denominator = distance_value;
            denominator *= cosine_value;
            cosine_component = denominator;
            denominator =
                ((struct ProjectionView *)state)->center - line;
            sine_source = sine;
            sine_value = sine_source >> 16;
            denominator *= sine_value;
            denominator += cosine_component;
            denominator /= 0x100;
            asm volatile("" : "+r"(denominator));
            division_denominator = denominator;
            division_denominator *= distance_value;
            if (division_denominator == 0) {
                goto clear_record;
            }

            perspective = func_080ECD30(initial_numerator,
                division_denominator);
            record->x_scale = record->x_scale_copy =
                ((s16)vertical_sine * perspective) / 0x100;
            record->y_scale = ((s16)vertical_cosine * perspective) / 0x100;
            record->negative_y_scale = -record->y_scale;
            second_numerator = (line -
                ((struct ProjectionView *)state)->center) << 8;
            division_denominator = cosine_value;
        }

project_record:
        perspective = func_080ECD30(second_numerator, division_denominator);
        {
            register s32 negative_scale asm("r0");
            register s32 projected_value asm("r1");
            register s32 projection_term asm("r0");
            register struct ViewState *origin_base_x asm("r3");
            register struct ViewState *origin_base_y asm("r2");

            negative_scale = -((struct ProjectionView *)state)->scale;
            projected_value = record->x_scale;
            projected_value *= negative_scale;
            projection_term = record->y_scale;
            projection_term *= perspective;
            projected_value -= projection_term;
            origin_base_x = state_base;
            projected_value += origin_base_x->origin_x;
            record->x = projected_value;

            negative_scale = -((struct ProjectionView *)state)->scale;
            projected_value = record->negative_y_scale;
            projected_value *= negative_scale;
            projection_term = record->x_scale_copy;
            projection_term *= perspective;
            projected_value -= projection_term;
            origin_base_y = state_base;
            projected_value += origin_base_y->origin_y;
            record->y = projected_value;
        }
        continue;

clear_record:
        record->y = division_denominator;
        record->x = division_denominator;
        *(s32 *)&record->negative_y_scale = division_denominator;
        *(s32 *)&record->x_scale = division_denominator;
    }

    {
        register s32 sine_source asm("r3") = sine;
        register s32 sine_value asm("r2");
        register struct ViewState *depth_base asm("r1");
        register s32 numerator asm("r0");
        register s32 limit_value asm("r3");
        register s32 cosine_value asm("r1");
        register s32 scaled_numerator asm("r1");
        register s32 numerator_product asm("r4");
        register s32 denominator asm("r0");
        register s32 denominator_limit asm("r1");
        register s32 scaled_denominator asm("r1");
        u32 result;

        asm volatile("" : "+r"(sine_source));
        sine_value = (s16)(sine_source >> 16);
        if (sine_value != 0) {
            depth_base = state_base;
            numerator = depth_base->depth;
            limit_value = limit;
            asm volatile("" : "+r"(limit_value));
            numerator = limit_value - numerator;
            cosine_value = (s16)(cosine_shifted >> 16);
            numerator *= cosine_value;
            scaled_numerator = numerator / 0x100;
            asm volatile("" : "+r"(scaled_numerator));
            numerator_product = scaled_numerator;
            numerator_product *= ((struct ProjectionView *)state)->distance;
            denominator_limit = limit;
            denominator = sine_value;
            asm volatile("" : "+r"(denominator));
            denominator *= denominator_limit;
            scaled_denominator = denominator / 0x100;
            result = func_080ECD30(numerator_product, scaled_denominator) +
                ((struct ProjectionView *)state)->center;
            if (result <= 159) {
                return (u8)result;
            }
        }
    }
    return 0xFF;
}
