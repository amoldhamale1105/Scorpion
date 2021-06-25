section .asm

extern int21h_handler
extern no_interrupt_handler
extern isr80h_handler

global int21h
global idt_load
global no_interrupt
global enable_interrupts
global disable_interrupts
global isr80h_wrapper

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

int21h:
    pushad
    call int21h_handler
    popad
    iret

no_interrupt:
    pushad
    call no_interrupt_handler
    popad
    iret

isr80h_wrapper:
    ; Interrupt frame start
    ; Already pushed by processor upon entry to this interrupt
    ; uint32 ip
    ; uint32 cs
    ; uint32 flags
    ; uint32 sp
    ; uint32 ss
    ; Pushad pushes general purpose registers to the stack
    pushd

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