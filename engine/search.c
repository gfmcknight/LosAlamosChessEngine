//
// Created by Graham McKnight on 7/2/2017.
//

#include <malloc.h>
#include <stdlib.h>
#include <math.h>

#include "chessEngine.h"

/*
 * Function Name: evaluateMove()
 * Function Prototype: double evaluateMove(int * board, int color, int depth,
 *                                         double alpha, int evaluator);
 * Description: Determines the likeliest board value that will result from the
 *              current position (after a move has been made in the caller).
 *              Employs a recursive negamax search with alpha-bet pruning.
 * Parameters:
 *      int * board -- The array holding the board state.
 *      int color -- The color of the player whose turn it is in this board.
 *      int depth -- The depth in ply to search to.
 *      double alpha -- The value of the best move that the caller was able to
 *                      find so far. If this algorithm finds a move that is
 *                      worse for the caller, then the search terminates in
 *                      this branch.
 *      int profile -- The profile with which to evaluate.
 *      int evaluator -- The perspective from which to evaluate from using the
 *                       evalProfile.
 *      bool capture -- Whether the previous move was a capture.
 * Side Effects: Makes a move on the board and reverses it; allocates memory
 *               and frees it. Not thread safe for a single board.
 * Return Value: The best-worst-case determined by the negamax algorithm.
 */

double evaluateMove(int * board, int color, int depth, double alpha,
                    int profile, int evaluator, int capture)
{
    if (depth <= -evalProfile[profile * NUM_PROPERTIES + Q_DEPTH_INDEX] ||
            (!capture && depth <= 0))
    {
        return evaluatePosition(board, color, evaluator, profile);
    }

    struct Move possibleMoves[MOVE_BUFSIZ];
    allRawMoves(board, color, possibleMoves);

    double bestMoveValue = LOSS;
    double currentValue;
    int isCapture;

    int numMoves;
    for (numMoves = 0; notNullMove(possibleMoves[numMoves]); numMoves++);
    qsort(possibleMoves, numMoves, sizeof(struct Move), moveCompare);

    for (int i = 0; notNullMove(possibleMoves[i]); i++)
    {
        // If we can capture the king, we have won
        if ((board[possibleMoves[i].destination] & PIECE_MASK) >> PIECE_OFFSET
            == KING)
        {
            free(possibleMoves);
            // Adding depth helps to promote quicker checkmates.
            return WIN + depth;
        }
        applyMove(board, possibleMoves[i]);
        isCapture = possibleMoves[i].previousPiece != EMPTY;
        currentValue = -evaluateMove(board, !color, depth - 1, -bestMoveValue,
                                     profile, evaluator, isCapture);
        reverseMove(board, possibleMoves[i]);
        if (currentValue > bestMoveValue)
        {
            bestMoveValue = currentValue;
            if (currentValue > alpha) {
                return currentValue;
            }
        }
    }

    return bestMoveValue;
}

/*
 * Function Name: search()
 * Function Prototype: void* search(void* args);
 * Description: Searches for the best possible move to make given the current
 *              board position, evaluated by the negamax algorithm. Each call
 *              to search() should be in a different thread.
 * Parameters:
 *      void* args -- Pointer to a struct SearchThreadObject with the following
 *                    properties:
 *          int * board -- Pointer to the board for this thread.
 *          Move * moveSet -- Pointer to the first move for this thread to
 *                            analyze.
 *          int num -- The number of moves for this thread to evaluate.
 *          int depth -- The depth in ply to search.
 *          int color -- The color of the current player making the move. ALl
 *                       evaluations are made from the perspective of this
 *                       color.
 *          bool finished -- Set to true when this thread is finished.
 *          double evaluation -- Value of the best move found by this thread.
 *          Move bestMove -- Set to the move that yields the greatest value by
 *                           the negamax algorithm.
 * Side Effects: Allocates and deallocates memory, makes changes to the board
 *               pointed to by the SearchThreadObject and reverses them, and
 *               modifies the SearchThreadObject's finished, evaluation, and
 *               bestMove.
 * Return Value: NULL.
 */
void* search(void* args)
{
    struct SearchThreadObject* object = (struct SearchThreadObject*) args;

    double target = evalProfile[object->profile * NUM_PROPERTIES +
                                TARGET_INDEX];


    struct Move * possibleMoves = object->moveSet;
    struct Move bestMove;
    bestMove.source = bestMove.destination = 0;
    // The worst possible situation is to be in checkmate now
    double bestMoveValue = LOSS - object->depth;
    double currentValue;

    qsort(possibleMoves, object->num, sizeof(struct Move), moveCompare);

    for (int i = 0; i < object->num; i++)
    {
        // If we can capture the king, we have won
        if ((object->board[possibleMoves[i].destination] & PIECE_MASK)
                    >> PIECE_OFFSET == KING)
        {
            object->evaluation = WIN;
            struct Move result = possibleMoves[i];
            object->bestMove = result;
            object->finished = TRUE;
            return NULL;
        }
        applyMove(object->board, possibleMoves[i]);

        int mate = TRUE;
        struct Move* responses = allRawMoves(object->board, !object->color, NULL);

        for (int j = 0; notNullMove(responses[j]); j++)
        {
            applyMove(object->board, responses[j]);
            if (!inCheck(object->board, !object->color))
            {
                mate = FALSE;
                reverseMove(object->board, responses[j]);
                break;
            }
            reverseMove(object->board, responses[j]);
        }

        free(responses);

        if (inCheck(object->board, object->color))
        {
            currentValue = LOSS - object->depth - 1;
        }
        else if (mate)
        {
            if (inCheck(object->board, !object->color))
            {
                object->evaluation = WIN;
                object->bestMove = possibleMoves[i];
                object->finished = TRUE;
                return NULL;
            }
            else
            {
                currentValue = 0;
            }
        }
        else
        {
            currentValue = -evaluateMove(object->board, !object->color,
                object->depth - 1, -bestMoveValue, object->profile,
                object->color, FALSE);
        }


        reverseMove(object->board, possibleMoves[i]);
        // Find the move that most closely approaches the target
        if (fabs(target - currentValue) < fabs(target - bestMoveValue))
        {
            bestMoveValue = currentValue;
            bestMove = possibleMoves[i];
        }
    }

    object->evaluation = bestMoveValue;
    object->bestMove = bestMove;
    object->finished = TRUE;
    return NULL;
}