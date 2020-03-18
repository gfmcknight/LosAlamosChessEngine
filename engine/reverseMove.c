//
// Created by Graham McKnight on 7/1/2017.
//

#include "chessEngine.h"

/*
 * Function Name: reverseMove()
 * Function Prototype: void reverseMove(int * board, struct Move move);
 * Description: Reverses a given move on the board, reverting captures
 *              and promotions.
 * Parameters:
 *      int * board -- The array holding the board state.
 *      struct Move move -- The move to reverse on the board.
 * Side Effects: Makes a change to the array representing the board.
 * Return Value: None.
 */

void reverseMove(int * board, struct Move move)
{
    if (move.promotion != 0)
    {
        int color = move.promotion & COLOR;
        board[move.source] = (PAWN << PIECE_OFFSET) | color;
    }
    else
    {
        board[move.source] = board[move.destination];
    }

    board[move.destination] = move.previousPiece;
}