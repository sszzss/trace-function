#include "symbols.h"
#include "stack.h"

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

func_t functions[MAX_FUNCTIONS];
unsigned int totals[MAX_FUNCTIONS];
unsigned int calls[MAX_FUNCTIONS][MAX_FUNCTIONS];

char imageName[100];

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
