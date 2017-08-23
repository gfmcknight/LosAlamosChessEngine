//
// Created by Graham McKnight on 7/1/2017.
//

#include "chessEngine.h"

/*
 * Function Name: collapsePosition()
 * Function Prototype: int collapsePosition(int x, int y);
 * Description: Turns the x and y coordinates of a move into a single index
 *              on the board.
 * Parameters:
 *      int x -- The column on the board.
 *      int y -- The row on the board.
 * Side Effects: None.
 * Return Value: The single index which represents the x and y values.
 */

int collapsePosition(int x, int y)
{
    return x + y * BOARD_WIDTH;
}