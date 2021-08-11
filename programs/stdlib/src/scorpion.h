#ifndef SCORPION_H
#define SCORPION_H

#include <stddef.h>

void print(const char* message);
int getkey();
void* scorpion_malloc(size_t size);

#endif