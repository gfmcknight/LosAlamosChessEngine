//
// Created by Graham McKnight on 7/1/2017.
//

#include "chessEngine.h"

/*
 * Function Name: applyMove()
 * Function Prototype: void applyMove(int * board, struct Move move);
 * Description: Makes a given move on the board.
 * Parameters:
 *      int * board -- The array holding the board state.
 *      struct Move move -- The move to apply to the board.
 * Side Effects: Makes a change to the array representing the board.
 * Return Value: None.
 */

void applyMove(int * board, struct Move move)
{
    if (move.promotion != 0)
    {
        board[move.destination] = move.promotion;
    }
    else
    {
        board[move.destination] = board[move.source];
    }

    board[move.source] = EMPTY;
}