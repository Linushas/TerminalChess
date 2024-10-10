#ifndef MOVES_H
#define MOVES_H

#include "definitions.h"
#include <stdbool.h>

int executeMove(move m, p pieces[], bool nextPlayer);

int in_check(p pieces[]);

int castle(p pieces[], bool nextPlayer, int move_type);

int charInputToIndex(char ch);

void getAvailableMoves(p pieces[], int selected_piece, int board[BOARD_SIZE][BOARD_SIZE]);

int getPiece(p pieces[], int x_pos, int y_pos);

move getMove(p pieces[], bool nextPlayer);

#endif