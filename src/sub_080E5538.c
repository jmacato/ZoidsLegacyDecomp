#include "m2c_prelude.h"

struct ConfigE5538 {
    u8 bytes[4];
    u16 stats[10];
    u32 words[8];
};

struct ObjectE5538 {
    u8 type;
    u8 pad01[0x0F];
    s16 level;
    u8 bonus_a[6];
    u8 bonus_b[0x1E];
    u8 config_bytes[4];
    u16 stats[10];
    u32 words[8];
};

extern struct ConfigE5538 D_087AFCC4[];

u16 func_080E522C(s16, s32);
u8 func_080E523C(u8);

void sub_080E5538(struct ObjectE5538 *object)
{
    struct ConfigE5538 *config;
    u8 i;

    config = &D_087AFCC4[object->type];
    asm volatile("" : : "r"(config));
    asm volatile("" : : "r"(config));
    asm volatile("" : : "r"(config));
    object->config_bytes[0] = config->bytes[0];
    object->config_bytes[1] = config->bytes[1];
    object->config_bytes[2] = config->bytes[2];
    object->config_bytes[3] = config->bytes[3];

    i = 4;
    do {
        object->words[i] = config->words[i];
        i++;
    } while (i <= 7);

    object->stats[0] = config->stats[0];
    object->stats[1] = config->stats[1];
    object->stats[2] = config->stats[2];
    {
        register u16 *stat3 asm("r5");
        register u16 *stat4 asm("r9");
        register u16 *stat5 asm("r8");
        register u16 *stat6 asm("r4");
        register u16 *stat9 asm("r6");
        register s32 scale asm("r4");
        u8 bonus_index;
        u16 value;
        register u16 captured_value asm("r0");

        value = config->stats[3];
        stat3 = &object->stats[3];
        asm volatile("" : "+r"(stat3));
        *stat3 = value;
        captured_value = config->stats[4];
        asm volatile("" : "+r"(captured_value));
        stat4 = &object->stats[4];
        *stat4 = captured_value;
        captured_value = config->stats[5];
        asm volatile("" : "+r"(captured_value));
        stat5 = &object->stats[5];
        *stat5 = captured_value;
        value = config->stats[6];
        stat6 = &object->stats[6];
        asm volatile("" : "+r"(stat6));
        *stat6 = value;
        object->stats[7] = config->stats[7];
        object->stats[8] = config->stats[8];
        value = config->stats[9];
        stat9 = &object->stats[9];
        asm volatile("" : "+r"(stat9));
        *stat9 = value;

        bonus_index = func_080E523C(object->type);
        *stat3 += object->bonus_a[bonus_index];
        {
            register u32 bonus asm("r0") =
                object->bonus_b[bonus_index] * 5;
            register u32 current asm("r2") = *stat6;

            asm volatile("" : "+r"(bonus));
            asm volatile("" : "+r"(current));
            *stat6 = bonus + current;
        }

        {
            register s32 phase1 asm("r1");
            register s32 phase2 asm("r2");

            asm volatile("" : "=r"(phase1));
            asm volatile("" : "=r"(phase2));
            scale = object->level;
            asm volatile("" : : "r"(phase1), "r"(phase2));
        }
        scale = (s32)(scale + ((u32)scale >> 31)) >> 1;
        scale += 100;
        asm volatile("" : "+r"(scale));

        object->stats[0] = func_080E522C((s16)object->stats[0], scale);
        {
            register s32 phase asm("r1");

            asm volatile("" : "=r"(phase));
            object->stats[1] = func_080E522C((s16)object->stats[1],
                ({ asm volatile("" : : "r"(phase)); scale; }));
        }
        object->stats[2] = func_080E522C((s16)object->stats[2], scale);
        *stat3 = func_080E522C((s16)*stat3, scale);
        *stat4 = func_080E522C(
            ({
                register u16 *view asm("r1") = stat4;

                asm volatile("" : "+r"(view));
                *(s16 *)view;
            }), scale);
        {
            register u16 result asm("r0");

            result = func_080E522C(
                ({
                    register u16 *view asm("r2") = stat5;

                    asm volatile("" : "+r"(view));
                    *(s16 *)view;
                }), scale);
            {
                register u16 *view asm("r2") = stat5;

                asm volatile("" : "+r"(view));
                *view = result;
            }
        }
        {
            register s32 phase asm("r2");

            asm volatile("" : "=r"(phase));
            *stat9 = func_080E522C((s16)*stat9,
                ({ asm volatile("" : : "r"(phase)); scale; }));
        }
    }
}
