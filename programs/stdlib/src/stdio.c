#include "stdio.h"
#include "scorpion.h"
#include "stdlib.h"
#include <stdarg.h>

int putchar(int c)
{
    scorpion_putchar((char)c);
    return 0;
}

int printf(const char* format, ...)
{
    va_list ap;
    const char* p; 
    char* sval;
    int ival;
    
    va_start(ap, format);
    for(p = format; *p; p++)
    {
        if (*p != '%')
        {
            putchar(*p);
            continue;
        }

        switch(*++p)
        {
        case 'i':
            ival = va_arg(ap, int);
            print(itoa(ival));
            break;

        case 's':
            sval = va_arg(ap, char*);
            print(sval);
            break;

        default:
            putchar(*p);
            break;
        }
    }

    return 0;
}