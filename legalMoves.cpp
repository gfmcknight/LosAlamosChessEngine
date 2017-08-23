//
// Created by Graham McKnight on 8/21/2017.
//

#include <malloc.h>

#include "engine\chessEngine.h"

static struct Move * legalMoves;
static int legalIndex;

void computeLegalMoves(int board[BOARD_SIZE], int position)
{
    legalMoves = getLegalMoves(board, position);
    legalIndex = 0;
}

int getNextLegalMove()
{
    if (!notNullMove(legalMoves[legalIndex]))
    {
        free(legalMoves);
        return -1;
    }
    return legalMoves[legalIndex++].destination;
}