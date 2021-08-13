#include "scorpion.h"
#include "stdlib.h"
#include "stdio.h"

int main(int argc, char** argv)
{
    printf("Hello, I am %i years old\n", 116);

    void* ptr = malloc(512);
    free(ptr);
    
    char buf[1024];
    scorpion_terminal_readline(buf, sizeof(buf), true);
    print(buf);
    
    while(1) 
    {
    }
    return 0;
}