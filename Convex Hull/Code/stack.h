/*
    Written by William Sutherland for
    COMP20007 Assignment 1 2023 Semester 1
    Modified by Grady Fitzpatrick

    Header for module which contains stack-related
        data structures and functions.
*/
#ifndef STACK_H
#define STACK_H

/* The data structure of the stack */
struct stack;

/* Creates the stack */
struct stack *createStack(int item);

/* Note that you are passing a pointer to the pointer of the stack
   into the below arguments */

/* Pops an item from the stack and returns the void pointer */
struct stack *pop(struct stack *s);

/* Push an item to the top of the stack */
struct stack *push(struct stack *s, int item);

/* Frees the memory associated with the stack */
void freeStack(struct stack *s);

/* Get second top element from stack */
int getSecondTop(struct stack *s);

/* Get top element from stack */
int getTop(struct stack *s);

/* Show all items in the stack */
void showStack(struct stack *s);

/* Check if stack has the shird layer */
int hasThird(struct stack *s);

#endif