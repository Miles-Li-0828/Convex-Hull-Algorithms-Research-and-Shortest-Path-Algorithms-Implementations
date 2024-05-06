/*
    Skeleton written by Grady Fitzpatrick for
    COMP20007 Assignment 1 2024 Semester 1

    Header for module which contains convex hull
        specification data structures and functions.

    Implemented by Miles Li
*/
#include "linkedList.h"
#include "pq.h"
#include "problem.h"
#include "convexHull.h"
#include "stack.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define TRUE 1

enum orientationResult
{
    COLLINEAR = 0,
    CLOCKWISE = 1,
    COUNTERCLOCKWISE = 2
};

/* Finds the orientation between the three given points - calculates the angle between
    the Middle-First vector and Middle-Final vector - if the Middle-First vector is zero-length,
    the gradient of the Middle-Final vector is instead used. */
enum orientationResult orientation(struct problem *p, int idxFirst, int idxMiddle, int idxFinal);

enum orientationResult orientation(struct problem *p, int idxFirst, int idxMiddle, int idxFinal)
{
    assert(idxFirst >= 0 && idxFirst < p->numPoints);
    assert(idxMiddle >= 0 && idxMiddle < p->numPoints);
    assert(idxFinal >= 0 && idxFinal < p->numPoints);

    /* Use cross-product to calculate turn direction. */
    long double p0x = p->pointsX[idxFirst];
    long double p0y = p->pointsY[idxFirst];

    long double p1x = p->pointsX[idxMiddle];
    long double p1y = p->pointsY[idxMiddle];

    long double p2x = p->pointsX[idxFinal];
    long double p2y = p->pointsY[idxFinal];

    /* Cross product of vectors P1P0 & P1P2 */
    long double crossProduct = (p0x - p1x) * (p2y - p1y) - (p0y - p1y) * (p2x - p1x);

    if (crossProduct == 0)
    {
        if (idxFirst == idxMiddle)
        {
            /* Special case where we are only looking for positive slope of P1P2. */
            if (p2x == p1x)
            {
                /* Special case: dx = 0, vertical */
                if (p2y < p1y)
                {
                    /* Directly upwards */
                    return COUNTERCLOCKWISE;
                }
                else if (p2y == p1y)
                {
                    /* Same point. */
                    return COLLINEAR;
                }
                else
                {
                    return CLOCKWISE;
                }
            }
            long double m = (p2y - p1y) / (p2x - p1x);
            if (m >= 0)
            {
                return COUNTERCLOCKWISE;
            }
            else
            {
                return CLOCKWISE;
            }
        }
        return COLLINEAR;
    }
    else if (crossProduct > 0)
    {
        return CLOCKWISE;
    }
    else
    {
        return COUNTERCLOCKWISE;
    }
}

struct solution *jarvisMarch(struct problem *p)
{
    /* Part A - perform Jarvis' March to construct a convex
    hull for the given problem. */
    /* IMPLEMENT HERE */
    // Initialise an empty hull
    struct linkedList *hull = newList();
    assert(hull);
    struct solution *s = (struct solution *)malloc(sizeof(struct solution));
    assert(s);
    s->operationCount = 0;

    // If less than 3 points, return an empty hull
    if (p->numPoints < 3)
    {
        s->convexHull = hull;
        return s;
    }

    // Find the leftmost point and put it in the hull
    int mostLeftIdx = 0;
    for (int i = 1; i < p->numPoints; i++)
    {
        // More left than marked point
        if (p->pointsX[i] < p->pointsX[mostLeftIdx])
        {
            mostLeftIdx = i;
        }
        // Horizonally same, find most bottom point
        else if (p->pointsX[i] == p->pointsX[mostLeftIdx] && p->pointsY[i] < p->pointsY[mostLeftIdx])
        {
            mostLeftIdx = i;
        }
    }

    // Draw an intact convex hull by anticlockwise direction
    int currentIdx = mostLeftIdx;
    while (TRUE)
    {
        insertTail(hull, p->pointsX[currentIdx], p->pointsY[currentIdx]);

        int nextPointIdx = 0;

        for (int i = 0; i < p->numPoints; i++)
        {
            if (nextPointIdx == currentIdx ||
                orientation(p, nextPointIdx, currentIdx, i) == COUNTERCLOCKWISE)
            {
                nextPointIdx = i;
            }
            s->operationCount++;
        }
        currentIdx = nextPointIdx;

        if (currentIdx == mostLeftIdx)
            break;
    }

    s->convexHull = hull;
    printf("Operation count: %d\n", s->operationCount);
    return s;
}

struct solution *grahamScan(struct problem *p)
{
    /* Part B - perform Graham's Scan to construct a convex
    hull for the given problem. */
    /* IMPLEMENT HERE */
    struct linkedList *hull = newList();
    struct solution *s = (struct solution *)malloc(sizeof(struct solution));
    assert(s);

    int *sortedIndices = (int *)malloc(p->numPoints * sizeof(int));

    s->operationCount = 0;

    // If less than 3 points, return an empty hull
    if (p->numPoints < 3)
    {
        s->convexHull = hull;
        return s;
    }

    // Find the lowest point
    int lowestIdx = 0;
    for (int i = 0; i < p->numPoints; i++)
    {
        if (p->pointsY[i] < p->pointsY[lowestIdx])
            lowestIdx = i;
        else if (p->pointsY[i] == p->pointsY[lowestIdx] &&
                 p->pointsX[i] < p->pointsX[lowestIdx])
            lowestIdx = i;
    }

    /* Sort the points by angle */
    // Use bubble sort, sort all the indices accoding to the angles
    sortedIndices[0] = lowestIdx;
    for (int i = 1; i < p->numPoints; i++)
    {
        if (i == lowestIdx)
            continue;
        sortedIndices[i] = i;
    }
    s->operationCount = bubbleSort(sortedIndices, p->numPoints, p);
    sortedIndices = realloc(sortedIndices, (p->numPoints + 1) * sizeof(int));
    sortedIndices[p->numPoints] = sortedIndices[0];

    // Push first 3 points into the stack
    struct stack *points = createStack(sortedIndices[0]);
    points = push(points, sortedIndices[1]);
    points = push(points, sortedIndices[2]);

    // Iterate over the points left
    for (int i = 3; i < p->numPoints + 1; i++)
    {
        while (
            orientation(p, getSecondTop(points), getTop(points), sortedIndices[i]) !=
            COUNTERCLOCKWISE)
        {
            points = pop(points);
        }
        points = push(points, sortedIndices[i]);
    }
    // Pop the origin point
    points = pop(points);

    // Put points in stack to a list
    while (points != NULL)
    {
        int idx = getTop(points);
        points = pop(points);
        insertHead(hull, p->pointsX[idx], p->pointsY[idx]);
    }

    // The end
    printf("Basic operations: %d\n", s->operationCount);
    s->convexHull = hull;
    return s;
}

void freeSolution(struct solution *s)
{
    if (!s)
    {
        return;
    }
    if (s->convexHull)
    {
        freeList(s->convexHull);
    }
    free(s);
}

// Use bubble sort to sort the points by angles
int bubbleSort(int indices[], int n, struct problem *p)
{
    int count = 0;
    int tempIdx;
    for (int i = 1; i < n - 1; i++)
    {
        for (int j = 1; j < n - i - 1; j++)
        {
            count++;
            // If angle of point j+1 is bigger than point j, swap
            if (orientation(p, indices[j], indices[0], indices[j + 1]) ==
                COUNTERCLOCKWISE)
            {
                tempIdx = indices[j];
                indices[j] = indices[j + 1];
                indices[j + 1] = tempIdx;
            }
            // If angles are same, compare the distance
            else if (orientation(p, indices[j], indices[0], indices[j + 1]) ==
                     COLLINEAR)
            {
                double distance1 = sqrt(pow(p->pointsY[indices[j]] -
                                                p->pointsY[indices[0]],
                                            2) +
                                        pow(p->pointsX[indices[j]] -
                                                p->pointsX[indices[0]],
                                            2));
                double distance2 = sqrt(pow(p->pointsY[indices[j + 1]] -
                                                p->pointsY[indices[0]],
                                            2) +
                                        pow(p->pointsX[indices[j + 1]] -
                                                p->pointsX[indices[0]],
                                            2));
                if (distance2 < distance1)
                {
                    tempIdx = indices[j];
                    indices[j] = indices[j + 1];
                    indices[j + 1] = tempIdx;
                }
            }
        }
    }
    return count;
}