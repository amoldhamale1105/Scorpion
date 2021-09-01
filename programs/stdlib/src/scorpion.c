#include "scorpion.h"
#include "string.h"

struct command_argument* scorpion_parse_command(const char* command, int max)
{
    struct command_argument* root_command = 0;
    char scommand[1024];
    if (max >= (int) sizeof(scommand))
    {
        return 0;
    }

    strncpy(scommand, command, sizeof(scommand));
    char* token = strtok(scommand, " ");
    if (!token)
    {
        goto out;
    }

    root_command = scorpion_malloc(sizeof(struct command_argument));
    if (!root_command)
    {
        goto out;
    }

    strncpy(root_command->argument, token, sizeof(root_command->argument));
    root_command->next = 0;

    struct command_argument* current = root_command;
    token = strtok(NULL, " ");
    while(token != 0)
    {
        struct command_argument* new_command = scorpion_malloc(sizeof(struct command_argument));
        if (!new_command)
        {
            break;
        }

        strncpy(new_command->argument, token, sizeof(new_command->argument));
        new_command->next = 0;
        current->next = new_command;
        current = new_command;
        token = strtok(NULL, " ");
    }

out:
    return root_command;
}

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