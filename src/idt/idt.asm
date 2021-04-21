section .asm

global idt_load
idt_load:
    push ebp
    mov ebp, esp

    mov ebx, [ebp+8] ; points to the first arg passed to a function
    lidt [ebx]
    pop ebp
    ret