/*
    Skeleton written by Grady Fitzpatrick for
    COMP20007 Assignment 1 2024 Semester 1

    Implementation details for module which contains doubly-linked list
        specification data structures and functions.

    Implemented by <YOU>
*/

#include "linkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

struct linkedList
{
    struct linkedListNode *head;
    struct linkedListNode *tail;
};

struct linkedListNode
{
    /* IMPLEMENT HERE */
    long double x;
    long double y;
    struct linkedListNode *next;
    struct linkedListNode *prev;
};

/* Print out each value in the list from the first value to the final value.
    Each value is printed with the format "(x, y) " where x is the x value
    set when inserting the item and y is the y value set when inserting
    the item. */
void traverseRingForward(struct linkedList *list)
{
    /* IMPLEMENT HERE */
    struct linkedListNode *cursor = list->head;

    // Check if the list is empty
    if (list == NULL || list->head == NULL || list->tail == NULL)
    {
        printf("This is a empty list\n");
        return;
    }

    // Iterate though the list
    while (cursor != NULL)
    {
        printf("(%.6Lf, %.6Lf) ", cursor->x, cursor->y);
        cursor = cursor->next;
    }
}

/* Print out first the first item of the list, then print out each value in
    the list from the final value to the second value.
    Each value is printed with the format "(x, y) " where x is the x value
    set when inserting the item and y is the y value set when inserting
    the item. */
void traverseRingBackwards(struct linkedList *list)
{
    /* IMPLEMENT HERE */
    struct linkedListNode *cursor = list->head;

    // Check if the list is empty
    if (list == NULL || list->head == NULL || list->tail == NULL)
    {
        printf("This is a empty list\n");
        return;
    }

    // Print the first node in the list
    printf("(%.6Lf, %.6Lf) ", cursor->x, cursor->y);

    // From the tail, traverse back to the head
    cursor = list->tail;
    while (cursor != list->head)
    {
        printf("(%.6Lf, %.6Lf) ", cursor->x, cursor->y);
        cursor = cursor->prev;
    }
}

/* Return a new empty list. */
struct linkedList *newList()
{
    /* IMPLEMENT HERE */
    struct linkedList *list = (struct linkedList *)
        malloc(sizeof(struct linkedList));
    assert(list != NULL);
    list->head = list->tail = NULL;
    return list;
}

/* Insert the given x, y pair at the head of the list */
void insertHead(struct linkedList *list, long double x, long double y)
{
    /* IMPLEMENT HERE */
    struct linkedListNode *new = (struct linkedListNode *)
        malloc(sizeof(struct linkedListNode));
    assert(new != NULL);
    new->x = x;
    new->y = y;
    new->next = NULL;
    new->prev = NULL;

    // List is empty, assign head = tail = new
    if (list->head == NULL || list->tail == NULL)
    {
        list->head = list->tail = new;
        return;
    }

    // List is not empty, insert to the head
    new->next = list->head;
    list->head->prev = new;
    list->head = new;
}

/* Insert the given x, y pair at the tail of the list */
void insertTail(struct linkedList *list, long double x, long double y)
{
    /* IMPLEMENT HERE */
    struct linkedListNode *new = (struct linkedListNode *)
        malloc(sizeof(struct linkedListNode));
    assert(new != NULL);
    new->x = x;
    new->y = y;
    new->next = NULL;
    new->prev = NULL;

    // List is empty, assign head = tail = new
    if (list->head == NULL || list->tail == NULL)
    {
        list->head = list->tail = new;
        return;
    }

    // List is not empty, insert to the tail
    new->prev = list->tail;
    list->tail->next = new;
    list->tail = new;
}

/* Free all items in the given list. */
void freeList(struct linkedList *list)
{
    /* IMPLEMENT HERE */
    // Handle the exception that if list is empty
    if (list == NULL)
    {
        return;
    }

    // Iterate through the list and free every node
    struct linkedListNode *cursor1 = list->head;
    struct linkedListNode *cursor2;

    while (cursor1 != NULL)
    {
        cursor2 = cursor1;
        cursor1 = cursor1->next;
        free(cursor2);
    }
    free(list);
}
