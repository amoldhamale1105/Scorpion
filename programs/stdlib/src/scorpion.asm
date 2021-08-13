[BITS 32]

section .asm

global print:function
global scorpion_getkey:function
global scorpion_malloc:function
global scorpion_free:function
global scorpion_putchar:function

; void print(const char* message)
print:
    push ebp
    mov ebp, esp
    push dword[ebp+8]
    mov eax, 1 ; command print
    int 0x80
    add esp, 4
    pop ebp
    ret

; int scorpion_getkey()
scorpion_getkey:
    push ebp
    mov ebp, esp
    mov eax, 2 ; command getkey
    int 0x80
    pop ebp
    ret

; void scorpion_putchar(char c)
scorpion_putchar:
    push ebp
    mov ebp, esp
    mov eax, 3 ; command putchar
    push dword[ebp+8]
    int 0x80
    add esp, 4
    pop ebp
    ret

; void* scorpion_malloc(size_t size)
scorpion_malloc:
    push ebp
    mov ebp, esp
    mov eax, 4 ; command malloc to allocate memory for process
    push dword[ebp+8] ; variable size pushed to stack
    int 0x80
    add esp, 4 ; restore the stack
    pop ebp
    ret

; void scorpion_free(void* ptr)
scorpion_free:
    push ebp
    mov ebp, esp
    mov eax, 5 ; command free
    push dword[ebp+8]
    int 0x80
    add esp, 4
    pop ebp
    ret