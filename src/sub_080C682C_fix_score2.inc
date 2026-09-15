.macro mov dst, src
.purgem mov
mov r4, #0
.endm
.macro ldrsh dst, addr:vararg
.purgem ldrsh
ldrsh r0, [r0, r4]
.endm
