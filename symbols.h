#ifndef __SYMBOLS_H_
#define __SYMBOLS_H_

#define MAX_FUNCTIONS 400
#define MAX_FUNCTION_NAME 200

typedef struct
{
    unsigned int address;
    char funcName[MAX_FUNCTION_NAME + 1];
} func_t;

void initSymbol(char *imageName);

int lookupSymbol(unsigned int address);

void addSymbol(unsigned int address);

void addCallTrace(unsigned int address);

void emitSymbols();

#endif