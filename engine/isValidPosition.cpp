//
// Created by Graham McKnight on 7/1/2017.
//

#include "chessEngine.h"

/*
 * Function Name: isValidPosition()
 * Function Prototype: bool isValidPosition(int x, int y);
 * Description: Determines whether the given x and y coordinates give a
 *              position that's on the board.
 * Parameters:
 *      int x -- The column on the board.
 *      int y -- The row on the board.
 * Side Effects: None.
 * Return Value: True if the x and y are in the range [0,6)
 */

bool isValidPosition(int x, int y)
{
    return x >= 0 && x < BOARD_WIDTH &&
           y >= 0 && y < BOARD_WIDTH;
}