//
// Created by Graham McKnight on 8/21/2017.
//

#include "engine\chessEngine.h"

#ifndef LOSALAMOSCHESS_CHESSINTERFACE_H
#define LOSALAMOSCHESS_CHESSINTERFACE_H

#define NO_MATE      0
#define STALEMATE    1
#define CHECKMATE    2
#define MATERIAL_TIE 3
#define REPETITION   4
#define MOVE_RULE    5

void initGame();
int checkStatus(int board[BOARD_SIZE], int color);
void computeLegalMoves(int board[BOARD_SIZE], int position);
int getNextLegalMove();
int setAIProperty(char * name, double value, int profile);
int getBestMove(int board[BOARD_SIZE], int white, int profile);

#endif
