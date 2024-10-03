#ifndef PIECES_H
#define PIECES_H

#include "../definitions.h"

int knight_rules(move m);
int visible_to_knight(p pieces[], p knight, int target_x, int target_y);

int pawn_rules(move m, p pieces[]);
int visible_to_pawn(p pieces[], p pawn, int target_x, int target_y);

int king_rules(move m, p pieces[]);

int bishop_rules(move m, p pieces[]);
int visible_to_bishop(p pieces[], p bishop, int target_x, int target_y);

int queen_rules(move m, p pieces[]);
int visible_to_queen(p pieces[], p queen, int target_x, int target_y);

int rook_rules(move m, p pieces[]);
int visible_to_rook(p pieces[], p rook, int target_x, int target_y);

#endif