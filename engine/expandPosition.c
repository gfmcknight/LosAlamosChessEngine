//
// Created by Graham McKnight on 7/1/2017.
//

#include "chessEngine.h"

/*
 * Function Name: expandPosition()
 * Function Prototype: void expandPosition(int position, int* x, int* y);
 * Description: Turns the position index into its x and y components.
 * Parameters:
 *      int position -- the position on the board.
 *      int* x -- Pointer to the column on the board.
 *      int* y -- Pointer to the row on the board.
 * Side Effects: Sets the values pointed to by x and y.
 * Return Value: None.
 */

void expandPosition(int position, int* x, int* y)
{
    *x = position % BOARD_WIDTH;
    *y = position / BOARD_WIDTH;
}