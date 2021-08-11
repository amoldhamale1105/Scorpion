[BITS 32]

global print:function
global getkey:function
global scorpion_malloc:function

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

; int getkey()
getkey:
    push ebp
    mov ebp, esp
    mov eax, 2 ; command getkey
    int 0x80
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