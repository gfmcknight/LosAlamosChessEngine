//
// Created by Graham McKnight on 7/1/2017.
//

#include <malloc.h>

#include "chessEngine.h"

/*
 * Function Name: allRawMoves()
 * Function Prototype: struct Move * allRawMoves(int * board, int color);
 * Description: Compiles all possible moves for every piece for a given
 *              color on the heap.
 * Parameters:
 *      int * board -- The array holding the board state.
 *      int color -- The bit pattern for the color of the player to search for.
 * Side Effects: Allocates memory on the heap.
 * Return Value: A pointer to the nul-terminated array of possible moves.
 */

struct Move * allRawMoves(int * board, int color)
{
    struct Move * moves = (struct Move *)
            malloc(sizeof(struct Move) * MOVE_BUFSIZ);
    int length = 0;
    int numAdded = 0;

    for (unsigned int i = 0;
         i < BOARD_SIZE && length < MAX_MOVES; i++)
    {
        if ((board[i] != EMPTY) && (board[i] & COLOR) == color)
        {
            getRawMoves(board, i, &numAdded, moves + length);
            length += numAdded;
        }
    }
    moves[length].destination = 0;
    moves[length].source = 0;
    return moves;
}