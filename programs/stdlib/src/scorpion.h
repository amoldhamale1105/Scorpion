#ifndef SCORPION_H
#define SCORPION_H

#include <stddef.h>
#include <stdbool.h>

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

void print(const char* message);
int scorpion_getkey();
void* scorpion_malloc(size_t size);
void scorpion_free(void* ptr);
void scorpion_putchar(char c);
int scorpion_getkeyblock();
void scorpion_terminal_readline(char* out, int max, bool output_while_typing);
void scorpion_process_load_start(const char* filename);
struct command_argument* scorpion_parse_command(const char* command, int max);
void scorpion_process_get_arguments(struct process_arguments* arguments);

#endif