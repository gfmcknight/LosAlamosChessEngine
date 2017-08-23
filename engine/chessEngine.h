//
// Created by Graham McKnight on 7/1/2017.
//

#ifndef LOSALAMOSCHESS_CHESSENGINE_H
#define LOSALAMOSCHESS_CHESSENGINE_H

#define EMPTY 0

#define COLOR 1
#define WHITE 0
#define BLACK 1

#define PAWN        1
#define SUPER_PAWN  2
#define KNIGHT      3
#define BISHOP      4
#define ROOK        5
#define ARCH_BISHOP 6
#define QUEEN       7
#define SUPER_QUEEN 8
#define KING        9

#define PIECE_MASK 0x3E
#define PIECE_OFFSET 1

#define BOARD_WIDTH 6
#define BOARD_SIZE  BOARD_WIDTH * BOARD_WIDTH

#define SINGLE_MAX_MOVES 26
#define MAX_MOVES        124
#define MOVE_BUFSIZ      150

#define NUM_PROPERTIES      27
#define SELF_INDEX           0
#define OPPONENT_INDEX      10
#define KING_SAFETY_INDEX   20
#define KING_CENTER_INDEX   21
#define MOBILITY_INDEX      22
#define PAWN_PUSH_INDEX     23
#define CENTER_CUTOFF_INDEX 24
#define DEPTH_INDEX         25
#define Q_DEPTH_INDEX       26

#define NOISE 0.05f

#define CENTER (((double) (BOARD_WIDTH - 1)) / 2.0f)

#define NUM_THREADS 2
#define MAX_PROFILES 2

#define WIN   50000.0f
#define LOSS -50000.0f

#define MAX_REPETITIONS 3
#define MOVE_LIMIT 50

struct Move {
    int source;
    int destination;
    int previousPiece;
    int promotion;
    int heuristic;
};

struct SearchThreadObject {
    int * board;
    Move * moveSet;
    int num;
    int depth;
    int color;
    int profile;
    bool finished;
    double evaluation;
    Move bestMove;
};

extern double evalProfile[NUM_PROPERTIES * MAX_PROFILES];

bool isValidPosition(int x, int y);
int collapsePosition(int x, int y);
void expandPosition(int position, int* x, int* y);
struct Move encodeMove(int * board, int source,
                        int dest, int promote);
void applyMove(int * board, struct Move move);
void reverseMove(int * board, struct Move move);
struct Move * getRawMoves(int * board, int position,
                           int * numMoves, struct Move * buffer);
struct Move * allRawMoves(int * board, int color);
bool inCheck(int * board, int color);
struct Move * getLegalMoves(int * board, int position);
double evaluatePosition(int * board, int color, int evaluator, int profile);
void* search(void* args);
bool notNullMove(struct Move move);
int getEvalPropertyIndex(const char * string);
int rawMoveCount(int * board, int position);
int moveCompare(const void* p1, const void* p2);

#endif //LOSALAMOSCHESS_CHESSENGINE_H
