//
// Created by Graham McKnight on 7/1/2017.
//

#include <malloc.h>
#include "chessEngine.h"

/*
 * Function Name: inCheck()
 * Function Prototype: bool inCheck(int * board, int color);
 * Description: Determines whether the player of the given color is in check.
 * Parameters:
 *      int * board -- The array holding the board state.
 *      int color -- The bit pattern for the color of the player to check.
 * Side Effects: None.
 * Return Value: True if the player is in check, false otherwise.
 */

bool inCheck(int * board, int color)
{
    // The checker is the opposite of the color of
    // the player we're given.
    int colorOfChecker = !color;
    struct Move * moves = allRawMoves(board, colorOfChecker);

    for (int i = 0; notNullMove(moves[i]); i++)
    {
        if (board[moves[i].destination] ==
                ((KING << PIECE_OFFSET) | color))
        {
            free(moves);
            return true;
        }
    }

    free(moves);
    return false;
}