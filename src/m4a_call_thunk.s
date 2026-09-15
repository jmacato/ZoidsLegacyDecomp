/* M4A dynamic-call thunk with a function pointer in r3. */
.syntax unified
.thumb
.section .text
.global m4a_call_thunk
.thumb_func
m4a_call_thunk:
    bx r3
