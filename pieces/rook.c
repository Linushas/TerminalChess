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
