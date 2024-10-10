#include "pieces.h"
#include "../definitions.h"
#include "../chessboard.h"
#include <stdio.h>
#include <stdlib.h>

int visible_to_pawn(p pieces[], p pawn, int target_x, int target_y)
{
    int i, board[BOARD_SIZE][BOARD_SIZE];
    getBoard(pieces, board);
    int dx = pawn.x - target_x;
    
    i = board[pawn.x][pawn.y];
    if(i < 16)
    {   
        if(pawn.y == 1 && pawn.y + 2 == target_y && dx == 0 && board[target_x][target_y] == EMPTY_COORDINATE)
            return 1;
        else if(pawn.y + 1 == target_y && dx == 0 && board[target_x][target_y] == EMPTY_COORDINATE)
            return 1;
        else if(pawn.y + 1 == target_y && abs(dx) == 1 && board[target_x][target_y] != EMPTY_COORDINATE)
            return 1;
        else
            return 0;  
    }
    else
    {
        if(pawn.y == 6 && pawn.y - 2 == target_y && dx == 0 && board[target_x][target_y] == EMPTY_COORDINATE)
            return 1;
        else if(pawn.y - 1 == target_y && dx == 0 && board[target_x][target_y] == EMPTY_COORDINATE)
            return 1;
        else if(pawn.y - 1 == target_y && abs(dx) == 1 && board[target_x][target_y] != EMPTY_COORDINATE)
            return 1;
        else
            return 0;  
    }
}
