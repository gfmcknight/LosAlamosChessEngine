//
// Created by Graham McKnight on 7/1/2017.
//

#include <stdlib.h>
#include <cmath>
#include "chessEngine.h"

/*
 * Function Name: evaluatePosition()
 * Function Prototype: double evaluatePosition(int * board, int color,
 *                                             int evaluator);
 * Description: Evaluates the given position based on the profile for the
 *              engine. The sign of the evaluation is based on the player
 *              whose turn it is, but is evaluated from the perspective of
 *              the evaluator.
 * Parameters:
 *      int * board -- The array holding the board state.
 *      int color -- The color of the player who made the last move.
 *      int evaluator -- The color of the AI player evaluating the board.
 * Side Effects: None.
 * Return Value: The value of the position for the player given by color.
 */

double evaluatePosition(int * board, int color, int evaluator, int profile)
{
    double value = ((double)rand() / (double)RAND_MAX) * NOISE - 0.5f * NOISE;
    double material = 0.0f;
    double centralityValue = 0.0f;
    double safetyValue = 0.0f;
    int moveCount;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        // Evaluates to -1 or 1, depending on piece/player color
        int benefitMagnitude = ((board[i] & COLOR) ^ color) * -2 + 1;
        value += benefitMagnitude * evalProfile[profile * NUM_PROPERTIES +
            (OPPONENT_INDEX * ((board[i] & COLOR) ^ evaluator)) +
            ((board[i] & PIECE_MASK) >> PIECE_OFFSET)];

        material += evalProfile[profile * NUM_PROPERTIES +
                (OPPONENT_INDEX * ((board[i] & COLOR) ^ evaluator)) +
                ((board[i] & PIECE_MASK) >> PIECE_OFFSET)];

        moveCount = rawMoveCount(board, i);
        value += moveCount * benefitMagnitude *
                   evalProfile[profile * NUM_PROPERTIES + MOBILITY_INDEX];

        switch ((board[i] & PIECE_MASK) >> PIECE_OFFSET) {
            case PAWN:
            {
                int x, y;
                expandPosition(i, &x, &y);
                value += abs(color * BOARD_WIDTH - y) *
                        evalProfile[profile * NUM_PROPERTIES +
                                    PAWN_PUSH_INDEX];
            }
            case SUPER_PAWN:
            {
                int x, y;
                expandPosition(i, &x, &y);
                value += abs(color * BOARD_WIDTH - y) *
                         evalProfile[profile * NUM_PROPERTIES +
                                     PAWN_PUSH_INDEX];
            }
            case KING:
            {
                int x, y;
                expandPosition(i, &x, &y);
                centralityValue -= benefitMagnitude *
                        (fabs(CENTER - x) + fabs(CENTER - y)) *
                        evalProfile[profile * NUM_PROPERTIES +
                                    KING_CENTER_INDEX];
                safetyValue -= benefitMagnitude * moveCount *
                               evalProfile[profile * NUM_PROPERTIES +
                                           KING_SAFETY_INDEX];
            }
        }
        if (material < evalProfile[profile * NUM_PROPERTIES +
                                   CENTER_CUTOFF_INDEX])
        {
            value += centralityValue;
        }
        else
        {
            value += safetyValue;
        }
    }

    return value;
}