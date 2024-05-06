/*
graph.c

Set of vertices and edges implementation.

Implementations for helper functions for graph construction and manipulation.

Skeleton written by Grady Fitzpatrick for COMP20007 Assignment 1 2024
*/
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include "graph.h"
#include "utils.h"
#include "pq.h"

#define INITIALEDGES 32
#define NIL -1

struct edge;

/* Definition of a graph. */
struct graph
{
    int numVertices;
    int numEdges;
    int allocedEdges;
    struct edge **edgeList;
};

/* Definition of an edge. */
struct edge
{
    int start;
    int end;
    int cost;
};

struct graph *newGraph(int numVertices)
{
    struct graph *g = (struct graph *)malloc(sizeof(struct graph));
    assert(g);
    /* Initialise edges. */
    g->numVertices = numVertices;
    g->numEdges = 0;
    g->allocedEdges = 0;
    g->edgeList = NULL;
    return g;
}

/* Adds an edge to the given graph. */
void addEdge(struct graph *g, int start, int end, int cost)
{
    assert(g);
    struct edge *newEdge = NULL;
    /* Check we have enough space for the new edge. */
    if ((g->numEdges + 1) > g->allocedEdges)
    {
        if (g->allocedEdges == 0)
        {
            g->allocedEdges = INITIALEDGES;
        }
        else
        {
            (g->allocedEdges) *= 2;
        }
        g->edgeList = (struct edge **)realloc(g->edgeList,
                                              sizeof(struct edge *) * g->allocedEdges);
        assert(g->edgeList);
    }

    /* Create the edge */
    newEdge = (struct edge *)malloc(sizeof(struct edge));
    assert(newEdge);
    newEdge->start = start;
    newEdge->end = end;
    newEdge->cost = cost;

    /* Add the edge to the list of edges. */
    g->edgeList[g->numEdges] = newEdge;
    (g->numEdges)++;
}

/* Returns a new graph which is a deep copy of the given graph (which must be
  freed with freeGraph when no longer used). */
struct graph *duplicateGraph(struct graph *g)
{
    struct graph *copyGraph = (struct graph *)malloc(sizeof(struct graph));
    assert(copyGraph);
    copyGraph->numVertices = g->numVertices;
    copyGraph->numEdges = g->numEdges;
    copyGraph->allocedEdges = g->allocedEdges;
    copyGraph->edgeList = (struct edge **)malloc(sizeof(struct edge *) * g->allocedEdges);
    assert(copyGraph->edgeList || copyGraph->numEdges == 0);
    int i;
    /* Copy edge list. */
    for (i = 0; i < g->numEdges; i++)
    {
        struct edge *newEdge = (struct edge *)malloc(sizeof(struct edge));
        assert(newEdge);
        newEdge->start = (g->edgeList)[i]->start;
        newEdge->end = (g->edgeList)[i]->end;
        newEdge->cost = (g->edgeList)[i]->cost;
        (copyGraph->edgeList)[i] = newEdge;
    }
    return copyGraph;
}

/* Frees all memory used by graph. */
void freeGraph(struct graph *g)
{
    int i;
    for (i = 0; i < g->numEdges; i++)
    {
        free((g->edgeList)[i]);
    }
    if (g->edgeList)
    {
        free(g->edgeList);
    }
    free(g);
}

struct solution *graphSolve(struct graph *g, enum problemPart part,
                            int numLocations, int startingLocation,
                            int finalLocation)
{
    struct solution *solution = (struct solution *)
        malloc(sizeof(struct solution));
    assert(solution);
    if (part == PART_A)
    {
        /* IMPLEMENT 2A SOLUTION HERE */
        // Since the graph is undirected graph, the edges are symmetric
        int edgesCount = g->numEdges;
        // So, there are 2*E edges in this
        for (int i = 0; i < edgesCount; i++)
        {
            addEdge(g,
                    g->edgeList[i]->end,
                    g->edgeList[i]->start,
                    g->edgeList[i]->cost);
        }

        // Apply Dijkstra's algorithm
        int *vertices = (int *)malloc(g->numVertices * sizeof(int));
        assert(vertices != NULL);

        // Initialise all vertices
        for (int i = 0; i < g->numVertices; i++)
        {
            vertices[i] = i;
        }

        // Use Dijkstra's algorithm get the shortest path
        int shortestDist = dijkstra(g, vertices,
                                    startingLocation, finalLocation);

        solution->damageTaken = shortestDist;
    }
    else if (part == PART_B)
    {
        /* IMPLEMENT 2B SOLUTION HERE */
        /* Totally same as part a */

        // Since the graph is undirected graph, the edges are symmetric
        int edgesCount = g->numEdges;
        // So, there are 2*E edges in this
        for (int i = 0; i < edgesCount; i++)
        {
            addEdge(g,
                    g->edgeList[i]->end,
                    g->edgeList[i]->start,
                    g->edgeList[i]->cost);
        }

        // Apply Dijkstra's algorithm
        int *vertices = (int *)malloc(g->numVertices * sizeof(int));
        assert(vertices != NULL);

        // Initialise all vertices
        for (int i = 0; i < g->numVertices; i++)
        {
            vertices[i] = i;
        }

        // Use Dijkstra's algorithm get the shortest path
        int shortestDist = dijkstra(g, vertices,
                                    startingLocation, finalLocation);
        solution->totalCost = shortestDist;
    }
    else if (part == PART_C)
    {
        /* IMPLEMENT 2C SOLUTION HERE */
        // Since the graph is undirected graph, the edges are symmetric
        int edgesCount = g->numEdges;
        // So, there are 2*E edges in this
        for (int i = 0; i < edgesCount; i++)
        {
            addEdge(g,
                    g->edgeList[i]->end,
                    g->edgeList[i]->start,
                    g->edgeList[i]->cost);
        }

        // Apply Prim's algorithm
        int *vertices = (int *)malloc(g->numVertices * sizeof(int));
        assert(vertices != NULL);
        int lowestCost = 0;

        // Initialise all vertices
        for (int i = 0; i < g->numVertices; i++)
        {
            vertices[i] = i;
        }

        lowestCost = prim(g, vertices, startingLocation);
        solution->artisanCost = lowestCost;
    }
    else
    {
        /* IMPLEMENT 2D SOLUTION HERE */
        // Since the graph is undirected graph, the edges are symmetric
        int edgesCount = g->numEdges;
        // So, there are 2*E edges in this
        for (int i = 0; i < edgesCount; i++)
        {
            addEdge(g,
                    g->edgeList[i]->end,
                    g->edgeList[i]->start,
                    g->edgeList[i]->cost);
        }

        // Apply Dijkstra's algorithm
        int *vertices = (int *)malloc(g->numVertices * sizeof(int));
        assert(vertices != NULL);

        // Initialise all vertices
        for (int i = 0; i < g->numVertices; i++)
        {
            vertices[i] = i;
        }

        // Use Dijkstra's algorithm get the shortest path
        int shortestDist = dijkstraForD(g, vertices,
                                        startingLocation, finalLocation);

        solution->totalPercentage = shortestDist;
    }
    return solution;
}

// Dijkstra's Algorithm to calculate the shortest path in a graph
int dijkstra(struct graph *g, int *vertices,
             int startPoint, int destination)
{
    int *dist = (int *)malloc(g->numVertices * sizeof(int));
    assert(dist != NULL);
    int *prev = (int *)malloc(g->numVertices * sizeof(int));
    assert(prev != NULL);
    int shortestPath = INT_MAX;

    // Initialise the distance array and previous array
    for (int i = 0; i < g->numVertices; i++)
    {
        dist[i] = INT_MAX;
        prev[i] = NIL;
    }
    dist[startPoint] = 0;
    struct pq *priorityQueue = newPQ();

    for (int i = 0; i < g->numVertices; i++)
    {
        enqueue(priorityQueue, (vertices + i), dist[i]);
    }

    // Allocate the shortest path by priority queue
    while (!empty(priorityQueue))
    {
        int *u = (int *)deletemin(priorityQueue);
        for (int i = 0; i < g->numEdges; i++)
        {
            if (*u == g->edgeList[i]->start)
            {
                int *w = &(g->edgeList[i]->end);
                if (isInQueue(priorityQueue, w) &&
                    dist[*u] + g->edgeList[i]->cost < dist[g->edgeList[i]->end])
                {
                    dist[g->edgeList[i]->end] = dist[*u] + g->edgeList[i]->cost;
                    prev[g->edgeList[i]->end] = *u;
                    updatePq(priorityQueue,
                             w,
                             dist[g->edgeList[i]->end]);
                }
            }
        }
    }

    // Find the distance from start point to destination
    shortestPath = dist[destination];
    return shortestPath;
}

// Prim's algorithm calculate the shortest path over all nodes
int prim(struct graph *g, int *vertices, int startPoint)
{
    int *cost = (int *)malloc(g->numVertices * sizeof(int));
    assert(cost != NULL);
    int *prev = (int *)malloc(g->numVertices * sizeof(int));
    assert(prev != NULL);
    int lowestCost = 0;

    // Initialise cost array, prev array
    for (int i = 0; i < g->numVertices; i++)
    {
        cost[i] = INT_MAX;
        prev[i] = NIL;
    }
    cost[startPoint] = 0;
    struct pq *priorityQueue = newPQ();

    for (int i = 0; i < g->numVertices; i++)
    {
        enqueue(priorityQueue, (vertices + i), cost[i]);
    }

    // Allocate the priority queue and find lowest cost
    while (!empty(priorityQueue))
    {
        int *u = (int *)deletemin(priorityQueue);

        for (int i = 0; i < g->numEdges; i++)
        {
            if (g->edgeList[i]->start == *u)
            {
                int *w = &(g->edgeList[i]->end);
                if (isInQueue(priorityQueue, w) &&
                    g->edgeList[i]->cost < cost[*w])
                {
                    cost[*w] = g->edgeList[i]->cost;
                    prev[*w] = *u;
                    updatePq(priorityQueue, w, g->edgeList[i]->cost);
                }
            }
        }
    }

    // Calculate the lowest cost
    for (int i = 0; i < g->numVertices; i++)
    {
        lowestCost += cost[i];
    }
    return lowestCost;
}

// Dijkstra's Algorithm for part D
int dijkstraForD(struct graph *g, int *vertices,
                 int startPoint, int destination)
{
    double *dist = (double *)malloc(g->numVertices * sizeof(double));
    assert(dist != NULL);
    int *prev = (int *)malloc(g->numVertices * sizeof(int));
    assert(prev != NULL);
    double shortestPath = INT_MAX;

    // Initialise the distance array and previous array
    for (int i = 0; i < g->numVertices; i++)
    {
        dist[i] = INT_MAX;
        prev[i] = NIL;
    }
    dist[startPoint] = 0;
    struct pq *priorityQueue = newPQ();

    for (int i = 0; i < g->numVertices; i++)
    {
        enqueue(priorityQueue, (vertices + i), dist[i]);
    }

    // Allocate the shortest path by priority queue
    while (!empty(priorityQueue))
    {
        int *u = (int *)deletemin(priorityQueue);
        for (int i = 0; i < g->numEdges; i++)
        {
            if (*u == g->edgeList[i]->start)
            {
                int *w = &(g->edgeList[i]->end);
                if (isInQueue(priorityQueue, w) &&
                    dist[*u] * (100 + g->edgeList[i]->cost) / 100 +
                            g->edgeList[i]->cost <
                        dist[g->edgeList[i]->end])
                {
                    dist[g->edgeList[i]->end] = dist[*u] *
                                                    (100 +
                                                     g->edgeList[i]->cost) /
                                                    100 +
                                                g->edgeList[i]->cost;
                    prev[g->edgeList[i]->end] = *u;
                    updatePq(priorityQueue,
                             w,
                             dist[g->edgeList[i]->end]);
                }
            }
        }
    }

    // Find the distance from start point to destination
    shortestPath = dist[destination];
    return shortestPath;
}