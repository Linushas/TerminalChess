#ifndef PIECES_H
#define PIECES_H

#include "../definitions.h"

int visible_to_knight(p pieces[], p knight, int target_x, int target_y);

int visible_to_pawn(p pieces[], p pawn, int target_x, int target_y);

int visible_to_king(p pieces[], p king, int target_x, int target_y);

int visible_to_bishop(p pieces[], p bishop, int target_x, int target_y);

int visible_to_queen(p pieces[], p queen, int target_x, int target_y);

int visible_to_rook(p pieces[], p rook, int target_x, int target_y);

#endif