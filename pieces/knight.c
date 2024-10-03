#include "pieces.h"
#include "../definitions.h"
#include "../chessboard.h"
#include <stdio.h>
#include <stdlib.h>

int knight_rules(move m)
{
    if(m.direction == KNIGHT) return 1;
    else return 0;
}

int visible_to_knight(p pieces[], p knight, int target_x, int target_y)
{
    int dx = knight.x - target_x, dy = knight.y - target_y;
    if((abs(dx) == 1 && abs(dy) == 2) || (abs(dx) == 2 && abs(dy) == 1))
        return 1;
    else
        return 0;
}

