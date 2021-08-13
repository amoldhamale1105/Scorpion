#include "scorpion.h"
#include "stdlib.h"
#include "stdio.h"

int main(int argc, char** argv)
{
    printf("Hello, I am %i years old\n", 116);

    void* ptr = malloc(512);
    free(ptr);
    
    while(1) 
    {
        if (getkey() != 0)
        {
            print("key was pressed!\n");
        }
    }
    return 0;
}