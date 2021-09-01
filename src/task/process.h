#ifndef PROCESS_H
#define PROCESS_H

#include <stdint.h>
#include <stdbool.h>
#include "task.h"
#include "config.h"

#define PROCESS_FILETYPE_ELF 0
#define PROCESS_FILETYPE_BINARY 1

typedef unsigned char PROCESS_TYPE;

struct process_allocation
{
    void* ptr;
    size_t size;
};

struct command_argument
{
    char argument[512];
    struct command_argument* next;
};

struct process_arguments
{
    int argc;
    char** argv;
};

struct process
{
    //The process id
    uint16_t id;

    char filename[SCORPION_MAX_PATH];

    //The main process task
    struct task* task;

    //The memory malloc allocations of the process
    struct process_allocation allocations[SCORPION_MAX_PROGRAM_ALLOCATIONS];

    PROCESS_TYPE filetype;

    union
    {
        //The physical pointer to process memory
        void* ptr;
        struct elf_file* elf_file;
    };

    //The physical pointer to stack memory
    void* stack;

    //The size of the data pointed to by 'ptr'
    uint32_t size;

    struct keyboard_buffer
    {
        char buffer[SCORPION_KEYBOARD_BUFFER_SIZE];
        int tail;
        int head;
    }keyboard;

    //The arguments of the process
    struct process_arguments arguments;
};

int process_switch(struct process* process);
int process_load_switch(const char* filename, struct process** process);
int process_load(const char* filename, struct process** process);
int process_load_for_slot(const char* filename, struct process** process, int process_slot);
struct process* process_current();
struct process* process_get(int process_id);
void* process_malloc(struct process* process, size_t size);
void process_free(struct process* process, void* ptr);

void process_get_arguments(struct process* process, int* argc, char*** argv);
int process_inject_arguments(struct process* process, struct command_argument* root_argument);

#endif