#include "shell.h"
#include "stdio.h"
#include "stdlib.h"
#include "scorpion.h"

int main(int argc, char** argv)
{   
    print("Scorpion v1.0.0\n");
    while(1)
    {
        print("\n> ");
        char buf[1024];
        scorpion_terminal_readline(buf, sizeof(buf), true);
        print("\n");
        scorpion_system_run(buf);
    }
    return 0;
}