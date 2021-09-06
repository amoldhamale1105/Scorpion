[BITS 32]

global _start
extern c_start
extern scorpion_exit

section .asm

_start:
    call c_start
    call scorpion_exit
    ret