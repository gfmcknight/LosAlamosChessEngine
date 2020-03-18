//
// Created by Graham McKnight on 7/3/2017.
//

#include "chessEngine.h"

/*
 * Function Name: notNullMove()
 * Function Prototype: bool notNullMove(struct Move move);
 * Description: Verifies that a move is not the terminator in a group.
 * Parameters:
 *      struct Move move -- the move to check.
 * Side Effects: None.
 * Return Value: True if the move is the null move, false otherwise.
 */

int notNullMove(struct Move move)
{
    return move.destination != 0 ||
           move.source != 0;
}