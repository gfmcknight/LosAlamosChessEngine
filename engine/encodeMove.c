//
// Created by Graham McKnight on 7/1/2017.
//

#include "chessEngine.h"

/*
 * Function Name: encodeMove()
 * Function Prototype: struct Move encodeMove(int * board, int source,
                                              int dest, int promote);
 * Description: Encodes a move from one square to another, taking into account
 *              the board state for captures and promotions.
 * Parameters:
 *      int * board -- The array holding the board state.
 *      int square -- The collapsed position that the piece started at.
 *      int dest -- The collapsed position that the piece moved to.
 *      int promote -- The bit pattern for the piece to promote to, or 0 if
 *                     the piece does not promote with this move.
 * Side Effects: None.
 * Return Value: The encoded move.
 */

struct Move encodeMove(int * board, int source, int dest, int promote)
{
    struct Move move;
    move.destination = dest;
    move.source = source;
    move.previousPiece = board[dest];
    if (promote != 0)
    {
        int color = board[source] & COLOR;
        move.promotion = (promote << PIECE_OFFSET) | color;
    }
    else
    {
        move.promotion = 0;
    }

    if (move.previousPiece == EMPTY)
    {
        move.heuristic = -QUEEN;
    }
    else
    {
        move.heuristic = ((move.previousPiece & PIECE_MASK) >> PIECE_OFFSET)
                - ((board[source] & PIECE_MASK) >> PIECE_OFFSET);
    }

    return move;
}