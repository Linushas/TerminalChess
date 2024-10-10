#include "pieces.h"
#include "../definitions.h"
#include "../chessboard.h"
#include <stdio.h>
#include <stdlib.h>

int visible_to_queen(p pieces[], p queen, int target_x, int target_y)
{
    if(visible_to_rook(pieces, queen, target_x, target_y) == 1)
        return 1;
    else if(visible_to_bishop(pieces, queen, target_x, target_y) == 1)
        return 1;
    else
        return 0;
}
