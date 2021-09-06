[BITS 32]

section .asm

global print:function
global scorpion_getkey:function
global scorpion_malloc:function
global scorpion_free:function
global scorpion_putchar:function
global scorpion_process_load_start:function
global scorpion_process_get_arguments:function
global scorpion_system:function
global scorpion_exit:function

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

; void scorpion_process_load_start(const char* filename)
scorpion_process_load_start:
    push ebp
    mov ebp, esp
    mov eax, 6 ; command 6 to start a process
    push dword[ebp+8]
    int 0x80
    add esp, 4
    pop ebp
    ret

;int scorpion_system(struct command_argument* arguments)
scorpion_system:
    push ebp
    mov ebp, esp
    mov eax, 7 ;command 7 runs a system command based on the arguments
    push dword[ebp+8]
    int 0x80
    add esp, 4
    pop ebp
    ret

;void scorpion_process_get_arguments(struct process_arguments* arguments)
scorpion_process_get_arguments:
    push ebp
    mov ebp, esp
    mov eax, 8 ; command 8 to get process args
    push dword[ebp+8] ; variable arguments
    int 0x80
    add esp, 4
    pop ebp
    ret

;void scorpion_exit()
scorpion_exit:
    push ebp
    mov ebp, esp
    mov eax, 9
    int 0x80
    pop ebp
    ret