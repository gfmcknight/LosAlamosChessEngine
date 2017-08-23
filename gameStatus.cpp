//
// Created by Graham McKnight on 8/21/2017.
//

#include <string>

#include "chessInterface.h"
#include "engine\chessEngine.h"

static int previousBoards[MOVE_LIMIT][BOARD_SIZE];
static int boardIndex;
static int prevNumPieces;

void initGame()
{
    boardIndex = 0;
    prevNumPieces = 0;
}

int checkStatus(int board[BOARD_SIZE], bool white)
{
    int color = white ? WHITE : BLACK;

    int repetitions = 1;
    int numPieces = 0;
    int pieces[KING + 1];

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        pieces[(board[i] & PIECE_MASK) >> PIECE_OFFSET]++;
        if (board[i] != EMPTY)
        {
            numPieces++;
        }
    }

    if (numPieces != prevNumPieces)
    {
        prevNumPieces = numPieces;
        boardIndex = 0;
    }

    for (int i = boardIndex - 1; i > 0; i--)
    {
        if (memcmp(board, previousBoards[i], sizeof(int) * BOARD_SIZE) == 0) {
            repetitions++;
            if (repetitions >= MAX_REPETITIONS)
            {
                return REPETITION;
            }
        }
    }

    memcpy(previousBoards[boardIndex++], board, sizeof(int)* BOARD_SIZE);

    if (pieces[PAWN] == 0 && pieces[SUPER_PAWN] == 0 &&
        pieces[ROOK] == 0 && pieces[ARCH_BISHOP] == 0 &&
        pieces[QUEEN] == 0 && pieces[SUPER_QUEEN] == 0)
    {
        if (pieces[KING] == 2)
        {
            if (pieces[KNIGHT] + pieces[BISHOP] < 2)
            {
                return MATERIAL_TIE;
            }
        }
        else if (pieces[KING] == 4)
        {
            if (pieces[KNIGHT] + pieces[BISHOP] == 0)
            {
                return MATERIAL_TIE;
            }
        }
    }

    struct Move * rawMoves = allRawMoves(board, color);
    for (int i = 0; notNullMove(rawMoves[i]); i++) {
        applyMove(board, rawMoves[i]);
        if (!inCheck(board, color)) {
            free(rawMoves);

            if (boardIndex == MOVE_LIMIT)
            {
                return MOVE_RULE;
            }
            else
            {
                return NO_MATE;
            }
        }
        reverseMove(board, rawMoves[i]);
    }

    free(rawMoves);
    if (inCheck(board, color)) {
        return CHECKMATE;
    }
    else {
        return STALEMATE;
    }
}