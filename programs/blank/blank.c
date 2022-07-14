#include "scorpion.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

int main(int argc, char** argv)
{
    const char* outputStr = argc == 1 ? "without" : "with";
    printf("Executing program %s %s arguments ", argv[0], outputStr);
    
    for(int i = 1; i < argc; i++)
    {
        printf("%s ", argv[i]);
    }
    printf("\n");

    return 0;
}