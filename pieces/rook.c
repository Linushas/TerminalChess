#include "pieces.h"
#include "../definitions.h"
#include "../chessboard.h"
#include <stdio.h>
#include <stdlib.h>

int rook_rules(move m, p pieces[])
{
    int i, board[BOARD_SIZE][BOARD_SIZE];
    getBoard(pieces, board);
    int deltaY = abs(m.start_y - m.dest_y);
    int deltaX = abs(m.start_x - m.dest_x);

    if(m.direction == DOWN)
    {
        for(i = 1; i < deltaY; i++)
        {
            if(board[m.start_x][m.start_y + i] != EMPTY_COORDINATE)
                return 0;
            
        }
        return 1;
    }
    else if(m.direction == UP)
    {
        for(i = 1; i < deltaY; i++)
        {
            if(board[m.start_x][m.start_y - i] != EMPTY_COORDINATE)
                return 0;
            
        }
        return 1;
    }
    else if(m.direction == RIGHT)
    {
        for(i = 1; i < deltaX; i++)
        {
            if(board[m.start_x + i][m.start_y] != EMPTY_COORDINATE)
                return 0;
            
        }
        return 1;
    }
    else if(m.direction == LEFT)
    {
        for(i = 1; i < deltaX; i++)
        {
            if(board[m.start_x - i][m.start_y] != EMPTY_COORDINATE)
                return 0;
            
        }
        return 1;
    }
    else return 0;
}