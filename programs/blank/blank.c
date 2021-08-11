#include "scorpion.h"
#include "stdlib.h"

int main(int argc, char** argv)
{
    print("Hello how are you?\n");

    void* ptr = malloc(512);
    if (ptr)
    {
        print("memory allocated!\n");
    }
    while(1) 
    {
        if (getkey() != 0)
        {
            print("key was pressed!\n");
        }
    }
    return 0;
}