#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "symbols.h"
#include "draw.h"

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("Illegal arguments.\n");
        exit(-1);
    }

    initSymbol(argv[1]);
    initStack();

    FILE *traceFp;
    traceFp = fopen(argv[2], "r");
    if (traceFp == NULL)
    {
        printf("Can't open %s.\n", argv[2]);
        exit(-1);
    }

    char type;
    unsigned int address;
    while (!feof(traceFp))
    {
        fscanf(traceFp, "%c%x\n", &type, &address);

        if (type == '>')
        {
            addSymbol(address);
            addCallTrace(address);
            pushStack(address);
        }
        else if (type == '<')
        {
            popStack();
        }
    }

    emitSymbols();

    fclose(traceFp);

    drawWithDocker("graph.dot", "svg");

    return 0;
}
