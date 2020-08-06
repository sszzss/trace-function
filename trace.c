#include <stdio.h>
#include <stdlib.h>

#include "stack.h"


int main(int argc, char **argv)
{
    if(argc != 3)
    {
        printf("Illegal arguments.");
        exit(-1);
    }

    FILE *traceFp;
    traceFp = fopen(argv[1], "r");
    if(traceFp == NULL)
    {
        printf("Can't open %s.\n", argv[1]);
        exit(-1);
    }

    char type;
    unsigned int address;
    while(!feof(traceFp))
    {
        fscanf(traceFp, "%c%x\n", &type, &address);
        if(type == '>')
        {
            printf(">");
        }
        else if(type == '<')
        {
            printf("<");
        }
    }

    fclose(traceFp);

    return 0;
}