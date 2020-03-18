//
// Created by Graham McKnight on 7/1/2017.
//
#include <stdlib.h>
#include <string.h>

#include "chessEngine.h"

/*
 * Function Name: getLegalMoves()
 * Function Prototype: struct Move * getLegalMoves(int * board, int position);
 * Description: Returns the set of raw moves that won't result in the player
 *              being in check.
 * Parameters:
 *      int * board -- The array holding the board state.
 *      int position -- The collapsed position from which the move will be
 *                      made.
 * Side Effects: Allocates memory on the heap.
 * Return Value: A pointer to the nul-terminated array of legal moves.
 */

struct Move * getLegalMoves(int * board, int position)
{
    struct Move moves[SINGLE_MAX_MOVES];
    int count = 0;
    int rawCount;

    int color = board[position] & COLOR;

    struct Move * rawMoves = getRawMoves(
            board, position, &rawCount, NULL);

    for (int i = 0; i < rawCount; i++)
    {
        applyMove(board, rawMoves[i]);
        if (!inCheck(board, color))
        {
            moves[count] = rawMoves[i];
            count++;
        }
        reverseMove(board, rawMoves[i]);
    }

    free(rawMoves);

    moves[count].source = 0;
    moves[count].destination = 0;
    count++;

    struct Move * buffer =
            (struct Move *) malloc(sizeof(struct Move) * count);
    (void) memcpy(buffer, moves, sizeof(struct Move) * count);
    return buffer;
}