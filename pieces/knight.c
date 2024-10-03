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