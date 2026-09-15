#include "m2c_prelude.h"

struct CollisionRecord {
    u32 unk0;
    u8 unk4;
    u8 pad5;
    u16 unk6;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    u8 unk18;
};

u16 func_080AB224(u8, s32, s32);                    /* extern */
u16 func_080AB268(u8, u16, s32, s32);               /* extern */
struct CollisionRecord;
s32 func_080AC098(struct CollisionRecord *);        /* extern */

void sub_080AB2EC(struct CollisionRecord *arg0) {
    volatile s32 sp0;
    volatile s32 sp4;
    volatile s32 sp8;
    volatile s32 spC;
    volatile s32 sp10;
    volatile s32 sp14;
    volatile s32 sp18;
    register s32 temp_r0 asm("r0");
    register s32 temp_r0_11 asm("r0");
    register s32 temp_r0_16 asm("r0");
    register s32 temp_r0_6 asm("r0");
    s32 initial_delta;
    u16 mode;
    register s32 temp_r1 asm("r9");
    register s32 temp_r2 asm("r10");
    register s32 temp_r2_2 asm("r10");
    register s32 temp_r4 asm("r4");
    register s32 temp_r5 asm("r5");
    s32 temp_r7_2;
    s32 var_r0;
    register s32 var_r0_10 asm("r0");
    register s32 var_r0_11 asm("r0");
    s32 var_r0_12;
    register s32 var_r0_13 asm("r0");
    s32 var_r0_14;
    register s32 var_r0_15 asm("r0");
    register s32 var_r0_2 asm("r0");
    s32 var_r0_3;
    s32 var_r0_4;
    register s32 var_r0_5 asm("r0");
    register s32 var_r0_6 asm("r0");
    s32 var_r0_7;
    register s32 var_r0_8 asm("r0");
    s32 var_r0_9;
    register s32 var_r1 asm("r1");
    register s32 var_r1_2 asm("r1");
    register s32 var_r1_3 asm("r1");
    register s32 var_r1_4 asm("r1");
    s32 var_r1_5;
    s32 var_r1_6;
    register s32 var_r1_7 asm("r1");
    register s32 var_r1_8 asm("r1");
    s32 var_r2;
    s32 var_r2_10;
    s32 var_r2_11;
    s32 var_r2_2;
    s32 var_r2_3;
    s32 var_r2_4;
    s32 var_r2_5;
    s32 var_r2_6;
    register s32 var_r2_7 asm("r2");
    register s32 var_r2_8 asm("r2");
    register s32 var_r2_9 asm("r2");
    register s32 var_r3 asm("r3");
    s32 var_r3_2;
    s32 var_r3_3;
    s32 var_r3_4;
    s32 var_r3_5;
    register s32 var_r3_6 asm("r3");
    s32 var_r3_7;
    s32 var_r3_8;
    s32 var_r3_9;
    s32 var_r4;
    s32 var_r4_2;
    register s32 var_sl asm("r10");
    s32 var_sl_2;
    u32 temp_r1_3;
    register u32 mode1_remainder asm("r8");
    register u32 mode1_initial_check asm("r1");
    u32 temp_r7;
    u32 temp_r7_3;
    u8 temp_r0_10;
    u8 temp_r0_12;
    u8 temp_r0_13;
    u8 temp_r0_14;
    u8 temp_r0_15;
    u8 temp_r0_17;
    u8 temp_r0_18;
    u8 temp_r0_19;
    u8 temp_r0_20;
    u8 temp_r0_2;
    u8 temp_r0_3;
    u8 temp_r0_4;
    u8 temp_r0_5;
    u8 temp_r0_7;
    u8 temp_r0_8;
    u8 temp_r0_9;

    if (((u32) (u16) (arg0->unk6 - 6) > 1U) && !(arg0->unk0 & 4)) {
        sp8 = arg0->unk10;
        spC = arg0->unk14;
        mode = *(u16 *)0x0202ECF4;
        initial_delta = sp8;
        if (mode == 0) {
            if (initial_delta == 0) {
                goto block_74;
            }
            temp_r0_11 = arg0->unk8;
            asm volatile("" : "+r"(temp_r0_11));
            if (initial_delta > 0) {
                register s32 adjusted asm("r2");
                adjusted = 0x800;
                asm volatile("" : "+r"(adjusted));
                adjusted = temp_r0_11 + adjusted;
                sp0 = adjusted;
                asm volatile("" ::: "memory");
            } else {
                register s32 adjusted asm("r4");
                adjusted = 0xFFFFF800;
                asm volatile("" : "+r"(adjusted));
                adjusted = temp_r0_11 + adjusted;
                sp0 = adjusted;
            }
            sp4 = arg0->unkC;
            {
                register s32 base asm("r1");
                base = sp0;
                asm volatile("" : "+r"(base));
                temp_r5 = base + initial_delta;
            }
            var_r1_3 = temp_r5;
            asm volatile("" : "+r"(var_r1_3));
            if (temp_r5 < 0) {
                register s32 rounding asm("r2");
                rounding = 0xFFF;
                asm volatile("" : "+r"(rounding));
                var_r1_3 = temp_r5 + rounding;
            }
            temp_r1 = var_r1_3 >> 0xC;
            var_r2_8 = sp4;
            if (var_r2_8 < 0) {
                register s32 rounding asm("r3");
                rounding = 0xFFF;
                asm volatile("" : "+r"(rounding));
                var_r2_8 += rounding;
            }
            temp_r2 = var_r2_8 >> 0xC;
            sp10 = (s32) func_080AB224(arg0->unk4, temp_r1, temp_r2 - 1);
            sp14 = (s32) func_080AB224(arg0->unk4, temp_r1, temp_r2);
            sp18 = (s32) func_080AB224(arg0->unk4, temp_r1, temp_r2 + 1);
            {
                register s32 mask asm("r0");
                temp_r4 = 0xFFF;
                asm volatile("" : "+r"(temp_r4));
                mask = temp_r4;
                asm volatile("" : "+r"(mask));
                temp_r7_3 = sp4 & mask;
            }
            if (((temp_r7_3 <= 0x7FFU) && ((sp14 != 0) || (({ register s32 query asm("r1") = sp10; asm volatile("" : "+r"(query)); query; }) != 0))) || (({ register s32 query asm("r2") = sp14; asm volatile("" : "+r"(query)); query; }) != 0) || ((temp_r7_3 > 0x800U) && (({ register s32 query asm("r3") = sp18; asm volatile("" : "+r"(query)); query; }) != 0))) {
                if ((s32) arg0->unk10 > 0) {
                    var_r0_7 = temp_r5;
                    if (temp_r5 < 0) {
                        register s32 rounding asm("r4");
                        rounding = 0xFFF;
                        asm volatile("" : "+r"(rounding));
                        var_r0_7 = temp_r5 + rounding;
                    }
                    var_r0_8 = (var_r0_7 >> 0xC) << 0xC;
                    var_r1_4 = sp0;
                } else {
                    var_r0_9 = temp_r5;
                    if (temp_r5 < 0) {
                        register s32 rounding asm("r2");
                        rounding = 0xFFF;
                        asm volatile("" : "+r"(rounding));
                        var_r0_9 = temp_r5 + rounding;
                    }
                    var_r0_8 = (var_r0_9 >> 0xC) << 0xC;
                    {
                        register s32 base asm("r3");
                        register s32 offset asm("r4");
                        base = sp0;
                        offset = 0xFFFFF000;
                        asm volatile("" : "+r"(base), "+r"(offset));
                        var_r1_4 = base + offset;
                    }
                }
                asm volatile("" : "+r"(var_r1_4));
                sp8 = var_r0_8 - var_r1_4;
            }
            if ((s32) arg0->unk14 <= 0) {
                if (temp_r7_3 <= 0x800U) {
                    if ((sp10 == 0) && (({ register s32 query asm("r1") = sp14; asm volatile("" : "+r"(query)); query; }) != 0)) {
                        u8 kind;
                        s32 delta;
                        kind = arg0->unk4;
                        delta = arg0->unk10;
                        var_r1_5 = temp_r1 + 1;
                        if (delta > 0) {
                            var_r1_5 -= 2;
                        }
                        if ((func_080AB224(kind, var_r1_5, temp_r2 - 1) << 0x10) == 0) {
                            temp_r0_12 = arg0->unk18;
                            if (temp_r0_12 == 2) {
                                register s32 correction asm("r2");
                                correction = -0xB5;
                                asm volatile("" : "+r"(correction));
                                spC = correction;
                            } else if (temp_r0_12 == 3) {
                                register s32 correction asm("r3");
                                correction = -0x16A;
                                asm volatile("" : "+r"(correction));
                                spC = correction;
                                asm volatile("");
                            }
                        } else {
                            goto block_39;
                        }
                    } else {
block_39:
                        if (temp_r7_3 > 0x800U) {
                            goto block_40;
                        }
                    }
                } else {
block_40:
                    if ((({ register s32 query asm("r4") = sp14; asm volatile("" : "+r"(query)); query; }) == 0) && (sp18 != 0)) {
                        temp_r0_13 = arg0->unk18;
                        if (temp_r0_13 == 2) {
                            var_r0_10 = 0x7FF;
                            spC = -0xB5;
                            if (temp_r7_3 > (u32)var_r0_10) {
                                var_r0_10 = sp4 - 0xB5;
                                goto block_49;
                            }
                        } else if (temp_r0_13 == 3) {
                            register s32 offset asm("r3");
                            var_r0_10 = 0x7FF;
                            offset = -0x16A;
                            asm volatile("" : "+r"(offset));
                            spC = offset;
                            if (temp_r7_3 > (u32)var_r0_10) {
                                register s32 base asm("r4");
                                base = sp4;
                                asm volatile("" : "+r"(base));
                                var_r0_10 = base + offset;
block_49:
                                {
                                    register s32 masked asm("r0");
                                    register s32 threshold asm("r1");
                                    masked = var_r0_10;
                                    threshold = 0xFFF;
                                    asm volatile("" : "+r"(masked), "+r"(threshold));
                                    masked &= threshold;
                                    threshold = 0x800;
                                    asm volatile("" : "+r"(threshold));
                                    if (masked <= threshold) {
                                        threshold -= temp_r7_3;
                                        spC = threshold;
                                    }
                                }
                            }
                        }
                    }
                }
                if (arg0->unk14 >= 0) {
                    goto block_52;
                }
                goto block_75;
            }
block_52:
            if (temp_r7_3 > 0x7FFU) {
                if ((sp18 == 0) && (({ register s32 query asm("r1") = sp14; asm volatile("" : "+r"(query)); query; }) != 0)) {
                    u8 kind;
                    s32 delta;
                    kind = arg0->unk4;
                    delta = arg0->unk10;
                    var_r1_6 = temp_r1 + 1;
                    if (delta > 0) {
                        var_r1_6 -= 2;
                    }
                    if ((func_080AB224(kind, var_r1_6, temp_r2 + 1) << 0x10) == 0) {
                        temp_r0_14 = arg0->unk18;
                        if (temp_r0_14 == 2) {
                            register s32 correction asm("r2");
                            correction = 0xB5;
                            asm volatile("" : "+r"(correction));
                            spC = correction;
                        } else if (temp_r0_14 == 3) {
                            var_r3_9 = 0x16A;
                            goto block_73;
                        }
                    } else {
                        goto block_62;
                    }
                } else {
block_62:
                    if (temp_r7_3 <= 0x7FFU) {
                        goto block_63;
                    }
                }
            } else {
block_63:
                if ((({ register s32 query asm("r4") = sp14; asm volatile("" : "+r"(query)); query; }) == 0) && (sp10 != 0)) {
                    temp_r0_15 = arg0->unk18;
                    if (temp_r0_15 == 2) {
                        var_r3_9 = 0x800;
                        {
                            register s32 correction asm("r1");
                            correction = 0xB5;
                            asm volatile("" : "+r"(correction));
                            spC = correction;
                        }
                        if (temp_r7_3 <= (u32)var_r3_9) {
                            var_r0_11 = sp4 + 0xB5;
                            goto block_71;
                        }
                    } else if (temp_r0_15 == 3) {
                        var_r3_9 = 0x800;
                        temp_r4 = 0x16A;
                        spC = temp_r4;
                        if (temp_r7_3 <= (u32)var_r3_9) {
                            register s32 base asm("r1");
                            base = sp4;
                            asm volatile("" : "+r"(base));
                            var_r0_11 = base + temp_r4;
block_71:
                            {
                                register s32 masked asm("r0");
                                register s32 threshold asm("r1");
                                masked = var_r0_11;
                                threshold = 0xFFF;
                                asm volatile("" : "+r"(masked), "+r"(threshold));
                                masked &= threshold;
                                threshold = 0x7FF;
                                asm volatile("" : "+r"(threshold));
                                if (masked > threshold) {
                                var_r3_9 -= temp_r7_3;
block_73:
                                spC = var_r3_9;
                                }
                            }
                        }
                    }
                }
            }
block_74:
            if (arg0->unk14 != 0) {
block_75:
                {
                    register s32 base asm("r0");
                    register s32 delta asm("r3");
                    base = arg0->unk8;
                    asm volatile("" : "+r"(base));
                    delta = sp8;
                    asm volatile("" : "+r"(delta));
                    base += delta;
                    sp0 = base;
                }
                temp_r0_16 = arg0->unkC;
                asm volatile("" : "+r"(temp_r0_16));
                if (arg0->unk14 > 0) {
                    register s32 adjusted asm("r4");
                    adjusted = 0x800;
                    asm volatile("" : "+r"(adjusted));
                    adjusted = temp_r0_16 + adjusted;
                    sp4 = adjusted;
                    asm volatile("" ::: "memory");
                } else {
                    register s32 adjusted asm("r1");
                    adjusted = 0xFFFFF800;
                    asm volatile("" : "+r"(adjusted));
                    adjusted = temp_r0_16 + adjusted;
                    sp4 = adjusted;
                }
                {
                    register s32 base asm("r3");
                    base = sp4;
                    asm volatile("" : "+r"(base));
                    temp_r7_2 = base + arg0->unk14;
                }
                var_r1_7 = sp0;
                asm volatile("" : "+r"(var_r1_7));
                if (var_r1_7 < 0) {
                    register s32 rounding asm("r4");
                    rounding = 0xFFF;
                    asm volatile("" : "+r"(rounding));
                    var_r1_7 += rounding;
                }
                temp_r1 = var_r1_7 >> 0xC;
                var_r2_9 = temp_r7_2;
                if (temp_r7_2 < 0) {
                    register s32 rounding asm("r0");
                    rounding = 0xFFF;
                    asm volatile("" : "+r"(rounding));
                    var_r2_9 = temp_r7_2 + rounding;
                }
                {
                    u8 kind;
                    temp_r2_2 = var_r2_9 >> 0xC;
                    kind = arg0->unk4;
                    temp_r5 = temp_r1 - 1;
                    sp10 = (s32) func_080AB224(kind, temp_r5, temp_r2_2);
                }
                sp14 = (s32) func_080AB224(arg0->unk4, temp_r1, temp_r2_2);
                {
                    u8 kind;
                    kind = arg0->unk4;
                    temp_r4 = temp_r1 + 1;
                    sp18 = (s32) func_080AB224(kind, temp_r4, temp_r2_2);
                }
                {
                    register s32 mask asm("r0");
                    register s32 mask_source asm("r1");
                    register u32 source asm("r2");
                    register u32 remainder asm("r8");
                    register u32 masked asm("r3");
                    mask_source = 0xFFF;
                    asm volatile("" : "+r"(mask_source));
                    mask = mask_source;
                    asm volatile("" : "+r"(mask));
                    source = sp0;
                    asm volatile("" : "+r"(source));
                    remainder = source;
                    asm volatile("" : "+r"(remainder));
                    masked = remainder;
                    asm volatile("" : "+r"(masked));
                    masked &= mask;
                    remainder = masked;
                    asm volatile("" : "+r"(remainder));
                    temp_r1_3 = remainder;
                }
                if (((temp_r1_3 <= 0x7FFU) && (sp10 != 0)) || (({ register s32 query asm("r1") = sp14; asm volatile("" : "+r"(query)); query; }) != 0) || ((temp_r1_3 > 0x800U) && (({ register s32 query asm("r2") = sp18; asm volatile("" : "+r"(query)); query; }) != 0))) {
                    if ((s32) arg0->unk14 > 0) {
                        var_r0_12 = temp_r7_2;
                        if (temp_r7_2 < 0) {
                            register s32 rounding asm("r3");
                            rounding = 0xFFF;
                            asm volatile("" : "+r"(rounding));
                            var_r0_12 = temp_r7_2 + rounding;
                        }
                        var_r0_13 = (var_r0_12 >> 0xC) << 0xC;
                        var_r1_8 = sp4;
                    } else {
                        var_r0_14 = temp_r7_2;
                        if (temp_r7_2 < 0) {
                            register s32 rounding asm("r2");
                            rounding = 0xFFF;
                            asm volatile("" : "+r"(rounding));
                            var_r0_14 = temp_r7_2 + rounding;
                        }
                        var_r0_13 = (var_r0_14 >> 0xC) << 0xC;
                        {
                            register s32 base asm("r3");
                            base = sp4;
                            asm volatile("" : "+r"(base));
                            var_r1_8 = base + 0xFFFFF000;
                        }
                    }
                    asm volatile("" : "+r"(var_r1_8));
                    spC = var_r0_13 - var_r1_8;
                }
                if ((s32) arg0->unk10 <= 0) {
                    if (temp_r1_3 <= 0x800U) {
                        if ((({ register s32 query asm("r3") = sp10; asm volatile("" : "+r"(query)); query; }) == 0) && (sp14 != 0)) {
                            u8 kind;
                            s32 delta;
                            kind = arg0->unk4;
                            delta = arg0->unk14;
                            var_r2_10 = temp_r2_2 + 1;
                            if (delta > 0) {
                                var_r2_10 -= 2;
                            }
                            if ((func_080AB224(kind, temp_r5, var_r2_10) << 0x10) == 0) {
                                temp_r0_17 = arg0->unk18;
                                if (temp_r0_17 == 2) {
                                    register s32 correction asm("r1");
                                    correction = -0xB5;
                                    asm volatile("" : "+r"(correction));
                                    sp8 = correction;
                                } else if (temp_r0_17 == 3) {
                                    register s32 correction asm("r2");
                                    correction = -0x16A;
                                    asm volatile("" : "+r"(correction));
                                    sp8 = correction;
                                    asm volatile("");
                                }
                            } else {
                                goto block_108;
                            }
                        } else {
block_108:
                            if (temp_r1_3 > 0x800U) {
                                goto block_109;
                            }
                        }
                    } else {
block_109:
                        if ((sp14 == 0) && (({ register s32 query asm("r1") = sp18; asm volatile("" : "+r"(query)); query; }) != 0)) {
                            temp_r0_18 = arg0->unk18;
                            if (temp_r0_18 == 2) {
                                var_r0_15 = 0x7FF;
                                {
                                    register s32 correction asm("r2");
                                    correction = -0xB5;
                                    asm volatile("" : "+r"(correction));
                                    sp8 = correction;
                                }
                                if (temp_r1_3 > (u32)var_r0_15) {
                                    var_r0_15 = sp0 - 0xB5;
                                    goto block_118;
                                }
                            } else if (temp_r0_18 == 3) {
                                var_r0_15 = 0x7FF;
                                var_r1_8 = -0x16A;
                                sp8 = var_r1_8;
                                if (temp_r1_3 > (u32)var_r0_15) {
                                    register s32 base asm("r2");
                                    base = sp0;
                                    asm volatile("" : "+r"(base));
                                    var_r0_15 = base + var_r1_8;
block_118:
                                    {
                                        register s32 masked asm("r0");
                                        register s32 threshold asm("r1");
                                        masked = var_r0_15;
                                        threshold = 0xFFF;
                                        asm volatile("" : "+r"(masked), "+r"(threshold));
                                        masked &= threshold;
                                        threshold = 0x800;
                                        asm volatile("" : "+r"(threshold));
                                        if (masked <= threshold) {
                                            masked = temp_r1_3;
                                            asm volatile("" : "+r"(masked));
                                            masked = threshold - masked;
                                            sp8 = masked;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    if (arg0->unk10 < 0) {

                    } else {
                        goto block_122;
                    }
                } else {
block_122:
                    if (temp_r1_3 > 0x7FFU) {
                        if ((({ register s32 query asm("r1") = sp18; asm volatile("" : "+r"(query)); query; }) == 0) && (({ register s32 query asm("r2") = sp14; asm volatile("" : "+r"(query)); query; }) != 0)) {
                            u8 kind;
                            s32 delta;
                            kind = arg0->unk4;
                            delta = arg0->unk14;
                            var_r2_11 = temp_r2_2 + 1;
                            if (delta > 0) {
                                var_r2_11 -= 2;
                            }
                            if ((func_080AB224(kind, temp_r4, var_r2_11) << 0x10) == 0) {
                                temp_r0_19 = arg0->unk18;
                                if (temp_r0_19 == 2) {
                                    var_r3_6 = 0xB5;
                                    goto block_326;
                                } else if (temp_r0_19 == 3) {
                                    register s32 correction asm("r4");
                                    correction = 0x16A;
                                    asm volatile("" : "+r"(correction));
                                    sp8 = correction;
                                    asm volatile("" ::: "memory");
                                }
                            } else {
                                goto block_134;
                            }
                        } else {
block_134:
                            if (temp_r1_3 > 0x7FFU) {

                            } else {
                                goto block_136;
                            }
                        }
                    } else {
block_136:
                        if (sp14 != 0) {

                        } else if (({ register s32 query asm("r1") = sp10; asm volatile("" : "+r"(query)); query; }) == 0) {

                        } else {
                            temp_r0_20 = arg0->unk18;
                            if (temp_r0_20 == 2) {
                                var_r2_11 = 0x800;
                                {
                                    register s32 correction asm("r3");
                                    correction = 0xB5;
                                    asm volatile("" : "+r"(correction));
                                    sp8 = correction;
                                }
                                if (temp_r1_3 > (u32)var_r2_11) {

                                } else if ((s32) ((sp0 + 0xB5) & 0xFFF) <= 0x7FF) {

                                } else {
                                    register s32 correction asm("r4");
                                    correction = temp_r1_3;
                                    asm volatile("" : "+r"(correction));
                                    correction = var_r2_11 - correction;
                                    sp8 = correction;
                                    asm volatile("" ::: "memory");
                                }
                            } else if (temp_r0_20 == 3) {
                                var_r2_11 = 0x800;
                                var_r0_15 = 0x16A;
                                sp8 = var_r0_15;
                                if (temp_r1_3 > (u32)var_r2_11) {

                                } else if ((s32) ({
                                    register s32 aux asm("r1");
                                    aux = sp0;
                                    asm volatile("" : "+r"(aux));
                                    var_r0_15 = aux + var_r0_15;
                                    asm volatile("" : "+r"(var_r0_15));
                                    aux = 0xFFF;
                                    asm volatile("" : "+r"(aux));
                                    var_r0_15 &= aux;
                                    asm volatile("" : "+r"(var_r0_15));
                                    var_r0_15;
                                }) <= 0x7FF) {

                                } else {
                                    register s32 correction asm("r3");
                                    correction = temp_r1_3;
                                    asm volatile("" : "+r"(correction));
                                    correction = var_r2_11 - correction;
                                    var_r3_6 = correction;
                                    goto block_326;
                                }
                            }
                        }
                    }
                }
            }
        } else {
            register s32 mode_delta asm("r4");
            mode_delta = sp8;
            asm volatile("" : "+r"(mode_delta));
            if (mode_delta == 0) {
                goto block_240;
            }
            temp_r0 = arg0->unk8;
            asm volatile("" : "+r"(temp_r0));
            if (mode_delta > 0) {
                register s32 adjusted asm("r1");
                adjusted = 0x800;
                asm volatile("" : "+r"(adjusted));
                adjusted = temp_r0 + adjusted;
                sp0 = adjusted;
                asm volatile("" ::: "memory");
            } else {
                register s32 adjusted asm("r2");
                adjusted = 0xFFFFF800;
                asm volatile("" : "+r"(adjusted));
                adjusted = temp_r0 + adjusted;
                sp0 = adjusted;
            }
            sp4 = ({ register s32 value asm("r4") = arg0->unkC; value; });
            {
                register s32 base asm("r0");
                base = sp0;
                asm volatile("" : "+r"(base));
                temp_r5 = base + initial_delta;
            }
            var_r1 = temp_r5;
            asm volatile("" : "+r"(var_r1));
            if (temp_r5 < 0) {
                register s32 rounding asm("r2");
                rounding = 0x7FF;
                asm volatile("" : "+r"(rounding));
                var_r1 = temp_r5 + rounding;
            }
            temp_r1 = var_r1 >> 0xB;
            var_r4 = sp4;
            if (var_r4 < 0) {
                register s32 rounding asm("r3");
                rounding = 0x7FF;
                asm volatile("" : "+r"(rounding));
                var_r4 += rounding;
            }
            {
                s32 tile_y;
                s32 adjustment;
                tile_y = var_r4 >> 0xB;
                adjustment = func_080AC098(arg0);
                adjustment <<= 0x18;
                var_sl = tile_y;
                if (adjustment == 0) {
                    register s32 one asm("r4");
                    one = 1;
                    asm volatile("" : "+r"(one));
                    var_sl += one;
                }
            }
            sp10 = (s32) func_080AB268(arg0->unk4, arg0->unk6, temp_r1, var_sl - 1);
            sp14 = (s32) func_080AB268(arg0->unk4, arg0->unk6, temp_r1, var_sl);
            {
                u8 kind;
                u16 state;
                kind = arg0->unk4;
                state = arg0->unk6;
                temp_r4 = var_sl + 1;
                sp18 = (s32) func_080AB268(kind, state, temp_r1, temp_r4);
            }
            {
                register s32 mask asm("r0");
                register s32 mask_source asm("r1");
                mask_source = 0x7FF;
                asm volatile("" : "+r"(mask_source));
                mask = mask_source;
                asm volatile("" : "+r"(mask));
                temp_r7 = sp4 & mask;
            }
            if ((({ register s32 query asm("r2") = sp10; asm volatile("" : "+r"(query)); query; }) != 0) || (({ register s32 query asm("r3") = sp14; asm volatile("" : "+r"(query)); query; }) != 0) || ((temp_r7 != 0) && (sp18 != 0))) {
                if ((s32) arg0->unk10 > 0) {
                    var_r0 = temp_r5;
                    if (temp_r5 < 0) {
                        var_r0 = temp_r5 + 0x7FF;
                    }
                    var_r0_2 = ((var_r0 >> 0xB) << 0xB) - ({ register s32 base asm("r2") = sp0; asm volatile("" : "+r"(base)); base; });
                    asm volatile("" : "+r"(var_r0_2));
                } else {
                    s32 base;
                    var_r0_3 = temp_r5;
                    if (temp_r5 < 0) {
                        register s32 rounding asm("r3");
                        rounding = 0x7FF;
                        asm volatile("" : "+r"(rounding));
                        var_r0_3 = temp_r5 + rounding;
                    }
                    var_r0_2 = (var_r0_3 >> 0xB) << 0xB;
                    asm volatile("" : "+r"(var_r0_2));
                    {
                        register s32 fixed_base asm("r1");
                        register s32 source asm("r2");
                        register s32 offset asm("r3");
                        source = sp0;
                        offset = 0xFFFFF800;
                        asm volatile("" : "+r"(source), "+r"(offset));
                        fixed_base = source + offset;
                        asm volatile("" : "+r"(fixed_base));
                        base = fixed_base;
                    }
                    var_r0_2 -= base;
                }
                sp8 = var_r0_2;
            }
            if ((s32) arg0->unk14 <= 0) {
                if (temp_r7 != 0) {
                    if (sp10 == 0) {
                        if ((({ register s32 query asm("r1") = sp14; query; }) == 0) && (({ register s32 query asm("r2") = sp18; query; }) != 0)) {
                            temp_r0_2 = arg0->unk18;
                            if (temp_r0_2 == 2) {
                                register s32 threshold asm("r0");
                                register s32 correction asm("r3");
                                threshold = 0x3FF;
                                correction = -0xB5;
                                spC = correction;
                                if ((temp_r7 <= (u32)threshold) && ((s32) ((sp4 - 0xB5) & 0x7FF) > 0x400)) {
                                    spC = 0 - temp_r7;
                                    asm volatile("" ::: "memory");
                                }
                            } else if (temp_r0_2 == 3) {
                                s32 threshold;
                                register s32 offset asm("r1");
                                threshold = 0x3FF;
                                offset = -0x16A;
                                spC = offset;
                                if ((temp_r7 <= (u32)threshold) && ((s32) ({
                                    register s32 value asm("r0");
                                    register s32 base asm("r2");
                                    base = sp4;
                                    value = base + offset;
                                    offset = 0x7FF;
                                    value &= offset;
                                    value;
                                }) > 0x400)) {
                                    var_r3 = 0 - temp_r7;
                                    goto block_205;
                                }
                            }
                        } else {
                            goto block_192;
                        }
                    }
                } else {
block_192:
                    if ((sp10 == 0) && (({ register s32 query asm("r1") = sp14; query; }) != 0)) {
                        u8 kind;
                        u16 state;
                        kind = arg0->unk4;
                        state = arg0->unk6;
                        temp_r5 = var_sl - 2;
                        if ((func_080AB268(kind, state, temp_r1, temp_r5) << 0x10) == 0) {
                            u8 kind2;
                            u16 state2;
                            s32 delta2;
                            kind2 = arg0->unk4;
                            state2 = arg0->unk6;
                            delta2 = arg0->unk10;
                            var_r2 = temp_r1 + 1;
                            if (delta2 > 0) {
                                var_r2 -= 2;
                            }
                            if ((func_080AB268(kind2, state2, var_r2, temp_r5) << 0x10) == 0) {
                                u8 kind3;
                                u16 state3;
                                s32 delta3;
                                kind3 = arg0->unk4;
                                state3 = arg0->unk6;
                                delta3 = arg0->unk10;
                                var_r2_2 = temp_r1 + 2;
                                if (delta3 > 0) {
                                    var_r2_2 -= 4;
                                }
                                if ((func_080AB268(kind3, state3, var_r2_2, temp_r5) << 0x10) == 0) {
                                    temp_r0_3 = arg0->unk18;
                                    if (temp_r0_3 == 2) {
                                        register s32 correction asm("r2");
                                        correction = -0xB5;
                                        spC = correction;
                                    } else if (temp_r0_3 == 3) {
                                        var_r3 = -0x16A;
block_205:
                                        spC = var_r3;
                                    }
                                }
                            }
                        }
                    }
                }
                if ((s32) arg0->unk14 < 0) {
                    goto block_242;
                }
                goto block_208;
            }
block_208:
            if ((sp10 != 0) && (({ register s32 query asm("r1") = sp14; asm volatile("" : "+r"(query)); query; }) == 0) && (({ register s32 query asm("r2") = sp18; asm volatile("" : "+r"(query)); query; }) == 0)) {
                u8 kind;
                u16 state;
                s32 delta;
                register s32 call_y asm("r3");
                kind = arg0->unk4;
                state = arg0->unk6;
                delta = arg0->unk10;
                var_r2_3 = temp_r1 + 1;
                if (delta > 0) {
                    var_r2_3 -= 2;
                }
                call_y = temp_r4;
                if ((func_080AB268(kind, state, var_r2_3, call_y) << 0x10) == 0) {
                    u8 kind2;
                    u16 state2;
                    s32 delta2;
                    kind2 = arg0->unk4;
                    state2 = arg0->unk6;
                    delta2 = arg0->unk10;
                    var_r2_4 = temp_r1 + 2;
                    if (delta2 > 0) {
                        var_r2_4 -= 4;
                    }
                    if ((func_080AB268(kind2, state2, var_r2_4, temp_r4) << 0x10) == 0) {
                        temp_r0_4 = arg0->unk18;
                        if (temp_r0_4 == 2) {
                            if ((temp_r7 <= 0x400U) || ((s32) ((sp4 + 0xB5) & 0x7FF) > 0x3FF)) {
                                register s32 correction asm("r3");
                                correction = 0xB5;
                                spC = correction;
                                asm volatile("" : "+r"(correction) : : "memory");
                            } else {
                                goto block_224;
                            }
                        } else if (temp_r0_4 == 3) {
                            if ((temp_r7 > 0x400U) && ((s32) ({
                                register s32 value asm("r0");
                                register s32 base asm("r4");
                                register s32 offset asm("r1");
                                base = sp4;
                                offset = 0x16A;
                                asm volatile("" : "+r"(base), "+r"(offset));
                                value = base + offset;
                                asm volatile("" : "+r"(value));
                                offset = 0x7FF;
                                asm volatile("" : "+r"(offset));
                                value &= offset;
                                asm volatile("" : "+r"(value));
                                value;
                            }) <= 0x3FF)) {
block_224:
                                spC = 0x800 - temp_r7;
                                asm volatile("" ::: "memory");
                            } else {
                                register s32 correction asm("r2");
                                correction = 0x16A;
                                spC = correction;
                                asm volatile("" : "+r"(correction) : : "memory");
                            }
                        }
                    } else {
                        goto block_226;
                    }
                } else {
                    goto block_226;
                }
            } else {
block_226:
                if ((temp_r7 != 0) && (({ register s32 query asm("r3") = sp14; asm volatile("" : "+r"(query)); query; }) != 0) && (({ register s32 query asm("r4") = sp18; asm volatile("" : "+r"(query)); query; }) == 0)) {
                    u8 kind;
                    u16 state;
                    kind = arg0->unk4;
                    state = arg0->unk6;
                    temp_r4 = var_sl + 2;
                    if ((func_080AB268(kind, state, temp_r1, temp_r4) << 0x10) == 0) {
                        u8 kind2;
                        u16 state2;
                        s32 delta2;
                        kind2 = arg0->unk4;
                        state2 = arg0->unk6;
                        delta2 = arg0->unk10;
                        var_r2_5 = temp_r1 + 1;
                        if (delta2 > 0) {
                            var_r2_5 -= 2;
                        }
                        if ((func_080AB268(kind2, state2, var_r2_5, temp_r4) << 0x10) == 0) {
                            u8 kind3;
                            u16 state3;
                            s32 delta3;
                            kind3 = arg0->unk4;
                            state3 = arg0->unk6;
                            delta3 = arg0->unk10;
                            var_r2_6 = temp_r1 + 2;
                            if (delta3 > 0) {
                                var_r2_6 -= 4;
                            }
                            if ((func_080AB268(kind3, state3, var_r2_6, temp_r4) << 0x10) == 0) {
                                temp_r0_5 = arg0->unk18;
                                if (temp_r0_5 == 2) {
                                    spC = 0xB5;
                                    asm volatile("" ::: "memory");
                                } else if (temp_r0_5 == 3) {
                                    register s32 correction asm("r1");
                                    correction = 0x16A;
                                    asm volatile("" : "+r"(correction));
                                    spC = correction;
                                }
                            }
                        }
                    }
                }
            }
block_240:
            if (arg0->unk14 == 0) {

            } else {
block_242:
                {
                    register s32 base asm("r0");
                    register s32 delta asm("r3");
                    base = arg0->unk8;
                    asm volatile("" : "+r"(base));
                    delta = sp8;
                    asm volatile("" : "+r"(delta));
                    base += delta;
                    sp0 = base;
                }
                temp_r0_6 = arg0->unkC;
                asm volatile("" : "+r"(temp_r0_6));
                if (arg0->unk14 > 0) {
                    register s32 adjusted asm("r4");
                    adjusted = 0x800;
                    asm volatile("" : "+r"(adjusted));
                    adjusted = temp_r0_6 + adjusted;
                    sp4 = adjusted;
                    asm volatile("" ::: "memory");
                } else {
                    register s32 adjusted asm("r1");
                    adjusted = 0xFFFFF800;
                    asm volatile("" : "+r"(adjusted));
                    adjusted = temp_r0_6 + adjusted;
                    sp4 = adjusted;
                }
                {
                    register s32 base asm("r3");
                    base = sp4;
                    asm volatile("" : "+r"(base));
                    temp_r7_2 = base + arg0->unk14;
                }
                var_r1_2 = sp0;
                asm volatile("" : "+r"(var_r1_2));
                if (var_r1_2 < 0) {
                    register s32 rounding asm("r4");
                    rounding = 0x7FF;
                    asm volatile("" : "+r"(rounding));
                    var_r1_2 += rounding;
                }
                temp_r1 = var_r1_2 >> 0xB;
                var_r4_2 = temp_r7_2;
                if (temp_r7_2 < 0) {
                    register s32 rounding asm("r0");
                    rounding = 0x7FF;
                    asm volatile("" : "+r"(rounding));
                    var_r4_2 = temp_r7_2 + rounding;
                }
                {
                    s32 tile_y;
                    s32 adjustment;
                    tile_y = var_r4_2 >> 0xB;
                    adjustment = func_080AC098(arg0);
                    adjustment <<= 0x18;
                    var_sl_2 = tile_y;
                    if (adjustment == 0) {
                        register s32 one asm("r1");
                        one = 1;
                        asm volatile("" : "+r"(one));
                        var_sl_2 += one;
                    }
                }
                sp10 = (s32) func_080AB268(arg0->unk4, arg0->unk6, temp_r1 - 1, var_sl_2);
                sp14 = (s32) func_080AB268(arg0->unk4, arg0->unk6, temp_r1, var_sl_2);
                {
                    u8 kind;
                    u16 state;
                    kind = arg0->unk4;
                    state = arg0->unk6;
                    temp_r4 = temp_r1 + 1;
                    sp18 = (s32) func_080AB268(kind, state, temp_r4, var_sl_2);
                }
                {
                    register s32 mask asm("r0");
                    register s32 mask_source asm("r2");
                    mask_source = 0x7FF;
                    asm volatile("" : "+r"(mask_source));
                    mask = mask_source;
                    asm volatile("" : "+r"(mask));
                    {
                        register s32 source asm("r3");
                        source = sp0;
                        asm volatile("" : "+r"(source));
                        mode1_remainder = source;
                        asm volatile("" : "+r"(mode1_remainder));
                        mode1_initial_check = mode1_remainder;
                        asm volatile("" : "+r"(mode1_initial_check));
                        mode1_initial_check &= mask;
                        mode1_remainder = mode1_initial_check;
                        asm volatile("" : "+r"(mode1_remainder));
                    }
                }
                if ((({ register s32 query asm("r2") = sp10; asm volatile("" : "+r"(query)); query; }) != 0) || (({ register s32 query asm("r3") = sp14; asm volatile("" : "+r"(query)); query; }) != 0) || ((mode1_initial_check != 0) && (sp18 != 0))) {
                    if ((s32) arg0->unk14 > 0) {
                        var_r0_4 = temp_r7_2;
                        if (temp_r7_2 < 0) {
                            register s32 rounding asm("r1");
                            rounding = 0x7FF;
                            asm volatile("" : "+r"(rounding));
                            var_r0_4 = temp_r7_2 + rounding;
                        }
                        var_r0_5 = ((var_r0_4 >> 0xB) << 0xB) - ({ register s32 base asm("r2") = sp4; asm volatile("" : "+r"(base)); base; });
                        asm volatile("" : "+r"(var_r0_5));
                    } else {
                        s32 base;
                        var_r0_6 = temp_r7_2;
                        asm volatile("" : "+r"(var_r0_6));
                        if (temp_r7_2 < 0) {
                            register s32 rounding asm("r3");
                            rounding = 0x7FF;
                            asm volatile("" : "+r"(rounding));
                            var_r0_6 = temp_r7_2 + rounding;
                        }
                        var_r0_5 = (var_r0_6 >> 0xB) << 0xB;
                        asm volatile("" : "+r"(var_r0_5));
                        {
                            register s32 fixed_base asm("r1");
                            register s32 source asm("r2");
                            register s32 offset asm("r3");
                            source = sp4;
                            offset = 0xFFFFF800;
                            asm volatile("" : "+r"(source), "+r"(offset));
                            fixed_base = source + offset;
                            asm volatile("" : "+r"(fixed_base));
                            base = fixed_base;
                        }
                        var_r0_5 -= base;
                    }
                    spC = var_r0_5;
                }
                if ((s32) arg0->unk10 > 0) {
                    goto block_293;
                }
                {
                    register u32 remainder_check asm("r0");
                    remainder_check = mode1_remainder;
                    asm volatile("" : "+r"(remainder_check));
                if (remainder_check != 0) {
                    if (({ register s32 query asm("r1") = sp10; asm volatile("" : "+r"(query)); query; }) == 0) {
                        if ((({ register s32 query asm("r2") = sp14; asm volatile("" : "+r"(query)); query; }) == 0) && (({ register s32 query asm("r3") = sp18; asm volatile("" : "+r"(query)); query; }) != 0)) {
                            temp_r0_7 = arg0->unk18;
                            if (temp_r0_7 == 2) {
                                register s32 threshold asm("r0");
                                register s32 correction asm("r1");
                                threshold = 0x3FF;
                                asm volatile("" : "+r"(threshold));
                                correction = -0xB5;
                                asm volatile("" : "+r"(correction));
                                sp8 = correction;
                                if ((mode1_remainder <= (u32)threshold) && ((s32) ((sp0 - 0xB5) & 0x7FF) > 0x400)) {
                                    var_r2_7 = mode1_remainder;
                                    asm volatile("" : "+r"(var_r2_7));
                                    var_r2_7 = -var_r2_7;
                                    goto block_290;
                                }
                            } else if (temp_r0_7 == 3) {
                                s32 threshold;
                                register s32 offset asm("r3");
                                threshold = 0x3FF;
                                offset = -0x16A;
                                sp8 = offset;
                                if ((mode1_remainder <= (u32)threshold) && ((s32) ({
                                    register s32 value asm("r0");
                                    register s32 base asm("r1");
                                    base = sp0;
                                    value = base + offset;
                                    base = 0x7FF;
                                    value &= base;
                                    value;
                                }) > 0x400)) {
                                    var_r2_7 = mode1_remainder;
                                    asm volatile("" : "+r"(var_r2_7));
                                    var_r2_7 = -var_r2_7;
                                    goto block_290;
                                }
                            }
                        } else {
                            goto block_277;
                        }
                    }
                } else {
block_277:
                    if ((({ register s32 query asm("r3") = sp10; asm volatile("" : "+r"(query)); query; }) == 0) && (sp14 != 0)) {
                        u8 kind;
                        u16 state;
                        kind = arg0->unk4;
                        state = arg0->unk6;
                        temp_r5 = temp_r1 - 2;
                        if ((func_080AB268(kind, state, temp_r5, var_sl_2) << 0x10) == 0) {
                            u8 kind2;
                            u16 state2;
                            s32 delta2;
                            kind2 = arg0->unk4;
                            state2 = arg0->unk6;
                            delta2 = arg0->unk14;
                            var_r3_2 = var_sl_2 + 1;
                            if (delta2 > 0) {
                                var_r3_2 -= 2;
                            }
                            if ((func_080AB268(kind2, state2, temp_r5, var_r3_2) << 0x10) == 0) {
                                u8 kind3;
                                u16 state3;
                                s32 delta3;
                                kind3 = arg0->unk4;
                                state3 = arg0->unk6;
                                delta3 = arg0->unk14;
                                var_r3_3 = var_sl_2 + 2;
                                if (delta3 > 0) {
                                    var_r3_3 -= 4;
                                }
                                if ((func_080AB268(kind3, state3, temp_r5, var_r3_3) << 0x10) == 0) {
                                    temp_r0_8 = arg0->unk18;
                                    if (temp_r0_8 == 2) {
                                        register s32 correction asm("r1");
                                        correction = -0xB5;
                                        sp8 = correction;
                                        asm volatile("" : "+r"(correction) : : "memory");
                                    } else if (temp_r0_8 == 3) {
                                        var_r2_7 = -0x16A;
block_290:
                                        asm volatile("" : "+r"(var_r2_7));
                                        sp8 = var_r2_7;
                                    }
                                }
                            }
                        }
                    }
                }
                }
                if ((s32) arg0->unk10 < 0) {

                } else {
block_293:
                    if ((({ register s32 query asm("r3") = sp10; asm volatile("" : "+r"(query)); query; }) != 0) && (sp14 == 0) && (({ register s32 query asm("r1") = sp18; asm volatile("" : "+r"(query)); query; }) == 0)) {
                        u8 kind;
                        u16 state;
                        s32 delta;
                        register s32 tile_x asm("r2");
                        kind = arg0->unk4;
                        state = arg0->unk6;
                        tile_x = temp_r4;
                        delta = arg0->unk14;
                        var_r3_4 = var_sl_2 + 1;
                        if (delta > 0) {
                            var_r3_4 -= 2;
                        }
                        if ((func_080AB268(kind, state, tile_x, var_r3_4) << 0x10) == 0) {
                            u8 kind2;
                            u16 state2;
                            s32 delta2;
                            kind2 = arg0->unk4;
                            state2 = arg0->unk6;
                            delta2 = arg0->unk14;
                            var_r3_5 = var_sl_2 + 2;
                            if (delta2 > 0) {
                                var_r3_5 -= 4;
                            }
                            if ((func_080AB268(kind2, state2, temp_r4, var_r3_5) << 0x10) == 0) {
                                temp_r0_9 = arg0->unk18;
                                if (temp_r0_9 == 2) {
                                    if ((mode1_remainder <= 0x400U) || ((s32) ((sp0 + 0xB5) & 0x7FF) > 0x3FF)) {
                                        var_r3_6 = 0xB5;
                                        asm volatile("" : "+r"(var_r3_6));
                                        goto block_326;
                                    }
                                    goto block_310;
                                }
                                if (temp_r0_9 == 3) {
                                    if ((mode1_remainder > 0x400U) && ((s32) ({
                                        register s32 value asm("r0");
                                        register s32 base asm("r4");
                                        register s32 offset asm("r1");
                                        base = sp0;
                                        offset = 0x16A;
                                        asm volatile("" : "+r"(base), "+r"(offset));
                                        value = base + offset;
                                        asm volatile("" : "+r"(value));
                                        offset = 0x7FF;
                                        asm volatile("" : "+r"(offset));
                                        value &= offset;
                                        asm volatile("" : "+r"(value));
                                        value;
                                    }) <= 0x3FF)) {
block_310:
                                        {
                                            register s32 constant asm("r0");
                                            register s32 correction asm("r2");
                                            constant = 0x800;
                                            asm volatile("" : "+r"(constant));
                                            correction = mode1_remainder;
                                            asm volatile("" : "+r"(correction));
                                            correction = constant - correction;
                                            sp8 = correction;
                                        }
                                    } else {
                                        goto block_325;
                                    }
                                }
                            } else {
                                goto block_312;
                            }
                        } else {
                            goto block_312;
                        }
                    } else {
block_312:
                        if ((({ register u32 check asm("r4") = mode1_remainder; asm volatile("" : "+r"(check)); check; }) != 0) && (sp14 != 0) && (({ register s32 query asm("r1") = sp18; asm volatile("" : "+r"(query)); query; }) == 0)) {
                            u8 kind;
                            u16 state;
                            kind = arg0->unk4;
                            state = arg0->unk6;
                            temp_r4 = temp_r1 + 2;
                            if ((func_080AB268(kind, state, temp_r4, var_sl_2) << 0x10) == 0) {
                                u8 kind2;
                                u16 state2;
                                s32 delta2;
                                kind2 = arg0->unk4;
                                state2 = arg0->unk6;
                                delta2 = arg0->unk14;
                                var_r3_7 = var_sl_2 + 1;
                                if (delta2 > 0) {
                                    var_r3_7 -= 2;
                                }
                                if ((func_080AB268(kind2, state2, temp_r4, var_r3_7) << 0x10) == 0) {
                                    u8 kind3;
                                    u16 state3;
                                    s32 delta3;
                                    kind3 = arg0->unk4;
                                    state3 = arg0->unk6;
                                    delta3 = arg0->unk14;
                                    var_r3_8 = var_sl_2 + 2;
                                    if (delta3 > 0) {
                                        var_r3_8 -= 4;
                                    }
                                    if ((func_080AB268(kind3, state3, temp_r4, var_r3_8) << 0x10) == 0) {
                                        temp_r0_10 = arg0->unk18;
                                        if (temp_r0_10 != 2) {
                                            goto block_328;
                                        }
                                        {
                                            register s32 correction asm("r2");
                                            correction = 0xB5;
                                            sp8 = correction;
                                            asm volatile("" : "+r"(correction) : : "memory");
                                        }
                                        goto block_327;
block_328:
                                        if (temp_r0_10 != 3) {
                                            goto block_327;
                                        }
                                        asm volatile("" ::: "memory");
block_325:
                                        var_r3_6 = 0x16A;
                                        goto block_326;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        goto block_327;
block_326:
        sp8 = var_r3_6;
block_327:
        arg0->unk10 = ({ register s32 value asm("r4") = sp8; asm volatile("" : "+r"(value)); value; });
        arg0->unk14 = spC;
    }
}
