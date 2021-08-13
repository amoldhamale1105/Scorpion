#include "stdio.h"
#include "scorpion.h"

int putchar(int c)
{
    scorpion_putchar((char)c);
    return 0;
}