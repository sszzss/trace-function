#include <assert.h>

#define MAX_ELEMENTS 200

static unsigned int stack[MAX_ELEMENTS];
static int index;

void initStack()
{
    index = 0;
    return;
}

int stackSize()
{
    return index;
}

unsigned int stackTop()
{
    assert(index > 0);
    return stack[index - 1];
}

void pushStack(unsigned int value)
{
    assert(index < MAX_ELEMENTS);
    stack[index] =value;
    index++;

    return;
}

unsigned int popStack()
{
    assert(index > 0);

    index--;
    return stack[index];
}