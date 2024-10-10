#include "pieces.h"
#include "../definitions.h"
#include "../chessboard.h"
#include <stdio.h>
#include <stdlib.h>

int visible_to_rook(p pieces[], p rook, int target_x, int target_y)
{
    int i, board[BOARD_SIZE][BOARD_SIZE];
    getBoard(pieces, board);

    int dx = target_x - rook.x, dy = target_y - rook.y;
    int x = rook.x, y = rook.y;

    if(abs(dx) == 0 && abs(dy) > 0)
    {
        for(i = 1; i <= abs(dy); i++)
        {   
            if(dx == 0 && dy > 0)
            {   
                x = rook.x;   
                y = rook.y + i;
            }
            else if(dx == 0 && dy < 0)
            {
                x = rook.x;   
                y = rook.y - i;
            }
            if(board[x][y] != EMPTY_COORDINATE)
                break;
        }
        if(x == target_x && y == target_y)
            return 1;
        else
            return 0;
    } 
    else if(abs(dx) > 0 && abs(dy) == 0)
    {
        
        for(i = 1; i <= abs(dx); i++)
        { 
            if(dx > 0 && dy == 0)
            {
                x = rook.x + i;   
                y = rook.y;
            }
            else if(dx < 0 && dy == 0)
            {
                x = rook.x - i;   
                y = rook.y;
            }
            if(board[x][y] != EMPTY_COORDINATE)
                break;
        }
        if(x == target_x && y == target_y)
            return 1;
        else
            return 0;
    }
    else return 0;
}
