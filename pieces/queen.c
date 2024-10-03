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