//
// Created by Graham McKnight on 7/4/2017.
//

//
// Created by gfm13 on 7/1/2017.
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

static int canMoveOrCapture(int * board, int source, int x, int y, int* dest)
{
    int color = board[source] & COLOR;
    if (!isValidPosition(x, y))
    {
        *dest = -1;
        return FALSE;
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
 *                                              int* count);
 * Description: Helper function to count the number of moves that a pawn can
 *              make from a given position.
 * Parameters:
 *      int * board -- The array holding the board state.
 *      int position -- The collapsed position from which to make the move.
 *      int * count -- The current number of moves that can be made from the
 *                     position.
 * Side Effects: Modifies value pointed to by count.
 * Return Value: None.
 */

static void addPawnMoves(int * board, int position, int* count)
{
    int x, y;
    expandPosition(position, &x, & y);
    int color = board[position] & COLOR;
    int destination; // variable that will be used

    int direction = color ? -1 : 1;
    int destY = y + direction;
    if (canMoveOrCapture(board, position, x - 1, destY,
                         &destination) &&
            board[destination] != EMPTY)
    {
        if (destY == 0 || destY == BOARD_WIDTH - 1) {
            (*count)++;
        } else {
            (*count)++;
        }
    }

    if (canMoveOrCapture(board, position, x + 1, destY,
                         &destination) &&
            board[destination] != EMPTY)
    {
        if (destY == 0 || destY == BOARD_WIDTH - 1) {
            (*count)++;
        } else {
            (*count)++;
        }
    }

    if (canMoveOrCapture(board, position, x, destY,
                         &destination) &&
        board[destination] == EMPTY) {
        if (destY == 0 || destY == BOARD_WIDTH - 1) {
            (*count)++;
        } else {
            (*count)++;
        }
    }
}

/*
 * Function Name: addSuperPawnMoves()
 * Function Prototype: static void addSuperPawnMoves(int * board, int position,
 *                                                   int* count);
 * Description: Helper function to count the number of moves that a super pawn
 *              can make from a given position, that a pawn cannot.
 * Parameters:
 *      int * board -- The array holding the board state.
 *      int position -- The collapsed position from which to make the move.
 *      int * count -- The current number of moves that can be made from the
 *                     position.
 * Side Effects: Modifies value pointed to by count.
 * Return Value: None.
 */

static void addSuperPawnMoves(int * board, int position, int* count) {
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
            (*count)++;
        }
    }
}

/*
 * Function Name: addKnightMoves()
 * Function Prototype: static void addKnightMoves(int * board, int position,
 *                                                int* count);
 * Description: Helper function to count the number of moves that a knight can
 *              make from a given position.
 * Parameters:
 *      int * board -- The array holding the board state.
 *      int position -- The collapsed position from which to make the move.
 *      int * count -- The current number of moves that can be made from the
 *                     position.
 * Side Effects: Modifies value pointed to by count.
 * Return Value: None.
 */

static void addKnightMoves(int * board, int position, int* count)
{
    int x, y;
    expandPosition(position, &x, &y);
    int destination; // variable that will be used

    if (canMoveOrCapture(board, position,
                         x - 2, y - 1, &destination)) {
        (*count)++;
    }

    if (canMoveOrCapture(board, position,
                         x - 2, y + 1, &destination)) {
        (*count)++;
    }

    if (canMoveOrCapture(board, position,
                         x + 2, y - 1, &destination)) {
        (*count)++;
    }

    if (canMoveOrCapture(board, position,
                         x + 2, y + 1, &destination)) {
        (*count)++;
    }

    if (canMoveOrCapture(board, position,
                         x - 1, y - 2, &destination)) {
        (*count)++;
    }

    if (canMoveOrCapture(board, position,
                         x - 1, y + 2, &destination)) {
        (*count)++;
    }

    if (canMoveOrCapture(board, position,
                         x + 1, y - 2, &destination)) {
        (*count)++;
    }

    if (canMoveOrCapture(board, position,
                         x + 1, y + 2, &destination)) {
        (*count)++;
    }
}

/*
 * Function Name: addBishopMoves()
 * Function Prototype: static void addBishopMoves(int * board, int position,
 *                                                int* count);
 * Description: Helper function to count the number of moves that a bishop can
 *              make from a given position.
 * Parameters:
 *      int * board -- The array holding the board state.
 *      int position -- The collapsed position from which to make the move.
 *      int * count -- The current number of moves that can be made from the
 *                     position.
 * Side Effects: Modifies value pointed to by count.
 * Return Value: None.
 */

static void addBishopMoves(int * board, int position, int* count) {
    int x, y;
    expandPosition(position, &x, &y);
    int destination; // variable that will be used

    for (int i = 1;; i++) {
        if (canMoveOrCapture(board, position,
                             x + i, y + i, &destination)) {
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
 *                                              int* count);
 * Description: Helper function to count the number of moves that a rook can
 *              make from a given position.
 * Parameters:
 *      int * board -- The array holding the board state.
 *      int position -- The collapsed position from which to make the move.
 *      int * count -- The current number of moves that can be made from the
 *                     position.
 * Side Effects: Modifies value pointed to by count.
 * Return Value: None.
 */

static void addRookMoves(int * board, int position, int* count) {
    int x, y;
    expandPosition(position, &x, &y);
    int destination; // variable that will be used

    for (int i = 1;; i++) {
        if (canMoveOrCapture(board, position,
                             x + i, y, &destination)) {
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
 *                                              int* count);
 * Description: Helper function to count the number of moves that a king can
 *              make from a given position.
 * Parameters:
 *      int * board -- The array holding the board state.
 *      int position -- The collapsed position from which to make the move.
 *      int * count -- The current number of moves that can be made from the
 *                     position.
 * Side Effects: Modifies value pointed to by count.
 * Return Value: None.
 */

static void addKingMoves(int * board, int position, int* count) {
    int x, y;
    expandPosition(position, &x, &y);
    int destination; // variable that will be used

    if (canMoveOrCapture(board, position,
                         x - 1, y - 1, &destination)) {
        (*count)++;
    }

    if (canMoveOrCapture(board, position,
                         x, y - 1, &destination)) {
        (*count)++;
    }

    if (canMoveOrCapture(board, position,
                         x + 1, y - 1, &destination)) {
        (*count)++;
    }

    if (canMoveOrCapture(board, position,
                         x - 1, y, &destination)) {
        (*count)++;
    }

    if (canMoveOrCapture(board, position,
                         x + 1, y, &destination)) {
        (*count)++;
    }

    if (canMoveOrCapture(board, position,
                         x - 1, y + 1, &destination)) {
        (*count)++;
    }

    if (canMoveOrCapture(board, position,
                         x, y + 1, &destination)) {
        (*count)++;
    }

    if (canMoveOrCapture(board, position,
                         x + 1, y + 1, &destination)) {
        (*count)++;
    }
}
/*
 * Function Name: rawMoveCount()
 * Function Prototype: int rawMoveCount(int * board, int position);
 * Description: Gets the total number of moves possible from a given position.
 * Parameters:
 *      int * board -- The array holding the board state.
 *      int position -- The collapsed position from which to make the move.
 * Side Effects: None.
 * Return Value: The number of possible moves that can be made from that
 *               position.
 */

int rawMoveCount(int * board, int position)
{
    int count = 0;


    switch ((board[position] & PIECE_MASK) >> PIECE_OFFSET) {
        case PAWN:
        {
            addPawnMoves(board, position, &count);
            break;
        }

        case SUPER_PAWN:
        {
            addPawnMoves(board, position, &count);
            addSuperPawnMoves(board, position, &count);
            break;
        }

        case KNIGHT:
        {
            addKnightMoves(board, position, &count);
            break;
        }

        case BISHOP:
        {
            addBishopMoves(board, position, &count);
            break;
        }

        case ROOK:
        {
            addRookMoves(board, position, &count);
            break;
        }

        case ARCH_BISHOP:
        {
            addBishopMoves(board, position, &count);
            addKnightMoves(board, position, &count);
            break;
        }

        case QUEEN:
        {
            addRookMoves(board, position, &count);
            addBishopMoves(board, position, &count);
            break;
        }

        case SUPER_QUEEN:
        {
            addRookMoves(board, position, &count);
            addBishopMoves(board, position, &count);
            addKnightMoves(board, position, &count);
            break;
        }

        case KING:
        {
            addKingMoves(board, position, &count);
            break;
        }
    }

    return count;
}