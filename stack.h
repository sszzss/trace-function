#ifndef __STACK_H_
#define __STACK_H_

void initStack();

int stackSize();

unsigned int stackTop();

void pushStack(unsigned int value);

unsigned int popStack();

#endif