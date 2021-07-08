section .asm

extern int21h_handler
extern no_interrupt_handler
extern isr80h_handler
extern interrupt_handler

global idt_load
global no_interrupt
global enable_interrupts
global disable_interrupts
global isr80h_wrapper
global interrupt_pointer_table

enable_interrupts:
    sti
    ret

disable_interrupts:
    cli
    ret

idt_load:
    push ebp
    mov ebp, esp

    mov ebx, [ebp+8] ; points to the first arg passed to a function
    lidt [ebx]
    pop ebp
    ret

no_interrupt:
    pushad
    call no_interrupt_handler
    popad
    iret

%macro interrupt 1
    global int%1
    int%1:
        ; Interrupt frame start
        ; Already pushed by processor upon entry to this interrupt
        ; uint32 ip
        ; uint32 cs
        ; uint32 flags
        ; uint32 sp
        ; uint32 ss
        ; Pushad pushes general purpose registers to the stack
        pushad
        ; Interrupt frame end
        push esp
        push dword %1
        call interrupt_handler
        add esp, 8
        popad
        iret
%endmacro

%assign i 0
%rep 512
    interrupt i
%assign i i+1
%endrep

isr80h_wrapper:
    ; Interrupt frame start
    ; Already pushed by processor upon entry to this interrupt
    ; uint32 ip
    ; uint32 cs
    ; uint32 flags
    ; uint32 sp
    ; uint32 ss
    ; Pushad pushes general purpose registers to the stack
    pushad

    ; Interrupt frame end

    ; Push stack pointer so that we are pointing to the interrupt frame (the data we and the processor pushed on the stack for this interrupt)
    push esp

    ; EAX holds our command to be pushed into the isr80h_handler
    push eax
    call isr80h_handler
    mov dword[tmp_res], eax
    add esp, 8

    ; Restore general purpose registers for user land
    popad
    mov eax, [tmp_res]
    iretd

section .data
; Stores return result from isr80h_handler
tmp_res: dd 0

%macro interrupt_array_entry 1
    dd int%1
%endmacro

interrupt_pointer_table:
%assign i 0
%rep 512
    interrupt_array_entry i
%assign i i+1
%endrep
