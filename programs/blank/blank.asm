[BITS 32]

section .asm

global _start

_start:
    push 21
    push 17
    mov eax, 0 ; command 0 to SUM
    int 0x80
    add esp, 8
    
    jmp $