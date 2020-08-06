#include <stdio.h>
#include <stdlib.h>


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
            
        }
        else if(type == '<')
        {

        }
    }

    fclose(traceFp);

    return 0;
}