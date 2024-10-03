#include "pieces.h"
#include "../definitions.h"
#include "../chessboard.h"
#include <stdio.h>
#include <stdlib.h>

int queen_rules(move m, p pieces[])
{
    int board[BOARD_SIZE][BOARD_SIZE];
    getBoard(pieces, board);

    if(m.direction == UP || m.direction == DOWN || m.direction == LEFT || m.direction == RIGHT)
    {
        if(rook_rules(m, pieces) == 1) return 1;
        else return 0;
    }
    else if(m.direction == UPLEFT || m.direction == DOWNRIGHT || m.direction == DOWNLEFT || m.direction == UPRIGHT)
    {
        if(bishop_rules(m, pieces) == 1) return 1;
        else return 0;
    }
    else return 0;
}

int visible_to_queen(p pieces[], p queen, int target_x, int target_y)
{
    if(visible_to_rook(pieces, queen, target_x, target_y) == 1)
        return 1;
    else if(visible_to_bishop(pieces, queen, target_x, target_y) == 1)
        return 1;
    else
        return 0;
}
