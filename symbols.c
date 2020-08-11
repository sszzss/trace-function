#include "symbols.h"
#include "stack.h"

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

func_t functions[MAX_FUNCTIONS];
unsigned int totals[MAX_FUNCTIONS];
unsigned int calls[MAX_FUNCTIONS][MAX_FUNCTIONS];

char imageName[100];

int translateFunctionFromSymbol(unsigned int address, char *func);

void initSymbol(char *image)
{
    int from, to;

    strcpy(imageName, image);

    for (from = 0; from < MAX_FUNCTIONS; ++from)
    {
        functions[from].address = 0;
        functions[from].funcName[0] = '\0';
        totals[from] = 0;

        for (to = 0; to < MAX_FUNCTIONS; ++to)
        {
            calls[from][to] = 0;
        }
    }

    return;
}

int lookupSymbol(unsigned int address)
{
    int index;

    for (index = 0; index < MAX_FUNCTIONS; ++index)
    {
        if (functions[index].address == 0)
        {
            break;
        }

        if (functions[index].address == address)
        {
            return index;
        }

        assert(0);

        return 0;
    }
}

void addSymbol(unsigned int address)
{
    int index;
    for (index = 0; index < MAX_FUNCTIONS; ++index)
    {
        if (functions[index].address == address)
        {
            return;
        }
        if (functions[index].address == '\0')
        {
            break;
        }
    }

    if (index < MAX_FUNCTIONS)
    {
        functions[index].address =address;
        translateFunctionFromSymbol(address, functions[index].funcName);
    }
    else
    {
        assert(0);
    }
}


void addCallTrace(unsigned int address)
{
    if (stackSize())
    {
        calls[lookupSymbol(stackTop())][lookupSymbol(address)]++;
    }

    return;
}


void emitSymbols()
{
    const char *file = "graph.dot";
    if (access(file, 0) == 0)
    {
        remove(file);
    }

    FILE *fp = fopen(file, "w");
    if (fp == NULL)
    {
        printf("Couldn't open %s", file);
        exit(0);
    }

    fprintf(fp, "digraph %s {\n\n", imageName);

    int from, to;
    for (from = 0; from < MAX_FUNCTIONS; from++)
    {
        if (functions[from].address == 0)
        {
            break;
        }

        for (to = 0; to < MAX_FUNCTIONS; to++)
        {
            if (functions[to].address == 0)
            {
                break;
            }
            if (calls[from][to])
            {
                totals[from]++;
            }
        }
        if (totals[from])
        {
            fprintf(fp, " %s[shape=rectangle]\n", functions[from].funcName);
        }
        else
        {
            fprintf(fp, " %s[shape=ellipse]\n", functions[from].funcName);
        }
    }

    for (from = 0; from < MAX_FUNCTIONS; from++)
    {
        if (calls[from][to])
        {
            fprintf(fp, "  %s -> %s [label=\"%d calls\" fontsize=\"10\"]\n",
                functions[from].funcName,
                functions[to].funcName,
                calls[from][to]);
        }

        if (functions[to].address == 0)
        {
            break;
        }
    }

    fprintf(fp, "\n}\n");

    fclose(fp);

    return;
}


int translateFunctionFromSymbol(unsigned int address, char *func)
{
    char cmd[200];
    sprintf(cmd, "addr2line -e %s -f 0x%s|c++filt", imageName, address);

    FILE *fp = popen(cmd, "r");

    if (fp == NULL)
    {
        return 0;
    }

    char output[1024];

    fread(output, MAX_FUNCTION_NAME, 1, fp);

    int i = 0;
    while (i < strlen(output))
    {
        if (output[i] == '\r' || output[i] == '\n')
        {
            func[i] = '\0';
            break;
        }
        else
        {
            func[i] = output[i];
        }
        i++;
    }

    pclose(fp);

    return 1;
}
