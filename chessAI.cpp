//
// Created by Graham McKnight on 8/21/2017.
//

#include <pthread.h>
#include <unistd.h>
#include <malloc.h>

#include "engine\chessEngine.h"

double evalProfile[NUM_PROPERTIES * MAX_PROFILES];

bool setAIProperty(char * name, double value, int profile)
{
    if (profile >= MAX_PROFILES)
    {
        return false;
    }

    int index = getEvalPropertyIndex(name);

    if (index == -1)
    {
        return false;
    }
    else
    {
        evalProfile[index + (profile * NUM_PROPERTIES)] = value;
        return true;
    }
}

int getBestMove(int board[BOARD_SIZE], bool white, int profile)
{
    if (profile >= MAX_PROFILES)
    {
        return 0;
    }

    int color = white ? WHITE : BLACK;
    
    int cBoard[BOARD_SIZE * NUM_THREADS];
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < NUM_THREADS; j++)
        {
            cBoard[j * BOARD_SIZE + i] = board[i];
        }
    }

    int depth = (int)evalProfile[profile * NUM_PROPERTIES + DEPTH_INDEX];
    
    struct Move * moveSet = allRawMoves(cBoard, color);
    // Get the number of moves
    for (int i = 0; notNullMove(moveSet[i]); i++);

    pthread_t threads[NUM_THREADS];

    struct Move bestMove;
    double bestValue;

    struct SearchThreadObject args[NUM_THREADS];
    
    for (int j = 0; j < NUM_THREADS; j++)
    {
        pthread_create(&threads[j], NULL, search, &args[j]);
    }
    bool working = true;
    while (working)
    {
        working = false;
        sleep(1);
        for (int j = 0; j < NUM_THREADS; j++)
        {
            working = working || !args[j].finished;
        }
    }

    bestMove = args[0].bestMove;
    bestValue = args[0].evaluation;
    for (int j = 0; j < NUM_THREADS; j++)
    {
        if (args[j].evaluation > bestValue)
        {
            bestMove = args[j].bestMove;
            bestValue = args[j].evaluation;
        }
    }

    free(moveSet);
    return bestMove.destination * BOARD_SIZE +
        bestMove.source;
}