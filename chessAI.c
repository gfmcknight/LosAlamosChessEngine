//
// Created by Graham McKnight on 8/21/2017.
//

#include <malloc.h>

#include "engine\chessEngine.h"

double evalProfile[NUM_PROPERTIES * MAX_PROFILES];

int setAIProperty(char * name, double value, int profile)
{
    if (profile >= MAX_PROFILES)
    {
        return FALSE;
    }

    int index = getEvalPropertyIndex(name);

    if (index == -1)
    {
        return FALSE;
    }
    else
    {
        evalProfile[index + (profile * NUM_PROPERTIES)] = value;
        return TRUE;
    }
}

int getBestMove(int board[BOARD_SIZE], int white, int profile)
{
    if (profile >= MAX_PROFILES)
    {
        return 0;
    }

    int color = white ? WHITE : BLACK;
    
    int cBoard[BOARD_SIZE];
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        cBoard[i] = board[i];
    }

    int depth = (int)evalProfile[profile * NUM_PROPERTIES + DEPTH_INDEX];
    
    struct Move * moveSet = allRawMoves(cBoard, color, NULL);

    // Get the number of moves
    int nMoves;
    for (nMoves = 0; notNullMove(moveSet[nMoves]); nMoves++);

    if (nMoves == 0) {
        free(moveSet);
        return 0;
    }

    struct Move bestMove;
    double bestValue;

    struct SearchThreadObject args;

    args.moveSet = moveSet;
    args.finished = FALSE;
    args.board = cBoard;
    args.num = nMoves;
    args.color = color;
    args.depth = depth;
    args.profile = profile;

    search(&args);

    bestMove = args.bestMove;

    free(moveSet);
    return bestMove.destination * BOARD_SIZE +
        bestMove.source;
}