#include "stdlib.h"
#include "scorpion.h"

void* malloc(size_t size)
{
    return scorpion_malloc(size);
}

void free(void* ptr)
{
    scorpion_free(ptr);
}