#include "scorpion.h"
#include "stdlib.h"

int main(int argc, char** argv)
{
    print("Hello how are you?\n");
    print(itoa(97343));
    
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