.syntax unified
.arm
.section .text
.global rom_restart
.type rom_restart, %function
.equ rom_entry_address, 0x080000C0
rom_restart:
    b rom_entry_address
.size rom_restart, . - rom_restart
