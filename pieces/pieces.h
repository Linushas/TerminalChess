#ifndef PIECES_H
#define PIECES_H

#include "../definitions.h"

int knight_rules(move m);
int pawn_rules(move m, p pieces[]);
int king_rules(move m, p pieces[]);
int bishop_rules(move m, p pieces[]);
int visible_to_bishop(p pieces[], p bishop, int target_x, int target_y);
int queen_rules(move m, p pieces[]);
int rook_rules(move m, p pieces[]);

#endif