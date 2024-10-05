#ifndef MOVES_H
#define MOVES_H

#include "definitions.h"
#include <stdbool.h>

int executeMove(move m, p pieces[], bool nextPlayer);

int in_check(p pieces[]);

void castle();

int charInputToIndex(char ch);

int getPiece(p pieces[], int x_pos, int y_pos);

move getMove(p pieces[], bool nextPlayer);

#endif