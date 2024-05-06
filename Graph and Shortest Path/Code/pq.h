/*
pq.h

Visible structs and functions for priority queues.

Skeleton written by Grady Fitzpatrick for COMP20007 Assignment 1 2022
*/
/* The priority queue. */
struct pq;

/* Get a new empty priority queue. */
struct pq *newPQ();

/* Add an item to the priority queue - cast pointer to (void *). */
void enqueue(struct pq *pq, void *item, int priority);

/* Take the smallest item from the priority queue - cast pointer back to
  original type. */
void *deletemin(struct pq *pq);

/* Returns 1 if empty, 0 otherwise. */
int empty(struct pq *pq);

/* Remove all items from priority queue (doesn't free) and free the queue. */
void freePQ(struct pq *pq);

/* Check if the item is in the priority queue */
int isInQueue(struct pq *pq, void *item);

/* Update the priority queue with new priority */
void updatePq(struct pq *pq, void *item, int priority);

// Check the elements in queue
void checkPq(struct pq *pq);