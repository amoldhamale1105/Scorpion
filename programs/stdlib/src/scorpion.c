#include "scorpion.h"

int scorpion_getkeyblock()
{
    int val = 0;
    do
    {
        val = scorpion_getkey();
    }
    while(val == 0);
    return val;
}

void scorpion_terminal_readline(char* out, int max, bool output_while_typing)
{
    int i = 0;
    for(i = 0; i < max-1; i++)
    {
        char key = scorpion_getkeyblock();

        //carriage return (Enter key) means we have read the line
        if (key == 13)
        {
            break;
        }

        if (output_while_typing)
        {
            scorpion_putchar(key);
        }

        //backspace
        if (key == 0x0A && i >= 1)
        {
            out[i-1] = 0;
            // -2 because we increment by 1 when we continue
            i -= 2;
            continue;
        }

        out[i] = key;
    }

    out[i] = 0;
}