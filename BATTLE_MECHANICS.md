# Zoids Legacy battle mechanics

The rules below describe the retail game. Numbers are decimal unless they start with `0x`. Arithmetic is integer: division truncates toward zero unless a formula writes floor explicitly. `clamp(x, lo, hi)` forces a value into that range.

## Battle shape

A battle has two sides. Each side has 8 unit slots, of which the first 6 can be active at once. Slots 0 to 2 form the front row and slots 3 to 5 the back row. Each unit gets one turn per round and up to 3 actions per turn. Each action picks one equipment slot and one target pattern.

The round starts by rebuilding the turn order, then every active unit regenerates EP. Frozen units and units carrying a turn marker are left out of the new order. The order table holds 36 entries, enough for 12 units with extra turns.

### Initiative and turn order

Initiative is built from speed and sensor accuracy:

$$IV = SP + SR + 500 \cdot u_{15} + 1000 \cdot u_{16}$$

<!-- src
SP + SR => src/zoids/calculate_zoid_derived_stats.c:101
500 \cdot u_{15} => src/zoids/calculate_zoid_derived_stats.c:102-116
1000 \cdot u_{16} => src/zoids/calculate_zoid_derived_stats.c:117-131
-->

where $u_{15}$ and $u_{16}$ are 1 when the pilot has the Ultra Reaction 1 or Ultra Reaction 2 ability.

```c src/zoids/calculate_zoid_derived_stats.c:101-131
zoid->initiative = (u16)zoid->speed + zoid->sensor_accuracy;
if ((FindAbilityValue(abilities, PILOT_ABILITY_ULTRA_REACTION_1, 0) << 16) != 0) {
    register u32 add asm("r2");
    register u32 sum asm("r0");
    register u32 current asm("r1");

    add = 0xFA;
    add <<= 1;
    asm volatile("" : "+r"(add));
    sum = add;
    asm volatile("" : "+r"(sum));
    current = zoid->initiative;
    asm volatile("" : "+r"(current));
    sum += current;
    zoid->initiative = sum;
}
if ((FindAbilityValue(abilities, PILOT_ABILITY_ULTRA_REACTION_2, 0) << 16) != 0) {
    register u32 add asm("r2");
    register u32 sum asm("r0");
    register u32 current asm("r1");

    add = 0xFA;
    add <<= 2;
    asm volatile("" : "+r"(add));
    sum = add;
    asm volatile("" : "+r"(sum));
    current = zoid->initiative;
    asm volatile("" : "+r"(current));
    sum += current;
    zoid->initiative = sum;
}
```

The order is sorted by descending initiative. Equal initiatives go to the side chosen at the start of the round. A unit with an extra-turn effect appears $n+1$ times, where $n$ is the effect value, and each later copy has half the initiative of the previous one:

$$IV_{k+1} = \left\lfloor \frac{IV_k}{2} \right\rfloor$$

<!-- src
\left\lfloor \frac{IV_k}{2} \right\rfloor => src/battle/turn_order/insert_battle_unit_turn_order_entries.c:329-334
-->

```c src/battle/turn_order/insert_battle_unit_turn_order_entries.c:132-149,329-334
if (frame.order_mode == BATTLE_TURN_ORDER_DESCENDING_INITIATIVE) {
    register u32 entry_side asm("r3");

    entry_side = *(u8 *)(offset - (0 - (u32)entry_sides));

    if (entry_side != BATTLE_TURN_ORDER_EMPTY_ENTRY ||
        *(u8 *)(offset - (0 - (u32)entry_units_or_count)) != BATTLE_TURN_ORDER_EMPTY_ENTRY) {
        register s32 signed_priority asm("r2");
        register s32 previous_signed_priority asm("r0");

        signed_priority = priority_shifted >> 16;
        previous_signed_priority = (s16)previous_priority;
        if (signed_priority > previous_signed_priority)
            goto found;
        if (signed_priority == previous_signed_priority &&
            side_byte == battle_state[BATTLE_TURN_ORDER_OFFSET(tie_preferred_side)] && entry_side != side_byte)
            goto found;
    }
...
sign_copy = priority_shifted;
asm("" : "+r"(sign_copy));
sign = sign_copy >> 31;
signed_priority += sign;
signed_priority = (u32)signed_priority << 15;
priority = (u32)signed_priority >> 16;
```

### Opening initiative bonus

The game compares the best initiative each side can field, after adding the opening abilities:

$$M_s = \max_{i \in s} IV_i + 200 \cdot c_{12,s} + 500 \cdot c_{13,s}$$

Here $c_{12,s}$ and $c_{13,s}$ count active units on side $s$ with abilities 12 and 13. If

$$\frac{M_0}{2} \ge M_1$$

and side 1 has no unit with ability 14, every active unit on side 0 gets an initiative effect equal to its own mobility for the opening round. The same check runs in the other direction, with side 0 checked first when both qualify. The bonus lasts one round and is then counted down and removed.

<!-- src
200 \cdot c_{12,s} => src/battle/turn_order/apply_battle_opening_initiative_bonus.c:79-81
500 \cdot c_{13,s} => src/battle/turn_order/apply_battle_opening_initiative_bonus.c:82-84
\frac{M_0}{2} \ge M_1 => src/battle/turn_order/apply_battle_opening_initiative_bonus.c:94-95
-->

```c src/battle/turn_order/apply_battle_opening_initiative_bonus.c:79-129
            if ((FindAbilityValue(pilot_record, PILOT_ABILITY_OPENING_INITIATIVE_200, 0) << 16) != 0) {
                *side_initiative += 200;
            }
            if ((FindAbilityValue(pilot_record, PILOT_ABILITY_OPENING_INITIATIVE_500, 0) << 16) != 0) {
                *side_initiative += 500;
            }
            if ((FindAbilityValue(pilot_record, PILOT_ABILITY_BLOCK_OPPONENT_OPENING_BONUS, 0) << 16) != 0) {
                block_flags[side] = 1;
            }
        }
        unit_slot++;
    } while (unit_slot <= BATTLE_ACTIVE_UNIT_COUNT - 1);
    side = next_side;
} while (side <= BATTLE_SIDE_COUNT - 1);

if (opening_initiatives[0] / 2 >= opening_initiatives[1] && block_flags[1] == 0) {
    side = 0;
} else if (opening_initiatives[1] / 2 >= opening_initiatives[0] && block_flags[0] == 0) {
    side = 1;
} else {
    return;
}

{
    s32 zero;
    register u8 *battle_state asm("r8");

    unit_slot = 0;
    zero = 0;
    battle_state = gBattleState;
    asm volatile("" : "+r"(battle_state));
    do {
        if ((IsBattleUnitActive(side, unit_slot) << 24) != 0) {
            AddBattleEffect(side, unit_slot, -1, 0,
                zero, zero, BATTLE_EFFECT_INITIATIVE,
                ({
                    register u32 unit_field_address asm("r0");

                    unit_field_address = unit_slot * 0x270;
                    asm volatile("" : "+r"(unit_field_address));
                    unit_field_address += side * 0x1380;
                    asm volatile("" : "+r"(unit_field_address));
                    unit_field_address += (u32)battle_state;
                    asm volatile("" : "+r"(unit_field_address));
                    BATTLE_UNIT_FIELD(unit_field_address, s16, mobility);
                }),
                1, zero);
            RecalculateBattleUnitStats(side, unit_slot);
        }
        unit_slot++;
    } while (unit_slot <= BATTLE_ACTIVE_UNIT_COUNT - 1);
```

## The stat sheet

| Stat | Meaning | Used for |
| --- | --- | --- |
| HP | Damage capacity | Destroyed at 0 |
| EP | Energy for weapons and commands | Spent per action |
| GEP | EP restored at the start of each round | Round-start regen and Charge EP |
| SP | Speed | Initiative and evasion score |
| MM | Mobility | Evasion score and action-effect removal rolls |
| IV | Initiative, computed from SP and SR | Turn order |
| DF | Defense | Damage reduction |
| AM | Armor rating | Direct-hit conversion |
| DCP | Shutdown resistance | Freeze threshold and resistance |
| SR | Sensor accuracy | Initiative and hit-rate cushion |
| CLV | Required pilot level | Under-level stat scaling |
| TP | Training points | Garage training; not read by battle code |
| CP | Weight limit | Load penalty |
| SIZE | Size class | Hit rate, formation rules |

Limits applied after every recalculation: HP 9999, DCP 9999, EP 999, GEP 99, SP 9999, MM 999, DF 9999, AM 99, SR 9999, CP 999, IV 9999, EVS 9999.

## Building a battle stat block

The order is fixed and each step feeds the next:

1. Load the base stat table for the Zoid model.
2. Apply form bonuses.
3. Scale by Zoid level.
4. Add battle stat effects.
5. Apply the equipment weight penalty.
6. Apply pilot and Organoid percentage modifiers.
7. Apply the underwater mobility penalty.
8. Apply a sensor-accuracy override effect, if present.
9. Clamp.
10. Compute evasion score and initiative.
11. Add derived-stat effects (initiative and evasion score).
12. Clamp again, then cap current HP and EP to their maxima.

```c src/battle/recalculate_battle_unit_stats.c:68-108
LoadZoidBaseStats(unit);
ApplyBattleStatEffects(side, unit_slot);
ApplyEquipmentWeightPenalty(unit);
ApplyPilotZoidStatModifiers(unit, pilot, auxiliary_pilot);
if ((gBattleSetup[1] == 0xB) && !(0xC0 & M2C_FIELD(unit, u8 *, 0x36))) {
    temp_r1 = M2C_FIELD(unit, s16 *, 0x44);
    M2C_FIELD(unit, s16 *, 0x44) = (s16)((s32)(temp_r1 + ((u32)temp_r1 >> 31)) >> 1);
}
temp_r0 = FindBattleEffect(side, unit_slot, BATTLE_EFFECT_SENSOR_ACCURACY_OVERRIDE);
if (temp_r0 != BATTLE_EFFECT_NOT_FOUND) {
    register u32 offset asm("r1");
    register u32 work asm("r0");
    register u8 *base asm("r2");

    base = gBattleState;
    asm volatile("" : "+r"(base));
    offset = temp_r0 * 0xC;
    work = unit_slot * 0x270;
    offset += work;
    work = side * 0x1380;
    offset += work;
    offset += (u32)base;
    offset += 0xEA;
    temp_r0 = *(u16 *)offset;
    {
        register u16 *dest asm("r2");

        dest = (u16 *)((u8 *)unit + 0x4A);
        *dest = temp_r0;
    }
}
ClampZoidStats(unit);
CalculateZoidDerivedStats(unit, pilot, auxiliary_pilot);
ApplyBattleDerivedStatEffects(side, unit_slot);
ClampZoidStats(unit);
if ((s32)M2C_FIELD(unit, s16 *, 6) > (s32)(s16)M2C_FIELD(unit, u16 *, 0x3A)) {
    M2C_FIELD(unit, s16 *, 6) = (s16)M2C_FIELD(unit, u16 *, 0x3A);
}
if ((s32)M2C_FIELD(unit, s16 *, 8) > (s32)(s16)M2C_FIELD(unit, u16 *, 0x3E)) {
    M2C_FIELD(unit, s16 *, 8) = (s16)M2C_FIELD(unit, u16 *, 0x3E);
}
```

### Base stats, form, and level

The form bonus is added to EP regen and defense before level scaling:

$$GEP' = GEP_{base} + a_{form}$$

$$DF' = DF_{base} + 5 \cdot b_{form}$$

Level scales only HP, DCP, EP, GEP, SP, MM, and CP. DF, AM, and SR are not level-scaled:

$$scale = 100 + \left\lfloor \frac{L}{2} \right\rfloor$$

$$X' = \left\lfloor \frac{X \cdot scale}{100} \right\rfloor$$

<!-- src
GEP_{base} + a_{form} => src/zoids/load_zoid_base_stats.c:84
DF_{base} + 5 \cdot b_{form} => src/zoids/load_zoid_base_stats.c:86-92
100 + \left\lfloor \frac{L}{2} \right\rfloor => src/zoids/load_zoid_base_stats.c:101-105
\left\lfloor \frac{X \cdot scale}{100} \right\rfloor => src/zoids/load_zoid_base_stats.c:108-147
-->

A level 40 Zoid therefore uses a scale of 120, a 20 percent increase over its base values.

```c src/zoids/load_zoid_base_stats.c:83-149
    bonus_index = GetZoidFormIndex(zoid->zoid_id);
    *ep_regen += zoid->bonus_a[bonus_index];
    {
        register u32 bonus asm("r0") =
            zoid->bonus_b[bonus_index] * 5;
        register u32 current asm("r2") = *defense;

        asm volatile("" : "+r"(bonus));
        asm volatile("" : "+r"(current));
        *defense = bonus + current;
    }

    {
        register s32 phase1 asm("r1");
        register s32 phase2 asm("r2");

        asm volatile("" : "=r"(phase1));
        asm volatile("" : "=r"(phase2));
        scale = zoid->level;
        asm volatile("" : : "r"(phase1), "r"(phase2));
    }
    scale = (s32)(scale + ((u32)scale >> 31)) >> 1;
    scale += 100;
    asm volatile("" : "+r"(scale));

    zoid->stats[ZOID_STAT_MAX_HP] = ScaleByPercent((s16)zoid->stats[ZOID_STAT_MAX_HP], scale);
    {
        register s32 phase asm("r1");

        asm volatile("" : "=r"(phase));
        zoid->stats[ZOID_STAT_DCP] = ScaleByPercent((s16)zoid->stats[ZOID_STAT_DCP],
            ({ asm volatile("" : : "r"(phase)); scale; }));
    }
    zoid->stats[ZOID_STAT_MAX_EP] = ScaleByPercent((s16)zoid->stats[ZOID_STAT_MAX_EP], scale);
    *ep_regen = ScaleByPercent((s16)*ep_regen, scale);
    *speed = ScaleByPercent(
        ({
            register u16 *view asm("r1") = speed;

            asm volatile("" : "+r"(view));
            *(s16 *)view;
        }), scale);
    {
        register u16 result asm("r0");

        result = ScaleByPercent(
            ({
                register u16 *view asm("r2") = mobility;

                asm volatile("" : "+r"(view));
                *(s16 *)view;
            }), scale);
        {
            register u16 *view asm("r2") = mobility;

            asm volatile("" : "+r"(view));
            *view = result;
        }
    }
    {
        register s32 phase asm("r2");

        asm volatile("" : "=r"(phase));
        *load_capacity = ScaleByPercent((s16)*load_capacity,
            ({ asm volatile("" : : "r"(phase)); scale; }));
    }
}
```

### Equipment weight penalty

Let $w_i$ be the weight of the equipment in equipment slot $i$ and let $W = w_0 + w_1 + w_2 + w_3$. Equipment slots 0 through 3 are the ones counted for the Zoid's load. If $W > CP$ and $W - CP < CP$:

$$SP' = \left\lfloor \frac{SP \cdot (2CP - W)}{CP} \right\rfloor$$

$$MM' = \left\lfloor \frac{MM \cdot (2CP - W)}{CP} \right\rfloor$$

<!-- src
\left\lfloor \frac{SP \cdot (2CP - W)}{CP} \right\rfloor => src/zoids/apply_equipment_weight_penalty.c:90-101
\left\lfloor \frac{MM \cdot (2CP - W)}{CP} \right\rfloor => src/zoids/apply_equipment_weight_penalty.c:103-122
W - CP < CP => src/zoids/apply_equipment_weight_penalty.c:84-89
-->

If the overage is at least the whole limit, both speed and mobility become 0. The same factor is applied to a weapon's hit rate when the Zoid is overloaded, after the weapon's own effects are added.

```c src/zoids/apply_equipment_weight_penalty.c:81-132
if (equipment_weight > load_capacity) {
    register s32 saved_total asm("r3") = equipment_weight;
    register s32 saved_limit asm("r2") = load_capacity;
    register s32 difference asm("r0") = saved_total - saved_limit;
    asm volatile("" : "+r"(saved_total));
    asm volatile("" : "+r"(saved_limit));
    asm volatile("" : "+r"(difference));

    if (difference < saved_limit) {
        register s16 *value_ptr asm("r4") = &owner->speed;
        register s32 speed_value asm("r1");
        register s32 factor asm("r0");
        register s32 divisor asm("r1");

        speed_value = M2C_FIELD(value_ptr, s16 *, 0);
        asm volatile("" : "+r"(speed_value));
        factor = saved_limit << 1;
        factor -= saved_total;
        factor *= speed_value;
        divisor = saved_limit;
        *value_ptr = DivideSigned32(factor, divisor);

        value_ptr++;
        {
            register s32 second_value asm("r3");
            register s32 second_limit asm("r1");
            register s32 second_factor asm("r0");
            register s32 second_total asm("r2");
            register s32 hold_r0 asm("r0");
            register s32 hold_r2 asm("r2");

            asm volatile("" : "=r"(hold_r0), "=r"(hold_r2));
            second_value = M2C_FIELD(value_ptr, s16 *, 0);
            asm volatile("" : "+r"(second_value) : "r"(hold_r0), "r"(hold_r2));
            second_limit = M2C_FIELD(limit_ptr, s16 *, 0);
            asm volatile("" : "+r"(second_limit) : "r"(hold_r0));
            second_factor = second_limit << 1;
            second_total = M2C_FIELD(owner, s16 *, 0xE);
            asm volatile("" : "+r"(second_total));
            second_factor -= second_total;
            second_factor *= second_value;
            *value_ptr = DivideSigned32(second_factor, second_limit);
        }
    } else {
        register s16 *clear_ptr asm("r0") = &owner->mobility;
        register s32 clear asm("r1") = 0;
        asm volatile("" : "+r"(clear_ptr));
        asm volatile("" : "+r"(clear));
        *clear_ptr = clear;
        clear_ptr--;
        *clear_ptr = clear;
    }
```

### Pilot and Organoid modifiers

The pilot's effective level is the pilot level plus Zoid proficiency plus the Organoid level bonus:

$$L_{eff} = \min\left(99,\; L_p + p + L_{org}\right)$$

The proficiency term is +5, +10, or +20 when the pilot has the matching Zoid proficiency ability (1, 2, or 3) for that model. The pilot percentage bonuses apply to max HP, sensor accuracy, mobility, and DCP:

$$X' = X + \left\lfloor \frac{X \cdot b_X}{100} \right\rfloor$$

If the effective level is below the Zoid's required level, the same four stats are scaled again:

$$X' = \left\lfloor \frac{X \cdot L_{eff}}{CLV} \right\rfloor$$

<!-- src
\min\left(99,\; L_p + p + L_{org}\right) => src/zoids/apply_pilot_zoid_stat_modifiers.c:14-29
X + \left\lfloor \frac{X \cdot b_X}{100} \right\rfloor => src/zoids/apply_pilot_zoid_stat_modifiers.c:30-33
\left\lfloor \frac{X \cdot L_{eff}}{CLV} \right\rfloor => src/zoids/apply_pilot_zoid_stat_modifiers.c:34-38
-->

The Organoid, when active, adds its percentages to sensor accuracy, speed, and defense in the same way. A Zoid whose pilot is disabled by a `PILOT_INACTIVE` effect recalculates with no pilot at all.

```c src/zoids/apply_pilot_zoid_stat_modifiers.c:13-47
if (pilot != (void *)0) {
    effective_pilot_level = M2C_FIELD(pilot, u8 *, PLAYER_PILOT_OFFSET(level));
    if ((FindAbilityValue(pilot, PILOT_ABILITY_ZOID_PROFICIENCY_1, M2C_FIELD(zoid, u8 *, PLAYER_ZOID_OFFSET(model_id))) << 0x10) != 0) {
        effective_pilot_level += 5;
    }
    if ((FindAbilityValue(pilot, PILOT_ABILITY_ZOID_PROFICIENCY_2, M2C_FIELD(zoid, u8 *, PLAYER_ZOID_OFFSET(model_id))) << 0x10) != 0) {
        effective_pilot_level += 0xA;
    }
    if ((FindAbilityValue(pilot, PILOT_ABILITY_ZOID_PROFICIENCY_3, M2C_FIELD(zoid, u8 *, PLAYER_ZOID_OFFSET(model_id))) << 0x10) != 0) {
        effective_pilot_level += 0x14;
    }
    if (auxiliary_pilot != (void *)0) {
        effective_pilot_level += M2C_FIELD(auxiliary_pilot, u8 *, PLAYER_AUXILIARY_PILOT_OFFSET(level_bonus));
    }
    if ((u32) effective_pilot_level > PLAYER_PILOT_LEVEL_LIMIT) {
        effective_pilot_level = PLAYER_PILOT_LEVEL_LIMIT;
    }
    M2C_FIELD(zoid, s16 *, PLAYER_ZOID_OFFSET(max_hp)) = (s16) ((u16) M2C_FIELD(zoid, s16 *, PLAYER_ZOID_OFFSET(max_hp)) + ScaleByPercent(M2C_FIELD(zoid, s16 *, PLAYER_ZOID_OFFSET(max_hp)), M2C_FIELD(pilot, s16 *, PLAYER_PILOT_OFFSET(max_hp_bonus_percent))));
    M2C_FIELD(zoid, s16 *, PLAYER_ZOID_OFFSET(sensor_accuracy)) = (s16) ((u16) M2C_FIELD(zoid, s16 *, PLAYER_ZOID_OFFSET(sensor_accuracy)) + ScaleByPercent(M2C_FIELD(zoid, s16 *, PLAYER_ZOID_OFFSET(sensor_accuracy)), M2C_FIELD(pilot, s16 *, PLAYER_PILOT_OFFSET(sensor_accuracy_bonus_percent))));
    M2C_FIELD(zoid, s16 *, PLAYER_ZOID_OFFSET(mobility)) = (s16) ((u16) M2C_FIELD(zoid, s16 *, PLAYER_ZOID_OFFSET(mobility)) + ScaleByPercent(M2C_FIELD(zoid, s16 *, PLAYER_ZOID_OFFSET(mobility)), M2C_FIELD(pilot, s16 *, PLAYER_PILOT_OFFSET(mobility_bonus_percent))));
    M2C_FIELD(zoid, s16 *, PLAYER_ZOID_OFFSET(dcp)) = (s16) ((u16) M2C_FIELD(zoid, s16 *, PLAYER_ZOID_OFFSET(dcp)) + ScaleByPercent(M2C_FIELD(zoid, s16 *, PLAYER_ZOID_OFFSET(dcp)), M2C_FIELD(pilot, s16 *, PLAYER_PILOT_OFFSET(dcp_bonus_percent))));
    if ((u32) effective_pilot_level < (u32) M2C_FIELD(zoid, u8 *, PLAYER_ZOID_OFFSET(required_pilot_level))) {
        M2C_FIELD(zoid, s16 *, PLAYER_ZOID_OFFSET(max_hp)) = DivideSigned32(M2C_FIELD(zoid, s16 *, PLAYER_ZOID_OFFSET(max_hp)) * effective_pilot_level, M2C_FIELD(zoid, u8 *, PLAYER_ZOID_OFFSET(required_pilot_level)));
        M2C_FIELD(zoid, s16 *, PLAYER_ZOID_OFFSET(sensor_accuracy)) = DivideSigned32(M2C_FIELD(zoid, s16 *, PLAYER_ZOID_OFFSET(sensor_accuracy)) * effective_pilot_level, M2C_FIELD(zoid, u8 *, PLAYER_ZOID_OFFSET(required_pilot_level)));
        M2C_FIELD(zoid, s16 *, PLAYER_ZOID_OFFSET(mobility)) = DivideSigned32(M2C_FIELD(zoid, s16 *, PLAYER_ZOID_OFFSET(mobility)) * effective_pilot_level, M2C_FIELD(zoid, u8 *, PLAYER_ZOID_OFFSET(required_pilot_level)));
        M2C_FIELD(zoid, s16 *, PLAYER_ZOID_OFFSET(dcp)) = DivideSigned32(M2C_FIELD(zoid, s16 *, PLAYER_ZOID_OFFSET(dcp)) * effective_pilot_level, M2C_FIELD(zoid, u8 *, PLAYER_ZOID_OFFSET(required_pilot_level)));
    }
}
if (auxiliary_pilot != (void *)0) {
    M2C_FIELD(zoid, s16 *, PLAYER_ZOID_OFFSET(sensor_accuracy)) = (s16) ((u16) M2C_FIELD(zoid, s16 *, PLAYER_ZOID_OFFSET(sensor_accuracy)) + ScaleByPercent(M2C_FIELD(zoid, s16 *, PLAYER_ZOID_OFFSET(sensor_accuracy)), M2C_FIELD(auxiliary_pilot, s16 *, PLAYER_AUXILIARY_PILOT_OFFSET(sensor_accuracy_bonus_percent))));
    auxiliary_stat_address = (zoid + 0x4A) - 8;
    M2C_FIELD(auxiliary_stat_address, s16 *, 0) = (s16) ((u16) M2C_FIELD(auxiliary_stat_address, s16 *, 0) + ScaleByPercent(M2C_FIELD(auxiliary_stat_address, s16 *, 0), M2C_FIELD(auxiliary_pilot, s16 *, PLAYER_AUXILIARY_PILOT_OFFSET(speed_bonus_percent))));
    auxiliary_stat_address += 4;
    M2C_FIELD(auxiliary_stat_address, s16 *, 0) = (s16) ((u16) M2C_FIELD(auxiliary_stat_address, s16 *, 0) + ScaleByPercent(M2C_FIELD(auxiliary_stat_address, s16 *, 0), M2C_FIELD(auxiliary_pilot, s16 *, PLAYER_AUXILIARY_PILOT_OFFSET(defense_bonus_percent))));
}
```

### Weapon stats

A weapon record supplies attack power, hit rate, accuracy limit, EP cost, weight, attributes, range, and target pattern. Equipment slots 4 through 7 also receive a form bonus:

$$AT' = AT + 20 \cdot q_{form, slot-4}$$

```c src/zoids/load_zoid_equipment_stats.c:14-27
if (!(*(u16 *)((u8 *)output_stats + 2) & 1)) {
    if (equipment_slot > 3) {
        s32 t = ((u32)(GetZoidFormIndex(*zoid) << 0x18) >> 0x16) - 4;
        s32 off = equipment_slot + t;
        u8 *base = zoid + 0x1E;
        *(u16 *)((u8 *)output_stats + 0xA) = (u16)(base[off] * 0x14 + *(u16 *)((u8 *)output_stats + 0xA));
    }
    if ((s16)*(u16 *)((u8 *)output_stats + 0xA) > 0x270F) {
        *(u16 *)((u8 *)output_stats + 0xA) = 0x270F;
    }
    if ((s16)*(u16 *)((u8 *)output_stats + 0xC) > (s16)*(u16 *)((u8 *)output_stats + 0xE)) {
        *(u16 *)((u8 *)output_stats + 0xC) = *(u16 *)((u8 *)output_stats + 0xE);
    }
}
```

Power is capped at 9999 and hit rate is capped at the weapon's accuracy limit before other modifiers. Battle effects that add attack power or hit rate are applied next. The weapon takes the overload hit-rate factor, then the pilot modifiers. When $W > CP$:

$$HR' = \left\lfloor \frac{HR \cdot (2CP - W)}{CP} \right\rfloor$$

The pilot accuracy percent is the pilot's HR bonus plus signed ability deltas (ranged, melee, missile, laser, particle, ballistic bonuses and penalties), packed into a signed 16-bit value:

$$c = b_{HR} + \sum \delta_{ability}$$

$$HR'' = HR' + \left\lfloor \frac{HR' \cdot c}{100} \right\rfloor$$

If $L_{eff} < CLV$ the weapon hit rate is scaled by $L_{eff}/CLV$ as well. The Organoid adds its power percentage:

$$AT'' = AT' + \left\lfloor \frac{AT' \cdot b_{org,AT}}{100} \right\rfloor$$

<!-- src
AT + 20 \cdot q_{form, slot-4} => src/zoids/load_zoid_equipment_stats.c:15-20
b_{HR} + \sum \delta_{ability} => src/zoids/apply_pilot_weapon_modifiers.c:52-85
HR' + \left\lfloor \frac{HR' \cdot c}{100} \right\rfloor => src/zoids/apply_pilot_weapon_modifiers.c:86-99
AT' + \left\lfloor \frac{AT' \cdot b_{org,AT}}{100} \right\rfloor => src/zoids/apply_pilot_weapon_modifiers.c:106-119
-->

EP-saving abilities multiply the cost by 90, 70, and 50 percent in sequence. A nonzero cost that reaches 0 becomes 1. After the pilot modifiers, power is clamped to 9999 and hit rate to the accuracy limit.

```c src/zoids/apply_pilot_weapon_modifiers.c:52-152
    accuracy_bonus_percent = M2C_FIELD(pilot, u16 *, 0x3A);
#define APPLY_STAT(ID, OP) do {                                             \
        delta = FindAbilityValue(pilot, (ID), M2C_FIELD(weapon_stats, s32 *, 4));       \
        asm volatile(                                                       \
            "lsl %0, %0, #16\n"                                           \
            "asr %0, %0, #16\n"                                           \
            OP " %0, %0, %1\n"                                            \
            "lsl %0, %0, #16\n"                                           \
            "lsr %0, %0, #16"                                             \
            : "+r"(accuracy_bonus_percent)                                                   \
            : "r"(delta));                                                 \
    } while (0)
    APPLY_STAT(PILOT_ABILITY_RANGED_ACCURACY_PENALTY, "sub");
    APPLY_STAT(PILOT_ABILITY_MELEE_ACCURACY_PENALTY, "sub");
    APPLY_STAT(PILOT_ABILITY_MELEE_ACCURACY_BONUS, "add");
    APPLY_STAT(0x19, "sub");
    APPLY_STAT(0x1A, "sub");
    APPLY_STAT(PILOT_ABILITY_MISSILE_ACCURACY_PENALTY, "sub");
    APPLY_STAT(PILOT_ABILITY_LASER_ACCURACY_PENALTY, "sub");
    APPLY_STAT(PILOT_ABILITY_PARTICLE_ACCURACY_PENALTY, "sub");
    APPLY_STAT(PILOT_ABILITY_BALLISTIC_ACCURACY_PENALTY, "sub");
    APPLY_STAT(0x22, "add");
    APPLY_STAT(0x23, "add");
    APPLY_STAT(PILOT_ABILITY_MISSILE_ACCURACY_BONUS, "add");
    APPLY_STAT(PILOT_ABILITY_LASER_ACCURACY_BONUS, "add");
    APPLY_STAT(PILOT_ABILITY_PARTICLE_ACCURACY_BONUS, "add");
#undef APPLY_STAT
    delta = FindAbilityValue(pilot, PILOT_ABILITY_BALLISTIC_ACCURACY_BONUS, M2C_FIELD(weapon_stats, s32 *, 4));
    asm volatile(
        "lsl %0, %0, #16\n"
        "asr %0, %0, #16\n"
        "add %0, %0, %1"
        : "+r"(accuracy_bonus_percent)
        : "r"(delta));
    {
        register s32 result asm("r0");
        asm volatile(
            "movs r1, #12\n"
            "ldrsh r0, [r5, r1]\n"
            "lsl %1, %1, #16\n"
            "asr %1, %1, #16\n"
            "add r1, %1, #0\n"
            "bl func_080E522C"
            : "=r"(result), "+r"(accuracy_bonus_percent)
            :
            : "r1", "r2", "r3", "lr", "cc", "memory");
        M2C_FIELD(weapon_stats, s16 *, 0xC) = (u16) M2C_FIELD(weapon_stats, s16 *, 0xC) + result;
    }
    {
        u8 *required_pilot_level = &M2C_FIELD(unit, u8 *, 0x39);
        if ((u32) effective_pilot_level < (u32) *required_pilot_level) {
            M2C_FIELD(weapon_stats, s16 *, 0xC) = DivideSigned32(M2C_FIELD(weapon_stats, s16 *, 0xC) * effective_pilot_level, *required_pilot_level);
        }
    }
    if (auxiliary_pilot != 0) {
        register s32 result asm("r0");
        asm volatile(
            "movs r1, #10\n"
            "ldrsh r0, [r5, r1]\n"
            "mov r2, r9\n"
            "movs r3, #44\n"
            "ldrsh r1, [r2, r3]\n"
            "bl func_080E522C"
            : "=r"(result)
            :
            : "r1", "r2", "r3", "lr", "cc", "memory");
        M2C_FIELD(weapon_stats, s16 *, 0xA) = (u16) M2C_FIELD(weapon_stats, s16 *, 0xA) + result;
    }
    if (M2C_FIELD(weapon_stats, s16 *, 0x10) != 0) {
        if ((FindAbilityValue(pilot, PILOT_ABILITY_RANGED_EP_SAVING_1, M2C_FIELD(weapon_stats, s32 *, 4)) << 0x10) != 0) {
            M2C_FIELD(weapon_stats, s16 *, 0x10) = ScaleByPercent(M2C_FIELD(weapon_stats, s16 *, 0x10), 0x5A);
        }
        if ((FindAbilityValue(pilot, PILOT_ABILITY_RANGED_EP_SAVING_2, M2C_FIELD(weapon_stats, s32 *, 4)) << 0x10) != 0) {
            M2C_FIELD(weapon_stats, s16 *, 0x10) = ScaleByPercent(M2C_FIELD(weapon_stats, s16 *, 0x10), 0x46);
        }
        if ((FindAbilityValue(pilot, PILOT_ABILITY_RANGED_EP_SAVING_3, M2C_FIELD(weapon_stats, s32 *, 4)) << 0x10) != 0) {
            M2C_FIELD(weapon_stats, s16 *, 0x10) = ScaleByPercent(M2C_FIELD(weapon_stats, s16 *, 0x10), 0x32);
        }
        if ((FindAbilityValue(pilot, PILOT_ABILITY_MELEE_EP_SAVING_1, M2C_FIELD(weapon_stats, s32 *, 4)) << 0x10) != 0) {
            M2C_FIELD(weapon_stats, s16 *, 0x10) = ScaleByPercent(M2C_FIELD(weapon_stats, s16 *, 0x10), 0x5A);
        }
        if ((FindAbilityValue(pilot, PILOT_ABILITY_MELEE_EP_SAVING_2, M2C_FIELD(weapon_stats, s32 *, 4)) << 0x10) != 0) {
            M2C_FIELD(weapon_stats, s16 *, 0x10) = ScaleByPercent(M2C_FIELD(weapon_stats, s16 *, 0x10), 0x46);
        }
        if ((FindAbilityValue(pilot, PILOT_ABILITY_MELEE_EP_SAVING_3, M2C_FIELD(weapon_stats, s32 *, 4)) << 0x10) != 0) {
            M2C_FIELD(weapon_stats, s16 *, 0x10) = ScaleByPercent(M2C_FIELD(weapon_stats, s16 *, 0x10), 0x32);
        }
        if (M2C_FIELD(weapon_stats, s16 *, 0x10) == 0) {
            M2C_FIELD(weapon_stats, s16 *, 0x10) = 1;
        }
    }
    if ((s32) M2C_FIELD(weapon_stats, s16 *, 0xA) > 0x270F) {
        M2C_FIELD(weapon_stats, s16 *, 0xA) = 0x270F;
    }
    {
        u16 accuracy_limit = M2C_FIELD(weapon_stats, u16 *, 0xE);
        if ((s32) M2C_FIELD(weapon_stats, s16 *, 0xC) > (s32) (s16) accuracy_limit) {
            M2C_FIELD(weapon_stats, s16 *, 0xC) = accuracy_limit;
        }
    }
}
```

### Evasion score and initiative

$$EVS = \left\lfloor \frac{SP \cdot MM}{100} \right\rfloor + E_{passive}$$

The passive equipment bonus is added by items whose catalog flags end in 3, whose area type is 6, whose low effect byte is the evasion-score kind (0x0B), and which carry no weapon-type bits. Initiative is $SP + SR$ plus the Ultra Reaction values above. Both EVS and IV then receive their own battle stat effects.

```c src/zoids/calculate_zoid_derived_stats.c:35,72-93
zoid->evasion_score = ScaleByPercent(zoid->speed, zoid->mobility);
...
if ((7 & item->flags) == 3 && item->area_type == 6) {
    u32 attributes;

    attributes = item->attributes;
    if (!(BATTLE_CONDITION_WEAPON_TYPE_MASK & attributes)) {
        u32 low;

        low = EQUIPMENT_EFFECT_KIND_MASK;
        low &= attributes;
        if (low != 0x16) {
            asm volatile("" : "+r"(low));
            if (low == EQUIPMENT_EFFECT_EVASION_SCORE) {
                register u16 value asm("r0");
                register u16 current asm("r1");

                value = item->value;
                asm volatile("" : "+r"(value));
                current = zoid->evasion_score;
                asm volatile("" : "+r"(current));
                value += current;
                zoid->evasion_score = value;
            }
```

In an underwater battle, mobility is halved for units that do not carry a water-capable or flying movement flag:

$$MM' = \left\lfloor \frac{MM}{2} \right\rfloor$$

<!-- src
\left\lfloor \frac{SP \cdot MM}{100} \right\rfloor => src/zoids/calculate_zoid_derived_stats.c:35
E_{passive} => src/zoids/calculate_zoid_derived_stats.c:72-93
\left\lfloor \frac{MM}{2} \right\rfloor => src/battle/recalculate_battle_unit_stats.c:72-75
-->

## Range and rows

A weapon's range is compared against the row distance between attacker and target.

| Row distance | Hit modifier |
| --- | --- |
| 0 or 1 | 0 |
| 2 | -10 |
| 3 | -30 |

Front row to front row across sides is distance 1. Front to back or back to front is 2. Back to back is 3. On the same side, front to back is 1 and same-row is 0.

Range kinds are 0 to 1, 0 to 2, 0 to 3, exactly 2, 2 to 3, and exactly 3.

```c src/battle/get_battle_row_distance.c:5-35
u8 GetBattleRowDistance(u8 attacker_side, u8 attacker_unit_slot, u8 target_side, u8 target_unit_slot) {
    u8 row_distance;
    if (attacker_unit_slot <= 5) {
        row_distance = 0;
        if (attacker_side != target_side) {
            row_distance = 1;
            if (target_unit_slot > 2) {
                row_distance = 2;
            }
            if (attacker_unit_slot <= 2) {
                goto ret_r;
            }
            goto add_one;
        }
        if (attacker_unit_slot <= 2) {
            if (target_unit_slot > 2) {
                goto add_one;
            }
            goto ret_r;
        }
        if (target_unit_slot > 2) {
            goto ret_r;
        }
add_one:
        row_distance = row_distance + 1;
        return row_distance;
ret_r:
        return row_distance;
    }
    return 1;
}
```

## Hit rate

The hit calculation combines weapon hit rate, target size, row distance, the evasion score difference, and a set of situational modifiers:

$$A = \Delta_{size} + \Delta_{row} + \left\lfloor \frac{EVS_{att} - EVS_{tgt}}{10} \right\rfloor$$

| Size class | Modifier |
| --- | --- |
| S | -20 |
| M | 0 |
| L | +10 |
| XL | +25 |
| 4 (double icon) | +30 |

The attacker's sensor accuracy only offsets negative modifiers; the result stays at or below zero:

$$A' = \begin{cases} \min(A + SR_{att}, 0) & A < 0 \\ A & A \ge 0 \end{cases}$$

```c src/battle/calculate_battle_hit_rate.c:132-199,334,340-357
    temp_r0_3 = M2C_FIELD(sp14, u8 *, 0x38);
    switch (temp_r0_3) {                            /* switch 1 */
    case 1:                                         /* switch 1 */
        break;
    case 0:                                         /* switch 1 */
        asm volatile(
            "lsl %0, %1, #16"
            : "=r"(var_r0)
            : "r"(var_r6)
            : "cc");
        {
            register u32 case_addend asm("r2") = 0xFFEC0000;

            asm volatile(
                "add %0, %0, %1"
                : "+r"(var_r0)
                : "r"(case_addend)
                : "cc");
        }
        asm volatile("" : "+r"(var_r0));
        var_r6 = var_r0 >> 0x10;
        break;
    case 2:                                         /* switch 1 */
        asm volatile(
            "lsl %0, %1, #16\n\t"
            "mov r3, #160\n\t"
            "lsl r3, r3, #12\n\t"
            "add %0, %0, r3"
            : "=r"(var_r0)
            : "r"(var_r6)
            : "r3", "cc");
        var_r6 = var_r0 >> 0x10;
        break;
    case 3:                                         /* switch 1 */
        asm volatile(
            "lsl %0, %1, #16\n\t"
            "mov %1, #200\n\t"
            "lsl %1, %1, #13\n\t"
            "add %0, %0, %1"
            : "=r"(var_r0), "+r"(var_r6)
            :
            : "cc");
        var_r6 = var_r0 >> 0x10;
        break;
    case 4:                                         /* switch 1 */
        var_r0 = (var_r6 << 0x10) + 0x1E0000;
        var_r6 = var_r0 >> 0x10;
        break;
    }
    temp_r0_4 = (u8)GetBattleRowDistance(sp4, sp8, target_side, target_unit_slot);
    if (temp_r0_4 == 2) {
        goto block_13;
    }
    if (temp_r0_4 <= 2) {
        goto block_12;
    }
    if (temp_r0_4 == 3) {
        goto block_15;
    }
    goto block_12;
block_13:
    var_r0_2 = (var_r6 << 0x10) + 0xFFF60000;
    goto block_14;
block_15:
    var_r0_2 = (var_r6 << 0x10) + 0xFFE20000;
block_14:
    var_r6 = var_r0_2 >> 0x10;
block_12:
...
temp_r1_4 = DivideSigned32(base_value - (s16)var_r4, 0xA);
...
{
    register s32 signed_adjustment asm("r1") =
        (s16)retained_adjustment;

    signed_adjustment += temp_r1_4;
    signed_adjustment <<= 16;
    retained_adjustment = (u32)signed_adjustment >> 16;
    signed_adjustment >>= 16;
    if (signed_adjustment < 0) {
        register s32 clamp_sum asm("r0") =
            signed_adjustment + M2C_FIELD(sp10, u16 *, 0x4A);

        clamp_sum <<= 16;
        retained_adjustment = (u32)clamp_sum >> 16;
        if (clamp_sum > 0) {
            retained_adjustment = 0;
        }
    }
```

The result is then:

$$Hit = \mathrm{clamp}\left(HR + A' + \sum m, 0, 999\right)$$

The situational modifiers $m$ are:

- +20 when the attacker is flying and the target is not.
- -20 when the weapon is not anti-air, the attacker has no anti-air effect, and the target is flying.
- -20 on a water/land mismatch in either direction: a non-water weapon in a water battle, or a water-compatible weapon on land.
- +20 for a melee weapon with the melee anti-air effect against a flying target.
- minus the target pilot's melee or ranged evasion ability value, depending on the weapon type.
- minus each of the target's evasion-rate effects whose condition matches.

Evasion-score effects that match the attacker (against radar, or against homing for a homing weapon) are added to the target's EVS before the EVS term is computed. Evasion-rate effects whose condition flag is empty always apply. A half-evasion effect halves the remaining chance:

$$Hit' = Hit + \left\lfloor \frac{100 - Hit}{2} \right\rfloor$$

<!-- src
\Delta_{size} => src/battle/calculate_battle_hit_rate.c:132-180
\Delta_{row} => src/battle/calculate_battle_hit_rate.c:181-199
\left\lfloor \frac{EVS_{att} - EVS_{tgt}}{10} \right\rfloor => src/battle/calculate_battle_hit_rate.c:334
\min(A + SR_{att}, 0) => src/battle/calculate_battle_hit_rate.c:348-357
HR + A' + \sum m, 0, 999 => src/battle/calculate_battle_hit_rate.c:745-750
Hit + \left\lfloor \frac{100 - Hit}{2} \right\rfloor => src/battle/calculate_battle_hit_rate.c:645-649
-->

```c src/battle/calculate_battle_hit_rate.c:641-649
if (temp_r1_8 != 0) {
    register u32 kind_mask asm("r0") = BATTLE_EFFECT_KIND_MASK;

    kind_mask &= temp_r1_8;
    if (kind_mask == BATTLE_EFFECT_HALF_EVASION_RATE) {
        temp_r0_7 = (s16) var_r7;
        temp_r1_9 = 0x64 - temp_r0_7;
        var_r7 = temp_r0_7 + ((s32) (temp_r1_9 + (temp_r1_9 >> 0x1F)) >> 1);
    }
```

### Direct hit rate

Armor turns a hit into a direct hit. Start from the target's armor and add every armor-rate effect whose weapon-type bits match the weapon:

$$AM' = \mathrm{clamp}\left(AM + \sum e_{armor}, 0, 99\right)$$

$$DirectHit = \mathrm{clamp}\left(\left\lfloor \frac{Hit - AM'}{2} \right\rfloor, 0, 999\right)$$

<!-- src
AM + \sum e_{armor}, 0, 99 => src/battle/calculate_battle_hit_rate.c:713-731,735-740
\left\lfloor \frac{Hit - AM'}{2} \right\rfloor, 0, 999 => src/battle/calculate_battle_hit_rate.c:741-742,745-750
-->

A direct hit is resolved against this direct-hit rate. With armor 0, the direct-hit rate is half the hit rate.

```c src/battle/calculate_battle_hit_rate.c:713-731,735-742,745-750
if (kind_mask == BATTLE_EFFECT_ARMOR_RATE) {
    entry_flags = M2C_FIELD(temp_r5_5, u32 *, 0);
    high_mask = BATTLE_CONDITION_WEAPON_TYPE_MASK;
    entry_flags &= high_mask;
    low_mask = WEAPON_TYPE_MASK;
    entry_flags >>= 24;
    equipment_stats = sp18;
    weapon_attributes = equipment_stats->attributes;
    entry_flags &= weapon_attributes;
    weapon_attributes &= low_mask;
    if (entry_flags == weapon_attributes) {
        register s32 signed_sum asm("r0") = (s16)var_r4_2;
        register u32 addend asm("r5") =
            M2C_FIELD(temp_r5_5, u16 *, 6);

        signed_sum += addend;
        var_r4_2 = (u16)signed_sum;
    }
}
...
temp_r0_9 = (s16) var_r4_2;
if ((s32) temp_r0_9 < 0) {
    var_r4_2 = 0;
} else if ((s32) temp_r0_9 > 0x63) {
    var_r4_2 = 0x63;
}
temp_r0_10 = (s16) var_r7 - (s16) var_r4_2;
var_r7 = (u16) ((u32) ((temp_r0_10 + (temp_r0_10 >> 0x1F)) << 0xF) >> 0x10);
...
temp_r0_11 = (s16) var_r7;
if ((s32) temp_r0_11 < 0) {
    var_r7 = 0;
} else if ((s32) temp_r0_11 > 0x3E7) {
    var_r7 = 0x3E7;
}
```

## Resolving an action

All probability rolls use the game's random helper, which returns an integer from 0 to 32767.

```arm 0x080005AC-0x080005D4
80005ac:  e59f3020   ldr  r3, [pc, #32]  @ 0x80005d4
80005b0:  e5931000   ldr  r1, [r3]
80005b4:  e59f201c   ldr  r2, [pc, #28]  @ 0x80005d8
80005b8:  e0000291   mul  r0, r1, r2
80005bc:  e59f1018   ldr  r1, [pc, #24]  @ 0x80005dc
80005c0:  e0800001   add  r0, r0, r1
80005c4:  e5830000   str  r0, [r3]
80005c8:  e1a00820   lsr  r0, r0, #16
80005cc:  e3c00902   bic  r0, r0, #32768  @ 0x8000
80005d0:  e12fff1e   bx  lr
```

1. Hit roll: $roll_h = \lfloor rand \cdot 200 / 2^{16} \rfloor$, giving 0 to 99. The attack misses when $roll_h = 0$ or $roll_h > Hit$.
2. Shield check: if the target has an energy shield effect (kind 21) on the auxiliary pilot, has more than 1 EP, and $(rand \gg 14) = 0$ (one chance in two), the outcome is `SHIELD` instead of damage.
3. Direct check: with the hit roll values from above, the attack is a direct hit when $2 \cdot roll_h \le DirectHit$; otherwise it is a normal hit.
4. Freeze check: a surviving hit whose damage is at least the target's DCP rolls shutdown resistance.

<!-- src
\lfloor rand \cdot 200 / 2^{16} \rfloor => src/battle/roll_battle_action_outcomes.c:244-247
roll_h = 0 => src/battle/roll_battle_action_outcomes.c:248-250
roll_h > Hit => src/battle/roll_battle_action_outcomes.c:251-263
(rand \gg 14) = 0 => src/battle/roll_battle_action_outcomes.c:264-284
2 \cdot roll_h \le DirectHit => src/battle/roll_battle_action_outcomes.c:319-328
-->

```c src/battle/roll_battle_action_outcomes.c:244-284,319-328,527
temp_r0 = CallFunctionR0(*(s32 *)0x03000010) * 0x64;
temp_r0 *= 2;
temp_r6 = (u8 *) (temp_r0 >> 0x10);
temp_r1 = (s32) temp_r0 >> 0x10;
if (temp_r1 == 0) {
    goto block_set1;
}
if (temp_r1 > (s32) ({
        register u8 *entry_r2 asm("r2") = temp_r2;
        register u32 offset_r3 asm("r3");
        register s32 value_r0 asm("r0");
        asm volatile(
            "mov %1, #2\n\t"
            "ldrsh %0, [%2, %1]"
            : "=r"(value_r0), "=r"(offset_r3)
            : "r"(entry_r2));
        value_r0;
    })) {
    goto block_set1;
}
if (((FindActiveBattleAuxiliaryPilotEffectValue(target_side, target_unit_slot, 0x15) << 0x10) != 0) &&
    ((s32) ({
        register u32 index_r1 asm("r1") = target_unit_slot;
        register u32 address_r0 asm("r0");
        register u32 row_r2 asm("r2");
        register u8 *base_r3 asm("r3");

        address_r0 = index_r1 << 2;
        address_r0 += target_unit_slot;
        address_r0 <<= 3;
        address_r0 -= index_r1;
        address_r0 <<= 4;
        row_r2 = sp8;
        address_r0 += row_r2;
        base_r3 = gBattleState;
        address_r0 += (u32)base_r3;
        index_r1 = 8;
        *(s16 *)(address_r0 + index_r1);
    }) > 1) && ((CallFunctionR0(*(s32 *)0x03000010) >> 0xE) == 0)) {
    goto block_set2;
}
...
compare_r1 = (u32)temp_r6 << 16;
compare_r1 >>= 15;
temp_r6 = (u8 *)temp_r2;
asm volatile(
    "mov %1, #6\n\t"
    "ldrsh %0, [%2, %1]"
    : "=r"(entry_value_r0), "=r"(offset_r3)
    : "r"(temp_r6));
if (compare_r1 > entry_value_r0) {
    *temp_r4 = BATTLE_OUTCOME_HIT;
...
*temp_r4 |= ((u32) (CallFunctionR0(*(s32 *)0x03000010) * 3) >> 0xF) * 8;
```

The game shows four preview values before the roll: normal hit rate, normal damage, direct-hit rate against armor, and direct-hit damage with defense skipped. Every outcome also gets a random variant of 0, 8, or 16 in bits 0x38.

### Damage

Base power is the weapon's attack power after all modifiers. Two situational changes apply before defense. A melee weapon with the melee anti-air effect, against a flying target:

$$P' = P + 20$$

A non-water weapon in a water battle:

$$P' = \left\lfloor \frac{P}{2} \right\rfloor$$

Defense is skipped entirely for a direct hit and for a weapon with the ignore-defense attribute. Otherwise defense starts from the target's DF and adds every defense effect whose weapon-type condition matches:

$$DF' = \mathrm{clamp}\left(DF + \sum e_{defense} + e_{scenario}, 0, 9999\right)$$

The scenario term comes from a scripted battle table and is added even on direct hits and ignore-defense hits; ordinary defense effects are not. Damage is then:

$$D = \mathrm{clamp}\left(P' - DF', 1, 9999\right)$$

<!-- src
P + 20 => src/battle/calculate_battle_damage.c:66-70
\left\lfloor \frac{P}{2} \right\rfloor => src/battle/calculate_battle_damage.c:83-92
DF + \sum e_{defense} => src/battle/calculate_battle_damage.c:96-107
e_{scenario} => src/battle/calculate_battle_damage.c:193-224
P' - DF', 1, 9999 => src/battle/calculate_battle_damage.c:236-267
-->

The applied damage is the preview value that matches the outcome kind.

```c src/battle/calculate_battle_damage.c:66-107,193-267
if (FindBattleEffect(attacker_side, attacker_unit_slot, BATTLE_EFFECT_MELEE_ANTI_AIR_BONUS) != 0xFF &&
    (equipment_stats->attributes & WEAPON_MELEE) != 0 &&
    (target_unit[0x36] & ZOID_MOVEMENT_FLYING) != 0) {
    equipment_stats->power_or_value += 20;
}

{
    register u32 attack_power asm("r3") = equipment_stats->power_or_value;
    register u32 loaded_flags asm("r1");

    damage = attack_power;
    loaded_flags = equipment_stats->attributes;
    {
        register u32 flag_test asm("r0") = WEAPON_WATER_COMPATIBLE;

        flag_test &= loaded_flags;
        weapon_attributes = loaded_flags;
        if (flag_test == 0 && gBattleSetup[1] == 11) {
        register u32 shifted asm("r0") = attack_power << 16;
        register s32 half asm("r1") = (s32)shifted >> 16;

        shifted >>= 31;
        half += shifted;
        half <<= 15;
        half = (u32)half >> 16;
        damage = half;
        }
    }
}

defense_total = 0;
if ((weapon_attributes & WEAPON_IGNORE_DEFENSE) == 0) {
    register u32 direct_hit_check asm("r4") = direct_hit;

    if (direct_hit_check == 0) {
        register u32 row_offset asm("ip");
        register u32 mask asm("r7");
        register u32 flags_view asm("r6");
        register u32 expected asm("r4");
        register u32 index asm("r3");

        defense_total = *(u16 *)(target_unit + 0x46);
...
{
    register u8 *base asm("r1") = gBattleState;
    register u32 offset asm("r2") = 0x27BE;
    register u8 *kind_flags asm("r0");

    kind_flags = base + offset;
    kind_flags += target_side;
    if (*kind_flags == 49) {
        register u32 stride asm("r0") = 148;
        register u32 entry_offset asm("r1") = target_side;
        register u8 *entry asm("r1");

        entry_offset *= stride;
        {
            register u8 *table_base asm("r3") = gBattleState;
            register u32 table_offset asm("r4") = 0xA084;
            register u8 *table asm("r0");

            table = table_base + table_offset;
            entry = entry_offset + (u32)table;
        }
        {
            register u32 sum asm("r0") = defense_total << 16;
            register u32 addend asm("r1");

            sum = (s32)sum >> 16;
            addend = *(u16 *)entry;
            sum += addend;
            defense_total = (u16)sum;
        }
    }
}

{
    s16 signed_accumulator = defense_total;

    if (signed_accumulator < 0) {
        defense_total = 0;
    } else if (signed_accumulator > 9999) {
        defense_total = 9999;
    }
}

{
    register s32 difference asm("r1");
    register s32 signed_result asm("r0");

    {
        register u32 result_view asm("r0") = damage;

        difference = result_view << 16;
        difference >>= 16;
    }
    {
        register s32 subtrahend asm("r0") = defense_total << 16;

        subtrahend >>= 16;
        difference -= subtrahend;
    }
    difference <<= 16;
    {
        register u32 normalized asm("r2") = (u32)difference >> 16;

        damage = normalized;
    }
    signed_result = difference >> 16;
    if (signed_result <= 0) {
        register u32 one asm("r3") = 1;

        asm volatile("" : "+r"(one));
        damage = one;
    } else if (signed_result > 9999) {
        damage = 9999;
    }
}
```

### Applying the result

- Damage greater than or equal to current HP destroys the unit. Scripted battles keep a few story pilots at 1 HP; for example, setup 8 does this for pilot IDs 0x1E, 0x5F, and 0x3B.
- Otherwise HP is reduced by the damage. If the damage is at least DCP and the unit did not resist, the unit gets a `FREEZE` effect and is removed from the turn order.
- A landing hit whose target holds an energy shield is absorbed unless the weapon has the penetrate attribute. The shield value is compared against the direct-hit damage preview, even on a normal hit. If the shield is larger it drops by that amount; otherwise the shield effect is removed. The hit never reaches HP.
- A `SHIELD` outcome costs the target 2 EP and adds effect kind 35 (0x23).
- After the hit, equipment effects and the stat recalculation run.

```c src/battle/apply_battle_target_outcome.c:290-337,643-692,963-985
block_13:
    {
        register u32 work_r0 asm("r0") = var_r0;
        register u32 work_r1 asm("r1");
        register u32 current_r4 asm("r4");
        register u8 *store_r3 asm("r3");

        work_r1 = (u32)frame.target_unit;
        current_r4 = *(u16 *)(work_r1 + 6);
        work_r1 = (s32)*(s16 *)(work_r1 + 6);
        work_r0 <<= 16;
        temp_r2_2 = (s32)work_r0 >> 16;
        frame.sp30 = work_r0;
        if ((s32)work_r1 <= temp_r2_2) {
            goto block_21;
        }
        work_r0 = current_r4 - temp_r2_2;
        store_r3 = frame.target_unit;
        *(u16 *)(store_r3 + 6) = work_r0;
        current_r4 = 0x3C;
        asm volatile(
            "ldrsh %0, [%1, %2]"
            : "=r"(work_r0)
            : "r"(store_r3), "r"(current_r4));
        if (temp_r2_2 >= (s32)work_r0) {
            goto block_16;
        }
    }
    goto block_38;
block_16:
    {
        register u32 mask_r0 asm("r0") = BATTLE_OUTCOME_FREEZE_RESISTED;
        register u32 flags_r1 asm("r1") = frame.outcome_flags;

        mask_r0 &= flags_r1;
        temp_r1_4 = mask_r0;
    }
    if (temp_r1_4 == 0) {
        goto block_18;
    }
    goto block_38;
block_18:
    if ((AddBattleEffect(target_side_index, target_slot_index, -1, 0x18, (s32) temp_r1_4, (s32) temp_r1_4, 0x19, (s32) temp_r1_4, (s32) temp_r1_4, (s32) temp_r1_4) << 0x18) != 0) {
        goto block_20;
    }
    goto block_38;
block_20:
    RemoveBattleUnitFromTurnOrder(target_side_index, target_slot_index);
...
block_47:
    {
        register u32 work_r0 asm("r0");
        register u32 work_r1 asm("r1");
        register u32 work_r2 asm("r2");
        register u32 amount_r3 asm("r3");
        register u32 record_r7 asm("r7");
        register u32 record_r8 asm("r8");

        work_r1 = temp_r2 << 1;
        work_r1 += temp_r2;
        work_r1 <<= 2;
        work_r0 = target_slot_index << 2;
        work_r0 += target_slot_index;
        work_r0 <<= 3;
        work_r0 -= target_slot_index;
        work_r0 <<= 4;
        work_r1 += work_r0;
        work_r0 = target_side_index << 2;
        work_r0 += target_side_index;
        work_r0 <<= 3;
        work_r0 -= target_side_index;
        work_r0 <<= 7;
        work_r1 += work_r0;
        temp_r4 = (s32)gBattleState;
        work_r1 += temp_r4;
        work_r1 += 0xEA;
        record_r7 = *(u16 *)work_r1;
        record_r8 = record_r7;
        asm volatile(
            "mov %1, #0\n\t"
            "ldrsh %0, [%2, %1]"
            : "=r"(work_r0), "=r"(amount_r3)
            : "r"(work_r1));
        temp_r4 = (s32)frame.target_preview;
        record_r7 = 8;
        asm volatile(
            "ldrsh %0, [%1, %2]"
            : "=r"(amount_r3)
            : "r"(temp_r4), "r"(record_r7));
        if ((s32)work_r0 <= (s32)amount_r3) {
            goto block_50;
        }
        work_r2 = record_r8;
        work_r0 = work_r2 - amount_r3;
        *(u16 *)work_r1 = work_r0;
    }
    goto block_51;
block_50:
    RemoveBattleEffect(target_side_index, target_slot_index);
...
if (work_r2 != 2) {
    goto block_77;
}
work_r1 = target_slot_index << 2;
work_r1 += target_slot_index;
work_r1 <<= 3;
work_r1 -= target_slot_index;
work_r1 <<= 4;
work_r0 = target_side_index << 2;
work_r0 += target_side_index;
work_r0 <<= 3;
work_r0 -= target_side_index;
work_r0 <<= 7;
work_r1 += work_r0;
work_r1 += base_r3;
work_r0 = *(u16 *)(work_r1 + 8);
work_r0 -= 2;
base_r3 = 0;
asm volatile("" : "+r"(base_r3));
*(u16 *)(work_r1 + 8) = work_r0;
AddBattleEffect(target_side_index, target_slot_index, -1, (s32)base_r3,
              (s32)base_r3, (s32)base_r3, 0x23, (s32)base_r3,
              (s32)base_r3, (s32)base_r3);
```

The freeze, confusion, pilot-inactive, and defense-damage bits apply their status when the weapon hits. Defense damage adds a negative defense effect equal to one tenth of the weapon's power.

## Shutdown and DCP

DCP is the damage threshold for shutdown. The resistance value starts from how far the hit was below DCP:

$$R_0 = (DCP - D) + 3\left\lfloor \sqrt{b_{DCP}} \right\rfloor + 30 z_+ - 30 z_-$$

$b_{DCP}$ is the pilot's DCP bonus percent, square-rooted with the BIOS integer square root. $z_+$ is the status-resistance bonus ability (21) and $z_-$ the status-resistance penalty ability (22). The value is held in 16 bits.

If the unit's internal flag word has bit 0x40 set and $0 \le R_0 \le 95$, the resistance is boosted:

$$R_1 = R_0 + \left\lfloor \frac{3(100 - R_0)}{4} \right\rfloor$$

The final resistance is clamped to 99:

$$R = \min(R_1, 99)$$

A resistance roll $roll_s = \lfloor rand \cdot 100 / 2^{15} \rfloor$ from 0 to 99 is compared against $R$. The unit resists when $roll_s \le R$. So for $R \le 98$:

$$P(\text{shutdown}) \approx \frac{99 - R}{100}$$

and at $R = 99$ the unit always resists.

```c src/battle/roll_battle_status_resistance.c:10-55
s32 RollBattleStatusResistance(u8 side, u8 unit_slot, u16 base_chance) {
    s32 unit_offset;
    s32 side_offset;
    s32 side_stride_units;
    s32 unit_stride_units;
    s32 flag_boost;
    u16 resistance_chance;
    void *pilot_record;
    register s32 battle_state_address asm("r8");

    side_stride_units = side * 0x27;
    side_offset = side_stride_units << 7;
    unit_stride_units = unit_slot * 0x27;
    unit_offset = unit_stride_units << 4;
    battle_state_address = 0x02034B4C;
    pilot_record = side_offset + (unit_offset + battle_state_address) + 0x70;
    {
        s32 signed_base_chance;
        s32 pilot_dcp_bonus;

        pilot_dcp_bonus = BiosSqrt(M2C_FIELD(pilot_record, s16 *, PLAYER_PILOT_OFFSET(dcp_bonus_percent))) * 3;
        signed_base_chance = (s16)base_chance;
        resistance_chance = signed_base_chance + pilot_dcp_bonus;
    }
    if ((FindAbilityValue(pilot_record, PILOT_ABILITY_STATUS_RESISTANCE_BONUS, 0) << 0x10) != 0) {
        resistance_chance += 0x1E;
    }
    if ((FindAbilityValue(pilot_record, PILOT_ABILITY_STATUS_RESISTANCE_PENALTY, 0) << 0x10) != 0) {
        resistance_chance -= 0x1E;
    }
    if (((u32) resistance_chance <= 0x5FU) && (0x40 & BATTLE_UNIT_FIELD((unit_offset + side_offset + battle_state_address), u16, flags))) {
        flag_boost = (0x64 - resistance_chance) * 3;
        if (flag_boost < 0) {
            flag_boost += 3;
        }
        resistance_chance += flag_boost >> 2;
    }
    if ((u32) resistance_chance > 0x63U) {
        resistance_chance = 0x63;
    }
    if ((s32) ((u32) (CallFunctionR0(*(s32 *)0x03000010) * 0x64) >> 0xF) <= (s32) resistance_chance) {
        return 1;
    }
    return 0;
}
```

The ROM compares the 16-bit resistance value as unsigned. If $DCP - D$ is negative, the subtraction wraps to a large 16-bit value, the boost test fails, the clamp sets 99, and the unit is immune. The same happens when the ability penalties pull a positive value below zero after the square-root bonus. A hit has a shutdown chance only while the damage stays within the pilot's compensation window. Hitting much harder than DCP makes shutdown impossible. A unit with $R_0$ of 96, 97, or 98 has a 3, 2, or 1 percent chance, and $R = 99$ always resists.

<!-- src
(DCP - D) => src/battle/roll_battle_status_resistance.c:31-32
3\left\lfloor \sqrt{b_{DCP}} \right\rfloor => src/battle/roll_battle_status_resistance.c:30
30 z_+ => src/battle/roll_battle_status_resistance.c:34-36
30 z_- => src/battle/roll_battle_status_resistance.c:37-39
0 \le R_0 \le 95 => rom:0x080BE506-0x080BE508
R_0 + \left\lfloor \frac{3(100 - R_0)}{4} \right\rfloor => src/battle/roll_battle_status_resistance.c:40-46
\min(R_1, 99) => src/battle/roll_battle_status_resistance.c:47-49
\lfloor rand \cdot 100 / 2^{15} \rfloor => src/battle/roll_battle_status_resistance.c:50
-->

```thumb 0x080BE506-0x080BE54A,0x080BE554-0x080BE560
80be506:  2c5f        cmp  r4, #95  @ 0x5f
80be508:  d811        bhi.n  0x80be52e
80be50a:  19f0        adds  r0, r6, r7
80be50c:  4440        add  r0, r8
80be50e:  8881        ldrh  r1, [r0, #4]
80be510:  2040        movs  r0, #64  @ 0x40
80be512:  4008        ands  r0, r1
80be514:  2800        cmp  r0, #0
80be516:  d00a        beq.n  0x80be52e
80be518:  2064        movs  r0, #100  @ 0x64
80be51a:  1b00        subs  r0, r0, r4
80be51c:  0041        lsls  r1, r0, #1
80be51e:  1808        adds  r0, r1, r0
80be520:  2800        cmp  r0, #0
80be522:  da00        bge.n  0x80be526
80be524:  3003        adds  r0, #3
80be526:  1080        asrs  r0, r0, #2
80be528:  1820        adds  r0, r4, r0
80be52a:  0400        lsls  r0, r0, #16
80be52c:  0c04        lsrs  r4, r0, #16
80be52e:  2c63        cmp  r4, #99  @ 0x63
80be530:  d900        bls.n  0x80be534
80be532:  2463        movs  r4, #99  @ 0x63
80be534:  4806        ldr  r0, [pc, #24]
80be536:  6800        ldr  r0, [r0, #0]
80be538:  f02e fc10   bl  0x80ecd5c
80be53c:  2164        movs  r1, #100  @ 0x64
80be53e:  4348        muls  r0, r1
80be540:  0bc0        lsrs  r0, r0, #15
80be542:  42a0        cmp  r0, r4
80be544:  dd06        ble.n  0x80be554
80be546:  2000        movs  r0, #0
80be548:  e005        b.n  0x80be556
...
80be554:  2001        movs  r0, #1
80be556:  bc08        pop  {r3}
80be558:  4698        mov  r8, r3
80be55a:  bcf0        pop  {r4, r5, r6, r7}
80be55c:  bc02        pop  {r1}
80be55e:  4708        bx  r1
```

The freeze threshold check and the resistance roll both use the damage that is actually applied.

## EP economy

Round start:

$$EP' = \min(EP + GEP, EP_{max})$$

```c src/game/modes/run_battle.c:1385-1402
offset = inner * 0x270;
offset += outer_offset;
base_view = base;
record = (u8 *)(offset + (u32)base_view);
sum = (u32)record;
sum += 0x40;
sum = *(u16 *)sum;
current_value = *(u16 *)(record + 8);
sum += current_value;
*(u16 *)(record + 8) = (u16)sum;
sum = (s32)(s16)sum;
raw_limit = *(u16 *)(record + 0x3E);
limit_offset = 0x3E;
signed_limit = (s32)*(s16 *)(record + limit_offset);
if ((s32)sum <= (s32)signed_limit) {
    goto block_205;
}
*(u16 *)(record + 8) = (u16)raw_limit;
```

This runs for every active unit, including frozen ones. Charge EP is a separate action. It adds

$$\Delta EP = \min(GEP, EP_{max} - EP)$$

<!-- src
\min(EP + GEP, EP_{max}) => src/game/modes/run_battle.c:1385-1402
\min(GEP, EP_{max} - EP) => src/game/modes/run_battle.c:3816-3823
-->

and puts a turn marker on the unit. The marker keeps the unit out of any turn order rebuilt later in the round.

```c src/game/modes/run_battle.c:3815-3828,3834-3841
    AddBattleEffect(gBattleState[0x27A4], gBattleState[0x27A5], -1, 0, 0, 0, 0x1A, 0, 1, 0);
    temp_r5_7 = *(void **)&gBattleState[0x27A8];
    if ((s32) (M2C_FIELD(temp_r5_7, s16 *, 8) + M2C_FIELD(temp_r5_7, s16 *, 0x40)) > (s32) M2C_FIELD(temp_r5_7, s16 *, 0x3E)) {
        goto block_507;
    }
    var_r0_9 = (u16) M2C_FIELD(temp_r5_7, s16 *, 0x40);
    goto block_508;
block_507:
    var_r0_9 = (u16) M2C_FIELD(temp_r5_7, s16 *, 0x3E) - (u16) M2C_FIELD(temp_r5_7, s16 *, 8);
block_508:
    temp_r5_8 = (s16) var_r0_9;
    if (temp_r5_8 == 0) {
        goto block_510;
    }
...
register u32 record_offset asm("r2") = 0x27A8;
register u8 *record_address asm("r0") = base + record_offset;
register u8 *record asm("r2") = *(u8 **)record_address;
register u32 current asm("r0") = *(u16 *)(record + 8);

current = temp_r5_8 + current;
zero = 0;
*(u16 *)(record + 8) = current;
```

Each weapon action pays its EP cost. EP-saving abilities reduce it.

## Effects

A unit has 32 effect slots. Each slot holds condition flags, kind and lifetime bits, a value, and a lifetime or cost field. Kinds 21 through 28 and the shield-block marker (kind 35) are singletons: a unit cannot hold two of the same kind. Adding an effect fails when the slots are full or the singleton already exists.

Effect kinds used by the engine:

| Kind | Effect |
| --- | --- |
| 1 | HP recovery |
| 2 | Max HP |
| 3 | DCP |
| 4 | EP recovery |
| 5 | Max EP |
| 6 | EP regen |
| 7 | Speed |
| 8 | Mobility |
| 9 | Defense |
| 10 | Armor rate |
| 11 | Sensor accuracy |
| 12 | Load capacity |
| 13 | Initiative |
| 14 | Evasion score |
| 15 | Attack power |
| 16 | Hit rate |
| 17 | Evasion rate |
| 18 | Double attack power |
| 19 | Half evasion rate |
| 20 | Sensor accuracy override |
| 21 | Energy shield |
| 22 | Anti-air |
| 23 | Auxiliary pilot active |
| 24 | Pilot inactive |
| 25 | Freeze |
| 26 | Turn marker |
| 27 | Confusion |
| 28 | Extra turns |
| 29 | Double melee power |
| 30 | Melee anti-air bonus |
| 31 | Melee defense damage chance |
| 32 | Ignore melee defense |
| 35 | Shield-block marker (0x23) |

Kinds 2 through 12 are flat additions applied during the recalculation, before the derived stats are computed. HP and EP recovery add to the current values at the turn update, then the block is reclamped. Initiative and evasion-score effects are applied after the derived stats are computed, then the block is clamped again.

The lifetime bits select when an effect goes away:

| Bits | Lifetime |
| --- | --- |
| 0x0000 | Counted down at the end of each round |
| 0x2000 | Removed by an action-lived removal roll |
| 0x4000 | Charges an EP cost each turn |
| 0x6000 | Removed by the round resistance mask |
| 0x8000 | Removed when the attack ends |
| 0xA000 | Charges an EP cost each round |

```c src/battle/add_battle_effect.c:68,223-324
if ((((u32) (u16) (temp_r7 - 0x15) <= 7U) || (temp_r7 == 0x23)) && (FindBattleEffect(hold0, sp18, temp_r7) != 0xFF)) {
...
block_23:
    temp_r0_2 = 0x38 & sp20;
    switch (temp_r0_2) {                            /* irregular */
    case 0:
        M2C_FIELD(var_r4, u16 *, 4) = temp_r7;
        M2C_FIELD(var_r4, u16 *, 6) = var_r6;
        if (2 & sp20) {
            var_r0 = 0;
        } else {
            M2C_FIELD(var_r4, u16 *, 8) = (u16) sp28;
            goto block_39;
        }
        goto block_38;
    case 8:
        M2C_FIELD(var_r4, u16 *, 4) = (u16) (temp_r7 | 0x2000);
        M2C_FIELD(var_r4, u16 *, 6) = var_r6;
        M2C_FIELD(var_r4, u16 *, 8) = (u16) sp28;
        goto block_39;
    case 16:
        M2C_FIELD(var_r4, u16 *, 4) = (u16) (temp_r7 | 0x4000);
        M2C_FIELD(var_r4, u16 *, 6) = var_r6;
        M2C_FIELD(var_r4, u16 *, 8) = (u16) sp2C;
        goto block_39;
    case 24: {
        register u32 case24_bits asm("r3");
        register s32 case24_addr asm("r0") = sp34 + (hold0 * 0x18);
        register s32 case24_offset asm("r1");
        asm volatile("" : "+r"(case24_addr));
        case24_offset = 0xA1DC;
        asm volatile("" : "+r"(case24_offset));
        case24_offset += (s32)base_tail;
        asm volatile("" : "+r"(case24_offset));
        case24_addr += case24_offset;
        asm volatile("" : "+r"(case24_addr));
        case24_bits = M2C_FIELD(case24_addr, s32 *, 0) & (1 << var_r5);
        asm volatile("" : "+r"(case24_bits));
        if (case24_bits != 0) {
            goto block_36;
        }
        M2C_FIELD(var_r4, u16 *, 4) = (u16) (temp_r7 | 0x6000);
        M2C_FIELD(var_r4, u16 *, 6) = var_r6;
        M2C_FIELD(var_r4, u16 *, 8) = case24_bits;
        goto block_39;
    }
    case 32: {
        register u32 case32_copy asm("r0");
        {
            register u32 case32_mask asm("r1") = 0x8000;
            asm volatile("" : "+r"(case32_mask));
            case32_copy = case32_mask;
            asm volatile("" : "+r"(case32_copy));
        }
        {
            register u32 case32_zero asm("r2") = 0;
            register u32 case32_result asm("r1") = temp_r7;
            asm volatile("" : "+r"(case32_zero));
            asm volatile("" : "+r"(case32_result));
            case32_result |= case32_copy;
            M2C_FIELD(var_r4, u16 *, 4) = (u16)case32_result;
            M2C_FIELD(var_r4, u16 *, 6) = var_r6;
            M2C_FIELD(var_r4, u16 *, 8) = case32_zero;
        }
        goto block_39;
    }
block_36:
        return 0;
    case 40: {
        {
            register u32 case40_mask asm("r2") = 0xA000;
            register u32 case40_copy asm("r0");
            register u32 case40_result asm("r1");
            asm volatile("" : "+r"(case40_mask));
            case40_copy = case40_mask;
            asm volatile("" : "+r"(case40_copy));
            case40_result = temp_r7;
            asm volatile("" : "+r"(case40_result));
            case40_result |= case40_copy;
            M2C_FIELD(var_r4, u16 *, 4) = (u16)case40_result;
            M2C_FIELD(var_r4, u16 *, 6) = var_r6;
        }
        {
            register s32 case40_input asm("r3") = sp2C;
            register s32 case40_signed asm("r0");
            asm volatile("" : "+r"(case40_input));
            case40_signed = (s16)case40_input;
            asm volatile("" : "+r"(case40_signed));
            case40_signed = -case40_signed;
            var_r0 = case40_signed;
        }
    }
block_38:
        M2C_FIELD(var_r4, u16 *, 8) = var_r0;
        goto block_39;
    default:
block_39:
        temp_r2_4 = (s8) sp1C;
        temp_r1_3 = ((0xF & temp_r2_4) << 8) | M2C_FIELD(var_r4, u16 *, 4);
        M2C_FIELD(var_r4, u16 *, 4) = temp_r1_3;
        if (sp24 != 0) {
            M2C_FIELD(var_r4, u16 *, 4) = (u16) (temp_r1_3 | 0x80);
        }
        M2C_FIELD(var_r4, s32 *, 0) = condition_flags;
```

For action-lived effects, at the end of an action the game rolls

$$roll_r = \left\lfloor \frac{rand \cdot 100}{2^{15}} \right\rfloor$$

and removes the effect when

$$roll_r > \left\lfloor \frac{lifetime \cdot (100 + b_{MM})}{100} \right\rfloor$$

<!-- src
\left\lfloor \frac{rand \cdot 100}{2^{15}} \right\rfloor => src/battle/roll_battle_effect_removal_masks.c:110
\left\lfloor \frac{lifetime \cdot (100 + b_{MM})}{100} \right\rfloor => src/battle/roll_battle_effect_removal_masks.c:111-118
-->

The threshold rises with the effect lifetime and the pilot's mobility percent. Round-mask effects use the shutdown resistance roll with a base of 0 at the end of each round; a successful resistance roll marks the effect for removal. Effects whose condition bits include radar or weapon-type tests are only applied when the matching weapon or attacker state is present.

```c src/battle/roll_battle_effect_removal_masks.c:98-120
unit_record = gBattleState + side_record_offset + unit_record_offset;
effect_offset = (effect_slot * 0xC) + BATTLE_UNIT_OFFSET(effects);
effect = unit_record + effect_offset;
if (mask_bank == BATTLE_EFFECT_REMOVAL_ROUND) {
    if ((RollBattleStatusResistance(side, unit_slot, 0) << 24) != 0)
        *round_mask |= 1 << effect_slot;
} else {
    register s32 effect_lifetime asm("r0");
    register s32 pilot_mobility_bonus asm("r1");
    register u32 pilot_mobility_address asm("r1");
    register u8 *battle_state_base asm("r2");

    roll = (CallFunctionR0(gRandomNumberCallback) * 100U) >> 15;
    effect_lifetime = BATTLE_EFFECT_FIELD(effect, s16, lifetime_value);
    pilot_mobility_address = unit_record_offset + side_record_offset;
    battle_state_base = gBattleState;
    pilot_mobility_address += (u32)battle_state_base;
    pilot_mobility_address += BATTLE_UNIT_OFFSET(pilot_id) + PLAYER_PILOT_OFFSET(mobility_bonus_percent);
    pilot_mobility_bonus = *(s16 *)pilot_mobility_address;
    if ((s32)roll > ScaleByPercent(effect_lifetime,
            pilot_mobility_bonus + 100))
        *action_mask |= 1 << effect_slot;
}
```

## Weapon attributes

| Bit | Attribute | Effect |
| --- | --- | --- |
| 0x01 | Ballistic | Type matching for abilities and armor |
| 0x02 | Missile | Type matching |
| 0x04 | Laser | Type matching |
| 0x08 | Particle | Type matching |
| 0x10 | Melee | Melee rules, melee anti-air, melee defense |
| 0x20 | Anti-air | Cancels the flying-target hit penalty |
| 0x40 | Water compatible | No water hit penalty in water |
| 0x80 | Homing | Triggers against-homing effects |
| 0x100 | Penetrate | Ignores energy shields |
| 0x200 | Ignore defense | Skips DF |
| 0x400 | Defense damage | Reduces the target's DF by one tenth of the weapon power |
| 0x800 | Pilot inactive | Disables the target's pilot bonuses |
| 0x1000 | Freeze | Adds a freeze effect on hit |
| 0x2000 | Confusion | Adds a confusion effect on hit |
| 0x1F | Type mask | The five damage types above |

The first five bits are mutually exclusive for ability lookup. A ranged accuracy ability only matches a non-melee weapon, a melee ability only a melee weapon, and the missile, laser, particle, and ballistic abilities require the matching type bit.

## Escape

Escape chance is computed from the average initiative of each side, counting units with a nonzero Zoid ID:

$$E = 50 + 40 \cdot [\bar{IV}_0 > \bar{IV}_1] + 10(N_0 - N_1) + 10 \cdot rounds$$

<!-- src
50 + 40 \cdot [\bar{IV}_0 > \bar{IV}_1] => src/battle/get_battle_escape_chance.c:40-46
10(N_0 - N_1) => src/battle/get_battle_escape_chance.c:47-56
10 \cdot rounds => src/battle/get_battle_escape_chance.c:57-67
-->

$N_0$ and $N_1$ count the units with a nonzero Zoid ID on each side, and $rounds$ is the number of elapsed rounds. The result is clamped to 1 to 99. When $gBattleSetup[0] = 2$, the chance is 100.

```c src/battle/get_battle_escape_chance.c:18-74
if (gBattleSetup[0] != 2) {
    for (side = 0; side < 2; side++) {
        s32 *sump = &initiative_sums[side];
        u8 *cntp = &unit_counts[side];
        s32 z = 0;
        asm volatile("" : "+r"(z));
        *cntp = z;
        *sump = z;
        for (unit = 0; unit < 6; unit++) {
            u8 *battle_unit = &gBattleState[side * 0x1380 + unit * 0x270];
            if (battle_unit[0] != 0) {
                initiative_sums[side] += BATTLE_UNIT_FIELD(battle_unit, s16, initiative);
                unit_counts[side]++;
            }
        }
        {
            s32 *fp = &initiative_sums[side];
            u8 c = unit_counts[side];
            *fp = DivideSigned32(*fp, c);
        }
    }
    {
        s32 player_initiative = initiative_sums[0];
        s32 enemy_initiative = initiative_sums[1];
        escape_chance = 50;
        if (player_initiative > enemy_initiative) {
            escape_chance = 90;
        }
    }
    {
        s32 d;
        {
            register s32 c0 asm("r0");
            c0 = unit_counts[0];
            asm volatile("" : "+r"(c0));
            d = c0;
        }
        escape_chance += (d - unit_counts[1]) * 10;
    }
    escape_chance = (s16)escape_chance;
    {
        u8 *p = gBattleState;
        s32 round_bonus = BATTLE_ESCAPE_FIELD(p, u8, elapsed_rounds) * 10;
        s32 v = escape_chance + round_bonus;
        asm volatile("" :: "r"(p));
        escape_chance = v;
        if ((s16)v <= 0) {
            escape_chance = 1;
        }
    }
    if (escape_chance > 99) {
        escape_chance = 99;
    }
} else {
    escape_chance = 100;
}
return escape_chance;
```

## Training and fusion

TP is a garage progression value. The battle stat pipeline never reads it; training changes the stored Zoid stats that the pipeline loads. Organoid fusion shows up in battle only through the Organoid fields the stat pipeline reads: the level bonus added to effective pilot level, the HP, power, sensor, speed, and defense percentages, and the auxiliary-pilot effects.

## On the name DCP

The US help text calls the stat "Shutdown resistance" and says low values make shutdowns more likely, which is how the threshold and resistance rolls behave. No first-party text expands the acronym. Community material uses "Damage Durability" and "Damage Capacity Point". The code field is DCP.
