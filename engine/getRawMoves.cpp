//
// Created by Graham McKnight on 7/1/2017.
//
#include <string.h>
#include <malloc.h>

#include "chessEngine.h"

/*
 * Function Name: canMoveOrCapture()
 * Function Prototype: static bool canMoveOrCapture(int * board, int source,
 *                                                  int x, int y, int* dest);
 * Description: Helper function that checks if a square can be moved to by
 *              a piece. This is done by checking if the destination exists,
 *              and then if not occupied by a piece of the same color.
 * Parameters:
 *      int * board -- The array holding the board state.
 *      int source -- The collapsed position to move from.
 *      int x -- The column on the board to move to.
 *      int y -- The row on the board to move to.
 *      int* dest -- Pointer to the collapsed position to move to.
 * Side Effects: Collapses the position given by x and y and stores that in
 *               the value pointed to by dest.
 * Return Value: True if the piece at the given source can move to the given
 *               destination.
 */

static bool canMoveOrCapture(int * board, int source, int x, int y, int* dest)
{
    int color = board[source] & COLOR;
    if (!isValidPosition(x, y))
    {
        return false;
    }
    else
    {
        *dest = collapsePosition(x, y);
        return board[*dest] == EMPTY ||
               (board[*dest] & COLOR) != color;
    }
}

/*
 * Function Name: addPawnMoves()
 * Function Prototype: static void addPawnMoves(int * board, int position,
 *                                              struct Move * moves,
 *                                              int* count);
 * Description: Helper function to add to the list the moves that a pawn can
 *              make from a given position.
 * Parameters:
 *      int * board -- The array holding the board state.
 *      int position -- The collapsed position from which to make the move.
 *      struct Move * moves -- The buffer holding the moves that can be made
 *                             from the given position.
 *      int * count -- The current number of moves that can be made from the
 *                     position.
 * Side Effects: Modifies value pointed to by count.
 * Return Value: None.
 */

static void addPawnMoves(int * board, int position, struct Move * moves,
                         int* count)
{
    int x, y;
    expandPosition(position, &x, & y);
    int color = board[position] & COLOR;
    int destination; // variable that will be used

    int direction = color ? -1 : 1;
    int destY = y + direction;
    if (canMoveOrCapture(board, position, x - 1, destY,
                         &destination) &&
        board[destination] != EMPTY) {
        if (destY == 0 || destY == BOARD_WIDTH - 1) {
            moves[*count] = encodeMove(board, position,
                                      destination, QUEEN);
            (*count)++;
        } else {
            moves[*count] = encodeMove(board, position,
                                      destination, 0);
            (*count)++;
        }
    }
    if (canMoveOrCapture(board, position, x + 1, destY,
                         &destination) &&
        board[destination] != EMPTY) {
        if (destY == 0 || destY == BOARD_WIDTH - 1) {
            moves[*count] = encodeMove(board, position,
                                      destination, QUEEN);
            (*count)++;
        } else {
            moves[*count] = encodeMove(board, position,
                                      destination, 0);
            (*count)++;
        }
    }
    if (canMoveOrCapture(board, position, x, destY,
                         &destination) &&
        board[destination] == EMPTY) {
        if (destY == 0 || destY == BOARD_WIDTH - 1) {
            moves[*count] = encodeMove(board, position,
                                      destination, QUEEN);
            (*count)++;
        } else {
            moves[*count] = encodeMove(board, position,
                                      destination, 0);
            (*count)++;
        }
    }
}

/*
 * Function Name: addSuperPawnMoves()
 * Function Prototype: static void addSuperPawnMoves(int * board, int position,
 *                                                   struct Move * moves,
 *                                                   int* count);
 * Description: Helper function to add to the list the moves that a super pawn
 *              can make from a given position, that a pawn cannot.
 * Parameters:
 *      int * board -- The array holding the board state.
 *      int position -- The collapsed position from which to make the move.
 *      struct Move * moves -- The buffer holding the moves that can be made
 *                             from the given position.
 *      int * count -- The current number of moves that can be made from the
 *                     position.
 * Side Effects: Modifies value pointed to by count.
 * Return Value: None.
 */

static void addSuperPawnMoves(int * board, int position, struct Move * moves,
                         int* count) {
    int x, y;
    expandPosition(position, &x, &y);
    int color = board[position] & COLOR;
    int destination; // variable that will be used

    int direction = color ? -1 : 1;
    int destY = y - direction;

    if (canMoveOrCapture(board, position, x, destY,
                         &destination) &&
        board[destination] == EMPTY) {
        if (destY != 0 && destY != BOARD_WIDTH - 1) {
            moves[*count] = encodeMove(board, position,
                                       destination, 0);
            (*count)++;
        }
    }
}

/*
 * Function Name: addKnightMoves()
 * Function Prototype: static void addKnightMoves(int * board, int position,
 *                                                struct Move * moves,
 *                                                int* count);
 * Description: Helper function to add to the list the moves that a knight can
 *              make from a given position.
 * Parameters:
 *      int * board -- The array holding the board state.
 *      int position -- The collapsed position from which to make the move.
 *      struct Move * moves -- The buffer holding the moves that can be made
 *                             from the given position.
 *      int * count -- The current number of moves that can be made from the
 *                     position.
 * Side Effects: Modifies value pointed to by count.
 * Return Value: None.
 */

static void addKnightMoves(int * board, int position, struct Move * moves,
                         int* count)
{
    int x, y;
    expandPosition(position, &x, &y);
    int destination; // variable that will be used

    if (canMoveOrCapture(board, position,
                         x - 2, y - 1, &destination)) {
        moves[*count] = encodeMove(board, position,
                                  destination, 0);
        (*count)++;
    }
    if (canMoveOrCapture(board, position,
                         x - 2, y + 1, &destination)) {
        moves[*count] = encodeMove(board, position,
                                  destination, 0);
        (*count)++;
    }
    if (canMoveOrCapture(board, position,
                         x + 2, y - 1, &destination)) {
        moves[*count] = encodeMove(board, position,
                                  destination, 0);
        (*count)++;
    }
    if (canMoveOrCapture(board, position,
                         x + 2, y + 1, &destination)) {
        moves[*count] = encodeMove(board, position,
                                  destination, 0);
        (*count)++;
    }
    if (canMoveOrCapture(board, position,
                         x - 1, y - 2, &destination)) {
        moves[*count] = encodeMove(board, position,
                                  destination, 0);
        (*count)++;
    }
    if (canMoveOrCapture(board, position,
                         x - 1, y + 2, &destination)) {
        moves[*count] = encodeMove(board, position,
                                  destination, 0);
        (*count)++;
    }
    if (canMoveOrCapture(board, position,
                         x + 1, y - 2, &destination)) {
        moves[*count] = encodeMove(board, position,
                                  destination, 0);
        (*count)++;
    }
    if (canMoveOrCapture(board, position,
                         x + 1, y + 2, &destination)) {
        moves[*count] = encodeMove(board, position,
                                  destination, 0);
        (*count)++;
    }
}

/*
 * Function Name: addBishopMoves()
 * Function Prototype: static void addBishopMoves(int * board, int position,
 *                                                struct Move * moves,
 *                                                int* count);
 * Description: Helper function to add to the list the moves that a bishop can
 *              make from a given position.
 * Parameters:
 *      int * board -- The array holding the board state.
 *      int position -- The collapsed position from which to make the move.
 *      struct Move * moves -- The buffer holding the moves that can be made
 *                             from the given position.
 *      int * count -- The current number of moves that can be made from the
 *                     position.
 * Side Effects: Modifies value pointed to by count.
 * Return Value: None.
 */

static void addBishopMoves(int * board, int position, struct Move * moves,
                           int* count) {
    int x, y;
    expandPosition(position, &x, &y);
    int destination; // variable that will be used

    for (int i = 1;; i++) {
        if (canMoveOrCapture(board, position,
                             x + i, y + i, &destination)) {
            moves[*count] = encodeMove(board, position,
                                      destination, 0);
            (*count)++;
            if (board[destination] != EMPTY)
            {
                break;
            }
        } else {
            break;
        }
    }
    for (int i = 1;; i++) {
        if (canMoveOrCapture(board, position,
                             x - i, y + i, &destination)) {
            moves[*count] = encodeMove(board, position,
                                      destination, 0);
            (*count)++;
            if (board[destination] != EMPTY)
            {
                break;
            }
        } else {
            break;
        }
    }
    for (int i = 1;; i++) {
        if (canMoveOrCapture(board, position,
                             x + i, y - i, &destination)) {
            moves[*count] = encodeMove(board, position,
                                      destination, 0);
            (*count)++;
            if (board[destination] != EMPTY)
            {
                break;
            }
        } else {
            break;
        }
    }
    for (int i = 1;; i++) {
        if (canMoveOrCapture(board, position,
                             x - i, y - i, &destination)) {
            moves[*count] = encodeMove(board, position,
                                      destination, 0);
            (*count)++;
            if (board[destination] != EMPTY)
            {
                break;
            }
        } else {
            break;
        }
    }
}

/*
 * Function Name: addRookMoves()
 * Function Prototype: static void addRookMoves(int * board, int position,
 *                                              struct Move * moves,
 *                                              int* count);
 * Description: Helper function to add to the list the moves that a rook can
 *              make from a given position.
 * Parameters:
 *      int * board -- The array holding the board state.
 *      int position -- The collapsed position from which to make the move.
 *      struct Move * moves -- The buffer holding the moves that can be made
 *                             from the given position.
 *      int * count -- The current number of moves that can be made from the
 *                     position.
 * Side Effects: Modifies value pointed to by count.
 * Return Value: None.
 */

static void addRookMoves(int * board, int position, struct Move * moves,
                           int* count) {
    int x, y;
    expandPosition(position, &x, &y);
    int destination; // variable that will be used

    for (int i = 1;; i++) {
        if (canMoveOrCapture(board, position,
                             x + i, y, &destination)) {
            moves[*count] = encodeMove(board, position,
                                      destination, 0);
            (*count)++;
            if (board[destination] != EMPTY)
            {
                break;
            }
        } else {
            break;
        }
    }
    for (int i = 1;; i++) {
        if (canMoveOrCapture(board, position,
                             x - i, y, &destination)) {
            moves[*count] = encodeMove(board, position,
                                      destination, 0);
            (*count)++;
            if (board[destination] != EMPTY)
            {
                break;
            }
        } else {
            break;
        }
    }
    for (int i = 1;; i++) {
        if (canMoveOrCapture(board, position,
                             x, y + i, &destination)) {
            moves[*count] = encodeMove(board, position,
                                      destination, 0);
            (*count)++;
            if (board[destination] != EMPTY)
            {
                break;
            }
        } else {
            break;
        }
    }
    for (int i = 1;; i++) {
        if (canMoveOrCapture(board, position,
                             x, y - i, &destination)) {
            moves[*count] = encodeMove(board, position,
                                      destination, 0);
            (*count)++;
            if (board[destination] != EMPTY)
            {
                break;
            }
        } else {
            break;
        }
    }
}

/*
 * Function Name: addKingMoves()
 * Function Prototype: static void addKingMoves(int * board, int position,
 *                                              struct Move * moves,
 *                                              int* count);
 * Description: Helper function to add to the list the moves that a king can
 *              make from a given position.
 * Parameters:
 *      int * board -- The array holding the board state.
 *      int position -- The collapsed position from which to make the move.
 *      struct Move * moves -- The buffer holding the moves that can be made
 *                             from the given position.
 *      int * count -- The current number of moves that can be made from the
 *                     position.
 * Side Effects: Modifies value pointed to by count.
 * Return Value: None.
 */

static void addKingMoves(int * board, int position, struct Move * moves,
                         int* count) {
    int x, y;
    expandPosition(position, &x, &y);
    int destination; // variable that will be used

    if (canMoveOrCapture(board, position,
                         x - 1, y - 1, &destination)) {
        moves[*count] = encodeMove(board, position,
                                  destination, 0);
        (*count)++;
    }
    if (canMoveOrCapture(board, position,
                         x, y - 1, &destination)) {
        moves[*count] = encodeMove(board, position,
                                  destination, 0);
        (*count)++;
    }
    if (canMoveOrCapture(board, position,
                         x + 1, y - 1, &destination)) {
        moves[*count] = encodeMove(board, position,
                                  destination, 0);
        (*count)++;
    }
    if (canMoveOrCapture(board, position,
                         x - 1, y, &destination)) {
        moves[*count] = encodeMove(board, position,
                                  destination, 0);
        (*count)++;
    }
    if (canMoveOrCapture(board, position,
                         x + 1, y, &destination)) {
        moves[*count] = encodeMove(board, position,
                                  destination, 0);
        (*count)++;
    }
    if (canMoveOrCapture(board, position,
                         x - 1, y + 1, &destination)) {
        moves[*count] = encodeMove(board, position,
                                  destination, 0);
        (*count)++;
    }
    if (canMoveOrCapture(board, position,
                         x, y + 1, &destination)) {
        moves[*count] = encodeMove(board, position,
                                  destination, 0);
        (*count)++;
    }
    if (canMoveOrCapture(board, position,
                         x + 1, y + 1, &destination)) {
        moves[*count] = encodeMove(board, position,
                                  destination, 0);
        (*count)++;
    }
}

/*
 * Function Name: getRawMoves()
 * Function Prototype: struct Move * getRawMoves(int * board, int position,
 *                                      int* numMoves, struct Move * buffer);
 * Description: Gets the set of moves the piece at the given position can make.
 * Parameters:
 *      int * board -- The array holding the board state.
 *      int position -- The collapsed position from which to make the move.
 *      int* numMoves -- Pointer to the number of moves created by this
 *                       function.
 *      struct Move * buffer -- The buffer to write moves to.
 * Side Effects: Modifies the contents of the buffer, or allocates memory if
 *               null. Sets the value pointed to by numMoves to the number of
 *               moves added.
 * Return Value: Pointer to the buffer where the moves were placed.
 */

struct Move * getRawMoves(int * board, int position,
                           int* numMoves, struct Move * buffer)
{
    struct Move moves[SINGLE_MAX_MOVES];
    int count = 0;

    switch ((board[position] & PIECE_MASK) >> PIECE_OFFSET) {
        case PAWN:
        {
            addPawnMoves(board, position, moves, &count);
            break;
        }

        case SUPER_PAWN:
        {
            addPawnMoves(board, position, moves, &count);
            addSuperPawnMoves(board, position, moves, &count);
            break;
        }

        case KNIGHT:
        {
            addKnightMoves(board, position, moves, &count);
            break;
        }

        case BISHOP:
        {
            addBishopMoves(board, position, moves, &count);
            break;
        }

        case ROOK:
        {
            addRookMoves(board, position, moves, &count);
            break;
        }

        case ARCH_BISHOP:
        {
            addBishopMoves(board, position, moves, &count);
            addKnightMoves(board, position, moves, &count);
            break;
        }

        case QUEEN:
        {
            addRookMoves(board, position, moves, &count);
            addBishopMoves(board, position, moves, &count);
            break;
        }

        case SUPER_QUEEN:
        {
            addRookMoves(board, position, moves, &count);
            addBishopMoves(board, position, moves, &count);
            addKnightMoves(board, position, moves, &count);
            break;
        }

        case KING:
        {
            addKingMoves(board, position, moves, &count);
            break;
        }
    }

    *numMoves = count;
    if (buffer == NULL)
    {
        buffer = (struct Move *) malloc(sizeof(struct Move) * count);
    }
    (void) memcpy(buffer, moves, sizeof(struct Move) * count);
    return buffer;
}