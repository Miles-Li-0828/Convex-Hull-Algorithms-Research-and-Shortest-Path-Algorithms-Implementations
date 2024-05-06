/*
    Written by William Sutherland for
    COMP20007 Assignment 1 2023 Semester 1
    Modified by Grady Fitzpatrick

    Implementation for module which contains
        stack-related data structures and
        functions.
*/
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct stack
{
    int item;
    struct stack *below;
};

struct stack *createStack(int item)
{
    struct stack *s = (struct stack *)malloc(sizeof(struct stack));
    assert(s);
    s->item = item;
    s->below = NULL;
    return s;
}

struct stack *pop(struct stack *s)
{
    if (s == NULL)
        return NULL;

    struct stack *b = s->below;
    free(s);
    return b;
}

int getSecondTop(struct stack *s)
{
    if (s == NULL || s->below == NULL)
        return -1;
    int secondTop = s->below->item;
    return secondTop;
}

int getTop(struct stack *s)
{
    if (s == NULL)
        return -1;
    int top = s->item;
    return top;
}

struct stack *push(struct stack *s, int item)
{
    if (s == NULL)
    {
        s = createStack(item);
        return s;
    }

    struct stack *top = createStack(item);
    top->below = s;
    return top;
}

void freeStack(struct stack *s)
{
    for (struct stack *curr = s; curr != NULL; s = curr)
    {
        curr = curr->below;
        free(s);
    }
}
