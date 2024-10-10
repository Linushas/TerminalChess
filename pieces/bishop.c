#include "pieces.h"
#include "../definitions.h"
#include "../chessboard.h"
#include <stdio.h>
#include <stdlib.h>

int visible_to_bishop(p pieces[], p bishop, int target_x, int target_y)
{
    int i, board[BOARD_SIZE][BOARD_SIZE];
    getBoard(pieces, board);

    int dx = target_x - bishop.x, dy = target_y - bishop.y;
    int x = bishop.x, y = bishop.y;

    if(abs(dx) != abs(dy)) return 0;
    else
    {
        for(i = 1; i <= abs(dx); i++)
        {   
            if(dx > 0 && dy > 0)
            {   
                x = bishop.x + i;   
                y = bishop.y + i;
            }
            else if(dx < 0 && dy < 0)
            {
                x = bishop.x - i;   
                y = bishop.y - i;
            }
            else if(dx > 0 && dy < 0)
            {
                x = bishop.x + i;   
                y = bishop.y - i;
            }
            else if(dx < 0 && dy > 0)
            {
                x = bishop.x - i;   
                y = bishop.y + i;
            }
            if(board[x][y] != EMPTY_COORDINATE){
                break;}
        }
        if(x == target_x && y == target_y)
            return 1;
        else
            return 0;
    }
}
