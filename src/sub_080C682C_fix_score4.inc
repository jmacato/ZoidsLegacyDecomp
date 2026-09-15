.macro mov dst, src
.purgem mov
mov r2, #0
.endm
.macro ldrsh dst, addr:vararg
.purgem ldrsh
ldrsh r0, [r0, r2]
.endm
