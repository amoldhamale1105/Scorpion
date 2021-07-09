#include "kernel.h"
#include <stddef.h>
#include <stdint.h>
#include "idt/idt.h"
#include "memory/heap/kheap.h"
#include "memory/paging/paging.h"
#include "memory/memory.h"
#include "keyboard/keyboard.h"
#include "string/string.h"
#include "isr80h/isr80h.h"
#include "task/task.h"
#include "task/process.h"
#include "fs/file.h"
#include "disk/disk.h"
#include "fs/pparser.h"
#include "disk/streamer.h"
#include "task/tss.h"
#include "gdt/gdt.h"
#include "config.h"
#include "status.h"

uint16_t* video_mem = 0;
uint16_t terminal_row = 0;
uint16_t terminal_col = 0;

uint16_t terminal_make_char(uint8_t c, uint8_t color)
{
    return (color << 8) | c;
}

void terminal_putchar(int x, int y, char c, char color)
{
    video_mem[(y * VGA_WIDTH) + x] = terminal_make_char(c, color);
}

void terminal_writechar(char c, char color)
{
    if (c == '\n')
    {
        terminal_row++;
        terminal_col = 0;
        return;
    }

    terminal_putchar(terminal_col, terminal_row, c, color);
    terminal_col++;
    if(terminal_col >= VGA_WIDTH)
    {
        terminal_col = 0;
        terminal_row++;
    }
}

void terminal_initialize()
{
    video_mem = (uint16_t*)0xB8000;
    terminal_row = 0;
    terminal_col = 0;

    for (int y = 0; y < VGA_HEIGHT; y++)
    {
        for (int x = 0; x < VGA_WIDTH; x++)
        {
            terminal_putchar(x, y, ' ', 0);
        }
    }
}

void print(const char* str)
{
    size_t len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        terminal_writechar(str[i], 15);
    }
}

static struct paging_4gb_chunk* kernel_chunk = 0;

void panic(const char* msg)
{
    print(msg);
    while(1) {}
}

void kernel_page()
{
    kernel_registers();
    paging_switch(kernel_chunk);
}

struct tss tss;
struct gdt gdt_real[SCORPION_TOTAL_GDT_SEGMENTS];
struct gdt_structured gdt_structured[SCORPION_TOTAL_GDT_SEGMENTS] = {
    {.base = 0x00, .limit = 0x00, .type = 0x00}, //NULL segment
    {.base = 0x00, .limit = 0xFFFFFFFF, .type = 0x9a}, // Kernel code segment
    {.base  = 0x00, .limit = 0xFFFFFFFF, .type = 0x92}, //Kernel data segment
    {.base = 0x00, .limit = 0xFFFFFFFF, .type = 0xF8}, //User code segment
    {.base = 0x00, .limit = 0xFFFFFFFF, .type = 0xF2}, //User data segment
    {.base = (uint32_t)&tss, .limit = sizeof(tss), .type = 0xE9} //TSS segment
};

void pic_timer_callback(struct interrupt_frame* frame)
{
    print("Timer activated\n");
}

void kernel_main()
{
    terminal_initialize();

    memset(gdt_real, 0x00, sizeof(gdt_real));
    gdt_structured_to_gdt(gdt_real, gdt_structured, SCORPION_TOTAL_GDT_SEGMENTS);

    //Load the GDT
    gdt_load(gdt_real, sizeof(gdt_real));

    //Initialise the heap
    kheap_init();

    //Initialise the file system
    fs_init();

    //Search and initialise the disks
    disk_search_and_init();

    //Initialize the interrupt descriptor table
    idt_init();

    //Set up TSS
    memset(&tss, 0x00, sizeof(tss));
    tss.esp0 = 0x600000;
    tss.ss0 = KERNEL_DATA_SELECTOR;

    //Load the TSS
    tss_load(0x28);

    //Setup paging
    kernel_chunk = paging_new_4gb(PAGING_IS_WRITEABLE | PAGING_IS_PRESENT | PAGING_ACCESS_FROM_ALL);

    //Switch to kernel paging chunk
    paging_switch(kernel_chunk);

    //Enable paging
    enable_paging();

    //Register the kernel commands
    isr80h_register_commands();

    //Initialise all the system keyboards
    keyboard_init();

    idt_register_interrupt_callback(0x20, pic_timer_callback);

    struct process* process = 0;
    int res = process_load_switch("0:/blank.bin", &process);
    if (res != SCORPION_ALL_OK)
    {
        panic("Failed to load blank.bin");
    }

    keyboard_push('A');
    
    task_run_first_ever_task();

    while (1) {}
}