//
// Created by Graham McKnight on 7/30/2017.
//

#include "chessEngine.h"

/*
 * Function Name: moveCompare()
 * Function Prototype: int moveCompare(const void* p1, const void* p2);
 * Description: Comparison function for sorting the possible moves by
 *              Most-Valuable-Victim Least-Valuable-Aggressor.
 * Parameters:
 *      const void* p1 -- The first move to compare.
 *      const void* p2 -- The second move to compare.
 * Side Effects: None.
 * Return Value: Negative if p1 is a more promising move, positive if p2 is
 *               a more promising move. 0 if they have equal potential.
 */

int moveCompare(const void* p1, const void* p2)
{
    return ((struct Move*) p2)->heuristic - ((struct Move*) p1)->heuristic;
}