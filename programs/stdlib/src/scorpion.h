#ifndef SCORPION_H
#define SCORPION_H

#include <stddef.h>
#include <stdbool.h>

void print(const char* message);
int scorpion_getkey();
void* scorpion_malloc(size_t size);
void scorpion_free(void* ptr);
void scorpion_putchar(char c);
int scorpion_getkeyblock();
void scorpion_terminal_readline(char* out, int max, bool output_while_typing);

#endif