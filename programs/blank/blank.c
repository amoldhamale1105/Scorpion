#include "scorpion.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

int main(int argc, char** argv)
{
    char words[] = "Hello how are you?";
    const char* token = strtok(words, " ");
    while (token)
    {
        printf("%s\n", token);
        token = strtok(NULL, " ");
    }
    
    printf("Hello, I am %i years old\n", 116);

    while(1) 
    {
    }
    return 0;
}