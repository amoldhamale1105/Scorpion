#include "scorpion.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

int main(int argc, char** argv)
{
    for(int i = 0; i < argc; i++)
    {
        printf("%s\n", argv[i]);
    }

    // Meant to create an exception
    char* ptr = (char*)0;
    *ptr = 0x50;

    while(1) 
    {
    }
    return 0;
}