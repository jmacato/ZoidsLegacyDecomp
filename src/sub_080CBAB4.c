#include "m2c_prelude.h"

typedef struct BattleState {
    u16 unk0;
    u16 flags;
    u32 status;
} BattleState;

BattleState *func_080E669C(void);
void func_080E66B8(void);
void func_080E8C90(u32, u32, u32, u32, BattleState *);
extern u8 D_02034B4C[];

s32 sub_080CBAB4(u8 arg0)
{
    register u32 direction asm("r9") = arg0;
    BattleState *state = func_080E669C();

    if (direction != 0) {
        goto navigate;
    }

    {
        register u8 *table_base asm("r8");
        register u8 *player_ptr asm("r9");
        register u32 player asm("r5");
        register u32 preferred_count asm("r4");
        register u8 *table_load asm("r0") = (u8 *)0x020218E4;
        register u8 *player_load asm("r2") = (u8 *)0x02033F37;
        register u32 table_offset asm("r3") = 0x691C;
        register u8 *preferred_count_ptr asm("r1");

        __asm__("" : "+r"(table_load));
        __asm__("" : "+r"(player_load));
        player = *player_load;
        preferred_count_ptr = table_load + table_offset;
        preferred_count_ptr = (u8 *)(player + (u32)preferred_count_ptr);
        preferred_count = *preferred_count_ptr;
        table_base = table_load;
        player_ptr = player_load;

        if (preferred_count != 0) {
            register u8 *state_load asm("r0") = D_02034B4C;
            register u32 count_offset asm("r2") = 0xA1AF;
            register u8 *count_ptr asm("r1");
            register u32 live_count asm("r3");

            __asm__("" : "+r"(state_load));
            __asm__("" : "+r"(count_offset));
            count_ptr = state_load + count_offset;
            live_count = *count_ptr;
            __asm__("" : "+r"(live_count));
            if (preferred_count <= live_count) {
                goto preferred_failed;
            }
            {
                register s32 i asm("r3") = 0;
                register u32 count_check asm("r0") = *count_ptr;
                register u8 *validated_count_ptr asm("r5");

                if (i < (s32)count_check) {
                    register u8 *search_state asm("r4") = D_02034B4C;
                    register u32 selection_offset asm("r1") = 0xA1B0;
                    register u8 *selection_base asm("r6");
                    register u32 count asm("r4");
                    register u32 preferred asm("r1");
                    register u32 preferred_index asm("r0");
                    register u8 *preferred_base asm("r1");
                    register u8 *preferred_address asm("r0");

                    __asm__("" : "+r"(search_state));
                    __asm__("" : "+r"(selection_offset));
                    selection_base = search_state + selection_offset;
                    count = count_check;
                    preferred_index = player << 1;
                    preferred_index += player;
                    preferred_index = count + preferred_index;
                    preferred_base = (u8 *)0x6922;
                    __asm__("" : "+r"(preferred_base));
                    preferred_base += (u32)table_base;
                    preferred_address = (u8 *)(preferred_index + (u32)preferred_base);
                    preferred = *preferred_address;

preferred_search_loop:
                    {
                        register u32 narrow asm("r0") = (u32)i << 24;
                        register s32 signed_i asm("r2") = (s32)narrow >> 24;
                        register u8 *entry asm("r0") =
                            (u8 *)(signed_i + (u32)selection_base);

                        if (*entry == preferred) {
                            goto preferred_search_done;
                        }
                        narrow = signed_i + 1;
                        narrow <<= 24;
                        i = narrow >> 24;
                        narrow = (s32)narrow >> 24;
                        if ((s32)narrow < (s32)count) {
                            goto preferred_search_loop;
                        }
                    }
                }

preferred_search_done:
                {
                    register u32 narrow asm("r0") = (u32)i << 24;
                    register u8 *state_load2 asm("r2");
                    register u32 count_offset2 asm("r4");
                    register u32 count2 asm("r0");

                    i = (s32)narrow >> 24;
                    __asm__("" : "+r"(i));
                    state_load2 = D_02034B4C;
                    count_offset2 = 0xA1AF;
                    __asm__("" : "+r"(state_load2));
                    __asm__("" : "+r"(count_offset2));
                    validated_count_ptr = state_load2 + count_offset2;
                    count2 = *validated_count_ptr;
                    __asm__("" : "+r"(count2));
                    if (i != (s32)count2) {
                        goto preferred_failed;
                    }
                }
                {
                    register u8 *unit_base_slot asm("r0") = (u8 *)0x02033F38;
                    register u32 unit_base asm("r1") = *(u32 *)unit_base_slot;
                    register u8 *player_view asm("r2") = player_ptr;
                    register u32 player2 asm("r4") = *player_view;
                    register u32 preferred_index asm("r0");
                    register u8 *preferred_base asm("r6") = (u8 *)0x6922;
                    register u32 preferred asm("r2");
                    register u16 *unit_field asm("r1");

                    preferred_index = player2 << 1;
                    preferred_index += player2;
                    preferred_index = i + preferred_index;
                    preferred_base += (u32)table_base;
                    preferred_index += (u32)preferred_base;
                    preferred = *(u8 *)preferred_index;
                    unit_field = (u16 *)(unit_base + (preferred << 2) + 0x52);
                    if (*unit_field == 0) {
                        goto preferred_failed;
                    }
                    func_080E8C90(*(u8 *)0x02033F36, player2, preferred,
                                  i, state);
                    {
                        register u32 flags asm("r1") = state->flags;
                        register u32 test asm("r0") = 1;

                        test &= flags;
                        if (test != 0) {
                            goto preferred_failed;
                        }
                    }
                    if (*validated_count_ptr != 0
                        && (state->status & 0x10) != 0) {
                        goto preferred_failed;
                    }
                    {
                        register u32 count3 asm("r1") = *validated_count_ptr;
                        register u8 *destination asm("r3");

                        __asm__("" : "+r"(count3));
                        {
                            register u8 *store_base asm("r4") = D_02034B4C;
                            register u32 store_offset asm("r0") = 0xA1B0;

                            __asm__("" : "+r"(store_base));
                            __asm__("" : "+r"(store_offset));
                            destination = store_base + store_offset;
                            destination = (u8 *)(count3 + (u32)destination);
                            __asm__("" : "+r"(destination));
                        }
                        {
                            register u8 *player_view2 asm("r4") = player_ptr;
                            register u32 player3 asm("r2") = *player_view2;
                            register u32 source_offset asm("r0");

                            source_offset = player3 << 1;
                            source_offset += player3;
                            count3 += source_offset;
                            count3 += (u32)preferred_base;
                            *destination = *(u8 *)count3;
                        }
                        goto done;
                    }
                }
            }
            }
        }

preferred_failed:

    {
        register u32 candidate asm("r8");
        register u8 *state_base asm("r9");
        register u8 *selection_base asm("sl");
        register u8 *count_ptr asm("r4");
        {
            register u32 zero asm("r0") = 0;
            register u8 *state_init asm("r1");
            register u32 selection_offset asm("r2");

            __asm__("" : "+r"(zero));
            candidate = zero;
            state_init = D_02034B4C;
            __asm__("" : "+r"(state_init));
            state_base = state_init;
            selection_offset = 0xA1B0;
            __asm__("" : "+r"(selection_offset));
            selection_base = state_base + selection_offset;
        }

fallback_loop:
        {
            register u32 raw_candidate asm("r2");
            register u32 candidate_copy asm("r3");
            register s32 value asm("r5");
            register u8 *unit_slot asm("r6") = (u8 *)0x27A8;
            register u32 unit_base asm("r1");
            register u16 *unit_field asm("r1");

            unit_slot += (u32)state_base;
            unit_base = *(u32 *)unit_slot;
            candidate_copy = candidate;
            __asm__("" : "+r"(candidate_copy));
            raw_candidate = candidate_copy << 24;
            value = (s32)raw_candidate >> 24;
            unit_field = (u16 *)(unit_base + (value << 2) + 0x52);
            if (*unit_field != 0) {
                register u32 call0 asm("r0");
                register u32 call1 asm("r1");
                register u32 count_offset asm("r4");

                call0 = *(u8 *)0x02033F36;
                call1 = *(u8 *)0x02033F37;
                raw_candidate >>= 24;
                count_offset = 0xA1AF;
                __asm__("" : "+r"(count_offset));
                count_ptr = state_base + count_offset;
                func_080E8C90(call0, call1,
                              raw_candidate, *count_ptr, state);
                {
                    register u32 flags asm("r1") = state->flags;
                    register u32 test asm("r0") = 2;

                    test &= flags;
                    if (test != 0) {
                        goto fallback_next;
                    }
                }
                {
                    register u32 count0 asm("r0") = *count_ptr;
                    register s32 i asm("r3");
                    register u32 count asm("r1");

                    if (count0 == 0) {
                        goto fallback_found;
                    }
                    i = 0;
                    count = count0;
                    if (i < (s32)count) {
                        register u8 *first_selection asm("r4") = selection_base;
                        register u32 first_value asm("r0");

                        __asm__("" : "+r"(first_selection));
                        first_value = *first_selection;
                        if (first_value != value) {
                            register u8 *search_state asm("r0") = D_02034B4C;
                            register u32 selection_offset asm("r2") = 0xA1B0;
                            register u8 *selection_scan asm("r4");

                            __asm__("" : "+r"(search_state));
                            __asm__("" : "+r"(selection_offset));
                            selection_scan = search_state + selection_offset;
                            __asm__("" : "+r"(selection_scan));
                            {
                            register s32 compare_value asm("r2") = value;

fallback_search_loop:
                            {
                                register u32 narrow asm("r0") = (u32)i << 24;

                                narrow += 0x01000000;
                                i = narrow >> 24;
                                narrow = (s32)narrow >> 24;
                                if ((s32)narrow >= (s32)count) {
                                    goto fallback_search_done;
                                }
                                if (*(u8 *)((u32)narrow + (u32)selection_scan)
                                    != compare_value) {
                                    goto fallback_search_loop;
                                }
                            }
                            }
                        }
                    }

fallback_search_done:
                    {
                        register u32 narrow asm("r0") = (u32)i << 24;
                        register u8 *state_load asm("r4");
                        register u32 count_offset asm("r2");
                        register u8 *count_view asm("r1");
                        register u32 live_count asm("r1");

                        narrow = (s32)narrow >> 24;
                        __asm__ volatile("" : "+r"(narrow) : : "memory");
                        state_load = D_02034B4C;
                        count_offset = 0xA1AF;
                        __asm__("" : "+r"(state_load));
                        __asm__("" : "+r"(count_offset));
                        count_view = state_load + count_offset;
                        live_count = *count_view;
                        if ((s32)narrow != (s32)live_count) {
                            goto fallback_next;
                        }
                    }
                    {
                        register u32 flags asm("r1") = state->flags;
                        register u32 test asm("r0") = 1;

                        test &= flags;
                        if (test != 0 || (state->status & 0x10) != 0) {
                            goto fallback_next;
                        }
                    }
                    goto fallback_found;
                }
            }
        }

fallback_next:
        {
            register u32 candidate_view asm("r3");
            register u32 narrow asm("r0");
            register u32 bump asm("r4");
            register u32 next asm("r1");

            __asm__("" : "=r"(candidate_view) : "0"(candidate));
            narrow = candidate_view << 24;
            __asm__ volatile("" : "+r"(narrow));
            bump = 0x01000000;
            __asm__("" : "+r"(bump));
            narrow += bump;
            next = narrow >> 24;
            __asm__("" : "+r"(next));
            candidate = next;
            narrow = (s32)narrow >> 24;
            if ((s32)narrow <= 7) {
                goto fallback_loop;
            }
        }

fallback_found:
        {
            register u32 candidate_view asm("r2") = candidate;
            register u32 narrow asm("r0") = candidate_view << 24;

            narrow = (s32)narrow >> 24;
            if ((s32)narrow > 7) {
                __asm__ volatile("b .Lcbab4_return_zero");
            }
            {
                register u8 *state_work asm("r0") = D_02034B4C;
                register u32 count_offset asm("r3") = 0xA1AF;
                register u8 *count_ptr2 asm("r1");
                register u32 selection_offset asm("r4");
                register u32 live_count asm("r1");

                __asm__("" : "+r"(state_work));
                __asm__("" : "+r"(count_offset));
                count_ptr2 = state_work + count_offset;
                selection_offset = 0xA1B0;
                __asm__("" : "+r"(selection_offset));
                state_work += selection_offset;
                live_count = *count_ptr2;
                state_work += live_count;
                *(u8 *)state_work = candidate_view;
                __asm__("" : : "r"(state_work));
            }
        }
        goto done;
    }

navigate:
    __asm__ volatile("" : "+r"(direction));
    {
        register u32 candidate asm("r8");
        register u8 *count_ptr asm("sl");
        register s32 raw_candidate asm("r2");
        {
            register u8 *state_load asm("r0");
            register u32 count_offset asm("r1");
            register u8 *count_ptr_low asm("r4");

            state_load = D_02034B4C;
            __asm__("" : "+r"(state_load));
            count_offset = 0xA1AF;
            __asm__("" : "+r"(count_offset));
            count_ptr_low = state_load + count_offset;
            {
                register u32 selection_index asm("r1") = *count_ptr_low;
                register u32 selection_offset asm("r2") = 0xA1B0;
                register u8 *selection_root asm("r3") =
                    state_load + selection_offset;
                register u8 *selection_ptr asm("r1");
                register u32 current asm("r0");

                __asm__("" : "+r"(selection_index));
                selection_index += (u32)selection_root;
                __asm__("" : "+r"(selection_root));
                selection_ptr = (u8 *)selection_index;
                current = *selection_ptr;
                current += direction;
                current <<= 24;
                current >>= 24;
                candidate = current;
                raw_candidate = current << 24;
                current = raw_candidate >> 24;
                {
                    register u32 selected asm("r1") = *selection_ptr;
                    __asm__ volatile(
                        "cmp %0, %1\n\tbeq .Lcbab4_return_zero"
                        : : "r"(current), "r"(selected) : "cc");
                }
            }
            count_ptr = count_ptr_low;
        }
navigation_loop:
        {
            register s32 signed_candidate asm("r0");

            signed_candidate = raw_candidate >> 24;
            if (signed_candidate < 0) {
                register u32 seven asm("r3") = 7;
                __asm__("" : "+r"(seven));
                candidate = seven;
            } else if (signed_candidate > 7) {
                register u32 zero asm("r4") = 0;
                __asm__("" : "+r"(zero));
                candidate = zero;
            }
        }

navigation_check:
        {
            register u8 *state_load asm("r6") = D_02034B4C;
            register u32 unit_offset asm("r1") = 0x27A8;
            register u8 *unit_slot asm("r0");
            register u32 unit_address asm("r1");
            register u32 candidate_copy asm("r3");
            register s32 value asm("r5");
            register u16 *unit_field asm("r1");

            __asm__("" : "+r"(unit_offset));
            unit_slot = state_load + unit_offset;
            unit_address = *(u32 *)unit_slot;
            candidate_copy = candidate;
            raw_candidate = candidate_copy << 24;
            value = raw_candidate >> 24;
            unit_address += value << 2;
            unit_address += 0x52;
            unit_field = (u16 *)unit_address;
            if (*unit_field != 0) {
                register u32 call0 asm("r0");
                register u32 call1 asm("r1");
                register u32 count_offset asm("r3");
                register u8 *count_ptr_low asm("r4");

                call0 = *(u8 *)0x02033F36;
                __asm__("" : "+r"(call0));
                call1 = *(u8 *)0x02033F37;
                __asm__("" : "+r"(call1));
                raw_candidate = (u32)raw_candidate >> 24;
                count_offset = 0xA1AF;
                count_ptr_low = state_load + count_offset;
                func_080E8C90(call0, call1, raw_candidate,
                              *count_ptr_low, state);
                {
                    register u32 flags asm("r1") = state->flags;
                    register u32 test asm("r0") = 2;

                    test &= flags;
                    if (test != 0) {
                        goto navigation_next;
                    }
                }
                {
                    register u32 count0 asm("r0") = *count_ptr_low;
                    register s32 i asm("r3");

                    if (count0 == 0) {
                        goto navigation_found;
                    }
                    i = 0;
                    {
                        register u32 initial_count asm("r4") =
                            *(volatile u8 *)count_ptr_low;

                        __asm__("" : "+r"(initial_count));
                        if (i >= (s32)initial_count) {
                            goto navigation_search_done;
                        }
                    }
                    {
                            register u8 *search_state asm("r4") = D_02034B4C;
                            register u32 selection_offset asm("r0") = 0xA1B0;
                            register u8 *selection_scan asm("r1") =
                                search_state + selection_offset;
                            register u32 loop_work asm("r2");
                            register u32 count asm("r4");

                            if (*selection_scan == value) {
                                goto navigation_search_done;
                            }
                            loop_work = (u32)count_ptr;
                            count = *(u8 *)loop_work;
                            loop_work = value;
navigation_search_loop:
                            {
                                register u32 narrow asm("r0") = (u32)i << 24;
                                i = 0x01000000;
                                narrow += i;
                                i = narrow >> 24;
                                narrow = (s32)narrow >> 24;
                                if ((s32)narrow >= (s32)count) {
                                    goto navigation_search_done;
                                }
                                if (*(u8 *)((u32)narrow + (u32)selection_scan)
                                    != loop_work) {
                                    goto navigation_search_loop;
                                }
                            }
                    }

navigation_search_done:
                    {
                        register u32 narrow asm("r0") = (u32)i << 24;
                        register u8 *count_view asm("r4");
                        register u32 count asm("r4");

                        narrow = (s32)narrow >> 24;
                        count_view = count_ptr;
                        count = *count_view;
                        if ((s32)narrow != (s32)count) {
                            goto navigation_next;
                        }
                    }
                    {
                        register u32 flags asm("r1") = state->flags;
                        register u32 test asm("r0") = 1;
                        test &= flags;
                        if (test != 0) {
                            goto navigation_next;
                        }
                    }
                    if ((state->status & 0x10) == 0) {
                        goto navigation_found;
                    }
                }
            }
        }
navigation_next:
        {
            register u32 signed_current asm("r1") =
                (u32)(s8)candidate;
            register u32 signed_direction asm("r0") =
                (u32)(s8)direction;

            signed_current += signed_direction;
            signed_current <<= 24;
            candidate = signed_current >> 24;
            raw_candidate = candidate << 24;
            {
                register s32 signed_raw asm("r1") = raw_candidate >> 24;
                register u8 *count_view asm("r3");
                register u32 count asm("r0");
                register u8 *selection_root asm("r4");

                __asm__ volatile("" : "+r"(signed_raw) : : "memory");
                __asm__("" : "=r"(count_view) : "0"(count_ptr));
                count = *count_view;
                selection_root = (u8 *)0x0203ECFC;
                __asm__("" : "+r"(selection_root));
                count += (u32)selection_root;
                count = *(u8 *)count;
                if (signed_raw != (s32)count) {
                    goto navigation_loop;
                }
            }
        }

        if ((s8)candidate == ((u8 *)0x0203ECFC)[*count_ptr]) {
            goto navigation_same;
        }

navigation_same:
navigation_found:
        {
            register u32 candidate_view asm("r1");
            register s32 signed_candidate asm("r0");
            register u8 *state_base asm("r3");
            register u32 count_offset asm("r4");
            register u8 *count_ptr2 asm("r2");
            register u8 *selection_ptr asm("r1");
            register u32 count asm("r2");
            register u32 current asm("r2");

            __asm__("" : "=r"(candidate_view) : "0"(candidate));
            signed_candidate = (s32)(candidate_view << 24) >> 24;
            __asm__ volatile("" : "+r"(signed_candidate) : : "memory");
            state_base = D_02034B4C;
            count_offset = 0xA1AF;
            __asm__("" : "+r"(state_base));
            __asm__("" : "+r"(count_offset));
            count_ptr2 = state_base + count_offset;
            count_offset++;
            selection_ptr = state_base + count_offset;
            count = *count_ptr2;
            selection_ptr += count;
            current = *selection_ptr;
            __asm__("" : "+r"(current));
            if (signed_candidate == current) {
                __asm__ volatile(".Lcbab4_return_zero:");
                func_080E66B8();
                return 0;
            }
            {
                register u32 store_value asm("r3");
                __asm__("" : "=r"(store_value) : "0"(candidate));
                *selection_ptr = store_value;
            }
        }
    }

done:
    func_080E66B8();
    return 1;
}
