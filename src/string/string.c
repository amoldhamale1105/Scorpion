#include "string.h"

int strlen(const char* ptr)
{
    int len = 0;
    while (ptr[len])
    {
        len++;
    }

    return len;
}

int strnlen(const char* ptr, int max)
{
    int len;
    for (len = 0; len < max; len++)
    {
        if (!ptr[len]) break;
    }

    return len;
}

bool isdigit(char c)
{
    return c >= 48 && c <= 57;
}

int tonumericdigit(char c)
{
    //48 is ASCII value for numeric character '0'
    return c - 48;
}
