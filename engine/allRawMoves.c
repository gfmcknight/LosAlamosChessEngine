//
// Created by Graham McKnight on 7/1/2017.
//

#include <malloc.h>

#include "chessEngine.h"

/*
 * Function Name: allRawMoves()
 * Function Prototype: struct Move * allRawMoves(int * board, int color,
 *                                               struct Move * buffer);
 * Description: Compiles all possible moves for every piece for a given
 *              color on the heap.
 * Parameters:
 *      int * board -- The array holding the board state.
 *      int color -- The bit pattern for the color of the player to search for.
 *      struct Move * buffer -- The buffer in which to place the moves. If null,
 *                              then a buffer will be malloc'ed.
 * Side Effects: May allocates memory on the heap.
 * Return Value: A pointer to the nul-terminated array of possible moves.
 */

struct Move * allRawMoves(int * board, int color, struct Move * buffer)
{
    if (buffer == NULL)
    {
        buffer = (struct Move *)
            malloc(sizeof(struct Move) * MOVE_BUFSIZ);
    }

    int length = 0;
    int numAdded = 0;

    for (unsigned int i = 0;
         i < BOARD_SIZE && length < MAX_MOVES; i++)
    {
        if ((board[i] != EMPTY) && (board[i] & COLOR) == color)
        {
            getRawMoves(board, i, &numAdded, buffer + length);
            length += numAdded;
        }
    }
    buffer[length].destination = 0;
    buffer[length].source = 0;
    return buffer;
}