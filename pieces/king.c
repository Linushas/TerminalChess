#include "pieces.h"
#include "../definitions.h"
#include "../chessboard.h"
#include <stdio.h>
#include <stdlib.h>

int king_rules(move m, p pieces[])
{
    int board[BOARD_SIZE][BOARD_SIZE];
    getBoard(pieces, board);

    int deltaY = abs(m.start_y - m.dest_y);
    int deltaX = abs(m.start_x - m.dest_x);

    if(deltaY <= 1 && deltaX <= 1) return 1;
    else return 0;
}